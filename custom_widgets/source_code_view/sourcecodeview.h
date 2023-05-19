#pragma once

#include <QTextBrowser>
#include <QFile>

class SourceCodeView : public QTextBrowser {
    Q_OBJECT
public:
    SourceCodeView(QWidget* parent = nullptr, QFile* source = nullptr);

private:
    QFile* _currentSource;

    void readSource();
};

