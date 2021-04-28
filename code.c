#define MAX_TASKS 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id; // task id
    int priority;
    int arrivialTime;
    int burstTime;
} Task;
 Task* Build(int id, int priority , int arrivialTime , int burstTime)
 {
     Task* task = (Task*)malloc(sizeof( Task));
     task->id = id;
     task->priority = priority;
     task->burstTime = burstTime;
     task->arrivialTime = arrivialTime;
     return task;

 }
Task** Table(char* fileName)
{
    int id; // task id
    int priority;
    int arrivialTime;
    int burstTime;
    Task** array_task= malloc(MAX_TASKS*sizeof(Task*));
    FILE *read;
    int i=0;
    read = fopen(fileName,"r");
    while (!feof(read))
    {

        fscanf(read,"%d%*c %d%*c %d%*c %d%*c",&id,&priority,&arrivialTime,&burstTime);
        array_task[i] = Build(id,priority,arrivialTime,burstTime);


        i++;

    }
    return array_task;

}
void Display(Task** arr )

{
    int i=0;
    printf("=======================PROCESS==TABLE=============================\n");
    printf("  ID    |    priority   |   Arrivial Time  |    Burst Time \n");
    printf("---------+---------------+------------------+-----------------\n");
    while(arr[i] != NULL && i< MAX_TASKS )
    {
        printf("  %d     |",arr[i]->id);
        printf("    %d           |",arr[i]->priority);
        printf("  %d              |",arr[i]->arrivialTime);
        printf("  %d  \n",arr[i]->burstTime);

        i++;

    }
    printf("=================================================================\n");

}


void main(int argc,char **argv)
 {


    Task** arr = Table(argv[1]);
    Display(arr);
 }



