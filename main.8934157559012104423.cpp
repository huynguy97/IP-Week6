//                            
//                            

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdlib.h>
#include <string.h>
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

    char next = 0;
    int num = 0;

    while(next != '\n'){
        cin.get(next);
        filename[num] = next;
        num++;
    }

    filename[num - 1] = '\0';

    return num <= MAX_FILENAME_LENGTH;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                               
    assert(inputfile.is_open());
    //                                                                                    

    char next = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if(i == 0 || i == ROWS - 1 || j == 0 || j == COLUMNS - 1){
                universe[i][j] = Dead;
            }else{
                inputfile.get(next);

                if(next == DEAD)
                    universe[i][j] = Dead;
                else
                    universe[i][j] = Live;
            }
        }
        if(!(i == 0 || i == ROWS - 1))
            inputfile.get(next);
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                                            
    assert(true);
    //                

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            cout << universe[i][j];
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

    for(int i = 1; i <= NO_OF_ROWS; i++){
        for(int j = 1; j <= NO_OF_COLUMNS; j++){

            int livingCellsCount = 0;
            for(int p = -1; p <= 1; p++)
                for(int q = -1; q <= 1; q++)
                    if(!(p == 0 && q == 0))
                        if(now[i + p][j + q] == Live)
                            livingCellsCount++;

            if(now[i][j] == Dead && livingCellsCount == 3)
                next[i][j] = Live;
            if(now[i][j] == Live &&(livingCellsCount < 2 || livingCellsCount > 3))
                next[i][j] = Dead;
        }
    }
}

int main ()
{
    cout << "Please enter a file name: ";
    char filename[MAX_FILENAME_LENGTH];
    if(!enter_filename(filename)){
        cout << "This filename is not valid.";
        exit(1);
    }

    ifstream inputfile(filename);
    if(!inputfile){
        cout << "The file has not been opened for some reason.";
        exit(1);
    }

    Cell universe[ROWS][COLUMNS];
    read_universe_file(inputfile, universe);
    show_universe(universe);

    Cell nextUniverse[ROWS][COLUMNS];
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
            nextUniverse[i][j] = universe[i][j];

    next_generation(universe, nextUniverse);
    show_universe(nextUniverse);
}

