#include "coursework.h"
#include<semaphore.h>  
#include<pthread.h>

#define MAX_BUFFER_SIZE 10
#define MAX_NUMBER_OF_JOBS 50

sem_t empty[3], full;

struct queue PQ_tasks[PRIORITY];
float t_sum_Res = 0, t_sum_TA = 0;   
int Produced_Counter = 0, Consumed_Counter = 0;

void *Producer_Demo()
{

        do  
	{

        	struct element e = generateProcess();
        
		if (sem_wait(&empty[e.pid_priority]) == -1)
			exit(0);   
		
		if (addFirst(&PQ_tasks[e.pid_priority], &e) == -1) 
			exit(0);

        	Produced_Counter++;

        	printf("\nProducer is running\nPID %d has been added into queue %d\n", e.pid, e.pid_priority);
        	printf("# of Jobs produced %d\n# of Jobs consumed %d\n", Produced_Counter, Consumed_Counter);

        	if (sem_post(&full) == -1)
			exit(0); 
    
	} while (Produced_Counter < MAX_NUMBER_OF_JOBS);

}

void *Consumer_Demo(void *arg)
{

	int tag = *(int*)arg;
	tag --;

        do 
	{

		struct timeval startTime, currentTime;
        	int Number_Time_Slice = 0;

		if (sem_wait(&full) == -1)
			exit(0);

		while (PQ_tasks[tag].count > 0)
		{

			int counter = PQ_tasks[tag].count - 1;
			struct element e = PQ_tasks[tag].e[counter];
			struct timeval staT, endT;
		
			if (removeLast(&PQ_tasks[tag]) == -1)
				exit(0);
			
			if (Number_Time_Slice <= counter)
			{
			
				gettimeofday(&staT, NULL);
				t_sum_Res += (int) getDifferenceInMilliSeconds(e.created_time, staT);
			
			}

			if (e.pid_time <= TIME_SLICE)
			{

				runPreemptiveJobv2(&e);

				gettimeofday(&endT, NULL);  
				t_sum_TA += (int) getDifferenceInMilliSeconds(e.created_time, endT);

				Consumed_Counter++;

				if (sem_post(&empty[tag]) == -1)
					exit(0);

			} else 
				runPreemptiveJobv2(&e);
			
			if (e.pid_time > 0)			
				if (addFirst(&PQ_tasks[tag], &e) == -1)
					exit(0);

			printf("\nConsumer %d (for Priority %d) is running\nPID %d running\n", tag+1, tag, e.pid);		
			printf("# of Jobs produced %d\n# of Jobs consumed %d\n", Produced_Counter, Consumed_Counter);	

			Number_Time_Slice++;
		}

	if (Produced_Counter == MAX_NUMBER_OF_JOBS) return arg;

	} while (Consumed_Counter < MAX_NUMBER_OF_JOBS);

}

int InitTask()
{

	printf("Max Buffer for Each PQ: %d\nMax Number of Jobs for Each PQ: %d\n", MAX_BUFFER_SIZE, MAX_NUMBER_OF_JOBS);
	printf("Producer: 1  Consumer: %d\n", PRIORITY);

	for (int i = 0; i < PRIORITY; i++)
	{

        	if (init(&PQ_tasks[i], MAX_BUFFER_SIZE) == -1) 
			exit(0);

        	if (sem_init(&empty[i], 0, MAX_BUFFER_SIZE) == -1)
			exit(0);

    	}

    	if (sem_init(&full, 0, 0) == -1)
		exit(0);

	return 0;

}

int EndTask()
{

	for (int i = 0; i < PRIORITY; i++)
		if (sem_destroy(&empty[i]) == -1)
			exit(0);

	if (sem_destroy(&full) == -1)
		exit(0);

	for (int i = 0; i < PRIORITY; i++)
		freeAll(&PQ_tasks[i]);

	return 0;
}

int main()
{    

	InitTask();

	pthread_t PT_Producer, PT_Consumers[PRIORITY];

    	if (pthread_create(&PT_Producer, NULL, Producer_Demo, NULL) != 0)
        	printf( "Failed to create PT_Producer."); 
      
	for (int i = 0; i < PRIORITY; i++)   
        	if (pthread_create(&PT_Consumers[i], NULL, Consumer_Demo, &i) != 0 )
            		printf( "Failed to create PT_Consumers." ); 
    
    	if (pthread_join(PT_Producer , NULL) != 0)
        	printf( "Waiting PT_Producer."); 
    
    	for (int i = 0; i < PRIORITY; i++)
        	if (pthread_join(PT_Consumers[i], NULL) != 0)
            		printf( "Waiting PT_Consumers.");
   
	printf("\nAverage response time: %.2f milliseconds\nAverage turn around time: %.2f milliseconds\n", 
	       t_sum_Res/MAX_NUMBER_OF_JOBS, t_sum_TA/MAX_NUMBER_OF_JOBS);

	EndTask();
 
    	return 0;
}
