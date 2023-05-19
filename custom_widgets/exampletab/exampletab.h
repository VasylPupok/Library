#pragma once

#include <QTreeWidget>
#include <QHash>
#include <QSet>

#include <models/library/Library.h>
#include <custom_widgets/source_code_view/sourcecodeview.h>

class ExampleTab : public QTreeWidget {
	Q_OBJECT
public:
	ExampleTab(QWidget* parent = nullptr);
	ExampleTab(Library* existing_book, QWidget* parent = nullptr);

	constexpr Library* currentBook() const {
		return this->_bookExample;
	}

	void handleClick(QTreeWidgetItem* item, SourceCodeView* viewRef);

public slots:
	inline void setFilterTypeIndex(int index) { 
		this->_filterTypeIndex = index; 
	};

	void search(const QString& prefix);

private:
	Library* _bookExample;
	QHash<QTreeWidgetItem*, QFile*> _exampleMap;

	QHash<QString, QTreeWidgetItem*> _typeItemMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _typePatternsMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _patternLanguagesMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _launguageProjectsMap;
	QHash<QTreeWidgetItem*, QTreeWidgetItem*> _projectSourcesMap;

	int _filterTypeIndex = 0;

	void init();
};

