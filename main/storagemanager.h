#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "testresult.h"

#include <QObject>
#include <QVector>

class StorageManager : public QObject {
	Q_OBJECT
	QVector<TestResult> m_testResults;

	void init();
	void createTables();

  public:
	explicit StorageManager();
	uint addTestResult( TestResult result );
	const TestResult &getTestResult( uint uid ) const;

  signals:
	void testResultAdded( uint uid );
  public slots:
};
StorageManager &storageManager();
#endif // STORAGEMANAGER_H
