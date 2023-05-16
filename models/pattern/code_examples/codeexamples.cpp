
#include "codeexamples.h"

#include <QFile>
#include <QJsonDocument>

#include <paths.h>
#include <debug.h>

CodeExamples::CodeExamples(const QString& path) :
	_path(path)
{
    QFile jsonFile(this->_path + EXAMPLES_INFO_FILE_NAME);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);

    this->_info = QJsonDocument::fromJson(jsonFile.readAll()).object();

    jsonFile.close();
    QStringList patternDirs = this->_info["project_folders"].toVariant().toStringList();

    DEBUG_LOG(this->_info)

    QString dir;
    for (const QString& patternDirName : patternDirs) {
        dir = path + patternDirName;
        if (!dir.endsWith("\\")) dir += "\\";
        this->_examples.push_back(Example(dir));
    }
}
