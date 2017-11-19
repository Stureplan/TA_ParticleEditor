﻿#include "maincontainer.h"

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
	textFieldVelocityX		= findChild<QLineEdit*>		("velocityX",			Qt::FindChildOption::FindChildrenRecursively);
	velocityXSlider			= findChild<QSlider*>		("velocityXSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityY		= findChild<QLineEdit*>		("velocityY",			Qt::FindChildOption::FindChildrenRecursively);
	velocityYSlider			= findChild<QSlider*>		("velocityYSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityZ		= findChild<QLineEdit*>		("velocityZ",			Qt::FindChildOption::FindChildrenRecursively);
	velocityZSlider			= findChild<QSlider*>		("velocityZSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldGravity		= findChild<QLineEdit*>		("gravity",				Qt::FindChildOption::FindChildrenRecursively);
	emissionDelaySlider		= findChild<QSlider*>		("emissionDelaySlider",	Qt::FindChildOption::FindChildrenRecursively);
	emissionDelaySlider_label = findChild<QLabel*>		("label_EmDelaySlide",	Qt::FindChildOption::FindChildrenRecursively);
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
	psTabs					= findChild<QTabWidget*>	("psTabs",				Qt::FindChildOption::FindChildrenRecursively);

}
#pragma endregion

void MainContainer::Init()
{
	mCurrentPS.emittertype = EMITTER_TYPE::EMIT_POINT;
	mCurrentPS.lifetime = DEFAULT_LIFETIME;
	textFieldLifetime->setPlaceholderText(std::to_string(DEFAULT_LIFETIME).c_str());

	mCurrentPS.emissiondelay = DEFAULT_EMISSIONDELAY;
	emissionDelaySlider->setValue(10);

	mCurrentPS.velocity = DEFAULT_VELOCITY;
	textFieldVelocityX->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.X).c_str());
	textFieldVelocityY->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.Y).c_str());
	textFieldVelocityZ->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.Z).c_str());

	mCurrentPS.gravity = DEFAULT_GRAVITY;
	textFieldGravity->setPlaceholderText(std::to_string(DEFAULT_GRAVITY).c_str());

	mCurrentPS.maxparticles = DEFAULT_MAXPARTICLES;
	textFieldMaxParticles->setPlaceholderText(std::to_string(DEFAULT_MAXPARTICLES).c_str());

	mCurrentPS.startSizeX = DEFAULT_SIZE;
	mCurrentPS.startSizeY = DEFAULT_SIZE;
	textFieldStartSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldStartSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());

	mCurrentPS.endSizeX = DEFAULT_SIZE;
	mCurrentPS.endSizeY = DEFAULT_SIZE;
	textFieldEndSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldEndSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());


	mTexturePath = DEFAULT_TEXTUREPATH;
	textureView->setPixmap(mTexturePath);

	mColorIn  = Qt::white;
	mColorOut = Qt::white;

	mCurrentPS.rectSizeX = 1.0f;
	mCurrentPS.rectSizeZ = 1.0f;
	
	mCurrentPS.textureType = 0;
	mCurrentPS.textureRows = 4;
	mCurrentPS.textureColumns = 4;
}

void MainContainer::setGravity()
{
	mCurrentPS.gravity = textFieldGravity->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_GRAVITY, &mCurrentPS.gravity);
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
		mCurrentPS.emittertype = ps.emittertype;
		mCurrentPS.maxparticles = ps.maxparticles;
		mCurrentPS.velocity = ps.velocity;
		mCurrentPS.emissiondelay = ps.emissiondelay;
		mCurrentPS.lifetime = ps.lifetime;
		mCurrentPS.gravity = ps.gravity;
		mColorIn.setRgbF(ps.colorIn.X, ps.colorIn.Y, ps.colorIn.Z, ps.colorIn.W);
		mColorOut.setRgbF(ps.colorOut.X, ps.colorOut.Y, ps.colorOut.Z, ps.colorOut.W);
		mCurrentPS.startSizeX = ps.startSizeX;
		mCurrentPS.startSizeY = ps.startSizeY;
		mCurrentPS.endSizeX = ps.endSizeX;
		mCurrentPS.endSizeY = ps.endSizeY;
		mCurrentPS.rectSizeX = ps.rectSizeX;
		mCurrentPS.rectSizeZ = ps.rectSizeZ;

		SetUiElements();
		std::string path = n;
		graphics->Retexture(Utility::Path() + "Data\\Textures\\" + path);
		BuildParticleSystem();

		fclose(file);
	}


}

