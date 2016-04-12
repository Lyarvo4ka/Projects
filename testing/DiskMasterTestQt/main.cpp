
#include <QtCore/QCoreApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "testcopyrange.h"
#include "OptionsTest.h"

using namespace std;

void initTextCodecs(const char *codecName)
{
	QTextCodec *codec = QTextCodec::codecForName(codecName);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForTr(codec);
}

int main(int argc, char *argv[])
{
	freopen("testing.log", "w", stdout);
	initTextCodecs("CP1251");
	QApplication a(argc, argv);

	QTest::qExec(new TestCopyRange, argc, argv);
	QTest::qExec( new TestGlobalOptions, argc , argv );

	return 0;
}