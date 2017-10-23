#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
Buffer::Buffer()
	   :Gate("BUFFER", BUFFER, "images\\BUFFER.jpg",1)
{}

Buffer::Buffer(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	:Gate("BUFFER", BUFFER, r_GfxInfo, r_ApplicationManager, "images\\BUFFER.jpg",1)
{
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 3;
	p1->y = m_Current_GfxInfo.UpLeft.y + 25;
	m_InputPins[0]->setPosition(p1);
}
//==============================================================================================================
//Destructor:
Buffer::~Buffer()
{}

//==============================================================================================================
//Virtuals:
void Buffer::Operate()
{
		m_OutputPin->setStatus(m_InputPins[0]->getStatus());
}

void Buffer::Draw()
{
	m_ApplicationManager->getOutput()->drawComponent(m_URL, m_Current_Label, m_Current_GfxInfo.UpLeft);
}

bool Buffer::IsMatch(Point p)
{
	if( (p.x > m_Current_GfxInfo.UpLeft.x - 10) && (p.x < m_Current_GfxInfo.UpLeft.x +85) )
		if( (p.y > m_Current_GfxInfo.UpLeft.y - 10) && (p.y < m_Current_GfxInfo.UpLeft.y +60) )
			return true;
	return false;
}

void Buffer::Load(ifstream& in)
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

void Buffer::Save(ofstream& out)
{
	out<<"BUFFER"<<'\t';
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

void Buffer::UpdatePinsGfxInfo()
{
	//The OutputPin:
	Point* p1 = new Point;
	p1->x = m_Current_GfxInfo.UpLeft.x + 71;
	p1->y = m_Current_GfxInfo.UpLeft.y + 26;
	m_OutputPin->setPosition(p1);

	//The InputPins:
	Point* p2 = new Point;
	p2->x = m_Current_GfxInfo.UpLeft.x + 3;
	p2->y = m_Current_GfxInfo.UpLeft.y + 25;
	m_InputPins[0]->setPosition(p2);
}

char* Buffer::getUrl()
{
	return "images//BUFFER.jpg";
}

char* Buffer::getIC()
{
	return "74244";
}
char* Buffer::getType()
{
	return "BUFFER";
}