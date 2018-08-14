#include "engine.h"

DBHandler dbhandler;

Engine::Engine()
{
	
}


Engine::~Engine()
{

}

bool Engine::init()
{
	if (dbhandler.connectToDb()) {
		return false;
	}
	else {
		return true;
	}
}

qint16 Engine::scanFile(QString path)
{
	if (!QFileInfo::exists(path)) {
		return -1;
	}

	QString md5 = generateFileHash(path, QCryptographicHash::Md5);
	QString sha1 = generateFileHash(path, QCryptographicHash::Sha1);
	QString sha256 = generateFileHash(path, QCryptographicHash::Sha256);

	if (dbhandler.findInDB(md5, sha1, sha256)) {
		return 1;
	}
	else {
		return 0;
	}
}

bool Engine::lookup(QString hash)
{
	if (dbhandler.findInDB(hash)) {
		return true;
	}
	else {
		return false;
	}
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




