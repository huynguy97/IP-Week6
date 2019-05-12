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

const int MAX_FILENAME_LENGTH = 80;              //                                                                                   
//                                      
//                         
//                                      
//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    assert(filename);//                         
    cout << "Enter a filename with a maximum of  " << MAX_FILENAME_LENGTH-1 << " characters:\n";
    cin.getline(filename,99999); //                               
    int i = 0;
    while (filename[i])
    {
        i++;
    }
    if (i < MAX_FILENAME_LENGTH)
    {
        filename[MAX_FILENAME_LENGTH-1] = '\0'; //                              
        return true;
    }
    else
    {
        return false;
    }
    //                                                                                                                                                 
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(inputfile && universe);//                                       
    char filename[MAX_FILENAME_LENGTH];
    bool succeeded = enter_filename(filename);
    if (succeeded)
    {
        inputfile.open(filename);
        char c;
        int rownr = 1;
        int columnnr = 1;
        inputfile.get(c);
        for (int i = 0; i < COLUMNS; i++) //                 
        {
            for (int j = 0; j < ROWS; j++)
            {
                if(i == 0 || j == 0 || i == COLUMNS-1 || j == ROWS-1)
                {
                    universe[j][i] = Dead;
                }
            }
        }
        while(inputfile) //                                                        
        {
            switch(c)
            {
                case '.':
                    universe[rownr][columnnr] = Dead;
                    columnnr++;
                    break;
                case '*':
                    universe[rownr][columnnr] = Live;
                    columnnr++;
                    break;
                case '\n':
                    columnnr = 1;
                    rownr++;
                    break;
            }
            inputfile.get(c);
        }
        return true;
    }
    else
    {
        return false;
    }
    //                                                                                                                   
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(true); //                                                                                   
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            switch(universe[i][j])
            {
                case Dead: cout << '.'; break;
                case Live: cout << '*'; break;
            }
        }
        cout << '\n';
    }
    //                                                        
}

//                             
int count_neigbours(Cell universe [ROWS][COLUMNS], int row, int column)
{
    assert(true);//                
    int amount_alive = universe[row-1][column-1] + universe[row-1][column] + universe[row-1][column+1] + universe[row][column-1] + universe[row][column+1] + universe[row+1][column-1] + universe[row+1][column] + universe[row+1][column+1];
    return amount_alive;
    //                                                                         
}
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(now && next);//                           
    int amount_alive = 0;
    for (int i = 0; i < COLUMNS; i++) //                                           
        {
            for (int j = 0; j < ROWS; j++)
            {
                if(i == 0 || j == 0 || i == COLUMNS-1 || j == ROWS-1)
                {
                    next[j][i] = Dead;
                }
            }
        }
    for (int i = 1; i < ROWS-1; i++) //                                                     
    {
        for (int j = 1; j < COLUMNS-1; j++)
        {
            amount_alive = count_neigbours(now, i, j);
            switch(now[i][j]) //                                                                   
            {
            case Dead:
                {
                    if (amount_alive == 3)
                    {
                        next[i][j] = Live;
                    }
                    else
                    {
                        next[i][j] = Dead;
                    }
                    break;
                }
            case Live:
                {
                   if (amount_alive == 2 || amount_alive == 3)
                   {
                       next[i][j] = Live;
                   }
                   else
                   {
                       next[i][j] = Dead;
                   }
                   break;
                }
            }

        }
    }
    //                                                    
}

int main ()
{
    ifstream input_file;
    Cell universe1 [ROWS][COLUMNS];
    Cell universe2 [ROWS][COLUMNS];
    read_universe_file(input_file, universe1);
    cout << "=====================The First Universe======================\n";
    show_universe(universe1);
    cout << "=====================The Second Universe=====================\n";
    next_generation(universe1, universe2);
    show_universe(universe2);
    return 0;
}

