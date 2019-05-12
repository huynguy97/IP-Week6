#include <iostream>
#include <fstream>
#include <cassert>
//                                             
using namespace std;

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

#include <string>
//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{

int c, num=0;

/*             
     
               
                           
     
              

                                  
                     
        
                    
*/
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(true);
    //               
    for (int i = 0 ; i < NO_OF_ROWS;i++)
    {
        for(int j = 0 ; j < NO_OF_COLUMNS;j++)
            {
            char c = inputfile.get();
            if (c == DEAD)
            {
                universe[i][j] = Dead;
            }
            else if (c == LIVE)
            {

                universe[i][j] = Live;
            }
            else
            {
                return false;
            }
        }
        return true;

    }

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
Cell universe;

if (!read_universe_file("glider0.txt",universe))
     cout << "Program aborted." << endl ;
        return -1 ;
}

