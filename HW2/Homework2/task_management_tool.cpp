/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{		
	head = NULL;
}

void WorkPlan::close()
{
	head->previous->next = NULL;								// Break circular linked list
	while (head != NULL) {										// Loop until no day left
		Task *tmp_day = head->next;								// Store next day's first task's pointer	
		while (head != NULL) {									// Loop until no task left in that day
			Task *tmp_counterpart = head->counterpart;			// Store next task of that day.
			delete head->name;			
			delete head;
			head = tmp_counterpart;
		}
		head = tmp_day;
	}
}

void WorkPlan::add(Task *in_task)
{
	// Create a new task
	Task *task = new Task;
	*task = *in_task;
	task->name = new char(strlen(in_task->name) + 1);
	strcpy(task->name, in_task->name);
	if (head == NULL) {
		head = task;
		head->next = head;
		head->previous = head;
		head->counterpart = NULL;
	}
	else {

	}
} 

Task * WorkPlan::getTask(int day, int time)
{
	Task *current = head;
	while (current->day < day)								// Search for day
		current = current->next;
	if (current->day != day)								// If the given day does not exists
		return NULL;
	else {													// If given day exists then search for the time
		while (current != NULL && current->time < time)		// Search for time
			current = current->counterpart;
		if (current != NULL && current->time == time)		// If the time is correct return the task
			return current;
		else
			return NULL;									// If time is not correct or the no more nodes exists return NULL
	}
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{	//THIS FUNCTION WILL BE CODED BY YOU
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	//THIS FUNCTION WILL BE CODED BY YOU
}

void WorkPlan::remove(Task *target)
{
	//THIS FUNCTION WILL BE CODED BY YOU
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
