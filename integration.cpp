#include "integration.h"
#include "ui_integration.h"

#include <QPushButton>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QColor>
#include <QMessageBox>
#include <QDateTime>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTimer>
#include <QScrollArea>
#include <QScrollBar>
#include <QSet>
#include <QMap>
#include <QFrame>
#include <QResizeEvent>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QMenu>
#include <QAction>
#include <algorithm>

/* ============================================================
 *  CONSTRUCTEUR / DESTRUCTEUR
 * ============================================================ */
integration::integration(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::integration)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    seedDonneesTest();

    ui->chatDisplay->append(
        "<div style='color:#818CF8;font-weight:800;'>NovaBot</div>"
        "<div style='color:#E5E7EB;'>Bonjour. Je suis NovaBot, votre assistant HACKNOVA.<br>"
        "Tapez <b>aide</b> pour voir mes commandes.</div><br>");

    connecterBoutons();
    installerBoutonsScroll();
    rafraichirTout();
    rafraichirStats();

    appliquerTheme();
}

integration::~integration()
{
    delete ui;
}

void integration::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    mettreAJourBoutonsScroll();
}

/* ============================================================
 *  DONNÉES DE TEST
 * ============================================================ */
void integration::seedDonneesTest()
{
    m_employes = {
        {"EMP-001","Benali","Ahmed","pass1","Administrateur","Actif"},
        {"EMP-002","Trabelsi","Sarra","pass2","Responsable RH","Actif"},
        {"EMP-003","Gharbi","Yassine","pass3","Organisateur","Actif"},
        {"EMP-004","Mansouri","Leila","pass4","Administrateur","Inactif"},
        {"EMP-005","Khelifi","Mehdi","pass5","Organisateur","Actif"},
        {"EMP-006","Jebali","Nour","pass6","Responsable RH","Actif"},
        {"EMP-007","Sassi","Karim","pass7","Organisateur","Inactif"},
        {"EMP-008","Bouazizi","Ines","pass8","Administrateur","Actif"}
    };
    m_salles = {
        {"SAL-001","Amphi A",250,"Conférence","Disponible"},
        {"SAL-002","Amphi B",200,"Conférence","Occupée"},
        {"SAL-003","Salle 101",50,"Réunion","Disponible"},
        {"SAL-004","Salle 102",40,"Atelier","Disponible"},
        {"SAL-005","Salle 201",30,"Réunion","Occupée"},
        {"SAL-006","Labo Info 1",60,"Atelier","Disponible"},
        {"SAL-007","Labo Info 2",60,"Atelier","Maintenance"},
        {"SAL-008","Salle VIP",20,"Réunion","Disponible"}
    };
    m_evaluateurs = {
        {"EVL-001","Hamdi","Rania","r.hamdi@esprit.tn","Actif"},
        {"EVL-002","Mejri","Sami","s.mejri@esprit.tn","Actif"},
        {"EVL-003","Chaabane","Amine","a.chaabane@esprit.tn","Actif"},
        {"EVL-004","Ferchichi","Mariem","m.ferchichi@esprit.tn","Inactif"},
        {"EVL-005","Zouari","Hatem","h.zouari@esprit.tn","Actif"},
        {"EVL-006","Ayadi","Salma","s.ayadi@esprit.tn","Actif"},
        {"EVL-007","Krichen","Walid","w.krichen@esprit.tn","Actif"},
        {"EVL-008","Ben Amor","Dorra","d.benamor@esprit.tn","Actif"}
    };
    m_participants = {
        {"PAR-001","Ben Salah","Mohamed","m.bensalah@esprit.tn","+216 20 111 222","Team Alpha"},
        {"PAR-002","Bouaziz","Yasmine","y.bouaziz@esprit.tn","+216 20 333 444","Team Alpha"},
        {"PAR-003","Riahi","Anis","a.riahi@esprit.tn","+216 20 555 666","Team Beta"},
        {"PAR-004","Karoui","Lina","l.karoui@esprit.tn","+216 20 777 888","Team Beta"},
        {"PAR-005","Hammami","Bilel","b.hammami@esprit.tn","+216 20 999 000","Team Gamma"},
        {"PAR-006","Dridi","Syrine","s.dridi@esprit.tn","+216 21 111 333","Team Gamma"},
        {"PAR-007","Nasri","Oussama","o.nasri@esprit.tn","+216 21 222 444","Team Delta"},
        {"PAR-008","Aloui","Farah","f.aloui@esprit.tn","+216 21 333 555","Team Delta"},
        {"PAR-009","Belhaj","Ayoub","a.belhaj@esprit.tn","+216 21 444 666","Team Epsilon"},
        {"PAR-010","Guesmi","Rania","r.guesmi@esprit.tn","+216 21 555 777","Team Epsilon"}
    };
    m_sponsors = {
        {"SPO-001","TechCorp Tunisie","Ali Ben Romdhane","Gold","Actif"},
        {"SPO-002","InnoSoft","Sonia Tlili","Gold","Actif"},
        {"SPO-003","DataPlus","Karim Cherif","Silver","Actif"},
        {"SPO-004","CloudX","Nadia Zaidi","Silver","Actif"},
        {"SPO-005","SmartSys","Hichem Bouzid","Gold","Actif"},
        {"SPO-006","DevHub","Rim Kacem","Bronze","Inactif"},
        {"SPO-007","AlphaTech","Wassim Sfaxi","Bronze","Actif"},
        {"SPO-008","NextGen","Emna Guizani","Silver","Actif"}
    };
    m_projets = {
        {"PRJ-001","SmartCity IA","IA / ML","Terminé","Team Alpha"},
        {"PRJ-002","EduConnect","Web","En cours","Team Beta"},
        {"PRJ-003","MediTrack","Mobile","Terminé","Team Gamma"},
        {"PRJ-004","AgroSense","IoT","En cours","Team Delta"},
        {"PRJ-005","FinBot","IA / ML","En attente","Team Epsilon"},
        {"PRJ-006","GreenRoute","Web","Terminé","Team Alpha"},
        {"PRJ-007","HealthMate","Mobile","En cours","Team Beta"},
        {"PRJ-008","FarmEye","IoT","En attente","Team Gamma"},
        {"PRJ-009","CodeMentor","IA / ML","Terminé","Team Delta"},
        {"PRJ-010","TransitGo","Web","En cours","Team Epsilon"}
    };
}

/* ============================================================
 *  NAVIGATION
 * ============================================================ */
void integration::allerPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);

    QWidget *w = ui->stackedWidget->currentWidget();
    if (auto *sa = w->findChild<QScrollArea*>())
        sa->verticalScrollBar()->setValue(0);

    rafraichirStats();
    mettreAJourBoutonsScroll();
}

/* ============================================================
 *  RAFRAÎCHISSEMENT DES TABLEAUX
 * ============================================================ */
void integration::rafraichirTout()
{
    rafraichirEmployes();
    rafraichirSalles();
    rafraichirEvaluateurs();
    rafraichirParticipants();
    rafraichirSponsors();
    rafraichirProjets();

    auto fit = [](QTableWidget* t) {
        if (!t) return;
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->verticalHeader()->setVisible(false);
        t->setEditTriggers(QAbstractItemView::NoEditTriggers);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->setAlternatingRowColors(true);
    };
    fit(ui->tableWidgetEmployes);
    fit(ui->tableWidgetSalles);
    fit(ui->tableWidgetEvaluateurs);
    fit(ui->tableWidgetParticipants);
    fit(ui->tableWidgetSponsors);
    fit(ui->tableWidgetProjets);
}

void integration::rafraichirEmployes()
{
    auto *t = ui->tableWidgetEmployes;
    t->setRowCount(m_employes.size());
    for (int i = 0; i < m_employes.size(); ++i) {
        const auto &e = m_employes[i];
        t->setItem(i,0,new QTableWidgetItem(e.id));
        t->setItem(i,1,new QTableWidgetItem(e.nom));
        t->setItem(i,2,new QTableWidgetItem(e.prenom));
        t->setItem(i,3,new QTableWidgetItem(e.role));
        auto *st = new QTableWidgetItem(e.statut);
        st->setForeground(e.statut=="Actif" ? QColor("#34D399") : QColor("#F87171"));
        t->setItem(i,4,st);
        t->setItem(i,5,new QTableWidgetItem("Editer / Supprimer"));
    }
}

void integration::rafraichirSalles()
{
    auto *t = ui->tableWidgetSalles;
    t->setRowCount(m_salles.size());
    for (int i = 0; i < m_salles.size(); ++i) {
        const auto &s = m_salles[i];
        t->setItem(i,0,new QTableWidgetItem(s.id));
        t->setItem(i,1,new QTableWidgetItem(s.nom));
        t->setItem(i,2,new QTableWidgetItem(QString::number(s.capacite)));
        t->setItem(i,3,new QTableWidgetItem(s.type));
        auto *d = new QTableWidgetItem(s.dispo);
        if (s.dispo=="Disponible") d->setForeground(QColor("#34D399"));
        else if (s.dispo=="Occupée") d->setForeground(QColor("#FBBF24"));
        else d->setForeground(QColor("#F87171"));
        t->setItem(i,4,d);
        t->setItem(i,5,new QTableWidgetItem("Editer / Supprimer"));
    }
}

void integration::rafraichirEvaluateurs()
{
    auto *t = ui->tableWidgetEvaluateurs;
    t->setRowCount(m_evaluateurs.size());
    for (int i = 0; i < m_evaluateurs.size(); ++i) {
        const auto &e = m_evaluateurs[i];
        t->setItem(i,0,new QTableWidgetItem(e.id));
        t->setItem(i,1,new QTableWidgetItem(e.nom));
        t->setItem(i,2,new QTableWidgetItem(e.prenom));
        t->setItem(i,3,new QTableWidgetItem(e.email));
        auto *st = new QTableWidgetItem(e.statut);
        st->setForeground(e.statut=="Actif" ? QColor("#34D399") : QColor("#F87171"));
        t->setItem(i,4,st);
        t->setItem(i,5,new QTableWidgetItem("Editer / Supprimer"));
    }
}

void integration::rafraichirParticipants()
{
    auto *t = ui->tableWidgetParticipants;
    t->setRowCount(m_participants.size());
    for (int i = 0; i < m_participants.size(); ++i) {
        const auto &p = m_participants[i];
        t->setItem(i,0,new QTableWidgetItem(p.id));
        t->setItem(i,1,new QTableWidgetItem(p.nom));
        t->setItem(i,2,new QTableWidgetItem(p.prenom));
        t->setItem(i,3,new QTableWidgetItem(p.email));
        t->setItem(i,4,new QTableWidgetItem(p.tel));
        t->setItem(i,5,new QTableWidgetItem("CV"));
        t->setItem(i,6,new QTableWidgetItem(p.equipe));
        t->setItem(i,7,new QTableWidgetItem("Editer / Supprimer"));
    }
}

void integration::rafraichirSponsors()
{
    auto *t = ui->tableWidgetSponsors;
    t->setRowCount(m_sponsors.size());
    for (int i = 0; i < m_sponsors.size(); ++i) {
        const auto &s = m_sponsors[i];
        t->setItem(i,0,new QTableWidgetItem(s.id));
        t->setItem(i,1,new QTableWidgetItem(s.entreprise));
        t->setItem(i,2,new QTableWidgetItem(s.contact));
        auto *ty = new QTableWidgetItem(s.type);
        if (s.type=="Gold") ty->setForeground(QColor("#FBBF24"));
        else if (s.type=="Silver") ty->setForeground(QColor("#94A3B8"));
        else ty->setForeground(QColor("#FB923C"));
        t->setItem(i,3,ty);
        auto *st = new QTableWidgetItem(s.statut);
        st->setForeground(s.statut=="Actif" ? QColor("#34D399") : QColor("#F87171"));
        t->setItem(i,4,st);
        t->setItem(i,5,new QTableWidgetItem("Editer / Supprimer"));
    }
}

