#include <vector>

#include "CMUgraphicsLib\CMUgraphics.h"
#include "CMUgraphicsLib\auxil.h"	// where Pause is found
#include "Includes.h"

void DoAction(int & i, ActionType Action, Point click, vector<ScreenElement>& Components, Output* & Out, Input* & In );
bool CheckValidPlace (int i2,Point mouseClick , vector<ScreenElement>& Components);
void checkIfSelected (int & i2, Input* ptrInput , Output* ptrOutput , Point mouseClick , vector <ScreenElement>& Components /*the vector of components*/ );
void UpdateInterface(Output* & Out, vector<ScreenElement>& Components);

int main()
{
	Output* Out = new Output;
	Input* In = new Input(Out->getWindow(),Out);
	Out->drawInterface();
	Point P;
	int iterator=0;
	ActionType Action;
	vector <ScreenElement> Components;
	do
	{
		Action = ->getUserAction(P);
		DoAction(iterator ,Action, P, Components, Out, In);
		UpdateInterface(Out, Components);
	}while(Action != Exit);

	return 0;
}

void UpdateInterface(Output* & Out, vector<ScreenElement>& Components)
{
	Out->drawInterface();
	for( int i=0; i< Components.size() ; i++)
		if(Components[i].component != WIRE)
			Out->drawComponent(Components[i].URL , Components[i].Label , Components[i].GfxInfo.Center);
		else
			Out->drawLines(Components[i].GfxInfo.UpLeft, Components[i].GfxInfo.DownRight);
}

bool CheckValidPlace (int i2,Point mouseClick , vector<ScreenElement>& Components)
{
	int new_up_left_x = mouseClick.x;
	int new_up_left_y = mouseClick.y;

	int new_down_right_x = mouseClick.x + 75;
	int new_down_right_y = mouseClick.y + 50;

	if (i2 != 0)
	{
		int i;
		for (i=0 ; i < Components.size() ; i++)
		{
			if( (Components[i].GfxInfo.UpLeft.x < new_up_left_x) && (new_up_left_x < Components[i].GfxInfo.DownRight.x) &&
				(Components[i].GfxInfo.UpLeft.y < new_up_left_y) && (new_up_left_y < Components[i].GfxInfo.DownRight.y) 
				                                                 ||
			 (Components[i].GfxInfo.UpLeft.x < new_down_right_x) && (new_down_right_x < Components[i].GfxInfo.DownRight.x) &&
			 (Components[i].GfxInfo.UpLeft.y < new_down_right_y) && (new_down_right_y < Components[i].GfxInfo.DownRight.y)
			                                                     ||
			    (Components[i].GfxInfo.UpLeft.x < new_up_left_x) && (new_up_left_x < Components[i].GfxInfo.DownRight.x) &&
			 (Components[i].GfxInfo.UpLeft.y < new_down_right_y) && (new_down_right_y < Components[i].GfxInfo.DownRight.y)
			                                                     ||
			    (Components[i].GfxInfo.UpLeft.y < new_up_left_y) && (new_up_left_y < Components[i].GfxInfo.DownRight.y) &&
			 (Components[i].GfxInfo.UpLeft.x < new_down_right_x) && (new_down_right_x < Components[i].GfxInfo.DownRight.x) )
				return false;                                            
		}
	}

	return true;
}


