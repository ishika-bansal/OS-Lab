/*
	2017UCP1566
	ISHIKA 
	B-3
	IMPLEMENTATION OF EISENBERG SOLUTION FOR N-PROCESS CRITICAL SECTION PROBLEM
*/
#include <iostream>
#include <thread>

using namespace std;
const int n = 10;

//defined the states for n processes
enum states { IDLE, WAITING, ACTIVE } flags[n];

//global declaration
int turn;

//checking the entry protocol for any process; it has to pass this to perform its critical section
//also so that no other process can enter while it is in the critical section
void entryProtocol(int i) {
	int index;
	do {
		flags[i] = WAITING;

		index = turn;
		while (index != i) {
			if (flags[index] != IDLE)
				index = turn;
			else
				index = (index + 1) % n;
		}

		flags[i] = ACTIVE;

		index = 0;
		while ((index < n) && ((index == i) || (flags[index] != ACTIVE)))
			index++;
	} while (!((index >= n) && ((turn == i) || (flags[turn] == IDLE))));

	turn = i;
}

//steps to be followed after implementation of Critical Section
//so that other processed can now enter the section one by one
void exitProtocol(int i) {
	int index = (turn + 1) % n;
	while (flags[index] == IDLE) {
		index = (index + 1) % n;
	}

	turn = index;
	flags[i] = IDLE;
}
 
//Procedure for the thread running
void run(int i) {
	entryProtocol(i);
	cout << "thread " << i << " is running\n";
	exitProtocol(i);
}

int main() {
	//cout<<"Enter the velue of n"<<endl;
	//cin>>n;
	turn = 0;
	for (int index = 0; index < n; index++) {
		flags[index] = IDLE;
	}

	thread ts[n];
	for (int i = 0; i < n; i++) {
		ts[i] = thread(run, i);
	}
	for (int i = 0; i < n; i++) {
		ts[i].join();
	}

	return 0;
}
