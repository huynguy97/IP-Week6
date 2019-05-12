#include <iostream>
#include <fstream>  //       
#include <cassert>  //            
#include <string.h> //            
using namespace std;

//                            
//                            

enum Cell {Dead=0, Live};                        //                                                                           

const char DEAD             = '.';      	     //                                                          
const char LIVE             = '*';               //                                                          
const int NO_OF_ROWS        = 40;                //                                                                      
const int NO_OF_COLUMNS     = 60;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2; //                                                                               

const int MAX_FILENAME_LENGTH = 80;              //                                                                                   

//                                
bool enter_filename(char filename [MAX_FILENAME_LENGTH]) {
    //               
    assert(true);
    //                                                                                                                           
    cout << "Enter filename: ";
    //                                                    
    //                                                                                                                          
    cin.getline(filename, MAX_FILENAME_LENGTH);
    //                                                                                                          

    //                                            
    return MAX_FILENAME_LENGTH > strlen(filename);
}

//                           
bool read_universe_file(ifstream& inputfile, Cell universe [ROWS][COLUMNS]) {
    //                
    assert(true);
    //                                                                                
    char a;
    //                                                                                        
    for(int y = 0; y < NO_OF_ROWS; y++) {
        for (int x = 0; x < (NO_OF_COLUMNS+1); x++) {
            inputfile.get(a);
            if(a == DEAD) {
                universe [y+1][x+1] = Dead;
            } else if (a == LIVE) {
                universe [y+1][x+1] = Live;
            }
        }
    }
	//                                                                   
    for(int y = 0; y < ROWS; y++) {
        universe [y][0] = Dead;
        universe [y][NO_OF_COLUMNS] = Dead;
    }
    for(int x = 0; x < COLUMNS; x++) {
        universe [0][x] = Dead;
        universe [NO_OF_ROWS+1][x] = Dead;
    }

    return inputfile.is_open();
}

void show_universe(Cell universe [ROWS][COLUMNS]) {
    //                
    assert(true);
    //                                                                                
    for(int y = 0; y < (ROWS); y++) {
        for(int x = 0; x < (COLUMNS-1); x++) {
            switch(universe [y][x]) {
            case Dead:
                cout << DEAD; break;
            case Live:
                cout << LIVE; break;
            }
        }
        cout << "\n";
    }
}

//                             
void next_generation(Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS]) {
    //                
    assert(true);
    //                                                                                                                                 
    int neighbor_count = 0;
    //                                                        
    //                                        
    for (int y = 1; y < (ROWS-1); y++) {
        for (int x = 1; x < COLUMNS; x++) {
            neighbor_count = 0;
            //                                                                                                           
            for(int b = y-1; b <= y+1; b++) {
                for(int a = x-1; a <= x+1; a++) {
                    if(now [b][a] == Live) {
                        neighbor_count++;
                    }
                }
            }
            //                                                                                                            
            if(now [y][x] == Live) {
                neighbor_count--;
            }
            //                                                            
            if(neighbor_count == 3) {
                next [y][x] = Live;
            } else if(neighbor_count == 2) {
                next [y][x] = now [y][x];
            } else {
                next [y][x] = Dead;
            }
        }
    }
}

int main() {
    char filename [MAX_FILENAME_LENGTH];
    Cell universe [ROWS][COLUMNS];
    Cell next_universe [ROWS][COLUMNS];
    ifstream inputfile;

    if(!enter_filename(filename)) {
        cout << "\nERROR. Filename too long.";

        return -1;
    }

    inputfile.open(filename);

    if(!read_universe_file(inputfile, universe)) {
        cout << "\nERROR. File couldn't be read.";

        return -1;
    }
    show_universe(universe);

    cout << "\n";

    next_generation(universe,next_universe);
    show_universe(next_universe);

    inputfile.clear();
    inputfile.close();

    if(inputfile.is_open()) {
        cout << "\nERROR. File wasn't closed properly.";

        return -1;
    }

    return 0;
}