void MainContainer::SetUiElements()
{
	// Set UI textfields after loading a previously saved particle effect
	
	textFieldVelocityX->setText(QString::number(mCurrentPS.velocity.X));
	textFieldVelocityY->setText(QString::number(mCurrentPS.velocity.Y));
	textFieldVelocityZ->setText(QString::number(mCurrentPS.velocity.Z));

	//need implementation of rectangle position for emitter etc

	textFieldEmissionDelay	->setText(QString::number(mCurrentPS.emissiondelay));
	int value = mCurrentPS.emissiondelay * 100;
	emissionDelaySlider->setValue(value);
	textFieldLifetime		->setText(QString::number(mCurrentPS.lifetime));
	textFieldMaxParticles	->setText(QString::number(mCurrentPS.maxparticles));
	textFieldGravity		->setText(QString::number(mCurrentPS.gravity));
	textFieldRectSizeX		->setText(QString::number(mCurrentPS.rectSizeX));
	textFieldRectSizeZ		->setText(QString::number(mCurrentPS.rectSizeZ));
	textFieldStartSizeX		->setText(QString::number(mCurrentPS.startSizeX));
	textFieldStartSizeY		->setText(QString::number(mCurrentPS.startSizeY));
	textFieldEndSizeX		->setText(QString::number(mCurrentPS.endSizeX));
	textFieldEndSizeY		->setText(QString::number(mCurrentPS.endSizeY));


	colorInDisplay->setStyleSheet("QLineEdit { background: " + mColorIn.name() + "; selection-background-color: rgb(233, 99, 0); }");
	colorOutDisplay->setStyleSheet("QLineEdit { background: " + mColorOut.name() + "; selection-background-color: rgb(233, 99, 0); }");

	FLOAT4 inColor = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_IN, &inColor);
	
	FLOAT4 outColor = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_OUT, &outColor);

	int test;

	test = scaleBoxDisplay->currentIndex();
	test = mCurrentPS.emittertype;
	emitterTypeDisplay->setCurrentIndex(test);

	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mCurrentPS.startSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mCurrentPS.startSizeY);

	emitterTypeChanged(mCurrentPS.emittertype);

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
	ps.emittertype = mCurrentPS.emittertype;
	ps.maxparticles = mCurrentPS.maxparticles;
	ps.velocity = mCurrentPS.velocity;
	ps.emissiondelay = mCurrentPS.emissiondelay;
	ps.lifetime = mCurrentPS.lifetime;
	ps.gravity = mCurrentPS.gravity;
	ps.colorIn  = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	ps.colorOut = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	ps.startSizeX = mCurrentPS.startSizeX;
	ps.startSizeY = mCurrentPS.startSizeY;
	ps.endSizeX = mCurrentPS.endSizeX;
	ps.endSizeY = mCurrentPS.endSizeY;

	ps.rectSizeX = mCurrentPS.rectSizeX;
	ps.rectSizeZ = mCurrentPS.rectSizeZ;

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

		fclose(file);
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
	mCurrentPS.emittertype = (EMITTER_TYPE)mode;
	
	if (mode == EMITTER_TYPE::EMIT_POINT)
	{
		rectangleWidget->setEnabled(false);
	}
	if (mode == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		rectangleWidget->setEnabled(true);
		BuildParticleSystem();
	}

	particlesystem->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mCurrentPS.emittertype);
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
	if (mode == 2)
	{
		spriteSheetWidget->setEnabled(true);
		setColumnsRows();
	}

	mCurrentPS.textureType = mode;
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mCurrentPS.textureType);
	graphics->ChangeTextureType(mCurrentPS.textureType);
}

void MainContainer::startSizeX()
{
	mCurrentPS.startSizeX = textFieldStartSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mCurrentPS.startSizeX);
}

void MainContainer::startSizeY()
{
	mCurrentPS.startSizeY = textFieldStartSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mCurrentPS.startSizeY);
}

void MainContainer::endSizeX()
{
	mCurrentPS.endSizeX = textFieldEndSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_X, &mCurrentPS.endSizeX);
}

void MainContainer::endSizeY()
{
	mCurrentPS.endSizeY = textFieldEndSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_Y, &mCurrentPS.endSizeY);
}

