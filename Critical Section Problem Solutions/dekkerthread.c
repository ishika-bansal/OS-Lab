


// gcc -pthread <name.c>
// This program creates two threads, each thread 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 

int	x = 0;		// Shared variable
#define	THREAD1		0
#define	THREAD2		1

#define	TRUE		1
#define FALSE		0
  
int p1_wantstoenter;
int p2_wantstoenter;
int favouredProcess;
void Initialization(void) { 
	p1_wantstoenter=0;
	p2_wantstoenter=0;
	favouredProcess=1;
	srand(time(NULL));
} 

void	*func1(void *s) { 
	int	i, k;
	for (i=0; i < 5; i++)  {
		p1_wantstoenter=1;
		while(p2_wantstoenter) 
		{
			if(favouredProcess==2)
			{
				p1_wantstoenter=0;
				while(favouredProcess==2)
					;
				p1_wantstoenter=1;
			}
		}
		// Critical Section - shared variable is incremented
		x = x+1;
		printf("[%2d] :  Thread 1 in Critical Section (%d).\n", i+1,x);
		favouredProcess=2;
		p1_wantstoenter=0;

		// Random delay added
		k = (int) ((3.0*rand())/RAND_MAX);
		sleep(k);
	}
} 
  
  
void	*func2(void *s) { 
	int	i, k;
	for (i=0; i < 5; i++)  {
		p2_wantstoenter=1;
		while(p1_wantstoenter) 
		{
			if(favouredProcess==1)
			{
				p2_wantstoenter=0;
				while(favouredProcess==1)
					;
				p2_wantstoenter=1;
			}
		}
		// Critical Section - shared variable is incremented
		x = x+1;
		printf("[%2d] :  Thread 2 in Critical Section (%d).\n", i+1,x);
		favouredProcess=1;
		p2_wantstoenter=0;
		// Random delay added
		k = (int) ((5.0*rand())/RAND_MAX);
		sleep(k);
	}
} 
  

int main() { 
    	pthread_t 	Thread1, Thread2; 
    	// Initialized the lock then fork 2 threads 
	Initialization();
  
    	// Create two threads (both run func)  
    	pthread_create(&Thread1, NULL, func1, (void *) THREAD1); 
    	pthread_create(&Thread2, NULL, func2, (void *) THREAD2); 
  
	// Wait for the threads to end. 
    	pthread_join(Thread1, NULL); 
    	pthread_join(Thread2, NULL); 
  
    	return 0; 
} 
