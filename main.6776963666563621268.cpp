/*                        
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <string.h>
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
    assert(MAX_FILENAME_LENGTH > 0);
    /*                 
                                      
                                                                        
    */
    cout << "enter a file name" << endl;
    char c;
    for(int i = 0; i < MAX_FILENAME_LENGTH - 1; i++)
    {
        c = cin.get();
        if(c != '\n')
        {
            filename[i] = c;
        }
        else
        {
            filename[i] = '\0';
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              
    assert(inputfile.is_open());
    /*                 
                                                        
    */
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            universe[i][j] = Dead;
        }
    }
    char c;
    for(int i = 1; i <= NO_OF_ROWS; i++)
    {
        for(int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            inputfile >> c;
            if(c == LIVE)
            {
                universe[i][j] = Live;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(true);
    /*                 
                                              
    */
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if(universe[i][j] == 0)
                cout << DEAD;
            else
                cout << LIVE;
        }
        cout << "\n";
    }
}

int liveAround(Cell universe[ROWS][COLUMNS], int i, int j)
{
    //              
    assert(i > 0 && j > 0);
    /*                 
                                                                     
    */
    int counter = 0;
    for(int k = i - 1; k <= i + 1; k++)
    {
        for(int l = j - 1; l <= j+1; l++)
        {
            if(k != i || l != j)
            {
                if(universe[k][l] == Live)
                {
                    counter++;
                }
            }
        }
    }
    return counter;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert(true);
    /*                 
                                                 
                                                                                                 
                                                                                        
                                                                                       
                                                                                                    
                                        
    */
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            next[i][j] = now[i][j];
        }
    }
    for(int i = 1; i <= NO_OF_ROWS; i++)
    {
        for(int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            int liveNeighbours = liveAround(now, i, j);
            if(now[i][j] == Live)
            {
                if(liveNeighbours < 2)
                {
                    next[i][j] = Dead;
                }
                else if(liveNeighbours > 3)
                {
                    next[i][j] = Dead;
                }
            }
            else
            {
                if(liveNeighbours == 3)
                {
                    next[i][j] = Live;
                }
            }
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    if(enter_filename(filename))
    {
        ifstream input;
        input.open(filename);
        if(input.is_open())
        {
            Cell universe[ROWS][COLUMNS];
            read_universe_file(input, universe);
            show_universe(universe);
            Cell next[ROWS][COLUMNS];
            cout << "\nnext generation:\n" << endl;
            next_generation(universe, next);
            show_universe(next);
        }
        else
            cout << "opening file failed" << endl;
    }
    else cout << "filename too long" << endl;
}