void integration::rafraichirProjets()
{
    auto *t = ui->tableWidgetProjets;
    t->setRowCount(m_projets.size());
    for (int i = 0; i < m_projets.size(); ++i) {
        const auto &p = m_projets[i];
        t->setItem(i,0,new QTableWidgetItem(p.id));
        t->setItem(i,1,new QTableWidgetItem(p.nom));
        t->setItem(i,2,new QTableWidgetItem(p.categorie));
        auto *st = new QTableWidgetItem(p.statut);
        if (p.statut=="Terminé") st->setForeground(QColor("#34D399"));
        else if (p.statut=="En cours") st->setForeground(QColor("#818CF8"));
        else st->setForeground(QColor("#FBBF24"));
        t->setItem(i,3,st);
        t->setItem(i,4,new QTableWidgetItem(p.equipe));
        t->setItem(i,5,new QTableWidgetItem("Editer / Supprimer"));
    }
}

/* ============================================================
 *  STATISTIQUES
 * ============================================================ */
void integration::rafraichirStats()
{
    ui->cardStatValue->setText(QString::number(m_participants.size()));
    ui->cardStatValue2->setText(QString::number(m_projets.size()));
    ui->cardStatValue3->setText(QString::number(m_salles.size()));
    ui->cardStatValue4->setText(QString::number(m_sponsors.size()));
    ui->chartDonutCenterValue->setText(QString::number(m_projets.size()));

    int actifsEmp = 0, nbAdmin = 0;
    for (const auto &e : m_employes) {
        if (e.statut=="Actif") actifsEmp++;
        if (e.role=="Administrateur") nbAdmin++;
    }
    ui->cardEmpValue1->setText(QString::number(m_employes.size()));
    ui->cardEmpValue2->setText(QString::number(actifsEmp));
    ui->cardEmpValue3->setText(QString::number(nbAdmin));
    ui->cardEmpValue4->setText(QString::number(m_employes.size() - actifsEmp));

    int dispo=0, occ=0, capTot=0;
    for (const auto &s : m_salles) {
        capTot += s.capacite;
        if (s.dispo=="Disponible") dispo++;
        else if (s.dispo=="Occupée") occ++;
    }
    ui->cardSalleValue1->setText(QString::number(m_salles.size()));
    ui->cardSalleValue2->setText(QString::number(dispo));
    ui->cardSalleValue3->setText(QString::number(occ));
    ui->cardSalleValue4->setText(QString::number(capTot));

    int actifsEvl=0, inactifsEvl=0;
    for (const auto &e : m_evaluateurs) {
        if (e.statut=="Actif") actifsEvl++;
        else inactifsEvl++;
    }
    ui->cardEvalValue1->setText(QString::number(m_evaluateurs.size()));
    ui->cardEvalValue2->setText(QString::number(actifsEvl));
    ui->cardEvalValue3->setText(QString::number(inactifsEvl));

    ui->cardPartValue1->setText(QString::number(m_participants.size()));
    ui->cardPartValue2->setText(QString::number(m_participants.size()));
    ui->cardPartValue3->setText(QString::number(m_participants.size()));

    int actifsSpon=0, inactifsSpon=0;
    for (const auto &s : m_sponsors) {
        if (s.statut=="Actif") actifsSpon++;
        else inactifsSpon++;
    }
    ui->cardSponValue1->setText(QString::number(m_sponsors.size()));
    ui->cardSponValue2->setText(QString::number(actifsSpon));
    ui->cardSponValue3->setText(QString::number(inactifsSpon));

    int termines=0, enCours=0, attente=0;
    for (const auto &p : m_projets) {
        if (p.statut=="Terminé") termines++;
        else if (p.statut=="En cours") enCours++;
        else attente++;
    }
    ui->cardProjValue1->setText(QString::number(m_projets.size()));
    ui->cardProjValue2->setText(QString::number(termines));
    ui->cardProjValue3->setText(QString::number(attente));
    ui->cardProjValue4->setText(QString::number(enCours));

    int totPrj = qMax(1, m_projets.size());
    ui->barValue1->setText(QString("%1%").arg(termines*100/totPrj));
    ui->barValue2->setText(QString("%1%").arg(enCours*100/totPrj));
    ui->barValue3->setText(QString("%1%").arg(attente*100/totPrj));
    ui->barValue4->setText("0%");

    int w = 412;
    ui->barHFill1->setFixedWidth(termines * w / totPrj);
    ui->barHFill2->setFixedWidth(enCours * w / totPrj);
    ui->barHFill3->setFixedWidth(attente * w / totPrj);
    ui->barHFill4->setFixedWidth(0);

    int prog = (termines*100 + enCours*50) / totPrj;
    ui->progressBarHackathon->setValue(prog);
    ui->labelProgressNote->setText(QString("Phase 3/5 - Developpement (%1%)").arg(prog));

    QMap<QString,int> eqCount;
    for (const auto &p : m_participants) eqCount[p.equipe]++;
    int maxEq = 1;
    for (int v : eqCount) maxEq = qMax(maxEq, v);

    QList<QLabel*> vValues = {ui->barVValue1, ui->barVValue2, ui->barVValue3,
                               ui->barVValue4, ui->barVValue5, ui->barVValue6};
    QList<QFrame*> vBars   = {ui->barVBar1, ui->barVBar2, ui->barVBar3,
                             ui->barVBar4, ui->barVBar5, ui->barVBar6};
    QList<QLabel*> vLabels = {ui->barVLabel1, ui->barVLabel2, ui->barVLabel3,
                               ui->barVLabel4, ui->barVLabel5, ui->barVLabel6};

    QStringList teamNames = eqCount.keys();
    for (int i = 0; i < 6; ++i) {
        if (i < teamNames.size()) {
            int v = eqCount[teamNames[i]];
            vValues[i]->setText(QString::number(v));
            vLabels[i]->setText(teamNames[i].toUpper().left(5));
            int h = 30 + (v * 200 / maxEq);
            vBars[i]->setGeometry(vBars[i]->x(), 132 + (220 - h), 44, h);
            vBars[i]->show();
            vValues[i]->show();
            vLabels[i]->show();
        } else {
            vValues[i]->hide();
            vBars[i]->hide();
            vLabels[i]->hide();
        }
    }

    ui->labelBarsVFooterLeft->setText(QString("TOTAL : %1 inscriptions").arg(m_participants.size()));
}

/* ============================================================
 *  CONNEXION BOUTONS
 * ============================================================ */
