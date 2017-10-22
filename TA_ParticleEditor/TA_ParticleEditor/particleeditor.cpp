#include "particleeditor.h"

ParticleEditor::ParticleEditor(QWidget *parent, Qt::WindowFlags flags)	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	setCentralWidget(ui.maincontainer);
	setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	//QApplication::setKeyboardInputInterval(16);

	ui.maincontainer->GraphicsWindow(ui.graphics);
}

ParticleEditor::~ParticleEditor()
{
}
