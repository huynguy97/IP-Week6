#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstring>

//                                            
//                                                   

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
    char input;

    cout << "Enter a filename: " << endl;
    cin.get(input);

    //              
 //                                        
    //               
    //                                                                                
    //                                                

    int index = 0;
    while (input != '\n')
    {
        if (input == MAX_FILENAME_LENGTH)
            return false;
        if (input == '\n')
        {
            filename[index] = '\0';
        }
        else
        {
            cin.get(input);
            filename[index] = input;
            index++;
        }
    }
    cout << "You entered the filename: " << filename << endl;
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //             
    assert (inputfile.is_open());
    //               
    char b;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            inputfile.get(b);

            if (b ='*')
                universe[r][c] = Live;
            else if (b ='.')
                universe[r][c] = Dead;

        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    cout << universe[ROWS][COLUMNS];

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
    ifstream inputfile;
    Cell universe [ROWS][COLUMNS];

    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);
    inputfile.open(filename);

    read_universe_file (inputfile, universe);
    //                         

}

