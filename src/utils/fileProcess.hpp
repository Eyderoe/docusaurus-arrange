/**
 * @file fileProcess.hpp
 * @brief 文件处理
 * @details 生成读取修改目录配置文件,生成读取修改文件配置
 */

#ifndef FILEPROCESS_HPP
#define FILEPROCESS_HPP


#include <QString>
#include <QFile>


std::pair<QString,int> readFolderConfig(const QString &configPath);


#endif //FILEPROCESS_HPP
