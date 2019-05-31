#include "storagemanager.h"

#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

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
						 "(uid INT PRIMARY KEY ,"
						 "startTime DATE,"
						 "duration TEXT"
						 ")" );
	if ( !result ) {
		qDebug() << "failed to create table testResults";
		qDebug() << "SqLite error:" << query.lastError().text();
	}
	result = query.exec( "CREATE TABLE IF NOT EXISTS keyEvents "
						 "(eventID TEXT,"
						 "testID TEXT,"
						 "timeFromStartMS INT,"
						 "status TEXT,"
						 "keyPressed TEXT,"
						 "keyExpected TEXT,"
						 "keyInline TEXT,"
						 "isCorrect INT,"
						 "type TEXT"
						 ")" );
	if ( !result ) {
		qDebug() << "failed to create table keyEvents";
		qDebug() << "SqLite error:" << query.lastError().text();
	}
}
uint getNextUid() {
	QSqlQuery query( "SELECT MAX(uid ) FROM testResults;" );
	bool result = query.exec();
	if ( !result ) {
		qDebug() << "failed to 'SELECT MAX(uid ) FROM testResults;'";
		qDebug() << "SqLite error:" << query.lastError().text();
		// todo throw an error.
	}
	query.first();
	uint currentID = query.value( 0 ).toUInt();
	return currentID + 1;
}

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
	qDebug() << "uid is " << uid;
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
		*/ // return;
	}

	// add the key events.
	QSqlQuery queryKeyEvents;
	queryKeyEvents.prepare(
		"INSERT INTO keyEvents (testID, timeFromStartMS, "
		"status, isCorrect, type, eventID, keyPressed, keyExpected, keyInline) "
		"VALUES (:testID, :timeFromStartMS, "
		":status, :isCorrect, :type, :eventID, :keyPressed, :keyExpected, "
		":keyInline )" );
	qDebug() << "inserting " << result.m_keyEvents.length() << " keyEvent";
	for ( int i = 0; i < result.m_keyEvents.length(); i++ ) {
		KeyEvent keyEvent = result.m_keyEvents[ i ];
		queryKeyEvents.bindValue( ":testID", uid );
		queryKeyEvents.bindValue( ":eventID", i );
		queryKeyEvents.bindValue( ":timeFromStartMS",
								  keyEvent.m_timeElaspedMsec );
		queryKeyEvents.bindValue( ":status", keyEvent.keyStatusToString() );
		queryKeyEvents.bindValue( ":type", keyEvent.strokeTypeToString() );
		queryKeyEvents.bindValue( ":isCorrect", keyEvent.m_isCorrect );
		queryKeyEvents.bindValue( ":keyPressed", keyEvent.m_keyPressed );
		queryKeyEvents.bindValue( ":keyExpected", keyEvent.m_keyExpected );
		queryKeyEvents.bindValue( ":keyInline", keyEvent.m_keyInline );

		ok = queryKeyEvents.exec();
		if ( !ok ) {
			qDebug() << "failed to write the " << i
					 << " keyEvent to  to database";
			qDebug() << "Sql query is " << queryKeyEvents.executedQuery();
			qDebug() << "SqLite error:" << queryKeyEvents.lastError().text();
		/*QMessageBox::warning( this, "typingStats error",
							  "failed to write testresult to sql database",
							  QMessageBox::Ok );
		*/}
	}
}
const TestResult &StorageManager::getTestResult( uint uid ) const {
	return m_testResults.at( uid );
}
StorageManager storageManagerInstance;
StorageManager &storageManager() { return storageManagerInstance; }
