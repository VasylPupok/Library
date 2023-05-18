
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
    
    void search(const QString& prefix);


private:
    using PatternTabMap = QHash<QTreeWidgetItem*, const Pattern*>;
    using NameTabMap = QHash<QString, QTreeWidgetItem*>;

    Book* _patterns;
    PatternTabMap _tabMap;
    NameTabMap _nameMap;

    void init();
};



// Debug macros


