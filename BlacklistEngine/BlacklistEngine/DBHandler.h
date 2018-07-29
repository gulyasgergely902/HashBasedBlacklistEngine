#pragma once

#include <QtCore/qcoreapplication.h>
#include <qsqldatabase.h>
#include <qdir.h>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qsqlrecord.h>
#include "Utils.h"

class DBHandler
{
public:
	DBHandler();
	~DBHandler();
	bool connectToDb();
	bool findInDB(const QString& md5, const QString& sha1, const QString& sha256);
	bool findInDB(const QString& data);
};

