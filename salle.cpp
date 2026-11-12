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
#include <cmath>

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
#include <QListWidget>
#include <QListWidgetItem>
#include <QApplication>
#include <QStyle>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QPointer>

// ---- Nayuki QR Code generator ----
#include "qrcodegen.hpp"

// ---- ZXing-C++ (Scan d'image) ----
#include "ReadBarcode.h"
#include "ReaderOptions.h"
#include "BarcodeFormat.h"

/* ============================================================
 *  HELPERS — Oracle + utilitaires
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

QColor couleurDisponibilite(const QString &dispo)
{
    return dispo.compare("Disponible", Qt::CaseInsensitive) == 0
               ? QColor("#10B981")
               : QColor("#EF4444");
}

/* Palette centralisée */
namespace Palette {
const QString fond       = "#080C14";
const QString carte      = "#111827";
const QString carteAlt   = "#0B1120";
const QString bordure    = "#1E293B";
const QString texte      = "#E2E8F0";
const QString texteMuted = "#94A3B8";
const QString texteDim   = "#64748B";
const QString accent     = "#6366F1";
const QString accentDark = "#4338CA";
const QString succes     = "#10B981";
const QString succesDark = "#059669";
const QString danger     = "#EF4444";
const QString dangerDark = "#B91C1C";
const QString warning    = "#FBBF24";
}

/* Parse un nom "A-1-05" en composants */
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

} // namespace

/* ============================================================
 *  STYLES HELPERS STATIQUES
 * ============================================================ */
