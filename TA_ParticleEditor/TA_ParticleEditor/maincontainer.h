

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
#include <QPushButton>
#include <QSlider>
#include <QImageReader>
#include <QTabWidget>
#include <QCheckBox>
#include <QInputDialog>

#include "utility.h"
#include "graphics.h"

#define DEFAULT_LIFETIME 1.0f
#define DEFAULT_EMISSIONDELAY 0.1f
#define DEFAULT_VELOCITY FLOAT3(0,0,0)
#define DEFAULT_GRAVITY 1.0f
#define DEFAULT_DDS_TEXTUREPATH			std::string(Utility::Path() + "Data\\Textures\\ddstexture.png").c_str()


class MainContainer : public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

	void SetPointers(ParticleSystem* ps);
	void Initialize();
	void BuildParticleSystem();
	void SetUiElements();
	

public slots:
	void setLifetime();
	void setEmissionDelay(int value);
	void setVelocityX();
	void setVelocityXSlider(int value);
	void setVelocityY();
	void setVelocityYSlider(int value);
	void setVelocityZ();
	void setVelocityZSlider(int value);

	void SetOffsetX();
	void SetOffsetY();
	void SetOffsetZ();

	void SetOffsetXSlider(int value);
	void SetOffsetYSlider(int value);
	void SetOffsetZSlider(int value);


	void SetRotation();
	void SetRotationSlider(int value);
	void setMaxParticles();
	void setGravity();
	void BrowseTexture();
	void BrowseTextureNoise();
	void load();
	void save();

	void color0();
	void color1();
	void color2();
	void emitterTypeChanged(int index);
	void textureTypeChanged(int index);
	void shaderCompileChanged(int useless);
	void BloomParticles(int useless);
	void startSizeX();
	void startSizeY();
	void endSizeX();
	void endSizeY();
	void rectResize();
	void setColumnsRows();
	void setLooping(int value);

	void selectTab(int index);
	void addTab(int index);
	void removeTab(int index);
	void RenameTab(int index);

protected:
	virtual void keyPressEvent(QKeyEvent* evt);
	virtual void keyReleaseEvent(QKeyEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
private:
	void ClearValues();
	void ClearUI();
	void FillValues();

	// PROGRAM POINTERS
	Graphics* graphics;
	//ParticleSystem* particlesystem;
	
	// UI POINTERS
	QLabel* textFieldParticleInfo;
	QLineEdit* textFieldLifetime;
	QLabel* textFieldEmissionDelay;
	QLineEdit* textFieldVelocityX;
	QLineEdit* textFieldVelocityY;
	QLineEdit* textFieldVelocityZ;
	QLineEdit* textFieldOffsetX;
	QLineEdit* textFieldOffsetY;
	QLineEdit* textFieldOffsetZ;
	QLineEdit* textFieldMaxParticles;
	QLineEdit* textFieldGravity;
	QLineEdit* textFieldStartSizeX;
	QLineEdit* textFieldStartSizeY;
	QLineEdit* textFieldEndSizeX;
	QLineEdit* textFieldEndSizeY;
	QLineEdit* textFieldRectSizeX;
	QLineEdit* textFieldRectSizeZ;
	QLineEdit* textFieldRotation;
	QPushButton* browseBtn;
	QPushButton* saveBtn;
	QPushButton* loadBtn;
	QTextBrowser* textBrowser;
	QTextBrowser* textBrowserNoise;
	QLineEdit* color0Display;
	QLineEdit* color1Display;
	QLineEdit* color2Display;
	QComboBox* emitterTypeDisplay;
	QComboBox* textureTypeBox;
	QWidget* rectangleWidget;
	QWidget* spriteSheetWidget;
	QLabel* textureView;
	QLabel* textureViewNoise;
	QLineEdit* spriteColumns;
	QLineEdit* spriteRows;
	QSlider* velocityXSlider;
	QSlider* velocityYSlider;
	QSlider* velocityZSlider;
	QSlider* offsetXSlider;
	QSlider* offsetYSlider;
	QSlider* offsetZSlider;
	QSlider* rotationSlider;
	QSlider* emissionDelaySlider;
	QLabel*  emissionDelaySlider_label;
	QTabWidget* psTabs;
	QCheckBox* interpolateFrames;
	QCheckBox* noiseDissolve;
	QCheckBox* bloomParticles;
	QCheckBox* loopingCheckBox;

	// QT VARIABLES
	//QString mTexturePath;
	//QString mTextureNoisePath;
	QString savePath;
	QColor mColor0;
	QColor mColor1;
	QColor mColor2;

	// PS VARIABLES
	EMITTER mCurrentPS;
	int mCurrentPSIndex = 0;
};