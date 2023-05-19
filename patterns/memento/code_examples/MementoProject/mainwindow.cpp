#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->textEdit->installEventFilter(this);

    editor = new Editor(ui->textEdit);
    caretaker = new Caretaker(editor, ui->historyList);
    caretaker->Backup();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete editor;
    delete caretaker;
}

// Call Backup() of caretaker every time Space pressed and focus on text area
bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Space)
        {
            caretaker->Backup();
            return QMainWindow::eventFilter(target,event);
        }
    }
    return QMainWindow::eventFilter(target,event);
}

void MainWindow::on_undoBtn_clicked()
{
    caretaker->Undo();
}

