
#include "example.h"

#include <QFile>
#include <QJsonDocument>

#include <paths.h>
#include <debug.h>

Example::Example(const QString& path) :
	_path(path)
{
    QFile jsonFile(this->_path + CODE_EXAMPLE_INFO_FILE_NAME);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);

    this->_info = QJsonDocument::fromJson(jsonFile.readAll()).object();

    jsonFile.close();

    this->_name = this->info()["name"].toString();

    for (const QString& filename : this->_info["sources"].toVariant().toStringList()) {
        this->_sources.push_back(new QFile(this->path() + filename));
    }

    DEBUG_LOG("Retrieved example info")
    DEBUG_LOG(this->_name);
    DEBUG_LOG(this->_info);
    

    // TODO actually bring up example here
}
