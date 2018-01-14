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
	color0Display			= findChild<QLineEdit*>		("color0Display",		Qt::FindChildOption::FindChildrenRecursively);
	color1Display			= findChild<QLineEdit*>		("color1Display",		Qt::FindChildOption::FindChildrenRecursively);
	color2Display			= findChild<QLineEdit*>		("color2Display",		Qt::FindChildOption::FindChildrenRecursively);
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
	interpolateFrames		= findChild<QCheckBox*>		("interpolateFrames",	Qt::FindChildOption::FindChildrenRecursively);
	rotateParticles			= findChild<QCheckBox*>		("rotateParticles",		Qt::FindChildOption::FindChildrenRecursively);
	noiseDissolve			= findChild<QCheckBox*>		("noiseDissolve",		Qt::FindChildOption::FindChildrenRecursively);
	loopingCheckBox			= findChild<QCheckBox*>		("looping",				Qt::FindChildOption::FindChildrenRecursively);

	textFieldEmissionDelay = findChild<QLabel*>("label_EmDelaySlide", Qt::FindChildOption::FindChildrenRecursively);
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

	mCurrentPS.maxparticles = textFieldMaxParticles->text().toInt();

	mCurrentPS.startSizeX = textFieldStartSizeX->text().toFloat();
	mCurrentPS.startSizeY = textFieldStartSizeY->text().toFloat();

	mCurrentPS.endSizeX = textFieldEndSizeX->text().toFloat();
	mCurrentPS.endSizeY = textFieldEndSizeY->text().toFloat();

	char result[MAX_PATH];
	GetModuleFileNameA(NULL, result, MAX_PATH);
	PathRemoveFileSpecA(result);
	
	mTexturePath = QString(result).append("\\Data\\Textures\\plasmaball.png");
	//mTexturePath = textBrowser->placeholderText().toStdString().c_str();
	textureView->setPixmap(mTexturePath);

	mColor0 = Qt::white;
	mColor1 = Qt::white;
	mColor2 = Qt::white;

	mCurrentPS.color0 = FLOAT4(mColor0.redF(), mColor0.greenF(), mColor0.blueF(), mColor0.alphaF());
	mCurrentPS.color1 = FLOAT4(mColor1.redF(), mColor1.greenF(), mColor1.blueF(), mColor1.alphaF());
	mCurrentPS.color2 = FLOAT4(mColor2.redF(), mColor2.greenF(), mColor2.blueF(), mColor2.alphaF());



	mCurrentPS.rectSizeX = 1.0f;
	mCurrentPS.rectSizeZ = 1.0f;
	
	mCurrentPS.textureType = 0;
	mCurrentPS.textureRows = 4;
	mCurrentPS.textureColumns = 4;
	mCurrentPS.looping = (int)loopingCheckBox->isChecked();
}

void MainContainer::setGravity()
{
	mCurrentPS.gravity = textFieldGravity->text().toFloat();
	particlesystem->SetProperty(PS_PROPERTY::PS_GRAVITY, &mCurrentPS.gravity);
}

