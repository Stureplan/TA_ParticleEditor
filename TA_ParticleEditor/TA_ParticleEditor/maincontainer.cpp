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
	mPS.emittertype = EMITTER_TYPE::EMIT_POINT;
	mPS.lifetime = DEFAULT_LIFETIME;
	textFieldLifetime->setPlaceholderText(std::to_string(DEFAULT_LIFETIME).c_str());

	mPS.emissiondelay = DEFAULT_EMISSIONDELAY;
	emissionDelaySlider->setValue(10);

	mPS.velocity = DEFAULT_VELOCITY;
	textFieldVelocityX->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.X).c_str());
	textFieldVelocityY->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.Y).c_str());
	textFieldVelocityZ->setPlaceholderText(std::to_string(DEFAULT_VELOCITY.Z).c_str());

	mPS.gravity = DEFAULT_GRAVITY;
	textFieldGravity->setPlaceholderText(std::to_string(DEFAULT_GRAVITY).c_str());

	mPS.maxparticles = DEFAULT_MAXPARTICLES;
	textFieldMaxParticles->setPlaceholderText(std::to_string(DEFAULT_MAXPARTICLES).c_str());

	mPS.startSizeX = DEFAULT_SIZE;
	mPS.startSizeY = DEFAULT_SIZE;
	textFieldStartSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldStartSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());

	mPS.endSizeX = DEFAULT_SIZE;
	mPS.endSizeY = DEFAULT_SIZE;
	textFieldEndSizeX->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());
	textFieldEndSizeY->setPlaceholderText(std::to_string(DEFAULT_SIZE).c_str());


	mTexturePath = DEFAULT_TEXTUREPATH;
	textureView->setPixmap(mTexturePath);

	mColorIn  = Qt::white;
	mColorOut = Qt::white;

	mPS.rectSizeX = 1.0f;
	mPS.rectSizeZ = 1.0f;
	
	mPS.textureType = 0;
	mPS.textureRows = 4;
	mPS.textureColumns = 4;
}

void MainContainer::setGravity()
{
	mPS.gravity = textFieldGravity->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_GRAVITY, &mPS.gravity);
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
		mPS.emittertype = ps.emittertype;
		mPS.maxparticles = ps.maxparticles;
		mPS.velocity = ps.velocity;
		mPS.emissiondelay = ps.emissiondelay;
		mPS.lifetime = ps.lifetime;
		mPS.gravity = ps.gravity;
		mColorIn.setRgbF(ps.colorIn.X, ps.colorIn.Y, ps.colorIn.Z, ps.colorIn.W);
		mColorOut.setRgbF(ps.colorOut.X, ps.colorOut.Y, ps.colorOut.Z, ps.colorOut.W);
		mPS.startSizeX = ps.startSizeX;
		mPS.startSizeY = ps.startSizeY;
		mPS.endSizeX = ps.endSizeX;
		mPS.endSizeY = ps.endSizeY;
		mPS.rectSizeX = ps.rectSizeX;
		mPS.rectSizeZ = ps.rectSizeZ;

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
	
	textFieldVelocityX->setText(QString::number(mPS.velocity.X));
	textFieldVelocityY->setText(QString::number(mPS.velocity.Y));
	textFieldVelocityZ->setText(QString::number(mPS.velocity.Z));

	//need implementation of rectangle position for emitter etc

	textFieldEmissionDelay	->setText(QString::number(mPS.emissiondelay));
	int value = mPS.emissiondelay * 100;
	emissionDelaySlider->setValue(value);
	textFieldLifetime		->setText(QString::number(mPS.lifetime));
	textFieldMaxParticles	->setText(QString::number(mPS.maxparticles));
	textFieldGravity		->setText(QString::number(mPS.gravity));
	textFieldRectSizeX		->setText(QString::number(mPS.rectSizeX));
	textFieldRectSizeZ		->setText(QString::number(mPS.rectSizeZ));
	textFieldStartSizeX		->setText(QString::number(mPS.startSizeX));
	textFieldStartSizeY		->setText(QString::number(mPS.startSizeY));
	textFieldEndSizeX		->setText(QString::number(mPS.endSizeX));
	textFieldEndSizeY		->setText(QString::number(mPS.endSizeY));


	colorInDisplay->setStyleSheet("QLineEdit { background: " + mColorIn.name() + "; selection-background-color: rgb(233, 99, 0); }");
	colorOutDisplay->setStyleSheet("QLineEdit { background: " + mColorOut.name() + "; selection-background-color: rgb(233, 99, 0); }");

	FLOAT4 inColor = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_IN, &inColor);
	
	FLOAT4 outColor = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_OUT, &outColor);

	int test;

	test = scaleBoxDisplay->currentIndex();
	test = mPS.emittertype;
	emitterTypeDisplay->setCurrentIndex(test);

	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mPS.startSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mPS.startSizeY);

	emitterTypeChanged(mPS.emittertype);

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
	ps.emittertype = mPS.emittertype;
	ps.maxparticles = mPS.maxparticles;
	ps.velocity = mPS.velocity;
	ps.emissiondelay = mPS.emissiondelay;
	ps.lifetime = mPS.lifetime;
	ps.gravity = mPS.gravity;
	ps.colorIn  = FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF());
	ps.colorOut = FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF());
	ps.startSizeX = mPS.startSizeX;
	ps.startSizeY = mPS.startSizeY;
	ps.endSizeX = mPS.endSizeX;
	ps.endSizeY = mPS.endSizeY;

	ps.rectSizeX = mPS.rectSizeX;
	ps.rectSizeZ = mPS.rectSizeZ;

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
	mPS.emittertype = (EMITTER_TYPE)mode;
	
	if (mode == EMITTER_TYPE::EMIT_POINT)
	{
		rectangleWidget->setEnabled(false);
	}
	if (mode == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		rectangleWidget->setEnabled(true);
		BuildParticleSystem();
	}

	particlesystem->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mPS.emittertype);
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

	mPS.textureType = mode;
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mPS.textureType);
	graphics->ChangeTextureType(mPS.textureType);
}

