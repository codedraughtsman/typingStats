#ifndef TEXTENTRYWIDGET_H
#define TEXTENTRYWIDGET_H

#include <QTextDocument>
#include <QTextEdit>
#include <QWidget>
#include "texteditlogger.h"

class TextEntryWidget : public QWidget {
	Q_OBJECT
	QTextEdit *m_sourceWindow;
	TextEditLogger *m_inputWindow;
	QTextDocument *m_sourceDocument;
	QTextDocument *m_inputDocument;
	QString m_inputString;

	void createDisplayWindow();
	void createInputWindow();

public:
	explicit TextEntryWidget( QWidget *parent = nullptr );
	void setText( QString newText );

  signals:

  public slots:
	void checkText();
};

#endif // TEXTENTRYWIDGET_H
