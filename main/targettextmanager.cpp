#include "targettextmanager.h"
#include <QDateTime>
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
// todo cursor disapears when typing past the end of the target text.
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
		textChunks.append( QPair<QString, TextChunkStatus>(
			m_targetText.right( lengthLeft ), TextChunkStatus::UNTYPED ) );
	} else if ( m_targetText.length() < m_visibleText.length() ) {
		uint lengthLeft = m_visibleText.length() - i;
		textChunks.append( QPair<QString, TextChunkStatus>(
			m_visibleText.right( lengthLeft ), TextChunkStatus::ERROR ) );
	} // else the two strings are the same lenght and nothing needs to be added.

	return textChunks;
}

bool TargetTextManager::enteredTextIsValid() {
	// todo try this shorter method.
	// QString::compare(m_targetText, m_visibleText, Qt::CaseInsensitive);
	if ( m_visibleText.length() == 0 ) {
		// have not entered any text yet, so it is valid.
		return true;
	}

	uint overlapLength = qMin( m_targetText.length(), m_visibleText.length() );
	if ( m_visibleText.length() > m_targetText.length() ) {
		return false;
	}
	for ( uint i = 0; i < overlapLength; i++ ) {
		if ( m_targetText[ i ] != m_visibleText[ i ] ) {
			return false;
		}
	}
	return true;
}

void TargetTextManager::keyPressed( QKeyEvent *event ) {
	// todo add del key?. may not be needed since the cursor is always at the
	// end of the text and can never delete any text.
	// Todo remove nonprinting chars like arrow keys
	if ( m_keyEvents.isEmpty() ) {
		// start the timer running.
		m_testStartTime = QDateTime::currentMSecsSinceEpoch();
	}
	bool isCorrect = false;
	KeyEvent::strokeType strokeType;
	if ( event->key() == Qt::Key_Backspace ) {
		// check to see if the last entered char is incorrect.
		// todo mark the keyEvent that is being erased as nonFinal.

		// if the entered text is incorrect then backspacing is correct.
		isCorrect = !enteredTextIsValid();
		strokeType = KeyEvent::strokeType::ERASE;
		m_visibleText.chop( 1 );

	} else {

		bool wasCorrectBeforeKey = enteredTextIsValid();
		if ( event->key() == Qt::Key_Return ) {
			m_visibleText.append( '\n' );
		} else {
			m_visibleText += event->text();
		}
		isCorrect = enteredTextIsValid();
		if ( isCorrect ) {
			strokeType = KeyEvent::strokeType::FINAL;
		} else {
			if ( wasCorrectBeforeKey ) {
				strokeType = KeyEvent::strokeType::LEADING_ERROR;
			} else {
				strokeType = KeyEvent::strokeType::OVERTYPE;
			}
		}
	}

	long long timeElapsed =
		QDateTime::currentMSecsSinceEpoch() - m_testStartTime;
	m_keyEvents.push_back( KeyEvent( KeyEvent::keyStatus::PRESSED, strokeType,
									 event->text(), isCorrect, timeElapsed ) );

	emit textHasChanged();
	if ( m_visibleText == m_targetText ) {
		emit testHasFinished( m_keyEvents );
	}
}

void TargetTextManager::keyReleased( QKeyEvent *event ) {}
