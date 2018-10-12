#ifndef TEXTENTRYWIDGET_H
#define TEXTENTRYWIDGET_H

#include <QTextDocument>
#include <QTextEdit>
#include <QWidget>

class TextEntryWidget : public QWidget {
	Q_OBJECT
	QTextEdit *m_sourceWindow;
	QTextEdit *m_inputWindow;
	QTextDocument *m_sourceDocument;
	QTextDocument *m_inputDocument;

  public:
	explicit TextEntryWidget( QWidget *parent = nullptr );
	void setText( QString newText );

  signals:

  public slots:
	void checkText();
};

#endif // TEXTENTRYWIDGET_H
