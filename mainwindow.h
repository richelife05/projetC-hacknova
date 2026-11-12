#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // === MODULE SPONSOR ===
    void loadSponsorsFromDatabase();
    void ajouterSponsor();
    void supprimerSponsor();
    void modifierSponsor();
    void enregistrerModification();
    void rechercherSponsor();
    void trierSponsors();

    // === MODULE CLIENT ===
    void loadClientsFromDatabase();
    void ajouterClient();

private:
    QTableWidget *tableSponsors;
    QLineEdit *searchInput;
    QLineEdit *inputNom;
    QLineEdit *inputContact;
    QComboBox *comboType;
    QComboBox *comboStatut;
    QPushButton *btnAjouter;
    QPushButton *btnRechercher;
    QPushButton *btnTrier;
    QPushButton *btnEnregistrer;
    QPushButton *btnCancel;
    QString currentEditId;

    // Client Widgets
    QTableWidget *tableClients;
    QLineEdit *clientNom;
    QLineEdit *clientEmail;
    QLineEdit *clientTel;
    QPushButton *btnAjouterClient;

    void setupUi();
    void applyStyles();
};

#endif // MAINWINDOW_H