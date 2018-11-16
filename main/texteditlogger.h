#ifndef TEXTEDITLOGGER_H
#define TEXTEDITLOGGER_H

#include<QTextEdit>
#include<QKeyEvent>

class TextEditLogger : public QTextEdit
{
public:
	TextEditLogger();
protected:
	virtual void keyPressEvent(QKeyEvent * e);
	virtual void keyReleaseEvent(QKeyEvent * e);
};

#endif // TEXTEDITLOGGER_H