void integration::connecterBoutons()
{
    connect(ui->pushButtonConnexion, &QPushButton::clicked, this, &integration::onConnexion);
    connect(ui->pushButtonCGU, &QPushButton::clicked, this, &integration::onCGU);
    connect(ui->pushButtonPolitique, &QPushButton::clicked, this, &integration::onPolitique);
    connect(ui->pushButtonAPropos, &QPushButton::clicked, this, &integration::onAPropos);

    // Navbar Dashboard
    connect(ui->navEmployesDashboard,     &QPushButton::clicked, this, [this](){ allerPage(2); });
    connect(ui->navSallesDashboard,       &QPushButton::clicked, this, [this](){ allerPage(3); });
    connect(ui->navEvaluateursDashboard,  &QPushButton::clicked, this, [this](){ allerPage(4); });
    connect(ui->navParticipantsDashboard, &QPushButton::clicked, this, [this](){ allerPage(5); });
    connect(ui->navSponsorsDashboard,     &QPushButton::clicked, this, [this](){ allerPage(6); });
    connect(ui->navProjetsDashboard,      &QPushButton::clicked, this, [this](){ allerPage(7); });
    connect(ui->navDeconnexionDashboard,  &QPushButton::clicked, this, &integration::onDeconnexion);
    connect(ui->navProfileDashboard,      &QPushButton::clicked, this, &integration::onProfile);
    connect(ui->navNotifDashboard,        &QPushButton::clicked, this, &integration::onNotifications);

    // Navbar Employés
    connect(ui->navDashboardEmployes,    &QPushButton::clicked, this, [this](){ allerPage(1); });
    connect(ui->navSallesEmployes,       &QPushButton::clicked, this, [this](){ allerPage(3); });
    connect(ui->navEvaluateursEmployes,  &QPushButton::clicked, this, [this](){ allerPage(4); });
    connect(ui->navParticipantsEmployes, &QPushButton::clicked, this, [this](){ allerPage(5); });
    connect(ui->navSponsorsEmployes,     &QPushButton::clicked, this, [this](){ allerPage(6); });
    connect(ui->navProjetsEmployes,      &QPushButton::clicked, this, [this](){ allerPage(7); });
    connect(ui->navDeconnexionEmployes,  &QPushButton::clicked, this, &integration::onDeconnexion);

    // Navbar Salles
    connect(ui->navDashboardSalles,    &QPushButton::clicked, this, [this](){ allerPage(1); });
    connect(ui->navEmployesSalles,     &QPushButton::clicked, this, [this](){ allerPage(2); });
    connect(ui->navEvaluateursSalles,  &QPushButton::clicked, this, [this](){ allerPage(4); });
    connect(ui->navParticipantsSalles, &QPushButton::clicked, this, [this](){ allerPage(5); });
    connect(ui->navSponsorsSalles,     &QPushButton::clicked, this, [this](){ allerPage(6); });
    connect(ui->navProjetsSalles,      &QPushButton::clicked, this, [this](){ allerPage(7); });
    connect(ui->navDeconnexionSalles,  &QPushButton::clicked, this, &integration::onDeconnexion);

    // Navbar Évaluateurs
    connect(ui->navDashboardEvaluateurs,    &QPushButton::clicked, this, [this](){ allerPage(1); });
    connect(ui->navEmployesEvaluateurs,     &QPushButton::clicked, this, [this](){ allerPage(2); });
    connect(ui->navSallesEvaluateurs,       &QPushButton::clicked, this, [this](){ allerPage(3); });
    connect(ui->navParticipantsEvaluateurs, &QPushButton::clicked, this, [this](){ allerPage(5); });
    connect(ui->navSponsorsEvaluateurs,     &QPushButton::clicked, this, [this](){ allerPage(6); });
    connect(ui->navProjetsEvaluateurs,      &QPushButton::clicked, this, [this](){ allerPage(7); });
    connect(ui->navDeconnexionEvaluateurs,  &QPushButton::clicked, this, &integration::onDeconnexion);

    // Navbar Participants
    connect(ui->navDashboardParticipants,   &QPushButton::clicked, this, [this](){ allerPage(1); });
    connect(ui->navEmployesParticipants,    &QPushButton::clicked, this, [this](){ allerPage(2); });
    connect(ui->navSallesParticipants,      &QPushButton::clicked, this, [this](){ allerPage(3); });
    connect(ui->navEvaluateursParticipants, &QPushButton::clicked, this, [this](){ allerPage(4); });
    connect(ui->navSponsorsParticipants,    &QPushButton::clicked, this, [this](){ allerPage(6); });
    connect(ui->navProjetsParticipants,     &QPushButton::clicked, this, [this](){ allerPage(7); });
    connect(ui->navDeconnexionParticipants, &QPushButton::clicked, this, &integration::onDeconnexion);

    // Navbar Sponsors
    connect(ui->navDashboardSponsors,    &QPushButton::clicked, this, [this](){ allerPage(1); });
    connect(ui->navEmployesSponsors,     &QPushButton::clicked, this, [this](){ allerPage(2); });
    connect(ui->navSallesSponsors,       &QPushButton::clicked, this, [this](){ allerPage(3); });
    connect(ui->navEvaluateursSponsors,  &QPushButton::clicked, this, [this](){ allerPage(4); });
    connect(ui->navParticipantsSponsors, &QPushButton::clicked, this, [this](){ allerPage(5); });
    connect(ui->navProjetsSponsors,      &QPushButton::clicked, this, [this](){ allerPage(7); });
    connect(ui->navDeconnexionSponsors,  &QPushButton::clicked, this, &integration::onDeconnexion);

    // Navbar Projets
    connect(ui->navDashboardProjets,    &QPushButton::clicked, this, [this](){ allerPage(1); });
    connect(ui->navEmployesProjets,     &QPushButton::clicked, this, [this](){ allerPage(2); });
    connect(ui->navSallesProjets,       &QPushButton::clicked, this, [this](){ allerPage(3); });
    connect(ui->navEvaluateursProjets,  &QPushButton::clicked, this, [this](){ allerPage(4); });
    connect(ui->navParticipantsProjets, &QPushButton::clicked, this, [this](){ allerPage(5); });
    connect(ui->navSponsorsProjets,     &QPushButton::clicked, this, [this](){ allerPage(6); });
    connect(ui->navDeconnexionProjets,  &QPushButton::clicked, this, &integration::onDeconnexion);

    // CRUD Employés
    connect(ui->btnEmpAjouter,    &QPushButton::clicked, this, &integration::ajouterEmploye);
    connect(ui->btnEmpModifier,   &QPushButton::clicked, this, &integration::modifierEmploye);
    connect(ui->btnEmpSupprimer,  &QPushButton::clicked, this, &integration::supprimerEmploye);
    connect(ui->btnEmpRechercher, &QPushButton::clicked, this, &integration::rechercherEmployes);
    connect(ui->btnEmpTrier,      &QPushButton::clicked, this, &integration::trierEmployes);
    connect(ui->btnEmpConsulter,  &QPushButton::clicked, this, [this](){
        int r = ui->tableWidgetEmployes->currentRow();
        if (r < 0) { toast("Selectionnez une ligne", "warning"); return; }
        const auto &e = m_employes[r];
        toast(QString("%1 %2 - %3").arg(e.prenom, e.nom, e.role), "info");
    });

    // CRUD Salles
    connect(ui->btnSalleAjouter,    &QPushButton::clicked, this, &integration::ajouterSalle);
    connect(ui->btnSalleModifier,   &QPushButton::clicked, this, &integration::modifierSalle);
    connect(ui->btnSalleSupprimer,  &QPushButton::clicked, this, &integration::supprimerSalle);
    connect(ui->btnSalleRechercher, &QPushButton::clicked, this, &integration::rechercherSalles);
    connect(ui->btnSalleTrier,      &QPushButton::clicked, this, &integration::trierSalles);

    // CRUD Évaluateurs
    connect(ui->btnEvalAjouter,    &QPushButton::clicked, this, &integration::ajouterEvaluateur);
    connect(ui->btnEvalModifier,   &QPushButton::clicked, this, &integration::modifierEvaluateur);
    connect(ui->btnEvalSupprimer,  &QPushButton::clicked, this, &integration::supprimerEvaluateur);
    connect(ui->btnEvalRechercher, &QPushButton::clicked, this, &integration::rechercherEvaluateurs);
    connect(ui->btnEvalTrier,      &QPushButton::clicked, this, &integration::trierEvaluateurs);

    // CRUD Participants
    connect(ui->btnPartAjouter,    &QPushButton::clicked, this, &integration::ajouterParticipant);
    connect(ui->btnPartModifier,   &QPushButton::clicked, this, &integration::modifierParticipant);
    connect(ui->btnPartSupprimer,  &QPushButton::clicked, this, &integration::supprimerParticipant);
    connect(ui->btnPartRechercher, &QPushButton::clicked, this, &integration::rechercherParticipants);
    connect(ui->btnPartTrier,      &QPushButton::clicked, this, &integration::trierParticipants);

    // CRUD Sponsors
    connect(ui->btnSponAjouter,    &QPushButton::clicked, this, &integration::ajouterSponsor);
    connect(ui->btnSponModifier,   &QPushButton::clicked, this, &integration::modifierSponsor);
    connect(ui->btnSponSupprimer,  &QPushButton::clicked, this, &integration::supprimerSponsor);
    connect(ui->btnSponRechercher, &QPushButton::clicked, this, &integration::rechercherSponsors);
    connect(ui->btnSponTrier,      &QPushButton::clicked, this, &integration::trierSponsors);

    // CRUD Projets
    connect(ui->btnProjAjouter,    &QPushButton::clicked, this, &integration::ajouterProjet);
    connect(ui->btnProjModifier,   &QPushButton::clicked, this, &integration::modifierProjet);
    connect(ui->btnProjSupprimer,  &QPushButton::clicked, this, &integration::supprimerProjet);
    connect(ui->btnProjRechercher, &QPushButton::clicked, this, &integration::rechercherProjets);
    connect(ui->btnProjTrier,      &QPushButton::clicked, this, &integration::trierProjets);

    // Chatbot
    connect(ui->chatSendBtn, &QPushButton::clicked, this, &integration::onChatSend);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &integration::onChatSend);
    connect(ui->chatQuick1, &QPushButton::clicked, this, &integration::onChatQuick);
    connect(ui->chatQuick2, &QPushButton::clicked, this, &integration::onChatQuick);
    connect(ui->chatQuick3, &QPushButton::clicked, this, &integration::onChatQuick);
    connect(ui->chatQuick4, &QPushButton::clicked, this, &integration::onChatQuick);
}

/* ============================================================
 *  LOGIN & UTILISATEUR
 * ============================================================ */
void integration::onConnexion()
{
    QString user = ui->lineEditIdentifiant->text().trimmed();
    QString pass = ui->lineEditMotDePasse->text();
    if (user.isEmpty() || pass.isEmpty()) {
        toast("Veuillez remplir tous les champs", "warning");
        return;
    }
    m_userName = user;
    ui->labelTopbarUserName->setText(m_userName);
    ui->labelTopbarUserRole->setText(m_userRole);
    ui->labelTopbarAvatar->setText(m_userName.left(2).toUpper());
    toast(QString("Bienvenue %1").arg(user), "success");
    allerPage(1);
}

