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
	//particlesystem = ps;
	graphics					= findChild<Graphics*>		("graphics",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldParticleInfo		= findChild<QLabel*>		("label_ParticleInfo",	Qt::FindChildOption::FindChildrenRecursively);
	textFieldLifetime			= findChild<QLineEdit*>		("lifetime",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityX			= findChild<QLineEdit*>		("velocityX",			Qt::FindChildOption::FindChildrenRecursively);
	velocityXSlider				= findChild<QSlider*>		("velocityXSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityY			= findChild<QLineEdit*>		("velocityY",			Qt::FindChildOption::FindChildrenRecursively);
	velocityYSlider				= findChild<QSlider*>		("velocityYSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldVelocityZ			= findChild<QLineEdit*>		("velocityZ",			Qt::FindChildOption::FindChildrenRecursively);
	velocityZSlider				= findChild<QSlider*>		("velocityZSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldRotation			= findChild<QLineEdit*>		("rotation",			Qt::FindChildOption::FindChildrenRecursively);
	rotationSlider				= findChild<QSlider*>		("rotationSlider",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldGravity			= findChild<QLineEdit*>		("gravity",				Qt::FindChildOption::FindChildrenRecursively);
	emissionDelaySlider			= findChild<QSlider*>		("emissionDelaySlider",	Qt::FindChildOption::FindChildrenRecursively);
	emissionDelaySlider_label	= findChild<QLabel*>		("label_EmDelaySlide",	Qt::FindChildOption::FindChildrenRecursively);
	browseBtn					= findChild<QPushButton*>	("browsepath",			Qt::FindChildOption::FindChildrenRecursively);
	saveBtn						= findChild<QPushButton*>	("savePS",				Qt::FindChildOption::FindChildrenRecursively);
	loadBtn						= findChild<QPushButton*>	("loadPS",				Qt::FindChildOption::FindChildrenRecursively);
	textFieldMaxParticles		= findChild<QLineEdit*>		("maxParticles",		Qt::FindChildOption::FindChildrenRecursively);
	textBrowser					= findChild<QTextBrowser*>	("textBrowser",			Qt::FindChildOption::FindChildrenRecursively);
	textBrowserNoise			= findChild<QTextBrowser*>	("textBrowserNoise",	Qt::FindChildOption::FindChildrenRecursively);
	color0Display				= findChild<QLineEdit*>		("color0Display",		Qt::FindChildOption::FindChildrenRecursively);
	color1Display				= findChild<QLineEdit*>		("color1Display",		Qt::FindChildOption::FindChildrenRecursively);
	color2Display				= findChild<QLineEdit*>		("color2Display",		Qt::FindChildOption::FindChildrenRecursively);
	emitterTypeDisplay			= findChild<QComboBox*>		("emitterTypeBox",		Qt::FindChildOption::FindChildrenRecursively);
	textureTypeBox				= findChild<QComboBox*>		("textureTypeBox",		Qt::FindChildOption::FindChildrenRecursively);
	textFieldStartSizeX			= findChild<QLineEdit*>		("startSizeX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldStartSizeY			= findChild<QLineEdit*>		("startSizeY",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldEndSizeX			= findChild<QLineEdit*>		("endSizeX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldEndSizeY			= findChild<QLineEdit*>		("endSizeY",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldRectSizeX			= findChild<QLineEdit*>		("rectSizeX",			Qt::FindChildOption::FindChildrenRecursively);
	textFieldRectSizeZ			= findChild<QLineEdit*>		("rectSizeZ",			Qt::FindChildOption::FindChildrenRecursively);
	rectangleWidget				= findChild<QWidget*>		("rectangleWidget",		Qt::FindChildOption::FindChildrenRecursively);
	spriteSheetWidget			= findChild<QWidget*>		("spriteSheetWidget",	Qt::FindChildOption::FindChildrenRecursively);
	textureView					= findChild<QLabel*>		("textureView",			Qt::FindChildOption::FindChildrenRecursively);
	textureViewNoise			= findChild<QLabel*>		("textureViewNoise",	Qt::FindChildOption::FindChildrenRecursively);
	spriteColumns				= findChild<QLineEdit*>		("spriteColumns",		Qt::FindChildOption::FindChildrenRecursively);
	spriteRows					= findChild<QLineEdit*>		("spriteRows",			Qt::FindChildOption::FindChildrenRecursively);
	psTabs						= findChild<QTabWidget*>	("psTabs",				Qt::FindChildOption::FindChildrenRecursively);
	interpolateFrames			= findChild<QCheckBox*>		("interpolateFrames",	Qt::FindChildOption::FindChildrenRecursively);
	noiseDissolve				= findChild<QCheckBox*>		("noiseDissolve",		Qt::FindChildOption::FindChildrenRecursively);
	bloomParticles				= findChild<QCheckBox*>		("bloomParticles",		Qt::FindChildOption::FindChildrenRecursively);
	loopingCheckBox				= findChild<QCheckBox*>		("looping",				Qt::FindChildOption::FindChildrenRecursively);
	textFieldEmissionDelay		= findChild<QLabel*>		("label_EmDelaySlide",	Qt::FindChildOption::FindChildrenRecursively);
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
	mCurrentPS.rotation = textFieldRotation->text().toFloat();

	char result[MAX_PATH];
	GetModuleFileNameA(NULL, result, MAX_PATH);
	PathRemoveFileSpecA(result);
	
	mTexturePath = QString(result).append("\\Data\\Textures\\plasmaball.png");
	textureView->setPixmap(mTexturePath);

	mTextureNoisePath = QString(result).append("\\Data\\Textures\\noise_cloud.png");
	textureViewNoise->setPixmap(mTextureNoisePath);

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
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_GRAVITY, &mCurrentPS.gravity);
}

void MainContainer::load()
{
	std::string loadPath = QFileDialog::getOpenFileName(this).toStdString();
	int textureNameSize = 0;
	int textureNoiseNameSize = 0;
	EMITTER ps;
	FILE* file = fopen(loadPath.c_str(), "rb");

	if (file != NULL)
	{
		// Read regular texture
		fread(&textureNameSize, sizeof(int), 1, file);
		std::string n(textureNameSize, '\0');
		fread(&n[0], sizeof(char), textureNameSize, file);

		// Read noise texture
		fread(&textureNoiseNameSize, sizeof(int), 1, file);
		std::string n_n(textureNoiseNameSize, '\0');
		fread(&n_n[0], sizeof(char), textureNoiseNameSize, file);

		fread(&ps, sizeof(EMITTER), 1, file);
		mCurrentPS = ps;

		mTexturePath = n.c_str();
		mTextureNoisePath = n_n.c_str();
		std::string tex_fullpath = Utility::Path() + "Data\\Textures\\" + mTexturePath.toStdString();
		std::string tex_noise_fullpath = Utility::Path() + "Data\\Textures\\" + mTextureNoisePath.toStdString();
		graphics->Retexture(TEXTURE_TYPE::TEXTURE,		 tex_fullpath);
		graphics->Retexture(TEXTURE_TYPE::TEXTURE_NOISE, tex_noise_fullpath);

		textureView->setPixmap(QString(tex_fullpath.c_str()));
		textureViewNoise->setPixmap(QString(tex_noise_fullpath.c_str()));

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

	// Safe check to make sure we didn't just refuse to enter a name and escaped
	if (exportPath == ".ps") { return; }

	EMITTER ps = mCurrentPS;

	FILE* file = fopen(exportPath.c_str(), "wb");
	if (file != NULL)
	{
		std::string texpath = PathFindFileNameA(mTexturePath.toStdString().c_str());
		std::string textpath_noise = PathFindFileNameA(mTextureNoisePath.toStdString().c_str());
		const char* tex = texpath.c_str();
		const char* tex_noise = textpath_noise.c_str();

		int texturenamesize = strlen(tex);
		int texture_noisenamesize = strlen(tex_noise);

		// First just write the size of the texture filename (imagine this is a header)
		fwrite(&texturenamesize, sizeof(int), 1, file);

		// ...then write the texture name
		fwrite(tex, sizeof(const char), texturenamesize, file);

		// Write size of noise texture filename
		fwrite(&texture_noisenamesize, sizeof(int), 1, file);

		// ...then write texture noise name
		fwrite(tex_noise, sizeof(const char), texture_noisenamesize, file);

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

	textFieldRotation->setText(QString::number(mCurrentPS.rotation));
	rotationSlider->setValue((int)(mCurrentPS.rotation));

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
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_COLOR_0, &mCurrentPS.color0);

	mColor1.setRgbF(mCurrentPS.color1.X, mCurrentPS.color1.Y, mCurrentPS.color1.Z, mCurrentPS.color1.W);
	color1Display->setStyleSheet("QLineEdit { background: " + mColor1.name() + "; selection-background-color: rgb(233, 99, 0); }");
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_COLOR_1, &mCurrentPS.color1);

	mColor2.setRgbF(mCurrentPS.color2.X, mCurrentPS.color2.Y, mCurrentPS.color2.Z, mCurrentPS.color2.W);
	color2Display->setStyleSheet("QLineEdit { background: " + mColor2.name() + "; selection-background-color: rgb(233, 99, 0); }");
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_COLOR_2, &mCurrentPS.color2);

	emitterTypeDisplay->setCurrentIndex(mCurrentPS.emittertype);

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mCurrentPS.startSizeX);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mCurrentPS.startSizeY);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_END_SIZE_X,   &mCurrentPS.endSizeX);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_END_SIZE_Y,	  &mCurrentPS.endSizeY);


	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mCurrentPS.emittertype);

	//emitterTypeChanged(mCurrentPS.emittertype);	
	
	textBrowser->setText(PathFindFileNameA(mTexturePath.toStdString().c_str()));
	textBrowserNoise->setText(PathFindFileNameA(mTextureNoisePath.toStdString().c_str()));

	noiseDissolve->setChecked(mCurrentPS.noiseDissolve);
	bloomParticles->setChecked(mCurrentPS.bloomParticles);
}

