#include "integration.h"

#include "ui_integration.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QPushButton>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QScrollArea>
#include <QScrollBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLineEdit>
#include <QInputDialog>
#include <QComboBox>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QFrame>
#include <QColor>
#include <QBrush>
#include <QFont>
#include <QPainter>
#include <QFontMetrics>
#include <QPainterPath>
#include <QMap>
#include <algorithm>
#include <utility>
#include <QCheckBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringConverter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QFileInfo>
#include <QDateTime>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QPersistentModelIndex>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QSet>
#include <QSizePolicy>

// ======================================================================
// === HELPERS ===========================================================
// ======================================================================

// ---------- Aide : convertit le modèle SQL (Etmp.afficher()) en liste d'objets Employe ----------
static QVector<Employe> lireEmployes(QSqlQueryModel *m)
{
    QVector<Employe> v;
    if (!m) return v;
    for (int i = 0; i < m->rowCount(); ++i) {
        auto champ = [&](int c) { return m->data(m->index(i, c)).toString(); };
        v.append(Employe(champ(0), champ(1), champ(2), champ(3), champ(4), champ(5)));
    }
    return v;
}

// Déclaration anticipée : l'export (CSV/PDF) prend directement des en-têtes et des lignes
static void exporterDonnees(QWidget *parent, const QStringList &entetes, const QVector<QStringList> &lignes,
                            const QString &nomParDefaut, const QString &titre);

// ---------- Aide : exporte les lignes d'un tableau en CSV (Excel) ou en PDF, au choix de l'utilisateur ----------
static void exporterTable(QWidget *parent, QTableWidget *t, const QList<int> &colonnes,
                          const QString &nomParDefaut, const QString &titre)
{
    QStringList entetes;
    for (int c : colonnes) {
        auto *h = t->horizontalHeaderItem(c);
        entetes << (h ? h->text() : QString::number(c));
    }

    QVector<QStringList> lignes;
    for (int r = 0; r < t->rowCount(); ++r) {
        if (t->isRowHidden(r)) continue;
        QStringList l;
        for (int c : colonnes) {
            auto *it = t->item(r, c);
            l << (it ? it->text() : QString());
        }
        lignes.append(l);
    }

    exporterDonnees(parent, entetes, lignes, nomParDefaut, titre);
}

// ---------- Export commun (CSV ou PDF) à partir d'en-têtes et de lignes déjà prêts ----------
static void exporterDonnees(QWidget *parent, const QStringList &entetes, const QVector<QStringList> &lignes,
                            const QString &nomParDefaut, const QString &titre)
{
    if (lignes.isEmpty()) {
        QMessageBox::information(parent, "Export", "Aucune donnée à exporter.");
        return;
    }

    const QString filtreCsv = "Fichier CSV (*.csv)";
    const QString filtrePdf = "Document PDF (*.pdf)";
    QString filtreChoisi;
    QString chemin = QFileDialog::getSaveFileName(parent, "Exporter",
                                                  QDir::home().filePath(nomParDefaut + ".csv"),
                                                  filtreCsv + ";;" + filtrePdf, &filtreChoisi);
    if (chemin.isEmpty()) return;                             // annulé par l'utilisateur

    QString ext = QFileInfo(chemin).suffix().toLower();
    if (ext != "csv" && ext != "pdf") {
        ext = (filtreChoisi == filtrePdf) ? "pdf" : "csv";
        chemin += "." + ext;
    }

    if (ext == "pdf") {
        QString html = "<h2 style='color:#4338CA;'>" + titre.toHtmlEscaped() + "</h2>"
                                                                               "<p>Généré le " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</p>"
                                                                                     "<table border='1' cellspacing='0' cellpadding='6' width='100%'>"
                                                                                     "<tr style='background-color:#E0E7FF;'>";
        for (const QString &e : std::as_const(entetes)) html += "<th>" + e.toHtmlEscaped() + "</th>";
        html += "</tr>";
        for (const QStringList &l : std::as_const(lignes)) {
            html += "<tr>";
            for (const QString &v : l) html += "<td>" + v.toHtmlEscaped() + "</td>";
            html += "</tr>";
        }
        html += "</table>";

        QPdfWriter pdf(chemin);
        pdf.setPageSize(QPageSize(QPageSize::A4));
        pdf.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
        QTextDocument doc;
        doc.setHtml(html);
        doc.print(&pdf);

        if (!QFileInfo::exists(chemin)) {
            QMessageBox::critical(parent, "Export", "Impossible d'écrire dans le fichier :\n" + chemin);
            return;
        }
    } else {
        auto champ = [](QString v) -> QString {
            // Protection contre les formules Excel (=, +, -, @) puis échappement CSV
            if (!v.isEmpty() && QStringLiteral("=+-@").contains(v.at(0))) v.prepend(QChar('\''));
            v.replace(QChar('"'), QStringLiteral("\"\""));
            return QStringLiteral("\"") + v + QStringLiteral("\"");
        };
        QFile f(chemin);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QMessageBox::critical(parent, "Export", "Impossible d'écrire dans le fichier :\n" + chemin);
            return;
        }
        QTextStream out(&f);
        out.setEncoding(QStringConverter::Utf8);
        out.setGenerateByteOrderMark(true);                   // accents corrects dans Excel
        QStringList e2; for (const QString &e : std::as_const(entetes)) e2 << champ(e);
        out << e2.join(';') << "\r\n";
        for (const QStringList &l : std::as_const(lignes)) {
            QStringList l2; for (const QString &v : l) l2 << champ(v);
            out << l2.join(';') << "\r\n";
        }
        out.flush();
        f.close();
    }

    QMessageBox::information(parent, "Export",
                             QString("%1 ligne(s) exportée(s) vers :\n%2").arg(lignes.size()).arg(chemin));
}

static void afficherDialogue(QWidget *parent, const QString &titre, const QString &html)
{
    QDialog dlg(parent); dlg.setWindowTitle(titre); dlg.setMinimumSize(500, 400);
    auto *lay = new QVBoxLayout(&dlg); lay->setContentsMargins(20, 20, 20, 20); lay->setSpacing(12);
    auto *txt = new QTextBrowser; txt->setHtml(html); txt->setOpenExternalLinks(true); lay->addWidget(txt, 1);
    auto *btn = new QPushButton("FERMER"); btn->setCursor(Qt::PointingHandCursor); btn->setMinimumHeight(32);
    QObject::connect(btn, &QPushButton::clicked, &dlg, &QDialog::accept); lay->addWidget(btn, 0, Qt::AlignRight);
    dlg.exec();
}

// ======================================================================
// === CONSTRUCTEUR & DESTRUCTEUR ========================================
// ======================================================================

integration::integration(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::integration)
{
    ui->setupUi(this);
    initialiserGestionEvaluateurs();
    construirePageEvaluateurs();
    ui->stackedWidget->setCurrentIndex(0);

    appliquerTheme();
    connecterLogin();
    connecterNavigation();
    connecterChatbot();
    connecterActions();
    connecterCRUDEmployes();
    connecterCRUDSalles();

    // Les employés sont chargés depuis Oracle au moment de la connexion (voir onConnexion)
    chargerSallesDepuisBDD();

    // Le tableau des employés est rempli après l'authentification (voir onConnexion)
    dessinerStatistiques();
    remplirTableSalles();
    dessinerStatistiquesSalles();

    QSqlQuery countUsers;
    if (countUsers.exec("SELECT COUNT(*) FROM EMPLOYE") && countUsers.next() && countUsers.value(0).toInt() == 0) {
        QMessageBox::information(this, "Premier démarrage", "Créez le compte Administrateur initial pour sécuriser l'accès à l'application.");
        bool ok = false;
        const QString nom = QInputDialog::getText(this, "Compte administrateur", "Nom :", QLineEdit::Normal, QString(), &ok).trimmed();
        if (ok && !nom.isEmpty()) {
            const QString prenom = QInputDialog::getText(this, "Compte administrateur", "Prénom :", QLineEdit::Normal, QString(), &ok).trimmed();
            if (ok && !prenom.isEmpty()) {
                const QString password = QInputDialog::getText(this, "Compte administrateur", "Mot de passe (6 caractères minimum) :", QLineEdit::Password, QString(), &ok);
                if (ok) {
                    Employe admin(Employe::prochainId(), nom, prenom, password, "Administrateur", "Actif");
                    const QString erreur = admin.verifierSaisie();
                    if (!erreur.isEmpty() || !admin.ajouter()) QMessageBox::critical(this, "Création impossible", erreur.isEmpty() ? "Vérifiez la structure de la table EMPLOYE." : erreur);
                    else QMessageBox::information(this, "Compte créé", QString("Le compte Administrateur est prêt. Identifiant : %1").arg(admin.getId()));
                }
            }
        }
    }
}

integration::~integration()
{
    delete m_modelEmp;
    delete ui;
}

// ======================================================================
// === SLOTS GÉNÉRAUX (CONNEXION, NAVIGATION, THÈME) =====================
// ======================================================================

void integration::connecterLogin()
{
    if (ui->pushButtonConnexion)
        connect(ui->pushButtonConnexion, &QPushButton::clicked, this, &integration::onConnexion);
    if (ui->lineEditMotDePasse)
        connect(ui->lineEditMotDePasse, &QLineEdit::returnPressed, this, &integration::onConnexion);
    connect(ui->checkBoxSouvenir, &QCheckBox::toggled, this, [this](bool v) {
        ui->lineEditMotDePasse->setEchoMode(v ? QLineEdit::Normal : QLineEdit::Password);
    });
}

