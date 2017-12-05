/********************************************************************************
** Form generated from reading UI file 'particleeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICLEEDITOR_H
#define UI_PARTICLEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "graphics.h"
#include "maincontainer.h"

QT_BEGIN_NAMESPACE

class Ui_ParticleEditorClass
{
public:
    MainContainer *maincontainer;
    Graphics *graphics;
    QPushButton *browsepath;
    QLabel *label_Lifetime;
    QLabel *label_Velocity;
    QLabel *label_EmissionDelay;
    QLabel *label_MaxParticles;
    QTextBrowser *textBrowser;
    QPushButton *savePS;
    QLabel *label_Gravity;
    QLabel *label_Texture;
    QPushButton *color0Btn;
    QLineEdit *color0Display;
    QLineEdit *color1Display;
    QPushButton *color1Btn;
    QLabel *label_StartSize;
    QComboBox *emitterTypeBox;
    QLabel *label_EmitterType;
    QLineEdit *velocityX;
    QLineEdit *velocityY;
    QLineEdit *velocityZ;
    QLineEdit *gravity;
    QLineEdit *lifetime;
    QLabel *label_VelocityY;
    QLineEdit *startSizeX;
    QLineEdit *startSizeY;
    QLineEdit *maxParticles;
    QWidget *rectangleWidget;
    QLabel *label_SizeY_6;
    QLineEdit *rectSizeX;
    QLineEdit *rectSizeZ;
    QPushButton *loadPS;
    QComboBox *textureTypeBox;
    QWidget *spriteSheetWidget;
    QLineEdit *spriteColumns;
    QLineEdit *spriteRows;
    QCheckBox *interpolateFrames;
    QLabel *label_SizeY_7;
    QLineEdit *endSizeY;
    QLabel *label_EndSize;
    QLineEdit *endSizeX;
    QLabel *textureView;
    QSlider *emissionDelaySlider;
    QLabel *label_EmDelaySlide;
    QSlider *velocityXSlider;
    QSlider *velocityYSlider;
    QSlider *velocityZSlider;
    QTabWidget *psTabs;
    QWidget *tab;
    QWidget *tab_2;
    QLabel *label_VelocityX;
    QLabel *label_VelocityZ;
    QPushButton *color2Btn;
    QLineEdit *color2Display;
    QLabel *label_EmitterType_2;
    QCheckBox *rotateParticles;
    QCheckBox *noiseDissolve;
    QCheckBox *looping;

    void setupUi(QMainWindow *ParticleEditorClass)
    {
        if (ParticleEditorClass->objectName().isEmpty())
            ParticleEditorClass->setObjectName(QStringLiteral("ParticleEditorClass"));
        ParticleEditorClass->resize(984, 638);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ParticleEditorClass->sizePolicy().hasHeightForWidth());
        ParticleEditorClass->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        ParticleEditorClass->setPalette(palette);
        ParticleEditorClass->setStyleSheet(QStringLiteral(""));
        ParticleEditorClass->setTabShape(QTabWidget::Rounded);
        maincontainer = new MainContainer(ParticleEditorClass);
        maincontainer->setObjectName(QStringLiteral("maincontainer"));
        graphics = new Graphics(maincontainer);
        graphics->setObjectName(QStringLiteral("graphics"));
        graphics->setGeometry(QRect(9, 9, 640, 480));
        browsepath = new QPushButton(maincontainer);
        browsepath->setObjectName(QStringLiteral("browsepath"));
        browsepath->setGeometry(QRect(10, 604, 101, 25));
        label_Lifetime = new QLabel(maincontainer);
        label_Lifetime->setObjectName(QStringLiteral("label_Lifetime"));
        label_Lifetime->setGeometry(QRect(770, 218, 51, 20));
        label_Lifetime->setAlignment(Qt::AlignCenter);
        label_Velocity = new QLabel(maincontainer);
        label_Velocity->setObjectName(QStringLiteral("label_Velocity"));
        label_Velocity->setGeometry(QRect(660, 79, 71, 20));
        label_Velocity->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_EmissionDelay = new QLabel(maincontainer);
        label_EmissionDelay->setObjectName(QStringLiteral("label_EmissionDelay"));
        label_EmissionDelay->setGeometry(QRect(660, 170, 80, 20));
        label_EmissionDelay->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_MaxParticles = new QLabel(maincontainer);
        label_MaxParticles->setObjectName(QStringLiteral("label_MaxParticles"));
        label_MaxParticles->setGeometry(QRect(910, 171, 70, 16));
        label_MaxParticles->setAlignment(Qt::AlignCenter);
        textBrowser = new QTextBrowser(maincontainer);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 580, 101, 23));
        textBrowser->setTextInteractionFlags(Qt::NoTextInteraction);
        savePS = new QPushButton(maincontainer);
        savePS->setObjectName(QStringLiteral("savePS"));
        savePS->setGeometry(QRect(869, 570, 111, 41));
        label_Gravity = new QLabel(maincontainer);
        label_Gravity->setObjectName(QStringLiteral("label_Gravity"));
        label_Gravity->setGeometry(QRect(679, 218, 51, 20));
        label_Gravity->setAlignment(Qt::AlignCenter);
        label_Texture = new QLabel(maincontainer);
        label_Texture->setObjectName(QStringLiteral("label_Texture"));
        label_Texture->setGeometry(QRect(10, 563, 91, 16));
        color0Btn = new QPushButton(maincontainer);
        color0Btn->setObjectName(QStringLiteral("color0Btn"));
        color0Btn->setGeometry(QRect(660, 10, 70, 21));
        color0Display = new QLineEdit(maincontainer);
        color0Display->setObjectName(QStringLiteral("color0Display"));
        color0Display->setGeometry(QRect(730, 10, 211, 21));
        QFont font;
        font.setKerning(true);
        color0Display->setFont(font);
        color0Display->setCursor(QCursor(Qt::IBeamCursor));
        color0Display->setFocusPolicy(Qt::NoFocus);
        color0Display->setContextMenuPolicy(Qt::NoContextMenu);
        color0Display->setFrame(false);
        color0Display->setAlignment(Qt::AlignCenter);
        color0Display->setReadOnly(true);
        color1Display = new QLineEdit(maincontainer);
        color1Display->setObjectName(QStringLiteral("color1Display"));
        color1Display->setGeometry(QRect(730, 30, 211, 21));
        color1Display->setFont(font);
        color1Display->setCursor(QCursor(Qt::IBeamCursor));
        color1Display->setMouseTracking(false);
        color1Display->setFocusPolicy(Qt::NoFocus);
        color1Display->setContextMenuPolicy(Qt::NoContextMenu);
        color1Display->setFrame(false);
        color1Display->setAlignment(Qt::AlignCenter);
        color1Display->setReadOnly(true);
        color1Display->setClearButtonEnabled(false);
        color1Btn = new QPushButton(maincontainer);
        color1Btn->setObjectName(QStringLiteral("color1Btn"));
        color1Btn->setGeometry(QRect(660, 30, 70, 21));
        label_StartSize = new QLabel(maincontainer);
        label_StartSize->setObjectName(QStringLiteral("label_StartSize"));
        label_StartSize->setGeometry(QRect(661, 271, 91, 16));
        label_StartSize->setAlignment(Qt::AlignCenter);
        emitterTypeBox = new QComboBox(maincontainer);
        emitterTypeBox->setObjectName(QStringLiteral("emitterTypeBox"));
        emitterTypeBox->setGeometry(QRect(670, 370, 121, 24));
        emitterTypeBox->setLayoutDirection(Qt::LeftToRight);
        label_EmitterType = new QLabel(maincontainer);
        label_EmitterType->setObjectName(QStringLiteral("label_EmitterType"));
        label_EmitterType->setGeometry(QRect(680, 350, 100, 16));
        label_EmitterType->setAlignment(Qt::AlignCenter);
        velocityX = new QLineEdit(maincontainer);
        velocityX->setObjectName(QStringLiteral("velocityX"));
        velocityX->setGeometry(QRect(670, 102, 90, 20));
        velocityX->setAlignment(Qt::AlignCenter);
        velocityY = new QLineEdit(maincontainer);
        velocityY->setObjectName(QStringLiteral("velocityY"));
        velocityY->setGeometry(QRect(670, 126, 90, 20));
        velocityY->setAlignment(Qt::AlignCenter);
        velocityZ = new QLineEdit(maincontainer);
        velocityZ->setObjectName(QStringLiteral("velocityZ"));
        velocityZ->setGeometry(QRect(670, 150, 90, 20));
        velocityZ->setAlignment(Qt::AlignCenter);
        gravity = new QLineEdit(maincontainer);
        gravity->setObjectName(QStringLiteral("gravity"));
        gravity->setGeometry(QRect(660, 240, 90, 20));
        gravity->setAlignment(Qt::AlignCenter);
        lifetime = new QLineEdit(maincontainer);
        lifetime->setObjectName(QStringLiteral("lifetime"));
        lifetime->setGeometry(QRect(750, 240, 90, 20));
        lifetime->setAlignment(Qt::AlignCenter);
        label_VelocityY = new QLabel(maincontainer);
        label_VelocityY->setObjectName(QStringLiteral("label_VelocityY"));
        label_VelocityY->setGeometry(QRect(650, 126, 21, 20));
        label_VelocityY->setLayoutDirection(Qt::LeftToRight);
        label_VelocityY->setAlignment(Qt::AlignCenter);
        startSizeX = new QLineEdit(maincontainer);
        startSizeX->setObjectName(QStringLiteral("startSizeX"));
        startSizeX->setGeometry(QRect(670, 290, 35, 20));
        startSizeX->setAlignment(Qt::AlignCenter);
        startSizeY = new QLineEdit(maincontainer);
        startSizeY->setObjectName(QStringLiteral("startSizeY"));
        startSizeY->setGeometry(QRect(707, 290, 35, 20));
        startSizeY->setAlignment(Qt::AlignCenter);
        maxParticles = new QLineEdit(maincontainer);
        maxParticles->setObjectName(QStringLiteral("maxParticles"));
        maxParticles->setGeometry(QRect(920, 190, 45, 20));
        maxParticles->setAlignment(Qt::AlignCenter);
        rectangleWidget = new QWidget(maincontainer);
        rectangleWidget->setObjectName(QStringLiteral("rectangleWidget"));
        rectangleWidget->setEnabled(false);
        rectangleWidget->setGeometry(QRect(670, 396, 120, 50));
        label_SizeY_6 = new QLabel(rectangleWidget);
        label_SizeY_6->setObjectName(QStringLiteral("label_SizeY_6"));
        label_SizeY_6->setGeometry(QRect(4, 1, 110, 16));
        label_SizeY_6->setAlignment(Qt::AlignCenter);
        rectSizeX = new QLineEdit(rectangleWidget);
        rectSizeX->setObjectName(QStringLiteral("rectSizeX"));
        rectSizeX->setGeometry(QRect(0, 20, 60, 20));
        rectSizeX->setAlignment(Qt::AlignCenter);
        rectSizeZ = new QLineEdit(rectangleWidget);
        rectSizeZ->setObjectName(QStringLiteral("rectSizeZ"));
        rectSizeZ->setGeometry(QRect(60, 20, 60, 20));
        rectSizeZ->setAlignment(Qt::AlignCenter);
        loadPS = new QPushButton(maincontainer);
        loadPS->setObjectName(QStringLiteral("loadPS"));
        loadPS->setGeometry(QRect(750, 570, 111, 41));
        textureTypeBox = new QComboBox(maincontainer);
        textureTypeBox->setObjectName(QStringLiteral("textureTypeBox"));
        textureTypeBox->setGeometry(QRect(800, 370, 121, 24));
        textureTypeBox->setLayoutDirection(Qt::LeftToRight);
        spriteSheetWidget = new QWidget(maincontainer);
        spriteSheetWidget->setObjectName(QStringLiteral("spriteSheetWidget"));
        spriteSheetWidget->setEnabled(false);
        spriteSheetWidget->setGeometry(QRect(800, 400, 121, 71));
        spriteColumns = new QLineEdit(spriteSheetWidget);
        spriteColumns->setObjectName(QStringLiteral("spriteColumns"));
        spriteColumns->setGeometry(QRect(0, 16, 61, 20));
        spriteColumns->setAlignment(Qt::AlignCenter);
        spriteRows = new QLineEdit(spriteSheetWidget);
        spriteRows->setObjectName(QStringLiteral("spriteRows"));
        spriteRows->setGeometry(QRect(60, 16, 61, 20));
        spriteRows->setAlignment(Qt::AlignCenter);
        interpolateFrames = new QCheckBox(spriteSheetWidget);
        interpolateFrames->setObjectName(QStringLiteral("interpolateFrames"));
        interpolateFrames->setGeometry(QRect(4, 50, 121, 17));
        label_SizeY_7 = new QLabel(spriteSheetWidget);
        label_SizeY_7->setObjectName(QStringLiteral("label_SizeY_7"));
        label_SizeY_7->setGeometry(QRect(10, 0, 110, 16));
        label_SizeY_7->setAlignment(Qt::AlignCenter);
        endSizeY = new QLineEdit(maincontainer);
        endSizeY->setObjectName(QStringLiteral("endSizeY"));
        endSizeY->setGeometry(QRect(797, 290, 35, 20));
        endSizeY->setAlignment(Qt::AlignCenter);
        label_EndSize = new QLabel(maincontainer);
        label_EndSize->setObjectName(QStringLiteral("label_EndSize"));
        label_EndSize->setGeometry(QRect(751, 271, 91, 16));
        label_EndSize->setAlignment(Qt::AlignCenter);
        endSizeX = new QLineEdit(maincontainer);
        endSizeX->setObjectName(QStringLiteral("endSizeX"));
        endSizeX->setGeometry(QRect(760, 290, 35, 20));
        endSizeX->setAlignment(Qt::AlignCenter);
        textureView = new QLabel(maincontainer);
        textureView->setObjectName(QStringLiteral("textureView"));
        textureView->setGeometry(QRect(120, 580, 50, 50));
        textureView->setScaledContents(true);
        emissionDelaySlider = new QSlider(maincontainer);
        emissionDelaySlider->setObjectName(QStringLiteral("emissionDelaySlider"));
        emissionDelaySlider->setGeometry(QRect(690, 190, 121, 22));
        emissionDelaySlider->setStyleSheet(QStringLiteral("selection-background-color: rgb(53, 53, 53);"));
        emissionDelaySlider->setMinimum(1);
        emissionDelaySlider->setMaximum(100);
        emissionDelaySlider->setOrientation(Qt::Horizontal);
        label_EmDelaySlide = new QLabel(maincontainer);
        label_EmDelaySlide->setObjectName(QStringLiteral("label_EmDelaySlide"));
        label_EmDelaySlide->setGeometry(QRect(660, 195, 30, 13));
        label_EmDelaySlide->setTextInteractionFlags(Qt::NoTextInteraction);
        velocityXSlider = new QSlider(maincontainer);
        velocityXSlider->setObjectName(QStringLiteral("velocityXSlider"));
        velocityXSlider->setGeometry(QRect(780, 101, 200, 22));
        velocityXSlider->setStyleSheet(QStringLiteral("selection-background-color: rgb(53, 53, 53);"));
        velocityXSlider->setMinimum(-99);
        velocityXSlider->setMaximum(99);
        velocityXSlider->setSingleStep(1);
        velocityXSlider->setValue(0);
        velocityXSlider->setSliderPosition(0);
        velocityXSlider->setTracking(true);
        velocityXSlider->setOrientation(Qt::Horizontal);
        velocityXSlider->setInvertedAppearance(false);
        velocityYSlider = new QSlider(maincontainer);
        velocityYSlider->setObjectName(QStringLiteral("velocityYSlider"));
        velocityYSlider->setGeometry(QRect(780, 125, 200, 22));
        velocityYSlider->setStyleSheet(QStringLiteral("selection-background-color: rgb(53, 53, 53);"));
        velocityYSlider->setMinimum(-99);
        velocityYSlider->setOrientation(Qt::Horizontal);
        velocityZSlider = new QSlider(maincontainer);
        velocityZSlider->setObjectName(QStringLiteral("velocityZSlider"));
        velocityZSlider->setGeometry(QRect(780, 149, 200, 22));
        velocityZSlider->setStyleSheet(QStringLiteral("selection-background-color: rgb(53, 53, 53);"));
        velocityZSlider->setMinimum(-99);
        velocityZSlider->setOrientation(Qt::Horizontal);
        psTabs = new QTabWidget(maincontainer);
        psTabs->setObjectName(QStringLiteral("psTabs"));
        psTabs->setGeometry(QRect(10, 491, 641, 24));
        psTabs->setLayoutDirection(Qt::LeftToRight);
        psTabs->setTabPosition(QTabWidget::South);
        psTabs->setTabShape(QTabWidget::Rounded);
        psTabs->setIconSize(QSize(16, 16));
        psTabs->setElideMode(Qt::ElideNone);
        psTabs->setTabsClosable(true);
        psTabs->setMovable(false);
        psTabs->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        psTabs->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        psTabs->addTab(tab_2, QString());
        label_VelocityX = new QLabel(maincontainer);
        label_VelocityX->setObjectName(QStringLiteral("label_VelocityX"));
        label_VelocityX->setGeometry(QRect(650, 102, 21, 20));
        label_VelocityX->setLayoutDirection(Qt::LeftToRight);
        label_VelocityX->setAlignment(Qt::AlignCenter);
        label_VelocityZ = new QLabel(maincontainer);
        label_VelocityZ->setObjectName(QStringLiteral("label_VelocityZ"));
        label_VelocityZ->setGeometry(QRect(650, 150, 21, 20));
        label_VelocityZ->setLayoutDirection(Qt::LeftToRight);
        label_VelocityZ->setAlignment(Qt::AlignCenter);
        color2Btn = new QPushButton(maincontainer);
        color2Btn->setObjectName(QStringLiteral("color2Btn"));
        color2Btn->setGeometry(QRect(660, 50, 70, 21));
        color2Display = new QLineEdit(maincontainer);
        color2Display->setObjectName(QStringLiteral("color2Display"));
        color2Display->setGeometry(QRect(730, 50, 211, 21));
        color2Display->setFont(font);
        color2Display->setCursor(QCursor(Qt::IBeamCursor));
        color2Display->setMouseTracking(false);
        color2Display->setFocusPolicy(Qt::NoFocus);
        color2Display->setContextMenuPolicy(Qt::NoContextMenu);
        color2Display->setFrame(false);
        color2Display->setAlignment(Qt::AlignCenter);
        color2Display->setReadOnly(true);
        color2Display->setClearButtonEnabled(false);
        label_EmitterType_2 = new QLabel(maincontainer);
        label_EmitterType_2->setObjectName(QStringLiteral("label_EmitterType_2"));
        label_EmitterType_2->setGeometry(QRect(810, 350, 100, 16));
        label_EmitterType_2->setAlignment(Qt::AlignCenter);
        rotateParticles = new QCheckBox(maincontainer);
        rotateParticles->setObjectName(QStringLiteral("rotateParticles"));
        rotateParticles->setGeometry(QRect(850, 240, 111, 17));
        noiseDissolve = new QCheckBox(maincontainer);
        noiseDissolve->setObjectName(QStringLiteral("noiseDissolve"));
        noiseDissolve->setGeometry(QRect(850, 260, 111, 17));
        looping = new QCheckBox(maincontainer);
        looping->setObjectName(QStringLiteral("looping"));
        looping->setGeometry(QRect(820, 192, 61, 17));
        ParticleEditorClass->setCentralWidget(maincontainer);

        retranslateUi(ParticleEditorClass);
        QObject::connect(browsepath, SIGNAL(clicked()), maincontainer, SLOT(browse()));
        QObject::connect(savePS, SIGNAL(clicked()), maincontainer, SLOT(save()));
        QObject::connect(color0Btn, SIGNAL(clicked()), maincontainer, SLOT(color0()));
        QObject::connect(color1Btn, SIGNAL(clicked()), maincontainer, SLOT(color1()));
        QObject::connect(velocityX, SIGNAL(editingFinished()), maincontainer, SLOT(setVelocityX()));
        QObject::connect(velocityY, SIGNAL(editingFinished()), maincontainer, SLOT(setVelocityY()));
        QObject::connect(velocityZ, SIGNAL(editingFinished()), maincontainer, SLOT(setVelocityZ()));
        QObject::connect(gravity, SIGNAL(editingFinished()), maincontainer, SLOT(setGravity()));
        QObject::connect(lifetime, SIGNAL(editingFinished()), maincontainer, SLOT(setLifetime()));
        QObject::connect(startSizeX, SIGNAL(editingFinished()), maincontainer, SLOT(startSizeX()));
        QObject::connect(startSizeY, SIGNAL(editingFinished()), maincontainer, SLOT(startSizeY()));
        QObject::connect(maxParticles, SIGNAL(editingFinished()), maincontainer, SLOT(setMaxParticles()));
        QObject::connect(emitterTypeBox, SIGNAL(currentIndexChanged(int)), maincontainer, SLOT(emitterTypeChanged(int)));
        QObject::connect(rectSizeX, SIGNAL(editingFinished()), maincontainer, SLOT(rectResize()));
        QObject::connect(rectSizeZ, SIGNAL(editingFinished()), maincontainer, SLOT(rectResize()));
        QObject::connect(loadPS, SIGNAL(clicked()), maincontainer, SLOT(load()));
        QObject::connect(textureTypeBox, SIGNAL(currentIndexChanged(int)), maincontainer, SLOT(textureTypeChanged(int)));
        QObject::connect(endSizeX, SIGNAL(editingFinished()), maincontainer, SLOT(endSizeX()));
        QObject::connect(endSizeY, SIGNAL(editingFinished()), maincontainer, SLOT(endSizeY()));
        QObject::connect(spriteColumns, SIGNAL(editingFinished()), maincontainer, SLOT(setColumnsRows()));
        QObject::connect(spriteRows, SIGNAL(editingFinished()), maincontainer, SLOT(setColumnsRows()));
        QObject::connect(emissionDelaySlider, SIGNAL(valueChanged(int)), maincontainer, SLOT(setEmissionDelay(int)));
        QObject::connect(velocityXSlider, SIGNAL(valueChanged(int)), maincontainer, SLOT(setVelocityXSlider(int)));
        QObject::connect(velocityYSlider, SIGNAL(valueChanged(int)), maincontainer, SLOT(setVelocityYSlider(int)));
        QObject::connect(velocityZSlider, SIGNAL(valueChanged(int)), maincontainer, SLOT(setVelocityZSlider(int)));
        QObject::connect(psTabs, SIGNAL(tabBarClicked(int)), maincontainer, SLOT(addTab(int)));
        QObject::connect(psTabs, SIGNAL(tabCloseRequested(int)), maincontainer, SLOT(removeTab(int)));
        QObject::connect(psTabs, SIGNAL(tabBarClicked(int)), maincontainer, SLOT(selectTab(int)));
        QObject::connect(color2Btn, SIGNAL(clicked()), maincontainer, SLOT(color2()));
        QObject::connect(interpolateFrames, SIGNAL(stateChanged(int)), maincontainer, SLOT(shaderCompileChanged(int)));
        QObject::connect(rotateParticles, SIGNAL(stateChanged(int)), maincontainer, SLOT(shaderCompileChanged(int)));
        QObject::connect(noiseDissolve, SIGNAL(stateChanged(int)), maincontainer, SLOT(shaderCompileChanged(int)));
        QObject::connect(looping, SIGNAL(stateChanged(int)), maincontainer, SLOT(setLooping(int)));

        textureTypeBox->setCurrentIndex(0);
        psTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ParticleEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ParticleEditorClass)
    {
        ParticleEditorClass->setWindowTitle(QApplication::translate("ParticleEditorClass", "Particle Editor (v. 0.1)", Q_NULLPTR));
        browsepath->setText(QApplication::translate("ParticleEditorClass", "Browse", Q_NULLPTR));
        label_Lifetime->setText(QApplication::translate("ParticleEditorClass", "Lifetime", Q_NULLPTR));
        label_Velocity->setText(QApplication::translate("ParticleEditorClass", "Velocity", Q_NULLPTR));
        label_EmissionDelay->setText(QApplication::translate("ParticleEditorClass", "Emission Delay", Q_NULLPTR));
        label_MaxParticles->setText(QApplication::translate("ParticleEditorClass", "Max Particles", Q_NULLPTR));
        textBrowser->setPlaceholderText(QApplication::translate("ParticleEditorClass", "plasmaball.png", Q_NULLPTR));
        savePS->setText(QApplication::translate("ParticleEditorClass", "Save as...", Q_NULLPTR));
        label_Gravity->setText(QApplication::translate("ParticleEditorClass", "Gravity", Q_NULLPTR));
        label_Texture->setText(QApplication::translate("ParticleEditorClass", "Texture", Q_NULLPTR));
        color0Btn->setText(QApplication::translate("ParticleEditorClass", "Change", Q_NULLPTR));
        color0Display->setText(QApplication::translate("ParticleEditorClass", "Start Color", Q_NULLPTR));
        color0Display->setPlaceholderText(QApplication::translate("ParticleEditorClass", "Color Start", Q_NULLPTR));
        color1Display->setText(QApplication::translate("ParticleEditorClass", "Mid Color", Q_NULLPTR));
        color1Display->setPlaceholderText(QApplication::translate("ParticleEditorClass", "Color End", Q_NULLPTR));
        color1Btn->setText(QApplication::translate("ParticleEditorClass", "Change", Q_NULLPTR));
        label_StartSize->setText(QApplication::translate("ParticleEditorClass", "Start Size", Q_NULLPTR));
        emitterTypeBox->clear();
        emitterTypeBox->insertItems(0, QStringList()
         << QApplication::translate("ParticleEditorClass", "Point", Q_NULLPTR)
         << QApplication::translate("ParticleEditorClass", "Rectangle", Q_NULLPTR)
        );
        emitterTypeBox->setCurrentText(QApplication::translate("ParticleEditorClass", "Point", Q_NULLPTR));
        label_EmitterType->setText(QApplication::translate("ParticleEditorClass", "Emitter Type", Q_NULLPTR));
        velocityX->setInputMask(QApplication::translate("ParticleEditorClass", "##0\\.00", Q_NULLPTR));
        velocityX->setText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        velocityX->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        velocityY->setInputMask(QApplication::translate("ParticleEditorClass", "##0\\.00", Q_NULLPTR));
        velocityY->setText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        velocityY->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        velocityZ->setInputMask(QApplication::translate("ParticleEditorClass", "##0\\.00", Q_NULLPTR));
        velocityZ->setText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        velocityZ->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        gravity->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        gravity->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        gravity->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        lifetime->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        lifetime->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        lifetime->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        label_VelocityY->setText(QApplication::translate("ParticleEditorClass", "Y", Q_NULLPTR));
        startSizeX->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        startSizeX->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        startSizeX->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        startSizeY->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        startSizeY->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        startSizeY->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        maxParticles->setInputMask(QApplication::translate("ParticleEditorClass", "9000", Q_NULLPTR));
        maxParticles->setText(QApplication::translate("ParticleEditorClass", "100", Q_NULLPTR));
        maxParticles->setPlaceholderText(QApplication::translate("ParticleEditorClass", "100", Q_NULLPTR));
        label_SizeY_6->setText(QApplication::translate("ParticleEditorClass", "Rectangle Size", Q_NULLPTR));
        rectSizeX->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        rectSizeX->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        rectSizeX->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        rectSizeZ->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        rectSizeZ->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        rectSizeZ->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        loadPS->setText(QApplication::translate("ParticleEditorClass", "Load", Q_NULLPTR));
        textureTypeBox->clear();
        textureTypeBox->insertItems(0, QStringList()
         << QApplication::translate("ParticleEditorClass", "Single Texture", Q_NULLPTR)
         << QApplication::translate("ParticleEditorClass", "Texture Sheet", Q_NULLPTR)
        );
        textureTypeBox->setCurrentText(QApplication::translate("ParticleEditorClass", "Single Texture", Q_NULLPTR));
        spriteColumns->setInputMask(QApplication::translate("ParticleEditorClass", "90", Q_NULLPTR));
        spriteColumns->setText(QApplication::translate("ParticleEditorClass", "4", Q_NULLPTR));
        spriteColumns->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        spriteRows->setInputMask(QApplication::translate("ParticleEditorClass", "90", Q_NULLPTR));
        spriteRows->setText(QApplication::translate("ParticleEditorClass", "4", Q_NULLPTR));
        spriteRows->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        interpolateFrames->setText(QApplication::translate("ParticleEditorClass", "Frame Interpolation", Q_NULLPTR));
        label_SizeY_7->setText(QApplication::translate("ParticleEditorClass", "Columns / Rows", Q_NULLPTR));
        endSizeY->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        endSizeY->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        endSizeY->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        label_EndSize->setText(QApplication::translate("ParticleEditorClass", "End Size", Q_NULLPTR));
        endSizeX->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        endSizeX->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        endSizeX->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        textureView->setText(QString());
        label_EmDelaySlide->setText(QString());
        psTabs->setTabText(psTabs->indexOf(tab), QApplication::translate("ParticleEditorClass", "Particle System 1", Q_NULLPTR));
        psTabs->setTabText(psTabs->indexOf(tab_2), QApplication::translate("ParticleEditorClass", "Add...", Q_NULLPTR));
        label_VelocityX->setText(QApplication::translate("ParticleEditorClass", "X", Q_NULLPTR));
        label_VelocityZ->setText(QApplication::translate("ParticleEditorClass", "Z", Q_NULLPTR));
        color2Btn->setText(QApplication::translate("ParticleEditorClass", "Change", Q_NULLPTR));
        color2Display->setText(QApplication::translate("ParticleEditorClass", "End Color", Q_NULLPTR));
        color2Display->setPlaceholderText(QApplication::translate("ParticleEditorClass", "Color End", Q_NULLPTR));
        label_EmitterType_2->setText(QApplication::translate("ParticleEditorClass", "Texture Type", Q_NULLPTR));
        rotateParticles->setText(QApplication::translate("ParticleEditorClass", "Rotate Particles", Q_NULLPTR));
        noiseDissolve->setText(QApplication::translate("ParticleEditorClass", "Noise Dissolve", Q_NULLPTR));
        looping->setText(QApplication::translate("ParticleEditorClass", "Looping", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParticleEditorClass: public Ui_ParticleEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICLEEDITOR_H