void MainContainer::startSizeX()
{
	mPS.startSizeX = textFieldStartSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mPS.startSizeX);
}

void MainContainer::startSizeY()
{
	mPS.startSizeY = textFieldStartSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mPS.startSizeY);
}

void MainContainer::endSizeX()
{
	mPS.endSizeX = textFieldEndSizeX->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_X, &mPS.endSizeX);
}

void MainContainer::endSizeY()
{
	mPS.endSizeY = textFieldEndSizeY->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_Y, &mPS.endSizeY);
}

void MainContainer::rectResize()
{
	mPS.rectSizeX = textFieldRectSizeX->text().toFloat();
	mPS.rectSizeZ = textFieldRectSizeZ->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_RECT_SIZE_X, &mPS.rectSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_RECT_SIZE_Z, &mPS.rectSizeZ);
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
	mPS.maxparticles = textFieldMaxParticles->text().toInt();
	BuildParticleSystem();
}

void MainContainer::BuildParticleSystem()
{
	PARTICLESYSTEM ps(mPS.emittertype, mPS.maxparticles,
		mPS.velocity, mPS.emissiondelay, mPS.lifetime, mPS.gravity,
		FLOAT4(mColorIn.redF(), mColorIn.greenF(), mColorIn.blueF(), mColorIn.alphaF()),
		FLOAT4(mColorOut.redF(), mColorOut.greenF(), mColorOut.blueF(), mColorOut.alphaF()),
		mPS.startSizeX, mPS.startSizeY, mPS.endSizeX, mPS.endSizeY, mPS.rectSizeX, mPS.rectSizeZ,
		mPS.textureType, mPS.textureColumns, mPS.textureRows);

	graphics->Rebuild(ps);
}


void MainContainer::setVelocityX()
{
	float x = textFieldVelocityX->text().toFloat();

	mPS.velocity.X = x;
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mPS.velocity);

}

void MainContainer::setVelocityY()
{
	float y = textFieldVelocityY->text().toFloat();

	mPS.velocity.Y = y;
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mPS.velocity);

}

void MainContainer::setVelocityZ()
{
	float z = textFieldVelocityZ->text().toFloat();
	
	mPS.velocity.Z = z;
	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mPS.velocity);
}

void MainContainer::setEmissionDelay(int value)
{
	int a = emissionDelaySlider->value();
	mPS.emissiondelay = a / 100.0f;
	emissionDelaySlider_label->setText(QString::number(mPS.emissiondelay, 'f', 2));

	particlesystem->SetProperty(PS_PROPERTY::PS_EMISSIONDELAY, &mPS.emissiondelay);
}

void MainContainer::setVelocityXSlider(int value)
{
	int a = velocityXSlider->value();
	mPS.velocity.X = a;
	textFieldVelocityX->setText(QString::number(mPS.velocity.X, 'f', 1));

	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mPS.velocity);
}

void MainContainer::setVelocityYSlider(int value)
{
	int a = velocityYSlider->value();
	mPS.velocity.Y = a;
	textFieldVelocityY->setText(QString::number(mPS.velocity.Y, 'f', 1));

	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mPS.velocity);
}

void MainContainer::setVelocityZSlider(int value)
{
	int a = velocityZSlider->value();
	mPS.velocity.Z = a;
	textFieldVelocityZ->setText(QString::number(mPS.velocity.Z, 'f', 1));

	particlesystem->SetProperty(PS_PROPERTY::PS_VELOCITY, &mPS.velocity);
}

void MainContainer::setLifetime()
{
	mPS.lifetime = textFieldLifetime->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_LIFETIME, &mPS.lifetime);
}

void MainContainer::setColumnsRows()
{
	mPS.textureColumns = abs(spriteColumns->text().toInt());
	mPS.textureRows = abs(spriteRows->text().toInt());

	spriteColumns->setText(QString::number(mPS.textureColumns));
	spriteRows->setText(QString::number(mPS.textureRows));

	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_COLUMNS, &mPS.textureColumns);
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_ROWS,	 &mPS.textureRows);
}

void MainContainer::selectTab(int index)
{
	int max = psTabs->count() - 1;
	if (index != max)
	{
		// PS selected, change all values in maincontainer to reflect it.
		FillValues(graphics->ParticleSystemByIndex(index));
	}
}

void MainContainer::addTab(int index)
{
	int max = psTabs->count()-1;
	if (index == max && max < 4)
	{
		psTabs->insertTab(index, new QWidget(this), QString("Particle System %0").arg(max + 1));

		//graphics->AddParticleSystem();
	}
}

void MainContainer::removeTab(int index)
{
	int max = psTabs->count() - 1;
	if (index != max && max > 1)
	{
		psTabs->removeTab(index);

		//graphics->RemoveParticleSystem(index);
	}
}

void MainContainer::FillValues(PARTICLESYSTEM fromPS)
{
	mPS = fromPS;
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
