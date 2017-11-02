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
#define DEFAULT_TEXTURE "plasmaball.png"
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
		QLineEdit* lifetimeInputUI,
		QLineEdit* emissionDelayUI,
		QLineEdit* velocityXUI,
		QLineEdit* velocityYUI,
		QLineEdit* velocityZUI,
		QLineEdit* gravityUI,
		QPushButton* browseUI,
		QPushButton* saveUI,
		QLineEdit* maxParticlesUI,
		QTextBrowser* browseTextBoxUI,
		QLineEdit* colorInDisplayUI,
		QLineEdit* colorOutDisplayUI,
		QComboBox* scaleUI,
		QLineEdit* sizeXUI,
		QLineEdit* sizeYUI,
		QLineEdit* rectSizeXUI,
		QLineEdit* rectSizeZUI);
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
	void emitterTypeChanged(int index);
	void sizeX();
	void sizeY();

	void rectResize();

protected:
	virtual void keyPressEvent(QKeyEvent* evt);
	virtual void keyReleaseEvent(QKeyEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
private:
	Graphics* graphics;
	ParticleSystem* particlesystem;
	QLabel* textFieldParticleInfo;
	QLineEdit* textFieldLifetime;
	QLineEdit* textFieldEmissionDelay;
	QLineEdit* textFieldVelocityX;
	QLineEdit* textFieldVelocityY;
	QLineEdit* textFieldVelocityZ;
	QLineEdit* textFieldMaxParticles;
	QLineEdit* textFieldGravity;
	QLineEdit* textFieldSizeX;
	QLineEdit* textFieldSizeY;
	QLineEdit* textFieldRectSizeX;
	QLineEdit* textFieldRectSizeZ;


	QPushButton* browseBtn;
	QPushButton* saveBtn;
	QTextBrowser* textBrowser;
	QLineEdit* colorInDisplay;
	QLineEdit* colorOutDisplay;
	QComboBox* scaleBoxDisplay;

	QString mTexturePath;
	QString savePath;

	QColor mColorIn;
	QColor mColorOut;

	//FLOAT3 mPosition;
	EMITTER_TYPE mEmitterType;
	FLOAT3 mPosition;
	int mMaxParticles;
	FLOAT3 mVelocity;
	float mEmissionDelay;
	float mLifetime;
	float mGravity;
	float mTextFieldValue;
	float mSizeX;
	float mSizeY;
	float mRectSizeX;
	float mRectSizeZ;
};