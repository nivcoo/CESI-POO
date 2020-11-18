#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowManager; }
QT_END_NAMESPACE

class WindowManager : public QMainWindow
{
Q_OBJECT

public:
    WindowManager(QWidget *parent = nullptr);
    ~WindowManager();

private:
    Ui::WindowManager *ui;
};
#endif // WINDOWSMANAGER_H
