#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "config.h"
#include "dialt.h"
#include "dialr.h"
#include "dialm.h"
#include "dialogc.h"
#include "dialtorplot.h"
#include "dialposplot.h"
#include "dialquit.h"
#include "sequenceplot.h"
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
    void close_program();

    void save_config();

    void load_config();

    void on_taskButton_clicked();

    void on_convButton_clicked();

    void on_regButton_clicked();

    void on_modeButton_clicked();

    void on_posSaveButton_clicked();

    void on_torSaveButton_clicked();

    void on_torConfigButton_clicked();

    void on_posConfigButton_clicked();

    void on_pushButton_clicked();
    
private:
    double timepot, timetor;
    void updatePlotCanvas();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
