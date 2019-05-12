#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//                                              
//                                                   

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   
char filename[MAX_FILENAME_LENGTH];
//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert( true );
    //                                                                                  

    char c;
    cout << "enter a file name: \n";
    int index = 0;

//                                                                                             
    while(index < MAX_FILENAME_LENGTH)
    {
        cin.get(c);
        if(c == '\n')
        {
            c = '\0';
            filename[index] = c;
            return true;
        }
        else
        {
            filename[index] = c;
        }
        index++;

    }
    return false;

}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               

    //                
    //                                                         

    char c;
//             
    inputfile.open(filename);

//                                                           
    for(int row = 1; row < 41; row++)
    {
        for(int column = 1; column < 61; column++)
        {
            inputfile.get(c);
            if((c != '.') && (c != '*'))
            {
                inputfile.get(c);
            }
            if(c == '.')
            {
                universe[row][column] = Dead;
            }
            if(c == '*')
            {
                universe[row][column] = Live;
            }
        }
    }
    return true;
}

void show_universe (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(read_universe_file(inputfile, universe));
    //                                                                                 

    for(int row = 1; row < 41; row++)
    {
        for(int column = 1; column < 61; column++)
        {
            if(universe[row][column] == Live)
            {
                cout << "*" ;
            }

            if(universe[row][column] == Dead)
            {
                cout << "." ;
            }
        }

    cout << "\n";
    }
}

//                             
void next_generation (Cell universe [ROWS][COLUMNS], Cell next [ROWS][COLUMNS], ifstream& inputfile)
{
    //               
    assert(read_universe_file(inputfile, universe));

//                                                                                                                                                        
//                         
    int counter;
    for(int row = 1; row < 41; row++)
    {
        for(int column = 1; column < 61; column++)
        {
            if(universe[row][column] == Live)
            {
                if(universe[row-1][column-1] == Live) {counter++;}
                if(universe[row-1][column] == Live) {counter++;}
                if(universe[row-1][column+1] == Live) {counter++;}
                if(universe[row][column-1] == Live) {counter++;}
                if(universe[row][column+1] == Live) {counter++;}
                if(universe[row+1][column-1] == Live) {counter++;}
                if(universe[row+1][column] == Live) {counter++;}
                if(universe[row+1][column+1] == Live) {counter++;}

                if(counter < 2) {next[row][column] = Dead;}
                if(counter > 3) {next[row][column] = Dead;}
                if((counter == 2) || (counter == 3)) {next[row][column] = Live;}
                counter = 0;

            }

            if(universe[row][column] == Dead)
            {
                if(universe[row-1][column-1] == Live) {counter++;}
                if(universe[row-1][column] == Live) {counter++;}
                if(universe[row-1][column+1] == Live) {counter++;}
                if(universe[row][column-1] == Live) {counter++;}
                if(universe[row][column+1] == Live) {counter++;}
                if(universe[row+1][column-1] == Live) {counter++;}
                if(universe[row+1][column] == Live) {counter++;}
                if(universe[row+1][column+1] == Live) {counter++;}

                if(counter == 3) {next[row][column] = Live;}
                else {next[row][column] = Dead;}
                counter = 0;
            }
        }
    }
}

//                   
int main ()
{
    ifstream inputfile;
    Cell universe[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];

    enter_filename(filename);
    read_universe_file(inputfile, universe);

    show_universe(inputfile, universe);
    cout << "\n \n \n";
    next_generation(universe, next, inputfile);
    show_universe(inputfile, next);
}

