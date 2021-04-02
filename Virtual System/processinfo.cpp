#include <bits/stdc++.h>
using namespace std;

// 4(c)

int main(int argc, char **argv) {
   
    string pid = argv[1];
    string a = "/proc/"+pid+"/cmdline";   
   
    ifstream f;
    f.open(a);
    string cmdLine;
    while (f) {   
        getline(f, cmdLine);
        cout<<"The commandline with which the process was started = "<<cmdLine<<endl;
        break;      
    
    }   
    f.close();
    cout<<"\nProcess statistics : "<<endl;      
    f.open("/proc/stat");
    string line;
    while(f){
	getline(f, line);
	int c = line.find("cpu");
	if(c==string::npos)
		break;
	cout<<line<<endl;
    }
    f.close();
        
    string b = "/proc/"+pid+"/schedstat";     
    string cputime,waitingtime,timeslices;
    ifstream f2;
    f2.open(b);
    f2>>cputime>>waitingtime>>timeslices;
    cout<<"\nProcess with pid "<<pid<<endl;
    cout<<"CPU Time spent by process  = "<<pid<<cputime<<" seconds"<<endl;
    cout<<"Waiting time of the process =  "<<waitingtime<<" seconds"<<endl;
    cout<<"Number of time slices run on this cpu = "<<timeslices<<endl;
    f2.close();
    
    cout<<"\nThe ENVIRONMENT of the process : "<<endl;
    string c = "/proc/"+pid+"/environ";
    ifstream f3;
    f3.open(c);
    string env;
    while(f3){
    	getline(f3,env);
    	cout<<env<<endl;
    }
    cout<<endl<<env<<endl<<endl; 
    f3.close();   

    return 0;
   
}

