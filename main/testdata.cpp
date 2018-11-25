#include "testdata.h"

TestData::TestData() {}

TestData::TestData( const TestData &data )
	: m_title( data.m_title ), m_contents( data.m_contents ) {}

TestData::TestData( QString title, QString contents )
	: m_title( title ), m_contents( contents ) {}

QString TestData::getContents() const { return m_contents; }

QString TestData::getTitle() const { return m_title; }

QDebug operator<<( QDebug dbg, const TestData &data ) {

	dbg.nospace() << "TestData: " << data.getTitle() << " : "
				  << data.getContents();
	return dbg.maybeSpace();
}
