/*ISHIKA
B-3
2017UCP1566

FOR COMPILING : gcc -pthread 2017UCP1566.c
FOR EXECUTING : ./a.out

*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

//defining node structure
struct node
{
	int data;
	struct node* next;
};

//global declarations

struct node *head = NULL;

int favouredProcess = 1;
int P1WantsToEnter = 0;
int P2WantsToEnter = 0;


void printLinkedList(){
	printf("UPDATED LINKED LIST \n");
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
}


//calling it Process-1
//insertion Process

void *insertion(void *data){
	long num = pthread_self()%1000;
	
	P1WantsToEnter = 1;
	favouredProcess = 2;
	while(P2WantsToEnter && favouredProcess==2)
		;
	//do the insertion work
	printf("--- An inserter with process ID : %ld is entering --- \n",num);
	//printf("Inserting random number %d at the end of the linked list\n",value);
	int value = rand()%100;	
	struct node *temp = (struct node*) malloc(sizeof(struct node));	
	temp->data = value;
	temp->next = NULL;
	
	//inserting the first element	
	if(head==NULL){
		head=temp;
	}
	else{
		struct node *n = (struct node*) malloc(sizeof(struct node));
		while(n->next!=NULL)
		{
			n= n->next;		
		}
		n->next = temp;
	}
	//critical section ends here
	printLinkedList();
	P1WantsToEnter = 0;
}

//calling it process-2
//Deletion Process
void *deletion(){
	long num = pthread_self()%1000;
	P2WantsToEnter = 1;
	favouredProcess = 1;
	while(P1WantsToEnter && favouredProcess==1)
		;
	//do the deletion work
	/* CRITICAL SECTION */
	printf("--- A deleter with process ID : %ld is entering --- \n",num);
	int k = 0;//size of the linkedlist
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
		if(y==0 && k!=1){
			struct node* temp = head->next->next;
			head = head->next;
			head->next = temp;
		}

		//if only 1 element was there : linked list will be emptied
		else if(k==1){
			head = NULL;
		}

		//if some other node than head is to be deleted
		else{
			for(int i=0;g!=NULL&&i<y-1;i++)
				g=g->next;
			printf("Data to be deleted is : %d\n",g->next->data);
			struct node* d1 = g->next->next;
			free(g->next);
			g->next=d1;
		}
		printLinkedList();
	}
	else{
		printf("Nothing to delete\n");
		printLinkedList();
	}
	P2WantsToEnter = 0;
}

int main(){
	//declare threads for inserters and deleters
	pthread_t insert;
	pthread_t delete;
	int i = rand()%100;	
	
	
	pthread_create(&insert, NULL, insertion,(void *)&i);
	i = rand()%100;	
	pthread_create(&delete, NULL, deletion, (void *)&i);
	
	//joining all the threads together
	pthread_join(insert, NULL);
	pthread_join(delete, NULL);

	//Complete 	
	printf("\n***COMPLETED SUCCESSFULLY***\n");
	return 0;
} 
