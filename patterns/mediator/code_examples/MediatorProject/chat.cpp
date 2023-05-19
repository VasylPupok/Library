#include "chat.h"
#include "ui_chat.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Chat::Chat(QWidget *parent, QString n) :
    QDialog(parent),
    ui(new Ui::Chat),
    name(n)
{
    ui->setupUi(this);
}

Chat::~Chat()
{
    delete ui;
}
void Chat::setName(QString name){
    if(name == nullptr || name == "") throw std::exception();
    this->name = name;
}
QString Chat::getName(){return this->name;}

void Chat::showMessage(const QString message){
    ui->MessagesList->addItem(message);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_EnterChatBtn_clicked()
{
    QString message = ui->NameLineEdit->text();
    ui->NameLineEdit->clear();
    mediator->Notify(this,Action::ENTER, message);
}


void Chat::on_SendBtn_clicked()
{
    QString message = ui->MessageLineEdit->text();
    ui->MessageLineEdit->clear();
    mediator->Notify(this, Action::WRITE, message);
}

void Chat::closeEvent(QCloseEvent* e)
{
    mediator->Notify(this, Action::LEAVE, this->getName() + " left the chat.");
    QWidget::closeEvent(e);
}

