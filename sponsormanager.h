#ifndef SPONSORMANAGER_H
#define SPONSORMANAGER_H

#include <QString>
#include <QList>

// ==== L'CLASSE MÉTIER 1: SPONSOR ====
class Sponsor {
private:
    QString id, nomEntreprise, contact, typeSponsor, statut;
public:
    Sponsor();
    QString getId() const;
    QString getNomEntreprise() const;
    QString getContact() const;
    QString getTypeSponsor() const;
    QString getStatut() const;
    void setId(const QString &id);
    void setNomEntreprise(const QString &nom);
    void setContact(const QString &contact);
    void setTypeSponsor(const QString &type);
    void setStatut(const QString &statut);
};

// ==== L'MANAGER (CRUD SQL) ====
class SponsorManager {
public:
    static QList<Sponsor> getAllSponsors();
    static bool ajouterSponsor(const Sponsor &s);
    static bool supprimerSponsor(const QString &id);
    static bool modifierSponsor(const Sponsor &s);
    static QList<Sponsor> rechercherSponsor(const QString &keyword);
};

#endif // SPONSORMANAGER_H