
#include "patterntab.h"
#include "paths.h"

PatternTab::PatternTab(QWidget* parent) :
	QTreeWidget(parent),
	_patterns(new Book(PATTERNS_FOLDER))
{
	this->init();
}

void PatternTab::handleClick(QTreeWidgetItem* item, PatternView* pdfview) {
	if (this->_tabMap.contains(item)) {
		PATTERNTAB_LOG("Name of clicked pattern:");
		PATTERNTAB_LOG(this->_tabMap[item]->name());

		pdfview->setDocument(this->_tabMap[item]->getDescription());
	}
}

void PatternTab::init() {
	for (const Pattern& p : this->_patterns->patterns()) {
		if (!this->_nameMap.contains(p.type())) {
			QTreeWidgetItem* newType = new QTreeWidgetItem(this);
			newType->setText(0, p.type());
			this->_nameMap.insert(p.type(), newType);
		}

		QTreeWidgetItem* patternNameTreeItem = new QTreeWidgetItem(this->_nameMap[p.type()]);
		patternNameTreeItem->setText(0, p.name());
		this->_tabMap.insert(patternNameTreeItem, &p);
	}

	PATTERNTAB_DEBUG(
		PATTERNTAB_LOG("Retrieved patterns");
		for (auto& i : this->_patterns->patterns()) {
			PATTERNTAB_LOG(i.name());
			PATTERNTAB_LOG(i.type());
		}
	);
}




