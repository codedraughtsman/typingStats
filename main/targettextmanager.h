#ifndef TARGETTEXTMANAGER_H
#define TARGETTEXTMANAGER_H

#include "keyevent.h"

#include <QKeyEvent>
#include <QObject>

enum class TextChunkStatus { COMPLEATED, CURSOR, UNTYPED, ERROR };

class TargetTextManager : public QObject {
	Q_OBJECT
	QString m_targetText; // stores the desired target text.

	QString m_visibleText; // stores the text that has been entered so far and
						   // is visible to the user

	TextChunkStatus getTextCharStatus( uint index );
	QVector<KeyEvent> m_keyEvents; // logs the key presses and releases.
	uint m_testStartTime;

  public:
	explicit TargetTextManager( QString targetText = "",
								QObject *parent = nullptr );
	void setTargetText( QString targetText );
	QList<QPair<QString, TextChunkStatus>> getTextChunks();
	// todo add ways of getting keystrokes and test results from class.

	bool enteredTextIsValid();
  signals:
	// Todo add results to this.
	void testHasFinished( QVector<KeyEvent> );
	void textHasChanged( void );
  public slots:
	// handles the user input coming into the manager.
	void keyPressed( QKeyEvent *event );
	void keyReleased( QKeyEvent *event );
};

#endif // TARGETTEXTMANAGER_H
