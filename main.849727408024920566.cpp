#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;

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
bool enter_filename(char filename [MAX_FILENAME_LENGTH]) {
    assert(filename);
    assert(MAX_FILENAME_LENGTH > 0);

    bool ret = false;
    char c;

    cerr << "Path to the universe statefile: ";

    //                                               
    for (int i = 0; i < MAX_FILENAME_LENGTH && !ret; i++) {
        cin.get(c);

        if (c == '\n') {
            filename[i] = '\0';
            ret = true;
        } else {
            filename[i] = c;
        }
    }

    return ret;
    /*               
                                                                         
                                                                            
                            
                                                                             
                                                                           
     */
}

//                           
bool read_universe_file(ifstream& inputfile, Cell universe [ROWS][COLUMNS]) {
    assert(inputfile.is_open());
    assert(universe);

    //                             
    int i;
    for (i = 0; i < COLUMNS; i++) {
        universe[0][i] = Dead;
        universe[ROWS-1][i] = Dead;
    }
    for (i = 1; i < ROWS-1; i++) {
        universe[i][0] = Dead;
        universe[i][COLUMNS-1] = Dead;
    }

    //                    
    char c;
    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int col = 1; col <= NO_OF_COLUMNS+1; col++) {
            if (!inputfile) {
                cerr << "Malformed input: Unexpected EOF" << endl;
                return false;
            }

            inputfile.get(c);
            if (inputfile.fail()) {
                cerr << "Could not read from file: " << strerror(errno) << endl;
            }

            if (col == NO_OF_COLUMNS+1) {
                //           
                if (c == '\r') {
                    inputfile.get(c);
                }

                if (c != '\n') {
                    cerr << endl << "Malformed input: Expected a newline at "
                        << row << "x" << col << endl;
                    return false;
                }
            } else {
                switch (c) {
                    case '*':
                        universe[row][col] = Live;
                        break;
                    case '.':
                        universe[row][col] = Dead;
                        break;
                    case '\r':
                    case '\n':
                        cerr << endl << "Malformed input: Newline too early at "
                            << row << "x" << col << endl;
                        cerr << "Maybe the file's universe is smaller than "
                            << NO_OF_ROWS << "x" << NO_OF_COLUMNS
                            << "?" << endl;
                        return false;
                    default:
                        cerr << "Malformed input: Invalid character: ";
                        fprintf(stderr, "\\x%X", c);
                        cerr << " at " << row << "x" << col << endl;
                        return false;
                }
            }
        }
        /*                
                                                                             
                                                                                
                                                                          
                                         
         */
    }

    return true;
}

void show_universe(Cell universe [ROWS][COLUMNS]) {
    assert(universe);

    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int col = 1; col <= NO_OF_COLUMNS; col++) {
            if (universe[row][col] == Dead) {
                cout << DEAD;
            } else {
                cout << LIVE;
            }
        }
        cout << endl;
    }
    /*                
                                            
     */
}

//                             
void next_generation(Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS]) {
    assert(now);
    assert(next);

    for (int row = 1; row <= NO_OF_ROWS; row++) {
        for (int col = 1; col <= NO_OF_COLUMNS; col++) {
            int alive = 0;
            for (int irow = row - 1; irow <= row + 1; irow++) {
                for (int icol = col - 1; icol <= col + 1; icol++) {
                    if (now[irow][icol] == Live &&
                            (irow != row || icol != col)) {
                        alive++;
                    }
                }
            }

            if (now[row][col] == Live) {
                if (alive < 2) {
                    next[row][col] = Dead;
                } else if (alive > 3) {
                    next[row][col] = Dead;
                } else {
                    next[row][col] = Live;
                }
            } else {
                if (alive == 3) {
                    next[row][col] = Live;
                } else {
                    next[row][col] = Dead;
                }
            }
        }
    }
    /*                
                                                                     
     */
}

int main() {
    assert(ROWS > 0);
    assert(COLUMNS > 0);

    Cell universe_now[ROWS][COLUMNS];
    Cell universe_prev[ROWS][COLUMNS];

    char input_filename[MAX_FILENAME_LENGTH];
    ifstream input_file;

    if (!enter_filename(input_filename)) {
        cerr << "Input filename too long!" << endl;
        return 36; //             
    }

    input_file.open(input_filename);
    if (!input_file.is_open()) {
        cerr << "Could not open statefile: " << strerror(errno) << endl;
        return errno;
    }

    if (!read_universe_file(input_file, universe_now)) {
        cerr << "Could not parse statefile!" << endl;
        return -1;
    }

    //                                                     
    cerr << "Input newline to step forward, exit with EOF (C-d)" << endl;
    char input;
    cin.get(input);
    while (true) {
        if (cin.eof()) {
            return 0;
        }
        if (input == '\n') {
#ifdef __linux
            printf("\033[H\033[J");
#endif
            show_universe(universe_now);
            memcpy(universe_prev, universe_now, ROWS * COLUMNS * sizeof(Cell));
            next_generation(universe_prev, universe_now);
            cin.get(input);
        }
    }
}

