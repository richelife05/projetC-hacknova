#ifndef SPONSOR_H
#define SPONSOR_H

#include <QString>

class Sponsor {
private:
    QString id;
    QString nomEntreprise;
    QString contact;
    QString typeSponsor;
    QString statut;

public:
    Sponsor();

    // Getters
    QString getId() const;
    QString getNomEntreprise() const;
    QString getContact() const;
    QString getTypeSponsor() const;
    QString getStatut() const;

    // Setters
    void setId(const QString &id);
    void setNomEntreprise(const QString &nom);
    void setContact(const QString &contact);
    void setTypeSponsor(const QString &type);
    void setStatut(const QString &statut);
};

#endif // SPONSOR_H