void MainContainer::load()
{
	std::string loadPath = QFileDialog::getOpenFileName(this).toStdString();
	int textureNameSize = 0;
	EMITTER ps;
	FILE* file = fopen(loadPath.c_str(), "rb");

	if (file != NULL)
	{
		fread(&textureNameSize, sizeof(int), 1, file);
	
		std::string n(textureNameSize, '\0');
		fread(&n[0], sizeof(char), textureNameSize, file);
		fread(&ps, sizeof(EMITTER), 1, file);
		mCurrentPS = ps;

		mTexturePath = n.c_str();
		graphics->Retexture(Utility::Path() + "Data\\Textures\\" + mTexturePath.toStdString());
		fclose(file);

		SetUiElements();
		BuildParticleSystem();
	}
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

	EMITTER ps = mCurrentPS;

	FILE* file = fopen(exportPath.c_str(), "wb");
	if (file != NULL)
	{
		std::string texpath = mTexturePath.toStdString();
		const char* tex = texpath.c_str();

		int texturenamesize = strlen(tex);

		// First just write the size of the texture filename (imagine this is a header)
		fwrite(&texturenamesize, sizeof(int), 1, file);

		// ...then write the texture name
		fwrite(tex, sizeof(const char), texturenamesize, file);

		// ...then we write the particle system details
		fwrite(&ps, sizeof(EMITTER), 1, file);
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

void MainContainer::SetUiElements()
{
	// Set UI textfields after loading a previously saved particle effect
	
	textFieldVelocityX->setText(QString::number(mCurrentPS.velocity.X));
	textFieldVelocityY->setText(QString::number(mCurrentPS.velocity.Y));
	textFieldVelocityZ->setText(QString::number(mCurrentPS.velocity.Z));

	//need implementation of rectangle position for emitter etc

	textFieldEmissionDelay	->setText(QString::number(mCurrentPS.emissiondelay));
	emissionDelaySlider		->setValue((int)(mCurrentPS.emissiondelay * 100));
	textFieldLifetime		->setText(QString::number(mCurrentPS.lifetime));
	textFieldMaxParticles	->setText(QString::number(mCurrentPS.maxparticles));
	textFieldGravity		->setText(QString::number(mCurrentPS.gravity));
	textFieldRectSizeX		->setText(QString::number(mCurrentPS.rectSizeX));
	textFieldRectSizeZ		->setText(QString::number(mCurrentPS.rectSizeZ));
	textFieldStartSizeX		->setText(QString::number(mCurrentPS.startSizeX));
	textFieldStartSizeY		->setText(QString::number(mCurrentPS.startSizeY));
	textFieldEndSizeX		->setText(QString::number(mCurrentPS.endSizeX));
	textFieldEndSizeY		->setText(QString::number(mCurrentPS.endSizeY));



	mColor0.setRgbF(mCurrentPS.color0.X, mCurrentPS.color0.Y, mCurrentPS.color0.Z, mCurrentPS.color0.W);
	color0Display->setStyleSheet("QLineEdit { background: " + mColor0.name() + "; selection-background-color: rgb(233, 99, 0); }");
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_0, &mCurrentPS.color0);

	mColor1.setRgbF(mCurrentPS.color1.X, mCurrentPS.color1.Y, mCurrentPS.color1.Z, mCurrentPS.color1.W);
	color1Display->setStyleSheet("QLineEdit { background: " + mColor1.name() + "; selection-background-color: rgb(233, 99, 0); }");
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_1, &mCurrentPS.color1);

	mColor2.setRgbF(mCurrentPS.color2.X, mCurrentPS.color2.Y, mCurrentPS.color2.Z, mCurrentPS.color2.W);
	color2Display->setStyleSheet("QLineEdit { background: " + mColor2.name() + "; selection-background-color: rgb(233, 99, 0); }");
	particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_2, &mCurrentPS.color2);

	emitterTypeDisplay->setCurrentIndex(mCurrentPS.emittertype);

	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mCurrentPS.startSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mCurrentPS.startSizeY);
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_X,   &mCurrentPS.endSizeX);
	particlesystem->SetProperty(PS_PROPERTY::PS_END_SIZE_Y,	  &mCurrentPS.endSizeY);



	emitterTypeChanged(mCurrentPS.emittertype);

	textBrowser->setText(mTexturePath); //fix later when texture thing is done
}



void MainContainer::color0()
{
	QColor c = QColorDialog::getColor(mColor0, this, "Choose In Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid())
	{
		mColor0 = c;
		color0Display->setStyleSheet("QLineEdit { background: "+ mColor0.name()+"; selection-background-color: rgb(233, 99, 0); }");
		
		FLOAT4 color = FLOAT4(mColor0.redF(), mColor0.greenF(), mColor0.blueF(), mColor0.alphaF());
		particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_0, &color);
		mCurrentPS.color0 = color;
	}
}

