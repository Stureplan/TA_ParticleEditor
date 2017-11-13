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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "graphics.h"
#include "maincontainer.h"

QT_BEGIN_NAMESPACE

class Ui_ParticleEditorClass
{
public:
    MainContainer *maincontainer;
    Graphics *graphics;
    QLabel *label_ParticleInfo;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QPushButton *browsepath;
    QLabel *label_Lifetime;
    QLabel *label_VelocityX;
    QLabel *label_EmissionDelay;
    QLabel *label_MaxParticles;
    QTextBrowser *textBrowser;
    QPushButton *savePS;
    QLabel *label_Gravity;
    QLabel *label_Texture;
    QPushButton *colorInBtn;
    QLineEdit *colorInDisplay;
    QLineEdit *colorOutDisplay;
    QPushButton *colorOutBtn;
    QLabel *label_StartSize;
    QComboBox *emitterTypeBox;
    QLabel *label_EmitterType;
    QLineEdit *velocityX;
    QLineEdit *velocityY;
    QLineEdit *velocityZ;
    QLineEdit *gravity;
    QLineEdit *lifetime;
    QLineEdit *emissionDelay;
    QLabel *label_VelocityY;
    QLabel *label_VelocityZ;
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
    QLineEdit *endSizeY;
    QLabel *label_EndSize;
    QLineEdit *endSizeX;
    QLabel *textureView;
    QSlider *emissionDelaySlider;
    QLabel *label_EmDelaySlide;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ParticleEditorClass)
    {
        if (ParticleEditorClass->objectName().isEmpty())
            ParticleEditorClass->setObjectName(QStringLiteral("ParticleEditorClass"));
        ParticleEditorClass->resize(949, 653);
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
        label_ParticleInfo = new QLabel(maincontainer);
        label_ParticleInfo->setObjectName(QStringLiteral("label_ParticleInfo"));
        label_ParticleInfo->setGeometry(QRect(10, 500, 361, 91));
        QFont font;
        font.setPointSize(12);
        label_ParticleInfo->setFont(font);
        label_ParticleInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        line = new QFrame(maincontainer);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(650, 10, 3, 480));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(maincontainer);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(9, 10, 3, 480));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(maincontainer);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 490, 640, 3));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(maincontainer);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(9, 9, 642, 3));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        browsepath = new QPushButton(maincontainer);
        browsepath->setObjectName(QStringLiteral("browsepath"));
        browsepath->setGeometry(QRect(670, 439, 91, 25));
        label_Lifetime = new QLabel(maincontainer);
        label_Lifetime->setObjectName(QStringLiteral("label_Lifetime"));
        label_Lifetime->setGeometry(QRect(780, 138, 51, 20));
        label_Lifetime->setAlignment(Qt::AlignCenter);
        label_VelocityX = new QLabel(maincontainer);
        label_VelocityX->setObjectName(QStringLiteral("label_VelocityX"));
        label_VelocityX->setGeometry(QRect(680, 87, 71, 20));
        label_VelocityX->setAlignment(Qt::AlignCenter);
        label_EmissionDelay = new QLabel(maincontainer);
        label_EmissionDelay->setObjectName(QStringLiteral("label_EmissionDelay"));
        label_EmissionDelay->setGeometry(QRect(854, 138, 80, 20));
        label_EmissionDelay->setAlignment(Qt::AlignCenter);
        label_MaxParticles = new QLabel(maincontainer);
        label_MaxParticles->setObjectName(QStringLiteral("label_MaxParticles"));
        label_MaxParticles->setGeometry(QRect(860, 191, 70, 16));
        label_MaxParticles->setAlignment(Qt::AlignCenter);
        textBrowser = new QTextBrowser(maincontainer);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(770, 440, 171, 23));
        textBrowser->setTextInteractionFlags(Qt::NoTextInteraction);
        savePS = new QPushButton(maincontainer);
        savePS->setObjectName(QStringLiteral("savePS"));
        savePS->setGeometry(QRect(830, 550, 111, 41));
        label_Gravity = new QLabel(maincontainer);
        label_Gravity->setObjectName(QStringLiteral("label_Gravity"));
        label_Gravity->setGeometry(QRect(689, 138, 51, 20));
        label_Gravity->setAlignment(Qt::AlignCenter);
        label_Texture = new QLabel(maincontainer);
        label_Texture->setObjectName(QStringLiteral("label_Texture"));
        label_Texture->setGeometry(QRect(680, 420, 91, 16));
        colorInBtn = new QPushButton(maincontainer);
        colorInBtn->setObjectName(QStringLiteral("colorInBtn"));
        colorInBtn->setGeometry(QRect(660, 10, 70, 30));
        colorInDisplay = new QLineEdit(maincontainer);
        colorInDisplay->setObjectName(QStringLiteral("colorInDisplay"));
        colorInDisplay->setGeometry(QRect(729, 10, 211, 30));
        QFont font1;
        font1.setKerning(true);
        colorInDisplay->setFont(font1);
        colorInDisplay->setCursor(QCursor(Qt::IBeamCursor));
        colorInDisplay->setFocusPolicy(Qt::NoFocus);
        colorInDisplay->setContextMenuPolicy(Qt::NoContextMenu);
        colorInDisplay->setFrame(false);
        colorInDisplay->setAlignment(Qt::AlignCenter);
        colorInDisplay->setReadOnly(true);
        colorOutDisplay = new QLineEdit(maincontainer);
        colorOutDisplay->setObjectName(QStringLiteral("colorOutDisplay"));
        colorOutDisplay->setGeometry(QRect(730, 50, 211, 30));
        colorOutDisplay->setFont(font1);
        colorOutDisplay->setCursor(QCursor(Qt::IBeamCursor));
        colorOutDisplay->setMouseTracking(false);
        colorOutDisplay->setFocusPolicy(Qt::NoFocus);
        colorOutDisplay->setContextMenuPolicy(Qt::NoContextMenu);
        colorOutDisplay->setFrame(false);
        colorOutDisplay->setAlignment(Qt::AlignCenter);
        colorOutDisplay->setReadOnly(true);
        colorOutDisplay->setClearButtonEnabled(false);
        colorOutBtn = new QPushButton(maincontainer);
        colorOutBtn->setObjectName(QStringLiteral("colorOutBtn"));
        colorOutBtn->setGeometry(QRect(660, 50, 70, 30));
        label_StartSize = new QLabel(maincontainer);
        label_StartSize->setObjectName(QStringLiteral("label_StartSize"));
        label_StartSize->setGeometry(QRect(661, 191, 91, 16));
        label_StartSize->setAlignment(Qt::AlignCenter);
        emitterTypeBox = new QComboBox(maincontainer);
        emitterTypeBox->setObjectName(QStringLiteral("emitterTypeBox"));
        emitterTypeBox->setGeometry(QRect(820, 260, 121, 24));
        emitterTypeBox->setLayoutDirection(Qt::LeftToRight);
        label_EmitterType = new QLabel(maincontainer);
        label_EmitterType->setObjectName(QStringLiteral("label_EmitterType"));
        label_EmitterType->setGeometry(QRect(830, 240, 100, 16));
        label_EmitterType->setAlignment(Qt::AlignCenter);
        velocityX = new QLineEdit(maincontainer);
        velocityX->setObjectName(QStringLiteral("velocityX"));
        velocityX->setGeometry(QRect(670, 110, 90, 20));
        velocityX->setAlignment(Qt::AlignCenter);
        velocityY = new QLineEdit(maincontainer);
        velocityY->setObjectName(QStringLiteral("velocityY"));
        velocityY->setGeometry(QRect(760, 110, 90, 20));
        velocityY->setAlignment(Qt::AlignCenter);
        velocityZ = new QLineEdit(maincontainer);
        velocityZ->setObjectName(QStringLiteral("velocityZ"));
        velocityZ->setGeometry(QRect(850, 110, 90, 20));
        velocityZ->setAlignment(Qt::AlignCenter);
        gravity = new QLineEdit(maincontainer);
        gravity->setObjectName(QStringLiteral("gravity"));
        gravity->setGeometry(QRect(670, 160, 90, 20));
        gravity->setAlignment(Qt::AlignCenter);
        lifetime = new QLineEdit(maincontainer);
        lifetime->setObjectName(QStringLiteral("lifetime"));
        lifetime->setGeometry(QRect(760, 160, 90, 20));
        lifetime->setAlignment(Qt::AlignCenter);
        emissionDelay = new QLineEdit(maincontainer);
        emissionDelay->setObjectName(QStringLiteral("emissionDelay"));
        emissionDelay->setGeometry(QRect(850, 160, 90, 20));
        emissionDelay->setAlignment(Qt::AlignCenter);
        label_VelocityY = new QLabel(maincontainer);
        label_VelocityY->setObjectName(QStringLiteral("label_VelocityY"));
        label_VelocityY->setGeometry(QRect(770, 87, 71, 20));
        label_VelocityY->setLayoutDirection(Qt::LeftToRight);
        label_VelocityY->setAlignment(Qt::AlignCenter);
        label_VelocityZ = new QLabel(maincontainer);
        label_VelocityZ->setObjectName(QStringLiteral("label_VelocityZ"));
        label_VelocityZ->setGeometry(QRect(859, 87, 71, 20));
        label_VelocityZ->setLayoutDirection(Qt::LeftToRight);
        label_VelocityZ->setAlignment(Qt::AlignCenter);
        startSizeX = new QLineEdit(maincontainer);
        startSizeX->setObjectName(QStringLiteral("startSizeX"));
        startSizeX->setGeometry(QRect(670, 210, 35, 20));
        startSizeX->setAlignment(Qt::AlignCenter);
        startSizeY = new QLineEdit(maincontainer);
        startSizeY->setObjectName(QStringLiteral("startSizeY"));
        startSizeY->setGeometry(QRect(707, 210, 35, 20));
        startSizeY->setAlignment(Qt::AlignCenter);
        maxParticles = new QLineEdit(maincontainer);
        maxParticles->setObjectName(QStringLiteral("maxParticles"));
        maxParticles->setGeometry(QRect(870, 210, 45, 20));
        maxParticles->setAlignment(Qt::AlignCenter);
        rectangleWidget = new QWidget(maincontainer);
        rectangleWidget->setObjectName(QStringLiteral("rectangleWidget"));
        rectangleWidget->setEnabled(false);
        rectangleWidget->setGeometry(QRect(820, 300, 120, 110));
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
        loadPS->setGeometry(QRect(711, 550, 111, 41));
        textureTypeBox = new QComboBox(maincontainer);
        textureTypeBox->setObjectName(QStringLiteral("textureTypeBox"));
        textureTypeBox->setGeometry(QRect(670, 467, 91, 24));
        textureTypeBox->setLayoutDirection(Qt::LeftToRight);
        spriteSheetWidget = new QWidget(maincontainer);
        spriteSheetWidget->setObjectName(QStringLiteral("spriteSheetWidget"));
        spriteSheetWidget->setEnabled(false);
        spriteSheetWidget->setGeometry(QRect(770, 467, 81, 24));
        spriteColumns = new QLineEdit(spriteSheetWidget);
        spriteColumns->setObjectName(QStringLiteral("spriteColumns"));
        spriteColumns->setGeometry(QRect(0, 0, 41, 24));
        spriteColumns->setAlignment(Qt::AlignCenter);
        spriteRows = new QLineEdit(spriteSheetWidget);
        spriteRows->setObjectName(QStringLiteral("spriteRows"));
        spriteRows->setGeometry(QRect(40, 0, 41, 24));
        spriteRows->setAlignment(Qt::AlignCenter);
        endSizeY = new QLineEdit(maincontainer);
        endSizeY->setObjectName(QStringLiteral("endSizeY"));
        endSizeY->setGeometry(QRect(787, 210, 35, 20));
        endSizeY->setAlignment(Qt::AlignCenter);
        label_EndSize = new QLabel(maincontainer);
        label_EndSize->setObjectName(QStringLiteral("label_EndSize"));
        label_EndSize->setGeometry(QRect(741, 191, 91, 16));
        label_EndSize->setAlignment(Qt::AlignCenter);
        endSizeX = new QLineEdit(maincontainer);
        endSizeX->setObjectName(QStringLiteral("endSizeX"));
        endSizeX->setGeometry(QRect(750, 210, 35, 20));
        endSizeX->setAlignment(Qt::AlignCenter);
        textureView = new QLabel(maincontainer);
        textureView->setObjectName(QStringLiteral("textureView"));
        textureView->setGeometry(QRect(870, 470, 64, 64));
        textureView->setScaledContents(true);
        emissionDelaySlider = new QSlider(maincontainer);
        emissionDelaySlider->setObjectName(QStringLiteral("emissionDelaySlider"));
        emissionDelaySlider->setGeometry(QRect(500, 530, 91, 22));
        emissionDelaySlider->setMinimum(1);
        emissionDelaySlider->setMaximum(100);
        emissionDelaySlider->setOrientation(Qt::Horizontal);
        label_EmDelaySlide = new QLabel(maincontainer);
        label_EmDelaySlide->setObjectName(QStringLiteral("label_EmDelaySlide"));
        label_EmDelaySlide->setGeometry(QRect(520, 510, 47, 13));
        ParticleEditorClass->setCentralWidget(maincontainer);
        menuBar = new QMenuBar(ParticleEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 949, 21));
        ParticleEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ParticleEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ParticleEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ParticleEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ParticleEditorClass->setStatusBar(statusBar);

        retranslateUi(ParticleEditorClass);
        QObject::connect(browsepath, SIGNAL(clicked()), maincontainer, SLOT(browse()));
        QObject::connect(savePS, SIGNAL(clicked()), maincontainer, SLOT(save()));
        QObject::connect(colorInBtn, SIGNAL(clicked()), maincontainer, SLOT(colorIn()));
        QObject::connect(colorOutBtn, SIGNAL(clicked()), maincontainer, SLOT(colorOut()));
        QObject::connect(velocityX, SIGNAL(editingFinished()), maincontainer, SLOT(setVelocityX()));
        QObject::connect(velocityY, SIGNAL(editingFinished()), maincontainer, SLOT(setVelocityY()));
        QObject::connect(velocityZ, SIGNAL(editingFinished()), maincontainer, SLOT(setVelocityZ()));
        QObject::connect(gravity, SIGNAL(editingFinished()), maincontainer, SLOT(setGravity()));
        QObject::connect(lifetime, SIGNAL(editingFinished()), maincontainer, SLOT(setLifetime()));
        QObject::connect(emissionDelay, SIGNAL(editingFinished()), maincontainer, SLOT(setEmissionDelay()));
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
        QObject::connect(emissionDelaySlider, SIGNAL(valueChanged(int)), maincontainer, SLOT(emissionDelaySlide(int)));

        QMetaObject::connectSlotsByName(ParticleEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ParticleEditorClass)
    {
        ParticleEditorClass->setWindowTitle(QApplication::translate("ParticleEditorClass", "Particle Editor (v. 0.1)", Q_NULLPTR));
        label_ParticleInfo->setText(QApplication::translate("ParticleEditorClass", "<no info>", Q_NULLPTR));
        browsepath->setText(QApplication::translate("ParticleEditorClass", "Browse", Q_NULLPTR));
        label_Lifetime->setText(QApplication::translate("ParticleEditorClass", "Lifetime", Q_NULLPTR));
        label_VelocityX->setText(QApplication::translate("ParticleEditorClass", "Velocity X", Q_NULLPTR));
        label_EmissionDelay->setText(QApplication::translate("ParticleEditorClass", "Emission Delay", Q_NULLPTR));
        label_MaxParticles->setText(QApplication::translate("ParticleEditorClass", "Max Particles", Q_NULLPTR));
        textBrowser->setPlaceholderText(QApplication::translate("ParticleEditorClass", "plasmaball.png", Q_NULLPTR));
        savePS->setText(QApplication::translate("ParticleEditorClass", "Save as...", Q_NULLPTR));
        label_Gravity->setText(QApplication::translate("ParticleEditorClass", "Gravity", Q_NULLPTR));
        label_Texture->setText(QApplication::translate("ParticleEditorClass", "Texture", Q_NULLPTR));
        colorInBtn->setText(QApplication::translate("ParticleEditorClass", "Change", Q_NULLPTR));
        colorInDisplay->setText(QApplication::translate("ParticleEditorClass", "Start Color", Q_NULLPTR));
        colorInDisplay->setPlaceholderText(QApplication::translate("ParticleEditorClass", "Color Start", Q_NULLPTR));
        colorOutDisplay->setText(QApplication::translate("ParticleEditorClass", "End Color", Q_NULLPTR));
        colorOutDisplay->setPlaceholderText(QApplication::translate("ParticleEditorClass", "Color End", Q_NULLPTR));
        colorOutBtn->setText(QApplication::translate("ParticleEditorClass", "Change", Q_NULLPTR));
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
        emissionDelay->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        emissionDelay->setText(QApplication::translate("ParticleEditorClass", "0.1", Q_NULLPTR));
        emissionDelay->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        label_VelocityY->setText(QApplication::translate("ParticleEditorClass", "Velocity Y", Q_NULLPTR));
        label_VelocityZ->setText(QApplication::translate("ParticleEditorClass", "Velocity Z", Q_NULLPTR));
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
         << QApplication::translate("ParticleEditorClass", "Single Sprite", Q_NULLPTR)
         << QApplication::translate("ParticleEditorClass", "Sprite Sheet", Q_NULLPTR)
        );
        textureTypeBox->setCurrentText(QApplication::translate("ParticleEditorClass", "Single Sprite", Q_NULLPTR));
        spriteColumns->setInputMask(QApplication::translate("ParticleEditorClass", "90", Q_NULLPTR));
        spriteColumns->setText(QApplication::translate("ParticleEditorClass", "4", Q_NULLPTR));
        spriteColumns->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        spriteRows->setInputMask(QApplication::translate("ParticleEditorClass", "90", Q_NULLPTR));
        spriteRows->setText(QApplication::translate("ParticleEditorClass", "4", Q_NULLPTR));
        spriteRows->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0.0", Q_NULLPTR));
        endSizeY->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        endSizeY->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        endSizeY->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        label_EndSize->setText(QApplication::translate("ParticleEditorClass", "End Size", Q_NULLPTR));
        endSizeX->setInputMask(QApplication::translate("ParticleEditorClass", "#0\\.00", Q_NULLPTR));
        endSizeX->setText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        endSizeX->setPlaceholderText(QApplication::translate("ParticleEditorClass", "1.0", Q_NULLPTR));
        textureView->setText(QString());
        label_EmDelaySlide->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ParticleEditorClass: public Ui_ParticleEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICLEEDITOR_H
