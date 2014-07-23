#ifndef DIALOGC_H
#define DIALOGC_H

#include <QDialog>

namespace Ui {
class Dialogc;
}

class Dialogc : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogc(QWidget *parent = 0);
    ~Dialogc();

private:
    Ui::Dialogc *ui;
};

#endif // DIALOGC_H
