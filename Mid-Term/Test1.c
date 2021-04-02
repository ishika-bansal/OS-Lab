/*
  ISHIKA
  2017UCP1566
  B-3
  IMPLEMENTATION OF N PROCESSES-SHAREABLE RESOURCE!!
  //THREAD IDS DISPLAYED AS PROCESS NUMBER
  EXAMPLE CASE : N=3
*/
#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>
#define m 13 //defines maximum threads
int n=0;
sem_t lock; //locks the resource
sem_t waits; //locks the waiting processes
sem_t access1; //controls access to any entering 
//global declarations
int process_entering = 0;
int process_leaving = 0 ;
int process_in_execution =0;

int round1 =0;
void *procedure(void* number){
	long num = pthread_self()%1000;
     	sem_wait(&waits);
     	printf("--- Process %ld entered waiting room. --- \n", num); 
     	// Wait for the resource to become free.
	if((process_in_execution)==0&&round1!=0){
     	sem_wait(&access1); 
	}
	else if((process_in_execution)==0&&round1!=0){
     	sem_post(&access1); 
	}
	sem_wait(&lock);
     	sem_post(&waits); //leaves the waiting place
	// Wake up the resource...
	//sleep(1);
	process_entering +=1;
	process_in_execution +=1;
	printf("--- Process %ld using the resource. --- \n", num);
	sleep(2);//random wait indicating the time process holds the resource
	printf("--- Process %ld left the resource. --- \n", num);
	process_leaving +=1;
	//process_left +=1;
	process_in_execution -=1;
	round1++;
     	sem_post(&lock);
}
int main(){
	printf("Enter the value of n");
	scanf("%d", &n);
	//int x = m-n;

	sem_init(&lock,0,n);
	sem_init(&waits,0,m);
	sem_init(&access1,0,1);
	pthread_t proc[m];
	//initialising m process threads	
	for(int i=0;i<m;i++){
		//printf("Sending thread value : %d \n",i);
		pthread_create(&proc[i], NULL, procedure,(void *)&i);
	}
	//joining all the threads together
	for(int i=0;i<m;i++){
		pthread_join(proc[i],NULL);	
	}
	printf("***COMPLETED SUCCESSFULLY***");
	return 0;
}
	
	 
	
