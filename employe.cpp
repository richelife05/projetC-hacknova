#include "employe.h"
#include "ui_integration.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QRegularExpression>

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
// === EMPLOYE ==========================================================
// ======================================================================

Employe::Employe(const QString &id, const QString &nom, const QString &prenom,
                 const QString &mdp, const QString &role, const QString &statut)
    : id(id), nom(nom), prenom(prenom), mdp(mdp), role(role), statut(statut)
{
}

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (IDEMPLOYE, NOM, PRENOM, MDP, ROLE, STATUT) "
                  "VALUES (:id, :nom, :prenom, :mdp, :role, :statut)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mdp", mdp);
    query.bindValue(":role", role);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "ajouter :" << query.lastError().text();
        return false;
    }
    return true;
}

QString Employe::colonneTriValide(const QString &triPar)
{
    static const QStringList autorises = {"IDEMPLOYE", "NOM", "PRENOM"};
    return autorises.contains(triPar) ? triPar : QString("IDEMPLOYE");
}

static QString clauseTri(const QString &colonne, bool croissant)
{
    const QString sens = croissant ? " ASC" : " DESC";
    if (colonne == "NOM") return "NLSSORT(NOM, 'NLS_SORT=BINARY_AI')" + sens;
    if (colonne == "PRENOM") return "NLSSORT(PRENOM, 'NLS_SORT=BINARY_AI')" + sens;
    return "IDEMPLOYE" + sens;
}

static void nommerColonnes(QSqlQueryModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
}

QSqlQueryModel* Employe::afficher(const QString &triPar, bool croissant)
{
    const QString colonne = colonneTriValide(triPar);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT IDEMPLOYE, NOM, PRENOM, MDP, ROLE, STATUT FROM EMPLOYE ORDER BY "
                    + clauseTri(colonne, croissant));
    if (model->lastError().isValid())
        qDebug() << "afficher :" << model->lastError().text();

    nommerColonnes(model);
    return model;
}

QSqlQueryModel* Employe::rechercher(const QString &motCle, const QString &triPar, bool croissant)
{
    const QString colonne = colonneTriValide(triPar);

    QString k = motCle.trimmed().toUpper();
    k.replace("\\", "\\\\").replace("%", "\\%").replace("_", "\\_");
    const QString motif = "%" + k + "%";

    QSqlQuery query;
    query.prepare("SELECT IDEMPLOYE, NOM, PRENOM, MDP, ROLE, STATUT FROM EMPLOYE "
                  "WHERE UPPER(IDEMPLOYE) LIKE :k1 ESCAPE '\\' OR UPPER(NOM) LIKE :k2 ESCAPE '\\' "
                  "OR UPPER(PRENOM) LIKE :k3 ESCAPE '\\' OR UPPER(ROLE) LIKE :k4 ESCAPE '\\' "
                  "OR UPPER(STATUT) LIKE :k5 ESCAPE '\\' "
                  "ORDER BY " + clauseTri(colonne, croissant));
    query.bindValue(":k1", motif);
    query.bindValue(":k2", motif);
    query.bindValue(":k3", motif);
    query.bindValue(":k4", motif);
    query.bindValue(":k5", motif);
    if (!query.exec())
        qDebug() << "rechercher :" << query.lastError().text();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(std::move(query));
    nommerColonnes(model);
    return model;
}

bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM=:nom, PRENOM=:prenom, MDP=:mdp, ROLE=:role, STATUT=:statut "
                  "WHERE IDEMPLOYE=:id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mdp", mdp);
    query.bindValue(":role", role);
    query.bindValue(":statut", statut);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "modifier :" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::supprimer(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE IDEMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "supprimer :" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::authentifier(const QString &id, const QString &mdp)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE "
                  "WHERE TRIM(IDEMPLOYE) = :id AND MDP = :mdp AND STATUT = 'Actif'");
    query.bindValue(":id", id);
    query.bindValue(":mdp", mdp);

    qDebug() << "Requête préparée :" << query.lastQuery();

    if (!query.exec() || !query.next()) {
        qDebug() << "authentifier :" << query.lastError().text();
        return false;
    }
    const int trouves = query.value(0).toInt();
    qDebug() << "Authentification -> ID :" << id << "| résultats trouvés :" << trouves;
    return trouves > 0;
}

