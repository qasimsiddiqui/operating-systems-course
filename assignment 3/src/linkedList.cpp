#include <iostream>
#include <iomanip>

using namespace std;

struct node
{
	string name;
	int burstTime;
	int arrivalTime;
	int priority;

	int waitingTime;
	int turnaroundTime;
	node *next;
};

class linkedList
{
private:
	node *head = NULL;

public:
	linkedList(/* args */);
	void insertItem(string, int, int, int);
	void deleteItem(string);
	void traverse();
	node *getHead();
};

linkedList::linkedList(/* args */)
{
}

node *linkedList::getHead()
{
	return head;
}

void linkedList::traverse()
{
	node *temp;
	temp = head;
	cout << "Linked List : ";
	if (temp == NULL)
	{
		cout << "Empty Linked List." << endl;
	}
	else
	{
		cout << "\n_______________________________________________________________________________________________________________";
		cout << "\n||  Process Name  ||   Priority   ||   Burst Time   ||  Arrival Time  ||  Waiting Time  ||  Turnaround Time  ||";
		cout << "\n||================||==============||================||================||================||===================||";
		while (temp != NULL)
		{
			cout << "\n||" << setw(9) << temp->name << setw(9) << "||" << setw(8) << temp->priority << setw(8) << "||" << setw(9) << temp->burstTime << setw(9) << "||" << setw(8) << temp->arrivalTime << setw(10) << "||" << setw(9) << temp->waitingTime << setw(9) << "||" << setw(10) << temp->turnaroundTime << setw(11) << "||";
			temp = temp->next;
		}
		cout << "\n";
	}
}

node *createNode(string name, int priority, int burstTime, int arrivalTime)
{
	node *temp;
	temp = new struct node;
	temp->name = name;
	temp->priority = priority;
	temp->arrivalTime = arrivalTime;
	temp->burstTime = burstTime;
	temp->turnaroundTime = 0;
	temp->waitingTime = 0;
	temp->next = NULL;
	return temp;
}

void linkedList::insertItem(string name, int priority, int burstTime, int arrivalTime)
{
	node *temp, *end;
	temp = createNode(name, priority, burstTime, arrivalTime);
	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		end = head;
		while (end->next != NULL)
		{
			if (end->name == name || end->next->name == name)
			{
				cout << "\nA process already exists with same name.\n";
				return;
			}
			end = end->next;
		}
		end->next = temp;
	}
}

void linkedList::deleteItem(string name)
{
	node *temp, *previous;
	temp = head;
	previous = head;
	bool deleted = false;
	if (temp == NULL)
	{
		cout << "\nEmpty Linked List." << endl;
	}
	else
	{
		while (temp != NULL)
		{
			if (temp->name == name)
			{
				previous->next = temp->next;
				deleted = true;
				break;
			}
			else
			{
				previous = temp;
				temp = temp->next;
			}
		}
	}
	if (deleted)
		cout << "\nProcess \'" << name << "\' is deleted.\n";
	else
		cout << "\nProcess \'" << name << "\' not found.\n";
}
