#include <QtCore/QCoreApplication>

#include "engine.h"
#include "Utils.h"
#include "DBHandler.h"
#include <QtCore/qcommandlineparser.h>
#include <qcryptographichash.h>
#include <qfileinfo.h>
#include <qmap.h>

enum Option {
	scanOption,
	lookupOption,
	generateHashOption,
	scanFolderOption
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCoreApplication::setApplicationName("hbbengine");
	QCoreApplication::setApplicationVersion("1.0.0");

	Engine engine;
	Utils utils;

	engine.init();

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

	if (parser.isSet(scanOption)) {
		QString path = parser.value(scanOption);

		switch (engine.scanFile(path)) {
		case 0:
			utils.print("Result: No threat detected");
			break;
		case 1:
			utils.print("Result: Blocked");
			break;
		case -1:
			utils.print("Error: File not found!");
			break;
		}
		return 0;
	}
	else if (parser.isSet(lookupOption)) {
		QString hash = parser.value(lookupOption);

		switch (engine.lookup(parser.value(lookupOption))) {
		case true:
			utils.print("Result: Blocked");
			break;
		case false:
			utils.print("Result: No threat detected");
			break;
		}
		return 0;
	}
	else if (parser.isSet(generateHashOption)) {
		QString file = parser.value(generateHashOption);
		utils.print("MD5: " + engine.generateFileHash(file, QCryptographicHash::Md5));
		utils.print("SHA1: " + engine.generateFileHash(file, QCryptographicHash::Sha1));
		utils.print("SHA256: " + engine.generateFileHash(file, QCryptographicHash::Sha256));
		return 0;
	}
	else if (parser.isSet(scanFolderOption)) {
		QString folderPath = parser.value(scanFolderOption);
		if (!QFileInfo::exists(folderPath)) {
			utils.print("Given folder not found!");
			return 0;
		}
		QStringList results = engine.findFilesInFolder(folderPath);
		for (auto it = results.begin(); it != results.end(); ++it) {
			switch (engine.scanFile(*it)) {
			case 0:
				utils.print("File: " + *it + ", Result: Blocked");
				break;
			case 1:
				utils.print("FIle: " + *it + ", Result: No threat detected");
				break;
			case -1:
				utils.print("Error: File not found!");
				break;
			}
		}
		return 0;
	}
	else {
		parser.showHelp();
	}

	return a.exec();
}