#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "config.h"
#include "dialt.h"
#include "dialr.h"
#include "dialogc.h"
#include "dialtorplot.h"
#include "dialposplot.h"
#include "dialquit.h"
#include "sequenceplot.h"
#include "threadStarter.h"
#include "dialcomm.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QAction>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qwt_plot_item.h>
#include <QErrorMessage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //Utilities
    void close_program();
    void save_config();
    void load_config();

    //Plot
    void update_plot_canvas();
    void append_pos(const QPointF &point);
    void append_ext(const QPointF &point);

    //GUI related
    void control_signal_emitted(bool on);
    void control_pause_signal_emitted(bool on);
    void show_error(QString str);
    void show_status(QString str);
    void update_connection(QStringList str);

    //Thread related
    void connect_thread_signals();

    //Button slots
    void on_taskButton_clicked();
    void on_convButton_clicked();
    void on_regButton_clicked();
    void on_posSaveButton_clicked();
    void on_torSaveButton_clicked();
    void on_torConfigButton_clicked();
    void on_posConfigButton_clicked();
    void on_pushButton_clicked();
    void on_controlStartButton_clicked();
    void on_controlPauseButton_clicked();
    void on_controlStopButton_clicked();
    void on_commConfButton_clicked();

    void commConfSeq();

signals:
    void on_controlStartup(bool on);
    void on_controlPause(bool on);
    void comm_config(QHostAddress ipconf, quint16 portconf);

    //SINAIS PARA A COMM.
    void config();
    void sendRequest(CommMessage msg);
    void startComm();
    void stopComm();
    void pauseComm(bool pause);
    void finishComm();

private:
    threadStarter *thread;
    double timepot, timetor;
    QPalette red;
    QPalette black;
    Ui::MainWindow *ui;
    bool running;
};

#endif // MAINWINDOW_H
