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
    /*               
       */
    assert (true);
    /*                
                                                           
                                                                                         
                                                                                 
       */
    cout << "Enter the file name: ";

    for (int i = 0; i < MAX_FILENAME_LENGTH; ++i)
    {
        cin.get(filename[i]);
        if (filename[i] == '\n') {
            filename[i] = '\0';
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    /*               
                                 
       */
    assert(inputfile.is_open());
    /*                
                                                                                
                                                                                                            
       */
    char c;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
                if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1)
                    universe[i][j] = Dead;
                else {
                    inputfile >> c; //                  
                    universe[i][j] = (c == DEAD ? Dead : Live);
                }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    /*               
       */
    assert(true);
    /*                
                                                         
                                                         
                                                  
       */
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (universe[i][j] == Dead)
                cout << DEAD;
            else
                cout << LIVE;

            if (j == COLUMNS - 1)
                cout << '\n';
        }
    }
}

//                             
int get_live_neighbours(int i, int j, Cell now[ROWS][COLUMNS])
{
    /*               
                                         
                                            
       */
    assert(i >= 0 && i < ROWS || j >= 0 && j < COLUMNS);
    /*                
                                                
       */
    int live_neighbours = 0;

    for (int k = i - 1; k < i + 1; ++k) {
        for (int l = j - 1; l < j + 1; ++l) {
            if (now[k][l] == Live)
                live_neighbours++;
        }
    }
    return live_neighbours;
}

void next_generation (Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
    /*               
       */
    assert(true);
    /*                
                                                                                               
                                       
                                   
       */
    for (int i = 1; i <= ROWS; ++i) {
        for (int j = 1; j <= NO_OF_COLUMNS; ++j) {
            int live_neighbours = get_live_neighbours(i,j,now);

            if (now[i][j] == Dead)
            {
                if (live_neighbours < 2)
                    next[i][j] = Dead;
                else if (live_neighbours > 3)
                    next[i][j] = Dead;
                else
                    next[i][j] = Live;
            }
            else
            {
                if (live_neighbours == 3)
                    next[i][j] = Dead;
                else
                    next[i][j] = Live;
            }
        }
    }
}

int main ()
{
    char user_filename[MAX_FILENAME_LENGTH];

    while(!enter_filename(user_filename))
    {
        enter_filename(user_filename);
    }

    ifstream inputfile;
    inputfile.open(user_filename);

    Cell now[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];

    read_universe_file(inputfile, now);
    next_generation(now, next);
    show_universe(next);
}

