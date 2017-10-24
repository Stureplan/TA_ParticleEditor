﻿#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QPlainTextEdit>

#include "graphics.h"

class MainContainer : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

	void GraphicsWindow(Graphics* gfx);
	void ParticleIDLabel(QLabel* lbl);
	void ParticleInfoLabel(QLabel* lbl);
	void LifetimeInput(QPlainTextEdit* pte);

//public slots:
	//void setVector();

protected:
	virtual void keyPressEvent(QKeyEvent* evt);
	virtual void keyReleaseEvent(QKeyEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
private:
	Graphics* graphics;
	QLabel* labelID;
	QLabel* labelInfo;
	QPlainTextEdit* textField;
	float mLifetime;

};