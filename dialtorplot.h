#ifndef DIALTORPLOT_H
#define DIALTORPLOT_H

#include <QDialog>

namespace Ui {
class DialTorPlot;
}

class DialTorPlot : public QDialog
{
    Q_OBJECT

public:
    explicit DialTorPlot(QWidget *parent = 0);
    ~DialTorPlot();

private slots:
    void on_vButton_clicked();

    void on_physButton_clicked();

    void on_vButton_toggled(bool checked);

    void on_physButton_toggled(bool checked);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialTorPlot *ui;
};

#endif // DIALTORPLOT_H
