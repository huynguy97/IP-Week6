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
{
    //              
    assert(true);
    /*               
                                                                     
                                                                      
    */
    char c;
    int k=-1;
    cin.get(c);
    while(c!='\n')
        {
            filename[++k]=c;
            cin.get(c);
        }
    filename[++k]='\0';
    if(k<=MAX_FILENAME_LENGTH)
        return true;
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              
    assert(inputfile.is_open());
    /*               
                                                                                     
                       
    */

    char c;
    int i,j;

    for(int i=1;i<ROWS-1;i++)
        for(int j=1;j<COLUMNS-1;j++)
            {
                inputfile>>c;
                if(c==DEAD)
                    universe[i][j]=Dead;
                else if(c==LIVE)
                    universe[i][j]=Live;
            }

    if(i==ROWS-1)
        return true;
    return false;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(true);
    /*                
                                                         
    */

    for(int i=1;i<ROWS-1;i++)
    {
        for(int j=1;j<COLUMNS-1;j++)
            if(universe[i][j]==Live)
                cout<<LIVE;
            else
                cout<<DEAD;
        cout<<endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert(true);
    /*                
                                                                        
    */

    for(int j=1;j<COLUMNS-1;j++)
        now[0][j]=now[ROWS-1][j]=Dead;
    for(int i=1;i<ROWS-1;i++)
        now[i][0]=now[i][COLUMNS-1]=Dead;

    for(int i=1;i<ROWS-1;i++)
        for(int j=1;j<COLUMNS-1;j++)
        {
            int cells_around_it;
            cells_around_it=now[i-1][j-1]+now[i-1][j]+now[i-1][j+1]+now[i][j-1]+now[i][j+1]+now[i+1][j-1]+now[i+1][j]+now[i+1][j+1];
            if(now[i][j]==Live)
            {
                switch(cells_around_it)
                {
                    case 1: next[i][j]=Dead; break;
                    case 2:
                    case 3: next[i][j]=Live; break;
                    default: next[i][j]=Dead; break;
                }
            }
            else if(cells_around_it==3)
                next[i][j]=Live;
        }
}

int main ()
{

    char filename[MAX_FILENAME_LENGTH];

    Cell universe[ROWS][COLUMNS], next[ROWS][COLUMNS];

    ifstream finput;

    if(enter_filename(filename))
        {
            finput.open(filename);
            read_universe_file(finput,universe);
            show_universe(universe);
            cout<<endl;
            next_generation(universe,next);
            show_universe(next);
        }
    else
        cout<<"File name is invalid";

    return 0;
}