void DoAction(int& i, ActionType Action, Point click, vector<ScreenElement>& Components, Output* & Out, Input* & In )
{   
	ScreenElement* tmp;
	Point P;    
	switch(Action)
		{
			case SimulationMode: 
			case DesignMode:
			case Allignmemt:     
			case errorDetector:
			case CreateNewGate:
			case Exit:           
			case Save:
			case Load:           
			case Undo:
			case Redo:
				P.x = 5;
				P.y = 610;
				Out->drawStatusBar();
				Out->printStringStatusBar("These Action Will be Completed in the Second phase ISA", P);
				Pause(2000);
				break;
			case SelectComponent:
				checkIfSelected(i,In, Out, click , Components);
				break;
			default :
				{
					//if Other Action
					Point p2;
				    p2.x = 5;
					p2.y = 610;
					Out->drawStatusBar();
					Out->printStringStatusBar("Click on any point on the design area to add the selected componenet", p2);
					P=In->getClick();
					Out->drawStatusBar();
					bool ValidPlace = CheckValidPlace(i, P, Components);
					if(ValidPlace)
					{
						
						tmp = new ScreenElement;
						Components.push_back(*tmp);
						switch (Action)
						{
							//Add and gates
							case Add_AND_2 :
								Out->drawComponent("images//AND.jpg","AND_2",P);
								Components[i].component = AND_2;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "AND_2";
								Components[i].Name = "AND_2";
								Components[i].URL = "images//AND.jpg";
								i++;
								break;
							case Add_AND_3 :
								Out->drawComponent("images//AND3.jpg","AND_3",P);
								Components[i].component = AND_3;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "AND_3";
								Components[i].Name = "AND_3";
								Components[i].URL = "images//AND3.jpg";
								i++;
								break;
							case Add_AND_4 :
								Out->drawComponent("images//AND4.jpg","AND_4",P);
								Components[i].component = AND_4;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "AND_4";
								Components[i].Name = "AND_4";
								Components[i].URL = "images//AND4.jpg";
								i++;
								break;

							// Add nand gates
							case Add_NAND_2 :
								Out->drawComponent("images//NAND.jpg","NAND_2",P);
								Components[i].component = NAND_2;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NAND_2";
								Components[i].Name = "NAND_2";
								Components[i].URL = "images//NAND.jpg";
								i++;
								break;
							case Add_NAND_3 :
								Out->drawComponent("images//NAND3.jpg","NAND_3",P);
								Components[i].component = NAND_3;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NAND_3";
								Components[i].Name = "NAND_3";
								Components[i].URL = "images//NAND3.jpg";
								i++;
								break;
							case Add_NAND_4 :
								Out->drawComponent("images//NAND4.jpg","NAND_4",P);
								Components[i].component = NAND_4;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NAND_4";
								Components[i].Name = "NAND_4";
								Components[i].URL = "images//NAND4.jpg";
								i++;
								break;

							//Add or gates
							case Add_OR_2 :
								Out->drawComponent("images//OR.jpg","OR_2",P);
								Components[i].component = OR_2;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "OR_2";
								Components[i].Name = "OR_2";
								Components[i].URL = "images//OR.jpg";
								i++;
								break;
							case Add_OR_3 :
								Out->drawComponent("images//OR3.jpg","OR_3",P);
								Components[i].component = OR_3;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "OR_3";
								Components[i].Name = "OR_3";
								Components[i].URL = "images//OR3.jpg";
								i++;
								break;
							case Add_OR_4 :
								Out->drawComponent("images//OR4.jpg","OR_4",P);
								Components[i].component = OR_4;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "OR_4";
								Components[i].Name = "OR_4";
								Components[i].URL = "images//OR4.jpg";
								i++;
								break;

							//Add nor gates
							case Add_NOR_2 :
								Out->drawComponent("images//NOR.jpg","NOR_2",P);
								Components[i].component = NOR_2;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NOR_2";
								Components[i].Name = "NOR_2";
								Components[i].URL = "images//NOR.jpg";
								i++;
								break;
							case Add_NOR_3 :
								Out->drawComponent("images//NOR3.jpg","NOR_3",P);
								Components[i].component = NOR_3;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NOR_3";
								Components[i].Name = "NOR_3";
								Components[i].URL = "images//NOR3.jpg";
								i++;
								break;
							case Add_NOR_4 :
								Out->drawComponent("images//NOR4.jpg","NOR_4",P);
								Components[i].component = NOR_4;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NOR_4";
								Components[i].Name = "NOR_4";
								Components[i].URL = "images//NOR4.jpg";
								i++;
								break;

							//Add xor gates
							case Add_XOR_2 :
								Out->drawComponent("images//XOR.jpg","XOR_2",P);
								Components[i].component = XOR_2;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "XOR_2";
								Components[i].Name = "XOR_2";
								Components[i].URL = "images//XOR.jpg";
								i++;
								break;
							case Add_XOR_3 :
								Out->drawComponent("images//XOR3.jpg","XOR_3",P);
								Components[i].component = XOR_3;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "XOR_3";
								Components[i].Name = "XOR_3";
								Components[i].URL = "images//XOR3.jpg";
								i++;
								break;
							case Add_XOR_4 :
								Out->drawComponent("images//XOR4.jpg","XOR_4",P);
								Components[i].component = XOR_4;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "XOR_4";
								Components[i].Name = "XOR_4";
								Components[i].URL = "images//XOR4.jpg";
								i++;
								break;

							//Add xnor gates
							case Add_XNOR_2 :
								Out->drawComponent("images//XNOR.jpg","XNOR_2",P);
								Components[i].component = XNOR_2;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "XNOR_2";
								Components[i].Name = "XNOR_2";
								Components[i].URL = "images//XNOR.jpg";
								i++;
								break;
							case Add_XNOR_3 :
								Out->drawComponent("images//XNOR3.jpg","XNOR_3",P);
								Components[i].component = XNOR_3;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "XNOR_3";
								Components[i].Name = "XNOR_3";
								Components[i].URL = "images//XNOR3.jpg";
								i++;
								break;
							case Add_XNOR_4 :
								Out->drawComponent("images//XNOR4.jpg","XNOR_4" ,P);
								Components[i].component = XNOR_4;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "XNOR_4";
								Components[i].Name = "XNOR_4";
								Components[i].URL = "images//XNOR4.jpg";
								i++;
								break;

							case Add_NOT:
								Out->drawComponent("images//NOT.jpg","NOT",P);
								Components[i].component = NOT;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "NOT";
								Components[i].Name = "NOT";
								Components[i].URL = "images//NOT.jpg";
								i++;
								break;
	
							case Add_BUFFER:
								Out->drawComponent("images//BUFFER.jpg","BUFFER",P);
								Components[i].component = BUFFER;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "BUFFER";
								Components[i].Name = "BUFFER";
								Components[i].URL = "images//BUFFER.jpg";
								i++;
								break;
							case Add_SWITCH:
								Out->drawComponent("images//SWITCH_OFF.jpg","SWITCH",P);
								Components[i].component = SWITCH;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "SWITCH";
								Components[i].Name = "SWITCH";
								Components[i].URL = "images//SWITCH_OFF.jpg";
								i++;
								
								break;
							case Add_LED:
								Out->drawComponent("images//LED_OFF.jpg","LED",P);
								Components[i].component = LED;
								Components[i].GfxInfo.Center = P;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P.x + 75;
								Components[i].GfxInfo.DownRight.y = P.y + 50;
								Components[i].Label = "LED";
								Components[i].Name = "LED";
								Components[i].URL = "images//LED_OFF.jpg";
								i++;
								break;
							case Add_WIRE:
								p2.x = 5;
								p2.y = 610;
								Out->drawStatusBar();
								Out->printStringStatusBar("Click on any point on the design area to draw the wire", p2);
								Point P3=In->getClick();
								Out->drawLines(P,P3);
								Out->drawStatusBar();
								Components[i].component = WIRE;
								Components[i].GfxInfo.UpLeft.x = P.x;
								Components[i].GfxInfo.UpLeft.y = P.y;
								Components[i].GfxInfo.DownRight.x = P3.x;
								Components[i].GfxInfo.DownRight.y = P3.y;
								Components[i].Label = "WIRE";
								Components[i].Name = "WIRE";
								i++;
								break;

						}
					}
					else
					{
						P.x = 5;
						P.y = 610;
						Out->drawStatusBar();
						Out->printStringStatusBar("This is not a valid place to add this component", P);
						Pause(2000);
					}

				}
		}
}


