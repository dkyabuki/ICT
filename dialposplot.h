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

private slots:
    void on_physButton_clicked();

    void on_vButton_clicked();

    void on_vButton_toggled(bool checked);

    void on_physButton_toggled(bool checked);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialPosPlot *ui;
};

#endif // DIALPOSPLOT_H
