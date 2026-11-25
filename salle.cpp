#include "salle.h"
#include "ui_salle.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>
#include <QDate>
#include <QDateEdit>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QRegularExpression>
#include <QSet>
#include <QPageLayout>
#include <QBuffer>
#include <QImage>
#include <QClipboard>
#include <QPagedPaintDevice>
#include <QAbstractTextDocumentLayout>
#include <QDir>
#include <algorithm>
#include <cmath>
#include <functional>

#include <QPushButton>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QScrollArea>
#include <QScrollBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QFrame>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QMap>
#include <QTimer>
#include <QGroupBox>
#include <QApplication>
#include <QStyle>

// ---- Nayuki QR Code generator ----
#include "qrcodegen.hpp"

// ---- ZXing-C++ (Scan d'image) ----
#include "ReadBarcode.h"
#include "ReaderOptions.h"
#include "BarcodeFormat.h"

/* ============================================================
 *  HELPERS — Oracle + Palette Sombre HACKNOVA
 * ============================================================ */
namespace {

QSqlDatabase dbHacknova()
{
    QSqlDatabase db = QSqlDatabase::database("hacknova_connection", false);
    if (db.isValid() && !db.isOpen()) {
        if (!db.open())
            qDebug() << "Réouverture Oracle échouée :" << db.lastError().text();
    }
    return db;
}

QString sqlStr(const QVariant &v)
{
    return v.isNull() ? QString() : v.toString().trimmed();
}

QString normaliserDisponibilite(const QString &brute)
{
    const QString v = brute.trimmed();
    if (v.compare("Disponible",   Qt::CaseInsensitive) == 0) return "Disponible";
    if (v.compare("Indisponible", Qt::CaseInsensitive) == 0) return "Indisponible";
    if (v.compare("Occupée",      Qt::CaseInsensitive) == 0) return "Indisponible";
    if (v.compare("Maintenance",  Qt::CaseInsensitive) == 0) return "Indisponible";
    return "Indisponible";
}

QColor couleurDisponibilite(bool disponible)
{
    return disponible ? QColor("#34D399") : QColor("#F87171");
}

namespace Palette {
const QString fond       = "#0B0F1A";
const QString carte      = "#111827";
const QString carteAlt   = "#1E293B";
const QString bordure    = "#334155";
const QString texte      = "#F1F5F9";
const QString texteMuted = "#94A3B8";
const QString texteDim   = "#64748B";
const QString accent     = "#4338CA";
const QString accentGlow = "#818CF8";
const QString accentDark = "#1E1B4B";
const QString succes     = "#10B981";
const QString succesDark = "#059669";
const QString danger     = "#EF4444";
const QString dangerDark = "#DC2626";
const QString warning    = "#F59E0B";
}

void parserNomSalle(const QString &nom, QString &bloc, int &etage, int &numero)
{
    const QStringList parts = nom.split("-");
    if (parts.size() == 3) {
        bloc   = parts[0];
        etage  = parts[1].toInt();
        numero = parts[2].toInt();
    } else {
        bloc.clear();
        etage  = 0;
        numero = 0;
    }
}

/* ============================================================
 *  COMPOSANT PRO EMBED MESSAGE — Rendu officiel structuré
 * ============================================================ */
QString construireEmbedHtml(const QString &accentHex,
                            const QString &badgeTexte,
                            const QString &titre,
                            const QString &sousTitre,
                            const QString &corpsHtml,
                            const QString &engagementHtml = QString(),
                            const QString &piedHtml = QString())
{
    QString html = QString(
                       "<div style='background-color:#151D2E;border:1px solid #2A3852;"
                       "border-left:4px solid %1;border-radius:10px;padding:12px 15px;'>"
                       "<div style='margin-bottom:6px;'>"
                       "<span style='background-color:%1;color:#FFFFFF;font-size:9px;font-weight:900;"
                       "letter-spacing:0.8px;padding:2px 8px;border-radius:4px;'>%2</span>"
                       "</div>"
                       "<div style='color:#F8FAFC;font-size:13px;font-weight:800;margin-bottom:3px;'>%3</div>")
                       .arg(accentHex, badgeTexte.toHtmlEscaped(), titre.toHtmlEscaped());

    if (!sousTitre.isEmpty()) {
        html += QString("<div style='color:#94A3B8;font-size:11px;margin-bottom:8px;'>%1</div>")
        .arg(sousTitre.toHtmlEscaped());
    }

    html += QString("<div style='color:#E2E8F0;font-size:12px;line-height:1.45;'>%1</div>")
                .arg(corpsHtml);

    if (!engagementHtml.isEmpty()) {
        html += QString(
                    "<div style='margin-top:9px;padding-top:8px;border-top:1px solid #26334A;"
                    "color:#A5B4FC;font-size:11px;font-style:italic;'>%1</div>")
                    .arg(engagementHtml);
    }

    if (!piedHtml.isEmpty()) {
        html += QString(
                    "<div style='margin-top:7px;color:#64748B;font-size:10px;'>%1</div>")
                    .arg(piedHtml);
    }

    html += "</div>";
    return html;
}

QFrame *creerCarteEmbed(QWidget *parent,
                        const QString &accentHex,
                        const QString &badgeTexte,
                        const QString &titre,
                        const QString &sousTitre,
                        const QString &corpsHtml,
                        const QString &engagementHtml = QString(),
                        const QString &piedHtml = QString())
{
    auto *card = new QFrame(parent);
    card->setStyleSheet(QString(
                            "QFrame { background-color:#151D2E; border:1px solid #2A3852;"
                            "border-left:4px solid %1; border-radius:10px; }")
                            .arg(accentHex));

    auto *lay = new QVBoxLayout(card);
    lay->setContentsMargins(14, 11, 14, 11);
    lay->setSpacing(4);

    auto *topRow = new QHBoxLayout;
    auto *badge = new QLabel(badgeTexte.toUpper(), card);
    badge->setStyleSheet(QString(
                             "background-color:%1; color:#FFFFFF; font-size:9px; font-weight:900;"
                             "letter-spacing:0.8px; padding:3px 8px; border-radius:4px; border:none;")
                             .arg(accentHex));
    topRow->addWidget(badge, 0, Qt::AlignLeft);

    if (!sousTitre.isEmpty()) {
        auto *sub = new QLabel(sousTitre, card);
        sub->setStyleSheet("color:#94A3B8; font-size:10px; font-weight:600; border:none; background:transparent;");
        topRow->addStretch();
        topRow->addWidget(sub);
    }
    lay->addLayout(topRow);

    auto *lblTitle = new QLabel(titre, card);
    lblTitle->setStyleSheet("color:#F8FAFC; font-size:13px; font-weight:800; border:none; background:transparent;");
    lblTitle->setWordWrap(true);
    lay->addWidget(lblTitle);

    auto *lblBody = new QLabel(corpsHtml, card);
    lblBody->setTextFormat(Qt::RichText);
    lblBody->setStyleSheet("color:#E2E8F0; font-size:12px; border:none; background:transparent;");
    lblBody->setWordWrap(true);
    lay->addWidget(lblBody);

    if (!engagementHtml.isEmpty()) {
        auto *line = new QFrame(card);
        line->setFrameShape(QFrame::HLine);
        line->setStyleSheet("background-color:#26334A; max-height:1px; border:none; margin:3px 0;");
        lay->addWidget(line);

        auto *lblEng = new QLabel(engagementHtml, card);
        lblEng->setTextFormat(Qt::RichText);
        lblEng->setStyleSheet("color:#A5B4FC; font-size:11px; font-style:italic; border:none; background:transparent;");
        lblEng->setWordWrap(true);
        lay->addWidget(lblEng);
    }

    if (!piedHtml.isEmpty()) {
        auto *lblFoot = new QLabel(piedHtml, card);
        lblFoot->setTextFormat(Qt::RichText);
        lblFoot->setStyleSheet("color:#64748B; font-size:10px; border:none; background:transparent;");
        lblFoot->setWordWrap(true);
        lay->addWidget(lblFoot);
    }

    return card;
}

} // namespace

/* ============================================================
 *  STYLES HELPERS STATIQUES (MODE SOMBRE)
 * ============================================================ */
QString salle::styleBouton(const QString &couleur, const QString &hover,
                           const QString &texte)
{
    return QString(
               "QPushButton { background-color:%1; %2 border:none; border-radius:8px;"
               " font-weight:800; font-size:11px; padding:0 14px; min-height:34px; }"
               "QPushButton:hover { background-color:%3; }"
               "QPushButton:pressed { padding-top:2px; }")
        .arg(couleur, texte, hover);
}

QString salle::styleCarte()
{
    return QString("QFrame { background-color:%1; border:1px solid %2; border-radius:12px; }")
    .arg(Palette::carte, Palette::bordure);
}

QString salle::styleChamp()
{
    return QString("background-color:%1; color:%2; border:1px solid %3;"
                   "border-radius:8px; padding:0 10px; min-height:34px;")
        .arg(Palette::carteAlt, Palette::texte, Palette::bordure);
}

QString salle::styleTitreSection()
{
    return QString("color:%1; font-weight:800; font-size:13px;").arg(Palette::accentGlow);
}

/* ============================================================
 *  CONSTRUCTEUR / DESTRUCTEUR
 * ============================================================ */
salle::salle(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::salle)
{
    ui->setupUi(this);

    QSqlDatabase db;
    if (QSqlDatabase::contains("hacknova_connection")) {
        db = QSqlDatabase::database("hacknova_connection");
    } else {
        db = QSqlDatabase::addDatabase("QODBC", "hacknova_connection");
        db.setDatabaseName("HACKNOVA");
        db.setUserName("rayen");
        db.setPassword("rayen");
    }

    if (!db.isOpen()) {
        if (db.open())
            qDebug() << "Connexion Oracle réussie.";
        else {
            qDebug() << "Erreur de connexion Oracle :" << db.lastError().text();
            QMessageBox::critical(this, "Connexion Oracle",
                                  "Impossible de se connecter à la base Oracle :\n" +
                                      db.lastError().text() + "\n\nLes tableaux resteront vides.");
        }
    }

    if (ui->comboBoxSalleType && ui->lineEditSalleTypeAutre) {
        QObject::connect(ui->comboBoxSalleType, &QComboBox::currentTextChanged,
                         this, [this](const QString &text) {
                             bool isAutre = (text.compare("Autre", Qt::CaseInsensitive) == 0);
                             ui->lineEditSalleTypeAutre->setVisible(isAutre);
                             if (isAutre) ui->lineEditSalleTypeAutre->setFocus();
                         });
    }

    ui->stackedWidget->setCurrentIndex(0);

    organiserPageSalles();
    appliquerThemeSombre();
    connecterLogin();
    connecterNavigation();
    connecterChatbot();
    connecterActions();

    remplirTableSalles();
    dessinerStatistiquesSalles();
    mettreAJourTableauDeBordBas();
}

salle::~salle()
{
    if (m_debounceRechercheSalle) {
        m_debounceRechercheSalle->stop();
    }

    if (QSqlDatabase::contains("hacknova_connection")) {
        {
            QSqlDatabase db = QSqlDatabase::database("hacknova_connection", false);
            if (db.isOpen()) db.close();
        }
        QSqlDatabase::removeDatabase("hacknova_connection");
    }
    delete ui;
}

/* ============================================================
 *  ORGANISATION PAGE SALLES :
 *  - 2 boutons métiers en haut
 *  - Réorganisation statistiques (H & V + %)
 *  - Tri ASC/DESC + recherche instantanée
 * ============================================================ */
void salle::organiserPageSalles()
{
    if (!ui->scrollSallesContent) return;
    auto *parent = ui->scrollSallesContent;
    parent->setMinimumSize(1440, 1080);
    if (ui->scrollSalles) {
        ui->scrollSalles->setWidgetResizable(true);
    }

    if (!m_btnMetierAffectation) {
        m_btnMetierAffectation = new QPushButton("🎯 Métier 1 : Affectation intelligente", parent);
        m_btnMetierAffectation->setGeometry(810, 92, 290, 36);
        m_btnMetierAffectation->setCursor(Qt::PointingHandCursor);
        m_btnMetierAffectation->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));
        QObject::connect(m_btnMetierAffectation, &QPushButton::clicked,
                         this, &salle::ouvrirEspaceMetierAffectation);
    }

    if (!m_btnMetierQR) {
        m_btnMetierQR = new QPushButton("📱 Métier 2 : QR Code & Accès", parent);
        m_btnMetierQR->setGeometry(1110, 92, 300, 36);
        m_btnMetierQR->setCursor(Qt::PointingHandCursor);
        m_btnMetierQR->setStyleSheet(styleBouton(Palette::accent, Palette::accentDark));
        QObject::connect(m_btnMetierQR, &QPushButton::clicked,
                         this, &salle::ouvrirEspaceMetierQR);
    }

    if (ui->lineEdit_2) {
        ui->lineEdit_2->setGeometry(10, 325, 310, 38);
        ui->lineEdit_2->setPlaceholderText("Recherche instantanée par ID (partiel) ou nom...");
    }
    if (ui->btnRechercherSalle) {
        ui->btnRechercherSalle->setGeometry(330, 328, 115, 34);
    }

    if (!m_comboChampTri) {
        m_comboChampTri = new QComboBox(parent);
        m_comboChampTri->setGeometry(455, 328, 155, 34);
        m_comboChampTri->addItem("ID Salle", "ID");
        m_comboChampTri->addItem("Nom Salle", "NOM");
        m_comboChampTri->addItem("Capacité", "CAPACITE");
        m_comboChampTri->addItem("Type", "TYPE");
        m_comboChampTri->addItem("Disponibilité", "DISPONIBILITE");
        m_comboChampTri->addItem("Fin période", "DATE_FIN");
        m_comboChampTri->setStyleSheet(styleChamp());
        QObject::connect(m_comboChampTri, &QComboBox::currentIndexChanged,
                         this, &salle::onTriRapideChange);
    }

    if (!m_comboSensTri) {
        m_comboSensTri = new QComboBox(parent);
        m_comboSensTri->setGeometry(618, 328, 165, 34);
        m_comboSensTri->addItem("Croissant (ASC)", true);
        m_comboSensTri->addItem("Décroissant (DESC)", false);
        m_comboSensTri->setStyleSheet(styleChamp());
        QObject::connect(m_comboSensTri, &QComboBox::currentIndexChanged,
                         this, &salle::onTriRapideChange);
    }

    if (ui->btnTrierSalle) {
        ui->btnTrierSalle->setGeometry(792, 328, 125, 34);
        ui->btnTrierSalle->setText("FILTRES / TRI");
    }
    if (ui->btnExporterSalle) {
        ui->btnExporterSalle->setGeometry(925, 328, 125, 34);
    }

    if (ui->cardTableSalles) {
        ui->cardTableSalles->setGeometry(10, 385, 981, 470);
    }
    if (ui->tableSalles) {
        ui->tableSalles->setGeometry(15, 40, 951, 415);
    }

    if (ui->sallesPage_cardStats) {
        ui->sallesPage_cardStats->setGeometry(1000, 155, 412, 700);
        if (ui->sallesPage_labelStatutPie) ui->sallesPage_labelStatutPie->hide();
        if (ui->sallesPage_labelRoleBar)   ui->sallesPage_labelRoleBar->hide();

        if (!m_lblStatsResume) {
            m_lblStatsResume = new QLabel(ui->sallesPage_cardStats);
            m_lblStatsResume->setGeometry(16, 36, 380, 82);
            m_lblStatsResume->setWordWrap(true);
            m_lblStatsResume->setTextFormat(Qt::RichText);
        }
        if (!m_lblBarHorizontale) {
            m_lblBarHorizontale = new QLabel(ui->sallesPage_cardStats);
            m_lblBarHorizontale->setGeometry(16, 126, 380, 270);
        }
        if (!m_lblBarVerticale) {
            m_lblBarVerticale = new QLabel(ui->sallesPage_cardStats);
            m_lblBarVerticale->setGeometry(16, 406, 380, 280);
        }
    }

    if (!m_frameBottomDashboard) {
        m_frameBottomDashboard = new QFrame(parent);
        m_frameBottomDashboard->setGeometry(10, 868, 1402, 74);
        m_frameBottomDashboard->setStyleSheet(styleCarte());

        auto *hl = new QHBoxLayout(m_frameBottomDashboard);
        hl->setContentsMargins(18, 10, 18, 10);
        hl->setSpacing(18);

        auto makeIndic = [&](const QString &titre, const QString &couleur) -> QLabel* {
            auto *lbl = new QLabel(m_frameBottomDashboard);
            lbl->setTextFormat(Qt::RichText);
            lbl->setStyleSheet(QString(
                                   "background:%1; border:1px solid %2; border-radius:8px; padding:6px 12px; color:%3;")
                                   .arg(Palette::carteAlt, Palette::bordure, couleur));
            lbl->setText(QString("<b>%1 :</b> --").arg(titre));
            hl->addWidget(lbl, 1);
            return lbl;
        };

        m_lblDashTotal  = makeIndic("Total salles", Palette::accentGlow);
        m_lblDashDispo  = makeIndic("Disponibles", Palette::succes);
        m_lblDashOccupe = makeIndic("Occupées", Palette::danger);
        m_lblDashTaux   = makeIndic("Taux dispo", Palette::warning);
        m_lblDashMaj    = makeIndic("Dernière MAJ", Palette::texteMuted);
    }

    if (ui->labelFooterSalles) {
        ui->labelFooterSalles->setGeometry(14, 950, 1200, 22);
    }
}

