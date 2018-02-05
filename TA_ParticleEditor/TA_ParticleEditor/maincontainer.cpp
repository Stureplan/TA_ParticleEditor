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
	textFieldOffsetX			= findChild<QLineEdit*>		("offsetX",				Qt::FindChildOption::FindChildrenRecursively);
	textFieldOffsetY			= findChild<QLineEdit*>		("offsetY",				Qt::FindChildOption::FindChildrenRecursively);
	textFieldOffsetZ			= findChild<QLineEdit*>		("offsetZ",				Qt::FindChildOption::FindChildrenRecursively);
	offsetXSlider				= findChild<QSlider*>		("offsetXSlider",		Qt::FindChildOption::FindChildrenRecursively);
	offsetYSlider				= findChild<QSlider*>		("offsetYSlider",		Qt::FindChildOption::FindChildrenRecursively);
	offsetZSlider				= findChild<QSlider*>		("offsetZSlider",		Qt::FindChildOption::FindChildrenRecursively);
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

void MainContainer::Initialize()
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

	mCurrentPS.offset = FLOAT3(0);
	textFieldOffsetX->setPlaceholderText(std::to_string(mCurrentPS.offset.X).c_str());
	textFieldOffsetY->setPlaceholderText(std::to_string(mCurrentPS.offset.Y).c_str());
	textFieldOffsetZ->setPlaceholderText(std::to_string(mCurrentPS.offset.Z).c_str());


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
	
	QString tex = QString(result).append("\\Data\\Textures\\plasmaball.dds");
	textureView->setPixmap(tex);

	QString tex_n = QString(result).append("\\Data\\Textures\\noise_cloud.dds");
	textureViewNoise->setPixmap(tex_n);

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
	EMITTER ps;
	FILE* file = fopen(loadPath.c_str(), "rb");

	if (file != NULL)
	{
		//TODO HERE: Remove/empty all the stuff in Graphics and MainContainer,
		//every old particlesystem and emitter should be emptied to prepare
		//for the incoming file details.
		ClearValues();
		ClearUI();


		int amount_of_emitters = -1;
		fread(&amount_of_emitters, sizeof(int), 1, file);

		for (int i = 0; i < amount_of_emitters; i++)
		{
			int texture_particle_size = -1;
			int texture_noise_size = -1;

			fread(&texture_particle_size, sizeof(int), 1, file);
			std::string t(texture_particle_size, '\0');
			fread(&t[0], sizeof(char), texture_particle_size, file);

			fread(&texture_noise_size, sizeof(int), 1, file);
			std::string n(texture_noise_size, '\0');
			fread(&n[0], sizeof(char), texture_noise_size, file);

			EMITTER e;
			fread(&e, sizeof(EMITTER), 1, file);

			if (i == 0)
			{
				ps = e;
			}


			//add particle system
			psTabs->insertTab(i, new QWidget(this), QString("Emitter %0").arg(i+1));
			graphics->AddParticleSystem(i, e);


			char result[MAX_PATH];
			GetModuleFileNameA(NULL, result, MAX_PATH);
			PathRemoveFileSpecA(result);
			std::string dir = result;
			dir.append("\\Data\\Textures\\");

			graphics->Retexture(i, TEXTURE_TYPE::TEXTURE, dir+t);
			graphics->Retexture(i, TEXTURE_TYPE::TEXTURE_NOISE, dir+n);


			mCurrentPS = e;
			psTabs->setCurrentIndex(i);
			SetUiElements();
		}

		mCurrentPS = ps;
		psTabs->setCurrentIndex(0);
		
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

	FILE* file = fopen(exportPath.c_str(), "wb");
	if (file != NULL)
	{
		//====================================
		//		FILE STRUCTURE			    //
		//====================================
		//								    //
		//	(int)amount of emitters			//
		//	for...							//
		//		(int)texture_size			//
		//		(char*)texture_string		//
		//		(int)texture_noise_size		//
		//		(char*)texture_noise_string	//
		//		(EMITTER)emitter			//
		//								    //
		//====================================

		int amount_of_emitters = graphics->EmitterCount();
		fwrite(&amount_of_emitters, sizeof(int), 1, file);

		for (int i = 0; i < amount_of_emitters; i++)
		{
			std::string t = graphics->ParticleSystemByIndex(i)->TextureParticlePath();
			std::string n = graphics->ParticleSystemByIndex(i)->TextureNoisePath();

			const char* texture_particle = t.c_str();
			const char* texture_noise	 = n.c_str();

			int texture_particle_size	= strlen(texture_particle);
			int texture_noise_size		= strlen(texture_noise);

			fwrite(&texture_particle_size, sizeof(int), 1, file);
			fwrite(texture_particle, sizeof(const char), texture_particle_size, file);

			fwrite(&texture_noise_size, sizeof(int), 1, file);
			fwrite(texture_noise, sizeof(const char), texture_noise_size, file);

			EMITTER e = graphics->EmitterByIndex(i);
			if (e.looping == true)
			{
				e.maxparticles = (int)(e.lifetime / e.emissiondelay) + 1;
			}
			fwrite(&e, sizeof(EMITTER), 1, file);
		}

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
	velocityXSlider->setSliderPosition(mCurrentPS.velocity.X);
	velocityYSlider->setSliderPosition(mCurrentPS.velocity.Y);
	velocityZSlider->setSliderPosition(mCurrentPS.velocity.Z);
	textFieldVelocityX->setText(QString::number(mCurrentPS.velocity.X));
	textFieldVelocityY->setText(QString::number(mCurrentPS.velocity.Y));
	textFieldVelocityZ->setText(QString::number(mCurrentPS.velocity.Z));

	offsetXSlider->setSliderPosition(mCurrentPS.offset.X * 10);
	offsetYSlider->setSliderPosition(mCurrentPS.offset.Y * 10);
	offsetZSlider->setSliderPosition(mCurrentPS.offset.Z * 10);
	textFieldOffsetX->setText(QString::number(mCurrentPS.offset.X));
	textFieldOffsetY->setText(QString::number(mCurrentPS.offset.Y));
	textFieldOffsetZ->setText(QString::number(mCurrentPS.offset.Z));

	textFieldRotation->setText(QString::number(mCurrentPS.rotation));
	rotationSlider->setValue((int)(mCurrentPS.rotation*10));

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
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_END_SIZE_Y,	&mCurrentPS.endSizeY);


	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mCurrentPS.emittertype);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_SHADER, &mCurrentPS.shader);
	shaderCompileChanged(0);

	//emitterTypeChanged(mCurrentPS.emittertype);	
	spriteColumns	->setText(QString::number(mCurrentPS.textureColumns));
	spriteRows		->setText(QString::number(mCurrentPS.textureRows));
	textureTypeBox	->setCurrentIndex(mCurrentPS.textureType);
	textureTypeChanged(mCurrentPS.textureType);

	setColumnsRows();
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mCurrentPS.textureType);


	
	std::string tex = graphics->ParticleSystemByIndex(mCurrentPSIndex)->TextureParticlePath();
	textBrowser		->setText(tex.c_str());
	tex.insert(0, Utility::Path() + "Data\\Textures\\");
	textureView->setPixmap(QString(tex.c_str()));

	std::string tex_n = graphics->ParticleSystemByIndex(mCurrentPSIndex)->TextureNoisePath();
	textBrowserNoise->setText(tex_n.c_str());
	tex_n.insert(0, Utility::Path() + "Data\\Textures\\");
	textureViewNoise->setPixmap(QString(tex_n.c_str()));

	noiseDissolve->setChecked(mCurrentPS.noiseDissolve);
	bloomParticles->setChecked(mCurrentPS.bloomParticles);
	interpolateFrames->setChecked(mCurrentPS.interpolation);
}

