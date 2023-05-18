
#include "patternview.h"
#include <QShortcut>
#include <QObject>

PatternView::PatternView(QWidget* parent) :
	QPdfView(parent)
{
	this->setPageMode(QPdfView::PageMode::MultiPage);
	this->setZoomMode(ZoomMode::FitToWidth);
}
