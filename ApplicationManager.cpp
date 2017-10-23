//=============================================================================
#include "Includes.h"
#include <iostream>
#include <fstream>
using namespace std ;
//=============================================================================
ApplicationManager::ApplicationManager()
{
	ExitWindow = false;
	SimuMode = false;

	ptrOutput = new Output();
	ptrInput = new Input( ptrOutput->getWindow() , ptrOutput);

	LevelCount = 0;
	CompCount = 0;
	selected = -1 ;
	WiresExcCount = 0;


	ptrOutput->drawInterface(SimuMode);

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	for(int i=0; i<MaxLevelCount ; i++)
		LevelList[i] = NULL;

}
//=============================================================================

ApplicationManager::~ApplicationManager()
{
	//for(int i=0; i<CompCount; i++)
		//delete CompList[i];

	delete ptrInput;
	delete ptrOutput;
	
}

//=============================================================================

void ApplicationManager::AddComp(Component* r_Comp)
{
	CompList[CompCount] = r_Comp ;
	CompCount ++ ;
}

//=============================================================================

void ApplicationManager::RemoveComp(int r_ID)
{
	for (int i=0 ; i<CompCount ; i++)
	{
		if(CompList[i]->getID() == r_ID )
		{
			CompList[i] = CompList[CompCount-1];
			CompCount -- ;
			i = CompCount+1 ;
			//this->UpdateInterface();
		}
	}
}

//=============================================================================

Component* ApplicationManager::SearchByID(int r_ID)
{
	for (int i=0 ; i<CompCount ; i++)
	{
		if(CompList[i]->getID() == r_ID)
		{
			return CompList[i];
		}
	}
	return NULL;
}

//=============================================================================

int ApplicationManager::getCompCount()
{
	return CompCount ;
}

//=============================================================================

Output* ApplicationManager::getOutput()
{
	return ptrOutput;
}

//=============================================================================

Input* ApplicationManager::getInput()
{
	return ptrInput;
}

//=============================================================================

int ApplicationManager::getLevelCount()
{
	return LevelCount;
}

//=============================================================================

void ApplicationManager::AddLevel(Level* r_Level)
{
	LevelList[LevelCount] = r_Level ;
	LevelList[LevelCount]->setID(LevelCount + 1);
	LevelCount ++ ;
}

//=============================================================================

void ApplicationManager::RemoveLevel(int r_ID)
{
	for (int i=0 ; i<LevelCount ; i++)
	{
		if(LevelList[i]->getID() == r_ID)
		{
			delete LevelList[i];
			LevelList[i] = LevelList[LevelCount - 1];
			LevelCount --;
			i = LevelCount + 1;
		}
	}
}

//=============================================================================

void ApplicationManager::pushUndo(Action* r_Action)
{
	UndoStack.push(r_Action);
}

//=============================================================================

void ApplicationManager::pushRedo(Action* r_Action)
{
	RedoStack.push(r_Action);
}

//=============================================================================

Action* ApplicationManager::popUndo()
{
	Action* tmp = UndoStack.top() ;
	UndoStack.pop();
	return tmp;
}

//=============================================================================

Action* ApplicationManager::popRedo()
{
	Action* tmp = RedoStack.top() ;
	RedoStack.pop() ;
	return tmp ;
}

//=============================================================================

bool ApplicationManager::UndoIsEmpty()
{
	return UndoStack.empty() ;
}

//=============================================================================

bool ApplicationManager::RedoIsEmpty()
{
	return RedoStack.empty() ;
}
//=============================================================================

void ApplicationManager::setExit(bool rExit)
{
	ExitWindow = rExit;
}

//=============================================================================

bool ApplicationManager::getExit()
{
	return ExitWindow;
}

//=============================================================================

void ApplicationManager::setSimulationMode(bool r_SimuMode)
{
	SimuMode = r_SimuMode ;
}

//=============================================================================

bool ApplicationManager::getSimulationMode()
{
	return SimuMode ;
}

//=============================================================================

void ApplicationManager::AutoAlign(int r_EmptyLevel)
{
	for(int i=0 ; i<LevelCount ; i++)
		LevelList[i]->AutoAlign(r_EmptyLevel , this);
	for(int i=0 ; i<CompCount ; i++)
		CompList[i]->UpdatePinsGfxInfo() ;
}

//=============================================================================

void ApplicationManager::save(ofstream& out)
{
	
	out<<LevelCount<<endl;
	for(int i=0 ; i<LevelCount ; i++)
	{
		LevelList[i]->Save(out);
	}

	out<<"Connections:"<<endl;
	for(int i=0 ; i<CompCount ; i++)
	{
		if(CompList[i]->getName() == WIRE)
			CompList[i]->Save(out);
	}
}

//=============================================================================

