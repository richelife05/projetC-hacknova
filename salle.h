#ifndef SALLE_H
#define SALLE_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPixmap>
#include <QSet>
#include <QMap>
#include <QTimer>
#include <QDate>
#include <QDateTime>
#include <QComboBox>
#include <QLabel>
#include <QFrame>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class salle; }
QT_END_NAMESPACE

/* ============================================================
 *  MODÈLE MÉTIER — Salle, Période dynamique & Historique
 * ============================================================ */
struct PeriodeReservation
{
    QDate   dateDebut;
    int     dureeJours = 0;
    QString projet;
    QString reference;

    QDate dateFin() const
    {
        if (!dateDebut.isValid() || dureeJours <= 0) return dateDebut;
        return dateDebut.addDays(dureeJours - 1);
    }

    bool estActiveLe(const QDate &jour) const
    {
        if (!dateDebut.isValid() || dureeJours <= 0 || !jour.isValid()) return false;
        return (jour >= dateDebut && jour <= dateFin());
    }

    bool chevauche(const QDate &debutAutre, int dureeAutre) const
    {
        if (!dateDebut.isValid() || dureeJours <= 0 || !debutAutre.isValid() || dureeAutre <= 0)
            return false;
        const QDate finAutre = debutAutre.addDays(dureeAutre - 1);
        return !(finAutre < dateDebut || debutAutre > dateFin());
    }
};

struct EntreeHistoriqueSalle
{
    QDateTime dateHeure;
    QString   categorie;   // AJOUT, MODIFICATION, AFFECTATION, QR, CONSULTATION, SUPPRESSION
    QString   detail;
    QString   engagement;
};

struct Salle
{
    qint64  id           = 0;
    QString nom;         // ex: A-1-05
    int     capacite     = 0;
    QString type;
    QString disponibilite;
    QString bloc;        // A, B, C... H
    int     etage        = 1; // 1, 2, 3
    int     numeroSalle  = 1; // 01 à 15

    QDate   dateDebut;
    int     dureeJours   = 0;
    QDate   dateFin;
    QString projetAssocie;
    bool    disponibleAuto = true;

    bool estDisponible() const
    {
        return disponibleAuto;
    }
};

struct ResultatValidation
{
    bool    valide      = true;
    QString message;
    int     champFautif = -1;

    static ResultatValidation ok() { return ResultatValidation(); }
    static ResultatValidation erreur(const QString &msg, int champ = -1)
    {
        ResultatValidation r;
        r.valide      = false;
        r.message     = msg;
        r.champFautif = champ;
        return r;
    }
};

struct PayloadQR
{
    qint64  id           = 0;
    QString nom;
    int     capacite     = 0;
    QString type;
    QString disponibilite;
    QString remarqueAuto;
    QString engagementAdmin;
    QString messageQRAuto;
    QString dateGeneration;

    QString serialiser() const
    {
        return QString("HACKNOVA|SALLE|ID=%1").arg(id);
    }
};

/* ============================================================
 *  Critères de tri / filtrage avancés
 * ============================================================ */
struct CriteresTri
{
    QSet<QString> blocs;
    QSet<int>     etages;
    QSet<QString> types;
    QSet<QString> disponibilites;
    int           capaciteMin = 0;
    int           capaciteMax = 0;
    QString       nomContient;
    QString       champTri = "ID"; // ID, NOM, CAPACITE, TYPE, DISPONIBILITE, DATE_FIN
    bool          ordreCroissant = true;
    bool          trierParCapaciteCroissante   = false;
    bool          trierParCapaciteDecroissante = false;
    bool          trierParBloc = true;

    bool estVide() const {
        return blocs.isEmpty() && etages.isEmpty() && types.isEmpty()
        && disponibilites.isEmpty() && capaciteMin == 0 && capaciteMax == 0
            && nomContient.trimmed().isEmpty();
    }
};

/* ============================================================
 *  Options d'export PDF
 * ============================================================ */
struct OptionsExportPDF
{
    enum Portee { ToutesLesDonnees, ResultatsFiltres, SelectionSeule };
    Portee  portee         = ToutesLesDonnees;
    QString titre          = "Liste des salles HACKNOVA";
    QString sousTitre      = "Rapport généré automatiquement";
    QString enTete         = "HACKNOVA — Smart Hackathon Management";
    QString piedDePage     = "Document confidentiel — HACKNOVA";
    bool    numeroterPages = true;
    bool    paysage        = false;
    bool    afficherID     = true;
    bool    afficherNom    = true;
    bool    afficherCapacite = true;
    bool    afficherType   = true;
    bool    afficherDispo  = true;
    bool    afficherBloc   = true;
    bool    afficherEtage  = true;
};

/* ============================================================
 *  Classe principale — Gestion des Salles (Mode Sombre)
 * ============================================================ */
class salle : public QMainWindow
{
    Q_OBJECT

public:
    explicit salle(QWidget *parent = nullptr);
    ~salle() override;

