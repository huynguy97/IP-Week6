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
    //                
    for(int i=0; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(filename[i]);
        if ((filename[i]) == '\n')
        {
            filename[i] = '\0' ;
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());
    //                
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1)
            {
                universe[r][c] = Dead;
            }
            else
            {
                char d = inputfile.get();
                //        
                if (d == LIVE)
                {
                    universe[r][c] = Live;
                }
                else if (d == DEAD)
                {
                    universe[r][c]=Dead;

                }
                else
                {
                    return false;
                }
            }
        }
        if (r != 0 && r != ROWS-1)
        {

            char d = inputfile.get();
            if (d != '\n')
            {
                return false;
            }
        }
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1)
                {
                    universe[r][c] = Dead;
                }
            }
            return true;
        }
    }
}
void show_universe (Cell universe [ROWS][COLUMNS])
{

    //               
    //               
    int i = 0;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if ( !(r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1))
            {
                cout<< " " << i << " " << universe[r][c] << endl;
                i++;
            }
        }
        cout<<endl;
    }
}

//                             
int next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])

{

    //              
    //               

    int n=0 ; //              
    if (now[a][b] == Live)
    {
        if (n == 2 || n == 3)
        {
            return Live;
        }
        else
        {
            return Dead;
        }
    }
    else
    {
        if (n == 3)
        {
            return Live;
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    cout<<"Please enter the file name "<< "  "<< endl;
    if (!enter_filename(filename))
    {
        return -1;
    }
    ifstream inputfile(filename);
    if (!inputfile.is_open())
    {
        return -1;
    }
    Cell universe[ROWS][COLUMNS];
    read_universe_file(inputfile, universe);
    Cell next[ROWS][COLUMNS];
    next_generation(universe, next );

}

