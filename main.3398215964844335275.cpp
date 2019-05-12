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
{//               
    assert(true);
/*                 
                                                                              
                    
*/
    int nameLength = 0;
    char current = filename[0];

    for(int i = 1; i < MAX_FILENAME_LENGTH; i++){
        if(current == NULL)
            return true;

        nameLength++;
        current = filename[i];
    }

    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{//               
    assert(inputfile.is_open());
/*                 
                                                                                                             
                                                         
*/
    char a;

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if(i != 0 && j != 0 && i != ROWS - 1 && j != COLUMNS - 1){
                inputfile.get(a);

                if(a == '\n')
                    inputfile.get(a);

                if(inputfile){
                    Cell currentCellState;

                    if(a == '.'){
                        currentCellState = Dead;
                    }
                    else if(a == '*'){
                        currentCellState = Live;
                    }

                    //                      
                    universe[i][j] = currentCellState;
                }
                else{
                    return false;
                }
            }
            else{
                universe[i][j] = Dead;
            }
        }
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{

//               
    assert(true);
/*                 
                                                                      
*/    cout << "\n\n" << endl;

    for(int i = 1; i < ROWS - 1; i++){
        for(int j = 1; j < COLUMNS - 1; j++){
            cout << ((universe[i][j] == 0) ? "." : "*");
        }

        cout << endl;
    }
}

int surrounding_live_count(Cell now [ROWS][COLUMNS], int row, int column){
//               
    assert(0<=row<=ROWS && 0<=column<=COLUMNS);
/*                 
                                                                                
                                        
*/
    int surrounding = 0;

    int cellsToCheck[8][2] = {
        {row - 1, column - 1},
        {row - 1, column},
        {row - 1, column + 1},
        {row, column - 1},
        {row, column + 1},
        {row + 1, column - 1},
        {row + 1, column},
        {row + 1, column + 1}
    };

    for(int i = 0; i < 8; i++){
        if(now[cellsToCheck[i][0]][cellsToCheck[i][1]] == 1)
            surrounding++;
    }

    return surrounding;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{//               
    assert(true);
/*                 
                                                                             
                                                                  
*/
    for(int i = 0; i <= ROWS - 1; i++){
        for(int j = 0; j <= COLUMNS - 1; j++){
            if(i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1)
                next[i][j] = Dead;
        }
    }

    for(int i = 1; i < ROWS - 1; i++){
        for(int j = 1; j < COLUMNS - 1; j++){
            int surroundingLiveCells = surrounding_live_count(now, i, j);

            if(now[i][j] == 0){
                next[i][j] = (surroundingLiveCells == 3) ? Live : Dead;
            }
            else{
                if(surroundingLiveCells < 2){
                    next[i][j] = Dead;
                }
                else if(surroundingLiveCells < 4){
                    next[i][j] = Live;
                }
                else{
                    next[i][j] = Dead;
                }
            }
        }
    }
}

int main ()
{
    char filenameChars[MAX_FILENAME_LENGTH];

    cout << "Enter file name" << endl;
    cin.getline(filenameChars, MAX_FILENAME_LENGTH);

    string inputFileName(filenameChars);
    ifstream stream;

    Cell universe[ROWS][COLUMNS];

    if(enter_filename(filenameChars)){
        stream.open(inputFileName.c_str());

        if(!stream.is_open())
            cout << "Could not open the file specified" << endl;

        bool validUniverse = read_universe_file(stream, universe);

        if(validUniverse)
            show_universe(universe);

        Cell next[ROWS][COLUMNS];
        next_generation(universe, next);

        show_universe(next);
    }
}

