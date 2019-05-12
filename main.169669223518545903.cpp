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
    assert(true); //                                                        

    cout << "Enter a valid filename of the initial state: ";

    char c;

    for(int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(c);
        if(c == '\n')
        {
            filename[i] = '\0';
            cout << "The filename is: " << filename;
            return true;
        }
        else filename [i] = c;

    }
    return false;

    //               
    //                                                                                                            
}

//                           
void setFrame(Cell universe[ROWS][COLUMNS])
{
    //               
    assert(true); //                                                                          

    for(int i = 0; i < ROWS; i++)
    {
        if(i == 0 ||i == (ROWS - 1))
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                universe[i][j] = Dead;
            }
        }
        else
        {
            universe[i][0] = Dead;
            universe[i][COLUMNS - 1] = Dead;
        }
    }

    //               
    //                                                                             
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());

    setFrame(universe);
    cout << "Frame set" << endl;

    char c;
    for(int i = 0; i < NO_OF_ROWS; i++)
    {

        for(int j = 0; j <= NO_OF_COLUMNS; j++)
        {
            inputfile.get(c);
            switch(c)
            {
                case LIVE: if(j == NO_OF_COLUMNS) return false;
                            else universe[i+1][j+1] = Live;
                            break;
                case DEAD: if(j == NO_OF_COLUMNS) return false;
                            else universe[i+1][j+1] = Dead;
                            break;
                default: if(j != NO_OF_COLUMNS) return false;

            }
        }
    }
    return true;

    //               
    //                                                                    
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);  //                                                                          

    cout << endl << endl;
    for(int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            switch(universe[i][j])
            {
                case Live: cout << LIVE; break;
                case Dead: cout << DEAD; break;
                default: cout << "Something unexpected happened!" << endl; return;
            }

        }
        cout << endl;
    }
    cout << endl << endl;

    //               
    //                                                  
}

//                             
int countNeighbors(Cell now[ROWS][COLUMNS], int row, int column)
{
    //               
    assert(row < ROWS && row > 0 && column < COLUMNS && column > 0);  //                                                                          

    int neighbors = 0;
    for(int q = -1; q <= 1; q++)
    {
        for(int r = -1; r <= 1; r++)
        {
            if((q != 0 || r != 0) && now[row+r][column+q]) neighbors++;
        }
    }
    return neighbors;

    //               
    //                                                                               
}

void copyArrayAtoB(Cell a[ROWS][COLUMNS], Cell b[ROWS][COLUMNS])
{
    //               
    assert(true);  //                                                                          

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            b[i][j] = a[i][j];
        }
    }
    //               
    //                                                      
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);  //                                                                          

    for(int i = 1; i < (ROWS - 1); i++)
    {
        for(int j = 1; j < (COLUMNS - 1); j++)
        {
            int neighbors = countNeighbors(now, i, j);

            switch(neighbors)
            {
                case 0:
                case 1: next[i][j] = Dead;
                        break;
                case 2: if(now[i][j] == Live) next[i][j] = Live;
                        break;
                case 3: next[i][j] = Live;
                        break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8: next[i][j] = Dead;
                        break;
            }
        }
    }
    copyArrayAtoB(next,now);

    //               
    //                                                                                       
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    Cell universe [ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];
    ifstream inFile;

    if(!enter_filename(filename))
    {
        cout << "The filename was not valid" << endl;
        return 1;
    }
    else cout << endl << "Filename entered" << endl;

    inFile.open(filename);
    cout << "Try to open file" << endl;
    if(!inFile)
    {
        cout << "The file could not be opened" << endl;
        return 1;
    }
    else cout << "File was opened successfully" << endl;

    if(!read_universe_file(inFile, universe))
    {
        cout << "The universe could not be constructed from the text file" << endl;
        return 1;
    }
    else cout << "The universe was constructed from the text file" << endl;

    show_universe(universe);
    cout << "Universe shown" << endl;

    next_generation(universe, next);
    cout << "Next generation was computed" << endl;

    show_universe(universe);
    cout << "Universe shown" << endl;

    inFile.clear();
    inFile.close();
    if(!inFile)
    {
        cout << "The file could not be closed" << endl;
        return 1;
    }
    else cout << "File was closed successfully" << endl;

    return 0;
}

