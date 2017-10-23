#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
Led::Led(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	   :Component("LED", LED, r_GfxInfo, r_ApplicationManager)
{
	m_URL_ON = "images//LED_ON.jpg";
	m_URL_OFF = "images//LED_OFF.jpg";

	m_Pin = new InputPin;
	m_Pin->setComponent(this);
	
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 29;
	p1->y = m_Current_GfxInfo.UpLeft.y + 47;
	m_Pin->setPosition(p1);
}

Led::Led()
	:Component("LED",LED)
{
	m_URL_ON = "images//LED_ON.jpg";
	m_URL_OFF = "images//LED_OFF.jpg";

	m_Pin = new InputPin;
	m_Pin->setComponent(this);

}
//==============================================================================================================
//Destructor:
Led::~Led()
{
	delete [] m_URL_ON;
	delete [] m_URL_OFF;
}
//==============================================================================================================
//Getters:
InputPin* Led::getPin()
{
	return  m_Pin;
}

char* Led::getUrl()
{
	return m_URL_OFF;
}

char* Led::getIC()
{ 
	return NULL;
}

char* Led::getType()
{
	return "LED";
}
//==============================================================================================================
//setter:
bool Led::connectTo(OutputPin* r_Out)
{
	if(m_Pin->getConn())
		return false;
	else
	{
		m_Pin->setOutputPin(r_Out);
		m_Pin->setConn(true);
		return true;
	}

}
//==============================================================================================================
//Virtuals!:
void Led::Load(ifstream& in)
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

void Led::Save(ofstream& out)
{
	out<<"LED"<<'\t';
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

void Led::Operate()
{
}

void Led::Draw()
{
	if(m_Pin->getStatus() == LOW)
		m_ApplicationManager->getOutput()->drawComponent(m_URL_OFF , m_Current_Label, m_Current_GfxInfo.UpLeft);
	else
		m_ApplicationManager->getOutput()->drawComponent(m_URL_ON , m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool Led::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void Led::UpdatePinsGfxInfo()
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 29;
	p1->y = m_Current_GfxInfo.UpLeft.y + 47;
	m_Pin->setPosition(p1);
}