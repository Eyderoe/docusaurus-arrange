/**
* @file main_widget.hpp
 * @brief 唯一窗口
 * @details 所有的窗口行为,控件管理
 */

#ifndef MAIN_WIDGET_HPP
#define MAIN_WIDGET_HPP


#include "enhancedTree.hpp"
#include <QWidget>
#include "utils/structManage.hpp"
#include <iostream>
#include <QSettings>
#include "ui_main_widget.h"
#include "license_dialog.hpp"


QT_BEGIN_NAMESPACE
namespace Ui
{
class main_widget;
}
QT_END_NAMESPACE

class main_widget final : public QWidget {
        Q_OBJECT
    public:
        explicit main_widget (QWidget *parent = nullptr);
        ~main_widget () override;
    private:
        Ui::main_widget *ui;
        StructManager manger;

        void setupTree () const;
    private Q_SLOTS:
        void on_readButton_clicked ();
        void on_writeButton_clicked ();
        void on_licenseButton_clicked ();
};


#endif //MAIN_WIDGET_HPP
