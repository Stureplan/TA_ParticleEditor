#include "vld.h"

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
void MainContainer::SetPointers(ParticleSystem* ps)
{
	particlesystem = ps;
	graphics				= findChild<Graphics*>		("graphics",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldParticleInfo	= findChild<QLabel*>		("label_ParticleInfo",	Qt::FindChildOption::FindChildrenRecursively);
	textFieldLifetime		= findChild<QLineEdit*>		("lifetime",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldEmissionDelay	= findChild<QLineEdit*>		("emissionDelay",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityX		= findChild<QLineEdit*>		("velocityX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityY		= findChild<QLineEdit*>		("velocityY",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityZ		= findChild<QLineEdit*>		("velocityZ",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldGravity		= findChild<QLineEdit*>		("gravity",				Qt::FindChildOption::FindChildrenRecursively);
	browseBtn				= findChild<QPushButton*>	("browsepath",			Qt::FindChildOption::FindChildrenRecursively);
	saveBtn					= findChild<QPushButton*>	("savePS",				Qt::FindChildOption::FindChildrenRecursively);
	loadBtn					= findChild<QPushButton*>	("loadPS",				Qt::FindChildOption::FindChildrenRecursively);
	textFieldMaxParticles	= findChild<QLineEdit*>		("maxParticles",		Qt::FindChildOption::FindChildrenRecursively);
	textBrowser				= findChild<QTextBrowser*>	("textBrowser",			Qt::FindChildOption::FindChildrenRecursively);
	colorInDisplay			= findChild<QLineEdit*>		("colorInDisplay",		Qt::FindChildOption::FindChildrenRecursively);
	colorOutDisplay			= findChild<QLineEdit*>		("colorOutDisplay",		Qt::FindChildOption::FindChildrenRecursively);
	scaleBoxDisplay			= findChild<QComboBox*>		("scaleBox",			Qt::FindChildOption::FindChildrenRecursively);
	emitterTypeDisplay		= findChild<QComboBox*>		("emitterTypeBox",		Qt::FindChildOption::FindChildrenRecursively);
	textureTypeBox			= findChild<QComboBox*>		("textureTypeBox",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldStartSizeX		= findChild<QLineEdit*>		("startSizeX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldStartSizeY		= findChild<QLineEdit*>		("startSizeY",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldEndSizeX		= findChild<QLineEdit*>		("endSizeX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldEndSizeY		= findChild<QLineEdit*>		("endSizeY",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldRectSizeX		= findChild<QLineEdit*>		("rectSizeX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldRectSizeZ		= findChild<QLineEdit*>		("rectSizeZ",			Qt::FindChildOption::FindChildrenRecursively);
	rectangleWidget			= findChild<QWidget*>		("rectangleWidget",		Qt::FindChildOption::FindChildrenRecursively);
	spriteSheetWidget		= findChild<QWidget*>		("spriteSheetWidget",	Qt::FindChildOption::FindChildrenRecursively);
	textureView				= findChild<QLabel*>		("textureView",			Qt::FindChildOption::FindChildrenRecursively);
	spriteColumns			= findChild<QLineEdit*>		("spriteColumns",		Qt::FindChildOption::FindChildrenRecursively);
	spriteRows				= findChild<QLineEdit*>		("spriteRows",			Qt::FindChildOption::FindChildrenRecursively);
}
#pragma endregion

void MainContainer::Init()
{
	mEmitterType = EMITTER_TYPE::EMIT_POINT;

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

	mStartSizeX = DEFAULT_SIZE;
	mStartSizeY = DEFAULT_SIZE;
	textFieldStartSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldStartSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());

	mEndSizeX = DEFAULT_SIZE;
	mEndSizeY = DEFAULT_SIZE;
	textFieldEndSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldEndSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());


	mTexturePath = DEFAULT_TEXTUREPATH;
	textureView->setPixmap(mTexturePath);

	mColorIn  = Qt::white;
	mColorOut = Qt::white;

	mRectSizeX = 1.0f;
	mRectSizeZ = 1.0f;
	
	mTextureType = 0;
	mTextureRows = 4;
	mTextureColumns = 4;
}

void MainContainer::setGravity()
{
	mGravity = textFieldGravity->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_GRAVITY, &mGravity);
}

void MainContainer::load()
{
	std::string loadPath = QFileDialog::getOpenFileName(this).toStdString();
	unsigned int textureNameSize = 0;
	PARTICLESYSTEM ps;
	FILE* file = fopen(loadPath.c_str(), "rb");

	if (file != NULL)
	{
		fread(&textureNameSize, sizeof(unsigned int), 1, file);
	
		std::string n(textureNameSize, '\0');
		fread(&n[0], sizeof(char), textureNameSize, file);
		fread(&ps, sizeof(PARTICLESYSTEM), 1, file);
		mEmitterType = ps.emittertype;
		mMaxParticles = ps.maxparticles;
		mVelocity = ps.velocity;
		mEmissionDelay = ps.emissiondelay;
		mLifetime = ps.lifetime;
		mGravity = ps.gravity;
		mColorIn.setRgbF(ps.colorIn.X, ps.colorIn.Y, ps.colorIn.Z, ps.colorIn.W);
		mColorOut.setRgbF(ps.colorOut.X, ps.colorOut.Y, ps.colorOut.Z, ps.colorOut.W);
		mStartSizeX = ps.startSizeX;
		mStartSizeY = ps.startSizeY;
		mEndSizeX = ps.endSizeX;
		mEndSizeY = ps.endSizeY;
		mRectSizeX = ps.rectSizeX;
		mRectSizeZ = ps.rectSizeZ;

		SetUiElements();
		std::string path = n;
		graphics->Retexture(Utility::Path() + "Data\\Textures\\" + path);
		BuildParticleSystem();
	}
}

void MainContainer::SetUiElements()
{
	// Set UI textfields after loading a previously saved particle effect
	
	textFieldVelocityX->setText(QString::number(mVelocity.X));
	textFieldVelocityY->setText(QString::number(mVelocity.Y));
	textFieldVelocityZ->setText(QString::number(mVelocity.Z));

	//need implementation of rectangle position for emitter etc

	textFieldEmissionDelay	->setText(QString::number(mEmissionDelay));
	textFieldLifetime		->setText(QString::number(mLifetime));
	textFieldMaxParticles	->setText(QString::number(mMaxParticles));
	textFieldGravity		->setText(QString::number(mGravity));
	textFieldRectSizeX		->setText(QString::number(mRectSizeX));
	textFieldRectSizeZ		->setText(QString::number(mRectSizeZ));
	textFieldStartSizeX		->setText(QString::number(mStartSizeX));
	textFieldStartSizeY		->setText(QString::number(mStartSizeY));
	textFieldEndSizeX		->setText(QString::number(mEndSizeX));
	textFieldEndSizeY		->setText(QString::number(mEndSizeY));


	colorInDisplay->setStyleSheet("QLineEdit { background: " + mColorIn.name() + "; selection-background-color: rgb(233, 99, 0); }");
	colorOutDisplay->setStyleSheet("QLineEdit { background: " + mColorOut.name() + "; selection-background-color: rgb(233, 99, 0); }");

	FLOAT4 inColor = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_IN, &inColor);
	
	FLOAT4 outColor = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_OUT, &outColor);

	int test;

	test = scaleBoxDisplay->currentIndex();
	test = mEmitterType;
	emitterTypeDisplay->setCurrentIndex(test);

	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mStartSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mStartSizeY);

	emitterTypeChanged(mEmitterType);

	//textBrowser->setText(mTexturePath); fix later when texture thing is done
}

void MainContainer::save()
{
	std::string exportPath = QFileDialog::getSaveFileName(this).toStdString();
	
	size_t found = exportPath.find(".ps");
	if (found == std::string::npos)
	{
		// Only add .ps extension if it isn't already in the filename
		// (this is for overwriting already existing files)
		exportPath.append(".ps");
	}

	//std::string exportPath = PathFindFileNameA(savePath.toStdString().c_str());
	
	PARTICLESYSTEM ps;
	ps.emittertype = mEmitterType;
	ps.maxparticles = mMaxParticles;
	ps.velocity = mVelocity;
	ps.emissiondelay = mEmissionDelay;
	ps.lifetime = mLifetime;
	ps.gravity = mGravity;
	ps.colorIn  = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	ps.colorOut = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	ps.startSizeX = mStartSizeX;
	ps.startSizeY = mStartSizeY;
	ps.endSizeX = mEndSizeX;
	ps.endSizeY = mEndSizeY;

	ps.rectSizeX = mRectSizeX;
	ps.rectSizeZ = mRectSizeZ;

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

void MainContainer::emitterTypeChanged(int mode)
{
	mEmitterType = (EMITTER_TYPE)mode;
	
	if (mode == EMITTER_TYPE::EMIT_POINT)
	{
		rectangleWidget->setEnabled(false);
	}
	if (mode == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		rectangleWidget->setEnabled(true);
		BuildParticleSystem();
	}

	graphics->EmitterGizmo(mEmitterType);
	particlesystem->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mEmitterType);
}

void MainContainer::textureTypeChanged(int mode)
{
	if (mode == 0)
	{
		spriteSheetWidget->setEnabled(false);
	}
	if (mode == 1)
	{
		spriteSheetWidget->setEnabled(true);
		setColumnsRows();
	}

	mTextureType = mode;
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mTextureType);
	graphics->ChangeTextureType(mTextureType, mTextureColumns, mTextureRows);
}

void MainContainer::startSizeX()
{
	mStartSizeX = textFieldStartSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mStartSizeX);
}

