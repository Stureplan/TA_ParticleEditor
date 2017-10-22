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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include "graphics.h"
#include "maincontainer.h"

QT_BEGIN_NAMESPACE

class Ui_ParticleEditorClass
{
public:
    MainContainer *maincontainer;
    Graphics *graphics;
    QLabel *label;
    QLabel *label_4;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
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
        label = new QLabel(maincontainer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(660, 10, 200, 50));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label_4 = new QLabel(maincontainer);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(660, 50, 200, 50));
        label_4->setFont(font);
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
