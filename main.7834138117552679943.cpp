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

    cout << "Enter a filename: " << endl;

    cin.getline(filename, MAX_FILENAME_LENGTH);

    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                           
    assert(inputfile.is_open());
    //                                                                                                      

    char c;
    inputfile.get(c);
    int row=1;
    int column=1;

    while(inputfile)
    {
        if (c==DEAD) universe[row][column] = Dead;
        else universe[row][column] = Live;
        cout << c;

        column++;
        inputfile.get(c);

        if (c=='\n')
        {
            row++;
            column=1;
            cout << c;
            inputfile.get(c);
        }
    }

    for (row=0; row<ROWS; row++)
    {
        universe[row][0]=Dead;
        universe[row][COLUMNS-1]=Dead;
    }

    for(column=1; column<COLUMNS-1; column++)
    {
        universe[0][column]=Dead;
        universe[ROWS-1][column]=Dead;
    }

return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                     

    for (int row=0; row<ROWS; row++)
    {
        for (int column=0; column<COLUMNS; column++)
        {
            if (universe[row][column] == Dead) cout << DEAD;
            else cout << LIVE;
        }
        cout <<endl;
    }
    cout << endl;

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                                                                 

    for (int row=0; row<ROWS; row++)
    {
        for (int column=0; column<COLUMNS; column++)
        {
            if (column==0||column==COLUMNS-1||row==0||row==ROWS) next[row][column]=Dead;
            else
            {
                int i=0;
                if (now[row-1][column-1]==Live) i++;
                if (now[row-1][column]==Live) i++;
                if (now[row-1][column+1]==Live) i++;
                if (now[row][column-1]==Live) i++;
                if (now[row][column+1]==Live) i++;
                if (now[row+1][column-1]==Live) i++;
                if (now[row+1][column]==Live) i++;
                if (now[row+1][column+1]==Live) i++;

                if (now[row][column]==Dead)
                {
                    if (i==3) next[row][column]=Live;
                    else next[row][column]=Dead;
                }
                else
                {
                    if(i==0||i==1) next[row][column]=Dead;
                    else if (i==2 || i==3) next[row][column]=Live;
                    else next[row][column]=Dead;
                }

            }
        }
    }

}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    enter_filename(filename);

    ifstream myfile;
    myfile.open(filename);
    cout << "file open: " << myfile.is_open() << endl;

    Cell startUniverse [ROWS][COLUMNS];
    Cell nextUniverse [ROWS][COLUMNS];
    read_universe_file(myfile, startUniverse);
    show_universe(startUniverse);
    next_generation(startUniverse,nextUniverse);
    show_universe(nextUniverse);
}

