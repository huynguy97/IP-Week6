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
    assert (true);
    //                                                                                    

    cout << "Enter the name of the file: ";
    cin.get(filename, MAX_FILENAME_LENGTH);

    if(sizeof(filename)/sizeof(filename[0]) <= MAX_FILENAME_LENGTH)
    {
        //                                                     
        //                                                          
        return true;
    }
    else
        return false;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert (true);
    //                                                                                             
    char c;

    //                                                                                         
    for(int col = 0; col < COLUMNS; col++)
        for(int row = 0; row < ROWS; row++)
            universe[row][col] = Dead;

    //                                         
    for(int row = 1; row < ROWS-1; row++)
    {
        for(int col = 1; col < COLUMNS-1; col++)
        {
            inputfile.get(c);
            if(c == LIVE)
            {
                universe[row][col] = Live;
            }
        }
        inputfile.get(c);
    }

    return true;

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert (true);
    //                                

    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLUMNS; col++)
        {
            if(universe[row][col] == Dead)
                cout << DEAD;
            if(universe[row][col] == Live)
                cout << LIVE;
        }
        cout << endl;
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(true);
    //                                                                                 

    int livecount; //                                                

    for(int col = 0; col < COLUMNS; col++)
        for(int row = 0; row < ROWS; row++)
            next[row][col] = Dead;  //                                

    for (int c = 1; c < COLUMNS-2; c++)
    {
        for (int r = 1; r < ROWS-2; r++ )
        {
            livecount = 0;

            for(int i = -1; i<=1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    if(now[r+i][c+j] == Live && !(i == j && i == 0))    //                                                                                          
                    {
                        livecount++;
                    }
                }
            }
            //                 
                //                                                  
            if (now[r][c] == Live)                      //                                 
            {
                if(!(livecount < 2 || livecount > 3 ))
                    next[r][c] = Live;
            }
            else
                if(livecount == 3)
                    next[r][c] = Live;
        }
    }

}

int main ()
{
    assert (true);
    ifstream infile;
    char filename [MAX_FILENAME_LENGTH];
    Cell uni_now [ROWS][COLUMNS];
    Cell uni_next [ROWS][COLUMNS];
    if(!enter_filename(filename))
        cout<< "your filename is too long"<< endl; //                           
    infile.open(filename);

    read_universe_file(infile,uni_now);
    show_universe(uni_now);

    cout<< endl;
    for(int i; i<4;i++)                     //                                            
    {
        next_generation(uni_now, uni_next);
        show_universe( uni_next );
        for (int r = 0; r < ROWS; r++ )
            for (int c = 0; c < COLUMNS; c++ )
                uni_now[r][c] = uni_next[r][c];
        cout<< endl;
    }

}