void checkIfSelected (int & i2, Input* ptrInput , Output* ptrOutput , Point mouseClick , vector <ScreenElement>& Components /*the vector of components*/ )
{
     int i;

	 for (i=0 ; i < Components.size() ; i++)
	 {
		 if ( (mouseClick.x > Components[i].GfxInfo.UpLeft.x) && (mouseClick.x < Components[i].GfxInfo.DownRight.x) )

			 if ( (mouseClick.y > Components[i].GfxInfo.UpLeft.y) && (mouseClick.y < Components[i].GfxInfo.DownRight.y) )

			 {
				 if(Components[i].component != WIRE)
				 {
					 ptrOutput -> Highlight (Components[i].GfxInfo.UpLeft , Components[i].GfxInfo.DownRight);
					 Point p;
					 int inc = 30;
					 p.x = inc;         p.y = 607;

					 ptrOutput -> drawStatusBar();
					 ptrOutput -> drawImageStatusBar (Components[i].URL , false , p);

					 p.x = 68 + inc;       
					 ptrOutput -> printStringStatusBar (Components[i].Name , p);

					 p.x = 238 + inc;
					 ptrOutput -> printStringStatusBar (Components[i].Label , p);

					 p.x = 1036 - 300;
					 ptrOutput -> drawImageStatusBar ("images//EditButton.jpg" ,true , p);

					 p.x = 1036 - 150;
					 ptrOutput -> drawImageStatusBar ("images//RemoveButton.jpg" , true , p);


					 mouseClick = ptrInput -> getClick();

					 if ( (mouseClick.x > Components[i].GfxInfo.UpLeft.x) && (mouseClick.x < Components[i].GfxInfo.DownRight.x) )
					 {
			           if ( (mouseClick.y > Components[i].GfxInfo.UpLeft.y) && (mouseClick.y < Components[i].GfxInfo.DownRight.y) )
					   {
						   if (Components[i].URL == "images//SWITCH_ON.jpg")
							   Components[i].URL == "images//SWITCH_OFF.jpg";
						   
						   else if (Components[i].URL == "images//SWITCH_OFF.jpg")
							   Components[i].URL == "images//SWITCH_ON.jpg";

						   else if (Components[i].URL == "images//LED_ON.jpg")
							   Components[i].URL == "images//LED_OFF.jpg";

						   else if (Components[i].URL == "images//LED_OFF.jpg")
							   Components[i].URL == "images//LED_ON.jpg";
					   }
					   ptrOutput->drawComponent(Components[i].URL , Components[i].Label , Components[i].GfxInfo.Center );
					 }

					 else  if ( (mouseClick.y > 608) && (mouseClick.y < 638) )
				     {
						if ( (mouseClick.x > 736) && (mouseClick.x < 856) ) // edit Label
					    {
							 ptrOutput->drawPopUpWindow("editLabel");

							 p.x = 499;		p.y = 293;
							 char* temp = ptrInput -> getString(p);

							 Components[i].Label = temp;

							 bool exit = false;

						     while ( !exit )
						
						     {
								mouseClick = ptrInput -> getClick();

								if ( (mouseClick.x > 662) && (mouseClick.x < 792) && (mouseClick.y > 336) && (mouseClick.y < 366) )
									 exit = true;

							 }
						}
					 /////////////////////////////////////////////////////////////////////////////////
						else if ( (mouseClick.x > 886) && (mouseClick.x < 1006) ) // Remove
						{
							 vector <ScreenElement> ::iterator ii = Components.end();
							 Components.erase(ii-1);
							 i2--;
						}
					}

					ptrOutput -> drawStatusBar();

	   			    i = Components.size() + 1;  //force to exit
	
				}
		}	
	}
}