/* ============================================================
 *  HISTORIQUE OFFICIEL & EMBED MESSAGES AUTOMATIQUES
 * ============================================================ */
void salle::enregistrerHistorique(qint64 idSalle, const QString &categorie,
                                  const QString &detail, const QString &engagement)
{
    if (idSalle <= 0) return;

    EntreeHistoriqueSalle entree;
    entree.dateHeure  = QDateTime::currentDateTime();
    entree.categorie  = categorie.trimmed().toUpper();
    entree.detail     = detail.trimmed();
    entree.engagement = engagement.trimmed();

    m_historiqueSalles[idSalle].prepend(entree);
}

QString salle::genererMessageAutoConsultation(const Salle &s) const
{
    const QString etatOfficiel = s.estDisponible()
    ? QString("La direction opérationnelle HACKNOVA certifie que la salle <b>%1</b> est déclarée "
              "<span style='color:#34D399;font-weight:700;'>DISPONIBLE</span> et prête pour l'accueil d'une équipe ou d'un atelier.")
            .arg(s.nom.toHtmlEscaped())
    : QString("La direction opérationnelle HACKNOVA signale que la salle <b>%1</b> est actuellement "
              "<span style='color:#F87171;font-weight:700;'>INDISPONIBLE</span> ; toute affectation doit vérifier le planning actif.")
            .arg(s.nom.toHtmlEscaped());

    const QString recommandation = (s.capacite >= 25)
                                       ? QString("Dimensionnement validé pour sessions plénières, ateliers collaboratifs ou présentations (%1 places).")
                                             .arg(s.capacite)
                                       : QString("Dimensionnement adapté pour cellule projet, sprint technique ou session dédiée (%1 places).")
                                             .arg(s.capacite);

    return QString("%1<br><span style='color:#94A3B8;'>%2</span>").arg(etatOfficiel, recommandation);
}

QString salle::genererMessageAutoQR(const Salle &s, const QString &mode) const
{
    const QString statut = s.estDisponible() ? "DISPONIBLE" : "INDISPONIBLE";
    if (mode == "scan") {
        return QString("Contrôle d'accès QR validé auprès du référentiel Oracle pour la salle <b>%1</b> "
                       "(Identifiant #%2 · Capacité : %3 places · État : <b>%4</b>).")
            .arg(s.nom.toHtmlEscaped()).arg(s.id).arg(s.capacite).arg(statut.toHtmlEscaped());
    }
    return QString("Émission officielle du jeton QR d'identification pour la salle <b>%1</b> "
                   "(Identifiant #%2 · Catégorie : %3 · État : <b>%4</b>).")
        .arg(s.nom.toHtmlEscaped()).arg(s.id).arg(s.type.toHtmlEscaped()).arg(statut.toHtmlEscaped());
}

QString salle::genererMessageAutoAffectation(const Salle &s, const QDate &dDeb,
                                             const QDate &dFin, int duree,
                                             int effectif, const QString &projet) const
{
    const QString nomProj = projet.trimmed().isEmpty() ? "Session Hackathon Officielle" : projet.trimmed();
    return QString("Affectation officielle enregistrée : la salle <b>%1</b> est attribuée au projet "
                   "<b>« %2 »</b> pour <b>%3 participant(s)</b> (capacité : %4 places), "
                   "du <b>%5</b> au <b>%6</b> (durée : <b>%7 jour(s)</b>).")
        .arg(s.nom.toHtmlEscaped(), nomProj.toHtmlEscaped())
        .arg(effectif).arg(s.capacite)
        .arg(dDeb.toString("dd/MM/yyyy"), dFin.toString("dd/MM/yyyy"))
        .arg(duree);
}

void salle::ouvrirHistoriqueSalle(qint64 idSalle)
{
    const auto opt = chargerSalle(idSalle);
    const QString nomSalle = opt.has_value() ? opt->nom : QString("Salle #%1").arg(idSalle);

    QDialog dlg(this);
    dlg.setWindowTitle(QString("Historique Officiel — %1").arg(nomSalle));
    dlg.setMinimumSize(760, 600);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(14);

    // En-tête Embed officiel de l'historique
    auto *headerEmbed = creerCarteEmbed(
        &dlg,
        Palette::accentGlow,
        "REGISTRE OFFICIEL D'ACTIVITÉ",
        QString("Historique certifié — Salle %1 (ID #%2)").arg(nomSalle).arg(idSalle),
        QString("Édité le %1").arg(QDateTime::currentDateTime().toString("dd/MM/yyyy à HH:mm")),
        QString("Traçabilité complète des opérations, attributions de période, vérifications QR "
                "et engagements administratifs rattachés à la salle <b>%1</b>.")
            .arg(nomSalle.toHtmlEscaped()),
        QString("<b>Clause de traçabilité :</b> Toute opération consignée engage la responsabilité "
                "de l'administration HACKNOVA."),
        "Système HACKNOVA · Smart Hackathon Management");
    lay->addWidget(headerEmbed);

    QVector<EntreeHistoriqueSalle> entries = m_historiqueSalles.value(idSalle);

    if (opt.has_value() && opt->dateDebut.isValid() && opt->dureeJours > 0) {
        bool dejaPresent = false;
        for (const auto &e : entries) {
            if (e.categorie == "AFFECTATION") { dejaPresent = true; break; }
        }
        if (!dejaPresent) {
            EntreeHistoriqueSalle act;
            act.dateHeure  = QDateTime::currentDateTime();
            act.categorie  = "AFFECTATION";
            act.detail     = QString("Attribution active enregistrée pour <b>« %1 »</b> "
                                 "du <b>%2</b> au <b>%3</b> (<b>%4 jour(s)</b>).")
                             .arg((opt->projetAssocie.isEmpty() ? "Hackathon" : opt->projetAssocie).toHtmlEscaped(),
                                  opt->dateDebut.toString("dd/MM/yyyy"),
                                  opt->dateFin.toString("dd/MM/yyyy"))
                             .arg(opt->dureeJours);
            act.engagement = genererEngagementAdmin(*opt);
            entries.prepend(act);
        }
    }

    // Zone scrollable de cartes Embed modernes
    auto *scroll = new QScrollArea(&dlg);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("QScrollArea { background:transparent; }");

    auto *listWidget = new QWidget(&dlg);
    listWidget->setStyleSheet("background:transparent;");
    auto *listLay = new QVBoxLayout(listWidget);
    listLay->setContentsMargins(0, 2, 6, 2);
    listLay->setSpacing(10);

    if (entries.isEmpty()) {
        auto *emptyCard = creerCarteEmbed(
            listWidget,
            Palette::texteMuted,
            "AUCUNE ENTRÉE",
            "Aucune activité consignée sur cette session",
            QString("Salle %1").arg(nomSalle),
            "Aucune action n'a encore été enregistrée pour cette salle depuis le démarrage de la session.",
            "Les consultations de fiche, générations/scans de QR Code et affectations s'inscrivent automatiquement ici.");
        listLay->addWidget(emptyCard);
    } else {
        for (const auto &e : entries) {
            QString badgeCol = Palette::accentGlow;
            QString titreEntree = "Événement salle";
            if (e.categorie == "AFFECTATION") {
                badgeCol = Palette::warning;
                titreEntree = "Attribution de salle & planification";
            } else if (e.categorie == "AJOUT") {
                badgeCol = Palette::succes;
                titreEntree = "Création officielle de la salle";
            } else if (e.categorie == "MODIFICATION") {
                badgeCol = Palette::accentGlow;
                titreEntree = "Mise à jour des paramètres & disponibilité";
            } else if (e.categorie == "QR") {
                badgeCol = "#38BDF8";
                titreEntree = "Opération QR Code & contrôle d'accès";
            } else if (e.categorie == "CONSULTATION") {
                badgeCol = "#A78BFA";
                titreEntree = "Consultation de la fiche Oracle";
            }

            const QString engHtml = e.engagement.isEmpty()
                                        ? QString()
                                        : QString("<b>Engagement officiel :</b> %1").arg(e.engagement.toHtmlEscaped());

            auto *itemCard = creerCarteEmbed(
                listWidget,
                badgeCol,
                e.categorie,
                titreEntree,
                e.dateHeure.toString("dd/MM/yyyy · HH:mm:ss"),
                e.detail,
                engHtml,
                QString("Référence salle : %1 (ID #%2)").arg(nomSalle.toHtmlEscaped()).arg(idSalle));
            listLay->addWidget(itemCard);
        }
    }
    listLay->addStretch();
    scroll->setWidget(listWidget);
    lay->addWidget(scroll, 1);

    auto *btns = new QHBoxLayout;
    btns->setSpacing(10);

    auto *btnExportHist = new QPushButton("📄 EXPORTER L'HISTORIQUE (.HTML)", &dlg);
    btnExportHist->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    QObject::connect(btnExportHist, &QPushButton::clicked, &dlg, [&, nomSalle, entries]() {
        const QString chemin = QFileDialog::getSaveFileName(
            &dlg, "Exporter l'historique officiel",
            QString("historique_salle_%1_%2.html")
                .arg(nomSalle, QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")),
            "Fichiers HTML (*.html)");
        if (chemin.isEmpty()) return;

        QString docHtml = QString(
                              "<!DOCTYPE html><html><head><meta charset='utf-8'/>"
                              "<title>Historique Officiel — %1</title>"
                              "<style>body{font-family:'Segoe UI',Arial,sans-serif;background:#0B0F1A;color:#F1F5F9;padding:28px;}"
                              "h1{color:#818CF8;margin-bottom:4px;}.meta{color:#94A3B8;font-size:12px;margin-bottom:20px;}"
                              ".card{background:#151D2E;border:1px solid #2A3852;border-left:4px solid #818CF8;"
                              "border-radius:10px;padding:14px 18px;margin-bottom:14px;}"
                              ".badge{display:inline-block;background:#4338CA;color:#FFF;font-size:10px;font-weight:800;"
                              "padding:2px 8px;border-radius:4px;margin-bottom:6px;}"
                              ".date{color:#94A3B8;font-size:11px;float:right;}"
                              ".eng{margin-top:10px;padding-top:8px;border-top:1px solid #26334A;color:#A5B4FC;font-style:italic;font-size:12px;}"
                              "</style></head><body>"
                              "<h1>Historique Officiel — Salle %1 (ID #%2)</h1>"
                              "<div class='meta'>Document officiel généré le %3 · HACKNOVA</div>")
                              .arg(nomSalle.toHtmlEscaped())
                              .arg(idSalle)
                              .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy à HH:mm:ss"));

        for (const auto &e : entries) {
            docHtml += QString(
                           "<div class='card'><span class='badge'>%1</span>"
                           "<span class='date'>%2</span>"
                           "<div>%3</div>%4</div>")
                           .arg(e.categorie.toHtmlEscaped(),
                                e.dateHeure.toString("dd/MM/yyyy HH:mm:ss").toHtmlEscaped(),
                                e.detail,
                                e.engagement.isEmpty()
                                    ? QString()
                                    : QString("<div class='eng'>%1</div>").arg(e.engagement.toHtmlEscaped()));
        }
        docHtml += "</body></html>";

        QFile f(chemin);
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&f);
            out.setEncoding(QStringConverter::Utf8);
            out << docHtml;
            f.close();
            QMessageBox::information(&dlg, "Export réussi",
                                     QString("L'historique officiel a été enregistré :\n%1").arg(chemin));
        }
    });

    auto *btnFermer = new QPushButton("FERMER", &dlg);
    btnFermer->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));
    QObject::connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);

    btns->addWidget(btnExportHist);
    btns->addStretch();
    btns->addWidget(btnFermer);
    lay->addLayout(btns);

    dlg.exec();
}

/* ============================================================
 *  CALCUL DYNAMIQUE DES DATES ET DE LA DISPONIBILITÉ
 * ============================================================ */
void salle::calculerDisponibiliteAutomatique(Salle &s) const
{
    const QDate aujourdHui = QDate::currentDate();
    s.disponibilite = normaliserDisponibilite(s.disponibilite);
    bool dispoBase = (s.disponibilite.compare("Disponible", Qt::CaseInsensitive) == 0);

    const auto it = m_periodesSession.constFind(s.id);
    if (it != m_periodesSession.constEnd() && it->dateDebut.isValid() && it->dureeJours > 0) {
        s.dateDebut     = it->dateDebut;
        s.dureeJours    = it->dureeJours;
        s.dateFin       = it->dateFin();
        s.projetAssocie = it->projet;

        const bool occupeeAujourdHui = it->estActiveLe(aujourdHui);
        if (occupeeAujourdHui) {
            s.disponibleAuto = false;
            s.disponibilite  = "Indisponible";
            return;
        }
        s.disponibleAuto = dispoBase;
        s.disponibilite  = dispoBase ? "Disponible" : "Indisponible";
        return;
    }

    s.dateDebut     = QDate();
    s.dureeJours    = 0;
    s.dateFin       = QDate();
    s.projetAssocie.clear();
    s.disponibleAuto = dispoBase;
}

/* ============================================================
 *  CONNEXIONS DES ACTIONS
 * ============================================================ */
void salle::connecterActions()
{
    if (ui->btnAjouterSalle)
        QObject::connect(ui->btnAjouterSalle, &QPushButton::clicked,
                         this, &salle::onAjouterSalle);
    if (ui->btnAnnuler)
        QObject::connect(ui->btnAnnuler, &QPushButton::clicked,
                         this, &salle::onAnnulerSalle);
    if (ui->btnRechercherSalle)
        QObject::connect(ui->btnRechercherSalle, &QPushButton::clicked,
                         this, &salle::onRechercherSalle);
    if (ui->btnTrierSalle)
        QObject::connect(ui->btnTrierSalle, &QPushButton::clicked,
                         this, &salle::ouvrirDialogueTri);
    if (ui->btnExporterSalle)
        QObject::connect(ui->btnExporterSalle, &QPushButton::clicked,
                         this, &salle::ouvrirDialogueExport);

    if (ui->lineEdit_2) {
        QObject::connect(ui->lineEdit_2, &QLineEdit::returnPressed,
                         this, &salle::onRechercherSalle);

        if (!m_debounceRechercheSalle) {
            m_debounceRechercheSalle = new QTimer(this);
            m_debounceRechercheSalle->setSingleShot(true);
            m_debounceRechercheSalle->setInterval(180);
            QObject::connect(m_debounceRechercheSalle, &QTimer::timeout,
                             this, &salle::onRechercheDynamiqueSalle);
        }
        QObject::connect(ui->lineEdit_2, &QLineEdit::textChanged,
                         this, [this](const QString &) {
                             if (m_debounceRechercheSalle)
                                 m_debounceRechercheSalle->start();
                         });
    }
}

/* ============================================================
 *  CONTRÔLE DE SAISIE
 * ============================================================ */
ResultatValidation salle::validerSaisieSalle(const Salle &s, const QString &typeAutre) const
{
    if (s.capacite <= 0)
        return ResultatValidation::erreur("La capacité doit être strictement positive.", 0);

    if (s.type.compare("Autre", Qt::CaseInsensitive) == 0 && typeAutre.trimmed().isEmpty())
        return ResultatValidation::erreur("Veuillez préciser le type de salle (champ Autre).", 1);

    if (s.numeroSalle < 1 || s.numeroSalle > 15)
        return ResultatValidation::erreur("Le numéro de salle doit être entre 1 et 15.", 2);

    if (s.etage < 1 || s.etage > 3)
        return ResultatValidation::erreur("L'étage doit être entre 1 et 3.", 3);

    return ResultatValidation::ok();
}

void salle::focusChampFautif(int champFautif)
{
    switch (champFautif) {
    case 0: if (ui->spinBoxSalleCapacite)   ui->spinBoxSalleCapacite->setFocus();   break;
    case 1: if (ui->lineEditSalleTypeAutre) ui->lineEditSalleTypeAutre->setFocus(); break;
    case 2: if (ui->spinBoxSalleNumero)     ui->spinBoxSalleNumero->setFocus();     break;
    case 3: if (ui->spinBoxSalleEtage)      ui->spinBoxSalleEtage->setFocus();      break;
    default: break;
    }
}

/* ============================================================
 *  LECTURE SALLE / UNICITÉ / TYPES
 * ============================================================ */
std::optional<Salle> salle::chargerSalle(qint64 idSalle) const
{
    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return std::nullopt;

    QSqlQuery q(db);
    q.prepare("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE "
              "FROM SALLE WHERE ID_SALLE = :id");
    q.bindValue(":id", QString::number(idSalle), QSql::In);

    if (!q.exec() || !q.next()) return std::nullopt;

    Salle s;
    s.id            = q.value(0).toLongLong();
    s.nom           = sqlStr(q.value(1));
    s.capacite      = q.value(2).toInt();
    s.type          = sqlStr(q.value(3));
    s.disponibilite = sqlStr(q.value(4));
    parserNomSalle(s.nom, s.bloc, s.etage, s.numeroSalle);
    calculerDisponibiliteAutomatique(s);
    return s;
}

