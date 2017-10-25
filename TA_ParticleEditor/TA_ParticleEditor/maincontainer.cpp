﻿#include "maincontainer.h"

MainContainer::MainContainer(QWidget* parent)
{
	// Make sure the Main Container takes full focus (keyboard input)
	setFocusPolicy(Qt::StrongFocus);
}

MainContainer::~MainContainer() 
{
	
}

void MainContainer::GraphicsWindow(Graphics* gfx)
{
	graphics = gfx;
}

void MainContainer::ParticleIDLabel(QLabel* lbl)
{
	labelID = lbl;
}

void MainContainer::ParticleInfoLabel(QLabel* lbl)
{
	labelInfo = lbl;
}

void MainContainer::LifetimeInput(QPlainTextEdit* pte)
{
	textField = pte;
}

void MainContainer::setLifetime()
{
	QString text = textField->toPlainText();


	if (text == "-")
	{
		return;
	}

	bool ok;
	float t;

	bool newline = text.contains("\n");
	if (newline)
	{
		QString oldText = text;
		oldText.remove("\n");

		// check if has focus or not
		//textField->hasFocus()
		textField->document()->setPlainText(oldText);
	}

	t = text.toFloat(&ok);
	if (ok == true)
	{
		mLifetime = t; 
		int a = 0;
	}
	
	if(ok == false && text != NULL)
	{
		QString oldText = text;
		oldText.chop(1);
		textField->document()->setPlainText(oldText);

		QMessageBox msgBox;
		msgBox.setWindowTitle("Float ERROR");
		msgBox.setText("Input MUST be float, not character!");
		msgBox.exec();
	}
}

void MainContainer::keyPressEvent(QKeyEvent* evt)
{
	Qt::Key key = (Qt::Key)evt->key();



	if (key == Qt::Key::Key_Tab)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->Debug();
		}
	}
	if (key == Qt::Key::Key_Escape)
	{
		QCoreApplication::quit();
	}
	
	if (key == Qt::Key::Key_W || key == Qt::Key::Key_A || key == Qt::Key::Key_S || key == Qt::Key::Key_D)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->SetLastCameraMovement(key, false);
		}
	}
}

void MainContainer::keyReleaseEvent(QKeyEvent* evt)
{
	Qt::Key key = (Qt::Key)evt->key();

	if (key == Qt::Key::Key_W || key == Qt::Key::Key_A || key == Qt::Key::Key_S || key == Qt::Key::Key_D)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->SetLastCameraMovement(key, true);
		}

	}
}

void MainContainer::mousePressEvent(QMouseEvent* evt)
{
	if (evt->button() == Qt::MouseButton::LeftButton)
	{
		QPoint pt = evt->pos();
		// check if inside window to begin with
		if (graphics->rect().contains(pt))
		{
			XMFLOAT3 pos = XMFLOAT3(-999,-999,-999);
			int hitParticle = graphics->TestIntersection(pt.x(), pt.y(), pos);

			if (hitParticle > -1)
			{
				graphics->ParticleInspectionLabel(labelInfo);
			}
			else
			{
				labelID->setText("No particle selected");
				labelInfo->setText("<no info>");
			}
		}
	}
}
