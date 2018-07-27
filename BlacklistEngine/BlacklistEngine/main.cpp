#include <QtCore/QCoreApplication>

#include "engine.h"
#include <QtCore/qcommandlineparser.h>
#include <qdebug.h>
#include <qcryptographichash.h>

#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCoreApplication::setApplicationName("hbbengine");
	QCoreApplication::setApplicationVersion("1.0.0");

	Engine * e;

	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::translate("main", "Hash Based Blacklist Engine"));
	parser.addHelpOption();
	
	QCommandLineOption scanOption(QStringList() << "s" << "scan", QCoreApplication::translate("main", "Find the given file's hash in the database."), QCoreApplication::translate("main", "scan"), "");
	parser.addOption(scanOption);

	QCommandLineOption lookupOption(QStringList() << "l" << "lookup", QCoreApplication::translate("main", "Lookup a hash in the database."), QCoreApplication::translate("main", "lookup"), "");
	parser.addOption(lookupOption);

	QCommandLineOption generateHashOption(QStringList() << "g" << "generate", QCoreApplication::translate("main", "Generate a file's hash."), QCoreApplication::translate("main", "generate"), "");
	parser.addOption(generateHashOption);

	QCommandLineOption scanFolderOption(QStringList() << "f" << "folder", QCoreApplication::translate("main", "Scan files in a folder"), QCoreApplication::translate("main", "folder"), "");
	parser.addOption(scanFolderOption);

	parser.process(a);

	QString data;

	if (parser.isSet(scanOption)) {
		data = parser.value(scanOption);
		qDebug() << data;
	}
	else if (parser.isSet(lookupOption)) {
		data = parser.value(lookupOption);
		qDebug() << data;
	}
	else if (parser.isSet(generateHashOption)) {
		data = parser.value(generateHashOption);
		qDebug() << "MD5: " << e->generateFileHash(data, QCryptographicHash::Md5);
		qDebug() << "SHA1: " << e->generateFileHash(data, QCryptographicHash::Sha1);
		qDebug() << "SHA256: " << e->generateFileHash(data, QCryptographicHash::Sha256);
		return 0;
	}
	else if (parser.isSet(scanFolderOption)) {
		data = parser.value(scanFolderOption);
		qDebug() << data;
	}

	return a.exec();
}
