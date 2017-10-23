#include "Includes.h"


AddComponent::AddComponent()
{
	m_ptrAddedComponent = NULL;
}

void AddComponent::ReadActionParameters(ApplicationManager* pManager)
{ }

GraphicsInfo AddComponent::computeGfxInfo(Point center)
{
	GraphicsInfo temp;

	temp.Center = center;
	temp.UpLeft.x = center.x - (int)(0.5*75);
	temp.UpLeft.y = center.y - (int)(0.5*50);
	temp.DownRight.x = center.x + (int)(0.5*75);
	temp.DownRight.y = center.y + (int)(0.5*50);

	return temp;
}

void AddComponent::Execute(ApplicationManager* pManager)
{}

void AddComponent::unExecute(ApplicationManager* pManager)
{}

Component* AddComponent::getAddedComponent()
{
	return m_ptrAddedComponent;
}
