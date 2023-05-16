
#include "patternview.h"
#include <QShortcut>
#include <QObject>

PatternView::PatternView(QWidget* parent) :
	QPdfView(parent)
{
	this->setPageMode(QPdfView::PageMode::MultiPage);
	QShortcut* someShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
	QObject::connect(someShortcut, SIGNAL(activated()), this, SLOT(testShortcut()));
}
