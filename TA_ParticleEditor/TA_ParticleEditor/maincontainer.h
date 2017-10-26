#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBrowser>
#include "utility.h"
#include "graphics.h"

#define DEFAULT_MAXPARTICLES 0
#define DEFAULT_LIFETIME 1.0f
#define DEFAULT_EMISSIONDELAY 0.0f

class MainContainer : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

	void Init();
	void GraphicsWindow(Graphics* gfx);
	void ParticleInfoLabel(QLabel* lbl);
	void LifetimeInput(QPlainTextEdit* pte);
	void EmissionDelayInput(QPlainTextEdit* pte);
	void VelocityXInput(QPlainTextEdit* pte);
	void VelocityYInput(QPlainTextEdit* pte);
	void VelocityZInput(QPlainTextEdit* pte);
	void GravityInput(QPlainTextEdit* pte);
	void BrowseInput(QPushButton* pbtn);
	void SaveInput(QPushButton* pbtn);
	void MaxParticlesInput(QPlainTextEdit* pte);
	void BrowseTextBox(QTextBrowser* qtb);
	float ErrorHandleUI(QString text, QPlainTextEdit* qpte);
	

public slots:
	void setLifetime();
	void setEmissionDelay();
	void setVelocityX();
	void setVelocityY();
	void setVelocityZ();
	void setMaxParticles();
	void setGravity();
	void browse();
	void save();

protected:
	virtual void keyPressEvent(QKeyEvent* evt);
	virtual void keyReleaseEvent(QKeyEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
private:
	Graphics* graphics;
	QLabel* labelInfo;
	QPlainTextEdit* textFieldLifetime;
	QPlainTextEdit* textFieldEmissionDelay;
	QPlainTextEdit* textFieldVelocityX;
	QPlainTextEdit* textFieldVelocityY;
	QPlainTextEdit* textFieldVelocityZ;
	QPlainTextEdit* textFieldMaxParticles;
	QPlainTextEdit* textFieldGravity;
	QPushButton* browseBtn;
	QPushButton* saveBtn;
	QTextBrowser* textBrowser;
	QString texturePath;
	QString savePath;
	float mTextFieldValue;
	float mLifetime;
	float mEmissionDelay;
	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;
	float mGravity;
	int mMaxParticles;
	POSITION velocity;
};