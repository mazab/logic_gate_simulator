#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
XNOR4::XNOR4()
	:Gate("XNOR_4", XNOR_4, "images\\XNOR4.jpg", 4){}

XNOR4::XNOR4(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("XNOR_4", XNOR_4, r_GfxInfo, r_ApplicationManager, "images\\XNOR4.jpg", 4)
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x;
	p1->y = m_Current_GfxInfo.UpLeft.y + 16;
	m_InputPins[0]->setPosition(p1);

	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x + 4;
	p2->y = m_Current_GfxInfo.UpLeft.y + 23;
	m_InputPins[1]->setPosition(p2);

	Point* p3 = new Point;
	p3->x = m_Current_GfxInfo.UpLeft.x + 4;
	p3->y = m_Current_GfxInfo.UpLeft.y + 31;
	m_InputPins[2]->setPosition(p3);

	Point* p4 = new Point;
	p4->x = m_Current_GfxInfo.UpLeft.x;
	p4->y = m_Current_GfxInfo.UpLeft.y + 37;
	m_InputPins[3]->setPosition(p4);
}
//==============================================================================================================
//Destructor:
XNOR4::~XNOR4()
{}

//==============================================================================================================
//Virtuals:
void XNOR4::Operate()
{
	bool inputs[4];
	for(int i=0; i<4; i++)
	{
		if(m_InputPins[i]->getStatus() == HIGH)
			inputs[i] = true;
		else
			inputs[i] = false;
	}

	if( ((inputs[0] && !inputs[1]) || (inputs[1] && !inputs[0])) &&!((inputs[2] && !inputs[3]) || (inputs[3] && !inputs[2])) 
	                               ||
	   !((inputs[0] && !inputs[1]) || (inputs[1] && !inputs[0])) && ((inputs[2] && !inputs[3]) || (inputs[3] && !inputs[2])) )
		m_OutputPin->setStatus(LOW);
	else
		m_OutputPin->setStatus(HIGH);
}

void XNOR4::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool XNOR4::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void XNOR4::Load(ifstream& in)
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

void XNOR4::Save(ofstream& out)
{
	out<<"XNOR4"<<'\t';
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

void XNOR4::UpdatePinsGfxInfo()
{
	//The OutputPin:
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 71;
	p1->y = m_Current_GfxInfo.UpLeft.y + 26;
	m_OutputPin->setPosition(p1);

	//The InputPins:
	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x;
	p2->y = m_Current_GfxInfo.UpLeft.y + 16;
	m_InputPins[0]->setPosition(p2);

	Point* p3 = new Point;
	p3->x = m_Current_GfxInfo.UpLeft.x + 4;
	p3->y = m_Current_GfxInfo.UpLeft.y + 23;
	m_InputPins[1]->setPosition(p3);

	Point* p4 = new Point;
	p4->x = m_Current_GfxInfo.UpLeft.x + 4;
	p4->y = m_Current_GfxInfo.UpLeft.y + 31;
	m_InputPins[2]->setPosition(p4);

	Point* p5 = new Point;
	p5->x = m_Current_GfxInfo.UpLeft.x;
	p5->y = m_Current_GfxInfo.UpLeft.y + 37;
	m_InputPins[3]->setPosition(p5);
}
char* XNOR4::getUrl()
{
	return "images//XNOR4.jpg";
}

char* XNOR4::getIC()
{
	return "-----";
}
char* XNOR4::getType()
{
	return "XNOR_4";
}