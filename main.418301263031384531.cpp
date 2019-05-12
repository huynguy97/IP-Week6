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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
//                 
    assert(MAX_FILENAME_LENGTH >= 0);
//                  
/*                                                                                                                                                                                       
                                                                  */
//                
    cout << "Enter a filename of max length " << MAX_FILENAME_LENGTH << " with the enter character included" << endl;

    char x;
    int y = 0;
    for(y=0; y<MAX_FILENAME_LENGTH && x != '\n'; y++)
    {
        cin.get (x);
        filename[y] = x;
    }
    y --;
    cout << y << '\n';
    if (filename[y] == '\n')
    {
        filename[y] = '\0';
        cout << "filename success\n";
        return true;
    }
    else
    {
        cout << "invalid filename\n";
        return false;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//                 
    assert(!inputfile.is_open());
//                  
/*                                                                                              */
//                
    char filename [MAX_FILENAME_LENGTH];
    int a = 1;
    int b = 1;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
            universe[i][j] = Dead;
    char get;
    if (enter_filename(filename))
    {
        inputfile.open(filename);
        while (inputfile)
        {
            inputfile.get(get);
            if (a == 0 || a == ROWS - 1)
            {
                universe[a][b] = Dead;
                b++;
            }
            else if(get == LIVE)
            {
                universe[a][b] = Live;
                b++;
            }
            else if(get == DEAD)
            {
                universe[a][b] = Dead;
                b++;
            }
            else if(get == '\n')
            {
                universe[a][b] = Dead;
                a++;
                b = 0;
                universe[a][b] = Dead;
                b++;
            }
            else
            {
                cout << "Could not read cell state" << endl;
                return false;
            }
        }
        cout << "Reading succesfull" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//                 
    assert(true);
//                  
/*                      */
//                
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < COLUMNS; b++)
        {
            if (universe[a][b] == Dead)
            {
                cout << DEAD;
            }
            else if (universe[a][b] == Live)
            {
                cout << LIVE;
            }
        }
        cout << '\n';
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//                 
    assert (true);
//                  
/*                                                                             */
//                 
    int c = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            next[i][j] = Dead;
        }
    }
    for (int a = 1; a < ROWS - 1; a++)
    {
        for (int b = 1; b < COLUMNS - 1; b++)
        {
            if (now[a-1][b-1] == Live)
            {
                c++;
            }
            if (now[a-1][b] == Live)
            {
                c++;
            }
            if (now[a-1][b+1] == Live)
            {
                c++;
            }
            if (now[a][b-1] == Live)
            {
                c++;
            }
            if (now[a][b+1] == Live)
            {
                c++;
            }
            if (now[a+1][b-1] == Live)
            {
                c++;
            }
            if (now[a+1][b] == Live)
            {
                c++;
            }
            if (now[a+1][b+1] == Live)
            {
                c++;
            }
            if (c == 3)
            {
                next[a][b] = Live;
            }
            else if (c == 2)
            {
                if (now[a][b] == Live)
                {
                    next[a][b] = Live;
                }
                else
                {
                    next[a][b] = Dead;
                }
            }
            else
            {
                next[a][b] = Dead;
            }
            c = 0;
        }
    }
}

int main ()
{
    ifstream infile;
    Cell universum [ROWS][COLUMNS];
    Cell universum2 [ROWS][COLUMNS];
    if (read_universe_file(infile, universum))
    {
        show_universe(universum);
    }
    cout << '\n';
    next_generation(universum, universum2);
    show_universe(universum2);
}

