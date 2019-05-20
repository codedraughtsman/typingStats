#ifndef LASTTESTANALYTICWIDGET_H
#define LASTTESTANALYTICWIDGET_H

#include "testresult.h"

#include <QWidget>

namespace Ui {
class LastTestAnalyticWidget;
}

class LastTestAnalyticWidget : public QWidget {
	Q_OBJECT
	TestResult m_testResult;

  public:
	explicit LastTestAnalyticWidget( QWidget *parent = 0 );
	~LastTestAnalyticWidget();
	void setTestResult( TestResult result );

  public slots:
	void updateToTestResult( uint uid );

  private:
	Ui::LastTestAnalyticWidget *ui;
};

#endif // LASTTESTANALYTICWIDGET_H
