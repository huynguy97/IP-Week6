#include <iostream>
#include <fstream>
#include <cassert>

//                                                                        

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

    char a;
    int a_count = 0;

    cout << "Please enter a file (.txt): ";

    for(int i = 0 ; a != '\n' ; i++)
    {
        cin.get(a);
        filename[i] = a;
        a_count = i;
    }

    filename [a_count] = '\0';

    if (a_count > MAX_FILENAME_LENGTH)
    {
        cout << "file name is too long.";
        return false;
    }

    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(inputfile.is_open());
    //                                                                                                                                                 
    char c;

    inputfile >> c;
    while (inputfile)
    {
        for (int row = 1; row <= NO_OF_ROWS; row++)
        {
            for (int col = 1; col <= NO_OF_COLUMNS; col++ )
            {
                if (c == '*')
                {
                    universe[row][col] = static_cast<Cell>(1);
                }

                else if (c == '.')
                {
                    universe[row][col] = static_cast<Cell>(0);
                }

                else
                {
                    return false;
                }

                inputfile >> c;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                 
    //                                        

    for (int row = 1; row <= NO_OF_ROWS; row++)
    {

        for (int col = 1; col <= NO_OF_COLUMNS; col++ )
        {

            if (universe [row][col] == 0)
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

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //               
    //                                                                  

    int row;
    int col;
    int neighbours = 0;

    for (int row = 1; row <= NO_OF_ROWS; row++)
    {
        for (int col = 1; col <= NO_OF_COLUMNS; col++)
        {
            neighbours = (now[row-1][col-1] + now[row-1][col] + now[row-1][col+1] + now[row][col-1] + now[row][col+1] + now[row+1][col-1] + now[row+1][col] + now[row+1][col+1]);

            if (now[row][col] == 0)
            {
                if (neighbours == 3)
                {
                    next[row][col] = static_cast<Cell>(1);
                }
                else
                {
                    next[row][col] = static_cast<Cell>(0);
                }
            }
            else
            {
                if (neighbours < 2)
                {
                    next[row][col] = static_cast<Cell>(0);
                }
                else if (neighbours > 3)
                {
                    next[row][col] = static_cast<Cell>(0);

                }
                else if (1 < neighbours < 4)
                {
                    next[row][col] = static_cast<Cell>(1);
                }

            }
        }
    }
}

int main ()
{
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    char filename [MAX_FILENAME_LENGTH];

    if(enter_filename(filename))
    {
        ifstream inputfile (filename);

        if(inputfile.is_open())
        {
            if (!read_universe_file (inputfile, universe))
            {
                cout << "the file is not eligible for the Game of Life.";
            }
            else
            {
                show_universe(universe);
                cout <<" The next generation: " <<endl;
                next_generation(universe, next);
                show_universe(next);
                inputfile.clear () ;
                inputfile.close () ;
            }
        }
        else
        {
            cout << "file does not exist.";
        }
    }
}

