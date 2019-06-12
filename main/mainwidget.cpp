#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "textentrywidget.h"

MainWidget::MainWidget( QWidget *parent )
	: QMainWindow( parent ), ui( new Ui::MainWidget ) {
	ui->setupUi( this );

	connect( ui->testEditorWidget, &TestEditorWidget::startTest,
			 ui->textEntryWidget, &TextEntryWidget::startTest );
}

MainWidget::~MainWidget() { delete ui; }
