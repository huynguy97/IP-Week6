/*
                                                                                  
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <limits>

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
bool check_valid(char text [MAX_FILENAME_LENGTH]){
    //                    
    assert(true);
    //                                                                                                 
    char illegal[8] = {'/','\\','*','\?','\"','<','>','|'}; //                                                 
    int newline = -1; //                                               
    for(int i = 0; i < MAX_FILENAME_LENGTH; i++){
        if (text[i] == '\n'){ //                                     
            newline = i; //                               
            for (int j = i; j < MAX_FILENAME_LENGTH; j++){
                text[j] = '\0'; //                                                                                  
            }
            break;
        }
    }
    if (newline == -1){ //                                                                 
        return false;
    }
    for (int i = 0; i < 8; i++){
        int j = 0;
        while (text[j] != '\n' && j <= newline){
            if (text[j] == illegal[i]){ //                                                                                                   
                return false; //                     
            }
            j++;
        }
    }
    return true; //                   
}

//                                                                                             
bool enter_filename (char filename [MAX_FILENAME_LENGTH]){
    //                     
    assert(true);
    //                                                                                                                                          
    string message = "Please enter the input file. (max length 80) Illegal characters: / \\ * \" < > |";
    cout << message << endl;
    bool valid = false;
    while (!valid){
        int i = 0;
        while (cin.get(filename[i]) && i < MAX_FILENAME_LENGTH){ //                                                                                                              
            if (filename[i] == '\n'){
                break; //                                                             
            }
            i++;
        }
        valid = check_valid(filename); //                                                                                                    
        if (!valid){ //                                                                                                
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input. " << message << endl;
        }
    }
    cout << endl; //                                    
    return true; //                                                                                                                     
}

//                           

//                                                                                                        
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS]){
    //                                                
    for (int row = 0; row < ROWS; row++){ //                       
        for (int col = 0; col < COLUMNS; col++){ //                          
            if (row == 0 || row == ROWS - 1 || col == 0 || col == COLUMNS - 1){ //                             
                assert (universe[row][col] == Dead); //                                  
            }
        }
    }
    //                                                                               
    char filename[MAX_FILENAME_LENGTH] = "";
    if (!enter_filename(filename)){ //                                     
        cout << "An unknown error has occurred." << endl << endl;
    }
    inputfile.open(filename);
    if (!inputfile.is_open()) { //                                              
        cout << "Error: Input file " << filename << " could not be opened." << endl << endl;
        return false;
    }
    cout << "The file " << filename << " has been opened successfully." << endl << endl;
    char c = '\0';
    //                                                                                                                             
    for (int row = 1; row <= NO_OF_ROWS; row++){
        for (int col = 1; col <= NO_OF_COLUMNS; col++){
            inputfile.get(c);
            if (c == DEAD){
                universe [row][col] = Dead;
            } else if (c == LIVE) {
                universe [row][col] = Live;
            } else { //                                                                  
                cout << "Error: Unexpected character found in position (" << row << ", " << col << ") of file " << filename << endl << endl;
                return false;
            }
        }
        inputfile.get(c);
        if (c != '\n'){ //                                                                                                                                                      
            cout << "Error: Row " << row << " of file " << filename << " has too many characters." << endl << endl;
            return false;
        }
    }
    return true;
}

//                                                                                                          
void show_universe (Cell universe [ROWS][COLUMNS]){
    //                                                         
    for (int row = 1; row <= NO_OF_ROWS; row++){
        for (int col = 1; col <= NO_OF_COLUMNS; col++){
            assert (universe[row][col] == Dead || universe[row][col] == Live);
        }
    }
    //                                       
    for (int row = 1; row <= NO_OF_ROWS; row++){
        for (int col = 1; col <= NO_OF_COLUMNS; col++){
            if (universe [row][col] == Dead){ //               
                cout << DEAD;
            } else { //               
                cout << LIVE;
            }
        }
        cout << endl; //                                                             
    }
    cout << endl; //                                                   
}

//                             

//                                                                                                                                
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS]){
    //                                                                                                               
    for (int row = 0; row < ROWS; row++){ //                       
        for (int col = 0; col < COLUMNS; col++){ //                          
            if (row == 0 || row == ROWS - 1 || col == 0 || col == COLUMNS - 1){ //                             
                assert (now [row][col] == Dead && next [row][col] == Dead); //                                  
            } else { //                    
                assert (now[row][col] == Dead || now [row][col] == Live);
            }
        }
    }
    //                                                           
    int live_neighbours;
    for (int row = 1; row <= NO_OF_ROWS; row++){ //                       
        for (int col = 1; col <= NO_OF_COLUMNS; col++){ //                          
            live_neighbours = 0;
            for (int offset_row = -1; offset_row <= 1; offset_row++){ //                                                                 
                for (int offset_col = -1; offset_col <= 1; offset_col++){ //                                                                                   
                    if (!(offset_row == 0 && offset_col == 0)){ //                                   
                        live_neighbours += static_cast<int>(now [row + offset_row][col + offset_col]); //                                            
                    }
                }
            }
            if (now [row][col] == Live){ //                           
                switch (live_neighbours){ //                                                                                       
                    case 0:
                    case 1:     next [row][col] = Dead;
                                break;
                    case 2:
                    case 3:     next [row][col] = Live;
                                break;
                    default:    next [row][col] = Dead;
                                break;
                }
            } else { //                          
                if (live_neighbours == 3){ //                                                                    
                    next [row][col] = Live;
                } else {
                    next [row][col] = Dead;
                }
            }
        }
    }

}

//                 
int main (){
    ifstream infile;
    Cell universe [ROWS][COLUMNS];
    Cell next_universe [ROWS][COLUMNS];
    //                                                                   
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLUMNS; col++){
            universe [row][col] = Dead;
            next_universe [row][col] = Dead;
        }
    }
    if (!read_universe_file(infile, universe)){ //                                                                                
        cout << "File could not be read." << endl;
        return -1;
    }
    cout << "Universe: Step 0" << endl;
    show_universe(universe); //                              
    next_generation(universe,next_universe);
    cout << "Universe: Step 1" << endl;
    show_universe(next_universe); //                                           
    return 0;
}

