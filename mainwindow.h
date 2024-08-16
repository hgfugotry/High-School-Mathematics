#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculateButton_clicked();
    void on_helpButton_clicked();
    void on_createAVariableButton_clicked();

    void actionOpenSlot();
    void actionSaveAsSlot();

    void on_deleteAVariableButton_clicked();

    void on_versionButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
