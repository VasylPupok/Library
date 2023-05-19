#include <QString>
#include <vector>
class Component;
enum Action
{
    ENTER,
    WRITE,
    LEAVE
};

class Mediator
{
public:
    virtual ~Mediator(){};
    virtual void Notify(Component *sender, Action action, QString message) = 0;
};

class Component
{
protected:
    Mediator *mediator;

public:
    Component(Mediator *mediator = nullptr) : mediator(mediator) {}
    void setMediator(Mediator *mediator) {
        this->mediator = mediator;
    }
};

#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class Chat;
}

class Chat : public QDialog, public Component
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr, QString name=nullptr);
    ~Chat();
    void setName(QString name);
    QString getName();
    void showMessage(const QString message);
protected:
    void closeEvent(QCloseEvent* e);
private slots:
    void on_SendBtn_clicked();

private:
    Ui::Chat *ui;
    QString name;
};

#endif // CHAT_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Component
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_EnterChatBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

class ChatMediator : public Mediator{
private:
    MainWindow* landing;
    std::vector<Chat*> chats;
public:
    ChatMediator(MainWindow* l) : landing(l)
    {
        landing->setMediator(this);
    }
    ~ChatMediator()
    {
        for (auto c : chats)
        {
            delete c;
        }
    }

    void Notify(Component *sender, Action action, QString message) override
    {
        if (message == nullptr || message == "")
            return;

        if(sender == landing && action == Action::ENTER)
        {
            // add new person to chats and set mediator
            Chat *newChat = new Chat(landing, message);
            newChat->setMediator(this);
            chats.push_back(newChat);

            // open a chat window for new member
            // notify all in the chat about a member
            for(size_t i = 0; i < chats.size(); i++)
            {
                chats[i]->showMessage(message + " entered the chat.");
            }
            newChat->show();
        }
        else if(action == Action::WRITE && sender != landing)
        {
            // Find sender and remember his name
            // In sender's chat window use "Me:" instead of name
            QString senderName="";
            for(size_t i = 0; i < chats.size(); i++)
            {
                if(chats[i] == sender)
                {
                    senderName = chats[i]->getName();
                    chats[i]->showMessage("Me: " + message);
                }

            }
            // In other windows use sender's name
            for(size_t i = 0; i < chats.size(); i++)
            {
                if(chats[i] != sender)
                {
                    chats[i]->showMessage(senderName + ": " + message);
                }
            }
        }
        else if(action == Action::LEAVE && sender != landing)
        {
            // Notify all members about leaving the chat
            for(size_t i = 0; i < chats.size(); i++)
            {
                if(chats[i] != sender)
                    chats[i]->showMessage(message);
            }
        }
    }

};
