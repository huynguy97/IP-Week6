//                                                                                                           
//                                                                                                                                     
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
//                                    

bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert ( true ) ;
    //                
    //                    
    //                   
    char slash = (92) ;
    int filenamelength ;
    cout << " Sadly, names with a space in them don't work. Please remove any spacebars from the filename and advise me on how to fix this for the next time" << endl;
    cout << " Enter the name of the file to load up the game of life " << endl;
    cin >> filename ;
    char current ; //                               
    for ( int index = 0; index < MAX_FILENAME_LENGTH ; index++ )
    {
        current = filename [index] ;
        if ( current == ' ')
            filename [index] = 32 ;
        if ((int) current == 10)
        {
            filename [index] = ' \0 ' ;
            return true ;
        }
        if ( index == MAX_FILENAME_LENGTH )
            {
                return false ;
            }
    }
}

//                           
bool read_universe_file (ifstream& infile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert (infile.is_open()) ;
    //                
    //                               
    //               
    char a;
    int c = 1; //       
    for ( int r = 1 ; r < 42 ; r++ ) //          
    {
        while ( c < 62 )
        {
            infile.get(a) ;
            universe [r][c] = (Cell) a ;
            c++ ;
        }
        c = 1 ;
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true) ;
    //                
    //                                           
    //                  
    char a ;
    int c = 1 ;
    for ( int r = 1 ; r < 41 ; r++)
    {
        while ( c < 62 )
        {
            a = (char) universe [r][c] ;
            c++ ;
            cout << a ;
        }
        c = 1 ;
    }
}

//                            
//      
//                                                                                  
//                                                 
//                                             
//                                                                                                                 
//                                                                                            
int check_live_adjecent ( int r, int c, Cell now [ROWS][COLUMNS] )
{
    //               
    assert (true) ; //                                                                 
    //               
    //                       
    int l ;
    if ((int)now [r-1][c] == 42)
        l++ ;
    if ((int)now [r+1][c] == 42)
        l++ ;
    if ((int)now [r][c-1] == 42)
        l++ ;
    if ((int)now [r][c+1] == 42)
        l++ ;
    if ((int)now [r-1][c-1] == 42)
        l++ ;
    if ((int)now [r-1][c+1] == 42)
        l++ ;
    if ((int)now [r+1][c-1] == 42)
        l++ ;
    if ((int)now [r+1][c+1] == 42)
        l++ ;
    return l ;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert ( true ) ; //                         
    //               
    //                                            
    //                   
    cout << " THE NEXT GENERATION " << endl;

    char a ;
    for (int r = 1 ; r < 42 ; r++ )
    {
        int c = 1 ;
        int l = 0 ;
        while ( c < 62 )
        {
            a = now [r][c] ;
            l = check_live_adjecent ( r, c, now ) ;
            if ( l < 2 && a == 42 )
                 a = 46 ;
            if ( l > 3 && a == 42 )
                 a = 46 ;
            if ( l == 3 && a == 46 )
                 a = 42 ;
            c++ ;
            next[r-1][c-1] = (Cell) a ;
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH] ;
    if ( !enter_filename( filename ))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    ifstream infile ;
    infile.open ( filename ) ;
    Cell universe [ROWS][COLUMNS] ;
    read_universe_file ( infile, universe ) ;
    Cell next_universe [ROWS][COLUMNS] ;
    next_generation ( universe, next_universe ) ;
    show_universe ( next_universe ) ;
    return 0 ;
}

