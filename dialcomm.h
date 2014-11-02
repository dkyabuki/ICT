#ifndef DIALCOMM_H
#define DIALCOMM_H

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class DialComm;
}

class DialComm : public QDialog
{
    Q_OBJECT

public:
    explicit DialComm(QWidget *parent = 0);
    ~DialComm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_serialButton_clicked(bool checked);

    void on_udpButton_clicked(bool checked);

    void on_udpButton_toggled(bool checked);

    void on_serialButton_toggled(bool checked);

    void on_serialCombo_currentIndexChanged(int index);

private:
    void updateSerial();

    Ui::DialComm *ui;
};

#endif // DIALCOMM_H
