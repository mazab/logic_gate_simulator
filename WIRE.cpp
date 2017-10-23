#include "Includes.h"
#include <fstream>
using namespace std ;

//Constructor:
Wire::Wire(InputPin* r_Input, OutputPin* r_Output, const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager)
	 :Component("WIRE", WIRE, r_GfxInfo, r_ApplicationManager)
{  
	m_DrawingPoints_Count =0;
	m_Input = r_Input;
	m_Output = r_Output;

	LoadingTerminator = 0 ;
}

Wire::Wire()
	 :Component("WIRE", WIRE){LoadingTerminator = 0 ;}
//==============================================================================================================
//Destructor:
Wire::~Wire()
{}
//==============================================================================================================
//Setters:
void Wire::setInputPin(InputPin* r_In)
{
	m_Input = r_In;
}

void Wire::setOutputPin(OutputPin* r_Out)
{
	m_Output = r_Out;
}
//==============================================================================================================
//Getters:
InputPin* Wire::getInputPin()
{
	return m_Input;
}

OutputPin* Wire::getOutputPin()
{
	return m_Output;
}

int Wire::getConnectedPenIndex()
{
	if(m_Input->getComponent()->getName() == SWITCH)
		return 1;
	else
	{
		Component* C  = m_Input->getComponent();
		return ((Gate*)C)->getInputPinIndex(this->m_Input);
	}
}

int Wire::getLoadingTerminator()
{
	return LoadingTerminator ;
}

char* Wire::getIC()
{
	return NULL;
}

char* Wire::getType()
{
	return "Wire";
}

char* Wire::getUrl()
{
	return NULL;
}
//==============================================================================================================
//Virtuals!:
void Wire::Load(ifstream& in)
{
	int src_comp_ID =0 ; 
	int dst_comp_ID =0;
	int pin_no =0 ;

	in>>m_ID;
	if(m_ID != -1)
	{
		in>>src_comp_ID ;
		in>>dst_comp_ID ;
		in>>pin_no ;

		Component* src = m_ApplicationManager->SearchByID(src_comp_ID);
		Component* dst = m_ApplicationManager->SearchByID(dst_comp_ID);
	
		//make m_Input & m_Output:
		if(src->getName() == SWITCH)
			m_Output = ((Switch*)src)->getPin();
		else
			m_Output = ((Gate*)src)->getOutputPin();
			
		if(dst->getName() == LED)
			m_Input = ((Led*)dst)->getPin();
		else
			m_Input = ((Gate*)dst)->getInputPin(((Gate*)dst)->getConnectedInputs()+1);
		
		//connect m_in to m_out and m_out to m_in:
		if(src->getName() == SWITCH)
			((Switch*)src)->ConnectTo(m_Input);
		else
			((Gate*)src)->ConnectOutputPinTo(m_Input);
			
		if(dst->getName() == LED)
			((Led*)dst)->connectTo(m_Output);
		else
			((Gate*)dst)->ConnectInputPinTo(m_Output);

		m_Input->setWire(this);
		
	}
	else
	{
		ID_Generator = m_ApplicationManager->MaxID() +1;
		LoadingTerminator = -1 ;
	}

}
//======

void Wire::Save(ofstream& out)
{
	int src_Comp = m_Output->getComponent()->getID() ;
	int dst_Comp = m_Input->getComponent()->getID() ;
	Component* C = m_Input->getComponent();
	int pin_no;

	switch(C->getName())
	{
	case LED:
		pin_no =1;
		break;
		
	default:
		pin_no = ((Gate*)C)->getInputPinIndex(m_Input);
		break;
	}

	out<<m_ID<<'\t'<<src_Comp<<'\t'<<dst_Comp<<'\t'<<pin_no<<endl ;
}
//======

void Wire::Operate()
{
	m_Input->setStatus(m_Output->getStatus());
}
//======

