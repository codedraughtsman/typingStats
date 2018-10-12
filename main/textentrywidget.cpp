#include "textentrywidget.h"
#include <QDebug>
#include <QLayout>

#include <QVBoxLayout>

TextEntryWidget::TextEntryWidget( QWidget *parent ) : QWidget( parent ) {
	m_sourceWindow = new QTextEdit;
	m_sourceWindow->setMinimumSize( 100, 100 );
	m_sourceWindow->setReadOnly( true );
	m_sourceDocument = new QTextDocument;
	m_sourceWindow->setDocument( m_sourceDocument );
	m_sourceDocument->setHtml( "apple	<br>ss th" );

	m_inputWindow = new QTextEdit;
	m_inputDocument = new QTextDocument;
	m_inputWindow->setMinimumSize( 100, 100 );
	m_inputWindow->setDocument( m_inputDocument );

	QTextOption option;
	option.setFlags( QTextOption::ShowLineAndParagraphSeparators |
					 QTextOption::ShowTabsAndSpaces );
	m_sourceDocument->setDefaultTextOption( option );
	m_inputDocument->setDefaultTextOption( option );

	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget( m_sourceWindow );
	lay->addWidget( m_inputWindow );
	setLayout( lay );
	connect( m_inputWindow, &QTextEdit::textChanged, this,
			 &TextEntryWidget::checkText );
}

void TextEntryWidget::setText( QString newText ) {
	m_sourceWindow->setText( newText );
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

void TextEntryWidget::checkText() {
	int firstDifference =
		myDiff( m_sourceWindow->toPlainText(), m_inputWindow->toPlainText() );
	qDebug() << "firstDifference: " << firstDifference;
	if ( firstDifference == -1 ) {
		// set to good.
		m_sourceDocument->setHtml( m_sourceWindow->toPlainText() );

	} else {
		// set to error.
		qDebug() << QString( "error: strings differ. %1  !== %2 " )
						.arg( m_sourceWindow->toPlainText() )
						.arg( m_inputWindow->toPlainText() );
		QString newText( "%1<span style='color: red'>%2<\\span><span "
						 "style='color: black'>%3" );
		//		QString newText( "%1<font color='red'>%2<\\font>%3" );
		QString inText = m_sourceWindow->toPlainText();
		QString before = inText.left( firstDifference );
		QString center = inText.at( firstDifference );
		QString after = inText.right( inText.length() - 1 - firstDifference );
		qDebug() << newText;
		newText = newText.arg( before ).arg( center ).arg( after );
		qDebug() << "before : " << before << "center " << center
				 << " after: " << after << " inText.length()"
				 << inText.length();
		qDebug() << "html text:" << newText;

		m_sourceDocument->setHtml( newText );
	}
}
