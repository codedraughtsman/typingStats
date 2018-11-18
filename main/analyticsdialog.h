#ifndef ANALYTICSDIALOG_H
#define ANALYTICSDIALOG_H

#include <QDialog>

namespace Ui {
class AnalyticsDialog;
}

class AnalyticsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AnalyticsDialog(QWidget *parent = 0);
	~AnalyticsDialog();

private slots:


	void on_testSelectionButton_released();

	void on_repeatLastTest_released();

private:
	Ui::AnalyticsDialog *ui;
};

#endif // ANALYTICSDIALOG_H
