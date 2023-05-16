#pragma once

#include <QTextEdit>
#include <QFile>

class SourceCodeView : public QTextEdit {
    Q_OBJECT
public:
    SourceCodeView(QWidget* parent = nullptr, QFile* source = nullptr);

private:
    QFile* _currentSource;

    void readSource();
};

