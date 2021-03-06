/*
QN: 4 B
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

const int NUM_CPU_STATES = 10;

enum CPUStates
{
	S_USER = 0,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

typedef struct CPUData
{
	std::string cpu;
	size_t times[NUM_CPU_STATES];
} CPUData;

void ReadStatsCPU(std::vector<CPUData> & entries);

size_t GetIdleTime(const CPUData & e);
size_t GetActiveTime(const CPUData & e);

void PrintStats(const std::vector<CPUData> & entries1, const std::vector<CPUData> & entries2);
//To get available memory 
unsigned long long getTotalSystemMemory()
{
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_Size = sysconf(_SC_PAGE_SIZE);
	return pages*page_Size;
}

//To display swap size 
/*void swap()
{
	string str="free";
	const char *command = str.c_str[];
	cout<<"Compiling file using"<<command<<endl;
	system[command];
	

}*/

void swap(){
	string getinputcontent,word;
	ifstream in2;
    	in2.open("/proc/swaps",ios::binary);
    
    	cout<<"Swaps : "; 
    	while(in2>>word){
		cout<<word<<" ";
	if(word=="Priority")
		cout<<"\n";
    	}
}

void avgtime(){
	string getinputcontent,word;
	ifstream in2;
    	in2.open("/proc/loadavg",ios::binary);
    
    	cout<<"\n \nThe average load on the system in 1,5,15 minutes : "; 
    	while(in2>>word){
		cout<<word<<" ";
	
    	}

}

void contextswitch(){
	string getinputcontent,word;
	ifstream in2;
    	in2.open("/proc/stat",ios::binary);
    
    	cout<<"\n \nNo. of context switches : "; 
    	while(in2>>word){
	if(word=="ctxt"){		
		in2>>word;
		cout<<word<<endl;
    	}
	}
}
void interrupt(){
	string getinputcontent,word;
	ifstream in2;
    	in2.open("/proc/stat",ios::binary);
    
    	cout<<"\n \nNo. of interrupts : "; 
    	while(in2>>word){
	if(word=="intr"){		
		in2>>word;
		cout<<word<<endl;
    	}
	}
}
//THe rate of disk read/write in the system is given by iostat command
//The iostat command uses the /proc/diskstats 
void diskstat(){
	string getinputcontent,word;
	ifstream in2;
    	in2.open("/proc/diskstats",ios::binary);
    	//Read 
    	cout<<"\n \n "; 
    	while(in2>>word){
	if(word=="loop3"){		
		in2>>word;
		in2>>word;	
		in2>>word;
		cout<<"Total no. of sectors that normally reads from loop3: " <<word<<endl;
		in2>>word;
		cout<<"Total no. of sectors that normally writes from loop3: " <<word<<endl;
    	}
	}
}
void rate(){
	/*string getinputcontent,word;
	ifstream in2;
    	in2.open("/proc/diskstats",ios::binary);*/
	system("vmstat >>output.txt");
	string getinputcontent,word;
	ifstream in2;
    	in2.open("output.txt",ios::binary);
    	//Read 
    	cout<<"The no. of context switches in the kernel is stored in the output.txt"<<endl;
	system("sar -w -C -q 1 1");
	
	

}
int main(int argc, char * argv[]){
	
	std::vector<CPUData> entries1;
	std::vector<CPUData> entries2;

	// snapshot 1
	ReadStatsCPU(entries1);

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// snapshot 2
	ReadStatsCPU(entries2);

	// print output
	PrintStats(entries1, entries2);

	
	int x = getTotalSystemMemory();
	printf("The amount of free memory %d \n",x);
 	swap();
	avgtime();
	contextswitch();
	interrupt();
	diskstat();
	rate();
	

}
void ReadStatsCPU(std::vector<CPUData> & entries)
{
	std::ifstream fileStat("/proc/stat");

	std::string line;

	const std::string STR_CPU("cpu");
	const std::size_t LEN_STR_CPU = STR_CPU.size();
	const std::string STR_TOT("tot");

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
		if(!line.compare(0, LEN_STR_CPU, STR_CPU))
		{
			std::istringstream ss(line);

			// store entry
			entries.emplace_back(CPUData());
			CPUData & entry = entries.back();

			// read cpu label
			ss >> entry.cpu;

			// remove "cpu" from the label when it's a processor number
			if(entry.cpu.size() > LEN_STR_CPU)
				entry.cpu.erase(0, LEN_STR_CPU);
			// replace "cpu" with "tot" when it's total values
			else
				entry.cpu = STR_TOT;

			// read times
			for(int i = 0; i < NUM_CPU_STATES; ++i)
				ss >> entry.times[i];
		}
	}
}

size_t GetIdleTime(const CPUData & e)
{
	return	e.times[S_IDLE] + 
			e.times[S_IOWAIT];
}

size_t GetActiveTime(const CPUData & e)
{
	return	e.times[S_USER] +
			e.times[S_NICE] +
			e.times[S_SYSTEM] +
			e.times[S_IRQ] +
			e.times[S_SOFTIRQ] +
			e.times[S_STEAL] +
			e.times[S_GUEST] +
			e.times[S_GUEST_NICE];
}

void PrintStats(const std::vector<CPUData> & entries1, const std::vector<CPUData> & entries2)
{
	const size_t NUM_ENTRIES = entries1.size();

	for(size_t i = 0; i < NUM_ENTRIES; ++i)
	{
		const CPUData & e1 = entries1[i];
		const CPUData & e2 = entries2[i];

		std::cout.width(3);
		std::cout << e1.cpu << "] ";

		const float ACTIVE_TIME	= static_cast<float>(GetActiveTime(e2) - GetActiveTime(e1));
		const float IDLE_TIME	= static_cast<float>(GetIdleTime(e2) - GetIdleTime(e1));
		const float TOTAL_TIME	= ACTIVE_TIME + IDLE_TIME;

		std::cout << "active: ";
		std::cout.setf(std::ios::fixed, std::ios::floatfield);
		std::cout.width(6);
		std::cout.precision(2);
		std::cout << (100.f * ACTIVE_TIME / TOTAL_TIME) << "%";

		std::cout << " - idle: ";
		std::cout.setf(std::ios::fixed, std::ios::floatfield);
		std::cout.width(6);
		std::cout.precision(2);
		std::cout << (100.f * IDLE_TIME / TOTAL_TIME) << "%" << std::endl;
	}
}