void ApplicationManager::errorDetector()
{
	Component* pComp;
	for (int i=0 ; i<CompCount ; i++)
	{
		//poointer to the comp we are dealing with 
		pComp = CompList[i];

		//---------------------------------------------------------------------------------------------------------
		//case(1): LED or SWITCH : they have only one pin if it is not connected it gives an error
		//=========================================================================================
		if( pComp->getName() == LED )
		{
			if( !  ((Led*)pComp)->getPin()->getConn() )
				getOutput()->Highlight(pComp->getCurrentGfxInfo().UpLeft , pComp->getCurrentGfxInfo().DownRight);
		}
		else if(pComp->getName() == SWITCH)
		{
			if( !  ((Switch*)pComp)->getPin()->getConn() )
				getOutput()->Highlight(pComp->getCurrentGfxInfo().UpLeft , pComp->getCurrentGfxInfo().DownRight);
		}

		//----------------------------------------------------------------------------------------------------------
		//case(2): WIRE : it has 2 pins 1-input and 1-output if the output pin is not connected . it gives an error
		//==========================================================================================================
		else if( pComp->getName() == WIRE )
		{
			//if the input pin is not connected .. set the signal on it to HIGH (as in the TTL gates)
			if( ! ((Wire*)pComp)->getInputPin()->getConn() )
			{
				((Wire*)pComp)->getInputPin()->setStatus(HIGH) ;
			}
			//if the output pin is not connected .. give an error
			if( ! ((Wire*)pComp)->getOutputPin()->getConn() )
			{
				ptrOutput->Highlight(pComp->getCurrentGfxInfo().UpLeft , pComp->getCurrentGfxInfo().DownRight);
			}
		}

		//-----------------------------------------------------------------------------------------------------------
		//case(3): GATE: it has 1-output and more than 1 input(2,3,4) if any is not connected set to HIGH
		//=======================================================================================================
		else
		{
			//test the output pin (if not connected .. gove an error)
			//------------------------------------------------------------------------------------------------
			if(! ((Gate*)pComp)->getOutputPin()->getConn() )
			{
				ptrOutput->Highlight(pComp->getCurrentGfxInfo().UpLeft , pComp->getCurrentGfxInfo().DownRight);
			}
			//------------------------------------------------------------------------------------------------

			//test the input pins (if not connected set the input pin to HIGH as in TTL logic gates)
			//------------------------------------------------------------------------------------------------
			int inputCount = ((Gate*)pComp)->getInputPinsCount();
			for(int j=0 ; j<inputCount ; j++)
			{
				if(! ((Gate*)pComp)->getInputPin(j+1)->getConn() )
				{
					((Gate*)pComp)->getInputPin(j+1)->setStatus(HIGH) ;
				}
			}		
			//------------------------------------------------------------------------------------------------
		}
	}
}
//=============================================================================
Component** ApplicationManager::OnArea(Point P1, Point P2, int ID1, int ID2)
{
  // 1)---> Creating the corners of the area:
  //-------------------------------------------
	Point C1, C2, C3, C4; 
	  /*     C1--------------C2
	         |                |
			 |                |
			 |                |
			 C3--------------C4          */
	
	C1.x = P1.x;        C3.x = P1.x;
	C2.x = P2.x;        C4.x = P2.x;
	
	if( ((P1.y - P2.y) <= 50)  && (P1.y >= P2.y) )
	{
		C1.y = P1.y+55;        C3.y = P2.y-55;
		C2.y = P1.y+55;        C4.y = P2.y-55;
	}
	else if( ((P2.y - P1.y) <= 50) && (P2.y >= P1.y) )
	{
		C1.y = P2.y+55;        C3.y = P1.y-55;
		C2.y = P2.y+55;        C4.y = P1.y-55;
	}
	else
	{
		if(P1.y < P2.y) // P1 Up & P2 Dn:
		{
			C1.y = P1.y;        C3.y = P2.y;
			C2.y = P1.y;        C4.y = P2.y;
		}
		else //P1 Dn & P2 Up:
		{
			C1.y = P2.y;        C3.y = P1.y;
			C2.y = P2.y;        C4.y = P1.y;
		}
	}
  // 2)---> Testing:
  //-----------------
	Component** areaComp = new Component*[200];
	for(int i=0; i<200; i++)
		areaComp[i] = NULL;

	//The test loop:
	// at least one of the corners of the picture must be located 
	// in the area, to say that this component is in this area.
	int j=0;
	Point UpLeft, DnRight, UpRight, DnLeft;
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i]->getName() != WIRE)
		{
			//Define the corners of the tested Component:
			UpLeft = CompList[i]->getCurrentGfxInfo().UpLeft;
			DnRight = CompList[i]->getCurrentGfxInfo().DownRight;
			UpRight.x = DnRight.x;     UpRight.y = UpLeft.y;
			DnLeft.x = UpLeft.x;       DnLeft.y = DnRight.y;
		
			//Testing the first corner:
			if( (UpLeft.x > C1.x) && (UpLeft.x < C2.x) 
			   && (UpLeft.y > C1.y) && (UpLeft.y < C3.y) )
			{
			   if( (CompList[i]->getID() != ID1) && (CompList[i]->getID() != ID2) )
				   areaComp[j++] = CompList[i];
			}
		
			//Testing the 2nd corner:
			else if( (UpRight.x > C1.x) && (UpRight.x < C2.x) 
			   && (UpRight.y > C1.y) && (UpRight.y < C3.y) )
			{
			if( (CompList[i]->getID() != ID1) && (CompList[i]->getID() != ID2) )
				   areaComp[j++] = CompList[i];
			}

			//Testing the 3rd corner:
			else if( (DnLeft.x > C1.x) && (DnLeft.x < C2.x) 
			   && (DnLeft.y > C1.y) && (DnLeft.y < C3.y) )
			{
			   if( (CompList[i]->getID() != ID1) && (CompList[i]->getID() != ID2) )
				   areaComp[j++] = CompList[i];
			}

			//Testing the 4th corner:
			else if( (DnRight.x > C1.x) && (DnRight.x < C2.x) 
				&& (DnRight.y > C1.y) && (DnRight.y < C3.y) )
			{
				if( (CompList[i]->getID() != ID1) && (CompList[i]->getID() != ID2) )
					areaComp[j++] = CompList[i];
			}

			else
			{}
		}//end if

	} //end the test loop

	return areaComp;
	  
}

//----------------------------------------------------------------------------------------

void ApplicationManager::TruthTable(Action* pAct)
{
	int rowsCount = 0 ;
	int colsCount = 0;
	Component* SwitchList[20] ;
	Component* LedList[20] ;
	int SwitchCount = 0 ;
	int LedCount = 0;
	STATUS** pGrid = NULL ;

	//creating a list of switches and a list of leds
	for(int i=0 ; i<CompCount ; i++)
	{
		//making the list of Switches to apply the input signal in the table on them
		if(CompList[i]->getName() == SWITCH)
		{
			SwitchList[SwitchCount] = CompList[i] ;
			SwitchCount ++ ;
			colsCount ++ ;
		}
		//making the list of Leds to get their status after the SimulationMode is activated
		else if(CompList[i]->getName() == LED)
		{
			LedList[LedCount] = CompList[i] ;
			LedCount ++ ;
			colsCount ++ ;
		}
	}

	//-----------------------------
	//calculating the number of rows
	rowsCount = Pow(2 , SwitchCount ) ;

	//sending this data to the class CreateTruthTable
	((CreateTruthTable*)pAct)->setData(rowsCount ,colsCount ,SwitchCount ,LedCount) ;

	//creating the Grid acording to the data 
	
	((CreateTruthTable*)pAct)->CreateGrid();

	//getting the table done by the fn CreateGrid 
	pGrid = ((CreateTruthTable*)pAct)->getGrid();

	//-----------------------------
	//applying the signal in the truthtable on the switches(input component)
	//and get the signal on the Leds (putput Component) and put it in the table

	//first loop to loop over the rows
	for(int i=0 ; i<rowsCount ; i++)
	{
		//first part: is to apply the signal on the switches
		for(int j=0 ; j<SwitchCount ; j++)
		{
			((Switch*)SwitchList[j])->getPin()->setStatus(pGrid[i][j]) ;
		}

		//second part: is to activate the simulationMode action
		SimulationMode* pSimuMode = new SimulationMode ;
		pSimuMode->CircuitOperate(this) ;

		//third part: is to get the signal of the Leds and put them on the table
		int walker_cols = SwitchCount ;
		int walker_leds = 0 ;
		while( (walker_cols < colsCount) && (walker_leds < LedCount) )
		{
			pGrid[i][walker_cols] = ((Led*)LedList[walker_leds])->getPin()->getStatus() ;
			walker_cols++ ;
			walker_leds++ ;
		}
	}
	//-----------------------------
}

//---------------------------------------------------------------------------------------------

