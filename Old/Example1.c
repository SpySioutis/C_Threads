#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <unistd.h>


sem_t st1, st2, st3, st4;


void *thread_1(void *msg1);
void *thread_2(void *msg2);
void *thread_3(void *msg3);
void *thread_4(void *msg4);



int main(int argc, char *argv[])
{
	pthread_t tid1, tid2, tid3, tid4;
	sem_init(&st1, 0, 1);
	sem_init(&st2, 0, 1);
	sem_init(&st3, 0, 1);
	sem_init(&st4, 0, 1);
	char *m1="Hello ", *m2="there ", *m3="wonderful ", *m4="world!\n";
	sem_wait(&st2);
	sem_wait(&st3);
	sem_wait(&st4);
	pthread_create(&tid1, NULL, thread_1, (void *)m1);
	pthread_create(&tid2, NULL, thread_2, (void *)m2);
	pthread_create(&tid3, NULL, thread_3, (void *)m3);
	pthread_create(&tid4, NULL, thread_4, (void *)m4);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	return 0;
}


void *thread_1(void *msg1)
{
	char *ms1=(char *)msg1;
	for(;;)
	{
		sem_wait(&st1);
		printf("%s", ms1);
//		sleep(1);
		sem_post(&st2);
	}
	pthread_exit(0);
}

void *thread_2(void *msg2)
{
	char *ms2=(char *)msg2;
	for(;;)
	{
		sem_wait(&st2);
		printf("%s", ms2);
//		sleep(1);
		sem_post(&st3);
	}
	pthread_exit(0);
}


void *thread_3(void *msg3)
{
	char *ms3=(char *)msg3;
	for(;;)
	{
		sem_wait(&st3);
		printf("%s", ms3);
//		sleep(1);
		sem_post(&st4);
	}
	pthread_exit(0);
}


void *thread_4(void *msg4)
{
	char *ms4=(char *)msg4;
	for(;;)
	{
		sem_wait(&st4);
		printf("%s", ms4);
//		sleep(1);
		sem_post(&st1);
	}
	pthread_exit(0);
}


