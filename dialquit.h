#ifndef DIALQUIT_H
#define DIALQUIT_H

#include <QDialog>

namespace Ui {
class DialQuit;
}

class DialQuit : public QDialog
{
    Q_OBJECT

public:
    explicit DialQuit(QWidget *parent = 0);
    ~DialQuit();
    bool getAnswer();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialQuit *ui;
    bool quitProgram;
};

#endif // DIALQUIT_H
