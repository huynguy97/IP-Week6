/*                                                                      
                                                                                */

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
    cout << "please enter a filename"<<endl;
    char c = 'a';
    int counter = 0;
    while(c != '\n')
    {
        cin.get(c);
        filename[counter] = c;
        counter++;
        if(counter> MAX_FILENAME_LENGTH)
            return false;
    }
    filename[counter-1] = '\0';
   return true;
}

void create_universe_boundaries(Cell universe [ROWS][COLUMNS])
{
    //                       
    assert(true);
    //                                                                              
    int row=0, column=0;
    Cell value = Dead;
    for(row;row<2;row++)
    {
        for(column; column<=COLUMNS; column++)
            {
                universe[row][column] = value;
            }
    }
    column=0;
    for(row=ROWS; row>ROWS-2; row--)
    {
        for(column; column<=COLUMNS; column++)
        {
            universe[row][column] = value;
        }
    }
    column=0;
    for(row=2; row<ROWS-2; row++)
    {
        universe[row][0] = value;
        universe[row][1] = value;
        universe[row][COLUMNS] = value;
        universe[row][COLUMNS-1] = value;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                      
    assert(true);
    //                                                                                              
    string filename;
    cout << "enter a filename: " << endl;
    cin >> filename;
    inputfile.open (filename.c_str());
    if(inputfile)
    {
        cout << endl << filename << " successfully opened." << endl;
    }
    else
    {
        cout << "inputfile could not be opened." << endl;
        return false;
    }
    Cell value;
    char character;
    create_universe_boundaries(universe);
    int row = 1, column = 1;
    while (inputfile)
    {
        inputfile.get(character);
        if(character == 42 || character == 46)
        {
            if(character == 42)
            {
                value = Live;
            }
            else
            {
                value = Dead;
            }
            universe[row][column] = value;
            column++;
        }
        else
        {
            row++;
            column = 1;
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                     
    assert(true);
    //                                                    
    int row = 0, column = 0;
    while (row <= ROWS)
    {
        while(column <= COLUMNS)
        {
            if (universe[row][column] == 1)
            {

                cout << "* ";
            }
            else
            {
                cout << ". ";
            }
            column++;
        }
    row++;
    cout << endl;
    column = 0;
    }
}

int check_alive(Cell universe[ROWS][COLUMNS], int row, int column)
{
    //                     
    assert(true);
    //                                                                                                               
    int r = row-1, c = column-1, alive=0;
    for(c; c<=column+1; c++)
    {
        if(universe[r][c] == 1)
        {
            alive++;
        }
    }
    r=row;
    c=column-1;
    if(universe[r][c])
        alive++;
    c=column+1;
    if(universe[r][c])
    alive++;
    r=row+1;
    c=column-1;
    for(c; c<=column+1; c++)
    {
        if(universe[r][c] == 1)
        {
            alive++;
        }
    }
    return alive;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                      
    assert(true);
    //                                                 
    int row=2, column=2;
    create_universe_boundaries(now);
    while(row<ROWS-1)
    {
        while(column<COLUMNS-1)
        {

            if(now[row][column]==1)
            {

                if(check_alive(now, row, column) == 2 || check_alive(now, row, column) == 3)
                {
                    Cell value = Live;
                    next[row][column] = value;
                }
                else
                {
                    Cell value = Dead;
                    next[row][column] = value;
                }
            }
            else
            {
                if(check_alive(now, row, column) == 3)
                {
                    Cell value = Live;
                    next[row][column] = value;
                }
                else
                {
                    Cell value = Dead;
                    next[row][column] = value;
                }
            }
            column++;
        }
        row++;
        column=2;
        cout << endl;
    }
    create_universe_boundaries(next);
    show_universe(next);
}

int main ()
{
Cell universe[ROWS][COLUMNS];
Cell next[ROWS][COLUMNS];
ifstream infile;
read_universe_file (infile, universe);
show_universe(universe);
next_generation (universe,next);
infile.close();
}

