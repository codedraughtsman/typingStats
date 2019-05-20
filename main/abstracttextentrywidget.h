#ifndef ABSTRACTTEXTENTRYWIDGET_H
#define ABSTRACTTEXTENTRYWIDGET_H

#include "testresult.h"

#include <QWidget>

class AbstractTextEntryWidget : public QWidget {
	Q_OBJECT
  public:
	explicit AbstractTextEntryWidget( QWidget *parent = nullptr );
	virtual void setTest( QString text, uint durationInSeconds ) = 0;

  signals:
	void testFinished( TestResult result );
	void timePercentLeftUpdate( uint percentLeft );
};

#endif // ABSTRACTTEXTENTRYWIDGET_H
