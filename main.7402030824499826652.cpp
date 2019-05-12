#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (true);
    //                                                                                                                    

    cout << "Enter an input file name" << endl;

    char c;
    int index = 0;

    while(cin.get(c))
    {
        if(index < MAX_FILENAME_LENGTH)
        {
            if(c == '\n')
            {
                filename[index] = '\0';
                break;
            }
            else
            {
                filename[index] = c;
            }
            index++;
        }
        else
        {
            if(c != '\n')
            {
                return false;
            }
            else
            {
                filename[MAX_FILENAME_LENGTH] = '\0';
            }
        }
    }

    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true)
    //                                                    
    for (int k = 0; k < COLUMNS; k++)
    {
        universe [0] [k] = Dead ;
        universe [ROWS-1] [k] = Dead ;
    }
    char a ;
    for (int i = 0; i <= NO_OF_ROWS; i++)
    {
        universe [1+i] [COLUMNS-1] = Dead ;
        universe [1+i] [0] = Dead ;
        for (int j = 0; j <= NO_OF_COLUMNS; j++)
        {
            inputfile.get(a) ;
            if (a == DEAD)
            {
                universe [1+i] [1+j] = Dead ;
                //             
            }
            else if (a == LIVE)
            {
                universe [1+i] [1+j] = Live ;
                //             
            }

        }
        //              
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                                                          
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (universe [i] [j] == Live)
            {
                cout << LIVE ;
            }
            else
            {
                cout << DEAD ;
            }
        }
        cout << endl ;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                                        
    next = now;
    cout << endl;
    cout << "After 1 step:" << endl;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            int neighbours = 0;

            /*                                                                                                     
                                        
             
                                            
                 
                                                  
                     
                                            
                         
                                         
                         
                     
                 
             */

            //                                                                                                           
            if(next[i - 1][j - 1])
            {
                neighbours++;
            }
            if(next[i - 1][j])
            {
                neighbours++;
            }
            if(next[i - 1][j + 1])
            {
                neighbours++;
            }
            if(next[i][j - 1])
            {
                neighbours++;
            }
            if(next[i][j + 1])
            {
                neighbours++;
            }
            if(next[i + 1][j - 1])
            {
                neighbours++;
            }
            if(next[i + 1][j])
            {
                neighbours++;
            }
            if(next[i + 1][j + 1])
            {
                neighbours++;
            }

            if(i == 0 || i == (ROWS - 1) || j == 0 || j == (COLUMNS - 1))
            {
                neighbours = 0;
            }

            if(next[i][j] == Live)
            {
                if(neighbours < 2 || neighbours > 3)
                {
                    next[i][j] = Dead;
                }
            }
            else
            {
                if(neighbours == 3)
                {
                    next[i][j] = Live;
                }
            }

            if (next [i] [j] == Live)
            {
                cout << LIVE ;
            }
            else
            {
                cout << DEAD ;
            }
        }
        cout << endl ;
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream input;
    input.open(filename);

    if(input.is_open())
    {
        cout << "File was opened succesfully." << endl;
    }
    else
    {
        cout << "File was not opened." << endl;
    }

    Cell universe[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];
    read_universe_file(input, universe);
    show_universe(universe);
    next_generation(universe, next);
}

