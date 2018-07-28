#pragma once

#include <QtCore/qcoreapplication.h>
#include <qsqldatabase.h>
#include <qdir.h>
#include <qsqlquery.h>

class DBHandler
{
public:
	DBHandler();
	~DBHandler();
	QString findInDB(const QString& md5, const QString& sha1, const QString& sha256);
};

