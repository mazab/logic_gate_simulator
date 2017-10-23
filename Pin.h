#ifndef _PIN_H
#define _PIN_H

#include "Def.h"
//#include "Component.h"
//#include "WIRE.h"

//Pre Deff.:
class Component;
class Wire;

class Pin
{
protected:
	
	bool m_isConnected; //True if the pin is connected
	STATUS m_Status;	//Status of the Pin (on/off)
	Point *m_Position;
	Component* m_thisComponent;

public:
	
	//constructor & destructor:
	Pin();
	virtual ~Pin();

	//setters: 
	void setConn(bool r_isConnected);
	void setComponent(Component* r_thisComponent);
	void setStatus(STATUS r_Status);
	void setPosition(Point* P);
	
	//getters:
	bool getConn();
	Component* getComponent();
	STATUS getStatus();
	Point* getPosition();
};

#endif