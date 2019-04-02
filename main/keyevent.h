#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QDebug>
#include <QMetaType>
#include <QString>

/**
 * @brief The KeyEvent class holds the data of a single key press.
 * This includes the keyStatus (pressed, released) and the stroke type (CORRECT,
 * INCORRECT, BACKSPACE, OVERTYPE ).
 * The key its self is also stored as a QString.
 */
class KeyEvent {
  public:
	enum class keyStatus {
		PRESSED = ( 1 << 0 ),
		RELEASED = ( 1 << 1 ),
		ANY = ( 1 << 0 ) | ( 1 << 1 )
	};
	enum class strokeType {
		CORRECT = ( 1 << 0 ),
		INCORRECT = ( 1 << 1 ),
		BACKSPACE = ( 1 << 2 ),
		OVERTYPE = ( 1 << 3 )
	};

	KeyEvent() {}
	KeyEvent( keyStatus status, strokeType intype, QString key,
			  uint timeElaspedMsec );
	keyStatus m_status;
	strokeType m_type;
	QString m_key;
	uint m_timeElaspedMsec;
	bool isType( keyStatus status, strokeType type );
};
Q_DECLARE_METATYPE( KeyEvent )
QDebug operator<<( QDebug dbg, const KeyEvent &data );

/*
inline KeyEvent::strokeType operator|( KeyEvent::strokeType a,
									   KeyEvent::strokeType b ) {
	return static_cast<KeyEvent::strokeType>( static_cast<int>( a ) |
											  static_cast<int>( b ) );
}
*/
inline bool operator|( KeyEvent::strokeType a, KeyEvent::strokeType b ) {
	return static_cast<bool>( static_cast<int>( a ) | static_cast<int>( b ) );
}
inline bool operator|( KeyEvent::keyStatus a, KeyEvent::keyStatus b ) {
	return static_cast<bool>( static_cast<int>( a ) | static_cast<int>( b ) );
}

#endif // KEYEVENT_H
