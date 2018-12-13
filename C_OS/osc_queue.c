#include "osc_queue.h"

int addFirst(struct queue *my_arr, struct element *new_e)
{

	if ((my_arr->e == NULL) 
		|| (my_arr->count == my_arr->max))
	{

        	printf("Something Wrong with the queue\n");
        	return -1;

    	} else {
	
		for (int i = my_arr->count - 1; i >= 0; i--)
			my_arr->e[i + 1] = my_arr->e[i];
	
    		my_arr->e[0] = *new_e;
    		my_arr->count++;
		
		return 0;   
	}

}

int addHere(struct queue *my_arr, struct element *new_e, int index)
{

	if ((my_arr->e == NULL)
		|| (my_arr->count == my_arr->max)
                || (index < 0) 
		|| (index >= my_arr->max))
	{

        	printf("Something Wrong with the queue\n");
       		return -1;

	} else {

        	for (int i = my_arr->count - 1; i >= index; i--)
           		my_arr->e[i + 1] = my_arr->e[i];

		my_arr->e[index] = *new_e;
		my_arr->count++;;
		return 0;

	}    

}


int addLast(struct queue *my_arr, struct element *new_e)
{

	if ((my_arr->e == NULL)
		|| (my_arr->count == my_arr->max))
	{

		printf("Something Wrong with the queue\n");
		return -1;

	}
	
	my_arr->e[my_arr->count] = *new_e;
	my_arr->count++;
	return 0;

}

void freeAll(struct queue *my_arr)
{
	
	free(my_arr->e);
	my_arr->max = 0;
	my_arr->count = 0;
	my_arr->e = NULL;

}

int getCount(struct queue *my_arr)
{

	if (my_arr->e == NULL)
	{

		printf("Not initialized\n");
		return -1;
	
	} else
	
		return my_arr->count;


}

int init(struct queue *my_arr, int arr_size)
{

	printf("Initialising ...\n");
	my_arr->e = (struct element *) calloc(1, sizeof(struct element) * arr_size);

	if (my_arr->e == NULL)
	{ 

		printf("Error in memory allocation\n");
		return -1;

	} else {

		printf("Init: successfully malloc element with size of %d ...\n", arr_size);

		my_arr->max = arr_size;
		my_arr->count = 0;

		return 0;

	} 

}

void printAll(struct queue *my_arr)
{

	printf("There are %d elements in total\n", my_arr->count);

	for (int i = 0; i < my_arr->max; i++)
		printf("#[%d]: %d running-time %d created-time %ld sec %d usec %d priority\n", 
			i, my_arr->e[i].pid, my_arr->e[i].pid_time, my_arr->e[i].created_time.tv_sec, my_arr->e[i].created_time.tv_usec, my_arr->e[i].pid_priority);
    	

}

int removeHere(struct queue *my_arr, int index)
{
	if ((my_arr->e == NULL)
		|| (index < 0 )
		|| (index >= my_arr->max)
		|| (index >= my_arr->count))
    	{
       		printf("The index is out of bound!\n");
        	return -1;
    	}
  
    	for (int i = index; i < my_arr->count; i++)
        	my_arr->e[i] = my_arr->e[i+1]; 
    
    	memset(my_arr->e + my_arr->count - 1, 0, sizeof(struct element));
    	my_arr->count--;

	return 0;  

}

int removeLast(struct queue *my_arr)
{

	if (my_arr->count == 0) 
	{

		printf("No element in this queue\n");
		return -1;

	} else {
	
		memset(my_arr->e + my_arr->count - 1, 0, sizeof(struct element));
		my_arr->count--;
	}

	return 0;

}
