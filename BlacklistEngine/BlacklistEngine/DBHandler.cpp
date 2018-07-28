#include "DBHandler.h"



DBHandler::DBHandler()
{
}


DBHandler::~DBHandler()
{
}

QString DBHandler::findInDB(const QString& md5, const QString& sha1, const QString& sha256)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	QString path = QDir::currentPath() + "/hashDB.db";
	db.setDatabaseName(path);
	db.open();
	QSqlQuery query;
	query.prepare("SELECT * FROM hashTable WHERE md5 = (:md5) AND sha1 = (:sha1) AND sha256 = (:sha256))");
	query.bindValue(":md5", md5);

	return QString();
}
