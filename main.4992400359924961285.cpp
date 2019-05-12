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

    cout << "Enter filename:";

    char c;
    int index = 0;
    while (cin.get(c)) {
        if (index < MAX_FILENAME_LENGTH) {
            if (c == '\n') {
                filename[index] = '\0';
                break;
            } else {
                filename[index] = c;
            }
            index++;
        } else {
            if (c == '\n') {
                filename[MAX_FILENAME_LENGTH - 1] = '\0';
            } else {
                return false;
            }
        }
    }
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, char filename[MAX_FILENAME_LENGTH], Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(!inputfile.is_open());

    //               
    //                                                                                                                                                                        

    inputfile.open(filename);
    if (inputfile.is_open()) {
        for (int i = 0; i < ROWS; i++) {
            universe[i][0] = Dead;
            universe[i][COLUMNS - 1] = Dead;
        }
        for (int i = 0; i < COLUMNS; i++) {
            universe[0][i] = Dead;
            universe[ROWS - 1][i] = Dead;
        }
        for (int i = 1; i < ROWS; i++) {
            for (int j = 1; j < COLUMNS; j++) {
                char currentcell;
                inputfile.get(currentcell);
                if (currentcell != '\n') {
                    if (currentcell == DEAD) {
                        universe[i][j] = Dead;
                    } else {
                        universe[i][j] = Live;
                    }
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

int get_live_cell_neighbours(Cell universe[ROWS][COLUMNS], int row, int column) {
    //              
    assert((row > 0 && column > 0) && (row <= NO_OF_ROWS && column <= NO_OF_COLUMNS));

    //               
    //                                                                                                               

    //                         
    int livecells = 0;
    livecells += universe[row-1][column-1];
    livecells += universe[row-1][column];
    livecells += universe[row-1][column+1];
    livecells += universe[row][column-1];
    livecells += universe[row][column+1];
    livecells += universe[row+1][column-1];
    livecells += universe[row+1][column];
    livecells += universe[row+1][column+1];
    return livecells;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(true);

    //                
    //                                                                                                                            

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Cell currentcell = universe[i][j];
            if (currentcell == Dead) {
                cout << DEAD;
            } else {
                cout << LIVE;
            }
        }
        cout << endl;
    }
    cout << endl;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(true);

    //                
    //                                                                             

    for (int i = 0; i < ROWS; i++) {
        next[i][0] = Dead;
        next[i][COLUMNS - 1] = Dead;
    }
    for (int i = 0; i < COLUMNS; i++) {
        next[0][i] = Dead;
        next[ROWS - 1][i] = Dead;
    }

    for (int i = 1; i <= NO_OF_ROWS; i++) {
        for (int j = 1; j <= NO_OF_COLUMNS; j++) {
            Cell currentcell = now[i][j];
            int liveneighbours = get_live_cell_neighbours(now, i, j);
            if (currentcell == Live) {
                if (liveneighbours < 2) {
                    next[i][j] = Dead;
                } else if (liveneighbours == 2 || liveneighbours == 3) {
                    next[i][j] = Live;
                } else if (liveneighbours > 3) {
                    next[i][j] = Dead;
                }
            } else {
                if (liveneighbours == 3) {
                    next[i][j] = Live;
                } else {
                    next[i][j] = Dead;
                }
            }
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    if (enter_filename(filename)) {
        ifstream inputfile;
        Cell universe[ROWS][COLUMNS];
        if (read_universe_file(inputfile, filename, universe)) {
            show_universe(universe);
            Cell nextgen[ROWS][COLUMNS];
            next_generation(universe, nextgen);
            show_universe(nextgen);
        } else {
            cout << "File openening failed!";
        }
    } else {
        cout << "Filename too long!";
    }
    return 0;
}
