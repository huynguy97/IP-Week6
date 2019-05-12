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
    assert(true);
    cin.getline(filename, MAX_FILENAME_LENGTH);
    //                                     
}

//                           
void initialize_universe (Cell universe [ROWS][COLUMNS])
{
    assert(true);
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            universe[i][j] = Dead;
        }
    }
    //                            
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(inputfile.is_open());
    int row = 1;
    int col = 1;
    char c;
    initialize_universe (universe);
    while (inputfile)
    {
        inputfile.get(c);
        if (c == '\n')
        {
            row++;
            col = 1;
        }
        else
        {
            if (c == DEAD)
                universe [row][col] = Dead;
            else if (c == LIVE)
                universe [row][col] = Live;
            col++;
        }
    }
    //                                                                                      
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(true);
    string s = "";
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (universe [i][j] == Dead)
                s += DEAD;
            if (universe [i][j] == Live)
                s += LIVE;
        }
        s += "\n";
    }
    cout << s;
    //                                           
}

//                             
Cell gen_next_cell (Cell now [ROWS][COLUMNS], int row, int column)
{
    assert(row > 0 && row < ROWS-1
           && column > 0 && column < COLUMNS-1);
    int neighbours = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            neighbours += now [row+i][column+j];
    neighbours -= now[row][column];
    if (neighbours == 3)
        return Live;
    if (neighbours < 2 || neighbours > 3)
        return Dead;
    return now[row][column];
    //                                                                     
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(true);
    for (int i = 1; i < ROWS-1; i++)
        for (int j = 1; j < COLUMNS-1; j++)
            next [i][j] = gen_next_cell(now,i,j);
    //                                                                   
}

int main ()
{
    ifstream input;
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);
    input.open(filename);
    Cell U [ROWS][COLUMNS];
    Cell Temp [ROWS][COLUMNS];
    read_universe_file(input,U);
    for (int i = 0; i < 100; i++)
    {
        if (i%2 == 0)
            {
                next_generation(U,Temp);
                show_universe(U);
            }
        else
            {
                next_generation(Temp,U);
                show_universe(Temp);
            }
        system("PAUSE");
    }
}

