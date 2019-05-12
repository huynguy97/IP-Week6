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
    assert(MAX_FILENAME_LENGTH == 80);
//                                                                                                                            

    char ch;
    cout << "Filename: " << endl;

    for (int i = 0; i <= MAX_FILENAME_LENGTH && cin.get(ch); ++i)
    {
        if (ch != '\n')
            filename[i] = ch;
        else{
            filename[i] = '\0';
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//                
    assert(inputfile.is_open() && ROWS == 42 && COLUMNS == 62);
//                 

    int row = 0, column = 0;
    char ch;

    while (inputfile)
    {
        inputfile.get(ch);

        if (row == 0 || row == 41)          //                                                                  
        {
            for (int i = 0; i < COLUMNS; i++)
                universe [row][i] = Dead;

            if (row == 0)                   //                                                                                                   
                row++;
        }

        switch (column)                     //                                                                     
        {
            case 61: universe [row][column] = Dead; break;
            case 0: universe [row][column] = Dead; column++;
        }

        switch (ch)                         //                                            
        {
            case 46: universe [row][column] = Dead; break;                      //                
            case 42: universe [row][column] = Live; break;                      //                
            case '\n': row++; column = -1; break;                               //                                                              
            default: cout << "File contains invalid characters."; return false;
        }                                                                       //                                                                                                                             
        column++;
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//                
    assert(ROWS == 42 && COLUMNS == 62);
//                                                                                      

    for (int r = 0; r < ROWS; r++)
    {
        cout << "\t";
        for (int c = 0; c < COLUMNS; c++)
        {
            if (universe [r][c] == Live)
                cout << LIVE;
            else
                cout << DEAD;
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//                
    assert(ROWS == 42 && COLUMNS == 62);
//                                                                                                                                                         

    int livecells;

    for (int r = 1; r <= NO_OF_ROWS; r++)
    {
        for (int c = 1; c <= NO_OF_COLUMNS; c++)
        {
            livecells = 0;

            if (now [r-1][c-1] == Live)         //                                                  
                livecells++;                    //                                                  
            if (now [r-1][c] == Live)
                livecells++;
            if (now [r-1][c+1] == Live)
                livecells++;
            if (now [r][c-1] == Live)
                livecells++;
            if (now [r][c+1] == Live)
                livecells++;
            if (now [r+1][c-1] == Live)
                livecells++;
            if (now [r+1][c] == Live)
                livecells++;
            if (now [r+1][c+1] == Live)
                livecells++;

            if (now[r][c] == Live)              //                                                                                                  
            {
                switch (livecells)
                {
                    case 2: next[r][c] = Live; break;
                    case 3: next[r][c] = Live; break;
                    default: next[r][c] = Dead;
                }
            }
            else
            {
                if (livecells == 3)
                    next[r][c] = Live;
                else
                    next[r][c] = Dead;
            }
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];

    enter_filename(filename);

    ifstream inputfile (filename);
    Cell    universe [ROWS][COLUMNS],
            next [ROWS][COLUMNS];

    if (read_universe_file(inputfile, universe))
    {
        show_universe(universe);
        next_generation(universe, next);
        cout    << endl
                << "\t\t\t ____________________________ " << endl
                << "\t\t\t|       Next Generation:     |" << endl
                << "\t\t\t|____________________________|" << endl
                << endl;
        show_universe(next);
    }
}

