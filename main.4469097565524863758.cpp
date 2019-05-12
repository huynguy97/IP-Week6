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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                
    assert (MAX_FILENAME_LENGTH >= 0);
    //                 
    //                                                                                                  
    //               

    cout << "Input filename: " ;
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        filename[i] = cin.get();
        if (filename [i] == '\n')
        {
            filename [i] = '\0' ;
            ifstream input_file (filename) ;
            if (input_file.is_open())
            {
                cout << "file was opened" << '\n' ;
                return true;

            }
        }
    }
    cout << "filename is too long" ;
    return false;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    //                
    //                
    //                                                                           
    //              
    char ca;
    for (int r = 0; r < ROWS; r++)
    {
        cout << "check";
        for (int c = 0; c < COLUMNS; c++)
        {
            {
                if (r==ROWS)
                    universe[0][c] = Dead;
                universe[r][c] = Dead;

                if (c==COLUMNS)
                {
                    universe[r][0] = Dead;
                    universe[r][c] = Dead;
                }
                else
                {
                    inputfile.get(ca);
                    if (ca=='*')
                    {

                        universe [r][c] = Live ;
                    }
                    if (ca=='.')
                    {
                        universe [r][c] = Dead ;
                    }
                    if (ca=='\n')
                    {
                        cout << '\n' ;
                    }
                }
            }
        }
        return true;
    }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    //                                               
    //               
    //                              
    //              

    for (int r = -1; r < ROWS; r++ )
    {
        cout << '\n' ;
        for (int c = -1; c < COLUMNS; c++)
        {
            cout << universe[r][c];

        }

    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    //                                      
    //               
    //                                                                       
    //              
    for (int r = 0; r < ROWS; r++)
    {

        for (int c = 0; c < COLUMNS; c++)
        {

            int i = 0 ;

            if (now [r-1][c-1]== Live)
            {
                i++;
            }
            if (now [r-1][c]== Live)
            {
                i++;
            }
            if (now [r-1][c+1]== Live)
            {
                i++;
            }
            if (now [r][c+1]== Live)
            {
                i++;
            }
            if (now [r][c-1]== Live)
            {
                i++;
            }
            if (now [r+1][c-1]== Live)
            {
                i++;
            }
            if (now [r+1][c]== Live)
            {
                i++;
            }
            if (now [r+1][c+1]== Live)
            {
                i++;
            }

            if (now [r][c] == Live)
            {
                if (i < 2)
                {
                    next [r][c] = Dead;
                }
                if (i >3)
                {
                    next [r][c] = Dead;
                }
            }
            if (now [r][c] == Dead)
            {

                if (i = 3)
                {
                    next [r][c] = Live;
                }
                ;
            }

        }

    }
    now=next ;
}

int main ()
{

    char name[MAX_FILENAME_LENGTH];
    cout << enter_filename(name) ;
//                                                                         
}

