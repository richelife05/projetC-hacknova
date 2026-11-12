#include "sponsormanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// ==== SPONSOR ====
Sponsor::Sponsor() {}
QString Sponsor::getId() const { return id; }
QString Sponsor::getNomEntreprise() const { return nomEntreprise; }
QString Sponsor::getContact() const { return contact; }
QString Sponsor::getTypeSponsor() const { return typeSponsor; }
QString Sponsor::getStatut() const { return statut; }
void Sponsor::setId(const QString &id) { this->id = id; }
void Sponsor::setNomEntreprise(const QString &nom) { this->nomEntreprise = nom; }
void Sponsor::setContact(const QString &contact) { this->contact = contact; }
void Sponsor::setTypeSponsor(const QString &type) { this->typeSponsor = type; }
void Sponsor::setStatut(const QString &statut) { this->statut = statut; }

// ==== SPONSORMANAGER (Le CRUD) ====
QList<Sponsor> SponsorManager::getAllSponsors() {
    QList<Sponsor> liste;
    QSqlQuery query;
    query.exec("SELECT ID_SPONSOR, NOM_ENTREPRISE, CONTACT, TYPE_SPONSOR, STATUT FROM SPONSORS ORDER BY ID_SPONSOR");
    while (query.next()) {
        Sponsor s;
        s.setId(query.value("ID_SPONSOR").toString());
        s.setNomEntreprise(query.value("NOM_ENTREPRISE").toString());
        s.setContact(query.value("CONTACT").toString());
        s.setTypeSponsor(query.value("TYPE_SPONSOR").toString());
        s.setStatut(query.value("STATUT").toString());
        liste.append(s);
    }
    return liste;
}

bool SponsorManager::ajouterSponsor(const Sponsor &s) {
    QSqlQuery query;
    query.prepare("INSERT INTO SPONSORS (ID_SPONSOR, NOM_ENTREPRISE, CONTACT, TYPE_SPONSOR, STATUT) VALUES (:id, :nom, :contact, :type, :statut)");
    query.bindValue(":id", s.getId());
    query.bindValue(":nom", s.getNomEntreprise());
    query.bindValue(":contact", s.getContact());
    query.bindValue(":type", s.getTypeSponsor());
    query.bindValue(":statut", s.getStatut());
    return query.exec();
}

bool SponsorManager::supprimerSponsor(const QString &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM SPONSORS WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool SponsorManager::modifierSponsor(const Sponsor &s) {
    QSqlQuery query;
    query.prepare("UPDATE SPONSORS SET NOM_ENTREPRISE=:nom, CONTACT=:contact, TYPE_SPONSOR=:type, STATUT=:statut WHERE ID_SPONSOR=:id");
    query.bindValue(":nom", s.getNomEntreprise());
    query.bindValue(":contact", s.getContact());
    query.bindValue(":type", s.getTypeSponsor());
    query.bindValue(":statut", s.getStatut());
    query.bindValue(":id", s.getId());
    return query.exec();
}

QList<Sponsor> SponsorManager::rechercherSponsor(const QString &keyword) {
    QList<Sponsor> liste;
    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR, NOM_ENTREPRISE, CONTACT, TYPE_SPONSOR, STATUT FROM SPONSORS WHERE ID_SPONSOR LIKE :search OR NOM_ENTREPRISE LIKE :search");
    query.bindValue(":search", "%" + keyword + "%");
    if (query.exec()) {
        while (query.next()) {
            Sponsor s;
            s.setId(query.value("ID_SPONSOR").toString());
            s.setNomEntreprise(query.value("NOM_ENTREPRISE").toString());
            s.setContact(query.value("CONTACT").toString());
            s.setTypeSponsor(query.value("TYPE_SPONSOR").toString());
            s.setStatut(query.value("STATUT").toString());
            liste.append(s);
        }
    }
    return liste;
}