QString salle::styleBouton(const QString &couleur, const QString &hover,
                           const QString &texte)
{
    return QString(
               "QPushButton { background-color:%1; %2 border:none; border-radius:6px;"
               " font-weight:800; font-size:11px; padding:0 14px; min-height:32px; }"
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
    return QString("background-color:%1; color:#F1F5F9; border:1px solid #334155;"
                   "border-radius:6px; padding:0 10px; min-height:32px;")
        .arg(Palette::carteAlt);
}

QString salle::styleTitreSection()
{
    return QString("color:%1; font-weight:800; font-size:13px;").arg(Palette::texte);
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

    appliquerTheme();
    connecterLogin();
    connecterNavigation();
    connecterChatbot();
    connecterActions();

    remplirTableSalles();
    dessinerStatistiquesSalles();
    remplirTableEmployes();
    dessinerStatistiques();
}

salle::~salle()
{
    if (m_debounceRechercheSalle) {
        m_debounceRechercheSalle->stop();
        // QObject parent = this → supprimé automatiquement
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
 *  EMPLOYÉS — remplissage
 * ============================================================ */
void salle::remplirTableEmployes()
{
    auto *t = ui->tableEmployes;
    t->clearContents();
    t->setRowCount(0);
    t->verticalHeader()->setVisible(false);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setAlternatingRowColors(true);

    int lastCol = t->columnCount() - 1;
    for (int c = 0; c < lastCol; ++c)
        t->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    if (lastCol >= 0) {
        t->horizontalHeader()->setSectionResizeMode(lastCol, QHeaderView::Fixed);
        t->setColumnWidth(lastCol, 190);
    }
    t->verticalHeader()->setDefaultSectionSize(42);
}

void salle::dessinerStatistiques()
{
    {
        QPixmap pix(210, 210);
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);

        p.setBrush(QColor(Palette::bordure));
        p.setPen(Qt::NoPen);
        p.drawPie(QRectF(10, 20, 130, 130), 0, 360 * 16);

        QFont f = p.font();
        f.setFamily("Segoe UI");
        f.setPointSize(9);
        f.setBold(true);
        p.setFont(f);

        p.setPen(QColor(Palette::texteMuted));
        p.drawText(155, 48, "Actif (0)");
        p.drawText(155, 83, "Inactif (0)");

        f.setPointSize(8);
        f.setBold(false);
        p.setFont(f);
        p.setPen(QColor(Palette::texteDim));
        p.drawText(10, 195, "Répartition par statut");
        p.end();
        ui->labelStatutPie->setPixmap(pix);
    }

    {
        QPixmap pix(250, 210);
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);

        QFont f = p.font();
        f.setFamily("Segoe UI");
        f.setPointSize(9);
        f.setBold(true);
        p.setFont(f);
        p.setPen(QColor(Palette::texteDim));
        p.drawText(10, 100, "Aucun employé enregistré");

        f.setPointSize(8);
        f.setBold(false);
        p.setFont(f);
        p.drawText(10, 195, "Nombre d'employés par rôle");
        p.end();
        ui->labelRoleBar->setPixmap(pix);
    }
}

/* ============================================================
 *  CONNEXIONS DES ACTIONS
 * ============================================================ */
void salle::connecterActions()
{
    if (ui->btnSuggerer_2)
        QObject::connect(ui->btnSuggerer_2, &QPushButton::clicked,
                         this, &salle::onSuggererSalle);
    if (ui->btnValiderQR_4)
        QObject::connect(ui->btnValiderQR_4, &QPushButton::clicked,
                         this, &salle::onValiderQR);

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

    if (ui->leEffectif_2)
        QObject::connect(ui->leEffectif_2, &QLineEdit::returnPressed,
                         this, &salle::onSuggererSalle);
    if (ui->leCodeQR_4)
        QObject::connect(ui->leCodeQR_4, &QLineEdit::returnPressed,
                         this, &salle::onValiderQR);

    if (ui->btnScannerCamera_4)
        QObject::connect(ui->btnScannerCamera_4, &QPushButton::clicked,
                         this, &salle::ouvrirScannerImage);

    /* ============================================================
     *  RECHERCHE SALLE — bouton + Entrée + DYNAMIQUE (live)
     * ============================================================ */
    if (ui->lineEdit_2) {
        // 1) Entrée → recherche immédiate (comportement d'origine)
        QObject::connect(ui->lineEdit_2, &QLineEdit::returnPressed,
                         this, &salle::onRechercherSalle);

        // 2) Recherche dynamique avec debounce 250 ms
        if (!m_debounceRechercheSalle) {
            m_debounceRechercheSalle = new QTimer(this);
            m_debounceRechercheSalle->setSingleShot(true);
            m_debounceRechercheSalle->setInterval(250);
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
    case 0: if (ui->spinBoxSalleCapacite)     ui->spinBoxSalleCapacite->setFocus();     break;
    case 1: if (ui->lineEditSalleTypeAutre)   ui->lineEditSalleTypeAutre->setFocus();   break;
    case 2: if (ui->spinBoxSalleNumero)       ui->spinBoxSalleNumero->setFocus();       break;
    case 3: if (ui->spinBoxSalleEtage)        ui->spinBoxSalleEtage->setFocus();        break;
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
 *  CREATE — Ajouter une salle
 * ============================================================ */
void salle::onAjouterSalle()
{
    if (!ui->comboBoxSalleBloc || !ui->spinBoxSalleEtage ||
        !ui->spinBoxSalleNumero || !ui->spinBoxSalleCapacite) return;

    Salle s;
    s.bloc = ui->comboBoxSalleBloc->currentText();
    s.etage = ui->spinBoxSalleEtage->value();
    s.numeroSalle = ui->spinBoxSalleNumero->value();
    s.capacite = ui->spinBoxSalleCapacite->value();
    s.disponibilite = normaliserDisponibilite(ui->comboBoxSalleDispo->currentText());

    QString typeBase = ui->comboBoxSalleType->currentText();
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
    q.bindValue(":nom",   s.nom,            QSql::In);
    q.bindValue(":cap",   s.capacite,       QSql::In);
    q.bindValue(":type",  s.type,           QSql::In);
    q.bindValue(":dispo", s.disponibilite,  QSql::In);

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

    QMessageBox::information(this, "Ajouter une salle",
                             QString("Salle %1 ajoutée avec succès !").arg(s.nom));
    viderFormulaireSalle();
    rafraichirSallesEtStats();
}

/* ============================================================
 *  UPDATE — Modifier une salle
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
    dlg.setMinimumWidth(440);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(12);

    auto *titre = new QLabel(QString("<h2 style='color:%1;margin:0;'>%2</h2>")
                                 .arg(Palette::accent, s.nom.toHtmlEscaped()));
    lay->addWidget(titre);

    auto *form = new QFormLayout;
    form->setSpacing(10);

    auto *spCap = new QSpinBox(&dlg);
    spCap->setRange(1, 9999);
    spCap->setValue(s.capacite);
    spCap->setStyleSheet(styleChamp());

    auto *cbType = new QComboBox(&dlg);
    cbType->addItems(typesSalleDisponibles());
    int idx = cbType->findText(s.type);
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

    form->addRow("Capacité :",       spCap);
    form->addRow("Type :",           cbType);
    form->addRow("Précisez :",       edAutre);
    form->addRow("Disponibilité :",  cbDispo);
    lay->addLayout(form);

    auto *btns = new QHBoxLayout;
    btns->addStretch();
    auto *btnAnnuler = new QPushButton("Annuler", &dlg);
    btnAnnuler->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
    auto *btnValider = new QPushButton("Enregistrer", &dlg);
    btnValider->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    btns->addWidget(btnAnnuler);
    btns->addWidget(btnValider);
    lay->addLayout(btns);

    QObject::connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);
    QObject::connect(btnValider, &QPushButton::clicked, [&]() {
        QString finalType = cbType->currentText();
        if (finalType == "Autre" && !edAutre->text().isEmpty())
            finalType = edAutre->text();

        QSqlDatabase db2 = dbHacknova();
        if (!db2.transaction()) return;

        QSqlQuery u(db2);
        u.prepare("UPDATE SALLE SET CAPACITE = :cap, TYPE_SALLE = :type, "
                  "DISPONIBILITE = :dispo WHERE ID_SALLE = :id");
        u.bindValue(":cap",   spCap->value());
        u.bindValue(":type",  finalType);
        u.bindValue(":dispo", cbDispo->currentText());
        u.bindValue(":id",    QString::number(idSalle));

        if (!u.exec()) {
            db2.rollback();
            QMessageBox::warning(&dlg, "Erreur", u.lastError().text());
            return;
        }
        db2.commit();
        dlg.accept();
        rafraichirSallesEtStats();
        QMessageBox::information(this, "Succès", "Salle modifiée.");
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
    QMessageBox::information(this, "Supprimer une salle", "Salle supprimée.");
    rafraichirSallesEtStats();
}

/* ============================================================
 *  READ — Consulter une salle
 * ============================================================ */
void salle::ouvrirConsultationSalle(qint64 idSalle)
{
    const auto opt = chargerSalle(idSalle);
    if (!opt.has_value()) return;
    const Salle &s = *opt;
    const PayloadQR payload = construirePayloadQR(s);

    QDialog dlg(this);
    dlg.setWindowTitle(QString("Salle — %1").arg(s.nom));
    dlg.setMinimumSize(620, 640);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(14);

    auto *header = new QHBoxLayout;
    auto *titre = new QLabel(QString(
                                 "<div style='font-size:22px;font-weight:900;color:%1;'>%2</div>"
                                 "<div style='font-size:11px;color:%3;margin-top:2px;'>ID %4 · %5 places · %6</div>")
                                 .arg(Palette::texte, s.nom.toHtmlEscaped(), Palette::texteMuted)
                                 .arg(s.id).arg(s.capacite).arg(s.type.toHtmlEscaped()));
    titre->setTextFormat(Qt::RichText);
    header->addWidget(titre, 1);

    const QString dispoColor = s.estDisponible() ? Palette::succes : Palette::danger;
    const QString dispoTexte = s.estDisponible() ? "DISPONIBLE" : "INDISPONIBLE";
    auto *badge = new QLabel(dispoTexte);
    badge->setStyleSheet(QString(
                             "background:%1; color:#FFFFFF; font-weight:900; font-size:10px;"
                             "padding:6px 14px; border-radius:12px;").arg(dispoColor));
    header->addWidget(badge, 0, Qt::AlignTop);
    lay->addLayout(header);

    auto *infos = new QFrame;
    infos->setStyleSheet(styleCarte());
    auto *infosLay = new QVBoxLayout(infos);
    infosLay->setContentsMargins(18, 14, 18, 14);

    auto row = [&](const QString &k, const QString &v) {
        auto *h = new QHBoxLayout;
        auto *lk = new QLabel(k);
        lk->setStyleSheet(QString("color:%1;font-weight:700;font-size:11px;")
                              .arg(Palette::accent));
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
    lay->addWidget(infos);

    auto *remarque = new QFrame;
    remarque->setStyleSheet(QString(
                                "QFrame { background:%1; border-left:3px solid %2; border-radius:8px; }")
                                .arg(Palette::carteAlt, Palette::accent));
    auto *remLay = new QVBoxLayout(remarque);
    remLay->setContentsMargins(14, 10, 14, 10);
    auto *remTitle = new QLabel("💡 Remarque automatique");
    remTitle->setStyleSheet(QString("color:%1;font-weight:800;font-size:11px;")
                                .arg(Palette::accent));
    auto *remText = new QLabel(payload.remarqueAuto);
    remText->setStyleSheet(QString("color:%1;font-size:12px;").arg(Palette::texte));
    remText->setWordWrap(true);
    remLay->addWidget(remTitle);
    remLay->addWidget(remText);
    lay->addWidget(remarque);

    auto *admin = new QFrame;
    admin->setStyleSheet(QString(
                             "QFrame { background:%1; border:1px solid #312E81; border-radius:8px; }")
                             .arg(Palette::carteAlt));
    auto *adminLay = new QVBoxLayout(admin);
    adminLay->setContentsMargins(14, 10, 14, 10);
    auto *adminTitle = new QLabel("📜 Message administratif");
    adminTitle->setStyleSheet(QString("color:%1;font-weight:800;font-size:11px;")
                                  .arg(Palette::warning));
    auto *adminText = new QLabel(genererMessageAdministratif(s, "consultation"));
    adminText->setStyleSheet(QString("color:%1;font-size:12px;font-style:italic;")
                                 .arg(Palette::texte));
    adminText->setWordWrap(true);
    adminLay->addWidget(adminTitle);
    adminLay->addWidget(adminText);
    lay->addWidget(admin);

    auto *eng = new QLabel(payload.engagementAdmin);
    eng->setStyleSheet(QString("color:%1;font-style:italic;font-size:11px;"
                               "background:%2; padding:12px; border-radius:8px;")
                           .arg(Palette::texteMuted, Palette::carteAlt));
    eng->setWordWrap(true);
    lay->addWidget(eng);

    lay->addStretch();

    auto *btns = new QHBoxLayout;
    auto *btnQR = new QPushButton("📷 VOIR LE QR CODE");
    btnQR->setStyleSheet(styleBouton(Palette::accentDark, Palette::accent));
    QObject::connect(btnQR, &QPushButton::clicked, &dlg,
                     [this, idSalle]() { this->ouvrirGenerateurQR(idSalle); });

    auto *btnFermer = new QPushButton("FERMER");
    btnFermer->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
    QObject::connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);

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
                "FROM SALLE ORDER BY NOM_SALLE")) return;

    int row = 0;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
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
        t->setColumnWidth(lastCol, 260);
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
    dispoItem->setForeground(couleurDisponibilite(s.disponibilite));
    dispoItem->setTextAlignment(Qt::AlignCenter);
    QFont df = dispoItem->font();
    df.setBold(true);
    dispoItem->setFont(df);
    t->setItem(row, 4, dispoItem);

    t->setCellWidget(row, 5, creerWidgetActions(s.id, s.nom));
}

/* ============================================================
 *  READ — Recherche multicritère (bouton / Entrée)
 *  Comportement d'origine : affiche un QMessageBox si 0 résultat.
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
              "WHERE UPPER(NOM_SALLE) LIKE UPPER(:terme) "
              "   OR UPPER(TYPE_SALLE) LIKE UPPER(:terme) "
              "   OR TO_CHAR(ID_SALLE) = :id "
              "ORDER BY NOM_SALLE");
    q.bindValue(":terme", "%" + terme + "%", QSql::In);
    q.bindValue(":id",    terme, QSql::In);

    if (!q.exec()) { rafraichirSallesEtStats(); return; }

    int row = 0, trouvees = 0;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        insererLigneSalle(row++, s);
        ++trouvees;
    }
    if (trouvees == 0) {
        QMessageBox::information(this, "Recherche",
                                 QString("Aucune salle ne correspond à « %1 ».").arg(terme));
    }
    t->setSortingEnabled(true);
}

/* ============================================================
 *  READ — Recherche DYNAMIQUE (live search, debounce 250 ms)
 *  Pas de QMessageBox si 0 résultat (pour ne pas spammer).
 * ============================================================ */
void salle::onRechercheDynamiqueSalle()
{
    if (!ui->lineEdit_2 || !ui->tableSalles) return;

    // Champ vide → on restaure la liste complète
    if (ui->lineEdit_2->text().trimmed().isEmpty()) {
        rafraichirSallesEtStats();
        return;
    }

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return;

    const QString terme = ui->lineEdit_2->text().trimmed();

    auto *t = ui->tableSalles;
    viderTableSalles();

    QSqlQuery q(db);
    q.prepare("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE "
              "FROM SALLE "
              "WHERE UPPER(NOM_SALLE) LIKE UPPER(:terme) "
              "   OR UPPER(TYPE_SALLE) LIKE UPPER(:terme) "
              "   OR TO_CHAR(ID_SALLE) = :id "
              "ORDER BY NOM_SALLE");
    q.bindValue(":terme", "%" + terme + "%", QSql::In);
    q.bindValue(":id",    terme, QSql::In);

    if (!q.exec()) return;

    int row = 0;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        insererLigneSalle(row++, s);
    }

    t->setSortingEnabled(true);
    dessinerStatistiquesSalles();   // mise à jour du camembert
}

/* ============================================================
 *  Tri/filtrage avancé
 * ============================================================ */
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

        if (!c.blocs.isEmpty() && !c.blocs.contains(s.bloc)) continue;
        if (!c.etages.isEmpty() && !c.etages.contains(s.etage)) continue;
        if (!c.types.isEmpty() && !c.types.contains(s.type)) continue;
        if (!c.disponibilites.isEmpty() && !c.disponibilites.contains(s.disponibilite)) continue;
        if (c.capaciteMin > 0 && s.capacite < c.capaciteMin) continue;
        if (c.capaciteMax > 0 && s.capacite > c.capaciteMax) continue;
        if (!c.nomContient.trimmed().isEmpty()
            && !s.nom.contains(c.nomContient, Qt::CaseInsensitive)) continue;

        resultat.append(s);
    }

    std::sort(resultat.begin(), resultat.end(), [&c](const Salle &a, const Salle &b) {
        if (c.trierParCapaciteCroissante && a.capacite != b.capacite)
            return a.capacite < b.capacite;
        if (c.trierParCapaciteDecroissante && a.capacite != b.capacite)
            return a.capacite > b.capacite;
        if (a.bloc != b.bloc) return a.bloc < b.bloc;
        if (a.etage != b.etage) return a.etage < b.etage;
        return a.numeroSalle < b.numeroSalle;
    });

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
                                 "<div style='font-size:11px;color:%2;'>Combinez plusieurs critères simultanément.</div>")
                                 .arg(Palette::texte, Palette::texteMuted));
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
                             .arg(Palette::accent, Palette::bordure));
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
                              .arg(Palette::accent, Palette::bordure));
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

    auto *nomBox = new QGroupBox("Nom de salle");
    nomBox->setStyleSheet(capBox->styleSheet());
    auto *nomLay = new QHBoxLayout(nomBox);
    auto *edNom = new QLineEdit;
    edNom->setPlaceholderText("Contient… (ex: A-1)");
    edNom->setStyleSheet(styleChamp());
    nomLay->addWidget(edNom);
    cl->addWidget(nomBox);

    auto *triBox = new QGroupBox("Ordre d'affichage");
    triBox->setStyleSheet(capBox->styleSheet());
    auto *triLay = new QVBoxLayout(triBox);
    auto *rbNom   = new QCheckBox("Tri par défaut (bloc → étage → n°)");
    auto *rbCapA  = new QCheckBox("Capacité croissante");
    auto *rbCapD  = new QCheckBox("Capacité décroissante");
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
    btnReset->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
    auto *btnAnnuler = new QPushButton("Annuler");
    btnAnnuler->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
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
    });
    QObject::connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);
    QObject::connect(btnAppliquer, &QPushButton::clicked, [&]() {
        CriteresTri c;
        for (auto *cb : cbBlocs) if (cb->isChecked()) c.blocs.insert(cb->text());
        for (auto *cb : cbEtages) if (cb->isChecked()) c.etages.insert(cb->text().toInt());
        for (auto *cb : cbTypes) if (cb->isChecked()) c.types.insert(cb->text());
        for (auto *cb : cbDispo) if (cb->isChecked()) c.disponibilites.insert(cb->text());
        c.capaciteMin = spMin->value();
        c.capaciteMax = spMax->value();
        c.nomContient = edNom->text();
        c.trierParCapaciteCroissante   = rbCapA->isChecked();
        c.trierParCapaciteDecroissante = rbCapD->isChecked();

        dlg.accept();

        if (c.estVide() && !c.trierParCapaciteCroissante && !c.trierParCapaciteDecroissante) {
            rafraichirSallesEtStats();
        } else {
            appliquerCriteresTri(c);
            dessinerStatistiquesSalles();
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
                                 .arg(Palette::texte, Palette::texteMuted));
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
    form->addRow("Titre :",       edTitre);
    form->addRow("Sous-titre :",  edSous);
    form->addRow("En-tête :",     edEnTete);
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
                               .arg(Palette::accent, Palette::bordure));
    auto *colsLay = new QGridLayout(colsBox);
    colsLay->setSpacing(6);

    auto *ckID  = new QCheckBox("ID");          ckID->setChecked(true);
    auto *ckNom = new QCheckBox("Nom");         ckNom->setChecked(true);
    auto *ckCap = new QCheckBox("Capacité");    ckCap->setChecked(true);
    auto *ckTyp = new QCheckBox("Type");        ckTyp->setChecked(true);
    auto *ckDis = new QCheckBox("Disponibilité"); ckDis->setChecked(true);
    auto *ckBlc = new QCheckBox("Bloc");        ckBlc->setChecked(true);
    auto *ckEtg = new QCheckBox("Étage");       ckEtg->setChecked(true);
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
    btnAnnuler->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
    auto *btnExporter = new QPushButton("💾 Exporter en PDF");
    btnExporter->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    btns->addStretch();
    btns->addWidget(btnAnnuler);
    btns->addWidget(btnExporter);
    lay->addLayout(btns);

    QObject::connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);

    QObject::connect(btnExporter, &QPushButton::clicked, [&]() {
        OptionsExportPDF opt;
        opt.portee       = static_cast<OptionsExportPDF::Portee>(cbPortee->currentIndex());
        opt.titre        = edTitre->text().trimmed();
        opt.sousTitre    = edSous->text().trimmed();
        opt.enTete       = edEnTete->text().trimmed();
        opt.piedDePage   = edPied->text().trimmed();
        opt.paysage      = (cbOrient->currentIndex() == 1);
        opt.numeroterPages = ckNum->isChecked();
        opt.afficherID       = ckID->isChecked();
        opt.afficherNom      = ckNom->isChecked();
        opt.afficherCapacite = ckCap->isChecked();
        opt.afficherType     = ckTyp->isChecked();
        opt.afficherDispo    = ckDis->isChecked();
        opt.afficherBloc     = ckBlc->isChecked();
        opt.afficherEtage    = ckEtg->isChecked();

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
            "th { background:#312E81; color:#FFFFFF; padding:8px 10px; text-align:left; font-size:10pt; font-weight:bold; border:none; }"
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
 *  MÉTIER — Affectation intelligente
 * ============================================================ */
void salle::onSuggererSalle()
{
    if (!ui->leEffectif_2) return;

    bool ok = false;
    const int effectif = ui->leEffectif_2->text().trimmed().toInt(&ok);
    if (!ok || effectif <= 0) {
        QMessageBox::warning(this, "Affectation",
                             "Veuillez saisir un effectif valide (entier > 0).");
        ui->leEffectif_2->setFocus();
        return;
    }

    QSqlDatabase db = dbHacknova();
    if (!db.isValid() || !db.isOpen()) return;

    QSqlQuery q(db);
    q.prepare("SELECT ID_SALLE, NOM_SALLE, CAPACITE, TYPE_SALLE, DISPONIBILITE "
              "FROM SALLE WHERE DISPONIBILITE = 'Disponible'");
    if (!q.exec()) return;

    QVector<Salle> candidates;
    while (q.next()) {
        Salle s;
        s.id            = q.value(0).toLongLong();
        s.nom           = sqlStr(q.value(1));
        s.capacite      = q.value(2).toInt();
        s.type          = sqlStr(q.value(3));
        s.disponibilite = sqlStr(q.value(4));
        if (s.capacite >= effectif) candidates.append(s);
    }

    if (candidates.isEmpty()) {
        QMessageBox::warning(this, "Affectation intelligente",
                             QString("Aucune salle disponible ne peut accueillir %1 personne(s).").arg(effectif));
        return;
    }

    std::sort(candidates.begin(), candidates.end(), [effectif](const Salle &a, const Salle &b) {
        const int margeA = a.capacite - effectif;
        const int margeB = b.capacite - effectif;
        if (margeA != margeB) return margeA < margeB;
        return a.id < b.id;
    });

    const Salle &best = candidates.first();
    const int marge = best.capacite - effectif;

    QString conseil;
    if (marge <= 2)      conseil = "Ajustement optimal ✨";
    else if (marge <= 5) conseil = "Bonne adéquation ✅";
    else                 conseil = "Capacité plus large que nécessaire ⚠";

    QMessageBox::information(this, "Affectation intelligente",
                             QString("<b>Salle recommandée pour %1 personne(s) :</b><br><br>"
                                     "<b>%2</b> (cap. %3) — %4<br>Marge : %5 place(s)<br><br><i>%6</i>")
                                 .arg(effectif).arg(best.nom.toHtmlEscaped())
                                 .arg(best.capacite).arg(best.type.toHtmlEscaped())
                                 .arg(marge).arg(conseil));
}

/* ============================================================
 *  MÉTIER — QR CODE
 * ============================================================ */
QString salle::genererRemarqueAuto(const Salle &s) const
{
    QStringList notes;
    if (s.estDisponible()) notes << "Salle prête à être utilisée.";
    else notes << "Salle non disponible — vérifier avant toute réservation.";

    if (s.capacite < 5)      notes << QString("Capacité très réduite (%1 places) — idéale pour petites équipes.").arg(s.capacite);
    else if (s.capacite < 15) notes << QString("Capacité moyenne (%1 places) — convient aux équipes standard.").arg(s.capacite);
    else                      notes << QString("Grande capacité (%1 places) — adaptée aux événements de masse.").arg(s.capacite);

    if (s.type.contains("informatique", Qt::CaseInsensitive)) notes << "Prévoir vérification des postes et du réseau.";
    else if (s.type.contains("conférence", Qt::CaseInsensitive)) notes << "Prévoir sonorisation et projecteur.";
    else if (s.type.contains("réunion", Qt::CaseInsensitive)) notes << "Prévoir table de réunion et paperboard.";

    return notes.join(" ");
}

QString salle::genererEngagementAdmin(const Salle &s) const
{
    return QString("Je, administrateur HACKNOVA, engage ma responsabilité sur l'utilisation "
                   "conforme de la salle « %1 » (ID %2, type %3, capacité %4). Toute réservation "
                   "doit respecter les règles de sécurité et d'occupation. En cas d'anomalie, "
                   "la salle sera immédiatement réaffectée ou fermée.")
        .arg(s.nom, QString::number(s.id), s.type, QString::number(s.capacite));
}

QString salle::genererMessageAdministratif(const Salle &s, const QString &contexte) const
{
    const QString nom  = s.nom.toHtmlEscaped();
    const QString type = s.type.toHtmlEscaped();
    const QString cap  = QString::number(s.capacite);

    if (contexte == "consultation") {
        if (s.estDisponible()) {
            return QString("Bienvenue à la salle <b>%1</b>. Cette salle de type <b>%2</b> "
                           "est actuellement <b>disponible</b> et peut accueillir jusqu'à %3 personnes. "
                           "Vous pouvez procéder à la planification d'un événement.")
                .arg(nom, type, cap);
        } else {
            return QString("La salle <b>%1</b> est actuellement marquée <b>indisponible</b>. "
                           "Toute demande d'utilisation doit être préalablement validée par un "
                           "administrateur. Contactez le service logistique avant toute réservation.")
                .arg(nom);
        }
    }

    if (contexte == "reservation") {
        if (s.estDisponible())
            return QString("La réservation de la salle <b>%1</b> est possible. Confirmez votre "
                           "demande avec le responsable d'étage et respectez la capacité de %2 places.")
                .arg(nom, cap);
        return QString("La réservation de la salle <b>%1</b> ne peut être effectuée pour le moment "
                       "car la salle est indisponible.").arg(nom);
    }

    if (contexte == "avertissement") {
        return QString("⚠️ Attention : l'utilisation de la salle <b>%1</b> est soumise aux règles "
                       "d'occupation (%2 places max), au respect du matériel et au bon usage du "
                       "QR Code d'accès.").arg(nom, cap);
    }

    if (contexte == "maintenance") {
        return QString("La salle <b>%1</b> est en maintenance ou indisponible. "
                       "Merci de vérifier les prochaines disponibilités avant de planifier une activité.")
            .arg(nom);
    }

    return QString("Bienvenue à la salle <b>%1</b> — type %2 — capacité %3 personnes.")
        .arg(nom, type, cap);
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
    if (!opt.has_value()) return;
    const Salle &s = *opt;
    const PayloadQR payload = construirePayloadQR(s);
    const QString contenu = payload.serialiser();

    const QPixmap pixQR = genererPixmapQR(contenu, 360);
    if (pixQR.isNull()) {
        QMessageBox::warning(this, "QR Code",
                             "Échec de la génération du QR Code.\nVérifiez l'intégration de qrcodegen.");
        return;
    }

    QDialog dlg(this);
    dlg.setWindowTitle(QString("QR Code — %1").arg(s.nom));
    dlg.setMinimumWidth(600);
    dlg.setStyleSheet(QString("QDialog { background:%1; } QLabel { color:%2; }")
                          .arg(Palette::carte, Palette::texte));

    auto *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(12);

    auto *titre = new QLabel(QString(
                                 "<div style='font-size:20px;font-weight:900;color:%1;'>%2</div>"
                                 "<div style='font-size:11px;color:%3;'>ID %4 · %5 places · %6</div>")
                                 .arg(Palette::texte, s.nom.toHtmlEscaped(), Palette::texteMuted)
                                 .arg(s.id).arg(s.capacite).arg(s.type.toHtmlEscaped()));
    titre->setTextFormat(Qt::RichText);
    lay->addWidget(titre);

    auto *imgLabel = new QLabel;
    imgLabel->setPixmap(pixQR);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setStyleSheet("background:#FFFFFF;border-radius:12px;padding:16px;");
    lay->addWidget(imgLabel);

    auto *codeLabel = new QLabel(QString("<code style='color:%1;font-size:11px;'>%2</code>")
                                     .arg(Palette::texteMuted, contenu.toHtmlEscaped()));
    codeLabel->setTextFormat(Qt::RichText);
    codeLabel->setAlignment(Qt::AlignCenter);
    codeLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lay->addWidget(codeLabel);

    auto *infoMsg = new QLabel(genererMessageAdministratif(s, "consultation"));
    infoMsg->setStyleSheet(QString("color:%1;font-size:11px;background:%2;"
                                   "padding:12px;border-radius:8px;")
                               .arg(Palette::texteMuted, Palette::carteAlt));
    infoMsg->setWordWrap(true);
    lay->addWidget(infoMsg);

    auto *btns = new QHBoxLayout;
    auto *btnSave  = new QPushButton("💾 ENREGISTRER PNG");
    btnSave->setStyleSheet(styleBouton(Palette::succesDark, Palette::succes));
    auto *btnCopy  = new QPushButton("📋 COPIER LE CODE");
    btnCopy->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
    auto *btnClose = new QPushButton("FERMER");
    btnClose->setStyleSheet(styleBouton(Palette::bordure, "#334155", "color:#CBD5E1;"));
    btns->addWidget(btnSave);
    btns->addWidget(btnCopy);
    btns->addStretch();
    btns->addWidget(btnClose);
    lay->addLayout(btns);

    QObject::connect(btnClose, &QPushButton::clicked, &dlg, &QDialog::accept);
    QObject::connect(btnCopy, &QPushButton::clicked, [contenu]() {
        QApplication::clipboard()->setText(contenu);
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
                             "Aucun QR Code détecté dans cette image.\nVérifiez la qualité ou le cadrage.");
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
        QMessageBox::warning(this, "QR Code",
                             QString("Aucune salle ne correspond à l'ID %1.").arg(id));
        return;
    }
    const Salle &s = *opt;
    const QString couleur = s.estDisponible() ? Palette::succes : Palette::danger;
    const QString etat    = s.estDisponible() ? "✅ ACCÈS AUTORISÉ" : "⛔ ACCÈS REFUSÉ";
    const QString msgAdmin = genererMessageAdministratif(s, "consultation");

    QMessageBox::information(this, "Résultat du scan",
                             QString("<h2 style='color:%1;margin:0;'>%2</h2>"
                                     "<p style='color:%3;'>Salle identifiée : <b>%4</b></p><hr/>"
                                     "<p style='color:%5;'><b style='color:%6;'>Capacité :</b> %7 places</p>"
                                     "<p style='color:%5;'><b style='color:%6;'>Type :</b> %8</p>"
                                     "<p style='color:%5;'><b style='color:%6;'>Statut :</b> "
                                     "<span style='color:%1;font-weight:bold;'>%9</span></p>"
                                     "<p style='color:%5;font-style:italic;'>%10</p>")
                                 .arg(couleur, etat, Palette::texteMuted, s.nom.toHtmlEscaped())
                                 .arg(Palette::texte, Palette::accent)
                                 .arg(s.capacite).arg(s.type.toHtmlEscaped())
                                 .arg(s.disponibilite.toHtmlEscaped())
                                 .arg(msgAdmin));
}

void salle::onValiderQR()
{
    if (!ui->leCodeQR_4) return;
    const QString code = ui->leCodeQR_4->text().trimmed();
    if (code.isEmpty()) {
        QMessageBox::warning(this, "QR Code", "Saisissez un code manuel.");
        return;
    }
    traiterPayloadQRScanne(code);
    ui->leCodeQR_4->clear();
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

    auto *btnVoir  = makeBtn("VOIR",     "#475569", "#64748B");
    auto *btnModif = makeBtn("MODIFIER", Palette::accentDark, Palette::accent);
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
 *  STATISTIQUES SALLES
 * ============================================================ */
void salle::dessinerStatistiquesSalles()
{
    {
        QPixmap pix(190, 190);
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);

        int dispo = 0, indispo = 0;
        for (int i = 0; i < ui->tableSalles->rowCount(); ++i) {
            QTableWidgetItem *it = ui->tableSalles->item(i, 4);
            if (!it) continue;
            if (it->text().compare("Disponible", Qt::CaseInsensitive) == 0) dispo++;
            else indispo++;
        }
        int total = dispo + indispo;

        QRectF rect(10, 15, 110, 110);
        if (total == 0) {
            p.setBrush(QColor(Palette::bordure));
            p.setPen(Qt::NoPen);
            p.drawEllipse(rect);
        } else {
            double startAngle = 90.0;
            auto drawSlice = [&](int val, const QColor &color) {
                if (val <= 0) return;
                double sweep = -360.0 * val / total;
                p.setBrush(color);
                p.setPen(Qt::NoPen);
                p.drawPie(rect, int(startAngle * 16), int(sweep * 16));
                startAngle += sweep;
            };
            drawSlice(dispo,   QColor(Palette::succes));
            drawSlice(indispo, QColor(Palette::danger));
        }

        QFont f = p.font();
        f.setFamily("Segoe UI");
        f.setPointSize(8);
        f.setBold(true);
        p.setFont(f);

        int legY = 25;
        p.setBrush(QColor(Palette::succes));
        p.setPen(Qt::NoPen);
        p.drawEllipse(135, legY, 8, 8);
        p.setPen(QColor(Palette::texte));
        p.drawText(148, legY + 8, QString("Dispo (%1)").arg(dispo));
        legY += 25;

        p.setBrush(QColor(Palette::danger));
        p.setPen(Qt::NoPen);
        p.drawEllipse(135, legY, 8, 8);
        p.setPen(QColor(Palette::texte));
        p.drawText(148, legY + 8, QString("Indispo (%1)").arg(indispo));

        f.setBold(false);
        f.setPointSize(8);
        p.setFont(f);
        p.setPen(QColor(Palette::texteDim));
        p.drawText(10, 175, "Répartition par disponibilité");
        p.end();
        ui->sallesPage_labelStatutPie->setPixmap(pix);
    }

    {
        QPixmap pix(230, 190);
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        p.setRenderHint(QPainter::Antialiasing);

        QMap<QString, int> types;
        for (int i = 0; i < ui->tableSalles->rowCount(); ++i) {
            QTableWidgetItem *it = ui->tableSalles->item(i, 3);
            if (it && !it->text().isEmpty()) types[it->text()]++;
        }

        if (types.isEmpty()) {
            QFont f = p.font();
            f.setFamily("Segoe UI");
            f.setPointSize(9);
            f.setBold(true);
            p.setFont(f);
            p.setPen(QColor(Palette::texteDim));
            p.drawText(10, 100, "Aucune salle enregistrée");
        } else {
            int maxVal = 1;
            for (int v : types) if (v > maxVal) maxVal = v;

            auto couleur = [](const QString &t) -> QColor {
                if (t == "Salle informatique") return QColor("#818CF8");
                if (t == "Salle de réunion")   return QColor("#FBBF24");
                if (t == "Salle conférence")   return QColor("#10B981");
                return QColor("#EF4444");
            };

            int y = 20;
            const int barMaxW = 60;
            const int barH = 18;

            QFont f = p.font();
            f.setFamily("Segoe UI");
            f.setPointSize(8);
            f.setBold(true);
            p.setFont(f);

            for (auto it = types.begin(); it != types.end(); ++it) {
                p.setBrush(couleur(it.key()));
                p.setPen(Qt::NoPen);
                p.drawEllipse(10, y + 4, 8, 8);

                p.setPen(QColor(Palette::texte));
                p.drawText(25, y + 12, it.key());

                p.setPen(Qt::NoPen);
                p.setBrush(QColor(Palette::bordure));
                p.drawRoundedRect(130, y, barMaxW, barH, 4, 4);

                int w = int(barMaxW * double(it.value()) / maxVal);
                p.setBrush(couleur(it.key()));
                p.drawRoundedRect(130, y, w, barH, 4, 4);

                p.setPen(QColor("#FFFFFF"));
                p.drawText(130 + w + 6, y + 13, QString::number(it.value()));

                y += barH + 20;
            }
        }

        QFont f = p.font();
        f.setFamily("Segoe UI");
        f.setPointSize(8);
        f.setBold(false);
        p.setFont(f);
        p.setPen(QColor(Palette::texteDim));
        p.drawText(10, 175, "Nombre de salles par type");
        p.end();
        ui->sallesPage_labelRoleBar->setPixmap(pix);
    }
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
}

void salle::goLogin()    { allerPage(0); }
void salle::goEmployes() { allerPage(1); }
void salle::goSalles()   { allerPage(2); }

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
        if (actif == "O" || actif == "0") {
            q.finish();
            ui->lineEditMotDePasse->clear();
            goEmployes();
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
    if (ui->btnEmployes)    QObject::connect(ui->btnEmployes,    &QPushButton::clicked, this, &salle::goEmployes);
    if (ui->btnSalles)      QObject::connect(ui->btnSalles,      &QPushButton::clicked, this, &salle::goSalles);
    if (ui->sallesPage_btnEmployes) QObject::connect(ui->sallesPage_btnEmployes, &QPushButton::clicked, this, &salle::goEmployes);
    if (ui->sallesPage_btnSalles)   QObject::connect(ui->sallesPage_btnSalles,   &QPushButton::clicked, this, &salle::goSalles);
    if (ui->btnNotifications)       QObject::connect(ui->btnNotifications,       &QPushButton::clicked, this, &salle::onNotifications);
    if (ui->btnProfil)              QObject::connect(ui->btnProfil,              &QPushButton::clicked, this, &salle::onProfil);
    if (ui->btnDeconnexion)         QObject::connect(ui->btnDeconnexion,         &QPushButton::clicked, this, &salle::onDeconnexion);
    if (ui->sallesPage_btnDeconnexion) QObject::connect(ui->sallesPage_btnDeconnexion, &QPushButton::clicked, this, &salle::onDeconnexion);
}

void salle::connecterChatbot()
{
    if (ui->leQuestion)
        QObject::connect(ui->leQuestion, &QLineEdit::returnPressed,
                         this, &salle::onEnvoyerQuestion);

    if (ui->textChatbot) {
        ui->textChatbot->setHtml(R"(
            <div style='color:#E2E8F0;font-family:Segoe UI,Arial;font-size:13px;'>
            <p><b style='color:#818CF8;'>HACKNOVA Bot :</b>
            Bonjour 👋 Je suis votre assistant. Posez-moi une question
            sur les salles, les employés, les QR codes, etc.</p>
            </div>
        )");
    }
}

void salle::onEnvoyerQuestion()
{
    if (!ui->leQuestion || !ui->textChatbot) return;
    const QString q = ui->leQuestion->text().trimmed();
    if (q.isEmpty()) return;

    const QString ql = q.toLower();
    QString reponse;

    if (ql.contains("bonjour") || ql.contains("salut") || ql.contains("hello"))
        reponse = "Bonjour 👋 Comment puis-je vous aider ?";
    else if (ql.contains("combien") && ql.contains("salle"))
        reponse = QString("Il y a actuellement <b>%1 salles</b>.").arg(ui->tableSalles->rowCount());
    else if (ql.contains("disponible") || ql.contains("dispo")) {
        int n = 0;
        for (int i = 0; i < ui->tableSalles->rowCount(); ++i) {
            QTableWidgetItem *it = ui->tableSalles->item(i, 4);
            if (it && it->text().compare("Disponible", Qt::CaseInsensitive) == 0) n++;
        }
        reponse = QString("<b>%1 salles</b> sont disponibles.").arg(n);
    }
    else if (ql.contains("combien") && ql.contains("employ"))
        reponse = QString("Il y a <b>%1 employés</b>.").arg(ui->tableEmployes->rowCount());
    else if (ql.contains("qr") || ql.contains("code"))
        reponse = "Chaque salle possède un <b>QR Code</b> (bouton <b>QR</b> dans la liste). "
                  "Vous pouvez générer, enregistrer en PNG, imprimer ou scanner via import d'image.";
    else if (ql.contains("statistique") || ql.contains("graphique"))
        reponse = "Les statistiques sont calculées à droite (camembert + barres).";
    else if (ql.contains("merci"))
        reponse = "Avec plaisir 😊";
    else if (ql.contains("aide") || ql.contains("help"))
        reponse = "Je peux vous renseigner sur : salles, employés, disponibilités, "
                  "statistiques, QR codes.";
    else
        reponse = "Je n'ai pas compris. Tapez <b>aide</b>.";

    QString html = ui->textChatbot->toHtml();
    html += QString(R"(
        <div style='color:#E2E8F0;font-family:Segoe UI,Arial;font-size:13px;margin-top:8px;'>
        <p><b style='color:#10B981;'>Vous :</b> %1</p>
        <p><b style='color:#818CF8;'>Bot :</b> %2</p>
        </div>
    )").arg(q.toHtmlEscaped(), reponse);

    ui->textChatbot->setHtml(html);
    ui->textChatbot->verticalScrollBar()->setValue(
        ui->textChatbot->verticalScrollBar()->maximum());
    ui->leQuestion->clear();
}

/* ============================================================
 *  DIALOGUES — notifications / profil / déconnexion
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
                               "border:none; font-size:13px; }")
                           .arg(Palette::carteAlt, Palette::texte));
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
        <div style='color:#E2E8F0;font-family:Segoe UI;font-size:13px;'>
        <p style='color:#818CF8;font-weight:800;'>Notification</p>
        <p style='color:#94A3B8;'>Aucune notification disponible.</p>
        </div>
    )");
}

void salle::onProfil()
{
    afficherDialogue(this, "Profil utilisateur", R"(
        <div style='color:#E2E8F0;text-align:center;font-family:Segoe UI;'>
        <h1 style='color:#818CF8;'>HN</h1>
        <h2 style='color:#FFFFFF;'>Utilisateur</h2>
        <p style='color:#94A3B8;'><b>Rôle :</b> Administrateur</p>
        <p style='color:#94A3B8;'><b>Statut :</b> <span style='color:#10B981;'>Actif</span></p>
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
 *  THÈME GLOBAL
 * ============================================================ */
void salle::appliquerTheme()
{
    this->setStyleSheet(R"(
QMainWindow, QWidget#centralWidget { background-color:#080C14; }
QWidget { color:#E2E8F0; font-family:'Segoe UI','Arial',sans-serif; font-size:13px; }
QToolTip { background-color:#1E293B; color:#F1F5F9; border:1px solid #475569;
           border-radius:6px; padding:6px 10px; }

QScrollBar:vertical { background:transparent; width:10px; }
QScrollBar::handle:vertical { background:#334155; min-height:40px; border-radius:5px; }
QScrollBar::handle:vertical:hover { background:#475569; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0; }

QFrame#frameLoginBrand { background-color:#1E1B4B; border:1px solid #312E81;
    border-top-left-radius:20px; border-bottom-left-radius:20px; }
QFrame#frameLoginCard  { background-color:#111827; border:1px solid #1E293B;
    border-top-right-radius:20px; border-bottom-right-radius:20px; }
QLabel#labelLoginLogo { background-color:#4338CA; color:#FFFFFF; border-radius:60px;
    font-size:44px; font-weight:900; }
QLabel#labelLoginBrandTitle { color:#FFFFFF; font-size:28px; font-weight:900; letter-spacing:2px; }
QLabel#labelLoginBrandSub   { color:#A5B4FC; font-size:11px; font-weight:800; letter-spacing:1.5px; }
QLabel#labelLoginBrandSlogan{ color:#C7D2FE; font-size:13px; }
QLabel#labelLoginBrandTeam  { color:#6366F1; font-size:10px; font-weight:800; letter-spacing:1px; }
QLabel#labelLoginTitle      { color:#FFFFFF; font-size:24px; font-weight:900; }
QLabel#labelLoginField, QLabel#labelLoginField2 { color:#818CF8; font-size:11px; font-weight:800; letter-spacing:1px; }
QLineEdit#lineEditIdentifiant, QLineEdit#lineEditMotDePasse {
    background-color:#0F172A; color:#F1F5F9; border:1px solid #334155;
    border-radius:8px; padding:0 12px; font-size:14px; }
QLineEdit#lineEditIdentifiant:focus, QLineEdit#lineEditMotDePasse:focus { border:1px solid #6366F1; }
QCheckBox#checkBoxSouvenir { color:#94A3B8; font-size:12px; }
QPushButton#pushButtonConnexion { background-color:#4338CA; color:#FFFFFF; border:none;
    border-radius:8px; font-size:14px; font-weight:900; }
QPushButton#pushButtonConnexion:hover { background-color:#6366F1; }
QLabel#labelLoginFooter { color:#6366F1; font-size:12px; font-weight:bold; }

QFrame#frameNavbar, QFrame#sallesPage_frameNavbar { background-color:#111827;
    border:1px solid #1E293B; border-radius:12px; }
QLabel#labelNavLogo, QLabel#sallesPage_labelNavLogo { background-color:#4338CA; color:#FFFFFF;
    border-radius:8px; font-size:18px; font-weight:900; }
QLabel#labelNavBrand, QLabel#sallesPage_labelNavBrand { color:#FFFFFF; font-size:14px;
    font-weight:900; letter-spacing:1.5px; }
