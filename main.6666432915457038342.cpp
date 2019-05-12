#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
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
    //                                                                     
    char c;
    int i = 0;
    cout << "Please enter a filename and terminate with an enter:"<< endl;
    c = cin.get();//                                 
    while(c != '\n')//                                       
    {
        filename[i]=c;//                                
        i++;
        c = cin.get();//                       
    }
    filename[i]='\0';//                         
    if(i<MAX_FILENAME_LENGTH)//                                                          
    {
        return true;
    }
    else
    {
        return false;
    }

}

//                           

//                                               
void setup_universe(Cell universe [ROWS][COLUMNS])
{
    //             
    assert(true);
    //                                                          
    for(int i=0; i <ROWS;i++)
    {
        for(int x=0; x< COLUMNS; x++)
        {
            universe[i][x]= Dead;

        }
    }
}

bool open_file(ifstream& infile, char filename [MAX_FILENAME_LENGTH])
{
    assert(true);//                                   
    //                                              
    string file(filename);
    return infile.is_open();
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS], char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert(inputfile.is_open());
    //                                                                                      
    char c='c';
    open_file(inputfile, filename);
    for(int i=1; i <=NO_OF_ROWS;i++)
    {
        for(int x=1; x<= NO_OF_COLUMNS; x++)
        {
            inputfile >> c;
            if(c==DEAD)
            {
                universe[i][x]=Dead;

            }
            if(c==LIVE)
            {
                universe[i][x]=Live;
            }

        }
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                  
    for(int i=0;i<ROWS;i++)//                   
    {
        for(int x = 0; x<COLUMNS;x++)//            
        {
            if(universe[i][x]==Dead)
            {
                cout<< DEAD;
            }
            else if(universe[i][x]==Live)
            {
                cout << LIVE;
            }
        }
        cout<< "\n";//                                                          
    }
}

//                             

int count_alive_neighbours(Cell now[ROWS][COLUMNS], int row, int column)
{
    int alive= 0;
    //                                    
    for(int i = column-1; i <= column+1; i++)
    {
        Cell cell = now[row-1][i];//                                                                 
        if(cell==Live)
        {
            alive++;
        }
    }
    //                                                
    Cell cell = now[row][column-1];//                    
    if(cell==Live)
    {
        alive++;
    }
    cell = now[row][column+1];//                     
    if(cell==Live)
    {
        alive++;
    }
    //                                    
    for(int i = column-1; i<=column+1; i++)
    {
        Cell cell = now[row+1][i];//                                                                 
        if(cell==Live)
        {
            alive++;
        }
    }
    return alive;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                        
    int alive = 0;
    for(int row = 1; row <= NO_OF_ROWS; row++)//                    
    {
        for(int columns = 1; columns <= NO_OF_COLUMNS; columns++ )//            
        {
            alive = count_alive_neighbours(now, row, columns);//                                     
            switch(alive)//                                                                                                         
            {
                case 0:
                case 1:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8: next[row][columns] = Dead; break;
                case 2: if(now[row][columns]==Live)//                                                                 
                        {
                            next[row][columns]=Live;
                        }
                        else
                        {
                            next[row][columns]=Dead;
                        }
                        break;
                case 3: next[row][columns] = Live; break;
            }
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    Cell next [ROWS][COLUMNS];
    Cell universe [ROWS][COLUMNS];
    ifstream inputfile;

    enter_filename(filename);
    inputfile.open(filename);

    setup_universe(universe);//                          
    read_universe_file(inputfile, universe, filename);//                          
    show_universe(universe);//                                    
    cout << endl;//                                     
    setup_universe(next);//                                       
    next_generation(universe, next);//                              
    show_universe(next);//         
}

