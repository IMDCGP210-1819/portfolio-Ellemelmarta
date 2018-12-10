#include "main.h"
#include <iostream>
#include <list>

using namespace std;

/*
									   start
									   	 |
							selector (have ingredients?)
					/									\
				sequence							   sequence
			/		|								/			  \
		walk to		pick up	  				walk to cooker	     cook

*/


class Node
{
public:
	virtual bool willRun() = 0;
};


class CompositeNode : public Node
{
private:
	list<Node*> children;

public:
	const list<Node*>& getChildren() const 
	{ 
		return children; 
	}

	void addChild(Node* child)
	{
		children.emplace_back(child);
	}
};


class Selector : public CompositeNode
{
public:
	virtual bool willRun() override
	{
		for (Node* child : getChildren())
		{
			//if any child runs it returns true and runs/succeeds
			if (child->willRun())
				return true;
		}
		//only happens if all fail
		return false;
	}
};


class Sequence : public CompositeNode
{
public:
	virtual bool willRun() override
	{
		for (Node* child : getChildren())
		{
			//if any child fails it wont run and will fail the entire operation
			if (!child->willRun())
				return false;
		}
		//only happens when all return true
		return true;
	}
};


struct CookingStatus
{
	bool isCooked; //this isn't needed unless a selector at end for is cooked is added
	bool haveIngredients;
	int distanceToCooker;
	int distanceToIngredients;
};


class CheckIfIngredientsNeededTask : public Node
{
private:
	CookingStatus* status;

public:
	CheckIfIngredientsNeededTask(CookingStatus* status) : status(status) {}
	virtual bool willRun() override
	{
		if (status->haveIngredients == true)
			cout << "The sim has the ingredients needed." << endl;
		else
			cout << "The sim has not got the ingredients." << endl;

		return status->haveIngredients;
	}
};


class WalkToIngredientsTask : public Node
{
private:
	CookingStatus* status;
	
public:
	WalkToIngredientsTask(CookingStatus* status) : status(status) {}
	virtual bool willRun() override
	{
		if (status->distanceToIngredients > 0)
		{
			cout << "The sim approaches the ingredients." << endl;
			status->distanceToIngredients--;

			if (status->distanceToIngredients > 1)
				cout << "The sim is now" << status->distanceToIngredients << " meters from the ingredients." << endl;

			else if (status->distanceToIngredients == 1)
				cout << "The sim is now only 1 meter away from the ingredients." << endl;

			else
				cout << "The person is at the ingredients." << endl;
		}
		return true;
	}
};


class PickUpTheIngredientsTask : public Node
{
private:
	CookingStatus* status;

public:
	PickUpTheIngredientsTask(CookingStatus* status) : status(status) {}
	virtual bool willRun() override
	{
		if (status->distanceToIngredients > 0)
		{
			cout << "The sim is too far from the ingredients to pick them up." << endl;
			return false;
		}
		//else sim is at the ingredients and can pick it up
		status->haveIngredients = true;
		cout << "The sim picked up the ingredients." << endl;
		return true;
	}

};


class WalkToCookerTask : public Node
{

};


class PutOnCookerTask : public Node
{

};


int main()
{

	return 0;
}