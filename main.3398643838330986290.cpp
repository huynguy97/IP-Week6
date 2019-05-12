#include <iostream>
#include <fstream>
#include <cassert>

//                                       
//                                 

using namespace std;

enum Cell {Dead = 0, Live};                         //                                                                          

const char DEAD             = '.';                  //                                                         
const char LIVE             = '*';                  //                                                         
const int NO_OF_ROWS        = 40;                   //                                                                     
const int NO_OF_COLUMNS     = 60;                   //                                                                       
const int ROWS              = NO_OF_ROWS + 2;       //                                                                           
const int COLUMNS           = NO_OF_COLUMNS + 2;    //                                                                              

const int MAX_FILENAME_LENGTH = 80;                 //                                                                                  

//                              
//                                                                                      
bool enter_filename(char filename[MAX_FILENAME_LENGTH])
{
    return true;
}

//                         
bool read_universe_file(ifstream& inputfile, Cell universe[ROWS][COLUMNS])
{
    //               
    assert(inputfile);
    assert(universe);
    //                
    //                                                                                                              

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            universe[i][j] = Dead;
        }
    }

    for (int i = 1; i <= NO_OF_ROWS; i++)
    {
        for (int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            char current_cell = inputfile.get();

            if (current_cell == DEAD)
            {
                universe[i][j] = Dead;
            }
            else if (current_cell == LIVE)
            {
                universe[i][j] = Live;
            }
            else if (current_cell == '\n')
            {
                j--;
            }
        }
    }
}

void show_universe(Cell universe[ROWS][COLUMNS])
{
    //               
    assert(universe);
    //                
    //                                                                            

    for (int i = 1; i <= NO_OF_ROWS; i++)
    {
        for (int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            if (universe[i][j] == Dead)
            {
                cout << DEAD;
            }
            else if (universe[i][j] == Live)
            {
                cout << LIVE;
            }
        }
        cout << '\n';
    }
}

//                           
void next_generation(Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
    //               
    assert(now);
    assert(next);
    //                
    //                                                                                                             

    for (int i = 1; i <= NO_OF_ROWS; i++)
    {
        for (int j = 1; j <= NO_OF_COLUMNS; j++)
        {
            int live_neighbours = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (!(k == 0 && l == 0) && (now[i+k][j+l] == Live))
                    {
                        live_neighbours++;
                    }
                }
            }
            if ((now[i][j] == Live) && ((live_neighbours < 2) || (live_neighbours > 3)))
            {
                next[i][j] = Dead;
            }
            else if ((now[i][j] == Dead) && (live_neighbours == 3))
            {
                next[i][j] = Live;
            }
            else
            {
                next[i][j] = now[i][j];
            }
        }
    }
}

int main()
{
    cout << "enter the file you wish to open:\n";
    char filename[MAX_FILENAME_LENGTH];             //       
    cin.getline(filename, sizeof(filename));        //                                                                    

    ifstream inputfile;
    inputfile.open(filename, std::fstream::in);

    Cell universe[ROWS][COLUMNS];

    read_universe_file(inputfile, universe);

    Cell next[ROWS][COLUMNS];

    next_generation(universe, next);
    show_universe(next);

    inputfile.clear();
    inputfile.close();
    return 0;
}

