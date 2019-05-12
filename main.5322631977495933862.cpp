#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

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
    char files {"pulsar", "10 cell row", "glider0", "glider1", "glider2", "glider3", "glider4", "Gosper glider gun", "pulsar"};
    //              
    cout << "Please enter filename (with file extension, spaces allowed):" << endl;
    cin >> filename;

    for( intindex = 0 ; index < MAX_ELEMENTS; index++ )
    {
    cout<< "numbers["<< index << "] = "
    << numbers[index] << endl;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              

    //               

    //               

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              

    //               

    //               

    }

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              

    //               

    //               

    }

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);
}

