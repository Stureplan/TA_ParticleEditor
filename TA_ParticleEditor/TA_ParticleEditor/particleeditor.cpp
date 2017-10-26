#include "particleeditor.h"

ParticleEditor::ParticleEditor(QWidget *parent, Qt::WindowFlags flags)	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	setCentralWidget(ui.maincontainer);
	setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	//QApplication::setKeyboardInputInterval(16);

	ui.maincontainer->GraphicsWindow(ui.graphics);
	ui.maincontainer->ParticleInfoLabel(ui.label_ParticleInfo);
	ui.maincontainer->LifetimeInput(ui.lifetime);
	ui.maincontainer->EmissionDelayInput(ui.emissionDelay);
	ui.maincontainer->VelocityXInput(ui.velocityX);
	ui.maincontainer->VelocityYInput(ui.velocityY);
	ui.maincontainer->VelocityZInput(ui.velocityZ);
	ui.maincontainer->MaxParticlesInput(ui.maxParticles);
	ui.maincontainer->GravityInput(ui.gravity);
	ui.maincontainer->BrowseInput(ui.browsepath);
	ui.maincontainer->BrowseTextBox(ui.textBrowser);
	ui.maincontainer->SaveInput(ui.savePS);
}

ParticleEditor::~ParticleEditor()
{
}
