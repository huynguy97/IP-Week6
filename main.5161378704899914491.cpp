//                                                      
//                                                      

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
    //                             

    //                
    //                                                                                     

    cout << "Please enter a filename:" << endl;
    cin.getline(filename, MAX_FILENAME_LENGTH);
    string a(filename);

    if (a.length() <= MAX_FILENAME_LENGTH)
    {
        return true;
    }

    cout << "ERROR: The filename is too long!" << endl;
    return false;
}

//                           

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    //                                                                        
    //                       

    //                 
    //                                                                        
    //                                    

    if (inputfile.is_open())
    {
        for(int i = 1; i <= ROWS-2; i++)
        {
            for(int j = 1; j <= COLUMNS-2; j++)
            {
                char c;
                inputfile >> c;
                if (c == '*')
                {
                    universe[i][j] = Live;
                }
            }
        }
        return true;
    }
    return false;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    //                             

    //                 
    //                                     

    for (int i = 0; i <= ROWS-1; i++)
    {
        for (int j = 0; j <= COLUMNS-1; j++)
        {
            if (universe[i][j] == Dead)
            {
                cout << '.';
            }
            else
            {
                cout << '*';
            }
            if (j == COLUMNS-1)
            {
                cout << endl;
            }
        }
    }
}

int LIVE_checker (Cell now [ROWS][COLUMNS], int i, int j)
{
    //               
    assert (i >= 1 && i <= NO_OF_ROWS && j >= 1 && j <= NO_OF_COLUMNS);

    //                
    //                                                                             

    int count_LIVE = 0;
    for (int row = i-1; row <= i+1; row++)
    {
        for (int column = j-1; column <= j+1; column++)
        {
            count_LIVE += now[row][column];
        }
    }
    count_LIVE -= now[i][j];
    return count_LIVE;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    //                             

    //                
    //                                                                         
    //                                           
    for (int i = 1; i <= ROWS-2; i++)
    {
        for (int j = 1; j <= COLUMNS-2; j++)
        {
            int count_LIVE = LIVE_checker(now,i,j);
            int count_DEAD = 8-count_LIVE;

            if (now[i][j] == Live)
            {
                if (count_LIVE < 2)
                {
                    next[i][j] = Dead;
                }
                else if (count_LIVE == 2 || count_LIVE == 3)
                {
                    next[i][j] = Live;
                }
                else if (count_LIVE > 3)
                {
                    next[i][j] = Dead;
                }
            }
            else
            {
                if (count_LIVE == 3)
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
    Cell universe[ROWS][COLUMNS] = { Dead };
    Cell next [ROWS][COLUMNS] = { Dead };
    ifstream inputfile;

    enter_filename(filename);
    inputfile.open(filename);

    read_universe_file(inputfile,universe);

    cout << "The current configuration looks like:" << endl;
    show_universe(universe);

    next_generation(universe,next);
    cout << "After one iteration the configuration looks like:" << endl;
    show_universe(next);

    return 0;
}

