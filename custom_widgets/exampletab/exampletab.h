#pragma once

#include <QTreeWidget>
#include <QHash>

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

private:
	Book* _bookExample;

	QHash<QTreeWidgetItem*, QFile*> _exampleMap;

	void init();
};

