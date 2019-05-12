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
    assert (true);
    //               
    //                                                                                             
    //                                                                         

    cout << "Please enter the name of a file, including the file extension. The file may contain spaces." << endl;

    bool break_out = false;

    int c = 0;
    char C;
    while (c < MAX_FILENAME_LENGTH && !break_out)
    {
        cin.get (C);

        if (C == '\n')
        {
            break_out = true;
            filename[c] = '\0';
            cout << "Filename successfully entered" << endl;
        }
        else
        {
           filename[c] = C;
        }

        c++;
    }

    return break_out;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //              
    assert (inputfile.is_open());
    //               
    //                                                                                   

    char e;

    for (int d = 0; d < ROWS; d++)
    {
        for (int f = 0; f < COLUMNS; f++)
        {
            if (d == 0 || d == ROWS-1 || f == 0 || f == COLUMNS-1)
                universe[d][f] = Dead;
            else
            {
                inputfile.get(e);
                if (e == '\n')
                    inputfile.get(e);

                if (e == DEAD)
                    universe[d][f] = Dead;
                else if (e == LIVE)
                    universe[d][f] = Live;
            }
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert (true);
    //               
    //                                                                                   

    for (int d = 0; d < ROWS; d++)
    {
        for (int f = 0; f < COLUMNS; f++)
        {
            if (universe[d][f] == Dead)
                cout << ".";
            else if (universe[d][f] == Live)
                cout << "*";
        }

        cout << "\n";
    }
}

//                     
int live_neighbors(int d, int f, Cell now[ROWS][COLUMNS])
{
    //              
    assert (d > 0 && f > 0);
    //               
    //                                                    

    int counter = 0;

        if (now[d+1][f] == Live) counter++;
        if (now[d-1][f] == Live) counter++;
        if (now[d][f+1] == Live) counter++;
        if (now[d][f-1] == Live) counter++;
        if (now[d+1][f+1] == Live) counter++;
        if (now[d-1][f-1] == Live) counter++;
        if (now[d-1][f+1] == Live) counter++;
        if (now[d+1][f-1] == Live) counter++;

        return counter;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert (true);
    //               
    //                                                                                                        
    //                                                     
    //                                                                     
    //                                                    
    //                                                            

    for (int d = 1; d < NO_OF_ROWS; d++)
    {
        for (int f = 1; f < NO_OF_COLUMNS; f++)
        {
            int counter = live_neighbors(d,f,now);

            switch (counter)
            {
                case 0:
                case 1:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8: next[d][f] = Dead; break;
                case 2:
                    if (now[d][f] == Dead)
                        next[d][f] = Dead;
                    else
                        next[d][f] = Live; break;
                case 3: next[d][f] = Live; break;
            }
        }
    }
}

int main ()
{
    char file1[MAX_FILENAME_LENGTH];
    char filename;
    enter_filename(file1);

    ifstream file(file1);
    Cell universe[ROWS][COLUMNS];
    read_universe_file(file,universe);

    cout << "First configuration:" << endl;

    show_universe(universe);

    cout << endl;
    cout << "Next configuration:" << endl;

    Cell next[ROWS][COLUMNS];
    next_generation (universe,next);
    show_universe(next);

    return 0;
}