bool Employe::trouver(const QString &id, Employe &resultat)
{
    QSqlQuery query;
    query.prepare("SELECT IDEMPLOYE, NOM, PRENOM, MDP, ROLE, STATUT FROM EMPLOYE WHERE TRIM(IDEMPLOYE) = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        qDebug() << "trouver :" << query.lastError().text();
        return false;
    }
    resultat = Employe(query.value(0).toString().trimmed(), query.value(1).toString(),
                       query.value(2).toString(), query.value(3).toString(),
                       query.value(4).toString(), query.value(5).toString());
    return true;
}

bool Employe::peutSupprimer(const QString &role)
{
    return role == "Administrateur" || role == "Responsable RH";
}

QString Employe::prochainId()
{
    QSqlQuery query;
    int n = 1;
    if (query.exec("SELECT NVL(MAX(TO_NUMBER(REGEXP_SUBSTR(IDEMPLOYE, '[0-9]+$'))), 0) + 1 FROM EMPLOYE")
        && query.next())
        n = query.value(0).toInt();
    else
        qDebug() << "prochainId :" << query.lastError().text();

    return QString("EMP-%1").arg(n, 3, 10, QChar('0'));
}

QString Employe::verifierSaisie() const
{
    static const QRegularExpression reNom("^[\\p{L}][\\p{L} '\\-]{1,49}$");

    if (!reNom.match(nom).hasMatch())
        return "Nom invalide (lettres uniquement, 2 à 50 caractères).";
    if (!reNom.match(prenom).hasMatch())
        return "Prénom invalide (lettres uniquement, 2 à 50 caractères).";
    if (mdp.size() < 6 || mdp.size() > 50)
        return "Le mot de passe doit contenir entre 6 et 50 caractères.";
    if (role.isEmpty() || statut.isEmpty())
        return "Rôle et statut obligatoires.";
    if (statut != "Actif" && statut != "Inactif")
        return "Statut invalide (Actif ou Inactif).";
    if (role != "Administrateur" && role != "Responsable RH")
        return "Rôle invalide (Administrateur ou Responsable RH).";
    return QString();
}

// ======================================================================
// === HELPERS UI =======================================================
// ======================================================================

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

static void exporterDonnees(QWidget *parent, const QStringList &entetes, const QVector<QStringList> &lignes,
                            const QString &nomParDefaut, const QString &titre);

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
    if (chemin.isEmpty()) return;

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
        out.setGenerateByteOrderMark(true);
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
// === INTEGRATION : Constructeur =======================================
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

    chargerSallesDepuisBDD();

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
// === MESSAGE STANDARD : MODULE NON DISPONIBLE =========================
// ======================================================================
void integration::afficherModuleNonDisponible(const QString &nomModule)
{
    if (m_roleConnecte == "Administrateur") {
        // Petite fenêtre informative — style pro
        QMessageBox box(this);
        box.setWindowTitle("Module en préparation");
        box.setIcon(QMessageBox::Information);
        box.setTextFormat(Qt::RichText);
        box.setText(QString(
            "<div style='font-family:Segoe UI, Arial;font-size:13px;color:#E2E8F0;'>"
            "<p style='font-size:15px;font-weight:800;color:#818CF8;margin:0 0 10px 0;'>"
            "🚧 %1</p>"
            "<p style='color:#94A3B8;margin:0;'>"
            "Cette gestion sera accessible dans une <b style='color:#10B981;'>prochaine mise à jour</b>."
            "</p>"
            "<p style='color:#64748B;font-size:11px;margin-top:14px;'>"
            "Merci de votre compréhension — Équipe HACKNOVA."
            "</p></div>").arg(nomModule.toHtmlEscaped()));
        box.setStandardButtons(QMessageBox::Ok);
        box.button(QMessageBox::Ok)->setText("J'ai compris");
        box.exec();
    } else {
        // Alerte d'accès refusé — style pro
        QMessageBox box(this);
        box.setWindowTitle("Accès non autorisé");
        box.setIcon(QMessageBox::Warning);
        box.setTextFormat(Qt::RichText);
        box.setText(QString(
            "<div style='font-family:Segoe UI, Arial;font-size:13px;color:#E2E8F0;'>"
            "<p style='font-size:15px;font-weight:800;color:#EF4444;margin:0 0 10px 0;'>"
            "🔒 Accès refusé</p>"
            "<p style='color:#E2E8F0;margin:0 0 8px 0;'>"
            "Le module <b>%1</b> est <b style='color:#EF4444;'>hors de votre périmètre</b>."
            "</p>"
            "<p style='color:#94A3B8;margin:0;'>"
            "Votre rôle <b>Responsable RH</b> vous donne accès uniquement à la "
            "<b style='color:#10B981;'>gestion des employés</b>."
            "</p>"
            "<p style='color:#64748B;font-size:11px;margin-top:14px;'>"
            "Pour toute demande d'extension de droits, contactez un Administrateur."
            "</p></div>").arg(nomModule.toHtmlEscaped()));
        box.setStandardButtons(QMessageBox::Ok);
        box.button(QMessageBox::Ok)->setText("Compris");
        box.exec();
    }
}

