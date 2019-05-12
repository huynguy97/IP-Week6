#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <unistd.h>
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

    //                                                                                         
    string input = "";
    cout << "Enter a filename to open, of max length " << MAX_FILENAME_LENGTH << " ." << endl;
    int l = 0;
    char c;
    while(c != '\n'){
        c = cin.get();
        filename[l] = c;
        l++;
    }
    while(l > MAX_FILENAME_LENGTH){
        cout << "Filename is too long. Please enter a proper file name of less than or equal to " << MAX_FILENAME_LENGTH << " characters." << endl;
        while(c != '\n'){
            c = cin.get();
            filename[l] = c;
            l++;
        }
    }
    filename[l] = '\0';
    cout<<filename<<endl;
    //                                                                                   
    if(l <= MAX_FILENAME_LENGTH){
        return true;
    }
    else return false;
}

void filluniverse(Cell universe[ROWS][COLUMNS]){
    for(int i = 1; i <NO_OF_ROWS; i++){
        for(int y = 1; y<NO_OF_COLUMNS; y++){
            universe[i][y] = Live;
        }
    }
}

//                  
void copyUniverse (Cell universe[ROWS][COLUMNS], Cell universeCopy[ROWS][COLUMNS]){
    for(int a =0; a < ROWS; a++)
    {
        for(int b = 0; b < COLUMNS; b++)
        {
                universeCopy[a][b] = universe[a][b];
        }
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    char filename [MAX_FILENAME_LENGTH];
    bool fname = enter_filename(filename);
    cout << fname << endl;
    cout << "Filename in ruf: " << filename << endl;
    if(fname){
        inputfile.open("pulsar.txt");
    }
    //               
    assert(inputfile.is_open());
    //                                                                          
    filluniverse(universe);
    while(inputfile){
        for(int i = 1; i<NO_OF_ROWS; i++){
            for(int y = 1; y<NO_OF_COLUMNS; y++){
                if(inputfile.get() == DEAD){
                    universe[i][y] = Dead;
                } else universe[i][y] = Live;
            }
        }
    }
    return true;

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(universe); //                              
    for(int i = 0; i<NO_OF_ROWS; i++){
        for(int y = 0; i<NO_OF_COLUMNS; i++){
            if(universe[i][y] == 0){
                cout << DEAD << "\t";
            } else if(universe[i][y] == 1){
                cout << LIVE << "\t";
            }
        }
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(now && next);
    copyUniverse(now, next);

    for(int a = 1; a < NO_OF_ROWS; a++)
    {
        for(int b = 1; b < NO_OF_COLUMNS; b++)
        {
            int alive = 0;
            for(int c = -1; c < 2; c++)
            {
                for(int d = -1; d < 2; d++)
                {
                    if(!(c == 0 && d == 0))
                    {
                        if(next[a+c][b+d])
				{
					++alive;
				}
                    }
                }
            }
            if(alive < 2)
            {
                now[a][b] = Dead;
            }
            else if(alive == 3)
            {
                now[a][b] = Live;
            }
            else if(alive > 3)
            {
                now[a][b] = Dead;
            }
        }
    }
}

int main ()
{
    ifstream infile;
    Cell universe [ROWS][COLUMNS];
    Cell next_universe [ROWS][COLUMNS];
    //                                     
    filluniverse(universe);
    while(true){
        show_universe(universe);
        next_generation(universe, next_universe);
        usleep(200000);
        system("clear");
    }

}

