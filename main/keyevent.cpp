#include "keyevent.h"

KeyEvent::KeyEvent( KeyEvent::keyStatus status, KeyEvent::strokeType intype,
					QString key, bool isCorrect, uint timeElaspedMsec )
	: m_status( status ), m_type( intype ), m_isCorrect( isCorrect ),
	  m_key( key ), m_timeElaspedMsec( timeElaspedMsec ) {}

bool KeyEvent::isType( keyStatus status, KeyEvent::strokeType type,
					   bool isCorrect ) {
	return ( m_status | status ) && ( m_type | type ) &&
		   ( m_isCorrect || isCorrect );
}

QString KeyEvent::strokeTypeToString() {

	if ( m_type == strokeType::OVERTYPE ) {
		return "OVERTYPE";
	} else if ( m_type == strokeType::FINAL ) {
		return "FINAL";
	} else if ( m_type == strokeType::ERASE ) {
		return "ERASE";
	} else if ( m_type == strokeType::LEADING_ERROR ) {
		return "LEADING_ERROR";
	}
}
QString KeyEvent::keyStatusToString() {

	if ( m_status == keyStatus::PRESSED ) {
		return "PRESSED";
	} else if ( m_status == keyStatus::PRESSED ) {
		return "PRESSED";
	} else if ( m_status == keyStatus::ANY ) {
		return "ANY";
	}
}

QDebug operator<<( QDebug dbg, const KeyEvent &data ) {

	dbg.nospace() << "KeyEvent key: " << data.m_key
				  << ", timeElapsed: " << data.m_timeElaspedMsec;
	return dbg.maybeSpace();
}
