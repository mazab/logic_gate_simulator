#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
OR4::OR4()
	:Gate("OR_4", OR_4,"images\\OR4.jpg", 4){}

OR4::OR4(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("OR_4", OR_4, r_GfxInfo, r_ApplicationManager, "images\\OR4.jpg", 4)
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x;
	p1->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p1);

	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x + 6;
	p2->y = m_Current_GfxInfo.UpLeft.y + 22;
	m_InputPins[1]->setPosition(p2);

	Point* p3 = new Point;
	p3->x = m_Current_GfxInfo.UpLeft.x + 6;
	p3->y = m_Current_GfxInfo.UpLeft.y + 30;
	m_InputPins[2]->setPosition(p3);

	Point* p4 = new Point;
	p4->x = m_Current_GfxInfo.UpLeft.x;
	p4->y = m_Current_GfxInfo.UpLeft.y + 39;
	m_InputPins[3]->setPosition(p4);
}
//==============================================================================================================
//Destructor:
OR4::~OR4()
{}

//==============================================================================================================
//Virtuals:
void OR4::Operate()
{
	if( (m_InputPins[0]->getStatus() == HIGH) || (m_InputPins[1]->getStatus() == HIGH) || (m_InputPins[2]->getStatus() == HIGH) || (m_InputPins[3]->getStatus() == HIGH) )
		m_OutputPin->setStatus(HIGH);
	else
		m_OutputPin->setStatus(LOW);
}

void OR4::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool OR4::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void OR4::Load(ifstream& in)
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

void OR4::Save(ofstream& out)
{
	out<<"OR4"<<'\t';
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

void OR4::UpdatePinsGfxInfo()
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
	p3->x = m_Current_GfxInfo.UpLeft.x + 6;
	p3->y = m_Current_GfxInfo.UpLeft.y + 22;
	m_InputPins[1]->setPosition(p3);

	Point* p4 = new Point;
	p4->x = m_Current_GfxInfo.UpLeft.x + 6;
	p4->y = m_Current_GfxInfo.UpLeft.y + 30;
	m_InputPins[2]->setPosition(p4);

	Point* p5 = new Point;
	p5->x = m_Current_GfxInfo.UpLeft.x;
	p5->y = m_Current_GfxInfo.UpLeft.y + 39;
	m_InputPins[3]->setPosition(p5);
}
char* OR4::getUrl()
{
	return "images//OR4.jpg";
}

char* OR4::getIC()
{
	return "-------";
}
char* OR4::getType()
{
	return "OR_4";
}