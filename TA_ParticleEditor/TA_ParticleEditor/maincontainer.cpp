#include "maincontainer.h"

MainContainer::MainContainer(QWidget* parent)
{
	// Make sure the Main Container takes full focus (keyboard input)
	setFocusPolicy(Qt::StrongFocus);
	velocity = POSITION(0, 0, 0);
	Init();
	
}

MainContainer::~MainContainer() 
{
	
}

void MainContainer::Init()
{
	mTextFieldValue = 0.0f;
	mLifetime = 0.0f;
	mEmissionDelay = 0.0f;
	mGravity = 0.0f;
	mMaxParticles = DEFAULT_MAXPARTICLES;
}

void MainContainer::GraphicsWindow(Graphics* gfx)
{
	graphics = gfx;
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

void MainContainer::MaxParticlesInput(QPlainTextEdit* pte)
{
	textFieldMaxParticles = pte;
}

void MainContainer::BrowseInput(QPushButton* pbtn)
{
	browseBtn = pbtn;
}

void MainContainer::BrowseTextBox(QTextBrowser* qtb)
{
	textBrowser = qtb;
}

void MainContainer::SaveInput(QPushButton* pbtn)
{
	saveBtn = pbtn;
}

void MainContainer::GravityInput(QPlainTextEdit* pte)
{
	textFieldGravity = pte;
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
	texturePath = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png)"));
	textBrowser->setPlainText(texturePath);
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
	//graphics->setEmissionDelay(mEmissionDelay);
}

void MainContainer::setLifetime()
{
	QString text = textFieldLifetime->toPlainText();
	mLifetime = ErrorHandleUI(text, textFieldLifetime);
	//graphics->SetLifetime(mLifetime);
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
				graphics->ParticleInspectionLabel(labelInfo);
			}
			else
			{
				labelInfo->setText("<no info>");
			}
		}
	}
}
