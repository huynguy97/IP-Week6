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
    assert(true);
    //                                 
    //                                                                                           
    cout << "please enter filename ";
    char a;
    int index_postition = 0;
    cin.get(a);
    while (a != '\n' && cin && index_postition < MAX_FILENAME_LENGTH)
    {
        filename[index_postition++] = a;
        cin.get(a);
    }
    if (index_postition < MAX_FILENAME_LENGTH)
    {
        filename[index_postition] = '\0';
        return true;
    }
    else
        return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
     assert(inputfile.is_open());
    //                               
    //                                                                                                            

     for (int j=0; j<COLUMNS; j++)
     {
         universe[0][j] = Dead; //                                            
         universe[NO_OF_ROWS+1][j] = Dead; //                                     
     }

     for (int i=1; i<NO_OF_ROWS+1; i++)
     {
        universe[i][0] = Dead; //                                                      
        universe[i][NO_OF_COLUMNS+1] = Dead; //                                                    
        char a;
        for (int j=1; j<NO_OF_COLUMNS+1; j++)
         {
             inputfile.get(a); //                                                                                                                
             if ( inputfile && DEAD == a)
                universe[i][j] = Dead;
            else
                if ( inputfile && LIVE == a)
                    universe[i][j] = Live;
                else
                    return false; //                                               
         }
         inputfile.get(a); //                                                   
     }
     return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert (true);
    //                                                                            

     for (int i=0; i<ROWS; i++)
     {
         for (int j=0; j<COLUMNS; j++)
         {
             if (Live == universe[i][j])
                cout << LIVE;
            else
                cout << DEAD;
         }
         cout << endl;
     }

}
int number_live_neigbours(Cell universe [ROWS][COLUMNS], int row_pos, int col_pos)
{
    //                
    assert(row_pos < ROWS-1 && col_pos < COLUMNS-1);
    //                                                                           

    int number_live_neigbours = 0;
    for (int i=row_pos-1; i< row_pos+2; i++)
    {
        for (int j=col_pos-1; j<col_pos+2; j++)
        {
            if (universe[i][j] == Live )
            {
                if ((i != row_pos) || (j != col_pos))  //                                                          
                    number_live_neigbours++;
            }
        }
    }

    return number_live_neigbours;

}
//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
        assert (true);
    //                                                                                                                      

     for (int j=0; j<COLUMNS; j++)
     {
         next[0][j] = Dead;
         next[NO_OF_ROWS+1][j] = Dead;
     }
     for (int i=1; i<NO_OF_ROWS+1; i++)
     {
        next[i][0] = Dead;
        next[i][NO_OF_COLUMNS+1] = Dead;
        for (int j=1; j<NO_OF_COLUMNS+1; j++)
        {
            if (now[i][j] == Dead)
             {
                 if (3 == number_live_neigbours(now,i,j))
                     next[i][j] = Live;
                 else
                    next[i][j] = Dead;
             }
             else
             {
                 if(2 == number_live_neigbours(now,i,j) || 3 == number_live_neigbours(now,i,j))
                    next[i][j] = Live;
                 else
                    next[i][j] = Dead;
             }
        }
     }

}

int main ()
{
    char filename[MAX_FILENAME_LENGTH];
    if (enter_filename(filename))
    {
        ifstream input_file(filename);
        if (input_file)
        {
            Cell now [ROWS][COLUMNS];
            Cell next [ROWS][COLUMNS];
            if (read_universe_file(input_file,now))
            {
                show_universe(now);
                next_generation(now,next);
                cout << endl;
                cout << "Next generation universe" << endl;
                show_universe(next);
            }
            else
                cout << "Reading file failed" << endl;

        }
        else
            cout << "could not open file " << filename << endl;
    }
    else
        cout << "Invalid filename" << endl;

}

