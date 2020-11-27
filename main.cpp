#include <QtWidgets/QApplication>
#include "window/main/MainWindow.h"
#include "model/ModelManager.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("CESI");
    QCoreApplication::setApplicationName("CESI");
    QFile file(":global.qss");
    if (file.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(StyleSheet);
    }
    new ModelManager();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
