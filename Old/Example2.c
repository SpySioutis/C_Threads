#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <unistd.h>
sem_t writer_lock;
sem_t reader_lock;


void read_user(void)
{
	while(1) 
	{
		sem_wait(&reader_lock);
		/* simulate read operation by a delay*/
		printf("in reader task \n");
		sleep(2);
		sem_post(&writer_lock);
	}
}


void write_user(void)
{
	while(1) 
	{
		sem_wait(&writer_lock);
		/* simulate read operation by a delay*/
		printf("in writer task \n");
		sleep(2);
		sem_post(&reader_lock);
	}
}


void main()
{
	pthread_t read_thread;
	pthread_attr_t attribute;
	sem_init(&writer_lock,0,1);
	sem_init(&reader_lock,0,1);
	sem_wait(&reader_lock);
	pthread_attr_init(&attribute);
	pthread_create(&read_thread,&attribute,(void*)&read_user,NULL);
	write_user();
}
