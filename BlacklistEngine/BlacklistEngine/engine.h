#pragma once

#include <QtCore/qcoreapplication.h>
#include <qfile.h>
#include <qcryptographichash.h>

class Engine
{
public:
	Engine();
	~Engine();
	QString generateFileHash(QString path, QCryptographicHash::Algorithm algorithm);
};

