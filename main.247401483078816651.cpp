#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                
    assert(MAX_FILENAME_LENGTH>0);
    //                                                                            
    string s;
    cout<<"Enter the name of the file(max. 80 characters): ";       //                                                                      
    cin>>s;                                                         //                                                                   
    if(s.size()>MAX_FILENAME_LENGTH)
        return false;
    else
    {
        for(int i=0; i<MAX_FILENAME_LENGTH; i++)
            filename[i]=s[i];
        return true;
    }

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());
    //                                                                                         
    char a;

    for(int i=1; i<ROWS-1; i++)           //
        for(int j=1; j<COLUMNS-1; j++)    //                                                                          
        {
            a=inputfile.get();
            if(a=='\n')
                a=inputfile.get();
            else
            {
                if(a==LIVE)
                    universe[i][j]=Live;
                else
                    universe[i][j]=Dead;
            }
        }
    if(inputfile)
        return true;
    else
        return false;
}

void clear_universe(Cell universe[ROWS][COLUMNS]) //                                                    
{
    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLUMNS; j++)
            universe[i][j] = Dead;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(ROWS>0 && COLUMNS>0);
    //                                  
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLUMNS; j++)
        {
            if(universe[i][j]==Live)
                cout<<LIVE;
            else
                cout<<DEAD;
        }
        cout<<'\n';
    }

}

int check_neighbors(Cell universe[ROWS][COLUMNS],int x,int y)   //                                                      
{
    //               
    assert(ROWS>0 && COLUMNS>0);
    //                                                                  
    int count_live=0;
    bool is_live;
    if(universe[x][y]==Live)
        is_live=true;
    else
        is_live=false;
    for(int i=-1; i<2; i++)
        for(int j=-1; j<2; j++)
        {
            if(universe[x+i][y+j]==Live)
            {
                count_live++;
            }

        }
    if(is_live)
        count_live--;
    return count_live;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(ROWS>0 && COLUMNS>0);
    //                                                                            
    bool is_live;
    for(int i=1; i<ROWS-1; i++)
        for(int j=1; j<COLUMNS-1; j++)
        {
            if(now[i][j]==Live)
                is_live=true;
            else
                is_live=false;

            switch(is_live)
            {
            case false:
            {
                if(check_neighbors(now,i,j)==3)
                    next[i][j]=Live;
                else
                    next[i][j]=Dead;
                break;
            }
            case true:
            {
                if(check_neighbors(now,i,j)<2)
                    next[i][j]=Dead;
                else if(check_neighbors(now,i,j)>3)
                    next[i][j]=Dead;
                else
                    next[i][j]=Live;
                break;
            }
            }

        }
    show_universe(next);
}

int main ()
{
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    clear_universe(universe);
    ifstream infile;
    ofstream outfile("test.txt");
    int x,y;
    char a;
    char filename[MAX_FILENAME_LENGTH];
    cout<<"Which file do you want to output? ";
    cin>>filename;
    infile.open(filename);
    if(read_universe_file(infile, universe))
        show_universe(universe);
    else
        cout<<"File did not end last operation correctly";
    cout<<"This is the next generation: "<<endl;
    next_generation(universe,next);
}