void ApplicationManager::load(ifstream& in)
{
	int numLevel = 0 ;
	int numCompLevel = 0 ;
	string CompType ="" ;
	bool endConnections = false;

	in>>numLevel ;
	//this part is to load the Components from the file
	//--------------------------------------------------------------------
	for(int i=1 ; i<= numLevel ; i++)
	{
		in>>numCompLevel;
		for (int j=1 ; j<= numCompLevel ; j++)
		{
			Component* pComp = NULL ;
			in>>CompType;
			// switch case to create the required component
			
			//AND gates
			if(CompType == "AND2")
				pComp = new AND2 ;
			else if(CompType == "AND3")
				pComp = new AND3 ;
			else if(CompType == "AND4")
				pComp = new AND4 ;

			//NAND gates
			else if(CompType == "NAND2")
				pComp = new NAND2 ;
			else if(CompType == "NAND3")
				pComp = new NAND3 ;
			else if(CompType == "NAND4")
				pComp = new NAND4 ;

			//OR gates
			else if(CompType == "OR2")
				pComp = new OR2 ;
			else if(CompType == "OR3")
				pComp = new OR3 ;
			else if(CompType == "OR4")
				pComp = new OR4 ;

			//NOR gates
			else if(CompType == "NOR2")
				pComp = new NOR2 ;
			else if(CompType == "NOR3")
				pComp = new NOR3 ;
			else if(CompType == "NOR4")
				pComp = new NOR4 ;

			//XOR gates
			else if(CompType == "XOR2")
				pComp = new XOR2 ;
			else if(CompType == "XOR3")
				pComp = new XOR3 ;
			else if(CompType == "XOR4")
				pComp = new XOR4 ;

			//XNOR gates
			else if(CompType == "XNOR2")
				pComp = new XNOR2 ;
			else if(CompType == "XNOR3")
				pComp = new XNOR3 ;
			else if(CompType == "XNOR4")
				pComp = new XNOR4 ;

			//Input and Output Components
			else if(CompType == "SWITCH")
				pComp = new Switch ;
			else if(CompType == "LED")
				pComp = new Led ;

			//NOT and BUFFER
			else if(CompType == "NOT")
				pComp = new Not ;
			else if(CompType == "BUFFER")
				pComp = new Buffer ;


			pComp->Load(in);

			//add this component to the list of all components in the Application Manager
			AddComp(pComp);
		}
	}
	for(int i=0 ; i<CompCount ; i++)
	{
		CompList[i]->setApplicationManager(this) ;
		CompList[i]->UpdatePinsGfxInfo() ;
	}
	//--------------------------------------------------------------------
	//loading the wires:

	//reading the string which is "Connections"
	in>>CompType;
	//reading the first int of the line to check if it is -1 .. to determine is this a wire or not

	//loop to create all the wires
	while(!endConnections)
	{
		Component* pComp = new Wire;
		pComp->setApplicationManager(this) ;
		
		//activate the load fn in the component
		((Wire*)pComp)->Load(in);

		if(((Wire*)pComp)->getLoadingTerminator() == -1)
		{
			endConnections = true ;
		}
		else
		{
			//add the pointer to the wiresList and to the compList
			AddComp(pComp);
		}
	}

}

//=======================================================================
int ApplicationManager::Pow(int A, int B)
{
	int power =A;
	for(int i=1; i<B; i++)
		power *= A;

	return power;
}

//========================================================================
//Level Counting Operations:
//---------------------------

