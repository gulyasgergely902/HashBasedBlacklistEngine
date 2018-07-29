#include "DBHandler.h"

Utils * utils;

DBHandler::DBHandler()
{
	
}


DBHandler::~DBHandler()
{
}

bool DBHandler::connectToDb()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	QString path = QDir::currentPath() + "/hashDB.db";
	db.setDatabaseName(path);
	if (!db.open()) {
		utils->print("Error connecting to database!");
		return false;
	}
	return true;
}

bool DBHandler::findInDB(const QString& md5, const QString& sha1, const QString& sha256)
{
	bool found = false;
	QSqlQuery query;
	query.prepare("SELECT md5, sha1, sha256 FROM hashTable WHERE md5 = (:md5Var) OR sha1 = (:sha1Var) OR sha256 = (:sha256Var)");
	query.bindValue(":md5Var", md5);
	query.bindValue(":sha1Var", sha1);
	query.bindValue(":sha256Var", sha256);
	if (query.exec()) {
		while (query.next()) {
			found = true;
		}
	}
	else {
		utils->print("Database error: " + query.lastError().text());
	}

	return found;
}

bool DBHandler::findInDB(const QString & data)
{
	bool found = false;
	QSqlQuery query;
	query.prepare("SELECT md5, sha1, sha256 FROM hashTable WHERE md5 = (:md5Var) OR sha1 = (:sha1Var) OR sha256 = (:sha256Var)");
	query.bindValue(":md5Var", data);
	query.bindValue(":sha1Var", data);
	query.bindValue(":sha256Var", data);
	if (query.exec()) {
		while (query.next()) {
			found = true;
		}
	}
	else {
		utils->print("Database error: " + query.lastError().text());
	}

	return found;
}
