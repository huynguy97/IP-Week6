#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//                                                  
//                                      
//                                                                                               

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

void show_elements (char data [], int length)
{
    assert (length >= 0);
    for (int index = 0; index < length -1; index++)
    cout << data [index] << ' ';
    if (length > 0)
        cout << data [length - 1];
}

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //             
    assert (MAX_FILENAME_LENGTH >= 0);
    //                                                            
    cout << "Enter a file name: ";
    int numbers_read = 0;
    while (numbers_read < 1)
    {
        cin >> filename [numbers_read++];
    }
    cout << "Succes!";

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
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
    char file_input [MAX_FILENAME_LENGTH];
    file_input [0] = 'P';
    file_input [1] = 'e';
    show_elements(file_input, MAX_FILENAME_LENGTH);
}

