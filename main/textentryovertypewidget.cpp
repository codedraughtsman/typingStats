#include "textentryovertypewidget.h"

#include <QVBoxLayout>

TextEntryOverTypeWidget::TextEntryOverTypeWidget( QWidget *parent )
	: AbstractTextEntryWidget( parent ) {
	m_textEditWidget = new QTextEdit( this );
	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget( m_textEditWidget );
	setLayout( lay );
}

void TextEntryOverTypeWidget::setTest( QString text, uint durationInSeconds ) {
	m_text = text;
	m_textEditWidget->setText( m_text );
}

TestResult TextEntryOverTypeWidget::endTest() {}

void TextEntryOverTypeWidget::testFinished( TestResult result ) {}
void TextEntryOverTypeWidget::timePercentLeftUpdate( uint percentLeft ) {}

void TextEntryOverTypeWidget::testPause( bool shouldPause ) {}
