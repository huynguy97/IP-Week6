#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//                   
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
    //              
    //                                                                              
    string fname;
    cout << "Enter file name: ";
    cin >> fname;
    assert(fname.size() < MAX_FILENAME_LENGTH);
    for (int i = 0; i < fname.size(); i++){
        filename[i] = fname[i];
    }
    filename[fname.size()] = '\0';
    return fname.size() < MAX_FILENAME_LENGTH;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(inputfile.is_open());
    //               
    //                                                                               
    char c;
    int row = 1;
    int column = 1;
    inputfile.get(c);
    while(inputfile){
        if(c == '\n') {
            row++;
            column = 1;
        } else if (c == '*') {
            universe[row][column] = Live;
        } else if (c != '.') {
            cout << row << " " << column << " " << c << endl;
            assert(false);
        }
        column++;
        inputfile.get(c);
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(true);
    //                                                                              
    for(int i = 1; i < ROWS-1; i++){
        for (int j = 1; j < COLUMNS-1; j++){
            if(universe[i][j] == Dead){
                cout << DEAD;
            } else if (universe[i][j] == Live) {
                cout << LIVE;
            } /*      
                                                                                      
                              
             */
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(true);
    //               
    //                                                                                            
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            now[i][j] = next[i][j];
        }
    }
    for(int i = 1; i < ROWS-1; i++){
        for(int j = 1; j < COLUMNS-1; j++){
            int neighbours = (now[i+1][j] == Live) + (now[i-1][j] == Live) + (now[i][j+1] == Live) + (now[i][j-1] == Live) + (now[i+1][j+1] == Live) + (now[i-1][j-1] == Live) + (now[i+1][j-1] == Live) + (now[i-1][j+1] == Live);
            Cell cell = now[i][j];

            if (cell == Live){
                if(neighbours < 2) {
                    next[i][j] = Dead;
                } else if(neighbours > 3) {
                    next[i][j] = Dead;
                }
            } else if (cell == Dead && neighbours == 3) {
                next[i][j] = Live;
            }
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    if(enter_filename(filename)) {
        cout << filename << endl;
    }
    ifstream inputfile;
    inputfile.open(filename);
    Cell universe [ROWS][COLUMNS] = { Dead };
    Cell universeCopy [ROWS][COLUMNS] = { Dead };

    read_universe_file(inputfile, universe);
    next_generation(universeCopy, universe);
    show_universe(universe);
    return 0;
}

