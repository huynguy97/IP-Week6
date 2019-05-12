#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//                                                      
//                                                  

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
/*                
                                                                                                
                            
*/
    char c;
    cin.get(c);
    int i = 0;
    while (i < MAX_FILENAME_LENGTH - 1 && c != '\n') {
        filename[i] = c;

        cin.get(c);
        i++;
    }

    if (c == '\n') {
        filename[i] = '\0';
        return true;
    } else {
        return false;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//               
    assert(inputfile.is_open());
/*                
                                                                                                                        
                                   
                                                                       
*/
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            universe[row][column] = Dead;
        }
    }

    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int column = 1; column <= NO_OF_COLUMNS; column++) {
            char c;
            inputfile >> c;
            if (c == LIVE)
                universe[row][column] = Live;
            else if (c != DEAD)
                return false;
        }
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//               
    assert(true);
/*                
                           
*/

    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int column = 1; column <= NO_OF_COLUMNS; column++) {
            switch (universe[row][column]) {
            case Live:
                cout << LIVE;
                break;
            case Dead:
                cout << DEAD;
                break;
            }
        }
        cout << '\n';
    }
}

int count_live_neighbours(Cell universe[ROWS][COLUMNS], int row, int column)
{
//               
    assert(row >= 1 && row <= NO_OF_ROWS && column >= 1 && column <= NO_OF_COLUMNS);
/*                
                                                                                             
*/

    int live_neighbour = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = column - 1; j <= column + 1; j++) {
            if ((i != row || j != column) && universe[i][j] == Live)
                live_neighbour++;
        }
    }
    return live_neighbour;
}

void copy_universe(Cell from[ROWS][COLUMNS], Cell to[ROWS][COLUMNS])
{
//               
    assert(true);
/*                
                                                                                       
*/

    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int column = 1; column <= NO_OF_COLUMNS; column++) {
            to[row][column] = from[row][column];
        }
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//               
    assert(true);
/*                
                                                                                                          
*/
    Cell inbetween[ROWS][COLUMNS];

    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int column = 1; column <= NO_OF_COLUMNS; column++) {
            int live_neighbour = count_live_neighbours(now, row, column);

            if (now[row][column] == Live) {
                if (live_neighbour == 2 || live_neighbour == 3)
                    inbetween[row][column] = Live;
                else
                    inbetween[row][column] = Dead;
            } else {
                if (live_neighbour == 3)
                    inbetween[row][column] = Live;
                else
                    inbetween[row][column] = Dead;
            }
        }
    }

    copy_universe(inbetween, next);
}

int main ()
{

}

