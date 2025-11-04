/**
* @file enhancedTree.hpp
 * @brief 树和节点子类
 * @details 继承了树和节点,拓展了功能
 */

#ifndef ENHANCEDTREE_HPP
#define ENHANCEDTREE_HPP


#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QDropEvent>


class Node;
class Tree;

class Node final : public QTreeWidgetItem {
    public:
        Node () = default;
        Node (QString baseDir, const QString &name, int sidebarLoc, bool isFolder);

        QString baseDir; ///< 文件或目录路径
        int sidebarLoc; ///< 侧边栏位置
        bool isFolder; ///< 类型(0文件1目录)
};

class Tree final : public QTreeWidget {
    public:
        explicit Tree (QWidget *parent = nullptr);
    protected:
        void dropEvent (QDropEvent *event) override;
};


#endif //ENHANCEDTREE_HPP
