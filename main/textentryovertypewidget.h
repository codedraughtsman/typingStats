#ifndef TEXTENTRYOVERTYPEWIDGET_H
#define TEXTENTRYOVERTYPEWIDGET_H

#include "abstracttextentrywidget.h"
#include <QObject>

#include <QTextEdit>

class TextEntryOverTypeWidget : public AbstractTextEntryWidget {

	QString m_text;
	QTextEdit *m_textEditWidget;

  public:
	TextEntryOverTypeWidget( QWidget *parent = nullptr );

	// AbstractTextEntryWidget interface
  public:
	virtual void setTest( QString text, uint durationInSeconds ) override;
	TestResult endTest();

  signals:
	virtual void testFinished( TestResult result ) override;
	virtual void timePercentLeftUpdate( uint percentLeft );

  public slots:
	virtual void testPause( bool shouldPause ) override;
};

#endif // TEXTENTRYOVERTYPEWIDGET_H
