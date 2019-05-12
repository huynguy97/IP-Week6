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

    int no_of_chars = MAX_FILENAME_LENGTH;

    while (no_of_chars != 0) //                   
    {
        if (filename [no_of_chars] == 'n')
        {
            filename [no_of_chars] = '0';
            break;
        }
        else
        {
            no_of_chars--;
        }

        if (no_of_chars == 0)
            return false;
    }

    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
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

    cout << "Please enter filename: " << endl;

    char filename [MAX_FILENAME_LENGTH];

    cin.getline(filename,sizeof(filename));

    cout << filename << enter_filename(filename);

    return 0;
}

