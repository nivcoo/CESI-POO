
#ifndef MAIN_CPP_ORDERTAB_H
#define MAIN_CPP_ORDERTAB_H

#include <QWidget>
#include <QtCore>
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class OrderTab : public QWidget
{
Q_OBJECT

public:
    OrderTab(QWidget *parent = nullptr);
};

#endif