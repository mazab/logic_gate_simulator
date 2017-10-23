#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
OR3::OR3()
	:Gate("OR_3", OR_3,"images\\OR3.jpg", 3){}

OR3::OR3(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("OR_3", OR_3, r_GfxInfo, r_ApplicationManager, "images\\OR3.jpg", 3)
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x;
	p1->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p1);

	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x + 4;
	p2->y = m_Current_GfxInfo.UpLeft.y + 27;
	m_InputPins[1]->setPosition(p2);

	Point* p3 = new Point;
	p3->x = m_Current_GfxInfo.UpLeft.x;
	p3->y = m_Current_GfxInfo.UpLeft.y + 37;
	m_InputPins[2]->setPosition(p3);
}
//==============================================================================================================
//Destructor:
OR3::~OR3()
{}

//==============================================================================================================
//Virtuals:
void OR3::Operate()
{
	if( (m_InputPins[0]->getStatus() == HIGH) || (m_InputPins[1]->getStatus() == HIGH) || (m_InputPins[2]->getStatus() == HIGH) )
		m_OutputPin->setStatus(HIGH);
	else
		m_OutputPin->setStatus(LOW);
}

void OR3::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool OR3::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void OR3::Load(ifstream& in)
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

void OR3::Save(ofstream& out)
{
	out<<"OR3"<<'\t';
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

void OR3::UpdatePinsGfxInfo()
{
	//The OutputPin:
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 71;
	p1->y = m_Current_GfxInfo.UpLeft.y + 26;
	m_OutputPin->setPosition(p1);

	//The InputPins:
	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x;
	p2->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p2);

	Point* p3 = new Point;
	p3->x = m_Current_GfxInfo.UpLeft.x + 4;
	p3->y = m_Current_GfxInfo.UpLeft.y + 27;
	m_InputPins[1]->setPosition(p3);

	Point* p4 = new Point;
	p4->x = m_Current_GfxInfo.UpLeft.x;
	p4->y = m_Current_GfxInfo.UpLeft.y + 37;
	m_InputPins[2]->setPosition(p4);
}
char* OR3::getUrl()
{
	return "images//OR3.jpg";
}

char* OR3::getIC()
{
	return "744075";
}
char* OR3::getType()
{
	return "OR_3";
}