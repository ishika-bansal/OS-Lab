Implement Multiple Producer - Multiple Consumer problem using Semaphores
SHWETA SAHARAN
•
Jan 25
100 points
Class comments
Your work
Turned in

2017UCP1566_MCMP.c
C
Private comments
Implement Multiple Producer - Multiple Consumer problem using Semaphores 
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> 
#include<semaphore.h>
#include<unistd.h>

//putting maximum consumer and producer constraint
#define MAX_CONSUMERS 200
#define MAX_PRODUCERS 200

sem_t nEmpty;
sem_t nFull; 
sem_t S; //Resource mutex

int size = 0; // items in the buffer
int n = 5; //maximum size of the buffer 

//wait function
void randwait(int secs){
	sleep(secs);
}

//producer function
void *producer(void *number){
	int num = *(int*) number;
	sem_wait(&nEmpty); //as one empty slot will be less now
	sem_wait(&S); //locking the resource mutex
	printf("I am a producer with prod ID : %d\n", num); //printing the identity
	size++; //accessing the shared variable
	printf("Size of the shared buffer is : %d\n",size); //printing the value of the shared buffer size
	randwait(1); //wait
	sem_post(&S);//unlocking the resource mutex
	sem_post(&nFull); //as one full slot will be increased now
}

//consumer function
void *consumer(void *number){
	int num = *(int *) number;
	sem_wait(&nFull); //as one full slot will be less now
	sem_wait(&S); //locking the resource mutex
	printf("I am a consumer with consumer ID : %d\n", num); //printing the thread identity
	size--; //accessing the shared variable
	printf("Size of the shared buffer is : %d\n",size); //printing the value of the shared buffer size
	randwait(1); //wait
	sem_post(&S); //unlocking the resource mutex
	sem_post(&nEmpty); //as one slot has been consumed
}

int main(int argc, char *argv[]){
	
	int i, x, numConsumers, numProducers;
	//inputting number of consumers and producers
	printf("Enter the number of Consumers and Producers -- Maximum Number of Consumers and Producers are 200 \n");
	scanf("%d", &x);
	numConsumers = x;
	scanf("%d", &x);
	numProducers = x;
	//check
	if(numConsumers>MAX_CONSUMERS || numProducers>MAX_PRODUCERS){
		printf("The number entered for either Consumers or Producers is higher than maximum limit.\nExiting!");
		return 0;
	}
	
	//Create an array of threads to perform concurrently
	pthread_t custid[numConsumers];
	pthread_t prodid[numProducers];
	
	int Cust_Number[numConsumers];
	int Prod_Number[numProducers];
	
	//initialising the IDs for consumers
	for(i=0;i<numConsumers;i++){
		Cust_Number[i] = i;
	}
	
	//initialising the IDs for producers
	for(i=0;i<numProducers;i++){
		Prod_Number[i] = i;
	}
	
	printf("********************************************************************************************\n");
	printf("SOLUTION USING SEMAPHORES: \n");
	printf("Initial size of the shared buffer is : %d\n", size);
	printf("********************************************************************************************\n");
	
	printf("*****************PRINTING THREAD INFORMATION****************************\n");
	//initialising the semaphore
	sem_init(&nEmpty, 0, n); //initially all slots are empty
	sem_init(&nFull, 0, 0); //initially no slot is full
	sem_init(&S, 0, 1); //initially the resource is unlocked
	
	//launching the consumer threads
	for(i=0;i<numConsumers;i++){
		pthread_create(&custid[i], NULL, consumer, (void *)&Cust_Number[i]);
	}
	
	//launching the producer threads
	for(i=0;i<numProducers;i++){
		pthread_create(&prodid[i], NULL, producer, (void *)&Prod_Number[i]);
	}
	
	//joining the consumer threads
	for(i=0;i<numConsumers; i++){
		pthread_join(custid[i], NULL);
	}
	
	//joining the producer threads
	for(i=0;i<numProducers;i++){
		pthread_join(prodid[i], NULL);
	}		
	printf("******************FINAL BUFFER ITEMS SIZE : %d ******************************\n", size);
	return 0;
	
}
