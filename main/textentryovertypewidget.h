#ifndef TEXTENTRYOVERTYPEWIDGET_H
#define TEXTENTRYOVERTYPEWIDGET_H

#include "abstracttextentrywidget.h"
#include "targettextmanager.h"
#include "texteditlogger.h"
#include <QObject>

#include <QTextEdit>

class TextEntryOverTypeWidget : public AbstractTextEntryWidget {
	Q_OBJECT
	uint m_durationInSeconds;
	QString m_text;
	TextEditLogger *m_textEditWidget;

	TargetTextManager m_targetTextManager;

  public:
	// todo add default text to constructor.
	TextEntryOverTypeWidget( QWidget *parent = nullptr );

	// AbstractTextEntryWidget interface
  public:
	virtual void setTest( QString text, uint durationInSeconds ) override;
	TestResult endTest();

  signals:
	// virtual void testFinished( TestResult result ) override;
	// virtual void timePercentLeftUpdate( uint percentLeft );

  public slots:
	virtual void testPause( bool pauseTest ) override;

  private:
	QString colourizeChunk( QString text, TextChunkStatus status );
	void updateDisplayedText();
	QString convertTextToHTML( QString text );
  private slots:
	void testHasEnded( QVector<KeyEvent> keyEvents );
};

#endif // TEXTENTRYOVERTYPEWIDGET_H
