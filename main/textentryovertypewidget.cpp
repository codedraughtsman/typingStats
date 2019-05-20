#include "textentryovertypewidget.h"

#include <QVBoxLayout>

TextEntryOverTypeWidget::TextEntryOverTypeWidget( QWidget *parent )
	: AbstractTextEntryWidget( parent ), m_durationInSeconds( 0 ) {
	m_textEditWidget = new TextEditLogger( this );
	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget( m_textEditWidget );
	setLayout( lay );

	connect( &m_targetTextManager, &TargetTextManager::textHasChanged, this,
			 &TextEntryOverTypeWidget::updateDisplayedText );
	connect( &m_targetTextManager, &TargetTextManager::testHasFinished, this,
			 &TextEntryOverTypeWidget::testHasEnded );

	connect( m_textEditWidget, &TextEditLogger::keyPressed,
			 &m_targetTextManager, &TargetTextManager::keyPressed );
	connect( m_textEditWidget, &TextEditLogger::keyReleased,
			 &m_targetTextManager, &TargetTextManager::keyReleased );
}

void TextEntryOverTypeWidget::setTest( QString text, uint durationInSeconds ) {
	m_text.clear();
	m_durationInSeconds = durationInSeconds;
	m_targetTextManager.setTargetText( text );
}

QString TextEntryOverTypeWidget::convertTextToHTML( QString text ) {
	return text.replace( '\n', "&crarr;<br/>" ).replace( '\t', "&rarr;" );
}

void TextEntryOverTypeWidget::testHasEnded( QVector<KeyEvent> keyEvents ) {
	qDebug() << "TextEntryOverTypeWidget::testHasEnded";
	TestResult result( m_durationInSeconds, keyEvents );
	dumpObjectInfo();
	emit testFinished( result );
	// Todo show stats in window for this test.
}

QString TextEntryOverTypeWidget::colourizeChunk( QString text,
												 TextChunkStatus status ) {
	QStringList styleTags;
	if ( status == TextChunkStatus::UNTYPED ) {
		styleTags << "color:black";
	} else if ( status == TextChunkStatus::COMPLEATED ) {
		styleTags << "color:green";
	} else if ( status == TextChunkStatus::ERROR ) {
		styleTags << "color:red";
	} else if ( status == TextChunkStatus::CURSOR ) {
		if ( m_targetTextManager.enteredTextIsValid() ) {
			styleTags << "background-color:green";
		} else {
			// there is at least one mistake.
			styleTags << "background-color:red";
		}
	}
	if ( styleTags.empty() ) {
		// need to set text color to black;
		styleTags << "color:black";
	}
	QString outputTextHTML = QString( "<span style=\"%1\">%2</span>" )
								 .arg( styleTags.join( ';' ) )
								 .arg( convertTextToHTML( text ) );
	return outputTextHTML;
}

void TextEntryOverTypeWidget::updateDisplayedText() {
	QList<QPair<QString, TextChunkStatus>> textChunks =
		m_targetTextManager.getTextChunks();
	QString outputText;
	for ( int i = 0; i < textChunks.size(); i++ ) {
		outputText +=
			colourizeChunk( textChunks[ i ].first, textChunks[ i ].second );
	}
	m_textEditWidget->setText( outputText );
}
