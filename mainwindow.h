
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "models/book/Book.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:

	void on_viewFrameChanged(QFrame* newFrame);

	// generated in QtCreatorSlots
	void on_patternsTree_itemClicked(QTreeWidgetItem* item, int column);
	void on_examplesTree_itemClicked(QTreeWidgetItem* item, int column);
    void on_tabWidget_tabBarClicked(int index);
    void on_descriptionSearchLine_textChanged(const QString &arg1);
    void on_filterTypeSelector_currentIndexChanged(int index);
    void on_sourcesSearchLine_textChanged(const QString &arg1);

private:
	Ui::MainWindow* ui;

	Book* _currentBook;
};

#endif // MAINWINDOW_H