void ApplicationManager::ExcludeWires()
{
	for(int i=0;i<CompCount;i++)
	{
       if ( dynamic_cast <Wire*> (CompList[i]) == NULL )
		   AddWiresExcComp (CompList[i]);
	}
}
//=============================================================================
Component* ApplicationManager::getInputCompLED(Component* r_Comp)
{
	//retruns a pointer to the component which preceeds r_Comp 

	if (r_Comp == NULL) //checking the validity of arguments
		return NULL;

	if ( dynamic_cast<Switch*>(r_Comp) != NULL)
		return NULL;

	if ( dynamic_cast<Led*>(r_Comp) )	//checks if r_comp points to LED

		return /*start 2*/( /*strart 1*/( ((Led*)r_Comp)->getPin() )/*end 1*/ -> getOutputPin() )/*end 2*/ -> getComponent();

	//step 1: ((Led*)r_Comp)->getPin()
	//casts the component pointer r_Comp to type LED type and gets its input pin
	//----------------------------------
	//step 2: step 1 -> getOutputPin()
	//gets the output pin which is connected to the LED's pin
	//----------------------------------
	//final step: step 2 -> getComponent();
	//returns a pointer to the component which is connected to that LED
}
//=============================================================================
Component** ApplicationManager::getInputCompGate(Component* r_Comp , int& length)
{
	int n = ((Gate*)r_Comp)->getInputPinsCount();
	Component** temp = new Component*[n];

	temp[0] = ( (  ((Gate*)r_Comp)->getInputPin(1)  ) -> getOutputPin() )  -> getComponent();

	if (n > 1)
	temp[1] = ( (  ((Gate*)r_Comp)->getInputPin(2)  ) -> getOutputPin() )  -> getComponent();

	if (n > 2)
		temp[2] = ( (  ((Gate*)r_Comp)->getInputPin(3)  ) -> getOutputPin() )  -> getComponent();

	if (n == 4)
		temp[3] = ( (  ((Gate*)r_Comp)->getInputPin(4)  ) -> getOutputPin() )  -> getComponent();

	return temp;

}
//=============================================================================
bool ApplicationManager::checkInput(Component* r_Comp)
{
	if ( (dynamic_cast<Switch*>(r_Comp) != NULL) || (r_Comp == NULL) )
		return true;
	return false;
}
//=============================================================================
/*Component** ApplicationManager::getOutputComp(Component* r_Comp , int& Length)
{
	//r_Comp : the component in which input pins connected to its output are returned
	//Length : number of actual input pins connected to r_Comp 

	if (r_Comp == NULL) //checking the validity of arguments
		return NULL;

	if ( dynamic_cast<Led*>(r_Comp) != NULL)
		return NULL;

	InputPin** temp;
	int i;

	if ( dynamic_cast<Switch*>(r_Comp) )
	{
		temp = ( ((Switch*)r_Comp)->getPin() ) -> getConnectedPins(); //temp array of input pins connected to r_Comp output pin
		i = ( ((Switch*)r_Comp)->getPin() ) -> getConnectionsCount();   //number of actual components connected to r_Comp
	}

	else
	{
		temp = ( ((Gate*)r_Comp)->getOutputPin() ) -> getConnectedPins(); //temp array of input pins connected to r_Comp output pin
		i = ( ((Gate*)r_Comp)->getOutputPin() ) -> getConnectionsCount();   //number of actual components connected to r_Comp
	}

	if (temp == NULL) //r_Comp is not connected to any component
		return NULL;
	
	Length = i;
	Component** return_temp = new Component* [i];

	int j=0;

		while (j < i)
		{
			return_temp[j] = temp[j] -> getComponent();
			j++;
		}

		return return_temp;
}*/
//=============================================================================
void ApplicationManager::checkForFirstLevel()
{
	//this fn will put all the gates which is not connected in level 1 and set the input pin status to HIGH (as in TTL Mode)
	for(int i=0 ; i<WiresExcCount ; i++)
	{
		//checking if the component is not a switch
		if(CompListWiresExc[i]->getName() != SWITCH)
		{
			//if it is a led .. i only have an input pin .. check if it is connected
			if(CompListWiresExc[i]->getName() == LED)
			{
				//if not connected (set Status to HIGH and set Level to 1)
				if( ((Led*)CompListWiresExc[i])->getPin()->getConn() == false)
				{
					((Led*)CompListWiresExc[i])->getPin()->setStatus(HIGH) ;
					((Led*)CompListWiresExc[i])->setLevel(1);
				}
			}
			//if the component is a gate it will have more than one input and an output
			else
			{
				//if the output is not connected .. set level to 1
				if ( ((Gate*)CompListWiresExc[i])->getOutputPin()->getConn() == false)
				{
					((Gate*)CompListWiresExc[i])->setLevel(1) ;
				}
				//else if the any of the input pins is not connected
				else
				{
					// the number of input pins in this gate
					int pin_num = ((Gate*)CompListWiresExc[i])->getInputPinsCount() ;
					//loop over the pins to check on them if they are connected or not
					for(int k=0 ; k<pin_num ; k++)
					{
						//if the pin is not connected .. set its level to 1 and its status to HIGH(as in TTL mode)
						if ( ((Gate*)CompListWiresExc[i])->getInputPin(k+1)->getConn() == false)
						{
							((Gate*)CompListWiresExc[i])->getInputPin(k+1)->setStatus(HIGH);
							((Gate*)CompListWiresExc[i])->setLevel(1);
						}
					}
				}
			}
		}
	}
}
//=============================================================================
bool ApplicationManager::findCompLevel(int level)
{
	for (int i=0;i<WiresExcCount;i++)
	{
		if (CompListWiresExc[i] -> getLevel() == level)
			return true;
	}

	return false;
}
//=============================================================================
void ApplicationManager::setOutputPinsToNextLevel(Component* r_Comp)
{
		//r_Comp : the component in which input pins connected to its output are returned
	//Length : number of actual input pins connected to r_Comp 
	int tmp = 0 ;

	if (r_Comp == NULL) //checking the validity of arguments
		return;

	if ( dynamic_cast<Led*>(r_Comp) != NULL)
		return;

	if ( dynamic_cast<Switch*>(r_Comp) )
	{
		for (int i=0 ; i < ( ((Switch*)r_Comp)->getPin() ) -> getConnectionsCount() ; i++)
		{
			if ( (  ( ((Switch*)r_Comp)->getPin() ) ->getConnectedPins()[i]->getComponent())->getLevel()  < r_Comp->getLevel() )
				(  ( ((Switch*)r_Comp)->getPin() ) ->getConnectedPins()[i]->getComponent())->setLevel( (r_Comp->getLevel() + 1));  
		}
	}

	else
	{
		for ( int i=0 ; i < ( ((Gate*)r_Comp)->getOutputPin() ) ->getConnectionsCount() ; i++)
		{
			if ( ( ((Gate*)r_Comp)->getOutputPin() ) ->getConnectedPins()[i]->getComponent()->getLevel() < r_Comp->getLevel())
				(	( ((Gate*)r_Comp)->getOutputPin() ) ->getConnectedPins()[i]->getComponent()	) ->setLevel ( (r_Comp->getLevel() + 1) ); 
	
		}
	}
}
//=============================================================================
void ApplicationManager::determineLevelZero()
{
	for (int i = 0 ; i<WiresExcCount ; i++)
	{
		if ( dynamic_cast<Switch*>(CompListWiresExc[i]) != NULL )
			CompListWiresExc[i] -> setLevel(0);
	}
}
//=============================================================================
/*void ApplicationManager::setLevels()
{
	bool looper = findCompLevel(-1);
	int i = 0;
	int LevelsNo = 1;

	while (looper)
	{
		if (CompListWiresExc[i] -> getLevel() != -1  && dynamic_cast<Led*>(CompListWiresExc[i]) == NULL)
		{
			if (  (dynamic_cast<Gate*>(CompListWiresExc[i]) != NULL && ((Gate*)CompListWiresExc[i])->getConnectedInputs() != NULL)  || (dynamic_cast<Switch*>(CompListWiresExc[i]) != NULL) )/* && ((Switch*)CompListWiresExc[i])->getPin()->getConn())  )
			{
				setOutputPinsToNextLevel(CompListWiresExc[i]);

			if ( (CompListWiresExc[i]->getLevel()+1) > LevelsNo )
				LevelsNo = CompListWiresExc[i]->getLevel()+1;
			}
		}

		i++;

		if (i >= WiresExcCount)
			i=0;

		looper = findCompLevel(-1);
		
	}

	LevelCount = LevelsNo+1;
*/
//=============================================================================
void ApplicationManager::setLevels()
{
	bool test = true ;
	int k = 0 ; 
	bool end = false;
	determineLevelZero();
	Component* pComp = NULL ;

	while (!end)
	{
		for (int j=0 ; j < WiresExcCount ; j++)
		{
			Component* pComp_test = CompListWiresExc[j];
			test = true ;

			if(pComp_test->getLevel() == -1)
			{
				if (dynamic_cast<Switch*>(pComp_test) == NULL)
				{
					if ( dynamic_cast<Led*>(pComp_test) != NULL)
					{
						k=1;
						for(int p=0 ; p<k ; p++)
						{
							if(((Led*)pComp_test)->getPin()->getConn())
								if(((Led*)pComp_test)->getPin()->getOutputPin()->getComponent()->getLevel() == -1)
								{
									test = false ;
								}
						}
					}
					else 
					{
						k = ((Gate*)pComp_test)->getInputPinsCount();
						for(int p=0 ; p<k ; p++)
						{
							if(((Gate*)pComp_test)->getInputPin(p+1)->getOutputPin()->getComponent()->getLevel() == -1)
							{
								test = false ;
							}
						}
					}
			
					if(pComp_test->getLevel() == -1 && test)
					{
						pComp = pComp_test ;
						break;
					}
				}
			}
		}
		
		int* in_pin_num = new int[k] ;
		if(pComp != NULL)
		{
			if(pComp->getName() == LED)
			{
				pComp->setLevel(((Led*)pComp)->getPin()->getOutputPin()->getComponent()->getLevel() +1);
			}
			else if(pComp->getName() != SWITCH)
			{
				for(int p=0 ; p<k ; p++)
				{
					int m = ((Gate*)pComp)->getInputPin(p+1)->getOutputPin()->getComponent()->getLevel();
					in_pin_num[p] = m ; 
				}
				int max = in_pin_num[0] ;
				for(int n=1 ; n<k ; n++)
				{
					if(in_pin_num[n]>max)
						max = in_pin_num[n];
				}
				pComp->setLevel(max+1);
			}
		}

		/*int compExcCount_tmp = WiresExcCount ;
		for (int u=0 ; u < compExcCount_tmp ; u++)
		{
			if (CompListWiresExc[u]->getLevel() != -1)
			{
				CompListWiresExc[u] = NULL;
				CompListWiresExc[u] = CompListWiresExc[WiresExcCount-1];
				WiresExcCount--;
			}
		}*/
		/*if(WiresExcCount == 0)
			end = true ;*/
		for(int pp=0 ; pp<WiresExcCount ; pp++)
		{
			if(CompListWiresExc[pp]->getLevel() == -1)
			{
				end = false ;
				break ;
			}
			else
				end = true;
		}
	}
}
//=============================================================================
void ApplicationManager::fillLevels()
{
	ExcludeWires();

	if (WiresExcCount != 0)
	{
		//make Level Zero (Level of all switches)
		determineLevelZero();

		//determine level 1 with 2 kinds of gates .. the ones who has connections errors and that who are coming from level 0
		checkForFirstLevel() ;

		//put the gates in their level
		setLevels();

		int max = 0;

		for (int i=0 ; i<WiresExcCount ; i++)
		{
			if ( CompListWiresExc[i]->getLevel() > max)
				max = CompListWiresExc[i]->getLevel();
		}

		LevelCount = max + 1;

		for (int i=0 ; i<LevelCount ; i++)
		{
			LevelList[i] = new Level;
			LevelList[i]->setID(i);
		}

		for (int i=0 ; i<WiresExcCount ; i++)
			LevelList[ CompListWiresExc[i]->getLevel() ] -> AddToLevel(CompListWiresExc[i]);
	}
}
//===================================================================================================
void ApplicationManager::evacuateLevels()
{
	LevelCount = 0;
	WiresExcCount = 0;

	for (int i=0 ; i<CompCount ; i++)
		CompList[i]->setLevel(-1);
}
//===================================================================================================
void ApplicationManager::AddWiresExcComp(Component* r_Comp)
{
	CompListWiresExc[WiresExcCount] = r_Comp;
	WiresExcCount++;
}


