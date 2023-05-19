#include "chat.h"

#include <QApplication>

void AppCode(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    Mediator* mediator = new ChatMediator(w);
    w->show();
    a.exec();
    delete w;
    delete mediator;
}

int main(int argc, char *argv[]){
    AppCode(argc,argv);
    return 0;
}
