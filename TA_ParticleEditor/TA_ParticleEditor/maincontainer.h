#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QCoreApplication>

#include "graphics.h"

class MainContainer : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

	void GraphicsWindow(Graphics* gfx);

protected:
	virtual void keyPressEvent(QKeyEvent* evt);

private:
	Graphics* graphics;
};