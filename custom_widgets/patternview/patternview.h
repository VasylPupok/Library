
#pragma once

#include <QPdfView>

class PatternView : public QPdfView {
    Q_OBJECT
public:
    PatternView(QWidget* parent = nullptr);

private slots:
    // TODO remove this inline slot and add actual implementation of Ctrl+S
    void testShortcut() {
        qDebug() << this->document()->getAllText(0).text();
    };
};
