#include "Includes.h"

//initializing the static counter:
int Component::ID_Generator = 0;
//==============================================================================================================
//Constructor:
Component::Component(char* r_Label, ComponentType r_Name, const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
{
	m_Level = -1;
	Moving = false;
	m_ID = ++ID_Generator;
	m_Current_Label = r_Label;
	m_Old_Label = r_Label;
	m_Name = r_Name;
	m_ApplicationManager = r_ApplicationManager;
	m_Current_GfxInfo = r_GfxInfo;
	m_Old_GfxInfo = r_GfxInfo;
}

Component::Component(char* r_Label, ComponentType r_Name)
{
	m_Level = -1;
	Moving = false;
	m_ID = ++ID_Generator;
	m_Current_Label = r_Label;
	m_Old_Label = r_Label;
	m_Name = r_Name;

	m_ApplicationManager = NULL;
}
//==============================================================================================================
//Destructor:
Component::~Component()
{
	delete [] m_Current_Label;
	delete [] m_Old_Label;
	m_Current_Label = NULL;
	m_Old_Label = NULL;
}
//==============================================================================================================
//Setters:
void Component::changeMovingStatus()
{
	Moving = (Moving == true)? false : true;
}

void Component::setApplicationManager(ApplicationManager * r_ApplicationManager)
{
	m_ApplicationManager = r_ApplicationManager;
}

void Component::setCurrentGfxInfo(const GraphicsInfo & r_GfxInfo)
{
	m_Current_GfxInfo = r_GfxInfo;
}

void Component::setOldGfxInfo(const GraphicsInfo & r_GfxInfo)
{
	m_Old_GfxInfo = r_GfxInfo;
}

void Component::setCurrentLabel(char* r_Label)
{
	m_Current_Label = r_Label;
}

void Component::setOldLabel(char* r_Label)
{
	m_Old_Label = r_Label;
}

void Component::setLevel(int l)
{
	m_Level = l;
}
//==============================================================================================================
//Getters:
bool Component::isMoving()
{
	return Moving;
}

int Component::getIDGenerator()
{
	return ID_Generator;
}

int Component::getID()
{
	return m_ID;
}

GraphicsInfo Component::getCurrentGfxInfo()
{
	return m_Current_GfxInfo;
}

GraphicsInfo Component::getOldGfxInfo()
{
	return m_Old_GfxInfo;
}

char* Component::getCurrentLabel()
{
	return m_Current_Label;
}

char* Component::getOldLabel()
{
	return m_Old_Label;
}

 ComponentType Component::getName()
{
	return m_Name;
}

 int Component::getLevel()
 {
	 return m_Level;
 }