bool salle::nomSalleExiste(const QString &nom, qint64 idExclu) const
{
    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    if (idExclu > 0) {
        q.prepare("SELECT COUNT(*) FROM SALLE "
                  "WHERE UPPER(TRIM(NOM_SALLE)) = UPPER(TRIM(:nom)) "
                  "  AND ID_SALLE <> :idExclu");
        q.bindValue(":idExclu", QString::number(idExclu), QSql::In);
    } else {
        q.prepare("SELECT COUNT(*) FROM SALLE "
                  "WHERE UPPER(TRIM(NOM_SALLE)) = UPPER(TRIM(:nom))");
    }
    q.bindValue(":nom", nom, QSql::In);
    if (!q.exec() || !q.next()) return false;
    return q.value(0).toInt() > 0;
}

QStringList salle::typesSalleDisponibles() const
{
    QSet<QString> types;
    if (ui->comboBoxSalleType) {
        for (int i = 0; i < ui->comboBoxSalleType->count(); ++i) {
            const QString t = ui->comboBoxSalleType->itemText(i).trimmed();
            if (!t.isEmpty()) types.insert(t);
        }
    }
    QSqlDatabase db = dbHacknova();
    if (db.isValid() && db.isOpen()) {
        QSqlQuery q(db);
        if (q.exec("SELECT DISTINCT TYPE_SALLE FROM SALLE WHERE TYPE_SALLE IS NOT NULL")) {
            while (q.next()) types.insert(sqlStr(q.value(0)));
        }
    }
    return types.values();
}

/* ============================================================
 *  CREATE — Ajouter une salle (Disponibilité incrémentée auto)
 * ============================================================ */
void salle::onAjouterSalle()
{
    if (!ui->comboBoxSalleBloc || !ui->spinBoxSalleEtage ||
        !ui->spinBoxSalleNumero || !ui->spinBoxSalleCapacite) return;

    Salle s;
    s.bloc        = ui->comboBoxSalleBloc->currentText();
    s.etage       = ui->spinBoxSalleEtage->value();
    s.numeroSalle = ui->spinBoxSalleNumero->value();
    s.capacite    = ui->spinBoxSalleCapacite->value();

    s.disponibilite = "Disponible";
    if (ui->comboBoxSalleDispo) {
        int idxDispo = ui->comboBoxSalleDispo->findText("Disponible", Qt::MatchFixedString);
        if (idxDispo >= 0) ui->comboBoxSalleDispo->setCurrentIndex(idxDispo);
    }

    QString typeBase  = ui->comboBoxSalleType->currentText();
    QString typeAutre = ui->lineEditSalleTypeAutre->text().trimmed();
    s.type = (typeBase.compare("Autre", Qt::CaseInsensitive) == 0) ? typeAutre : typeBase;

    s.nom = QString("%1-%2-%3").arg(s.bloc).arg(s.etage).arg(s.numeroSalle, 2, 10, QChar('0'));

    const ResultatValidation v = validerSaisieSalle(s, typeAutre);
    if (!v.valide) {
        QMessageBox::warning(this, "Ajouter une salle", v.message);
        focusChampFautif(v.champFautif);
        return;
    }

    if (nomSalleExiste(s.nom)) {
        QMessageBox::warning(this, "Ajouter une salle",
                             QString("La salle « %1 » existe déjà.").arg(s.nom));
        return;
    }

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen() || !db.transaction()) {
        QMessageBox::critical(this, "Ajouter une salle", "Connexion Oracle indisponible.");
        return;
    }

    QSqlQuery q(db);
    q.prepare("INSERT INTO SALLE "
              "(ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE) "
              "VALUES (SEQ_SALLE.NEXTVAL, :nom, :cap, :type, :dispo)");
    q.bindValue(":nom",   s.nom,           QSql::In);
    q.bindValue(":cap",   s.capacite,      QSql::In);
    q.bindValue(":type",  s.type,          QSql::In);
    q.bindValue(":dispo", s.disponibilite, QSql::In);

    if (!q.exec()) {
        db.rollback();
        QMessageBox::warning(this, "Ajouter une salle", "Insertion échouée :\n" + q.lastError().text());
        return;
    }
    if (!db.commit()) {
        db.rollback();
        QMessageBox::warning(this, "Ajouter une salle", "Commit échoué.");
        return;
    }

    qint64 newId = 0;
    QSqlQuery qId(db);
    if (qId.exec("SELECT SEQ_SALLE.CURRVAL FROM DUAL") && qId.next()) {
        newId = qId.value(0).toLongLong();
    }

    ++m_compteurSallesDisponibles;
    if (newId > 0) {
        s.id = newId;
        enregistrerHistorique(newId, "AJOUT",
                              QString("Création officielle de la salle <b>%1</b> (%2 · %3 places · État : <b>Disponible</b>).")
                                  .arg(s.nom.toHtmlEscaped(), s.type.toHtmlEscaped()).arg(s.capacite),
                              genererEngagementAdmin(s));
    }

    QMessageBox::information(this, "Notification Officielle — Création de salle",
                             QString("La salle <b>%1</b> a été enregistrée avec succès dans Oracle.<br>"
                                     "Statut initial attribué : <b>Disponible</b> (compteur d'ajout : +%2).")
                                 .arg(s.nom.toHtmlEscaped())
                                 .arg(m_compteurSallesDisponibles));
    viderFormulaireSalle();
    rafraichirSallesEtStats();
}

/* ============================================================
 *  UPDATE — Modifier une salle + gestion période/dates
 * ============================================================ */
void salle::ouvrirModificationSalle(qint64 idSalle)
{
    const auto opt = chargerSalle(idSalle);
    if (!opt.has_value()) {
        QMessageBox::warning(this, "Modifier une salle", "Salle introuvable.");
        return;
    }
    const Salle s = *opt;

    QDialog dlg(this);
    dlg.setWindowTitle(QString("Modifier la salle %1").arg(s.nom));
    dlg.setMinimumWidth(480);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(12);

    auto *titre = new QLabel(QString("<h2 style='color:%1;margin:0;'>%2</h2>")
                                 .arg(Palette::accentGlow, s.nom.toHtmlEscaped()));
    lay->addWidget(titre);

    auto *form = new QFormLayout;
    form->setSpacing(10);

    auto *spCap = new QSpinBox(&dlg);
    spCap->setRange(1, 9999);
    spCap->setValue(s.capacite);
    spCap->setStyleSheet(styleChamp());

    auto *cbType = new QComboBox(&dlg);
    cbType->addItems(typesSalleDisponibles());
    int idx = cbType->findText(s.type, Qt::MatchFixedString);
    if (idx >= 0) cbType->setCurrentIndex(idx);
    else { cbType->addItem(s.type); cbType->setCurrentIndex(cbType->count() - 1); }
    cbType->setStyleSheet(styleChamp());

    auto *edAutre = new QLineEdit(&dlg);
    edAutre->setText(s.type);
    edAutre->setStyleSheet(styleChamp());
    edAutre->setVisible(false);

    QObject::connect(cbType, &QComboBox::currentTextChanged, [&](const QString &txt){
        bool isAutre = (txt.compare("Autre", Qt::CaseInsensitive) == 0);
        edAutre->setVisible(isAutre);
        if (!isAutre) edAutre->setText("");
    });

    auto *cbDispo = new QComboBox(&dlg);
    cbDispo->addItems({"Disponible", "Indisponible"});
    cbDispo->setCurrentIndex(s.estDisponible() ? 0 : 1);
    cbDispo->setStyleSheet(styleChamp());

    auto *edProjet = new QLineEdit(&dlg);
    edProjet->setPlaceholderText("Projet / événement (optionnel)");
    edProjet->setText(s.projetAssocie);
    edProjet->setStyleSheet(styleChamp());

    auto *dtDebut = new QDateEdit(&dlg);
    dtDebut->setCalendarPopup(true);
    dtDebut->setDisplayFormat("dd/MM/yyyy");
    dtDebut->setDate(s.dateDebut.isValid() ? s.dateDebut : QDate::currentDate());
    dtDebut->setStyleSheet(styleChamp());

    auto *spDuree = new QSpinBox(&dlg);
    spDuree->setRange(0, 365);
    spDuree->setSuffix(" jour(s)");
    spDuree->setValue(s.dureeJours);
    spDuree->setStyleSheet(styleChamp());

    auto *lblFinCalc = new QLabel(&dlg);
    lblFinCalc->setStyleSheet(QString("color:%1;font-weight:700;").arg(Palette::accentGlow));

    auto majFinCalculee = [&]() {
        if (spDuree->value() <= 0) {
            lblFinCalc->setText("Aucune période active (disponibilité selon statut BD)");
        } else {
            const QDate fin = dtDebut->date().addDays(spDuree->value() - 1);
            const bool activeToday = (QDate::currentDate() >= dtDebut->date() && QDate::currentDate() <= fin);
            lblFinCalc->setText(QString("Fin calculée : %1 (%2)")
                                    .arg(fin.toString("dd/MM/yyyy"),
                                         activeToday ? "Indisponible aujourd'hui" : "Hors période aujourd'hui"));
        }
    };
    majFinCalculee();
    QObject::connect(dtDebut, &QDateEdit::dateChanged, &dlg, [&](const QDate &){ majFinCalculee(); });
    QObject::connect(spDuree, &QSpinBox::valueChanged, &dlg, [&](int){ majFinCalculee(); });

    form->addRow("Capacité :",        spCap);
    form->addRow("Type :",            cbType);
    form->addRow("Précisez :",        edAutre);
    form->addRow("État de base :",    cbDispo);
    form->addRow("Projet associé :",   edProjet);
    form->addRow("Date début :",      dtDebut);
    form->addRow("Durée :",           spDuree);
    form->addRow("Période / Dispo :", lblFinCalc);
    lay->addLayout(form);

    auto *btns = new QHBoxLayout;
    btns->addStretch();
    auto *btnAnnuler = new QPushButton("Annuler", &dlg);
    btnAnnuler->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    auto *btnValider = new QPushButton("Enregistrer", &dlg);
    btnValider->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    btns->addWidget(btnAnnuler);
    btns->addWidget(btnValider);
    lay->addLayout(btns);

    QObject::connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);
    QObject::connect(btnValider, &QPushButton::clicked, [&]() {
        QString finalType = cbType->currentText();
        if (finalType == "Autre" && !edAutre->text().isEmpty())
            finalType = edAutre->text().trimmed();

        const QDate dDeb = dtDebut->date();
        const int dur = spDuree->value();

        if (dur > 0) {
            for (auto it = m_periodesSession.constBegin(); it != m_periodesSession.constEnd(); ++it) {
                if (it.key() == idSalle) continue;
                if (it->chevauche(dDeb, dur)) {
                    QMessageBox::warning(&dlg, "Chevauchement détecté",
                                         QString("Conflit de période avec la salle ID %1 (%2 → %3).")
                                             .arg(it.key())
                                             .arg(it->dateDebut.toString("dd/MM/yyyy"))
                                             .arg(it->dateFin().toString("dd/MM/yyyy")));
                    return;
                }
            }
        }

        QString dispoFinale = cbDispo->currentText();
        if (dur > 0) {
            const QDate dFin = dDeb.addDays(dur - 1);
            if (QDate::currentDate() >= dDeb && QDate::currentDate() <= dFin) {
                dispoFinale = "Indisponible";
            }
        }

        QSqlDatabase db2 = dbHacknova();
        if (!db2.transaction()) return;

        QSqlQuery u(db2);
        u.prepare("UPDATE SALLE SET CAPACITE = :cap, TYPE_SALLE = :type, "
                  "DISPONIBILITE = :dispo WHERE ID_SALLE = :id");
        u.bindValue(":cap",   spCap->value());
        u.bindValue(":type",  finalType);
        u.bindValue(":dispo", dispoFinale);
        u.bindValue(":id",    QString::number(idSalle));

        if (!u.exec()) {
            db2.rollback();
            QMessageBox::warning(&dlg, "Erreur", u.lastError().text());
            return;
        }
        db2.commit();

        const QString projTrim = edProjet->text().trimmed();
        if (dur > 0) {
            PeriodeReservation p;
            p.dateDebut  = dDeb;
            p.dureeJours = dur;
            p.projet     = projTrim;
            m_periodesSession[idSalle] = p;
        } else {
            m_periodesSession.remove(idSalle);
        }

        Salle modSalle = s;
        modSalle.capacite = spCap->value();
        modSalle.type = finalType;
        modSalle.disponibilite = dispoFinale;

        enregistrerHistorique(idSalle, "MODIFICATION",
                              QString("Mise à jour officielle : capacité <b>%1 places</b>, catégorie <b>%2</b>, "
                                      "état <b>%3</b>%4.")
                                  .arg(spCap->value()).arg(finalType.toHtmlEscaped(), dispoFinale.toHtmlEscaped())
                                  .arg(dur > 0 ? QString(", période <b>%1 → %2</b> (projet : <b>%3</b>)")
                                                     .arg(dDeb.toString("dd/MM/yyyy"),
                                                          dDeb.addDays(dur - 1).toString("dd/MM/yyyy"),
                                                          (projTrim.isEmpty() ? "Projet" : projTrim).toHtmlEscaped())
                                               : QString(", sans période planifiée")),
                              genererEngagementAdmin(modSalle));

        dlg.accept();
        rafraichirSallesEtStats();
        QMessageBox::information(this, "Notification Officielle — Mise à jour",
                                 QString("Les paramètres de la salle <b>%1</b> ont été mis à jour avec succès.")
                                     .arg(s.nom.toHtmlEscaped()));
    });

    dlg.exec();
}

/* ============================================================
 *  DELETE — Supprimer une salle
 * ============================================================ */
void salle::ouvrirSuppressionSalle(qint64 idSalle, const QString &nomSalle)
{
    if (QMessageBox::question(this, "Supprimer une salle",
                              QString("Supprimer définitivement « %1 » ?").arg(nomSalle),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen() || !db.transaction()) return;

    QSqlQuery q(db);
    q.prepare("DELETE FROM SALLE WHERE ID_SALLE = :id");
    q.bindValue(":id", QString::number(idSalle), QSql::In);

    if (!q.exec() || !db.commit()) {
        db.rollback();
        QMessageBox::warning(this, "Supprimer une salle", "Suppression impossible.");
        return;
    }
    m_periodesSession.remove(idSalle);
    m_historiqueSalles.remove(idSalle);
    QMessageBox::information(this, "Notification Officielle — Suppression",
                             QString("La salle <b>%1</b> a été retirée du référentiel.")
                                 .arg(nomSalle.toHtmlEscaped()));
    rafraichirSallesEtStats();
}

/* ============================================================
 *  READ — Consulter une salle (Embeds officiels + Historique)
 * ============================================================ */
void salle::ouvrirConsultationSalle(qint64 idSalle)
{
    const auto opt = chargerSalle(idSalle);
    if (!opt.has_value()) {
        QMessageBox::warning(this, "Consultation salle",
                             QString("Aucune salle trouvée pour l'ID %1.").arg(idSalle));
        return;
    }
    const Salle &s = *opt;
    const PayloadQR payload = construirePayloadQR(s);
    const QString msgOfficielVoir = genererMessageAutoConsultation(s);

    enregistrerHistorique(idSalle, "CONSULTATION",
                          QString("Consultation officielle de la fiche salle <b>%1</b> (état : <b>%2</b>).")
                              .arg(s.nom.toHtmlEscaped(), s.disponibilite.toHtmlEscaped()),
                          payload.engagementAdmin);

    QDialog dlg(this);
    dlg.setWindowTitle(QString("Fiche Officielle — %1").arg(s.nom));
    dlg.setMinimumSize(700, 740);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(12);

    auto *header = new QHBoxLayout;
    auto *titre = new QLabel(QString(
                                 "<div style='font-size:22px;font-weight:900;color:%1;'>%2</div>"
                                 "<div style='font-size:11px;color:%3;margin-top:2px;'>Identifiant #%4 · %5 places · %6</div>")
                                 .arg(Palette::accentGlow, s.nom.toHtmlEscaped(), Palette::texteMuted)
                                 .arg(s.id).arg(s.capacite).arg(s.type.toHtmlEscaped()));
    titre->setTextFormat(Qt::RichText);
    header->addWidget(titre, 1);

    const QString dispoColor = s.estDisponible() ? Palette::succesDark : Palette::dangerDark;
    const QString dispoTexte = s.estDisponible() ? "DISPONIBLE" : "INDISPONIBLE / OCCUPÉE";
    auto *badge = new QLabel(dispoTexte);
    badge->setStyleSheet(QString(
                             "background:%1; color:#FFFFFF; font-weight:900; font-size:10px;"
                             "padding:6px 14px; border-radius:12px;").arg(dispoColor));
    header->addWidget(badge, 0, Qt::AlignTop);
    lay->addLayout(header);

    auto *infos = new QFrame;
    infos->setStyleSheet(styleCarte());
    auto *infosLay = new QVBoxLayout(infos);
    infosLay->setContentsMargins(18, 12, 18, 12);

    auto row = [&](const QString &k, const QString &v) {
        auto *h = new QHBoxLayout;
        auto *lk = new QLabel(k);
        lk->setStyleSheet(QString("color:%1;font-weight:700;font-size:11px;")
                              .arg(Palette::accentGlow));
        auto *lv = new QLabel(v);
        lv->setStyleSheet(QString("color:%1;font-size:12px;").arg(Palette::texte));
        lv->setWordWrap(true);
        h->addWidget(lk, 0, Qt::AlignTop);
        h->addSpacing(16);
        h->addWidget(lv, 1);
        infosLay->addLayout(h);
    };
    row("Bloc / Étage / N°", QString("%1 · étage %2 · n° %3")
                                 .arg(s.bloc).arg(s.etage).arg(s.numeroSalle, 2, 10, QChar('0')));
    row("Capacité",          QString("%1 places").arg(s.capacite));
    row("Type",              s.type);
    row("Disponibilité",     s.disponibilite);
    row("Date système",      QDate::currentDate().toString("dd/MM/yyyy"));
    if (s.dateDebut.isValid() && s.dureeJours > 0) {
        row("Projet / Période", QString("%1 — Du %2 au %3 (%4 j)")
                                    .arg(s.projetAssocie.isEmpty() ? "Réservation active" : s.projetAssocie,
                                         s.dateDebut.toString("dd/MM/yyyy"),
                                         s.dateFin.toString("dd/MM/yyyy"))
                                    .arg(s.dureeJours));
    } else {
        row("Projet / Réservation", "Aucune période active enregistrée");
    }
    lay->addWidget(infos);

    // Embed 1 : Message officiel & diagnostic d'exploitation
    auto *embedEtat = creerCarteEmbed(
        &dlg,
        s.estDisponible() ? Palette::succes : Palette::warning,
        "MESSAGE OFFICIEL · ÉTAT D'EXPLOITATION",
        QString("Rapport d'état — Salle %1").arg(s.nom),
        QDate::currentDate().toString("dd/MM/yyyy"),
        msgOfficielVoir + "<br>" + payload.remarqueAuto.toHtmlEscaped());
    lay->addWidget(embedEtat);

    // Embed 2 : Avis administratif & Engagement officiel
    auto *embedAdmin = creerCarteEmbed(
        &dlg,
        Palette::accentGlow,
        "AVIS ADMINISTRATIF & ENGAGEMENT",
        "Certification & responsabilité de gestion",
        QString("Réf. SALLE-%1").arg(s.id),
        genererMessageAdministratif(s, "consultation"),
        QString("<b>Engagement officiel :</b> %1").arg(payload.engagementAdmin.toHtmlEscaped()),
        "HACKNOVA · Direction de la logistique et des espaces");
    lay->addWidget(embedAdmin);

    lay->addStretch();

    auto *btns = new QHBoxLayout;
    btns->setSpacing(10);

    auto *btnHistorique = new QPushButton("🕒 HISTORIQUE OFFICIEL", &dlg);
    btnHistorique->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    QObject::connect(btnHistorique, &QPushButton::clicked, &dlg,
                     [this, idSalle]() { this->ouvrirHistoriqueSalle(idSalle); });

    auto *btnQR = new QPushButton("📷 GÉNÉRER QR CODE", &dlg);
    btnQR->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));
    QObject::connect(btnQR, &QPushButton::clicked, &dlg,
                     [this, idSalle]() { this->ouvrirGenerateurQR(idSalle); });

    auto *btnFermer = new QPushButton("FERMER", &dlg);
    btnFermer->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    QObject::connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);

    btns->addWidget(btnHistorique);
    btns->addWidget(btnQR);
    btns->addStretch();
    btns->addWidget(btnFermer);
    lay->addLayout(btns);

    dlg.exec();
}

