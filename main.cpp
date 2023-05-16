
#include "mainwindow.h"

#include <QApplication>
#include <Windows.h>

int main(int argc, char* argv[]) {

#ifdef _ADD_DEBUG_CONSOLE
#ifdef _WIN32
	if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}
#endif
#endif

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