void integration::onDeconnexion()
{
    if (QMessageBox::question(this, "Déconnexion",
                              "Voulez-vous vraiment vous déconnecter ?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        ui->lineEditIdentifiant->clear();
        ui->lineEditMotDePasse->clear();
        ui->stackedWidget->setCurrentIndex(0);
        toast("Déconnecté", "info");
    }
}

void integration::onProfile()
{
    afficherDialogue("Profil utilisateur",
                     QString(
                         "<h2 style='color:#818CF8;'>%1</h2>"
                         "<p style='color:#94A3B8;'><b>Rôle :</b> %2</p>"
                         "<p style='color:#94A3B8;'><b>Email :</b> %1@hacknova.tn</p>"
                         "<p style='color:#94A3B8;'><b>Statut :</b> <span style='color:#34D399;'>Actif</span></p>"
                         "<p style='color:#94A3B8;'><b>Dernière connexion :</b> %3</p>"
                         "<hr/>"
                         "<p style='color:#64748B;font-size:11px;'>HACKNOVA - Smart Hackathon Management</p>"
                         ).arg(m_userName, m_userRole, QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm")));
}

void integration::onNotifications()
{
    afficherDialogue("Notifications",
                     "<div style='color:#E5E7EB;'>"
                     "<p style='color:#818CF8;font-weight:800;'>Nouvelle inscription</p>"
                     "<p style='color:#94A3B8;font-size:12px;'>Un nouveau participant s'est inscrit il y a 5 min.</p>"
                     "<hr/>"
                     "<p style='color:#818CF8;font-weight:800;'>Projet soumis</p>"
                     "<p style='color:#94A3B8;font-size:12px;'>Le projet 'EduConnect' a été soumis.</p>"
                     "<hr/>"
                     "<p style='color:#FBBF24;font-weight:800;'>Rappel deadline</p>"
                     "<p style='color:#94A3B8;font-size:12px;'>La date limite de soumission est dans 3 jours.</p>"
                     "</div>");
}

void integration::onCGU()
{
    afficherDialogue("Conditions Générales d'Utilisation",
                     "<div style='color:#E5E7EB;'>"
                     "<h3 style='color:#818CF8;'>1. Objet</h3>"
                     "<p>Les présentes conditions régissent l'utilisation de la plateforme HACKNOVA.</p>"
                     "<h3 style='color:#818CF8;'>2. Accès au service</h3>"
                     "<p>L'accès est réservé aux utilisateurs autorisés par l'organisation.</p>"
                     "<h3 style='color:#818CF8;'>3. Données personnelles</h3>"
                     "<p>Les données sont traitées conformément à la réglementation en vigueur.</p>"
                     "<h3 style='color:#818CF8;'>4. Responsabilités</h3>"
                     "<p>L'utilisateur s'engage à ne pas divulguer ses identifiants.</p>"
                     "</div>");
}

void integration::onPolitique()
{
    afficherDialogue("Politique d'utilisation",
                     "<div style='color:#E5E7EB;'>"
                     "<h3 style='color:#818CF8;'>Confidentialité</h3>"
                     "<p>Vos données ne sont jamais partagées avec des tiers.</p>"
                     "<h3 style='color:#818CF8;'>Sécurité</h3>"
                     "<p>Les mots de passe sont chiffrés et les sessions sécurisées.</p>"
                     "<h3 style='color:#818CF8;'>Cookies</h3>"
                     "<p>Aucun cookie de tracking n'est utilisé par la plateforme.</p>"
                     "</div>");
}

void integration::onAPropos()
{
    afficherDialogue("À propos de HACKNOVA",
                     "<div style='color:#E5E7EB;text-align:center;'>"
                     "<h1 style='color:#818CF8;letter-spacing:4px;'>HACKNOVA</h1>"
                     "<p style='color:#94A3B8;'>Smart Hackathon Management</p>"
                     "<hr/>"
                     "<p><b>Version :</b> 1.0.0</p>"
                     "<p><b>Groupe :</b> EL FALLEGA</p>"
                     "<p><b>Établissement :</b> Esprit School of Engineering</p>"
                     "<hr/>"
                     "<p style='color:#64748B;font-size:11px;'>© 2025 HACKNOVA. Tous droits réservés.</p>"
                     "</div>");
}

/* ============================================================
 *  CHATBOT
 * ============================================================ */
void integration::onChatQuick()
{
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    ui->chatInput->setText(btn->text());
    onChatSend();
}

void integration::onChatSend()
{
    QString msg = ui->chatInput->text().trimmed();
    if (msg.isEmpty()) return;

    ui->chatDisplay->append(QString(
                                "<div style='color:#818CF8;font-weight:800;'>Vous</div>"
                                "<div style='color:#E5E7EB;'>%1</div><br>").arg(msg.toHtmlEscaped()));
    ui->chatInput->clear();

    QString q = msg.toLower();
    QString rep;

    if (q.contains("bonjour") || q.contains("salut") || q.contains("hello"))
        rep = "Bonjour. Comment puis-je vous aider ?";
    else if (q.contains("aide") || q.contains("help"))
        rep = "Commandes :<br>- <b>stats</b> : statistiques globales<br>"
              "- <b>participants</b> : nombre d'inscrits<br>"
              "- <b>projets</b> : état des projets<br>"
              "- <b>sponsors</b> : partenaires<br>"
              "- <b>salles</b> : disponibilités";
    else if (q.contains("stats") || q.contains("statistique"))
        rep = QString("Employes : %1<br>Salles : %2<br>Participants : %3<br>"
                      "Sponsors : %4<br>Projets : %5")
                  .arg(m_employes.size()).arg(m_salles.size())
                  .arg(m_participants.size()).arg(m_sponsors.size()).arg(m_projets.size());
    else if (q.contains("participant")) {
        QSet<QString> eq;
        for (const auto &p : m_participants) eq.insert(p.equipe);
        rep = QString("%1 participants inscrits dans %2 equipes.")
                  .arg(m_participants.size()).arg(eq.size());
    }
    else if (q.contains("projet")) {
        int t = 0, e = 0, a = 0;
        for (const auto &p : m_projets) {
            if (p.statut == "Terminé") t++;
            else if (p.statut == "En cours") e++;
            else a++;
        }
        rep = QString("%1 projets : %2 termines, %3 en cours, %4 en attente.")
                  .arg(m_projets.size()).arg(t).arg(e).arg(a);
    }
    else if (q.contains("sponsor"))
        rep = QString("%1 sponsors actifs.").arg(m_sponsors.size());
    else if (q.contains("salle")) {
        int d = 0;
        for (const auto &s : m_salles) if (s.dispo == "Disponible") d++;
        rep = QString("%1 salles au total, dont %2 disponibles.").arg(m_salles.size()).arg(d);
    }
    else if (q.contains("employe") || q.contains("employé"))
        rep = QString("%1 employes enregistres.").arg(m_employes.size());
    else if (q.contains("merci"))
        rep = "Avec plaisir.";
    else
        rep = "Je n'ai pas compris. Tapez <b>aide</b> pour voir mes commandes.";

    QTimer::singleShot(350, this, [this, rep]() {
        ui->chatDisplay->append(QString(
                                    "<div style='color:#818CF8;font-weight:800;'>NovaBot</div>"
                                    "<div style='color:#E5E7EB;'>%1</div><br>").arg(rep));
        ui->chatDisplay->verticalScrollBar()->setValue(
            ui->chatDisplay->verticalScrollBar()->maximum());
    });
}

/* ============================================================
 *  CRUD EMPLOYÉS
 * ============================================================ */
void integration::ajouterEmploye()
{
    QString nom = ui->lineEditEmpNom->text().trimmed();
    QString pre = ui->lineEditEmpPrenom->text().trimmed();
    if (nom.isEmpty() || pre.isEmpty()) { toast("Nom et prenom obligatoires", "warning"); return; }
    Employe e;
    e.id = nextId("EMP", m_employes.size());
    e.nom = nom; e.prenom = pre;
    e.mdp = ui->lineEditEmpMdp->text();
    e.role = ui->comboBoxEmpRole->currentText();
    e.statut = ui->comboBoxEmpStatut->currentText();
    m_employes.append(e);
    rafraichirEmployes(); rafraichirStats();
    toast(QString("Employe '%1 %2' ajoute").arg(pre, nom), "success");
    ui->lineEditEmpNom->clear(); ui->lineEditEmpPrenom->clear(); ui->lineEditEmpMdp->clear();
}

void integration::modifierEmploye()
{
    int r = ui->tableWidgetEmployes->currentRow();
    if (r < 0) { toast("Selectionnez un employe", "warning"); return; }
    auto &e = m_employes[r];
    if (!ui->lineEditEmpNom->text().isEmpty())    e.nom = ui->lineEditEmpNom->text();
    if (!ui->lineEditEmpPrenom->text().isEmpty()) e.prenom = ui->lineEditEmpPrenom->text();
    if (!ui->lineEditEmpMdp->text().isEmpty())    e.mdp = ui->lineEditEmpMdp->text();
    e.role = ui->comboBoxEmpRole->currentText();
    e.statut = ui->comboBoxEmpStatut->currentText();
    rafraichirEmployes(); rafraichirStats();
    toast("Employe modifie", "success");
}

void integration::supprimerEmploye()
{
    int r = ui->tableWidgetEmployes->currentRow();
    if (r < 0) { toast("Selectionnez un employe", "warning"); return; }
    if (QMessageBox::question(this, "Confirmation",
                              QString("Supprimer %1 %2 ?").arg(m_employes[r].prenom, m_employes[r].nom))
        != QMessageBox::Yes) return;
    m_employes.removeAt(r);
    rafraichirEmployes(); rafraichirStats();
    toast("Employe supprime", "success");
}

void integration::rechercherEmployes()
{
    QString q = ui->lineEditRechercheEmployes->text().trimmed().toLower();
    if (q.isEmpty()) { rafraichirEmployes(); return; }
    auto *t = ui->tableWidgetEmployes;
    for (int i = 0; i < t->rowCount(); ++i)
        t->setRowHidden(i, !t->item(i,1)->text().toLower().contains(q)
                               && !t->item(i,2)->text().toLower().contains(q));
    toast(QString("Recherche : '%1'").arg(q), "info");
}

void integration::trierEmployes()
{
    std::sort(m_employes.begin(), m_employes.end(),
              [](const Employe &a, const Employe &b){ return a.nom < b.nom; });
    rafraichirEmployes();
    toast("Trie par nom", "info");
}

/* ============================================================
 *  CRUD SALLES
 * ============================================================ */
void integration::ajouterSalle()
{
    QString nom = ui->lineEditSalleNom->text().trimmed();
    if (nom.isEmpty()) { toast("Nom obligatoire", "warning"); return; }
    Salle s;
    s.id = nextId("SAL", m_salles.size());
    s.nom = nom;
    s.capacite = ui->spinBoxSalleCapacite->value();
    s.type = ui->comboBoxSalleType->currentText();
    s.dispo = ui->comboBoxSalleDispo->currentText();
    m_salles.append(s);
    rafraichirSalles(); rafraichirStats();
    toast(QString("Salle '%1' ajoutee").arg(nom), "success");
    ui->lineEditSalleNom->clear();
}

void integration::modifierSalle()
{
    int r = ui->tableWidgetSalles->currentRow();
    if (r < 0) { toast("Selectionnez une salle", "warning"); return; }
    auto &s = m_salles[r];
    if (!ui->lineEditSalleNom->text().isEmpty()) s.nom = ui->lineEditSalleNom->text();
    s.capacite = ui->spinBoxSalleCapacite->value();
    s.type = ui->comboBoxSalleType->currentText();
    s.dispo = ui->comboBoxSalleDispo->currentText();
    rafraichirSalles(); rafraichirStats();
    toast("Salle modifiee", "success");
}

void integration::supprimerSalle()
{
    int r = ui->tableWidgetSalles->currentRow();
    if (r < 0) { toast("Selectionnez une salle", "warning"); return; }
    if (QMessageBox::question(this, "Confirmation",
                              QString("Supprimer '%1' ?").arg(m_salles[r].nom)) != QMessageBox::Yes) return;
    m_salles.removeAt(r);
    rafraichirSalles(); rafraichirStats();
    toast("Salle supprimee", "success");
}

void integration::rechercherSalles()
{
    QString q = ui->lineEditRechercheSalle->text().trimmed().toLower();
    if (q.isEmpty()) { rafraichirSalles(); return; }
    auto *t = ui->tableWidgetSalles;
    for (int i = 0; i < t->rowCount(); ++i)
        t->setRowHidden(i, !t->item(i,1)->text().toLower().contains(q));
    toast(QString("Recherche : '%1'").arg(q), "info");
}

void integration::trierSalles()
{
    std::sort(m_salles.begin(), m_salles.end(),
              [](const Salle &a, const Salle &b){ return a.nom < b.nom; });
    rafraichirSalles();
    toast("Trie par nom", "info");
}

/* ============================================================
 *  CRUD ÉVALUATEURS
 * ============================================================ */
void integration::ajouterEvaluateur()
{
    QString nom = ui->lineEditEvalNom->text().trimmed();
    QString pre = ui->lineEditEvalPrenom->text().trimmed();
    if (nom.isEmpty() || pre.isEmpty()) { toast("Nom et prenom obligatoires", "warning"); return; }
    Evaluateur e;
    e.id = nextId("EVL", m_evaluateurs.size());
    e.nom = nom; e.prenom = pre;
    e.email = ui->lineEditEvalEmail->text();
    e.statut = ui->comboBoxEvalStatut->currentText();
    m_evaluateurs.append(e);
    rafraichirEvaluateurs(); rafraichirStats();
    toast(QString("Evaluateur '%1 %2' ajoute").arg(pre, nom), "success");
    ui->lineEditEvalNom->clear(); ui->lineEditEvalPrenom->clear(); ui->lineEditEvalEmail->clear();
}

void integration::modifierEvaluateur()
{
    int r = ui->tableWidgetEvaluateurs->currentRow();
    if (r < 0) { toast("Selectionnez un evaluateur", "warning"); return; }
    auto &e = m_evaluateurs[r];
    if (!ui->lineEditEvalNom->text().isEmpty())    e.nom = ui->lineEditEvalNom->text();
    if (!ui->lineEditEvalPrenom->text().isEmpty()) e.prenom = ui->lineEditEvalPrenom->text();
    if (!ui->lineEditEvalEmail->text().isEmpty())  e.email = ui->lineEditEvalEmail->text();
    e.statut = ui->comboBoxEvalStatut->currentText();
    rafraichirEvaluateurs(); rafraichirStats();
    toast("Evaluateur modifie", "success");
}

void integration::supprimerEvaluateur()
{
    int r = ui->tableWidgetEvaluateurs->currentRow();
    if (r < 0) { toast("Selectionnez un evaluateur", "warning"); return; }
    if (QMessageBox::question(this, "Confirmation",
                              QString("Supprimer %1 %2 ?").arg(m_evaluateurs[r].prenom, m_evaluateurs[r].nom))
        != QMessageBox::Yes) return;
    m_evaluateurs.removeAt(r);
    rafraichirEvaluateurs(); rafraichirStats();
    toast("Evaluateur supprime", "success");
}

void integration::rechercherEvaluateurs()
{
    QString q = ui->lineEditRechercheEval->text().trimmed().toLower();
    if (q.isEmpty()) { rafraichirEvaluateurs(); return; }
    auto *t = ui->tableWidgetEvaluateurs;
    for (int i = 0; i < t->rowCount(); ++i)
        t->setRowHidden(i, !t->item(i,1)->text().toLower().contains(q)
                               && !t->item(i,2)->text().toLower().contains(q));
    toast(QString("Recherche : '%1'").arg(q), "info");
}

void integration::trierEvaluateurs()
{
    std::sort(m_evaluateurs.begin(), m_evaluateurs.end(),
              [](const Evaluateur &a, const Evaluateur &b){ return a.nom < b.nom; });
    rafraichirEvaluateurs();
    toast("Trie par nom", "info");
}

/* ============================================================
 *  CRUD PARTICIPANTS
 * ============================================================ */
void integration::ajouterParticipant()
{
    QString nom = ui->lineEditPartNom->text().trimmed();
    QString pre = ui->lineEditPartPrenom->text().trimmed();
    if (nom.isEmpty() || pre.isEmpty()) { toast("Nom et prenom obligatoires", "warning"); return; }
    Participant p;
    p.id = nextId("PAR", m_participants.size());
    p.nom = nom; p.prenom = pre;
    p.email = ui->lineEditPartEmail->text();
    p.tel = ui->lineEditPartTel->text();
    p.equipe = ui->lineEditPartEquipe->text();
    m_participants.append(p);
    rafraichirParticipants(); rafraichirStats();
    toast(QString("Participant '%1 %2' ajoute").arg(pre, nom), "success");
    ui->lineEditPartNom->clear(); ui->lineEditPartPrenom->clear();
    ui->lineEditPartEmail->clear(); ui->lineEditPartTel->clear(); ui->lineEditPartEquipe->clear();
}

void integration::modifierParticipant()
{
    int r = ui->tableWidgetParticipants->currentRow();
    if (r < 0) { toast("Selectionnez un participant", "warning"); return; }
    auto &p = m_participants[r];
    if (!ui->lineEditPartNom->text().isEmpty())    p.nom = ui->lineEditPartNom->text();
    if (!ui->lineEditPartPrenom->text().isEmpty()) p.prenom = ui->lineEditPartPrenom->text();
    if (!ui->lineEditPartEmail->text().isEmpty())  p.email = ui->lineEditPartEmail->text();
    if (!ui->lineEditPartTel->text().isEmpty())    p.tel = ui->lineEditPartTel->text();
    if (!ui->lineEditPartEquipe->text().isEmpty()) p.equipe = ui->lineEditPartEquipe->text();
    rafraichirParticipants(); rafraichirStats();
    toast("Participant modifie", "success");
}

void integration::supprimerParticipant()
{
    int r = ui->tableWidgetParticipants->currentRow();
    if (r < 0) { toast("Selectionnez un participant", "warning"); return; }
    if (QMessageBox::question(this, "Confirmation",
                              QString("Supprimer %1 %2 ?").arg(m_participants[r].prenom, m_participants[r].nom))
        != QMessageBox::Yes) return;
    m_participants.removeAt(r);
    rafraichirParticipants(); rafraichirStats();
    toast("Participant supprime", "success");
}

void integration::rechercherParticipants()
{
    QString q = ui->lineEditRecherchePart->text().trimmed().toLower();
    if (q.isEmpty()) { rafraichirParticipants(); return; }
    auto *t = ui->tableWidgetParticipants;
    for (int i = 0; i < t->rowCount(); ++i)
        t->setRowHidden(i, !t->item(i,1)->text().toLower().contains(q)
                               && !t->item(i,2)->text().toLower().contains(q)
                               && !t->item(i,6)->text().toLower().contains(q));
    toast(QString("Recherche : '%1'").arg(q), "info");
}

void integration::trierParticipants()
{
    std::sort(m_participants.begin(), m_participants.end(),
              [](const Participant &a, const Participant &b){ return a.nom < b.nom; });
    rafraichirParticipants();
    toast("Trie par nom", "info");
}

/* ============================================================
 *  CRUD SPONSORS
 * ============================================================ */
void integration::ajouterSponsor()
{
    QString ent = ui->lineEditSponEntreprise->text().trimmed();
    if (ent.isEmpty()) { toast("Nom entreprise obligatoire", "warning"); return; }
    Sponsor s;
    s.id = nextId("SPO", m_sponsors.size());
    s.entreprise = ent;
    s.contact = ui->lineEditSponContact->text();
    s.type = ui->comboBoxSponType->currentText();
    s.statut = ui->comboBoxSponStatut->currentText();
    m_sponsors.append(s);
    rafraichirSponsors(); rafraichirStats();
    toast(QString("Sponsor '%1' ajoute").arg(ent), "success");
    ui->lineEditSponEntreprise->clear(); ui->lineEditSponContact->clear();
}

void integration::modifierSponsor()
{
    int r = ui->tableWidgetSponsors->currentRow();
    if (r < 0) { toast("Selectionnez un sponsor", "warning"); return; }
    auto &s = m_sponsors[r];
    if (!ui->lineEditSponEntreprise->text().isEmpty()) s.entreprise = ui->lineEditSponEntreprise->text();
    if (!ui->lineEditSponContact->text().isEmpty())    s.contact = ui->lineEditSponContact->text();
    s.type = ui->comboBoxSponType->currentText();
    s.statut = ui->comboBoxSponStatut->currentText();
    rafraichirSponsors(); rafraichirStats();
    toast("Sponsor modifie", "success");
}

void integration::supprimerSponsor()
{
    int r = ui->tableWidgetSponsors->currentRow();
    if (r < 0) { toast("Selectionnez un sponsor", "warning"); return; }
    if (QMessageBox::question(this, "Confirmation",
                              QString("Supprimer '%1' ?").arg(m_sponsors[r].entreprise)) != QMessageBox::Yes) return;
    m_sponsors.removeAt(r);
    rafraichirSponsors(); rafraichirStats();
    toast("Sponsor supprime", "success");
}

void integration::rechercherSponsors()
{
    QString q = ui->lineEditRechercheSpon->text().trimmed().toLower();
    if (q.isEmpty()) { rafraichirSponsors(); return; }
    auto *t = ui->tableWidgetSponsors;
    for (int i = 0; i < t->rowCount(); ++i)
        t->setRowHidden(i, !t->item(i,1)->text().toLower().contains(q));
    toast(QString("Recherche : '%1'").arg(q), "info");
}

void integration::trierSponsors()
{
    std::sort(m_sponsors.begin(), m_sponsors.end(),
              [](const Sponsor &a, const Sponsor &b){ return a.entreprise < b.entreprise; });
    rafraichirSponsors();
    toast("Trie par entreprise", "info");
}

/* ============================================================
 *  CRUD PROJETS
 * ============================================================ */
void integration::ajouterProjet()
{
    QString nom = ui->lineEditProjNom->text().trimmed();
    if (nom.isEmpty()) { toast("Nom obligatoire", "warning"); return; }
    Projet p;
    p.id = nextId("PRJ", m_projets.size());
    p.nom = nom;
    p.categorie = ui->comboBoxProjCategorie->currentText();
    p.statut = ui->comboBoxProjStatut->currentText();
    p.equipe = ui->lineEditProjEquipe->text();
    m_projets.append(p);
    rafraichirProjets(); rafraichirStats();
    toast(QString("Projet '%1' ajoute").arg(nom), "success");
    ui->lineEditProjNom->clear(); ui->lineEditProjEquipe->clear();
}

void integration::modifierProjet()
{
    int r = ui->tableWidgetProjets->currentRow();
    if (r < 0) { toast("Selectionnez un projet", "warning"); return; }
    auto &p = m_projets[r];
    if (!ui->lineEditProjNom->text().isEmpty())    p.nom = ui->lineEditProjNom->text();
    if (!ui->lineEditProjEquipe->text().isEmpty()) p.equipe = ui->lineEditProjEquipe->text();
    p.categorie = ui->comboBoxProjCategorie->currentText();
    p.statut = ui->comboBoxProjStatut->currentText();
    rafraichirProjets(); rafraichirStats();
    toast("Projet modifie", "success");
}

void integration::supprimerProjet()
{
    int r = ui->tableWidgetProjets->currentRow();
    if (r < 0) { toast("Selectionnez un projet", "warning"); return; }
    if (QMessageBox::question(this, "Confirmation",
                              QString("Supprimer '%1' ?").arg(m_projets[r].nom)) != QMessageBox::Yes) return;
    m_projets.removeAt(r);
    rafraichirProjets(); rafraichirStats();
    toast("Projet supprime", "success");
}

void integration::rechercherProjets()
{
    QString q = ui->lineEditRechercheProj->text().trimmed().toLower();
    if (q.isEmpty()) { rafraichirProjets(); return; }
    auto *t = ui->tableWidgetProjets;
    for (int i = 0; i < t->rowCount(); ++i)
        t->setRowHidden(i, !t->item(i,1)->text().toLower().contains(q)
                               && !t->item(i,2)->text().toLower().contains(q));
    toast(QString("Recherche : '%1'").arg(q), "info");
}

void integration::trierProjets()
{
    std::sort(m_projets.begin(), m_projets.end(),
              [](const Projet &a, const Projet &b){ return a.nom < b.nom; });
    rafraichirProjets();
    toast("Trie par nom", "info");
}

/* ============================================================
 *  THÈME DARK MODE ULTRA-MODERNE
 * ============================================================ */
void integration::appliquerTheme()
{
    this->setStyleSheet(R"(
/* ============================================================
   HACKNOVA DARK MODE — Palette
   Fond profond     #0B1020
   Surface          #111827
   Surface élevée   #1F2937
   Bordure          #1F2937 / #374151
   Texte principal  #E5E7EB
   Texte secondaire #94A3B8
   Accent indigo    #6366F1
   Accent clair     #818CF8
   Succès           #34D399
   Danger           #F87171
   Warning          #FBBF24
   ============================================================ */

QMainWindow, QWidget#centralWidget {
    background-color: #0B1020;
    font-family: "Arial";
    color: #E5E7EB;
}
QWidget { background-color: transparent; color: #E5E7EB; }

QToolTip {
    background-color: #1F2937; color: #E5E7EB;
    border: 1px solid #6366F1; padding: 6px 10px;
    border-radius: 6px; font-size: 11px;
}

/* ===================== SCROLL ===================== */
QScrollArea { background-color: #0B1020; border: none; }
QScrollArea > QWidget > QWidget { background-color: #0B1020; }
QScrollBar:vertical {
    background: #111827; width: 10px; border-radius: 5px; margin: 0;
}
QScrollBar::handle:vertical {
    background: #374151; border-radius: 5px; min-height: 30px;
}
QScrollBar::handle:vertical:hover { background: #6366F1; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
QScrollBar:horizontal {
    background: #111827; height: 10px; border-radius: 5px; margin: 0;
}
QScrollBar::handle:horizontal {
    background: #374151; border-radius: 5px; min-width: 30px;
}
QScrollBar::handle:horizontal:hover { background: #6366F1; }
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }

/* ===================== NAVBAR ===================== */
QFrame#frameNavbar, QFrame#frameNavbarEmployes, QFrame#frameNavbarSalles,
QFrame#frameNavbarEvaluateurs, QFrame#frameNavbarParticipants,
QFrame#frameNavbarSponsors, QFrame#frameNavbarProjets {
    background-color: #111827;
    border: none;
    border-bottom: 1px solid #1F2937;
}
QLabel#labelNavLogo, QLabel#labelNavLogoEmp, QLabel#labelNavLogoSalles,
QLabel#sbLogoEval, QLabel#sbLogoPart, QLabel#sbLogoSpon, QLabel#sbLogoProj {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #6366F1, stop:1 #8B5CF6);
    color: #FFFFFF; font-size: 17px; font-weight: 900;
    letter-spacing: 1px; border-radius: 12px;
    qproperty-alignment: AlignCenter;
}
QLabel#labelNavBrand, QLabel#labelNavBrandEmp, QLabel#labelNavBrandSalles,
QLabel#sbBrandEval, QLabel#sbBrandPart, QLabel#sbBrandSpon, QLabel#sbBrandProj {
    color: #FFFFFF; font-size: 19px; font-weight: 900; letter-spacing: 3px;
}
QLabel#labelNavSub, QLabel#labelNavSubEmp, QLabel#labelNavSubSalles,
QLabel#sbSubEval, QLabel#sbSubPart, QLabel#sbSubSpon, QLabel#sbSubProj {
    color: #818CF8; font-size: 9px; font-weight: 700; letter-spacing: 2px;
}
QFrame#frameNavSeparator, QFrame#frameNavSepEmp, QFrame#frameNavSepSalles,
QFrame#sbSepEval, QFrame#sbSepPart, QFrame#sbSepSpon, QFrame#sbSepProj {
    background-color: #1F2937; border: none;
}

QPushButton#navDashboardDashboard, QPushButton#navEmployesDashboard,
QPushButton#navSallesDashboard, QPushButton#navEvaluateursDashboard,
QPushButton#navParticipantsDashboard, QPushButton#navSponsorsDashboard,
QPushButton#navProjetsDashboard,
QPushButton#navDashboardEmployes, QPushButton#navEmployesEmployes,
QPushButton#navSallesEmployes, QPushButton#navEvaluateursEmployes,
QPushButton#navParticipantsEmployes, QPushButton#navSponsorsEmployes,
QPushButton#navProjetsEmployes,
QPushButton#navDashboardSalles, QPushButton#navEmployesSalles,
QPushButton#navSallesSalles, QPushButton#navEvaluateursSalles,
QPushButton#navParticipantsSalles, QPushButton#navSponsorsSalles,
QPushButton#navProjetsSalles,
QPushButton#navDashboardEvaluateurs, QPushButton#navEmployesEvaluateurs,
QPushButton#navSallesEvaluateurs, QPushButton#navEvaluateursEvaluateurs,
QPushButton#navParticipantsEvaluateurs, QPushButton#navSponsorsEvaluateurs,
QPushButton#navProjetsEvaluateurs,
QPushButton#navDashboardParticipants, QPushButton#navEmployesParticipants,
QPushButton#navSallesParticipants, QPushButton#navEvaluateursParticipants,
QPushButton#navParticipantsParticipants, QPushButton#navSponsorsParticipants,
QPushButton#navProjetsParticipants,
QPushButton#navDashboardSponsors, QPushButton#navEmployesSponsors,
QPushButton#navSallesSponsors, QPushButton#navEvaluateursSponsors,
QPushButton#navParticipantsSponsors, QPushButton#navSponsorsSponsors,
QPushButton#navProjetsSponsors,
QPushButton#navDashboardProjets, QPushButton#navEmployesProjets,
QPushButton#navSallesProjets, QPushButton#navEvaluateursProjets,
QPushButton#navParticipantsProjets, QPushButton#navSponsorsProjets,
QPushButton#navProjetsProjets {
    background: transparent; color: #94A3B8;
    font-size: 12px; font-weight: 800; letter-spacing: 0.5px;
    border: none; border-bottom: 3px solid transparent;
    padding: 14px 16px;
}
QPushButton#navDashboardDashboard:hover, QPushButton#navEmployesDashboard:hover,
QPushButton#navSallesDashboard:hover, QPushButton#navEvaluateursDashboard:hover,
QPushButton#navParticipantsDashboard:hover, QPushButton#navSponsorsDashboard:hover,
QPushButton#navProjetsDashboard:hover,
QPushButton#navDashboardEmployes:hover, QPushButton#navEmployesEmployes:hover,
QPushButton#navSallesEmployes:hover, QPushButton#navEvaluateursEmployes:hover,
QPushButton#navParticipantsEmployes:hover, QPushButton#navSponsorsEmployes:hover,
QPushButton#navProjetsEmployes:hover,
QPushButton#navDashboardSalles:hover, QPushButton#navEmployesSalles:hover,
QPushButton#navSallesSalles:hover, QPushButton#navEvaluateursSalles:hover,
QPushButton#navParticipantsSalles:hover, QPushButton#navSponsorsSalles:hover,
QPushButton#navProjetsSalles:hover,
QPushButton#navDashboardEvaluateurs:hover, QPushButton#navEmployesEvaluateurs:hover,
QPushButton#navSallesEvaluateurs:hover, QPushButton#navEvaluateursEvaluateurs:hover,
QPushButton#navParticipantsEvaluateurs:hover, QPushButton#navSponsorsEvaluateurs:hover,
QPushButton#navProjetsEvaluateurs:hover,
QPushButton#navDashboardParticipants:hover, QPushButton#navEmployesParticipants:hover,
QPushButton#navSallesParticipants:hover, QPushButton#navEvaluateursParticipants:hover,
QPushButton#navParticipantsParticipants:hover, QPushButton#navSponsorsParticipants:hover,
QPushButton#navProjetsParticipants:hover,
QPushButton#navDashboardSponsors:hover, QPushButton#navEmployesSponsors:hover,
QPushButton#navSallesSponsors:hover, QPushButton#navEvaluateursSponsors:hover,
QPushButton#navParticipantsSponsors:hover, QPushButton#navSponsorsSponsors:hover,
QPushButton#navProjetsSponsors:hover,
QPushButton#navDashboardProjets:hover, QPushButton#navEmployesProjets:hover,
QPushButton#navSallesProjets:hover, QPushButton#navEvaluateursProjets:hover,
QPushButton#navParticipantsProjets:hover, QPushButton#navSponsorsProjets:hover,
QPushButton#navProjetsProjets:hover {
    color: #FFFFFF; background-color: #1F2937;
    border-bottom: 3px solid #6366F1;
}

QPushButton#navDeconnexionDashboard, QPushButton#navDeconnexionEmployes,
QPushButton#navDeconnexionSalles, QPushButton#navDeconnexionEvaluateurs,
QPushButton#navDeconnexionParticipants, QPushButton#navDeconnexionSponsors,
QPushButton#navDeconnexionProjets {
    background-color: transparent; color: #F87171;
    font-size: 12px; font-weight: 800; letter-spacing: 0.5px;
    border: 1px solid #7F1D1D; border-radius: 8px; padding: 8px 16px;
}
QPushButton#navDeconnexionDashboard:hover, QPushButton#navDeconnexionEmployes:hover,
QPushButton#navDeconnexionSalles:hover, QPushButton#navDeconnexionEvaluateurs:hover,
QPushButton#navDeconnexionParticipants:hover, QPushButton#navDeconnexionSponsors:hover,
QPushButton#navDeconnexionProjets:hover {
    background-color: #B91C1C; color: #FFFFFF; border: 1px solid #B91C1C;
}

