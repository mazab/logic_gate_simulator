#include "Includes.h"

//Constructors:
UserDefined::UserDefined()
	:Gate("UserDefined", UserGate, NULL)
{ 
	m_Formula = NULL;
	m_InputsNames = NULL;
}

UserDefined::UserDefined(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager, char* r_Label, int r_Inputs, char* r_Formula)
	        :Gate(r_Label, UserGate, r_GfxInfo, r_ApplicationManager, NULL, r_Inputs)
{
	switch(r_Inputs)
	{
	case 2:
		{
			m_InputsNames = new char[2];
			m_InputsNames[0] = 'x';
			m_InputsNames[1] = 'y';
			break;
		}
	case 3:
		{
			m_InputsNames = new char[3];
			m_InputsNames[0] = 'x';
			m_InputsNames[1] = 'y';
			m_InputsNames[2] = 'z';
			break;
		}
	case 4:
		{
			m_InputsNames = new char[4];
			m_InputsNames[0] = 'x';
			m_InputsNames[1] = 'y';
			m_InputsNames[2] = 'z';
			m_InputsNames[3] = 'w';
			break;
		}
	}

	m_Formula = r_Formula;

	//set inputpins possitions:
	if(r_Inputs == 2)
	{
		Point p;
		p.x = m_Current_GfxInfo.UpLeft.x+1;
		p.y = m_Current_GfxInfo.UpLeft.y + 14;
		m_InputPins[0].setPosition(p);

		p.x = m_Current_GfxInfo.UpLeft.x + 1;
		p.y = m_Current_GfxInfo.UpLeft.y + 38;
		m_InputPins[1].setPosition(p);
	
	}

	else if(r_Inputs == 3)
	{
		Point p;
		p.x = m_Current_GfxInfo.UpLeft.x;
		p.y = m_Current_GfxInfo.UpLeft.y + 14;
		m_InputPins[0].setPosition(p);

		p.x = m_Current_GfxInfo.UpLeft.x;
		p.y = m_Current_GfxInfo.UpLeft.y + 27;
		m_InputPins[1].setPosition(p);

		p.x = m_Current_GfxInfo.UpLeft.x;
		p.y = m_Current_GfxInfo.UpLeft.y +37;
		m_InputPins[2].setPosition(p);

	}

	else // 4 inputs:
	{
		Point p;
		p.x = m_Current_GfxInfo.UpLeft.x;
		p.y = m_Current_GfxInfo.UpLeft.y + 16;
		m_InputPins[0].setPosition(p);

		p.x = m_Current_GfxInfo.UpLeft.x + 4;
		p.y = m_Current_GfxInfo.UpLeft.y + 23;
		m_InputPins[1].setPosition(p);

		p.x = m_Current_GfxInfo.UpLeft.x + 4;
		p.y = m_Current_GfxInfo.UpLeft.y + 31;
		m_InputPins[2].setPosition(p);

		p.x = m_Current_GfxInfo.UpLeft.x;
		p.y = m_Current_GfxInfo.UpLeft.y + 37;
		m_InputPins[3].setPosition(p);
	}
}
//==============================================================================================================
//Destructor:
UserDefined::~UserDefined()
{
}
//==============================================================================================================
//setters:
void UserDefined::createInputsNames(int i)
{
	m_Inputs = i;

	switch(i)
	{
	case 2:
		{
			m_InputsNames = new char[2];
			m_InputsNames[0] = 'x';
			m_InputsNames[1] = 'y';
			break;
		}
	case 3:
		{
			m_InputsNames = new char[3];
			m_InputsNames[0] = 'x';
			m_InputsNames[1] = 'y';
			m_InputsNames[2] = 'z';
			break;
		}
	case 4:
		{
			m_InputsNames = new char[4];
			m_InputsNames[0] = 'x';
			m_InputsNames[1] = 'y';
			m_InputsNames[2] = 'z';
			m_InputsNames[3] = 'w';
			break;
		}
	}

}

void UserDefined::setFormula(char* r_Formula)
{
	m_Formula = r_Formula;
}
//==============================================================================================================
//getters:
char* UserDefined::getFormula()
{
	return m_Formula;
}
//==============================================================================================================
//Virtuals:
