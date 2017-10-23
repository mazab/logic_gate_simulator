#include "Includes.h"

//Constructor:
Pin::Pin()
{
	m_Status = LOW;	//Default Status is LOW
	m_thisComponent = NULL;
	m_Position = NULL;
	m_isConnected = false;
}
//==============================================================================================================
//Destructor:
Pin::~Pin()
{}
//==============================================================================================================
//setters:
void Pin::setComponent(Component* r_thisComponent)
{
	m_thisComponent = r_thisComponent;
}

void Pin::setStatus(STATUS r_Status)
{
	m_Status = r_Status;
}

void Pin::setPosition(Point* P)
{
	m_Position = P;
}

void Pin::setConn(bool r_isConnected)
{
	m_isConnected = r_isConnected;
}
//==============================================================================================================
//geters:
Component* Pin::getComponent()
{
	return m_thisComponent;
}

STATUS Pin::getStatus()
{
	return m_Status;
}

Point* Pin::getPosition()
{
	return m_Position;
}

bool Pin::getConn()
{
	return m_isConnected;
}

