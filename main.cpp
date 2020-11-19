#include "window/main/MainWindow.h"
#include "ihm/IHM.h"


int main(int argc, char *argv[]) {


    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("CESI");
    QCoreApplication::setApplicationName("CESI");
    QFile File(":global.qss");
    if (File.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(File.readAll());
        a.setStyleSheet(StyleSheet);

    }
    new IHM();
    MainWindow w;
    w.show();
    return a.exec();
}
