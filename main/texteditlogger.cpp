#include "texteditlogger.h"

#include <QDebug>

TextEditLogger::TextEditLogger( QWidget *parent ) : QTextEdit( parent ) {}

void TextEditLogger::keyPressEvent( QKeyEvent *e ) {

	QTextEdit::keyPressEvent( e );
	emit keyPressed( e );
}

void TextEditLogger::keyReleaseEvent( QKeyEvent *e ) {
	QTextEdit::keyReleaseEvent( e );
	emit keyReleased( e );
}
