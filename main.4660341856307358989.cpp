#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

/*
                                                  

                                       

                                                  

                                          
                                          

                                                  
*/

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
    char c;

    int i = 0; //                 

    cout << "Enter filename (max 79 characters): ";
    do {
        cin.get(c);

        filename[i] = c;
        if (i >= MAX_FILENAME_LENGTH && c != '\n')
        {
            cout << "\nYou've entered too many characters.";
            return false;
        }
        i++;
    } while (c != '\n');

    filename[i-1] = '\0'; //                                        

    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              
    assert(inputfile.is_open());

    //                
    //                                                              

    //               
    char c;

    //                                                                          
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            if (col == 0 || col == COLUMNS-1 || row == 0 || row == ROWS-1)
            {
                //                                                                
                universe[row][col] = Dead;
            } else {
                //                                                 
                inputfile.get(c);
                if (c == DEAD)
                    universe[row][col] = Dead;
                else if (c == LIVE)
                    universe[row][col] = Live;
                else
                {
                    cout << "\nFile not correctly formatted: Unexpected character: \'" << c << "\'";
                    return false;
                }
            }
        }

        //                                                                                                                
        if (row != 0 && row != ROWS-1)
        {
            inputfile.get(c);

            if (c != '\n')
            { //                                                                                  
                cout << "\nFile not correctly formatted: Expected a new line";
                return false;
            }
        }
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(true);

    //                
    //                                      

    //               
    //                                                         
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            if (universe[row][col] == Live)
                cout << LIVE;
            else
                cout << DEAD;
        }
        cout << '\n'; //                                        
    }
}

//                             
int count_live_neighbors(int row, int col, Cell now [ROWS][COLUMNS])
{
    //              
    assert(row > 0 && col > 0 && row < ROWS-1 && col < COLUMNS-1);

    //                
    //                                                     

    //               
    int live_neighbors = 0;
    //                                                         
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x != 0 || y != 0) //                                                     
            {
                if (now[row+y][col+x] == Live)
                    live_neighbors++;
            }
        }
    }
    return live_neighbors;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert(true);

    //                
    //                                                                                     

    //               
    //                                                                              
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            if (col == 0 || col == COLUMNS-1 || row == 0 || row == ROWS-1)
            {
                //                                                                
                next[row][col] = Dead;
            } else {
                //                                                               
                int neighbors_live = count_live_neighbors(row, col, now);

                //                                                                                    
                if (neighbors_live < 2 || neighbors_live > 3)
                    next[row][col] = Dead;

                //                                                                                         
                if (neighbors_live == 2)
                    next[row][col] = now[row][col];

                //                                                                                   
                if (neighbors_live == 3)
                    next[row][col] = Live;
            }
        }
    }
}

int main ()
{
    char filename[FILENAME_MAX];

    //                      
    if (enter_filename(filename))
    {
        //              
        ifstream inputfile(filename);
        if (inputfile)
        {
            //                   
            Cell universe[ROWS][COLUMNS];
            if (read_universe_file(inputfile, universe))
            {
                cout << "\nStep 0: \n";
                show_universe(universe);

                //                                                     
                cout << "\n   ======================================================== \n";

                //                                   
                Cell new_universe[ROWS][COLUMNS];
                next_generation(universe, new_universe);

                cout << "\nStep 1: \n";
                show_universe(new_universe);
            }
			inputfile.close();
        } else {
            cout << "\nFile could not be opened.";
        }
    }
}

