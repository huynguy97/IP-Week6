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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    assert(filename) ; //             
    //                                                                                          
    cout << "Enter a filename. The total number of characters may not exceed " << MAX_FILENAME_LENGTH << ". \n" ;
    cin.getline(filename, 9999999) ; //                                                            
    int i = 0 ;
    while(filename[i]) //                                       
        i++ ;
    if (i >= MAX_FILENAME_LENGTH)
        return false ;
    filename[i] = '\0' ; //                                                                                                                      
    return true ;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(inputfile && universe) ;//                                   
    //                                                                                                       
    //                                                                                         
    char filename [MAX_FILENAME_LENGTH] ;
    enter_filename(filename) ;
    inputfile.open(filename) ;
    for (int i = 0 ; i < ROWS ; i++) //                                                 
    {
        for (int j = 0 ; j < COLUMNS ; j++)
        {
            if (j==0||j==COLUMNS-1||i==0||i==ROWS-1)
                universe[i][j] = Dead ;
        }
    }
    int column = 1 ; //                                                        
    int row = 1 ;//                                                        
    char c ;
    inputfile.get(c) ;
    while(inputfile) //                                                  
    {
        switch(c)
        {
        case '.':
            {
                universe[row][column] = Dead ;
                column++ ;
                break ;
            }
        case '*':
            {
                universe[row][column] = Live ;
                column++ ;
                break ;
            }
        case '\n':
            {
                row++ ; //                      
                column = 1 ; //                                
                break ;
            }
        }
        inputfile.get(c) ;
    }
    return (inputfile && enter_filename(filename)) ;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(universe) ;//              
    //                                                     
    for (int row = 0 ; row < ROWS ; row++)
    {
        for (int column = 0 ; column < COLUMNS ; column++)
        {
            switch(universe[row][column])
            {
                case 0 : cout << DEAD ; break ;
                case 1 : cout << LIVE ; break ;
            }
        }
        cout << "\n" ;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(now && next) ;//              
    //                                                                                       
    for (int row = 0 ; row < ROWS ; row++)
    {
        for (int column = 0 ; column < COLUMNS ; column++)
        {
            if (column==0||column==COLUMNS-1||row==0||row==ROWS-1)
                next[row][column] = now[row][column] ; //                          
            else
            {
                int live_around = 0 ; //                                                                             
                live_around = now[row+1][column] + now[row][column+1] + now[row-1][column] + now[row][column-1] + now[row+1][column+1] + now[row+1][column-1] + now[row-1][column-1] + now[row-1][column+1] ;
                switch(now[row][column])
                {
                case 0 :
                    {
                        if (live_around == 3)
                            next[row][column] = Live ;
                        else
                            next[row][column] = Dead ;
                        break ;
                    }
                case 1 :
                    {
                        if (live_around == 2 || live_around == 3)
                            next[row][column] = Live ;
                        else
                            next[row][column] = Dead ;
                        break ;
                    }
                }
            }
        }
    }
}

int main ()
{
    Cell now [ROWS][COLUMNS] ;
    Cell next [ROWS][COLUMNS] ;
    ifstream inputfile ;
    read_universe_file (inputfile, now) ;
    show_universe(now) ;
    next_generation(now, next) ;
    cout << "\n" ;
    show_universe(next) ;
    return 0 ;
}

