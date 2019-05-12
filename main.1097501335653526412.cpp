#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

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
    cout << "Input filename: ";
    assert(true);
    //                                                
    int i = 0;
    char a = 'a';
    while (a != '\n')
    {
        cin.get(a);
        filename[i] = a;
        i++;
    }
    filename[i-1] = '\0';
    if (i<=MAX_FILENAME_LENGTH)
        return true;
    else
        return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe[ROWS][COLUMNS])
{
    //                                                
    for (int k=0; k<=ROWS; k++)                          //                          
        for (int l=0; l<=COLUMNS; l++)
            universe[k][l] = Dead;
    char q;
    for (int i=1; i<=ROWS-1; i++)                        //                      
    {
        for (int j=1; j<=COLUMNS-1; j++)
        {
            cout << "test";
            inputfile.get(q);
            cout << q;
            cout << "hai2";
            if (q == '\n')
                inputfile.get(q);
            if (q == '*')
                universe[i][j] = Live;

        }
    }
    return 1;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
    ifstream input_file;
    Cell dead_or_alive_map[ROWS][COLUMNS];
    char filename[MAX_FILENAME_LENGTH+1];
    if(!enter_filename(filename))
    {
        cout << "Filename is too long.";
        return 0;
    }
    input_file.open(filename);
    if (!input_file.is_open())
    {
        cout << "Inputfile hasn't opened.";
        return 0;
    }
    if (!read_universe_file (input_file, dead_or_alive_map))
    {
        cout << "Inputfile hasn't opened or has too long of a name.";
        return 0;
    }
    else
        cout<<"check if it's finally allright";
    input_file.close();
    return 0;
}

