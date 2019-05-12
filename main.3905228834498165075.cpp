#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>

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
    assert(true);

    cout<<"What is the name of the file? please include the file extension(.exe, enz)";
    cin.getline(filename, MAX_FILENAME_LENGTH);
    if (strlen(filename) >= MAX_FILENAME_LENGTH)
    {
        cout<<"Please make sure the name of the file is not longer than the max filename length."<<endl;
        return false;
    }
    return true;
    //                                                                                
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(universe [ROWS][COLUMNS]);
    if (inputfile.is_open())
    {
        universe[ROWS][COLUMNS];
        return true;
    }
    return false;
    //                
}

void show_universe (ifstream& inputfile, Cell universe [ROWS][COLUMNS], int x[40*60], int y[40*60], int k, int length)
{
    assert(universe [ROWS][COLUMNS]);

    char cell;
    int livecell [40*60];
    int i =1;
    int correct =0;
    while (inputfile.get(cell))
    {
        cout<<cell;
        if (int(cell) == 42)
        {
            livecell[k] = i;
            k++;
        }
        i++;
        correct++;
        if (correct%60 == 0)
        {
            i--;
            correct = 0;
        }
    }
    i = 0;
    int value;
    int cellrow;
    int cellcol;
    for (i; i < k;i++)
    {
        value = livecell[i];
        cellrow = value/60+1;
        cellcol = value%60;
        cout<<cellrow<<"\t"<<cellcol<<endl;
        universe[cellrow][cellcol] = Live;
        x[i] = cellrow;
        y[i] = cellcol;
        cellcol = 0;
    }
    length = k;
    //                                           
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS], int x[40*60], int y[40*60], int k)
{
    assert(now [ROWS][COLUMNS]);

    int i =0;
    int q =0;
    int liveround = 0;
    cout<<x[0];
    for (i;i<k;i++)
    {
        if (now[x[i]][y[i]+1] == 1)
        {
            liveround++;
        }
        if (now[x[i]][y[i]-1] == 1)
        {
            liveround++;
        }
        if (now[x[i]-1][y[i]] == 1)
        {
            liveround++;
        }
        if (now[x[i]+1][y[i]] == 1)
        {
            liveround++;
        }
        if (now[x[i]-1][y[i]-1] == 1)
        {
            liveround++;
        }
        if (now[x[i]-1][y[i]+1] == 1)
        {
            liveround++;
        }
        if (now[x[i]+1][y[i]-1] == 1)
        {
            liveround++;
        }
        if (now[x[i]+1][y[i]+1] == 1)
        {
            liveround++;
        }
        if (liveround > 3)
        {
            next[x[i]][y[i]] == 0;
        }
        if (liveround < 2)
        {
            next[x[i]][y[i]] == 0;
        }
        else
        {
            next[x[i]][y[i]] == 1;
        }
    }
    i = 1;
    q = 1;
    for (i; i<=ROWS;i++)
    {
        for(q; q<=COLUMNS;q++)
        {
            if (next[i][q] == 0)
            {
                cell = '.';
            }
            else
            {
                cell = '*';
            }
            if (q == COLUMNS)
            {
                cout<<"\n";
            }
            cout<<cell;
        }
        q =0;
    }
    //                                                    
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    while(!enter_filename(filename));
    string name(filename);
    ifstream inputfile (name);
    Cell universe [ROWS][COLUMNS];
    int k =0;
    int length =0;
    int x[40*60];
    int y[40*60];
    show_universe(inputfile,universe,x,y,k,length);
    Cell now [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];
    cout<<"k is "<< length<<endl;
    int q =0;
    int i =0;
    for (i; i<=ROWS;i++)
    {
        for(q; q<=COLUMNS;q++)
        {
            now[i][q] = universe[i][q];
        }
        q =0;
    }
    next_generation(now, next, x, y, k);

    inputfile.close();
}

