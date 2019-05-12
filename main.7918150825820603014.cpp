#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

enum Cell {Dead=0, Live, net};                         //                                                                           

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
    assert ( MAX_FILENAME_LENGTH >= 0 );
    /*
                   
                                          
    */

    cout << "Please enter a file name including the file extension: " << endl;
    int i = 0;
    char c;
    while(c != '\n')
    {
        if(i >= 80)
        {
            cout << "Invalid file name.";
            return false;
        }
        c = cin.get();
        filename[i] = c;
        i++;
    }

    filename[i-1] = '\0';

    return true;
}

//                           
void make_padding(Cell universe [ROWS][COLUMNS]){
    //             
    assert(true);
    //              
    //                                                             
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if(i == 0 || j == 0 || i == ROWS-1 || j == COLUMNS-1){
                universe[i][j] = Dead;
            }
        }
    }
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //             
    assert(inputfile.is_open());
    //              
    //                                                                    
    make_padding(universe);
    int a = 1;

    for(string i; getline(inputfile, i); ) {
        for(int j=0; j < 60; j++){
            if(i[j] == DEAD){
                universe[a][j+1] = Dead;
            } else {
                universe[a][j+1] = Live;
            }
        }
        a++;
    }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //             
    assert(DEAD == '.' && LIVE == '*');
    //              
    //                                                     
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if(universe[i][j] == Dead)
                cout << DEAD;
            else
                cout << LIVE;
        }
        cout << endl;
    }
}

//                             
int check_neighbours(Cell n [ROWS][COLUMNS], int i, int j){
    //             
    assert(i > 0 && i < ROWS && j > 0 && j < COLUMNS);
    //              
    //                                                     
    int a = 0;
    if(n[i-1][j] == Live)
        a++;
    if(n[i-1][j-1] == Live)
        a++;
    if(n[i-1][j+1] == Live)
        a++;
    if(n[i][j+1] == Live)
        a++;
    if(n[i][j-1] == Live)
        a++;
    if(n[i+1][j-1] == Live)
        a++;
    if(n[i+1][j] == Live)
        a++;
    if(n[i+1][j+1] == Live)
        a++;

    return a;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //             
    assert(true);
    //              
    //                                                                             
    for(int i = 1; i <= NO_OF_ROWS; i++){
        for(int j = 1; j <= NO_OF_COLUMNS; j++){
            int check = check_neighbours(now, i, j);
            if(now[i][j] == Live){
                if(check != 2 && check != 3)
                    next[i][j] = Dead;
                else
                    next[i][j] = Live;
            } else if(now[i][j] == Dead){
                if(check == 3)
                    next[i][j] = Live;
                else
                    next[i][j] = Dead;
            }
        }
    }
    show_universe(next);
    cout << endl;
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);

    ifstream infile;
    infile.open(filename);

    Cell universe[ROWS][COLUMNS];
    read_universe_file(infile, universe);

    for(int i = 0; i < 2; i++){
        Cell NextU[ROWS][COLUMNS];
        NextU[ROWS][COLUMNS] = universe[ROWS][COLUMNS];
        make_padding(NextU);
        next_generation(universe, NextU);
    }
}

