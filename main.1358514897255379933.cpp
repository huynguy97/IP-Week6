//                                      

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
//                 
//                                                                                                                                                                                    

    int i = 0;
    char c = cin.get();
    while(c != '\n')
    {
        filename[i] = c;
        c = cin.get();
        i++;
        if(i >= MAX_FILENAME_LENGTH)
            return false;
    }

    filename[i] = '\0';
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//                
    assert (inputfile.is_open());
//                 
//                                                                                                            

    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            if(x == 0 || x == COLUMNS - 1 || y == 0 || y == ROWS - 1)
            {
                universe[y][x] = Dead;
                continue;
            }

            char cell = inputfile.get();

            //                                                                               

            switch(cell)
            {
            case DEAD:
                universe[y][x] = Dead;
                break;
            case LIVE:
                universe[y][x] = Live;
                break;
            default:
                cout << cell;
                return false;
            }
        }
        if (y != 0 && y != ROWS - 1)
            inputfile.ignore(1);
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//                
    assert (true);
//                 
//                                                                                

    for(int y = 1; y < ROWS - 1; y++)
    {
        for(int x = 1; x < COLUMNS - 1; x++)
        {
            switch(universe[y][x])
            {
            case Dead:
                cout << DEAD;
                break;
            case Live:
                cout << LIVE;
                break;
            }
            //                       
        }
        cout << endl;
    }
}

int live_cells_aroung (Cell universe [ROWS][COLUMNS], int row, int column)
{
//                
    assert (row > 0 && row < ROWS - 1 && column > 0 && column < COLUMNS - 1);
//                 
//                                                                             

    int live = 0;
    for(int y = row - 1; y <= row + 1; y++)
    {
        for(int x = column - 1; x <= column + 1; x++)
        {
            if(y == row && x == column) continue;
            live += universe[y][x];
        }
    }
    return live;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//                
    assert (true);
//                 
//                                                             

    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            if(x == 0 || x == COLUMNS - 1 || y == 0 || y == ROWS - 1)
            {
                next[y][x] = Dead;
                continue;
            }

            int livearound = live_cells_aroung(now, y, x);

            switch(livearound)
            {
            case 2:
                if(now[y][x] == Live)
                    next[y][x] = Live;
                else
                    next[y][x] = Dead;
                break;
            case 3:
                next[y][x] = Live;
                break;
            default:
                next[y][x] = Dead;
                break;

            }
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];

    cout << "Enter universe file name: ";

    if(!enter_filename(filename))
    {
        cout << "File name cannot be larger than " << MAX_FILENAME_LENGTH << " symbols\n";
        return -1;
    }

    ifstream inputfile;
    inputfile.open(filename);

    if(!inputfile)
    {
        cout << "File with file name: \"" << filename << "\" does not exist.\n";
        return -1;
    }

    Cell universe [ROWS][COLUMNS];

    if(!read_universe_file(inputfile, universe))
    {
        cout << "File \"" << filename << "\" is incorrect.";
        return -1;
    }

    cout << "Starting universe:\n";
    show_universe(universe);

    Cell new_universe[ROWS][COLUMNS];
    next_generation(universe, new_universe);

    cout << "\nUniverse after 1 step:\n";
    show_universe(new_universe);

    inputfile.close();

    if (!inputfile)
    {
        cout << "File was not closed succesfully.\n";
        return -1 ;
    }

    return 0;
}

