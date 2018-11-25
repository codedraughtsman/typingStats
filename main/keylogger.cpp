#include "keylogger.h"

KeyLogger::KeyLogger() {}

void KeyLogger::logEvent( KeyEvent event ) { m_events.append( event ); }

const QVector<KeyEvent> &KeyLogger::getEvents() { return m_events; }
