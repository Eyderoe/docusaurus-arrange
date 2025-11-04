#include "enhancedTree.hpp"

#include <iostream>

Node::Node (QString baseDir, const QString &name, const int sidebarLoc, const bool isFolder):
    baseDir(std::move(baseDir)), sidebarLoc(sidebarLoc), isFolder(isFolder) {
    setText(0, name);
    if (isFolder)
        setForeground(0, QBrush(QColor(92, 145, 232))); // 很好看的蓝色
    else
        setForeground(0, QBrush(QColor(232, 135, 92))); // 很好看的橙色
}

Tree::Tree (QWidget *parent) {}

/**
 * @brief 阻止跨层级拖放
 * @param event 放置事件
 */
void Tree::dropEvent (QDropEvent *event) {
    // 移动节点
    const Node *sourceItem = dynamic_cast<Node*>(currentItem());
    // 参考节点
    const Node *referItem = dynamic_cast<Node*>(itemAt(event->position().toPoint()));
    const QAbstractItemView::DropIndicatorPosition dropType = dropIndicatorPosition();
    // 因为只需要判断移动前后父节点是否一样
    const Node *parentItem = nullptr;
    switch (dropType) {
        case QAbstractItemView::AboveItem: // 上方
        case QAbstractItemView::BelowItem: // 下方
            parentItem = dynamic_cast<Node*>(referItem->parent());
            break;
        case QAbstractItemView::OnItem: // 内部
            parentItem = referItem;
            break;
        case QAbstractItemView::OnViewport: // 空白处(顶级目录)
            break;
    }
    // 判断
    if (parentItem != sourceItem->parent()) {
        event->ignore();
        return;
    }
    QTreeWidget::dropEvent(event);
}
