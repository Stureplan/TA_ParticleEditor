#include "particleeditor.h"

ParticleEditor::ParticleEditor(QWidget *parent, Qt::WindowFlags flags)	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	setCentralWidget(ui.maincontainer);
	setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	//QApplication::setKeyboardInputInterval(16);
	ui.maincontainer->SetPointers(ui.graphics->ParticleSystemPtr());
	ui.maincontainer->Init();
	ui.maincontainer->BuildParticleSystem();
	ui.graphics->LoadParticles();
}

ParticleEditor::~ParticleEditor()
{
}
