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

char filename[MAX_FILENAME_LENGTH];

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (true);
    //                
    //                                                             
    //               

    //                               
    cout << "Please enter the name of the file you wish to open: ";
    cin.getline(filename, MAX_FILENAME_LENGTH);
    return filename;
}

//                           
int empty_horizontal_rows(Cell universe[ROWS][COLUMNS], int y)
{
    //               
    assert (y == 0 || y == 41);
    //                
    //                                                      
    //               
    int x = 0;
    while (x >= 0 && x <= 61)
    {
        universe[y][x] = Dead;
        x++;
    }
    return 0;
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open());
    //                
    //                                                                   
    //               
    char c;
    int y = 0;

    while (y <= 41)
    {
        int x = 0;
        while (x <= 61)
        {
            if (y == 0)
                universe[y][x] = Dead;
            if (x == 0)
            {
                universe[y][x] = Dead;
                x = x+1;
            }
            inputfile.get(c);
            if (c == '*' && x < 61)
            {
                universe[y][x] = Live;
            }
            else
            {
                universe[y][x] = Dead;
            }
            x++;
        }
        y++;
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true);
    //                
    //                                                        
    //                                                          
    //                             
    //               
    for (int y = 0; y <= 41; y++)
    {
        for (int x = 0; x <= 61; x++)
        {
            //                       
            if (universe[y][x] == 1)
                cout << "*";
            else
                cout << ".";
        }
        cout << "\n";
    }
}

//                             

int check(int x, int y, Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
    //               
    assert (x >= 0 && y >= 0);
    //                
    //                                      
    //                                                                       
    //               
    int counter = 0;
    if (x >= 1 && x <= 60 && y >= 1 && y <= 40)
    {
        if (now [y-1][x-1] == Live)
            counter++;
        if (now [y-1][x] == Live)
            counter++;
        if (now [y-1][x+1] == Live)
            counter++;
        if (now [y][x-1] == Live)
            counter++;
        if (now [y][x+1] == Live)
            counter++;
        if (now [y+1][x-1] == Live)
            counter++;
        if (now [y+1][x] == Live)
            counter++;
        if (now [y+1][x+1] == Live)
            counter++;
    }

    switch (counter)
    {
        case 2: next[y][x] = now[y][x]; break;
        case 3: next[y][x] = Live; break;
        default: next[y][x] = Dead; break;
    }
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert (true);
    //                
    //                                                                             
    //               
    int y = 0;
    while (y <= 41)
    {
        int x = 0;
        while (x <= 61)
        {
            check(x, y, now, next);
            x++;
        }
        y++;
    }
}

int main ()
{
    enter_filename(filename);
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    ifstream inputfile (filename);
    if (inputfile.is_open())
    {
        cout << endl << "File has been opened successfully." << endl;
    }
    else
    {
        cout << endl << "Program failed to open the file.";
    }
    read_universe_file(inputfile, universe);
    next_generation(universe, next);
    show_universe(universe);
    cout << endl << endl << endl;
    show_universe(next);
    return 0;
}

