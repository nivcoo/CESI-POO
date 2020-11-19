#include "MainWindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::mainwindow),
        tabManager(new TabManager) {
    ui->setupUi(this);
    setWindowTitle("Test");
    setCentralWidget(tabManager);
    setObjectName("tabBar");

    //connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (buttonProfileClicked()));
}


MainWindow::~MainWindow() {
    delete tabManager;
    delete ui;
}