bool Wire::IsMatch(Point p)
{
	int index = 0;
	while(index < m_DrawingPoints_Count-1)
	{
		//if the line was horezontal:
		if(m_DrawingPoints[index].y == m_DrawingPoints[index+1].y)
		{
			if( (p.x > m_DrawingPoints[index].x) && (p.x < m_DrawingPoints[index+1].x) && ( (p.y <=  m_DrawingPoints[index].y+2)&&(p.y >=  m_DrawingPoints[index].y-2) ) )
				return true;
		}

		//if the line was vertical:
		else
		{   
			//if y1 > y2 (the line is going Up.):
			if(m_DrawingPoints[index].y >= m_DrawingPoints[index+1].y)
			{
				if( (p.y < m_DrawingPoints[index].y) && (p.y > m_DrawingPoints[index+1].y) && ( (p.x <=  m_DrawingPoints[index].x+2)&&(p.x >=  m_DrawingPoints[index].x-2) ) )
					return true;
			}
			
			//if y2 > y1 (the line is going Dn.):
			else
			{
				if( (p.y > m_DrawingPoints[index].y) && (p.y < m_DrawingPoints[index+1].y) && ( (p.x <=  m_DrawingPoints[index].x+2)&&(p.x >=  m_DrawingPoints[index].x-2) ) )
					return true;
			}

		}
		index++;
	}
	return false;
}
//======

void Wire::Draw()//Didn't finished yet!
{ 
	// (1)-->setting the drawing color:
	if( (m_ApplicationManager->getSimulationMode()) && (m_Input->getStatus() == HIGH) )
		m_ApplicationManager->getOutput()->setLineColor(true);
	else
		m_ApplicationManager->getOutput()->setLineColor(false);

	// (2)--> draw:
	//if one of the 2 components we match between them is moving, we will just draw a line between them!:
	
	if(m_Input->getComponent()->isMoving() || m_Output->getComponent()->isMoving())
		m_ApplicationManager->getOutput()->drawLines(*m_Output->getPosition(),*m_Input->getPosition());
	
	// isMoving != true :
	else
	{
		//try to draw the wire with virtecal and horezontal lines:
		bool test = DrawWire();

		//at the worest worest case, it will draw the wiredirectly, from the last point we can reach to the end point:
		if(!test)
		{
			m_ApplicationManager->getOutput()->drawLines(m_DrawingPoints[m_DrawingPoints_Count], *m_Input->getPosition());
			m_DrawingPoints[m_DrawingPoints_Count++] = *m_Input->getPosition();
		}
	}
}

