/*                         
                       
*/
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
    assert (true);
    /*                
                                                                                                    
    */
    cout << "Enter filename: ";
    for (int a = 0; a < MAX_FILENAME_LENGTH; a++)
    {
        filename [a] = cin.get();
        if (filename[a] == '\n')
        {
            filename[a] == '\0';
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true);
    //                                           
    char h;
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
                inputfile.get(h);
                if (h == DEAD)
                {
                    universe[r][c] = Dead;
                }
                else if (h == LIVE)
                {
                    universe[r][c] = Live;
                }
                else
                {
                    return false;
                }

            }
        }
        if (r != 0 && r != ROWS-1) {
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
    assert (true);
    //              
    //                                           

    ifstream inputfile;

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    int r;
    int c;

    //                             
    assert (r < ROWS);
    assert (c < COLUMNS);
    //                                                                                           
r = ROWS;
c = COLUMNS;

int o = 0;
char h;

for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {

            if (now[r-1][c-1] = Live)
                {
                    o=o++;
                }
            if (now[r][c-1] = Live)
                {
                    o=o++;
                }
            if (now[r+1][c-1] = Live)
                {
                    o=o++;
                }
            if (now[r-1][c] = Live)
                {
                    o=o++;
                }
            if (now[r+1][c] = Live)
                {
                    o=o++;
                }
            if (now[r-1][c+1] = Live)
                {
                    o=o++;
                }
            if (now[r][c+1] = Live)
                {
                    o=o++;
                }
            if (now[r+1][c+1] = Live)
                {
                    o=o++;
                }

            if (o < 2)
                next[r][c] == Dead;
            else if (o == 2|| o==3)
                next[r][c] == Live;
            else if (o > 3)
                next [r][c] == Dead;
            else if (o == 3 && now[r][c]==Dead)
                next[r][c]=Live;
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    /*
                                         
                
                  
     
    */

    enter_filename(filename);
    ifstream inputfile;
    inputfile.open(filename);
    Cell universe [ROWS][COLUMNS];

    /*                                           
                
                  
     
    */
    read_universe_file(inputfile, universe);
    inputfile.clear();
    inputfile.close();
    show_universe(universe);
    Cell now [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    next_generation (now [ROWS][COLUMNS], next [ROWS][COLUMNS])

}

