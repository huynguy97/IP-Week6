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
    //                                                
    assert(true);
    //                                                         
    cout << "Please enter an input file: ";
    char a;
    int x = 0;
    /*                                                                 
                                                                                                                
                                  */
    while(x<82 && a != '\n')
    {

        cin.get(a);

        filename[x] = a;
        if(x > 80)
            return false;
        x++;
    }
    filename[x-1] = '\0';

    return true;
}

//                           

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(inputfile.is_open());
    //                                              

        char a;
        int x = 0;
        int c = 0;
        Cell n;
        /*                                                                                                                                 
                                                                        */
        while(x < ROWS)
        {
            while(c < COLUMNS)
            {
                if((x == 0 || x == ROWS - 1)||(c == 0 || c == COLUMNS - 1))
                    a = DEAD;
                else
                    inputfile.get(a);

                if (a == DEAD)
                    n = Dead;

                else if(a == LIVE)
                {
                    n = Live;
                }
                universe [x][c] = n;
                c++;
            }
            x++;
            c = 0;
        }

    return true;
}

/*                                                                                                                 */
void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(true);
    //                              

    char z;
    int x = 0;
    int c = 0;
    while(x < ROWS)
    {
        while(c < COLUMNS)
        {
            if(universe [x][c] == Dead)
                z = DEAD;
            else if(universe [x][c] == Live)
                z = LIVE;

            cout << z;
            c++;
        }

        cout << "\n";
        x++;
        c = 0;
    }

}

//                             
/*                                                                                   
                                                                */
int int_ops(Cell now [ROWS][COLUMNS],int x, int c)
{
    assert(true);
    //                                                            
    int v = 0;
    int h = 0;
    while(h < 3)
    {
        if(now[(x-1)+h][c-1] == Live)
        {
            v++;
        }
        if(now[(x-1)+h][c+1] == Live)
        {
            v++;
        }
        if(h != 1 && now[(x-1)+h][c] == Live)
        {
            v++;
        }
        h++;
    }

    return v;
}

//                                                                                                               
char next_state(Cell now [ROWS][COLUMNS],int x, int c)
{
    assert(c != 0 && x != 0);
    //                                                           
    int v = int_ops(now,x,c);

    if(now[x][c] == Live)
    {
        if(v < 2 || v > 3)
            return DEAD;
        else
            return LIVE;
    }
    else
    {
       if(v == 3)
            return LIVE;
        else
            return DEAD;
    }

}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(true);
    //                                               

        char a;
        int x = 0;
        int c = 0;
        Cell n;
        //                                                     
        while(x < ROWS)
        {
            while(c < COLUMNS)
            {
                if((x == 0 || x == ROWS - 1)||(c == 0 || c == COLUMNS - 1))
                    a = DEAD;

                //                                                                                                               
                else
                {
                   a = next_state(now,x,c);
                }

                if (a == DEAD)
                    n = Dead;

                else if(a == LIVE)
                {
                    n = Live;
                }
                   next[x][c] = n;
                c++;
            }
            x++;
            c = 0;

        }
}

/*                                                                       
                                                                     
                                                                 */
int main ()
{

    ifstream inputFile;
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];

    char filename[MAX_FILENAME_LENGTH];
    if(enter_filename (filename))
        inputFile.open(filename);
    else
    {
        cout << "error";
        return -1;cout << "45";
    }

    read_universe_file (inputFile, universe);

    show_universe (universe);

    next_generation (universe, next);

    cout << "\n\n\n\n";

    show_universe (next);

}

