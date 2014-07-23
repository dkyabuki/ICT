#ifndef DIALR_H
#define DIALR_H

#include <QDialog>
#include "config.h"
#include <stdlib.h>
#include <qstring.h>

namespace Ui {
class Dialr;
}

class Dialr : public QDialog
{
    Q_OBJECT

public:
    explicit Dialr(QWidget *parent = 0);
    ~Dialr();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialr *ui;
};

#endif // DIALR_H
