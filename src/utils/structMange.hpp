#ifndef STRUCTMANGE_HPP
#define STRUCTMANGE_HPP


#include <QDir>
#include <QString>
#include <qtreewidget.h>

class Node;
class StructManger;

void traverse (const QDir &folder, QTreeWidget *tree);
void traverse (const QDir &folder, Node *node);


class Node final : public QTreeWidgetItem {
    public:
        explicit Node (QTreeWidget *parent = nullptr);
        explicit Node (QTreeWidgetItem *parent = nullptr);

        QString baseDir, displayName, actualName; // 目录,显示名称,实际名称
        int loc; // 位置
};

class StructManger {
    public:
        StructManger () = default;
        explicit StructManger (const QDir &path);
        void readStruct (QTreeWidget *tree);
        const QDir& getPath () const;
    private:
        QDir baseDir;
};

#endif //STRUCTMANGE_HPP
