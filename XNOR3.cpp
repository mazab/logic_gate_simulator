#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
XNOR3::XNOR3()
	:Gate("XNOR_3", XNOR_3, "images\\XNOR3.jpg", 3){}

XNOR3::XNOR3(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("XNOR_3", XNOR_3, r_GfxInfo, r_ApplicationManager, "images\\XNOR3.jpg", 3)
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
XNOR3::~XNOR3()
{}

//==============================================================================================================
//Virtuals:
void XNOR3::Operate()
{
	bool inputs[3];
	for(int i=0; i<3; i++)
	{
		if(m_InputPins[i]->getStatus() == HIGH)
			inputs[i] = true;
		else
			inputs[i] = false;
	}

	if( ((inputs[0] && !inputs[1]) || (inputs[1] && !inputs[0])) && !inputs[2] 
	                               ||
	   !((inputs[0] && !inputs[1]) || (inputs[1] && !inputs[0])) && inputs[2])
		m_OutputPin->setStatus(LOW);
	else
		m_OutputPin->setStatus(HIGH);
}

void XNOR3::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool XNOR3::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void XNOR3::Load(ifstream& in)
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

void XNOR3::Save(ofstream& out)
{
	out<<"XNOR3"<<'\t';
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

void XNOR3::UpdatePinsGfxInfo()
{
	//The OutputPin:
	Point* p1= new Point;
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
char* XNOR3::getUrl()
{
	return "images//XNOR3.jpg";
}

char* XNOR3::getIC()
{
	return "-----";
}
char* XNOR3::getType()
{
	return "XNOR_3";
}