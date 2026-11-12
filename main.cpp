#include "employe.h"
#include <QApplication>
#include "connection.h"
#include <QFont>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("Segoe UI", 11);
    a.setFont(font);
    if (Connection::createInstance().createConnection()) {
        qDebug() << "Base de données prête pour l'interface.";
    } else {
        QMessageBox::critical(nullptr, "Base de données","Connexion à Oracle impossible. Vérifiez le DSN ODBC.");
    }
    QSqlQuery q;
    if (q.exec("SELECT USER FROM DUAL") && q.next())
        qDebug() << "Utilisateur Oracle :" << q.value(0).toString();
    if (q.exec("SELECT COUNT(*) FROM EMPLOYE") && q.next())
        qDebug() << "Nombre d'employés vus par l'appli :" << q.value(0).toInt();

    QObject::connect(&a, &QCoreApplication::aboutToQuit, []() {
        Connection::createInstance().closeConnection();
    });

    integration w;
    w.showMaximized();
    return QApplication::exec();
}