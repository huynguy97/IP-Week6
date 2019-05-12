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
assert(true);
//                                                                                  
cout<< "please enter a filename " ;
for (int positie ; positie< MAX_FILENAME_LENGTH ; positie++)
{
    filename[positie] = cin.get();
    if (filename[positie] == '\n')
    {
        filename[positie] = '\0' ;
        return true;
    }
}
return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//              
 assert (inputfile.is_open());
//                                                                                                         
for(int x = 0 ; x < ROWS; x++)
{
    for(int y = 0; y < COLUMNS ; y++)
    {
        if(x==0  || y==0 || x == ROWS-1 || y==COLUMNS-1)
        universe[x][y] = Dead;
        else
        {
           char a = inputfile.get();
            if (a==DEAD)
                universe [x][y] = Dead;
            else if (a == LIVE)
                universe [x][y] = Live;
            else return false;
        }
    }
        if (!(x == 0 || x == ROWS-1))
            inputfile.get();
}
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//                
assert(true);
//                                                      
for(int x = 0 ; x < ROWS; x++)
{
    for(int y = 0; y < COLUMNS ; y++)
    {
        if (universe[x][y] == Dead )
            cout<< "." ;
        else if (universe[x][y] == Live)
            cout<< "*" ;
    }
    cout<< endl;
}
}

//                             
int neighbours (Cell universe [ROWS] [COLUMNS], int x, int y)
{
//              
assert(true);
//                                                                                              
int counter_life_cells = 0;
if (universe [x-1][y]   == Live) counter_life_cells++;
if (universe [x-1][y+1] == Live) counter_life_cells++;
if (universe [x][y+1]   == Live) counter_life_cells++;
if (universe [x+1][y+1] == Live) counter_life_cells++;
if (universe [x+1][y]   == Live) counter_life_cells++;
if (universe [x+1][y-1] == Live) counter_life_cells++;
if (universe [x][y-1]   == Live) counter_life_cells++;
if (universe [x-1][y-1] == Live) counter_life_cells++;
return counter_life_cells;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//                
assert(true);
//                                                                            
for(int x = 0 ; x < ROWS; x++)
{
    for(int y = 0; y < COLUMNS ; y++)
    {
        next[x][y] = Dead; //                                                                                    
        int counter_life_cells = neighbours(now, x, y);
        if (x != 0 && y != 0 && x != ROWS-1 && y != COLUMNS-1)
           {
             if (now[x][y] == Live && (counter_life_cells == 3 || counter_life_cells ==2))
            next[x][y] = Live;
            else if (now[x][y] == Dead && counter_life_cells == 3)
            next[x][y] = Live;
           }
    }
}
}

int main ()
{
char filename [MAX_FILENAME_LENGTH];
ifstream inputfile;
Cell universe [ROWS][COLUMNS];
Cell next [ROWS][COLUMNS];

if (!enter_filename(filename))
        return -1;
inputfile.open(filename);
read_universe_file(inputfile, universe);
show_universe (universe);
cout << endl << endl;
next_generation(universe, next);
show_universe(next);
}

