/*Ishika
2017UCP1566
to create a handler for ELF (executable and linking format) files in Linux. Your program should display important information 
about file under consideration. Name of executable file to be processed should be a command line argument. Output should be written to a file called output.txt.*/


#include <bits/stdc++.h> 
using namespace std;
int main (int argc, char** argv) 
{ 
    
      //Takes the Command line argument gcc    
	 string str = "gcc "; 
	 
	 //The argument 1 contains the parameter
    str = str + " -o aa " + argv[1]; 
  
    // Convert string to const char * as system requires 
    // parameter of type const char * 
    const char *command = str.c_str(); 
  
  
  //To compile the program and find using the command 
    cout << "Compiling file using " << command << endl; 
    system(command);  
    string s="aa ";
     str = "readelf "; 
     //THe output will be stored in the output.txt file
     //The output.txt file contains the header of the elf file 
    str = str  + s + "-h " + ">> output.txt"; 
  
    
    const char *comman = str.c_str(); 
  
    cout  << comman << endl; 
    system(comman); 

    cout << "\nRunning file "; 
  
    return 0; 
} 
