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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    assert (true);
    //                                                                                                                        
    //           

    cout << "Enter the filename for your universe:" << endl;
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++) {
        cin.get(filename[i]);
        if (filename[i] == '\n') {
            filename[i] = '\0';
            if (filename[i] == '\0'){
            cout << endl << "Reading successful..." << endl;
            }

            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert (inputfile.is_open() && "ERROR: Check input file");
    //                                                                                                                                   

    char dot_or_star = '.';
    int row_counter = 1;
    int column_counter = 1;

    while (inputfile) {
        inputfile.get (dot_or_star);

        if (dot_or_star == '.'){
        universe [row_counter][column_counter] = Dead;
        }
        if (dot_or_star == '*'){
        universe [row_counter][column_counter] = Live;
        }
        column_counter = column_counter + 1;
        if (dot_or_star == '\n') {
            column_counter = 1;
            row_counter = row_counter + 1;
        }

    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert (true);
    //                                                                  

    for (int row_count = 0; row_count < ROWS; row_count ++){
        for (int column_count = 0; column_count < COLUMNS; column_count ++){
            if (universe [row_count] [column_count] == Live) {
                cout << '*';
            }
            if (universe [row_count] [column_count] == Dead) {
                cout << '.';
            }
        }
        cout << endl;
    }
}
int find_the_neighbours (Cell find_in_universe [ROWS][COLUMNS], int row, int column){
    assert (true);
    //                                                                                                           

    int no_of_neighbors = 0;
    for (int loop1 = row-1; loop1 <= row + 1; loop1 ++ ) {
        for (int loop2 = column -1; loop2 <= column + 1; loop2 ++){
            if (find_in_universe [loop1][loop2] == Live && !(loop1 == row && loop2 == column)){
                no_of_neighbors = no_of_neighbors + 1;
            }
        }
    }
    return no_of_neighbors ;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(true);
    //                                                                         

    int neighbours = 0;
    for (int empty_loop1 = 0; empty_loop1 < ROWS; empty_loop1 ++) {
        for (int empty_loop2 = 0; empty_loop2 < COLUMNS; empty_loop2 ++){
            next [empty_loop1][empty_loop1] = Dead;
        }
    }
    for (int row_count = 1; row_count < ROWS - 1; row_count ++){
        for (int column_count = 1; column_count < COLUMNS - 1; column_count ++){
            if (now [row_count] [column_count] == Live) {
                neighbours = find_the_neighbours(now, row_count, column_count);
                switch (neighbours){
                case 0:
                    next [row_count] [column_count] = Dead;
                    break;
                case 1:
                    next [row_count] [column_count] = Dead;
                    break;
                case 2:
                    next [row_count] [column_count] = Live;
                    break;
                case 3:
                    next [row_count] [column_count] = Live;
                    break;
                case 4:
                    next [row_count] [column_count] = Dead;
                    break;
                case 5:
                    next [row_count] [column_count] = Dead;
                    break;
                case 6:
                    next [row_count] [column_count] = Dead;
                    break;
                case 7:
                    next [row_count] [column_count] = Dead;
                    break;
                case 8:
                    next [row_count] [column_count] = Dead;
                    break;
                }
            } else {
                        neighbours = find_the_neighbours(now, row_count, column_count);
                        if (neighbours == 3){
                            next [row_count] [column_count] = Live;
                        } else {
                            next [row_count] [column_count] = Dead;
                                }
            }
        }
    }
}

int main ()
{
    char choice = '.';
    Cell the_universe [ROWS] [COLUMNS];
    Cell the_other_universe [ROWS] [COLUMNS];
    char input_arr [MAX_FILENAME_LENGTH];
    enter_filename(input_arr);
    ifstream input_file(input_arr);
    if (input_file.is_open()) {
        cout << endl << "Opening successful..." << endl;
    }
    for (int row_dead = 0; row_dead < ROWS; row_dead ++) {
        the_universe [row_dead][0] = Dead;
        the_universe [row_dead][COLUMNS-1] = Dead;
    }
    for (int column_dead = 0; column_dead < COLUMNS; column_dead ++){
            the_universe [0][column_dead] = Dead;
            the_universe [ROWS-1][column_dead] = Dead;
    }
    read_universe_file(input_file, the_universe);
    show_universe(the_universe);
    while (choice != 'n' && choice !='N') {
        cout << endl << endl << "Do you want to see the next generation? (y/n)" << endl;
        cin >> choice;
        cout << endl << endl;
        if (choice == 'y' || choice == 'Y'){
            next_generation(the_universe, the_other_universe);
            show_universe(the_other_universe);
            for (int replace_counter1 = 0; replace_counter1 < ROWS; replace_counter1 ++){
                for (int replace_counter2 = 0; replace_counter2 < COLUMNS; replace_counter2 ++){
                    the_universe [replace_counter1][replace_counter2] = the_other_universe [replace_counter1] [replace_counter2];
                }
            }
        }
        while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N') {
            cout << "Your choice is wrong. Enter another Choice:" << endl;
            cin >> choice;
            cout << endl;
            if (choice == 'y' || choice == 'Y'){
                next_generation(the_universe, the_other_universe);
                show_universe(the_other_universe);
                for (int replace_counter1 = 0; replace_counter1 < ROWS; replace_counter1 ++){
                    for (int replace_counter2 = 0; replace_counter2 < COLUMNS; replace_counter2 ++){
                        the_universe [replace_counter1][replace_counter2] = the_other_universe [replace_counter1] [replace_counter2];
                    }
                }
            }
        }
    }

}

