#ifndef TESTEDITORWIDGET_H
#define TESTEDITORWIDGET_H

#include <QWidget>

namespace Ui {
class TestEditorWidget;
}

class TestEditorWidget : public QWidget {
	Q_OBJECT

  public:
	explicit TestEditorWidget( QWidget *parent = nullptr );
	~TestEditorWidget();

  signals:
	void startTest( QString text, uint durationInSeconds );

  private slots:
	void runStartTest();

  private:
	Ui::TestEditorWidget *ui;
};

#endif // TESTEDITORWIDGET_H
