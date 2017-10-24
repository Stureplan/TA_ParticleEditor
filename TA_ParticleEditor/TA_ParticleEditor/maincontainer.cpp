#include "maincontainer.h"

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
	//QString str = "hello";
	//pte->setPlaceholderText(str);
	//connect(pte, 
}
//void MainContainer::SetVelocity()
//{
//	XMFLOAT3(0, 0, 0);
//
//	//set velocity
//}

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
				//QLabel* label = new	QLabel(this);
				//label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
				labelID->setText(QString(std::string("Particle: " + std::to_string(hitParticle)).c_str()));
				
				QString sPosX; sPosX = sPosX.setNum(pos.x, 'f', 2);
				QString sPosY; sPosY = sPosY.setNum(pos.y, 'f', 2);
				QString sPosZ; sPosZ = sPosZ.setNum(pos.z, 'f', 2);

				QString	sPos = QString("X: %1 Y: %2 Z: %3").arg(sPosX, sPosY, sPosZ);
				labelInfo->setText(sPos);
				//label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
				//label->setGeometry(10,10, 30, 80);
			}
			else
			{
				labelID->setText("No particle selected");
				labelInfo->setText("<no info>");
			}
		}
	}
}
