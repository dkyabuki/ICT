#ifndef DIALCOMM_H
#define DIALCOMM_H

#include <QDialog>

namespace Ui {
class DialComm;
}

class DialComm : public QDialog
{
    Q_OBJECT

public:
    explicit DialComm(QWidget *parent = 0);
    ~DialComm();

private:
    Ui::DialComm *ui;
};

#endif // DIALCOMM_H
