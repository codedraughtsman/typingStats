#include "keyevent.h"

KeyEvent::KeyEvent( KeyEvent::keyStatus status, KeyEvent::strokeType intype,
					QString key, uint timeElaspedMsec )
	: m_status( status ), m_type( intype ), m_key( key ),
	  m_timeElaspedMsec( timeElaspedMsec ) {}

bool KeyEvent::isType( keyStatus status, KeyEvent::strokeType type ) {
	return ( m_status | status ) && ( m_type | type );
}

QDebug operator<<( QDebug dbg, const KeyEvent &data ) {

	dbg.nospace() << "KeyEvent key: " << data.m_key
				  << ", timeElapsed: " << data.m_timeElaspedMsec;
	return dbg.maybeSpace();
}
