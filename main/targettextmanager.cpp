#include "targettextmanager.h"
#include <QDebug>

TargetTextManager::TargetTextManager( QString targetText, QObject *parent )
	: QObject( parent ), m_targetText( targetText ) {}

void TargetTextManager::setTargetText( QString targetText ) {
	m_targetText = targetText;

	// clear the data that the user has entered so far.
	m_visibleText.clear();
	// todo clear the recorded keystrokes.
	emit textHasChanged();
}
TextChunkStatus TargetTextManager::getTextCharStatus( uint index ) {
	if ( m_targetText[ index ] == m_visibleText[ index ] ) {
		return TextChunkStatus::COMPLEATED;
	}
	return TextChunkStatus::ERROR;
}
QList<QPair<QString, TextChunkStatus>> TargetTextManager::getTextChunks() {
	QList<QPair<QString, TextChunkStatus>> textChunks;
	uint overlapLength = qMin( m_targetText.length(), m_visibleText.length() );
	uint i = 0;
	TextChunkStatus lastStatus = getTextCharStatus( 0 );
	QString text;
	for ( ; i < overlapLength; i++ ) {
		TextChunkStatus currentStatus = getTextCharStatus( i );
		if ( lastStatus != currentStatus ) {
			textChunks.append(
				QPair<QString, TextChunkStatus>( text, lastStatus ) );
			qDebug() << "appending chunk " << text;
			text.clear();
		}
		text.append( m_targetText[ i ] );
		lastStatus = currentStatus;
	}
	// add any leftover chunks.
	textChunks.append( QPair<QString, TextChunkStatus>( text, lastStatus ) );

	// add the cursor
	textChunks.append( QPair<QString, TextChunkStatus>(
		QString( m_targetText[ i++ ] ), TextChunkStatus::CURSOR ) );
	// add untyped text. check that the untyped text is greater than the typed
	// text. otherwise it may crash.
	if ( m_targetText.length() > m_visibleText.length() ) {
		uint lengthLeft = m_targetText.length() - i;
		qDebug() << "i" << i << ", m_targetText " << m_targetText.length();
		textChunks.append( QPair<QString, TextChunkStatus>(
			m_targetText.right( lengthLeft ), TextChunkStatus::UNTYPED ) );
	} else {
		uint lengthLeft = m_visibleText.length() - i;
		qDebug() << "i" << i << ", m_targetText " << m_targetText.length();
		textChunks.append( QPair<QString, TextChunkStatus>(
			m_visibleText.right( lengthLeft ), TextChunkStatus::ERROR ) );
	}
	return textChunks;
}

uint TargetTextManager::currentNumberOfMistakes() { return 1; }

bool TargetTextManager::isDeleationKeyPressEvent( QKeyEvent *event ) {
	return false;
}

void TargetTextManager::keyPressed( QKeyEvent *event ) {
	if ( isDeleationKeyPressEvent( event ) ) {
		return;
	} else {
		m_visibleText += event->text();
	}

	emit textHasChanged();
}

void TargetTextManager::keyReleased( QKeyEvent *event ) {}