//TODO: World Space Checkbox

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

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_SHADER, &mCurrentPS.shader);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_EMITTER_TYPE, &mCurrentPS.emittertype);
}

void MainContainer::textureTypeChanged(int mode)
{
	if (mode == 0)
	{
		// Single texture
		spriteSheetWidget->setEnabled(false);

		if (noiseDissolve->isChecked() == false)
		{
			mCurrentPS.shader = 0;
		}
		else
		{
			mCurrentPS.shader = 2;
		}
	}
	if (mode == 1)
	{
		// Texture sheet
		spriteSheetWidget->setEnabled(true);
		setColumnsRows();

		if (noiseDissolve->isChecked() == false)
		{
			mCurrentPS.shader = 1;
		}
		else
		{
			mCurrentPS.shader = 3;
		}
	}
	
	mCurrentPS.textureType = mode;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_SHADER, &mCurrentPS.shader);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_TEXTURE_TYPE, &mCurrentPS.textureType);
	graphics->RecompileShader(mCurrentPSIndex, mCurrentPS.textureType, noiseDissolve->isChecked(), mCurrentPS.shader);
}

void MainContainer::shaderCompileChanged(int useless)
{
	mCurrentPS.noiseDissolve = noiseDissolve->isChecked();
	mCurrentPS.interpolation = interpolateFrames->isChecked();

	if (mCurrentPS.textureType == 0 && mCurrentPS.noiseDissolve == 0)
	{
		mCurrentPS.shader = 0;
	}
	if (mCurrentPS.textureType == 1 && mCurrentPS.noiseDissolve == 0)
	{
		mCurrentPS.shader = 1;
	}
	if (mCurrentPS.textureType == 0 && mCurrentPS.noiseDissolve == 1)
	{
		mCurrentPS.shader = 2;
	}
	if (mCurrentPS.textureType == 1 && mCurrentPS.noiseDissolve == 1)
	{
		mCurrentPS.shader = 3;
	}

	graphics->RecompileShader(mCurrentPSIndex, mCurrentPS.textureType, mCurrentPS.noiseDissolve, mCurrentPS.shader);

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_SHADER, &mCurrentPS.shader);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_NOISE_DISSOLVE, &mCurrentPS.noiseDissolve);
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_INTERPOLATION, &mCurrentPS.interpolation);
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
	char result[MAX_PATH];
	GetModuleFileNameA(NULL, result, MAX_PATH);
	PathRemoveFileSpecA(result);
	std::string dir = result;
	dir.append("\\Data\\Textures");

	QString tex = QFileDialog::getOpenFileName(this,
		tr("Open Image"),dir.c_str(), tr("Image Files (*.png *.PNG *.dds *.DDS)"));

	if (tex != "")
	{
		textBrowser->setPlainText(PathFindFileNameA(tex.toStdString().c_str()));
		if (tex.contains(".DDS") || tex.contains(".dds"))
		{
			textureView->setPixmap(QString(DEFAULT_DDS_TEXTUREPATH));
		}
		else
		{
			textureView->setPixmap(tex);
		}

		graphics->Retexture(mCurrentPSIndex, TEXTURE_TYPE::TEXTURE, tex.toStdString());
		//mTexturePath = PathFindFileNameA(mTexturePath.toStdString().c_str());
	}
}

