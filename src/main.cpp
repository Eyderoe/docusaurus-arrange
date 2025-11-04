#include "QApplication"
#include "gui/main_widget.hpp"
#include "QSettings"

int main (int argc, char *argv[]) {
    QApplication::setOrganizationName("Eyderoe");
    QApplication::setApplicationName("DocusaurusArrange");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication a(argc, argv);
    main_widget w;
    w.show();
    return QApplication::exec();
}
