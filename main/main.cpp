#include "mainwindow.h"
#include <QApplication>
#include "analyticsdialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AnalyticsDialog w;
	w.show();

	return a.exec();
}
