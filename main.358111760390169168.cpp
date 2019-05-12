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

    assert (MAX_FILENAME_LENGTH == 80);
    //               

    cout << "Please enter a filename"<<endl;
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++) {
        cin.get(filename[i]);
        if (filename[i] == '\n') {
            filename [i] = '\0';

            return true;

        }
    }
    return false;

}

//                           

bool read_universe_file (ifstream& InFile, Cell universe [ROWS][COLUMNS])
{
    //            
    assert(InFile.is_open());

    //             
    for (int i = 0; i < ROWS ; i++ ) {
        char c;

        for (int j = 0; j < COLUMNS; j++) {
            if (i == 0 || j == 0 || i==ROWS -1 || j == COLUMNS -1)
            {
                universe[i][j] = Dead;
            }
            else {
                InFile.get(c);
                if (c == DEAD) {

                    universe[i][j] = Dead;
                } else if (c == LIVE) {
                    universe[i][j] = Live;

                }
            }

        }
        if (i != 0)
        {
            InFile.get(c);
        }

    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                

    assert(true);

    for (int i = 0; i < ROWS ; i++ )
    {
        char c ;
        for (int j = 0; j < COLUMNS; j++) {

            if (universe[i][j] == Dead) {
                cout << DEAD;

            } else if (universe[i][j] == Live) {

                cout << LIVE;
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
    int alive_counter;
    for (int i = 0; i < NO_OF_ROWS ; i++ )
    {

        for (int j = 0; j < NO_OF_COLUMNS; j++)
        {
            alive_counter = 0;

            if(now[i+1][j+1]) {alive_counter++;}
            if(now[i+1][j]) {alive_counter++;}
            if(now[i+1][j-1]) {alive_counter++;}
            if(now[i][j+1]) {alive_counter++;}
            if(now[i][j-1]) {alive_counter++;}
            if(now[i-1][j+1]) {alive_counter++;}
            if(now[i-1][j]) {alive_counter++;}
            if(now[i-1][j-1]) {alive_counter++;}

            if (now [i][j] == Live)
            {
                if (alive_counter < 2 || alive_counter > 3)
                {
                    next [i][j] = Dead;
                }
                else
                {
                    next [i][j] = Live;
                }

            }
            else
            {
                if ( alive_counter == 3)
                {
                    next [i][j] = Live;

                }
            }

        }

//
    }

}

int main ()
{
    Cell universe [ROWS][COLUMNS];
    Cell now [ROWS][COLUMNS];
    Cell next [ROWS] [COLUMNS];
    char filename [MAX_FILENAME_LENGTH];
    enter_filename(filename);
    ifstream InFile;
    InFile.open(filename);

    read_universe_file(InFile, universe);
    show_universe(universe);
    cout << "The next generation is:"<< endl;
    next_generation(now, next );

    show_universe(next);

    return 0;

}

