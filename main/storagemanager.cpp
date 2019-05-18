#include "storagemanager.h"

#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#define DIR_NAME "typingstats"
StorageManager::StorageManager() : QObject() { init(); }

void StorageManager::init() {

	// create DB path
	QString path = QDir::home().filePath( "." DIR_NAME "/storage.db" );
	qDebug() << "creating ~/" DIR_NAME "/ "
			 << QDir::home().mkpath( "." DIR_NAME "/" );
	QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( path );
	if ( !db.open() ) {
		qDebug() << "failed to open database: " << path;
		// todo exit program.
		// show user popup?
	}

	createTables();
}
void StorageManager::createTables() {
	QSqlQuery query;
	bool result;
	result = query.exec( "CREATE TABLE IF NOT EXISTS testResults "
						 "(uid TEXT PRIMARY KEY ,"
						 "startTime DATE,"
						 "duration TEXT"
						 ")" );
	if ( !result ) {
		qDebug() << "failed to create table testResults";
		qDebug() << "SqLite error:" << query.lastError().text();
	}
	result = query.exec( "CREATE TABLE IF NOT EXISTS keyEvents "
						 "(eventID TEXT PRIMARY KEY ,"
						 "testID TEXT,"
						 "timeFromStartMS INT,"
						 "status TEXT,"
						 "correct INT,"
						 "type TEXT"
						 ")" );
	if ( !result ) {
		qDebug() << "failed to create table keyEvents";
		qDebug() << "SqLite error:" << query.lastError().text();
	}
}
uint getNextUid() { return 1; }

void StorageManager::addTestResult( TestResult result ) {
	/*m_testResults.append( result );
	// use the index as the uid.
	uint uid = m_testResults.length() - 1;
	emit testResultAdded( uid );
	return uid;*/
	qDebug() << "saving result";
	uint uid = getNextUid();
	QSqlQuery query;
	QDateTime currentTime = QDateTime::currentDateTime();

	query.prepare( "INSERT INTO testResults (uid, startTime, Duration) "
				   "VALUES (:uid, :startTime, :Duration )" );
	query.bindValue( ":uid", uid );
	query.bindValue( ":startTime", currentTime.toString() );
	query.bindValue( ":Duration", result.m_testDurationMsec );
	bool ok = query.exec();
	if ( !ok ) {
		qDebug() << "failed to write testResult to database";
		qDebug() << "Sql query is " << query.executedQuery();
		qDebug() << "SqLite error:" << query.lastError().text();
		/*QMessageBox::warning( this, "typingStats error",
							  "failed to write testresult to sql database",
							  QMessageBox::Ok );
		*/ return;
	}

	// add the key events.
	QSqlQuery queryKeyEvents;
	queryKeyEvents.prepare( "INSERT INTO keyEvents (uid, timeFromStartMS, "
							"Duration, status, correct, type) "
							"VALUES (:testID, :timeFromStartMS, :Duration, "
							":status, :correct, :type )" );
	for ( KeyEvent keyEvent : result.m_keyEvents ) {

		queryKeyEvents.bindValue( ":testID", uid );
		queryKeyEvents.bindValue( ":timeFromStartMS",
								  keyEvent.m_timeElaspedMsec );
		queryKeyEvents.bindValue( ":Duration", keyEvent.m_timeElaspedMsec );
		queryKeyEvents.bindValue( ":status", (int)keyEvent.m_status );
		queryKeyEvents.bindValue( ":type", (int)keyEvent.m_type );
	}
	ok = query.exec();
	if ( !ok ) {
		qDebug() << "failed to write testResult to database";
		qDebug() << "Sql query is " << query.executedQuery();
		qDebug() << "SqLite error:" << query.lastError().text();
		/*QMessageBox::warning( this, "typingStats error",
							  "failed to write testresult to sql database",
							  QMessageBox::Ok );
		*/ return;
	}
}
const TestResult &StorageManager::getTestResult( uint uid ) const {
	return m_testResults.at( uid );
}
StorageManager storageManagerInstance;
StorageManager &storageManager() { return storageManagerInstance; }
