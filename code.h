#define MAX_TASKS 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lengh=0;
typedef enum
{
    FCFS = 1,
    SJF =  2,
    Priority = 3,
    Round_robin = 4,
    Pr_round_robin = 5
}Algorithm;
typedef struct {
    int id; // task id
    int priority;
    int arrivialTime;
    int burstTime;
} Task;
typedef struct
{
    Task currentTask;
    int roundTime;
    int leftTime;
}Thread;
struct QNode {
    Thread thread;
    struct QNode* next;
};
struct Queue {
    struct QNode *front, *rear;
};
 Task* Build(int id, int priority , int arrivialTime , int burstTime);
 Task** Table(char* fileName);
 void Display(Task** arr );
 void swapStruct(Task *firstStruct , Task *seondStruct); //  swap function to use it with bubble sort
void shortTimeSortStruct(Task** arr , int len);
void firstComeFirstServer(Task** arr);
void shortJobFirst(Task** arr);
void proiritySort(Task** arr ,int len );
void prioritySchedule(Task** arr);
void Schedule(Algorithm algoName,Task** arr );
Task* copyContient(Task* struct2);
int getTotalBurstTime(Task** arr);
void roundRobin(Task** arr,struct Queue* q);
struct QNode* newNode(Thread thread);
struct Queue* createQueue();
void enQueue(struct Queue* q, Thread k);
void deQueue(struct Queue* q);
Thread initThread(Task* task);
void addToQueue(Task** arr,struct Queue* q,int time1,int time2,int* lastindex);
void updateThread(Thread* thread);


