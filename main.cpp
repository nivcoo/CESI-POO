#include <QtWidgets/QApplication>
#include "window/main/MainWindow.h"
#include "ihm/IHM.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("CESI");
    QCoreApplication::setApplicationName("CESI");
    QFile file(":global.qss");
    if (file.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(StyleSheet);

    }
    new IHM();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
