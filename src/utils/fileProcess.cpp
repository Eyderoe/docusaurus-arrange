#include "fileProcess.hpp"

std::pair<QString, int> readFolderConfig (const QString &configPath) {
    QFile configFile(configPath);
    if (!configFile.exists()) {
        configFile.open(QIODevice::WriteOnly);
        configFile.close();;
    }
}