// ======================================================================
// === SLOTS GÉNÉRAUX ===================================================
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

    auto *scroll = new QScrollArea(page);
    scroll->setObjectName("scrollEvaluateurs");
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidgetResizable(false);
    ui->eval_mainContent->setGeometry(0, 0, 1420, 1000);
    scroll->setWidget(ui->eval_mainContent);
    auto *pageLayout = new QVBoxLayout(page);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    pageLayout->addWidget(scroll);

    connect(ui->sallesPage_btnDashboard_2, &QPushButton::clicked, this, &integration::goDashboard);
    connect(ui->sallesPage_btnEmployes_2, &QPushButton::clicked, this, &integration::goEmployes);
    connect(ui->sallesPage_btnSalles_2, &QPushButton::clicked, this, &integration::goSalles);
    connect(ui->sallesPage_btnEvaluateurs_2, &QPushButton::clicked, this, &integration::goEvaluateurs);
    connect(ui->sallesPage_btnParticipants_2, &QPushButton::clicked, this, &integration::goParticipants);
    connect(ui->sallesPage_btnSponsors_2, &QPushButton::clicked, this, &integration::goSponsors);
    connect(ui->sallesPage_btnProjets_2, &QPushButton::clicked, this, &integration::goProjets);
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
QMessageBox, QDialog { background:#111827; color:#E2E8F0; }
QMessageBox QLabel, QDialog QLabel { color:#E2E8F0; }
QMessageBox QPushButton, QDialog QPushButton { background:#4338CA; color:#fff; border:0; border-radius:6px; padding:6px 16px; }
    )");
}

void integration::connecterNavigation()
{
    // ---- Page Employés ----
    if (ui->btnEmployes)    connect(ui->btnEmployes,    &QPushButton::clicked, this, &integration::goEmployes);
    if (ui->btnSalles)      connect(ui->btnSalles,      &QPushButton::clicked, this, &integration::goSalles);
    if (ui->btnEvaluateurs) connect(ui->btnEvaluateurs, &QPushButton::clicked, this, &integration::goEvaluateurs);
    if (ui->btnDashboard)   connect(ui->btnDashboard,   &QPushButton::clicked, this, &integration::goDashboard);
    if (ui->btnParticipants) connect(ui->btnParticipants, &QPushButton::clicked, this, &integration::goParticipants);
    if (ui->btnSponsors)    connect(ui->btnSponsors,    &QPushButton::clicked, this, &integration::goSponsors);
    if (ui->btnProjets)     connect(ui->btnProjets,     &QPushButton::clicked, this, &integration::goProjets);

    // ---- Page Salles (nav latérale) ----
    if (ui->sallesPage_btnEmployes)    connect(ui->sallesPage_btnEmployes,    &QPushButton::clicked, this, &integration::goEmployes);
    if (ui->sallesPage_btnSalles)      connect(ui->sallesPage_btnSalles,      &QPushButton::clicked, this, &integration::goSalles);
    if (ui->sallesPage_btnEvaluateurs) connect(ui->sallesPage_btnEvaluateurs, &QPushButton::clicked, this, &integration::goEvaluateurs);
    if (ui->sallesPage_btnDashboard)   connect(ui->sallesPage_btnDashboard,   &QPushButton::clicked, this, &integration::goDashboard);
    if (ui->sallesPage_btnParticipants) connect(ui->sallesPage_btnParticipants, &QPushButton::clicked, this, &integration::goParticipants);
    if (ui->sallesPage_btnSponsors)    connect(ui->sallesPage_btnSponsors,    &QPushButton::clicked, this, &integration::goSponsors);
    if (ui->sallesPage_btnProjets)     connect(ui->sallesPage_btnProjets,     &QPushButton::clicked, this, &integration::goProjets);

    // ---- Boutons communs ----
    if (ui->btnNotifications) connect(ui->btnNotifications, &QPushButton::clicked, this, &integration::onNotifications);
    if (ui->btnProfil)        connect(ui->btnProfil,        &QPushButton::clicked, this, &integration::onProfil);
    if (ui->btnDeconnexion)   connect(ui->btnDeconnexion,   &QPushButton::clicked, this, &integration::onDeconnexion);
    if (ui->sallesPage_btnNotifications) connect(ui->sallesPage_btnNotifications, &QPushButton::clicked, this, &integration::onNotifications);
    if (ui->sallesPage_btnProfil)        connect(ui->sallesPage_btnProfil,        &QPushButton::clicked, this, &integration::onProfil);
    if (ui->sallesPage_btnDeconnexion)   connect(ui->sallesPage_btnDeconnexion,   &QPushButton::clicked, this, &integration::onDeconnexion);
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

void integration::goLogin()       { allerPage(0); }
void integration::goEmployes()    { allerPage(1); }

// === Les modules autres que « Employés » sont bloqués avec message selon le rôle ===
void integration::goSalles()
{
    if (m_roleConnecte.isEmpty()) return;
    afficherModuleNonDisponible("Gestion des salles");
}
void integration::goEvaluateurs()
{
    if (m_roleConnecte.isEmpty()) return;
    afficherModuleNonDisponible("Gestion des évaluateurs");
}
void integration::goDashboard()
{
    if (m_roleConnecte.isEmpty()) return;
    afficherModuleNonDisponible("Tableau de bord");
}
void integration::goParticipants()
{
    if (m_roleConnecte.isEmpty()) return;
    afficherModuleNonDisponible("Gestion des participants");
}
void integration::goSponsors()
{
    if (m_roleConnecte.isEmpty()) return;
    afficherModuleNonDisponible("Gestion des sponsors");
}
void integration::goProjets()
{
    if (m_roleConnecte.isEmpty()) return;
    afficherModuleNonDisponible("Gestion des projets");
}

// ======================================================================
// === CONNEXION ========================================================
// ======================================================================
void integration::onConnexion()
{
    const QString user = ui->lineEditIdentifiant->text().trimmed();
    const QString pass = ui->lineEditMotDePasse->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Connexion", "Veuillez saisir votre identifiant et votre mot de passe.");
        return;
    }

    // 1) Vérifier d'abord que l'employé existe (indépendamment du statut)
    Employe moi;
    if (!Employe::trouver(user, moi)) {
        QMessageBox::warning(this, "Connexion échouée", "Identifiant ou mot de passe incorrect.");
        return;
    }

    // 2) Refuser si le compte est inactif (message pro)
    if (moi.getStatut() != "Actif") {
        QMessageBox box(this);
        box.setWindowTitle("Compte inactif");
        box.setIcon(QMessageBox::Warning);
        box.setTextFormat(Qt::RichText);
        box.setText(QString(
            "<div style='font-family:Segoe UI, Arial;font-size:13px;color:#E2E8F0;'>"
            "<p style='font-size:15px;font-weight:800;color:#EF4444;margin:0 0 10px 0;'>"
            "⛔ Compte désactivé</p>"
            "<p style='color:#E2E8F0;margin:0 0 8px 0;'>"
            "Votre compte <b>%1</b> est actuellement <b style='color:#EF4444;'>inactif</b>."
            "</p>"
            "<p style='color:#94A3B8;margin:0;'>"
            "L'accès à la plateforme HACKNOVA est <b>suspendu</b>. "
            "Veuillez contacter un Administrateur pour réactiver votre accès."
            "</p>"
            "<p style='color:#64748B;font-size:11px;margin-top:14px;'>"
            "Identifiant : <b>%2</b></p></div>")
            .arg((moi.getPrenom() + " " + moi.getNom()).toHtmlEscaped())
            .arg(user.toHtmlEscaped()));
        box.setStandardButtons(QMessageBox::Ok);
        box.button(QMessageBox::Ok)->setText("Fermer");
        box.exec();
        return;
    }

    // 3) Vérifier le mot de passe
    if (!Employe::authentifier(user, pass)) {
        QMessageBox::warning(this, "Connexion échouée", "Identifiant ou mot de passe incorrect.");
        return;
    }

    // 4) Connexion validée
    m_idConnecte   = moi.getId().trimmed();
    m_roleConnecte = moi.getRole();

    // Tous les boutons de nav restent VISIBLES (demande explicite).
    // Aucun setVisible(false) — le contrôle d'accès se fait au clic.
    ui->btnSalles->setVisible(true);
    ui->btnDashboard->setVisible(true);
    ui->btnEvaluateurs->setVisible(true);
    ui->btnParticipants->setVisible(true);
    ui->btnSponsors->setVisible(true);
    ui->btnProjets->setVisible(true);
    ui->btnNotifications->setVisible(true);
    ui->btnProfil->setVisible(true);
    ui->sallesPage_btnDashboard->setVisible(true);
    ui->sallesPage_btnEmployes->setVisible(true);
    ui->sallesPage_btnEvaluateurs->setVisible(true);
    ui->sallesPage_btnParticipants->setVisible(true);
    ui->sallesPage_btnSponsors->setVisible(true);
    ui->sallesPage_btnProjets->setVisible(true);
    ui->sallesPage_btnNotifications->setVisible(true);
    ui->sallesPage_btnProfil->setVisible(true);

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
        delete m_modelEmp; m_modelEmp = nullptr;
        ui->tableEmployes->setRowCount(0);
        reinitialiserFormulaireEmploye();
        m_idConnecte.clear();
        m_roleConnecte.clear();
        m_rechercheEmp.clear();
        ui->lineEditRechercheEmp->clear();
        dessinerStatistiques();
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
// === MODULE EMPLOYE (inchangé) ========================================
// ======================================================================

void integration::connecterCRUDEmployes()
{
    connect(ui->btnAjouterEmploye,    &QPushButton::clicked, this, &integration::onAjouterEmploye);
    connect(ui->btnAnnulerEmploye,    &QPushButton::clicked, this, &integration::onAnnulerEmploye);
    connect(ui->btnRechercherEmploye, &QPushButton::clicked, this, &integration::onRechercherEmploye);
    connect(ui->btnTrierEmploye,      &QPushButton::clicked, this, &integration::onTrierEmploye);
    connect(ui->btnExporterEmploye,   &QPushButton::clicked, this, &integration::onExporterEmploye);

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

    static const QRegularExpression reLettres("^[\\p{L} '\\-]{0,50}$");
    ui->lineEditEmpNom->setValidator(new QRegularExpressionValidator(reLettres, this));
    ui->lineEditEmpPrenom->setValidator(new QRegularExpressionValidator(reLettres, this));
    ui->lineEditEmpMdp->setMaxLength(50);
    ui->lineEditEmpID->setReadOnly(true);
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

    const bool peutSuppr = Employe::peutSupprimer(m_roleConnecte);
    btnSuppr->setEnabled(peutSuppr);
    if (!peutSuppr) btnSuppr->setToolTip("Réservé à l'administrateur");

    lay->addWidget(btnModif);
    lay->addWidget(btnSuppr);
    lay->addStretch();

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
    remplirTableEmployes();
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
        remplirTableEmployes();
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

void integration::onRechercherEmploye()
{
    m_rechercheEmp = ui->lineEditRechercheEmp->text().trimmed();
    remplirTableEmployes();
}

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

void integration::onTriParColonne(int colonne)
{
    static const QMap<int, QString> colonnes = {{0, "IDEMPLOYE"}, {1, "NOM"}, {2, "PRENOM"}};
    if (!colonnes.contains(colonne)) return;
    m_triEmp = colonnes.value(colonne);
    m_triCroissant = true;
    remplirTableEmployes();
}

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
    QSqlQueryModel *m = m_rechercheEmp.isEmpty() ? Etmp.afficher(m_triEmp, m_triCroissant)
                                                 : Etmp.rechercher(m_rechercheEmp, m_triEmp, m_triCroissant);
    while (m->canFetchMore()) m->fetchMore();

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
        if (ql.contains("employ") || ql.contains("personnel")) {
            reponse = "Pour gérer les employés, ouvrez la page <b>Employés</b> : utilisez <b>Ajouter</b> pour créer une fiche, <b>Modifier</b> ou <b>Supprimer</b> dans la ligne concernée. La recherche filtre pendant la saisie et la liste de tri propose le nom, le prénom et l'ID.";
        } else {
            reponse = "Seule la <b>gestion des employés</b> est actuellement accessible. Les autres modules seront disponibles dans une prochaine mise à jour.";
        }
    }
    else if (ql.contains("combien") && ql.contains("employ")) reponse = QString("Il y a actuellement <b>%1 employés</b> enregistrés.").arg(emps.size());
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
    else reponse = "Je peux répondre sur la gestion des employés. Essayez par exemple : <b>gestion des employés</b> ou <b>combien d'employés</b>.";

    QString html = ui->textChatbot->toHtml();
    html += QString(R"(<div style='color:#E2E8F0;font-family:Segoe UI, Arial;font-size:13px;margin-top:8px;'><p><b style='color:#10B981;'>Vous :</b> %1</p><p><b style='color:#818CF8;'>Bot :</b> %2</p></div>)").arg(q.toHtmlEscaped(), reponse);
    ui->textChatbot->setHtml(html);
    ui->textChatbot->verticalScrollBar()->setValue(ui->textChatbot->verticalScrollBar()->maximum());
    ui->leQuestion->clear();
}

// ======================================================================
// === MODULE SALLE (code conservé, mais UI inaccessible) ===============
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
            if (s.id >= m_nextSalleId) m_nextSalleId = s.id + 1;
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

// ======================================================================
// === MODULE EVALUATEURS (code conservé, UI inaccessible) ==============
// ======================================================================

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
    ui->eval_tableEvaluateurs->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->eval_tableEvaluateurs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->eval_tableEvaluateurs->verticalScrollBar()->setSingleStep(24);

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
    ui->eval_statsChartHost->setGeometry(5, 35, 210, 191);
    m_labelProjetBar = new QLabel(ui->eval_cardStatsEvaluateurs);
    m_labelProjetBar->setObjectName("eval_projetBar");
    m_labelProjetBar->setGeometry(220, 35, 250, 191);
    for (const char *nom : {"eval_lblTotal", "eval_lblActifs", "eval_lblInactifs", "eval_lblRepartition"})
        if (auto *l = ui->eval_cardStatsEvaluateurs->findChild<QLabel*>(nom)) l->hide();

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

void integration::modifierEvaluateur() { ajouterEvaluateur(); }

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

void integration::mettreAJourStatistiques()
{
    int actifs = 0, inactifs = 0;
    QMap<QString, int> projets;
    for (int r = 0; r < m_modelEvaluateurs->rowCount(); ++r) {
        if (m_modelEvaluateurs->item(r, 3)->text() == "Actif") ++actifs; else ++inactifs;
        const QString projet = m_modelEvaluateurs->item(r, 4)->text().trimmed();
        projets[projet.isEmpty() ? QString("Non affecté") : projet]++;
    }

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
        p.drawText(QRect(131, 67, 77, 28), Qt::AlignLeft | Qt::AlignVCenter, QString("Actif %1%").arg(actifPct));
        p.setPen(Qt::NoPen); p.setBrush(QColor(239, 68, 68)); p.drawEllipse(119, 116, 8, 8);
        p.setPen(QColor(226, 232, 240));
        p.drawText(QRect(131, 107, 77, 28), Qt::AlignLeft | Qt::AlignVCenter, QString("Inactif %1%").arg(inactifPct));
        f.setPointSize(8); f.setBold(false); p.setFont(f); p.setPen(QColor(100, 116, 139));
        p.drawText(10, 190, "Répartition par statut");
        p.end(); ui->eval_statsChartHost->setPixmap(pix);
    }
    {
        QPixmap pix(250, 210); pix.fill(Qt::transparent);
        QPainter p(&pix); p.setRenderHint(QPainter::Antialiasing);
        static const QColor palette[] = { QColor(129, 140, 248), QColor(251, 191, 36), QColor(16, 185, 129),
                                         QColor(56, 189, 248), QColor(244, 114, 182), QColor(167, 139, 250) };
        int maxVal = 1; for (int v : projets) if (v > maxVal) maxVal = v;
        const int n = projets.size();
        const int step = n > 0 ? qMin(45, 150 / n) : 45;
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

// ======================================================================
// === MODULES MÉTIERS : désactivés (message pro) =======================
// ======================================================================
void integration::lancerTechChallenge()
{
    QMessageBox::information(this, "Module en préparation",
                             "Le <b>Tech Challenge Analyst</b> sera disponible dans une prochaine mise à jour.");
}

void integration::lancerDeliberation()
{
    QMessageBox::information(this, "Module en préparation",
                             "La <b>Délibération collaborative du jury</b> sera disponible dans une prochaine mise à jour.");
}