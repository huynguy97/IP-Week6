#include <iostream>
#include <fstream>
#include <cassert>
//                                                        
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
bool enter_filename (char filename [MAX_FILENAME_LENGTH]) {
    //               
    assert (true);
    for (int index = 0; index < MAX_FILENAME_LENGTH; index++) {
        filename[index] = cin.get();
        if (filename[index] == '\n') {
            filename[index] = '\0';
            return true;
        }
    }
    return false;

}

    //               

    //              

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert (inputfile.is_open());

    char c;
    inputfile.get(c);
    while (inputfile) {
        for (int a = 1; a < ROWS; a++) {
            for (int b = 1; b < COLUMNS; b++) {
                if (c == '.') {
                    universe[ROWS][COLUMNS] = Dead ;
                }
                else if (c == '*') {
                    universe[ROWS][COLUMNS] = Live ;
                }
                else {//                       
                    break;
                }
            }
        }
    }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    for(int a = 1; a < ROWS; a++){
        for(int b = 1; b < COLUMNS; b++){
            if(universe[ROWS][COLUMNS] == true){
                cout << LIVE;
            }
            else{
                cout << DEAD;
            }
            if(b == COLUMNS-1){
                cout << endl;
            }
        }
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    for(int a =0; a < ROWS; a++){
        for(int b = 0; b < COLUMNS; b++){next[a][b] = now[a][b];}
    }
    for(int a = 1; a < ROWS; a++){
        for(int b = 1; b < COLUMNS; b++){
            int life = 0;
            for(int c = -1; c < 2; c++){
                for(int d = -1; d < 2; d++){
                    if(!(c == 0 && d == 0)){
                        if(next[a+c][b+d]) {++life;}
                    }
                }
            }
            if(life < 2) {now[a][b] = Dead;}
            else if(life == 3){now[a][b] = Live;}
            else if(life > 3){now[a][b] = Dead;}
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    cout << "Give a file ";
    Cell universe[ROWS][COLUMNS];
    Cell now [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    enter_filename(filename);
    ifstream inputfile(filename);
    //                                                                                                                 
    //                                                                                                             
    //                                          
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << "do you want to see the next generation? (y/n) ";
    char y;
    cin >> y;
    if (y){
        next_generation(now, next);
    }
    else {
        return 0;
    }
}

