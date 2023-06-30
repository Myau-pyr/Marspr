#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new dbworker();
    db->connectDb("127.0.0.1", 5432, "postgres", "postgres", "lostdox1");

    ui->comboBox_getUser->addItems(db->listUser(1));
}


void MainWindow::createUI(const QStringList &headers)
{
    QStringList list;
    QString name_p;

    name_p = db->listUser(1)[ui->comboBox_getUser->currentIndex()];
    list = name_p.split(" ");


    ui->tableWidget_doc->setRowCount(0);
    ui->tableWidget_doc->setColumnCount                                 (5);
    ui->tableWidget_doc->setShowGrid                                    (true);
    ui->tableWidget_doc->setHorizontalHeaderLabels                      (headers);
    ui->tableWidget_doc->horizontalHeader()->setStretchLastSection      (true);
    ui->tableWidget_doc->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_doc->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_doc->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableWidget_doc->setColumnHidden(4, true);

    db->getDocList(ui->comboBox_getUser, list[0], list[1]);

    for(unsigned int i = 0; db->query->next(); i++)
    {
        ui->tableWidget_doc->insertRow(i);
        ui->tableWidget_doc->setItem(i,0, new QTableWidgetItem(db->query->value(0).toString()));
        ui->tableWidget_doc->setItem(i,1, new QTableWidgetItem(db->query->value(1).toString()));
        ui->tableWidget_doc->setItem(i,2, new QTableWidgetItem(db->query->value(2).toString()));
        ui->tableWidget_doc->setItem(i,3, new QTableWidgetItem(db->query->value(3).toString()));
        ui->tableWidget_doc->setItem(i,4, new QTableWidgetItem(db->query->value(4).toString()));
    }
    ui->tableWidget_doc->horizontalHeader()->resizeSection(0, 175);
    ui->tableWidget_doc->horizontalHeader()->resizeSection(1, 175);
}


void MainWindow::on_pushButton_checkDoc_clicked()
{
    this->createUI ( QStringList() <<  ( "Имя" )
                                   <<  ( "Фамилия" )
                                   <<  ( "Отчество" )
                                   <<  ( "Наименование документа" )
                                   <<  ( "Идентификационный номер" ));
}

void MainWindow::on_pushButton_delete_clicked()
{
    int id = ui->tableWidget_doc->selectionModel()->currentIndex().siblingAtColumn(4).data().toInt(); //id
    qDebug() << id;

    db->deleteDoc( id );

    this->createUI ( QStringList() <<  ( "Имя" )
                                   <<  ( "Фамилия" )
                                   <<  ( "Отчество" )
                                   <<  ( "Наименование документа" )
                                   <<  ( "Идентификационный номер" ));
}

void MainWindow::on_pushButton_putDoc_clicked()
{
    doc = new putDoc();
    doc->setWindowTitle("Взять документ");
    doc->exec();

    this->createUI ( QStringList() <<  ( "Имя" )
                                   <<  ( "Фамилия" )
                                   <<  ( "Отчество" )
                                   <<  ( "Наименование документа" )
                                   <<  ( "Идентификационный номер" ));
}

MainWindow::~MainWindow()
{
    delete ui;
}



