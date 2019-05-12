/*
            
                        
                    
*/
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
    assert (MAX_FILENAME_LENGTH > 0);

    //                                                                                                  

    //               
    for (int i = 0 ; i < MAX_FILENAME_LENGTH ; i++)
    {
      if (filename[i] == '.' && filename[i+1] == 't' && filename[i+2] == 'x' && filename[i+3] == 't' )
         return true;
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              
    assert (inputfile.is_open()) ;
    //                                                                                  
    char c ;
    //                
    //                                                   
    for (int i = 0 ; i < ROWS ; i++ )
    {
        for (int j = 0 ;  j < COLUMNS ; j++)
        {
            universe[i][j] = Dead ;
        }
    }
    //                           
    for (int i = 1 ; i < ROWS ; i++ )
    {
        for (int j = 1 ;  j < COLUMNS ; j++)
        {
            inputfile.get(c) ;

            if (c == '.' || i==41 || j == 61)
                universe[i][j] = Dead ;
            else
                universe[i][j] = Live ;
        }
    }
    inputfile.close() ;

    if (!inputfile.is_open())
        return true ;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                                                          
    //                                                                                                        
    //               
    cout << endl ;
    cout << endl ;
    //                    
    for (int i = 0 ; i < ROWS ; i++)
    {
        for (int j = 0 ;  j < COLUMNS ; j++)
        {
            if (universe[i][j] == Dead)
               cout << "." ;
            else
                cout << "*" ;
        }
        cout << endl ;
    }
    cout << endl ;
    cout << endl ;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS] , Cell next [ROWS][COLUMNS])
{
    //                                                 
    //                                                                
    //                
  int live_cont ;

  //                                                                                                                         
  for (int i = 0 ; i < ROWS ; i++ )
   {
     for (int j = 0 ;  j < COLUMNS ; j++)
      {
         next[i][j] = now[i][j] ;
         live_cont = 0 ;

         //                                                                 
         if (i > 0 && j > 0  && i < ROWS && j < COLUMNS)
            {
             //                                                                                                                            
             for(int i2 = -1 ; i2 < 2 ; i2++)
               {
               for(int j2 = -1 ; j2 < 2 ; j2++)
                {
                   //                                                                                        
                  if (now[i + i2][j + j2] == Live && (i2 != 0 || j2 != 0))
                     live_cont ++ ;
                }
               }
              //                                         
              if (now[i][j] == Dead && live_cont == 3)
                next[i][j] = Live;
              if (now[i][j] == Live && ((live_cont < 2 )||(live_cont > 3)))
                next[i][j] = Dead;
            }
        }
    }
}

int main ()
{
    char file_name [MAX_FILENAME_LENGTH] ;
    Cell universe [ROWS][COLUMNS], next_universe [ROWS][COLUMNS] ;
    ifstream file ;

    cin.get(file_name, MAX_FILENAME_LENGTH) ;

    if(enter_filename(file_name))
    {
        cout << "Valid name inserted!" << endl ;
    }else
        cout << "Name not valid!" << endl ;

    file.open(file_name) ;

    if(file.is_open())
        cout << "file opened successfully!" << endl ;
         else
            cout <<"file not opened" << endl ;

    if(read_universe_file(file,universe) )
        cout << "File read successfully!" << endl ;

    cout << endl ;
    cout << endl ;

    cout << "Original Universe" << endl ;

    show_universe(universe) ;

    next_generation(universe,next_universe) ;

    cout << "Next Generation Universe" << endl ;

    show_universe(next_universe) ;

    if(!file.is_open())
        cout << "file closed correctly!" ;

    return 0 ;
}

