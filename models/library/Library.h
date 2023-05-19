#pragma once

#include <QSet>
#include <QString>
#include <QJsonObject>
#include <models/pattern/pattern.h>

// TODO add exceptions for case, when info file was not found

class Library {
public:
	using PatternList = QList<Pattern>;

	Library(const QString& path);

	constexpr const QString& path() const {
		return this->_path;
	}

	constexpr const PatternList& patterns() const {
		return this->_patterns;
	}

	constexpr const QJsonObject& book_info() const {
		return this->_info;
	}

	const QSet<QString>& getPatternTypes() const;

private:
	QString _path;
	QJsonObject _info;
	PatternList _patterns;

	mutable QSet<QString>* _patternTypes = nullptr;

	void readInfoFile();
};
