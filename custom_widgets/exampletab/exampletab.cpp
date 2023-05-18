#include "exampletab.h"

#include <QFileInfo>
#include "debug.h"


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

	for (const Pattern& p : this->_bookExample->patterns()) {
		if (!this->_typeItemMap.contains(p.type())) {
			QTreeWidgetItem* newType = new QTreeWidgetItem(this);
			newType->setText(0, p.type());
			this->_typeItemMap.insert(p.type(), newType);
		}

		QTreeWidgetItem* patternNameTreeItem = new QTreeWidgetItem(this->_typeItemMap[p.type()]);
		patternNameTreeItem->setText(0, p.name());
		patternNameTreeItem->sortChildren(0, Qt::AscendingOrder);
		this->_typePatternsMap.insert(patternNameTreeItem, this->_typeItemMap[p.type()]);

		for (const Example& e : p.getExamples()->examples()) {
			QHash<QString, QTreeWidgetItem*> exampleLanguages;
			if (!exampleLanguages.contains(e.language())) {
				QTreeWidgetItem* newLang = new QTreeWidgetItem(patternNameTreeItem);
				newLang->setText(0, e.language());
				exampleLanguages.insert(e.language(), newLang);
				this->_patternLanguagesMap.insert(newLang, patternNameTreeItem);
			}

			QTreeWidgetItem* exampleNameTreeItem = new QTreeWidgetItem(exampleLanguages[e.language()]);
			exampleNameTreeItem->setText(0, e.name());
			this->_launguageProjectsMap.insert(exampleNameTreeItem, exampleLanguages[e.language()]);

			for (QFile* source : e.sources()) {
				QTreeWidgetItem* sourceNameTreeItem = new QTreeWidgetItem(exampleNameTreeItem);
				sourceNameTreeItem->setText(0, QFileInfo(*source).fileName());
				this->_exampleMap.insert(sourceNameTreeItem, source);
				this->_projectSourcesMap.insert(sourceNameTreeItem, exampleNameTreeItem);
			}
		}
	}

	this->sortItems(0, Qt::AscendingOrder);

	DEBUG_EXPR(
		DEBUG_LOG("Retrieved patterns");
	for (auto& i : this->_bookExample->patterns()) {
		DEBUG_LOG(i.name());
		DEBUG_LOG(i.type());
	}
	);
}

void ExampleTab::filter(const QString& prefix) {
	switch (this->_filterTypeIndex)
	{
	case 0:
		for (const QString& type : this->_bookExample->getPatternTypes()) {
			if (type.startsWith(prefix)) {
				this->invisibleRootItem()->addChild(this->_typeItemMap[type]);
			}
		}
		for (QString& typeName : this->_typeItemMap.keys()) {
			if (!typeName.startsWith(prefix)) {
				this->invisibleRootItem()->removeChild(this->_typeItemMap[typeName]);
			}
		}
		this->invisibleRootItem()->sortChildren(0, Qt::AscendingOrder);
		break;
	case 1:
		for (const QString& typeName : this->_bookExample->getPatternTypes()) {
			QTreeWidgetItem* typeItem = this->_typeItemMap[typeName];
			for (int i = 0; i < typeItem->childCount(); ++i) {
				if (!typeItem->child(i)->text(0).startsWith(prefix)) {
					typeItem->removeChild(typeItem->child(i));
				}
			}

			for (QTreeWidgetItem* pattern : this->_typePatternsMap.keys()) {
				if (pattern->text(0).startsWith(prefix)) {
					this->_typePatternsMap[pattern]->addChild(pattern);
				}
			}

			typeItem->sortChildren(0, Qt::AscendingOrder);
		}
		break;
	case 2:

		for (QTreeWidgetItem* language : this->_patternLanguagesMap.keys()) {
			if (language->text(0).startsWith(prefix)) {
				this->_patternLanguagesMap[language]->addChild(language);
			}
		}

		for (QTreeWidgetItem* pattern : this->_typePatternsMap.keys()) {
			for (int i = 0; i < pattern->childCount(); ++i) {
				if (!pattern->child(i)->text(0).startsWith(prefix)) {
					pattern->removeChild(pattern->child(i));
				}
			}

			pattern->sortChildren(0, Qt::AscendingOrder);
		}
		break;
	case 3:

		for (QTreeWidgetItem* project : this->_launguageProjectsMap.keys()) {
			if (project->text(0).startsWith(prefix)) {
				this->_launguageProjectsMap[project]->addChild(project);
			}
		}

		for (QTreeWidgetItem* language : this->_patternLanguagesMap.keys()) {
			for (int i = 0; i < language->childCount(); ++i) {
				if (!language->child(i)->text(0).startsWith(prefix)) {
					language->removeChild(language->child(i));
				}
			}

			
			language->sortChildren(0, Qt::AscendingOrder);
		}
		break;
	case 4:
		for (QTreeWidgetItem* project : this->_launguageProjectsMap.keys()) {
			for (int i = 0; i < project->childCount(); ++i) {
				if (!project->child(i)->text(0).startsWith(prefix)) {
					project->removeChild(project->child(i));
				}
			}

			for (QTreeWidgetItem* source : this->_exampleMap.keys()) {
				if (source->text(0).startsWith(prefix)) {
					this->_projectSourcesMap[source]->addChild(source);
				}
			}
			project->sortChildren(0, Qt::AscendingOrder);
		}
		break;
	default:
		break;
	}
}
