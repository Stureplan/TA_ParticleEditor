﻿#include "maincontainer.h"

MainContainer::MainContainer(QWidget* parent)
{
	// Make sure the Main Container takes full focus (keyboard input)
	setFocusPolicy(Qt::StrongFocus);
}

MainContainer::~MainContainer() {
	
}

void MainContainer::keyPressEvent(QKeyEvent* evt)
{
	if (evt->key() == Qt::Key::Key_Escape)
	{
		QCoreApplication::quit();
	}
}
