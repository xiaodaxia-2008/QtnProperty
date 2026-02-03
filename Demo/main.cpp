#include "MainWindow.h"
#include <QApplication>

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

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
