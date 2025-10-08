#include "QApplication"
#include "gui/main_widget.hpp"

int main (int argc, char *argv[]) {
    QApplication a(argc, argv);
    main_widget w;
    w.show();
    return QApplication::exec();
}