//TODO: World Space Checkbox
//TODO: Offset values & offset slider values & emitter gizmo position

void MainContainer::color0()
{
	QColor c = QColorDialog::getColor(mColor0, this, "Choose In Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid())
	{
		mColor0 = c;
		color0Display->setStyleSheet("QLineEdit { background: "+ mColor0.name()+"; selection-background-color: rgb(233, 99, 0); }");
		
		FLOAT4 color = FLOAT4(mColor0.redF(), mColor0.greenF(), mColor0.blueF(), mColor0.alphaF());
		graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_COLOR_0, &color);
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
		graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_COLOR_1, &color);
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
		graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_COLOR_2, &color);
		mCurrentPS.color2 = color;
	}
}

void MainContainer::emitterTypeChanged(int mode)
{
	mCurrentPS.emittertype = (EMITTER_TYPE)mode;
	
	if (mode == EMITTER_TYPE::EMIT_POINT)
	{
		rectangleWidget->setEnabled(false);
		//BuildParticleSystem();
	}
	if (mode == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		rectangleWidget->setEnabled(true);
		//BuildParticleSystem();
	}

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mCurrentPS.emittertype);
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
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mCurrentPS.textureType);
	graphics->RecompileShader(mCurrentPSIndex, mCurrentPS.textureType, false, interpolateFrames->isChecked());
}

