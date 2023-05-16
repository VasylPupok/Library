#pragma once

#include <QFile>
#include <QString>
#include <QJsonObject>

class Example {
public:
    using FileList = QList<QFile*>;

    Example(const QString& path);

    constexpr const QString& path() const {
        return this->_path;
    }

    constexpr const QString& name() const {
        return this->_name;
    }

    constexpr const QJsonObject& info() const {
        return this->_info;
    }

    constexpr const FileList& sources() const {
        return this->_sources;
    }

    inline const QString language() const {
        return this->_info["language"].toString();
    }



private:
    QString _path;
    QString _name;
    QJsonObject _info;
    FileList _sources;
};
