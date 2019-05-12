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

bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //              
    assert(MAX_FILENAME_LENGTH>0);

    //                                                                                   
    //                                            
    cout << "Enter name input file including file extension" << endl;
    cin.getline(filename,99999);

    int filename_length = 0;
    while (filename[filename_length] != '\0')
    {
        ++filename_length;
    }

    if (filename_length>MAX_FILENAME_LENGTH)
    {
        cout << "Error: filename too long" << endl;
    }

    return filename_length<=MAX_FILENAME_LENGTH;
    //                                                     
}

//                           
/*
                                                                          
                                                                                          
                                           
*/
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open());

    for(int column=0;column<COLUMNS;column++)
    {
        universe[0][column] = Dead;
        universe[ROWS-1][column] = Dead;
    }

    for(int row=1; row<ROWS-1; row++)
    {
        universe[row][0] = Dead;
        universe[row][COLUMNS-1] = Dead;
        for (int column=1; column<COLUMNS-1; column++)
        {
            char c;
            inputfile >> c;
            if (c=='*')
            {
                universe[row][column]=Live;
            }
            else if (c=='.')
            {
                universe[row][column]=Dead;
            }
            /*                 
             
             */
            else
            {
                cout << "There is an error in the input file" << endl;
                return false;
            }
        }
    }

    return true;
    //                                                                               
    //                               
}

/*
                                                             
                                                                
*/
void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    //                                                                

    for(int row=1; row<ROWS-1; row++)
    {
        for (int column=1; column<COLUMNS-1; column++)
        {
            switch(universe[row][column])
            {
                case Live : cout << '*';
                    break;
                case Dead : cout << '.';
                    break;
            }
        }
        cout << endl;
    }
    cout << endl;
    //                                                                                                                    
}

//                             
/*
                                                                                             
                                                                                                 
                                                                                                  
*/
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    //                                                                

    for(int row=1; row<=NO_OF_ROWS; row++)
    {
        for (int column=1; column<=NO_OF_COLUMNS; column++)
        {
            int live_neighbours=0;
            for (int close_row=row-1;close_row<=row+1;close_row++)
            {
                for (int close_column=column-1;close_column<=column+1;close_column++)
                {
                    if (now[close_row][close_column]==Live)
                        live_neighbours++;
                }
            }
            if (now[row][column]==Live)
                live_neighbours--;
            switch(now[row][column])
            {
                case Live :
                    if (live_neighbours==2||live_neighbours==3)
                        next[row][column]=Live;
                    else
                        next[row][column]=Dead;
                    break;
                case Dead :
                    if (live_neighbours==3)
                        next[row][column]=Live;
                    else
                        next[row][column]=Dead;
                    break;
            }
        }
    }
    //                                                                                             
    //                         
}

/*
                                                                                      
                                                                                         
                                          
*/
int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    ifstream inputfile ( filename );
    Cell universe [ROWS][COLUMNS];
    Cell universe2 [ROWS][COLUMNS];

    if (!enter_filename (filename))
    {
        cout << "Program aborted because the filename is invalid." << endl ;
        return -1 ;
    }
    inputfile.open(filename);

    if (!inputfile.is_open())
    {
        cout << "Program aborted because file could not be opened." << endl ;
        return -1 ;
    }

    if (!read_universe_file(inputfile, universe))
    {
        cout << "Program aborted because the input file cannot be read." << endl ;
        return -1 ;
    }

    show_universe(universe);
    next_generation(universe,universe2);
    show_universe(universe2);
    return 0;
}

