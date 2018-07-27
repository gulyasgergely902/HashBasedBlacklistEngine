#include <QtCore/QCoreApplication>

#include "engine.h"
#include <QtCore/qcommandlineparser.h>
#include <qdebug.h>

#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCoreApplication::setApplicationName("hbbengine");
	QCoreApplication::setApplicationVersion("1.0.0");

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

	if (parser.isSet(scanOption)) {
		const QString scanS = parser.value(scanOption);
		qDebug() << scanS;
	}
	else if (parser.isSet(lookupOption)) {
		const QString lookupS = parser.value(lookupOption);
		qDebug() << lookupS;
	}
	else if (parser.isSet(generateHashOption)) {
		const QString generateHashS = parser.value(generateHashOption);
		qDebug() << generateHashS;
	}
	else if (parser.isSet(scanFolderOption)) {
		const QString folderS = parser.value(scanFolderOption);
		qDebug() << folderS;
	}

	return a.exec();
}
