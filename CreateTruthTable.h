#ifndef CREATETRUTHTABLE_H
#define CREATETRUTHTABLE_H

#include"Action.h"

//class CreateTruthTable: makes the truth table of the whole circuit
class CreateTruthTable : public Action
{
private:
	int rowsCount ;       //number of rows in the truthtable
	int columnsCount ;    //number of columns in the truthtable (input + output)
	int SwitchCount ;     //number of switches (number of inputs)
	int LedCount ;        //number of leds (number of outputs)
	STATUS** ptrGrid ;    //2-dimensional array of STATUS (the truth table itself)

public:
	//constructor and destructor:
	//----------------------------
	CreateTruthTable() ;
	~CreateTruthTable() ;

	//virtual fns of the action:
	//---------------------------
	virtual void ReadActionParameters(ApplicationManager* pManager) ; 
	virtual void Execute(ApplicationManager* pManager) ;
	virtual void unExecute(ApplicationManager* pManager) ;

	//getters:
	//--------
	int getColCount() ;
	int getRowCount() ;
	int getSwitchCount() ;
	int getLedCount() ;
	STATUS** getGrid() ;

	//table making fns:
	//-----------------
	void CreateGrid() ;                //this fn creates the truth table according to the data it has
	void binary(int, ofstream&) ;      //this fn convert from decimal to binary and writes them in a file
	void setData(int , int , int , int);
};


#endif