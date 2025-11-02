/**
 * @file main_widget.hpp
 * @brief 唯一窗口
 * @details 所有的窗口行为,控件管理
 */

#ifndef MAIN_WIDGET_HPP
#define MAIN_WIDGET_HPP

#include <QWidget>
#include "utils/structMange.hpp"


QT_BEGIN_NAMESPACE
namespace Ui
{
class main_widget;
}
QT_END_NAMESPACE

class main_widget : public QWidget {
        Q_OBJECT
    public:
        explicit main_widget (QWidget *parent = nullptr);
        ~main_widget () override;
    private:
        Ui::main_widget *ui;
        StructManger manger;

        void setupTree () const;
    private Q_SLOTS:
        void on_readButton_clicked ();
        void on_pushButton_clicked ();
};


#endif //MAIN_WIDGET_HPP
