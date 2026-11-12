#include "mainwindow.h"
#include "sponsormanager.h"
#include "clientmanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QFormLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    applyStyles();

    // Rabt Sponsors
    connect(btnAjouter, &QPushButton::clicked, this, &MainWindow::ajouterSponsor);
    connect(btnRechercher, &QPushButton::clicked, this, &MainWindow::rechercherSponsor);
    connect(btnTrier, &QPushButton::clicked, this, &MainWindow::trierSponsors);
    connect(btnEnregistrer, &QPushButton::clicked, this, &MainWindow::enregistrerModification);

    // Rabt Clients
    connect(btnAjouterClient, &QPushButton::clicked, this, &MainWindow::ajouterClient);

    btnEnregistrer->hide();
    loadSponsorsFromDatabase();
    loadClientsFromDatabase();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    setWindowTitle("HACKNOVA — Smart Hackathon Management");
    resize(1400, 800);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(15);

    // --- GAUCHE (Sponsors) ---
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Rechercher un sponsor par son id...");
    searchInput->setMinimumHeight(40);
    btnRechercher = new QPushButton("RECHERCHER");
    btnTrier = new QPushButton("TRIER");
    QPushButton *btnExport = new QPushButton("EXPORTER");
    btnRechercher->setObjectName("btnAction");
    btnTrier->setObjectName("btnAction");
    btnExport->setObjectName("btnExport");
    topBarLayout->addWidget(searchInput, 3);
    topBarLayout->addWidget(btnRechercher, 1);
    topBarLayout->addWidget(btnTrier, 1);
    topBarLayout->addWidget(btnExport, 1);

    tableSponsors = new QTableWidget();
    tableSponsors->setColumnCount(6);
    tableSponsors->setHorizontalHeaderLabels({"ID", "Nom entreprise", "Contact", "Statut", "Type sponsor", "Action"});
    tableSponsors->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableSponsors->verticalHeader()->setVisible(false);
    tableSponsors->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableSponsors->setShowGrid(false);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QGroupBox *gbSmartPack = new QGroupBox("Smart Pack Builder Contrat PDF");
    QVBoxLayout *vboxSmart = new QVBoxLayout(gbSmartPack);
    vboxSmart->addWidget(new QLabel("Budget du Sponsor (DT) :"));
    vboxSmart->addWidget(new QLineEdit("5000"));
    vboxSmart->addStretch();
    QLabel *lblReco = new QLabel("Recommandé : PACK GOLD ⭐⭐⭐");
    lblReco->setStyleSheet("color: #f1c40f; font-weight: bold;");
    vboxSmart->addWidget(lblReco);

    QGroupBox *gbDash = new QGroupBox("Dashboard Objectifs Sponsoring");
    QVBoxLayout *vboxDash = new QVBoxLayout(gbDash);
    vboxDash->addWidget(new QLabel("Objectif Financier Globale (85%)"));
    QProgressBar *progObj = new QProgressBar();
    progObj->setValue(85);
    progObj->setFormat("%p%");
    vboxDash->addWidget(progObj);
    bottomLayout->addWidget(gbSmartPack);
    bottomLayout->addWidget(gbDash);

    leftLayout->addLayout(topBarLayout);
    leftLayout->addWidget(tableSponsors);
    leftLayout->addLayout(bottomLayout);

    // --- DROITE (Formulaire Sponsor + Formulaire Client) ---
    QVBoxLayout *rightLayout = new QVBoxLayout();

    // Formulaire Sponsor
    QGroupBox *gbAdd = new QGroupBox("Ajouter un sponsor");
    QVBoxLayout *formLayout = new QVBoxLayout(gbAdd);
    formLayout->addWidget(new QLabel("NOM ENTREPRISE"));
    inputNom = new QLineEdit();
    formLayout->addWidget(inputNom);
    formLayout->addWidget(new QLabel("CONTACT"));
    inputContact = new QLineEdit();
    formLayout->addWidget(inputContact);
    formLayout->addWidget(new QLabel("TYPE SPONSOR"));
    comboType = new QComboBox();
    comboType->addItems({"Gold", "Silver", "Bronze"});
    formLayout->addWidget(comboType);
    formLayout->addWidget(new QLabel("STATUT"));
    comboStatut = new QComboBox();
    comboStatut->addItems({"Actif", "Inactif"});
    formLayout->addWidget(comboStatut);
    btnAjouter = new QPushButton("AJOUTER");
    btnAjouter->setObjectName("btnAddSubmit");
    btnEnregistrer = new QPushButton("ENREGISTRER MODIF");
    btnEnregistrer->setObjectName("btnAddSubmit");
    btnCancel = new QPushButton("ANNULER");
    btnCancel->setObjectName("btnCancel");
    formLayout->addWidget(btnAjouter);
    formLayout->addWidget(btnEnregistrer);
    formLayout->addWidget(btnCancel);

    // Formulaire Client (Jdid)
    QGroupBox *gbClient = new QGroupBox("Ajouter un client");
    QVBoxLayout *formClient = new QVBoxLayout(gbClient);
    formClient->addWidget(new QLabel("NOM CLIENT"));
    clientNom = new QLineEdit();
    formClient->addWidget(clientNom);
    formClient->addWidget(new QLabel("EMAIL"));
    clientEmail = new QLineEdit();
    formClient->addWidget(clientEmail);
    formClient->addWidget(new QLabel("TELEPHONE"));
    clientTel = new QLineEdit();
    formClient->addWidget(clientTel);
    btnAjouterClient = new QPushButton("AJOUTER CLIENT");
    btnAjouterClient->setObjectName("btnAddSubmit");
    formClient->addWidget(btnAjouterClient);

    // Tableau Client (Jdid)
    tableClients = new QTableWidget();
    tableClients->setColumnCount(4);
    tableClients->setHorizontalHeaderLabels({"ID", "Nom", "Email", "Telephone"});
    tableClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Statistiques
    QGroupBox *gbStats = new QGroupBox("Statistiques des sponsors");
    QVBoxLayout *statsLayout = new QVBoxLayout(gbStats);
    auto addStat = [&](QString label, int percent, QString color) {
        statsLayout->addWidget(new QLabel(label));
        QProgressBar *pb = new QProgressBar();
        pb->setValue(percent);
        pb->setFormat(QString::number(percent) + "%");
        pb->setStyleSheet(QString("QProgressBar::chunk { background-color: %1; }").arg(color));
        statsLayout->addWidget(pb);
    };
    addStat("Gold (40%)", 40, "#f1c40f");
    addStat("Silver (35%)", 35, "#8e44ad");
    addStat("Bronze (25%)", 25, "#3498db");

    rightLayout->addWidget(gbAdd);
    rightLayout->addWidget(gbClient); // Zid l'Client
    rightLayout->addWidget(tableClients); // Zid l'Tableau mte3 l'Client
    rightLayout->addWidget(gbStats);
    rightLayout->addStretch();

    mainLayout->addLayout(leftLayout, 7);
    mainLayout->addLayout(rightLayout, 3);
}

