#include "particleeditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::addLibraryPath("./");
	QApplication a(argc, argv);
	ParticleEditor w;
	w.show();
	return a.exec();
}
