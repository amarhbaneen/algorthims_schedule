#include "code.h"


void main(int argc,char **argv)
 {


    Task** arr = Table(argv[1]);
    Display(arr);
    Schedule(FCFS,arr);
    Schedule(SJF,arr);
    Schedule(Priority,arr);
    Schedule(Round_robin,arr);
    Schedule(Pr_round_robin,arr);








}


 Task* Build(int id, int priority , int arrivialTime , int burstTime)
 {

     Task* task = (Task*)malloc(sizeof( Task));
     task->id = id;
     task->priority = priority;
     task->burstTime = burstTime;
     task->arrivialTime = arrivialTime;
     lengh++;
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
    while(arr[i] != NULL && i< lengh )
    {
        printf("  %d     |",arr[i]->id);
        printf("    %d           |",arr[i]->priority);
        printf("  %d              |",arr[i]->arrivialTime);
        printf("  %d  \n",arr[i]->burstTime);

        i++;

    }
    printf("=================================================================\n");


}
void swapStruct(Task *firstStruct , Task *seondStruct) //  swap function to use it with bubble sort
{
    Task tempStruct = *firstStruct;
    *firstStruct = *seondStruct;
    *seondStruct = tempStruct;
}
void shortTimeSortStruct(Task** arr , int len)
{
    int i,j;
    for (i = 0; i < len-1 && arr[i] != NULL; i++)


        for (j = 0; j < len-1-i; j++)
            if (arr[j]->burstTime > arr[j+1]->burstTime)
                swapStruct(arr[j], arr[j+1]);
}
void firstComeFirstServer(Task** arr)
{
    int i=0;

    while (arr[i] != NULL && i< lengh)
    {
        printf("<P<%d>,%d>",arr[i]->id,arr[i]->burstTime);
        i++;
    }


}
void shortJobFirst(Task** arr)
{
    shortTimeSortStruct(arr,lengh);
    firstComeFirstServer(arr);
}
void proiritySort(Task** arr ,int len )
{
     int i,j;
    for (i = 0; i < len-1 && arr[i] != NULL; i++)


        for (j = 0; j < len-1-i; j++)
            if (arr[j]->priority < arr[j+1]->priority)
                swapStruct(arr[j], arr[j+1]);
}
void prioritySchedule(Task** arr)
{
    proiritySort(arr,lengh);
    firstComeFirstServer(arr);
}
void Schedule(Algorithm algoName,Task** arr )


{
    switch (algoName)
    {
    case 1:
        printf("Scheduling Tasks - First Come First Server Algorthim :\n");
        firstComeFirstServer(arr);
            printf("\n");

        break;

    case 2:
        printf("Scheduling Tasks - Shortest Job First  Algorthim :\n");
        shortJobFirst(arr);
            printf("\n");

        break;
    case 3:
        printf("Scheduling Tasks - Proirty  Algorthim :\n");
        prioritySchedule(arr);
        printf("\n");
         break;

    case 4:
            printf("Scheduling Tasks - Round Robin Algorthim :\n");
            struct Queue* q = createQueue();
            roundRobin(arr,q);
            printf("\n");
            break;
     case 5:
            printf("Scheduling Tasks - Round Robin Algorthim with  Priority :\n");
            struct Queue* q1 = createQueue();
            roundRobin(arr,q1);
            printf("\n");
            break;




    default:
        break;
    }

}

Task* copyContient(Task* struct2)
{
    Task* struct1 = (Task*) malloc (sizeof(Task));
    struct1->id = struct2->id;
    struct1->arrivialTime = struct2->arrivialTime;
    struct1->burstTime = struct2->burstTime;
    struct1->priority = struct2->priority;
    return struct1;
}
int getTotalBurstTime(Task** arr)
{
    int total=0;
    for(int i=0;i<MAX_TASKS && arr[i] != NULL;i++)
    {
        int Tasktime = (arr[i]->burstTime % 2) + (arr[i]->burstTime /2);
        total = total+Tasktime;

    }
    return total;
}
void roundRobin1(Task** arr)
{

    int readyQueueLength = getTotalBurstTime(arr);
     Task** readyQueue =(Task**) malloc (getTotalBurstTime(arr) * sizeof(Task*));
     int past_time=0;
     int j=0;

     for(int i=0;i<MAX_TASKS && arr[i] != NULL;i++)
     {
         if(arr[i]->arrivialTime <= past_time && arr[i]->burstTime > 0)
         {

              readyQueue[j]=copyContient(arr[i]);
              past_time = past_time+2;
              arr[i]->burstTime = arr[i]->burstTime-2;
              j++;

         for(int k=0;k<MAX_TASKS && arr[k]!= NULL;k++)
         {
             if(k == i)
             {
                 k++;
             }
             else{

                 if( arr[k]->burstTime > 0 && arr[k]->arrivialTime <= past_time )
                 {

                     readyQueue[j]=copyContient(arr[k]);
                     j++;
                     arr[k]->burstTime = arr[k]->burstTime-2;
                 }
                 else{
                     k++;
                 }

             }
         }
         if(arr[i]->burstTime > 0)
         {

             readyQueue[j] = copyContient(arr[i]);

             arr[i]->burstTime = arr[i]->burstTime -2;

             j++;


         }
         }


     }
        for(int i=0;i< readyQueueLength && readyQueue[i] != NULL;i++)
        {
            printf("p %d - Burst %d \n", readyQueue[i]->id ,readyQueue[i]->burstTime);
        }


}
struct QNode* newNode(Thread thread)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->thread = thread;
    temp->next = NULL;
    return temp;
}
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
void enQueue(struct Queue* q, Thread k)
{
    // Create a new LL node
    struct QNode* temp = newNode(k);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}
void deQueue(struct Queue* q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return;

    // Store previous front and move front one node ahead
    struct QNode* temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}
void roundRobin(Task** arr,struct Queue* q ){
    int past_time =0 ;
    int lastindex=0;
    addToQueue(arr,q,past_time,past_time+2,&lastindex);

    for(int i=0;i<lastindex;i++)
    {
          Thread th = q->front->thread;
    deQueue(q);
    printf("<P<%d>,%d>",th.currentTask.id,th.roundTime);
    updateThread(&th);
    if(th.leftTime > 0 )
    {
         enQueue(q,th);
    }

     past_time = past_time+2;
     addToQueue(arr,q,past_time,past_time+2,&lastindex);
    }
    while ( q->front != NULL )
    {

          Thread th = q->front->thread;
          deQueue(q);
          printf("<P<%d>,%d>",th.currentTask.id,th.roundTime);
          updateThread(&th);
            if(th.leftTime > 0 )
            {
                 enQueue(q,th);
             }


    }









}
Thread initThread(Task* task)
{
    Thread thread;
    thread.currentTask = *task;
    thread.leftTime=task->burstTime;
    if(task->burstTime < 2)
    {
        thread.roundTime = 1;

    }
    else{
        thread.roundTime = 2;
    }
    return thread;
}
void updateThread(Thread* thread)
{
    thread->leftTime =thread->leftTime - 2 ;
    if(thread->leftTime < 2)
    {
        thread->roundTime = 1;

    }
    else{
        thread->roundTime = 2;
    }
}

void addToQueue(Task** arr,struct Queue* q,int time1 , int time2,int* lastindex)
{


    for(int i =*lastindex;i< MAX_TASKS && arr[i] != NULL; i++)
    {
        if(arr[i]->arrivialTime <= time2 && arr[i]->arrivialTime >= time1)
        {
            Thread thread = initThread(arr[i]);
            enQueue(q,thread);
            *lastindex = *lastindex +1;

        }

    }

}