#include "structManage.hpp"


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
    auto [name,location] = readFileConfig(filePath);
    nodes.push_back(new Node(filePath, name, location, false));
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
    auto [name,location] = readFolderConfig(folderPath);
    nodes.push_back(new Node(folderPath, name, location, true));
}

/**
 * @brief 递归新建树节点
 * @param folder 文件夹路径
 * @param tree 根树
 */
void traverseRead (const QDir &folder, QTreeWidget *tree) {
    // 获取子文件夹/文件
    QStringList files = folder.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    std::vector<Node*> nodes;
    for (auto &fileName : files) {
        QString child{folder.filePath(fileName)};
        if (QFileInfo info(child); info.isFile())
            addFile(nodes, child);
        else
            addFolder(nodes, child);
    }
    // 排序添加
    std::ranges::stable_sort(nodes, std::ranges::less{}, &Node::sidebarLoc);
    for (const auto node : nodes)
        tree->addTopLevelItem(node);
    // 遍历
    for (const auto node : nodes) {
        if (node->isFolder)
            traverseRead(node->baseDir, node);
    }
}
/**
 * @brief 递归新建树节点
 * @param folder 文件夹路径
 * @param parentNode 父节点
 */
void traverseRead (const QDir &folder, Node *parentNode) {
    // 获取子文件夹/文件
    QStringList files = folder.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    std::vector<Node*> nodes;
    for (auto &fileName : files) {
        QString child{folder.filePath(fileName)};
        if (QFileInfo info(child); info.isFile())
            addFile(nodes, child);
        else
            addFolder(nodes, child);
    }
    // 排序添加
    std::ranges::stable_sort(nodes, std::ranges::less{}, &Node::sidebarLoc);
    for (const auto node : nodes)
        parentNode->addChild(node);
    // 遍历
    for (const auto node : nodes) {
        if (node->isFolder)
            traverseRead(node->baseDir, node);
    }
}

/**
 * @brief 递归更改树节点侧边栏位置
 * @param parentNode 父节点
 */
void traverseWrite (const Node *parentNode) {
    int loc{};
    for (int i = 0; i < parentNode->childCount(); ++i) {
        loc += 10;
        const Node *child = dynamic_cast<Node*>(parentNode->child(i));
        if (loc != child->sidebarLoc) {
            if (child->isFolder)
                writeFolderConfig(child->baseDir, loc);
            else
                writeFileConfig(child->baseDir, loc);
        }
        if (child->isFolder)
            traverseWrite(child);
    }
}

StructManager::StructManager (const QDir &path): baseDir(path) {}

/**
 * @brief 创建文件树
 */
void StructManager::readStruct (QTreeWidget *tree) const {
    traverseRead(baseDir, tree);
}

/**
 * @brief 获取文档根目录
 * @return 根目录
 */
const QDir& StructManager::getPath () const {
    return baseDir;
}
