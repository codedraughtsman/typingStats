#ifndef ABSTRACTTEXTENTRYWIDGET_H
#define ABSTRACTTEXTENTRYWIDGET_H

#include "testresult.h"

#include <QWidget>

class AbstractTextEntryWidget : public QWidget {
	Q_OBJECT
  public:
	explicit AbstractTextEntryWidget( QWidget *parent = nullptr );
	virtual void setTest( QString text, uint durationInSeconds ) = 0;
	/**
	 * @brief endTest This ends the current test, returning the test result up
	 * to this point.
	 * @return The test result that the user has typed up to this point.
	 */
	virtual TestResult endTest() = 0;

  signals:
	void testFinished( TestResult result );
	void timePercentLeftUpdate( uint percentLeft );

  public slots:
	virtual void testPause( bool shouldPause ) = 0;
};

#endif // ABSTRACTTEXTENTRYWIDGET_H
