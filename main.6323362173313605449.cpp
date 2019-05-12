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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert(filename != NULL);
    /*              
                                                                                                                      
    */
    cout << "Please enter the filename" << endl;
    char c;
    int i = 0;
    while(c != '\n'){
        cin.get(c);
        filename[i] = c;
        i++;
    }
    for(int j = 0; j < MAX_FILENAME_LENGTH; j++){
        if(filename[j] == '\n'){
            filename[j] = '\0';
        }
    }
    return i <= MAX_FILENAME_LENGTH;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
        assert(universe != NULL);
    /*               
                                                                             
    */
    char c;
    for(int i = 0; i <= ROWS; i++){
        for(int j = 0; j <= COLUMNS; j++){
            if(j == 61){
                universe[i][j] = Dead;
            }else if(j == 0){
                universe[i][j] = Dead;
            }else if(i == 0){
                universe[i][j] = Dead;
            }else if(i == 41){
                universe[i][j] = Dead;
            }
        }
    }
    for(int row = 0; row <= NO_OF_ROWS; row++){
        for (int column = 0; column <= NO_OF_COLUMNS; column++){
            inputfile.get(c);
            if(c == '*'){
                universe[row + 1][column + 1] = Live;
            }else{
                universe[row + 1][column + 1] = Dead;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(universe != NULL);
    /*
                                                               
    */
    for(int row = 0; row < ROWS; row ++){
        for(int column = 0; column < COLUMNS; column ++){
            if(universe[row][column] == Live){
                cout << LIVE;
            }else{
                cout << DEAD;
            }
        }
        cout << '\n';
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(now != NULL && next != NULL);
    /*
                                                                                                      
    */
    for(int row = 0; row <= NO_OF_ROWS; row++){
        for(int column = 0; column <= NO_OF_COLUMNS; column++){
            int alive_surround = 0;
            for(int x = -1; x <= 1; x++){
                for(int y = -1; y <= 1; y++){
                    if(now[row + x][column + y] == Live){
                        alive_surround ++;
                    }
                }
            }
            if(now[row][column] == Live){
                alive_surround --;
            }
            Cell new_cell_state = Dead;
            if(alive_surround == 3){
                new_cell_state = Live;
            }else if(alive_surround == 2 && now[row][column] == Live){
                new_cell_state = Live;
            }
            next[row][column] = new_cell_state;
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    Cell universe[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];
    enter_filename(filename);
    ifstream inputfile;
    inputfile.open(filename);
    read_universe_file(inputfile, universe);
    inputfile.clear();
    inputfile.close();
    show_universe(universe);
    cout << '\n';
    next_generation(universe, next);
    show_universe(next);
}

