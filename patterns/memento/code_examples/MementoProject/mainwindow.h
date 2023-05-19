#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTime>
#include <vector>
#include <QKeyEvent>
#include <QEvent>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    class Editor;
    class Caretaker;

private slots:
    void on_undoBtn_clicked();

private:
    Ui::MainWindow *ui;
    Editor* editor;
    Caretaker* caretaker;
    bool eventFilter(QObject *target, QEvent *event) override;


};
#endif // MAINWINDOW_H

class Memento {
 public:
  virtual ~Memento() {}
  virtual QString getName() const = 0;
  virtual QString getDate() const = 0;
  virtual QString getState() const = 0;
};

class MainWindow::Editor
{
private:
    // saves is used to count momentos
    int saves;
    QTextEdit* textArea;
public:
    class EditorMemento : public Memento
    {
    private:
        QString text;
        QString name;
        QString date;
    public:
        EditorMemento(QString t = "", QString n = "") : text(t), name(n)
        {
            // set time of creation
            QTime time;
            int hour = time.currentTime().hour();
            int minute = time.currentTime().minute();
            int second = time.currentTime().second();
            date = QString("%1:%2:%3").arg(hour).arg(minute).arg(second);

        }
        QString getName() const override { return name; }
        QString getDate() const override { return date; }
        QString getState() const override{ return text; }
    };

    Editor(QTextEdit *t)
    {
        this->textArea = t;
        saves = 0;
    }
    void restore(Memento *memento)
    {
        saves--;
        textArea->clear();
        textArea->insertPlainText(memento->getState());
    }
    Memento* save()
    {
        saves++;
        return new EditorMemento(textArea->toPlainText(),"Save N" +QString::number(saves));
    }

};

class MainWindow::Caretaker
{
private:
    Editor *originator;
    std::vector<Memento*> mementos;

    // mementosDisplayList is used to display momentos data
    QListWidget *mementosDisplayList;

public:
    Caretaker(Editor* o, QListWidget* list) : originator(o), mementosDisplayList(list) {}
    ~Caretaker()
    {
        for (auto m : mementos) delete m;
    }
    // Add memento
    void Backup() {
        this->mementos.push_back(this->originator->save());
        this->ShowHistory();
    }
    // Restore originator's state( in our case - text)
    void Undo() {
        if (!this->mementos.size()) {
            return;
        }
        Memento *memento = this->mementos.back();
        this->mementos.pop_back();
        try {
            this->originator->restore(memento);
        } catch (...) {
            this->Undo();
        }
        this->ShowHistory();

        // if we ran out of momentos, create one
        if(this->mementos.size() == 0)
            this->Backup();

    }
    // Show history on display near text editor
    void ShowHistory() const {
        mementosDisplayList->clear();
        for (Memento *memento : this->mementos) {
            mementosDisplayList->addItem(memento->getDate() + " : " + memento->getName() + " : " + memento->getState());
        }
    }
};
