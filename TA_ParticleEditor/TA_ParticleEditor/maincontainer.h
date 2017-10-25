#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include "utility.h"

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
	void EmissionDelayInput(QPlainTextEdit* pte);
	void VelocityXInput(QPlainTextEdit* pte);
	void VelocityYInput(QPlainTextEdit* pte);
	void VelocityZInput(QPlainTextEdit* pte);
	void MaxParticlesInput(QPlainTextEdit* pte);
	float ErrorHandleUI(QString text, QPlainTextEdit* qpte);
	

public slots:
	void setLifetime();
	void setEmissionDelay();
	void setVelocityX();
	void setVelocityY();
	void setVelocityZ();
	void setMaxParticles();

protected:
	virtual void keyPressEvent(QKeyEvent* evt);
	virtual void keyReleaseEvent(QKeyEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
private:
	Graphics* graphics;
	QLabel* labelID;
	QLabel* labelInfo;
	QPlainTextEdit* textFieldLifetime;
	QPlainTextEdit* textFieldEmissionDelay;
	QPlainTextEdit* textFieldVelocityX;
	QPlainTextEdit* textFieldVelocityY;
	QPlainTextEdit* textFieldVelocityZ;
	QPlainTextEdit* textFieldMaxParticles;
	float mTextFieldValue;
	float mLifetime;
	float mEmissionDelay;
	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;
	int mMaxParticles;
	POSITION velocity;

};