//===================================================================================================
void ApplicationManager::UpdateInterface()
{
	ptrOutput->changeBuffering(true);
	//drawing the interface
	ptrOutput->drawInterface(SimuMode);

	//loop to draw all the components we have in the design
	for(int i=0 ; i<CompCount ; i++)
		CompList[i]->Draw() ;
	ptrOutput->changeBuffering(false);
}

//====================================================================================================
void ApplicationManager::ExecuteUserAction(ActionType Act, Point p)
{
	Action* pAct = NULL;
	bool valid = false ;
	switch(Act)
	{
		case(Add_AND_2):
		case(Add_AND_3):
		case(Add_AND_4):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddANDgate(p , Act , this);
			break;

		case(Add_OR_2):
		case(Add_OR_3):
		case(Add_OR_4):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddORgate(p , Act , this);
			break;

		case(Add_NAND_2):
		case(Add_NAND_3):
		case(Add_NAND_4):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddNANDgate(p , Act , this);
			break;

		case(Add_NOR_2):
		case(Add_NOR_3):
		case(Add_NOR_4):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddNORgate(p,Act,this);
			break;

		case(Add_XOR_2):
		case(Add_XOR_3):
		case(Add_XOR_4):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddXORgate(p , Act , this);
			break;

		case(Add_XNOR_2):
		case(Add_XNOR_3):
		case(Add_XNOR_4):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddXNORgate(p , Act , this);
			break;

		case(Add_WIRE):
			pAct = createWire();
			break;

		case(Add_SWITCH):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddSWITCH(p ,this);
			break;

		case(Add_LED):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddLED(p , this);
			break;

		case(Add_BUFFER):
			p = ptrInput->getClick() ;	
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddBuffer(p , this);
			break;

		case(Add_NOT):
			p = ptrInput->getClick() ;
			valid = CheckValidity(p) ;
			if(valid)
				pAct = new AddNOTgate(p , this);
			break;

		case(EXIT):
			pAct = new Exit;
			break; 

		case(UNDO):
			pAct = new Undo ;
			break;

		case(REDO):
			pAct = new Redo;
			break;

		case(AUTO_ALIGNMENT):
			pAct = new AutoAlignment;
			break;

		case(TRUTH_TABLE):
			pAct = new Truth_Table;
			break;

		case(ERROR_DETECTOR):
			pAct = new ErrorDetector;
			break;

		case(SAVE):
			pAct = new Save;
			break;

		case(LOAD):
			pAct = new Load ;
			break ;

		case(CREATE_NEW_GATE):
			//pAct = new UserDefined ;
			break; 

		case(SELECT_COMPONENT):
			DoCompAction();
			break;

		case(MOVE):
			pAct = new Move(getComponentByPoint(p));
			break;

		case(REMOVE):
			pAct = new Remove;
			break;

		case(SIMULATION_MODE):
			pAct = new SimulationMode ;
			break ;

		case(DESIGN_MODE):
			//pAct = new DesignMode;
			break ;

		case(CHANGE_LABEL):
			pAct = new ChangeLabel ;
			break;

		default:
			pAct = NULL;
			break;
	}

	//executing the action required
	if(pAct != NULL)
		pAct->Execute(this) ;
	
}
//================================================================================================================================
Component* ApplicationManager::getselectedcomponent()
{

	return CompList[selected];
}
//==================================================================================
ActionType ApplicationManager :: getUserAction(Point & p) //This fn. can detect each Snake-Head-Action, and return this action's type:
{
	//ActionType r_Action;
	Point r_P;
	 p = ptrInput->getClick();
	
	 // 1st Area -----> Add_ Component Area:
	if( (p.x > 10 && p.x < 84) && (p.y > 54 && p.y < 108) )
		return Add_BUFFER;

	else if( (p.x > 84 && p.x < 158) && (p.y > 54 && p.y < 108) )
		return Add_NOT;

	else if( (p.x > 10 && p.x < 84) && (p.y > 108 && p.y < 162) )
	{
		r_P.x = 74;
		r_P.y = 150;
		ptrOutput->drawSubMenu(r_P);
		p = ptrInput->getClick();
		if( (p.x > 74 && p.x < 194) && (p.y > 150 && p.y < 190) )
			return Add_AND_2;
		else if( (p.x > 74 && p.x < 194) && (p.y > 190 && p.y < 230) )
			return Add_AND_3;
		else if( (p.x > 74 && p.x < 194) && (p.y > 230 && p.y < 270) )
			return Add_AND_4;
		else
			return CANCEL;
	}

	else if( (p.x > 84 && p.x < 158) && (p.y > 108 && p.y < 162) )
	{
		r_P.x = 147;
		r_P.y = 150;
		ptrOutput->drawSubMenu(r_P);
		p = ptrInput->getClick();
		if( (p.x > 145 && p.x < 265) && (p.y > 150 && p.y < 190) )
			return Add_NAND_2;
		else if( (p.x > 145 && p.x < 265) && (p.y > 190 && p.y < 230) )
			return Add_NAND_3;
		else if( (p.x > 145 && p.x < 265) && (p.y > 230 && p.y < 270) )
			return Add_NAND_4;
		else
			return CANCEL;
	}
	
	else if( (p.x > 10 && p.x < 84) && (p.y > 162 && p.y < 216) )
	{
		r_P.x = 74;
		r_P.y = 204;
		ptrOutput->drawSubMenu(r_P);
		p = ptrInput->getClick();
		if( (p.x > 74 && p.x < 194) && (p.y > 204 && p.y < 244) )
			return Add_OR_2;
		else if( (p.x > 74 && p.x < 194) && (p.y > 244 && p.y < 284) )
			return Add_OR_3;
		else if( (p.x > 74 && p.x < 194) && (p.y > 284 && p.y < 324) )
			return Add_OR_4;
		else
			return CANCEL;
	}
	
	else if( (p.x > 84 && p.x < 158) && (p.y > 162 && p.y < 216) )
	{
		r_P.x = 145;
		r_P.y = 204;
		ptrOutput->drawSubMenu(r_P);
		p = ptrInput->getClick();
		if( (p.x > 145 && p.x < 265) && (p.y > 204 && p.y < 244) )
			return Add_NOR_2;
		else if( (p.x > 145 && p.x < 265) && (p.y > 244 && p.y < 284) )
			return Add_NOR_3;
		else if( (p.x > 145 && p.x < 265) && (p.y > 284 && p.y < 324) )
			return Add_NOR_4;
		else
			return CANCEL;
	}
	
	else if( (p.x > 10 && p.x < 84) && (p.y > 216 && p.y < 270) )
	{
		r_P.x = 74;
		r_P.y = 258;
		ptrOutput->drawSubMenu(r_P);
		p = ptrInput->getClick();
		if( (p.x > 74 && p.x < 194) && (p.y > 258 && p.y < 298) )
			return Add_XOR_2;
		else if( (p.x > 74 && p.x < 194) && (p.y > 298 && p.y < 338) )
			return Add_XOR_3;
		else if( (p.x > 74 && p.x < 194) && (p.y > 338 && p.y < 378) )
			return Add_XOR_4;
		else
			return CANCEL;
	}
	else if( (p.x > 84 && p.x < 158) && (p.y > 216 && p.y < 270) )
	{
		r_P.x = 145;
		r_P.y = 258;
		ptrOutput->drawSubMenu(r_P);
		p = ptrInput->getClick();
		if( (p.x > 145 && p.x < 265) && (p.y > 258 && p.y < 298) )
			return Add_XNOR_2;
		else if( (p.x > 145 && p.x < 265) && (p.y > 298 && p.y < 338) )
			return Add_XNOR_3;
		else if( (p.x > 145 && p.x < 265) && (p.y > 338 && p.y < 378) )
			return Add_XNOR_4;
		else
			return CANCEL;
	}
	
	else if( (p.x > 10 && p.x < 84) && (p.y > 324 && p.y < 378) )
		return Add_WIRE;
	
	else if( (p.x > 10 && p.x < 84) && (p.y > 378 && p.y < 432) )
		return Add_SWITCH;
	
	else if( (p.x > 84 && p.x < 158) && (p.y > 378 && p.y < 432) )
		return Add_LED;
	
	// 2nd area --------> Functions Bottons:
	else if( (p.x > 10 && p.x < 39) && (p.y > 10 && p.y < 49) )
		return UNDO;
	
	else if( (p.x > 39 && p.x < 68) && (p.y > 10 && p.y < 49) )
		return REDO;
	
	else if( (p.x > 68 && p.x < 97) && (p.y > 10 && p.y < 49) )
		return SAVE;
	
	else if( (p.x > 97 && p.x < 126) && (p.y > 10 && p.y < 49) )
		return LOAD;
	
	else if( (p.x > 126 && p.x < 158) && (p.y > 10 && p.y < 49) )
		return EXIT;
    //== == == ==
	/*else if( (p.x > 10 && p.x < 158) && (p.y > 437 && p.y < 472) )
		return Action* = new Action(Act, Comp);*/
	
	else if( (p.x > 10 && p.x < 158) && (p.y > 477 && p.y < 512) )
		return SIMULATION_MODE;
	
	else if( (p.x > 10 && p.x < 158) && (p.y > 517 && p.y < 552 ) )
		return AUTO_ALIGNMENT;

	else if( (p.x > 10 && p.x < 158) && (p.y > 557 && p.y < 592) )
		return ERROR_DETECTOR;
	else if( (p.x > 10 && p.x < 158) && (p.y > 437 && p.y < 552) )
		return CREATE_NEW_GATE;
	
	// 3rd Area ---------> The Design Area:
	else  //( (p.x > 167 && p.x < 1036) && (p.y > 0 && p.y < 602) && (CompCount!=0))
	{
		int i;
		for (i=0 ; i < CompCount ; i++)
			{
				if (CompList[i]->IsMatch(p))
					{
						selected = i;
						return SELECT_COMPONENT;
					}
			}
		return  CANCEL;
	}
		

}