/* ============================================================
 *  READ — Remplir le tableau des salles
 * ============================================================ */
void salle::remplirTableSalles()
{
    auto *t = ui->tableSalles;
    if (!t) return;
    viderTableSalles();

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return;

    QSqlQuery q(db);
    if (!q.exec("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE "
                "FROM SALLE ORDER BY ID_SALLE ASC")) return;

    QVector<Salle> liste;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        parserNomSalle(s.nom, s.bloc, s.etage, s.numeroSalle);
        calculerDisponibiliteAutomatique(s);
        liste.append(s);
    }

    trierSallesMemoire(liste, m_triCourant);

    int row = 0;
    for (const Salle &s : liste) {
        insererLigneSalle(row++, s);
    }

    t->verticalHeader()->setVisible(false);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setAlternatingRowColors(true);

    const int lastCol = t->columnCount() - 1;
    for (int c = 0; c < lastCol; ++c)
        t->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    if (lastCol >= 0) {
        t->horizontalHeader()->setSectionResizeMode(lastCol, QHeaderView::Fixed);
        t->setColumnWidth(lastCol, 270);
    }
    t->verticalHeader()->setDefaultSectionSize(44);
    t->setSortingEnabled(true);
}

void salle::insererLigneSalle(int row, const Salle &s)
{
    auto *t = ui->tableSalles;
    t->insertRow(row);

    t->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
    t->setItem(row, 1, new QTableWidgetItem(s.nom));

    auto *capItem = new QTableWidgetItem;
    capItem->setData(Qt::DisplayRole, s.capacite);
    capItem->setTextAlignment(Qt::AlignCenter);
    t->setItem(row, 2, capItem);

    t->setItem(row, 3, new QTableWidgetItem(s.type));

    auto *dispoItem = new QTableWidgetItem(s.disponibilite);
    dispoItem->setForeground(couleurDisponibilite(s.estDisponible()));
    dispoItem->setTextAlignment(Qt::AlignCenter);
    QFont df = dispoItem->font();
    df.setBold(true);
    dispoItem->setFont(df);
    t->setItem(row, 4, dispoItem);

    t->setCellWidget(row, 5, creerWidgetActions(s.id, s.nom));
}

/* ============================================================
 *  READ — Recherche instantanée par ID (partiel) ou Nom
 * ============================================================ */
void salle::onRechercherSalle()
{
    if (!ui->lineEdit_2 || !ui->tableSalles) return;

    const QString terme = ui->lineEdit_2->text().trimmed();
    if (terme.isEmpty()) { rafraichirSallesEtStats(); return; }

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return;

    auto *t = ui->tableSalles;
    viderTableSalles();

    QSqlQuery q(db);
    q.prepare("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE "
              "FROM SALLE "
              "WHERE TO_CHAR(ID_SALLE) LIKE :idPartiel "
              "   OR UPPER(NOM_SALLE) LIKE UPPER(:nomPartiel) "
              "   OR UPPER(TYPE_SALLE) LIKE UPPER(:nomPartiel) "
              "ORDER BY ID_SALLE ASC");
    q.bindValue(":idPartiel",  "%" + terme + "%", QSql::In);
    q.bindValue(":nomPartiel", "%" + terme + "%", QSql::In);

    if (!q.exec()) { rafraichirSallesEtStats(); return; }

    QVector<Salle> trouvees;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        parserNomSalle(s.nom, s.bloc, s.etage, s.numeroSalle);
        calculerDisponibiliteAutomatique(s);
        trouvees.append(s);
    }

    trierSallesMemoire(trouvees, m_triCourant);

    int row = 0;
    for (const Salle &s : trouvees) {
        insererLigneSalle(row++, s);
    }

    if (trouvees.isEmpty()) {
        QMessageBox::information(this, "Recherche",
                                 QString("Aucune salle ne correspond à « %1 ».").arg(terme));
    }
    t->setSortingEnabled(true);
}

void salle::onRechercheDynamiqueSalle()
{
    if (!ui->lineEdit_2 || !ui->tableSalles) return;

    const QString terme = ui->lineEdit_2->text().trimmed();
    if (terme.isEmpty()) {
        rafraichirSallesEtStats();
        return;
    }

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return;

    auto *t = ui->tableSalles;
    viderTableSalles();

    QSqlQuery q(db);
    q.prepare("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE "
              "FROM SALLE "
              "WHERE TO_CHAR(ID_SALLE) LIKE :idPartiel "
              "   OR UPPER(NOM_SALLE) LIKE UPPER(:nomPartiel) "
              "   OR UPPER(TYPE_SALLE) LIKE UPPER(:nomPartiel) "
              "ORDER BY ID_SALLE ASC");
    q.bindValue(":idPartiel",  "%" + terme + "%", QSql::In);
    q.bindValue(":nomPartiel", "%" + terme + "%", QSql::In);

    if (!q.exec()) return;

    QVector<Salle> trouvees;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        parserNomSalle(s.nom, s.bloc, s.etage, s.numeroSalle);
        calculerDisponibiliteAutomatique(s);
        trouvees.append(s);
    }

    trierSallesMemoire(trouvees, m_triCourant);

    int row = 0;
    for (const Salle &s : trouvees) {
        insererLigneSalle(row++, s);
    }

    t->setSortingEnabled(true);
    dessinerStatistiquesSalles();
    mettreAJourTableauDeBordBas();
}

/* ============================================================
 *  TRI CROISSANT / DÉCROISSANT & FILTRAGE AVANCÉ
 * ============================================================ */
void salle::onTriRapideChange()
{
    if (m_comboChampTri)
        m_triCourant.champTri = m_comboChampTri->currentData().toString();
    if (m_comboSensTri)
        m_triCourant.ordreCroissant = m_comboSensTri->currentData().toBool();

    if (ui->lineEdit_2 && !ui->lineEdit_2->text().trimmed().isEmpty()) {
        onRechercheDynamiqueSalle();
    } else if (!m_triCourant.estVide()) {
        appliquerCriteresTri(m_triCourant);
    } else {
        remplirTableSalles();
    }
}

void salle::trierSallesMemoire(QVector<Salle> &liste, const CriteresTri &c) const
{
    const bool asc = c.ordreCroissant;
    const QString champ = c.champTri;

    std::sort(liste.begin(), liste.end(), [&](const Salle &a, const Salle &b) {
        if (c.trierParCapaciteCroissante && a.capacite != b.capacite)
            return a.capacite < b.capacite;
        if (c.trierParCapaciteDecroissante && a.capacite != b.capacite)
            return a.capacite > b.capacite;

        if (champ == "ID") {
            if (a.id != b.id) return asc ? (a.id < b.id) : (a.id > b.id);
        } else if (champ == "NOM") {
            const int cmp = a.nom.compare(b.nom, Qt::CaseInsensitive);
            if (cmp != 0) return asc ? (cmp < 0) : (cmp > 0);
        } else if (champ == "CAPACITE") {
            if (a.capacite != b.capacite) return asc ? (a.capacite < b.capacite) : (a.capacite > b.capacite);
        } else if (champ == "TYPE") {
            const int cmp = a.type.compare(b.type, Qt::CaseInsensitive);
            if (cmp != 0) return asc ? (cmp < 0) : (cmp > 0);
        } else if (champ == "DISPONIBILITE") {
            const int cmp = a.disponibilite.compare(b.disponibilite, Qt::CaseInsensitive);
            if (cmp != 0) return asc ? (cmp < 0) : (cmp > 0);
        } else if (champ == "DATE_FIN") {
            if (a.dateFin != b.dateFin) return asc ? (a.dateFin < b.dateFin) : (a.dateFin > b.dateFin);
        }

        return a.id < b.id;
    });
}

void salle::onTrierSalle()
{
    ouvrirDialogueTri();
}

QVector<Salle> salle::chargerSallesFiltrees(const CriteresTri &c) const
{
    QVector<Salle> resultat;
    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return resultat;

    QSqlQuery q(db);
    q.exec("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE FROM SALLE");

    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        parserNomSalle(s.nom, s.bloc, s.etage, s.numeroSalle);
        calculerDisponibiliteAutomatique(s);

        if (!c.blocs.isEmpty() && !c.blocs.contains(s.bloc)) continue;
        if (!c.etages.isEmpty() && !c.etages.contains(s.etage)) continue;
        if (!c.types.isEmpty() && !c.types.contains(s.type)) continue;
        if (!c.disponibilites.isEmpty() && !c.disponibilites.contains(s.disponibilite)) continue;
        if (c.capaciteMin > 0 && s.capacite < c.capaciteMin) continue;
        if (c.capaciteMax > 0 && s.capacite > c.capaciteMax) continue;
        if (!c.nomContient.trimmed().isEmpty()
            && !s.nom.contains(c.nomContient, Qt::CaseInsensitive)
            && !QString::number(s.id).contains(c.nomContient.trimmed())) continue;

        resultat.append(s);
    }

    trierSallesMemoire(resultat, c);
    return resultat;
}

QVector<Salle> salle::chargerSallesSelectionnees(const QVector<qint64> &ids) const
{
    QVector<Salle> res;
    for (qint64 id : ids) {
        auto opt = chargerSalle(id);
        if (opt.has_value()) res.append(*opt);
    }
    return res;
}

QVector<qint64> salle::idsSallesAffichees() const
{
    QVector<qint64> ids;
    auto *t = ui->tableSalles;
    if (!t) return ids;
    for (int r = 0; r < t->rowCount(); ++r) {
        QTableWidgetItem *it = t->item(r, 0);
        if (it) ids.append(it->text().toLongLong());
    }
    return ids;
}

void salle::appliquerCriteresTri(const CriteresTri &c)
{
    const QVector<Salle> salles = chargerSallesFiltrees(c);
    auto *t = ui->tableSalles;
    viderTableSalles();
    int row = 0;
    for (const Salle &s : salles) {
        insererLigneSalle(row++, s);
    }
    t->setSortingEnabled(false);
    t->setSortingEnabled(true);
}

void salle::ouvrirDialogueTri()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Trier et filtrer les salles");
    dlg.setMinimumSize(720, 700);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(14);

    auto *titre = new QLabel(QString(
                                 "<div style='font-size:20px;font-weight:900;color:%1;'>🔍 Tri & filtrage avancés</div>"
                                 "<div style='font-size:11px;color:%2;'>Combinez plusieurs critères et choisissez le sens ASC/DESC.</div>")
                                 .arg(Palette::accentGlow, Palette::texteMuted));
    titre->setTextFormat(Qt::RichText);
    lay->addWidget(titre);

    auto *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("QScrollArea { background:transparent; }");

    auto *content = new QWidget;
    content->setStyleSheet(QString("background:%1;").arg(Palette::carte));
    auto *cl = new QVBoxLayout(content);
    cl->setContentsMargins(6, 6, 6, 6);
    cl->setSpacing(14);

    auto makeCheckGroup = [&](const QString &titre, const QStringList &items,
                              QVector<QCheckBox*> &out) -> QGroupBox* {
        auto *g = new QGroupBox(titre);
        g->setStyleSheet(QString(
                             "QGroupBox { color:%1; font-weight:800; font-size:12px;"
                             "border:1px solid %2; border-radius:8px; margin-top:10px; padding-top:14px; }"
                             "QGroupBox::title { subcontrol-origin: margin; left:12px; padding:0 6px; }")
                             .arg(Palette::accentGlow, Palette::bordure));
        auto *gl = new QGridLayout(g);
        gl->setSpacing(6);
        int i = 0;
        for (const QString &it : items) {
            auto *cb = new QCheckBox(it);
            cb->setStyleSheet(QString("QCheckBox { color:%1; font-size:12px; }")
                                  .arg(Palette::texte));
            out.append(cb);
            gl->addWidget(cb, i / 4, i % 4);
            ++i;
        }
        return g;
    };

    QVector<QCheckBox*> cbBlocs, cbEtages, cbTypes, cbDispo;
    cl->addWidget(makeCheckGroup("Bloc", {"A","B","C","D","E","F","G","H"}, cbBlocs));
    cl->addWidget(makeCheckGroup("Étage", {"1","2","3"}, cbEtages));

    QStringList typesDispos = typesSalleDisponibles();
    if (typesDispos.isEmpty()) typesDispos = {"Aucun type"};
    cl->addWidget(makeCheckGroup("Type de salle", typesDispos, cbTypes));
    cl->addWidget(makeCheckGroup("Disponibilité", {"Disponible","Indisponible"}, cbDispo));

    auto *capBox = new QGroupBox("Capacité");
    capBox->setStyleSheet(QString(
                              "QGroupBox { color:%1; font-weight:800; font-size:12px;"
                              "border:1px solid %2; border-radius:8px; margin-top:10px; padding-top:14px; }"
                              "QGroupBox::title { subcontrol-origin: margin; left:12px; padding:0 6px; }")
                              .arg(Palette::accentGlow, Palette::bordure));
    auto *capLay = new QHBoxLayout(capBox);
    auto *spMin = new QSpinBox; spMin->setRange(0, 9999);
    auto *spMax = new QSpinBox; spMax->setRange(0, 9999);
    spMin->setStyleSheet(styleChamp()); spMax->setStyleSheet(styleChamp());
    capLay->addWidget(new QLabel("Min :"));
    capLay->addWidget(spMin);
    capLay->addSpacing(12);
    capLay->addWidget(new QLabel("Max :"));
    capLay->addWidget(spMax);
    capLay->addStretch();
    cl->addWidget(capBox);

    auto *nomBox = new QGroupBox("Nom ou ID");
    nomBox->setStyleSheet(capBox->styleSheet());
    auto *nomLay = new QHBoxLayout(nomBox);
    auto *edNom = new QLineEdit;
    edNom->setPlaceholderText("Contient… (ex: A-1 ou 12)");
    edNom->setStyleSheet(styleChamp());
    nomLay->addWidget(edNom);
    cl->addWidget(nomBox);

    auto *triBox = new QGroupBox("Ordre d'affichage (Croissant / Décroissant)");
    triBox->setStyleSheet(capBox->styleSheet());
    auto *triLay = new QVBoxLayout(triBox);
    auto *rbNom   = new QCheckBox("Tri par ID (Croissant par défaut)");
    auto *rbCapA  = new QCheckBox("Capacité croissante (ASC)");
    auto *rbCapD  = new QCheckBox("Capacité décroissante (DESC)");
    rbNom->setChecked(true);
    for (auto *rb : {rbNom, rbCapA, rbCapD})
        rb->setStyleSheet(QString("QCheckBox { color:%1; font-size:12px; }").arg(Palette::texte));
    QObject::connect(rbNom,  &QCheckBox::toggled, [=](bool c){ if (c) { rbCapA->setChecked(false); rbCapD->setChecked(false);} });
    QObject::connect(rbCapA, &QCheckBox::toggled, [=](bool c){ if (c) { rbNom->setChecked(false);  rbCapD->setChecked(false);} });
    QObject::connect(rbCapD, &QCheckBox::toggled, [=](bool c){ if (c) { rbNom->setChecked(false);  rbCapA->setChecked(false);} });
    triLay->addWidget(rbNom);
    triLay->addWidget(rbCapA);
    triLay->addWidget(rbCapD);
    cl->addWidget(triBox);

    cl->addStretch();
    scroll->setWidget(content);
    lay->addWidget(scroll, 1);

    auto *btns = new QHBoxLayout;
    auto *btnReset = new QPushButton("♻ Réinitialiser");
    btnReset->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    auto *btnAnnuler = new QPushButton("Annuler");
    btnAnnuler->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    auto *btnAppliquer = new QPushButton("✅ Appliquer");
    btnAppliquer->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));

    btns->addWidget(btnReset);
    btns->addStretch();
    btns->addWidget(btnAnnuler);
    btns->addWidget(btnAppliquer);
    lay->addLayout(btns);

    QObject::connect(btnReset, &QPushButton::clicked, [&]() {
        for (auto *cb : cbBlocs) cb->setChecked(false);
        for (auto *cb : cbEtages) cb->setChecked(false);
        for (auto *cb : cbTypes) cb->setChecked(false);
        for (auto *cb : cbDispo) cb->setChecked(false);
        spMin->setValue(0); spMax->setValue(0);
        edNom->clear();
        rbNom->setChecked(true);
        m_triCourant = CriteresTri{};
    });
    QObject::connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);
    QObject::connect(btnAppliquer, &QPushButton::clicked, [&]() {
        CriteresTri c = m_triCourant;
        c.blocs.clear(); c.etages.clear(); c.types.clear(); c.disponibilites.clear();
        for (auto *cb : cbBlocs) if (cb->isChecked()) c.blocs.insert(cb->text());
        for (auto *cb : cbEtages) if (cb->isChecked()) c.etages.insert(cb->text().toInt());
        for (auto *cb : cbTypes) if (cb->isChecked()) c.types.insert(cb->text());
        for (auto *cb : cbDispo) if (cb->isChecked()) c.disponibilites.insert(cb->text());
        c.capaciteMin = spMin->value();
        c.capaciteMax = spMax->value();
        c.nomContient = edNom->text();
        c.trierParCapaciteCroissante   = rbCapA->isChecked();
        c.trierParCapaciteDecroissante = rbCapD->isChecked();
        m_triCourant = c;

        dlg.accept();

        if (c.estVide() && !c.trierParCapaciteCroissante && !c.trierParCapaciteDecroissante) {
            rafraichirSallesEtStats();
        } else {
            appliquerCriteresTri(c);
            dessinerStatistiquesSalles();
            mettreAJourTableauDeBordBas();
        }
    });

    dlg.exec();
}

