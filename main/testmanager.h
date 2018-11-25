#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QAbstractTableModel>
#include <QSharedPointer>

#include "testdata.h"

class TestManager : public QAbstractTableModel {
	QVector<QSharedPointer<TestData>> m_tests;

  public:
	TestManager();
	enum { TITLE, INSTANCE };

	virtual int rowCount( const QModelIndex &parent ) const override;
	virtual int columnCount( const QModelIndex &parent ) const override;
	virtual QVariant data( const QModelIndex &index, int role ) const override;
	void addTest( QString title, QString contents );
};
#endif // TESTMANAGER_H
