#ifndef DIALPOSPLOT_H
#define DIALPOSPLOT_H

#include <QDialog>

namespace Ui {
class DialPosPlot;
}

class DialPosPlot : public QDialog
{
    Q_OBJECT

public:
    explicit DialPosPlot(QWidget *parent = 0);
    ~DialPosPlot();

private:
    Ui::DialPosPlot *ui;
};

#endif // DIALPOSPLOT_H
