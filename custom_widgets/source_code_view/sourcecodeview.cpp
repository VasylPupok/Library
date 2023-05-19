#include "sourcecodeview.h"

SourceCodeView::SourceCodeView(QWidget* parent, QFile* source) :
	QTextBrowser(parent),
	_currentSource(source)
{
	readSource();
}

void SourceCodeView::readSource() {
	if (!this->_currentSource) return;

	this->_currentSource->open(QIODevice::ReadOnly | QIODevice::Text);

	this->setText(this->_currentSource->readAll().constData());

	this->_currentSource->close();
}
