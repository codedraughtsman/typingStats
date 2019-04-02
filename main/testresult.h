#ifndef TESTRESULT_H
#define TESTRESULT_H

#include "keyevent.h"

#include <QVector>

class TestResult {
  public:
	QVector<KeyEvent> m_keyEvents;
	uint m_testUid;
	uint m_testDurationMsec;
	TestResult();
	TestResult( uint testDurationMsec, QVector<KeyEvent> keyEvents );
	/**
	 * @brief getWpmGross is all the symbols typed (no including backspace,
	 * shift, or other modifiers)
	 * divided by 5 then divided by time taken.
	 * @return
	 */
	float getWpmGross( void );
	uint getNumberOfMatchingKeyEvents( KeyEvent::keyStatus status,
									   KeyEvent::strokeType type );
};

#endif // TESTRESULT_H
