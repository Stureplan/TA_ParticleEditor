#ifndef PARTICLEEDITOR_H
#define PARTICLEEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_particleeditor.h"

class ParticleEditor : public QMainWindow
{
	Q_OBJECT

public:
	ParticleEditor(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~ParticleEditor();

private:
	Ui::ParticleEditorClass ui;
};

#endif // PARTICLEEDITOR_H
