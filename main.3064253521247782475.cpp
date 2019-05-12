#include <iostream>
#include <fstream>
#include <cassert>

//                             
//                           

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
    assert(MAX_FILENAME_LENGTH>=0);
    //                                                
    //                                                                                
    cout << "Enter the name of the input file (must be at most 80 characters long): ";
    char c;
    int index = 0;
    do{
        if(index==MAX_FILENAME_LENGTH-1)return false;
        cin.get(c);
        filename[index] = c;
        index++;
    }while(c!='\n');
    filename[index-1] = '\0';
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(inputfile.is_open());
    //                                                
    //                                                                                          
    char c;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            if(i==0 || j==0 || i==ROWS-1 || j==COLUMNS-1){
                universe[i][j]=Dead;
                continue;
            }
            inputfile.get(c);
            if(c=='\n')inputfile.get(c);
            if(c=='.') universe[i][j] = Dead;
            if(c=='*') universe[i][j] = Live;
        }
    }
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(true);
    //                                                
    //                                                                                      

    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            if(universe[i][j]==Dead) cout << ".";
            if(universe[i][j]==Live) cout << "*";
        }
        cout << "\n";
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(true);
    //                                                
    //                                                                                 
    for(int i=1;i<=NO_OF_ROWS;i++){
        for(int j=1;j<=NO_OF_COLUMNS;j++){
            int aliveNeighbors = now[i-1][j-1]+now[i-1][j]+now[i-1][j+1]+now[i][j-1]+now[i][j+1]+now[i+1][j-1]+now[i+1][j]+now[i+1][j+1];
            if(now[i][j]==Dead){
                if(aliveNeighbors==3){
                    next[i][j]=Live;
                }else{
                    next[i][j]=Dead;
                }
                continue;
            }

            if(aliveNeighbors<2)next[i][j]=Dead;
            if(aliveNeighbors==2 || aliveNeighbors==3)next[i][j]=Live;
            if(aliveNeighbors>3) next[i][j]=Dead;
        }
    }
}

int main ()
{
    char input[MAX_FILENAME_LENGTH];
    enter_filename(input);
    ifstream textfile;
    textfile.open(input);

    Cell universe [ROWS][COLUMNS];
    read_universe_file(textfile, universe);

    Cell universeNext [ROWS][COLUMNS];
    next_generation(universe,universeNext);
    show_universe(universeNext);

    textfile.close();
}

