#include "Includes.h"

AddANDgate :: AddANDgate (Point Center , ActionType A , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);

	switch (A)
	{
	case Add_AND_2:

		m_ptrAddedComponent = new AND2 (*GfxInfo , r_ptrManager);
		break;

	case Add_AND_3:

		m_ptrAddedComponent = new AND3 (*GfxInfo , r_ptrManager);
		break;

	case Add_AND_4:

		m_ptrAddedComponent = new AND4 (*GfxInfo , r_ptrManager);
		break;

	default:
		break;
	} 

	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	r_ptrManager -> pushUndo (this);
}



void AddANDgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddANDgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

void AddANDgate::ReadActionParameters(ApplicationManager* pManager)
{
}

AddANDgate::~AddANDgate()
{
	delete m_ptrAddedComponent ;
}
