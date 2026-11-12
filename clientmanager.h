#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QString>
#include <QList>

// ==== L'CLASSE MÉTIER 2: CLIENT ====
class Client {
private:
    QString id, nom, email, telephone;
public:
    Client();
    QString getId() const;
    QString getNom() const;
    QString getEmail() const;
    QString getTelephone() const;
    void setId(const QString &id);
    void setNom(const QString &nom);
    void setEmail(const QString &email);
    void setTelephone(const QString &tel);
};

// ==== L'MANAGER (CRUD SQL) ====
class ClientManager {
public:
    static QList<Client> getAllClients();
    static bool ajouterClient(const Client &c);
};

#endif // CLIENTMANAGER_H