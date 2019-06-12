#include "testeditorwidget.h"
#include "ui_testeditorwidget.h"

TestEditorWidget::TestEditorWidget( QWidget *parent )
	: QWidget( parent ), ui( new Ui::TestEditorWidget ) {
	ui->setupUi( this );
	connect( ui->pushButton, &QPushButton::clicked, this,
			 &TestEditorWidget::runStartTest );
}

TestEditorWidget::~TestEditorWidget() { delete ui; }

void TestEditorWidget::runStartTest() {
	emit startTest( "this is a test", 120 );
}