//----------------------------------------------------------------------------------------------------------------------

void ApplicationManager ::DoCompAction()
{
	ptrOutput->Highlight(getselectedcomponent()->getCurrentGfxInfo().UpLeft,getselectedcomponent()->getCurrentGfxInfo().DownRight);
	show_status_bar();
	Point p2 = ptrInput->getClick();


 if (!getSimulationMode())
	{
		if ( (p2.x > getselectedcomponent()->getCurrentGfxInfo().UpLeft.x) && (p2.x < getselectedcomponent()->getCurrentGfxInfo().DownRight.x) )
		{
			if ( (p2.y > getselectedcomponent()->getCurrentGfxInfo().UpLeft.y) && (p2.y < getselectedcomponent()->getCurrentGfxInfo().DownRight.y) )
			{
				ExecuteUserAction(MOVE,p2);
			}
		}
		else{

		switch (getselectedcomponent()->getName())
			{
				case AND_2:
				case AND_3:
				case AND_4:
				case NAND_2:
				case NAND_3:
				case NAND_4:
				case OR_2:
				case OR_3:
				case OR_4:
				case NOR_2:
				case NOR_3:
				case NOR_4:
				case XOR_2:
				case XOR_3:
				case XOR_4:
				case XNOR_2:
				case XNOR_3:
				case XNOR_4:
				case BUFFER:
				case NOT:
					if ( (p2.y > 608) && (p2.y < 638) )
					{
						if ( (p2.x > 736) && (p2.x < 856) ) // edit Label	
							ExecuteUserAction( CHANGE_LABEL,p2);
						
						else if ((p2.x > 586) && (p2.x < 706))
							ExecuteUserAction( REMOVE,p2);

						else if ((p2.x >886 ) && (p2.x < 1006))
							ExecuteUserAction( TRUTH_TABLE,p2);
					}
					else 
						ExecuteUserAction(CANCEL,p2);
					
					break;
 
				case LED:
				case SWITCH:
					
					if ( (p2.y > 608) && (p2.y < 638) )
					{
						if ( (p2.x > 736) && (p2.x < 856) ) // edit Label
							ExecuteUserAction(CHANGE_LABEL,p2);
						
						else if ((p2.x > 886) && (p2.x < 1006))
							ExecuteUserAction(REMOVE,p2);
					}
					else 
						ExecuteUserAction(CANCEL,p2);
					break;

				case WIRE:
					if ( (p2.y > 608) && (p2.y < 638) )
					{
						if ((p2.x > 886) && (p2.x < 1006))
							
							ExecuteUserAction(REMOVE,p2);
					}
					else 
						ExecuteUserAction(CANCEL,p2);
					break;
					default :
					UpdateInterface();
					getUserAction(p2);
		}
		}
	}
	else if (getSimulationMode())
	{
		switch (getselectedcomponent()->getName())
			{
				case AND_2:
				case AND_3:
				case AND_4:
				case NAND_2:
				case NAND_3:
				case NAND_4:
				case OR_2:
				case OR_3:
				case OR_4:
				case NOR_2:
				case NOR_3:
				case NOR_4:
				case XOR_2:
				case XOR_3:
				case XOR_4:
				case XNOR_2:
				case XNOR_3:
				case XNOR_4:
				case BUFFER:
				case NOT:
					if ( (p2.y > 608) && (p2.y < 638) )
					{
						if ( (p2.x > 736) && (p2.x < 856) ) // edit Label
						
							ExecuteUserAction(CHANGE_LABEL,p2);
						
						else if ((p2.x > 886) && (p2.x < 1006))
							
							ExecuteUserAction(TRUTH_TABLE,p2);
					}
					else 
						ExecuteUserAction(CANCEL,p2);
					break;
 
				case LED:
					
					if ( (p2.y > 608) && (p2.y < 638) )
					{
						if ( (p2.x > 886) && (p2.x < 1006) ) // edit Label
						
							 ExecuteUserAction(CHANGE_LABEL,p2);
					}
					else 
						ExecuteUserAction(CANCEL,p2);
					break;

				case WIRE:
					
						ExecuteUserAction(CANCEL,p2);
					break;
				case SWITCH:
					SimulationMode* S;
					S->changeSwitchSignal(getselectedcomponent());
					break;
			}
	}
}
//=======================================================================================================================================

