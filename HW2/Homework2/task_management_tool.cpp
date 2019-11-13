/* @Author
 * Student Name: Fatih Altınpınar
 * Student ID: 150180707
 * Date: 13.11.2019
 */

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
    head = NULL;                // Setting head to NULL since there ar eno tasks.
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
    Task *task = new Task;                                      // Creating a copy of the task given as parameter
    task->day = in_task->day;                                   // Since same in_task is being sent to this function
    task->time = in_task->time;                                 // by changing their parameters rather than creating
    task->priority = in_task->priority;                         // a new task.
    task->name = new char[strlen(in_task->name) + 1];
    strcpy(task->name, in_task->name);

    if (head == NULL) {                     // If there are no tasks in the structure this one will be the first.
        head = task;
        head->next = head;
        head->previous = head;
        head->counterpart = NULL;
    }
    else if (task->day < head->day) {			// If the in_task is going to happen before head task we add it as the
        task->next = head;                      // new head.
        task->previous = head->previous;
        task->counterpart = NULL;
        head->previous->next = task;
        head->previous = task;
        head = task;
    }
    else {                                      // If it is not going to new head then:
        Task *current = head;
        while (current->day < task->day && current->next != head)   // Go over tasks until day of the current task is
            current = current->next;                                // greater or equal to added task.
        if (current->next == head && current->day < task->day){     // If the in_task has the greater day value than
            task->next = head;                                      // all of the tasks we need to at it before head.
            task->previous = current;
            task->counterpart = NULL;
            head->previous = task;
            current->next = task;
        }
        else if (task->day < current->day) {					// If task's day is smaller than current's day
            task->next = current;					            // It means that there is no task in the schedule that
            task->previous = current->previous;                 // is on the same day with in_task
            task->counterpart = NULL;                           // Thus in_task added to circular linked list part
            current->previous->next = task;
            current->previous = task;
        }
        else {
        // If there is at least one task with the same day of in_task's day it is required to be added to counterpart
            Task *current_task = current;
            if (task->time < current_task->time) {			// If new task is earlier than all other task on that day.
                task->next = current_task->next;            // previous and next days are connected to in_task
                task->previous = current_task->previous;
                task->counterpart = current_task;   // First task of that day before adding is connected as counterpart
                if (head == current_task)           // Checking if in_task going to replace head
                    head = task;
                current_task->next->previous = task;
                current_task->previous->next = task;
                current_task->next = NULL;
                current_task->previous = NULL;
            }
            else if (task->time == current_task->time) {
    // If new task has the same time with earliest task on that day then one of the tasks has to rescheduled by priority
                if (task->priority > current_task->priority) { // If in_task has a greater priority
                    task->next = current_task->next;           // It replaces the first task of the day
                    task->previous = current_task->previous;
                    current_task->previous->next = task;
                    current_task->next->previous = task;
                    task->counterpart = current_task->counterpart;
                    if (head == current_task)   // Checking if in_task going to replace head
                        head = task;
                    checkAvailableNextTimesFor(current_task); // First task of the day is rescheduled
                    current_task->day = getUsableDay();
                    current_task->time = getUsableTime();
                    add(current_task);
                    delete current_task->name;
                    delete current_task;
                }
                else {                              // If in_task has equal or less priority than first task of the day
                    checkAvailableNextTimesFor(task);       // Reschedule task to another time
                    task->day = getUsableDay();
                    task->time = getUsableTime();
                    add(task);
                    delete task->name;
                    delete task;
                }
            }
            else {      // If in_task is not going to first task of the day
                Task *prev_task = NULL;
                while (current_task != NULL && current_task->time < task->time ) {  // Iterate over counter_part
                    prev_task = current_task;       // until current_task time is greater or equal to in_task
                    current_task = current_task->counterpart;   // prev_task is required to connect counter_part of the
                                                                // of the structure since it is just a linked list
                                                                // that goes one way.
                }

                if (current_task != NULL && current_task->time == task->time) { // If in_task is going to replace another task
                    if (task->priority > current_task->priority) {    // If in_task has a higher priority
                        prev_task->counterpart = task;                // task will be replaced is rescheduled
                        task->next = NULL;
                        task->previous = NULL;
                        task->counterpart = current_task->counterpart;
                        checkAvailableNextTimesFor(current_task);
                        current_task->day = getUsableDay();
                        current_task->time = getUsableTime();
                        add(current_task);
                        delete current_task->name;
                        delete current_task;
                    }
                    else {                                          // Rescheduling in_task since it has lower priority.
                        checkAvailableNextTimesFor(task);
                        task->day = getUsableDay();
                        task->time = getUsableTime();
                        add(task);
                        delete task->name;
                        delete task;
                    }
                }
                else {  // If in_task is not going replace any other task it is inserted in between prev_task
                        // and counterpart which has a greater time than in_task.
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
    if(head == NULL)
        return NULL;
    Task *current = head;
    while (current->next != head && current->day < day)		// Search for day
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
    if (current_day == NULL) {              // If there is no task return day+1 and 8 as hour.
        usable_day = delayed->day + 1;
        usable_time = 8;
        return;
    }
    while (current_day->day < delayed->day && current_day->next != head) {      //Find tasks location from day aspect
        current_day = current_day->next;
    }

    if (current_day->day == delayed->day) {
        current_task = current_day;                 // If there is a day with the same day of the delayed task
        while (current_task->counterpart != NULL && current_task->counterpart->time <= delayed->time)
            current_task = current_task->counterpart; // Iterate until we pass the delayed task

        while (current_task->counterpart != NULL) {     // Until the end of the counterpart check if there is time
                                                        // between current_task and next task that is available.
            if ((current_task->counterpart->time) - (current_task->time) >= 2) {
                usable_day = current_task->day;
                usable_time = current_task->time + 1;
                return;
            }
            else
                current_task = current_task->counterpart;
        }
        // If there is no available time in same day the delayed function iterate to next day
        current_day = current_day->next;
    }

    while (current_day != head) {       // Check every day until we get back to head for available times
        current_task = current_day;
        if(current_task->time > 8){     // If first day of the task starts at a time greater than 8, task can be
            usable_day = current_task->day; // delayed to this day at 8 am
            usable_time = 8;
            return;
        }
        while (current_task->counterpart != NULL) { // Otherwise look for available times between tasks in counterpart
            if ((current_task->counterpart->time) - (current_task->time) >= 2) {
                usable_day = current_task->day;
                usable_time = current_task->time + 1;
                return;
            }else
                current_task = current_task->counterpart;
        }
        current_day = current_day->next;
    }


    current_day = head; // If available time is not found we need to find the first non allocated time.
    while (current_day->day < delayed->day && current_day->next != head)
        current_day = current_day->next;   // Iterate until current_day has greater or equal day to delayed one.
    while (current_day != head){      // Iterate until the end
        current_task = current_day;
        while(current_task->counterpart != NULL)
            current_task = current_task->counterpart;   // Get to end of the day
        if(current_task->time < 16){                    // If there last task of the day is on an hour lesser than 16
            usable_time = current_task->time + 1;       // return this as the available time for the task.
            usable_day = current_task->day;
            return;
        }
        current_day = current_day->next;
    }
}

void WorkPlan::delayAllTasksOfDay(int day)
{
    Task *current = head;
    while (current->day < day && current->next != head)
        current = current->next;                //First first task of the day which requires to be delayed is found
    if (current->day == day) {                  // If found
        current->previous->next = current->next;    // Remove this day completely from the structure so tasks in this day
        current->next->previous = current->previous;    // cannot be delayed into this day again

        while (current != NULL) {               // Go over every task in the day that has been removed from schedule
            Task *tmp = current->counterpart;
            checkAvailableNextTimesFor(current);    // Find available times for the task
            current->day = getUsableDay();
            current->time = getUsableTime();
            add(current);                           // Add the task
            delete current->name;                   // Remove the one that was connected to current day.
            delete current;
            current = tmp;
        }
    }
    else
        return;
}

void WorkPlan::remove(Task *target)
{
    Task *prev = head->previous;
    Task *current = head;
    while (current->day < target->day && current->next != head) {   // Iterate until correct day is found.
        prev = current;
        current = current->next;
    }
    if (current->day == target->day) {
        while (current != target && current->counterpart != NULL) { // Iterate over correct task with the time is found
            prev = current;
            current = current->counterpart;
        }
        if (current == target) {
            if (target->next != NULL) {                 // If target task is the first task of that day
                if (head == current) {                  // If target is head
                    if (current->counterpart != NULL)   // new will be counterpart if it has go one
                        head = current->counterpart;
                    else                                // if it does not have counterpart new head will be first task
                        head = current->next;           // of the next day
                }
                if (current->counterpart != NULL) { // If it has got a counterpart connect it as the first task of the day
                    prev->next = current->counterpart;
                    current->next->previous = current->counterpart;
                    current->counterpart->next = current->next;
                    current->counterpart->previous = prev;
                }
                else {                              // If it does not have counterpart connect previous day to next day
                    prev->next = current->next;
                    current->next->previous = prev;
                }

            }
            else {          // If it is not the first task of the day connect previous counterpart to next counterpart
                prev->counterpart = target->counterpart;
            }
            delete target->name;                   //Deallocate memory of the target node
            delete target;
        }
    }
    return;
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