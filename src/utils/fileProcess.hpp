/**
* @file fileProcess.hpp
 * @brief 文件处理
 * @details 生成读取修改目录配置文件,生成读取修改文件配置
 */

#ifndef FILEPROCESS_HPP
#define FILEPROCESS_HPP


#include <json.hpp>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>
#include <QLine>
#include <fstream>
#include <QDir>


std::tuple<QString, int> readFolderConfig (const QString &folderPath);
std::tuple<QString, int> readFileConfig (const QString &filePath);
void writeFolderConfig (const QString &folderPath, int sidebarLoc);
void writeFileConfig (const QString &filePath, int sidebarLoc);


#endif //FILEPROCESS_HPP