//==============================================================================================================
//service Pack:
bool Wire::isValid(Point P, Component**  CmpList)
{
	for(int i=0; CmpList[i] != NULL; i++)
	{
		if( (P.x > CmpList[i]->getCurrentGfxInfo().UpLeft.x-5) && (P.x < CmpList[i]->getCurrentGfxInfo().UpLeft.x +80) )
			if( (P.y >CmpList[i]->getCurrentGfxInfo().UpLeft.y-5) && (P.y < CmpList[i]->getCurrentGfxInfo().UpLeft.y +55) )
				return false;
	}
	return true;
}
//===
//this fn. will call itself with the non-defult values of x & y in one case:
bool Wire::DrawWire(int x, int y)
{   
	//set the drawing points to NULL:
	this->m_DrawingPoints_Count = 0;

	//The drawing start and end points:
	Point P1; 
	Point P2;
	
	//if this true, the fn. called itself:
	if(x != 0)
	{
		P1.x = x;
		P1.y = y;
	}
	//this call is from Wire::Draw():
	else
		P1 = *m_Output->getPosition();
	
	P2 = *m_Input->getPosition();
	//================================

	bool Up = (P1.y > P2.y) ? true : false; //to determine if the wire will go up !

	//Get an array of pointers to the components located in the drawing area:
	Component** onArea = m_ApplicationManager->OnArea(P1, P2, m_Output->getComponent()->getID(), m_Input->getComponent()->getID());
	
	//1st case ---> Nothing between the two points:
	if(onArea[0] == NULL)
	{
		//If the start and the end points are in the same hight:
		if(P1.y == P2.y)
		{
			//set the drawing points:
			m_DrawingPoints[m_DrawingPoints_Count++] = P1;
			m_DrawingPoints[m_DrawingPoints_Count++] = P2;

			//Draw:
			m_ApplicationManager->getOutput()->drawLines(P1 ,P2);

			return true;
		}
		
		else // Not in the same hight!:
		{
			/* We will Do This:    
			      (P1)__________(1)
			                     |
								(2)____________(P2)     */
			
			// (1):
		    Point intermediate1;
			intermediate1.x = P1.x + (P2.x - P1.x)/2;
			intermediate1.y = P1.y;
			
			// (2):
			Point intermediate2;
			intermediate2.x = intermediate1.x;
			intermediate2.y = P2.y;

			//set the drawing points:
			m_DrawingPoints[m_DrawingPoints_Count++] = P1;
			m_DrawingPoints[m_DrawingPoints_Count++] = intermediate1;
			m_DrawingPoints[m_DrawingPoints_Count++] = intermediate2;
			m_DrawingPoints[m_DrawingPoints_Count++] = P2;
			
			// Draw lines:
			m_ApplicationManager->getOutput()->drawLines(P1 ,intermediate1);
			m_ApplicationManager->getOutput()->drawLines(intermediate1 ,intermediate2);
			m_ApplicationManager->getOutput()->drawLines(intermediate2 ,P2);
			
			return true;
		}
	}//end 1st case

	//2nd Case ---> The DrawingAreacomponents not NULL!:
	else
	{
			Point intermediate[1000];
			int intermediateCount=0;

			bool pathFound = false; //to check if the path was found
			bool test = true; //for testing
			//iterator: (iterate on all points between P1.x & P2.x)
			Point nP; 

			//select the last valid point, to use it in the worest case!:
			Point validPoints[1000];
			int validPointsCount =0;

			if(isValid(P1, onArea))
				validPoints[validPointsCount++] = P1;
			else
				return false;

			nP.x = P1.x+9; 
			nP.y = P1.y;
			
			if(isValid(nP, onArea))
				validPoints[validPointsCount++] = nP;
			else
				return false;

			// (Loop1) loop for all Points between P1.x & P2.x , stop when finding a valid path: 
			//                        (P1)---1---2---3---4---5---6------(P2.x)
			while( (test) && (!pathFound) && (nP.x <= P2.x) )
			{
				int newX = nP.x;
				test = isValid(nP, onArea); //test if this point is empty
				// apdate this point to the last valed point:
				if(test) 
					validPoints[validPointsCount++] = nP; 

			   // (Loop2) Loop for all Points between P1.y & P2.y, to check if this path is valid:      
			   //                                      (P2.y)
         	   //                                        |
	 	       //	                                     |
			   // 	                                     |
               //                                      (nP)
				nP.y = (!Up)? (nP.y+7) : (nP.y-7); 
				                  // ______________________________________________________________________________
				while( (test) && (/*|*/( ((P1.y > P2.y) && (nP.y >= P2.y)) || ((P1.y < P2.y) && (nP.y <= P2.y)) )/*|*/) )
				{//                 |  |--------------->(if the iterator didnt reached P2.y yet)<---------------|  |
					//              |______________________________________________________________________________|
					
					test = isValid(nP, onArea); //test if this point is empty
					// apdate this point to the last valed point:
					if(test) 
						validPoints[validPointsCount++] = nP; 

					nP.y = (!Up)? (nP.y+7) : (nP.y-7);
				}//end Loop2
				
				if(test)
				{
					nP.y = P2.y; // make sure that is nP.y = P2.y, (thus because nP.y maybe < P2.y by pixel or 2 !)
					test = isValid(nP, onArea);
					if(test)
					{   
						// apdate this point to the last valed point:
						validPoints[validPointsCount++] = nP; 
						
						//setting the drawing intermediate points:
						intermediate[0].x = nP.x;
						intermediate[0].y = P1.y;
						intermediate[1] = nP;

						// (Loop3) loop from nP to P2, to make sure that the path from nP to P2 is valed:
						//                      (nP)---1---2---3---4---5-------(P2)
						nP.x +=7;
						while( (test) && (nP.x <= P2.x) )
						{
							test = isValid(nP, onArea);
							// apdate this point to the last valed point:
							if(test) 
								validPoints[validPointsCount++] = nP; 
							
							nP.x +=7;

						}//end Loop3

						//if the path is not valed, we will do:
						/*                      ________________
							                  (0)              (1)
					                           |                |
			                                   |                |
		                                     (nP)              (2)__________(P2)  */
						//if(!test)
						//{
						//	nP = intermediate[1];
						//	int Y = nP.y;
						//	if(Up)
						//	{
						//		for(int i=0; onArea[i] != NULL; i++)
						//		{
						//			if(onArea[i]->getCurrentGfxInfo().UpLeft.y < Y)
						//				Y = onArea[i]->getCurrentGfxInfo().UpLeft.y;
						//		}//end for
						//	}//end if(Up)
						//	
						//	else //if Dn:
						//	{
						//		for(int i=0; onArea[i] != NULL; i++)
						//		{
						//			if(onArea[i]->getCurrentGfxInfo().DownRight.y > Y)
						//				Y = onArea[i]->getCurrentGfxInfo().DownRight.y;
						//		}//end for
						//	}//end if Dn
						//	
						//	//now we found the path, we will check if it valid:
						//	
					 //       //(1):
						//	// (Loop4)
						//	test = true;
						//	while( (test) && (nP.y <= Y) )
						//	{
						//		test = isValid(nP, onArea);
						//		// apdate this point to the last valed point:
						//		if(test) 
						//			validPoints[validPointsCount++] = nP; 

						//		nP.y = (!Up)? (nP.y+3) : (nP.y-3);
						//	}//end Loop4

						//	//(2):
						//	nP.y = Y;
						//	// (Loop5)
						//	while( (test) && (nP.x <= P2.x-3) )
						//	{
						//		test = isValid(nP, onArea);
						//		// apdate this point to the last valed point:
						//		if(test) 
						//			validPoints[validPointsCount++] = nP; 

						//		nP.y +=3;
						//	}//end Loop5

						//	//(3):
						//	nP.x = P2.x-3;
						//	// (Loop6)
						//	while( (test) && (nP.y >= P2.y) )
						//	{
						//		test = isValid(nP, onArea);
						//		// apdate this point to the last valed point:
						//		if(test) 
						//			validPoints[validPointsCount++] = nP; 

						//		nP.y -=3;
						//	}//end Loop6

						//	//if the test is true, we will Draw !:
						//	if(test)
						//	{
						//		pathFound = true;

						//		//setting the intermediate points:
						//		intermediate[2].x = intermediate[1].x;
						//		intermediate[2].y = Y;
						//		intermediate[3].x = P2.x-3;
						//		intermediate[3].y = Y;
						//		intermediate[4].x = P2.x-3;
						//		intermediate[4].y = P2.y;

						//		//set the drawing points:
						//		m_DrawingPoints[m_DrawingPoints_Count++] = P1;
						//		m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[0];
						//		m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[1];
						//		m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[2];
						//		m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[3];
						//		m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[4];
						//		m_DrawingPoints[m_DrawingPoints_Count++] = P2;

						//		//Draw:
						//		m_ApplicationManager->getOutput()->drawLines(P1, intermediate[0]);
						//		m_ApplicationManager->getOutput()->drawLines(intermediate[0], intermediate[1]);
						//		m_ApplicationManager->getOutput()->drawLines(intermediate[1], intermediate[2]);
						//		m_ApplicationManager->getOutput()->drawLines(intermediate[2], intermediate[3]);
						//		m_ApplicationManager->getOutput()->drawLines(intermediate[3], intermediate[4]);
						//		m_ApplicationManager->getOutput()->drawLines(intermediate[4], P2);

						//		return true;
						//	}//end if(test)

						//}//end if(!test)
						//
						////if (test)
						/*else */
						{
							pathFound = true; //to termenate Loop1

							//set the drawing points:
							m_DrawingPoints[m_DrawingPoints_Count++] = P1;
							m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[0];
							m_DrawingPoints[m_DrawingPoints_Count++] = intermediate[1];
							m_DrawingPoints[m_DrawingPoints_Count++] = P2;

							//Draw:
							m_ApplicationManager->getOutput()->drawLines(P1, intermediate[0]);
							m_ApplicationManager->getOutput()->drawLines(intermediate[0], intermediate[1]);
							m_ApplicationManager->getOutput()->drawLines(intermediate[1], P2);

							return true;
						
						}//end else
					}//end if(valed)
				}// end if(test)

				//if the path didn't found yet, update the loop info. :
				if(!pathFound)
				{
					nP.x = newX+7;
					nP.y = P1.y;
				}

			}//end Loop1

			//the Worest case:-------> reaches the P2.x, and the valid path didn't found yet!:
			if(!pathFound)
			{
				if( (validPoints[validPointsCount].x == P1.x) && (validPoints[validPointsCount].y == P1.y) )
					return false;
				else
				{
					//set drawing points and Draw:
					m_DrawingPoints[m_DrawingPoints_Count++] = validPoints[0];
					for(int i=1; i< validPointsCount; i++)
					{
						//set the drawing Points:
						m_DrawingPoints[m_DrawingPoints_Count++] = validPoints[i];

						//Draw:
						m_ApplicationManager->getOutput()->drawLines(validPoints[i-1], validPoints[i]);
					
					}//end for
					
					return DrawWire(validPoints[validPointsCount-1].x, validPoints[validPointsCount-1].y);
				}
			}//end the worest case

	}// end 2nd case 
	return false;
}

//=============

void Wire::UpdatePinsGfxInfo()
{}
//============

