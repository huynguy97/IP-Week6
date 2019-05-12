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

    //               
    //                                                                                      
    //                                                                   

    cout << "Enter file the file name:" ;
    char c;
    for (int i=0; i <= MAX_FILENAME_LENGTH; i++ )
    {
        cin.get(c);
        filename[i] = c;
        if ( c == '\n')
        {
            filename [i] = '\0';
            return true;
        }
    }
    return false;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                

    //             
    assert(true);
    //              
    //                                               

    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < COLUMNS; b ++)
        {

            if ( a == 0 || b == 0 || a == ROWS - 1 || b == COLUMNS - 1)
            {
                universe[a][b] = Dead;
            }
            else
            {
                char c;
                inputfile.get(c);
                if ( c == '\n')
                {
                    inputfile.get(c);
                }
                if (c == '.' )
                {
                    universe[a][b] = Dead;
                }
                else
                {
                    universe[a][b] = Live;

                }
            }
        }

    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//              
    assert (true);

//               
//                                                             
//                                                               

    string universe_string;
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < COLUMNS; b ++)
        {

            if (universe[a][b] == Dead )
            {
                universe_string+='.';
            }
            else
            {
                universe_string+= '*';
            }
        }
        universe_string+='\n';
    }
    cout << "This is a step: " << endl;
    cout << universe_string << endl;
}

int number_of_live_neighbors(Cell universe[ROWS][COLUMNS], int column, int row)

{
    //             
    assert (column >= 1 && column <= NO_OF_COLUMNS && row >= 1 && row <= NO_OF_ROWS);
    //              
    //                                              

    int live_neighbors = 0;
    for ( int a = row - 1; a <= row + 1; a++)
    {
        for ( int b = column - 1; b <= column + 1; b++)
        {

            if (a != row || b != column)
            {
                //                                                                                                                                                 
                if (universe[a][b] == Live)
                {
                    live_neighbors ++;
                }
            }
        }
    }

    return live_neighbors;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{

    //              
    assert(true);
    //              
    //                                                                    
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < COLUMNS; b ++)
        {
            if ( a == 0 || b == 0 || a == ROWS - 1 || b == COLUMNS - 1)
            {
                next[a][b] = Dead;
            }
            else
            {
                int live_neighbors = number_of_live_neighbors(now,b,a);
                if (now[a][b] == Live )
                {
                    if (live_neighbors < 2 || live_neighbors > 3)
                    {
                        next[a][b] = Dead;
                    }
                    else
                    {
                        next[a][b] = Live;
                    }
                }
                else
                {
                    if (live_neighbors == 3)
                    {
                        next[a][b] = Live;
                    }
                    else
                    {
                        next[a][b] = Dead;
                    }
                }
            }
        }
    }

}

int main ()
{
    char filename [MAX_FILENAME_LENGTH] ;
    if (enter_filename(filename))
    {
        Cell universe [ROWS][COLUMNS];
        ifstream inputfile(filename);
        read_universe_file(inputfile, universe);
        show_universe(universe);
        Cell next_universe[ROWS][COLUMNS];
        number_of_live_neighbors(universe,1,1);
        next_generation(universe,next_universe);
        show_universe(next_universe);
    }
}

