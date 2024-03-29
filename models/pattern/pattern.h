#pragma once

#include <QJsonObject>
#include <QString>
#include <QPdfDocument>

#include <paths.h>
#include "code_examples/codeexamples.h"

// TODO add exceptions for case, when info file was not found

class Pattern {
public:
    Pattern(const QString& folder);

    constexpr const QString& path() const {
        return this->_path;
    }

    constexpr const QString& name() const {
        return this->_name;
    }

    constexpr const QJsonObject& info() const {
        return this->_info;
    }

    inline const QString type() const {
        return this->info()["pattern_type"].toString();
    }

    inline const QString info_file_path() const {
        return this->path() + PATTERN_INFO_FILE_NAME;
    }

    inline const QString description_file_path() const {
        return this->path() + PATTERN_DESCRIPTION_FILE_NAME;
    }

    QPdfDocument* getDescription() const;

    CodeExamples* getExamples() const {
        if (!this->_examples) {
            this->_examples = new CodeExamples(this->_path + EXAMPLES_DIRECTORY);
        }
        return this->_examples;
    }

private:
    QString _path;
    QString _name;
    QJsonObject _info;

    mutable QPdfDocument* _description = nullptr;
    mutable CodeExamples* _examples = nullptr;
};