void MainWindow::applyStyles() {
    QString style = R"(
        QMainWindow { background-color: #0d1117; }
        QWidget { color: #c9d1d9; font-family: "Segoe UI"; font-size: 13px; }
        QLineEdit, QComboBox { background-color: #161b22; border: 1px solid #30363d; border-radius: 5px; padding: 5px; color: white; }
        QPushButton { background-color: #21262d; border: 1px solid #30363d; border-radius: 5px; color: white; padding: 5px 10px; font-weight: bold; }
        #btnAction { background-color: #58a6ff; color: black; }
        #btnExport { background-color: #2ea043; color: white; }
        #btnAddSubmit { background-color: #2ea043; color: white; padding: 8px; margin-top: 10px; }
        #btnCancel { background-color: #30363d; color: white; }
        #btnModif { background-color: #58a6ff; color: black; font-size: 10px; border-radius: 3px; padding: 2px; }
        #btnSup { background-color: #da3633; color: white; font-size: 10px; border-radius: 3px; padding: 2px; }
        QTableWidget { background-color: #0d1117; gridline-color: #30363d; border: 1px solid #30363d; }
        QHeaderView::section { background-color: #161b22; color: #58a6ff; padding: 5px; border-bottom: 2px solid #30363d; font-weight: bold; }
        QGroupBox { border: 1px solid #30363d; border-radius: 5px; margin-top: 10px; font-weight: bold; }
        QGroupBox::title { subcontrol-origin: margin; left: 10px; color: #c9d1d9; }
    )";
    this->setStyleSheet(style);
}

// ==========================================
// === MODULE SPONSOR (Couche Métier 1)     ===
// ==========================================
void MainWindow::loadSponsorsFromDatabase() {
    tableSponsors->setRowCount(0);
    QList<Sponsor> liste = SponsorManager::getAllSponsors();
    int row = 0;
    for (const Sponsor &s : liste) {
        tableSponsors->insertRow(row);
        tableSponsors->setItem(row, 0, new QTableWidgetItem(s.getId()));
        tableSponsors->setItem(row, 1, new QTableWidgetItem(s.getNomEntreprise()));
        tableSponsors->setItem(row, 2, new QTableWidgetItem(s.getContact()));
        tableSponsors->setItem(row, 3, new QTableWidgetItem(s.getStatut()));
        tableSponsors->setItem(row, 4, new QTableWidgetItem(s.getTypeSponsor()));

        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(0,0,0,0);
        QPushButton *btnMod = new QPushButton("MODIFIER");
        QPushButton *btnSup = new QPushButton("SUPPRIMER");
        btnMod->setObjectName("btnModif");
        btnSup->setObjectName("btnSup");
        connect(btnSup, &QPushButton::clicked, this, &MainWindow::supprimerSponsor);
        connect(btnMod, &QPushButton::clicked, this, &MainWindow::modifierSponsor);
        actionLayout->addWidget(btnMod);
        actionLayout->addWidget(btnSup);
        tableSponsors->setCellWidget(row, 5, actionWidget);
        row++;
    }
}

void MainWindow::ajouterSponsor() {
    Sponsor s;
    s.setId("SPO-" + QString::number(rand() % 100).rightJustified(3, '0'));
    s.setNomEntreprise(inputNom->text().trimmed());
    s.setContact(inputContact->text().trimmed());
    s.setTypeSponsor(comboType->currentText());
    s.setStatut(comboStatut->currentText());

    if (SponsorManager::ajouterSponsor(s)) {
        QMessageBox::information(this, "Succès", "Sponsor ajouté !");
        loadSponsorsFromDatabase();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur d'ajout !");
    }
}

void MainWindow::supprimerSponsor() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QWidget *w = btn->parentWidget();
    int rowIndex = tableSponsors->indexAt(w->pos()).row();
    QString id = tableSponsors->item(rowIndex, 0)->text();

    if (SponsorManager::supprimerSponsor(id)) {
        QMessageBox::information(this, "Succès", "Sponsor supprimé !");
        loadSponsorsFromDatabase();
    }
}

void MainWindow::modifierSponsor() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QWidget *w = btn->parentWidget();
    int rowIndex = tableSponsors->indexAt(w->pos()).row();

    currentEditId = tableSponsors->item(rowIndex, 0)->text();
    inputNom->setText(tableSponsors->item(rowIndex, 1)->text());
    inputContact->setText(tableSponsors->item(rowIndex, 2)->text());
    comboStatut->setCurrentText(tableSponsors->item(rowIndex, 3)->text());
    comboType->setCurrentText(tableSponsors->item(rowIndex, 4)->text());

    btnEnregistrer->show();
    btnAjouter->hide();
}

void MainWindow::enregistrerModification() {
    Sponsor s;
    s.setId(currentEditId);
    s.setNomEntreprise(inputNom->text().trimmed());
    s.setContact(inputContact->text().trimmed());
    s.setTypeSponsor(comboType->currentText());
    s.setStatut(comboStatut->currentText());

    if (SponsorManager::modifierSponsor(s)) {
        QMessageBox::information(this, "Succès", "Modifié avec succès !");
        loadSponsorsFromDatabase();
        btnEnregistrer->hide();
        btnAjouter->show();
    }
}

void MainWindow::rechercherSponsor() {
    QString searchText = searchInput->text().trimmed();
    if (searchText.isEmpty()) { loadSponsorsFromDatabase(); return; }

    tableSponsors->setRowCount(0);
    QList<Sponsor> liste = SponsorManager::rechercherSponsor(searchText);
    int row = 0;
    for (const Sponsor &s : liste) {
        tableSponsors->insertRow(row);
        tableSponsors->setItem(row, 0, new QTableWidgetItem(s.getId()));
        tableSponsors->setItem(row, 1, new QTableWidgetItem(s.getNomEntreprise()));
        tableSponsors->setItem(row, 2, new QTableWidgetItem(s.getContact()));
        tableSponsors->setItem(row, 3, new QTableWidgetItem(s.getStatut()));
        tableSponsors->setItem(row, 4, new QTableWidgetItem(s.getTypeSponsor()));
        row++;
    }
}

void MainWindow::trierSponsors() {
    loadSponsorsFromDatabase();
}

// ==========================================
// === MODULE CLIENT (Couche Métier 2)       ===
// ==========================================
void MainWindow::loadClientsFromDatabase() {
    tableClients->setRowCount(0);
    QList<Client> liste = ClientManager::getAllClients();
    int row = 0;
    for (const Client &c : liste) {
        tableClients->insertRow(row);
        tableClients->setItem(row, 0, new QTableWidgetItem(c.getId()));
        tableClients->setItem(row, 1, new QTableWidgetItem(c.getNom()));
        tableClients->setItem(row, 2, new QTableWidgetItem(c.getEmail()));
        tableClients->setItem(row, 3, new QTableWidgetItem(c.getTelephone()));
        row++;
    }
}

void MainWindow::ajouterClient() {
    Client c;
    c.setId("CLI-" + QString::number(rand() % 100).rightJustified(3, '0'));
    c.setNom(clientNom->text().trimmed());
    c.setEmail(clientEmail->text().trimmed());
    c.setTelephone(clientTel->text().trimmed());

    if (ClientManager::ajouterClient(c)) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        loadClientsFromDatabase();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur d'ajout client !");
    }
}