#include "maincontainer.h"

MainContainer::MainContainer(QWidget* parent)
{
	// Make sure the Main Container takes full focus (keyboard input)
	setFocusPolicy(Qt::StrongFocus);
	velocity = POSITION(0, 0, 0);
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
	textFieldLifetime = pte;
}

void MainContainer::EmissionDelayInput(QPlainTextEdit* pte)
{
	textFieldEmissionDelay = pte;
}

void MainContainer::VelocityXInput(QPlainTextEdit* pte)
{
	textFieldVelocityX = pte;
}

void MainContainer::VelocityYInput(QPlainTextEdit* pte)
{
	textFieldVelocityY = pte;
}

void MainContainer::VelocityZInput(QPlainTextEdit* pte)
{
	textFieldVelocityZ = pte;
}

void MainContainer::setVelocityX()
{
	QString text = textFieldVelocityX->toPlainText();
	mVelocityX = ErrorHandleUI(text, textFieldVelocityX);

	velocity.X = mVelocityX;
	//graphics->SetVelocity(velocity);
}

void MainContainer::setVelocityY()
{
	QString text = textFieldVelocityY->toPlainText();
	mVelocityY = ErrorHandleUI(text, textFieldVelocityY);

	velocity.Y = mVelocityY;
	//graphics->SetVelocity(velocity);
}

void MainContainer::setVelocityZ()
{
	QString text = textFieldVelocityZ->toPlainText();
	mVelocityZ = ErrorHandleUI(text, textFieldVelocityZ);
	
	velocity.Z = mVelocityZ;
	//graphics->SetVelocity(velocity);
}


void MainContainer::setEmissionDelay()
{
	QString text = textFieldEmissionDelay->toPlainText();
	mEmissionDelay = ErrorHandleUI(text, textFieldEmissionDelay);
}

void MainContainer::setLifetime()
{
	QString text = textFieldLifetime->toPlainText();
	mLifetime = ErrorHandleUI(text, textFieldLifetime);
}

float MainContainer::ErrorHandleUI(QString text, QPlainTextEdit* qpte)
{
	if (text == "-")
	{
		return 0;
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
		qpte->document()->setPlainText(oldText);
	}

	t = text.toFloat(&ok);
	if (ok == true)
	{
		mTextFieldValue = t;
		return mTextFieldValue;
	}

	if (ok == false && text != NULL)
	{
		QString oldText = text;
		oldText.chop(1);
		qpte->document()->setPlainText(oldText);

		/*QMessageBox msgBox;
		msgBox.setWindowTitle("Float ERROR");
		msgBox.setText("Input MUST be float, not character!");
		msgBox.exec();*/
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
