
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:

	// generated in QtCreatorSlots
	void on_patternsTree_itemClicked(QTreeWidgetItem* item, int column);

	void setViewFrame(QFrame* newFrame);

    void on_examplesTree_itemClicked(QTreeWidgetItem *item, int column);

private:
	Ui::MainWindow* ui;

	
};

#endif // MAINWINDOW_H
