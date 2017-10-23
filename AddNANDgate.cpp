#include "Includes.h"

AddNANDgate :: AddNANDgate (Point Center , ActionType A , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);

	switch (A)
	{
	case Add_NAND_2:

		m_ptrAddedComponent = new NAND2 (*GfxInfo , r_ptrManager);
		break;

	case Add_NAND_3:

		m_ptrAddedComponent = new NAND3 (*GfxInfo , r_ptrManager);
		break;

	case Add_NAND_4:

		m_ptrAddedComponent = new NAND4 (*GfxInfo , r_ptrManager);
		break;

	default:
		break;
	} 

	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	
	r_ptrManager -> pushUndo (this);
}



void AddNANDgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddNANDgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddNANDgate::~AddNANDgate()
{ }
