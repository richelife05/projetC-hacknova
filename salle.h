#ifndef SALLE_H
#define SALLE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPixmap>
#include <QSet>
#include <QTimer>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class salle; }
QT_END_NAMESPACE

/* ============================================================
 *  MODÈLE MÉTIER — Salle
 * ============================================================ */
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

    bool estDisponible() const
    {
        return disponibilite.compare("Disponible", Qt::CaseInsensitive) == 0;
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
    QString dateGeneration;

    QString serialiser() const
    {
        return QString("HACKNOVA|SALLE|ID=%1").arg(id);
    }
};

/* ============================================================
 *  Critères de tri/filtrage avancés
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
    Portee  portee        = ToutesLesDonnees;
    QString titre         = "Liste des salles HACKNOVA";
    QString sousTitre     = "Rapport généré automatiquement";
    QString enTete        = "HACKNOVA — Smart Hackathon Management";
    QString piedDePage    = "Document confidentiel — HACKNOVA";
    bool    numeroterPages = true;
    bool    paysage        = false;
    bool    afficherID       = true;
    bool    afficherNom      = true;
    bool    afficherCapacite = true;
    bool    afficherType     = true;
    bool    afficherDispo    = true;
    bool    afficherBloc     = true;
    bool    afficherEtage    = true;
};

/* ============================================================
 *  Classe principale
 * ============================================================ */
class salle : public QMainWindow
{
    Q_OBJECT

public:
    explicit salle(QWidget *parent = nullptr);
    ~salle() override;

    // ---- Helpers visuels (PUBLICS : utilisables dans fonctions libres) ----
    static QString styleBouton(const QString &couleur, const QString &hover,
                               const QString &texte = "color:#FFFFFF;");
    static QString styleCarte();
    static QString styleChamp();
    static QString styleTitreSection();

private slots:
    void allerPage(int index);
    void goLogin();
    void goEmployes();
    void goSalles();

    void onConnexion();
    void onNotifications();
    void onProfil();
    void onDeconnexion();
    void onEnvoyerQuestion();

    // CRUD Salles
    void onAjouterSalle();
    void onRechercherSalle();
    void onRechercheDynamiqueSalle();   // ← NOUVEAU (live search)
    void onTrierSalle();
    void onExporterSalle();
    void onAnnulerSalle();
    void ouvrirModificationSalle(qint64 idSalle);
    void ouvrirSuppressionSalle(qint64 idSalle, const QString &nomSalle);
    void ouvrirConsultationSalle(qint64 idSalle);

    void onSuggererSalle();
    void onValiderQR();

    void ouvrirGenerateurQR(qint64 idSalle);
    void ouvrirScannerImage();

private:
    Ui::salle *ui;

    // ---- Timer de debounce pour la recherche dynamique ----
    QTimer *m_debounceRechercheSalle = nullptr;

    void appliquerTheme();
    void connecterLogin();
    void connecterNavigation();
    void connecterChatbot();
    void connecterActions();

    void remplirTableEmployes();
    void remplirTableSalles();
    void dessinerStatistiques();
    void dessinerStatistiquesSalles();

    void          rafraichirSallesEtStats();
    void          viderFormulaireSalle();
    void          viderTableSalles();
    QWidget      *creerWidgetActions(qint64 idSalle, const QString &nomSalle);

    ResultatValidation validerSaisieSalle(const Salle &s, const QString &typeAutre) const;

    std::optional<Salle> chargerSalle(qint64 idSalle) const;
    bool                 nomSalleExiste(const QString &nom, qint64 idExclu = -1) const;
    QStringList          typesSalleDisponibles() const;
    void                 focusChampFautif(int champFautif);
    void                 insererLigneSalle(int row, const Salle &s);

    // Tri/filtrage avancé
    QVector<Salle>  chargerSallesFiltrees(const CriteresTri &c) const;
    QVector<Salle>  chargerSallesSelectionnees(const QVector<qint64> &ids) const;
    void            ouvrirDialogueTri();
    void            appliquerCriteresTri(const CriteresTri &c);
    QVector<qint64> idsSallesAffichees() const;

    // Export PDF avancé
    void ouvrirDialogueExport();

    // QR
    PayloadQR construirePayloadQR(const Salle &s) const;
    QString   genererRemarqueAuto(const Salle &s) const;
    QString   genererEngagementAdmin(const Salle &s) const;
    QPixmap   genererPixmapQR(const QString &contenu, int taille = 320) const;
    void      traiterPayloadQRScanne(const QString &texte);

    // Messages administratifs dynamiques
    QString genererMessageAdministratif(const Salle &s, const QString &contexte) const;
};

#endif // SALLE_H