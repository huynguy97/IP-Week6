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
    cout << "Enter a filename" << endl ;

    char c ;
    int index = 0 ;
    while (cin.get(c))
    {
        if (index < MAX_FILENAME_LENGTH)
        {
            if (c == '\n')
            {
                filename [index] = '\0' ;
                break ;
            }
            else
            {
                filename [index] = c ;
            }
            index++ ;
        }
        else
        {
            if (c != '\n')
                return false ;
            else
                filename [MAX_FILENAME_LENGTH] = '\0' ;
        }
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
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
    cout << endl ;
}

int get_live_cell_neighbours(Cell universe[ROWS][COLUMNS], int row, int column) {
    //              
    assert((row > 0 && column > 0) && (row <= NO_OF_ROWS && column <= NO_OF_COLUMNS));

    //               
    //                                                                                                               

    //                         
    int livecells = 0;
    livecells += universe[row-1][column-1];
    livecells += universe[row-1][column];
    livecells += universe[row-1][column+1];
    livecells += universe[row][column-1];
    livecells += universe[row][column+1];
    livecells += universe[row+1][column-1];
    livecells += universe[row+1][column];
    livecells += universe[row+1][column+1];
    return livecells;
}

int number_live_neighbours (Cell universe [ROWS] [COLUMNS])
{
    int neighbours = 0 ;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {

            /*
                                  
                                        
             
                                            
                 
                                                      
                     
                                            
                         
                                         
                         
                     
                 
             
            */
            if (universe[i+1][j+1] == Live)
                neighbours++ ;
            else if (universe[i][j+1] == Live)
                neighbours++ ;
            else if (universe[i-1][j+1] == Live)
                neighbours++ ;
            else if (universe[i+1][j] == Live)
                neighbours++ ;
            else if (universe[i-1][j] == Live)
                neighbours++ ;
            else if (universe[i][j-1] == Live)
                neighbours++ ;
            else if (universe[i-1][j-1] == Live)
                neighbours++ ;
            else if (universe[i+1][j-1] == Live)
                neighbours++ ;

            //                   
        }
        //              
    }
    return neighbours ;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                

    for (int i = 0; i < NO_OF_ROWS; i++)
    {
        for (int j = 0; j < NO_OF_COLUMNS; j++)
        {
            if (now [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] == Live && number_live_neighbours(now)>3)
            {
                next [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] = Dead ;
            }
            else if (now [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] == Live && number_live_neighbours(now)<2)
            {
                next [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] = Dead ;
            }
            else if (now [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] == Live && (number_live_neighbours(now)==3 || number_live_neighbours(now)==2))
            {
                next [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] = Live ;
            }
            else if(now [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] == Dead && number_live_neighbours(now)==3)
            {
                next [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] = Live ;
            }
            else
            {
                next [1+NO_OF_ROWS] [1+NO_OF_COLUMNS] = Dead ;
            }
        }
    }
    for (int k = 0; k < ROWS; k++)
    {
        for (int l = 0; l < COLUMNS; l++)
        {
            if (next [k] [l] == Live)
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
    char filename [MAX_FILENAME_LENGTH] ;
    enter_filename(filename) ;

    ifstream input ;
    input.open (filename) ;

    if (input.is_open())
    {
        cout << "File is opened successfully." << endl ;
    }
    else
    {
        cout << "File is not opened successfully." << endl ;
    }

    Cell universe [ROWS] [COLUMNS] ;
    read_universe_file(input, universe) ;
    show_universe(universe) ;
    Cell next [ROWS] [COLUMNS] ;
    next_generation(universe, next) ;
    //                                  
    return 0 ;
}
