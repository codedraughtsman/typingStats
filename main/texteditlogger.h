#ifndef TEXTEDITLOGGER_H
#define TEXTEDITLOGGER_H

#include <QKeyEvent>
#include <QTextEdit>

class TextEditLogger : public QTextEdit {
	Q_OBJECT
  public:
	TextEditLogger( QWidget *parent = nullptr );

  protected:
	virtual void keyPressEvent( QKeyEvent *e );
	virtual void keyReleaseEvent( QKeyEvent *e );
  signals:
	void keyPressed( QKeyEvent *event );
	void keyReleased( QKeyEvent *event );
};

#endif // TEXTEDITLOGGER_H
