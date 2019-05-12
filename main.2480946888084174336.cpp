#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

/*                        */

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
        assert (true);

        cout << "Enter a file name" << endl;
        cin.getline(filename, MAX_FILENAME_LENGTH);

        for (int a = 0; a < MAX_FILENAME_LENGTH; a++){
            if (filename [a] == '\n'){
                filename [a] = '\0';
                return true;
            }
        }
        return false;
}

/*                                                                                 */

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert (inputfile.is_open());

    char character;
    for (int a = 1; a <= NO_OF_ROWS; a++){
        for (int b = 1; b <= NO_OF_COLUMNS; b++){
            inputfile.get(character);
            if (character == LIVE){
                universe [a][b] = Live;
            }
            else if (character == DEAD){
                universe [a][b] = Dead;
            }
        }
        inputfile.get(character);
    }
}

/*                                                                                                  */

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert (ROWS > 0 && COLUMNS > 0);

    for (int a = 1; a < ROWS - 1; a++){
        for (int b = 1; b < COLUMNS - 1; b++){
            if (universe [a][b] == Live)
                cout << LIVE;

            else
                cout << DEAD;
        }
        cout << endl;
    }
}

/*                                      */

//                             

int Check_neighbours(Cell now [ROWS][COLUMNS], int Cell_row, int Cell_column)
{
    assert (true);

    int nr_live_neighbours = 0;

    for (int a = Cell_row - 1; a <= Cell_row + 1; a++){
        for (int b = Cell_column - 1; b <= Cell_column + 1; b++){
            if (a == Cell_row && b == Cell_column){}
            else  {
                if (now [a][b] == Live){
                    nr_live_neighbours++;
                }
            }
        }
    }
    return nr_live_neighbours;
}

/*                                                       */

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert (ROWS > 0 && COLUMNS > 0);

    for (int a = 0; a < COLUMNS; a++){
        next [0][a] = Dead;
        next [ROWS - 1][a] = Dead;
    }

    for (int b = 0; b < ROWS; b++){
        next [b][0] = Dead;
        next [b][COLUMNS - 1] = Dead;
    }

    for (int i = 1; i <= NO_OF_ROWS; i++){
        for (int j = 1; j <= NO_OF_COLUMNS; j++){
            int x = Check_neighbours (now, i, j);
            if (now [i][j] == Live){
                if (x < 2){
                    next [i][j] = Dead;
                }
                if (x == 2 || x == 3){
                    next [i][j] = Live;
                }
                if (x > 3){
                    next[i][j] = Dead;
                }
            }
            if (now [i][j] == Dead){
                if (x == 3){
                    next [i][j] = Live;
                }
                else
                    next[i][j] = Dead;
            }
        }
    }
}

/*                                                                                           */

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream inputfile;
    inputfile.open (filename);
    Cell universe [ROWS][COLUMNS];
    read_universe_file (inputfile, universe);
    Cell next [ROWS][COLUMNS];
    next_generation(universe, next);
    show_universe (next);
}

