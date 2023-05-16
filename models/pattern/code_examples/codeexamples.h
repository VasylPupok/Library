#pragma once

#include <QString>
#include <QJsonObject>
#include <QList>

#include "example.h"

class CodeExamples {
public:
    using ExampleList = QList<Example>;

    CodeExamples(const QString& path);

    constexpr const QString& path() const {
        return this->_path;
    }

    constexpr const QJsonObject& info() const {
        return this->_info;
    }

    constexpr const ExampleList& examples() const {
        return this->_examples;
    }

private:
    QString _path;
    ExampleList _examples;
    QJsonObject _info;
};
