#include "main.h"
#include <iostream>
#include <list>

using namespace std;

/*
								Root
								  |
							  Sequence 1
						/					 \
			Selector1						Sequence2
			/		\					 /				\
Got Ingredients?	Sequence3		WalkToCooker	  CookFood
				  /			\
		   	 WalkToIng	 PickUpIng

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
			{
				cout << "The sim is now " << status->distanceToIngredients << " meters from the ingredients." << endl;
			}
			else if (status->distanceToIngredients == 1)
			{
				cout << "The sim is now only 1 meter away from the ingredients." << endl;
			}
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
private:
	CookingStatus* status;

public:
	WalkToCookerTask(CookingStatus* status) : status(status) {}
	virtual bool willRun() override
	{
		if (status->distanceToCooker > 0)
		{
			cout << "The sim approaches the cooker." << endl;
			status->distanceToCooker--;

			if (status->distanceToCooker > 1)
			{
				cout << "The sim is " << status->distanceToCooker << " from the cooker." << endl;
			}
			else if (status->distanceToCooker == 1)
			{
				cout << "The sim is now only 1 metre from the cooker." << endl;
			}
			else
			{
				cout << "The sime is now at the cooker" << endl;
			}
		}
		return true;
	}
};


class PutOnCookerTask : public Node
{
private:
	CookingStatus* status;
	
public:
	PutOnCookerTask(CookingStatus* status) : status(status) {}
	virtual bool willRun() override
	{
		if (status->distanceToCooker > 0)
		{
			cout << "The sim is too far from the cooker to cook the ingredients." << endl;
			return false;
		}
		else
		{
			status->isCooked = true;
			cout << "The sim cooks the food" << endl;
			return true;
		}
	}
};


int main()
{
	Selector *root = new Selector, *selector1 = new Selector;

	Sequence *sequence1 = new Sequence;
	Sequence *sequence2 = new Sequence;
	Sequence *sequence3 = new Sequence;

	//sets it so sim hasnt cooked and has no ingredients and is both 3 meters from ingredients and cooker
	CookingStatus* cookingStatus = new CookingStatus{ false, false, 3, 3 };

	CheckIfIngredientsNeededTask* checkIngredients = new CheckIfIngredientsNeededTask(cookingStatus);
	WalkToIngredientsTask* walkIngredients = new WalkToIngredientsTask(cookingStatus);
	PickUpTheIngredientsTask* pickUpIngredients = new PickUpTheIngredientsTask(cookingStatus);
	WalkToCookerTask* walkCooker = new WalkToCookerTask(cookingStatus);
	PutOnCookerTask* cookFood = new PutOnCookerTask(cookingStatus);

	//root is sequence as both need to return true before the task is finished (food is cooked)
	root->addChild(sequence1);

	//ingredients is selector as if they already have ingredients it can return true and be a completed branch
	sequence1->addChild(selector1);

	//cooking has to be sequence as it means walking to cooker and cooking the food
	//(could be changed to selector for the "isCooked") 
	sequence1->addChild(sequence2);

	//check or get ingredients branch
	selector1->addChild(checkIngredients);
	selector1->addChild(sequence3);

	sequence3->addChild(walkIngredients);
	sequence3->addChild(pickUpIngredients);

	//cooking branch
	sequence2->addChild(walkCooker);
	sequence2->addChild(cookFood);

	while (!root->willRun())
	{
		cout << "---------------------------------" << endl;
	}
	cout << endl << "Operation Complete. Behaviour tree exited" << endl;
	cin.get();


	/*
				 OUTPUT
	The sim has not got the ingredients.
	The sim approaches the ingredients.
	The sim is now 2 meters from the ingredients.
	The sim is too far from the ingredients to pick them up.
	---------------------------------
	The sim has not got the ingredients.
	The sim approaches the ingredients.
	The sim is now only 1 meter away from the ingredients.
	The sim is too far from the ingredients to pick them up.
	---------------------------------
	The sim has not got the ingredients.
	The sim approaches the ingredients.
	The person is at the ingredients.
	The sim picked up the ingredients.
	The sim approaches the cooker.
	The sim is 2 from the cooker.
	The sim is too far from the cooker to cook the ingredients.
	---------------------------------
	The sim has the ingredients needed.
	The sim approaches the cooker.
	The sim is now only 1 metre from the cooker.
	The sim is too far from the cooker to cook the ingredients.
	---------------------------------
	The sim has the ingredients needed.
	The sim approaches the cooker.
	The sime is now at the cooker
	The sim cooks the food

	Operation Complete. Behaviour tree exited

	*/
}