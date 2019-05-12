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
//                   

void copy_array(Cell universe[ROWS][COLUMNS], Cell next[ROWS][COLUMNS]) {
    //               
    assert(true);
    //                
    //                                    
    for(int i = 1; i < ROWS; i++)
        for(int j = 1; j < COLUMNS; j++)
            universe[i][j] = next[i][j];
}

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert(true);
    //                
    //                                                        
    char c = 'c';
    int i = 0;
    cout << "Enter a file name: ";
    while(c != '\n') {
        cin.get(c);
        if(c == '\n')
            filename[i] = '\0';
        else if (i < MAX_FILENAME_LENGTH && c != '\n')
            filename[i] = c;
        else {
            cout << "File name is too long.";
            return false;
        }
        i++;
    }
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                
    //                                                    
    char c = 'c';
    cout << "Initial universe: " << endl;
    for(int i = 0; i < NO_OF_ROWS; i++) {
        for(int j = 0; j < NO_OF_COLUMNS; j++) {
                inputfile.get(c);
                if(c == '\n')
                    inputfile.get(c);
                else if(c == DEAD)
                    universe[i][j] = Dead;
                else
                    universe[i][j] = Live;
        }
    }
    if(inputfile.is_open())
        return true;
    else {
        cout << "Couldn't open universe file." << endl;
        return false;
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                
    //                                                        
    for(int i = 1; i < NO_OF_ROWS; i++) {
        for(int j = 1; j < NO_OF_COLUMNS; j++)
            if(universe[i][j] == Live)
                cout << LIVE;
            else
                cout << DEAD;
        cout << endl;
    }
}

int live_adjecent_cells (Cell universe [ROWS] [COLUMNS], int a, int b){
    //               
    assert(a >= 1 && b >= 1);
    //                
    //                                            
    int alive = 0;
    if (universe [a-1][b] == Live)
        alive++;
    if (universe [a][b-1] == Live)
        alive++;
    if (universe [a-1][b-1] == Live)
        alive++;
    if (universe [a+1][b] == Live)
        alive++;
    if (universe [a][b+1] == Live)
        alive++;
    if (universe [a+1][b+1] == Live)
        alive++;
    if (universe [a-1][b+1] == Live)
        alive++;
    if (universe [a+1][b-1] == Live)
        alive++;
    return alive;
}
//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert (true);
    //                
    //                                    
    for(int i = 1; i < NO_OF_ROWS; i++) {
        for(int j = 1; j < NO_OF_COLUMNS; j++){
            int alive = live_adjecent_cells(now, i, j);
            if (now[i][j] == Live)
                switch (alive){
                case 0:
                case 1:
                    next[i][j] = Dead;
                    break;
                case 2:
                case 3:
                    next[i][j] = Live;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    next[i][j] = Dead;
                    break;
                }
            else if (alive == 3)
                next[i][j] = Live;
            else
                next[i][j] = now[i][j];
        }
    }
    cout << endl;
    cout << "Next generation: " << endl;
    show_universe(next);
    copy_array(now, next);
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH] = {};
    ifstream inputfile;
    Cell universe [ROWS][COLUMNS] = {{}, {}};
    Cell next [ROWS][COLUMNS] = {{}, {}};
    int generations = 0;
    if(enter_filename(filename))
        inputfile.open(filename);
    cout << "Enter number of generations: ";
    cin >> generations;
    if(read_universe_file(inputfile, universe)) {
        show_universe(universe);
        for(int i = 0; i < generations; i++)
            next_generation(universe, next);
    }
    return 0;
}

