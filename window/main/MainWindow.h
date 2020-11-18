//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_MAINWINDOW_H
#define MAIN_CPP_MAINWINDOW_H


#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QItemSelection>
#include "../content/TabManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    TabManager *tabManager;

    Ui::MainWindow *ui;
};

#endif //MAIN_CPP_MAINWINDOW_H
