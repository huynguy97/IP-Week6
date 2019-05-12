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

/*                                                       
                                          
                                                           
                                                           
                      
*/
bool enter_filename (char file_name[MAX_FILENAME_LENGTH])
{
    //               
    assert(true);
    /*                  
                                                                                    
                                                                                                
                                                                                       
    */
    cout << "Please enter the name of the file you want to open." << endl;
    int counter=0;
    char input=cin.get();
    //                                                                          
    //                                                                
    while(input != '\n' && counter < MAX_FILENAME_LENGTH - 1){
        file_name[counter]=input;
        input=cin.get();
        counter++;
    }
    //                                                                             
    //                                                                          
    //                                                                 
    if(input == '\n'){
        file_name[counter]='\0';
        return true;
    } else{
        return false;
    }
}

//                                                                                 
bool read_universe_file (ifstream& input_file, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(input_file.is_open());
    /*               
                                                                            
               
    */
    char input_char;
    for(int i=1;i < ROWS-1;i++){
        for(int j=1;j < COLUMNS-1;j++){
            input_char=input_file.get();
            if(input_char == '*'){
                universe[i][j]=Live;
            } else if(input_char == '.'){
                universe[i][j]=Dead;
            } else{
                //                                                           
                return false;
            }
        }
        if(input_file.get()!='\n'){
            //                                                                                    
            //                                                             
            return false;
        }
    }
    //           
    input_file.clear();
    input_file.close();
    if(!input_file){
        //                                      
        return false;
    } else{
        return true;
    }
}

//                                                               
void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    /*               
                                                
    */
    //                                            
    for(int i=0;i < ROWS;i++){
        for(int j=0;j < COLUMNS;j++){
            if(universe[i][j] == Live){
                cout.put('*');
            } else{
                cout.put('.');
            }
        }
        cout.put('\n');
    }
    cout << endl;
}

/*                                                                                  
                                                                                       
                                    
*/
Cell calculate_next_state(Cell universe[ROWS][COLUMNS], int row_index, int column_index)
{
    //               
    assert(row_index > 0 && row_index < ROWS);
    assert(column_index > 0 && column_index < COLUMNS);
    /*                
                                                                      
                                                                                  
                                   
    */
    int amount_neighbours_alive=0;
    //                                   
    for(int i=row_index-1; i<=row_index+1; i++){
        for(int j=column_index-1; j<=column_index+1; j++){
            //                                      
            if(universe[i][j] == Live && !(i == row_index && j == column_index)){
                amount_neighbours_alive++;
            }
        }
    }
    //                                                       
    //                                                                        
    if((universe[row_index][column_index] == Live && amount_neighbours_alive == 2) || amount_neighbours_alive == 3){
        return Live;
    } else{
        return Dead;
    }
}

/*                                                                        
                                                                          
                                                                             
                                                                            
                             
*/
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    /*                
                                                                              
                                                                                    
    */
    for(int i=1;i < ROWS-1;i++){
        for(int j=1;j < COLUMNS-1;j++){
            next[i][j] = calculate_next_state(now, i, j);
        }
    }
}

/*                                                                                 
                                                                                  
*/
void make_dead (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    /*                  
                                         
    */
    for(int i=0;i < ROWS;i++){
        for(int j=0;j < COLUMNS;j++){
            universe[i][j]=Dead;
        }
    }
}

//                                          
bool open_input_file (ifstream& input_file, char file_name[MAX_FILENAME_LENGTH])
{
    //                
    assert(true);
    /*                
                                                                              
                                                                                  
    */
    input_file.open(file_name);
    if(input_file.is_open()){
        return true;
    } else{
        return false;
    }
}

//                         

/*                                                                                                              
                                                                                                      
                                                 
*/
int main ()
{
    //                        
    char file_name[MAX_FILENAME_LENGTH];
    if(!enter_filename(file_name)){
        cout << "Filename entered was longer than: " << MAX_FILENAME_LENGTH << " Exiting program." << endl;
        return -1;
    }
    //                                                                                            
    Cell universe[ROWS][COLUMNS];
    make_dead(universe);
    //                                    
    ifstream input_file;
    if(!open_input_file(input_file, file_name)){
        cout << "File: " << file_name << " could not be opened. Exiting program." << endl;
        return -1;
    }
    if(!read_universe_file(input_file, universe)){
        cout << "Something went wrong when reading or closing: " << file_name << " Exiting program." << endl;
        return -1;
    }
    //               
    cout << "Printing the universe:" << endl;
    show_universe(universe);
    //                        
    Cell next_universe[ROWS][COLUMNS];
    make_dead(next_universe);
    next_generation(universe, next_universe);
    //                    
    cout << "Printing the next universe:" << endl;
    show_universe(next_universe);
}