void MainContainer::BrowseTextureNoise()
{
	char result[MAX_PATH];
	GetModuleFileNameA(NULL, result, MAX_PATH);
	PathRemoveFileSpecA(result);
	std::string dir = result;
	dir.append("\\Data\\Textures");

	QString tex = QFileDialog::getOpenFileName(this,
		tr("Open Image"), dir.c_str(), tr("Image Files (*.png *.PNG *.dds *.DDS)"));

	if (tex != "")
	{
		textBrowserNoise->setPlainText(PathFindFileNameA(tex.toStdString().c_str()));
		if (tex.contains(".DDS") || tex.contains(".dds"))
		{
			textureViewNoise->setPixmap(QString(DEFAULT_DDS_TEXTUREPATH));
		}
		else
		{
			textureViewNoise->setPixmap(tex);
		}
		graphics->Retexture(mCurrentPSIndex, TEXTURE_TYPE::TEXTURE_NOISE, tex.toStdString());
		//mTextureNoisePath = PathFindFileNameA(mTextureNoisePath.toStdString().c_str());
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
		mCurrentPS.interpolation, mCurrentPS.textureType, mCurrentPS.textureColumns, mCurrentPS.textureRows, mCurrentPS.looping, mCurrentPS.noiseDissolve, mCurrentPS.bloomParticles);

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

void MainContainer::SetOffsetX()
{
	float x = textFieldOffsetX->text().toFloat();

	mCurrentPS.offset.X = x;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_OFFSET, &mCurrentPS.offset);
}

void MainContainer::SetOffsetY()
{
	float y = textFieldOffsetY->text().toFloat();

	mCurrentPS.offset.Y = y;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_OFFSET, &mCurrentPS.offset);
}

void MainContainer::SetOffsetZ()
{
	float z = textFieldOffsetZ->text().toFloat();

	mCurrentPS.offset.Z = z;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_OFFSET, &mCurrentPS.offset);
}

void MainContainer::SetOffsetXSlider(int value)
{
	int x = offsetXSlider->value();
	mCurrentPS.offset.X = (float)(x*0.1f);
	textFieldOffsetX->setText(QString::number(mCurrentPS.offset.X, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_OFFSET, &mCurrentPS.offset);
}

void MainContainer::SetOffsetYSlider(int value)
{
	int y = offsetYSlider->value();
	mCurrentPS.offset.Y = (float)(y*0.1f);
	textFieldOffsetY->setText(QString::number(mCurrentPS.offset.Y, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_OFFSET, &mCurrentPS.offset);

}

void MainContainer::SetOffsetZSlider(int value)
{
	int z = offsetZSlider->value();
	mCurrentPS.offset.Z = (float)(z*0.1f);
	textFieldOffsetZ->setText(QString::number(mCurrentPS.offset.Z, 'f', 1));

	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_OFFSET, &mCurrentPS.offset);
}

void MainContainer::SetRotation()
{
	float r = textFieldRotation->text().toFloat();

	rotationSlider->setValue((int)(mCurrentPS.rotation * 10));


	mCurrentPS.rotation = r;
	graphics->ParticleSystemByIndex(mCurrentPSIndex)->SetProperty(PS_PROPERTY::PS_ROTATION, &mCurrentPS.rotation);
}

void MainContainer::SetRotationSlider(int value)
{
	int r = rotationSlider->value();
	mCurrentPS.rotation = (float)(r*0.1f);
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
		FillValues();
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

void MainContainer::ClearValues()
{
	graphics->ClearParticleSystems();
	mCurrentPSIndex = 0;
	mCurrentPS = EMITTER();


}

void MainContainer::ClearUI()
{
	int count = psTabs->count();
	for (int i = 0; i < count; i++)
	{
		psTabs->removeTab(i);
	}
}

void MainContainer::FillValues()
{
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
