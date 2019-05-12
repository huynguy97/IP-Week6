//                        

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
    assert ( true );
//                
//                                                                                                            

    cout << "Please enter a filename which contains at most 80 characters." << endl;

    int i = 0;
    char ch;
    ch = cin.get();

    while ( ch != '\n' && i < MAX_FILENAME_LENGTH )
    {
        filename[i] = ch;
        i++;
        ch = cin.get();
    }
    if ( ch != '\n' )
    {
        return false;
    }

    filename[i] = '\0';
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//               
    assert ( inputfile.is_open() );
//                  
//                                                       

    char x;

    for ( int r = 0; r < ROWS; r++ )
    {
        for ( int c = 0; c < COLUMNS; c++ )
        {
            universe[r][c] = Dead;
        }
    }

    for ( int r = 1; r <= NO_OF_ROWS; r++ )
    {
        for ( int c = 1; c <= NO_OF_COLUMNS; c++ )
        {
            inputfile >> x;
            if ( x == '*' )
            {
                universe[r][c] = Live;
            }
            else if ( x == '.' )
            {
                universe[r][c] = Dead;
            }
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//               
    assert ( true );
//                
//                                       

    for ( int r = 0; r < ROWS; r++ )
    {
        for ( int c = 0; c < COLUMNS; c++ )
        {
            if (universe[r][c] == Dead)
            {
                cout << DEAD;
            }
            if (universe[r][c] == Live)
            {
                cout << LIVE;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//               
    assert ( true );
//                
//                                                     
//                                                                                           
//                                                                                  
//                                                                                 
//                                                                                                                               

    for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLUMNS; c++)
		{

			int LiveCnt = 0;
			if (now[r-1][c-1] == Live)
			{
				LiveCnt++;
			}
			if (now[r-1][c] == Live)
			{
				LiveCnt++;
			}
			if (now[r+1][c] == Live)
			{
				LiveCnt++;
			}
			if (now[r-1][c+1] == Live)
			{
				LiveCnt++;
			}
			if (now[r][c-1] == Live)
			{
				LiveCnt++;
			}
			if (now[r][c+1] == Live)
			{
				LiveCnt++;
			}
			if (now[r+1][c-1] == Live)
			{
				LiveCnt++;
			}
			if (now[r+1][c+1] == Live)
			{
				LiveCnt++;
			}

			next[r][c] = Dead;

			if (now[r][c] == Live && LiveCnt < 2)
            {
                next[r][c] = Dead;
            }
            else if (now[r][c] == Live && (LiveCnt == 2 || LiveCnt == 3))
            {
                next[r][c] = Live;
            }
            else if (now[r][c] == Live && LiveCnt > 3)
            {
                next[r][c] = Dead;
            }
            else if (now[r][c] == Dead && LiveCnt == 3)
            {
                next[r][c] = Live;
            }

		}

	}

	for (int r = 1; r < NO_OF_ROWS + 1; r++)
    {
        for (int c = 1; c < NO_OF_COLUMNS + 1; c++)
        {
            now[r][c] = next[r][c];
        }
    }

}

int main ()
{
    char filename1[MAX_FILENAME_LENGTH];
    enter_filename(filename1);

    ifstream inputfile;
    inputfile.open(filename1);
    if (inputfile)
    {
        cout << "File opened succesfully" << endl;
    }

    Cell universe[ROWS][COLUMNS];

    read_universe_file(inputfile, universe);
    show_universe(universe);
    Cell next[ROWS][COLUMNS];

    for ( int l=0; l<10; l++)
    {
        next_generation(universe, next);
        show_universe(universe);
    }
    return 0;
}

