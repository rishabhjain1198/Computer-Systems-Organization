#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>

struct arg_struct {

	int arg1;
	int arg2;
};

void *thread(void *vargp);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Wrong number of arguments \n");
		exit(1);
	}
	
	int nthreads = atoi(argv[1]);

	if(!(nthreads > 0))
	{
		printf("Argument not correct \n");
		exit(1);
	}

	if(nthreads == 0)
	{
		printf("Thread 0 done\n");
		exit(0);
	}

	pthread_t tid1, tid2;
	//tid = malloc(nthreads * sizeof(pthread_t));
	struct arg_struct args1;
	args1.arg1 = nthreads;
	args1.arg2 = 1;
	pthread_create(&tid1, NULL, thread, (void *)&args1);

	struct arg_struct args2;
	args2.arg1 = nthreads;
	args2.arg2 = 2;
	pthread_create(&tid2, NULL, thread, (void *)&args2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("Thread 0 done\n");
	//free(tid);
	exit(0);
}

void *thread(void *vargp) /* Thread routine */
{
	struct arg_struct* thiargs = vargp;
	
	int thisone = thiargs -> arg2;	

	if(thisone > ((thiargs -> arg1) / 2))
	{
		printf("Thread %d done\n", thisone);
		return NULL;
	}

	pthread_t tidx, tidy;

	struct arg_struct child1;
	child1.arg1 = thiargs -> arg1;
	child1.arg2 = (thisone*2) + 1;
	pthread_create(&tidx, NULL, thread, (void *)&child1);	

	struct arg_struct child2;
	child2.arg1 = thiargs -> arg1;
	child2.arg2 = (thisone*2) + 2;
	pthread_create(&tidy, NULL, thread, (void *)&child2);

	pthread_join(tidx, NULL);
	pthread_join(tidy, NULL);

	printf("Thread %d done\n", thisone);
	return NULL;
}
