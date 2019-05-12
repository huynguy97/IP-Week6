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
    assert(MAX_FILENAME_LENGTH > 0);
    //                                                              
    int i = 0;
    while(filename[i]) //                                                 
    {
        if(filename [i] == '\n') //                        
        {
            filename [i] = '\0';
        }
        else
            i++;
    }
    return (i < MAX_FILENAME_LENGTH); //                                           
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile);
    //                                                                              

    char a;
    int i = 0;
    inputfile >> a;
    for(int row = 0; row < ROWS; row++) //                                         
        {
            for(int column = 0; column < COLUMNS; column++)
            {
                if(row==0 || row==ROWS-1 || column==0 ||column==COLUMNS-1) //                          
                {
                    universe[row][column] = Dead;
                    i++;
                }
                else if(inputfile)
                {
                    switch(a) //                                 
                    {
                        case '.': universe[row][column] = Dead; break;
                        case '*': universe[row][column] = Live; break;
                    }
                    inputfile >> a; //                                           
                    i++;
                }
            }
        }
    return (i == ROWS*COLUMNS);
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(true);
    //                                  
    for(int row = 0; row < ROWS; row++)
        {
            for(int column = 0; column < COLUMNS; column++)
            {
                switch(universe[row][column])//                              
                {
                    case Dead: cout << '.'; break;
                    case Live: cout << '*'; break;
                }
            }
            cout << endl; //           
        }
}

//                             
int number_of_neighbors(Cell now [ROWS][COLUMNS], int row, int column)
{
    //              
    assert(true);
    //                                                    
    int number = now[row+1][column-1] + now[row+1][column] + now[row+1][column+1] + now[row][column-1] + now[row][column+1] + now[row-1][column-1] + now[row-1][column] + now[row-1][column+1];
    return number;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                               
    int neighbors;
    for(int row = 0; row < ROWS; row++)
        {
            for(int column = 0; column < COLUMNS; column++)
            {
                if(row==0 || row==ROWS-1 || column==0 ||column==COLUMNS-1) //                   
                {
                    next[row][column] = now[row][column];
                }
                else
                {
                    neighbors = number_of_neighbors(now,row,column); //                                                              
                    if(neighbors < 2 || neighbors > 3)
                        next[row][column] = Dead;
                    else if(neighbors == 2)
                        next[row][column] = now[row][column];
                    else
                        next[row][column] = Live;
                }
            }
        }
}

int main ()
{
    ifstream input_file;
    char file_name [999];
    Cell in_universe [ROWS][COLUMNS];
    Cell new_universe [ROWS][COLUMNS];

    cout << "Enter an name for the input file (with extension)..."<<endl;
    cin.getline(file_name,999);
    if(!enter_filename(file_name)) //                                 
    {
        cout << "The entered file name is too long" << endl;
    }
    else
    {
            ifstream input_file(static_cast<string>(file_name).c_str());
            if(!input_file) //                          
            {
                cout << "The file can not be opened" << endl;

            }
            else
            {
                if(read_universe_file(input_file, in_universe)) //                                                             
                {
                    show_universe(in_universe);
                    cout << endl;
                    next_generation(in_universe,new_universe);
                    show_universe(new_universe);

                }
                else
                {
                    cout << "The universe can not be loaded" << endl;
                }

            }
    }

}

