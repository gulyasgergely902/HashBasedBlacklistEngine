#pragma once

#include <QtCore/qcoreapplication.h>
#include <qfile.h>

class Engine
{
public:
	Engine();
	~Engine();
	QString generateFileHash(QString path);
};

