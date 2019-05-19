#include "testresult.h"

TestResult::TestResult() {}

TestResult::TestResult( uint testDurationMsec, QVector<KeyEvent> keyEvents )
	: m_keyEvents( keyEvents ), m_testDurationMsec( testDurationMsec ) {}

float TestResult::getWpmGross() {
	uint symbolsTotal = 0;
	for ( KeyEvent key : m_keyEvents ) {
		/*if ( key.m_type == KeyEvent::strokeType::CORRECT ) {
			symbolsTotal++;
		}*/	}
		// return ( symbolsTotal / 5.0 ) / ( m_testDurationMsec / ( 60 * 1000 )
		// );
		return ( symbolsTotal * 60.0 * 1000 ) / ( m_testDurationMsec * 5 );
}

uint TestResult::getNumberOfMatchingKeyEvents( KeyEvent::keyStatus status,
											   KeyEvent::strokeType type,
											   bool isCorrect ) {
	uint count = 0;
	for ( KeyEvent event : m_keyEvents ) {
		if ( event.isType( status, type, isCorrect ) ) {
			count++;
		}
	}
	return count;
}
