/*
  ISHIKA
  2017UCP1566
  B-3
*/
#include<iostream>
#include <bits/stdc++.h>
#include<string.h>
#include<unordered_set>
using namespace std;

class info{
public:
    int time_entry;
    int space_required;
    int duration;	
    int running;
    int first_exec;
    int complete;
};

class pairr{
public:
    int start;
    int end;
    int size;
    int flag;
    int pid;
};

//global declaration
int timer = 0;
int proc_num=0;

void WORST_FIT(info a[],int n, int m){
	vector <int> fail;
	vector <int> success;
	int f = 0;
	//cout<<"VALUE OF N : "<<n<<endl;
	cout<<"TOTAL MEMORY SIZE IS : "<<m<<endl;
	cout<<"WORST FIT ALGORITHM"<<endl;
	//unordered_map<pairr,int, MyHashFunction> blocks;
	vector<pairr>p;
	pairr u = {0,m-1,m,0};
	p.push_back(u);
	for(int i=0;i<n;i++){
	     a[i].running=0;
	     a[i].first_exec=0;
	     a[i].complete==0;
	     cout<<a[i].time_entry<<"         "<<a[i].space_required<<"            "<<a[i].duration<<endl;	
	}
	cout<<"*********************************************************************************************************************************"<<endl;
	int last = 0;
	int memory_available=m;
	int faill=0;
	while(1){
	    //cout<<"MEMORY TOTAL RIGHT NOW : "<<memory_available<<endl;
	    f=0;
	    //decrementing the duration counter for each process
	    for(int i=0;i<n;i++){
		if(a[i].running&&!a[i].complete){
			a[i].duration--;
			//cout<<"Decremented duration of "<<i<<" process to "<<a[i].duration<<endl;
			if(a[i].duration==0){
				a[i].running=0;
				a[i].complete=1;
				for(int j=0;j<p.size();j++){
					if(p[j].pid==i+1){
						//cout<<"PROCESS "<<p[j].pid<<" IS COMPLETED AT TIME "<<timer<<endl;
						//cout<<memory_available<<" AVAILABLE MEMORY"<<endl;
						memory_available +=a[i].space_required;					
						p[j].flag=0;
						p[j].pid=-1;
					}
				}
			}
		}
	    }
	    //checking if two memory blocks are consecutively free
	    for(int j=0;j<p.size()-1;j++){
		if(p[j].flag==0&&p[j+1].flag==0){
			p[j+1].start=p[j].start;
			p[j+1].size += p[j].size;
			p[j+1].pid=-1;
			p.erase(p.begin()+j);
			j--;//to go back to this pointer and check with the next consecutive pair
		}
		if(j==p.size())
			break;
	    }
	    //if a new process demands memory
	    for(int i=0;i<n;i++){
		if(a[i].time_entry==timer){
	    		int opt_size=INT_MIN;
	    		int index=-1;
			for(int j=0;j<p.size();j++){
				if(p[j].size>=a[i].space_required&&p[j].flag==0){
					if(p[j].size>opt_size){
						opt_size = p[j].size;
						index=j;
						//cout<<j<<endl;
					}
					//cout<<"HEY TIMER VALUE IS :"<<timer<<endl;
					//break;
				}
			}
			int j=index;
			if(index!=-1){
				memory_available -=a[i].space_required;
				success.push_back(i+1);
				//cout<<memory_available<<" AVAILABLE MEMORY!!!!!!!!!!!!!!"<<endl;
				p[j].flag=1;
				//cout<<"Block "<<j<<" has turned its flag to "<<p[j].flag<<endl;
				p[j].pid = i+1;
				a[i].running = 1;
				a[i].first_exec=1;
				//cout<<"Process "<<i+1<<" is the getting block number "<<j<<endl;
				//splitting the memory block
				int q = p[j].end;
				p[j].end-= p[j].size-a[i].space_required;
				if(p[j].end!=m-1){
				      pairr o = {p[j].end+1,q,q-p[j].end,0,-1};
				      p.insert(p.begin()+j+1,o);
				}
				p[j].size=p[j].end-p[j].start+1;
			}
			//last=j;
			if(!a[i].first_exec){
				//cout<<memory_available<<" AVAILABLE MEMORY!!!"<<endl;				
				cout<<" PROCESS "<<i+1<<" COULDN'T BE GIVEN THE SPACE. MEMORY ALLOTMENT FAIL."<<endl;
				faill++;
				if(memory_available>=a[i].space_required){
					fail.push_back(i+1);
					cout<<"EXTERNAL FRAGMENTATION"<<endl;
				}
				a[i].complete=1;
			}
		}
	    }
	    //check if any process is left to be completed
	    for(int i=0;i<n;i++){
		if(!a[i].complete){
			f=1;
			break;
		}
	    }
	   /* cout<<"TIME INTERVAL : "<<timer<<"-"<<timer+1<<endl;
	    cout<<"Start Address  End Address     Space    ProcessID"<<endl;
	    //printing the memory structure every second
	    for(int j=0;j<p.size();j++)
		cout<<p[j].start<<"\t\t"<<p[j].end<<"\t\t"<<p[j].size<<"\t"<<p[j].pid<<endl;
	    //cout<<"MEMORY TOTAL RIGHT NOW : "<<memory_available<<endl;
	    cout<<"*********************************************************************************************************************************"<<endl;
	    */
	    if(timer%50==0){
		cout<<"TIMER : "<<timer<<endl;
		cout<<"NUMBER OF EXTERNAL FRAGMENTATION : "<<fail.size()<<endl;
		cout<<"NUMBER OF SUCCESSFUL ALLOCATIONS : "<<success.size()<<endl;
		float d;
		d = success.size();
		if(d+faill==0)
			cout<<"PERCENTAGE OF SUCCESSFUL ALLOCATIONS CANNOT BE DEFINED AS NO REQUEST CAME IN THIS INTERVAL"<<endl;
		else		
			cout<<"PERCENTAGE OF SUCCESSFUL ALLOCATIONS : "<<(d/(d+faill))*100<<"%"<<endl;		
		cout<<"*********************************************************************************************************************************"<<endl;
		//fail.clear();
		//success.clear();
		//faill=0;
	    }
	    timer++;
	    //condition to break the loop
	    if(f==0)	
		break;
	}
}
int main(){
    int memory=0;
    ifstream file;
    file.open("alloc.dat");

//reading the number of pages
    string line;
    getline(file, line);
    istringstream a (line);
    istream_iterator<int> begin(a), eof;
    vector<int> numbers(begin, eof);
    memory = *numbers.begin();
    vector <int> v;
    vector<string>w;

//Reading the page reference string
    while(1){
	getline(file,line);
	if(line=="-1,-1,-1")
		break;
	stringstream ss(line);
	while (ss.good()) {
        	string substr;
        	getline(ss, substr, ',');
		int y = stoi(substr);
        	v.push_back(y);
    	}
    }

    proc_num = v.size()/3;
    info* table;
    table = new info[proc_num];
    for(int i=0,j=0;i<proc_num;i++){
	table[i].time_entry = v[j];
	j++;
	table[i].space_required = v[j];
	j++;
	table[i].duration = v[j];
	j++;
    }
    WORST_FIT(table,proc_num,memory);
}
