#include <iostream>
#include <fstream>
#include <cassert>
#include <math.h>
using namespace std;
//                         
enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    cout << "please enter the file name, which is less than " << MAX_FILENAME_LENGTH << '\n';
    while (filename[MAX_FILENAME_LENGTH] < 80)
    {cin.get(filename[MAX_FILENAME_LENGTH]);
    filename [MAX_FILENAME_LENGTH]++;}
    if (filename[MAX_FILENAME_LENGTH] > MAX_FILENAME_LENGTH)
    {
        cout << "your file couldn't be opened" << endl;
        return false;
    }
    else
    {
        cout << "your file was succesfully opened" << endl;
        return true;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    char* filename[MAX_FILENAME_LENGTH];
    enter_filename(filename[MAX_FILENAME_LENGTH]);
    inputfile==filename;
    infile >> [ROWS][COLUMNS];
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
    char* filename[MAX_FILENAME_LENGTH];
    enter_filename(filename[MAX_FILENAME_LENGTH]);
}

