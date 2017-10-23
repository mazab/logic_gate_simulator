//------------------------------------------------
#include "Includes.h"
#include <fstream>
//------------------------------------------------

Level::Level()
{
	Count = 0;
	ID = 0;
	for(int i=0 ; i<MaxCompCountLevel ; i++)
		LevelCompList[i] = NULL;
}

//------------------------------------------------

Level::~Level()
{
}

//------------------------------------------------

void Level::setCount(int r_Count)
{
	Count = r_Count ;
}

//------------------------------------------------

void Level::setID(int r_ID)
{
	ID = r_ID;
}

//------------------------------------------------

int Level::getCount()
{
	return Count;
}

//------------------------------------------------

int Level::getID()
{
	return ID;
}

//------------------------------------------------

void Level::AddToLevel(Component* r_Comp)
{
	LevelCompList[Count] = r_Comp ; 
	Count ++ ;
}

//------------------------------------------------

void Level::RemoveFromLevel(int r_ID)
{
	for(int i=0 ; i<Count ; i++)
	{
		if(LevelCompList[i]->getID() == r_ID )
		{
			LevelCompList[i] = LevelCompList[Count-1];
			LevelCompList[Count-1] = NULL;
			Count --;
			//force to leave the loop
			i = Count+1 ;
		}
	}
}

//------------------------------------------------

void Level::AutoAlign(int emptyLevel_Vertical , ApplicationManager* pManager)
{
	//get the window width and height from the Application manager throw the output class
	int windowWidth = pManager->getOutput()->getWidthWindow();
	int windowHeight = pManager->getOutput()->getHeightWindow();

	//distance between every 2 components in a specific level
	//this will be calculated according to the number of components in each level
	int emptyLevel_Horizontal = (windowHeight - (Count * 50) - 42)/(Count + 1);

	//the new Graphics info of the component
	GraphicsInfo gfx ;

	for(int j = 1 ; j <= Count ; j++)
	{
		//setting the center point of the component 
		gfx.Center.x = ((ID+1) * emptyLevel_Vertical) + (int)((ID+0.5) * 75) + 168;
		gfx.Center.y = (j * emptyLevel_Horizontal) + (int)((j-1+0.5) * 50) ;

		//setting the upper left point of the component
		gfx.UpLeft.x = (gfx.Center.x) - (int)(0.5 * 75);
		gfx.UpLeft.y = (gfx.Center.y) - (int)(0.5 * 50);

		//setting the down right point of the component
		gfx.DownRight.x = (gfx.Center.x) + (int)(0.5 * 75);
		gfx.DownRight.y = (gfx.Center.y) + (int)(0.5 * 50);

		//applying the changes in points on the required component
		LevelCompList[j-1] ->setCurrentGfxInfo(gfx);
	}
}

//------------------------------------------------

void Level::Save(ofstream& out)
{
	out<<Count<<endl;
	for(int i=0 ; i<Count ; i++)
	{
		LevelCompList[i]->Save(out);
	}
}

//-------------------------------------------------

void Level::OperateLevel(ApplicationManager* pManager)
{
	int input_pin_count = 0 ;
	STATUS tmp_status = LOW ;
	//loop over the components and activate the operate fn in them
	for(int i=0 ; i<Count ; i++)
	{
		if(LevelCompList[i]->getName() == SWITCH)
		{
			input_pin_count = ((Switch*)LevelCompList[i])->getPin()->getConnectionsCount() ;
			tmp_status = ((Switch*)LevelCompList[i])->getPin()->getStatus() ;
			//transfering the signal from the output pin of the gate we are dealing with to the input pins connected to it
			for(int j=0 ; j<input_pin_count ; j++)
			{
				((Switch*)LevelCompList[i])->getPin()->getConnectedPins()[j]->setStatus(tmp_status);
			}
		}
		else if (LevelCompList[i]->getName() == LED)
		{
			//calling the fn operate of the
			LevelCompList[i]->Operate() ;
		}
		else
		{
			//calling the fn operate of the
			LevelCompList[i]->Operate() ;
			//trnsfering the signal over the wires to the next level
			input_pin_count = ((Gate*)LevelCompList[i])->getOutputPin()->getConnectionsCount() ;
			tmp_status = ((Gate*)LevelCompList[i])->getOutputPin()->getStatus() ;
			//transfering the signal from the output pin of the gate we are dealing with to the input pins connected to it
			for(int j=0 ; j<input_pin_count ; j++)
			{
				((Gate*)LevelCompList[i])->getOutputPin()->getConnectedPins()[j]->setStatus(tmp_status);
			}
		}
	}
}