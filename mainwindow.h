#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scopesetupwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private:
    Ui::MainWindow *ui;
    scopeSetupWindow *setupWindow;
    
public slots:
    void setStatusbarText(const QString& text);

private slots:
    void on_actionOpenSetupWindow_triggered();
    void on_actionStatusbasShowNumber_triggered(int number);

signals:
    void statusTextUpdate(const QString & text);
};

#endif // MAINWINDOW_H
