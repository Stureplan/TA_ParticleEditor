#include "maincontainer.h"

MainContainer::MainContainer(QWidget* parent)
{
	// Make sure the Main Container takes full focus (keyboard input)
	setFocusPolicy(Qt::StrongFocus);
}

MainContainer::~MainContainer() 
{
	
}

#pragma region POINTERS
void MainContainer::SetPointers(Graphics* gfx, QLabel* particleInfoUI, QPlainTextEdit* lifetimeInputUI, QPlainTextEdit* emissionDelayUI, QPlainTextEdit* velocityXUI, QPlainTextEdit* velocityYUI, QPlainTextEdit* velocityZUI,	QPlainTextEdit* gravityUI, QPushButton* browseUI, QPushButton* saveUI, QPlainTextEdit* maxParticlesUI, QTextBrowser* browseTextBoxUI)
{
	graphics = gfx;
	textFieldParticleInfo = particleInfoUI;
	textFieldLifetime = lifetimeInputUI;
	textFieldEmissionDelay = emissionDelayUI;
	textFieldVelocityX = velocityXUI;
	textFieldVelocityY = velocityYUI;
	textFieldVelocityZ = velocityZUI;
	textFieldGravity = gravityUI;
	browseBtn = browseUI;
	saveBtn = saveUI;
	textFieldMaxParticles = maxParticlesUI;
	textBrowser = browseTextBoxUI;
}
#pragma endregion

void MainContainer::Init()
{
	mTextFieldValue = 0.0f;

	mLifetime = DEFAULT_LIFETIME;
	textFieldLifetime->setPlainText(std::to_string(DEFAULT_LIFETIME).c_str());

	mEmissionDelay = DEFAULT_EMISSIONDELAY;
	textFieldLifetime->setPlainText(std::to_string(DEFAULT_EMISSIONDELAY).c_str());

	mVelocity = DEFAULT_VELOCITY;
	textFieldVelocityX->setPlainText(std::to_string(DEFAULT_VELOCITY.X).c_str());
	textFieldVelocityY->setPlainText(std::to_string(DEFAULT_VELOCITY.Y).c_str());
	textFieldVelocityZ->setPlainText(std::to_string(DEFAULT_VELOCITY.Z).c_str());

	mGravity = DEFAULT_GRAVITY;
	textFieldGravity->setPlainText(std::to_string(DEFAULT_GRAVITY).c_str());

	mMaxParticles = DEFAULT_MAXPARTICLES;
	textFieldMaxParticles->setPlainText(std::to_string(DEFAULT_MAXPARTICLES).c_str());
}

void MainContainer::setGravity()
{
	QString text = textFieldGravity->toPlainText();
	mGravity = ErrorHandleUI(text, textFieldGravity);
}

void MainContainer::save()
{
	savePath = QFileDialog::getSaveFileName(this);
	//graphics->Export(savePath);
}

void MainContainer::browse()
{
	mTexturePath = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png)"));
	textBrowser->setPlainText(mTexturePath);
	//graphics->SetTexturePath(texturePath);
}

void MainContainer::setMaxParticles()
{
	QString text = textFieldMaxParticles->toPlainText();
	bool newline = text.contains("\n");
	if (newline)
	{
		QString oldText = text;
		oldText.remove("\n");
		textFieldMaxParticles->document()->setPlainText(oldText);
	}
	bool ok;
	float t;

	t = text.toInt(&ok);

	if (ok == true)
	{
		if (t > 1000)
		{
			textFieldMaxParticles->document()->setPlainText("999");
			mMaxParticles = 999;
		}
		else
		{
			mMaxParticles = t;
		}
			
	}
	if (ok == false && text != NULL)
	{
		QString oldText = text;
		oldText.chop(1);
		textFieldMaxParticles->document()->setPlainText(oldText);
	}
	if (ok == false)
	{
		mMaxParticles = DEFAULT_MAXPARTICLES;
	}

	//graphics->SetMaxParticles(mMaxParticles);
}

void MainContainer::BuildParticleSystem()
{
	PARTICLESYSTEM ps(mPosition, mMaxParticles,
		mVelocity, mEmissionDelay, mLifetime, mGravity,
		mTexturePath.toStdString());

	graphics->SetParticleSystem(ps);
}


void MainContainer::setVelocityX()
{
	QString text = textFieldVelocityX->toPlainText();
	float x = ErrorHandleUI(text, textFieldVelocityX);

	mVelocity.X = x;
	BuildParticleSystem();
}

void MainContainer::setVelocityY()
{
	QString text = textFieldVelocityY->toPlainText();
	float y = ErrorHandleUI(text, textFieldVelocityY);

	mVelocity.Y = y;
	BuildParticleSystem();

}

void MainContainer::setVelocityZ()
{
	QString text = textFieldVelocityZ->toPlainText();
	float z = ErrorHandleUI(text, textFieldVelocityZ);
	
	mVelocity.Z = z;
	BuildParticleSystem();
}


void MainContainer::setEmissionDelay()
{
	QString text = textFieldEmissionDelay->toPlainText();
	mEmissionDelay = ErrorHandleUI(text, textFieldEmissionDelay);
	BuildParticleSystem();
}

void MainContainer::setLifetime()
{
	QString text = textFieldLifetime->toPlainText();
	mLifetime = ErrorHandleUI(text, textFieldLifetime);
	BuildParticleSystem();
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


	if (key == Qt::Key::Key_1)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->Debug(false);
		}
	}

	if (key == Qt::Key::Key_2)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->Debug(true);
		}
	}


	if (key == Qt::Key::Key_Escape)
	{
		QCoreApplication::quit();
	}

	if (key == Qt::Key::Key_Space)
	{
		graphics->PauseSimulation();
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
				graphics->ParticleInspectionLabel(textFieldParticleInfo);
			}
			else
			{
				textFieldParticleInfo->setText("<no info>");
			}
		}
	}
}
