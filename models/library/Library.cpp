
#include "Library.h"
#include "paths.h"

#include <QFile>
#include <QJsonDocument>

const QSet<QString>& Library::getPatternTypes() const {
    if (!this->_patternTypes) {
        this->_patternTypes = new QSet<QString>;
        for (const Pattern& p : this->_patterns) {
            this->_patternTypes->insert(p.type());
        }
    }
    return *this->_patternTypes;
}

void Library::readInfoFile() {
    QFile jsonFile(this->_path + BOOK_INFO_FILE_NAME);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);

    this->_info = QJsonDocument::fromJson(jsonFile.readAll()).object();

    jsonFile.close();
}

Library::Library(const QString& path) :
	_path(path)
{
    readInfoFile();
    QStringList patternDirs = this->_info["folders"].toVariant().toStringList();
    QString dir;
    for (const QString& patternDirName : patternDirs) {
        dir = path + patternDirName;
        if (!dir.endsWith("\\")) dir += "\\";
        this->_patterns.push_back(Pattern(dir));
    }
}
