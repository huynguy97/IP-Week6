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
    assert(true);
    cout<<"give a filename and end with \n"<<endl;
    for(int i=0; i<MAX_FILENAME_LENGTH; i++){
        cin.get(filename[i]);
        if (filename[i]== '\n') {
                filename[i] == '\0';
                return 1;
            }
        }
         return false;

    //                                                                                    
}
    //                                           

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                               
    assert(inputfile.open);

    for(int i=0; i<NO_OF_ROWS;i++ ){
        for(int i2=0; i2<NO_OF_COLUMNS; i2++){
            char c;
            inputfile.get(c);
            if(c==DEAD){
                universe[i][i2] = Dead;
                else if (c==LIFE){
                    universe[i][i2] = Live ;
                }
            }

        }
    }
//                                              

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(true)
    for (int r=0; r<ROWS; r++){
            for(int c=0; c<COLUMNS; c++){
                if
            }
            cout<<endl;

    }
    cout<<endl;
}
    //                                          
//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{

}