void MainContainer::startSizeY()
{
	mStartSizeY = textFieldStartSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mStartSizeY);
}

void MainContainer::endSizeX()
{
	mEndSizeX = textFieldEndSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_X, &mEndSizeX);
}

void MainContainer::endSizeY()
{
	mEndSizeY = textFieldEndSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_Y, &mEndSizeY);
}

void MainContainer::rectResize()
{
	mRectSizeX = textFieldRectSizeX->text().toFloat();
	mRectSizeZ = textFieldRectSizeZ->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_RECT_SIZE_X, &mRectSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_RECT_SIZE_Z, &mRectSizeZ);
	BuildParticleSystem();
}

void MainContainer::browse()
{
	mTexturePath = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png *.PNG *.dds *.DDS)"));

	if (mTexturePath != "")
	{
		textBrowser->setPlainText(PathFindFileNameA(mTexturePath.toStdString().c_str()));
		if (mTexturePath.contains(".DDS") || mTexturePath.contains(".dds"))
		{
			textureView->setPixmap(QString(DEFAULT_DDS_TEXTUREPATH));
		}
		else
		{
			textureView->setPixmap(mTexturePath);
		}
		graphics->Retexture(mTexturePath.toStdString());
	}
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
	PARTICLESYSTEM ps(mEmitterType, mMaxParticles,
		mVelocity, mEmissionDelay, mLifetime, mGravity,
		FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF()),
		FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF()),
		mStartSizeX, mStartSizeY, mEndSizeX, mEndSizeY, mRectSizeX, mRectSizeZ,
		mTextureType, mTextureColumns, mTextureRows);

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

void MainContainer::setColumnsRows()
{
	mTextureColumns = abs(spriteColumns->text().toInt());
	mTextureRows = abs(spriteRows->text().toInt());

	spriteColumns->setText(QString::number(mTextureColumns));
	spriteRows->setText(QString::number(mTextureRows));

	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_COLUMNS, &mTextureColumns);
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_ROWS,	 &mTextureRows);
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
	return 0.0f;
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
