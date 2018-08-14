#pragma once

#include <QtCore/qcoreapplication.h>
#include <qfile.h>
#include <qcryptographichash.h>
#include <qdiriterator.h>
#include <qfileinfo.h>

#include "DBHandler.h"

class Engine
{
public:
	Engine();
	~Engine();
	bool init();
	qint16 scanFile(QString path);
	bool lookup(QString hash);
	QString generateFileHash(QString path, QCryptographicHash::Algorithm algorithm);
	QStringList findFilesInFolder(const QString & path);
};

