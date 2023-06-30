#ifndef DBWORKER_H
#define DBWORKER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QComboBox>
#include <QSqlError>
#include <QMessageBox>

class dbworker
{
public:
    dbworker();

public:
    QSqlDatabase db;
    QSqlQuery *query;

public:
    int connectDb( QString host,
                     int port,
                     QString dbName,
                     QString userName,
                     QString password );

    void getDocList( QComboBox *cmb,
                     QString name,
                     QString surname );

    int deleteDoc( int id_param );

    int addDoc( int usr_id,
                int doc_id );


    QStringList listUser ( int i );

    QStringList listDoc ();

};

#endif // DBWORKER_H
