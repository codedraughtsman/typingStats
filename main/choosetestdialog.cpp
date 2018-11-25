#include "choosetestdialog.h"
#include "testdata.h"
#include "testmanager.h"
#include "textentrywidget.h"
#include "ui_choosetestdialog.h"

ChooseTestDialog::ChooseTestDialog( QWidget *parent )
	: QDialog( parent ), ui( new Ui::ChooseTestDialog ) {
	ui->setupUi( this );
	TestManager *tm = new TestManager;
	tm->addTest( "test 1", "apple tree" );
	tm->addTest( "orignal",
				 "apple tree\nthe quick brown fox junped over the lazy dog" );

	ui->testSelectionView->setModel( tm );
}

ChooseTestDialog::~ChooseTestDialog() { delete ui; }

void ChooseTestDialog::startTest( void ) {
	QModelIndex index = ui->testSelectionView->currentIndex();
	double durationMsec = ui->durationTime->currentText().toInt() * 60 * 1000;

	QModelIndex instanceIndex = ui->testSelectionView->model()->index(
		index.row(), TestManager::INSTANCE );
	QSharedPointer<TestData> tdata =
		instanceIndex.data( Qt::DisplayRole ).value<QSharedPointer<TestData>>();

	TextEntryWidget *tew = new TextEntryWidget();
	tew->setWindowTitle( "typing test: " + tdata->getTitle() );
	tew->startTest( tdata->getContents(), durationMsec );
	tew->show();
	close();
}

void ChooseTestDialog::on_StartButton_released() { startTest(); }

void ChooseTestDialog::on_cancelButton_released() { close(); }

void ChooseTestDialog::on_testSelectionView_doubleClicked(
	const QModelIndex &index ) {
	Q_UNUSED( index );
	startTest();
}
