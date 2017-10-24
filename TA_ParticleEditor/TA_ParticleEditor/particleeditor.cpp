#include "particleeditor.h"

ParticleEditor::ParticleEditor(QWidget *parent, Qt::WindowFlags flags)	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	setCentralWidget(ui.maincontainer);
	setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	//QApplication::setKeyboardInputInterval(16);

	ui.maincontainer->GraphicsWindow(ui.graphics);
	ui.maincontainer->ParticleIDLabel(ui.label_ParticleID);
	ui.maincontainer->ParticleInfoLabel(ui.label_ParticleInfo);
	//ui.maincontainer->LifetimeInput(ui.lifetime);
}

ParticleEditor::~ParticleEditor()
{
}
