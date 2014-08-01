#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    void updatePlotCanvas();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