void MainContainer::rectResize()
{
	mCurrentPS.rectSizeX = textFieldRectSizeX->text().toFloat();
	mCurrentPS.rectSizeZ = textFieldRectSizeZ->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_RECT_SIZE_X, &mCurrentPS.rectSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_RECT_SIZE_Z, &mCurrentPS.rectSizeZ);
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
	mCurrentPS.maxparticles = textFieldMaxParticles->text().toInt();
	BuildParticleSystem();
}

void MainContainer::BuildParticleSystem()
{
	PARTICLESYSTEM ps(mCurrentPS.emittertype, mCurrentPS.maxparticles,
		mCurrentPS.velocity, mCurrentPS.emissiondelay, mCurrentPS.lifetime, mCurrentPS.gravity,
		FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF()),
		FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF()),
		mCurrentPS.startSizeX, mCurrentPS.startSizeY, mCurrentPS.endSizeX, mCurrentPS.endSizeY, mCurrentPS.rectSizeX, mCurrentPS.rectSizeZ,
		mCurrentPS.textureType, mCurrentPS.textureColumns, mCurrentPS.textureRows);

	graphics->Rebuild(ps);
}


void MainContainer::setVelocityX()
{
	float x = textFieldVelocityX->text().toFloat();

	mCurrentPS.velocity.X = x;
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);

}

void MainContainer::setVelocityY()
{
	float y = textFieldVelocityY->text().toFloat();

	mCurrentPS.velocity.Y = y;
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);

}

void MainContainer::setVelocityZ()
{
	float z = textFieldVelocityZ->text().toFloat();
	
	mCurrentPS.velocity.Z = z;
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setEmissionDelay(int value)
{
	int a = emissionDelaySlider->value();
	mCurrentPS.emissiondelay = a / 100.0f;
	emissionDelaySlider_label->setText(QString::number(mCurrentPS.emissiondelay, 'f', 2));

	particlesystem->SetProperty(PS_PROPERTY::PS_EMISSIONDELAY, &mCurrentPS.emissiondelay);
}

void MainContainer::setVelocityXSlider(int value)
{
	int a = velocityXSlider->value();
	mCurrentPS.velocity.X = a;
	textFieldVelocityX->setText(QString::number(mCurrentPS.velocity.X, 'f', 1));

	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setVelocityYSlider(int value)
{
	int a = velocityYSlider->value();
	mCurrentPS.velocity.Y = a;
	textFieldVelocityY->setText(QString::number(mCurrentPS.velocity.Y, 'f', 1));

	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setVelocityZSlider(int value)
{
	int a = velocityZSlider->value();
	mCurrentPS.velocity.Z = a;
	textFieldVelocityZ->setText(QString::number(mCurrentPS.velocity.Z, 'f', 1));

	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setLifetime()
{
	mCurrentPS.lifetime = textFieldLifetime->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_LIFETIME, &mCurrentPS.lifetime);
}

void MainContainer::setColumnsRows()
{
	mCurrentPS.textureColumns = abs(spriteColumns->text().toInt());
	mCurrentPS.textureRows = abs(spriteRows->text().toInt());

	spriteColumns->setText(QString::number(mCurrentPS.textureColumns));
	spriteRows->setText(QString::number(mCurrentPS.textureRows));

	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_COLUMNS, &mCurrentPS.textureColumns);
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_ROWS,	 &mCurrentPS.textureRows);
}

void MainContainer::selectTab(int index)
{
	int max = psTabs->count() - 1;
	if (index != max)
	{
		// PS selected, change all values in maincontainer to reflect it.
		mCurrentPSIndex = index;
		FillValues(graphics->ParticleSystemByIndex(index));
	}
}

void MainContainer::addTab(int index)
{
	int max = psTabs->count()-1;
	if (index == max && max < 4)
	{
		psTabs->insertTab(index, new QWidget(this), QString("Particle System %0").arg(max + 1));
		graphics->AddParticleSystem(mCurrentPS);
	}
}

void MainContainer::removeTab(int index)
{
	int max = psTabs->count() - 1;
	if (index != max && max > 1)
	{
		psTabs->removeTab(index);
		graphics->RemoveParticleSystem(index);
	}
}

void MainContainer::FillValues(PARTICLESYSTEM fromCurrentPS)
{
	mCurrentPS = fromCurrentPS;

	// TODO: Fill UI pointers with values...
	// Actually just make an UpdateUI() function which fills UI pointers with mCurrentPS values.
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

	if (key == Qt::Key::Key_Shift || key == Qt::Key::Key_Control)
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

	if (key == Qt::Key::Key_Shift || key == Qt::Key::Key_Control)
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
