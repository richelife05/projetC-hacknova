#include "connection.h"
#include <QSqlDatabase>    // <-- Add this line
#include <QSqlError>       // <-- Good practice to include this too
#include <QDebug>          // <-- Good practice to include this too

// Ctor
// Initialise l'attribut `db` avec le driver ODBC.
// On le fait dans le constructeur pour que `db` soit stocké dans le Singleton.
// Cela signifie que la même instance de `QSqlDatabase` sera utilisée partout dans l'application
// via le Singleton, au lieu de créer une nouvelle connexion à chaque fois.
Connection::Connection() {
    db = QSqlDatabase::addDatabase("QODBC");
}

//Dtor
// Ferme la connexion si elle est encore ouverte lorsque l'objet est détruit
// Rien à faire ici : la fermeture est faite par closeConnection() AVANT la destruction de QApplication.
// (Fermer un QSqlDatabase dans le destructeur d'un singleton statique peut faire planter l'application à la sortie.)
Connection::~Connection() {
}

// Ferme la connexion et retire la connexion par défaut de Qt
void Connection::closeConnection() {
    if (db.isOpen())
        db.close();
    db = QSqlDatabase();                                      // libère notre copie du handle
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

// --- Accès à l'instance unique du Singleton ---
// Utilise la technique "Meyers Singleton" : instance statique locale
// Elle est créée la première fois qu'on appelle createInstance()
// et reste vivante pendant toute la durée du programme (thread-safe en C++11+)
Connection& Connection::createInstance() {
    static Connection instance;  // Instance unique du Singleton
    return instance; // Retourne une référence à cette instance
}


bool Connection::createConnection() {
    db.setDatabaseName("basededonne_hacknova");// saisissez le nom de votre source de données ici
    db.setUserName("Lina");// saisissez votre nom d'utilisateur ici
    db.setPassword("houta30");// saisissez votre mot de passe utilisateur ici

    if (db.open()) {
        qDebug() << "Connexion établie";
        return true;
    }

    qDebug() << "Échec de la connexion :" << db.lastError().text();
    return false;
}