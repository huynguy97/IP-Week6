#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//           
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
    assert(true);
    /*               
                                                                      
                                                                         
    */
    cout << "Enter a filename: ";
    for(int i=0; i<MAX_FILENAME_LENGTH; i++)
    {
        cin.get(filename[i]);
        if(filename[i] == '\n')
        {
            filename[i] = '\0';
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
    /*                                                                                                             
    */

    char c;
    inputfile.get(c);

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            universe[i][j] = Dead;
        }
    }

    for(int i = 0; c != '\n' ; i++)
    {
        for(int j = 0; c != '\n' ; j++)
        {
            if(c == '*')
            {
                universe[i+1][j+1] = Live;
            }
            inputfile.get(c);
        }
        inputfile.get(c);
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                                 
    //                                                  
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if(universe[i][j])
            {
                cout << "*";
            }
            else
            {
                cout << ".";
            }
        }
        cout <<"\n";
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                                
    //                                      

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            next[i][j] = Dead;
        }
    }

    for(int i = 1; i <= NO_OF_ROWS; i++)
    {
        for(int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            int live_neighbours = now[i-1][j-1] + now[i][j-1] + now[i+1][j-1] + now[i-1][j] + now[i+1][j] + now[i-1][j+1] + now[i][j+1] + now[i+1][j+1];

            if(now[i][j])
            {
                if(live_neighbours < 4 && live_neighbours > 1)
                {
                    next[i][j] = Live;
                }
            }
            else
            {
               if(live_neighbours == 3)
               {
                   next[i][j] = Live;
               }
            }
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    if(enter_filename(filename))
    {
        ifstream inputfile;
        Cell universe[ROWS][COLUMNS];
        Cell universe2[ROWS][COLUMNS];

        inputfile.open(filename);

        read_universe_file(inputfile, universe);
        show_universe(universe);
        cout << "\n";
        next_generation(universe,universe2);
        show_universe(universe2);
        inputfile.close();
    }
    else
    {
        cout << "filename is invalid";
    }

}