void MainContainer::color1()
{
	QColor c = QColorDialog::getColor(mColor1, this, "Choose In Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid())
	{
		mColor1 = c;
		color1Display->setStyleSheet("QLineEdit { background: " + mColor1.name() + "; selection-background-color: rgb(233, 99, 0); }");

		FLOAT4 color = FLOAT4(mColor1.redF(), mColor1.greenF(), mColor1.blueF(), mColor1.alphaF());
		particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_1, &color);
		mCurrentPS.color1 = color;
	}
}

void MainContainer::color2()
{
	QColor c = QColorDialog::getColor(mColor2, this, "Choose In Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid())
	{
		mColor2 = c;

		QString b = "#80FFFFFF";
		color2Display->setStyleSheet("QLineEdit { background: " + b + "; selection-background-color: rgb(233, 99, 0); }");

		//		color2Display->setStyleSheet("QLineEdit { background: " + mColor2.name() + "; selection-background-color: rgb(233, 99, 0); }");

		FLOAT4 color = FLOAT4(mColor2.redF(), mColor2.greenF(), mColor2.blueF(), mColor2.alphaF());
		particlesystem->SetProperty(PS_PROPERTY::PS_COLOR_2, &color);
		mCurrentPS.color2 = color;
	}
}

void MainContainer::emitterTypeChanged(int mode)
{
	mCurrentPS.emittertype = (EMITTER_TYPE)mode;
	
	if (mode == EMITTER_TYPE::EMIT_POINT)
	{
		rectangleWidget->setEnabled(false);
		BuildParticleSystem();
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

	mCurrentPS.textureType = mode;
	particlesystem->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mCurrentPS.textureType);
	graphics->RecompileShader(mCurrentPS.textureType, false, interpolateFrames->isChecked(), rotateParticles->isChecked());
}

void MainContainer::shaderCompileChanged(int useless)
{
	graphics->RecompileShader(mCurrentPS.textureType, noiseDissolve->isChecked(), interpolateFrames->isChecked(), rotateParticles->isChecked());
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

void MainContainer::BrowseTexture()
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
		mTexturePath = PathFindFileNameA(mTexturePath.toStdString().c_str());
	}
}

void MainContainer::BrowseNoiseTexture()
{
	mNoiseTexturePath = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png *.PNG *.dds *.DDS)"));

	if (mNoiseTexturePath != "")
	{

	}
}

void MainContainer::setMaxParticles()
{
	mCurrentPS.maxparticles = textFieldMaxParticles->text().toInt();
	BuildParticleSystem();
}

void MainContainer::BuildParticleSystem()
{
	EMITTER ps(mCurrentPS.emittertype, mCurrentPS.maxparticles,
		mCurrentPS.velocity, mCurrentPS.emissiondelay, mCurrentPS.lifetime, mCurrentPS.gravity,
		FLOAT4(mColor0.redF(), mColor0.greenF(), mColor0.blueF(), mColor0.alphaF()),
		FLOAT4(mColor1.redF(), mColor1.greenF(), mColor1.blueF(), mColor1.alphaF()),
		FLOAT4(mColor2.redF(), mColor2.greenF(), mColor2.blueF(), mColor2.alphaF()),
		mCurrentPS.startSizeX, mCurrentPS.startSizeY, mCurrentPS.endSizeX, mCurrentPS.endSizeY, mCurrentPS.rectSizeX, mCurrentPS.rectSizeZ,
		mCurrentPS.textureType, mCurrentPS.textureColumns, mCurrentPS.textureRows, mCurrentPS.looping);

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

void MainContainer::setLooping(int value)
{
	//TODO: UI controls for replaying a particle system
	//TODO: Multiple Emitters
	if (value == 2) value = 1;
	mCurrentPS.looping = value;
	BuildParticleSystem();
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

void MainContainer::FillValues(EMITTER fromCurrentPS)
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

	if (key == Qt::Key::Key_F)
	{
		graphics->UpdateOnce();
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

}
