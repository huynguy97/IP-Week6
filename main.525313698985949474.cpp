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
    /*                 */
        assert(MAX_FILENAME_LENGTH >= 0);
    /*
                       
                                                       
                                                                                     
                                
    */

    cout << "Please enter a filename (max. 80 characters): ";
    int i = 0;
    char c;
    while (i < MAX_FILENAME_LENGTH)
    {
        cin.get(c);
        if (c == '\n')
        {
            filename [i] = '\0';
            return true;
        }
        else
        {
            filename[i] = c;
        }
        i++;
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    /*                 */
    assert(inputfile.is_open() && ROWS >= 2 && COLUMNS >= 2);
    /*
                        
                                                             
                                                                              
    */

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            if (r == 0 || r == ROWS-1 || c == 0 || c == COLUMNS-1) {
                universe[r][c] = Dead;
            }
            else {
                char x = inputfile.get();
                if (x == DEAD)
                {
                    universe [r][c] = Dead;
                }
                else if (x == LIVE)
                {
                    universe [r][c] = Live;
                }
                else {
                    return false;
                }
            }
        }
        if (!(r == 0 || r == ROWS-1)) {
            char enter = inputfile.get();
            if (enter != '\n') {
                cout << r << " " << endl;
                return false;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    /*                 */
        assert(ROWS >= 2 && COLUMNS >= 2);
    /*
                        
                                                                                   
    */

    for (int c =1; c < ROWS-1; c++)
    {
        for (int d = 1; d < COLUMNS-1; d++)
        {
            Cell cell = universe [c][d];
            if (cell == Dead)
            {
                cout << DEAD;
            }
            if (cell == Live)
            {
                cout << LIVE;
            }
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    /*                 */
    assert(ROWS >= 2 && COLUMNS >=2);
    /*
                                                                                                  
    */

    int a = 0;
    int b = 0;
    while (a <= ROWS)
    {
        if (a == 0 || b == 0 || a == ROWS || b == COLUMNS)
        {
            next [a][b] = Dead;
        }
        else
        {
            int surround = 0;
            if (now [a-1][b-1] == Live)
                surround++;
            if (now [a-1][b] == Live)
                surround++;
            if (now [a-1][b+1] == Live)
                surround++;
            if (now [a][b-1] == Live)
                surround++;
            if (now [a][b+1] == Live)
                surround++;
            if (now [a+1][b-1] == Live)
                surround++;
            if (now [a+1][b] == Live)
                surround++;
            if (now [a+1][b+1] == Live)
                surround++;
            if (now [a][b] == Live)
            {
                if (surround < 2 || surround > 3)
                {
                    next [a][b] = Dead;
                }
                else
                {
                    next [a][b] = Live;
                }
            }
            if (now [a][b] == Dead)
            {
                if (surround == 3)
                {
                    next [a][b] = Live;
                }
                else
                {
                    next [a][b] = Dead;
                }
            }
        }
        if (b == COLUMNS)
        {
            a++;
            b = 0;
        }
        else
        {
            b++;
        }
    }
}

int main ()
{
    char theFilename [MAX_FILENAME_LENGTH];
    enter_filename(theFilename);
    ifstream file(theFilename);
    Cell theUniverse [ROWS][COLUMNS];
    read_universe_file(file, theUniverse);
    Cell theNextUniverse [ROWS][COLUMNS];
    next_generation(theUniverse, theNextUniverse);
    show_universe(theNextUniverse);
}

