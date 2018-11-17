#include "mainwindow.h"

#include "textentrywidget.h"

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ) {
	TextEntryWidget *tew=new TextEntryWidget( this );
	tew->startTest("apple tree\nthe quick brown fox junped over the lazy dog",120*1000);
	setCentralWidget(tew);

}

MainWindow::~MainWindow() {}
