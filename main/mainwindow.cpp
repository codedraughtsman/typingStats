#include "mainwindow.h"

#include <textentrywidget.h>

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ) {

	setCentralWidget( new TextEntryWidget( this ) );
}

MainWindow::~MainWindow() {}
