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
    int i = 0;
    while(filename[i] != '\0')
    {
        i++;
    }
    if (i>MAX_FILENAME_LENGTH)
    {
        cout << "Error \n";
        return false;
    }
    else
    {
        return true;
    }

}

//                           

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                          
    if (inputfile)
    {

        //                                      
        for(int r = 0; r < ROWS; r++)
        {
            universe[r][0] = Dead;
            universe[r][COLUMNS-1] = Dead;
        }

        for(int c = 0; c < COLUMNS; c++)
        {
            universe[0][c] = Dead;
            universe[ROWS-1][c] = Dead;
        }

        for(int r = 0; r < NO_OF_ROWS; r++)
        {
            for(int c = 0; c < NO_OF_COLUMNS; c++)
            {

                char x;
                inputfile >> x;

                if (x == DEAD ){
                    universe[r+1][c+1] = Dead;
                }
                if (x == LIVE){
                    universe[r+1][c+1] = Live;
                }
            }
        }
        inputfile.close();

        return true;
    }

    else
    {
        cout << "The file did not open correctly.";
        return false;
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //             
    assert(true);
    //                                                                     

    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLUMNS; c++)
        {
            if (universe[r][c] == Dead)
            {
                cout << ".";
            }
            else if (universe[r][c] == Live)
            {
                cout << "*";
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
    for(int a = 1; a < ROWS-1 ; a++)
    {
        for(int b = 1; b < COLUMNS-1; b++)
        {
            int alive = 0;

            for(int c = -1; c < 2; c++)
            {
                for(int d = -1; d < 2; d++)
                {
                    if(!(c == 0 && d == 0))
                    {
                        if(now[a+c][b+d]==Live)
                        {
                            ++alive;
                        }
                    }
                }
            }
            if(alive < 2) {next[a][b] = Dead;}
            else if(alive == 3){next[a][b] = Live;}
            else if(alive > 3){next[a][b] = Dead;}
        }
    }
}

int main ()
{
    char filename[200];
    Cell universe [ROWS][COLUMNS];
    Cell temp [ROWS][COLUMNS];
    ifstream input_file;
    ofstream output_file;

    cout << "Welcome to the Game of Life! \nEnter a file name to start\n> ";
    cin.getline(filename,sizeof(filename));
    if(enter_filename(filename))
    {
        input_file.open(filename);
    }
    read_universe_file(input_file, universe);

    show_universe(universe);
    next_generation(universe, temp);
    input_file.close () ;
    output_file.close () ;
}

