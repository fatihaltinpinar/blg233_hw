/*
PLEASE DO NOT CHANGE THIS FILE 
*/

#define NAME_LENGTH 2

struct Task{
	//Task() : previous(NULL),next(NULL),counterpart(NULL){} // Default values for previous, next, counterpart 
	char *name;
	int day;
	int time;
	int priority;

	Task *previous;
	Task *next;
	Task *counterpart;
};
