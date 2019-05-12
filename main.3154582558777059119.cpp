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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{   //              
    assert(true);
    //                                                                                       
    int i=0;
    while(i<=MAX_FILENAME_LENGTH)
    {
        cin.get(filename[i]);
        if(filename[i]=='\n')
        {
            filename[i] = '\0';
            return true;
        }
        i++;
    }

     return false;
}

//                           

char convert_cell_to_char(Cell a)
{
    //             
    assert(true);
    //                                   
    if(a==Live)
        return '*';
    else
        return '.';
}

Cell convert_char_to_cell(char a)
{
    //             
    assert(true);
    //                                    
    if(a=='*')
        return Live;
    else
        return Dead;
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//                
    assert(inputfile.is_open());
    //                                                                                                  

    char c;
    for(int i=0;i<ROWS;i++)
    {
        universe[i][0]=Dead;
        universe[i][COLUMNS-1]=Dead;
    }

    for(int j=0;j<COLUMNS;j++)
    {
        universe[0][j]=Dead;
        universe[ROWS-1][j]=Dead;
    }
    for(int i =0;i<NO_OF_ROWS;i++)
    {
        for(int j=0;j<NO_OF_COLUMNS;j++)
        {
            inputfile >> c;
            //         
            universe[i+1][j+1] = convert_char_to_cell(c);
        }
        cout<< endl;
    }
     if(c=='\0') return true;
     else return false;

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //             
    assert(true);
    //                                                  
    for(int i=0;i<ROWS;i++)
    {for(int j=0;j<COLUMNS;j++)
        cout<<convert_cell_to_char(universe[i][j]);
    cout<<endl;}
    }

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert(true);
    //                                                
    for(int i=1;i<ROWS-1;i++)
    {
        for(int j=1;j<COLUMNS-1;j++)
        {
            int No_of_live_neighbours=0;
            for(int k=-1;k<2;k++)
            {
                for(int l=-1;l<2;l++)
                {
                    if (now[i-k][j-l] == Live)
                        No_of_live_neighbours++;
                }
            }
            if(now[i][j] == Live)
                No_of_live_neighbours--; //                                                                  
            if(No_of_live_neighbours<2 || No_of_live_neighbours >3)
                next[i][j] = Dead;
            else if((No_of_live_neighbours==2&&now[i][j]==Live)|| No_of_live_neighbours==3)
                next[i][j] = Live;
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    Cell now [ROWS][COLUMNS];
    //                                      
    //                             
    ifstream inputfile;

    if (enter_filename(filename))
        inputfile.open(filename);
    else cout<<"Error: File couldn't be opened.";

    cout<<read_universe_file(inputfile,universe)<<endl;
    show_universe(universe);

    cout<<"Next configuration:"<<endl;
    next_generation(universe,next);
    show_universe(next);

    return 0;

    /*                                                            

                                                 

                                  
                     
         
                         
         
            
         
                                                                  
                          
         */

}

