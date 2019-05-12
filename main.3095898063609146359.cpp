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
        assert (MAX_FILENAME_LENGTH>0);
    //                
        //                                                                                                             
    //               
    int a = 0;
    cout << "Enter file name: ";
    char c;
    cin.get(c);
    while (c!='\n')
    {
        filename[a]=c;
        a=a+1;
        if (a > MAX_FILENAME_LENGTH)
            return false;
        cin.get(c);
    }
    filename[a]='\0';
    for (int index=0; index < MAX_FILENAME_LENGTH-1; index++)
        cout << filename[index] << ' ' ;
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
        assert (inputfile.is_open () && ROWS > 0 && COLUMNS > 0);
    //                
        //                                                                                                          
        //                                           
    //               
    int nr_of_rows = 0;
    int nr_of_columns = 0;
    for (int row = 0; row < ROWS; row++)
    {
        for (int column = 0; column < COLUMNS; column++)
        {
            universe[row][column];
            nr_of_columns++;
            nr_of_rows++;
        }
    }
    if ((nr_of_rows > ROWS || nr_of_rows < ROWS) && (nr_of_columns > COLUMNS || nr_of_columns < COLUMNS))
        return false;
    else
        return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
        assert (ROWS > 0 && COLUMNS > 0);
    //                
        //                                          
    //               
    for (int row = 0; row < ROWS; row++)
    {
        for (int column = 0; column < COLUMNS; column++)
        {
            if (universe[row][column] == Dead)
                cout << DEAD ;
            else
                cout << LIVE ;
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
        assert (ROWS > 0 && COLUMNS > 0);
    //                
        //                                                                                                
    //              
    for (int row = 0; row < ROWS; row++)
    {
        for (int column = 0; column < COLUMNS; column++)
        {
            Cell current = now[row][column];
            Cell top = now[row-1][column];
            Cell bottom = now[row+1][column];
            Cell left = now[row][column-1];
            Cell right = now[row][column+1];
            Cell topRight = now[row-1][column+1];
            Cell topLeft = now[row-1][column-1];
            Cell bottomRight = now[row+1][column+1];
            Cell bottomLeft = now[row+1][column-1];
            int aliveCount = top+bottom+right+left+topRight+topLeft+bottomRight+bottomLeft;
            int deadCount = 8 - aliveCount;
            if (now[row][column] == Live)
            {
                if (aliveCount == 2 || aliveCount == 3)
                    next[row][column] == Live;
                else if (aliveCount < 2)
                    next[row][column] == Dead;
                else next[row][column] == Dead;
            }
            else if (aliveCount == 3)
                next[row][column] == Live;
            else
                next[row][column] == Dead;
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream inputFile(filename);
    inputFile.open(filename);
    Cell universe[ROWS][COLUMNS];
    read_universe_file(inputFile,universe);
    cout << "Finished reading file." << endl;
    show_universe(universe);
    Cell next[ROWS][COLUMNS];
    cout << "Next state: " << endl;
    next_generation(universe, next);
    show_universe(next);
}

