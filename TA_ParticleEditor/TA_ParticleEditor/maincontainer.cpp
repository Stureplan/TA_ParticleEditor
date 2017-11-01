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
void MainContainer::SetPointers(Graphics* gfx, ParticleSystem* ps, QLabel* particleInfoUI, QLineEdit* lifetimeInputUI, QLineEdit* emissionDelayUI, QLineEdit* velocityXUI, QLineEdit* velocityYUI, QLineEdit* velocityZUI, QLineEdit* gravityUI, QPushButton* browseUI, QPushButton* saveUI, QLineEdit* maxParticlesUI, QTextBrowser* browseTextBoxUI, QLineEdit* colorInDisplayUI, QLineEdit* colorOutDisplayUI, QComboBox* scaleUI, QLineEdit* sizeXUI, QLineEdit* sizeYUI)
{
	graphics = gfx;
	particlesystem = ps;
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
	colorInDisplay = colorInDisplayUI;
	colorOutDisplay = colorOutDisplayUI;
	scaleBoxDisplay = scaleUI;
	textFieldSizeX = sizeXUI;
	textFieldSizeY = sizeYUI;
}
#pragma endregion

void MainContainer::Init()
{
	mEmitterType = EMITTER_TYPE::EMIT_POINT;
	mPosition = FLOAT3(0, 0, 0);


	mTextFieldValue = 0.0f;

	mLifetime = DEFAULT_LIFETIME;
	textFieldLifetime->setPlaceholderText(std::to_string(DEFAULT_LIFETIME).c_str());

	mEmissionDelay = DEFAULT_EMISSIONDELAY;
	textFieldEmissionDelay->setPlaceholderText(std::to_string(DEFAULT_EMISSIONDELAY).c_str());

	mVelocity = DEFAULT_VELOCITY;
	textFieldVelocityX->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.X).c_str());
	textFieldVelocityY->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.Y).c_str());
	textFieldVelocityZ->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.Z).c_str());

	mGravity = DEFAULT_GRAVITY;
	textFieldGravity->setPlaceholderText(std::to_string(DEFAULT_GRAVITY).c_str());

	mMaxParticles = DEFAULT_MAXPARTICLES;
	textFieldMaxParticles->setPlaceholderText(std::to_string(DEFAULT_MAXPARTICLES).c_str());

	mSizeX = DEFAULT_SIZE;
	mSizeY = DEFAULT_SIZE;
	textFieldSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());

	mTexturePath = DEFAULT_TEXTURE;

	mColorIn  = Qt::white;
	mColorOut = Qt::white;
}

void MainContainer::setGravity()
{
	mGravity = textFieldGravity->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_GRAVITY, &mGravity);
}

void MainContainer::save()
{
	std::string exportPath = QFileDialog::getSaveFileName(this).toStdString();
	exportPath.append(".ps");
	//std::string exportPath = PathFindFileNameA(savePath.toStdString().c_str());
	
	PARTICLESYSTEM ps;
	ps.emittertype = mEmitterType;
	ps.position = mPosition;
	ps.maxparticles = mMaxParticles;
	ps.velocity = mVelocity;
	ps.emissiondelay = mEmissionDelay;
	ps.lifetime = mLifetime;
	ps.gravity = mGravity;
	ps.colorIn  = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	ps.colorOut = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	ps.sizeX = mSizeX;
	ps.sizeY = mSizeY;


	FILE* file = fopen(exportPath.c_str(), "wb");
	if (file != NULL)
	{
		std::string texpath = mTexturePath.toStdString();
		const char* tex = texpath.c_str();

		unsigned int texturenamesize = strlen(tex);
		
		// First just write the size of the texture filename (imagine this is a header)
		fwrite(&texturenamesize, sizeof(unsigned int), 1, file);

		// ...then write the texture name
		fwrite(tex, sizeof(const char), texturenamesize, file);

		// ...then we write the particle system details
		fwrite(&ps, sizeof(PARTICLESYSTEM), 1, file);
		int result = fclose(file);

		if (result == 0)
		{
			QMessageBox msg;
			msg.setWindowTitle("File Exported");
			msg.setText(QString("File: " + QString(exportPath.c_str()) + " was successfully exported."));
			msg.exec();
		}
		else
		{
			QMessageBox msg;
			msg.setWindowTitle("File Export Failed");
			msg.setText(QString("File: " + QString(exportPath.c_str()) + " failed on export."));
			msg.exec();
		}
	}





	//graphics->Export(savePath);
}

void MainContainer::colorIn()
{
	QColor c = QColorDialog::getColor(mColorIn, this, "Choose In Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid())
	{
		mColorIn = c;
		colorInDisplay->setStyleSheet("QLineEdit { background: "+ mColorIn.name()+"; selection-background-color: rgb(233, 99, 0); }");
		
		FLOAT4 color = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
		particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_IN, &color);
	}
}

