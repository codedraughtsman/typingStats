#include "textentrywidget.h"

#include "keyevent.h"
#include <QDebug>
#include <QLayout>
#include <QEvent>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

void TextEntryWidget::createDisplayWindow() {
	m_sourceWindow = new QTextEdit;
	m_sourceWindow->setMinimumSize( 100, 100 );
	m_sourceWindow->setReadOnly( true );
	m_sourceDocument = new QTextDocument;
	m_sourceWindow->setDocument( m_sourceDocument );
}
void TextEntryWidget::createInputWindow() {
	m_inputWindow = new TextEditLogger;
	m_inputDocument = new QTextDocument;
	m_inputWindow->setMinimumSize( 100, 100 );
	m_inputWindow->setDocument( m_inputDocument );

	QTextOption option;
	option.setFlags( QTextOption::ShowLineAndParagraphSeparators |
					 QTextOption::ShowTabsAndSpaces );
	m_sourceDocument->setDefaultTextOption( option );
	m_inputDocument->setDefaultTextOption( option );
}

void TextEntryWidget::updateCountDownBar( void ) {
	qDebug() << "updateCountDownBar is called. elapsed time is:"
			 << m_timeLeft.remainingTime();
	m_countDownBar->setValue(
		( m_testDurationMsec - m_timeLeft.remainingTime() ) );
}
void TextEntryWidget::startTest( QString text, double durationMsec ) {
	qDebug() << "called startTest. duration is: " << durationMsec;
	m_testDurationMsec = durationMsec;
	m_countDownBar->setRange( 0, m_testDurationMsec );
	m_timeLeft.setRemainingTime( m_testDurationMsec );
	setText( text );
}

void TextEntryWidget::recordKeyEvent( KeyEvent::keyStatus keyStatus,
									  QString keyText ) {
	m_keyLogger.logEvent(
		KeyEvent( keyStatus, KeyEvent::strokeType::CORRECT, keyText,
				  m_testDurationMsec - m_timeLeft.remainingTime() ) );
}
void TextEntryWidget::keyPressed( QString key ) {
	recordKeyEvent( KeyEvent::keyStatus::PRESSED, key );
}
void TextEntryWidget::keyReleased( QString key ) {
	recordKeyEvent( KeyEvent::keyStatus::RELEASED, key );
}

TextEntryWidget::TextEntryWidget( QWidget *parent ) : QWidget( parent ) {
	createDisplayWindow();
	createInputWindow();

	QHBoxLayout *buttonBox = new QHBoxLayout;
	QPushButton *pauseButton = new QPushButton( "pause" );
	QPushButton *cancelButton = new QPushButton( "cancel" );

	buttonBox->addWidget( pauseButton );
	buttonBox->addWidget( cancelButton );

	connect( cancelButton, &QPushButton::released, this,
			 &TextEntryWidget::close );

	m_countDownBar = new QProgressBar;

	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget( m_sourceWindow );
	lay->addWidget( m_inputWindow );
	lay->addWidget( m_countDownBar );
	lay->addLayout( buttonBox );
	setLayout( lay );
	connect( m_inputWindow, &QTextEdit::textChanged, this,
			 &TextEntryWidget::checkText );

	m_timer = new QTimer( this );
	connect( m_timer, &QTimer::timeout, this,
			 &TextEntryWidget::updateCountDownBar );
	m_timer->start( 500 );

	connect( m_inputWindow, &TextEditLogger::keyPressed, this,
			 &TextEntryWidget::keyPressed );
	connect( m_inputWindow, &TextEditLogger::keyReleased, this,
			 &TextEntryWidget::keyReleased );
}

TextEntryWidget::~TextEntryWidget() {
	m_timer->stop();
	delete m_timer;
}

void TextEntryWidget::setText( QString newText ) {
	m_inputString = newText;
	checkText();
}

int myDiff( QString str1, QString str2 ) {
	int minLength = qMin( str1.length(), str2.length() );
	for ( int i = 0; i < minLength; i++ ) {
		if ( str1[ i ] != str2[ i ] ) {
			return i;
		}
	}
	if ( str2.length() > minLength ) {
		return minLength;
	}
	return -1;
}
QString colourizeText( QString text, QString colour, int startIndex = -1,
					   int endIndex = -1 ) {
	if ( startIndex == -1 ) {
		return "<span style='white-space: pre;color: " + colour + "'>" + text +
			   "<\\span>";
	}
	QString beforeColour = text.left( startIndex );
	QString inColour = text.mid( startIndex, endIndex - startIndex );
	QString afterColour;
	if ( text.length() > endIndex ) {
		afterColour = text.mid( endIndex, text.length() - endIndex );
	}

	QString outText = beforeColour;
	outText += "<span style='white-space: pre;color:" + colour + "'>" +
			   inColour + "<\\span>";
	outText += afterColour;
	return outText;
}
void TextEntryWidget::checkText() {
	int firstDifference = myDiff( m_inputString, m_inputWindow->toPlainText() );

	if ( firstDifference == -1 ) {
		if ( m_inputString == m_inputWindow->toPlainText() ) {
			qDebug() << "strings are the same.";
			emit testFinished();
			close();
		}
		// set to good.
		m_sourceDocument->setHtml( colourizeText( m_inputString, "green" ) );

	} else {
		// set to error.
		qDebug() << QString( "error: strings differ. %1  !== %2 " )
						.arg( m_sourceWindow->toPlainText() )
						.arg( m_inputWindow->toPlainText() );

		QString colouredText = colourizeText(
			m_inputString, "red", firstDifference, firstDifference + 1 );
		QString colouredTextInput =
			colourizeText( m_inputWindow->toPlainText(), "red", firstDifference,
						   firstDifference + 1 );

		bool flag = m_inputWindow->blockSignals( true );
		m_sourceDocument->setHtml(
			"<span style='white-space: pre;color:black'>" + colouredText +
			"<\\span>" );
		m_inputDocument->setHtml(
			"<span style='white-space: pre;color:black'>" + colouredTextInput +
			"<\\span>" );
		m_inputWindow->blockSignals( flag );
	}
}
