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
    assert(true);
    //                                
    //                                                                                                    
    cout << "Please enter a file name: ";
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        filename[i] = cin.get();
        if (filename[i] == '\n')
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
    //                                
    //                                                                                 
    char c;
    int row = 1;
    int column = 1;
    while (inputfile)
    {
        inputfile.get (c);
        if(c == '\n')
        {
            row++;
            column=1;
        }
        else
        {
            if (c == '*')
            {
                universe[row][column] = Live;
            }
            else
            {
                universe[row][column] = Dead;
            }
            column++;
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                               
    //                                                           

    for (int i = 1; i < ROWS -1; i++)
    {
        for (int j = 1; j < COLUMNS -1; j++)
        {
            if(universe[i][j] == Dead)
            {
                cout << '.';
            }
            else
            {
                cout << '*';
            }
        }
        cout << endl;
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                               
    //                                                                                                               

    for(int i = 1; i < ROWS -1; i++)
    {
        for(int j = 1; j < COLUMNS -1; j++)
        {

            Cell test = now[i][j];
            int amt_of_neighbours = (now[i-1][j] == Live) + (now[i+1][j] == Live) + (now[i][j+1] == Live) + (now[i][j-1] == Live) + (now[i+1][j+1] == Live) + (now[i+1][j-1] == Live) + (now[i-1][j-1] == Live) + (now[i-1][j+1] == Live);

            if(test == Live)
            {
                if (amt_of_neighbours < 2)
                {
                    next [i][j] = Dead;
                }
                if (amt_of_neighbours > 3)
                {
                    next [i][j] = Dead;
                }
            }
            else if (amt_of_neighbours == 3)
            {
                next [i][j] = Live;
            }
        }
    }
}

int main ()
{
    char inputname [MAX_FILENAME_LENGTH];
    enter_filename (inputname);

    Cell universe [ROWS] [COLUMNS] = { Dead };
    ifstream inputfile;
    inputfile.open(inputname);
    //                                    
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << endl << endl;
    Cell copy_of_universe [ROWS] [COLUMNS] = { Dead };
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            copy_of_universe[i][j] = universe[i][j];
        }
    }
    next_generation(copy_of_universe, universe);
    show_universe(universe);
    cout << endl << endl;
}

