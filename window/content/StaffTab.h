
#ifndef MAIN_CPP_STAFFTAB_H
#define MAIN_CPP_STAFFTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class StaffTab : public QWidget
{
Q_OBJECT

public:
    StaffTab(QWidget *parent = nullptr);
};

#endif