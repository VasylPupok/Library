
#pragma once

#include <QTreeWidget>
#include <QList>
#include <QHash>

#include <models/pattern/pattern.h>
#include <models/book/Book.h>

#include <custom_widgets/patternview/patternview.h>

class PatternTab : public QTreeWidget {
public:
    PatternTab(QWidget* parent = nullptr);
    PatternTab(Book* existing_book, QWidget* parent = nullptr);

    constexpr Book* currentBook() const {
        return this->_patterns;
    }

    void handleClick(QTreeWidgetItem *item, PatternView* pdfview);

private:
    using PatternTabMap = QHash<QTreeWidgetItem*, const Pattern*>;
    using NameTabMap = QHash<QString, QTreeWidgetItem*>;

    Book* _patterns;
    PatternTabMap _tabMap;

    // kinda usless for now map "name" - "tab", but probably it will be useful in future
    // The only usage - init() method, where it used for detecting already added names
    NameTabMap _nameMap;

    void init();
};



// Debug macros


