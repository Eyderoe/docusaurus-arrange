#ifndef LICENSE_DIALOG_HPP
#define LICENSE_DIALOG_HPP

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui
{
class license_dialog;
}
QT_END_NAMESPACE

class license_dialog : public QDialog {
        Q_OBJECT
    public:
        explicit license_dialog (QWidget *parent = nullptr);
        ~license_dialog () override;
    private:
        Ui::license_dialog *ui;
};


#endif //LICENSE_DIALOG_HPP
