#include "analyticsdialog.h"
#include "choosetestdialog.h"
#include "storagemanager.h"
#include "textentrywidget.h"
#include "ui_analyticsdialog.h"

AnalyticsDialog::AnalyticsDialog( QWidget *parent )
	: QDialog( parent ), ui( new Ui::AnalyticsDialog ) {
	ui->setupUi( this );
}

AnalyticsDialog::~AnalyticsDialog() { delete ui; }

void AnalyticsDialog::on_testSelectionButton_released() {
	ChooseTestDialog *w = new ChooseTestDialog();
	w->show();
}

void AnalyticsDialog::on_repeatLastTest_released() {
	TextEntryWidget *tew = new TextEntryWidget();
	tew->startTest( "apple tree\nthe quick brown fox junped over the lazy dog",
					120 );
	tew->show();
}
