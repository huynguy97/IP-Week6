/*                                         */

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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert(true);
    //                
    //                                                       
    //                
    int last_character = 0;

    for (int i = 0; i < MAX_FILENAME_LENGTH; i++) {
		if (int(filename[i] != 0)) {
			last_character++;
		}
		else {
			filename[last_character] = '\0';
			i = MAX_FILENAME_LENGTH;
		}
	}

    /*                                           
	                                            
		                          
			                                                       
	 
    */

	if (last_character < MAX_FILENAME_LENGTH){
        return true;
	}
	else {
        return false;
	}
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());
    //                
    //                                                
    //               
    int rows = 0, columns = 0;
    char c;

    for (int index_rows = 0; index_rows < ROWS; index_rows++){
        for (int index_columns= 0; index_columns < COLUMNS; index_columns++){
            if (index_rows == 0){
                universe[index_rows][index_columns] = Dead;
            }
            else if (index_rows == 41){
                universe[index_rows][index_columns] = Dead;
            }
            else if (index_columns == 0){
                universe[index_rows][index_columns] = Dead;
            }
            else if (index_columns == 61){
                universe[index_rows][index_columns] = Dead;
            }
            else {
                inputfile.get(c);
                while (inputfile && (int(c) != 42 && int(c) != 46)){
                    inputfile.get(c);
                }
                //                       
                if (c == 46){
                    universe[index_rows][index_columns] = Dead;
                }
                else if (c == 42){
                    universe[index_rows][index_columns] = Live;
                }
            }
            columns++;
        }
        if (columns != 62){
            return false;
        }
        else {
            rows++;
            columns = 0;
        }
    }
    if (rows == 42){
        return true;
    }
    else{
        return false;
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                      
    //               
    for (int index_rows = 0; index_rows < ROWS; index_rows++){
        for (int index_colums = 0; index_colums < COLUMNS; index_colums++){
            if (universe[index_rows][index_colums] == Dead){
                cout << '.';
            }
            else if (universe[index_rows][index_colums] == Live){
                cout << '*';
            }
        }
        cout << "\n";
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                
    //                                                                    
    //                                            
    //               
    for (int index_rows = 0; index_rows < ROWS; index_rows++){
        for (int index_columns= 0; index_columns < COLUMNS; index_columns++){
            //                           
            if (index_rows == 0){
                next[index_rows][index_columns] = Dead;
            }
            //                          
            else if (index_rows == 61){
                next[index_rows][index_columns] = Dead;
            }
            //                              
            else if (index_columns == 0){
                next[index_rows][index_columns] = Dead;
            }
            //                             
            else if (index_columns == 61){
                next[index_rows][index_columns] = Dead;
            }
            //                             
            else {
                int current_cell = now[index_rows][index_columns];
                int adjusted_row = 0;
                int adjusted_column = 0;
                int neighbours_reset = 0;
                int alive_neighbours = 0;

                //                              
                for(int neighbour_rows = 0; neighbour_rows < 3; neighbour_rows++){
                    for(int neighbour_colums = 0; neighbour_colums < 3; neighbour_colums++){
                        if (neighbour_rows == 0){
                            adjusted_row = index_rows-1;
                        }
                        else if (neighbour_rows == 1){
                            adjusted_row = index_rows;
                        }
                        else if (neighbour_rows == 2){
                            adjusted_row = index_rows + 1;
                        }

                        if (neighbour_colums == 0){
                            adjusted_column = index_columns-1;
                        }
                        else if (neighbour_colums == 1){
                            adjusted_column = index_columns;
                        }
                        else if (neighbour_colums == 2){
                            adjusted_column = index_columns + 1;
                        }
                        //                                                      
                        if ((index_rows == adjusted_row) &&
                            (index_columns == adjusted_column)){
                                alive_neighbours += 0;
                        }
                        //                                
                        else {
                            if (now[adjusted_row][adjusted_column] == Dead){
                                alive_neighbours += 0;
                            }
                            else if (now[adjusted_row][adjusted_column] == Live){
                                alive_neighbours += 1;
                            }
                        }
                        neighbours_reset++;
                    }
                    neighbours_reset++;
                    if (neighbours_reset == 9){
                        neighbours_reset = 0;
                        alive_neighbours = 0;
                    }
                }
                //                                                     
                //                                 
                if (current_cell == Live && alive_neighbours < 2){
                    next[index_rows][index_columns] = Dead;
                }
                //                                                             
                //                 
                else if (current_cell == Live && (alive_neighbours == 2
                                                  || alive_neighbours == 3)){
                    next[index_rows][index_columns] = Live;
                }
                //                                                            
                //                
                else if (current_cell == Live && alive_neighbours > 3){
                    next[index_rows][index_columns] = Dead;
                }
                //                                                             
                //                                                              
                else if(current_cell == Dead && alive_neighbours == 3){
                    next[index_rows][index_columns] = Live;
                }
            }
        }
    }
}

void copy_array(Cell universe[ROWS][COLUMNS], Cell next[ROWS][COLUMNS]){
    //              
    assert(true);
    //                
    //                                                                        
    for (int index_rows = 0; index_rows < ROWS; index_rows++){
        for (int index_columns = 0; index_columns < COLUMNS; index_columns++){
            universe[index_rows][index_columns] = next[index_rows][index_columns];
        }
    }
}

int main ()
{
    //                                  
    Cell universe[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];
    char filename_input[MAX_FILENAME_LENGTH];
    char run_program;
    int steps;

    //       
    cout << "Enter a filename: ";
    cin >> filename_input;
    bool correct_filename = enter_filename(filename_input);
    cout << "The filename is smaller than 80 characters is: " << correct_filename << endl;

    //       
    string filename(filename_input);
    ifstream inputfile (filename.c_str());
    bool correct_universe = read_universe_file(inputfile, universe);
    if (correct_universe){
        show_universe(universe);

        //       
        next_generation(universe, next);
        cout << endl;
        show_universe(next);

        //                                                                      
        cout << "Would you like to run multiple steps forward?(y/n) ";
        cin >> run_program;

        if (run_program == 'y'){
            cout << "Enter the amount of steps you wish to run: ";
            cin >> steps;
            while(steps != 0){
                copy_array(universe, next);
                next_generation(universe,next);
                show_universe(next);
                cout << endl;
                steps--;
            }
        }
        else {
            cout << "Program terminated." << endl;
        }
    }
    else {
        cout << "The entered universe is incorrect." << endl;
    }
}

