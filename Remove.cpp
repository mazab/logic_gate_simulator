#include "Includes.h"


Remove::Remove(void)
{
	Used = NULL;
	
	for(int i=0; i<FANOUT; i++)
		Wires[i] = NULL;

	First=true;

}
//=================================================================================================================================

Remove::~Remove(void)
{
	Used = NULL;

	for(int i=0; i<FANOUT; i++)
		Wires[i] = NULL;
}
//=================================================================================================================================

void Remove::setUsedComp(ApplicationManager* pManager)
{
	Used=pManager->getselectedcomponent();
}
//=================================================================================================================================

void Remove::ReadActionParameters(ApplicationManager* pManager)
{}
//=================================================================================================================================

void Remove::Execute(ApplicationManager *pManager)
{
	if (First)
	{
		setUsedComp(pManager);
	}
	
	// (2)--->remove the component from the CompList:
	pManager->RemoveComp(Used->getID());

	// (1)--->Remove connectins:
	switch(Used->getName())
	{

	case SWITCH:
		{
			int connectionsCount = ((Switch*)Used)->getPin()->getConnectionsCount();
			for(int i=0; i<connectionsCount; i++)
			{

				//remove the wire:
				Wires[i] = ((Switch*)Used)->getPin()->getConnectedPins()[i]->getWire();
				if (Wires[i]!=NULL)
				{
				pManager->RemoveComp(Wires[i]->getID());
				
				//desconnect the connected pins:
				if (((Switch*)Used)->getPin()->getConnectedPins()[i]->getComponent()->getName()==LED)
				{
				((Switch*)Used)->getPin()->getConnectedPins()[i]->setConn(false);
				((Switch*)Used)->getPin()->getConnectedPins()[i]->setOutputPin(NULL);
				}
				else 
				{
					Component *C =((Switch*)Used)->getPin()->getConnectedPins()[i]->getComponent();
					((Gate*)C)->DisconnectInputPinFrom(((Switch*)Used)->getPin());
				}
				}
			}
			break;
		}//end case SWITCH

	case LED:
		{
			//if the led is connected:
			if( ((Led*)Used)->getPin()->getConn() )
			{
				//disconnect the connected pin:
				//if switch:
				if(((Led*)Used)->getPin()->getOutputPin()->getComponent()->getName() == SWITCH)
					((Led*)Used)->getPin()->getOutputPin()->DisConnectTo(((Led*)Used)->getPin());
				//if Gate:
				else
					((Gate*)(((Led*)Used)->getPin()->getOutputPin()->getComponent()))->DisconnectOutputPinFrom(((Led*)Used)->getPin());

				//remove the wire from the componentlist:
				pManager->RemoveComp(((Led*)Used)->getPin()->getWire()->getID());
			}//end if
			break;
		}//end case LED

	case WIRE:
		{
			//disconnect the input pin:
			if(((Wire*)Used)->getInputPin()->getComponent()->getName() == LED)
			{
				((Wire*)Used)->getInputPin()->setConn(false);
				((Wire*)Used)->getInputPin()->setOutputPin(NULL);
				((Wire*)Used)->getInputPin()->setWire(NULL);
			}
			else
			{
				Component* C = ((Wire*)Used)->getInputPin()->getComponent();
				((Gate*)C)->DisconnectInputPinFrom(((Wire*)Used)->getOutputPin());
			}

			//disconnect the output pin:
			((Wire*)Used)->getOutputPin()->DisConnectTo(((Wire*)Used)->getInputPin());
			if(((Wire*)Used)->getOutputPin()->getComponent()->getName() != SWITCH)
			{
				Component* t = ((Wire*)Used)->getOutputPin()->getComponent();
				((Gate*)t)->decFanouts();
			}
			break;
		}//end case WIRE

	default: //Gates!
		{
			//disconnect the output pin:
			int connectionsCount = ((Gate*)Used)->getOutputPin()->getConnectionsCount();
			for(int i=0; i<connectionsCount; i++)
			{
				//remove the wire:
				Wires[i] = ((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->getWire();
				if (Wires[i]!=NULL)
				{
				pManager->RemoveComp(Wires[i]->getID());

				//disconnect the connected pins:
				if (((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->getComponent()->getName()==LED)
				{
					((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->setConn(false);
				((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->setOutputPin(NULL);
				}
				else 
				{
					Component *C =(((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->getComponent());
					((Gate*)C)->DisconnectInputPinFrom(((Gate*)Used)->getOutputPin());
				}
				}
			}//end for

			//disconnect the input pins:
			connectionsCount = ((Gate*)Used)->getConnectedInputs();
			InputPin* In = NULL;
			for(int i=0; i<connectionsCount; i++)
			{
				In = ((Gate*)Used)->getInputPin(i+1);
				if(In->getConn())
				{

					if( In->getOutputPin()->getComponent()->getName() == SWITCH )
					{
						//disconnect the connected pin:
						In->getOutputPin()->DisConnectTo(In);

						//remove the wire from the componentlist:
						pManager->RemoveComp(In->getWire()->getID());
						Component * C = In->getWire();

					}//end if

					else //Gate!
					{
						//disconnect the connected pin:
						((Gate*)(In->getOutputPin()->getComponent()))->DisconnectOutputPinFrom(In);

						//remove the wire from the componentlist:
						pManager->RemoveComp(In->getWire()->getID());
					}//end else

				}
			}//end for
			
		}//end case GATE
		break;
	}//end switch

	

	if (First)
	{
			pManager->pushUndo(this);
			First=false;
	}
		
}
//=================================================================================================================================

 void Remove::unExecute(ApplicationManager *pManager)
 {
	 // (1)---> put the component in the compList:
	 pManager->AddComp(Used);

	// (2) Reconnect the pins! :
	 switch(Used->getName())
	 {
	 case SWITCH:
		 {
			int connectionsCount = ((Switch*)Used)->getPin()->getConnectionsCount();
			for(int i=0; i<connectionsCount; i++)
			{
				

				//reconnect the connected pins:
				if (((Switch*)Used)->getPin()->getConnectedPins()[i]->getComponent()->getName()==LED)
				{
					((Switch*)Used)->getPin()->getConnectedPins()[i]->setConn(true);
					((Switch*)Used)->getPin()->getConnectedPins()[i]->setOutputPin(((Switch*)Used)->getPin());
				}
				else 
				{
					Component *C =(((Switch*)Used)->getPin()->getConnectedPins()[i]->getComponent());
					((Gate*)C)->ConnectInputPinTo(((Switch*)Used)->getPin());
					((Switch*)Used)->getPin()->DisConnectTo((((Switch*)Used)->getPin()->getConnectedPins()[i]));
					((Switch*)Used)->getPin()->ConnectTo( ((Gate*)C)->getInputPin(((Gate*)C)->getConnectedInputs()));
				}
				//reconnect the wire:
				Wires[i]->setInputPin(((Switch*)Used)->getPin()->getConnectedPins()[i]);
				((Switch*)Used)->getPin()->getConnectedPins()[i]->setWire(Wires[i]);
				pManager->AddComp(Wires[i]);
			}//end fore
		 
		 }//end case SWITCH
		 break;

	 case LED:
		 {
			 //if the led was connected:
			if( ((Led*)Used)->getPin()->getConn() )
			{
				//reconnect the connected pin:
				//if switch:
				if(((Led*)Used)->getPin()->getOutputPin()->getComponent()->getName() == SWITCH)
					((Led*)Used)->getPin()->getOutputPin()->ConnectTo(((Led*)Used)->getPin());
				//if Gate:
				else
					((Gate*)(((Led*)Used)->getPin()->getOutputPin()->getComponent()))->ConnectOutputPinTo(((Led*)Used)->getPin());

				//add the wire from the componentlist:
				pManager->AddComp(((Led*)Used)->getPin()->getWire());
			}//end if

		 }//end case LED:
		 break;

	 case WIRE:
		 {
			 //connect the input pin:
			 Component* CC = ((Wire*)Used)->getInputPin()->getComponent();
			 ((Gate*)CC)->ConnectInputPinTo(((Wire*)Used)->getOutputPin());
			 ((Wire*)Used)->setInputPin(((Gate*)CC)->getInputPin(((Gate*)CC)->getConnectedInputs()));
			//((Wire*)Used)->getInputPin()->setConn(true);
			//((Wire*)Used)->getInputPin()->setOutputPin(((Wire*)Used)->getOutputPin());
			((Wire*)Used)->getInputPin()->setWire((Wire*)Used);

			//connect the output pin:
			((Wire*)Used)->getOutputPin()->ConnectTo(((Wire*)Used)->getInputPin());
		 
		 }//end case WIRE
		 break;

	 default: //GATE!
		 {
			 //connect the output pin:
			int connectionsCount = ((Gate*)Used)->getOutputPin()->getConnectionsCount();
			for(int i=0; i<connectionsCount; i++)
			{
				

				//reconnect the connected pins:
				if (((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->getComponent()->getName()==LED)
				{
				((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->setConn(true);
				((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->setOutputPin(((Gate*)Used)->getOutputPin());
				}
				else 
				{
					Component *C =(((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->getComponent());
					((Gate*)C)->ConnectInputPinTo(((Gate*)Used)->getOutputPin());
					((Gate*)Used)->getOutputPin()->DisConnectTo((((Gate*)Used)->getOutputPin()->getConnectedPins()[i]));
					((Gate*)Used)->getOutputPin()->ConnectTo( ((Gate*)C)->getInputPin(((Gate*)C)->getConnectedInputs()));
				}

				//add the wires:
				Wires[i]->setInputPin(((Gate*)Used)->getOutputPin()->getConnectedPins()[i]);
				((Gate*)Used)->getOutputPin()->getConnectedPins()[i]->setWire(Wires[i]);
				pManager->AddComp(Wires[i]);
			
			}//end fore

			//reconnect the input pins:
			connectionsCount = ((Gate*)Used)->getConnectedInputs();
			InputPin* In = NULL;
			for(int i=0; i<connectionsCount; i++)
			{
				In = ((Gate*)Used)->getInputPin(i+1);
				if( In->getOutputPin()->getComponent()->getName() == SWITCH )
				{
					//reconnect the connected pin:
					In->getOutputPin()->ConnectTo(In);

					//add the wire to the componentlist:
					pManager->AddComp(In->getWire());
				}//end if

				else //Gate!
				{
					//reconnect the connected pin:
					((Gate*)(In->getOutputPin()->getComponent()))->ConnectOutputPinTo(In);

					//add the wire to the componentlist:
					pManager->AddComp(In->getWire());
				}//end else


			}//end for
		 
		 }//end case GATE
		 break;
	 }//end switch

	 // (3)---> return the wireslist to NULL:
	for(int i=0; i<FANOUT; i++)
		Wires[i] = NULL;

 }