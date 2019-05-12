#include <iostream>
#include <fstream>
#include <cassert>

/* 
                               
                          
*/

using namespace std;

enum Cell {Dead=0, Live=1};                         //                                                                           

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
    //                                                                                 
    cout << "Enter filename (Only 80 characters allowed):\n";
    char c = 0;
    for(int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(c);
        if(c == '\n')
        {
            filename[i] = '\0';
            return true;
        }
        else
            filename[i] = c;
    }
    filename[79] = '\0';
    while(c != '\n')
        cin.get(c);
    cout << "Filename too long\n";
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());
    //               
    //                                               

    //             
    for(int i = 0; i < ROWS; i++)
    {
        universe[i][0] = Dead;
        universe[i][COLUMNS-1] = Dead;
    }
    for(int i = 1; i < COLUMNS-1; i++)
    {
        universe[0][i] = Dead;
        universe[ROWS-1][i] = Dead;
    }
    //              
    for(int i = 1; i <= NO_OF_ROWS; i++)
    {
        for(int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            char c;
            inputfile.get(c);
            if(c == '.')
                universe[i][j] = Dead;
            else
                universe[i][j] = Live;
        }
        //                
        char newline;
        inputfile.get(newline);
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //               
    //                                                      
    cout << endl;
    for(int i = 1; i < ROWS - 1; i++)
    {
        for(int j = 1; j < COLUMNS - 1; j++)
        {
            if(universe[i][j])
                cout << '*';
            else
                cout << '.';
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

    //              
    for(int i = 0; i < ROWS; i++)
    {
        now[i][0] = Dead;
        now[i][COLUMNS-1] = Dead;
    }
    for(int i = 1; i < COLUMNS-1; i++)
    {
        now[0][i] = Dead;
        now[ROWS-1][i] = Dead;
    }

    for(int i = 1; i <= NO_OF_ROWS; i++)
    {
        for(int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            int liveNeighbours =
                now[i-1][j-1] +
                now[i-1][j  ] +
                now[i-1][j+1] +
                now[i  ][j-1] +
                now[i  ][j+1] +
                now[i+1][j-1] +
                now[i+1][j  ] +
                now[i+1][j+1];

            if(now[i][j] == Live)
                next[i][j] = liveNeighbours >= 2 && liveNeighbours <= 3 ? Live : Dead;
            else
                next[i][j] = liveNeighbours == 3 ? Live : Dead;
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    while(!enter_filename(filename));

    ifstream infile(filename);
    if(!infile.is_open())
    {
        cout << "Could not open file\n";
        return 1;
    }

    Cell universe[ROWS][COLUMNS];
    read_universe_file(infile, universe);
    show_universe(universe);

    Cell omniverse[ROWS][COLUMNS];
    next_generation(universe, omniverse);

    char c;
    cin.get(c);

    show_universe(omniverse);

    return 0;
}

