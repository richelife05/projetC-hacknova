#include "sponsor.h"

Sponsor::Sponsor() {
    // Constructeur par défaut (vide)
}

// Getters
QString Sponsor::getId() const {
    return id;
}

QString Sponsor::getNomEntreprise() const {
    return nomEntreprise;
}

QString Sponsor::getContact() const {
    return contact;
}

QString Sponsor::getTypeSponsor() const {
    return typeSponsor;
}

QString Sponsor::getStatut() const {
    return statut;
}

// Setters
void Sponsor::setId(const QString &id) {
    this->id = id;
}

void Sponsor::setNomEntreprise(const QString &nom) {
    this->nomEntreprise = nom;
}

void Sponsor::setContact(const QString &contact) {
    this->contact = contact;
}

void Sponsor::setTypeSponsor(const QString &type) {
    this->typeSponsor = type;
}

void Sponsor::setStatut(const QString &statut) {
    this->statut = statut;
}