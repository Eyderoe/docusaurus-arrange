#include "structMange.hpp"


Node::Node (QString baseDir, QString name, const int sidebarLoc, const bool isFolder):
    baseDir(std::move(baseDir)), name(std::move(name)), sidebarLoc(sidebarLoc), isFolder(isFolder) {}

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
    // 处理,有配置读取配置, 没有配置添加配置
}

/**
 * @brief 假如有可能,添加一个目录作为节点
 * @param nodes 临时节点数组
 * @param folderPath 目录
 */
void addFolder (std::vector<Node*> &nodes, const QString &folderPath) {
    // 有效目录,根下至少有一个md或mdx / 有配置文件
    QStringList files = QDir(folderPath).entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    bool available{false};
    for (auto &file : files) {
        if (file.endsWith(".md") || file.endsWith(".mdx") || (file == "_category_.json")) {
            available = true;
            break;
        }
    }
    if (!available)
        return;
    // 处理,没有文件生成文件
    const QString configPath{folderPath + QDir::separator() + "_category_.json"};
    const auto result = readFolderConfig(configPath); // 沟槽的qt5.23
    nodes.emplace_back(new Node(folderPath, result.first, result.second, true));
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
                     [](const Node *a, const Node *b) { return (a->sidebarLoc) < (b->sidebarLoc); });
    for (const auto node : nodes)
        tree->addTopLevelItem(node);
    // 遍历
    for (const auto node : nodes) {
        if (node->isFolder)
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
              [](const Node *a, const Node *b) { return (a->sidebarLoc) < (b->sidebarLoc); });
    for (const auto node : nodes)
        parentNode->addChild(node);
    // 遍历
    for (const auto node : nodes) {
        if (node->isFolder)
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
const QDir& StructManger::getPath () const {
    return baseDir;
}
