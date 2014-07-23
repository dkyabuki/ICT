#ifndef DIALM_H
#define DIALM_H

#include <QDialog>
#include "config.h"

namespace Ui {
class Dialm;
}

class Dialm : public QDialog
{
    Q_OBJECT

public:
    explicit Dialm(QWidget *parent = 0);
    ~Dialm();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialm *ui;
};

#endif // DIALM_H
