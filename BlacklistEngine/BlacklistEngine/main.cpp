#include <QtCore/QCoreApplication>

#include "engine.h"
#include "Utils.h"
#include "DBHandler.h"
#include <QtCore/qcommandlineparser.h>
#include <qcryptographichash.h>
#include <qfileinfo.h>

#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCoreApplication::setApplicationName("hbbengine");
	QCoreApplication::setApplicationVersion("1.0.0");

	Engine * engine;
	Utils * utils;
	DBHandler * dbhandler;

	dbhandler->connectToDb();

	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::translate("main", "Given a file or folder, the application checks whether it was compromised or not."));
	parser.addHelpOption();
	
	QCommandLineOption scanOption(QStringList() << "s" << "scan", QCoreApplication::translate("main", "Find the given file's hash in the database."), QCoreApplication::translate("main", "file"), "");
	parser.addOption(scanOption);

	QCommandLineOption lookupOption(QStringList() << "l" << "lookup", QCoreApplication::translate("main", "Lookup a hash in the database."), QCoreApplication::translate("main", "hash"), "");
	parser.addOption(lookupOption);

	QCommandLineOption generateHashOption(QStringList() << "g" << "generate", QCoreApplication::translate("main", "Generate a file's hash."), QCoreApplication::translate("main", "file"), "");
	parser.addOption(generateHashOption);

	QCommandLineOption scanFolderOption(QStringList() << "f" << "folder", QCoreApplication::translate("main", "Scan files in a folder"), QCoreApplication::translate("main", "folder"), "");
	parser.addOption(scanFolderOption);

	parser.process(a);

	QString data;

	if (parser.isSet(scanOption)) {
		data = parser.value(scanOption);
		if (!QFileInfo::exists(data)) {
			utils->print("File not found!");
			return 0;
		}
		QString md5 = engine->generateFileHash(data, QCryptographicHash::Md5);
		QString sha1 = engine->generateFileHash(data, QCryptographicHash::Sha1);
		QString sha256 = engine->generateFileHash(data, QCryptographicHash::Sha256);
		if (dbhandler->findInDB(md5, sha1, sha256)) {
			utils->print("Result: Blocked");
		}
		else {
			utils->print("Result: No threat detected");
		}
		return 0;
	}
	else if (parser.isSet(lookupOption)) {
		data = parser.value(lookupOption);
		if (dbhandler->findInDB(data)) {
			utils->print("Result: Blocked");
		}
		else {
			utils->print("Result: No threat detected");
		}
		return 0;
	}
	else if (parser.isSet(generateHashOption)) {
		data = parser.value(generateHashOption);
		utils->print("MD5: " + engine->generateFileHash(data, QCryptographicHash::Md5));
		utils->print("SHA1: " + engine->generateFileHash(data, QCryptographicHash::Sha1));
		utils->print("SHA256: " + engine->generateFileHash(data, QCryptographicHash::Sha256));
		return 0;
	}
	else if (parser.isSet(scanFolderOption)) {
		data = parser.value(scanFolderOption);
		if (!QFileInfo::exists(data)) {
			utils->print("Given folder not found!");
			return 0;
		}
		QStringList results = engine->findFilesInFolder(data);
		for (auto it = results.begin(); it != results.end(); ++it) {
			QString md5 = engine->generateFileHash(*it, QCryptographicHash::Md5);
			QString sha1 = engine->generateFileHash(*it, QCryptographicHash::Sha1);
			QString sha256 = engine->generateFileHash(*it, QCryptographicHash::Sha256);
			if (dbhandler->findInDB(md5, sha1, sha256)) {
				utils->print("Result for " + *it + ": Blocked");
			}
			else {
				utils->print("Result for " + *it + ": No threat detected");
			}
		}
		return 0;
	}
	else {
		parser.showHelp();
	}

	return a.exec();
}
