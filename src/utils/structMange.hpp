/**
 * @file structMange.hpp
 * @brief 文件树管理
 * @details 节点和树的继承,目录结构的读取和写入
 */

#ifndef STRUCTMANGE_HPP
#define STRUCTMANGE_HPP


#include <QDir>
#include <QString>
#include <qtreewidget.h>
#include "fileProcess.hpp"
#include <iostream>
#include <utility>


class Node;
class StructManger;

void traverse (const QDir &folder, QTreeWidget *tree);
void traverse (const QDir &folder, Node *parentNode);

class Node final : public QTreeWidgetItem {
    public:
        explicit Node (QTreeWidget *parent = nullptr);
        explicit Node (QTreeWidgetItem *parent = nullptr);
        Node(QString baseDir, QString name,int sidebarLoc,bool isFolder);

        QString baseDir; ///< 文件或目录路径
        QString name; ///< 显示在Docusaurus中的名称
        int sidebarLoc; ///< 侧边栏位置
        bool isFolder; ///< 类型(0文件1目录)
};

class StructManger {
    public:
        StructManger () = default;
        explicit StructManger (const QDir &path);
        void readStruct (QTreeWidget *tree);
        const QDir& getPath () const;
    private:
        QDir baseDir; ///< docs路径
};

#endif //STRUCTMANGE_HPP
