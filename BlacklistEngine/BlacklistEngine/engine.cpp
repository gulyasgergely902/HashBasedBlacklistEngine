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
			return hash.result().toHex();
		}

	}

	return "null";
}

QStringList Engine::findFilesInFolder(const QString & path)
{
	QStringList results;
	QDirIterator it(path, QDirIterator::NoIteratorFlags);
	while (it.hasNext()) {
		it.next();
		if (QFileInfo(it.filePath()).isFile()) {
			results << it.filePath();
		}
	}
	return results;
}




