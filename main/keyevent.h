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
	enum class keyStatus { PRESSED, RELEASED };
	enum class strokeType { CORRECT, INCORRECT, BACKSPACE, OVERTYPE };

	KeyEvent() {}
	KeyEvent( keyStatus status, strokeType intype, QString key,
			  uint timeElaspedMsec );
	keyStatus m_status;
	strokeType m_type;
	QString m_key;
	uint m_timeElaspedMsec;
};
Q_DECLARE_METATYPE( KeyEvent )
QDebug operator<<( QDebug dbg, const KeyEvent &data );

#endif // KEYEVENT_H
