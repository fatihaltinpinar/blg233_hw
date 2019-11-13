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
	Task *task = new Task;
	task->day = in_task->day;
	task->time = in_task->time;
	task->priority = in_task->priority;
	task->name = new char[strlen(in_task->name) + 1];
	strcpy(task->name, in_task->name);

	if (head == NULL) {				// Add if no task exists
		head = task;
		head->next = head;
		head->previous = head;
		head->counterpart = NULL;
	}
	else if (task->day < head->day) {			// Add if the task is earlier than the previous head task.
		task->next = head;
		task->previous = head->previous;
		task->counterpart = NULL;
		head->previous->next = task;
		head->previous = task;
		head = task;
	}
	else {
		Task *current = head;
		while (current->day < task->day && current->next != head) // Get to the day required by the task in the list.
			current = current->next;
		
		if (current->day != task->day) {						// If there are no task in the same day with 
			task->next = current;								// Insert task into the circular doubly linked list
			task->previous = current->previous;
			task->counterpart = NULL;
			current->previous->next = task;
			current->previous = task;
		}
		else {													// If there are tasks with the same day
			Task *current_task = current;
			if (task->time < current_task->time) {				// If new task is earlier than all other task on that day.
				task->next = current_task->next;
				task->previous = current_task->previous;
				task->counterpart = current_task;
				if (head == current_task)
					head = task;
				current_task->next->previous = task;
				current_task->previous->next = task;
				current_task->next = NULL;
				current_task->previous = NULL;
			}
			else if (task->time == current_task->time) {		// If new task has the same time with earliest task on that day
				if (task->priority > current_task->priority) {	// that is already added to structure check priorities and replace accordingly
					task->next = current_task->next;
					task->previous = current_task->previous;
					current_task->previous->next = task;
					current_task->next->previous = task;
					task->counterpart = current_task->counterpart;	
					if (head == current_task)
						head = task;
					checkAvailableNextTimesFor(current_task);	
					current_task->day = getUsableDay();
					current_task->time = getUsableTime();
					add(current_task);
				}
				else {
					checkAvailableNextTimesFor(task);
					task->day = getUsableDay();
					task->time = getUsableTime();
					add(task);
				}
			}
			else {
				Task *prev_task = NULL;
				while (current_task->time < task->time && current != NULL) {
					prev_task = current_task;
					current_task = current_task->counterpart;
				}

				if (current_task != NULL && current_task->time == task->time) {
					if (task->priority > current_task->priority) {
						prev_task->counterpart = task;
						task->next = NULL;
						task->previous = NULL;
						task->counterpart = current_task->counterpart;
						checkAvailableNextTimesFor(current_task);
						current_task->day = getUsableDay();
						current_task->time = getUsableTime();
						add(current_task);
					}
					else {
						checkAvailableNextTimesFor(task);
						task->day = getUsableDay();
						task->time = getUsableTime();
						add(task);
					}
				}
				else {
					prev_task->counterpart = task;
					task->next = NULL;
					task->previous = NULL;
					task->counterpart = current_task;
				}

			}							
		}
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
{	
	Task *current_day = head;
	Task *current_task = head;
	if (current_day == NULL) {
		usable_day = delayed->day + 1;
		usable_time = 8;
		return;
	}
	while (current_day->day < delayed->day && current_day->next != head) {
		current_day = current_day->next;
	}
	
	if (current_day->day == delayed->day) {
		current_task = current_day;
		while (current_task->time <= delayed->time && current_task->counterpart != NULL) 
			current_task = current_task->counterpart;
		
		while (current_task->counterpart != NULL) {
			if ((current_task->counterpart->time) - (current_task->time) >= 2) {
				usable_day = current_task->day;
				usable_time = current_task->time + 1;
				return;
			}
			else 
				current_task = current_task->counterpart;
		}
	}else {
		while (current_day->next != head) {
			current_task = current_day;
			while (current_task->counterpart != NULL) {
				if ((current_task->counterpart->time) - (current_task->time) >= 2) {
					usable_day = current_task->day;
					usable_time = current_task->time + 1;
					return;
				}else
					current_task = current_task->counterpart;
			}
			current_day = current_day->next;
		}
	}
	// If available time does not exists
	current_day = head;
	while (current_day->day < delayed->day && current_day->next != head) 
		current_day = current_day->next;
	if (current_day->day == delayed->day) {
		current_task = current_day;
		while (current_task->counterpart != NULL) 
			current_task = current_task->counterpart;

		if (current_task->time < 16) {
			usable_time = current_task->time + 1;
			usable_day = current_task->day;
			return;
		}
	}else if((current_day->next->day) - (current_day->day) >= 2 || current_day->next == head){
		usable_day = current_day->day + 1;
		usable_time = 8;
		return;
	}
	else {
		Task temp;
		temp.day = current_day->day + 1;
		temp.time = 8;
		checkAvailableNextTimesFor(&temp);
	}
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	Task *current = head;
	while (current->day < day && current->next != head)
		current = current->next;
	if (current->day == day) {
		current->previous->next = current->next;
		current->next->previous = current->previous;

		while (current != NULL) {
			Task *tmp = current->counterpart;
			checkAvailableNextTimesFor(current);
			add(current);
			delete current->name;
			delete current;
			current = tmp;
		}
	}
	else
		return;
}

void WorkPlan::remove(Task *target)
{
	
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
