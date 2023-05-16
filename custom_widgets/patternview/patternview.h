
#pragma once

#include <QPdfView>

class PatternView : public QPdfView {
    Q_OBJECT
public:
    PatternView(QWidget* parent = nullptr);

private slots:
    void testShortcut() {
        qDebug() << this->document()->getAllText(0).text();
    };
};