QLabel#labelNavSub, QLabel#sallesPage_labelNavSub { color:#818CF8; font-size:9px; font-weight:800; }

QPushButton#btnDashboard, QPushButton#btnEmployes, QPushButton#btnSalles,
QPushButton#btnEvaluateurs, QPushButton#btnParticipants, QPushButton#btnSponsors,
QPushButton#btnProjets, QPushButton#btnNotifications, QPushButton#btnProfil,
QPushButton#sallesPage_btnDashboard, QPushButton#sallesPage_btnEmployes,
QPushButton#sallesPage_btnEvaluateurs, QPushButton#sallesPage_btnParticipants,
QPushButton#sallesPage_btnSponsors, QPushButton#sallesPage_btnProjets,
QPushButton#sallesPage_btnNotifications, QPushButton#sallesPage_btnProfil {
    background-color:transparent; color:#94A3B8; border:none; border-radius:6px;
    font-size:10px; font-weight:800; padding:6px 8px; }
QPushButton#btnDashboard:hover, QPushButton#btnEmployes:hover, QPushButton#btnSalles:hover,
QPushButton#btnEvaluateurs:hover, QPushButton#btnParticipants:hover, QPushButton#btnSponsors:hover,
QPushButton#btnProjets:hover, QPushButton#btnNotifications:hover, QPushButton#btnProfil:hover,
QPushButton#sallesPage_btnDashboard:hover, QPushButton#sallesPage_btnEmployes:hover,
QPushButton#sallesPage_btnEvaluateurs:hover, QPushButton#sallesPage_btnParticipants:hover,
QPushButton#sallesPage_btnSponsors:hover, QPushButton#sallesPage_btnProjets:hover,
QPushButton#sallesPage_btnNotifications:hover, QPushButton#sallesPage_btnProfil:hover {
    background-color:#1F2937; color:#F1F5F9; }
