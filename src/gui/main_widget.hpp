#ifndef MAIN_WIDGET_HPP
#define MAIN_WIDGET_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class main_widget; }
QT_END_NAMESPACE

class main_widget : public QWidget {
Q_OBJECT

public:
    explicit main_widget(QWidget *parent = nullptr);
    ~main_widget() override;

private:
    Ui::main_widget *ui;
};


#endif //MAIN_WIDGET_HPP