/* ============================================================
 *  Export PDF avancé
 * ============================================================ */
void salle::ouvrirDialogueExport()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Exporter les salles en PDF");
    dlg.setMinimumSize(620, 720);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(14);

    auto *titre = new QLabel(QString(
                                 "<div style='font-size:20px;font-weight:900;color:%1;'>📄 Export PDF personnalisé</div>"
                                 "<div style='font-size:11px;color:%2;'>Choisissez la portée, les colonnes et la mise en page.</div>")
                                 .arg(Palette::accentGlow, Palette::texteMuted));
    titre->setTextFormat(Qt::RichText);
    lay->addWidget(titre);

    auto *form = new QFormLayout;
    form->setSpacing(10);
    form->setLabelAlignment(Qt::AlignLeft);

    auto *cbPortee = new QComboBox;
    cbPortee->addItems({"Toutes les salles",
                        "Résultats actuellement affichés",
                        "Salles sélectionnées dans le tableau"});
    cbPortee->setStyleSheet(styleChamp());
    form->addRow("Portée :", cbPortee);

    auto *edTitre   = new QLineEdit("Liste des salles HACKNOVA");
    auto *edSous    = new QLineEdit("Rapport généré le " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));
    auto *edEnTete  = new QLineEdit("HACKNOVA — Smart Hackathon Management");
    auto *edPied    = new QLineEdit("Document confidentiel — HACKNOVA");
    for (auto *e : {edTitre, edSous, edEnTete, edPied}) e->setStyleSheet(styleChamp());
    form->addRow("Titre :",        edTitre);
    form->addRow("Sous-titre :",   edSous);
    form->addRow("En-tête :",      edEnTete);
    form->addRow("Pied de page :", edPied);

    auto *cbOrient = new QComboBox;
    cbOrient->addItems({"Portrait", "Paysage"});
    cbOrient->setStyleSheet(styleChamp());
    form->addRow("Orientation :", cbOrient);

    auto *colsBox = new QGroupBox("Colonnes à afficher");
    colsBox->setStyleSheet(QString(
                               "QGroupBox { color:%1; font-weight:800; font-size:12px;"
                               "border:1px solid %2; border-radius:8px; margin-top:10px; padding-top:14px; }"
                               "QGroupBox::title { subcontrol-origin: margin; left:12px; padding:0 6px; }")
                               .arg(Palette::accentGlow, Palette::bordure));
    auto *colsLay = new QGridLayout(colsBox);
    colsLay->setSpacing(6);

    auto *ckID  = new QCheckBox("ID");            ckID->setChecked(true);
    auto *ckNom = new QCheckBox("Nom");           ckNom->setChecked(true);
    auto *ckCap = new QCheckBox("Capacité");      ckCap->setChecked(true);
    auto *ckTyp = new QCheckBox("Type");          ckTyp->setChecked(true);
    auto *ckDis = new QCheckBox("Disponibilité"); ckDis->setChecked(true);
    auto *ckBlc = new QCheckBox("Bloc");          ckBlc->setChecked(true);
    auto *ckEtg = new QCheckBox("Étage");         ckEtg->setChecked(true);
    for (auto *c : {ckID, ckNom, ckCap, ckTyp, ckDis, ckBlc, ckEtg})
        c->setStyleSheet(QString("QCheckBox { color:%1; font-size:12px; }").arg(Palette::texte));
    colsLay->addWidget(ckID,  0, 0); colsLay->addWidget(ckNom, 0, 1);
    colsLay->addWidget(ckCap, 0, 2); colsLay->addWidget(ckTyp, 0, 3);
    colsLay->addWidget(ckDis, 1, 0); colsLay->addWidget(ckBlc, 1, 1);
    colsLay->addWidget(ckEtg, 1, 2);

    auto *ckNum = new QCheckBox("Numérotation des pages (1/2, 2/2, …)");
    ckNum->setChecked(true);
    ckNum->setStyleSheet(QString("QCheckBox { color:%1; font-size:12px; }").arg(Palette::texte));
    colsLay->addWidget(ckNum, 2, 0, 1, 4);

    lay->addLayout(form);
    lay->addWidget(colsBox);
    lay->addStretch();

    auto *btns = new QHBoxLayout;
    auto *btnAnnuler = new QPushButton("Annuler");
    btnAnnuler->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    auto *btnExporter = new QPushButton("💾 Exporter en PDF");
    btnExporter->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    btns->addStretch();
    btns->addWidget(btnAnnuler);
    btns->addWidget(btnExporter);
    lay->addLayout(btns);

    QObject::connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);

    QObject::connect(btnExporter, &QPushButton::clicked, [&]() {
        OptionsExportPDF opt;
        opt.portee         = static_cast<OptionsExportPDF::Portee>(cbPortee->currentIndex());
        opt.titre          = edTitre->text().trimmed();
        opt.sousTitre      = edSous->text().trimmed();
        opt.enTete         = edEnTete->text().trimmed();
        opt.piedDePage     = edPied->text().trimmed();
        opt.paysage        = (cbOrient->currentIndex() == 1);
        opt.numeroterPages = ckNum->isChecked();
        opt.afficherID     = ckID->isChecked();
        opt.afficherNom    = ckNom->isChecked();
        opt.afficherCapacite = ckCap->isChecked();
        opt.afficherType   = ckTyp->isChecked();
        opt.afficherDispo  = ckDis->isChecked();
        opt.afficherBloc   = ckBlc->isChecked();
        opt.afficherEtage  = ckEtg->isChecked();

        QVector<Salle> salles;
        if (opt.portee == OptionsExportPDF::ToutesLesDonnees) {
            salles = chargerSallesFiltrees(CriteresTri{});
        } else if (opt.portee == OptionsExportPDF::ResultatsFiltres) {
            salles = chargerSallesSelectionnees(idsSallesAffichees());
        } else {
            QSet<int> rows;
            for (auto *it : ui->tableSalles->selectedItems())
                rows.insert(it->row());
            QVector<qint64> ids;
            for (int r : rows) {
                auto *it = ui->tableSalles->item(r, 0);
                if (it) ids.append(it->text().toLongLong());
            }
            salles = chargerSallesSelectionnees(ids);
        }

        if (salles.isEmpty()) {
            QMessageBox::information(&dlg, "Export PDF", "Aucune salle à exporter.");
            return;
        }

        const QString chemin = QFileDialog::getSaveFileName(
            &dlg, "Enregistrer le PDF",
            QString("salles_%1.pdf").arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")),
            "Fichiers PDF (*.pdf)");
        if (chemin.isEmpty()) return;

        QPrinter printer(QPrinter::ScreenResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(chemin);
        printer.setPageOrientation(opt.paysage ? QPageLayout::Landscape : QPageLayout::Portrait);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

        QString html = QString(
            "<html><head><meta charset='utf-8'/><style>"
            "body { font-family:'Segoe UI', Arial, sans-serif; font-size:11pt; color:#1E293B; margin:0; }"
            "h1 { color:#4338CA; font-size:22pt; margin:0 0 4px 0; padding:0; }"
            "h2 { color:#64748B; font-size:12pt; font-weight:normal; margin:0 0 16px 0; padding:0; }"
            ".entete { color:#94A3B8; font-size:9pt; text-align:right; margin-bottom:8px; }"
            ".pied { color:#94A3B8; font-size:9pt; text-align:center; margin-top:16px; }"
            "table { border-collapse:collapse; width:100%; margin-top:8px; table-layout:fixed; }"
            "th { background:#1E1B4B; color:#FFFFFF; padding:8px 10px; text-align:left; font-size:10pt; font-weight:bold; border:none; }"
            "td { border-bottom:1px solid #E2E8F0; padding:6px 10px; font-size:10pt; vertical-align:middle; word-wrap:break-word; }"
            "tr { page-break-inside: avoid; }"
            "tr:nth-child(even) td { background:#F8FAFC; }"
            ".dispo { color:#059669; font-weight:bold; }"
            ".indispo { color:#B91C1C; font-weight:bold; }"
            "</style></head><body>");

        if (!opt.enTete.isEmpty())
            html += QString("<div class='entete'>%1</div>").arg(opt.enTete.toHtmlEscaped());
        html += QString("<h1>%1</h1>").arg(opt.titre.toHtmlEscaped());
        if (!opt.sousTitre.isEmpty())
            html += QString("<h2>%1</h2>").arg(opt.sousTitre.toHtmlEscaped());

        html += "<table><thead><tr>";
        if (opt.afficherID)       html += "<th style='width:8%;'>ID</th>";
        if (opt.afficherNom)      html += "<th style='width:16%;'>Nom</th>";
        if (opt.afficherBloc)     html += "<th style='width:8%;'>Bloc</th>";
        if (opt.afficherEtage)    html += "<th style='width:8%;'>Étage</th>";
        if (opt.afficherCapacite) html += "<th style='width:12%;'>Capacité</th>";
        if (opt.afficherType)     html += "<th style='width:24%;'>Type</th>";
        if (opt.afficherDispo)    html += "<th style='width:14%;'>Disponibilité</th>";
        html += "</tr></thead><tbody>";

        for (const Salle &s : salles) {
            html += "<tr>";
            if (opt.afficherID)       html += QString("<td>%1</td>").arg(s.id);
            if (opt.afficherNom)      html += QString("<td>%1</td>").arg(s.nom.toHtmlEscaped());
            if (opt.afficherBloc)     html += QString("<td>%1</td>").arg(s.bloc.toHtmlEscaped());
            if (opt.afficherEtage)    html += QString("<td>%1</td>").arg(s.etage);
            if (opt.afficherCapacite) html += QString("<td>%1</td>").arg(s.capacite);
            if (opt.afficherType)     html += QString("<td>%1</td>").arg(s.type.toHtmlEscaped());
            if (opt.afficherDispo) {
                const QString cls = s.estDisponible() ? "dispo" : "indispo";
                html += QString("<td class='%1'>%2</td>").arg(cls, s.disponibilite.toHtmlEscaped());
            }
            html += "</tr>";
        }
        html += "</tbody></table>";

        if (!opt.piedDePage.isEmpty())
            html += QString("<div class='pied'>%1</div>").arg(opt.piedDePage.toHtmlEscaped());

        html += "</body></html>";

        QTextDocument doc;
        doc.setHtml(html);
        doc.setDocumentMargin(0);

        const QRectF pageRect = printer.pageLayout().paintRectPixels(printer.resolution());
        doc.setPageSize(QSizeF(pageRect.width(), pageRect.height()));

        if (!opt.numeroterPages) {
            doc.print(&printer);
        } else {
            QPainter painter;
            if (!painter.begin(&printer)) {
                QMessageBox::warning(&dlg, "Export PDF",
                                     "Impossible de démarrer l'impression PDF.");
                return;
            }

            QAbstractTextDocumentLayout *layout = doc.documentLayout();
            int nbPages = 1;
            if (layout) {
                const qreal docH  = layout->documentSize().height();
                const qreal pageH = pageRect.height();
                nbPages = qMax(1, int(std::ceil(docH / pageH)));
            }

            const qreal footerH = 24.0;

            for (int page = 0; page < nbPages; ++page) {
                if (page > 0) printer.newPage();

                painter.save();
                painter.translate(0, -page * pageRect.height());

                QAbstractTextDocumentLayout::PaintContext ctx;
                ctx.clip = QRectF(0, page * pageRect.height(),
                                  pageRect.width(), pageRect.height());
                layout->draw(&painter, ctx);
                painter.restore();

                painter.save();
                QFont f = painter.font();
                f.setFamily("Segoe UI");
                f.setPointSizeF(9.0);
                painter.setFont(f);
                painter.setPen(QColor("#94A3B8"));

                const QString txt = QString("Page %1 / %2").arg(page + 1).arg(nbPages);
                QRectF footerRect(pageRect.left(),
                                  pageRect.bottom() - footerH,
                                  pageRect.width(),
                                  footerH);
                painter.drawText(footerRect, Qt::AlignCenter, txt);
                painter.restore();
            }

            painter.end();
        }

        QMessageBox::information(&dlg, "Export PDF",
                                 QString("%1 salle(s) exportée(s) vers :\n%2").arg(salles.size()).arg(chemin));
        dlg.accept();
    });

    dlg.exec();
}

void salle::onExporterSalle()
{
    ouvrirDialogueExport();
}

/* ============================================================
 *  AFFECTATION INTELLIGENTE :
 *  - Recommandation auto + liste des salles disponibles
 *  - Embed message officiel + Historique
 * ============================================================ */
bool salle::affecterSalleSpecifique(const Salle &s, const QDate &dDeb, int duree,
                                    int effectif, const QString &projet,
                                    QWidget *parentDlg, QString *messageSortie)
{
    const QDate dFin = dDeb.addDays(duree - 1);

    for (auto it = m_periodesSession.constBegin(); it != m_periodesSession.constEnd(); ++it) {
        if (it.key() == s.id) continue;
        if (it->chevauche(dDeb, duree)) {
            QMessageBox::warning(parentDlg, "Conflit de période",
                                 QString("La salle %1 est déjà réservée du %2 au %3.")
                                     .arg(s.nom,
                                          it->dateDebut.toString("dd/MM/yyyy"),
                                          it->dateFin().toString("dd/MM/yyyy")));
            return false;
        }
    }

    PeriodeReservation p;
    p.dateDebut  = dDeb;
    p.dureeJours = duree;
    p.projet     = projet.trimmed();
    m_periodesSession[s.id] = p;

    if (QDate::currentDate() >= dDeb && QDate::currentDate() <= dFin) {
        QSqlDatabase db = dbHacknova();
        if (db.isValid() && db.isOpen() && db.transaction()) {
            QSqlQuery u(db);
            u.prepare("UPDATE SALLE SET DISPONIBILITE = 'Indisponible' WHERE ID_SALLE = :id");
            u.bindValue(":id", QString::number(s.id));
            if (u.exec()) db.commit();
            else db.rollback();
        }
    }

    const QString msgOfficiel = genererMessageAutoAffectation(s, dDeb, dFin, duree, effectif, projet);
    const QString eng         = genererEngagementAdmin(s);
    enregistrerHistorique(s.id, "AFFECTATION", msgOfficiel, eng);

    if (messageSortie) {
        *messageSortie = construireEmbedHtml(
            Palette::succes,
            "CONFIRMATION OFFICIELLE D'AFFECTATION",
            QString("Salle %1 attribuée avec succès").arg(s.nom),
            QString("Période : %1 → %2").arg(dDeb.toString("dd/MM/yyyy"), dFin.toString("dd/MM/yyyy")),
            msgOfficiel,
            QString("<b>Engagement officiel :</b> %1").arg(eng.toHtmlEscaped()),
            "HACKNOVA · Système d'affectation intelligente");
    }

    rafraichirSallesEtStats();
    return true;
}

