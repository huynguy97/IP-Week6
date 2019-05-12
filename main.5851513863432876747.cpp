#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//      
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
    assert(MAX_FILENAME_LENGTH >= 0);
    //               
    //                                                                          
    //                                                               

    char name;
    cout << "Enter the name of an existing text file: ";
    for(int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(name);
        filename[i] = name;
        if (int(filename[i]) == '\n')
        {
            filename[i] = '\0';
            return true;
        }
    }
    return false;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS], char filename [MAX_FILENAME_LENGTH])
{
    //              
    assert(ROWS >= 0 && COLUMNS >= 0);
    //               
    //                                                                                                    
    //                            

    inputfile.open(filename);
    if(!inputfile)
        return false;
    char c;
    //                                      
    for(int i = 1; i < NO_OF_ROWS+1; i++)
    {
        for(int j = 1; j < NO_OF_COLUMNS+1; j++)
        {
            inputfile.get(c);
            if(c == LIVE)
                universe [i][j]= Live;
            else universe [i][j]= Dead;
        }
        inputfile.get(c); //                    
    }

    //                                
    for(int k = 0; k < ROWS; k++)
    {
        universe[k][0] = Dead;
        universe[k][COLUMNS] = Dead;
        for(int l = 0; l < COLUMNS; l++)
            {
                if( k == 0)
                    universe[k][l] = Dead;
                else if( k == ROWS )
                    universe[k][l] = Dead;
            }
    }
	return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(ROWS >= 0 && COLUMNS >= 0);
    //              
    //                                                                        
    //                                                           

    cout << "\n";
	for(int j = 0; j < (ROWS-1); j++)
	{
		for(int k = 0; k < (COLUMNS - 1); k++)
		{
			if(universe[j][k] == Dead)
				cout << DEAD;
			else cout << LIVE;
		}
		cout << "\n";
	}

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
    assert(ROWS >= 0 && COLUMNS >=0);
    //                 
    //                                                                              
    //                                                                                      

    for(int i = 1; i < (ROWS - 2); i++)
    {

        for(int j = 1; j < (COLUMNS - 2); j++)
        {
            //                                                                 
            int live_cells =    now[i-1][j-1] + now[i-1][j] + now[i-1][j+1] +
                                now[i][j-1] + now[i][j+1] +
                                now[i+1][j-1] + now[i+1][j] + now [i+1][j+1];
            //                                                                                      
            if(now[i][j] == Live)
            {
                switch(live_cells)
                {
                    case 0:
                    case 1: next[i][j] = Dead; break;
                    case 2:
                    case 3: next[i][j] = Live; break;
                    default: next[i][j] = Dead; break;
                }
            }
            if(now[i][j] == Dead)
            {
                    switch(live_cells)
                    {
                        case 3: next[i][j] = Live; break;
                        default: next[i][j] = Dead; break;
                    }
            }

        }
        //                                           
        for(int k = 0; k < ROWS-1; k++)
        {
            for(int l = 0; l < COLUMNS-1; l++)
                {
                    if( k == 0)
                        next[k][l] = Dead;
                    else if( l > 0 && l < COLUMNS - 2)
                        {
                            next[k][0] = Dead;
                            next[k][COLUMNS-1] = Dead;
                        }
                    else if( k == COLUMNS - 1)
                        next[k][l] = Dead;
                }

        }

    }
    //                        
    cout << "\nNew universe looks like: " << "\n";
    show_universe(next);
}

int main ()
{
    //                                                                                                      
    //                                                                              
    char filename [FILENAME_MAX];
    ifstream inputfile;
    Cell universe [ROWS][COLUMNS];
    Cell next_universe [ROWS][COLUMNS];

    enter_filename(filename);
    cout << "Filename is: " << filename << "\n";
    read_universe_file(inputfile, universe, filename);
    cout << "\nCurrent universe looks like: \n";
    show_universe(universe);
    next_generation(universe, next_universe);
    return 0;
}

