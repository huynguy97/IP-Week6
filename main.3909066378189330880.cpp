//                     
//                      
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
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
    int counter = 0;
    char input;
    while (counter < 80)
    {
        cin.get(input);
        if (input == '\n')
        {
            filename[counter] = '\0';
            return true;
        }
        else
        {
            filename[counter] = input;
        }
        ++counter;
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS], string file)
{
    inputfile.open(file.c_str());
    for (int i = 1; i < 41; i++)
    {

      for (int a = 1; a < 61; a++)
    {
        char c;
        inputfile.get(c);
        switch(c)
        {
            case '.': universe [i][a] = Dead; break;
            case '*': universe [i][a] = Live; break;
        }
    }
    inputfile.get();
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    for (int i = 1; i < 41; i++)
    {
        for (int a = 1; a < 61; a++)
        {
            switch(universe[i][a])
            {
                case Dead: cout << '.'; break;
                case Live: cout << '*'; break;
            }
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    for (int i = 1; i < 41; i++)
    {
        for (int a = 1; a < 61; a++)
        {
            int e = i+1;
            int f = i-1;
            int g = a+1;
            int h = a-1;

            if (now[i][a] == Dead)
            {
                int b = 0;
                if (now [i-1][a-1] == Live)
                {
                    ++b;
                }
                if (now [i-1][a] == Live)
                {
                    ++b;
                }
                if (now [i-1][a+1] == Live)
                {
                    ++b;
                }
                if (now [i][a-1] == Live)
                {
                    ++b;
                }
                if (now [i][a+1] == Live)
                {
                    ++b;
                }
                if (now [i+1][a-1] == Live)
                {
                    ++b;
                }
                if (now [i+1][a] == Live)
                {
                    ++b;
                }
                if (now [i+1][a+1] == Live)
                {
                    ++b;
                }

                if (b == 3)
                {
                    next [i][a] = Live;
                }
                else
                {
                    next [i][a] = Dead;
                }
            }
            if (now[i][a] == Live)
            {
                int b = 0;
                if (now [i-1][a-1] == Live)
                {
                    ++b;
                }
                if (now [i-1][a] == Live)
                {
                    ++b;
                }
                if (now [i-1][a+1] == Live)
                {
                    ++b;
                }
                if (now [i][a-1] == Live)
                {
                    ++b;
                }
                if (now [i][a+1] == Live)
                {
                    ++b;
                }
                if (now [i+1][a-1] == Live)
                {
                    ++b;
                }
                if (now [i+1][a] == Live)
                {
                    ++b;
                }
                if (now [i+1][a+1] == Live)
                {
                    ++b;
                }

                if (b < 2 || b > 3)
                {
                    next [i][a] = Dead;
                }
                else
                {
                    next [i][a] = Live;
                }
            }

            switch(next [i][a])
            {
                case Dead: cout << '.'; break;
                case Live: cout << '*'; break;
            }
        }
        cout << endl;
    }
}

int main ()
{
    cout << "enter the file name: ";
    char file [MAX_FILENAME_LENGTH];
    enter_filename(file);
    cout << file;
    ifstream inputfile;
    Cell universe[ROWS][COLUMNS];
    read_universe_file(inputfile, universe, file);
    show_universe(universe);
    Cell now [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    next_generation(universe, next);
}

