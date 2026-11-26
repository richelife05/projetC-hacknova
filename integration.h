#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QTableWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QProgressBar>
#include <QMenu>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class integration; }
QT_END_NAMESPACE

struct Employe     { QString id, nom, prenom, mdp, role, statut; };
struct Salle       { QString id, nom; int capacite; QString type, dispo; };
struct Evaluateur  { QString id, nom, prenom, email, statut; };
struct Participant { QString id, nom, prenom, email, tel, equipe; };
struct Sponsor     { QString id, entreprise, contact, type, statut; };
struct Projet      { QString id, nom, categorie, statut, equipe; };

class integration : public QMainWindow
{
    Q_OBJECT

public:
    explicit integration(QWidget *parent = nullptr);
    ~integration();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onConnexion();
    void onDeconnexion();
    void onProfile();
    void onNotifications();
    void onCGU();
    void onPolitique();
    void onAPropos();
    void onChatSend();
    void onChatQuick();
    void scrollHaut();
    void scrollBas();

    // CRUD Employés
    void ajouterEmploye();
    void modifierEmploye();
    void supprimerEmploye();
    void rechercherEmployes();
    void trierEmployes();

    // CRUD Salles
    void ajouterSalle();
    void modifierSalle();
    void supprimerSalle();
    void rechercherSalles();
    void trierSalles();

    // CRUD Évaluateurs
    void ajouterEvaluateur();
    void modifierEvaluateur();
    void supprimerEvaluateur();
    void rechercherEvaluateurs();
    void trierEvaluateurs();

    // CRUD Participants
    void ajouterParticipant();
    void modifierParticipant();
    void supprimerParticipant();
    void rechercherParticipants();
    void trierParticipants();

    // CRUD Sponsors
    void ajouterSponsor();
    void modifierSponsor();
    void supprimerSponsor();
    void rechercherSponsors();
    void trierSponsors();

    // CRUD Projets
    void ajouterProjet();
    void modifierProjet();
    void supprimerProjet();
    void rechercherProjets();
    void trierProjets();

private:
    Ui::integration *ui;

    QList<Employe>     m_employes;
    QList<Salle>       m_salles;
    QList<Evaluateur>  m_evaluateurs;
    QList<Participant> m_participants;
    QList<Sponsor>     m_sponsors;
    QList<Projet>      m_projets;

    QPushButton *m_btnScrollTop    = nullptr;
    QPushButton *m_btnScrollBottom = nullptr;

    QString m_userName = "Utilisateur";
    QString m_userRole = "Administrateur";

    void connecterBoutons();
    void allerPage(int index);

    void rafraichirTout();
    void rafraichirEmployes();
    void rafraichirSalles();
    void rafraichirEvaluateurs();
    void rafraichirParticipants();
    void rafraichirSponsors();
    void rafraichirProjets();
    void rafraichirStats();

    void appliquerTheme();
    void installerBoutonsScroll();
    void mettreAJourBoutonsScroll();
    QScrollArea* scrollAreaCourante() const;

    void toast(const QString &message, const QString &type = "info");
    QString nextId(const QString &prefix, int count);
    void seedDonneesTest();

    // Dialogue moderne
    void afficherDialogue(const QString &titre, const QString &contenu);
};

#endif // INTEGRATION_H