QPushButton#btnEmployes, QPushButton#sallesPage_btnSalles {
    background-color:#312E81; color:#FFFFFF; border-bottom:2px solid #6366F1; }
QPushButton#btnDeconnexion, QPushButton#sallesPage_btnDeconnexion {
    background-color:#7F1D1D; color:#FFFFFF; border:1px solid #991B1B; border-radius:6px;
    font-size:10px; font-weight:800; padding:6px 8px; }
QPushButton#btnDeconnexion:hover, QPushButton#sallesPage_btnDeconnexion:hover {
    background-color:#991B1B; }

QLabel#labelTitleEmployes, QLabel#labelTitleSalles { color:#FFFFFF; font-size:22px; font-weight:900; }
QLabel#labelSubEmployes, QLabel#labelSubSalles { color:#64748B; font-size:13px; }

QFrame#cardFormEmployes, QFrame#cardFormSalles, QFrame#cardTableEmployes, QFrame#cardTableSalles,
QFrame#frameChatbot, QFrame#cardStats, QFrame#sallesPage_cardStats,
QFrame#frameAffectation_2, QFrame#frameQR_4 {
    background-color:#111827; border:1px solid #1E293B; border-radius:12px; }
QLabel#labelFormTitleEmployes, QLabel#labelFormTitleSalles,
QLabel#labelTableTitleEmployes, QLabel#labelTableTitleSalles,
QLabel#lblTitreChatbot, QLabel#labelStatsTitle, QLabel#sallesPage_labelStatsTitle,
QLabel#lblTitreAffect_2, QLabel#lblTitreQR_4 {
    color:#FFFFFF; font-size:15px; font-weight:800; }
