#ifndef TEXTEDITLOGGER_H
#define TEXTEDITLOGGER_H

#include <QKeyEvent>
#include <QTextEdit>

class TextEditLogger : public QTextEdit {
	Q_OBJECT
  public:
	TextEditLogger();

  protected:
	virtual void keyPressEvent( QKeyEvent *e );
	virtual void keyReleaseEvent( QKeyEvent *e );
  signals:
	void keyPressed( QString key );
	void keyReleased( QString key );
};

#endif // TEXTEDITLOGGER_H
