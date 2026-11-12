#include "connection.h"
#include <QSqlError>
#include <QDebug>

bool Connection::createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Hna t7ott l'ism li 3tih l'DSN fel ODBC (mthln: "DS_SmartMarket")
    db.setDatabaseName("DS_SmartMarket");

    // ⚠️ Hna t7ott ism l'Workspace mte3ek (SPONSOR)
    db.setUserName("SPONSOR");

    // Hna t7ott l'mot de passe mte3 l'Workspace SPONSOR
    db.setPassword("votre_mot_de_passe_apex");

    if (!db.open()) {
        qDebug() << "Erreur de connexion :" << db.lastError().text();
        return false;
    }

    qDebug() << "Connexion à Oracle réussie !";
    return true;
}