void ApplicationManager::show_status_bar()
{
	int inc = 30;
	Point p;
	p.x = inc;         p.y = 607;
	ptrOutput -> drawStatusBar();
	
		switch (getselectedcomponent()->getName())
			{
				case AND_2:
				case AND_3:
				case AND_4:
				case NAND_2:
				case NAND_3:
				case NAND_4:
				case OR_2:
				case OR_3:
				case OR_4:
				case NOR_2:
				case NOR_3:
				case NOR_4:
				case XOR_2:
				case XOR_3:
				case XOR_4:
				case XNOR_2:
				case XNOR_3:
				case XNOR_4:
				case BUFFER:
				case NOT:
			
				{
					if (!getSimulationMode())
					{
					ptrOutput -> drawImageStatusBar (getselectedcomponent()->getUrl() , false , p);
					 p.x = 68 + inc;       
					 ptrOutput -> printStringStatusBar ("Type :" , p);

					 p.x = 110 + inc;       
					 ptrOutput -> printStringStatusBar (getselectedcomponent()->getType() , p);

					 p.x = 220 + inc;
					 ptrOutput -> printStringStatusBar ("Lable :" , p);

					 p.x = 267 + inc;
					 ptrOutput -> printStringStatusBar (getselectedcomponent()->getCurrentLabel() , p);

					 p.x = 420 + inc;
					 ptrOutput -> printStringStatusBar ("IC :" , p);
					 p.x = 445 + inc;
					 ptrOutput -> printStringStatusBar (getselectedcomponent()->getIC()  , p);

					 p.x = 1036 - 300;
					 ptrOutput -> drawImageStatusBar ("images//EditButton.jpg" ,true , p);

					 p.x= 1036 -450;
					 ptrOutput -> drawImageStatusBar ("images//RemoveButton.jpg" , true , p);

					 p.x = 1036 - 150;
					 ptrOutput -> drawImageStatusBar ("images//TruthTable.jpg" , true , p);



					}
					else
					{
						ptrOutput -> drawImageStatusBar (getselectedcomponent()->getUrl() , false , p);

						 p.x = 68 + inc;       
						 ptrOutput -> printStringStatusBar ("Type:" , p);

						 p.x = 110 + inc;       
						 ptrOutput -> printStringStatusBar ( getselectedcomponent()->getType() , p);

						 p.x = 220 + inc;
						 ptrOutput -> printStringStatusBar ("Lable:" , p);

						 p.x = 267 + inc;
						 ptrOutput -> printStringStatusBar (getselectedcomponent()->getCurrentLabel() , p);
						 p.x = 420 + inc;
						 ptrOutput -> printStringStatusBar ("IC :" , p);
						 p.x = 445 + inc;
						 ptrOutput -> printStringStatusBar (getselectedcomponent()->getIC()  , p);

						 p.x = 1036 - 150;
						 ptrOutput -> drawImageStatusBar ("images//TruthTable.jpg" ,true , p);
						 p.x = 1036 - 300;
						 ptrOutput -> drawImageStatusBar ("images//EditButton.jpg" ,true , p);

					}
				}
				break;

				case LED:
				case SWITCH:
				{
					if (!getSimulationMode())
					{
						ptrOutput -> drawImageStatusBar (getselectedcomponent()->getUrl() , false , p);

						 p.x = 68 + inc;       
						 ptrOutput -> printStringStatusBar ("Type:" , p);

						 p.x = 110 + inc;       
						 ptrOutput -> printStringStatusBar ( getselectedcomponent()->getType() , p);

						 p.x = 220 + inc;
						 ptrOutput -> printStringStatusBar ("Lable:" , p);

						 p.x = 267 + inc;
						 ptrOutput -> printStringStatusBar (getselectedcomponent()->getCurrentLabel() , p);

						 p.x = 1036 - 300;
						 ptrOutput -> drawImageStatusBar ("images//EditButton.jpg" ,true , p);

						 p.x = 1036 - 150;
						 ptrOutput -> drawImageStatusBar ("images//RemoveButton.jpg" , true , p);

					
					}
					else
					{
						ptrOutput -> drawImageStatusBar (getselectedcomponent()->getUrl() , false , p);

						 p.x = 68 + inc;       
						 ptrOutput -> printStringStatusBar ("Type:" , p);

						 p.x = 110 + inc;       
						 ptrOutput -> printStringStatusBar ( getselectedcomponent()->getType() , p);

						 p.x = 220 + inc;
						 ptrOutput -> printStringStatusBar ("Lable:" , p);

						 p.x = 267 + inc;
						 ptrOutput -> printStringStatusBar (getselectedcomponent()->getCurrentLabel() , p);
						 p.x = 1036 - 150;
						 ptrOutput -> drawImageStatusBar ("images//EditButton.jpg" , true , p);
					}
				}
				break;

				case WIRE:         //to be continued
				{
						if (!getSimulationMode())
						{
							p.x = 10 + inc;       
							ptrOutput -> printStringStatusBar ("Source component : " , p);

							p.x = 142 + inc;       
							ptrOutput -> printStringStatusBar ( ((Wire*)getselectedcomponent())->getOutputPin()->getComponent()->getCurrentLabel() , p);

							p.x = 322 + inc;
							ptrOutput -> printStringStatusBar ("Target component :" , p);

							p.x = 450 + inc;
							ptrOutput -> printStringStatusBar (((Wire*)getselectedcomponent())->getInputPin()->getComponent()->getCurrentLabel() , p);
							
							p.x = 1036 - 150;
							ptrOutput -> drawImageStatusBar ("images//RemoveButton.jpg" , true , p);
						}
						else 
						{
							p.x = 10 + inc;       
							ptrOutput -> printStringStatusBar ("Source component : " , p);

							p.x = 142 + inc;       
							ptrOutput -> printStringStatusBar ( ((Wire*)getselectedcomponent())->getOutputPin()->getComponent()->getCurrentLabel() , p);

							p.x = 322 + inc;
							ptrOutput -> printStringStatusBar ("Target component :" , p);

							p.x = 450 + inc;
							ptrOutput -> printStringStatusBar (((Wire*)getselectedcomponent())->getInputPin()->getComponent()->getCurrentLabel() , p);

							p.x=630 + inc; 
							if ( ((Wire*)getselectedcomponent())->getInputPin()->getStatus()== LOW)
							ptrOutput -> printStringStatusBar ("Signal = 0" , p);
							else
							ptrOutput -> printStringStatusBar ("Signal = 1" , p);
						}
				}
				break;
}
}

