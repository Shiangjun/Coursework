#include "coursework.h"
#define MAX_PROCESSES 5

struct queue PQ_tasks[PRIORITY];
float t_sum_Res = 0, t_sum_TA = 0; 


void generatePQ()
{
	
	for (int tag = 0; tag < PRIORITY; tag++)
	{
	
		init(&PQ_tasks[tag], MAX_PROCESSES);
		
		printf("Q #%d\n", tag);
		printAll(&PQ_tasks[tag]);
	
	}
		
	printf("Generating processes for PQ ...\n");
	
	for (int index = 0; index < MAX_PROCESSES; index++)
	{
		struct element e = generateProcess();

		printf("New process has priority %d\n", e.pid_priority);
		printf("PQ %d: add now\n", e.pid_priority);

		if (addFirst(&PQ_tasks[e.pid_priority], &e) == -1) 
			exit(0);

		for (int tag = 0; tag < PRIORITY; tag++)
		{
			printf("#%d\n",tag);
			printAll(&PQ_tasks[tag]);
		}

	}

}

void runPQ()
{

	for (int tag = 0; tag < PRIORITY; tag++)
	{
		int Number_Time_Slice = 0;

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
				printf("Q:  %d P:  %d C:  %d S:  %d R:  %d\n", 
					tag, e.pid, e.created_time.tv_sec, staT.tv_sec, getDifferenceInMilliSeconds(e.created_time, staT));

				t_sum_Res += getDifferenceInMilliSeconds(e.created_time, staT);
			
			}

			if (e.pid_time <= TIME_SLICE)
			{

				runPreemptiveJobv2(&e);

				gettimeofday(&endT, NULL);  
				printf("Q:  %d P:  %d C:  %d E:  %d T:  %d\n", 
					tag, e.pid, e.created_time.tv_sec, endT.tv_sec, getDifferenceInMilliSeconds(e.created_time, endT));

				t_sum_TA += getDifferenceInMilliSeconds(e.created_time, endT);
			
			} else 
				runPreemptiveJobv2(&e);

			if (e.pid_time > 0)
				addFirst(&PQ_tasks[tag], &e);

			Number_Time_Slice++;

		}
	}

}

int main()
{

	generatePQ();

	printf("Running the processes using PQ ...\n");

	runPQ();

	printf("Average response time: %.2f milliseconds\nAverage turn around time: %.2f milliseconds\n", 
		t_sum_Res/MAX_PROCESSES, t_sum_TA/MAX_PROCESSES);

	for (int tag = 0; tag < PRIORITY; tag++)
		freeAll(&PQ_tasks[tag]);

	return 0;

}
