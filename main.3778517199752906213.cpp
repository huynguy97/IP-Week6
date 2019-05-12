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
{//             
    assert(true);
    //              
    //                                                                                      

    cout << "Enter file name:" << endl;
    for(int i = 0; i <= MAX_FILENAME_LENGTH; i++)
    {
        //                                                                      
        //                               
        if(i == MAX_FILENAME_LENGTH)
        {
            cout << "Error! File name too long." << endl;
            return false;
        }

        cin.get(filename[i]);
        //                           
        if(filename[i] == '\n')
        {
            //                                          
            filename[i] = '\0';
            return true;
        }
    }

    //                                                                        
    cout << "Something went wrong." << endl;
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                           
    assert(inputfile && inputfile.is_open());
    //               
    //                                                                                            

    for(int row = 0; row < NO_OF_ROWS; row++)
    {//                       

        for(int col = 0; col <= NO_OF_COLUMNS; col++)
        {//                                                             

            char c;
            inputfile.get(c);

            if(!inputfile)
            {
                cout << "Error reading file.." << endl;
                return false;
            }

            if(c == '.')
                universe[row + 1][col + 1] = Dead;
            else if(c == '*')
                universe[row + 1][col + 1] = Live;
        }
    }

    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //              
    assert(true);
    //               
    //                                                                                                    

    for(int row = 0; row <= NO_OF_ROWS; row++)
    {
        for(int col = 0; col <= NO_OF_COLUMNS; col++)
        {
            bool alive = universe[row][col] == Live;
            if(alive)
                cout << '*';
            else
                cout << '.';
        }
        cout << endl;
    }
}

int check_adjacent(Cell universe [ROWS][COLUMNS], int row, int column)
{
    //             
    assert(row > 0 && column > 0);
    //              
    //                                                                                       

    int counter = 0;

    if (universe[row -1][column -1] == Live) //        
        counter++;
    if (universe[row -1][column] == Live) //    
        counter++;
    if (universe[row -1][column +1] == Live) //         
        counter++;
    if (universe[row][column +1] == Live) //      
        counter++;
    if (universe[row +1][column +1] == Live) //           
        counter++;
    if (universe[row +1][column] == Live) //     
        counter++;
    if (universe[row +1][column -1] == Live) //          
        counter++;
    if (universe[row][column -1] == Live) //    
        counter++;

    return counter;
}
//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //             
    assert(true);

    //              
    //                                                                                                                

    for(int row = 0; row < NO_OF_ROWS; row++)
    {
        for(int col = 0; col < NO_OF_COLUMNS; col++)
        {
            int adjacent_alive = check_adjacent(now, row + 1, col +1);

            switch (adjacent_alive)
            {

                case 2:
                    next[row +1 ][col +1] = now [row +1 ][col +1];
                    break;
                case 3:
                    next[row +1 ][col +1] = Live;
                    break;
                default:
                    next[row +1 ][col +1] = Dead;
                    break;
            }
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];

    if(!enter_filename(filename))
        return 1;

    ifstream inputfile(filename);
    Cell universe[ROWS][COLUMNS];

    if(read_universe_file(inputfile, universe))
        show_universe(universe);

    Cell next_universe[ROWS][COLUMNS];

    cout << endl << "Next generation:" << endl << endl;

    next_generation(universe, next_universe);

    show_universe(next_universe);

    return 0;
}

