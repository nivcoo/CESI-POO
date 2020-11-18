#include "manager/window/WindowManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowManager w;
    w.show();
    return a.exec();
}
