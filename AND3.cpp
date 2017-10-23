#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
AND3::AND3()
	:Gate("AND_3", AND_3,"images\\AND3.jpg" ,3){}

AND3::AND3(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("AND_3", AND_3, r_GfxInfo, r_ApplicationManager, "images\\AND3.jpg", 3)
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x;
	p1->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p1);

	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x;
	p2->y = m_Current_GfxInfo.UpLeft.y + 27;
	m_InputPins[1]->setPosition(p2);

	Point* p3 = new Point ;
	p3->x = m_Current_GfxInfo.UpLeft.x;
	p3->y = m_Current_GfxInfo.UpLeft.y + 37;
	m_InputPins[2]->setPosition(p3);
}
//==============================================================================================================
//Destructor:
AND3::~AND3()
{}

//==============================================================================================================
//Virtuals:
void AND3::Operate()
{
	if( (m_InputPins[0]->getStatus() == LOW) || (m_InputPins[1]->getStatus() == LOW) || (m_InputPins[2]->getStatus() == LOW) )
		m_OutputPin->setStatus(LOW);
	else
		m_OutputPin->setStatus(HIGH);
}

void AND3::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool AND3::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void AND3::Load(ifstream& in)
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

void AND3::Save(ofstream& out)
{
	out<<"AND3"<<'\t';
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

void AND3::UpdatePinsGfxInfo()
{
	//The OutputPin:
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 71;
	p1->y = m_Current_GfxInfo.UpLeft.y + 26;
	m_OutputPin->setPosition(p1);

	//The InputPins:
	Point* p2 = new Point ;
	p2->x = m_Current_GfxInfo.UpLeft.x;
	p2->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p2);

	Point* p3 = new Point ;
	p3->x = m_Current_GfxInfo.UpLeft.x;
	p3->y = m_Current_GfxInfo.UpLeft.y + 22;
	m_InputPins[1]->setPosition(p3);

	Point* p4 = new Point ;
	p4->x = m_Current_GfxInfo.UpLeft.x;
	p4->y = m_Current_GfxInfo.UpLeft.y + 30;
	m_InputPins[2]->setPosition(p4);
}
char* AND3::getUrl()
{
	return "images//AND3.jpg";
}

char* AND3::getIC()
{
	return "7411";
}
char* AND3::getType()
{
	return "AND_3";
}