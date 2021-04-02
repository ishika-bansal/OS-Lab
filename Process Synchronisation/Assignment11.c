/*
  ISHIKA
  2017UCP1566
  B-3
  IMPLEMENTATION OF INSERTER, DELETER AND SEARCHER!!!
  TEST CASE : i=7, s=5, d=8
*/
#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};

struct node *head = NULL;
struct node *tail = NULL; 

sem_t search; //locks the search process
sem_t delete; //locks the delete process by search
sem_t insert; //locks the insert process
sem_t delete1; //locks the delete process by insert

//global declarations
int search_count = 0;
int in=0;
int s=0;
int d=0;

//search thread procedure
void *sea(void* number){
	long num = pthread_self()%1000;
	//printf("SEARCH TRYING \n");
	sem_wait(&search);
	search_count++;
	if(search_count==1)
		sem_wait(&delete);
	sem_post(&search);
	/* CRITICAL SECTION */
	printf("--- A searcher with process ID : %ld is entering --- \n",num);
	int x = rand()%100;
	struct node* t = head;
	int f =0;
	printf("Searching for number %d in the linked list by process ID : %ld\n",x,num);
	while(t!=NULL){
		if(t->data==x){
			printf("Data found in the linked list at the index %d by process ID : %ld\n",x,num);
			f = 1;			
			break;
		}
		t=t->next;
	}
	if(f==0)
		printf("Data %d is not present in the linked list by process ID : %ld\n",x,num);
	printf("--- A searcher with process ID : %ld is leaving --- \n",num);
	sem_wait(&search);
	search_count--;
	if(search_count==0)
		sem_post(&delete);
	//printf("--- Bye, I am a searcher with process ID : %ld finally ending--- \n",num);
	sem_post(&search);
	//sleep(3);
}

//insertion thread procedure
void *ins(void* number){
	long num = pthread_self()%1000;
	//printf("INSERTION TRYING \n");	
	sem_wait(&insert);
	sem_wait(&delete1);     	
	/* CRITICAL SECTION */
	printf("--- An inserter with process ID : %ld is entering --- \n",num);
	int x = rand()%100;
	printf("Inserting random number %d at the end of the linked list\n",x);
	struct node *temp = (struct node*) malloc(sizeof(struct node));	
	temp->data = x;
	temp->next = NULL;
	if(tail!=NULL){
		tail->next=temp;
		tail=temp;
	}	
	//inserting the first element	
	if(head==NULL){
		head=temp;
		tail=temp;
	}
	printf("UPDATED LINKED LIST \n");
	struct node* f = (struct node*) malloc(sizeof(struct node));
	f = head;
	printf("%d",f->data);
	while(f->next!=NULL){
		printf(" -> %d",f->next->data);	
		f = f->next;	
	}
	printf("\n");
	//sleep(3);
	printf("--- An inserter with process ID : %ld is leaving --- \n",num);
     	sem_post(&delete1);
	sem_post(&insert);
}

//deletion thread procedure
void *del(void* number){
	long num = pthread_self()%1000;
	sem_wait(&delete);
	sem_wait(&delete1);
	/* CRITICAL SECTION */
	printf("--- A deleter with process ID : %ld is entering --- \n",num);
	//sleep(3);
	int k = 0;
	struct node* g = (struct node*) malloc(sizeof(struct node));
	g = head;

	//if linked list is not empty
	if(head!=NULL){

		//counting the number of nodes in the linked list
		while(g->next!=NULL){	
			g = g->next;
			k++;	
		}
		k++;
		printf("TOTAL NUMBER OF NODES IS : %d\n",k);

		//randomly generated index to be deleted
		int y = rand()%k;
		printf("%d index is being deleted\n",y);	
		g=head;
		printf("HEAD DATA IS : %d\n",g->data);

		//if head has to be deleted and moved to the next node
		if(y==0&&k!=1){
			struct node* temp = head->next->next;
			head = head->next;
			head->next = temp;
		}

		//if only 1 element was there : linked list will be emptied
		else if(k==1){
			head = NULL;
			tail = NULL;
		}

		//if some other node than head is to be deleted
		else{
			for(int i=0;g!=NULL&&i<y-1;i++)
				g=g->next;
			printf("Data to be deleted is : %d\n",g->next->data);
			struct node* d1 = g->next->next;
			//if last element is deleted, update the tail pointer as well			
			if(d1==NULL){
				tail=g;
			}
			//OR
			/*if(k-1==y){
				tail=g;
			}*/
			free(g->next);
			g->next=d1;
		}
	}
	printf("UPDATED LINKED LIST \n");
	//if linked list is not empty
	if(head!=NULL){
		struct node* f = head;
		printf("%d",f->data);
		while(f->next!=NULL){
			printf(" -> %d",f->next->data);	
			f = f->next;	
		}
		printf("\n");
	}
	//empty linked list
	else{
		printf("NULL \n");
	}
	printf("--- A deleter with process ID : %ld is leaving --- \n",num);
     	sem_post(&delete1);
	sem_post(&delete);
}
int main(){
	printf("Enter the number of inserters, searchers and deleters\n");
	scanf("%d %d %d", &in,&s,&d);

	//initialise binary semaphores
	sem_init(&search,0,1);
	sem_init(&delete,0,1);
	sem_init(&insert,0,1);
	sem_init(&delete1,0,1);

	//declare thread arrays for inserters, deleters and searchers
	pthread_t insert[in];
	pthread_t delete[d];
	pthread_t search[s];

	//initialising m process threads	
	for(int i=0;i<in;i++){
		//printf("Sending thread value : %d \n",i);
		pthread_create(&insert[i], NULL, ins,(void *)&i);
	}

	for(int i=0;i<d;i++){
		//printf("Sending thread value : %d \n",i);
		pthread_create(&delete[i], NULL, del,(void *)&i);
	}

	for(int i=0;i<s;i++){
		//printf("Sending thread value : %d \n",i);
		pthread_create(&search[i], NULL, sea,(void *)&i);
	}

	//joining all the threads together
	for(int i=0;i<in;i++){
		pthread_join(insert[i],NULL);	
	}
	for(int i=0;i<d;i++){
		pthread_join(delete[i],NULL);	
	}
	for(int i=0;i<s;i++){
		pthread_join(search[i],NULL);	
	}

	//Complete 	
	printf("\n***COMPLETED SUCCESSFULLY***\n");
	return 0;
} 
