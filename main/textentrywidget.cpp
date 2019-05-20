#include "textentrywidget.h"

#include <QDebug>
#include <QEvent>
#include <QLayout>
#include <QPushButton>
#include <QTimer>

#include "keyevent.h"
#include "storagemanager.h"
#include "textentryovertypewidget.h"

TextEntryWidget::TextEntryWidget( QWidget *parent ) : QWidget( parent ) {
	createDisplayWindow();
	createButtons();

	m_countDownBar = new QProgressBar;
	m_countDownBar->setRange( 0, 100 );

	setupLayout();
	setupConnections();
}
TextEntryWidget::~TextEntryWidget() {}

void TextEntryWidget::createDisplayWindow() {
	m_textEntryWidget = new TextEntryOverTypeWidget( this );
	m_textEntryWidget->setMinimumSize( 400, 400 );
}

void TextEntryWidget::createButtons() {
	m_buttonBox = new QHBoxLayout;
	QPushButton *pauseButton = new QPushButton( "pause" );
	QPushButton *cancelButton = new QPushButton( "cancel" );

	m_buttonBox->addWidget( pauseButton );
	m_buttonBox->addWidget( cancelButton );

	connect( cancelButton, &QPushButton::released, this,
			 &TextEntryWidget::close );
}

void TextEntryWidget::setupLayout() {
	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget( m_textEntryWidget );
	lay->addWidget( m_countDownBar );
	lay->addLayout( m_buttonBox );
	setLayout( lay );
}

void TextEntryWidget::setupConnections() {
	qDebug() << "TextEntryWidget::setupConnections";
	connect( m_textEntryWidget, &TextEntryOverTypeWidget::timePercentLeftUpdate,
			 m_countDownBar, &QProgressBar::setValue );
	bool ok =
		connect( m_textEntryWidget, &TextEntryOverTypeWidget::testFinished,
				 this, &TextEntryWidget::testHasEnded );
	qDebug() << "ok " << ok;
	dumpObjectInfo();
}

void TextEntryWidget::startTest( QString text, uint durationInSeconds ) {
	m_textEntryWidget->setTest( text, durationInSeconds );
}

void TextEntryWidget::testHasEnded( TestResult result ) {
	// store results in database;
	qDebug() << "calling TextEntryWidget::testHasEnded";
	storageManager().addTestResult( result );
	emit testFinished( result );
}

void TextEntryWidget::endTest() {
	// todo stop the currently running test and get the results.
	// emit testFinished( result );
}
