
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "custom_widgets/source_code_view/sourcecodeview.h"

#include "paths.h"
#include "debug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->_currentBook = new Book(PATTERNS_DIRECTORY);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_viewFrameChanged(QFrame* newFrame) {
    newFrame->setParent(this->ui->centralwidget);
    delete this->ui->viewFrame;
    this->ui->viewFrame = newFrame;
    this->ui->viewWidget->addWidget(newFrame);
}

void MainWindow::on_patternsTree_itemClicked(QTreeWidgetItem *item, int column) {
    on_viewFrameChanged(new PatternView());
    this->ui->patternsTree->handleClick(item, reinterpret_cast<PatternView*>(this->ui->viewFrame));

    DEBUG_LOG("Clicked item text:");
    DEBUG_LOG(item->data(column, 0));
}

void MainWindow::on_examplesTree_itemClicked(QTreeWidgetItem *item, int column) {
    on_viewFrameChanged(new SourceCodeView());
    this->ui->examplesTree->handleClick(item, reinterpret_cast<SourceCodeView*>(this->ui->viewFrame));
}

void MainWindow::on_tabWidget_tabBarClicked(int index) {
    // make that area empty
    on_viewFrameChanged(new QFrame());
}

