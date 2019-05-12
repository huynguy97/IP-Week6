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
    //                
    assert(true);
    //                
    //                                                                                                               
    //              
    cout << "Enter a file name:"  << endl;
    char a = 'a';
    int index = 0;
    while (a != '\n')
    {
        cin.get(a);
        filename[index] = a;
        index++;
        if (index > MAX_FILENAME_LENGTH)
        {
            return false;
        }

    }
    filename [index] = '\0';
    return true;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                 
    //               
    char filename[MAX_FILENAME_LENGTH];
    if (enter_filename(filename))
    {
        inputfile.open(filename);
        char d;
        for(int i = 0; i < NO_OF_ROWS; i++)
        {
            for(int j = 0; j < NO_OF_COLUMNS; j++)
            {
                inputfile.get (d);

                if (d == LIVE)
                {
                    universe[i][j] = Live;
                }
                else if (d == DEAD)
                {
                    universe[i][j] = Dead;
                }

            }
        }

    }
    for (int i=0; i< ROWS; i++)
        {
            for (int j=0; j<COLUMNS; j++)
            {
                universe[0][j] = Dead;
                universe [ROWS-1][j] = Dead;
                universe[i][0] = Dead;
                universe [i][COLUMNS-1] = Dead;
            }
        }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                
    //              
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if (universe [i][j]== Live)
            {
                cout << LIVE;
            }
            else
            {
                cout << DEAD;
            }

        }
        cout << endl;
    }

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
    Cell universe [ROWS][COLUMNS];
    ifstream inputfile;
    read_universe_file (inputfile,universe);
    show_universe(universe);
    return 0;
}