void salle::ouvrirEspaceMetierAffectation()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Métier 1 — Affectation intelligente & Salles disponibles");
    dlg.setMinimumSize(880, 650);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(14);

    auto *lblTitre = new QLabel(
        "<h2 style='color:#818CF8;margin:0;'>🎯 Affectation intelligente des salles</h2>"
        "<p style='color:#94A3B8;margin:4px 0 0 0;'>"
        "Consultez la liste des salles disponibles selon l'effectif et la période, affectez directement "
        "depuis la liste ou lancez la recommandation automatique, et accédez à l'historique officiel.</p>");
    lblTitre->setTextFormat(Qt::RichText);
    lblTitre->setWordWrap(true);
    lay->addWidget(lblTitre);

    auto *form = new QFormLayout;
    form->setSpacing(10);

    auto *edEff = new QLineEdit(&dlg);
    edEff->setPlaceholderText("Ex. 6");
    edEff->setText("5");
    edEff->setStyleSheet(styleChamp());

    auto *dtDebut = new QDateEdit(&dlg);
    dtDebut->setCalendarPopup(true);
    dtDebut->setDisplayFormat("dd/MM/yyyy");
    dtDebut->setDate(QDate::currentDate());
    dtDebut->setStyleSheet(styleChamp());

    auto *spDuree = new QSpinBox(&dlg);
    spDuree->setRange(1, 365);
    spDuree->setValue(3);
    spDuree->setStyleSheet(styleChamp());

    auto *edProjet = new QLineEdit(&dlg);
    edProjet->setPlaceholderText("Nom du projet / équipe hackathon");
    edProjet->setStyleSheet(styleChamp());

    form->addRow("Effectif requis :", edEff);
    form->addRow("Date début :",      dtDebut);
    form->addRow("Durée (jours) :",   spDuree);
    form->addRow("Projet / Équipe :", edProjet);
    lay->addLayout(form);

    auto *actionBar = new QHBoxLayout;
    actionBar->setSpacing(10);

    auto *btnListerDispo = new QPushButton("📋 Lister les salles disponibles", &dlg);
    btnListerDispo->setStyleSheet(styleBouton(Palette::accent, Palette::accentDark));

    auto *btnRecommander = new QPushButton("⚡ Recommander & affecter la meilleure", &dlg);
    btnRecommander->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));

    actionBar->addWidget(btnListerDispo);
    actionBar->addWidget(btnRecommander);
    actionBar->addStretch();
    lay->addLayout(actionBar);

    auto *lblListeTitle = new QLabel("<b>Salles disponibles correspondantes :</b>");
    lblListeTitle->setStyleSheet(QString("color:%1;font-size:12px;").arg(Palette::accentGlow));
    lay->addWidget(lblListeTitle);

    auto *tblDispo = new QTableWidget(&dlg);
    tblDispo->setColumnCount(6);
    tblDispo->setHorizontalHeaderLabels({"ID", "Nom", "Type", "Capacité", "Écart places", "Actions"});
    tblDispo->verticalHeader()->setVisible(false);
    tblDispo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblDispo->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblDispo->setAlternatingRowColors(true);
    tblDispo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tblDispo->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tblDispo->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tblDispo->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    tblDispo->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    tblDispo->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    tblDispo->setColumnWidth(5, 220);
    tblDispo->verticalHeader()->setDefaultSectionSize(40);
    lay->addWidget(tblDispo, 1);

    auto *lblEmbedSortie = new QLabel(&dlg);
    lblEmbedSortie->setTextFormat(Qt::RichText);
    lblEmbedSortie->setWordWrap(true);
    lblEmbedSortie->setText(construireEmbedHtml(
        Palette::accentGlow,
        "ASSISTANT D'AFFECTATION",
        "Sélection des espaces disponibles",
        "Prêt",
        "Renseignez l'effectif et la période souhaitée pour afficher les salles éligibles et procéder à l'affectation officielle."));
    lay->addWidget(lblEmbedSortie);

    auto lireParams = [&](int &effectif, QDate &dDeb, int &dur) -> bool {
        bool ok = false;
        effectif = edEff->text().trimmed().toInt(&ok);
        if (!ok || effectif <= 0) {
            QMessageBox::warning(&dlg, "Affectation", "Saisissez un effectif strictement positif.");
            return false;
        }
        dDeb = dtDebut->date();
        dur  = spDuree->value();
        return true;
    };

    auto calculerCandidates = [&](int effectif, const QDate &dDeb, int dur) -> QVector<Salle> {
        QVector<Salle> candidates;
        const QVector<Salle> toutes = chargerSallesFiltrees(CriteresTri{});
        for (const Salle &s : toutes) {
            if (s.capacite < effectif) continue;
            bool conflit = false;
            auto itP = m_periodesSession.constFind(s.id);
            if (itP != m_periodesSession.constEnd() && itP->chevauche(dDeb, dur)) {
                conflit = true;
            }
            if (!conflit && s.estDisponible()) {
                candidates.append(s);
            }
        }
        std::sort(candidates.begin(), candidates.end(), [effectif](const Salle &a, const Salle &b) {
            const int mA = a.capacite - effectif;
            const int mB = b.capacite - effectif;
            if (mA != mB) return mA < mB;
            return a.id < b.id;
        });
        return candidates;
    };

    std::function<void()> remplirListeDispo = [&]() {
        int effectif = 0, dur = 0;
        QDate dDeb;
        if (!lireParams(effectif, dDeb, dur)) return;

        for (int r = tblDispo->rowCount() - 1; r >= 0; --r) {
            QWidget *w = tblDispo->cellWidget(r, 5);
            if (w) { tblDispo->removeCellWidget(r, 5); w->deleteLater(); }
        }
        tblDispo->setRowCount(0);

        const QVector<Salle> candidates = calculerCandidates(effectif, dDeb, dur);
        int row = 0;
        for (const Salle &s : candidates) {
            tblDispo->insertRow(row);
            tblDispo->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
            tblDispo->setItem(row, 1, new QTableWidgetItem(s.nom));
            tblDispo->setItem(row, 2, new QTableWidgetItem(s.type));
            tblDispo->setItem(row, 3, new QTableWidgetItem(QString("%1 places").arg(s.capacite)));
            tblDispo->setItem(row, 4, new QTableWidgetItem(QString("+%1").arg(s.capacite - effectif)));

            auto *cellW = new QWidget;
            auto *hl = new QHBoxLayout(cellW);
            hl->setContentsMargins(4, 2, 4, 2);
            hl->setSpacing(6);

            auto *btnAff = new QPushButton("AFFECTER", cellW);
            btnAff->setCursor(Qt::PointingHandCursor);
            btnAff->setStyleSheet(QString(
                                      "QPushButton { background:%1; color:#FFF; border:none; border-radius:5px;"
                                      "padding:4px 8px; font-size:10px; font-weight:800; }"
                                      "QPushButton:hover { background:%2; }")
                                      .arg(Palette::succesDark, Palette::succes));

            auto *btnHist = new QPushButton("HISTORIQUE", cellW);
            btnHist->setCursor(Qt::PointingHandCursor);
            btnHist->setStyleSheet(QString(
                                       "QPushButton { background:%1; color:#F1F5F9; border:1px solid %2;"
                                       "border-radius:5px; padding:4px 8px; font-size:10px; font-weight:800; }"
                                       "QPushButton:hover { background:%2; }")
                                       .arg(Palette::carteAlt, Palette::bordure));

            const qint64 sid = s.id;
            QObject::connect(btnAff, &QPushButton::clicked, &dlg, [&, s, effectif, dDeb, dur]() {
                QString embedSortie;
                if (affecterSalleSpecifique(s, dDeb, dur, effectif, edProjet->text(), &dlg, &embedSortie)) {
                    lblEmbedSortie->setText(embedSortie);
                    QMessageBox::information(&dlg, "Confirmation Officielle", embedSortie);
                    remplirListeDispo();
                }
            });

            QObject::connect(btnHist, &QPushButton::clicked, &dlg, [this, sid]() {
                this->ouvrirHistoriqueSalle(sid);
            });

            hl->addWidget(btnAff);
            hl->addWidget(btnHist);
            tblDispo->setCellWidget(row, 5, cellW);
            ++row;
        }

        if (candidates.isEmpty()) {
            lblEmbedSortie->setText(construireEmbedHtml(
                Palette::danger,
                "AUCUNE DISPONIBILITÉ",
                "Aucun espace éligible trouvé",
                QString("Effectif : %1 · Durée : %2 j").arg(effectif).arg(dur),
                "Aucune salle disponible sans conflit de période ne correspond à cet effectif. "
                "Ajustez la date, la durée ou l'effectif requis."));
        } else {
            lblEmbedSortie->setText(construireEmbedHtml(
                Palette::accentGlow,
                "RÉSULTATS D'ÉLIGIBILITÉ",
                QString("%1 salle(s) disponible(s) identifiée(s)").arg(candidates.size()),
                QString("Effectif : %1 · Début : %2").arg(effectif).arg(dDeb.toString("dd/MM/yyyy")),
                "Cliquez sur <b>AFFECTER</b> pour valider l'attribution officielle d'une salle ou sur "
                "<b>HISTORIQUE</b> pour consulter son registre complet."));
        }
    };

    QObject::connect(btnListerDispo, &QPushButton::clicked, &dlg, remplirListeDispo);

    QObject::connect(btnRecommander, &QPushButton::clicked, &dlg, [&]() {
        int effectif = 0, dur = 0;
        QDate dDeb;
        if (!lireParams(effectif, dDeb, dur)) return;

        const QVector<Salle> candidates = calculerCandidates(effectif, dDeb, dur);
        if (candidates.isEmpty()) {
            QMessageBox::warning(&dlg, "Affectation",
                                 "Aucune salle disponible sans conflit pour cette période et cet effectif.");
            return;
        }

        const Salle &best = candidates.first();
        QString embedSortie;
        if (affecterSalleSpecifique(best, dDeb, dur, effectif, edProjet->text(), &dlg, &embedSortie)) {
            lblEmbedSortie->setText(embedSortie);
            QMessageBox::information(&dlg, "Recommandation Officielle Validée", embedSortie);
            remplirListeDispo();
        }
    });

    auto *footerBtns = new QHBoxLayout;
    footerBtns->addStretch();
    auto *btnFermer = new QPushButton("FERMER", &dlg);
    btnFermer->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    QObject::connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);
    footerBtns->addWidget(btnFermer);
    lay->addLayout(footerBtns);

    remplirListeDispo();
    dlg.exec();
}

void salle::ouvrirEspaceMetierQR()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Métier 2 — QR Code, Scan & Fiche Oracle");
    dlg.setMinimumSize(640, 420);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(14);

    auto *lbl = new QLabel("<h2 style='color:#818CF8;margin:0;'>📱 QR Code & Vérification Oracle</h2>"
                           "<p style='color:#94A3B8;'>Importez une image QR ou saisissez une référence (ex. <code>HACKNOVA|SALLE|ID=1</code>) pour charger la fiche depuis Oracle.</p>");
    lbl->setTextFormat(Qt::RichText);
    lbl->setWordWrap(true);
    lay->addWidget(lbl);

    auto *edCode = new QLineEdit(&dlg);
    edCode->setPlaceholderText("HACKNOVA|SALLE|ID=1 ou ID numérique");
    edCode->setStyleSheet(styleChamp());
    lay->addWidget(edCode);

    auto *lblEmbedQR = new QLabel(&dlg);
    lblEmbedQR->setTextFormat(Qt::RichText);
    lblEmbedQR->setWordWrap(true);
    lblEmbedQR->setText(construireEmbedHtml(
        "#38BDF8",
        "CONTRÔLE D'ACCÈS QR",
        "Lecteur & vérificateur officiel Oracle",
        "En attente d'entrée",
        "Importez un fichier QR Code ou saisissez un identifiant de salle pour vérifier son statut en temps réel."));
    lay->addWidget(lblEmbedQR);

    auto *btns = new QHBoxLayout;
    btns->setSpacing(10);
    auto *btnImport = new QPushButton("📁 Importer image QR", &dlg);
    btnImport->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));
    auto *btnVerifier = new QPushButton("✅ Vérifier dans Oracle", &dlg);
    btnVerifier->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    auto *btnFermer = new QPushButton("Fermer", &dlg);
    btnFermer->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));

    btns->addWidget(btnImport);
    btns->addWidget(btnVerifier);
    btns->addStretch();
    btns->addWidget(btnFermer);
    lay->addLayout(btns);

    QObject::connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);
    QObject::connect(btnImport, &QPushButton::clicked, [&]() {
        lblEmbedQR->setText(construireEmbedHtml(
            "#38BDF8",
            "SCAN D'IMAGE",
            "Sélection du fichier QR Code",
            QDateTime::currentDateTime().toString("HH:mm:ss"),
            "Veuillez sélectionner l'image contenant le QR Code de la salle."));
        ouvrirScannerImage();
    });
    QObject::connect(btnVerifier, &QPushButton::clicked, [&]() {
        const QString txt = edCode->text().trimmed();
        if (txt.isEmpty()) {
            QMessageBox::warning(&dlg, "QR Code", "Saisissez ou importez un code QR.");
            return;
        }
        lblEmbedQR->setText(construireEmbedHtml(
            Palette::succes,
            "VÉRIFICATION ORACLE",
            QString("Analyse de la référence « %1 »").arg(txt),
            QDateTime::currentDateTime().toString("HH:mm:ss"),
            "Interrogation de la base Oracle en cours..."));
        traiterPayloadQRScanne(txt);
    });

    dlg.exec();
}

/* ============================================================
 *  MÉTIER — QR CODE CONNECTÉ À ORACLE
 * ============================================================ */
QString salle::genererRemarqueAuto(const Salle &s) const
{
    QStringList notes;
    if (s.estDisponible()) notes << "Salle prête à être utilisée.";
    else notes << "Salle non disponible ou actuellement occupée.";

    if (s.capacite < 5)       notes << QString("Capacité très réduite (%1 places).").arg(s.capacite);
    else if (s.capacite < 15) notes << QString("Capacité moyenne (%1 places).").arg(s.capacite);
    else                      notes << QString("Grande capacité (%1 places).").arg(s.capacite);

    return notes.join(" ");
}

QString salle::genererEngagementAdmin(const Salle &s) const
{
    return QString("Je, administrateur HACKNOVA, engage ma responsabilité sur l'utilisation "
                   "conforme de la salle « %1 » (ID %2, type %3, capacité %4).")
        .arg(s.nom, QString::number(s.id), s.type, QString::number(s.capacite));
}

QString salle::genererMessageAdministratif(const Salle &s, const QString &contexte) const
{
    const QString nom  = s.nom.toHtmlEscaped();
    const QString type = s.type.toHtmlEscaped();
    const QString cap  = QString::number(s.capacite);

    if (contexte == "consultation") {
        if (s.estDisponible()) {
            return QString("La salle <b>%1</b> (%2, %3 places) est <b>disponible</b> à la date du %4.")
                .arg(nom, type, cap, QDate::currentDate().toString("dd/MM/yyyy"));
        }
        return QString("La salle <b>%1</b> est actuellement <b>indisponible</b> à la date du %2.")
            .arg(nom, QDate::currentDate().toString("dd/MM/yyyy"));
    }
    return QString("Salle <b>%1</b> — type %2 — capacité %3 personnes.").arg(nom, type, cap);
}

PayloadQR salle::construirePayloadQR(const Salle &s) const
{
    PayloadQR p;
    p.id              = s.id;
    p.nom             = s.nom;
    p.capacite        = s.capacite;
    p.type            = s.type;
    p.disponibilite   = s.disponibilite;
    p.remarqueAuto    = genererRemarqueAuto(s);
    p.engagementAdmin = genererEngagementAdmin(s);
    p.messageQRAuto   = genererMessageAutoQR(s, "generation");
    p.dateGeneration  = QDateTime::currentDateTime().toString(Qt::ISODate);
    return p;
}

QPixmap salle::genererPixmapQR(const QString &contenu, int taille) const
{
    try {
        const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(
            contenu.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);
        const int modules = qr.getSize();
        const int quiet   = 4;
        const int total   = modules + quiet * 2;
        const int scale   = qMax(1, taille / total);
        const int finalSz = total * scale;

        QImage img(finalSz, finalSz, QImage::Format_RGB32);
        img.fill(Qt::white);

        for (int y = 0; y < modules; ++y) {
            for (int x = 0; x < modules; ++x) {
                if (!qr.getModule(x, y)) continue;
                const int px = (x + quiet) * scale;
                const int py = (y + quiet) * scale;
                for (int dy = 0; dy < scale; ++dy) {
                    QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(py + dy));
                    for (int dx = 0; dx < scale; ++dx) line[px + dx] = qRgb(0, 0, 0);
                }
            }
        }
        return QPixmap::fromImage(img);
    }
    catch (const std::exception &e) {
        qDebug() << "Nayuki encodeText a échoué :" << e.what();
        return QPixmap();
    }
}