QLabel#lblDescAffect_2, QLabel#lblDescQR_4 { color:#94A3B8; font-size:12px; }

QLabel#lblEmpID, QLabel#lblEmpNom, QLabel#lblEmpPrenom, QLabel#lblEmpMdp,
QLabel#lblEmpRole, QLabel#lblEmpStatut, QLabel#lblSalleID, QLabel#lblSalleNom,
QLabel#lblSalleCapacite, QLabel#lblSalleType, QLabel#lblSalleDispo,
QLabel#lblSalleBloc, QLabel#lblSalleEtage, QLabel#lblSalleNumero {
    color:#818CF8; font-size:11px; font-weight:800; }
QLineEdit#lineEditEmpID, QLineEdit#lineEditEmpNom, QLineEdit#lineEditEmpPrenom,
QLineEdit#lineEditEmpMdp, QLineEdit#lineEditSalleID, QLineEdit#lineEditSalleNom,
QLineEdit#lineEdit, QLineEdit#lineEdit_2, QLineEdit#lineEditSalleTypeAutre,
QSpinBox#spinBoxSalleCapacite, QSpinBox#spinBoxSalleEtage, QSpinBox#spinBoxSalleNumero,
QComboBox#comboBoxSalleBloc {
    background-color:#0B1120; color:#F1F5F9; border:1px solid #334155;
    border-radius:6px; padding:0 10px; font-size:13px; min-height:32px; }
