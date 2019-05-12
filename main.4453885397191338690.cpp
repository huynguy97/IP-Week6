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
    //                                                                              
    //                                                  
    char a;
    int i = 0;
    cin.get(a);
    while (a!='\n')
    {
        filename[i]=a;
        cin.get(a);
        i++;
        if (i == MAX_FILENAME_LENGTH)
            return false;
    }
    filename [i] = '\0';
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(inputfile.is_open());
    //                 
    //                                                              
    char c;
    for (int i=0; i < NO_OF_ROWS; i++)
    {
        for (int j=0; j < NO_OF_COLUMNS; j++)
        {
            inputfile.get(c);
            if (c=='\n')
                inputfile.get(c);
            if (c=='.')
                universe [i+1][j+1]=Dead;
            else
                universe [i+1][j+1]=Live;
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
    //                                         
    for (int i = 0; i< ROWS; i++){
        for (int j = 0; j < COLUMNS; j++){
            if(i==0||j==0||i==ROWS-1||j==COLUMNS-1){
                cout << '.';
            }
            else{
                if(universe[i][j]==0)
                    cout << '.';
                else
                    cout << '*';
            }
        }
        cout << '\n';
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                
    //                                                                                                   
    for (int i = 1; i<= NO_OF_ROWS; i++){
        for (int j = 1; j <= NO_OF_COLUMNS; j++){
            int counter = 0;
                for(int p = -1; p < 2 ; p ++){
                    for (int q = -1; q < 2; q++){
                        if (now[i+p][j+p]==Live){
                            counter++;
                        }
                    }
                }
            if (now[i][j]==Live){
                if (counter == 3 || counter == 4)
                    next[i][j] = Live;
                else
                    next[i][j] = Dead;
            }
            else{
                if (counter == 3)
                next[i][j] = Live;
                else
                    next[i][j] = Dead;
            }
        }
    }
}

int main ()
{
    char filename1 [MAX_FILENAME_LENGTH];
    ifstream inputfile;
    if (enter_filename (filename1))
        {
            inputfile.open(filename1);
        }
    else
        cout << "ERROR.";
    Cell universe [ROWS][COLUMNS];
    read_universe_file (inputfile, universe);
    show_universe(universe);
    Cell next [ROWS][COLUMNS];
    next_generation(universe, next);
    show_universe(next);
}

