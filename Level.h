#ifndef LEVEL_H
#define LEVEL_H



//class Level represents a level in the circuti holds pointers to the component in the level
class Level
{
	//max number of of Components in the Level
	enum {MaxCompCountLevel = 10};
private:
	int Count;                                          //actual number of components in the Level
	Component* LevelCompList[MaxCompCountLevel];        //array of pointers to the Components in this Level
	int ID;                                             //Level Id 

public:
	//constructor and destructor:
	//---------------------------
	Level();
	~Level();

	//setters:
	//--------
	void setCount(int);
	void setID(int);

	//getters:
	//--------
	int getCount();
	int getID();

	//List operations:
	//----------------
	void AddToLevel(Component*);
	void RemoveFromLevel(int);
	void AutoAlign(int , ApplicationManager*);
	void Save(ofstream&);
	void OperateLevel(ApplicationManager*) ;
};

#endif