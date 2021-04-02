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

// Function to check whether a page exists in a frame or not 
bool search(string key, vector<string >& fr) 
{ 
    for (int i = 0; i < fr.size(); i++) 
        if (fr[i] == key) 
            return true; 
    return false; 
} 
  
// Function to find the frame that will not be used recently in future after given index in pg[0..pn-1] 
int predict(vector <string> pg, vector<string> fr, int pn, int index) 
{ 
    // Store the index of pages which are going 
    // to be used recently in future 
    int res = -1, farthest = index; 
    for (int i = 0; i < fr.size(); i++) { 
        int j; 
        for (j = index; j < pn; j++) { 
            if (fr[i] == pg[j]) { 
                if (j > farthest) { 
                    farthest = j; 
                    res = i; 
                } 
                break; 
            } 
        } 
        // If a page is never referenced in future, return it. 
        if (j == pn) 
            return i; 
    } 
  
    // If all of the frames were not in future, return any of them, we return 0. Otherwise we return res. 
    return (res == -1) ? 0 : res; 
} 
  
void OPTIMAL(vector <string> pg, int pn, int fn) 
{ 
    // Create an array for given number of 
    // frames and initialize it as empty. 
    vector<string> fr; 
  
    // Traverse through page reference array 
    // and check for miss and hit. 
    float hit = 0.0; int miss = 0;
    for (int i = 0; i < pn; i++) { 
  
	timer++;
        // Page found in a frame : HIT 
        if (search(pg[i], fr)) { 
            hit++;  
	  if(timer%25==0){
	      cout<<" "<<endl;
	      cout<<"***********************************************"<<endl;
	      cout<<"TIMER VALUE IS :"<<timer<<endl;
	      cout<<"MISS VALUE IS : "<< miss<<endl;
	      cout<<"HITS VALUE IS : "<<hit<<endl;
	      float ratio = hit/miss;
   	      cout<<"HIT RATIO IS : "<< ratio<<endl;
	      cout<<"***********************************************"<<endl;
	      hit=0;
	      miss=0;
	  }
	   continue;
        } 

        // Page not found in a frame : MISS 
        // If there is space available in frames. 
	miss++;
        if (fr.size() < fn) 
            fr.push_back(pg[i]); 
  
        // Find the page to be replaced. 
        else { 
            int j = predict(pg, fr, pn, i + 1); 
            fr[j] = pg[i]; 
        } 
	//cout<<timer<<endl;
	if(timer%25==0){
	  cout<<" "<<endl;
	  cout<<"***********************************************"<<endl;
	  cout<<"TIMER VALUE IS :"<<timer<<endl;
	  cout<<"MISS VALUE IS : "<< miss<<endl;
	  cout<<"HITS VALUE IS : "<<hit<<endl;
	  float ratio = hit/miss;
   	  cout<<"HIT RATIO IS : "<< ratio<<endl;
	  cout<<"***********************************************"<<endl;
	 // hit=0;
	  //miss=0;
	}
    } 
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

  /*  for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << endl;*/
    int page = v.size()-1;
    cout<<"TOTAL : "<<page<<endl;
    OPTIMAL(v,page,frame_number);
    return 0;
}
