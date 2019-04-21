#ifndef TEXTENTRYWIDGET_H
#define TEXTENTRYWIDGET_H

#include "abstracttextentrywidget.h"
#include "keylogger.h"
#include "texteditlogger.h"
#include <QDeadlineTimer>
#include <QProgressBar>
#include <QTextDocument>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class TextEntryWidget : public QWidget {
	Q_OBJECT

	// widgets
	QHBoxLayout *m_buttonBox;
	QProgressBar *m_countDownBar;
	AbstractTextEntryWidget *m_textEntryWidget;

	void createDisplayWindow();
	void createButtons();

	void setupLayout();
	void setupConnections();

  public:
	explicit TextEntryWidget( QWidget *parent = nullptr );
	~TextEntryWidget();
	void setText( QString newText );

	void endTest();
  signals:
	void testFinished( TestResult result );

  public slots:
	void startTest( QString text, double durationMsec );

  private slots:
	void testHasEnded( TestResult result );
};

#endif // TEXTENTRYWIDGET_H
