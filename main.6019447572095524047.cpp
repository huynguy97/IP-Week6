#include <iostream>
#include <fstream>
#include <cassert>
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
    //                
    assert (true);
    /*                                                                                                           
                                                                         
    */
    cout << "Enter a filename (maximum of 80 characters): ";
    for (int index = 0; index < MAX_FILENAME_LENGTH; index++)
    {
        cin.get(filename[index]);
        if (filename[index] == '\n')
        {
            filename[index] = '\0';
            return true;
        }
    }

    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open() && ROWS >= 0 && COLUMNS >=0);

    //                                                                                                                                     
    //                                                                                                                  
    //                                                                                                      

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1)
            {
                universe[r][c] = Dead;
            }
            else
            {
                char c = inputfile.get();
                if (c == DEAD)
                {
                    universe[r][c] = Dead;
                }
                else if (c == LIVE)
                {
                    universe[r][c] = Live;
                }
                else
                {
                    return false;
                }
            }
        }
        if (r != 0 && r != ROWS-1)
        {
            if (inputfile.get() != '\n')
            {
                return false;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{

    //               
    assert (ROWS >= 0 && COLUMNS >=0);

    //                                                                                         
    //                                                           

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1)
            {
                cout << DEAD ;
                if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1)
                {
                    universe[r][c] = Dead;
                }
                else
                {
                    if (universe[r][c] == Dead)
                    {
                        cout << DEAD;
                    }
                    else if (universe[r][c] == Live)
                    {
                        cout << LIVE;
                    }
                }

            }
        }
        if (r != 1 && r != ROWS-1)
        {
            cout << '\n';
        }
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{

//                

    assert (true);

//                                                                            
//                                                                                                                
//                                                                                                                               

int living cells;

    if (now == Dead)
    {
        if(living_cells == 3)
        {
            next = Live;
        }
        else
        {
            next = Dead;
        }
    }
    else
    {
        switch(next)
        {
        case (living_cells == 1):
            return Dead;
            if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1)
            {
                universe[r][c] = Dead;
            case (living_cells == 2 || living_cells == 3):
                return Live;
            case (living_cells > 3):
                return Dead;

            }
        }

    }

    int main ()
    {
        char filename[MAX_FILENAME_LENGTH];
        if (!enter_filename(filename))
        {
            cout << "Filename too long!" << endl;
            return -1;
        }
        ifstream inputfile(filename);
        Cell universe[ROWS][COLUMNS];
        if (!read_universe_file(inputfile, universe))
        {
            cout << "File could not be read!" << endl;
            return -2;
        }
        show_universe(universe);

        inputfile.close();

    }

