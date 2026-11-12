#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class integration; }
QT_END_NAMESPACE

// ======================================================================
// === CLASSE METIER : Employe ==========================================
// ======================================================================
class Employe
{
public:
    Employe() {}
    Employe(const QString &id, const QString &nom, const QString &prenom,
            const QString &mdp, const QString &role, const QString &statut);

    QString getId() const     { return id; }
    QString getNom() const    { return nom; }
    QString getPrenom() const { return prenom; }
    QString getMdp() const    { return mdp; }
    QString getRole() const   { return role; }
    QString getStatut() const { return statut; }

    void setId(const QString &v)     { id = v; }
    void setNom(const QString &v)    { nom = v; }
    void setPrenom(const QString &v) { prenom = v; }
    void setMdp(const QString &v)    { mdp = v; }
    void setRole(const QString &v)   { role = v; }
    void setStatut(const QString &v) { statut = v; }

    bool ajouter();
    QSqlQueryModel* afficher(const QString &triPar = "IDEMPLOYE", bool croissant = true);
    bool modifier();
    bool supprimer(const QString &id);

    QSqlQueryModel* rechercher(const QString &motCle, const QString &triPar = "IDEMPLOYE", bool croissant = true);
    static QString colonneTriValide(const QString &triPar);

    static bool authentifier(const QString &id, const QString &mdp);
    static bool trouver(const QString &id, Employe &resultat);
    static bool peutSupprimer(const QString &role);

    static QString prochainId();
    QString verifierSaisie() const;

private:
    QString id, nom, prenom, mdp, role, statut;
};

// ======================================================================
// === STRUCTURE Salle (inchangée) ======================================
// ======================================================================
struct Salle {
    int     id;
    QString nom;
    int     capacite;
    QString type;
    QString dispo;
};

// ======================================================================
// === CLASSE UI : integration ==========================================
// Tous les boutons de nav restent visibles ; seul le module Employés
// est réellement fonctionnel. Les autres déclenchent un message
// adapté selon le rôle (Administrateur / Responsable RH).
// ======================================================================
class integration : public QMainWindow
{
    Q_OBJECT

public:
    explicit integration(QWidget *parent = nullptr);
    ~integration() override;

private slots:
    void allerPage(int index);
    void goLogin();
    void goEmployes();
    void goSalles();
    void goEvaluateurs();
    void goDashboard();
    void goParticipants();
    void goSponsors();
    void goProjets();

    void onConnexion();
    void onNotifications();
    void onProfil();
    void onDeconnexion();

    void onAjouterEmploye();
    void onAnnulerEmploye();
    void onModifierEmploye(int row);
    void onSupprimerEmploye(int row);
    void onRechercherEmploye();
    void onTrierEmploye();
    void onTriParColonne(int colonne);
    void onExporterEmploye();
    void onEnvoyerQuestion();

    void onAjouterSalle();
    void onAnnulerSalle();
    void onModifierSalle(int row);
    void onSupprimerSalle(int row);
    void onRechercherSalle();
    void onTrierSalle();
    void onExporterSalle();
    void onSuggererSalle();
    void onValiderQR();

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
    QLabel *m_labelProjetBar = nullptr;

    QString m_idConnecte;
    QString m_roleConnecte;

    void appliquerTheme();
    void connecterLogin();
    void connecterNavigation();
    void construirePageEvaluateurs();
    void initialiserGestionEvaluateurs();
    void reconstruireBoutonsAction();
    void mettreAJourStatistiques();
    bool formulaireValide() const;
    void afficherMessage(const QString &titre, const QString &message);

    // Message affiché quand un rôle clique sur une gestion non disponible
    void afficherModuleNonDisponible(const QString &nomModule);

    Employe Etmp;
    QSqlQueryModel *m_modelEmp = nullptr;
    QString m_triEmp = "IDEMPLOYE";
    bool    m_triCroissant = true;
    QString m_rechercheEmp;
    QString m_editEmpId;

    void connecterCRUDEmployes();
    void connecterChatbot();
    void remplirTableEmployes();
    void ajouterLigneEmploye(int row, const Employe &e);
    void reinitialiserFormulaireEmploye();
    void dessinerStatistiques();
    QVector<Employe> employesComplets();

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

#endif // EMPLOYE_H