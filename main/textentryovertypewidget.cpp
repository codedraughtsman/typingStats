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

QString TextEntryOverTypeWidget::colourizeChunk( QString text,
												 TextChunkStatus status ) {
	QStringList styleTags;
	if ( status == TextChunkStatus::COMPLEATED ||
		 status == TextChunkStatus::UNTYPED ) {
		styleTags << "color:green";
	} else if ( status == TextChunkStatus::ERROR ) {
		styleTags << "color:red";
	} else if ( status == TextChunkStatus::CURSOR ) {
		if ( m_targetTextManager.currentNumberOfMistakes() ) {
			// there is at least one mistake.
			styleTags << "background-color:red";
		} else {
			styleTags << "background-color:green";
		}
	}
	QString outputTextHTML = QString( "<span style=\"%1\">%2</span>" )
								 .arg( styleTags.join( ';' ) )
								 .arg( text );
	return outputTextHTML;
}

void TextEntryOverTypeWidget::updateDisplayedText() {
	QList<QPair<QString, TextChunkStatus>> textChunks =
		m_targetTextManager.getTextChunks();
	QString outputText;
	for ( uint i = 0; i < textChunks.size(); i++ ) {
		outputText +=
			colourizeChunk( textChunks[ i ].first, textChunks[ i ].second );
	}
	m_textEditWidget->setText( outputText );
}

TestResult TextEntryOverTypeWidget::endTest() {}

void TextEntryOverTypeWidget::testFinished( TestResult result ) {}
void TextEntryOverTypeWidget::timePercentLeftUpdate( uint percentLeft ) {}

void TextEntryOverTypeWidget::testPause( bool pauseTest ) {}