QPushButton#navProfileDashboard, QPushButton#navNotifDashboard {
    background-color: #1F2937; color: #E5E7EB;
    border: 1px solid #374151; border-radius: 8px;
    padding: 8px 14px; font-size: 12px; font-weight: 700;
}
QPushButton#navProfileDashboard:hover, QPushButton#navNotifDashboard:hover {
    background-color: #6366F1; border: 1px solid #6366F1; color: #FFFFFF;
}

/* ===================== TOPBAR ===================== */
QFrame#frameTopbar, QFrame#frameTopbarEmployes, QFrame#frameTopbarSalles,
QFrame#frameTopbarEvaluateurs, QFrame#frameTopbarParticipants,
QFrame#frameTopbarSponsors, QFrame#frameTopbarProjets {
    background-color: #111827; border: none;
    border-bottom: 1px solid #1F2937;
}
QLabel#labelTopbarTitle, QLabel#topbarTitleEmp, QLabel#topbarTitleSalles,
QLabel#topbarTitleEval, QLabel#topbarTitlePart, QLabel#topbarTitleSpon,
QLabel#topbarTitleProj {
    color: #FFFFFF; font-size: 22px; font-weight: 900; letter-spacing: 0.3px;
}
QLabel#labelTopbarSub, QLabel#topbarSubEmp, QLabel#topbarSubSalles,
QLabel#topbarSubEval, QLabel#topbarSubPart, QLabel#topbarSubSpon,
QLabel#topbarSubProj {
    color: #94A3B8; font-size: 13px;
}
QLabel#labelTopbarAvatar {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #6366F1, stop:1 #8B5CF6);
    color: #FFFFFF; font-size: 13px; font-weight: 900;
    border-radius: 20px; qproperty-alignment: AlignCenter;
}
QLabel#labelTopbarUserName { color: #FFFFFF; font-size: 12px; font-weight: 800; }
QLabel#labelTopbarUserRole { color: #94A3B8; font-size: 10px; }

