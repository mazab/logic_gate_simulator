#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "Component.h"
//Esentials:
//-------------
#include "ApplicationManager.h"
#include "Def.h"
#include "Output.h"
#include "Input.h"

//Pins"
//--------
#include "Pin.h"
#include "InputPin.h"
#include "OutputPin.h"

//Components:
//--------------
#include "Gate.h"
#include "AND2.h"
#include "AND3.h"
#include "AND4.h"
#include "NAND2.h"
#include "NAND3.h"
#include "NAND4.h"
#include "OR2.h"
#include "OR3.h"
#include "OR4.h"
#include "NOR2.h"
#include "NOR3.h"
#include "NOR4.h"
#include "XOR2.h"
#include "XOR3.h"
#include "XOR4.h"
#include "XNOR2.h"
#include "XNOR3.h"
#include "XNOR4.h"
#include "BUFFER.h"
#include "NOT.h"
#include "LED.h"
#include "Switch.h"
#include "WIRE.h"

//#include "UserDefined.h"

//Actions:
//-----------
#include "Action.h"
#include "Level.h"
#include "CreateTruthTable.h"
#include "AutoAlignment.h"
#include "Exit.h"
#include "Undo.h"
#include "Redo.h"
#include "Save.h"
#include "Load.h"
#include "ErrorDetector.h"
#include "AddComponent.h"
#include "AddANDgate.h"
#include "AddBuffer.h"
#include "AddLED.h"
#include "AddNANDgate.h"
#include "AddNORgate.h"
#include "AddNOTgate.h"
#include "AddORgate.h"
#include "AddSWITCH.h"
#include "AddWire.h"
#include "AddXNORgate.h"
#include "AddXORgate.h"
#include "Move.h"
#include "Truth_Table.h"
#include "ChangeLabel.h"
#include "SimulationMode.h"
#include "Remove.h"

#endif