QLineEdit#lineEditSalleNom:focus, QLineEdit#lineEdit_2:focus,
QSpinBox#spinBoxSalleCapacite:focus { border:1px solid #6366F1; }

QComboBox#comboBoxEmpRole, QComboBox#comboBoxEmpStatut,
QComboBox#comboBoxSalleType, QComboBox#comboBoxSalleDispo {
    background-color:#0B1120; color:#F1F5F9; border:1px solid #334155;
    border-radius:6px; padding:0 10px; font-size:13px; min-height:32px; }
QComboBox QAbstractItemView { background-color:#1E293B; color:#F1F5F9;
    border:1px solid #334155; selection-background-color:#4338CA; }

QPushButton#btnAjouterEmploye, QPushButton#btnExporterEmploye,
QPushButton#btnAjouterSalle, QPushButton#btnExporterSalle {
    background-color:#059669; color:#FFFFFF; border:1px solid #047857;
    border-radius:6px; font-size:12px; font-weight:800; padding:0 14px;
    min-width:100px; min-height:32px; }
QPushButton#btnAjouterEmploye:hover, QPushButton#btnExporterEmploye:hover,
QPushButton#btnAjouterSalle:hover, QPushButton#btnExporterSalle:hover {
    background-color:#10B981; }
QPushButton#btn_Annuler, QPushButton#btnTrierEmploye,
QPushButton#btnAnnuler, QPushButton#btnTrierSalle {
    background-color:#1E293B; color:#CBD5E1; border:1px solid #334155;
    border-radius:6px; font-size:12px; font-weight:800; padding:0 14px;
    min-width:100px; min-height:32px; }
