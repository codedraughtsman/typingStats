#ifndef CHOOSETESTDIALOG_H
#define CHOOSETESTDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseTestDialog;
}

class ChooseTestDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChooseTestDialog(QWidget *parent = 0);
	~ChooseTestDialog();

private slots:

	void on_StartButton_released();

	void on_cancelButton_released();

private:
	Ui::ChooseTestDialog *ui;
};

#endif // CHOOSETESTDIALOG_H
