
#include "pattern.h"

#include <QFile>
#include <QJsonDocument>

#include "paths.h"

Pattern::Pattern(const QString& path) :
    _path(path)
{
    QFile jsonFile(this->info_file_path());
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);

    this->_info = QJsonDocument::fromJson(jsonFile.readAll()).object();

    jsonFile.close();

    this->_name = this->_info["name"].toString();
}

QPdfDocument* Pattern::getDescription() const {
    if (!_description) {
        this->_description = new QPdfDocument;
        this->_description->load(this->description_file_path());
    }
    return _description;
}
