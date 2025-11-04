#include "fileProcess.hpp"


using json = nlohmann::ordered_json; // 保证顺序一致性


/**
 * @brief 读取文件夹配置
 * @param folderPath 文件夹路径
 * @return <显示名称,侧边栏位置>
 */
std::tuple<QString, int> readFolderConfig (const QString &folderPath) {
    int position{0};
    QString name{};
    // 先取文件夹名称
    name = QDir(folderPath).dirName();
    // 再尝试在config里面找东西
    const QString filePath = folderPath + QDir::separator() + "_category_.json";
    QFile configFile(filePath);
    if (!configFile.exists()) {
        configFile.open(QIODevice::WriteOnly);
        configFile.close();
    }
    // 读取json
    configFile.open(QIODevice::ReadOnly);
    QTextStream stream(&configFile);
    json config = json::parse(stream.readAll().toUtf8().constData());
    auto it = config.find("position");
    if (it != config.end())
        position = it.value();
    it = config.find("label");
    if (it != config.end())
        name = QString::fromStdString(it.value());
    configFile.close();
    return {name, position};
}

/**
 * @brief 读取文件头
 * @param filePath 文件路径
 * @return <显示名称,侧边栏位置>
 */
std::tuple<QString, int> readFileConfig (const QString &filePath) {
    int position{};
    QString name{};
    QFile file(filePath);
    enum class headerStatus { notIn, in, pass }; // 状态机 真好用
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fileStream(&file);
    fileStream.setEncoding(QStringConverter::Utf8);
    // 开始处理
    headerStatus status = headerStatus::notIn;
    while (!fileStream.atEnd()) {
        const QString line = fileStream.readLine();
        // 状态机
        switch (status) {
            case headerStatus::notIn: // 最开始进来的时候
                if (!line.startsWith("---"))
                    status = headerStatus::pass;
                else
                    status = headerStatus::in;
                break;
            case headerStatus::in: // yaml-header里面
                if (line.startsWith("---") || line.startsWith("#"))
                    status = headerStatus::pass;
                else {
                    if (line.startsWith("sidebar_position:")) {
                        position = line.section(':', -1).trimmed().toInt();
                    } else if (line.startsWith("title:")) {
                        name = line.section(':', -1).trimmed();
                    }
                }
                break;
            case headerStatus::pass: // 出yaml-header了
                if (line.startsWith("# "))
                    name = line.section('#', -1).trimmed();
                break;
        }
        // 夯: yaml-header里的title
        // 人上人: 一级标题(#)
        if (!name.isEmpty())
            return {name, position};
    }
    // 拉: 文件名
    return {QFileInfo(filePath).completeBaseName(), position};
}

/**
 * @brief 将侧边栏位置写入文件夹配置
 * @param folderPath 文件夹路径
 * @param sidebarLoc 侧边栏位置
 */
void writeFolderConfig (const QString &folderPath, const int sidebarLoc) {
    QFile configFile(folderPath + QDir::separator() + "_category_.json");
    configFile.open(QIODevice::ReadWrite);
    QTextStream stream(&configFile);
    json config = json::parse(stream.readAll().toUtf8().constData());
    config["position"] = sidebarLoc;
    configFile.resize(0);
    configFile.seek(0);
    QTextStream outStream(&configFile);
    outStream << QString::fromStdString(config.dump(4));
    configFile.close();
}

/**
 * @brief 将侧边栏位置写入文件头
 * @param filePath 文件路径
 * @param sidebarLoc 侧边栏位置
 */
void writeFileConfig (const QString &filePath, const int sidebarLoc) {
    QFile file(filePath);
    enum class headerStatus { notIn, in, pass };
    int sidebarLineLoc{-2}; // -2表示没有yaml-header,-1表示存在yaml-header但没有位置,其他表示位置
    // 先读取
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fileStream(&file);
    fileStream.setEncoding(QStringConverter::Utf8);
    headerStatus status = headerStatus::notIn;
    int lineLoc{};
    while (!fileStream.atEnd()) {
        ++lineLoc;
        const QString line = fileStream.readLine();
        // 状态机
        bool out{false};
        switch (status) {
            case headerStatus::notIn:
                if (!line.startsWith("---"))
                    status = headerStatus::pass;
                else {
                    status = headerStatus::in;
                    sidebarLineLoc = -1;
                }
                break;
            case headerStatus::in: // yaml-header里面
                if (line.startsWith("---"))
                    status = headerStatus::pass;
                else {
                    if (line.startsWith("sidebar_position:")) {
                        sidebarLineLoc = lineLoc;
                        out = true;
                    }
                }
                break;
            case headerStatus::pass: // 出yaml-header了
                out = true;
                break;
        }
        if (out)
            break;
    }
    file.close();
    // 后写入
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QStringList lines;
    while (!in.atEnd())
        lines.append(in.readLine());
    if (sidebarLineLoc == -2) { // 不存在yaml-header
        lines.insert(0, "");
        lines.insert(0, "---");
        lines.insert(0, "sidebar_position: " + QString::number(sidebarLoc));
        lines.insert(0, "---");
    } else if (sidebarLineLoc == -1) { // 存在yaml-header,但无侧边栏位置
        lines.insert(1, "sidebar_position: " + QString::number(sidebarLoc));
    } else { // 存在侧边栏位置但需要修改
        lines[sidebarLineLoc - 1] = "sidebar_position: " + QString::number(sidebarLoc);
    }
    file.resize(0);
    file.seek(0);
    QTextStream out(&file);
    for (const QString &line : lines)
        out << line << Qt::endl;
    file.close();
}
