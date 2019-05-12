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
    assert( true );
//                 
//                                                                                                                                                          
//                                                                                            
    char c;
    int i;

    cout << "Please enter a filename: ";
    cin.get(c);
    for( i = 0; c != '\n' && i < MAX_FILENAME_LENGTH; i++)//                                                                                                                      
    {
        filename [i] = c;
        cin.get(c);
    }
    if (i  == MAX_FILENAME_LENGTH)//                                                                                               
    {
        cout << "The filename you entered is too long! ";
        return false;
    }
    filename [i] = '\0';
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//               
    assert( true);
//                
//                                                                                                         
    char filename [MAX_FILENAME_LENGTH];
    if( !enter_filename ( filename) )//                                                      
    {
        return false;
    }

    inputfile.open( filename );
    if( !inputfile)//                                                   
    {
        cout << "File couldn't be opened. ";
        return false;
    }
    char c;

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            if(i==0||i==ROWS-1 || j==0 || j==COLUMNS-1)//          
            {
                universe [i][j] = Dead;
            }
            else
            {
                inputfile.get(c);
                if(c == '\n')//                                                   
                    inputfile.get(c);

                if(!inputfile)
                {
                    cout << "Something went wrong while reading the file. ";
                    return false;
                }
                if (c=='.')//                     
                    universe [i][j] = Dead;
                else//                        
                    universe [i][j] = Live;
            }
        }
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
//                
    assert( true );
//                 
//                                                              
//                                                                                           

    cout << "A new universe begins here:\n";
    for (int i=1;i<=NO_OF_ROWS;i++)//                          
    {
        for(int j=1;j<=NO_OF_COLUMNS;j++)
        {
            if (universe [i][j] == Live)
                cout << '*';
            else
                cout << '.';
        }
        cout << endl;
    }
    cout << endl;
}

//                             

int cell_to_int(Cell cell)
{
//                
    assert(true);
//                 
//                                                          
    if(cell == Dead)
        return 0;
    return 1;
}

int countcells(Cell universe [ROWS][COLUMNS], int i, int j)
{
//                
    assert(i>0 && i<ROWS-1 && j>0 && j<COLUMNS-1);//                                 
//                 
//                                                                        

    int cnt = 0;
    cnt += cell_to_int(universe [i-1][j-1]);//                                    
    cnt += cell_to_int(universe [i-1][j]);
    cnt += cell_to_int(universe [i-1][j+1]);
    cnt += cell_to_int(universe [i][j-1]);
    cnt += cell_to_int(universe [i][j+1]);
    cnt += cell_to_int(universe [i+1][j-1]);
    cnt += cell_to_int(universe [i+1][j]);
    cnt += cell_to_int(universe [i+1][j+1]);
    return cnt;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//                
    assert(true);
//                 
//                                                          
    int cnt;
    for (int i=0;i<ROWS;i++)
    {
        for (int j=0;j<COLUMNS;j++)
        {
            if(i==0||i==ROWS-1 || j==0 || j==COLUMNS-1)//          
            {
                next [i][j] = Dead;
            }
            else
            {
                cnt = countcells(now, i, j);
                if(cnt == 3)//                                                                    
                    next [i][j] = Live;
                else if(now [i][j]==Live && cnt == 2)//                                                                             
                    next [i][j] = Live;
                else//                       
                    next [i][j] = Dead;
            }
        }
    }
}

int main ()
{
    ifstream inputfile;
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    if(read_universe_file ( inputfile, universe))//                                             
    {
        show_universe(universe);
        next_generation(universe, next);
        show_universe(next);
    }
    else
    {
        cout << "Program aborted\n";
    }
}

