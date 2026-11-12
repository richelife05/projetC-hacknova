#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class Connection {
public:
    static bool createConnection() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("Smart_Market");
        db.setUserName("SPONSOR");
        db.setPassword("13046024");

        if (!db.open()) {
            qDebug() << "Erreur de connexion :" << db.lastError().text();
            return false;
        }
        qDebug() << "Connexion à Oracle réussie !";
        return true;
    }
};

#endif // CONNECTION_H