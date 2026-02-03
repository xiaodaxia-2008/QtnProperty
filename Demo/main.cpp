#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QtnProperty/Install.h>
#include <iostream>

void regABColorDelegates();
void regIntListDelegates();
void regLayerDelegates();
void regPenWidthDelegates();
void regFreqDelegates();

int main(int argc, char *argv[])
{
	regABColorDelegates();
	regIntListDelegates();
	regLayerDelegates();
	regPenWidthDelegates();
	regFreqDelegates();

	QApplication a(argc, argv);

	qtnPropertyInstallTranslations(QLocale("zh"));

	MainWindow w;
	w.show();

	return a.exec();
}
