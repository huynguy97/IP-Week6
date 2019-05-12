#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

enum Cell { Dead = 0, Live };                         //                                                                           

const char DEAD = '.';               //                                                          
const char LIVE = '*';               //                                                          
const int NO_OF_ROWS = 40;                //                                                                      
const int NO_OF_COLUMNS = 60;                //                                                                        
const int ROWS = NO_OF_ROWS + 2; //                                                                            
const int COLUMNS = NO_OF_COLUMNS + 2; //                                                                               

const int MAX_FILENAME_LENGTH = 80;              //                                                                                   

//                                
bool enter_filename(char filename[MAX_FILENAME_LENGTH])
{
    //               
    assert(true);
    //                
    //                                                                   
    cout << "Please enter a Filename with extension(.txt): ";
	cin.getline(filename, MAX_FILENAME_LENGTH);

	return (strlen(filename) <= MAX_FILENAME_LENGTH);
}

//                           
Cell cast_cell_from_char(char input_char)
{
    //               
    assert(input_char == DEAD || input_char == LIVE);
    //                
    //                                  
    if (input_char == LIVE)
        return Live;
    else
        return Dead;
}

bool read_universe_file(ifstream& inputfile, Cell universe[ROWS][COLUMNS])
{
    //               
    assert(inputfile);
	//                
	//                                                                                   
    for(int r = 0; r < ROWS; r++)
    {
        if (r == 0 || r == ROWS-1) //                         
        {
            for(int c = 0; c < COLUMNS; c++)
                universe[r][c] = Dead;
        }
        else
        {
            for(int c = 0; c < COLUMNS; c++)
            {
                if (c == 0 || c == COLUMNS-1) //                            
                    universe[r][c] = Dead;
                else
                    universe[r][c] = cast_cell_from_char(inputfile.get());
            }
            inputfile.ignore();
        }
    }
	return true;
}

void show_universe(Cell universe[ROWS][COLUMNS])
{
	//                
	assert(ROWS == NO_OF_ROWS + 2 && COLUMNS == NO_OF_COLUMNS + 2);
    //                                                 

    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLUMNS; c++)
        {
            if(universe[r][c] == Live)
                cout << LIVE;
            else
                cout << DEAD;
        }
        cout << endl;
    }
}

//                             
bool will_be_alive(Cell now[ROWS][COLUMNS], int r, int c)
{
    //               
    assert(r >= 1 && r <= NO_OF_ROWS);
    assert(c >= 1 && c <= NO_OF_COLUMNS);
    //                
    //                                                                                                                                  
    int alive_neigbohrs = 0;
    bool will_live = false;

    Cell neigbohrs [8] = {now[r][c+1], now[r][c-1], now[r+1][c], now[r-1][c], now[r+1][c+1], now[r+1][c-1], now[r-1][c+1], now[r-1][c-1]};

    for (int i = 0; i < 8; i++)
        alive_neigbohrs += neigbohrs[i];

    will_live = (alive_neigbohrs == 3 );
    if(!will_live)
        will_live = (alive_neigbohrs == 2 && now[r][c]);

    return will_live;
}

void next_generation(Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
    //               
    assert(ROWS == NO_OF_ROWS + 2 && COLUMNS == NO_OF_COLUMNS + 2);
	//                
    //                                                                                             
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLUMNS; c++)
        {
            if( c == 0 || c == COLUMNS-1)
                next[r][c] =  Dead;
            else if (r == 0 || r == ROWS-1)
                next[r][c] =  Dead;
            else
                next[r][c] =  static_cast<Cell>( will_be_alive(now, r, c) );
        }
    }
}

int main()
{
	char filename[80];
	Cell universe[ROWS][COLUMNS];
    ifstream inputfile;

    if (! enter_filename(filename))
        return -1;

    inputfile.open(filename);
    read_universe_file(inputfile, universe);
    inputfile.close();
    show_universe(universe);
    cout << "The following generation will look like this:" << endl;

    Cell next_gen[ROWS][COLUMNS];
    next_generation(universe, next_gen);
    show_universe(next_gen);
}