    static QString styleBouton(const QString &couleur, const QString &hover,
                               const QString &texte = "color:#FFFFFF;");
    static QString styleCarte();
    static QString styleChamp();
    static QString styleTitreSection();

private slots:
    void allerPage(int index);
    void goLogin();
    void goSalles();

    void onConnexion();
    void onNotifications();
    void onProfil();
    void onDeconnexion();
    void onEnvoyerQuestion();

    // CRUD & gestion Salles
    void onAjouterSalle();
    void onRechercherSalle();
    void onRechercheDynamiqueSalle();
    void onTriRapideChange();
    void onTrierSalle();
    void onExporterSalle();
    void onAnnulerSalle();
    void ouvrirModificationSalle(qint64 idSalle);
    void ouvrirSuppressionSalle(qint64 idSalle, const QString &nomSalle);
    void ouvrirConsultationSalle(qint64 idSalle);
    void ouvrirHistoriqueSalle(qint64 idSalle);

    // Deux métiers en haut de page
    void ouvrirEspaceMetierAffectation();
    void ouvrirEspaceMetierQR();

    void ouvrirGenerateurQR(qint64 idSalle);
    void ouvrirScannerImage();

private:
    Ui::salle *ui;

    QTimer *m_debounceRechercheSalle = nullptr;

    // Compteur local des salles disponibles (incrémenté auto à chaque ajout)
    int m_compteurSallesDisponibles = 0;

    // Contrôles dynamiques page Salles
    QComboBox   *m_comboChampTri        = nullptr;
    QComboBox   *m_comboSensTri         = nullptr;
    QPushButton *m_btnMetierAffectation = nullptr;
    QPushButton *m_btnMetierQR          = nullptr;
    QLabel      *m_lblStatsResume       = nullptr;
    QLabel      *m_lblBarHorizontale    = nullptr;
    QLabel      *m_lblBarVerticale      = nullptr;
    QFrame      *m_frameBottomDashboard = nullptr;
    QLabel      *m_lblDashTotal         = nullptr;
    QLabel      *m_lblDashDispo         = nullptr;
    QLabel      *m_lblDashOccupe        = nullptr;
    QLabel      *m_lblDashTaux          = nullptr;
    QLabel      *m_lblDashMaj           = nullptr;

    QMap<qint64, PeriodeReservation> m_periodesSession;
    QMap<qint64, QVector<EntreeHistoriqueSalle>> m_historiqueSalles;
    CriteresTri m_triCourant;

    void appliquerThemeSombre();
    void connecterLogin();
    void connecterNavigation();
    void connecterChatbot();
    void connecterActions();
    void organiserPageSalles();

    void remplirTableSalles();
    void dessinerStatistiquesSalles();
    void mettreAJourTableauDeBordBas();

    void          calculerDisponibiliteAutomatique(Salle &s) const;
    void          rafraichirSallesEtStats();
    void          viderFormulaireSalle();
    void          viderTableSalles();
    QWidget      *creerWidgetActions(qint64 idSalle, const QString &nomSalle);

    // Historique & messages automatiques
    void    enregistrerHistorique(qint64 idSalle, const QString &categorie,
                               const QString &detail, const QString &engagement = QString());
    QString genererMessageAutoConsultation(const Salle &s) const;
    QString genererMessageAutoQR(const Salle &s, const QString &mode) const;
    QString genererMessageAutoAffectation(const Salle &s, const QDate &dDeb,
                                          const QDate &dFin, int duree,
                                          int effectif, const QString &projet) const;
    bool    affecterSalleSpecifique(const Salle &s, const QDate &dDeb, int duree,
                                 int effectif, const QString &projet,
                                 QWidget *parentDlg, QString *messageSortie = nullptr);

    ResultatValidation validerSaisieSalle(const Salle &s, const QString &typeAutre) const;

    std::optional<Salle> chargerSalle(qint64 idSalle) const;
    bool                 nomSalleExiste(const QString &nom, qint64 idExclu = -1) const;
    QStringList          typesSalleDisponibles() const;
    void                 focusChampFautif(int champFautif);
    void                 insererLigneSalle(int row, const Salle &s);

    QVector<Salle>  chargerSallesFiltrees(const CriteresTri &c) const;
    QVector<Salle>  chargerSallesSelectionnees(const QVector<qint64> &ids) const;
    void            trierSallesMemoire(QVector<Salle> &liste, const CriteresTri &c) const;
    void            ouvrirDialogueTri();
    void            appliquerCriteresTri(const CriteresTri &c);
    QVector<qint64> idsSallesAffichees() const;

    void ouvrirDialogueExport();

    PayloadQR construirePayloadQR(const Salle &s) const;
    QString   genererRemarqueAuto(const Salle &s) const;
    QString   genererEngagementAdmin(const Salle &s) const;
    QPixmap   genererPixmapQR(const QString &contenu, int taille = 320) const;
    void      traiterPayloadQRScanne(const QString &texte);

    QString genererMessageAdministratif(const Salle &s, const QString &contexte) const;
};

#endif // SALLE_H