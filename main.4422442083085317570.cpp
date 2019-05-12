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
    //              
    //                                                                                                                                              
    char c;
    int index=0;
    cout<<"welcome to the game of life, which file would you like to open? ";
    c = cin.get();
    while(c!='\n')
    {
        filename[index]=c;
        index++;
        c = cin.get();
        if (index>=80)
        {
            cout<<"Over 80 characters terminating";
            return false;
        }
    }
    filename[index]='\0';
    cout <<"opening "<<filename<<endl;
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile,Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile);
    //              
    //                                                                                        
    char c;
    for(int indexx=1;indexx<=NO_OF_ROWS;indexx++)
    {
        for(int indexy=1;indexy<=NO_OF_COLUMNS;indexy++)
        {
            inputfile >> c;
            if(c==LIVE)
            {
                universe[indexx][indexy]=Live;
            }
            else
            {
                universe[indexx][indexy]=Dead;
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
    //                                                                      

    for(int indexx=1;indexx<=NO_OF_ROWS;indexx++)
    {
        for(int indexy=1;indexy<=NO_OF_COLUMNS;indexy++)
        {
            {
                if(universe[indexx][indexy]==Live)
                {
                    cout<<LIVE;
                }
                else
                {
                    cout<<DEAD;
                }
            }
        }
        cout<<endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //             
    //                                                                                

    for(int indexx=1;indexx<=NO_OF_ROWS;indexx++)
    {
        for(int indexy=1;indexy<=NO_OF_COLUMNS;indexy++)
        {
            int living=0;
            for(int x=-1;x<2;x++)
            {
                for(int y=-1;y<2;y++)
                {
                    if(x!=0 || y!=0)
                    {
                        if(now[indexx+x][indexy+y]==Live)
                        {
                            living++;
                        }
                    }
                }
            }
            switch (living)
            {

                case 1: next[indexx][indexy]=Dead; break;
                case 2: next[indexx][indexy]=now[indexx][indexy];break;
                case 3: next[indexx][indexy]=Live;break;
                default: next[indexx][indexy]=Dead;
            }
        }
    }
}
void makeabreak(int breakline)
{
    //             
    assert(breakline==1||breakline==0);
    //             
    //                                                               
    if(breakline==1)
    {
        cout<<endl;
        cout<<"==================second generation====================="<<endl;
        cout<<endl;
    }
    if (breakline==0)
    {
        cout<<endl;
        cout<<"==================first generation====================="<<endl;
        cout<<endl;
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    if(!enter_filename(filename))
    {
        return 0;
    }
    Cell universe[ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    ifstream input_file(filename);
    read_universe_file(input_file,universe);
    makeabreak(0);
    show_universe(universe);
    makeabreak(1);
    next_generation(universe,next);
    show_universe(next);
    return 0;
}

