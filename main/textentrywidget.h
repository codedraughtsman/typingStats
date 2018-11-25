#ifndef TEXTENTRYWIDGET_H
#define TEXTENTRYWIDGET_H

#include "keylogger.h"
#include "texteditlogger.h"
#include <QDeadlineTimer>
#include <QProgressBar>
#include <QTextDocument>
#include <QTextEdit>
#include <QWidget>

class TextEntryWidget : public QWidget {
	Q_OBJECT
	QTextEdit *m_sourceWindow;
	TextEditLogger *m_inputWindow;
	QTextDocument *m_sourceDocument;
	QTextDocument *m_inputDocument;
	QString m_inputString;
	QProgressBar *m_countDownBar;
	QDeadlineTimer m_timeLeft;
	double m_testDurationMsec;
	QTimer *m_timer;
	KeyLogger m_keyLogger;

	void createDisplayWindow();
	void createInputWindow();

  public:
	explicit TextEntryWidget( QWidget *parent = nullptr );
	~TextEntryWidget();
	void setText( QString newText );

  signals:
	void testFinished( void );
  public slots:
	void checkText();
	void startTest( QString text, double durationMsec );
	void keyReleased( QString key );
	void keyPressed( QString key );

  protected:
	void recordKeyEvent( KeyEvent::keyStatus keyStatus, QString keyText );
  private slots:
	void updateCountDownBar();
};

#endif // TEXTENTRYWIDGET_H
