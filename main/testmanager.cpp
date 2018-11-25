#include "testmanager.h"

TestManager::TestManager() {}

int TestManager::rowCount( const QModelIndex &parent ) const {
	Q_UNUSED( parent )
	return m_tests.length();
}

int TestManager::columnCount( const QModelIndex &parent ) const {
	Q_UNUSED( parent )
	return 2;
}

QVariant TestManager::data( const QModelIndex &index, int role ) const {
	if ( !index.isValid() )
		return QVariant();

	if ( index.row() >= m_tests.size() )
		return QVariant();

	if ( role == Qt::DisplayRole ) {
		if ( index.column() == TITLE ) {
			// return title string.
			QSharedPointer<TestData> t = m_tests.at( index.row() );
			return t->getTitle();
		} else if ( index.column() == INSTANCE ) {
			// return instance.
			QSharedPointer<TestData> t = m_tests.at( index.row() );
			QVariant v;
			v.setValue( t );
			return v;
		}
	}
	// invalid request. return an invalid result.
	return QVariant();
}

void TestManager::addTest( QString title, QString contents ) {
	QSharedPointer<TestData> td =
		QSharedPointer<TestData>( new TestData( title, contents ) );
	m_tests.append( td );
}
