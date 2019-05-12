#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
/*
            
                            
                       
*/

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
    cout << "Please, enter a file name: ";
    int i = 0;
    char c;
    while(i < MAX_FILENAME_LENGTH && c != '\n'){
        cin.get(c);
        filename[i] = c;
        i++;
    }
    filename[i-1] = '\0';
    cout << filename << "\n";
    return c == '\n';
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile);
    /*                                                                      
                                                                                 
    */
    for(int rows = 1; rows < ROWS - 1; rows++){
        for(int col = 1; col < COLUMNS; col++){
            char c;
            inputfile.get(c);
            if (c == DEAD && c != '\n'){
                universe[rows][col] = Dead;
            }else{
                if (c == LIVE && c != '\n'){
                    universe[rows][col] = Live;
                }
            }
        }
    }
    for (int i = 0; i < COLUMNS; i++){
        universe[0][i] = Dead;
    }
    for (int i = 0; i < COLUMNS; i++){
        universe[41][i] = Dead;
    }
    for (int i = 1; i < ROWS; i++){
        universe[i][0] = Dead;
    }
    for (int i = 1; i < ROWS; i++){
        universe[i][61] = Dead;
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    /*                                                                           
                       
    */
    for(int rows = 0; rows < ROWS; rows++){
        for(int col = 0; col < COLUMNS; col++){
            if (universe[rows][col] == Dead){
                cout << DEAD;
            }else{
                if(universe[rows][col] == Live)
                cout << LIVE;
            }
        }
        cout << "\n";
    }
}

//                             

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
    assert(true);
    /*                                                                          
                                                                                 
                                                                               
                                                       
    */
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLUMNS; c++){
            next[r][c] = now[r][c];
        }
    }
    for(int r = 1; r < ROWS-1; r++){
        for(int c = 1; c < COLUMNS-1; c++){
            int live_n = 0;
            if (now[r-1][c-1] == Live)
                live_n++;
            if (now[r-1][c] == Live)
                live_n++;
            if (now[r-1][c+1] == Live)
                live_n++;
            if (now[r][c-1] == Live)
                live_n++;
            if (now[r][c+1] == Live)
                live_n++;
            if (now[r+1][c-1] == Live)
                live_n++;
            if (now[r+1][c] == Live)
                live_n++;
            if (now[r+1][c+1] == Live)
                live_n++;
            if(now[r][c] == Dead && live_n == 3)
                next[r][c] = Live;
            if(now[r][c] == Live){
                if(live_n < 2 || live_n > 3)
                next[r][c] = Dead;
            }
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);
    Cell universe[ROWS][COLUMNS];
    ifstream inputfile(filename);
    if (inputfile){
        read_universe_file(inputfile, universe);
        show_universe(universe);
    }else{
        cout << "The file could not be opened...";
    }
    Cell next_gen[ROWS][COLUMNS];
    next_generation(universe, next_gen);
    cout << "\n";
    show_universe(next_gen);
    return 0;
}

