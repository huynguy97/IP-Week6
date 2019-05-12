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
    //             
    assert(true);
    //              
    //                    

    int currentPos = 0;
    cout << "Please enter a filename: ";
    cin.getline(filename, MAX_FILENAME_LENGTH-1);
    //                         

    for (int i=0; i<=MAX_FILENAME_LENGTH; i++){
            if (filename[i] == '\0'){
                filename[i] = '\0';
                cout << "i = " << i << endl;
                return true;
            }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              
    assert(inputfile);
    //              
    //                                                

    //                                                
    char c;

    for(int k=0; k<=COLUMNS; k++){
        universe[0][k] = Dead;
        universe[ROWS-1][k] = Dead;
    }

    for(int i=1; i<ROWS-1; i++){
        universe[i][0] = Dead;
        universe[i][COLUMNS-1] = Dead;

        for(int j=1; j<COLUMNS-1; j++){
            inputfile.get(c);
            //          

            if(c == '.'){
                universe[i][j] = Dead;
                //                             
            }
            else if(c == '*'){
                universe[i][j] = Live;
                //                             
            }
            else{
                j--;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    //             
    assert(true);
    //             
    //                                     

    for(int z=0; z<ROWS; z++){
        for(int y=0; y<COLUMNS; y++){
            if(universe[z][y] == Dead){
                cout << '.';
            }
            else if(universe[z][y] == Live){
                cout << '*';
                //                      
            }
        }
         cout << '\n';
    }
}

int count_neighbours(Cell universe [ROWS][COLUMNS], int row, int column){

    //             
    assert(true);
    //             
    //                                              

    int counter = 0;

    if(universe[row-1][column-1] == Live){
        counter++;
    }
    if(universe[row][column-1] == Live){
        counter++;
    }
    if(universe[row+1][column-1] == Live){
        counter++;
    }
    if(universe[row-1][column] == Live){
        counter++;
    }
    if(universe[row+1][column] == Live){
        counter++;
    }
    if(universe[row-1][column+1] == Live){
        counter++;
    }
    if(universe[row][column+1] == Live){
        counter++;
    }
    if(universe[row+1][column+1] == Live){
        counter++;
    }

    return counter;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    //            
    assert(true);
    //             
    //                               
    int counter;

    for(int k=0; k<=COLUMNS; k++){
        next[0][k] = Dead;
        next[ROWS-1][k] = Dead;
    }

    for (int n=1; n<ROWS-1; n++){
        next[n][0] = Dead;
        next[n][COLUMNS-1] = Dead;
        for(int m=1; m<COLUMNS-1; m++){
            counter = count_neighbours(now, n, m);
            cout << counter;
            if(now[n][m] == Live){
                if(counter < 2 || counter > 3) next[n][m] = Dead;
                else next[n][m] = Live;
            }
            else{
                if(counter == 3) next[n][m] = Live;
                else next[n][m] = Dead;
            }
        }
    }

}

int main ()
{

    //     
    //                        
    //                      

    ifstream inputfile;
    Cell universe [ROWS][COLUMNS];
    Cell next_gen [ROWS][COLUMNS];

    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);
    inputfile.open(filename);
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout << "\n-------------------------------------------------\n" << endl;
    next_generation(universe, next_gen);
    show_universe(next_gen);
}

