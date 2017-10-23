#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H
//-------------------------------------------
#include "Def.h"
#include <stack>
using namespace std;
//-------------------------------------------
//Pre Defs:
class Component;
class Output;
class Input;
class Action;
class Level;
//-------------------------------------------
//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount  = 200 };	    //Max no of Components
	enum { MaxFigCount   = 200 };	    //Max no of figures
	enum { MaxLevelCount = 20  };       //Max no of Levels 

private:
	int LevelCount;                     //actual no of levels in the design
	int CompCount;                      //actual no of components in the design
	bool ExitWindow;                    //this will exit the loop in the main to exit the application
	bool SimuMode;                      //indicates if you are in the simulation mode or not
	int WiresExcCount;      			//actual no of components in the design (excluding wires)
	int selected;

	Component* CompList[MaxCompCount];  //list of all the components in the design
	Level* LevelList[MaxLevelCount];    //list of all the levels in the design
	Component* CompListWiresExc[MaxCompCount]; //list of components with the wires excluded

	stack <Action*> UndoStack;          //stack for the undo operations
	stack <Action*> RedoStack;          //stack for the redo operation

	Input* ptrInput;                    //pointer to the input object in the App. ApplicationManager
	Output* ptrOutput;                  //pointer to the output object in the App. ApplicationManager


public:	
	//Constructor and Destructor:
	//---------------------------
	ApplicationManager();
	~ApplicationManager();

	//component List operations:
	//---------------------------
	void AddComp(Component*);     //adds a component to the CompList
	void RemoveComp(int);         //removes a component from the CompList accoring to the index
	void AddWiresExcComp(Component*); //adds a component to the wires excluded list
	Component* SearchByID(int);   //this fn takes an ID and returns a pointer to the object holding that ID
	int getCompCount();

	//input and output operations:
	//----------------------------
	Input* getInput();            //returns a pointer to the input class
	Output* getOutput();          //returns a pointer to the output class

	//Level List operations:
	//----------------------
	int getLevelCount();          //returns the actual number of levels in the design
	void AddLevel(Level*);        //adds a level to the level list
	void RemoveLevel(int);        //removes a level from the level list according to the ID

	//Stacks operations:
	//------------------
	void pushUndo(Action*);       //push an action to the undo stack
	void pushRedo(Action*);       //push an action to the redo stack

	Action* popUndo();            //pop an element from the undo stack and return it 
	Action* popRedo();            //pop an element from the redo stack and return it

	bool UndoIsEmpty();           //checks if the undo stack is empty
	bool RedoIsEmpty();           //checks if the redo stack is empty

	//other operations:
	//------------------

	//setter and getter for the ExitWindow Attribute
	void setExit(bool);
	bool getExit();

	//setter and getter for the SimulationMode Attribute
	void setSimulationMode(bool);
	bool getSimulationMode();

	//action handling operations:
	//---------------------------
	void ExecuteUserAction(ActionType, Point p);     //executes the action selected by the user
	void UpdateInterface();                          //Updates the interface after every single action
	bool CheckValidity(Point);                       //check if this place is valid to insert the component

	//other operations:
	//------------------
	void AutoAlign(int);
	void save(ofstream&);
	void load(ifstream&);
	void errorDetector();
	void TruthTable(Action*);
	void simulate();
	int Pow(int A, int B);                 // Calculate the power!

	//Wire Service Pack!:
	//--------------------
	//Returns an array of pointers to the components Located between P1 & P2 and they IDs dont match ID1 & ID2:
	Component** OnArea(Point P1, Point P2, int ID1, int ID2);  

	//level counting operations:
	//-----------------------------
	void ExcludeWires();
	bool checkInput(Component* r_Comp);			//checks wether the input of r_Comp are NULL or switch
	Component* getInputCompLED(Component* r_Comp);   //returns the component connected to the LED r_Comp
	Component** getInputCompGate(Component* r_Comp , int& Length); //returns the component connected to the r_Comp
	Component** getOutputComp(Component* r_Comp , int &Length);//returns the component connected the output pin of r_Comp
	bool findCompLevel(int level);		//search for a component with certain level
	void checkForFirstLevel();  //checks if the component exists in the first level
	void setInputPinsToPrevLevel(Component* r_Comp , int PinNo); //sets the input levels to the prev level of this component
	void setOutputPinsToNextLevel(Component* r_Comp); // sets the level of components connected to the outpin of r_Comp to the next level
	int getInputsLevel(Component* r_Comp , int PinNo); //returns the level of components connected to the specified pin of this component
													   //Note: this will not work for switches as there are no input pins
	void determineLevelZero();					 //determines the first level in the circuit
	void setLevels();							 //sets the Level of each component in the circuit
	void fillLevels();							//fill th elevelks with components
	void evacuateLevels();
	//===================================================================================================
	Component* getselectedcomponent();  //this Fn return pointer on the selected component
	//===============================
	ActionType  getUserAction(Point&p);  // this Fn detect the required action
	//===============================
	void DoCompAction();                  // this fn executes actions related to components ( remove , move , changelabel)
	//===========================================
	void show_status_bar();                // this fn shows the component status bar
	Action* createWire();
	Component* getComponentByPoint(Point);
	bool CheckValidity (Point mouseClick,Component*Comp);
	int MaxID();
	//===============================
	ActionType SelectSimulationAction(); 
	void setSelected(int);
};

#endif