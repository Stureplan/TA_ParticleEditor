#include "particleeditor.h"

ParticleEditor::ParticleEditor(QWidget *parent, Qt::WindowFlags flags)	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	//setCentralWidget(ui.mainContainer);
	centralWidget()->setLayout(ui.graphics->layout());
	setCentralWidget(ui.graphics);

}

ParticleEditor::~ParticleEditor()
{
}
