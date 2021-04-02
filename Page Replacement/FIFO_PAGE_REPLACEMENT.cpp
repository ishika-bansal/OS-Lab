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

//global declaration
int timer = 0;

void FIFO(vector <string> pages, int x, int m){
    unordered_set <string> s;
    int n = pages.size()-1;
    // To store the pages in FIFO manner
    queue<string> indexes;

    // Start from initial page
    int page_faults = 0;
    float hits=0.0;
    for (int i=0; i<n; i++)
    {
        timer++;
        // Check if the set can hold more pages
        if (s.size() < m)
        {
            // Insert it into set if not present
            // already which represents page fault
            if (s.find(pages[i])==s.end())
            {
                // Insert the current page into the set
                s.insert(pages[i]);

                // increment page fault
                page_faults++;
		//cout<<"Incremented page fault value"<<page_faults<<" while inserting the page"<<pages[i]<<endl;

                // Push the current page into the queue
                indexes.push(pages[i]);
            }
	    else
		hits++;
        }
        // If the set is full then need to perform FIFO
        // i.e. remove the first page of the queue from
        // set and queue both and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            if (s.find(pages[i]) == s.end())
            {
                // Store the first page in the
                // queue to be used to find and
                // erase the page from the set
                string val = indexes.front();
                // Pop the first page from the queue
                indexes.pop();

                // Remove the indexes page from the set
                s.erase(val);

                // insert the current page in the set
                s.insert(pages[i]);

		//cout<<"Incremented page fault value"<<page_faults<<" while inserting the page"<<pages[i]<<endl;
                // push the current page into
                // the queue
                indexes.push(pages[i]);

                // Increment page faults
                page_faults++;
            }
	    else
		hits++;
        }
	if(timer%25==0){
	  cout<<" "<<endl;
	  cout<<"***********************************************"<<endl;
	  cout<<"TIMER VALUE IS :"<<timer<<endl;
	  cout<<"MISS VALUE IS : "<< page_faults<<endl;
	  cout<<"HITS VALUE IS : "<<hits<<endl;
	  float ratio = hits/page_faults;
   	  cout<<"HIT RATIO IS : "<< ratio<<endl;
	  cout<<"***********************************************"<<endl;
	  //hits=0;
	  //page_faults=0;
	}
    }
    //cout<<page_faults<<endl;
    //cout<<timer<<endl;
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

    //for (size_t i = 0; i < v.size(); i++)
      //  cout << v[i] << endl;
    FIFO(v,page_number,frame_number);
    return 0;
}
