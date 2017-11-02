#include "particleeditor.h"

ParticleEditor::ParticleEditor(QWidget *parent, Qt::WindowFlags flags)	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	setCentralWidget(ui.maincontainer);
	setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	//QApplication::setKeyboardInputInterval(16);
	ui.maincontainer->SetPointers
	(
		ui.graphics,
		ui.graphics->ParticleSystemPtr(),
		ui.label_ParticleInfo, 
		ui.lifetime, 
		ui.emissionDelay, 
		ui.velocityX, 
		ui.velocityY,
		ui.velocityZ,
		ui.gravity,
		ui.browsepath,
		ui.savePS,
		ui.maxParticles,
		ui.textBrowser,
		ui.colorInDisplay,
		ui.colorOutDisplay,
		ui.scaleBox,
		ui.sizeX,
		ui.sizeY,
		ui.rectSizeX,
		ui.rectSizeZ
	);

	ui.maincontainer->Init();
	ui.maincontainer->BuildParticleSystem();
	ui.graphics->LoadParticles();
}

ParticleEditor::~ParticleEditor()
{
}
