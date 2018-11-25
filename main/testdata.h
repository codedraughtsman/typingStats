#ifndef TESTDATA_H
#define TESTDATA_H

#include <QDebug>
#include <QMetaType>
#include <QString>

class TestData {
	QString m_title, m_contents;

  public:
	TestData();
	TestData( const TestData &data );
	TestData( QString title, QString contents );
	QString getContents() const;
	QString getTitle() const;
};
Q_DECLARE_METATYPE( TestData )
Q_DECLARE_METATYPE( TestData * )
Q_DECLARE_METATYPE( QSharedPointer<TestData> )

QDebug operator<<( QDebug dbg, const TestData &data );
#endif // TESTDATA_H
