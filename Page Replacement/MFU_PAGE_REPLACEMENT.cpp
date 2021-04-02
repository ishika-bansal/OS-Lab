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
    public :
	int time_entry;
    public :
	int frequency;
};

//global declaration
int timer = 0;


int LRU(vector <string> pages, int n, int capacity){ 
    // To represent set of current pages. We use 
    // an unordered_set so that we quickly check 
    // if a page is present in set or not 
    unordered_set<string> s; 
  
    // To store least recently used indexes of pages. 
    unordered_map<string, info> indexes; 
  
    // Start from initial page 
    int page_faults = 0; float hit=0.0;
    for (int i=0; i<n; i++) 
    { 	
	timer++;
        // Check if the set can hold more pages 
        if (s.size() < capacity) 
        { 
            // Insert it into set if not present already which represents page fault 
            if (s.find(pages[i])==s.end()) 
            { 
                s.insert(pages[i]); 		
                page_faults++; 
		//cout<<"Incremented page fault value"<<page_faults<<" while inserting the page"<<pages[i]<<endl;
		indexes[pages[i]].time_entry = i; 
            } 
	    else
		hit++;
	    indexes[pages[i]].frequency++;
		//hit++;
		//cout<<pages[i]<<"value of frequency is changed to : "<<indexes[pages[i]].frequency<<endl;
        } 
  
        // If the set is full then need to perform lru i.e. remove the least recently used page and insert the current page 
        else
        { 
            // Check if current page is not already 
            // present in the set 
            if (s.find(pages[i]) == s.end()) 
            { 
                // Find the least recently used pages 
                // that is present in the set 
                int lfu = INT_MIN;
		int time = INT_MAX;
		string val; 
                for (auto it=s.begin(); it!=s.end(); it++) 
                { 
                    if (indexes[*it].frequency >= lfu && indexes[*it].time_entry<time) 
                    { 
                        lfu = indexes[*it].frequency; 
                        val = *it; 
			time = indexes[*it].time_entry;
                    } 
                } 
                // Remove the indexes page 
		//cout<<"Removed "<<val<<" to insert "<<pages[i]<<endl;
                s.erase(val); 
                // insert the current page 
                s.insert(pages[i]); 
	
  		indexes[pages[i]].time_entry = i; 
                // Increment page faults 
                page_faults++; 
		//cout<<"Incremented page fault value"<<page_faults<<" while inserting the page"<<pages[i]<<endl;
            } 
	    else
		hit++;
	    indexes[pages[i]].frequency++;
  
        } 
	
	if(timer%25==0){
	  cout<<" "<<endl;
	  cout<<"***********************************************"<<endl;
	  cout<<"TIMER VALUE IS :"<<timer<<endl;
	  cout<<"MISS VALUE IS : "<< page_faults<<endl;
	  cout<<"HITS VALUE IS : "<<hit<<endl;
	  float ratio = hit/page_faults;
   	  cout<<"HIT RATIO IS : "<< ratio<<endl;
	  cout<<"***********************************************"<<endl;
	  //hit=0;
	  //page_faults=0;
	}
	}
  
   // cout<<"PAGE FAULTS ARE : "<< page_faults; 
} 
  
int main(){
    //number of frames
    int frame_number=5;
    //frame *f;
    //f = new frame[frame_number];
    int page_number=0;
    ifstream file;
    file.open("reference.dat");

//reading the number of pages
    string line;
    getline(file, line);
    istringstream a (line);
    istream_iterator<int> begin(a), eof;
    vector<int> numbers(begin, eof);
    page_number = *numbers.begin();

//Reading the page reference string
    getline(file,line);
    vector <string> v;
    stringstream ss(line);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }

    /*for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << endl;*/
    int page = v.size()-1;
    LRU(v,page,frame_number);
    return 0;
}
