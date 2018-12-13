#include "coursework.h"
#define MAX_PROCESSES 5

struct queue tasks;

int main()
{

	if (init(&tasks, MAX_PROCESSES) == -1) 
		exit(0);

	printAll(&tasks);
	
	printf("Performing FIFO ... \n");

	for (int i = 0; i < MAX_PROCESSES; i++)
	{

		struct element e = generateProcess();

        	if (addFirst(&tasks, &e) == -1) 
			exit(0);

        	printf("Add: pid %d into the queue with time %d\n", e.pid, e.pid_time);

    	}
    	printAll(&tasks);

    	for (int i = 0; i < MAX_PROCESSES; i++)
	{

		printf("Remove: %d from the queue index %d\n", tasks.e[tasks.count-1].pid, tasks.count-1);

		if (removeLast(&tasks) == -1)
			exit(0);

		printAll(&tasks);

    	}

	printf("Performing LIFO ...\n");

	for (int i = 0; i < MAX_PROCESSES; i++)
	{

		struct element e = generateProcess();

		if (addLast(&tasks, &e) == -1) 
			exit(0);

		printf("Add: pid %d into the queue with time %d\n", e.pid, e.pid_time);

	}

	printAll(&tasks);

	for (int i = 0; i < MAX_PROCESSES; i++)
	{

		printf("Remove: %d from the queue index %d\n", tasks.e[tasks.count-1].pid, tasks.count-1);

		if (removeLast(&tasks) == -1)
			exit(0);

		printAll(&tasks);

	}

	freeAll(&tasks);

	return 0;
}
