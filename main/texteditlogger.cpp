#include "texteditlogger.h"

#include <QDebug>

TextEditLogger::TextEditLogger() {}

void TextEditLogger::keyPressEvent( QKeyEvent *e ) {

	QTextEdit::keyPressEvent( e );
	emit keyPressed( e->text() );
}

void TextEditLogger::keyReleaseEvent( QKeyEvent *e ) {
	QTextEdit::keyReleaseEvent( e );
	emit keyReleased( e->text() );
}
