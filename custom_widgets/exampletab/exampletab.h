#pragma once

#include <QTreeWidget>
#include <QHash>
#include <QSet>

#include <models/book/Book.h>
#include <custom_widgets/source_code_view/sourcecodeview.h>

class ExampleTab : public QTreeWidget {
	Q_OBJECT
public:
	ExampleTab(QWidget* parent = nullptr);
	ExampleTab(Book* existing_book, QWidget* parent = nullptr);

	constexpr Book* currentBook() const {
		return this->_bookExample;
	}

	void handleClick(QTreeWidgetItem* item, SourceCodeView* viewRef);

public slots:
	inline void setFilterTypeIndex(int index) { 
		this->_filterTypeIndex = index; 
	};

	void filter(const QString& prefix);

private:
	Book* _bookExample;
	QHash<QTreeWidgetItem*, QFile*> _exampleMap;

	QHash<QString, QTreeWidgetItem*> _typeItemMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _typePatternsMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _patternLanguagesMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _launguageProjectsMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _projectSourcesMap;

	int _filterTypeIndex = 0;

	void init();
};