/* ===================== CARDS ===================== */
QFrame#cardStat, QFrame#cardStat2, QFrame#cardStat3, QFrame#cardStat4,
QFrame#cardEmpStat1, QFrame#cardEmpStat2, QFrame#cardEmpStat3, QFrame#cardEmpStat4,
QFrame#cardSalleStat1, QFrame#cardSalleStat2, QFrame#cardSalleStat3, QFrame#cardSalleStat4,
QFrame#cardEvalStat1, QFrame#cardEvalStat2, QFrame#cardEvalStat3,
QFrame#cardPartStat1, QFrame#cardPartStat2, QFrame#cardPartStat3,
QFrame#cardSponStat1, QFrame#cardSponStat2, QFrame#cardSponStat3,
QFrame#cardProjStat1, QFrame#cardProjStat2, QFrame#cardProjStat3, QFrame#cardProjStat4,
QFrame#cardDonut, QFrame#cardBarsH, QFrame#cardBarsV,
QFrame#cardFormEmployes, QFrame#cardTableEmployes,
QFrame#cardFormSalles, QFrame#cardTableSalles,
QFrame#cardFormEvaluateurs, QFrame#cardTableEvaluateurs,
QFrame#cardFormParticipants, QFrame#cardTableParticipants,
QFrame#cardFormSponsors, QFrame#cardTableSponsors,
QFrame#cardFormProjets, QFrame#cardTableProjets,
QFrame#cardChatbot {
    background-color: #111827;
    border: 1px solid #1F2937;
    border-radius: 14px;
}
QFrame#cardStat:hover, QFrame#cardStat2:hover,
QFrame#cardStat3:hover, QFrame#cardStat4:hover {
    border: 1px solid #6366F1;
}

QLabel#cardStatTitle, QLabel#cardStatTitle2, QLabel#cardStatTitle3, QLabel#cardStatTitle4,
QLabel#cardEmpTitle1, QLabel#cardEmpTitle2, QLabel#cardEmpTitle3, QLabel#cardEmpTitle4,
QLabel#cardSalleTitle1, QLabel#cardSalleTitle2, QLabel#cardSalleTitle3, QLabel#cardSalleTitle4,
QLabel#cardEvalTitle1, QLabel#cardEvalTitle2, QLabel#cardEvalTitle3,
QLabel#cardPartTitle1, QLabel#cardPartTitle2, QLabel#cardPartTitle3,
QLabel#cardSponTitle1, QLabel#cardSponTitle2, QLabel#cardSponTitle3,
QLabel#cardProjTitle1, QLabel#cardProjTitle2, QLabel#cardProjTitle3, QLabel#cardProjTitle4 {
    color: #94A3B8; font-size: 10px; font-weight: 800; letter-spacing: 1.5px;
}
QLabel#cardStatValue, QLabel#cardStatValue2, QLabel#cardStatValue3, QLabel#cardStatValue4,
QLabel#cardEmpValue1, QLabel#cardEmpValue2, QLabel#cardEmpValue3, QLabel#cardEmpValue4,
QLabel#cardSalleValue1, QLabel#cardSalleValue2, QLabel#cardSalleValue3, QLabel#cardSalleValue4,
QLabel#cardEvalValue1, QLabel#cardEvalValue2, QLabel#cardEvalValue3,
QLabel#cardPartValue1, QLabel#cardPartValue2, QLabel#cardPartValue3,
QLabel#cardSponValue1, QLabel#cardSponValue2, QLabel#cardSponValue3,
QLabel#cardProjValue1, QLabel#cardProjValue2, QLabel#cardProjValue3, QLabel#cardProjValue4 {
    color: #FFFFFF; font-size: 32px; font-weight: 900;
}
QLabel#cardStatSub, QLabel#cardStatSub2, QLabel#cardStatSub3, QLabel#cardStatSub4,
QLabel#cardEmpSub1, QLabel#cardEmpSub2, QLabel#cardEmpSub3, QLabel#cardEmpSub4,
QLabel#cardSalleSub1, QLabel#cardSalleSub2, QLabel#cardSalleSub3, QLabel#cardSalleSub4,
QLabel#cardEvalSub1, QLabel#cardEvalSub2, QLabel#cardEvalSub3,
QLabel#cardPartSub1, QLabel#cardPartSub2, QLabel#cardPartSub3,
QLabel#cardSponSub1, QLabel#cardSponSub2, QLabel#cardSponSub3,
QLabel#cardProjSub1, QLabel#cardProjSub2, QLabel#cardProjSub3, QLabel#cardProjSub4 {
    color: #64748B; font-size: 11px;
}

