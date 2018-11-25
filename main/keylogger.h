#ifndef KEYLOGGER_H
#define KEYLOGGER_H
#include "keyevent.h"
#include <QVector>

class KeyLogger {
	QVector<KeyEvent> m_events;

  public:
	KeyLogger();
	void logEvent( KeyEvent event );
	const QVector<KeyEvent> &getEvents();
};

#endif // KEYLOGGER_H
