#include "Includes.h"

int main()
{
	ApplicationManager AppManager ;
	ActionType Act;
	do
	{
		Point p;
		p.x = 0;
		p.y = 0;
		Act = AppManager.getUserAction(p) ;

		AppManager.ExecuteUserAction(Act,p) ;

		AppManager.UpdateInterface() ;

	}while(!AppManager.getExit());

	return 0;
}