void MainContainer::shaderCompileChanged(int useless)
{
	graphics->RecompileShader(mCurrentPSIndex, mCurrentPS.textureType, noiseDissolve->isChecked(), interpolateFrames->isChecked());

	mCurrentPS.noiseDissolve = noiseDissolve->isChecked();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_NOISE_DISSOLVE, &mCurrentPS.noiseDissolve);
}

void MainContainer::BloomParticles(int useless)
{
	//TODO: Setup blooming.
	//graphics->Bloom(bloomParticles->isChecked());

	mCurrentPS.bloomParticles = bloomParticles->isChecked();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_BLOOM_PARTICLES, &mCurrentPS.bloomParticles);

}

void MainContainer::startSizeX()
{
	mCurrentPS.startSizeX = textFieldStartSizeX->text().toFloat();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_START_SIZE_X, &mCurrentPS.startSizeX);
}

void MainContainer::startSizeY()
{
	mCurrentPS.startSizeY = textFieldStartSizeY->text().toFloat();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_START_SIZE_Y, &mCurrentPS.startSizeY);
}

void MainContainer::endSizeX()
{
	mCurrentPS.endSizeX = textFieldEndSizeX->text().toFloat();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_END_SIZE_X, &mCurrentPS.endSizeX);
}

void MainContainer::endSizeY()
{
	mCurrentPS.endSizeY = textFieldEndSizeY->text().toFloat();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_END_SIZE_Y, &mCurrentPS.endSizeY);
}

