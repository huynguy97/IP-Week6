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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //             
    asser (MAX_FILENAME_LENGTH > 0)
    //                                                                                                 
    cout << "Enter the name of the file: " << endl;
    char c;
    cin.get(c);
    int index = 0;
    while (c != '\n')
    {
        filename [index] = c;
        index ++;
        cin.get(c);
    }
    if (c == '\n')
    {
        filename [index] = '\0';
    }
    if (index < MAX_FILENAME_LENGTH)
        return true;
    else
        return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //             
    assert (ROWS > 0 && COLUMNS > 0)
    //                                                                                         
    if (!inputfile)
    {
        return false;
    }
    for (int r = 0; r < ROWS; r++)
    {
            for (int c = 0; c < COLUMNS; c++)
            {
                if (r == 0 || r == 41 || c == 0 || c == 61)
                {
                    universe[r][c] = Dead;
                }
                else
                {
                    char c = inputfile.get();
                    if (c == DEAD)
                    {
                        universe [r][c] = Dead;
                    }
                    else
                        universe [r][c] = Live;

                }
            }
        char x;
        inputfile.get(x);
        if (x = '\n')
        {
            r = 0;
        }
    }
    inputfile.close();
    return true;

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //             
    assert (ROWS > 0 && COLUMNS > 0)
    //                                                                                    
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (universe [r][c] == Dead)
                cout << DEAD ;
            else
                cout << LIVE;
        }
    cout << endl;
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
    cout << "Enter the filename: ";
    char FileInput =
    Cell universe [ROWS][COLUMNS];
    read_universe_file(FileInput, universe);
    show_universe(universe);
}

