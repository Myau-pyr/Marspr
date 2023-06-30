#include "putdoc.h"
#include "ui_putdoc.h"

putDoc::putDoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::putDoc)
{
    ui->setupUi(this);
    db = new dbworker();

    ui->comboBox_usr->addItems(db->listUser(2));
    ui->comboBox_docs->addItems(db->listDoc());
}

putDoc::~putDoc()
{
    delete ui;
}

void putDoc::on_pushButton_push_clicked()
{
    int usr_id = ui->comboBox_usr->currentIndex() + 1;
    int doc_id = ui->comboBox_docs->currentIndex() + 1;

    db->addDoc(usr_id, doc_id);
}
