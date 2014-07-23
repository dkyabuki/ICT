#ifndef DIALT_H
#define DIALT_H

#include <QDialog>
#include "config.h"

namespace Ui {
class Dialt;
}

class Dialt : public QDialog
{
    Q_OBJECT

public:
    explicit Dialt(QWidget *parent = 0);
    ~Dialt();

private slots:
    void on_sensorCheck_stateChanged(int arg1);
    void on_controlCheck_stateChanged(int arg1);
    void on_actuatorCheck_stateChanged(int arg1);
    void on_serialCheck_stateChanged(int arg1);

    void on_sensorEnable_stateChanged(int arg1);
    void on_controlEnable_stateChanged(int arg1);
    void on_actuatorEnable_stateChanged(int arg1);
    void on_serialEnable_stateChanged(int arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialt *ui;
};

#endif // DIALT_H
