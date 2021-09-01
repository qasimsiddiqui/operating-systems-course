#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "linkedList.cpp"

void swap(node *, node *);
void sortList(linkedList &);
void drawGanttChart(linkedList &);
void calculateWaitingTime(linkedList &);
void calculateTurnaroundTime(linkedList &);
void readFileAndInsertProcess(linkedList &, const char *);

int main(int argc, char const *argv[])
{
	char ch;
	linkedList list;
	cout << "Priority Scheduler Implementation";
	do
	{
		cout << "\n\nSelect Option:\n"
			 << "1 >> Insert a New Process\n"
			 << "2 >> Sort Process\n"
			 << "3 >> Read file and Insert process into linked list\n"
			 << "4 >> Delete a Process\n"
			 << "5 >> Traverse the Linked list\n"
			 << "6 >> Calculate Turnaround Time\n"
			 << "7 >> Calculate waiting Time\n"
			 << "8 >> Draw Gantt Chart\n"
			 << "0 >> Exit\n";
		cin >> ch;
		switch (ch)
		{
		case '0':
		{
			exit(0);
			break;
		}
		case '1':
		{
			string name;
			int priority;
			int arrival;
			int burst;
			cout << "Enter name of Process: ";
			cin >> name;
			cout << "Enter priority of Process: ";
			cin >> priority;
			cout << "Enter burst time of Process: ";
			cin >> burst;
			cout << "Enter arrival time of Process: ";
			cin >> arrival;

			list.insertItem(name, priority, burst, arrival);

			list.traverse();
			break;
		}
		case '2':
		{
			sortList(list);
			list.traverse();
			break;
		}
		case '3':
		{
			readFileAndInsertProcess(list, argv[1]);
			list.traverse();
			break;
		}
		case '4':
		{
			string name;
			cout << "Enter name of Process to delete: ";
			cin >> name;
			list.deleteItem(name);
			break;
		}
		case '5':
		{
			list.traverse();
			break;
		}
		case '6':
		{
			calculateTurnaroundTime(list);
			list.traverse();
			break;
		}
		case '7':
		{
			calculateWaitingTime(list);
			list.traverse();
			break;
		}
		case '8':
		{
			drawGanttChart(list);
			//list.drawGanttChart();
			break;
		}
		default:
		{
			cout << "Invalid Choice. Try again." << endl;
			break;
		}
		}
	} while (ch != '0');
	return 0;
}

void swap(struct node *a, struct node *b)
{
	string name = a->name;
	int priority = a->priority;
	int arrival = a->arrivalTime;
	int burst = a->burstTime;

	a->arrivalTime = b->arrivalTime;
	a->burstTime = b->burstTime;
	a->name = b->name;
	a->priority = b->priority;

	b->arrivalTime = arrival;
	b->burstTime = burst;
	b->priority = priority;
	b->name = name;
}

void sortList(linkedList &list)
{
	node *temp = list.getHead();

	// Traverse the List
	while (temp)
	{
		node *min = temp;
		node *r = temp->next;

		// Traverse the unsorted sublist
		while (r)
		{
			if (min->priority > r->priority)
				min = r;

			r = r->next;
		}

		swap(temp, min);
		temp = temp->next;
	}
}

void readFileAndInsertProcess(linkedList &list, const char *filePath)
{
	ifstream inFile;
	inFile.open(filePath);
	cout << filePath;
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!inFile.eof())
	{
		int i;
		string name;
		string subStr;
		int val[3];
		string line = "";

		getline(inFile, line);

		stringstream ss(line);

		i = -1;
		while (!ss.eof())
		{
			getline(ss, subStr, ',');

			if (i == -1)
			{
				name = subStr;
			}
			else
			{
				val[i] = stoi(subStr);
			}
			i++;
		}

		list.insertItem(name, val[0], val[1], val[2]);
	}
	inFile.close();
}

void calculateTurnaroundTime(linkedList &list)
{
	calculateWaitingTime(list);
	node *temp;
	temp = list.getHead();
	if (temp == NULL)
	{
		cout << "Empty Linked List." << endl;
	}
	else
	{
		while (temp != NULL)
		{
			temp->turnaroundTime = temp->waitingTime + temp->burstTime;
			temp = temp->next;
		}
	}
}

void calculateWaitingTime(linkedList &list)
{
	sortList(list);
	node *temp,
		*p;
	temp = list.getHead();
	int Wtime = 0;
	if (temp == NULL)
	{
		cout << "Empty Linked List." << endl;
	}
	else
	{
		while (temp != NULL)
		{
			p = list.getHead();
			Wtime = 0;
			while (p->name != temp->name)
			{
				Wtime += p->burstTime;
				p = p->next;
			}
			temp->waitingTime = Wtime;
			temp = temp->next;
		}
	}
}

void drawGanttChart(linkedList &list)
{
	calculateTurnaroundTime(list);
	node *temp;
	temp = list.getHead();
	int sign;
	int TAtime;
	if (temp == NULL)
	{
		cout << "\nEmpty Linked List." << endl;
	}
	else
	{
		cout << "\n\n0";
		while (temp != NULL)
		{
			cout << setw(temp->burstTime / 2) << temp->turnaroundTime;
			if (temp->next == NULL)
				TAtime = temp->turnaroundTime;
			temp = temp->next;
		}
		cout << "\n|";
		sign = TAtime;
		sign = (sign / 2) - 4;
		while (sign >= 0)
		{
			cout << "=";
			sign--;
		}
		cout << "|\n|";
		temp = list.getHead();
		while (temp != NULL)
		{
			cout << setw(temp->burstTime / 2) << "|";
			temp = temp->next;
		}
		cout << "\n|";
		sign = TAtime;
		sign = (sign / 2) - 4;
		while (sign >= 0)
		{
			cout << "=";
			sign--;
		}
		cout << "|\n";
		temp = list.getHead();
		while (temp != NULL)
		{
			cout << temp->name << setw(temp->burstTime / 2);
			temp = temp->next;
		}
	}
}