void salle::ouvrirGenerateurQR(qint64 idSalle)
{
    const auto opt = chargerSalle(idSalle);
    if (!opt.has_value()) {
        QMessageBox::warning(this, "QR Code", "Salle introuvable dans Oracle.");
        return;
    }
    const Salle &s = *opt;
    const PayloadQR payload = construirePayloadQR(s);
    const QString contenu = payload.serialiser();

    enregistrerHistorique(idSalle, "QR", payload.messageQRAuto, payload.engagementAdmin);

    const QPixmap pixQR = genererPixmapQR(contenu, 340);
    if (pixQR.isNull()) {
        QMessageBox::warning(this, "QR Code", "Échec de la génération du QR Code.");
        return;
    }

    QDialog dlg(this);
    dlg.setWindowTitle(QString("QR Code Officiel — %1").arg(s.nom));
    dlg.setMinimumWidth(640);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(12);

    auto *titre = new QLabel(QString(
                                 "<div style='font-size:20px;font-weight:900;color:%1;'>%2</div>"
                                 "<div style='font-size:11px;color:%3;'>Identifiant #%4 · %5 places · %6</div>")
                                 .arg(Palette::accentGlow, s.nom.toHtmlEscaped(), Palette::texteMuted)
                                 .arg(s.id).arg(s.capacite).arg(s.type.toHtmlEscaped()));
    titre->setTextFormat(Qt::RichText);
    lay->addWidget(titre);

    auto *imgLabel = new QLabel;
    imgLabel->setPixmap(pixQR);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setStyleSheet("background:#FFFFFF;border-radius:12px;padding:14px;");
    lay->addWidget(imgLabel);

    auto *codeLabel = new QLabel(QString("<code style='color:%1;font-size:11px;'>%2</code>")
                                     .arg(Palette::accentGlow, contenu.toHtmlEscaped()));
    codeLabel->setTextFormat(Qt::RichText);
    codeLabel->setAlignment(Qt::AlignCenter);
    codeLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lay->addWidget(codeLabel);

    auto *embedQR = creerCarteEmbed(
        &dlg,
        "#38BDF8",
        "ÉMISSION OFFICIELLE QR",
        QString("Jeton d'accès — Salle %1").arg(s.nom),
        QDateTime::currentDateTime().toString("dd/MM/yyyy · HH:mm"),
        payload.messageQRAuto,
        QString("<b>Engagement officiel :</b> %1").arg(payload.engagementAdmin.toHtmlEscaped()),
        "HACKNOVA · Identification numérique des salles");
    lay->addWidget(embedQR);

    auto *btns = new QHBoxLayout;
    btns->setSpacing(8);
    auto *btnSave  = new QPushButton("💾 ENREGISTRER PNG");
    btnSave->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    auto *btnCopy  = new QPushButton("📋 COPIER LE CODE");
    btnCopy->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));
    auto *btnHist  = new QPushButton("🕒 HISTORIQUE OFFICIEL");
    btnHist->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));
    auto *btnClose = new QPushButton("FERMER");
    btnClose->setStyleSheet(styleBouton(Palette::carteAlt, Palette::bordure, "color:#F1F5F9;"));

    btns->addWidget(btnSave);
    btns->addWidget(btnCopy);
    btns->addWidget(btnHist);
    btns->addStretch();
    btns->addWidget(btnClose);
    lay->addLayout(btns);

    QObject::connect(btnClose, &QPushButton::clicked, &dlg, &QDialog::accept);
    QObject::connect(btnCopy, &QPushButton::clicked, [contenu]() {
        QApplication::clipboard()->setText(contenu);
    });
    QObject::connect(btnHist, &QPushButton::clicked, &dlg, [this, idSalle]() {
        this->ouvrirHistoriqueSalle(idSalle);
    });
    QObject::connect(btnSave, &QPushButton::clicked, &dlg, [this, pixQR, s]() {
        const QString path = QFileDialog::getSaveFileName(this, "Enregistrer le QR Code",
                                                          QString("qr_salle_%1.png").arg(s.nom), "Images PNG (*.png)");
        if (!path.isEmpty() && pixQR.save(path, "PNG"))
            QMessageBox::information(this, "QR Code", "Image enregistrée.");
    });

    dlg.exec();
}

void salle::ouvrirScannerImage()
{
    const QString chemin = QFileDialog::getOpenFileName(this,
                                                        "Importer une image QR Code", QString(), "Images (*.png *.jpg *.jpeg)");
    if (chemin.isEmpty()) return;

    QImage image(chemin);
    if (image.isNull()) {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image.");
        return;
    }

    QImage formatOk = image.convertToFormat(QImage::Format_Grayscale8);
    ZXing::ImageView imageView(formatOk.bits(), formatOk.width(), formatOk.height(),
                               ZXing::ImageFormat::Lum, formatOk.bytesPerLine());

    auto options = ZXing::ReaderOptions().setFormats(ZXing::BarcodeFormat::QRCode).setTryHarder(true);
    auto resultats = ZXing::ReadBarcodes(imageView, options);

    if (resultats.empty()) {
        QMessageBox::warning(this, "Scan QR",
                             "Aucun QR Code détecté dans cette image.");
        return;
    }

    traiterPayloadQRScanne(QString::fromStdString(resultats[0].text()).trimmed());
}

void salle::traiterPayloadQRScanne(const QString &texte)
{
    qint64 id = -1;
    static const QRegularExpression reHacknova(R"(^HACKNOVA\|\w+\|ID=(\d+)$)");
    const auto m = reHacknova.match(texte.trimmed());
    if (m.hasMatch()) {
        id = m.captured(1).toLongLong();
    } else {
        static const QRegularExpression reLegacy(R"(^SALLE-(\d+))");
        const auto m2 = reLegacy.match(texte.trimmed());
        if (m2.hasMatch()) id = m2.captured(1).toLongLong();
        else {
            bool ok = false;
            const qint64 v = texte.trimmed().toLongLong(&ok);
            if (ok) id = v;
        }
    }

    if (id <= 0) {
        QMessageBox::warning(this, "QR Code",
                             "Contenu QR invalide.\nFormat attendu : HACKNOVA|SALLE|ID=<n>");
        return;
    }

    const auto opt = chargerSalle(id);
    if (!opt.has_value()) {
        QMessageBox::warning(this, "QR Code — Salle introuvable",
                             QString("La salle associée à l'ID %1 n'existe plus ou est introuvable dans Oracle.").arg(id));
        return;
    }
    const Salle &s = *opt;
    const QString couleur = s.estDisponible() ? Palette::succes : Palette::danger;
    const QString etat    = s.estDisponible() ? "DISPONIBLE" : "INDISPONIBLE / OCCUPÉE";
    const QString msgQR   = genererMessageAutoQR(s, "scan");
    const QString eng     = genererEngagementAdmin(s);

    enregistrerHistorique(s.id, "QR", msgQR, eng);

    const QString periodeInfo = (s.dateDebut.isValid() && s.dureeJours > 0)
                                    ? QString("<b>Projet :</b> %1<br><b>Période :</b> Du %2 au %3 (%4 jour(s))")
                                          .arg(s.projetAssocie.isEmpty() ? "Réservation" : s.projetAssocie.toHtmlEscaped(),
                                               s.dateDebut.toString("dd/MM/yyyy"))
                                          .arg(s.dateFin.toString("dd/MM/yyyy"))
                                          .arg(s.dureeJours)
                                    : "Aucune période de réservation active enregistrée.";

    const QString corpsHtml = QString(
                                  "<p style='margin:0 0 6px 0;'><b>Identifiant :</b> #%1 · <b>Salle :</b> <b>%2</b> · "
                                  "<b>Catégorie :</b> %3 · <b>Capacité :</b> %4 places</p>"
                                  "<p style='margin:0 0 8px 0;'><b>État officiel :</b> <span style='color:%5;font-weight:800;'>%6</span></p>"
                                  "<p style='margin:0 0 8px 0;'>%7</p>"
                                  "<p style='margin:0;color:#94A3B8;'>%8</p>")
                                  .arg(s.id).arg(s.nom.toHtmlEscaped())
                                  .arg(s.type.toHtmlEscaped()).arg(s.capacite)
                                  .arg(couleur, etat.toHtmlEscaped(), msgQR, periodeInfo);

    const QString embedMsg = construireEmbedHtml(
        couleur,
        "FICHE OFFICIELLE QR · ORACLE",
        QString("Salle %1 — %2").arg(s.nom, etat),
        QDateTime::currentDateTime().toString("dd/MM/yyyy à HH:mm"),
        corpsHtml,
        QString("<b>Engagement officiel :</b> %1").arg(eng.toHtmlEscaped()),
        "HACKNOVA · Contrôle d'accès certifié");

    QMessageBox::information(this, "Fiche Officielle QR — Oracle", embedMsg);
}

QWidget *salle::creerWidgetActions(qint64 idSalle, const QString &nomSalle)
{
    auto *container = new QWidget;
    auto *lay = new QHBoxLayout(container);
    lay->setContentsMargins(4, 2, 4, 2);
    lay->setSpacing(4);

    auto makeBtn = [&](const QString &txt, const QString &bg, const QString &hover) {
        auto *b = new QPushButton(txt, container);
        b->setCursor(Qt::PointingHandCursor);
        b->setStyleSheet(QString(
                             "QPushButton { background-color:%1; color:#FFF; border:none;"
                             "border-radius:4px; padding:4px 6px; font-size:10px; font-weight:800;}"
                             "QPushButton:hover { background-color:%2; }").arg(bg, hover));
        return b;
    };

    auto *btnVoir  = makeBtn("VOIR",     "#334155", "#475569");
    auto *btnModif = makeBtn("MODIFIER", Palette::accent, Palette::accentDark);
    auto *btnQR    = makeBtn("QR",       Palette::succesDark, Palette::succes);
    auto *btnSuppr = makeBtn("SUPPR",    Palette::dangerDark, Palette::danger);

    lay->addWidget(btnVoir);
    lay->addWidget(btnModif);
    lay->addWidget(btnQR);
    lay->addWidget(btnSuppr);

    QObject::connect(btnVoir,  &QPushButton::clicked, this,
                     [this, idSalle]() { ouvrirConsultationSalle(idSalle); });
    QObject::connect(btnModif, &QPushButton::clicked, this,
                     [this, idSalle]() { ouvrirModificationSalle(idSalle); });
    QObject::connect(btnQR,    &QPushButton::clicked, this,
                     [this, idSalle]() { ouvrirGenerateurQR(idSalle); });
    QObject::connect(btnSuppr, &QPushButton::clicked, this,
                     [this, idSalle, nomSalle]() { ouvrirSuppressionSalle(idSalle, nomSalle); });

    return container;
}

/* ============================================================
 *  HELPERS — reset / rafraîchissement
 * ============================================================ */
void salle::onAnnulerSalle() { viderFormulaireSalle(); }

void salle::rafraichirSallesEtStats()
{
    remplirTableSalles();
    dessinerStatistiquesSalles();
    mettreAJourTableauDeBordBas();
}

void salle::viderFormulaireSalle()
{
    if (ui->lineEditSalleID)      ui->lineEditSalleID->clear();
    if (ui->comboBoxSalleBloc)    ui->comboBoxSalleBloc->setCurrentIndex(0);
    if (ui->spinBoxSalleEtage)    ui->spinBoxSalleEtage->setValue(1);
    if (ui->spinBoxSalleNumero)   ui->spinBoxSalleNumero->setValue(1);
    if (ui->spinBoxSalleCapacite) ui->spinBoxSalleCapacite->setValue(0);
    if (ui->comboBoxSalleType)    ui->comboBoxSalleType->setCurrentIndex(0);
    if (ui->lineEditSalleTypeAutre) {
        ui->lineEditSalleTypeAutre->clear();
        ui->lineEditSalleTypeAutre->setVisible(false);
    }
    if (ui->comboBoxSalleDispo)   ui->comboBoxSalleDispo->setCurrentIndex(0);
    if (ui->comboBoxSalleBloc)    ui->comboBoxSalleBloc->setFocus();
}

void salle::viderTableSalles()
{
    auto *t = ui->tableSalles;
    if (!t) return;
    t->setSortingEnabled(false);
    for (int i = t->rowCount() - 1; i >= 0; --i) {
        QWidget *w = t->cellWidget(i, 5);
        if (w) { t->removeCellWidget(i, 5); w->deleteLater(); }
    }
    t->clearContents();
    t->setRowCount(0);
}

/* ============================================================
 *  STATISTIQUES AVANCÉES (%, BARRES HORIZONTALES & VERTICALES)
 * ============================================================ */
void salle::dessinerStatistiquesSalles()
{
    if (!m_lblStatsResume || !m_lblBarHorizontale || !m_lblBarVerticale) return;

    const QVector<Salle> salles = chargerSallesFiltrees(CriteresTri{});
    const int total = salles.size();
    int dispo = 0, occupe = 0, capTotale = 0;
    QMap<QString, int> parType;
    QMap<QString, int> parCapacite;

    for (const Salle &s : salles) {
        if (s.estDisponible()) ++dispo;
        else ++occupe;
        capTotale += s.capacite;
        parType[s.type.isEmpty() ? "Non défini" : s.type]++;

        QString trancheCap;
        if (s.capacite < 10)      trancheCap = "< 10";
        else if (s.capacite < 30) trancheCap = "10-29";
        else if (s.capacite < 60) trancheCap = "30-59";
        else                      trancheCap = "60+";
        parCapacite[trancheCap]++;
    }

    const double pctDispo  = (total > 0) ? (100.0 * dispo  / total) : 0.0;
    const double pctOccupe = (total > 0) ? (100.0 * occupe / total) : 0.0;

    m_lblStatsResume->setText(QString(
                                  "<div style='background:#1E293B;border:1px solid #334155;border-radius:8px;padding:8px 10px;font-size:11px;color:#F1F5F9;'>"
                                  "<b>Total :</b> %1 &nbsp;|&nbsp; "
                                  "<span style='color:#34D399;'><b>Dispo :</b> %2 (%3%)</span> &nbsp;|&nbsp; "
                                  "<span style='color:#F87171;'><b>Occupées :</b> %4 (%5%)</span><br>"
                                  "<b>Capacité cumulée :</b> %6 places &nbsp;|&nbsp; "
                                  "<span style='color:#818CF8;'><b>Ajouts dispo :</b> +%7</span>"
                                  "</div>")
                                  .arg(total)
                                  .arg(dispo).arg(pctDispo, 0, 'f', 1)
                                  .arg(occupe).arg(pctOccupe, 0, 'f', 1)
                                  .arg(capTotale)
                                  .arg(m_compteurSallesDisponibles));

    // A. Barres horizontales (Disponibilité, Occupation, Types)
    {
        QPixmap pix(380, 270);
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(QColor(Palette::accentGlow));
        QFont tf("Segoe UI", 9, QFont::Bold);
        p.setFont(tf);
        p.drawText(6, 16, "A. Barres horizontales — États & Types");

        struct ItemBar { QString label; int val; QColor col; };
        QVector<ItemBar> items;
        items.append({"Disponible", dispo, QColor(Palette::succes)});
        items.append({"Occupée", occupe, QColor(Palette::danger)});
        for (auto it = parType.begin(); it != parType.end(); ++it) {
            items.append({it.key(), it.value(), QColor(Palette::accentGlow)});
        }

        int maxVal = 1;
        for (const auto &it : items) if (it.val > maxVal) maxVal = it.val;

        int y = 30;
        const int barH = 18;
        const int maxBarW = 165;
        QFont lf("Segoe UI", 8, QFont::Bold);
        p.setFont(lf);

        for (const auto &it : items) {
            if (y + barH > 260) break;
            p.setPen(QColor(Palette::texte));
            p.drawText(6, y + 13, it.label.left(18));

            p.setPen(Qt::NoPen);
            p.setBrush(QColor(Palette::carteAlt));
            p.drawRoundedRect(140, y, maxBarW, barH, 4, 4);

            const int w = int(maxBarW * (double(it.val) / maxVal));
            p.setBrush(it.col);
            p.drawRoundedRect(140, y, qMax(2, w), barH, 4, 4);

            p.setPen(QColor(Palette::texte));
            p.drawText(140 + maxBarW + 8, y + 13, QString::number(it.val));
            y += 26;
        }
        p.end();
        m_lblBarHorizontale->setPixmap(pix);
    }

    // B. Barres verticales (Tranches de capacité)
    {
        QPixmap pix(380, 280);
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(QColor(Palette::accentGlow));
        QFont tf("Segoe UI", 9, QFont::Bold);
        p.setFont(tf);
        p.drawText(6, 16, "B. Barres verticales — Capacités");

        const QStringList tranches = {"< 10", "10-29", "30-59", "60+"};
        int maxVal = 1;
        for (const QString &tr : tranches) {
            if (parCapacite.value(tr, 0) > maxVal) maxVal = parCapacite.value(tr, 0);
        }

        const int baseY = 238;
        const int maxH  = 160;
        const int barW  = 52;
        const int gap   = 32;
        int x = 26;

        QFont lf("Segoe UI", 8, QFont::Bold);
        p.setFont(lf);

        for (const QString &tr : tranches) {
            const int val = parCapacite.value(tr, 0);
            const int h = int(maxH * (double(val) / maxVal));

            p.setPen(Qt::NoPen);
            p.setBrush(QColor(Palette::carteAlt));
            p.drawRoundedRect(x, baseY - maxH, barW, maxH, 5, 5);

            p.setBrush(QColor(Palette::accentGlow));
            p.drawRoundedRect(x, baseY - h, barW, qMax(2, h), 5, 5);

            p.setPen(QColor(Palette::texte));
            p.drawText(x, baseY - h - 6, barW, 14, Qt::AlignCenter, QString::number(val));
            p.drawText(x, baseY + 6, barW, 18, Qt::AlignCenter, tr);

            x += barW + gap;
        }
        p.end();
        m_lblBarVerticale->setPixmap(pix);
    }
}

