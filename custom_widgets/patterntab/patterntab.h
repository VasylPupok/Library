
#pragma once

#include <QTreeWidget>
#include <QList>
#include <QMap>

#include <models/pattern/pattern.h>
#include <models/book/Book.h>

#include <custom_widgets/patternview/patternview.h>

class PatternTab : public QTreeWidget {
public:
    PatternTab(QWidget* parent = nullptr);

    void handleClick(QTreeWidgetItem *item, PatternView* pdfview);

private:
    using PatternTabMap = QMap<QTreeWidgetItem*, const Pattern*>;
    using NameTabMap = QMap<QString, QTreeWidgetItem*>;

    Book* _patterns;
    PatternTabMap _tabMap;

    // kinda usless for now map "name" - "tab", but probably it will be useful in future
    // The only usage - init() method, where it used for detecting already added names
    NameTabMap _nameMap;

    void init();
};



// Debug macros

#ifdef PATTERNTAB_DEBUG_ON
    #define PATTERNTAB_LOG(expr) qDebug() << expr;
    #define PATTERNTAB_DEBUG(expr) expr;
#ifndef _ADD_DEBUG_CONSOLE
    #define _ADD_DEBUG_CONSOLE
#endif
#else
    #define PATTERNTAB_LOG(expr) void;
    #define PATTERNTAB_DEBUG(expr) void;
#endif
