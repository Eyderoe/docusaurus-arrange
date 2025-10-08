#include "structMange.hpp"


/**
 * @brief 假如有可能,添加一个文件作为节点
 * @param nodes 临时节点数组
 * @param filePath 文件
 */
void addFile (std::vector<Node*> &nodes, const QString &filePath) {
    // 只选择md和mdx
    const QString suffix{QFileInfo(filePath).suffix()};
    if ((suffix != "md") && (suffix != "mdx"))
        return;

}

/**
 * @brief 假如有可能,添加一个目录作为节点
 * @param nodes 临时节点数组
 * @param folderPath 目录
 */
void addFolder (std::vector<Node*> &nodes, QString &folderPath) {

}

/**
 * @brief 递归新建树节点
 * @param folder 文件夹路径
 * @param tree 根树
 */
void traverse (const QDir &folder, QTreeWidget *tree) {
    // 获取子文件夹/文件
    QStringList files = folder.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    std::vector<Node*> nodes;
    for (auto &fileName : files) {
        QString child{folder.filePath(fileName)};
        QFileInfo info(child);
        if (info.isFile())
            addFile(nodes, child);
        else
            addFolder(nodes, child);
    }
    // 排序添加
    std::stable_sort(nodes.begin(), nodes.end(),
              [](const Node *a, const Node *b) { return (a->loc) < (b->loc); });
    for (const auto node : nodes)
        tree->addTopLevelItem(node);
    // 遍历
    for (const auto node : nodes) {
        QFileInfo info(node->baseDir);
        if (info.isDir())
            traverse(node->baseDir, node);
    }
}
/**
 * @brief 递归新建树节点
 * @param folder 文件夹路径
 * @param parentNode 父节点
 */
void traverse (const QDir &folder, Node *parentNode) {
    // 获取子文件夹/文件
    QStringList files = folder.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    std::vector<Node*> nodes;
    for (auto &fileName : files) {
        QString child{folder.filePath(fileName)};
        QFileInfo info(child);
        if (info.isFile())
            addFile(nodes, child);
        else
            addFolder(nodes, child);
    }
    // 排序添加
    std::sort(nodes.begin(), nodes.end(),
              [](const Node *a, const Node *b) { return (a->loc) < (b->loc); });
    for (const auto node : nodes)
        parentNode->addChild(node);
    // 遍历
    for (const auto node : nodes) {
        QFileInfo info(node->baseDir);
        if (info.isDir())
            traverse(node->baseDir, node);
    }
}


StructManger::StructManger (const QDir &path): baseDir(path) {}

/**
 * @brief 创建文件树
 */
void StructManger::readStruct (QTreeWidget *tree) {
    traverse(baseDir, tree);
}

/**
 * @brief 获取文档根目录
 * @return 根目录
 */
const QDir & StructManger::getPath () const {
    return baseDir;
}
