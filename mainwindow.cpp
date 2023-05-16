
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setViewFrame(QFrame* newFrame) {
    newFrame->setParent(this->ui->centralwidget);
    delete this->ui->viewFrame;
    this->ui->viewFrame = newFrame;
    this->ui->viewWidget->addWidget(newFrame);
}



void MainWindow::on_patternsTree_itemClicked(QTreeWidgetItem *item, int column) {
    setViewFrame(new PatternView());
    this->ui->patternsTree->handleClick(item, reinterpret_cast<PatternView*>(this->ui->viewFrame));

    PATTERNTAB_LOG("Clicked item text:");
    PATTERNTAB_LOG(item->data(column, 0));
}


void MainWindow::on_examplesTree_itemClicked(QTreeWidgetItem *item, int column) {

}

