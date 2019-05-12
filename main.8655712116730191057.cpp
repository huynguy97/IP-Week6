#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

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
    assert(true);
    //                                                
    cout << "What is the name of the file you want to use: \n ";
    int i = 0;
    char c;
    c = cin.get();
    while(c != '\n' && i < MAX_FILENAME_LENGTH){
        filename[i] = c ;
        i++;
        c = cin.get();
    }
    if(c!= '\n'){
        return false;
    }
    filename[i] = '\0';

    return true;
}

//                           
bool read_universe_file (ifstream& input_file, Cell universe [ROWS][COLUMNS])
{
    assert(input_file);
    //                                                
    char q;
    for ( int r =0; r < ROWS; r ++){

        for ( int c = 0; c < COLUMNS; c ++) {
            universe[r][c] = Dead;
        }

    }

for ( int r = 1; r <= NO_OF_ROWS; r ++){

    for ( int c = 1; c <= NO_OF_COLUMNS; c ++){
        input_file >> q;
        if( q == '*'){
            universe [r][c] = Live;
        }
        else if (q == '.'){
            universe [r][c] = Dead;
        }

    }

}

}

void show_universe (Cell universe [ROWS][COLUMNS]) {
    assert(universe);
    for (int r = 0; r < ROWS; r++) {

        for (int c = 0; c < COLUMNS; c++) {
            if( universe[r][c] == Dead){
                cout << DEAD;
            }
            else if (universe[r][c] == Live){
                cout << LIVE;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS] ) {
    assert(now);
    assert(next);
    //                                                
    for (int r = 1; r < NO_OF_ROWS+1; r++) {
        for (int c = 1; c < NO_OF_COLUMNS+1; c++) {
            int alive = 0;
            if (now[r - 1][c - 1] == Live) {
                alive++;
            }
            if (now[r - 1][c] == Live) {
                alive++;
            }
            if (now[r + 1][c] == Live) {
                alive++;
            }
            if (now[r - 1][c + 1] == Live) {
                alive++;
            }
            if (now[r][c - 1] == Live) {
                alive++;
            }
            if (now[r][c + 1] == Live) {
                alive++;
            }
            if (now[r + 1][c - 1] == Live) {
                alive++;
            }
            if (now[r + 1][c + 1] == Live) {
                alive++;
            }

            next[r][c] = Dead;

            if (now[r][c] == Live && alive < 2) {

                next[r][c] = Dead;
            } else if (now[r][c] == Live && (alive == 2 || alive == 3)) {

                next[r][c] = Live;
            } else if (now[r][c] == Live && alive > 3) {

                next[r][c] = Dead;
            } else if (now[r][c] == Dead && alive == 3) {

                next[r][c] = Live;
            }

        }
    }
    for (int r = 1; r < NO_OF_ROWS+1; r++) {
        for (int c = 1; c < NO_OF_COLUMNS + 1; c++) {
            now[r][c] = next [r][c];

        }
    }
}

int main ()
{

    char filename1 [MAX_FILENAME_LENGTH];
    enter_filename(filename1);
    ifstream input_file;
    input_file.open(filename1);
    Cell universe [ROWS][COLUMNS];
    read_universe_file(input_file, universe );
    show_universe(universe);

    Cell next [ROWS][COLUMNS];
    //                                

    for(int l = 0; l <= 10; l++) {
        next_generation(universe, next);
        show_universe(universe);
    }
    return 0;
}
