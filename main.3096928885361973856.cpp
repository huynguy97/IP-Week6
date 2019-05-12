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
//                                             
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (true);
    /*                
                                                    
                                          
                                                                        
    */
    //               
    cout << "Please give the name of the file: " << endl;
    cin.get(filename,MAX_FILENAME_LENGTH);
    int i = 0;
    while(filename[i] != '\n') {
        i++;
    }
    filename[i] = '\0';
    if(i <= MAX_FILENAME_LENGTH){
        return true;
    } else {
        return false;
    }

}

//                           
//                                                     
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open());
    /*                
                                                                          
    */
    //               
    char c;
    inputfile >> c;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            if(i == 0 || i == ROWS-1 || j == 0 || j == COLUMNS-1){
                universe[i][j] = Dead;
            } else {
                switch(c) {
                    case '*': universe[i][j] = Live; break;
                    case '.': universe[i][j] = Dead; break;
                }
                inputfile >> c;
            }
        }
    }
    return true;
}

//                                     
void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true);
    /*                
                                               
    */
    //               
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            switch(universe[i][j]) {
                case Live: cout << '*'; break;
                case Dead: cout << '.'; break;
            }
        }
        cout << "\n";
    }
}

//                                         
int countneighbors(Cell now [ROWS][COLUMNS],int i,int j) {
    //               
    assert (i < ROWS && i > 0 && j < COLUMNS && j > 0);
    /*                
                               
    */
    //               
    int neighbors = 0;
    if(now[i-1][j-1] == Live) {
        neighbors++;
    }
    if(now[i-1][j] == Live) {
        neighbors++;
    }
    if(now[i-1][j+1] == Live) {
        neighbors++;
    }
    if(now[i][j-1] == Live) {
        neighbors++;
    }
    if(now[i][j+1] == Live) {
        neighbors++;
    }
    if(now[i+1][j-1] == Live) {
        neighbors++;
    }
    if(now[i+1][j] == Live) {
        neighbors++;
    }
    if(now[i+1][j+1] == Live) {
        neighbors++;
    }
    return neighbors;
}

//                             
//                              
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert (true);
    /*                
                                                                       
    */
    //               
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            next[i][j] = Dead;
        }
    }
    for(int i = 1; i < ROWS-1; i++) {
        for(int j = 1; j < COLUMNS-1; j++) {
            if(now[i][j] == Live) {
                int neighbors = countneighbors(now, i, j);
                if(neighbors == 3 || neighbors == 2) {
                    next[i][j] = Live;
                }
            }
            if(now[i][j] == Dead) {
                int neighbors = countneighbors(now, i, j);
                if(neighbors == 3) {
                    next[i][j] = Live;
                }
            }
        }
    }
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            now[i][j] = next[i][j];
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream inputfile (filename);
    Cell universe [ROWS][COLUMNS];
    Cell nextuniverse [ROWS][COLUMNS];
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << "\n";
    next_generation(universe, nextuniverse);
    show_universe(universe);
    return 0;
}

