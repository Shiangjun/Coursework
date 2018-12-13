#include "coursework.h"
#include <pthread.h>  
#include <semaphore.h>

#define MAX_BUFFER_SIZE 10
#define  MAX_NUMBER_OF_JOBS 50

sem_t empty,full;            

struct queue tasks;
float t_sum_Res = 0, t_sum_TA = 0; 
int Produced_Counter = 0, Consumed_Counter = 0;

void *Producer_Demo(void *Pointer)
{

	do 
	{ 

        	if (sem_wait(&empty) == -1)
			exit(0);  
        
		struct element e = generateProcess();
        	int index;

		for (index = 0; index < tasks.count
	      		&& e.pid_time < tasks.e[index].pid_time; 
			index++);
		
		if (addHere(&tasks, &e, index) == -1) 
			exit(0);

		Produced_Counter++;

        	printf("\nProducer is running\nPID %d has been added into ready queue\n", e.pid, e.pid_priority);
        	printf("# of Jobs produced %d\n# of Jobs consumed %d\n", Produced_Counter, Consumed_Counter);

        	if (sem_post(&full) == -1)
			exit(0);  

	} while (Produced_Counter < MAX_NUMBER_OF_JOBS); 

}



void *Consumer_Demo(void *Pointer)
{
  
	do
	{
		if (sem_wait(&full) == -1)
			exit(0); 

		struct timeval staT, endT;
		int index = tasks.count - 1;
		struct element e = tasks.e[index];

		if (removeLast(&tasks) == -1)
			exit(0);

		gettimeofday(&staT, NULL);
		runNonPreemptiveJobv2(&e);
		gettimeofday(&endT, NULL);

		t_sum_Res += (int) getDifferenceInMilliSeconds(e.created_time, staT);
		t_sum_TA += (int) getDifferenceInMilliSeconds(e.created_time, endT);
	
		Consumed_Counter++;
	
        	printf("\nConsumer is running\nPID %d is running\n", e.pid);
		printf("# of Jobs produced: %d\n# of Jobs consumed: %d\n", Produced_Counter, Consumed_Counter);

        	if (sem_post(&empty) == -1)
			exit(0);

	} while (Consumed_Counter < MAX_NUMBER_OF_JOBS);

}


void InitTask()
{

	init(&tasks, MAX_BUFFER_SIZE);
	printf("Buffer Size: %d\n", MAX_BUFFER_SIZE);
	printf("Max Number of Jobs: %d\n", MAX_NUMBER_OF_JOBS);

	if (sem_init(&empty, 0, MAX_BUFFER_SIZE) == -1)
		exit(0);
	
	if (sem_init(&full, 0, 0) == -1)
		exit(0);

	return ;

}


void EndTask()
{

	if (sem_destroy(&empty) == -1)
		exit(0);

	if (sem_destroy(&full) == -1)
		exit(0);

	freeAll(&tasks);

	return ;

}

int main()
{     
	InitTask();
	
	pthread_t PT_Producer, PT_Consumer; 
    
	if (pthread_create(&PT_Producer, NULL, Producer_Demo, NULL) != 0)  
		printf("Creating Producer Fails"); 
	if (pthread_create(&PT_Consumer, NULL, Consumer_Demo, NULL) != 0)  
		printf("Creating Consumer Fails");  

	if (pthread_join(PT_Producer, NULL ) != 0)  
		printf("Joining Producer Fails");  
	if (pthread_join(PT_Consumer, NULL ) != 0)  
		printf("Joining Consumer Fails");  
	
	printf("\nAverage response time: %.2f milliseconds\nAverage turn around time: %.2f milliseconds\n", 
	       t_sum_Res/MAX_NUMBER_OF_JOBS, t_sum_TA/MAX_NUMBER_OF_JOBS);

	EndTask();
	
	return 0;  
}  