void salle::mettreAJourTableauDeBordBas()
{
    if (!m_lblDashTotal || !m_lblDashDispo || !m_lblDashOccupe || !m_lblDashTaux || !m_lblDashMaj)
        return;

    const QVector<Salle> salles = chargerSallesFiltrees(CriteresTri{});
    const int total = salles.size();
    int dispo = 0, occupe = 0;
    for (const Salle &s : salles) {
        if (s.estDisponible()) ++dispo;
        else ++occupe;
    }
    const double taux = (total > 0) ? (100.0 * dispo / total) : 0.0;

    m_lblDashTotal->setText(QString("<b>Total salles :</b> %1").arg(total));
    m_lblDashDispo->setText(QString("<b>Disponibles :</b> %1").arg(dispo));
    m_lblDashOccupe->setText(QString("<b>Occupées :</b> %1").arg(occupe));
    m_lblDashTaux->setText(QString("<b>Taux dispo :</b> %1%").arg(taux, 0, 'f', 1));
    m_lblDashMaj->setText(QString("<b>Dernière MAJ :</b> %1")
                              .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss")));
}

/* ============================================================
 *  NAVIGATION / LOGIN / CHATBOT
 * ============================================================ */
void salle::allerPage(int index)
{
    if (index < 0 || index >= ui->stackedWidget->count()) return;
    ui->stackedWidget->setCurrentIndex(index);
    QWidget *w = ui->stackedWidget->currentWidget();
    if (w) {
        if (auto *sa = w->findChild<QScrollArea*>())
            sa->verticalScrollBar()->setValue(0);
    }
    if (index == 2) {
        rafraichirSallesEtStats();
    }
}

void salle::goLogin()  { allerPage(0); }
void salle::goSalles() { allerPage(2); }

void salle::connecterLogin()
{
    if (ui->pushButtonConnexion)
        QObject::connect(ui->pushButtonConnexion, &QPushButton::clicked,
                         this, &salle::onConnexion);
    if (ui->lineEditMotDePasse)
        QObject::connect(ui->lineEditMotDePasse, &QLineEdit::returnPressed,
                         this, &salle::onConnexion);
    if (ui->lineEditIdentifiant)
        QObject::connect(ui->lineEditIdentifiant, &QLineEdit::returnPressed, this, [this]() {
            if (ui->lineEditMotDePasse) ui->lineEditMotDePasse->setFocus();
        });
    if (ui->checkBoxSouvenir && ui->lineEditMotDePasse) {
        QObject::connect(ui->checkBoxSouvenir, &QCheckBox::toggled, this, [this](bool checked) {
            ui->lineEditMotDePasse->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
        });
    }
}

void salle::onConnexion()
{
    if (!ui->lineEditIdentifiant || !ui->lineEditMotDePasse) return;

    const QString user = ui->lineEditIdentifiant->text().trimmed();
    const QString pass = ui->lineEditMotDePasse->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Connexion échouée",
                             "Nom d'utilisateur ou mot de passe incorrect.");
        if (user.isEmpty()) ui->lineEditIdentifiant->setFocus();
        else                ui->lineEditMotDePasse->setFocus();
        return;
    }

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Connexion", "Connexion à la base Oracle indisponible.");
        return;
    }

    QSqlQuery q(db);
    q.prepare("SELECT NOM_UTILISATEUR, ACTIF FROM UTILISATEURS "
              "WHERE UPPER(TRIM(NOM_UTILISATEUR)) = UPPER(TRIM(:u)) "
              "  AND MOT_DE_PASSE_HASH = :p");
    q.bindValue(":u", user, QSql::In);
    q.bindValue(":p", pass, QSql::In);

    if (!q.exec()) {
        QMessageBox::warning(this, "Connexion", "Erreur :\n" + q.lastError().text());
        return;
    }

    if (q.next()) {
        const QString actif = q.value(1).toString().trimmed().toUpper();
        if (actif == "O" || actif == "1" || actif == "0") {
            q.finish();
            ui->lineEditMotDePasse->clear();
            goSalles();
            return;
        }
        QMessageBox::warning(this, "Connexion refusée", "Ce compte est inactif.");
        q.finish();
        return;
    }

    q.finish();
    QMessageBox::warning(this, "Connexion échouée",
                         "Nom d'utilisateur ou mot de passe incorrect.");
    ui->lineEditMotDePasse->setFocus();
    ui->lineEditMotDePasse->selectAll();
}

void salle::connecterNavigation()
{
    if (ui->sallesPage_btnSalles)
        QObject::connect(ui->sallesPage_btnSalles, &QPushButton::clicked, this, &salle::goSalles);
    if (ui->sallesPage_btnNotifications)
        QObject::connect(ui->sallesPage_btnNotifications, &QPushButton::clicked, this, &salle::onNotifications);
    if (ui->sallesPage_btnProfil)
        QObject::connect(ui->sallesPage_btnProfil, &QPushButton::clicked, this, &salle::onProfil);
    if (ui->sallesPage_btnDeconnexion)
        QObject::connect(ui->sallesPage_btnDeconnexion, &QPushButton::clicked, this, &salle::onDeconnexion);
}

void salle::connecterChatbot()
{
    // Pas de widget chatbot dédié dans salle.ui
}

void salle::onEnvoyerQuestion()
{
    // Pas de widget chatbot dédié dans salle.ui
}

/* ============================================================
 *  DIALOGUES — notifications / profil / déconnexion (MODE SOMBRE)
 * ============================================================ */
static void afficherDialogue(QWidget *parent, const QString &titre, const QString &html)
{
    QDialog dlg(parent);
    dlg.setWindowTitle(titre);
    dlg.setMinimumSize(500, 400);
    dlg.setStyleSheet(QString("QDialog { background:%1; }").arg(Palette::carte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(20, 20, 20, 20);

    auto *txt = new QTextBrowser;
    txt->setHtml(html);
    txt->setOpenExternalLinks(true);
    txt->setStyleSheet(QString("QTextBrowser { background:%1; color:%2; "
                               "border:1px solid %3; border-radius:8px; padding:10px; font-size:13px; }")
                           .arg(Palette::carteAlt, Palette::texte, Palette::bordure));
    lay->addWidget(txt, 1);

    auto *btn = new QPushButton("FERMER");
    btn->setMinimumHeight(32);
    btn->setStyleSheet(salle::styleBouton(Palette::accentDark, Palette::accent));
    QObject::connect(btn, &QPushButton::clicked, &dlg, &QDialog::accept);
    lay->addWidget(btn, 0, Qt::AlignRight);

    dlg.exec();
}

void salle::onNotifications()
{
    afficherDialogue(this, "Notifications", R"(
        <div style='color:#F1F5F9;font-family:Segoe UI;font-size:13px;'>
        <p style='color:#818CF8;font-weight:800;'>Notification</p>
        <p style='color:#94A3B8;'>Aucune notification disponible.</p>
        </div>
    )");
}

void salle::onProfil()
{
    afficherDialogue(this, "Profil utilisateur", R"(
        <div style='color:#F1F5F9;text-align:center;font-family:Segoe UI;'>
        <h1 style='color:#818CF8;'>HN</h1>
        <h2>Utilisateur</h2>
        <p style='color:#94A3B8;'><b>Rôle :</b> Administrateur</p>
        <p style='color:#94A3B8;'><b>Statut :</b> <span style='color:#34D399;'>Actif</span></p>
        <hr/>
        <p style='color:#64748B;font-size:11px;'>HACKNOVA — Smart Hackathon Management</p>
        </div>
    )");
}

void salle::onDeconnexion()
{
    if (QMessageBox::question(this, "Déconnexion",
                              "Voulez-vous vous déconnecter ?",
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;
    if (ui->lineEditIdentifiant) ui->lineEditIdentifiant->clear();
    if (ui->lineEditMotDePasse)  ui->lineEditMotDePasse->clear();
    if (ui->checkBoxSouvenir)    ui->checkBoxSouvenir->setChecked(false);
    goLogin();
}

/* ============================================================
 *  THÈME GLOBAL SOMBRE — Identité HACKNOVA (#0B0F1A / #111827 / #4338CA)
 * ============================================================ */
void salle::appliquerThemeSombre()
{
    this->setStyleSheet(R"(
QMainWindow, QWidget#centralWidget, QWidget#pageLogin, QWidget#pageSalles,
QScrollArea, QWidget#scrollSallesContent { background-color:#0B0F1A; }
QWidget { color:#F1F5F9; font-family:'Segoe UI','Arial',sans-serif; font-size:13px; }
QToolTip { background-color:#1E1B4B; color:#FFFFFF; border:1px solid #818CF8;
           border-radius:6px; padding:6px 10px; }

QScrollBar:vertical { background:#0B0F1A; width:10px; }
QScrollBar::handle:vertical { background:#334155; min-height:40px; border-radius:5px; }
QScrollBar::handle:vertical:hover { background:#475569; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0; }

QFrame#frameLoginBrand { background-color:#1E1B4B; border:1px solid #4338CA;
    border-top-left-radius:20px; border-bottom-left-radius:20px; }
QFrame#frameLoginCard  { background-color:#111827; border:1px solid #334155;
    border-top-right-radius:20px; border-bottom-right-radius:20px; }
QLabel#labelLoginLogo { background-color:#4338CA; color:#FFFFFF; border-radius:60px;
    font-size:44px; font-weight:900; }
QLabel#labelLoginBrandTitle { color:#FFFFFF; font-size:28px; font-weight:900; letter-spacing:2px; }
QLabel#labelLoginBrandSub   { color:#A5B4FC; font-size:11px; font-weight:800; letter-spacing:1.5px; }
QLabel#labelLoginBrandSlogan{ color:#E0E7FF; font-size:13px; }
QLabel#labelLoginBrandTeam  { color:#818CF8; font-size:10px; font-weight:800; letter-spacing:1px; }
QLabel#labelLoginTitle      { color:#F1F5F9; font-size:24px; font-weight:900; }
QLabel#labelLoginField, QLabel#labelLoginField2 { color:#A5B4FC; font-size:11px; font-weight:800; letter-spacing:1px; }
QLineEdit#lineEditIdentifiant, QLineEdit#lineEditMotDePasse {
    background-color:#1E293B; color:#F1F5F9; border:1px solid #334155;
    border-radius:8px; padding:0 12px; font-size:14px; }
QLineEdit#lineEditIdentifiant:focus, QLineEdit#lineEditMotDePasse:focus { border:1px solid #818CF8; }
QCheckBox#checkBoxSouvenir { color:#94A3B8; font-size:12px; }
QPushButton#pushButtonConnexion { background-color:#4338CA; color:#FFFFFF; border:none;
    border-radius:8px; font-size:14px; font-weight:900; }
QPushButton#pushButtonConnexion:hover { background-color:#3730A3; }
QLabel#labelLoginFooter { color:#818CF8; font-size:12px; font-weight:bold; }

QFrame#frameNavbar, QFrame#sallesPage_frameNavbar { background-color:#111827;
    border:1px solid #334155; border-radius:12px; }
QLabel#labelNavLogo, QLabel#sallesPage_labelNavLogo { background-color:#4338CA; color:#FFFFFF;
    border-radius:8px; font-size:18px; font-weight:900; }
QLabel#labelNavBrand, QLabel#sallesPage_labelNavBrand { color:#FFFFFF; font-size:14px;
    font-weight:900; letter-spacing:1.5px; }
QLabel#labelNavSub, QLabel#sallesPage_labelNavSub { color:#A5B4FC; font-size:9px; font-weight:800; }

QPushButton#sallesPage_btnSalles, QPushButton#sallesPage_btnNotifications,
QPushButton#sallesPage_btnProfil {
    background-color:transparent; color:#CBD5E1; border:none; border-radius:6px;
    font-size:10px; font-weight:800; padding:6px 8px; }
QPushButton#sallesPage_btnSalles:hover, QPushButton#sallesPage_btnNotifications:hover,
QPushButton#sallesPage_btnProfil:hover {
    background-color:#1E293B; color:#FFFFFF; }
QPushButton#sallesPage_btnSalles {
    background-color:#4338CA; color:#FFFFFF; border-bottom:2px solid #A5B4FC; }
QPushButton#sallesPage_btnDeconnexion {
    background-color:#DC2626; color:#FFFFFF; border:none; border-radius:6px;
    font-size:10px; font-weight:800; padding:6px 8px; }
QPushButton#sallesPage_btnDeconnexion:hover {
    background-color:#B91C1C; }

QLabel#labelTitleSalles { color:#F1F5F9; font-size:22px; font-weight:900; }
QLabel#labelSubSalles   { color:#94A3B8; font-size:13px; }

QFrame#cardFormSalles, QFrame#cardTableSalles, QFrame#sallesPage_cardStats {
    background-color:#111827; border:1px solid #334155; border-radius:12px; }
QLabel#labelFormTitleSalles, QLabel#labelTableTitleSalles, QLabel#sallesPage_labelStatsTitle {
    color:#818CF8; font-size:15px; font-weight:800; }

QLabel#lblSalleID, QLabel#lblSalleCapacite, QLabel#lblSalleType, QLabel#lblSalleDispo,
QLabel#lblSalleBloc, QLabel#lblSalleEtage, QLabel#lblSalleNumero {
    color:#A5B4FC; font-size:11px; font-weight:800; }

QLineEdit#lineEditSalleID, QLineEdit#lineEdit_2, QLineEdit#lineEditSalleTypeAutre,
QSpinBox#spinBoxSalleCapacite, QSpinBox#spinBoxSalleEtage, QSpinBox#spinBoxSalleNumero,
QComboBox#comboBoxSalleBloc, QComboBox#comboBoxSalleType, QComboBox#comboBoxSalleDispo {
    background-color:#1E293B; color:#F1F5F9; border:1px solid #334155;
    border-radius:8px; padding:0 10px; font-size:13px; min-height:32px; }
QLineEdit#lineEdit_2:focus, QSpinBox#spinBoxSalleCapacite:focus { border:1px solid #818CF8; }

QComboBox QAbstractItemView { background-color:#1E293B; color:#F1F5F9;
    border:1px solid #475569; selection-background-color:#4338CA; selection-color:#FFFFFF; }

QPushButton#btnAjouterSalle, QPushButton#btnExporterSalle {
    background-color:#059669; color:#FFFFFF; border:none;
    border-radius:8px; font-size:12px; font-weight:800; padding:0 14px;
    min-width:100px; min-height:32px; }
QPushButton#btnAjouterSalle:hover, QPushButton#btnExporterSalle:hover {
    background-color:#10B981; }

QPushButton#btnAnnuler, QPushButton#btnTrierSalle {
    background-color:#1E293B; color:#F1F5F9; border:1px solid #475569;
    border-radius:8px; font-size:12px; font-weight:800; padding:0 14px;
    min-width:100px; min-height:32px; }
QPushButton#btnAnnuler:hover, QPushButton#btnTrierSalle:hover {
    background-color:#334155; }

QPushButton#btnRechercherSalle {
    background-color:#4338CA; color:#FFFFFF; border:none;
    border-radius:8px; font-size:12px; font-weight:800; padding:0 14px;
    min-width:100px; min-height:32px; }
QPushButton#btnRechercherSalle:hover {
    background-color:#3730A3; }

QTableWidget { background-color:#111827; alternate-background-color:#162032;
    color:#F1F5F9; border:1px solid #334155; border-radius:8px; gridline-color:#1E293B; }
QTableWidget::item { padding:4px 8px; border-bottom:1px solid #1E293B; }
QTableWidget::item:selected { background-color:#4338CA; color:#FFFFFF; }
QHeaderView::section { background-color:#1E1B4B; color:#FFFFFF; font-size:11px;
    font-weight:800; padding:8px 6px; border:none; }

QLabel#labelFooterSalles { color:#64748B; }

QMessageBox, QDialog { background-color:#111827; color:#F1F5F9; }
QMessageBox QLabel, QDialog QLabel { color:#F1F5F9; }
QMessageBox QPushButton, QDialog QPushButton {
    background-color:#4338CA; color:#FFFFFF; border:none; border-radius:8px;
    font-weight:800; padding:6px 16px; }
QMessageBox QPushButton:hover, QDialog QPushButton:hover { background-color:#3730A3; }
)");
}