/* ===================== FORM ===================== */
QLabel#lblEmpID, QLabel#lblEmpNom, QLabel#lblEmpPrenom, QLabel#lblEmpMdp,
QLabel#lblEmpRole, QLabel#lblEmpStatut,
QLabel#lblSalleID, QLabel#lblSalleNom, QLabel#lblSalleCap,
QLabel#lblSalleType, QLabel#lblSalleDispo,
QLabel#lblEvalID, QLabel#lblEvalNom, QLabel#lblEvalPrenom,
QLabel#lblEvalEmail, QLabel#lblEvalStatut,
QLabel#lblPartID, QLabel#lblPartNom, QLabel#lblPartPrenom,
QLabel#lblPartEmail, QLabel#lblPartTel, QLabel#lblPartEquipe,
QLabel#lblSponID, QLabel#lblSponEntreprise, QLabel#lblSponContact,
QLabel#lblSponType, QLabel#lblSponStatut,
QLabel#lblProjID, QLabel#lblProjNom, QLabel#lblProjCat,
QLabel#lblProjStatut, QLabel#lblProjEquipe,
QLabel#labelLoginField, QLabel#labelLoginField2 {
    color: #94A3B8; font-size: 10px; font-weight: 800; letter-spacing: 1px;
}
QLineEdit, QComboBox, QDateEdit, QSpinBox {
    background-color: #0B1020;
    border: 1.5px solid #374151;
    border-radius: 8px; padding: 8px 12px;
    color: #E5E7EB; font-size: 13px;
    min-height: 22px;
    selection-background-color: #6366F1; selection-color: #FFFFFF;
}
QLineEdit:focus, QComboBox:focus, QDateEdit:focus, QSpinBox:focus {
    border: 1.5px solid #6366F1; background-color: #111827;
}
QLineEdit:read-only { background-color: #1F2937; color: #94A3B8; }
QComboBox::drop-down { border: none; width: 24px; }
QComboBox::down-arrow {
    image: none;
    border-left: 4px solid transparent;
    border-right: 4px solid transparent;
    border-top: 5px solid #818CF8;
    width: 0; height: 0; margin-right: 10px;
}
QComboBox QAbstractItemView {
    background-color: #111827; border: 1px solid #374151;
    border-radius: 8px;
    selection-background-color: #6366F1;
    selection-color: #FFFFFF; color: #E5E7EB;
    padding: 4px; outline: none;
}

/* ===================== BUTTONS ===================== */
QPushButton#btnEmpAjouter, QPushButton#btnSalleAjouter, QPushButton#btnEvalAjouter,
QPushButton#btnPartAjouter, QPushButton#btnSponAjouter, QPushButton#btnProjAjouter {
    background-color: #047857;
    color: #FFFFFF; font-size: 11px; font-weight: 800; letter-spacing: 1px;
    border: none; border-radius: 8px; padding: 10px 18px;
}
QPushButton#btnEmpAjouter:hover, QPushButton#btnSalleAjouter:hover,
QPushButton#btnEvalAjouter:hover, QPushButton#btnPartAjouter:hover,
QPushButton#btnSponAjouter:hover, QPushButton#btnProjAjouter:hover {
    background-color: #10B981;
}
QPushButton#btnEmpSupprimer, QPushButton#btnSalleSupprimer, QPushButton#btnEvalSupprimer,
QPushButton#btnPartSupprimer, QPushButton#btnSponSupprimer, QPushButton#btnProjSupprimer {
    background-color: #B91C1C;
    color: #FFFFFF; font-size: 11px; font-weight: 800; letter-spacing: 1px;
    border: none; border-radius: 8px; padding: 10px 18px;
}
QPushButton#btnEmpSupprimer:hover, QPushButton#btnSalleSupprimer:hover,
QPushButton#btnEvalSupprimer:hover, QPushButton#btnPartSupprimer:hover,
QPushButton#btnSponSupprimer:hover, QPushButton#btnProjSupprimer:hover {
    background-color: #EF4444;
}
QPushButton#btnEmpModifier, QPushButton#btnSalleModifier, QPushButton#btnEvalModifier,
QPushButton#btnPartModifier, QPushButton#btnSponModifier, QPushButton#btnProjModifier,
QPushButton#btnEmpRechercher, QPushButton#btnSalleRechercher, QPushButton#btnEvalRechercher,
QPushButton#btnPartRechercher, QPushButton#btnSponRechercher, QPushButton#btnProjRechercher {
    background-color: #6366F1;
    color: #FFFFFF; font-size: 11px; font-weight: 800; letter-spacing: 1px;
    border: none; border-radius: 8px; padding: 10px 18px;
}
QPushButton#btnEmpModifier:hover, QPushButton#btnSalleModifier:hover,
QPushButton#btnEvalModifier:hover, QPushButton#btnPartModifier:hover,
QPushButton#btnSponModifier:hover, QPushButton#btnProjModifier:hover,
QPushButton#btnEmpRechercher:hover, QPushButton#btnSalleRechercher:hover,
QPushButton#btnEvalRechercher:hover, QPushButton#btnPartRechercher:hover,
QPushButton#btnSponRechercher:hover, QPushButton#btnProjRechercher:hover {
    background-color: #818CF8;
}
QPushButton#btnEmpConsulter, QPushButton#btnEmpTrier,
QPushButton#btnSalleConsulter, QPushButton#btnSalleTrier,
QPushButton#btnEvalConsulter, QPushButton#btnEvalTrier,
QPushButton#btnPartConsulter, QPushButton#btnPartTrier,
QPushButton#btnSponConsulter, QPushButton#btnSponTrier,
QPushButton#btnProjConsulter, QPushButton#btnProjTrier {
    background-color: #334155; color: #E5E7EB;
    font-size: 11px; font-weight: 700; letter-spacing: 0.5px;
    border: 1px solid #475569; border-radius: 8px; padding: 10px 18px;
}
QPushButton#btnEmpConsulter:hover, QPushButton#btnEmpTrier:hover,
QPushButton#btnSalleConsulter:hover, QPushButton#btnSalleTrier:hover,
QPushButton#btnEvalConsulter:hover, QPushButton#btnEvalTrier:hover,
QPushButton#btnPartConsulter:hover, QPushButton#btnPartTrier:hover,
QPushButton#btnSponConsulter:hover, QPushButton#btnSponTrier:hover,
QPushButton#btnProjConsulter:hover, QPushButton#btnProjTrier:hover {
    background-color: #475569;
}

/* ===================== TABLE ===================== */
QTableWidget {
    background-color: #0B1020;
    border: 1px solid #1F2937;
    border-radius: 10px;
    gridline-color: #1F2937;
    font-size: 13px; color: #E5E7EB;
    selection-background-color: #312E81;
    selection-color: #FFFFFF;
    alternate-background-color: #111827;
    padding: 4px; outline: none;
}
QTableWidget::item { padding: 8px; border-bottom: 1px solid #1F2937; }
QTableWidget::item:selected {
    background-color: #312E81; color: #FFFFFF;
}
QHeaderView::section {
    background-color: #111827; color: #818CF8;
    font-size: 10px; font-weight: 800; letter-spacing: 1px;
    padding: 12px 10px;
    border: none; border-right: 1px solid #1F2937;
    border-bottom: 2px solid #6366F1;
}
QHeaderView::section:first { border-top-left-radius: 10px; }
QHeaderView::section:last  { border-top-right-radius: 10px; }
QTableCornerButton::section { background-color: #111827; border: none; }

/* ===================== LOGIN ===================== */
QWidget#pageConnexion {
    background: qradialgradient(cx:0.3, cy:0.3, radius:1.4,
        stop:0 #1E1B4B, stop:0.5 #0B1020, stop:1 #05070F);
}
QFrame#frameLoginCard {
    background-color: #111827; border: 1px solid #1F2937;
    border-radius: 20px;
}
QFrame#frameLoginBrand {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #4338CA, stop:0.6 #6366F1, stop:1 #8B5CF6);
    border-top-left-radius: 20px; border-bottom-left-radius: 20px;
}
QLabel#labelLoginLogo {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #FFFFFF, stop:1 #E0E7FF);
    color: #4338CA; font-size: 34px; font-weight: 900;
    letter-spacing: 2px; border-radius: 20px;
    qproperty-alignment: AlignCenter;
}
QLabel#labelLoginBrandTitle {
    color: #FFFFFF; font-size: 30px; font-weight: 900; letter-spacing: 5px;
}
QLabel#labelLoginBrandSub {
    color: #E0E7FF; font-size: 10px; font-weight: 700; letter-spacing: 3px;
}
QLabel#labelLoginBrandSlogan { color: #F1F5F9; font-size: 13px; }
QLabel#labelLoginTitle { color: #FFFFFF; font-size: 26px; font-weight: 900; }
QLabel#labelLoginSub { color: #94A3B8; font-size: 13px; }
QPushButton#pushButtonConnexion {
    background-color: #6366F1; color: #FFFFFF;
    font-size: 13px; font-weight: 900; letter-spacing: 2px;
    border: none; border-radius: 10px; padding: 16px;
}
QPushButton#pushButtonConnexion:hover {
    background-color: #818CF8;
}
QPushButton#pushButtonCGU, QPushButton#pushButtonPolitique,
QPushButton#pushButtonAPropos {
    color: #94A3B8; font-size: 12px; background: transparent;
    border: none; padding: 4px; text-align: left;
}
QPushButton#pushButtonCGU:hover, QPushButton#pushButtonPolitique:hover,
QPushButton#pushButtonAPropos:hover {
    color: #818CF8;
}
QLabel#labelLoginFooter { color: #475569; font-size: 11px; }
QFrame#frameLoginSeparator, QFrame#frameLoginSeparator2 {
    background-color: #1F2937; border: none;
}

/* ===================== PROGRESS ===================== */
QProgressBar {
    background-color: #0B1020; border: 1px solid #374151;
    border-radius: 10px; text-align: center;
    font-size: 10px; font-weight: 800; color: #E5E7EB; min-height: 20px;
}
QProgressBar::chunk {
    background-color: #6366F1; border-radius: 10px;
}

