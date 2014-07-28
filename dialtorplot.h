#ifndef DIALTORPLOT_H
#define DIALTORPLOT_H

#include <QDialog>

namespace Ui {
class dialTorPlot;
}

class dialTorPlot : public QDialog
{
    Q_OBJECT

public:
    explicit dialTorPlot(QWidget *parent = 0);
    ~dialTorPlot();

private:
    Ui::dialTorPlot *ui;
};

#endif // DIALTORPLOT_H
