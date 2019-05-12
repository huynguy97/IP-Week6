#include <iostream>
#include <fstream>
#include <cassert>

/*                                                        
                                                                                                                                                                                                
                                                                        
*/

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
    assert ( true ) ;
    //                 
    //                                                                                                                                 
    //                                           
    cout << "Please enter a file name (80 characters max)." << endl ;
    for (int index = 0; index < MAX_FILENAME_LENGTH; index++)
    {
        cin.get(filename[index]);
        if (filename[index] == '\n')
        {
            filename[index] = '\0' ;
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert (inputfile.is_open()) ;
    //               
    //                                                                                   
    for (int r = 0; r < ROWS ; r++)
    {
        for (int c = 0; c < COLUMNS ; c++)
        {
            if (r == 0 || c == 0 || c == COLUMNS-1 || r == ROWS-1)
                universe [r][c] = Dead ;
            else
            {
                char a ;
                inputfile.get(a);
                if (a == DEAD)
                    universe [r][c] = Dead ;
                if (a == LIVE)
                    universe [r][c] = Live ;
            }
        }
        if (r != 0 && r != ROWS-1) {
            inputfile.get() ;
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true) ;
    //                
    //                  
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (universe[r][c] == Dead)
                cout << "." ;
            else
                cout << "*" ;
        }
        cout << endl ;
    }
    cout << endl ;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert (true) ;
    //                
    //                                
    for (int r = 1; r < NO_OF_ROWS + 1; r++)
    {
        for (int c = 1; c < NO_OF_COLUMNS + 1; c++)
        {
            int neighbour_count = 0 ;
            if (now [r][c] == Live)
            {
                if (now[r-1][c-1] == Live)
                    neighbour_count++ ;
                if (now[r][c-1] == Live)
                    neighbour_count++ ;
                if (now[r+1][c-1] == Live)
                    neighbour_count++ ;
                if (now[r-1][c] == Live)
                    neighbour_count++ ;
                if (now[r+1][c] == Live)
                    neighbour_count++ ;
                if (now[r-1][c+1] == Live)
                    neighbour_count++ ;
                if (now[r][c+1] == Live)
                    neighbour_count++ ;
                if (now[r+1][c+1] == Live)
                    neighbour_count++ ;
                if (neighbour_count > 3 || neighbour_count < 2)
                    next[r][c] = Dead ;
                else
                    next[r][c] = Live ;
            }
            if (now [r][c] == Dead)
            {
                if (now[r-1][c-1] == Live)
                    neighbour_count++ ;
                if (now[r][c-1] == Live)
                    neighbour_count++ ;
                if (now[r+1][c-1] == Live)
                    neighbour_count++ ;
                if (now[r-1][c] == Live)
                    neighbour_count++ ;
                if (now[r+1][c] == Live)
                    neighbour_count++ ;
                if (now[r-1][c+1] == Live)
                    neighbour_count++ ;
                if (now[r][c+1] == Live)
                    neighbour_count++ ;
                if (now[r+1][c+1] == Live)
                    neighbour_count++ ;
                if (neighbour_count == 3)
                    next[r][c] = Live ;
                else
                    next[r][c] = Dead ;
            }
        }
    }

}

int main ()
{
    char FILENAME [MAX_FILENAME_LENGTH] ;
    enter_filename(FILENAME) ;
    ifstream file(FILENAME) ;
    Cell universe[ROWS][COLUMNS];
    read_universe_file(file, universe);
    show_universe(universe) ;
    next_generation(universe, universe) ;
    show_universe(universe) ;
    return 0 ;
}

