#ifndef TARGETTEXTMANAGER_H
#define TARGETTEXTMANAGER_H

#include <QKeyEvent>
#include <QObject>
enum class TextChunkStatus { COMPLEATED, CURSOR, UNTYPED, ERROR };

class TargetTextManager : public QObject {
	Q_OBJECT
	QString m_targetText; // stores the desired target text.

	QString m_visibleText; // stores the text that has been entered so far and
						   // is visible to the user

	bool isDeleationKeyPressEvent( QKeyEvent *event );

	TextChunkStatus getTextCharStatus( uint index );

  public:
	explicit TargetTextManager( QString targetText = "",
								QObject *parent = nullptr );
	void setTargetText( QString targetText );
	QList<QPair<QString, TextChunkStatus>> getTextChunks();
	uint currentNumberOfMistakes();
	// todo add ways of getting keystrokes and test results from class.

  signals:
	// Todo add results to this.
	void testHasFinished( void );
	void textHasChanged( void );
  public slots:
	// handles the user input coming into the manager.
	void keyPressed( QKeyEvent *event );
	void keyReleased( QKeyEvent *event );
};

#endif // TARGETTEXTMANAGER_H
