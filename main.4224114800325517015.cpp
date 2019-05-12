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
    assert(true);
    /*               
                                                                   
     */
    cout << "Please enter the file name(don't forget to include the extension): ";
    cin >> filename;
    for (int index =0; index < MAX_FILENAME_LENGTH; index++)
    {
        filename[index] = cin.get();
        if (filename[index]== '\n')
        {
            filename[index]= '\0';
            return true;
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    char c;
    for (int row=1; row<=ROWS-2; row++)
	{
		for (int col=1; col<=COLUMNS-2; col++)
		{
		    inputfile.get(c);
		    if (c='.'){
                universe[row][col]= Dead;
		    }
		    if (c='*'){
                universe[row][col]= Live;
		    }
			cout << universe[row][col];
		}
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
    char name[MAX_FILENAME_LENGTH];
    if(!enter_filename(name)){
        return -1;
    }
    ifstream file(name);
}

