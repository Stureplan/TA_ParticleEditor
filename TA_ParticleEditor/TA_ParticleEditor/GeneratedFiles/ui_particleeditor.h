/********************************************************************************
** Form generated from reading UI file 'particleeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICLEEDITOR_H
#define UI_PARTICLEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "graphics.h"

QT_BEGIN_NAMESPACE

class Ui_ParticleEditorClass
{
public:
    QWidget *mainContainer;
    Graphics *graphics;
    QLabel *label;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ParticleEditorClass)
    {
        if (ParticleEditorClass->objectName().isEmpty())
            ParticleEditorClass->setObjectName(QStringLiteral("ParticleEditorClass"));
        ParticleEditorClass->resize(949, 653);
        mainContainer = new QWidget(ParticleEditorClass);
        mainContainer->setObjectName(QStringLiteral("mainContainer"));
        graphics = new Graphics(mainContainer);
        graphics->setObjectName(QStringLiteral("graphics"));
        graphics->setGeometry(QRect(9, 9, 640, 480));
        label = new QLabel(mainContainer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(660, 10, 200, 50));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label_4 = new QLabel(mainContainer);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(660, 50, 200, 50));
        label_4->setFont(font);
        ParticleEditorClass->setCentralWidget(mainContainer);
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

        QMetaObject::connectSlotsByName(ParticleEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ParticleEditorClass)
    {
        ParticleEditorClass->setWindowTitle(QApplication::translate("ParticleEditorClass", "ParticleEditor", Q_NULLPTR));
        label->setText(QApplication::translate("ParticleEditorClass", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("ParticleEditorClass", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParticleEditorClass: public Ui_ParticleEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICLEEDITOR_H
