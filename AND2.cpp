#include "Includes.h"
#include <fstream>
using namespace std ;


//Constructor:
AND2::AND2()
	:Gate("AND_2", AND_2,"images//AND2.jpg", 2){}

AND2::AND2(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("AND_2", AND_2, r_GfxInfo, r_ApplicationManager, "images//AND2.jpg", 2)
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 1;
	p1->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p1);

	Point* p2 = new Point ;
	p2->x = m_Current_GfxInfo.UpLeft.x + 1;
	p2->y = m_Current_GfxInfo.UpLeft.y + 38;
	m_InputPins[1]->setPosition(p2);
}
//==============================================================================================================
//Destructor:
AND2::~AND2()
{}

//==============================================================================================================
//Virtuals:
void AND2::Operate()
{
	if( (m_InputPins[0]->getStatus() == LOW) || (m_InputPins[1]->getStatus() == LOW) )
		m_OutputPin->setStatus(LOW);
	else
		m_OutputPin->setStatus(HIGH);
}

void AND2::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool AND2::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void AND2::Load(ifstream& in)
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

void AND2::Save(ofstream& out)
{
	out<<"AND2"<<'\t';
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

void AND2::UpdatePinsGfxInfo()
{
	//The OutputPin:
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 71;
	p1->y = m_Current_GfxInfo.UpLeft.y + 26;
	m_OutputPin->setPosition(p1);

	//The InputPins:
	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x + 1;
	p2->y = m_Current_GfxInfo.UpLeft.y + 14;
	m_InputPins[0]->setPosition(p2);

	Point* p3 = new Point ;
	p3->x = m_Current_GfxInfo.UpLeft.x + 1;
	p3->y = m_Current_GfxInfo.UpLeft.y + 38;
	m_InputPins[1]->setPosition(p3);
}

char* AND2::getUrl()
{
	return "images//AND2.jpg";
}

char* AND2::getIC()
{
	return "7408";
}
char* AND2::getType()
{
	return "AND_2";
}