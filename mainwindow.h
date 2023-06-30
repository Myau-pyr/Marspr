#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "dbworker.h"
#include "putdoc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    dbworker *db;
    putDoc *doc;

private:
    void createUI( const
                   QStringList &headers );


private slots:
    void on_pushButton_checkDoc_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_putDoc_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