/* ===================== CHARTS ===================== */
QFrame#chartDonut {
    background: qconicalgradient(cx:0.5, cy:0.5, angle:0,
        stop:0.00 #6366F1, stop:0.35 #6366F1,
        stop:0.35 #8B5CF6, stop:0.60 #8B5CF6,
        stop:0.60 #A5B4FC, stop:0.75 #A5B4FC,
        stop:0.75 #1F2937, stop:1.00 #1F2937);
    border-radius: 70px;
}
QFrame#chartDonutHole { background-color: #111827; border-radius: 42px; }
QLabel#chartDonutCenterValue {
    color: #FFFFFF; font-size: 22px; font-weight: 900;
    qproperty-alignment: AlignCenter;
}
QLabel#chartDonutCenterLabel {
    color: #94A3B8; font-size: 9px; font-weight: 800;
    letter-spacing: 1px; qproperty-alignment: AlignCenter;
}

QFrame#barHFill1, QFrame#barHFill2, QFrame#barHFill3 {
    background-color: #6366F1; border-radius: 5px;
}
QFrame#barHFill4 { background-color: #B91C1C; border-radius: 5px; }
QFrame#barHTrack1, QFrame#barHTrack2, QFrame#barHTrack3, QFrame#barHTrack4 {
    background-color: #1F2937; border-radius: 5px;
}
QLabel#barLabel1, QLabel#barLabel2, QLabel#barLabel3, QLabel#barLabel4 {
    color: #E5E7EB; font-size: 12px; font-weight: 700;
}
QLabel#barValue1, QLabel#barValue2, QLabel#barValue3 {
    color: #818CF8; font-size: 12px; font-weight: 900;
}
QLabel#barValue4 { color: #F87171; font-size: 12px; font-weight: 900; }

QFrame#barVBar1, QFrame#barVBar2, QFrame#barVBar3,
QFrame#barVBar4, QFrame#barVBar5, QFrame#barVBar6 {
    background-color: #6366F1; border-radius: 6px;
}
QLabel#barVLabel1, QLabel#barVLabel2, QLabel#barVLabel3,
QLabel#barVLabel4, QLabel#barVLabel5, QLabel#barVLabel6 {
    color: #94A3B8; font-size: 10px; font-weight: 700;
    qproperty-alignment: AlignCenter;
}
QLabel#barVValue1, QLabel#barVValue2, QLabel#barVValue3,
QLabel#barVValue4, QLabel#barVValue5, QLabel#barVValue6 {
    color: #FFFFFF; font-size: 11px; font-weight: 800;
    qproperty-alignment: AlignCenter;
}
QLabel#labelDonutFooter, QLabel#labelProgressNote, QLabel#labelBarsVFooterLeft {
    color: #64748B; font-size: 11px;
}
QLabel#labelBarsVFooterRight { color: #34D399; font-size: 11px; font-weight: 800; }
QLabel#labelProgressTitle {
    color: #94A3B8; font-size: 10px; font-weight: 800; letter-spacing: 1.5px;
}
QLabel#labelDonutTitle, QLabel#labelBarsHTitle, QLabel#labelBarsVTitle,
QLabel#formTitleEmp, QLabel#formTitleSalles, QLabel#formTitleEval,
QLabel#formTitlePart, QLabel#formTitleSpon, QLabel#formTitleProj,
QLabel#tableTitleEmp, QLabel#tableTitleSalles, QLabel#tableTitleEval,
QLabel#tableTitlePart, QLabel#tableTitleSpon, QLabel#tableTitleProj {
    color: #FFFFFF; font-size: 14px; font-weight: 800; letter-spacing: 0.3px;
}
QLabel#labelDonutSub, QLabel#labelBarsHSub, QLabel#labelBarsVSub {
    color: #94A3B8; font-size: 12px;
}

/* ===================== CHATBOT ===================== */
QTextBrowser#chatDisplay {
    background-color: #0B1020;
    border: 1px solid #1F2937;
    border-radius: 10px;
    color: #E5E7EB;
    padding: 12px;
    font-size: 13px;
    selection-background-color: #6366F1;
}
QLabel#chatTitle {
    color: #FFFFFF; font-size: 15px; font-weight: 900; letter-spacing: 0.3px;
}
QLabel#chatSub { color: #94A3B8; font-size: 12px; }
QLabel#chatQuickTitle {
    color: #94A3B8; font-size: 10px; font-weight: 800; letter-spacing: 1.5px;
}
QLabel#chatStatusOnline {
    background-color: #064E3B; color: #34D399;
    font-size: 10px; font-weight: 800; border-radius: 8px; padding: 3px 10px;
}
QPushButton#chatQuick1, QPushButton#chatQuick2, QPushButton#chatQuick3, QPushButton#chatQuick4 {
    background-color: #0B1020; color: #E5E7EB;
    border: 1px solid #1F2937; border-radius: 8px;
    padding: 10px 16px; font-size: 12px; font-weight: 600;
    text-align: left;
}
QPushButton#chatQuick1:hover, QPushButton#chatQuick2:hover,
QPushButton#chatQuick3:hover, QPushButton#chatQuick4:hover {
    background-color: #1F2937; border: 1px solid #6366F1; color: #818CF8;
}
QPushButton#chatSendBtn {
    background-color: #6366F1;
    color: #FFFFFF; font-size: 12px; font-weight: 900; letter-spacing: 1px;
    border: none; border-radius: 8px; padding: 10px 18px;
}
QPushButton#chatSendBtn:hover {
    background-color: #818CF8;
}

/* ===================== DIALOG ===================== */
QDialog {
    background-color: #111827;
}
QDialog QLabel { color: #E5E7EB; }
QDialog QTextBrowser {
    background-color: #0B1020; border: 1px solid #1F2937;
    border-radius: 10px; color: #E5E7EB; padding: 12px;
}
QDialog QPushButton {
    background-color: #6366F1; color: #FFFFFF;
    border: none; border-radius: 8px;
    padding: 8px 18px; font-weight: 800;
}
QDialog QPushButton:hover { background-color: #818CF8; }
)");
}

/* ============================================================
 *  SCROLL FLOTTANT
 * ============================================================ */
void integration::installerBoutonsScroll()
{
    m_btnScrollTop    = new QPushButton(this);
    m_btnScrollBottom = new QPushButton(this);

    QString btnStyle = R"(
        QPushButton {
            background-color: #6366F1; color: #FFFFFF;
            border: none; border-radius: 22px;
            font-size: 16px; font-weight: 900;
        }
        QPushButton:hover { background-color: #818CF8; }
        QPushButton:pressed { background-color: #4F46E5; }
    )";

    m_btnScrollTop->setFixedSize(44, 44);
    m_btnScrollTop->setText("^");
    m_btnScrollTop->setStyleSheet(btnStyle);
    m_btnScrollTop->setToolTip("Haut de page");
    m_btnScrollTop->setCursor(Qt::PointingHandCursor);

    m_btnScrollBottom->setFixedSize(44, 44);
    m_btnScrollBottom->setText("v");
    m_btnScrollBottom->setStyleSheet(btnStyle);
    m_btnScrollBottom->setToolTip("Bas de page");
    m_btnScrollBottom->setCursor(Qt::PointingHandCursor);

    connect(m_btnScrollTop,    &QPushButton::clicked, this, &integration::scrollHaut);
    connect(m_btnScrollBottom, &QPushButton::clicked, this, &integration::scrollBas);

    m_btnScrollTop->hide();
    m_btnScrollBottom->hide();
}

void integration::mettreAJourBoutonsScroll()
{
    QScrollArea *sa = scrollAreaCourante();
    if (!sa) {
        if (m_btnScrollTop)    m_btnScrollTop->hide();
        if (m_btnScrollBottom) m_btnScrollBottom->hide();
        return;
    }

    int w = this->width();
    int h = this->height();

    m_btnScrollTop->move(w - 70, h - 120);
    m_btnScrollBottom->move(w - 70, h - 66);

    m_btnScrollTop->show();
    m_btnScrollBottom->show();

    m_btnScrollTop->raise();
    m_btnScrollBottom->raise();
}

QScrollArea* integration::scrollAreaCourante() const
{
    QWidget *w = ui->stackedWidget->currentWidget();
    if (!w) return nullptr;
    return w->findChild<QScrollArea*>();
}

void integration::scrollHaut()
{
    QScrollArea *sa = scrollAreaCourante();
    if (sa) sa->verticalScrollBar()->setValue(0);
}

void integration::scrollBas()
{
    QScrollArea *sa = scrollAreaCourante();
    if (sa) sa->verticalScrollBar()->setValue(sa->verticalScrollBar()->maximum());
}

/* ============================================================
 *  UTILITAIRES
 * ============================================================ */
void integration::toast(const QString &message, const QString &type)
{
    QLabel *toastLbl = new QLabel(this);
    toastLbl->setText(message);
    toastLbl->setAlignment(Qt::AlignCenter);
    toastLbl->setWordWrap(true);

    QString bg, fg, border;
    if (type == "success")      { bg = "#064E3B"; fg = "#34D399"; border = "#10B981"; }
    else if (type == "warning") { bg = "#78350F"; fg = "#FBBF24"; border = "#F59E0B"; }
    else if (type == "error")   { bg = "#7F1D1D"; fg = "#F87171"; border = "#EF4444"; }
    else                        { bg = "#1E1B4B"; fg = "#818CF8"; border = "#6366F1"; }

    toastLbl->setStyleSheet(QString(
                                "QLabel { background-color: %1; color: %2; "
                                "border: 1px solid %3; "
                                "padding: 12px 22px; border-radius: 10px; "
                                "font-size: 13px; font-weight: 700; }").arg(bg, fg, border));

    toastLbl->adjustSize();
    int w = toastLbl->width() + 20;
    int x = (this->width() - w) / 2;
    int y = this->height() - 100;
    toastLbl->setGeometry(x, y, w, toastLbl->height());

    toastLbl->show();
    toastLbl->raise();

    QTimer::singleShot(2200, toastLbl, &QLabel::deleteLater);
}

QString integration::nextId(const QString &prefix, int count)
{
    return QString("%1-%2").arg(prefix).arg(count + 1, 3, 10, QChar('0'));
}

void integration::afficherDialogue(const QString &titre, const QString &contenu)
{
    QDialog dlg(this);
    dlg.setWindowTitle(titre);
    dlg.setMinimumSize(560, 480);
    dlg.setStyleSheet(R"(
        QDialog { background-color: #111827; }
        QLabel#dlgTitle { color: #FFFFFF; font-size: 18px; font-weight: 900; }
        QTextBrowser { background-color: #0B1020; border: 1px solid #1F2937;
                       border-radius: 10px; color: #E5E7EB; padding: 14px; }
        QPushButton { background-color: #6366F1; color: #FFFFFF;
                      border: none; border-radius: 8px;
                      padding: 10px 22px; font-weight: 800; letter-spacing: 1px; }
        QPushButton:hover { background-color: #818CF8; }
    )");

    auto *layout = new QVBoxLayout(&dlg);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);

    auto *title = new QLabel(titre);
    title->setObjectName("dlgTitle");
    layout->addWidget(title);

    auto *browser = new QTextBrowser;
    browser->setHtml(contenu);
    browser->setOpenExternalLinks(true);
    layout->addWidget(browser, 1);

    auto *btnBox = new QHBoxLayout;
    btnBox->addStretch();
    auto *btnFermer = new QPushButton("FERMER");
    btnFermer->setCursor(Qt::PointingHandCursor);
    connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);
    btnBox->addWidget(btnFermer);
    layout->addLayout(btnBox);

    dlg.exec();
}