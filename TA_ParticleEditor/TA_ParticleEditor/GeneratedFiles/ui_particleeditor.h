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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
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
    QPlainTextEdit *lifetime;
    QLabel *label_Lifetime;
    QPlainTextEdit *emissionDelay;
    QPlainTextEdit *maxParticles;
    QPlainTextEdit *velocityX;
    QPlainTextEdit *velocityY;
    QPlainTextEdit *velocityZ;
    QLabel *label_Velocity;
    QLabel *label_EmissionDelay;
    QLabel *label_MaxParticles;
    QTextBrowser *textBrowser;
    QProgressBar *progressBar;
    QPushButton *savePS;
    QPlainTextEdit *gravity;
    QLabel *label_Gravity;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ParticleEditorClass)
    {
        if (ParticleEditorClass->objectName().isEmpty())
            ParticleEditorClass->setObjectName(QStringLiteral("ParticleEditorClass"));
        ParticleEditorClass->resize(949, 653);
        maincontainer = new MainContainer(ParticleEditorClass);
        maincontainer->setObjectName(QStringLiteral("maincontainer"));
        graphics = new Graphics(maincontainer);
        graphics->setObjectName(QStringLiteral("graphics"));
        graphics->setGeometry(QRect(9, 9, 640, 480));
        label_ParticleInfo = new QLabel(maincontainer);
        label_ParticleInfo->setObjectName(QStringLiteral("label_ParticleInfo"));
        label_ParticleInfo->setGeometry(QRect(660, 10, 200, 171));
        QFont font;
        font.setPointSize(12);
        label_ParticleInfo->setFont(font);
        label_ParticleInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        line = new QFrame(maincontainer);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(649, 10, 3, 480));
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
        browsepath->setGeometry(QRect(670, 470, 75, 31));
        lifetime = new QPlainTextEdit(maincontainer);
        lifetime->setObjectName(QStringLiteral("lifetime"));
        lifetime->setGeometry(QRect(670, 260, 64, 24));
        label_Lifetime = new QLabel(maincontainer);
        label_Lifetime->setObjectName(QStringLiteral("label_Lifetime"));
        label_Lifetime->setGeometry(QRect(680, 240, 51, 20));
        emissionDelay = new QPlainTextEdit(maincontainer);
        emissionDelay->setObjectName(QStringLiteral("emissionDelay"));
        emissionDelay->setGeometry(QRect(670, 320, 64, 24));
        maxParticles = new QPlainTextEdit(maincontainer);
        maxParticles->setObjectName(QStringLiteral("maxParticles"));
        maxParticles->setGeometry(QRect(670, 380, 64, 24));
        velocityX = new QPlainTextEdit(maincontainer);
        velocityX->setObjectName(QStringLiteral("velocityX"));
        velocityX->setGeometry(QRect(670, 140, 64, 24));
        velocityY = new QPlainTextEdit(maincontainer);
        velocityY->setObjectName(QStringLiteral("velocityY"));
        velocityY->setGeometry(QRect(750, 140, 64, 24));
        velocityZ = new QPlainTextEdit(maincontainer);
        velocityZ->setObjectName(QStringLiteral("velocityZ"));
        velocityZ->setGeometry(QRect(830, 140, 64, 24));
        label_Velocity = new QLabel(maincontainer);
        label_Velocity->setObjectName(QStringLiteral("label_Velocity"));
        label_Velocity->setGeometry(QRect(680, 110, 71, 31));
        label_EmissionDelay = new QLabel(maincontainer);
        label_EmissionDelay->setObjectName(QStringLiteral("label_EmissionDelay"));
        label_EmissionDelay->setGeometry(QRect(670, 300, 121, 16));
        label_MaxParticles = new QLabel(maincontainer);
        label_MaxParticles->setObjectName(QStringLiteral("label_MaxParticles"));
        label_MaxParticles->setGeometry(QRect(670, 360, 91, 16));
        textBrowser = new QTextBrowser(maincontainer);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(750, 470, 191, 41));
        progressBar = new QProgressBar(maincontainer);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 490, 641, 21));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        savePS = new QPushButton(maincontainer);
        savePS->setObjectName(QStringLiteral("savePS"));
        savePS->setGeometry(QRect(780, 540, 111, 41));
        gravity = new QPlainTextEdit(maincontainer);
        gravity->setObjectName(QStringLiteral("gravity"));
        gravity->setGeometry(QRect(670, 200, 64, 24));
        label_Gravity = new QLabel(maincontainer);
        label_Gravity->setObjectName(QStringLiteral("label_Gravity"));
        label_Gravity->setGeometry(QRect(680, 180, 51, 20));
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
        QObject::connect(lifetime, SIGNAL(textChanged()), maincontainer, SLOT(setLifetime()));
        QObject::connect(emissionDelay, SIGNAL(textChanged()), maincontainer, SLOT(setEmissionDelay()));
        QObject::connect(velocityX, SIGNAL(textChanged()), maincontainer, SLOT(setVelocityX()));
        QObject::connect(velocityY, SIGNAL(textChanged()), maincontainer, SLOT(setVelocityY()));
        QObject::connect(velocityZ, SIGNAL(textChanged()), maincontainer, SLOT(setVelocityZ()));
        QObject::connect(maxParticles, SIGNAL(textChanged()), maincontainer, SLOT(setMaxParticles()));
        QObject::connect(browsepath, SIGNAL(clicked()), maincontainer, SLOT(browse()));
        QObject::connect(savePS, SIGNAL(clicked()), maincontainer, SLOT(save()));
        QObject::connect(gravity, SIGNAL(textChanged()), maincontainer, SLOT(setGravity()));

        QMetaObject::connectSlotsByName(ParticleEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ParticleEditorClass)
    {
        ParticleEditorClass->setWindowTitle(QApplication::translate("ParticleEditorClass", "ParticleEditor", Q_NULLPTR));
        label_ParticleInfo->setText(QApplication::translate("ParticleEditorClass", "<no info>", Q_NULLPTR));
        browsepath->setText(QApplication::translate("ParticleEditorClass", "Browse", Q_NULLPTR));
        lifetime->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0", Q_NULLPTR));
        label_Lifetime->setText(QApplication::translate("ParticleEditorClass", "Lifetime", Q_NULLPTR));
        emissionDelay->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0", Q_NULLPTR));
        maxParticles->setPlaceholderText(QString());
        velocityX->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0", Q_NULLPTR));
        velocityY->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0", Q_NULLPTR));
        velocityZ->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0", Q_NULLPTR));
        label_Velocity->setText(QApplication::translate("ParticleEditorClass", "Velocity", Q_NULLPTR));
        label_EmissionDelay->setText(QApplication::translate("ParticleEditorClass", "Emission Delay", Q_NULLPTR));
        label_MaxParticles->setText(QApplication::translate("ParticleEditorClass", "Max Particles", Q_NULLPTR));
        savePS->setText(QApplication::translate("ParticleEditorClass", "Save as...", Q_NULLPTR));
        gravity->setPlaceholderText(QApplication::translate("ParticleEditorClass", "0", Q_NULLPTR));
        label_Gravity->setText(QApplication::translate("ParticleEditorClass", "Gravity", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParticleEditorClass: public Ui_ParticleEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICLEEDITOR_H
