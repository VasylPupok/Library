#include "exampletab.h"

#include "debug.h"
#include <QFileInfo>

ExampleTab::ExampleTab(QWidget* parent) :
	QTreeWidget(parent),
	_bookExample(new Book(PATTERNS_DIRECTORY))
{
	this->init();
}

ExampleTab::ExampleTab(Book* existing_book, QWidget* parent) :
	QTreeWidget(parent),
	_bookExample(existing_book)
{
	this->init();
}

void ExampleTab::handleClick(QTreeWidgetItem* item, SourceCodeView* viewRef) {
	if (this->_exampleMap.contains(item)) {
		QFile* source = this->_exampleMap[item];
		source->open(QIODevice::ReadOnly | QIODevice::Text);

		QString text = source->readAll();

		DEBUG_LOG("Read source text");
		DEBUG_LOG(text);

		viewRef->setText(text);

		source->close();
	}
}

void ExampleTab::init() {
	QHash<QString, QTreeWidgetItem*> patternTypes;
	QHash<QString, QTreeWidgetItem*> exampleLanguages;

	for (const Pattern& p : this->_bookExample->patterns()) {
		if (!patternTypes.contains(p.type())) {
			QTreeWidgetItem* newType = new QTreeWidgetItem(this);
			newType->setText(0, p.type());
			patternTypes.insert(p.type(), newType);
		}

		QTreeWidgetItem* patternNameTreeItem = new QTreeWidgetItem(patternTypes[p.type()]);
		patternNameTreeItem->setText(0, p.name());

		for (const Example& e : p.getExamples()->examples()) {
			if (!exampleLanguages.contains(e.language())) {
				QTreeWidgetItem* newLang = new QTreeWidgetItem(patternNameTreeItem);
				newLang->setText(0, e.language());
				exampleLanguages.insert(e.language(), newLang);
			}

			QTreeWidgetItem* exampleNameTreeItem = new QTreeWidgetItem(exampleLanguages[e.language()]);
			exampleNameTreeItem->setText(0, e.name());

			for (QFile* source : e.sources()) {
				QTreeWidgetItem* sourceNameTreeItem = new QTreeWidgetItem(exampleNameTreeItem);
				sourceNameTreeItem->setText(0, QFileInfo(*source).fileName());
				this->_exampleMap.insert(sourceNameTreeItem, source);
			}
		}
		exampleLanguages.clear();
	}

	DEBUG_EXPR(
		DEBUG_LOG("Retrieved patterns");
		for (auto& i : this->_bookExample->patterns()) {
			DEBUG_LOG(i.name());
			DEBUG_LOG(i.type());
		}
	);
}
