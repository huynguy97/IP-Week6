#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;
//                                               

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

void get (char& a)
{

}

void put (char b)
{

}

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (true);
    //                                                                                                                                                    
    cout << "Please enter the file name:" ;
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++) {
        cin.get(filename[i]);
        if (filename[i] ==  '\n' ) {
            filename[i] = '\0' ;
            return true;
        }
    }

    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true) ;
    //                                                                         

string filename ;
ifstream inputfile.open (filename.c_str);
int character_nr = 0;
char c ;
inputfile.get (c);
while (inputfile.open)
{
    int r;
    int j;
    for (int j = 2; int r = 2 ; j <= ROWS; r <= COLUMNS; j++ ; r++ )
    {
        universe [j] = c [r] = c ;
    cout << universe [j] [r];
    character_nr++ ;
    inputfile.get (c);
    }
}
return true ;

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (inputfile.is_open );
    //                                                                                                                                               
 int j;
 int r;
 int cell [j][r] = {{ROWS},{COLUMNS}};
 for (int j=0; j< ROWS ; j++)
 {
     for ( r=0; r< COLUMNS ; r++)
        cout << cell [j] [r]; " ";
 }
    cout << endl;

}

//                             

bool under_population ( int j, int r)
{
    if ( [j+1] == 1 || [j-1] == 1 && [r+1] == 1 || [r-1] == 1 )
    {
        result false;
    }
    else
    {
        result true;
    }
}
bool overcrowded ( int j, int r)
{
    if ( [j+1]==1)&& [j-1}==1 && [r+1]==1 && [r-1]==1 )
    {
        result true;
    }
    else
    {
        result false;
    }
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert  ( (2<=j && j<40) && (2<=r && r<40) )
    //                                                                                                      

if ( cell [j] [r]==1)
{
    {
        switch ( cell )
        {
        case under_population(j, r) == true : cell [j][r] = 0 ; break ;
        case overcrowded (j, r) == true : cell [j][r] = 0 ; break ;
        default : cell [j][r] == 1 ; break;
        }
        cout << cell [j][r] ;
    }
    else {
            if( overcrowded(j, r) == true)
            {
                cell [j][r] = 1 ;
            }
            cout << cell [j] [r] ;
}

}

int main ()
{
ifstream inputfile;
string filename;
enter_filename ( filename  [80]) ;
int j;
int r;
read_universe_file (inputfile, universe [ROWS][COLUMNS]);
show_universe (universe [ROWS][COLUMNS]);
next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS]);

return 0;

}

