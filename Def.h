#ifndef _DEF_H
#define _DEF_H

//=====================================================================================================
enum ActionType // The All posible Actions inherted from the class Action
{
	//Snake-Head-Actions !   -----> This type of actions will be handled inside the ApplicationManager class.
 //========================
	     //Add_ Operations:
	        Add_BUFFER,  Add_NOT,
			Add_AND,     Add_NAND,
			Add_OR,      Add_NOR,
            Add_XOR,     Add_XNOR,
			Add_WIRE,    Add_SWITCH,
			Add_LED,
			Add_UserGate,
		//Functions Bottons:
			SIMULATION_MODE, DESIGN_MODE,
			AUTO_ALIGNMENT,  ERROR_DETECTOR,
			CREATE_NEW_GATE,
		//General Bottons:
			EXIT,           SAVE,
			LOAD,           UNDO,
			REDO,
		//Sellection Operations:
			SELECT_COMPONENT,
	     
	//Snake-Body-Actions !   -----> This type of actions will be handled inside the Actins classes.
 //========================
		//Component Tools:
			MOVE,           REMOVE,
			TRUTH_TABLE,	CHANGE_LABEL,
		//Addation Detailes:
			Add_AND_2,		Add_AND_3,		Add_AND_4,
			Add_OR_2,		Add_OR_3,		Add_OR_4,
			Add_NAND_2,		Add_NAND_3,		Add_NAND_4,
			Add_NOR_2,		Add_NOR_3,		Add_NOR_4,
			Add_XOR_2,		Add_XOR_3,		Add_XOR_4,
			Add_XNOR_2,     Add_XNOR_3,     Add_XNOR_4,
//========================
 //if nothing from those:
   CANCEL,
};

//=====================================================================================================
struct Point //Could contain any screen point
{
	int x;
	int y;
};
//=====================================================================================================
enum STATUS //Possible Status for the pin
{
	LOW,
	HIGH,
};
//=====================================================================================================
#define MAX_PINS 20  // The max. value for the FANOUT Notation.
//=====================================================================================================
#define FANOUT 5 // Suggested value for FANOUTs for all gates.
//=====================================================================================================
//assume fan out is 5 for now it can be read from the user or can be predefined as const
/*enum FANOUT
{
	AND2_FANOUT = 5	//Fan out of 2-input AND gate
};*/
//=====================================================================================================
struct GraphicsInfo //A structure to contain drawing parameters for each component
{
	Point UpLeft; 
	Point Center;
	Point DownRight;
};
//=====================================================================================================
enum ComponentType
{
	UserGate,
	BUFFER,
	NOT,
	AND_2,   AND_3,   AND_4,
	OR_2,    OR_3,    OR_4,
	NAND_2,  NAND_3,  NAND_4,
	NOR_2,   NOR_3,   NOR_4,
	XOR_2,   XOR_3,   XOR_4,
	XNOR_2,  XNOR_3,  XNOR_4,
	SWITCH,
	LED,
	WIRE,
};
//=====================================================================================================
struct ScreenElement
{
	ComponentType component;
	char* Name;
	char* Label;
	char* URL;
	GraphicsInfo GfxInfo;
};
//=====================================================================================================
#endif