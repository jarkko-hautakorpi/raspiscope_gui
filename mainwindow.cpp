#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scopesetupwindow.h"
#include "serialdatalink.h"
#include "datalink_commands.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("RaspiScope 0.1 alpha", 1500);

    //scopeSettings settings;
    static serialDataLink link;


    // Status bar SLOT connections
    connect(&link, SIGNAL(errorMessage(const QString&)),
            this, SLOT(setStatusbarText(const QString&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpenSetupWindow_triggered()
{
    setupWindow = new scopeSetupWindow(this);
    setupWindow->setModal(true);
    if(this->isFullScreen()) {
        setupWindow->showFullScreen();
    }
    setupWindow->exec();
}

void MainWindow::setStatusbarText(const QString &text) {
    ui->statusbar->showMessage(text,2000);
}



void MainWindow::on_actionStatusbasShowNumber_triggered(int number)
{
    QString text = (QString) number;
    this->setStatusbarText(text);
}
