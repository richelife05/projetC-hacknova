#include "client.h"
Client::Client() {}
QString Client::getId() const { return id; }
QString Client::getNom() const { return nom; }
QString Client::getEmail() const { return email; }
QString Client::getTelephone() const { return telephone; }
void Client::setId(const QString &id) { this->id = id; }
void Client::setNom(const QString &nom) { this->nom = nom; }
void Client::setEmail(const QString &email) { this->email = email; }
void Client::setTelephone(const QString &tel) { this->telephone = tel; }