
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

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

    cout << "Please enter the file's name: " << endl;

    char c;

    for (int index = 0; index < MAX_FILENAME_LENGTH; ++index) {
        cin.get(c);

        if (c == '\n') {
            filename[index] = '\0';
            //                
            //                                                 
            cout << filename << endl;
            return true;

        }

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ' || c == ',' || c == '_' || c == '.') {
            filename[index] = c;
        } else {
            //                                                                                 
            do {
                cin >> c;
            } while (c != '\n');

        //                
            //                                                   
            return false;
        }
    }

    //                                                              
    do {
        cin >> c;
    } while (c != '\n');

//                
    //                                                                                                                              
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//                
    assert (inputfile.is_open());
    //                                                                

    //     
    for(int i=1; i <= NO_OF_ROWS; ++i) {
        //        
        for(int j= 1; j <= NO_OF_COLUMNS; ++j) {
            //                                               
            switch(inputfile.get()) {
                case '.':
                    universe[i][j] = Dead;
                    break;
                case '*':
                    universe[i][j] = Live;
                    break;
                default:
                    cout << "Encountered an unknown character! " << endl;

                //                                            
                    return false;
            }
        }
        if (inputfile.get() == '\r') //                                                                           
            inputfile.get();
    }

    //                               
    for(int i=0; i < COLUMNS; i++) {
        universe[0][i] = Dead;
        universe[ROWS -1][i] = Dead;
    }
    for(int i=0; i < ROWS; i++) {
        universe[i][0] = Dead;
        universe[i][COLUMNS -1] = Dead;
    }

//                                                                                              

    return true;
}

//                                     
void show_universe (Cell universe [ROWS][COLUMNS])
{
//                     

    //                                             
    for (int i=0; i <= NO_OF_ROWS; i++) {
        for (int j=0; j <= NO_OF_COLUMNS; j++) {
            //                                                                                                                                 
            if (universe[i][j] == Dead) {
                cout << DEAD;
            } else {
                cout << LIVE;
            }
        }
        cout << endl; //                                      
    }

//                                                                           
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//                     

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            if (row > 0 && col > 0 && row <= NO_OF_ROWS && col <= NO_OF_COLUMNS) {
                int n = -now[row][col]; //                                                                                         

                //                                                                                                                     
                for (int r2 = row - 1; r2 <= row + 1; ++r2) {
                    for (int c2 = col - 1; c2 <= col + 1; ++c2) {
                        n += now[r2][c2];;
                    }
                }

                //                                                  
                if (now[row][col] == Live) {
                    next[row][col] = n == 2 || n == 3 ? Live : Dead;
                } else {
                    next[row][col] = n == 3 ? Live : Dead;
                }
            } else { //                                                                                         
                next[row][col] = Dead;
            }
        }
    }

//                 
    //                                                                                      
}

int main ()
{
    //                                                        
    char fileArray[MAX_FILENAME_LENGTH];
    enter_filename(fileArray);
    string filename(fileArray);

    ifstream inputfile(filename);

    //                                                                              
    Cell universe[ROWS][COLUMNS], next[ROWS][COLUMNS];

    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << '\n';

    for(int i = 0; i <= 5; ++i) {
        //                             
        next_generation(universe, next);
        show_universe(next);
        cout << '\n';

        //                                                                     
        memcpy(universe, next, ROWS * COLUMNS * sizeof(Cell));
    }

}

