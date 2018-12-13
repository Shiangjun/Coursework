#include "coursework.h"
#define MAX_PROCESSES 5

struct queue tasks;
float t_sum_Res = 0, t_sum_TA = 0;

void generateSJF()
{

	if (init(&tasks, MAX_PROCESSES) == -1)
		exit(0);

	printAll(&tasks);

	printf("Generating processes for SJF ...\n");

	struct element e = generateProcess();

	if (addFirst(&tasks, &e) == -1)
		exit(0);

	printf("SJF: add first\n");

	for (int i = 1; i < MAX_PROCESSES; i++)
	{

		printAll(&tasks);
		
		e = generateProcess();
		int index;

		if (e.pid_time > tasks.e[0].pid_time)
			printf("SJF: add new largest\n");

		for (index = 0; 
			index < tasks.count 
			&& e.pid_time < tasks.e[index].pid_time; 
			index++);	
		
		if (addHere(&tasks, &e, index) == -1) 
			exit(0);

       	}
	
	printAll(&tasks);
    	
}

void runSJF()
{

	printf("Running the processes using SJF ...\n");
	struct timeval staT, endT;
	
	for (int i = 0; i < MAX_PROCESSES; i++)
	{

		int index = tasks.count - 1;
		
		gettimeofday(&staT, NULL);
		runNonPreemptiveJob(&tasks, tasks.count-1);
		gettimeofday(&endT, NULL);
		
		int t_Res = (int) getDifferenceInMilliSeconds(tasks.e[index].created_time, staT);
		t_sum_Res += t_Res;

		int t_TA = (int) getDifferenceInMilliSeconds(tasks.e[index].created_time, endT);
		t_sum_TA += t_TA;

		if (removeLast(&tasks) == -1)
			exit(0);
		
		printf("C: %ld S: %ld E: %ld R:%d T:%d\n", 
			tasks.e[index].created_time.tv_sec, staT.tv_sec, endT.tv_sec, t_Res, t_TA);

    	}

}

int main()
{

	generateSJF();
	runSJF();	

	printf("Average response time: %.2f milliseconds\nAverage turn around time: %.2f milliseconds\n", 
		t_sum_Res/MAX_PROCESSES, t_sum_TA/MAX_PROCESSES);

	freeAll(&tasks);

	return 0;

}