QPushButton#btn_Annuler:hover, QPushButton#btnTrierEmploye:hover,
QPushButton#btnAnnuler:hover, QPushButton#btnTrierSalle:hover {
    background-color:#334155; }
QPushButton#btnRechercherEmploye, QPushButton#btnRechercherSalle {
    background-color:#4338CA; color:#FFFFFF; border:1px solid #3730A3;
    border-radius:6px; font-size:12px; font-weight:800; padding:0 14px;
    min-width:100px; min-height:32px; }
QPushButton#btnRechercherEmploye:hover, QPushButton#btnRechercherSalle:hover {
    background-color:#6366F1; }
QPushButton#btnSuggerer_2, QPushButton#btnValiderQR_4, QPushButton#btnEnvoyer,
QPushButton#btnScannerCamera_4 {
    background-color:#4338CA; color:#FFFFFF; border:1px solid #3730A3;
    border-radius:6px; font-size:12px; font-weight:800; padding:0 12px; min-height:30px; }
QPushButton#btnSuggerer_2:hover, QPushButton#btnValiderQR_4:hover,
QPushButton#btnEnvoyer:hover, QPushButton#btnScannerCamera_4:hover {
    background-color:#6366F1; }

QTableWidget { background-color:#0B1120; alternate-background-color:#111827;
    color:#E2E8F0; border:1px solid #1E293B; border-radius:8px; gridline-color:#1E293B; }
QTableWidget::item { padding:4px 8px; border-bottom:1px solid #1E293B; }
QTableWidget::item:selected { background-color:#312E81; color:#FFFFFF; }
QHeaderView::section { background-color:#111827; color:#94A3B8; font-size:11px;
    font-weight:800; padding:8px 6px; border:none; border-bottom:2px solid #312E81; }

QTextBrowser#textChatbot { background-color:#0B1120; color:#E2E8F0;
    border:1px solid #1E293B; border-radius:8px; padding:6px; }
QLineEdit#leQuestion, QLineEdit#leEffectif_2, QLineEdit#leCodeQR_4 {
    background-color:#111827; color:#F1F5F9; border:1px solid #334155;
    border-radius:6px; padding:0 10px; }

QMessageBox, QDialog { background-color:#111827; color:#E2E8F0; }
QMessageBox QLabel, QDialog QLabel { color:#E2E8F0; }
QMessageBox QPushButton, QDialog QPushButton {
    background-color:#4338CA; color:#FFFFFF; border:none; border-radius:6px;
    font-weight:800; padding:6px 16px; }
QMessageBox QPushButton:hover, QDialog QPushButton:hover { background-color:#6366F1; }
)");
}