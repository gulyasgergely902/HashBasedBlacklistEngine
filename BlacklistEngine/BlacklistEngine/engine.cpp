#include "engine.h"

#include <iostream>


Engine::Engine()
{
	
}


Engine::~Engine()
{

}

QString Engine::generateFileHash(QString path, QCryptographicHash::Algorithm algorithm)
{
	QFile file(path);
	if (file.open(QFile::ReadOnly)) {
		QCryptographicHash hash(algorithm);
		if (hash.addData(&file)) {
			return hash.result();
		}

	}

	return "null";
}


