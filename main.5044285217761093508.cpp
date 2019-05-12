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
    //               
    assert (true);

    //               
    //                  
    cout << "Please enter a file name" << endl;
    char c;
    //                                            
    for (int i=0; i < MAX_FILENAME_LENGTH; i++)
    {
        c = cin.get();
        filename[i] = c;
        if (c == '\n')
        {
            filename[i] = '\0';
            return true;
        }
        else
        {
            filename[i] = c;
        }
    }
    //                                                            
    if (filename[MAX_FILENAME_LENGTH]<=MAX_FILENAME_LENGTH)
        return true;
    else
        cout << "File name is too long" << endl;
    return false;

    assert (sizeof(filename) <= MAX_FILENAME_LENGTH);
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(inputfile.is_open());
    //                                                                                                           
    char c;
    inputfile >> c;
    while (inputfile) {
        for (int a= 1; a<= NO_OF_ROWS; a++)
        {
            for (int b = 1; b <= NO_OF_COLUMNS; b++ ) {
                if (c == '*') {
                    universe[a][b] = Live;
                }
                else if (c == '.') {
                    universe[a][b] = Dead;
                }
                else {
                    return false;
                }

                inputfile >> c;
            }
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                 
    for (int a = 1; a <= NO_OF_ROWS; a++)
    {

        for (int b = 1; b <= NO_OF_COLUMNS; b++ )
        {

            if (universe [a][b] == 0)
            {
                cout << ".";

            }
            else
            {
                cout << "*";
            }

        }
        cout << endl;
    }
}
/*
                               
                                                                          
 
                                                      
 
*/
int main ()
{
    char new_file_name[MAX_FILENAME_LENGTH];
    enter_filename(new_file_name);
    Cell rows_and_columns [ROWS][COLUMNS];
    ifstream inputfile;
    inputfile.open(new_file_name);
    read_universe_file(inputfile, rows_and_columns);
    show_universe(rows_and_columns);

}

