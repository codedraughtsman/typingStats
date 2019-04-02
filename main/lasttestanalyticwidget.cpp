#include "lasttestanalyticwidget.h"
#include "storagemanager.h"
#include "ui_lasttestanalyticwidget.h"

LastTestAnalyticWidget::LastTestAnalyticWidget( QWidget *parent )
	: QWidget( parent ), m_testResult( TestResult() ),
	  ui( new Ui::LastTestAnalyticWidget ) {
	ui->setupUi( this );
}

LastTestAnalyticWidget::~LastTestAnalyticWidget() { delete ui; }

void LastTestAnalyticWidget::setTestResult( TestResult result ) {
	m_testResult = result;
	qDebug() << "updating lastTestAnalyticWidget";
	qDebug() << "gross wpm is: " << m_testResult.getWpmGross();
	ui->WpmValue->setText( QString( "%1" ).arg(
		QString::number( m_testResult.getWpmGross(), 'f', 2 ) ) );
	ui->TotalKeyPressesValue->setText( QString( "%1" ).arg(
		QString::number( m_testResult.m_keyEvents.length(), 'f', 2 ) ) );
	ui->TotalUsedSymbolsValue->setText( QString( "%1" ).arg( QString::number(
		m_testResult.getNumberOfMatchingKeyEvents(
			KeyEvent::keyStatus::PRESSED, KeyEvent::strokeType::CORRECT ),
		'f', 2 ) ) );
}
void LastTestAnalyticWidget::updateToTestResult( uint uid ) {
	setTestResult( storageManager().getTestResult( uid ) );
}
