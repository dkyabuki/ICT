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
    void save_config();

    void load_config();

    void on_taskButton_clicked();

    void on_convButton_clicked();

    void on_regButton_clicked();

    void on_modeButton_clicked();

    void on_posSaveButton_clicked();

    void on_torSaveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
