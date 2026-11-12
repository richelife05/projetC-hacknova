#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "employe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class integration; }
QT_END_NAMESPACE

// ---------- DATA MODELS ----------
struct Salle {
    int     id;
    QString nom;
    int     capacite;
    QString type;
    QString dispo;
};

class integration : public QMainWindow
{
    Q_OBJECT

public:
    explicit integration(QWidget *parent = nullptr);
    ~integration() override;

private slots:
    // ============================================================================
    // === SLOTS GÉNÉRAUX (NAVIGATION ENTRE PAGES, CONNEXION) =====================
    // ============================================================================
    void allerPage(int index);
    void goLogin();
    void goEmployes();
    void goSalles();
    void goEvaluateurs();

    void onConnexion();
    void onNotifications();
    void onProfil();
    void onDeconnexion();

    // ============================================================================
    // === MODULE EMPLOYE =========================================================
    // ============================================================================
    void onAjouterEmploye();
    void onAnnulerEmploye();
    void onModifierEmploye(int row);
    void onSupprimerEmploye(int row);
    void onRechercherEmploye();
    void onTrierEmploye();
    void onTriParColonne(int colonne);
    void onExporterEmploye();
    void onEnvoyerQuestion();               // chatbot

    // ============================================================================
    // === MODULE SALLE ===========================================================
    // ============================================================================
    void onAjouterSalle();
    void onAnnulerSalle();
    void onModifierSalle(int row);
    void onSupprimerSalle(int row);
    void onRechercherSalle();
    void onTrierSalle();
    void onExporterSalle();
    void onSuggererSalle();
    void onValiderQR();

    // === MODULE EVALUATEURS ===
    void ajouterEvaluateur();
    void modifierEvaluateur();
    void supprimerEvaluateur();
    void annulerFormulaire();
    void rechercherEvaluateur();
    void trierEvaluateurs();
    void exporterEvaluateurs();
    void selectionnerLigne();
    void lancerTechChallenge();
    void lancerDeliberation();

private:
    Ui::integration *ui;
    QWidget *m_pageEvaluateurs = nullptr;
    QStandardItemModel *m_modelEvaluateurs = nullptr;
    int m_ligneEnEditionEval = -1;
    QLabel *m_labelProjetBar = nullptr;     // diagramme en barres (créé dans le code)

    // ============================================================================
    // === ATTRIBUTS GÉNÉRAUX =====================================================
    // ============================================================================
    QString m_idConnecte;                   // employé authentifié (vide si personne n'est connecté)
    QString m_roleConnecte;                 // son rôle : sert aux droits d'accès

    void appliquerTheme();
    void connecterLogin();
    void connecterNavigation();
    void construirePageEvaluateurs();
    void initialiserGestionEvaluateurs();
    void reconstruireBoutonsAction();
    void mettreAJourStatistiques();
    bool formulaireValide() const;
    void afficherMessage(const QString &titre, const QString &message);

    // ============================================================================
    // === MODULE EMPLOYE : attributs et méthodes =================================
    // ============================================================================
    // Architecture Modèle-Vue (Atelier CRUD)
    Employe Etmp;                           // objet du Modèle : ajouter(), afficher(), modifier(), supprimer(), rechercher()
    QSqlQueryModel *m_modelEmp = nullptr;   // modèle retourné par Etmp.afficher() / Etmp.rechercher()
    QString m_triEmp = "IDEMPLOYE";         // colonne de tri
    bool    m_triCroissant = true;          // sens du tri
    QString m_rechercheEmp;                 // mot-clé de la recherche en cours (vide = tout afficher)
    QString m_editEmpId;                    // ID de l'employé en cours de modification (vide = mode ajout)

    void connecterCRUDEmployes();
    void connecterChatbot();
    void remplirTableEmployes();            // lit le modèle SQL
    void ajouterLigneEmploye(int row, const Employe &e);
    void reinitialiserFormulaireEmploye();
    void dessinerStatistiques();
    QVector<Employe> employesComplets();    // tous les employés (statistiques, chatbot)

    // ============================================================================
    // === MODULE SALLE : attributs et méthodes ===================================
    // ============================================================================
    QVector<Salle> m_salles;
    int m_nextSalleId  = 1;
    int m_editSalleRow = -1;

    void connecterCRUDSalles();
    void connecterActions();
    void remplirTableSalles();
    void ajouterLigneSalle(int row, const Salle &s);
    void reinitialiserFormulaireSalle();
    void dessinerStatistiquesSalles();
    void chargerSallesDepuisBDD();
};

#endif // INTEGRATION_H