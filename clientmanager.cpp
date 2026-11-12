#include "clientmanager.h"
#include <QSqlQuery>
#include <QSqlError>

// ==== CLIENT ====
Client::Client() {}
QString Client::getId() const { return id; }
QString Client::getNom() const { return nom; }
QString Client::getEmail() const { return email; }
QString Client::getTelephone() const { return telephone; }
void Client::setId(const QString &id) { this->id = id; }
void Client::setNom(const QString &nom) { this->nom = nom; }
void Client::setEmail(const QString &email) { this->email = email; }
void Client::setTelephone(const QString &tel) { this->telephone = tel; }

// ==== CLIENTMANAGER (Le CRUD) ====
QList<Client> ClientManager::getAllClients() {
    QList<Client> liste;
    QSqlQuery query;
    query.exec("SELECT ID_CLIENT, NOM, EMAIL, TELEPHONE FROM CLIENTS");
    while (query.next()) {
        Client c;
        c.setId(query.value("ID_CLIENT").toString());
        c.setNom(query.value("NOM").toString());
        c.setEmail(query.value("EMAIL").toString());
        c.setTelephone(query.value("TELEPHONE").toString());
        liste.append(c);
    }
    return liste;
}

bool ClientManager::ajouterClient(const Client &c) {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (ID_CLIENT, NOM, EMAIL, TELEPHONE) VALUES (:id, :nom, :email, :tel)");
    query.bindValue(":id", c.getId());
    query.bindValue(":nom", c.getNom());
    query.bindValue(":email", c.getEmail());
    query.bindValue(":tel", c.getTelephone());
    return query.exec();
}