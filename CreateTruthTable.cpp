//---------------------------------------------------
#include "Includes.h"
#include <fstream>
//---------------------------------------------------

CreateTruthTable::CreateTruthTable()
{
	rowsCount = 0 ;
	columnsCount = 0 ;
	SwitchCount = 0 ;
	LedCount = 0 ;
	ptrGrid = NULL ;
}

//---------------------------------------------------

CreateTruthTable::~CreateTruthTable()
{
	//free the allocated memrory by the 2-dim array ..
	for(int i=0 ; i<rowsCount ; i++)
		delete [] ptrGrid[i] ;

	delete [] ptrGrid ;
}

//---------------------------------------------------

void CreateTruthTable::ReadActionParameters(ApplicationManager* pManager)
{

}

//---------------------------------------------------

void CreateTruthTable::Execute(ApplicationManager* pManager)
{
	//Calling the truthtable fn in the Application Manager
	pManager->TruthTable(this) ;

	if(SwitchCount <= 5)
	{
		//Calling the drawTruthTable fn in the output class to print in on a window .
		pManager->getOutput()->drawTruthTable(rowsCount,columnsCount , SwitchCount , LedCount , ptrGrid) ;
	}

	//making a file of the truth tabel Called TruthTable.txt
	ofstream out("truthTable.txt") ;
	out<<"\n";
	out<<"-------------------------------------------------\n" ;
	out<<"-< Truth Table - Logic Circuit Simulator V.1.0 >-\n" ;
	out<<"-------------------------------------------------\n" ;
	out<<"\n";

	for(int i=0 ; i<5+2 ; i++)
		out<<"____";
	out<<"\n\n";
	out<<" ";

	//making the header of the table:
	for(int j=0 ; j<SwitchCount ; j++)
	{
		out<<"  "<<"I"<<j ;
	}
	//printing a seperator
	out<<"  |  " ;
	for(int j=SwitchCount; j<columnsCount ; j++)
	{
		out<<"  "<<"O"<<j-2 ;
	}
	out<<endl<<endl ;
	for(int i=0 ; i<columnsCount+2 ; i++)
		out<<"____";
	out<<"\n\n";

	for(int i=0 ; i<rowsCount-1 ; i++)
	{
		//printing the input part
		for(int j=0 ; j<SwitchCount ; j++)
		{
			out<<"   "<<ptrGrid[i][j] ;
		}
		//printing a seperator
		out<<"   | " ;
		//printing the output part
		for(int j=SwitchCount ; j<columnsCount ; j++)
		{
			out<<"   "<<ptrGrid[i][j] ;
		}
		out<<endl ;
		for(int i=0 ; i<5+2 ; i++)
			out<<"____";
		out<<"\n\n";
	}
	out.close() ;
}

//---------------------------------------------------

void CreateTruthTable::unExecute(ApplicationManager* pManager)
{}

//---------------------------------------------------

int CreateTruthTable::getColCount()
{
	return columnsCount ;
}

int CreateTruthTable::getRowCount()
{
	return rowsCount ;
}

int CreateTruthTable::getSwitchCount()
{
	return SwitchCount ;
}

int CreateTruthTable::getLedCount()
{
	return LedCount ;
}

STATUS** CreateTruthTable::getGrid()
{
	return ptrGrid ;
}
//---------------------------------------------------

void CreateTruthTable::CreateGrid()
{
	//creating the dynamic 2-dimensional array 
	ptrGrid = new STATUS*[rowsCount] ;
	for(int i=0 ; i<rowsCount ; i++)
		ptrGrid[i] = new STATUS[columnsCount] ;

	//---------------------------

	ofstream out("binary.txt");
	string binaryNum;

	//setting all the fields in the table to LOW
	for(int m=0 ; m<rowsCount ; m++)
	{
		for(int n=0 ; n<columnsCount ; n++)
			ptrGrid[m][n] = LOW ;
	}

	//making a list of the numbers in decimal system and put them into a file called binary
	for(int i=0 ; i<rowsCount ;i++ )
	{
		//send the decimal number to the binary fn which will convert it to binary and prints it in a file
		binary(i,out);
		out <<endl;
	}
	//closing the file
	out.close() ;

	///---------------------------------

	//read from the file the binary numbers and put them in the table
	ifstream in("binary.txt");
	int strLength ; //length of the binary string 
	int j ; //walker to walk over the binary bit string til its end

	//loop to fill in the input fields in the table
	for(int i=0 ; i<rowsCount ; i++)
	{
		//read a binary string from the file
		in>>binaryNum ;
		//get the length of this binary string
		strLength = binaryNum.length() ;

		j = SwitchCount - 1 ;
		while (j>=0 && strLength > 0)
		{
			//if the bit is 1 --> this is a HIGH signal
			if(binaryNum[strLength-1] == '1')
				ptrGrid[i][j] = HIGH ;
			//if the bit is 0 --> this is a LOW  signal
			else
				ptrGrid[i][j] = LOW ;
			//decrment the walker and go back by only one bit
			j -- ;
			strLength -- ;
		}//end of the internal loop
	}//end of outer loop
}

//---------------------------------------------------
void CreateTruthTable::binary(int number , ofstream& out) 
{
	//recusive fn to convert from decimal to binary
	//===========================================================================================================
	//B.S.: this fn is copied(but with some modifications) from -->
	//Data Structures: A pesudoCode Approach with C - third Edition - by: Richard Gilberg and Behrouz Frouzan
	//===========================================================================================================
	int remainder;
	if(number <= 1) 
	{
		out << number;
		return;
	}

	remainder = number%2;
	binary(number >> 1 , out);
	out << remainder;
}

//=================================================

void CreateTruthTable::setData(int r_rows ,int r_cols  , int r_SwitchCount , int r_LedCount)
{
	rowsCount = r_rows + 1 ;
	columnsCount = r_cols ; 
	SwitchCount = r_SwitchCount ; 
	LedCount = r_LedCount ; 
}