void integration::construirePageEvaluateurs()
{
    auto *page = ui->pageEvaluateurs;
    m_pageEvaluateurs = page;
    page->setMinimumSize(0, 0);
    page->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    // Défilement vertical (haut / bas) comme la page « Gestion des employés » :
    // tout le contenu est placé dans une QScrollArea qui occupe la page.
    auto *scroll = new QScrollArea(page);
    scroll->setObjectName("scrollEvaluateurs");
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidgetResizable(false);
    ui->eval_mainContent->setGeometry(0, 0, 1420, 1000);            // même taille de contenu que les employés
    scroll->setWidget(ui->eval_mainContent);
    auto *pageLayout = new QVBoxLayout(page);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    pageLayout->addWidget(scroll);

    connect(ui->sallesPage_btnDashboard_2, &QPushButton::clicked, this, [this]() { allerPage(1); });
    connect(ui->sallesPage_btnEmployes_2, &QPushButton::clicked, this, &integration::goEmployes);
    connect(ui->sallesPage_btnSalles_2, &QPushButton::clicked, this, &integration::goSalles);
    connect(ui->sallesPage_btnParticipants_2, &QPushButton::clicked, this, [this]() { QMessageBox::information(this, "Participants", "Le module Participants n'est pas encore intégré à cette application."); });
    connect(ui->sallesPage_btnSponsors_2, &QPushButton::clicked, this, [this]() { QMessageBox::information(this, "Sponsors", "Le module Sponsors n'est pas encore intégré à cette application."); });
    connect(ui->sallesPage_btnProjets_2, &QPushButton::clicked, this, [this]() { QMessageBox::information(this, "Projets", "Le module Projets n'est pas encore intégré à cette application."); });
    connect(ui->sallesPage_btnNotifications_2, &QPushButton::clicked, this, &integration::onNotifications);
    connect(ui->sallesPage_btnProfil_2, &QPushButton::clicked, this, &integration::onProfil);
    connect(ui->sallesPage_btnDeconnexion_2, &QPushButton::clicked, this, &integration::onDeconnexion);

    const auto descendants = page->findChildren<QWidget*>();
    for (QWidget *widget : descendants) widget->setStyleSheet(QString());
    page->setStyleSheet(R"(
QScrollArea#scrollEvaluateurs { background:#080C14; border:0; }
QWidget#pageEvaluateurs, QWidget#eval_mainContent { background:#080C14; color:#E2E8F0; font-family:'Segoe UI','Arial',sans-serif; font-size:13px; }
QFrame#sallesPage_frameNavbar_2 { background:#111827; border:1px solid #1E293B; border-radius:12px; }
QLabel#sallesPage_labelNavLogo_2 { background:#4338CA; color:#fff; border-radius:10px; font-size:19px; font-weight:900; }
QLabel#sallesPage_labelNavBrand_2 { color:#fff; font-size:14px; font-weight:900; letter-spacing:1px; }
QLabel#sallesPage_labelNavSub_2 { color:#818CF8; font-size:9px; font-weight:800; letter-spacing:.6px; }
QPushButton#sallesPage_btnDashboard_2, QPushButton#sallesPage_btnEmployes_2, QPushButton#sallesPage_btnSalles_2, QPushButton#sallesPage_btnEvaluateurs_2, QPushButton#sallesPage_btnParticipants_2, QPushButton#sallesPage_btnSponsors_2, QPushButton#sallesPage_btnProjets_2, QPushButton#sallesPage_btnNotifications_2, QPushButton#sallesPage_btnProfil_2 { background:transparent; color:#94A3B8; border:0; border-radius:6px; padding:6px 8px; font-size:9px; font-weight:800; }
QPushButton#sallesPage_btnDashboard_2:hover, QPushButton#sallesPage_btnEmployes_2:hover, QPushButton#sallesPage_btnSalles_2:hover, QPushButton#sallesPage_btnEvaluateurs_2:hover, QPushButton#sallesPage_btnParticipants_2:hover, QPushButton#sallesPage_btnSponsors_2:hover, QPushButton#sallesPage_btnProjets_2:hover, QPushButton#sallesPage_btnNotifications_2:hover, QPushButton#sallesPage_btnProfil_2:hover { background:#1F2937; color:#F1F5F9; }
QPushButton#sallesPage_btnEvaluateurs_2 { background:#312E81; color:#fff; border-bottom:2px solid #6366F1; }
QPushButton#sallesPage_btnDeconnexion_2 { background:#7F1D1D; color:#fff; border:1px solid #991B1B; border-radius:6px; padding:6px 10px; font-size:9px; font-weight:800; }
QLabel#eval_pageTitle { color:#fff; font-size:22px; font-weight:900; letter-spacing:.5px; }
QLabel#eval_subTitle { color:#64748B; font-size:13px; }
QFrame#eval_cardFormEvaluateurs, QFrame#eval_cardTableEvaluateurs, QFrame#eval_cardDeliberation, QFrame#eval_cardTechChallenge { background:#111827; border:1px solid #1E293B; border-radius:12px; }
QFrame#eval_cardStatsEvaluateurs { background:#111827; border:1px solid #312E81; border-radius:12px; }
QFrame#eval_frameSaisieDeliberation, QFrame#eval_frameSaisieTechChallenge { background:transparent; border:1px solid #1E293B; border-radius:8px; }
QLabel#eval_formTitle, QLabel#eval_listTitle, QLabel#eval_deliberationTitle, QLabel#eval_techChallengeTitle { color:#fff; font-size:15px; font-weight:800; }
QLabel#eval_idLabel, QLabel#eval_nomLabel, QLabel#eval_prenomLabel, QLabel#eval_statutLabel { color:#818CF8; font-size:10px; font-weight:800; letter-spacing:.5px; }
QLabel#eval_deliberationDescription, QLabel#eval_techChallengeDescription { color:#94A3B8; font-size:11px; }
QLabel#eval_labelTotal, QLabel#eval_labelActifs, QLabel#eval_labelInactifs { color:#94A3B8; font-size:12px; }
QLabel#eval_statsChartHost, QLabel#eval_projetBar { background:transparent; }
QLabel#eval_labelStatsTitle { color:#fff; font-size:14px; font-weight:800; }
QFrame#eval_cardStatsEvaluateurs QLabel, QFrame#eval_cardTechChallenge QLabel, QFrame#eval_cardDeliberation QLabel { border:none; background:transparent; }
QLineEdit, QComboBox { background:#0B1120; color:#F1F5F9; border:1px solid #334155; border-radius:6px; padding:6px 10px; min-height:30px; selection-background-color:#4338CA; }
QLineEdit:focus, QComboBox:focus { border:1px solid #6366F1; }
QLineEdit:read-only { background:#1E293B; color:#64748B; }
QComboBox::drop-down { border:0; width:20px; }
QComboBox::down-arrow { border-left:4px solid transparent; border-right:4px solid transparent; border-top:5px solid #818CF8; width:0; height:0; margin-right:6px; }
QComboBox QAbstractItemView { background:#1E293B; color:#F1F5F9; selection-background-color:#4338CA; }
QPushButton#eval_btnAjouter, QPushButton#eval_btnExporter { background:#059669; color:#fff; border:1px solid #047857; border-radius:6px; padding:0 12px; font-weight:800; }
QPushButton#eval_btnAjouter:hover, QPushButton#eval_btnExporter:hover { background:#10B981; }
QPushButton#eval_btnAnnuler, QPushButton#eval_btnTrier { background:#1E293B; color:#CBD5E1; border:1px solid #334155; border-radius:6px; padding:0 12px; font-weight:800; }
QPushButton#eval_btnRechercher { background:#4338CA; color:#fff; border:1px solid #3730A3; border-radius:6px; padding:0 12px; font-weight:800; }
QPushButton#eval_btnMetier1, QPushButton#eval_btnMetier2 { background:#4338CA; color:#fff; border:1px solid #3730A3; border-radius:6px; padding:5px 10px; font-size:10px; font-weight:800; }
QPushButton#eval_btnMetier1:hover, QPushButton#eval_btnMetier2:hover { background:#312E81; color:#fff; border-color:#6366F1; }
QPushButton#btnChallengeAnalyst_4, QPushButton#btnSoumettreDeliberation_3 { background:#4338CA; color:#fff; border:1px solid #6366F1; border-radius:6px; padding:0 10px; font-weight:800; }
QPushButton#btnChallengeAnalyst_4:hover, QPushButton#btnSoumettreDeliberation_3:hover { background:#6366F1; border-color:#818CF8; }
QPushButton#btnChallengeAnalyst_4:pressed, QPushButton#btnSoumettreDeliberation_3:pressed { background:#3730A3; }
QTableView { background:#0B1120; alternate-background-color:#111827; color:#E2E8F0; border:1px solid #1E293B; border-radius:8px; gridline-color:#1E293B; font-size:13px; selection-background-color:#312E81; selection-color:#fff; outline:none; }
QTableView::item { padding:4px 8px; border-bottom:1px solid #1E293B; }
QTableView::item:selected { background:#312E81; color:#fff; }
QTableView QHeaderView::section { background:#111827; color:#94A3B8; font-size:11px; font-weight:800; letter-spacing:.5px; padding:8px 6px; border:0; border-bottom:2px solid #312E81; }
QTableView QHeaderView::section:first { border-top-left-radius:8px; }
QTableView QHeaderView::section:last { border-top-right-radius:8px; }
QTableView QTableCornerButton::section { background:#111827; border:0; }
QMessageBox, QDialog { background:#111827; color:#E2E8F0; }
QMessageBox QLabel, QDialog QLabel { color:#E2E8F0; }
QMessageBox QPushButton, QDialog QPushButton { background:#4338CA; color:#fff; border:0; border-radius:6px; padding:6px 16px; }
    )");
}


void integration::connecterNavigation()
{
    if (ui->btnEmployes) connect(ui->btnEmployes, &QPushButton::clicked, this, &integration::goEmployes);
    if (ui->btnSalles) connect(ui->btnSalles, &QPushButton::clicked, this, &integration::goSalles);
    if (ui->sallesPage_btnSalles) connect(ui->sallesPage_btnSalles, &QPushButton::clicked, this, &integration::goSalles);
    if (ui->sallesPage_btnEmployes) connect(ui->sallesPage_btnEmployes, &QPushButton::clicked, this, &integration::goEmployes);

    if (ui->btnEvaluateurs) connect(ui->btnEvaluateurs, &QPushButton::clicked, this, &integration::goEvaluateurs);
    if (ui->sallesPage_btnEvaluateurs) connect(ui->sallesPage_btnEvaluateurs, &QPushButton::clicked, this, &integration::goEvaluateurs);


    if (ui->btnNotifications) connect(ui->btnNotifications, &QPushButton::clicked, this, &integration::onNotifications);
    if (ui->btnProfil)        connect(ui->btnProfil,        &QPushButton::clicked, this, &integration::onProfil);
    if (ui->btnDeconnexion)   connect(ui->btnDeconnexion,   &QPushButton::clicked, this, &integration::onDeconnexion);
}

void integration::appliquerTheme()
{
    this->setStyleSheet(R"(
QMainWindow, QWidget#centralWidget { background-color: #080C14; }
QWidget { color: #E2E8F0; font-family: 'Segoe UI', 'Arial', sans-serif; font-size: 13px; }
QToolTip { background-color: #1E293B; color: #F1F5F9; border: 1px solid #475569; border-radius: 6px; padding: 6px 10px; font-size: 12px; }
QScrollBar:vertical { background: transparent; width: 10px; margin: 0; }
QScrollBar::handle:vertical { background: #334155; min-height: 40px; border-radius: 5px; }
QScrollBar::handle:vertical:hover { background: #475569; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
QScrollBar:horizontal { background: transparent; height: 10px; }
QScrollBar::handle:horizontal { background: #334155; min-width: 40px; border-radius: 5px; }
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }
QFrame#frameLoginBrand { background-color: #1E1B4B; border: 1px solid #312E81; border-top-left-radius: 20px; border-bottom-left-radius: 20px; }
QFrame#frameLoginCard { background-color: #111827; border: 1px solid #1E293B; border-top-right-radius: 20px; border-bottom-right-radius: 20px; }
QLabel#labelLoginLogo { background-color: #4338CA; color: #FFFFFF; border-radius: 60px; font-family: 'Segoe UI', 'Arial'; font-size: 44px; font-weight: 900; }
QLabel#labelLoginBrandTitle { color: #FFFFFF; font-size: 28px; font-weight: 900; letter-spacing: 2px; }
QLabel#labelLoginBrandSub { color: #A5B4FC; font-size: 11px; font-weight: 800; letter-spacing: 1.5px; }
QLabel#labelLoginBrandSlogan { color: #C7D2FE; font-size: 13px; }
QLabel#labelLoginBrandTeam { color: #6366F1; font-size: 10px; font-weight: 800; letter-spacing: 1px; }
QLabel#labelLoginTitle { color: #FFFFFF; font-size: 24px; font-weight: 900; }
QLabel#labelLoginField, QLabel#labelLoginField2 { color: #818CF8; font-size: 11px; font-weight: 800; letter-spacing: 1px; }
QLineEdit#lineEditIdentifiant, QLineEdit#lineEditMotDePasse { background-color: #0F172A; color: #F1F5F9; border: 1px solid #334155; border-radius: 8px; padding: 0 12px; font-size: 14px; selection-background-color: #4338CA; }
QLineEdit#lineEditIdentifiant:focus, QLineEdit#lineEditMotDePasse:focus { border: 1px solid #6366F1; background-color: #111827; }
QCheckBox#checkBoxSouvenir { color: #94A3B8; font-size: 12px; spacing: 6px; }
QCheckBox#checkBoxSouvenir::indicator { width: 16px; height: 16px; border: 1px solid #475569; border-radius: 3px; background: #0F172A; }
QCheckBox#checkBoxSouvenir::indicator:checked { background: #4338CA; border: 1px solid #6366F1; }
QPushButton#pushButtonConnexion { background-color: #4338CA; color: #FFFFFF; border: none; border-radius: 8px; font-size: 14px; font-weight: 900; letter-spacing: 1px; }
QPushButton#pushButtonConnexion:hover { background-color: #6366F1; }
QPushButton#pushButtonConnexion:pressed { background-color: #3730A3; }
QLabel#labelLoginFooter { color: #6366F1; font-size: 12px; font-weight: bold; }
QFrame#frameNavbar, QFrame#sallesPage_frameNavbar { background-color: #111827; border: 1px solid #1E293B; border-radius: 12px; }
QLabel#labelNavLogo, QLabel#sallesPage_labelNavLogo { background-color: #4338CA; color: #FFFFFF; border-radius: 8px; font-size: 18px; font-weight: 900; }
QLabel#labelNavBrand, QLabel#sallesPage_labelNavBrand { color: #FFFFFF; font-size: 14px; font-weight: 900; letter-spacing: 1.5px; }
QLabel#labelNavSub, QLabel#sallesPage_labelNavSub { color: #818CF8; font-size: 9px; font-weight: 800; letter-spacing: 0.5px; }
QPushButton#btnDashboard, QPushButton#btnEmployes, QPushButton#btnSalles, QPushButton#btnEvaluateurs, QPushButton#btnParticipants, QPushButton#btnSponsors, QPushButton#btnProjets, QPushButton#btnNotifications, QPushButton#btnProfil, QPushButton#sallesPage_btnDashboard, QPushButton#sallesPage_btnEmployes, QPushButton#sallesPage_btnEvaluateurs, QPushButton#sallesPage_btnParticipants, QPushButton#sallesPage_btnSponsors, QPushButton#sallesPage_btnProjets, QPushButton#sallesPage_btnNotifications, QPushButton#sallesPage_btnProfil { background-color: transparent; color: #94A3B8; border: none; border-radius: 6px; font-size: 10px; font-weight: 800; letter-spacing: 0.5px; padding: 6px 8px; }
QPushButton#btnDashboard:hover, QPushButton#btnEmployes:hover, QPushButton#btnSalles:hover, QPushButton#btnEvaluateurs:hover, QPushButton#btnParticipants:hover, QPushButton#btnSponsors:hover, QPushButton#btnProjets:hover, QPushButton#btnNotifications:hover, QPushButton#btnProfil:hover, QPushButton#sallesPage_btnDashboard:hover, QPushButton#sallesPage_btnEmployes:hover, QPushButton#sallesPage_btnEvaluateurs:hover, QPushButton#sallesPage_btnParticipants:hover, QPushButton#sallesPage_btnSponsors:hover, QPushButton#sallesPage_btnProjets:hover, QPushButton#sallesPage_btnNotifications:hover, QPushButton#sallesPage_btnProfil:hover { background-color: #1F2937; color: #F1F5F9; }
QPushButton#btnEmployes, QPushButton#sallesPage_btnSalles { background-color: #312E81; color: #FFFFFF; border-bottom: 2px solid #6366F1; }
QPushButton#btnDeconnexion, QPushButton#sallesPage_btnDeconnexion { background-color: #7F1D1D; color: #FFFFFF; border: 1px solid #991B1B; border-radius: 6px; font-size: 10px; font-weight: 800; padding: 6px 8px; }
QPushButton#btnDeconnexion:hover, QPushButton#sallesPage_btnDeconnexion:hover { background-color: #991B1B; }
QLabel#labelTitleEmployes, QLabel#labelTitleSalles { color: #FFFFFF; font-size: 22px; font-weight: 900; letter-spacing: 0.5px; }
QLabel#labelSubEmployes, QLabel#labelSubSalles { color: #64748B; font-size: 13px; }
QFrame#cardFormEmployes, QFrame#cardFormSalles, QFrame#cardTableEmployes, QFrame#cardTableSalles, QFrame#frameChatbot, QFrame#cardStats, QFrame#sallesPage_cardStats, QFrame#frameAffectation_2, QFrame#frameQR_4 { background-color: #111827; border: 1px solid #1E293B; border-radius: 12px; }
QLabel#labelFormTitleEmployes, QLabel#labelFormTitleSalles, QLabel#labelTableTitleEmployes, QLabel#labelTableTitleSalles, QLabel#lblTitreChatbot, QLabel#labelStatsTitle, QLabel#sallesPage_labelStatsTitle, QLabel#lblTitreAffect_2, QLabel#lblTitreQR_4 { color: #FFFFFF; font-size: 15px; font-weight: 800; letter-spacing: 0.5px; }
QLabel#lblDescAffect_2, QLabel#lblDescQR_4 { color: #94A3B8; font-size: 12px; }
QLabel#lblEmpID, QLabel#lblEmpNom, QLabel#lblEmpPrenom, QLabel#lblEmpMdp, QLabel#lblEmpRole, QLabel#lblEmpStatut, QLabel#lblSalleID, QLabel#lblSalleNom, QLabel#lblSalleCapacite, QLabel#lblSalleType, QLabel#lblSalleDispo { color: #818CF8; font-size: 11px; font-weight: 800; letter-spacing: 0.5px; }
QLineEdit#lineEditEmpID, QLineEdit#lineEditEmpNom, QLineEdit#lineEditEmpPrenom, QLineEdit#lineEditEmpMdp, QLineEdit#lineEditSalleID, QLineEdit#lineEditSalleNom, QLineEdit#lineEditRechercheEmp, QLineEdit#lineEditRechercheSalle, QSpinBox#spinBoxSalleCapacite { background-color: #0B1120; color: #F1F5F9; border: 1px solid #334155; border-radius: 6px; padding: 0 10px; font-size: 13px; selection-background-color: #4338CA; min-height: 32px; }
QLineEdit#lineEditEmpID:focus, QLineEdit#lineEditEmpNom:focus, QLineEdit#lineEditEmpPrenom:focus, QLineEdit#lineEditEmpMdp:focus, QLineEdit#lineEditSalleID:focus, QLineEdit#lineEditSalleNom:focus, QLineEdit#lineEditRechercheEmp:focus, QLineEdit#lineEditRechercheSalle:focus, QSpinBox#spinBoxSalleCapacite:focus { border: 1px solid #6366F1; background-color: #111827; }
QLineEdit#lineEditEmpID:read-only, QLineEdit#lineEditSalleID:read-only { background-color: #1E293B; color: #64748B; }
QComboBox#comboBoxEmpRole, QComboBox#comboBoxEmpStatut, QComboBox#comboBoxSalleType, QComboBox#comboBoxSalleDispo, QComboBox#comboTriEmploye { background-color: #0B1120; color: #F1F5F9; border: 1px solid #334155; border-radius: 6px; padding: 0 10px; font-size: 13px; min-height: 32px; }
QComboBox#comboBoxEmpRole:focus, QComboBox#comboBoxEmpStatut:focus, QComboBox#comboBoxSalleType:focus, QComboBox#comboBoxSalleDispo:focus, QComboBox#comboTriEmploye:focus { border: 1px solid #6366F1; }
QComboBox::drop-down { border: none; width: 20px; }
QComboBox::down-arrow { border-left: 4px solid transparent; border-right: 4px solid transparent; border-top: 5px solid #818CF8; width: 0; height: 0; margin-right: 6px; }
QComboBox QAbstractItemView { background-color: #1E293B; color: #F1F5F9; border: 1px solid #334155; border-radius: 6px; selection-background-color: #4338CA; selection-color: #FFFFFF; padding: 4px; font-size: 13px; }
QPushButton#btnAjouterEmploye, QPushButton#btnExporterEmploye, QPushButton#btnAjouterSalle, QPushButton#btnExporterSalle { background-color: #059669; color: #FFFFFF; border: 1px solid #047857; border-radius: 6px; font-size: 12px; font-weight: 800; letter-spacing: 0.5px; padding: 0 14px; min-width: 100px; min-height: 32px; }
QPushButton#btnAjouterEmploye:hover, QPushButton#btnExporterEmploye:hover, QPushButton#btnAjouterSalle:hover, QPushButton#btnExporterSalle:hover { background-color: #10B981; border-color: #34D399; }
QPushButton#btnAjouterEmploye:pressed, QPushButton#btnExporterEmploye:pressed, QPushButton#btnAjouterSalle:pressed, QPushButton#btnExporterSalle:pressed { background-color: #047857; }
QPushButton#btnAnnulerEmploye, QPushButton#btnTrierEmploye, QPushButton#btnAnnulerSalle, QPushButton#btnTrierSalle { background-color: #1E293B; color: #CBD5E1; border: 1px solid #334155; border-radius: 6px; font-size: 12px; font-weight: 800; padding: 0 14px; min-width: 100px; min-height: 32px; }
QPushButton#btnAnnulerEmploye:hover, QPushButton#btnTrierEmploye:hover, QPushButton#btnAnnulerSalle:hover, QPushButton#btnTrierSalle:hover { background-color: #334155; color: #FFFFFF; border-color: #475569; }
QPushButton#btnRechercherEmploye, QPushButton#btnRechercherSalle { background-color: #4338CA; color: #FFFFFF; border: 1px solid #3730A3; border-radius: 6px; font-size: 12px; font-weight: 800; letter-spacing: 0.5px; padding: 0 14px; min-width: 100px; min-height: 32px; }
QPushButton#btnRechercherEmploye:hover, QPushButton#btnRechercherSalle:hover { background-color: #6366F1; border-color: #818CF8; }
QPushButton#btnSuggererSalle, QPushButton#btnValiderQRSalle, QPushButton#btnEnvoyer { background-color: #4338CA; color: #FFFFFF; border: 1px solid #3730A3; border-radius: 6px; font-size: 12px; font-weight: 800; padding: 0 12px; min-width: 80px; min-height: 30px; }
QPushButton#btnSuggererSalle:hover, QPushButton#btnValiderQRSalle:hover, QPushButton#btnEnvoyer:hover { background-color: #6366F1; border-color: #818CF8; }
QTableWidget { background-color: #0B1120; alternate-background-color: #111827; color: #E2E8F0; border: 1px solid #1E293B; border-radius: 8px; gridline-color: #1E293B; font-size: 13px; selection-background-color: #312E81; selection-color: #FFFFFF; outline: none; }
QTableWidget::item { padding: 4px 8px; border-bottom: 1px solid #1E293B; }
QTableWidget::item:selected { background-color: #312E81; color: #FFFFFF; }
QScrollBar:vertical { width: 18px; background: #0B1120; margin: 3px 2px; border-radius: 8px; }
QScrollBar::handle:vertical { min-height: 52px; background: #475569; border: 3px solid #0B1120; border-radius: 7px; }
QScrollBar::handle:vertical:hover { background: #818CF8; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: #111827; }
QHeaderView::section { background-color: #111827; color: #94A3B8; font-size: 11px; font-weight: 800; letter-spacing: 0.5px; padding: 8px 6px; border: none; border-bottom: 2px solid #312E81; }
QHeaderView::section:first { border-top-left-radius: 8px; }
QHeaderView::section:last  { border-top-right-radius: 8px; }
QTableCornerButton::section { background-color: #111827; border: none; }
QFrame#frameChatbot, QFrame#frameAffectation_2, QFrame#frameQR_4 { background-color: #111827; border: 1px solid #1E293B; border-radius: 12px; }
QLabel#lblTitreChatbot, QLabel#lblTitreAffect_2, QLabel#lblTitreQR_4 { color: #FFFFFF; font-size: 13px; font-weight: 800; }
QFrame#frameSaisieChatbot, QFrame#frameSaisieAffect_2, QFrame#frameSaisieQR_4 { background-color: #0B1120; border: 1px solid #1E293B; border-radius: 8px; }
QTextBrowser#textChatbot { background-color: #0B1120; color: #E2E8F0; border: 1px solid #1E293B; border-radius: 8px; font-size: 13px; padding: 6px; selection-background-color: #4338CA; }
QLineEdit#leQuestion, QLineEdit#lineEditEffectifSalle, QLineEdit#lineEditCodeQRSalle { background-color: #111827; color: #F1F5F9; border: 1px solid #334155; border-radius: 6px; padding: 0 10px; font-size: 13px; }
QLineEdit#leQuestion:focus, QLineEdit#lineEditEffectifSalle:focus, QLineEdit#lineEditCodeQRSalle:focus { border: 1px solid #6366F1; background-color: #0B1120; }
QFrame#cardStats, QFrame#sallesPage_cardStats { background-color: #111827; border: 1px solid #312E81; border-radius: 12px; }
QLabel#labelStatsTitle, QLabel#sallesPage_labelStatsTitle { color: #FFFFFF; font-size: 14px; font-weight: 800; }
QLabel#labelStatutPie, QLabel#labelRoleBar, QLabel#sallesPage_labelStatutPie, QLabel#sallesPage_labelRoleBar { background-color: transparent; }
QLabel#labelFooterEmployes, QLabel#labelFooterSalles { color: #475569; font-size: 11px; }
QMessageBox, QDialog { background-color: #111827; color: #E2E8F0; }
QMessageBox QLabel, QDialog QLabel { color: #E2E8F0; font-size: 13px; }
QMessageBox QPushButton, QDialog QPushButton { background-color: #4338CA; color: #FFFFFF; border: none; border-radius: 6px; font-size: 12px; font-weight: 800; padding: 6px 16px; min-width: 70px; }
QMessageBox QPushButton:hover, QDialog QPushButton:hover { background-color: #6366F1; }
QPushButton:disabled { background-color: #1E293B !important; color: #475569 !important; border: 1px solid #334155 !important; }
)");
}

void integration::allerPage(int index)
{
    if (index < 0 || index >= ui->stackedWidget->count()) return;
    ui->stackedWidget->setCurrentIndex(index);
    QWidget *w = ui->stackedWidget->currentWidget();
    if (w) { if (auto *sa = w->findChild<QScrollArea*>()) sa->verticalScrollBar()->setValue(0); }
}

void integration::goLogin()    { allerPage(0); }

void integration::goEmployes() { allerPage(1); }

void integration::goSalles()   { if (m_roleConnecte == "Administrateur") allerPage(2); }

void integration::goEvaluateurs()
{
    if (m_roleConnecte == "Administrateur" && m_pageEvaluateurs)
        allerPage(ui->stackedWidget->indexOf(m_pageEvaluateurs));
}

void integration::onConnexion()
{
    const QString user = ui->lineEditIdentifiant->text().trimmed();
    const QString pass = ui->lineEditMotDePasse->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Connexion", "Veuillez saisir votre identifiant et votre mot de passe.");
        return;
    }

    // Vérification dans Oracle (requête préparée, dans la classe Employe)
    if (!Employe::authentifier(user, pass)) {
        QMessageBox::warning(this, "Connexion échouée", "Identifiant ou mot de passe incorrect.");
        return;
    }

    // Authentification réussie : on retient l'utilisateur connecté et son rôle (droits d'accès)
    Employe moi;
    if (!Employe::trouver(user, moi)) {
        QMessageBox::warning(this, "Connexion échouée", "Impossible de charger votre profil.");
        return;
    }
    m_idConnecte   = moi.getId().trimmed();
    m_roleConnecte = moi.getRole();
    const bool admin = m_roleConnecte == "Administrateur";
    ui->btnSalles->setVisible(admin);
    ui->btnDashboard->setVisible(admin);
    ui->btnEvaluateurs->setVisible(admin);
    ui->btnParticipants->setVisible(admin);
    ui->btnSponsors->setVisible(admin);
    ui->btnProjets->setVisible(admin);
    ui->btnNotifications->setVisible(admin);
    ui->btnProfil->setVisible(true);
    ui->sallesPage_btnDashboard->setVisible(admin);
    ui->sallesPage_btnEmployes->setVisible(admin);
    ui->sallesPage_btnEvaluateurs->setVisible(admin);
    ui->sallesPage_btnParticipants->setVisible(admin);
    ui->sallesPage_btnSponsors->setVisible(admin);
    ui->sallesPage_btnProjets->setVisible(admin);
    ui->sallesPage_btnNotifications->setVisible(admin);
    ui->sallesPage_btnProfil->setVisible(admin);
    m_rechercheEmp.clear();
    ui->lineEditRechercheEmp->clear();
    m_triEmp = "IDEMPLOYE";
    m_triCroissant = true;
    ui->lineEditMotDePasse->clear();

    remplirTableEmployes();
    dessinerStatistiques();
    goEmployes();
}

void integration::onDeconnexion()
{
    const auto rep = QMessageBox::question(this, "Déconnexion", "Voulez-vous vraiment vous déconnecter ?", QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::Yes) {
        ui->lineEditIdentifiant->clear(); ui->lineEditMotDePasse->clear();
        delete m_modelEmp; m_modelEmp = nullptr;      // plus de données en mémoire après déconnexion
        ui->tableEmployes->setRowCount(0);
        reinitialiserFormulaireEmploye();
        m_idConnecte.clear();
        m_roleConnecte.clear();
        m_rechercheEmp.clear();
        ui->lineEditRechercheEmp->clear();
        dessinerStatistiques();                       // vide les graphiques
        goLogin();
    }
}

void integration::onNotifications()
{
    const QVector<Employe> emps = employesComplets();
    int inactifs = 0;
    for (const auto &e : emps) if (e.getStatut() == "Inactif") inactifs++;

    const QString rappel = inactifs > 0
                               ? QString("%1 employé(s) inactif(s) : vérifiez leur statut.").arg(inactifs)
                               : QString("Aucun employé inactif.");

    afficherDialogue(this, "Notifications", QString(R"(<div style='color:#E2E8F0;font-family:Segoe UI, Arial;font-size:13px;'><p style='color:#818CF8;font-weight:800;'>Effectif</p><p style='color:#94A3B8;font-size:12px;'>%1 employé(s) enregistré(s).</p><hr/><p style='color:#FBBF24;font-weight:800;'>Rappel</p><p style='color:#94A3B8;font-size:12px;'>%2</p></div>)").arg(emps.size()).arg(rappel));
}

void integration::onProfil()
{
    Employe moi;
    if (!Employe::trouver(m_idConnecte, moi)) {
        QMessageBox::warning(this, "Profil", "Profil introuvable.");
        return;
    }
    const QString initiales = (moi.getPrenom().left(1) + moi.getNom().left(1)).toUpper().toHtmlEscaped();
    const QString couleur   = moi.getStatut() == "Actif" ? "#10B981" : "#EF4444";

    afficherDialogue(this, "Profil utilisateur", QString(R"(<div style='color:#E2E8F0;text-align:center;font-family:Segoe UI, Arial;'><h1 style='color:#818CF8;'>%1</h1><h2 style='color:#FFFFFF;'>%2</h2><p style='color:#94A3B8;'><b>Identifiant :</b> %3</p><p style='color:#94A3B8;'><b>Rôle :</b> %4</p><p style='color:#94A3B8;'><b>Statut :</b> <span style='color:%5;'>%6</span></p><hr/><p style='color:#64748B;font-size:11px;'>HACKNOVA — Smart Hackathon Management</p></div>)")
                                                     .arg(initiales,
                                                          (moi.getPrenom() + " " + moi.getNom()).toHtmlEscaped(),
                                                          moi.getId().toHtmlEscaped(),
                                                          moi.getRole().toHtmlEscaped(),
                                                          couleur,
                                                          moi.getStatut().toHtmlEscaped()));
}

// ======================================================================
// === MODULE EMPLOYE ====================================================
// ======================================================================

void integration::connecterCRUDEmployes()
{
    connect(ui->btnAjouterEmploye,    &QPushButton::clicked, this, &integration::onAjouterEmploye);
    connect(ui->btnAnnulerEmploye,    &QPushButton::clicked, this, &integration::onAnnulerEmploye);
    connect(ui->btnRechercherEmploye, &QPushButton::clicked, this, &integration::onRechercherEmploye);
    connect(ui->btnTrierEmploye,      &QPushButton::clicked, this, &integration::onTrierEmploye);
    connect(ui->btnExporterEmploye,   &QPushButton::clicked, this, &integration::onExporterEmploye);

    // Recherche avec la touche Entrée, tri par clic sur l'en-tête d'une colonne
    connect(ui->lineEditRechercheEmp, &QLineEdit::returnPressed, this, &integration::onRechercherEmploye);
    connect(ui->lineEditRechercheEmp, &QLineEdit::textChanged, this, [this](const QString &text) { m_rechercheEmp = text.trimmed(); remplirTableEmployes(); });
    connect(ui->comboTriEmploye, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
        switch (index) {
        case 1: m_triEmp = "NOM"; m_triCroissant = true; break;
        case 2: m_triEmp = "NOM"; m_triCroissant = false; break;
        case 3: m_triEmp = "PRENOM"; m_triCroissant = true; break;
        case 4: m_triEmp = "PRENOM"; m_triCroissant = false; break;
        case 5: m_triEmp = "IDEMPLOYE"; m_triCroissant = true; break;
        case 6: m_triEmp = "IDEMPLOYE"; m_triCroissant = false; break;
        default: return;
        }
        remplirTableEmployes();
    });
    ui->tableEmployes->horizontalHeader()->setSectionsClickable(true);
    connect(ui->tableEmployes->horizontalHeader(), &QHeaderView::sectionClicked, this, &integration::onTriParColonne);
    ui->btnTrierEmploye->setToolTip("Alterne le tri : par identifiant, puis par nom (A → Z). Vous pouvez aussi cliquer sur l'en-tête ID ou Nom.");

    // ---- Contrôle de saisie côté interface (en plus de Employe::verifierSaisie) ----
    static const QRegularExpression reLettres("^[\\p{L} '\\-]{0,50}$");
    ui->lineEditEmpNom->setValidator(new QRegularExpressionValidator(reLettres, this));
    ui->lineEditEmpPrenom->setValidator(new QRegularExpressionValidator(reLettres, this));
    ui->lineEditEmpMdp->setMaxLength(50);
    ui->lineEditEmpID->setReadOnly(true);                                  // l'ID est généré par Employe::prochainId()
    ui->lineEditEmpID->setPlaceholderText("Généré automatiquement");
}

void integration::connecterChatbot()
{
    if (ui->leQuestion)
        connect(ui->leQuestion, &QLineEdit::returnPressed, this, &integration::onEnvoyerQuestion);
    if (ui->btnEnvoyer)
        connect(ui->btnEnvoyer, &QPushButton::clicked, this, &integration::onEnvoyerQuestion);

    if (ui->textChatbot) {
        ui->textChatbot->setHtml(R"(
            <div style='color:#E2E8F0;font-family:Segoe UI, Arial;font-size:13px;'>
            <p><b style='color:#818CF8;'>HACKNOVA Bot :</b>
            Bonjour 👋 Je suis votre assistant. Posez-moi une question
            sur les employés, les rôles, les statuts, etc.</p>
            </div>
        )");
    }
}

void integration::remplirTableEmployes()
{
    delete m_modelEmp;
    m_modelEmp = m_rechercheEmp.isEmpty() ? Etmp.afficher(m_triEmp, m_triCroissant)
                                          : Etmp.rechercher(m_rechercheEmp, m_triEmp, m_triCroissant);
    while (m_modelEmp->canFetchMore()) m_modelEmp->fetchMore();

    auto *t = ui->tableEmployes;
    t->setRowCount(m_modelEmp->rowCount());

    for (int i = 0; i < m_modelEmp->rowCount(); ++i) {
        auto champ = [&](int c) { return m_modelEmp->data(m_modelEmp->index(i, c)).toString(); };
        Employe e(champ(0), champ(1), champ(2), champ(3), champ(4), champ(5));
        ajouterLigneEmploye(i, e);
        t->setRowHidden(i, false);
    }

    t->verticalHeader()->setVisible(false);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setAlternatingRowColors(true);
    t->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    t->verticalScrollBar()->setSingleStep(24);

    int lastCol = t->columnCount() - 1;
    for (int c = 0; c < lastCol; ++c)
        t->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    if (lastCol >= 0) {
        t->horizontalHeader()->setSectionResizeMode(lastCol, QHeaderView::Fixed);
        t->setColumnWidth(lastCol, 260);
    }
    t->verticalHeader()->setDefaultSectionSize(42);

    // Flèche de tri sur la colonne triée
    static const QMap<QString, int> indexColonne = {{"IDEMPLOYE", 0}, {"NOM", 1}, {"PRENOM", 2}};
    t->horizontalHeader()->setSortIndicatorShown(true);
    t->horizontalHeader()->setSortIndicator(indexColonne.value(m_triEmp, 0),
                                            m_triCroissant ? Qt::AscendingOrder : Qt::DescendingOrder);
}

void integration::ajouterLigneEmploye(int row, const Employe &e)
{
    auto *t = ui->tableEmployes;

    t->setItem(row, 0, new QTableWidgetItem(e.getId()));
    t->setItem(row, 1, new QTableWidgetItem(e.getNom()));
    t->setItem(row, 2, new QTableWidgetItem(e.getPrenom()));
    t->setItem(row, 3, new QTableWidgetItem(QString(e.getMdp().size(), QChar(0x2022))));
    t->setItem(row, 4, new QTableWidgetItem(e.getRole()));

    auto *itemStatut = new QTableWidgetItem(e.getStatut());
    itemStatut->setForeground(e.getStatut() == "Actif" ? QColor(16, 185, 129) : QColor(239, 68, 68));
    t->setItem(row, 5, itemStatut);

    QString styleModif = R"(
        QPushButton { background-color:#4338CA; color:#FFFFFF; border:1px solid #6366F1;
            border-radius:6px; font-size:12px; font-weight:800; padding:4px 8px; min-width:65px; min-height:32px; }
        QPushButton:hover { background-color:#6366F1; border-color:#818CF8; }
        QPushButton:pressed { background-color:#3730A3; }
    )";
    QString styleSuppr = R"(
        QPushButton { background-color:#DC2626; color:#FFFFFF; border:1px solid #EF4444;
            border-radius:6px; font-size:12px; font-weight:800; padding:4px 8px; min-width:65px; min-height:32px; }
        QPushButton:hover { background-color:#EF4444; border-color:#F87171; }
        QPushButton:pressed { background-color:#B91C1C; }
        QPushButton:disabled { background-color:#334155; color:#64748B; border:1px solid #475569; }
    )";

    auto *container = new QWidget;
    auto *lay = new QHBoxLayout(container);
    lay->setContentsMargins(4, 2, 4, 2);
    lay->setSpacing(6);

    auto *btnModif = new QPushButton("MODIFIER");
    btnModif->setCursor(Qt::PointingHandCursor);
    btnModif->setFixedSize(120, 32);
    btnModif->setStyleSheet(styleModif);

    auto *btnSuppr = new QPushButton("SUPPRIMER");
    btnSuppr->setCursor(Qt::PointingHandCursor);
    btnSuppr->setFixedSize(120, 32);
    btnSuppr->setStyleSheet(styleSuppr);

    // Droits d'accès : seul l'administrateur peut supprimer un employé
    const bool peutSuppr = Employe::peutSupprimer(m_roleConnecte);
    btnSuppr->setEnabled(peutSuppr);
    if (!peutSuppr) btnSuppr->setToolTip("Réservé à l'administrateur");

    lay->addWidget(btnModif);
    lay->addWidget(btnSuppr);
    lay->addStretch();

    // On retrouve la ligne par l'identifiant (robuste après recherche ou tri)
    const QString empId = e.getId();
    auto trouverLigne = [this, empId]() -> int {
        for (int i = 0; i < ui->tableEmployes->rowCount(); ++i) {
            auto *it = ui->tableEmployes->item(i, 0);
            if (it && it->text() == empId) return i;
        }
        return -1;
    };
    connect(btnModif, &QPushButton::clicked, this, [this, trouverLigne]() {
        const int r = trouverLigne();
        if (r >= 0) onModifierEmploye(r);
    });
    connect(btnSuppr, &QPushButton::clicked, this, [this, trouverLigne]() {
        const int r = trouverLigne();
        if (r >= 0) onSupprimerEmploye(r);
    });

    t->setCellWidget(row, 6, container);
}

void integration::onAjouterEmploye()
{
    const QString nom    = ui->lineEditEmpNom->text().trimmed();
    const QString prenom = ui->lineEditEmpPrenom->text().trimmed();
    const QString mdp    = ui->lineEditEmpMdp->text();
    const QString role   = ui->comboBoxEmpRole->currentText();
    const QString statut = ui->comboBoxEmpStatut->currentText();

    const bool modification = !m_editEmpId.isEmpty();
    const QString id = modification ? m_editEmpId : Employe::prochainId();

    Employe e(id, nom, prenom, mdp, role, statut);

    // Contrôle de saisie (dans la classe Employe)
    const QString erreur = e.verifierSaisie();
    if (!erreur.isEmpty()) {
        QMessageBox::warning(this, "Saisie invalide", erreur);
        return;
    }

    const bool ok = modification ? e.modifier() : e.ajouter();
    if (!ok) {
        QMessageBox::critical(this, "Erreur base de données",
                              modification ? "Impossible de modifier." : "Impossible d'ajouter.");
        return;
    }

    reinitialiserFormulaireEmploye();
    remplirTableEmployes();      // actualisation de l'affichage
    dessinerStatistiques();

    QMessageBox::information(this, modification ? "Modification" : "Ajout",
                             QString("Employé %1 %2.").arg(id, modification ? "modifié" : "ajouté"));
}

void integration::onAnnulerEmploye() { reinitialiserFormulaireEmploye(); }

void integration::onModifierEmploye(int row)
{
    if (!m_modelEmp || row < 0 || row >= ui->tableEmployes->rowCount()) return;
    const QString selectedId = ui->tableEmployes->item(row, 0)->text();
    int modelRow = -1;
    for (int i = 0; i < m_modelEmp->rowCount(); ++i)
        if (m_modelEmp->data(m_modelEmp->index(i, 0)).toString() == selectedId) { modelRow = i; break; }
    if (modelRow < 0) return;
    auto champ = [&](int column) { return m_modelEmp->data(m_modelEmp->index(modelRow, column)).toString(); };
    ui->lineEditEmpID->setText(champ(0));
    ui->lineEditEmpNom->setText(champ(1));
    ui->lineEditEmpPrenom->setText(champ(2));
    ui->lineEditEmpMdp->setText(champ(3));

    int iRole = ui->comboBoxEmpRole->findText(champ(4));
    if (iRole >= 0) ui->comboBoxEmpRole->setCurrentIndex(iRole);

    int iStatut = ui->comboBoxEmpStatut->findText(champ(5));
    if (iStatut >= 0) ui->comboBoxEmpStatut->setCurrentIndex(iStatut);

    m_editEmpId = champ(0);
    ui->btnAjouterEmploye->setText("ENREGISTRER");
    ui->lineEditEmpNom->setFocus();
}

void integration::onSupprimerEmploye(int row)
{
    if (!m_modelEmp || row < 0 || row >= ui->tableEmployes->rowCount()) return;
    const QString idStr = ui->tableEmployes->item(row, 0)->text();
    int modelRow = -1;
    for (int i = 0; i < m_modelEmp->rowCount(); ++i)
        if (m_modelEmp->data(m_modelEmp->index(i, 0)).toString() == idStr) { modelRow = i; break; }
    if (modelRow < 0) return;
    auto champ = [&](int column) { return m_modelEmp->data(m_modelEmp->index(modelRow, column)).toString(); };
    // Droits d'accès (le bouton est déjà désactivé, on revérifie côté code)
    if (!Employe::peutSupprimer(m_roleConnecte)) {
        QMessageBox::warning(this, "Accès refusé", "Cette action est réservée aux rôles autorisés.");
        return;
    }
    if (idStr.trimmed() == m_idConnecte) {
        QMessageBox::warning(this, "Suppression impossible", "Vous ne pouvez pas supprimer votre propre compte.");
        return;
    }

    const auto rep = QMessageBox::question(this, "Supprimer",
                                           QString("Supprimer %1 — %2 %3 ?").arg(idStr, champ(1), champ(2)),
                                           QMessageBox::Yes | QMessageBox::No);
    if (rep != QMessageBox::Yes) return;

    if (Etmp.supprimer(idStr)) {
        if (m_editEmpId == idStr) reinitialiserFormulaireEmploye();

        remplirTableEmployes();   // actualisation de l'affichage
        dessinerStatistiques();
    } else {
        QMessageBox::critical(this, "Erreur base de données", "Impossible de supprimer.");
    }
}

void integration::reinitialiserFormulaireEmploye()
{
    ui->lineEditEmpID->clear(); ui->lineEditEmpNom->clear(); ui->lineEditEmpPrenom->clear(); ui->lineEditEmpMdp->clear();
    ui->comboBoxEmpRole->setCurrentIndex(0); ui->comboBoxEmpStatut->setCurrentIndex(0);
    m_editEmpId.clear();
    ui->btnAjouterEmploye->setText("AJOUTER");
}

// Recherche : la requête est exécutée par Employe::rechercher() (requête préparée), pas dans la vue
void integration::onRechercherEmploye()
{
    m_rechercheEmp = ui->lineEditRechercheEmp->text().trimmed();
    remplirTableEmployes();
}

// Bouton TRIER : alterne entre le tri par identifiant et le tri par nom (ordre alphabétique A -> Z)
void integration::onTrierEmploye()
{
    if (m_triEmp == "NOM") {
        m_triEmp = "IDEMPLOYE";
        ui->btnTrierEmploye->setToolTip("Tri actuel : par identifiant. Cliquez pour trier par nom (A → Z).");
    } else {
        m_triEmp = "NOM";
        ui->btnTrierEmploye->setToolTip("Tri actuel : par nom (A → Z). Cliquez pour trier par identifiant.");
    }
    m_triCroissant = true;
    remplirTableEmployes();
}

// Clic sur l'en-tête "ID" ou "Nom" : trie sur cette colonne, toujours en ordre croissant (A -> Z)
void integration::onTriParColonne(int colonne)
{
    static const QMap<int, QString> colonnes = {{0, "IDEMPLOYE"}, {1, "NOM"}, {2, "PRENOM"}};
    if (!colonnes.contains(colonne)) return;                  // autres colonnes : pas de tri
    m_triEmp = colonnes.value(colonne);
    m_triCroissant = true;
    remplirTableEmployes();
}

// Liste complète des employés pour les statistiques et le chatbot (indépendante de la recherche en cours).
// Vide tant que personne n'est connecté.
QVector<Employe> integration::employesComplets()
{
    if (m_idConnecte.isEmpty()) return {};
    QSqlQueryModel *m = Etmp.afficher();
    while (m->canFetchMore()) m->fetchMore();
    const QVector<Employe> v = lireEmployes(m);
    delete m;
    return v;
}

void integration::dessinerStatistiques()
{
    const QVector<Employe> emps = employesComplets();
    int actifs = 0, inactifs = 0;
    for (const Employe &e : emps) { if (e.getStatut() == "Actif") ++actifs; else if (e.getStatut() == "Inactif") ++inactifs; }
    {
        const int total = actifs + inactifs;
        QPixmap pix(210, 210); pix.fill(Qt::transparent);
        QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        const QRectF pie(5, 35, 108, 108);
        if (total > 0) {
            const double angleActif = 360.0 * actifs / total;
            p.setPen(Qt::NoPen); p.setBrush(QColor(16, 185, 129));
            p.drawPie(pie, 90 * 16, int(-angleActif * 16));
            p.setBrush(QColor(239, 68, 68));
            p.drawPie(pie, int((90 - angleActif) * 16), int(-(360 - angleActif) * 16));
        } else {
            p.setPen(Qt::NoPen); p.setBrush(QColor(51, 65, 85)); p.drawEllipse(pie);
        }

        QFont f = p.font(); f.setFamily("Segoe UI"); f.setPointSize(8); f.setBold(true); p.setFont(f);
        const int actifPct = total ? qRound(100.0 * actifs / total) : 0;
        const int inactifPct = total ? qRound(100.0 * inactifs / total) : 0;
        p.setPen(Qt::NoPen); p.setBrush(QColor(16, 185, 129)); p.drawEllipse(119, 76, 8, 8);
        p.setPen(QColor(226, 232, 240));
        p.drawText(QRect(131, 67, 77, 28), Qt::AlignLeft | Qt::AlignVCenter,
                   QString("Actif %1%").arg(actifPct));
        p.setPen(Qt::NoPen); p.setBrush(QColor(239, 68, 68)); p.drawEllipse(119, 116, 8, 8);
        p.setPen(QColor(226, 232, 240));
        p.drawText(QRect(131, 107, 77, 28), Qt::AlignLeft | Qt::AlignVCenter,
                   QString("Inactif %1%").arg(inactifPct));
        f.setPointSize(8); f.setBold(false); p.setFont(f); p.setPen(QColor(100, 116, 139));
        p.drawText(10, 190, "Répartition par statut");
        p.end(); ui->labelStatutPie->setPixmap(pix);
    }
    {
        QPixmap pix(250, 210); pix.fill(Qt::transparent); QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        QMap<QString, int> roles; for (const auto &e : emps) roles[e.getRole()]++;
        int maxVal = 1; for (int v : roles) if (v > maxVal) maxVal = v;
        auto couleur = [](const QString &r) -> QColor { if (r == "Administrateur") return QColor(129, 140, 248); if (r == "Responsable RH") return QColor(251, 191, 36); return QColor(16, 185, 129); };
        int y = 30; const int barMaxW = 80; const int barH = 20;
        QFont f = p.font(); f.setFamily("Segoe UI"); f.setPointSize(9); f.setBold(true); p.setFont(f);
        for (auto it = std::as_const(roles).cbegin(); it != std::as_const(roles).cend(); ++it) {
            p.setBrush(couleur(it.key())); p.setPen(Qt::NoPen); p.drawEllipse(10, y + 5, 8, 8);
            p.setPen(QColor(226, 232, 240)); p.drawText(25, y + 13, it.key());
            p.setPen(Qt::NoPen); p.setBrush(QColor(30, 41, 59)); p.drawRoundedRect(130, y, barMaxW, barH, 4, 4);
            int w = int(barMaxW * (double)it.value() / maxVal); p.setBrush(couleur(it.key())); p.drawRoundedRect(130, y, w, barH, 4, 4);
            p.setPen(QColor(255, 255, 255)); p.drawText(130 + w + 8, y + 14, QString::number(it.value()));
            y += barH + 25;
        }
        f.setPointSize(8); f.setBold(false); p.setFont(f); p.setPen(QColor(100, 116, 139)); p.drawText(10, 195, "Nombre d'employés par rôle");
        p.end(); ui->labelRoleBar->setPixmap(pix);
    }
}

void integration::onExporterEmploye()
{
    // Les données viennent d'Oracle (classe Employe), comme l'affichage, les statistiques et le chatbot :
    // même requête que le tableau (recherche et tri en cours). Pour exporter TOUS les employés quelle que
    // soit la recherche, remplacer par : Etmp.afficher(m_triEmp, m_triCroissant)
    QSqlQueryModel *m = m_rechercheEmp.isEmpty() ? Etmp.afficher(m_triEmp, m_triCroissant)
                                                 : Etmp.rechercher(m_rechercheEmp, m_triEmp, m_triCroissant);
    while (m->canFetchMore()) m->fetchMore();

    // Colonnes exportées : ID, Nom, Prénom, Rôle, Statut (le mot de passe n'est volontairement pas exporté)
    const QList<int> colonnes = {0, 1, 2, 4, 5};
    QStringList entetes;
    for (int c : colonnes)
        entetes << m->headerData(c, Qt::Horizontal).toString();

    QVector<QStringList> lignes;
    for (int r = 0; r < m->rowCount(); ++r) {
        QStringList l;
        for (int c : colonnes)
            l << m->data(m->index(r, c)).toString().trimmed();
        lignes.append(l);
    }
    delete m;

    exporterDonnees(this, entetes, lignes, "employes", "Liste des employés");
}

void integration::onEnvoyerQuestion()
{
    QString q = ui->leQuestion->text().trimmed(); if (q.isEmpty()) return;
    QString reponse; QString ql = q.toLower();
    const QVector<Employe> emps = employesComplets();
    if (m_idConnecte.isEmpty()) reponse = "Veuillez vous connecter pour interroger les données.";
    else if (ql.contains("bonjour") || ql.contains("salut") || ql.contains("hello")) reponse = "Bonjour 👋 Comment puis-je vous aider ?";
    else if (ql.contains("employ") && (ql.contains("cherche") || ql.contains("trouve") || QRegularExpression("\\d+").match(q).hasMatch())) {
        const QRegularExpressionMatch idMatch = QRegularExpression("\\d+").match(q);
        const QString needle = idMatch.hasMatch() ? idMatch.captured(0) : QString();
        QStringList found;
        for (const Employe &e : emps) {
            const bool match = needle.isEmpty()
            ? (ql.contains(e.getNom().toLower()) || ql.contains(e.getPrenom().toLower()))
            : e.getId().contains(needle, Qt::CaseInsensitive);
            if (match) found << QString("%1 %2 — %3, %4 (%5)")
                             .arg(e.getPrenom().toHtmlEscaped(), e.getNom().toHtmlEscaped(),
                                  e.getId().toHtmlEscaped(), e.getRole().toHtmlEscaped(),
                                  e.getStatut().toHtmlEscaped());
        }
        reponse = found.isEmpty() ? "Aucun employé correspondant dans la base." : found.join("<br>");
    }
    else if (ql.contains("gestion") || ql.contains("gérer") || ql.contains("gerer")) {
        if (ql.contains("salle")) {
            reponse = "Pour gérer les salles, ouvrez la page <b>Salles</b>. Vous pouvez ajouter une salle, sélectionner une ligne pour la modifier ou la supprimer, rechercher par nom et trier la liste.";
        } else if (ql.contains("employ") || ql.contains("personnel")) {
            reponse = "Pour gérer les employés, ouvrez la page <b>Employés</b> : utilisez <b>Ajouter</b> pour créer une fiche, <b>Modifier</b> ou <b>Supprimer</b> dans la ligne concernée. La recherche filtre pendant la saisie et la liste de tri propose le nom, le prénom et l'ID. Le Responsable RH gère les employés ; l'Administrateur gère toutes les pages.";
        } else if (ql.contains("rôle") || ql.contains("role") || ql.contains("admin") || ql.contains("responsable") || ql.contains("utilisateur")) {
            reponse = "L'<b>Administrateur</b> peut gérer toutes les pages et les comptes. Le <b>Responsable RH</b> peut gérer les employés. Les comptes se créent depuis le formulaire de la page Employés.";
        } else {
            reponse = "Je peux vous aider à gérer les <b>employés</b> (ajout, modification, suppression, recherche et tri), les <b>salles</b> ou les <b>rôles</b>. Précisez ce que vous souhaitez gérer.";
        }
    }    else if (ql.contains("combien") && ql.contains("employ")) reponse = QString("Il y a actuellement <b>%1 employés</b> enregistrés.").arg(emps.size());
    else if (ql.contains("actif")) { int n = 0; for (const auto &e : emps) if (e.getStatut() == "Actif") n++; reponse = QString("<b>%1 employés</b> sont actifs.").arg(n); }
    else if (ql.contains("inactif")) { int n = 0; for (const auto &e : emps) if (e.getStatut() == "Inactif") n++; reponse = QString("<b>%1 employés</b> sont inactifs.").arg(n); }
    else if (ql.contains("admin")) { int n = 0; for (const auto &e : emps) if (e.getRole() == "Administrateur") n++; reponse = QString("Il y a <b>%1 administrateurs</b>.").arg(n); }
    else if (ql.contains("rh") || ql.contains("responsable")) { int n = 0; for (const auto &e : emps) if (e.getRole() == "Responsable RH") n++; reponse = QString("Il y a <b>%1 responsables RH</b>.").arg(n); }
    else if (ql.contains("rôle") || ql.contains("role")) {
        QMap<QString,int> roles; for (const auto &e : emps) roles[e.getRole()]++;
        QString liste;
        for (auto it = roles.cbegin(); it != roles.cend(); ++it) {
            liste += QString("<li>%1 : <b>%2</b></li>").arg(it.key()).arg(it.value());
        }
        reponse = "Répartition par rôle :<ul>" + liste + "</ul>";
    }
    else if (ql.contains("statistique") || ql.contains("graphique")) reponse = "Consultez les <b>statistiques</b> à droite : camembert statuts + barres rôles.";
    else if (ql.contains("merci")) reponse = "Avec plaisir 😊";
    else if (ql.contains("aide") || ql.contains("help")) reponse = "Je peux vous renseigner sur : <ul><li>le nombre d'employés</li><li>les actifs / inactifs</li><li>les rôles</li><li>les statistiques</li></ul>";
    else reponse = "Je peux répondre sur la gestion des employés, des salles et des rôles. Essayez par exemple : <b>gestion des employés</b> ou <b>gestion des salles</b>.";

    QString html = ui->textChatbot->toHtml();
    html += QString(R"(<div style='color:#E2E8F0;font-family:Segoe UI, Arial;font-size:13px;margin-top:8px;'><p><b style='color:#10B981;'>Vous :</b> %1</p><p><b style='color:#818CF8;'>Bot :</b> %2</p></div>)").arg(q.toHtmlEscaped(), reponse);
    ui->textChatbot->setHtml(html);
    ui->textChatbot->verticalScrollBar()->setValue(ui->textChatbot->verticalScrollBar()->maximum());
    ui->leQuestion->clear();
}

// ======================================================================
// === MODULE SALLE ======================================================
// ======================================================================

void integration::connecterCRUDSalles()
{
    connect(ui->btnAjouterSalle,    &QPushButton::clicked, this, &integration::onAjouterSalle);
    connect(ui->btnAnnulerSalle,    &QPushButton::clicked, this, &integration::onAnnulerSalle);
    connect(ui->btnRechercherSalle, &QPushButton::clicked, this, &integration::onRechercherSalle);
    connect(ui->btnTrierSalle,      &QPushButton::clicked, this, &integration::onTrierSalle);
    connect(ui->btnExporterSalle,   &QPushButton::clicked, this, &integration::onExporterSalle);
}

void integration::connecterActions()
{
    if (ui->btnSuggererSalle)
        connect(ui->btnSuggererSalle, &QPushButton::clicked, this, &integration::onSuggererSalle);
    if (ui->btnValiderQRSalle)
        connect(ui->btnValiderQRSalle, &QPushButton::clicked, this, &integration::onValiderQR);
}

void integration::chargerSallesDepuisBDD()
{
    m_salles.clear();
    QSqlQuery query;

    if (query.exec("SELECT id_salle, nom, capacite, type, disponibilite FROM salle")) {
        while (query.next()) {
            Salle s;
            s.id = query.value(0).toInt();
            s.nom = query.value(1).toString();
            s.capacite = query.value(2).toInt();
            s.type = query.value(3).toString();
            s.dispo = query.value(4).toString();

            m_salles.append(s);

            if (s.id >= m_nextSalleId) {
                m_nextSalleId = s.id + 1;
            }
        }
    } else {
        qDebug() << "Erreur chargement salles :" << query.lastError().text();
    }
}

void integration::remplirTableSalles()
{
    auto *t = ui->tableSalles;
    t->setRowCount(m_salles.size());
    for (int i = 0; i < m_salles.size(); ++i) ajouterLigneSalle(i, m_salles[i]);

    t->verticalHeader()->setVisible(false);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setAlternatingRowColors(true);
    t->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    t->verticalScrollBar()->setSingleStep(24);

    int lastCol = t->columnCount() - 1;
    for (int c = 0; c < lastCol; ++c) t->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    if (lastCol >= 0) { t->horizontalHeader()->setSectionResizeMode(lastCol, QHeaderView::Fixed); t->setColumnWidth(lastCol, 190); }
    t->verticalHeader()->setDefaultSectionSize(42);
}

void integration::ajouterLigneSalle(int row, const Salle &s)
{
    auto *t = ui->tableSalles;
    t->setItem(row, 0, new QTableWidgetItem(QString("SAL-%1").arg(s.id, 3, 10, QChar('0'))));
    t->setItem(row, 1, new QTableWidgetItem(s.nom));
    t->setItem(row, 2, new QTableWidgetItem(QString::number(s.capacite)));
    t->setItem(row, 3, new QTableWidgetItem(s.type));

    auto *itemDispo = new QTableWidgetItem(s.dispo);
    if (s.dispo == "Disponible")   itemDispo->setForeground(QColor(16, 185, 129));
    else if (s.dispo == "Occupée") itemDispo->setForeground(QColor(251, 191, 36));
    else                           itemDispo->setForeground(QColor(239, 68, 68));
    t->setItem(row, 4, itemDispo);

    QString styleModif = R"(QPushButton { background-color:#4338CA; color:#FFFFFF; border:1px solid #6366F1; border-radius:6px; font-size:11px; font-weight:700; padding:4px 8px; min-width:65px; min-height:26px; } QPushButton:hover { background-color:#6366F1; border-color:#818CF8; } QPushButton:pressed { background-color:#3730A3; })";
    QString styleSuppr = R"(QPushButton { background-color:#DC2626; color:#FFFFFF; border:1px solid #EF4444; border-radius:6px; font-size:11px; font-weight:700; padding:4px 8px; min-width:65px; min-height:26px; } QPushButton:hover { background-color:#EF4444; border-color:#F87171; } QPushButton:pressed { background-color:#B91C1C; })";

    auto *container = new QWidget;
    auto *lay = new QHBoxLayout(container);
    lay->setContentsMargins(4, 2, 4, 2); lay->setSpacing(6);

    auto *btnModif = new QPushButton("MODIFIER"); btnModif->setCursor(Qt::PointingHandCursor); btnModif->setStyleSheet(styleModif);
    auto *btnSuppr = new QPushButton("SUPPRIMER"); btnSuppr->setCursor(Qt::PointingHandCursor); btnSuppr->setStyleSheet(styleSuppr);

    lay->addWidget(btnModif); lay->addWidget(btnSuppr); lay->addStretch();

    const int salleId = s.id;
    connect(btnModif, &QPushButton::clicked, this, [this, salleId]() {
        for (int i = 0; i < m_salles.size(); ++i) if (m_salles[i].id == salleId) { onModifierSalle(i); return; }
    });
    connect(btnSuppr, &QPushButton::clicked, this, [this, salleId]() {
        for (int i = 0; i < m_salles.size(); ++i) if (m_salles[i].id == salleId) { onSupprimerSalle(i); return; }
    });

    t->setCellWidget(row, 5, container);
}

void integration::onAjouterSalle()
{
    const QString nom   = ui->lineEditSalleNom->text().trimmed();
    const int     cap   = ui->spinBoxSalleCapacite->value();
    const QString type  = ui->comboBoxSalleType->currentText();
    const QString dispo = ui->comboBoxSalleDispo->currentText();

    if (nom.isEmpty()) { QMessageBox::warning(this, "Ajout salle", "Veuillez saisir un nom de salle."); return; }

    if (m_editSalleRow >= 0) {
        Salle &s = m_salles[m_editSalleRow];
        s.nom = nom; s.capacite = cap; s.type = type; s.dispo = dispo;
        QMessageBox::information(this, "Modification", QString("Salle SAL-%1 modifiée.").arg(s.id, 3, 10, QChar('0')));
    } else {
        Salle s;
        s.id = m_nextSalleId++;
        s.nom = nom; s.capacite = cap; s.type = type; s.dispo = dispo;
        m_salles.append(s);
        QMessageBox::information(this, "Ajout", QString("Salle SAL-%1 ajoutée.").arg(s.id, 3, 10, QChar('0')));
    }
    reinitialiserFormulaireSalle(); remplirTableSalles(); dessinerStatistiquesSalles();
}

void integration::onAnnulerSalle() { reinitialiserFormulaireSalle(); }

void integration::onModifierSalle(int row)
{
    if (row < 0 || row >= m_salles.size()) return;
    const Salle &s = m_salles[row];
    ui->lineEditSalleID->setText(QString("SAL-%1").arg(s.id, 3, 10, QChar('0')));
    ui->lineEditSalleNom->setText(s.nom);
    ui->spinBoxSalleCapacite->setValue(s.capacite);
    int iType = ui->comboBoxSalleType->findText(s.type); if (iType >= 0) ui->comboBoxSalleType->setCurrentIndex(iType);
    int iDispo = ui->comboBoxSalleDispo->findText(s.dispo); if (iDispo >= 0) ui->comboBoxSalleDispo->setCurrentIndex(iDispo);
    m_editSalleRow = row;
    ui->btnAjouterSalle->setText("ENREGISTRER");
    ui->lineEditSalleNom->setFocus();
}

void integration::onSupprimerSalle(int row)
{
    if (row < 0 || row >= m_salles.size()) return;
    const Salle &s = m_salles[row];
    const auto rep = QMessageBox::question(this, "Supprimer", QString("Supprimer SAL-%1 — %2 ?").arg(s.id, 3, 10, QChar('0')).arg(s.nom), QMessageBox::Yes | QMessageBox::No);
    if (rep != QMessageBox::Yes) return;

    m_salles.remove(row);
    if (m_editSalleRow == row)      reinitialiserFormulaireSalle();
    else if (m_editSalleRow > row)  m_editSalleRow--;

    remplirTableSalles(); dessinerStatistiquesSalles();
}

void integration::reinitialiserFormulaireSalle()
{
    ui->lineEditSalleID->clear(); ui->lineEditSalleNom->clear(); ui->spinBoxSalleCapacite->setValue(0);
    ui->comboBoxSalleType->setCurrentIndex(0); ui->comboBoxSalleDispo->setCurrentIndex(0);
    m_editSalleRow = -1;
    ui->btnAjouterSalle->setText("AJOUTER");
}

void integration::onRechercherSalle()
{
    const QString key = ui->lineEditRechercheSalle->text().trimmed().toLower();
    if (key.isEmpty()) { remplirTableSalles(); return; }
    for (int i = 0; i < ui->tableSalles->rowCount(); ++i) {
        bool match = false;
        for (int c = 0; c < ui->tableSalles->columnCount(); ++c) {
            auto *it = ui->tableSalles->item(i, c);
            if (it && it->text().toLower().contains(key)) { match = true; break; }
        }
        ui->tableSalles->setRowHidden(i, !match);
    }
}

void integration::onTrierSalle()
{
    std::sort(m_salles.begin(), m_salles.end(), [](const Salle &a, const Salle &b) { return a.nom.localeAwareCompare(b.nom) < 0; });
    remplirTableSalles(); dessinerStatistiquesSalles();
}

void integration::dessinerStatistiquesSalles()
{
    {
        QPixmap pix(190, 190); pix.fill(Qt::transparent); QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        int dispo = 0, occ = 0, maint = 0;
        for (const auto &s : std::as_const(m_salles)) { if (s.dispo == "Disponible") dispo++; else if (s.dispo == "Occupée") occ++; else maint++; }
        int total = dispo + occ + maint; if (total == 0) total = 1;
        QRectF rect(10, 15, 110, 110); double startAngle = 90.0;
        auto drawSlice = [&](int val, const QColor &color) {
            if (val <= 0) return;
            double sweep = -360.0 * val / total;
            p.setBrush(color); p.setPen(Qt::NoPen); p.drawPie(rect, int(startAngle * 16), int(sweep * 16)); startAngle += sweep;
        };
        drawSlice(dispo, QColor(16, 185, 129)); drawSlice(occ, QColor(251, 191, 36)); drawSlice(maint, QColor(239, 68, 68));
        QFont f = p.font(); f.setFamily("Segoe UI"); f.setPointSize(8); f.setBold(true); p.setFont(f);
        int legY = 25; p.setBrush(QColor(16, 185, 129)); p.setPen(Qt::NoPen); p.drawEllipse(135, legY, 8, 8);
        p.setPen(QColor(226, 232, 240)); p.drawText(148, legY + 8, QString("Dispo (%1)").arg(dispo)); legY += 25;
        p.setBrush(QColor(251, 191, 36)); p.setPen(Qt::NoPen); p.drawEllipse(135, legY, 8, 8);
        p.setPen(QColor(226, 232, 240)); p.drawText(148, legY + 8, QString("Occupée (%1)").arg(occ)); legY += 25;
        p.setBrush(QColor(239, 68, 68)); p.setPen(Qt::NoPen); p.drawEllipse(135, legY, 8, 8);
        p.setPen(QColor(226, 232, 240)); p.drawText(148, legY + 8, QString("Maint. (%1)").arg(maint));
        f.setBold(false); f.setPointSize(8); p.setFont(f); p.setPen(QColor(100, 116, 139)); p.drawText(10, 175, "Répartition par disponibilité");
        p.end(); ui->sallesPage_labelStatutPie->setPixmap(pix);
    }
    {
        QPixmap pix(230, 190); pix.fill(Qt::transparent); QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        QMap<QString, int> types; for (const auto &s : std::as_const(m_salles)) types[s.type]++;
        int maxVal = 1; for (int v : types) if (v > maxVal) maxVal = v;
        auto couleur = [](const QString &t) -> QColor { if (t == "Salle informatique") return QColor(129, 140, 248); if (t == "Salle de réunion") return QColor(251, 191, 36); if (t == "Salle conférence") return QColor(16, 185, 129); return QColor(239, 68, 68); };
        int y = 20; const int barMaxW = 60; const int barH = 18;
        QFont f = p.font(); f.setFamily("Segoe UI"); f.setPointSize(8); f.setBold(true); p.setFont(f);
        for (auto it = std::as_const(types).cbegin(); it != std::as_const(types).cend(); ++it) {
            p.setBrush(couleur(it.key())); p.setPen(Qt::NoPen); p.drawEllipse(10, y + 4, 8, 8);
            p.setPen(QColor(226, 232, 240)); p.drawText(25, y + 12, it.key());
            p.setPen(Qt::NoPen); p.setBrush(QColor(30, 41, 59)); p.drawRoundedRect(130, y, barMaxW, barH, 4, 4);
            int w = int(barMaxW * (double)it.value() / maxVal); p.setBrush(couleur(it.key())); p.drawRoundedRect(130, y, w, barH, 4, 4);
            p.setPen(QColor(255, 255, 255)); p.drawText(130 + w + 6, y + 13, QString::number(it.value()));
            y += barH + 20;
        }
        f.setBold(false); f.setPointSize(8); p.setFont(f); p.setPen(QColor(100, 116, 139)); p.drawText(10, 175, "Nombre de salles par type");
        p.end(); ui->sallesPage_labelRoleBar->setPixmap(pix);
    }
}

void integration::onSuggererSalle()
{
    QString effStr = ui->lineEditEffectifSalle->text().trimmed(); bool ok = false; int effectif = effStr.toInt(&ok);
    if (!ok || effectif <= 0) { QMessageBox::warning(this, "Affectation", "Veuillez saisir un effectif valide (nombre entier > 0)."); return; }
    QString suggestion; bool trouve = false;
    for (const auto &s : std::as_const(m_salles)) {
        if (s.dispo == "Disponible" && s.capacite >= effectif) {
            suggestion = QString("<b>%1</b> (cap. %2) — type : %3").arg(s.nom).arg(s.capacite).arg(s.type); trouve = true; break;
        }
    }
    if (trouve) QMessageBox::information(this, "Affectation intelligente", "Salle recommandée pour un effectif de " + QString::number(effectif) + " :<br><br>" + suggestion);
    else QMessageBox::warning(this, "Affectation intelligente", "Aucune salle disponible ne peut accueillir " + QString::number(effectif) + " personnes.");
}

void integration::onValiderQR()
{
    QString code = ui->lineEditCodeQRSalle->text().trimmed();
    if (code.isEmpty()) { QMessageBox::warning(this, "QR Code", "Veuillez saisir ou scanner un code."); return; }
    QMessageBox::information(this, "QR Code · Accès", QString("Code <b>%1</b> validé.<br>Accès autorisé.").arg(code.toHtmlEscaped()));
    ui->lineEditCodeQRSalle->clear();
}

void integration::onExporterSalle()
{
    exporterTable(this, ui->tableSalles, {0, 1, 2, 3, 4}, "salles", "Liste des salles");
}


void integration::initialiserGestionEvaluateurs()
{
    m_modelEvaluateurs = new QStandardItemModel(this);
    m_modelEvaluateurs->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Statut", "Projet", "Action"});
    ui->eval_tableEvaluateurs->setModel(m_modelEvaluateurs);
    ui->eval_tableEvaluateurs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->eval_tableEvaluateurs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->eval_tableEvaluateurs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->eval_tableEvaluateurs->setAlternatingRowColors(true);
    ui->eval_tableEvaluateurs->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->eval_tableEvaluateurs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->eval_tableEvaluateurs->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->eval_tableEvaluateurs->setColumnWidth(5, 260);
    ui->eval_tableEvaluateurs->verticalHeader()->setVisible(false);
    ui->eval_tableEvaluateurs->verticalHeader()->setDefaultSectionSize(42);
    ui->eval_tableEvaluateurs->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);       // défile vers le haut / le bas
    ui->eval_tableEvaluateurs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->eval_tableEvaluateurs->verticalScrollBar()->setSingleStep(24);

    // Carte statistiques : mise en page identique à « Statistiques des employés » (indépendante de l'ancien .ui)
    // Dimensions des cadres : colonne de droite alignée (x = 931, largeur 481), bas aligné sur le tableau
    ui->eval_cardFormEvaluateurs->setGeometry(10, 160, 911, 161);
    ui->eval_comboStatut->setGeometry(710, 60, 190, 32);
    ui->eval_cardTableEvaluateurs->setGeometry(10, 380, 911, 441);
    ui->eval_tableEvaluateurs->setGeometry(15, 40, 881, 391);
    ui->eval_cardStatsEvaluateurs->setGeometry(931, 160, 481, 231);
    ui->eval_cardTechChallenge->setGeometry(931, 401, 481, 205);
    ui->eval_techChallengeTitle->setGeometry(0, 8, 481, 28);
    ui->eval_techChallengeTitle->setAlignment(Qt::AlignCenter);
    ui->eval_techChallengeDescription->setGeometry(20, 40, 441, 78);
    ui->eval_frameSaisieTechChallenge->setGeometry(20, 135, 441, 55);
    ui->lineEditChallengeAnalyst_4->setGeometry(10, 10, 300, 35);
    ui->btnChallengeAnalyst_4->setGeometry(320, 10, 110, 35);
    ui->eval_cardDeliberation->setGeometry(931, 616, 481, 205);
    ui->eval_deliberationTitle->setGeometry(0, 8, 481, 28);
    ui->eval_deliberationTitle->setAlignment(Qt::AlignCenter);
    ui->eval_deliberationDescription->setGeometry(20, 40, 441, 78);
    ui->eval_frameSaisieDeliberation->setGeometry(20, 135, 441, 55);
    ui->lineEditDeliberationJury_3->setGeometry(10, 10, 300, 35);
    ui->btnSoumettreDeliberation_3->setGeometry(320, 10, 110, 35);

    ui->eval_labelStatsTitle->setGeometry(15, 10, 400, 20);
    ui->eval_labelStatsTitle->setText(QString::fromUtf8("\xF0\x9F\x93\x8A Statistiques des \xC3\xA9valuateurs"));
    ui->eval_statsChartHost->setGeometry(5, 35, 210, 191);          // camembert
    m_labelProjetBar = new QLabel(ui->eval_cardStatsEvaluateurs);   // barres par projet
    m_labelProjetBar->setObjectName("eval_projetBar");
    m_labelProjetBar->setGeometry(220, 35, 250, 191);
    for (const char *nom : {"eval_lblTotal", "eval_lblActifs", "eval_lblInactifs", "eval_lblRepartition"})
        if (auto *l = ui->eval_cardStatsEvaluateurs->findChild<QLabel*>(nom)) l->hide();   // anciens libellés (ancien .ui)

    ui->eval_comboStatut->clear();
    ui->eval_comboStatut->addItems({"Actif", "Inactif"});
    ui->eval_inputId->setText("E007");
    const QStringList ids = {"E001", "E002", "E003", "E004", "E005", "E006"};
    const QStringList noms = {"Ben Salah", "Trabelsi", "Gharbi", "Ayari", "Jaziri", "Chaabane"};
    const QStringList prenoms = {"Amine", "Sara", "Yassine", "Hiba", "Malek", "Omar"};
    const QStringList statuts = {"Actif", "Actif", "Inactif", "Actif", "Actif", "Inactif"};
    const QStringList projets = {"Smart Campus", "Cloud Platform", "Green City", "Smart Campus", "FinTech Junior", "Cloud Platform"};
    for (int i = 0; i < ids.size(); ++i) {
        QList<QStandardItem*> row;
        row << new QStandardItem(ids[i]) << new QStandardItem(noms[i])
            << new QStandardItem(prenoms[i]) << new QStandardItem(statuts[i])
            << new QStandardItem(projets[i]) << new QStandardItem("");
        m_modelEvaluateurs->appendRow(row);
    }
    reconstruireBoutonsAction();
    connect(ui->eval_btnAjouter, &QPushButton::clicked, this, &integration::ajouterEvaluateur);
    connect(ui->eval_btnAnnuler, &QPushButton::clicked, this, &integration::annulerFormulaire);
    connect(ui->eval_btnRechercher, &QPushButton::clicked, this, &integration::rechercherEvaluateur);
    connect(ui->eval_btnTrier, &QPushButton::clicked, this, &integration::trierEvaluateurs);
    connect(ui->eval_btnExporter, &QPushButton::clicked, this, &integration::exporterEvaluateurs);
    connect(ui->eval_tableEvaluateurs->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, [this](const QModelIndex &, const QModelIndex &) { selectionnerLigne(); });
    connect(ui->btnChallengeAnalyst_4, &QPushButton::clicked, this, &integration::lancerTechChallenge);
    connect(ui->btnSoumettreDeliberation_3, &QPushButton::clicked, this, &integration::lancerDeliberation);
    mettreAJourStatistiques();
}
void integration::reconstruireBoutonsAction()
{
    // Mêmes couleurs que les boutons MODIFIER / SUPPRIMER de la gestion des employés
    static const QString styleModif = R"(
        QPushButton { background-color:#4338CA; color:#FFFFFF; border:1px solid #6366F1;
            border-radius:6px; font-size:12px; font-weight:800; padding:0 8px; }
        QPushButton:hover { background-color:#6366F1; border-color:#818CF8; }
        QPushButton:pressed { background-color:#3730A3; }
    )";
    static const QString styleSuppr = R"(
        QPushButton { background-color:#DC2626; color:#FFFFFF; border:1px solid #EF4444;
            border-radius:6px; font-size:12px; font-weight:800; padding:0 8px; }
        QPushButton:hover { background-color:#EF4444; border-color:#F87171; }
        QPushButton:pressed { background-color:#B91C1C; }
    )";

    for (int row = 0; row < m_modelEvaluateurs->rowCount(); ++row) {
        // Statut coloré comme dans la liste des employés (vert = Actif, rouge = Inactif)
        auto *itemStatut = m_modelEvaluateurs->item(row, 3);
        itemStatut->setForeground(itemStatut->text() == "Actif" ? QColor(16, 185, 129) : QColor(239, 68, 68));

        QWidget *container = new QWidget(ui->eval_tableEvaluateurs);
        QHBoxLayout *layout = new QHBoxLayout(container);
        layout->setContentsMargins(4, 2, 4, 2);
        layout->setSpacing(6);
        QPushButton *modifier = new QPushButton("MODIFIER", container);
        QPushButton *supprimer = new QPushButton("SUPPRIMER", container);
        modifier->setCursor(Qt::PointingHandCursor);
        modifier->setFixedSize(120, 32);
        modifier->setStyleSheet(styleModif);
        supprimer->setCursor(Qt::PointingHandCursor);
        supprimer->setFixedSize(120, 32);
        supprimer->setStyleSheet(styleSuppr);
        layout->addWidget(modifier);
        layout->addWidget(supprimer);
        layout->addStretch();
        QPersistentModelIndex pIndex(m_modelEvaluateurs->index(row, 0));
        ui->eval_tableEvaluateurs->setIndexWidget(m_modelEvaluateurs->index(row, 5), container);
        connect(modifier, &QPushButton::clicked, this, [this, pIndex]() {
            if (!pIndex.isValid()) return;
            m_ligneEnEditionEval = pIndex.row();
            ui->eval_tableEvaluateurs->selectRow(m_ligneEnEditionEval);
            ui->eval_inputId->setText(m_modelEvaluateurs->item(m_ligneEnEditionEval, 0)->text());
            ui->eval_inputNom->setText(m_modelEvaluateurs->item(m_ligneEnEditionEval, 1)->text());
            ui->eval_inputPrenom->setText(m_modelEvaluateurs->item(m_ligneEnEditionEval, 2)->text());
            ui->eval_comboStatut->setCurrentText(m_modelEvaluateurs->item(m_ligneEnEditionEval, 3)->text());
            ui->eval_btnAjouter->setText("Enregistrer");
        });
        connect(supprimer, &QPushButton::clicked, this, [this, pIndex]() {
            if (!pIndex.isValid()) return;
            if (QMessageBox::question(this, "Confirmer la suppression",
                                      "Supprimer cet évaluateur ?") != QMessageBox::Yes) return;
            m_modelEvaluateurs->removeRow(pIndex.row());
            annulerFormulaire();
            mettreAJourStatistiques();
            reconstruireBoutonsAction();
        });
    }
}

void integration::afficherMessage(const QString &titre, const QString &message)
{
    QMessageBox::information(this, titre, message);
}

bool integration::formulaireValide() const
{
    if (ui->eval_inputId->text().trimmed().isEmpty() ||
        ui->eval_inputNom->text().trimmed().isEmpty() ||
        ui->eval_inputPrenom->text().trimmed().isEmpty()) {
        QMessageBox::warning(const_cast<integration*>(this), "Champs obligatoires",
                             "Veuillez saisir l'ID, le nom et le prénom de l'évaluateur.");
        return false;
    }
    return true;
}

void integration::ajouterEvaluateur()
{
    if (!formulaireValide()) return;
    const QString id = ui->eval_inputId->text().trimmed();
    if (m_ligneEnEditionEval >= 0 && m_ligneEnEditionEval < m_modelEvaluateurs->rowCount()) {
        for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
            if (r != m_ligneEnEditionEval && m_modelEvaluateurs->item(r, 0)->text().compare(id, Qt::CaseInsensitive) == 0) {
                QMessageBox::warning(this, "ID existant", "Un autre évaluateur utilise déjà cet ID.");
                return;
            }
        }
        m_modelEvaluateurs->item(m_ligneEnEditionEval, 0)->setText(id);
        m_modelEvaluateurs->item(m_ligneEnEditionEval, 1)->setText(ui->eval_inputNom->text().trimmed());
        m_modelEvaluateurs->item(m_ligneEnEditionEval, 2)->setText(ui->eval_inputPrenom->text().trimmed());
        m_modelEvaluateurs->item(m_ligneEnEditionEval, 3)->setText(ui->eval_comboStatut->currentText());
    } else {
        for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
            if (m_modelEvaluateurs->item(r, 0)->text().compare(id, Qt::CaseInsensitive) == 0) {
                QMessageBox::warning(this, "ID existant", "Cet ID évaluateur existe déjà.");
                return;
            }
        }
        QList<QStandardItem*> row;
        row << new QStandardItem(id) << new QStandardItem(ui->eval_inputNom->text().trimmed())
            << new QStandardItem(ui->eval_inputPrenom->text().trimmed())
            << new QStandardItem(ui->eval_comboStatut->currentText()) << new QStandardItem("À affecter") << new QStandardItem("");
        m_modelEvaluateurs->appendRow(row);
    }
    reconstruireBoutonsAction();
    annulerFormulaire();
    mettreAJourStatistiques();
}

void integration::selectionnerLigne()
{
    QModelIndex index = ui->eval_tableEvaluateurs->currentIndex();
    if (!index.isValid()) return;
    int r = index.row();
    ui->eval_inputId->setText(m_modelEvaluateurs->item(r, 0)->text());
    ui->eval_inputNom->setText(m_modelEvaluateurs->item(r, 1)->text());
    ui->eval_inputPrenom->setText(m_modelEvaluateurs->item(r, 2)->text());
    ui->eval_comboStatut->setCurrentText(m_modelEvaluateurs->item(r, 3)->text());
    m_ligneEnEditionEval = r;
}

void integration::modifierEvaluateur()
{
    ajouterEvaluateur();
}

void integration::supprimerEvaluateur()
{
    int r = ui->eval_tableEvaluateurs->currentIndex().row();
    if (r < 0) {
        QMessageBox::information(this, "Sélection", "Sélectionnez un évaluateur à supprimer.");
        return;
    }
    if (QMessageBox::question(this, "Confirmer la suppression", "Supprimer l'évaluateur sélectionné ?") == QMessageBox::Yes) {
        m_modelEvaluateurs->removeRow(r);
        reconstruireBoutonsAction();
        annulerFormulaire();
        mettreAJourStatistiques();
    }
}

void integration::annulerFormulaire()
{
    ui->eval_inputNom->clear();
    ui->eval_inputPrenom->clear();
    ui->eval_comboStatut->setCurrentIndex(0);
    ui->eval_tableEvaluateurs->clearSelection();
    m_ligneEnEditionEval = -1;
    ui->eval_btnAjouter->setText("Ajouter");
    int maxId = 0;
    for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
        QString digits = m_modelEvaluateurs->item(r, 0)->text();
        digits.remove(QRegularExpression("[^0-9]"));
        maxId = qMax(maxId, digits.toInt());
    }
    ui->eval_inputId->setText(QString("E%1").arg(maxId + 1, 3, 10, QChar('0')));
}

void integration::rechercherEvaluateur()
{
    QString q = ui->eval_inputRecherche->text().trimmed();
    bool found = false;
    for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
        bool match = q.isEmpty();
        for (int c = 0; c < 4; ++c)
            if (m_modelEvaluateurs->item(r, c)->text().contains(q, Qt::CaseInsensitive)) match = true;
        ui->eval_tableEvaluateurs->setRowHidden(r, !match);
        if (match && !found && !q.isEmpty()) {
            ui->eval_tableEvaluateurs->selectRow(r);
            found = true;
        }
    }
    if (!q.isEmpty() && !found) QMessageBox::information(this, "Recherche", "Aucun évaluateur trouvé.");
}

void integration::trierEvaluateurs()
{
    static bool ascending = true;
    m_modelEvaluateurs->sort(1, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    ascending = !ascending;
    reconstruireBoutonsAction();
}

void integration::exporterEvaluateurs()
{
    QString path = QFileDialog::getSaveFileName(this, "Exporter les évaluateurs", "evaluateurs.csv", "Fichier CSV (*.csv)");
    if (path.isEmpty()) return;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Export impossible", "Impossible de créer le fichier.");
        return;
    }
    QTextStream out(&file);
    out << "ID évaluateur;Nom;Prénom;Statut\n";
    for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r)
        out << m_modelEvaluateurs->item(r,0)->text() << ';' << m_modelEvaluateurs->item(r,1)->text() << ';'
            << m_modelEvaluateurs->item(r,2)->text() << ';' << m_modelEvaluateurs->item(r,3)->text() << '\n';
    file.close();
    afficherMessage("Export terminé", "La liste a été exportée au format CSV.");
}

// Statistiques des évaluateurs : même présentation que « Statistiques des employés »
// (camembert Actif / Inactif + diagramme en barres, dessinés dans des QLabel).
void integration::mettreAJourStatistiques()
{
    int actifs = 0, inactifs = 0;
    QMap<QString, int> projets;
    for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
        if (m_modelEvaluateurs->item(r, 3)->text() == "Actif") ++actifs; else ++inactifs;
        const QString projet = m_modelEvaluateurs->item(r, 4)->text().trimmed();
        projets[projet.isEmpty() ? QString("Non affecté") : projet]++;
    }

    {   // Camembert : répartition par statut
        const int total = actifs + inactifs;
        QPixmap pix(210, 210); pix.fill(Qt::transparent);
        QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        const QRectF pie(5, 35, 108, 108);
        if (total > 0) {
            const double angleActif = 360.0 * actifs / total;
            p.setPen(Qt::NoPen); p.setBrush(QColor(16, 185, 129));
            p.drawPie(pie, 90 * 16, int(-angleActif * 16));
            p.setBrush(QColor(239, 68, 68));
            p.drawPie(pie, int((90 - angleActif) * 16), int(-(360 - angleActif) * 16));
        } else {
            p.setPen(Qt::NoPen); p.setBrush(QColor(51, 65, 85)); p.drawEllipse(pie);
        }

        QFont f = p.font(); f.setFamily("Segoe UI"); f.setPointSize(8); f.setBold(true); p.setFont(f);
        const int actifPct = total ? qRound(100.0 * actifs / total) : 0;
        const int inactifPct = total ? qRound(100.0 * inactifs / total) : 0;
        p.setPen(Qt::NoPen); p.setBrush(QColor(16, 185, 129)); p.drawEllipse(119, 76, 8, 8);
        p.setPen(QColor(226, 232, 240));
        p.drawText(QRect(131, 67, 77, 28), Qt::AlignLeft | Qt::AlignVCenter, QString("Actif %1%").arg(actifPct));
        p.setPen(Qt::NoPen); p.setBrush(QColor(239, 68, 68)); p.drawEllipse(119, 116, 8, 8);
        p.setPen(QColor(226, 232, 240));
        p.drawText(QRect(131, 107, 77, 28), Qt::AlignLeft | Qt::AlignVCenter, QString("Inactif %1%").arg(inactifPct));
        f.setPointSize(8); f.setBold(false); p.setFont(f); p.setPen(QColor(100, 116, 139));
        p.drawText(10, 190, "Répartition par statut");
        p.end(); ui->eval_statsChartHost->setPixmap(pix);
    }
    {   // Barres : nombre d'évaluateurs par projet
        QPixmap pix(250, 210); pix.fill(Qt::transparent);
        QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        static const QColor palette[] = { QColor(129, 140, 248), QColor(251, 191, 36), QColor(16, 185, 129),
                                         QColor(56, 189, 248), QColor(244, 114, 182), QColor(167, 139, 250) };
        int maxVal = 1; for (int v : projets) if (v > maxVal) maxVal = v;
        const int n = projets.size();
        const int step = n > 0 ? qMin(45, 150 / n) : 45;     // les barres se resserrent s'il y a beaucoup de projets
        const int barH = qMax(8, qMin(20, step - 6));
        const int barMaxW = 80;
        QFont f = p.font(); f.setFamily("Segoe UI"); f.setPointSize(9); f.setBold(true); p.setFont(f);
        const QFontMetrics fm(f);
        int y = 30, i = 0;
        for (auto it = std::as_const(projets).cbegin(); it != std::as_const(projets).cend(); ++it, ++i) {
            const QColor couleur = palette[i % 6];
            p.setPen(Qt::NoPen); p.setBrush(couleur); p.drawEllipse(10, y + (barH - 8) / 2, 8, 8);
            p.setPen(QColor(226, 232, 240));
            p.drawText(QRect(25, y, 100, barH), Qt::AlignLeft | Qt::AlignVCenter, fm.elidedText(it.key(), Qt::ElideRight, 100));
            p.setPen(Qt::NoPen); p.setBrush(QColor(30, 41, 59)); p.drawRoundedRect(130, y, barMaxW, barH, 4, 4);
            const int w = int(barMaxW * (double)it.value() / maxVal);
            p.setBrush(couleur); p.drawRoundedRect(130, y, w, barH, 4, 4);
            p.setPen(QColor(255, 255, 255));
            p.drawText(QRect(130 + w + 8, y, 30, barH), Qt::AlignLeft | Qt::AlignVCenter, QString::number(it.value()));
            y += step;
        }
        f.setPointSize(8); f.setBold(false); p.setFont(f); p.setPen(QColor(100, 116, 139));
        p.drawText(10, 195, "Nombre d'évaluateurs par projet");
        p.end(); if (m_labelProjetBar) m_labelProjetBar->setPixmap(pix);
    }
}

// Métier 1 : le jury saisit les notes par critère. Le score n'est jamais automatique
// à partir d'informations inexistantes : il est calculé explicitement avec le bouton.
// Métier 1 : Tech Challenge Analyst — analyse technique structurée d'un projet.
void integration::lancerTechChallenge()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Métier 1 — Tech Challenge Analyst | Analyse technique");
    dialog.resize(980, 700);
    dialog.setMinimumSize(820, 620);
    dialog.setStyleSheet(R"(
QDialog{background:#080C14;color:#E2E8F0;font-family:'Segoe UI',Arial;font-size:13px;}
QLabel{color:#E2E8F0;} QLabel#titreMetier{color:#fff;font-size:21px;font-weight:900;} QLabel#sousTitreMetier{color:#94A3B8;}
QGroupBox{background:#111827;border:1px solid #1E293B;border-radius:10px;margin-top:12px;padding:12px;font-weight:700;color:#fff;}
QGroupBox::title{subcontrol-origin:margin;left:12px;padding:0 5px;color:#A5B4FC;}
QLineEdit,QComboBox,QPlainTextEdit,QDoubleSpinBox{background:#0B1120;color:#F1F5F9;border:1px solid #334155;border-radius:6px;padding:7px;}
QPushButton{background:#4338CA;color:#fff;border:0;border-radius:6px;padding:8px 14px;font-weight:800;}
QPushButton:hover{background:#6366F1;} QTableWidget{background:#0B1120;color:#E2E8F0;gridline-color:#1E293B;}
    )");

    auto *root = new QVBoxLayout(&dialog);
    root->setContentsMargins(22, 18, 22, 18);
    root->setSpacing(12);
    auto *title = new QLabel("Tech Challenge Analyst — Analyse technique des projets");
    title->setObjectName("titreMetier");
    root->addWidget(title);
    auto *subtitle = new QLabel("Évaluez les choix techniques, repérez les risques et produisez une recommandation explicable.");
    subtitle->setObjectName("sousTitreMetier");
    subtitle->setWordWrap(true);
    root->addWidget(subtitle);

    auto *projectBox = new QGroupBox("Projet analysé");
    auto *projectForm = new QFormLayout(projectBox);
    auto *project = new QComboBox;
    project->addItems({"Smart Campus", "Green City", "Health AI", "FinTech Junior", "Cloud Platform", "Autre projet"});
    auto *stack = new QLineEdit;
    stack->setPlaceholderText("Langages, frameworks, base de données, infrastructure…");
    projectForm->addRow("Nom du projet :", project);
    projectForm->addRow("Technologies :", stack);
    root->addWidget(projectBox);

    auto *criteriaBox = new QGroupBox("Évaluation technique (notes sur 20)");
    auto *criteria = new QFormLayout(criteriaBox);
    auto makeScore = [&dialog]() {
        auto *spin = new QDoubleSpinBox(&dialog);
        spin->setRange(0, 20);
        spin->setDecimals(1);
        spin->setSingleStep(0.5);
        spin->setValue(10);
        return spin;
    };
    auto *architecture = makeScore();
    auto *security = makeScore();
    auto *quality = makeScore();
    auto *scalability = makeScore();
    auto *feasibility = makeScore();
    criteria->addRow("Architecture et cohérence (25 %) :", architecture);
    criteria->addRow("Sécurité et protection des données (25 %) :", security);
    criteria->addRow("Qualité technique et tests (20 %) :", quality);
    criteria->addRow("Performance et évolutivité (15 %) :", scalability);
    criteria->addRow("Faisabilité et maturité du prototype (15 %) :", feasibility);
    root->addWidget(criteriaBox);

    auto *notesBox = new QGroupBox("Risques, preuves et observations du jury");
    auto *notesLayout = new QVBoxLayout(notesBox);
    auto *notes = new QPlainTextEdit;
    notes->setPlaceholderText("Ex. tests manquants, dépendance critique, risque de sécurité, preuve de faisabilité…");
    notes->setMinimumHeight(85);
    notesLayout->addWidget(notes);
    root->addWidget(notesBox, 1);

    auto *result = new QLabel("Saisissez les notes, puis calculez l'analyse.");
    result->setWordWrap(true);
    result->setStyleSheet("background:#111827;border:1px solid #312E81;border-radius:8px;padding:12px;font-weight:700;");
    root->addWidget(result);
    auto *buttons = new QHBoxLayout;
    auto *calculate = new QPushButton("Calculer l'analyse");
    auto *exportButton = new QPushButton("Exporter le rapport CSV");
    auto *close = new QPushButton("Fermer");
    buttons->addWidget(calculate);
    buttons->addWidget(exportButton);
    buttons->addStretch();
    buttons->addWidget(close);
    root->addLayout(buttons);

    QString report;
    QObject::connect(calculate, &QPushButton::clicked, &dialog, [&]() {
        const double score = architecture->value() * .25 + security->value() * .25
                             + quality->value() * .20 + scalability->value() * .15
                             + feasibility->value() * .15;
        QString avis = score >= 15 ? "Solide — prêt pour le challenge"
                       : score >= 12 ? "Prometteur — corrections ciblées requises"
                       : score >= 9  ? "Prototype à renforcer avant le challenge"
                                     : "Risque technique élevé — révision nécessaire";
        QStringList alertes;
        if (security->value() < 8) alertes << "sécurité";
        if (architecture->value() < 8) alertes << "architecture";
        if (quality->value() < 8) alertes << "qualité/tests";
        const QString risques = alertes.isEmpty() ? "Aucun seuil critique détecté" : "Points critiques : " + alertes.join(", ");
        result->setText(QString("Score technique pondéré : %1 / 20\nAvis : %2\n%3")
                            .arg(score, 0, 'f', 2).arg(avis, risques));
        report = QString("Projet;Technologies;Architecture/20;Sécurité/20;Qualité/20;Évolutivité/20;Faisabilité/20;Score pondéré/20;Avis;Risques et observations\n%1;%2;%3;%4;%5;%6;%7;%8;%9;%10\n")
                     .arg(project->currentText(), stack->text()).arg(architecture->value()).arg(security->value())
                     .arg(quality->value()).arg(scalability->value()).arg(feasibility->value())
                     .arg(score, 0, 'f', 2).arg(avis, risques + ". " + notes->toPlainText());
    });
    QObject::connect(exportButton, &QPushButton::clicked, &dialog, [&]() {
        if (report.isEmpty()) { QMessageBox::information(&dialog, "Rapport", "Calculez d'abord l'analyse technique."); return; }
        const QString path = QFileDialog::getSaveFileName(&dialog, "Exporter le rapport technique", "analyse_technique_projet.csv", "Fichier CSV (*.csv)");
        if (path.isEmpty()) return;
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { QMessageBox::warning(&dialog, "Export", "Impossible de créer le fichier."); return; }
        QTextStream out(&file); out.setEncoding(QStringConverter::Utf8); out << report;
        QMessageBox::information(&dialog, "Export", "Le rapport technique a été exporté.");
    });
    QObject::connect(close, &QPushButton::clicked, &dialog, &QDialog::accept);
    dialog.exec();
}

// Métier 2 : les membres du jury notent séparément, puis comparent leurs avis.// Un projet sélectionné -> un seul évaluateur actif dont la spécialité correspond.
void integration::lancerDeliberation()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Métier 2 — Délibération collaborative du jury");
    dialog.resize(1080, 720);
    dialog.setMinimumSize(900, 620);
    dialog.setStyleSheet(R"(
QDialog{background:#080C14;color:#E2E8F0;font-family:'Segoe UI',Arial;font-size:13px;}
QLabel{color:#E2E8F0;} QLabel#titreDeliberation{color:#fff;font-size:21px;font-weight:900;} QLabel#sousTitreDeliberation{color:#94A3B8;}
QGroupBox{background:#111827;border:1px solid #1E293B;border-radius:10px;margin-top:12px;padding:12px;font-weight:700;color:#fff;}
QGroupBox::title{subcontrol-origin:margin;left:12px;padding:0 5px;color:#A5B4FC;}
QComboBox,QLineEdit{background:#0B1120;color:#F1F5F9;border:1px solid #334155;border-radius:6px;padding:7px;}
QPushButton{background:#4338CA;color:#fff;border:0;border-radius:6px;padding:8px 14px;font-weight:800;} QPushButton:hover{background:#6366F1;}
QTableWidget{background:#0B1120;alternate-background-color:#111827;color:#E2E8F0;gridline-color:#1E293B;selection-background-color:#312E81;}
QHeaderView::section{background:#111827;color:#A5B4FC;padding:8px;border:0;font-weight:800;}
QDoubleSpinBox{background:#0B1120;color:#F1F5F9;border:1px solid #334155;border-radius:5px;padding:4px;}
    )");
    auto *root = new QVBoxLayout(&dialog);
    root->setContentsMargins(22, 18, 22, 18);
    root->setSpacing(12);
    auto *title = new QLabel("Délibération collaborative du jury");
    title->setObjectName("titreDeliberation");
    root->addWidget(title);
    auto *subtitle = new QLabel("Chaque juré note indépendamment. L'application calcule la moyenne pondérée et signale les écarts avant la décision finale.");
    subtitle->setObjectName("sousTitreDeliberation");
    subtitle->setWordWrap(true);
    root->addWidget(subtitle);

    auto *projectBox = new QGroupBox("Projet présenté");
    auto *projectLayout = new QFormLayout(projectBox);
    auto *project = new QComboBox;
    project->addItems({"Smart Campus", "Green City", "Health AI", "FinTech Junior", "Cloud Platform", "Autre projet"});
    projectLayout->addRow("Projet :", project);
    root->addWidget(projectBox);

    auto *juryBox = new QGroupBox("Notes individuelles du jury — sur 20");
    auto *juryLayout = new QVBoxLayout(juryBox);
    auto *table = new QTableWidget(3, 7, juryBox);
    table->setHorizontalHeaderLabels({"Juré", "Technique", "Innovation", "Faisabilité", "Impact", "Commentaire", "Score pondéré"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setAlternatingRowColors(true);
    table->setMinimumHeight(220);

    QStringList evaluateursActifs;
    for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
        if (m_modelEvaluateurs->item(r, 3)->text().compare("Actif", Qt::CaseInsensitive) == 0)
            evaluateursActifs << m_modelEvaluateurs->item(r, 1)->text() + " " + m_modelEvaluateurs->item(r, 2)->text();
    }
    if (evaluateursActifs.size() < 2) {
        QMessageBox::warning(this, "Jury incomplet", "Il faut au moins deux évaluateurs actifs pour lancer une délibération collaborative.");
        return;
    }
    for (int r = 0; r < 3; ++r) {
        auto *juror = new QComboBox(table);
        juror->addItem("Choisir un juré");
        juror->addItems(evaluateursActifs);
        if (r < evaluateursActifs.size()) juror->setCurrentIndex(r + 1);
        table->setCellWidget(r, 0, juror);
        for (int c = 1; c <= 4; ++c) {
            auto *note = new QDoubleSpinBox(table);
            note->setRange(0, 20);
            note->setDecimals(1);
            note->setSingleStep(.5);
            note->setValue(10);
            table->setCellWidget(r, c, note);
        }
        auto *comment = new QLineEdit(table);
        comment->setPlaceholderText("Argument principal / réserve");
        table->setCellWidget(r, 5, comment);
        table->setItem(r, 6, new QTableWidgetItem("À calculer"));
    }
    juryLayout->addWidget(table);
    root->addWidget(juryBox, 1);

    auto *decision = new QLabel("Pondération : technique 40 % · innovation 25 % · faisabilité 20 % · impact 15 %.");
    decision->setWordWrap(true);
    decision->setStyleSheet("background:#111827;border:1px solid #312E81;border-radius:8px;padding:12px;font-weight:700;");
    root->addWidget(decision);
    auto *buttons = new QHBoxLayout;
    auto *calculate = new QPushButton("Calculer le consensus");
    auto *exportButton = new QPushButton("Exporter la délibération CSV");
    auto *close = new QPushButton("Fermer");
    buttons->addWidget(calculate);
    buttons->addWidget(exportButton);
    buttons->addStretch();
    buttons->addWidget(close);
    root->addLayout(buttons);

    QString report;
    QObject::connect(calculate, &QPushButton::clicked, &dialog, [&]() {
        QSet<QString> jurors;
        QVector<double> scores;
        QStringList lines;
        for (int r = 0; r < table->rowCount(); ++r) {
            auto *juror = qobject_cast<QComboBox*>(table->cellWidget(r, 0));
            if (!juror || juror->currentIndex() <= 0) continue;
            const QString name = juror->currentText();
            if (jurors.contains(name)) { QMessageBox::warning(&dialog, "Juré répété", "Chaque ligne doit correspondre à un juré différent."); return; }
            jurors.insert(name);
            const double tech = qobject_cast<QDoubleSpinBox*>(table->cellWidget(r, 1))->value();
            const double innovation = qobject_cast<QDoubleSpinBox*>(table->cellWidget(r, 2))->value();
            const double feasibility = qobject_cast<QDoubleSpinBox*>(table->cellWidget(r, 3))->value();
            const double impact = qobject_cast<QDoubleSpinBox*>(table->cellWidget(r, 4))->value();
            const double score = tech * .40 + innovation * .25 + feasibility * .20 + impact * .15;
            scores << score;
            table->item(r, 6)->setText(QString::number(score, 'f', 2));
            auto *comment = qobject_cast<QLineEdit*>(table->cellWidget(r, 5));
            auto csv = [](QString value) { value.replace("\"", "\"\""); return "\"" + value + "\""; };
            lines << QString("%1;%2;%3;%4;%5;%6;%7")
                         .arg(csv(project->currentText()), csv(name)).arg(tech).arg(innovation).arg(feasibility).arg(impact)
                         .arg(csv(comment ? comment->text() : QString()));
        }
        if (scores.size() < 2) { QMessageBox::information(&dialog, "Délibération", "Sélectionnez au moins deux jurés différents."); return; }
        double total = 0, minimum = scores.first(), maximum = scores.first();
        for (double score : scores) { total += score; minimum = qMin(minimum, score); maximum = qMax(maximum, score); }
        const double average = total / scores.size();
        const double spread = maximum - minimum;
        const QString consensus = spread <= 2.0 ? "Consensus fort" : spread <= 4.0 ? "Consensus modéré" : "Divergence : discussion complémentaire requise";
        const QString avis = average >= 14 ? "Avis favorable" : average >= 11 ? "Avis favorable avec réserves" : "Avis défavorable / projet à revoir";
        decision->setText(QString("Projet : %1\nMoyenne du jury : %2 / 20\nÉcart entre les notes : %3 points — %4\nDécision proposée : %5")
                              .arg(project->currentText()).arg(average, 0, 'f', 2).arg(spread, 0, 'f', 1).arg(consensus, avis));
        report = "Projet;Jure;Technique/20;Innovation/20;Faisabilite/20;Impact/20;Score pondere/20;Commentaire\n" + lines.join("\n")
                 + QString("\n\nMoyenne du jury;%1/20\nConsensus;%2\nDecision proposee;%3\n").arg(average, 0, 'f', 2).arg(consensus, avis);
    });
    QObject::connect(exportButton, &QPushButton::clicked, &dialog, [&]() {
        if (report.isEmpty()) { QMessageBox::information(&dialog, "Délibération", "Calculez le consensus avant l'export."); return; }
        const QString path = QFileDialog::getSaveFileName(&dialog, "Exporter la délibération", "deliberation_jury.csv", "Fichier CSV (*.csv)");
        if (path.isEmpty()) return;
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { QMessageBox::warning(&dialog, "Export", "Impossible de créer le fichier."); return; }
        QTextStream out(&file); out.setEncoding(QStringConverter::Utf8); out << report;
        QMessageBox::information(&dialog, "Export", "La délibération a été exportée.");
    });
    QObject::connect(close, &QPushButton::clicked, &dialog, &QDialog::accept);
    dialog.exec();
}