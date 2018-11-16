#include "mainwindow.h"

#include "textentrywidget.h"

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ) {
	TextEntryWidget *tew=new TextEntryWidget( this );
	tew->setText("apple tree\nthe quick brown fox junped over the lazy dog");
	setCentralWidget(tew);

}

MainWindow::~MainWindow() {}
