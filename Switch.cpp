#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
Switch::Switch()
	   :Component("SWITCH", SWITCH)
{
	m_URL_ON = "images//SWITCH_ON.jpg";
	m_URL_OFF = "images//SWITCH_OFF.jpg";

	m_Pin = new OutputPin;
	m_Pin->setComponent(this);
}

Switch::Switch(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	   :Component("SWITCH", SWITCH, r_GfxInfo, r_ApplicationManager)
{
	m_URL_ON = "images//SWITCH_ON.jpg";
	m_URL_OFF = "images//SWITCH_OFF.jpg";
	
	m_Pin = new OutputPin;
	m_Pin->setComponent(this);

	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 55;
	p1->y = m_Current_GfxInfo.UpLeft.y + 25;
	m_Pin->setPosition(p1);
}
//==============================================================================================================
//Destructor:
Switch::~Switch()
{
	delete [] m_URL_ON;
	delete [] m_URL_OFF;
}
//==============================================================================================================
//Getters:
OutputPin* Switch::getPin()
{
	return  m_Pin;
}


//==============================================================================================================
//Virtuals!:
void Switch::Load(ifstream& in)
{
	string r_Label ;
	in>>m_ID;
	in>>r_Label;
	m_Current_Label = new char[r_Label.length()+1] ;
	strcpy(m_Current_Label , r_Label.c_str()) ;
	in>>m_Current_GfxInfo.Center.x;
	in>>m_Current_GfxInfo.Center.y;

	//----------------------
	//calculating the UpLeft and DownRight points
	//----------------------
	
	m_Current_GfxInfo.UpLeft.x = m_Current_GfxInfo.Center.x -(int)(0.5*75);
	m_Current_GfxInfo.UpLeft.y = m_Current_GfxInfo.Center.y -(int)(0.5*50);

	m_Current_GfxInfo.DownRight.x = m_Current_GfxInfo.Center.x +(int)(0.5*75);
	m_Current_GfxInfo.DownRight.y = m_Current_GfxInfo.Center.y +(int)(0.5*50);
}

void Switch::Save(ofstream& out)
{
	out<<"SWITCH"<<'\t';
	out<<m_ID<<'\t';

	if(m_Current_Label == "")
	{
		out<<"$"<<'\t';
	}
	else
	{
		out<<m_Current_Label<<'\t';
	}

	out<<m_Current_GfxInfo.Center.x<<'\t';

	out<<m_Current_GfxInfo.Center.y<<'\t'<<endl;
}

void Switch::Operate()
{
	if(m_Pin->getStatus() == LOW)
		m_Pin->setStatus(HIGH);
	else
		m_Pin->setStatus(LOW);
}

void Switch::Draw()
{
	if(m_Pin->getStatus() == LOW)
		m_ApplicationManager->getOutput()->drawComponent(m_URL_OFF , m_Current_Label, m_Current_GfxInfo.UpLeft);
	else
		m_ApplicationManager->getOutput()->drawComponent(m_URL_ON , m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool Switch::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void Switch::UpdatePinsGfxInfo()
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 55;
	p1->y = m_Current_GfxInfo.UpLeft.y + 25;
	m_Pin->setPosition(p1);
}
//==============================================================================================================
//Setter:
bool Switch::ConnectTo(InputPin* In)
{
	return m_Pin->ConnectTo(In);
}

//===============================================
char* Switch::getUrl()
{
	return m_URL_OFF;
}

char* Switch::getIC()
{
	return "-------";
}
char* Switch::getType()
{
	return "OR_4";
}