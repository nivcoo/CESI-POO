#include "WindowManager.h"
#include "./ui_WindowManager.h"

WindowManager::WindowManager(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::WindowManager) {
    ui->setupUi(this);
}

WindowManager::~WindowManager() {
    delete ui;
}

