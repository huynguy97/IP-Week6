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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (true);
    //              
    for(int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(filename[i]);
        if (filename [i] == '\n')
        {
            filename[i] = '\0';
            return true;
        }
    }
    //               
    //                                                                                                                                            
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open());
    //              
    char c;
    for (int i = 0 ; i < ROWS ; i++)
    {
        for(int j = 0 ; j < COLUMNS ; j++)
        {
            if (i == 0 || j == 0 || i == ROWS -1 || j == COLUMNS - 1)
            {
                universe[i][j] = Dead;
            }
            else
            {
                inputfile >> c;
                if (c == DEAD)
                {
                    universe[i][j] = Dead;
                }
                else if (c == LIVE)
                {
                    universe[i][j] = Live;
                }
            }
        }
    }
    //               
    //                                                                                                                                                     
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true);
    //              
    for (int i = 0 ; i < ROWS ; i++)
    {
        for(int j = 0 ; j < COLUMNS ; j++)
        {
            if (universe[i][j] == Dead)
            {
                cout << DEAD;
            }
            else if (universe[i][j] == Live)
            {
                cout << LIVE;
            }
        }
        cout << endl;
    }
    //               
    //                                                                                                                             
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert (true);
    //              
    int livingcells = 0;
    for (int i = 1 ; i < ROWS ; i++)
    {
        for(int j = 1 ; j < COLUMNS ; j++)
        {
            livingcells = 0;
            if (now[i+1][j+1]) { livingcells++; }
            if (now[i+1][j])   { livingcells++; }
            if (now[i+1][j-1]) { livingcells++; }
            if (now[i][j+1])   { livingcells++; }
            if (now[i][j-1])   { livingcells++; }
            if (now[i-1][j+1]) { livingcells++; }
            if (now[i-1][j])   { livingcells++; }
            if (now[i-1][j-1]) { livingcells++; }

            if (now [i][j] == Live)
            {
                if(livingcells < 2 || livingcells > 3)
                {
                    next[i][j] = Dead;
                }
                else
                {
                    next[i][j] = Live;
                }
            }
            else if (now[i][j] == Dead)
            {
                if(livingcells == 3)
                {
                    next[i][j] = Live;
                }
                else
                {
                    next[i][j] = Dead;
                }
            }
            if (i == 0 || j == 0 || i == ROWS -1 || j == COLUMNS - 1)
            {
                next[i][j] = Dead;
            }
        }
    }
    //               
    //                                                                         
}

int main ()
{
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    cout << "what file do you want to open?" << endl;
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream inputfile;
    inputfile.open(filename);
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << "this is the next generation: " << endl;
    next_generation(universe,next);
    show_universe(next);
    cout << "program done" ;
}

