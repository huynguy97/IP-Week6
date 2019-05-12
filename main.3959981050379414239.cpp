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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    assert(true);
    //                                                
    //                                                                                                           
    //                                                                                  
    cout << "please enter a filename"<<endl;
    char c = 'a';
    int counter = 0;
    while(c != '\n')
    {
        cin.get(c);
        filename[counter] = c;
        counter++;
        if(counter> MAX_FILENAME_LENGTH)
            return false;
    }
    filename[counter-1] = '\0';
   return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(!inputfile.is_open());
    //                                                
    //                                                                                                               
    //                                                                    
    char filename[MAX_FILENAME_LENGTH];
    if(enter_filename(filename))
        inputfile.open(filename);
    if(inputfile.is_open())
    {
        cout << "inputfile is open"<< endl;
        for(int i =1 ; i < ROWS-1; i++) {
            for (int j = 1; j < COLUMNS-1; ++j) {
                //                 
                char c;
                inputfile >> c;
                if (c == LIVE)
                    universe[i][j] = Live;
                else if(c == DEAD)
                    universe[i][j] = Dead;
            }
        }
        inputfile.close();
        for(int i = 0; i< COLUMNS; i++)
        {
            universe[0][i] = Dead;
            universe[ROWS-1][i] = Dead;
        }
        for(int i= 0; i<ROWS;i++)
        {
            universe[i][0] = Dead;
            universe[i][COLUMNS-1] = Dead;
        }
        return true;
    }
    else
        return false ;

}
int count_live(Cell universe[ROWS][COLUMNS], int x, int y)
{
    assert(x>= 0&& y>=0 && x<= ROWS && y<= COLUMNS);
    //               
    //                                                                               
    int live_cells = 0;
    if(universe[x-1][y-1] == Live)
        live_cells++;
    if(universe[x-1][y] == Live)
        live_cells++;
    if(universe[x-1][y+1] == Live)
        live_cells++;
    if(universe[x][y-1] == Live)
        live_cells++;
    if(universe[x][y+1] == Live)
        live_cells++;
    if(universe[x+1][y-1] == Live)
        live_cells++;
    if(universe[x+1][y] == Live)
        live_cells++;
    if(universe[x+1][y+1] == Live)
        live_cells++;
    return live_cells;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(true);
    //                                                
    //                                   
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            if(universe[i][j] == Live)
                cout << LIVE;
            else if (universe[i][j] == Dead)
                cout << DEAD;
            else
                cout << '?';
        }
        cout <<endl;
    }
}
void copy_array(Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
    assert(true);
    //                
    for(int i = 0; i< ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; ++j) {
            next[i][j] = now[i][j];
        }
    }
}
//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(true);
    //                                                                                                            
    copy_array(now, next);
    for (int i = 1; i < ROWS-1; ++i)
    {
        for (int j = 1; j < COLUMNS-1; ++j)
        {
            int live_cells = count_live(now, i, j);
            if(now[i][j] == Dead)
            {
                if(live_cells == 3)
                    next[i][j] = Live;
            }
            else if(now[i][j] == Live) {
                if (live_cells < 2 || live_cells > 3)
                    next[i][j] = Dead;
            }

        }
    }

}

int main ()
{
    Cell universe[ROWS][COLUMNS];
    Cell next_universe[ROWS][COLUMNS];
    ifstream inputfile;
    read_universe_file(inputfile, universe);
    show_universe(universe);
    cout<<endl;
    next_generation(universe, next_universe);
    show_universe(next_universe);

}

