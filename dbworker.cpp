#include "dbworker.h"

dbworker::dbworker()
{

}

int dbworker::connectDb(QString hostName, int port, QString dbName, QString userName, QString password)
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(hostName);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(password);

    if(!db.open()) {
        qDebug() << "Database not open! Data: " + db.lastError().text();
        return 1;
    }
    else {
         qDebug() << "Database " + dbName + " is open!";
         return 0;
    }
}

void dbworker::getDocList(QComboBox *cmb, QString name, QString surname)
{
    query = new QSqlQuery(db);

    if(cmb->currentText() == "Все пользователи")
        query->exec("SELECT users.name, users.surname, users.patronymic, documents.doc_name, doc_check.id FROM doc_check "
                    "JOIN documents ON documents.id = doc_check.doc_id "
                    "JOIN users ON users.id = doc_check.user_id");
    else
        query->exec("SELECT users.name, users.surname, users.patronymic, documents.doc_name, doc_check.id FROM doc_check "
                    "JOIN documents ON documents.id = doc_check.doc_id "
                    "JOIN users ON users.id = doc_check.user_id WHERE users.name = '" +name + "' AND users.surname = '" + surname + "'");


}

int dbworker::deleteDoc(int id_param)
{
    query = new QSqlQuery(db);
    query->prepare("DELETE FROM doc_check WHERE id = :id_p");
    query->bindValue(":id_p", id_param);

    if(!query->exec()) {
        qDebug() << "Error delete!" + query->lastError().text();
        return 1;
    }
    else {
        qDebug() << "Success delete!";
        return 0;
    }

}

int dbworker::addDoc(int usr_id, int doc_id)
{
    query = new QSqlQuery(db);

    query->prepare("INSERT INTO doc_check (user_id, doc_id) VALUES(:usr_p, :doc_p)");
    query->bindValue(":usr_p", usr_id);
    query->bindValue(":doc_p", doc_id);

    if(!query->exec()) {
        QMessageBox::critical(0, "Ошибка взятия", "Документ занят другим пользователем!");
        return 1;
    }
    else {
        qDebug() << "Success insert!";
        return 0;
    }
}

QStringList dbworker::listUser(int i)
{
    query = new QSqlQuery(db);
    QStringList list;

    if(i == 1) {
        list.append("Все пользователи");
    }

    query->exec("SELECT name, surname, patronymic FROM users");

    for(int i = 0; query->next(); i++)
        list << query->value(0).toString() + " " + query->value(1).toString() + " " + query->value(2).toString();

    return list;
}

QStringList dbworker::listDoc()
{
    query = new QSqlQuery(db);
    QStringList list;

    query->exec("SELECT doc_name FROM documents");

    for(int i = 0; query->next(); i++)
        list << query->value(0).toString();

    return list;
}
