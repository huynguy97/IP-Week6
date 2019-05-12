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
    assert( sizeof(filename) <= MAX_FILENAME_LENGTH ) ;
    //                 
    //                                                                                        
    //                                   
    cout << "Enter a filename with a maximum of 80 characters (including '.txt')\n" ;
    int counter = 0 ;
    char c ;
    cin.get(c) ;
    filename[counter] = c ;
    while (filename[counter] != '\n')
    {
        counter++ ;
        if (counter > 80)
        {
            return false ;
        }
        cin.get(c) ;
        filename[counter] = c ;
    }
    filename[counter] = '\0' ;
    return true ;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(inputfile.is_open()) ;
    //                 
    //                                
    //                                                                                     
    char c ;
    int row = 1 ;
    int column = 1 ;
    while (inputfile.get(c))
    {
        if (c == '\n')
        {
            row++ ;
            column = 1 ;
        }
        else
        {
            if (c == DEAD)
            {
                universe[row][column] = Dead ;
            }
            else
            {
                universe[row][column] = Live ;
            }
            column++ ;
        }
    }
    if (row != 42 && column != 62)
    {
        return false ;
    }
    else
    {
        return true ;
    }
}

void clear_universe(Cell universe [ROWS][COLUMNS])
{
    //                
    assert ( true ) ;
    //                 
    //                                 
    for (int row = 0 ; row < ROWS ; row++)
    {
        for (int column = 0 ; column < COLUMNS ; column++)
        {
            universe[row][column] = Dead ;
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert( true ) ;
    //                 
    //                                  
    for (int row = 0 ; row < ROWS ; row++)
    {
        for (int column = 0 ; column < COLUMNS ; column++)
        {
            if (universe[row][column] == Live)
            {
                cout << LIVE ;
            }
            else
            {
                cout << DEAD ;
            }
        }
        cout << "\n" ;
    }
}

//                             

int count_living (int row, int column, Cell universe[ROWS][COLUMNS])
{
    //                
    assert(row > 0 && row < ROWS && column > 0 && column < COLUMNS) ;
    //                 
    //                                                                  
    int live_counter = 0 ;
    for (int i = row - 1 ; i <= row + 1 ; i++)
    {
        for (int j = column - 1 ; j <= column + 1 ; j++)
        {
            if (universe[i][j] == Live)
            {
                live_counter++ ;
                if (row == i && column == j)
                {
                    live_counter-- ;
                }
            }
        }
    }
    return live_counter ;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
    assert( true )
    //                 
    //                                                 
    for (int row = 1 ; row <= NO_OF_ROWS ; row++ )
    {
        for (int column = 1 ; column <= NO_OF_COLUMNS ; column++ )
        {
            if ((count_living(row, column, now) == 3) || (count_living(row, column, now) == 2 && now[row][column] == Live))
            {
                next[row][column] = Live ;
            }
            else
            {
                next[row][column] = Dead ;
            }
        }
    }
}

int main ()
{
    Cell universe [ROWS][COLUMNS] ;
    clear_universe(universe) ;
    char filename [MAX_FILENAME_LENGTH] ;
    enter_filename(filename) ;
    string infile = filename ;
    ifstream inputfile ;
    inputfile.open(filename) ;
    read_universe_file(inputfile, universe) ;
    Cell next [ROWS][COLUMNS] ;
    next_generation(universe, next) ;
    show_universe(next) ;
    return 0 ;
}

