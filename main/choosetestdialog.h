#ifndef CHOOSETESTDIALOG_H
#define CHOOSETESTDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseTestDialog;
}

class ChooseTestDialog : public QDialog {
	Q_OBJECT

  public:
	explicit ChooseTestDialog( QWidget *parent = 0 );
	~ChooseTestDialog();

  protected:
	void startTest();
  private slots:

	void on_StartButton_released();

	void on_cancelButton_released();

	void on_testSelectionView_doubleClicked( const QModelIndex &index );

  private:
	Ui::ChooseTestDialog *ui;
};

#endif // CHOOSETESTDIALOG_H