void MainContainer::rectResize()
{
	mCurrentPS.rectSizeX = textFieldRectSizeX->text().toFloat();
	mCurrentPS.rectSizeZ = textFieldRectSizeZ->text().toFloat();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_RECT_SIZE_X, &mCurrentPS.rectSizeX);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_RECT_SIZE_Z, &mCurrentPS.rectSizeZ);
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
		graphics->Retexture(TEXTURE_TYPE::TEXTURE, mTexturePath.toStdString());
		mTexturePath = PathFindFileNameA(mTexturePath.toStdString().c_str());
	}
}

void MainContainer::BrowseTextureNoise()
{
	mTextureNoisePath = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "", tr("Image Files (*.png *.PNG *.dds *.DDS)"));

	if (mTextureNoisePath != "")
	{
		textBrowserNoise->setPlainText(PathFindFileNameA(mTextureNoisePath.toStdString().c_str()));
		if (mTextureNoisePath.contains(".DDS") || mTextureNoisePath.contains(".dds"))
		{
			textureViewNoise->setPixmap(QString(DEFAULT_DDS_TEXTUREPATH));
		}
		else
		{
			textureViewNoise->setPixmap(mTextureNoisePath);
		}
		graphics->Retexture(TEXTURE_TYPE::TEXTURE_NOISE, mTextureNoisePath.toStdString());
		mTextureNoisePath = PathFindFileNameA(mTextureNoisePath.toStdString().c_str());
	}
}

void MainContainer::setMaxParticles()
{
	mCurrentPS.maxparticles = textFieldMaxParticles->text().toInt();
	BuildParticleSystem();
}

void MainContainer::BuildParticleSystem()
{
	//TODO: Try using just graphics->Rebuild(mCurrentPS);. Not sure if that will work, but would be smooth.
	EMITTER ps(mCurrentPS.emittertype, mCurrentPS.maxparticles,
		mCurrentPS.velocity, mCurrentPS.emissiondelay, mCurrentPS.lifetime, mCurrentPS.gravity,
		FLOAT4(mColor0.redF(), mColor0.greenF(), mColor0.blueF(), mColor0.alphaF()),
		FLOAT4(mColor1.redF(), mColor1.greenF(), mColor1.blueF(), mColor1.alphaF()),
		FLOAT4(mColor2.redF(), mColor2.greenF(), mColor2.blueF(), mColor2.alphaF()),
		mCurrentPS.startSizeX, mCurrentPS.startSizeY, mCurrentPS.endSizeX, mCurrentPS.endSizeY, mCurrentPS.rectSizeX, mCurrentPS.rectSizeZ, mCurrentPS.rotation,
		mCurrentPS.textureType, mCurrentPS.textureColumns, mCurrentPS.textureRows, mCurrentPS.looping, mCurrentPS.noiseDissolve, mCurrentPS.bloomParticles);

	graphics->Rebuild(mCurrentPSIndex, ps);
}


void MainContainer::setVelocityX()
{
	float x = textFieldVelocityX->text().toFloat();

	mCurrentPS.velocity.X = x;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);

}

