#include "choosetestdialog.h"
#include "textentrywidget.h"
#include "ui_choosetestdialog.h"

ChooseTestDialog::ChooseTestDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChooseTestDialog)
{
	ui->setupUi(this);
}

ChooseTestDialog::~ChooseTestDialog()
{
	delete ui;
}


void ChooseTestDialog::on_StartButton_released()
{
	TextEntryWidget *tew=new TextEntryWidget( );
	double durationMsec= ui->durationTime->currentText().toInt()*60*1000;
	tew->startTest("apple tree\nthe quick brown fox junped over the lazy dog",durationMsec);
	tew->show();
}

void ChooseTestDialog::on_cancelButton_released()
{
	close();
}
