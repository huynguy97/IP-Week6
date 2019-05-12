//                    
//                      

#include <iostream>
#include <fstream>
#include <cassert>
#include <string.h>
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
   int numbers [MAX_FILENAME_LENGTH];
   for (int c; c >= MAX_FILENAME_LENGTH; c++)
   {
       return true;
   }

}
Cell char_to_cell(char c){
//
if(c=='.')
{
    return Dead;
}
else if(c=='*')
{
    return Live;

}
}
//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    char c;
for(int i = 1; i < NO_OF_ROWS+1; i ++){
    for(int j = 1; j < NO_OF_COLUMNS+2; j++){
        inputfile.get(c);
            universe[i][j] = char_to_cell(c);

    }
for (int i = 0; i < COLUMNS; i ++)
    {
    universe[0][i] = Dead;
    }
for (int q = 0; q < COLUMNS; q ++)
    {
    universe[ROWS-1][q] = Dead;
    }
for (int j = 0; j < ROWS; j ++)
    {
    universe[j][0] = Dead;
    }
for (int r = 0; r < ROWS; r ++)
    {
    universe[r][COLUMNS-1] = Dead;
    }
}
    //       
}

void show_universe (Cell universe [ROWS][COLUMNS])
{

   //                                
      //                            
      for(int i = 1; i < NO_OF_ROWS+2; i ++){
        for(int j = 1; j < NO_OF_COLUMNS+2; j++){

        if (universe [i][j] == Dead)
        {
        cout << DEAD ;
        }
        else if (universe [i][j] == Live)
        {
            cout << LIVE ;
        }
    }
    cout << '\n';
    }
cout << '\n\n';
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                

}

int main ()
{
char c;
cout << "filename:" ;
string file_name;
cin >> file_name;
Cell universe[ROWS][COLUMNS];

ifstream input_file (file_name);
read_universe_file(input_file,universe);
show_universe(universe);
Cell now
Cell next;

}

