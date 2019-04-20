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
						 "dateTime DATE,"
						 "status TEXT,"
						 "correct TEXT,"
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
	// Todo add the key events.
}

const TestResult &StorageManager::getTestResult( uint uid ) const {
	return m_testResults.at( uid );
}
StorageManager storageManagerInstance;
StorageManager &storageManager() { return storageManagerInstance; }