//======================================================================================
bool ApplicationManager::CheckValidity (Point mouseClick)
{
	bool test = false;
	Point newPoint;
	Point p;			p.x=30;

	if ( ( mouseClick.x-(int)(0.5*75) ) <= 168)
	{
		getOutput()->printStringStatusBar("Can not deploy here , invalid place" , p);
		getOutput()->MessagePause(2000);
		return false;
	}
	if ( (mouseClick.y+50) >= 602)
	{
		getOutput()->printStringStatusBar("Can not deploy here , invalid place" , p);
		getOutput()->MessagePause(2000);
		return false;
	}
	// (1)--->Check for first corner:
	newPoint.x = mouseClick.x-10;
	newPoint.y = mouseClick.y-10;
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
	}

	// (2)--->Check for the second corner:
	newPoint.x = mouseClick.x+85;
	newPoint.y = mouseClick.y-10;
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
	}

	// (3)--->Check for the thierd corner:
	newPoint.x = mouseClick.x-10;
	newPoint.y = mouseClick.y+60;
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
	}

	// (4)--->Check for the forth corner:
	newPoint.x = mouseClick.x+85;
	newPoint.y = mouseClick.y+60;
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
	}
	return true;
}

//=========================================================================================

Component* ApplicationManager::getComponentByPoint(Point p)
{
	for(int i=0 ; i<CompCount ; i++)
	{
		if(p.x > CompList[i]->getCurrentGfxInfo().UpLeft.x && p.x<CompList[i]->getCurrentGfxInfo().DownRight.x && p.y>CompList[i]->getCurrentGfxInfo().UpLeft.y && p.y < CompList[i]->getCurrentGfxInfo().DownRight.y)
			return CompList[i] ;
	}
	return NULL ;
}

//===========================================================================================

void ApplicationManager::simulate()
{
	//making the levels of the design
	evacuateLevels() ; 
	fillLevels() ;

	//loop over the levels to operate them
	//we don't operate level 1 as it is the level of switches

	for(int i=0 ; i<LevelCount ; i++)
	{
		LevelList[i]->OperateLevel(this);
	}
}

//=============


Action* ApplicationManager::createWire()
{
	Point P1 = getInput()->getClick();
	Point P2 = getInput()->getClick();
	Component* Source = getComponentByPoint(P1);
	Component* Destination = getComponentByPoint(P2);
	InputPin* tempDestPin;
	OutputPin* tempSourcePin;
	bool test = false;
	Point p;		p.x = 40;

	if ( (dynamic_cast<Led*>(Source) != NULL) || Source == NULL)
	{
		getOutput()->printStringStatusBar("Invalid Source Component" , p);
		getOutput()->MessagePause(2000);
		return NULL;
	}

	if ( (dynamic_cast<Switch*>(Destination) != NULL) || Destination == NULL)
	{
		getOutput()->printStringStatusBar("Invalid destination Component" , p);
		getOutput()->MessagePause(2000);
		return NULL;
	}

	if(P2.x <= P1.x)
		return NULL;

		if ( dynamic_cast<Switch*>(Source) != NULL )
    	{
			tempSourcePin = ((Switch*)Source)->getPin();

			if (dynamic_cast<Led*>(Destination) != NULL)
			{
				tempDestPin = ((Led*)Destination)->getPin();
				test = ((Led*)Destination)->connectTo(tempSourcePin);
			}
			else 
			{
				test = ((Gate*)Destination)->ConnectInputPinTo(tempSourcePin);
				tempDestPin = ((Gate*)Destination)->getInputPin( ((Gate*)Destination)->getConnectedInputs() );
			}
			if(test)
				test = ((Switch*)Source)->ConnectTo(tempDestPin);
	}

	else 
	{
		//source is a gate
		tempSourcePin = ((Gate*)Source)->getOutputPin();

		if (dynamic_cast<Led*>(Destination) != NULL)
		{
			tempDestPin = ((Led*)Destination)->getPin();
			test = ((Led*)Destination)->connectTo(tempSourcePin);
		}
		else
		{
			test = ((Gate*)Destination)->ConnectInputPinTo(tempSourcePin);
			tempDestPin = ((Gate*)Destination)->getInputPin( ((Gate*)Destination)->getConnectedInputs() );
		}

		if(test)
			test = ((Gate*)Source)->ConnectOutputPinTo(tempDestPin);
	}	
	if(test)
	{
		Action* pAct = new AddWire(tempSourcePin , tempDestPin ,this);
		return pAct;
	}
	getOutput()->printStringStatusBar("This Operation is INVALID, This component reached the max. fanOuts",p);
	getOutput()->MessagePause(2000);
	return NULL;

}

//==========================================================================================================

bool ApplicationManager::CheckValidity (Point mouseClick,Component*Comp)
{
	bool test = false;
	Point newPoint;
	Point p;			p.x=30;

	if ( ( mouseClick.x-(int)(0.5*75) ) <= 168)
	{
		return false;
	}
	if ( (mouseClick.y+50) >= 602)
	{		
		return false;
	}

	// (1)--->Check for first corner:
	newPoint.x = mouseClick.x-10;
	newPoint.y = mouseClick.y-10;
	for(int i=0; i<CompCount; i++)
		if (Comp!=CompList[i])
		{
	{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
	}
		}
	// (2)--->Check for the second corner:
	newPoint.x = mouseClick.x+85;
	newPoint.y = mouseClick.y-10;
	for(int i=0; i<CompCount; i++)
	{
		if (Comp!=CompList[i])
		{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
		}
	}

	// (3)--->Check for the thierd corner:
	newPoint.x = mouseClick.x-10;
	newPoint.y = mouseClick.y+60;
	for(int i=0; i<CompCount; i++)
	{
		if (Comp!=CompList[i])
		{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
		}
	}

	// (4)--->Check for the forth corner:
	newPoint.x = mouseClick.x+85;
	newPoint.y = mouseClick.y+60;
	for(int i=0; i<CompCount; i++)
	{
		if (Comp!=CompList[i])
		{
		if(CompList[i]->getName() != WIRE)
		{
			test = CompList[i]->IsMatch(newPoint);
			if (test == true) return !test;
		}
		}
	}
	return true;
}
//=========================================================================================
int ApplicationManager::MaxID()
{
	int max = CompList[0]->getID();
	for(int i=1; i<CompCount; i++)
	{
		if(CompList[0]->getID() > max)
			max = CompList[i]->getID();
	}
	return max;
}
//=======================================================================
ActionType ApplicationManager::SelectSimulationAction()
{
	Point p = getInput()->getClick() ;

	if(p.x >10 && p.x <158)
	{
		if(p.y > 50 && p.y < 85)
		{
			return EXIT ;
		}
		else if(p.y >90 && p.y < 125)
		{
			return SAVE ;
		}
		else if(p.y>130 && p.y <165)
		{
			return DESIGN_MODE ;
		}
		else if(p.y >170 && p.y < 205)
		{
			return TRUTH_TABLE ;
		}
		else
		{
			return CANCEL ;
		}
	}
	else
	{
		int i;
		for (i=0 ; i < getCompCount() ; i++)
			{
				if (CompList[i]->IsMatch(p))
					{
						setSelected(i);
						return SELECT_COMPONENT;
					}
			}
		return  CANCEL;
			}
		}

//=================================
void ApplicationManager::setSelected(int  i )
{
	selected = i;
}
