#include <iostream>
#include <fstream>
#include <cassert>
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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert(MAX_FILENAME_LENGTH > 0 && filename);
    //                
    //                                                  
    //                                                                
    char c;
    int i = 0;
    bool foundnewline = false;

    cout << "Please enter the name of a file: ";

    while (i < MAX_FILENAME_LENGTH && !foundnewline)
    {
        cin.get(c);
        if (c == '\n')
        {
            filename[i] = '\0'; //                   
            foundnewline = true; //                             
        }
        else
            filename[i] = c;
        i++;
    }
    return foundnewline;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open() && universe);
    //                
    //                                                                                 
    //                                                            
    char c;
    for (int i = 0; i < NO_OF_ROWS; i++) //                 
    {
        for (int j = 0; j < NO_OF_COLUMNS; j++) //                    
        {
            inputfile.get(c);
            if (c == DEAD)
                universe[i+1][j+1] = Dead; //                      
            else if (c == LIVE)
                universe[i+1][j+1] = Live; //                      
            else
            {
                cout << "Error: no . or * found at [" << i << "][" << j << "]";
                return false;
            }
        }
        inputfile.get(c);
        if (c != '\n')
        {
            cout << "Error: number of columns don't match with file";
            return false;
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(universe);
    //                
    //                                                              
    //                      
    for (int i = 1; i <= NO_OF_ROWS; i++)
    {
        for (int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            if (universe[i][j] == Dead)
                cout << DEAD;
            else if (universe[i][j] == Live)
                cout << LIVE;
            else
                cout << "Error: not every item of universe if dead or live" << endl;
        }
        cout << '\n'; //                         
    }
    cout << endl;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(now && next);
    //                
    //                                                                    
    int neighbors;
    for (int i = 1; i <= NO_OF_ROWS; i++)
    {
        for (int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            neighbors = now[i-1][j-1] + now[i-1][j] + now[i-1][j+1] + now[i][j-1] + now[i][j+1] + now[i+1][j-1] + now[i+1][j] + now[i+1][j+1];
            if (neighbors < 2)
                next[i][j] = Dead;
            if (now[i][j] == Live && neighbors == 2)
                next[i][j] = Live;
            if (neighbors > 3)
                next[i][j] = Dead;
            if (neighbors == 3)
                next[i][j] = Live;
        }
    }
}

int main ()
{
    ifstream inputfile;
    ofstream outputfile;
    char filename [MAX_FILENAME_LENGTH];
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];

    enter_filename(filename);
    inputfile.open(filename);

    read_universe_file(inputfile, universe);

    next_generation(universe, next);
    show_universe(next);

    inputfile.close();
    return 0;
}

