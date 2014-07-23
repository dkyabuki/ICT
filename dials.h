#ifndef DIALS_H
#define DIALS_H

#include <QDialog>

namespace Ui {
class DialS;
}

class DialS : public QDialog
{
    Q_OBJECT

public:
    explicit DialS(QWidget *parent = 0);
    ~DialS();

private:
    Ui::DialS *ui;
};

#endif // DIALS_H
