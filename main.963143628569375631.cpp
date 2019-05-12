#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
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

bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                                                
    assert(MAX_FILENAME_LENGTH >=0);
    //                                                                                                                                    
    char c ='a';
    cout << "Enter file name incl file extension: " << '\n';

    int i=0;

    for(i; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(c);
        if (c == '\n')
        {
            filename[i]='\0';
            return true;
        }
        else
        {
            filename[i] = c;
        }

    }
    filename[MAX_FILENAME_LENGTH-1]='\0';
    return false;

}

//                           

Cell get_cell(char c)
{
//              
    assert (c == '.' || c == '*');
//                                                                            
    if (c=='.')
    {
        return Dead;
    }
    else if (c=='*')
    {
        return Live;
    }

}
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open ());
    //                                                                                                        
    //                                                                                                  
    char c= 'a';
    for (int j=0; j<COLUMNS ; j++)
    {
        universe[0][j] =Dead;
        universe[41][j] =Dead;

    }
    for (int i=0; i<ROWS; i++)
    {
        universe[i][0] = Dead;
        universe[i][61] = Dead;
    }
    for (int i=1; i<=NO_OF_ROWS; i++)//     
    {

        for (int j=1; j<=NO_OF_COLUMNS; j++)
        {
            inputfile >> c;
            universe[i][j]= get_cell(c);

        }
    }

    return true;

}

void show_universe (Cell universe [ROWS][COLUMNS])

{
    //                
    assert(read_universe_file);
    //                                             

    for (int i = 0; i< ROWS; i++)
    {
        for(int j=0; j< COLUMNS; j++)
        {

            if (universe[i][j] ==Dead)
            {
                cout<< '.';
            }
            else if(universe[i][j]== Live)
            {
                cout << '*';
            }

        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                 
    //                                                               

    int n = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            next[i][j] = now[i][j];
        }
    }

    for (int i=1; i<ROWS-1; i++)
    {
        for (int j=1; i<COLUMNS-1; j++)
        {
            n = 0;
            if (now[i][j-1] == Live)
            {
                n++;
            }
            if (now[i][j+1] == Live)
            {
                n++;
            }
            if (now[i-1][j-1] == Live)
            {
                n++;
            }
            if (now[i-1][j] == Live)
            {
                n++;
            }
            if (now[i-1][j+1] == Live)
            {
                n++;
            }
            if (now[i+1][j-1] == Live)
            {
                n++;
            }
            if (now[i+1][j] == Live)
            {
                n++;
            }
            if (now[i+1][j+1] == Live)
            {
                n++;
            }
            if (now[i][j]==Live)
            {
                if(n<2)
                {
                    next[i][j]=Dead;
                }

                if(n==2 || n==3)
                {
                    next[i][j] = Live;
                }
                if(n>3)
                {
                    next[i][j]=Dead;
                }
            }
            if(now[i][j]==Dead && n==3)
            {
                next[i][j]= Live;
            }

            else
            {
                next[i][j]= Dead;
            }
        }

    }

}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename( filename);
    ifstream input_file;
    //                
    input_file.open(filename);
    Cell universe[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];
    read_universe_file(input_file, universe);
    next_generation(universe, next);
    show_universe(next);
    input_file.close();

}

