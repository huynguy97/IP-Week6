#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdio>
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
    assert(true);
    //                                                                             
    //              
    char b;
    int length=0;
    while  (length < MAX_FILENAME_LENGTH)
    {
        cin.get (b);
        filename[length]=b;
        if (b == '\n')
            {
                cout << "Returned true." << endl;
                filename[length]='\0';

                return true;
            }
        ++length;

    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS], string inputput)
{
    //              
    assert (true);
    //                                                                                         
    //              
    inputfile.open(inputput);
    if ( inputfile.is_open() )
        {
            cout << inputput << " could be opened." << endl;

            char a;
            Cell b;
            for (int j = 1;  j <= NO_OF_ROWS; j++)
            {
                for (int i = 1; i <= NO_OF_COLUMNS; i++)

                {
                inputfile.get(a);
                if (a == '.')
                {
                    b = Dead;
                }

                if (a == '*')
                {
                    b = Live;
                }

                universe[j][i]= b;
                }
            inputfile.get(a);

            }
            cout << "Well done." << endl;
            return true;
        }
    else
        {
            cout << inputput << "Could not be opened." << endl;
            return false;
        }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(true);
    //                                                                  
    //              
    cout << "Hi this is show universe" << endl;
   for(int j = 0; j < ROWS; j++)
    {
        for(int i = 0; i < COLUMNS; i++)
        {
            if (i == 0 || j == 0 || i == COLUMNS-1 || j == ROWS-1)
            {
                universe[j][i] = Dead;
            }
            if (universe[j][i] == 0)
            {
                cout << ".";
            }
            if (universe [j][i] == 1)
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
    //              
    for (int j = 1;  j <= NO_OF_ROWS; j++)
    {
        for (int i = 1; i <= NO_OF_COLUMNS; i++)
        {
           int n = 0;
           if (now[j-1][i-1]== Live)
           {
               n++;
           }
           if (now[j-1][i]== Live)
           {
               n++;
           }
           if (now[j-1][i+1]==Live)
           {
               n++;
           }
           if (now[j][i-1]==Live)
           {
               n++;
           }
           if (now[j][i+1]==Live)
           {
               n++;
           }
           if (now[j+1][i-1]==Live)
           {
               n++;
           }
           if (now[j+1][i]==Live)
           {
               n++;
           }
           if (now[j+1][i+1]==Live)
           {
               n++;
           }

           if(now[j][i] ==Live)
           {
                switch(n)
                {
                    case 0:
                    case 1:
                        next[j][i] = Dead;
                        break;
                    case 2:
                    case 3:
                        next[j][i] = Live;
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        next[j][i] = Dead;
                        break;
                }
           }
           else
           {
               if (n == 3)
               {
                   next[j][i] = Live;
               }
           }

        }
    }
    show_universe(next);
}

int main ()
{
    cout << "Enter a file name for input including the file extension " << endl;
    char input[MAX_FILENAME_LENGTH];

    if(enter_filename(input)== false)
        {
        cout << "Something doesn't seem to work." << endl;
        }
    else
        {
        cout << "Something does work." << endl;
        }
    ifstream inputfile;
    Cell universe[ROWS][COLUMNS];
    read_universe_file(inputfile, universe, input);
    show_universe (universe);

    Cell next [ROWS][COLUMNS];
    next_generation(universe, next);
    return 0;
}

