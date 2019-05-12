#include <iostream>
#include <fstream>
#include <cassert>
#include <stdlib.h>
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
//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    assert(MAX_FILENAME_LENGTH > 0);
    //                                                     
    for(int i = 0; i < MAX_FILENAME_LENGTH; i++){
        if (filename[i] == '\0')
    return true;
    }
    return false;
}
//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(inputfile.is_open() && NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);
    //                                                                      
    char c;
    for (int i = 0; i < NO_OF_ROWS; i++){
        for (int j = 0; j < NO_OF_COLUMNS; j++){
            inputfile >> c;
            if(c == LIVE)
                universe[i][j] = Live;
            if(c == DEAD)
                universe[i][j] = Dead;
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);
    //                                      
    for (int i=0; i < NO_OF_ROWS; i++){
        for (int j=0; j < NO_OF_COLUMNS; j++){
            if(universe[i][j] == Live)
                cout << LIVE;
            if(universe[i][j] == Dead)
                cout << DEAD;
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);
    //                                   
    int alive;
    for (int i=1; i <= NO_OF_ROWS; i++){
        for (int j=1; j <= NO_OF_COLUMNS; j++){

            alive = 0;
            if(now[i+1][j+1]) {alive++;}
            if(now[i+1][j]) {alive++;}
            if(now[i+1][j-1]) {alive++;}
            if(now[i][j+1]) {alive++;}
            if(now[i][j-1]) {alive++;}
            if(now[i-1][j+1]) {alive++;}
            if(now[i-1][j]) {alive++;}
            if(now[i-1][j-1]) {alive++;}

            if(now[i][j]){
                if(alive < 2 || alive > 3){
                    next[i][j] = Dead;
                }
                else
                    next[i][j] = Live;
            }
            else{
                if(alive == 3){
                    next[i][j] = Live;
                }
                else
                    next[i][j] = Dead;
            }

        }
        }
    }

int main ()
{
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    Cell now [ROWS][COLUMNS];
    char filename[MAX_FILENAME_LENGTH];
    cout << "Please enter an existing textfile under 80 characters long." << endl;
    cin.get(filename,MAX_FILENAME_LENGTH);
    ifstream inputfile(filename);
    if(enter_filename(filename)){
        read_universe_file(inputfile, universe);
        show_universe(universe);
        cout << endl;
        for (int i=0; i < NO_OF_ROWS; i++){
            for (int j=0; j < NO_OF_COLUMNS; j++){
                now[i][j] = universe[i][j];
            }
        }
        char cycle;
        cout << "Do you want to make life (y/n)"<< endl;
        cin >> cycle;
        do{
            system("ping 127.0.0.1 -n 2 > nul");
            system("cls");
            next_generation(now, next);
            show_universe(next);
            for (int i=1; i <= NO_OF_ROWS; i++){
                for (int j=1; j <= NO_OF_COLUMNS; j++){
                    now[i][j] = next[i][j];
                }
            }
        }while(cycle == 'y');

    }
}

