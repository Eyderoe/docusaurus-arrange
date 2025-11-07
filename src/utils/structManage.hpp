/**
* @file structManage.hpp
 * @brief 文件树管理
 * @details 节点和树的继承,目录结构的读取和写入
 */

#ifndef STRUCTMANAGE_HPP
#define STRUCTMANAGE_HPP


#include <QDir>
#include <QString>
#include <qtreewidget.h>
#include "fileProcess.hpp"
#include <iostream>
#include <utility>

#include "gui/enhancedTree.hpp"


class Node;
class StructManager;

void addFile (std::vector<Node*> &nodes, const QString &filePath);
void addFolder (std::vector<Node*> &nodes, const QString &folderPath);

template <typename parent>
void traverseRead (const QDir &folder, parent *parentNode);
template <typename parent>
void traverseWrite (const parent *parentNode);

class StructManager {
    public:
        StructManager () = default;
        explicit StructManager (const QDir &path);
        void readStruct (Tree *tree) const;
        [[nodiscard]] const QDir& getPath () const;
    private:
        QDir baseDir; ///< docs路径
};

#endif //STRUCTMANAGE_HPP
