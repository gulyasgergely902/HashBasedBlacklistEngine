#pragma once

#include <QtCore/qcoreapplication.h>
#include <qfile.h>
#include <qcryptographichash.h>
#include <qdiriterator.h>
#include <qfileinfo.h>

class Engine
{
public:
	Engine();
	~Engine();
	QString generateFileHash(QString path, QCryptographicHash::Algorithm algorithm);
	QStringList findFilesInFolder(const QString & path);
};

