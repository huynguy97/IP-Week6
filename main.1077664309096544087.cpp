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
bool enter_filename (char filename [MAX_FILENAME_LENGTH]) {
    //               

    //                                
    char name;
    cout << "Enter a file name:, including the file extension .txt (The max length of the file name is 80 characters)\n";

 }

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                

    //                                

    string infilename;
    cout << "Enter the file you want to open.\n";
    cin >> infilename;
    inputfile.open(infilename.c_str());
    if (inputfile) {
        cout << "You opened the file.\n";
        }
        else {
            cout << "File could not be opened!\n";
        }
    Cell value;
    char character;
    int row=0, column=0;
    while (inputfile){
        inputfile.get(character);
        if (character == 42 || character ==46){
            if (character == 42){
                value = Live;
            }
            if (character == 46){
                value = Dead;
            }
            universe [row][column]=value;
            column++;
        }
        else {
            row++;
            column = 0;
        }
    }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    int row = 0, column = 0;
    while (row < ROWS){
        while (column < COLUMNS){
            if (universe [row][column]==1){
                cout << "*";

            }
            if (universe [row][column]==0){
                cout << ".";
            }
            column++;
        }

        cout << endl;
        row++;
        column=0;
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
    Cell universe [ROWS][COLUMNS];
    ifstream infile;
    read_universe_file(infile, universe);
    show_universe(universe);
}