void MainContainer::colorOut()
{
	QColor c = QColorDialog::getColor(mColorOut, this, "Choose In Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid())
	{
		mColorOut = c;
		colorOutDisplay->setStyleSheet("QLineEdit { background: " + mColorOut.name() + "; selection-background-color: rgb(233, 99, 0); }");

		FLOAT4 color = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
		particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_OUT, &color);
	}
}

void MainContainer::scaleModeChanged(int mode)
{
	graphics->ChangeScaleMode(mode);
}

void MainContainer::emitterTypeChanged(int mode)
{
	mEmitterType = (EMITTER_TYPE)mode;
	
	BuildParticleSystem();
}

void MainContainer::sizeX()
{
	mSizeX = textFieldSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_SIZE_X, &mSizeX);
	graphics->ChangeSize(mSizeX, mSizeY);
}

void MainContainer::sizeY()
{
	mSizeY = textFieldSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_SIZE_Y, &mSizeY);
	graphics->ChangeSize(mSizeX, mSizeY);
}

void MainContainer::browse()
{
	mTexturePath = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png)"));
	textBrowser->setPlainText(PathFindFileNameA(mTexturePath.toStdString().c_str()));
	graphics->Retexture(mTexturePath.toStdString());
	//graphics->SetTexturePath(texturePath);
}

void MainContainer::setMaxParticles()
{
	mMaxParticles = textFieldMaxParticles->text().toInt();
	/*QString text = textFieldMaxParticles->toPlainText();
	bool newline = text.contains("\n");
	if (newline)
	{
		QString oldText = text;
		oldText.remove("\n");
		textFieldMaxParticles->document()->setPlainText(oldText);
	}
	bool space = text.contains(" ");
	if (space)
	{
		QString oldText = text;
		oldText.remove(" ");

		textFieldMaxParticles->document()->setPlainText(oldText);
	}
	bool ok;
	int t;

	t = text.toInt(&ok);

	if (ok == true)
	{
		if (t > 999)
		{
			textFieldMaxParticles->setPlainText("999");// document()->setPlainText("999");
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
	*/
	BuildParticleSystem();
}

void MainContainer::BuildParticleSystem()
{
	PARTICLESYSTEM ps(mEmitterType, mPosition, mMaxParticles,
		mVelocity, mEmissionDelay, mLifetime, mGravity,
		FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF()),
		FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF()),
		mSizeX, mSizeY);

	graphics->Rebuild(ps);
}


void MainContainer::setVelocityX()
{
	float x = textFieldVelocityX->text().toFloat();
	//float x = ErrorHandleUI(text, textFieldVelocityX);

	mVelocity.X = x;
	//BuildParticleSystem();
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mVelocity);

}

void MainContainer::setVelocityY()
{
	float y = textFieldVelocityY->text().toFloat();
	//float y = ErrorHandleUI(text, textFieldVelocityY);

	mVelocity.Y = y;
	//BuildParticleSystem();
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mVelocity);

}

void MainContainer::setVelocityZ()
{
	float z = textFieldVelocityZ->text().toFloat();
	//float z = ErrorHandleUI(text, textFieldVelocityZ);
	
	mVelocity.Z = z;
	//BuildParticleSystem();
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mVelocity);
}


void MainContainer::setEmissionDelay()
{
	mEmissionDelay = textFieldEmissionDelay->text().toFloat();
	
	particlesystem->SetProperty(PS_PROPERTY::PS_EMISSIONDELAY, &mEmissionDelay);
	BuildParticleSystem();
}

void MainContainer::setLifetime()
{
	mLifetime = textFieldLifetime->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_LIFETIME, &mLifetime);
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

	bool space = text.contains(" ");
	if (space)
	{
		QString oldText = text;
		oldText.remove(" ");

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



		return oldText.toFloat(&ok);


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

	if (key == Qt::Key::Key_W || key == Qt::Key::Key_S)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->SetLastCameraMovement(key, false);
		}
	}
	
	if (key == Qt::Key::Key_A || key == Qt::Key::Key_D)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->SetLastCameraRotation(key, false);
		}
	}
}

void MainContainer::keyReleaseEvent(QKeyEvent* evt)
{
	Qt::Key key = (Qt::Key)evt->key();

	if (key == Qt::Key::Key_W || key == Qt::Key::Key_S)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->SetLastCameraMovement(key, true);
		}
	}

	if (key == Qt::Key::Key_A || key == Qt::Key::Key_D)
	{
		if (evt->isAutoRepeat() == false)
		{
			graphics->SetLastCameraRotation(key, true);
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
