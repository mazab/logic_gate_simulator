#include "Includes.h"


AddWire::AddWire(OutputPin* Source, InputPin* Destination ,ApplicationManager* pManager)
{
		GraphicsInfo*  GfxInfo = new GraphicsInfo;
		m_ptrAddedComponent = new Wire (Destination , Source , *GfxInfo , pManager);
		Destination->setWire((Wire*)m_ptrAddedComponent);
		pManager -> pushUndo(this);

		First = true;

}

void AddWire::ReadActionParameters(ApplicationManager* pManager)
{}

void AddWire :: Execute (ApplicationManager* pManager)
{
	if(First)
	{
		// (1)->Executes the action
		pManager -> AddComp(m_ptrAddedComponent);
		First = false;
	}
	else
	{
		// (1)->Executes the action in case of Redo
		pManager -> AddComp(m_ptrAddedComponent);
		// (2)->re set the wire:
		((Wire*)m_ptrAddedComponent)->getInputPin()->setWire((Wire*)m_ptrAddedComponent);
		// (3)->re connect the input pin to the output pin:
		((Wire*)m_ptrAddedComponent)->getInputPin()->setOutputPin(((Wire*)m_ptrAddedComponent)->getOutputPin());
		((Wire*)m_ptrAddedComponent)->getInputPin()->setConn(true);
		if(dynamic_cast <Gate*>(((Wire*)m_ptrAddedComponent)->getInputPin()->getComponent()) != NULL)
			{
				Component* C = ((Wire*)m_ptrAddedComponent)->getInputPin()->getComponent();
				((Gate*)C)->incInputs();
			}
		// (4)->re connect the output pin to the input pin:
		((Wire*)m_ptrAddedComponent)->getOutputPin()->ConnectTo(((Wire*)m_ptrAddedComponent)->getInputPin());
		if(dynamic_cast <Gate*>(((Wire*)m_ptrAddedComponent)->getOutputPin()->getComponent()) != NULL)
			{
				Component* C = ((Wire*)m_ptrAddedComponent)->getOutputPin()->getComponent();
				((Gate*)C)->incFanouts();
			}
	}
}

void AddWire :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 

	//disconnect the input pin:
	if(((Wire*)m_ptrAddedComponent)->getInputPin()->getComponent()->getName() == LED)
	{
		((Wire*)m_ptrAddedComponent)->getInputPin()->setConn(false);
		((Wire*)m_ptrAddedComponent)->getInputPin()->setOutputPin(NULL);
		((Wire*)m_ptrAddedComponent)->getInputPin()->setWire(NULL);
	}
	else
	{
		Component* C = ((Wire*)m_ptrAddedComponent)->getInputPin()->getComponent();
		((Gate*)C)->DisconnectInputPinFrom(((Wire*)m_ptrAddedComponent)->getOutputPin());
	}

	//disconnect the output pin:
	((Wire*)m_ptrAddedComponent)->getOutputPin()->DisConnectTo(((Wire*)m_ptrAddedComponent)->getInputPin());
	if(((Wire*)m_ptrAddedComponent)->getOutputPin()->getComponent()->getName() != SWITCH)
	{
		Component* t = ((Wire*)m_ptrAddedComponent)->getOutputPin()->getComponent();
		((Gate*)t)->decFanouts();
	}
		
		
}

AddWire::~AddWire()
{ }
