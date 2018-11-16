#include "texteditlogger.h"

#include <QDebug>

TextEditLogger::TextEditLogger()
{

}

void TextEditLogger::keyPressEvent(QKeyEvent *e)
{
	qDebug() << "keypress event :"<< e->text();
	QTextEdit::keyPressEvent(e);
}

void TextEditLogger::keyReleaseEvent(QKeyEvent *e)
{
	qDebug() << "keyrelease event :"<< e->text();
}
