#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QCoreApplication>

class MainContainer : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(MainContainer)

public:
	MainContainer(QWidget* parent = Q_NULLPTR);
	~MainContainer();

protected:
	virtual void keyPressEvent(QKeyEvent* evt);

private:
	
};