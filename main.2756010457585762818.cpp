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
const int NEIGHBOR_RANGE    = 3;                  //                                                     

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

//                                
/*
                                                                 
                                        
*/
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                                                
    assert(MAX_FILENAME_LENGTH >= 0);

    cout << "Insert filename: ";
    cin.get(filename, 80);
    string temp = filename;
    if (temp.length() <= MAX_FILENAME_LENGTH)
        return true;
    return false;
}

//                           

/*
                                                        
*/
void universe_frame (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(ROWS > 0 && COLUMNS > 0);

    for (int i = 0; i < ROWS; i++) {
        universe[i][0] = Dead;
        universe[i][COLUMNS-1] = Dead;
    }

    for (int j = 0; j < COLUMNS; j++) {
        universe[0][j] = Dead;
        universe[ROWS-1][j] = Dead;
    }
}

/*
                                                                      
                                                    
*/
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(inputfile.is_open());
    assert(ROWS > 0 && COLUMNS > 0);

    universe_frame(universe);

    char a;
    for (int i = 1; i <= NO_OF_ROWS; i++) {
        for (int j = 1; j <= NO_OF_COLUMNS; j++) {
            inputfile.get(a);
            if (a == '\n')
                inputfile.get(a);
            if (a == '.')
                universe[i][j] = Dead;
            if (a == '*')
                universe[i][j] = Live;
        }
    }
}

/*
                                                                
*/
void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (universe[i][j] == Dead)
                cout << '.';
            if (universe[i][j] == Live)
                cout << '*';
        }
        cout << endl;
    }
}

/*
                                                          
*/
int neighbors (Cell now [NEIGHBOR_RANGE][NEIGHBOR_RANGE])
{
    //               
    assert(NEIGHBOR_RANGE > 0);

    int counter = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (now[i][j] == Live)
                counter++;
        }
    }
    return counter;
}

//                             

/*
                                                                        
                        
*/
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(ROWS > 0 && COLUMNS > 0);

    universe_frame(next);

    for (int i = 1; i <= NO_OF_ROWS; i++) {
        for (int j = 1; j <= NO_OF_COLUMNS; j++) {
            Cell neighbor_arr [3][3] = {{now[i-1][j-1], now[i-1][j], now[i-1][j+1]},
                                  {now[i][j-1], now[i][j], now[i][j+1]},
                                  {now[i+1][j-1], now[i+1][j], now[i+1][j+1]}};
            int neighbor = neighbors(neighbor_arr);
            if (neighbor < 2 || neighbor > 3)
                next[i][j] = Dead;
            else if (now[i][j] == Dead && neighbor == 3)
                next[i][j] = Live;
            else
                next[i][j] = Live;
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    if (!enter_filename(filename)) {
        return -1;
    }
    Cell universe [ROWS][COLUMNS];
    Cell next_universe [ROWS][COLUMNS];
    ifstream inputfile(filename);
    if (!inputfile)
        return -1;
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << endl;
    next_generation(universe, next_universe);
    show_universe(next_universe);
}

