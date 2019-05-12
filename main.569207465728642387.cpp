//                            
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
        assert (true);
    /*                  
                                                                                                             
    */

    cout << "Enter the name of the file, that you want to use (with a maximum filename length of " << MAX_FILENAME_LENGTH << " ). " << endl;

    char c;
    int i;

    for (i = 0 ; c != '\n' ; i++ )
    {
        if (i <= 79 )
        {
            cin.get (c);
            filename [i] = c;
        }
        else
        {
            cout << "ERROR: Your filename is longer then the maximum filename length. ";
            return false;
        }
    }

    filename [i - 1] = '\0';
    return true;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
        assert (inputfile.is_open());
    /*                  
                                                     
                                                              
                                                                      
                                                                      
    */

    char c;
    int columns;
    int rows;

    for (rows = 0 ; rows < ROWS ; rows++ )
    {
        for (columns = 0 ; columns < COLUMNS ; columns++)
        {
            if ((columns == 0 || columns == COLUMNS-1) || (rows == 0 || rows == ROWS - 1))
            {
                universe [rows][columns] = Dead;
            }
            else
            {
                inputfile.get(c);
                if (c == '.')
                {
                    universe [rows][columns] = Dead;
                }
                if (c == '*')
                {
                    universe [rows][columns] = Live;
                }
            }
        }
        if(!(rows == 0 || rows == ROWS - 1))
        {
            inputfile.get(c);
        }

    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
        assert (true);
    /*                  
                                                       
    */

    for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                cout << universe[r][c];
            }
            cout << endl;
        }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               

    /*                 

    */

}

int main ()
{
char filename [MAX_FILENAME_LENGTH];
enter_filename (filename);

ifstream test;
test.open(filename);

Cell universe [ROWS][COLUMNS];
read_universe_file (test, universe);
show_universe (universe);

}

