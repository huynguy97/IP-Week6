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
    assert (true);
    //                                                                                       
    cout << "Please enter the name of the file you want to open, including the extension (e.g. .txt)." << endl;
    cout << "The name may include spaces, but must not exceed " << MAX_FILENAME_LENGTH << " characters." << endl;
    cout << "Terminate the filename by pressing enter." << endl;
    char file;
    for (int index = 0; index < MAX_FILENAME_LENGTH; index++)
    {
        cin.get(file);
        if (file == '\n')
        {
            file = '\0';
            filename [index] = file;
            return true;
        }
        filename [index] = file;
        cout << file << endl;
    }
    cout << "You entered: " << filename << endl;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert (inputfile.is_open());
    //                                                                                                         
    char x;
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
                inputfile.get(x);
                if (x == DEAD)
                {
                    universe [r][c] = Dead;
                }
                else if (x == LIVE)
                {
                    universe [r][c] = Live;
                }
                else
                {
                    return false;
                }
            }
        }
        if (r != 0 && r != ROWS-1)
        {
            inputfile.get(x);
            if (x != '\n')
                return false;
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert (true);
    //                                                                                
    //                                                                                     

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (universe[r][c] == Dead)
            {
                cout << DEAD;
            }
            else if (universe[r][c] == Live)
            {
                cout << LIVE;
            }
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell universe [ROWS][COLUMNS], Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                                            
    //                                                                             

    for (int r = 0; r < ROWS-1; r++)
    {
       for (int c = 0; c < COLUMNS-1; c++)
       {
           if (universe[r][c] == Dead)
           {
               now[r][c] = Dead;
           }
           else if (universe[r][c] == Live)
           {
               now[r][c] = Live;
           }
       }
    }
    for (int r = 1; r < NO_OF_ROWS ; r++)
    {
        for (int c = 1; c < NO_OF_COLUMNS ; c++)
        {
            int countlive = 0;
            if (now[r][c] == Dead)
            {
                if (universe[r][c-1] == Live)
                    countlive++;
                if (universe[r][c+1] == Live)
                    countlive++;
                if (universe[r-1][c-1] == Live)
                    countlive++;
                if (universe[r-1][c] == Live)
                    countlive++;
                if (universe[r-1][c+1] == Live)
                    countlive++;
                if (universe[r+1][c-1] == Live)
                    countlive++;
                if (universe[r+1][c] == Live)
                    countlive++;
                if (universe[r+1][c+1] == Live)
                    countlive++;
                if (countlive == 3)
                    next[r][c] = Live;
            }
            else if (now[r][c] == Live)
            {
                if (universe[r][c-1] == Live)
                    countlive++;
                if (universe[r][c+1] == Live)
                    countlive++;
                if (universe[r-1][c-1] == Live)
                    countlive++;
                if (universe[r-1][c] == Live)
                    countlive++;
                if (universe[r-1][c+1] == Live)
                    countlive++;
                if (universe[r+1][c-1] == Live)
                    countlive++;
                if (universe[r+1][c] == Live)
                    countlive++;
                if (universe[r+1][c+1] == Live)
                    countlive++;
                if (countlive < 2)
                    next[r][c] = Dead;
                else if (countlive == 2 || countlive == 3)
                    next[r][c] = Live;
                else if (countlive > 3)
                    next[r][c] = Dead;
            }
        }
    }
    cout << endl;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (next[r][c] == Dead)
            {
                cout << DEAD;
            }
            else if (next[r][c] == Live)
            {
                cout << LIVE;
            }
        }
        cout << endl;
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    Cell universe [ROWS][COLUMNS];
    Cell now [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    enter_filename(filename);
    cout << "Trying to open file ..." << endl;
    ifstream inputfile;
    inputfile.open(filename);
    if (inputfile.is_open())
        cout << "Your file has been opened successfully." << endl;
    else
    {
        cout << "Unfortunately, I am not able to open your file." << endl;
        cout << "The program will stop now." << endl;
        return false;
    }
    read_universe_file(inputfile, universe);
    show_universe(universe);
    next_generation(universe, now, next);
}

