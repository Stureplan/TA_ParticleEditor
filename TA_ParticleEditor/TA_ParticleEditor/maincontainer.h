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

#define DEFAULT_MAXPARTICLES 10
#define DEFAULT_LIFETIME 1.0f
#define DEFAULT_EMISSIONDELAY 0.1f
#define DEFAULT_VELOCITY POSITION(0,0,0)
#define DEFAULT_GRAVITY 1.0f

class MainContainer : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

	void SetPointers(Graphics* gfx,
		QLabel* particleInfoUI,
		QPlainTextEdit* lifetimeInputUI,
		QPlainTextEdit* emissionDelayUI,
		QPlainTextEdit* velocityXUI,
		QPlainTextEdit* velocityYUI,
		QPlainTextEdit* velocityZUI,
		QPlainTextEdit* gravityUI,
		QPushButton* browseUI,
		QPushButton* saveUI,
		QPlainTextEdit* maxParticlesUI,
		QTextBrowser* browseTextBoxUI);
	void Init();
	void BuildParticleSystem();

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
	QLabel* textFieldParticleInfo;
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
	QString mTexturePath;
	QString savePath;
	POSITION mPosition;
	int mMaxParticles;
	POSITION mVelocity;
	float mEmissionDelay;
	float mLifetime;
	float mGravity;
	float mTextFieldValue;
};