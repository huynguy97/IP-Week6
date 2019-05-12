

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
    cout << "Enter filename" <<endl;
    cin.getline(filename, MAX_FILENAME_LENGTH); //                              
    assert(filename); //                              
    int i = 0;
    while(filename[i]) //                                  
    i++;
    if(i>MAX_FILENAME_LENGTH) //                                  
    {
        return false;
    }
    filename[i] = '\0'; //                                       
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{

    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename); //                           
    inputfile.open(filename); //              
    assert(inputfile.is_open()); //                                
    for (int i = 0 ; i < ROWS ; i++)
    {
        for (int j = 0 ; j < COLUMNS ; j++)
        {
            if (j==0 || j==COLUMNS-1 || i==0 || i==ROWS-1) //                                 
                universe[i][j] = Dead;
        }
    }

    char c;

    for (int row = 1 ; row < ROWS-1 ; row++)
    {
        for (int column = 1 ; column < COLUMNS-1 ; column++)
        {
                inputfile >> c;
                if(c=='.')
                {
                    universe[row][column] = Dead;
                }
                //          
                else
                {
                    universe[row][column] = Live; //                                                                              
                }
        }
        inputfile.ignore(); //                            

    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    for (int row = 0 ; row < ROWS ; row++)
    {
        for (int column = 0 ; column < COLUMNS ; column++)
        {
            if(universe[row][column]==Dead) //                    
                cout << DEAD ;
            else
                cout << LIVE ;
        }
        cout << "\n" ;
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(now && next); //                                                 
    for (int row = 0 ; row < ROWS ; row++)
    {
        for (int column = 0; column < COLUMNS ; column++) //                                 
        {
            if (column==0 || column==COLUMNS-1 || row==0 || row==ROWS-1) //                                   
                next[row][column] = now[row][column] ;
            else
            {
                int life_around = 0 ;
                life_around = now[row+1][column] + now[row-1][column] + now[row][column+1] + now[row][column-1] + now[row+1][column+1]
                + now[row+1][column-1] + now[row-1][column+1] + now[row-1][column-1] ; //                                                

                if(now[row][column]==Live) //                         
                {
                    if (life_around == 3)
                        next[row][column] = Live ;
                    else
                        next[row][column] = Dead ;
                }

                if(now[row][column]==Dead) //                       
                {
                        if (life_around == 2 || life_around == 3)
                            next[row][column] = Live ;
                        else
                           next[row][column] = Dead ;
                }
            }
        }
    }
}

int main ()
{

    Cell now [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    Cell universe [ROWS][COLUMNS];
    ifstream inputfile;
    read_universe_file(inputfile,now);
    show_universe(now);
    next_generation(now,next);
    cout <<endl;
    show_universe(next);
    return 0;

}