void MainContainer::setVelocityY()
{
	float y = textFieldVelocityY->text().toFloat();

	mCurrentPS.velocity.Y = y;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);

}

void MainContainer::setVelocityZ()
{
	float z = textFieldVelocityZ->text().toFloat();
	
	mCurrentPS.velocity.Z = z;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setEmissionDelay(int value)
{
	int a = emissionDelaySlider->value();
	mCurrentPS.emissiondelay = a / 100.0f;
	emissionDelaySlider_label->setText(QString::number(mCurrentPS.emissiondelay, 'f', 2));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_EMISSIONDELAY, &mCurrentPS.emissiondelay);
}

void MainContainer::setVelocityXSlider(int value)
{
	int a = velocityXSlider->value();
	mCurrentPS.velocity.X = a;
	textFieldVelocityX->setText(QString::number(mCurrentPS.velocity.X, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setVelocityYSlider(int value)
{
	int a = velocityYSlider->value();
	mCurrentPS.velocity.Y = a;
	textFieldVelocityY->setText(QString::number(mCurrentPS.velocity.Y, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::setVelocityZSlider(int value)
{
	int a = velocityZSlider->value();
	mCurrentPS.velocity.Z = a;
	textFieldVelocityZ->setText(QString::number(mCurrentPS.velocity.Z, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_VELOCITY, &mCurrentPS.velocity);
}

void MainContainer::SetRotation()
{
	float r = textFieldRotation->text().toFloat();

	mCurrentPS.rotation = r;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_ROTATION, &mCurrentPS.rotation);
}

void MainContainer::SetRotationSlider(int value)
{
	int a = rotationSlider->value();
	mCurrentPS.rotation = a;
	textFieldRotation->setText(QString::number(mCurrentPS.rotation, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_ROTATION, &mCurrentPS.rotation);
}

void MainContainer::setLifetime()
{
	mCurrentPS.lifetime = textFieldLifetime->text().toFloat();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_LIFETIME, &mCurrentPS.lifetime);
}

void MainContainer::setColumnsRows()
{
	mCurrentPS.textureColumns = abs(spriteColumns->text().toInt());
	mCurrentPS.textureRows = abs(spriteRows->text().toInt());

	spriteColumns->setText(QString::number(mCurrentPS.textureColumns));
	spriteRows->setText(QString::number(mCurrentPS.textureRows));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_TEXTURE_COLUMNS, &mCurrentPS.textureColumns);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_TEXTURE_ROWS,	 &mCurrentPS.textureRows);
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
		mCurrentPS = graphics->EmitterByIndex(mCurrentPSIndex);
		FillValues(mCurrentPS);
		graphics->CurrentEmitterIndex(mCurrentPSIndex);
	}
}

void MainContainer::addTab(int index)
{
	int max = psTabs->count()-1;
	if (index == max && max < 4)
	{
		//psTabs->addTab(new QWidget(this), QString("Emitter %0").arg(max + 1));
		psTabs->insertTab(index, new QWidget(this), QString("Emitter %0").arg(max + 1));
		graphics->AddParticleSystem(index, mCurrentPS);
	}
}

void MainContainer::removeTab(int index)
{
	int max = psTabs->count() - 1;
	if (index != max && max > 1)
	{
		psTabs->removeTab(index);
		graphics->RemoveParticleSystem(index);

		int newindex = index;
		if (index != 0) { newindex -= 1; }
		psTabs->setCurrentIndex(newindex);
		selectTab(newindex);

		graphics->CurrentEmitterIndex(newindex);
	}
}

void MainContainer::RenameTab(int index)
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Change Emitter Name"),
		tr("Emitter name:"), QLineEdit::Normal,
		"Emitter", &ok);

	if (ok == true && text.isEmpty() == false)
	{
		psTabs->setTabText(index, text);

	}



}

void MainContainer::FillValues(EMITTER fromCurrentPS)
{
	mCurrentPS = fromCurrentPS;

	// TODO: Fill UI pointers with values...
	// Actually just make an UpdateUI() function which fills UI pointers with mCurrentPS values.
	SetUiElements();
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
