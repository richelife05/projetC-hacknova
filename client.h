#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
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
#endif // CLIENT_H