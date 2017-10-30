#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBrowser>
#include <QColorDialog>
#include <QColor>
#include <QLineEdit>
#include <QComboBox>


#include "utility.h"
#include "graphics.h"

#define DEFAULT_MAXPARTICLES 10
#define DEFAULT_LIFETIME 1.0f
#define DEFAULT_EMISSIONDELAY 0.1f
#define DEFAULT_VELOCITY FLOAT3(0,0,0)
#define DEFAULT_GRAVITY 1.0f
#define DEFAULT_SIZE 1.0f

class MainContainer : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

	void SetPointers(Graphics* gfx,
		ParticleSystem* ps,
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
		QTextBrowser* browseTextBoxUI,
		QLineEdit* colorInDisplayUI,
		QLineEdit* colorOutDisplayUI,
		QComboBox* scaleUI,
		QPlainTextEdit* sizeXUI,
		QPlainTextEdit* sizeYUI);
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

	void colorIn();
	void colorOut();
	void scaleModeChanged(int index);
	void sizeX();
	void sizeY();


protected:
	virtual void keyPressEvent(QKeyEvent* evt);
	virtual void keyReleaseEvent(QKeyEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
private:
	Graphics* graphics;
	ParticleSystem* particlesystem;
	QLabel* textFieldParticleInfo;
	QPlainTextEdit* textFieldLifetime;
	QPlainTextEdit* textFieldEmissionDelay;
	QPlainTextEdit* textFieldVelocityX;
	QPlainTextEdit* textFieldVelocityY;
	QPlainTextEdit* textFieldVelocityZ;
	QPlainTextEdit* textFieldMaxParticles;
	QPlainTextEdit* textFieldGravity;
	QPlainTextEdit* textFieldSizeX;
	QPlainTextEdit* textFieldSizeY;

	QPushButton* browseBtn;
	QPushButton* saveBtn;
	QTextBrowser* textBrowser;
	QLineEdit* colorInDisplay;
	QLineEdit* colorOutDisplay;
	QComboBox* scaleBoxDisplay;

	QString mTexturePath;
	QString savePath;

	QColor colIn;
	QColor colOut;

	FLOAT3 mPosition;
	int mMaxParticles;
	FLOAT3 mVelocity;
	float mEmissionDelay;
	float mLifetime;
	float mGravity;
	float mTextFieldValue;
	float mSizeX;
	float mSizeY;
};