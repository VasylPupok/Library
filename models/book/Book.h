#pragma once

#include <QJsonObject>
#include <models/pattern/pattern.h>

// TODO add exceptions for case, when info file was not found

class Book {
public:
	using PatternList = QList<Pattern>;

	Book(const QString& path);

	constexpr const QString& path() const {
		return this->_path;
	}

	constexpr const PatternList& patterns() const {
		return this->_patterns;
	}

	constexpr const QJsonObject& book_info() const {
		return this->_info;
	}

private:
	QString _path;
	QJsonObject _info;
	PatternList _patterns;

	void readInfoFile();
};
