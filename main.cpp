#include "demogallary.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	DemoGallary w;
	w.show();
	return a.exec();
}
