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
bool enter_filename (char filename [MAX_FILENAME_LENGTH], string& input_name)
{
    //                                                
    assert(true);
    //                                                  
    cout << "Please enter a file name with the (.txt) extension (MAX 80 Characters long):" <<endl;
    for (int i = 0 ; i < MAX_FILENAME_LENGTH+1; i++)
    {
        cin.get(filename[i]);
        if (filename[i] == '\n' && i <= 80)
        {
            filename[i] = '\0';
            i = MAX_FILENAME_LENGTH;
            input_name = filename;
        }
    }
    if (input_name.length() == 0)
    {
        return false;
    }
    else return true;

}

void populating_universe_with_dead(Cell universe [ROWS][COLUMNS])
{
    assert(true);
    //                                                 
    for (int i = 0; i < ROWS; i++)
    {
        for(int y = 0; y < COLUMNS; y++)
        {
            universe[i][y] = Dead;
        }
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS], string input_name)
{
    assert(input_name.length() != 0);
    //                                                           
    universe [ROWS][COLUMNS];
    inputfile.open(input_name.c_str());
    populating_universe_with_dead(universe);
    while(inputfile)
    {
        char letter;
        for(int i=1;ROWS>i;i++)
        {
            for(int u=1;COLUMNS>u;u++)
            {
                inputfile.get(letter);
                switch(letter)
                    {
                    case LIVE:
                    universe[i][u] = Live;
                    break;
                    case DEAD:
                    universe[i][u] = Dead;
                    break;
                    }

            }
        }

    }
    //                                                
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(true);
    //                                         
    //                                                
    for(int i=0 ; ROWS>i ; i++)
    {
        for(int u=0; COLUMNS>u;u++)
        {
            if(universe [i][u]==1)
            {
               cout <<'*' ;
            }
            else
                cout << '.';
        }
        cout << endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(true);
    //                                                        
    populating_universe_with_dead(next);
    for(int i=1;ROWS>i;i++)
        {
            for(int u=1;COLUMNS>u;u++)
            {
                int Nr_live_cells=0;
                    for(int o=-1;1>=o;o++)
                    {
                        for(int p=-1;1>=p;p++)
                        {
                            if(now[i+o][u+p]==Live){
                                Nr_live_cells++;
                            }
                        }
                    }

                if(now[i][u]==Live)
                {
                    Nr_live_cells--;
                    if(Nr_live_cells==3||Nr_live_cells==2)
                    {
                        next[i][u]=Live;
                    }
                    if(Nr_live_cells<2)
                    {
                        next[i][u]=Dead;
                    }
                    if(Nr_live_cells>3)
                    {
                        next[i][u]=Dead;
                    }
                }
                if(now[i][u]==Dead)
                {
                    if(Nr_live_cells==3)
                    {
                        next[i][u]=Live;
                    }
                    else
                        next[i][u]=Dead;
                }
            }
        }
        show_universe(next);

}

int main ()
{
    ifstream inputfile;
    string input_name;
    Cell universe [ROWS][COLUMNS];
    Cell next_universe [ROWS][COLUMNS];
    char filename[MAX_FILENAME_LENGTH];
    if(enter_filename(filename,input_name))
    {
        read_universe_file(inputfile, universe, input_name);
        show_universe(universe);
        cout << endl;
        next_generation(universe,next_universe);
    }
    else
    {
        cout << "Input file name invalid!";
    }
}

