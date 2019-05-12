#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>
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

    //                                
    //                                                                           

    if (strlen(filename) <= MAX_FILENAME_LENGTH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(ROWS <= 42 || COLUMNS <= 62);
    //                               
    //                                                                      
    //                                
    int k=0;
    char c;
    for (int i = 1 ; i < ROWS-1 ; i++)
    {
        for (int j = 1 ; j < COLUMNS-1 ; j++)
        {
            inputfile >> c;
            if (c == '.')
            {
                universe[i][j] = Dead;
            }
            else if (c == '*')
            {
                universe[i][j] = Live;
            }
        }
        inputfile.ignore();
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
   assert(ROWS <= 42 || COLUMNS <= 62);
    //                               
    //                                                                     
    //                                                         
    for (int row = 1 ; row < ROWS-1 ; row++)
    {
        for (int column = 1; column < COLUMNS-1; column++)
        {
            if (universe[row][column] == Dead)
            {
                cout << ".";
            }
            else
            {
                cout << "*";
            }

        }
        cout << endl;
    }
}

int around_cell (int i, int j, Cell now [ROWS][COLUMNS])
{
    //                                                                 
    //                             
    int z=0;
    for (int a=i-1 ; a <= i+1 ; a++)
    {
        for (int b=j-1 ; b <= j+1 ; b++)
        {
            z += now[a][b];
        }
    }
    z -= now[i][j];
    return z;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
      assert(ROWS <= 42 || COLUMNS <= 62);

    //                                
    //                                                                                
    //                                                                             
    //               
    int z = 0;
    for (int i = 1 ; i < ROWS ; i++)
    {
        for (int j = 1 ; j < COLUMNS ; j++)
        {
            if (now[i][j] == Dead)
            {
                z = around_cell(i, j, now);
                if (z == 3)
                {
                    next[i][j] = Live;
                }
                else
                {
                    next[i][j] = Dead;
                }
            }
            else if (now[i][j] == Live)
            {
                z = around_cell(i, j, now);
                if (z == 2 || z == 3)
                {
                    next[i][j] = Live;
                }
                else
                {
                    next[i][j] = Dead;
                }
            }

        }

    }
}

int main ()
{
    char filename [80];
    ifstream infile;
    cout << "Enter file name: ";
    cin.getline(filename, MAX_FILENAME_LENGTH);
    enter_filename(filename);
    infile.open(filename);
    Cell universe[ROWS][COLUMNS] = { Dead };
    read_universe_file(infile, universe);
    show_universe(universe);
    Cell next [ROWS][COLUMNS] = { Dead };
    next_generation(universe,next);
    cout << "\n\n";
    show_universe(next);
}

