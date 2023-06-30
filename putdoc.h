#ifndef PUTDOC_H
#define PUTDOC_H

#include <QDialog>

#include "dbworker.h"

namespace Ui {
class putDoc;
}

class putDoc : public QDialog
{
    Q_OBJECT

public:
    explicit putDoc(QWidget *parent = nullptr);
    ~putDoc();

public:
    dbworker *db;


private slots:
    void on_pushButton_push_clicked();

private:
    Ui::putDoc *ui;
};

#endif // PUTDOC_H
