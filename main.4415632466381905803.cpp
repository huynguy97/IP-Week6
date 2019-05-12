#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

//                                               

//                                                                             
//                                                                                                                   
//                                                               
//                                                                                                               
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

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH]){

    string input;
    assert(MAX_FILENAME_LENGTH >= input.length());
    //                                                
    //                                                                

    char c;
    int i = 0;
    bool a = true;
    while(a){

        cin.get(c);
        if(i>MAX_FILENAME_LENGTH){
            return false;
        }
        filename[i++] = c;
        if (c =='\n'){
            a = false;
        }
    }
    filename[i-1] = '\0';
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    assert(inputfile.is_open());
    //                                                
    //                                                                  
    cout << "\n";
    char c;
    for (int i = 1; i < ROWS-1; i++) {
        for (int j = 1; j < COLUMNS-1; j++) {
            inputfile >> c;
            if (c == '*') {
                universe[i][j] = Live;
            }
            if (c == '.') {
                universe[i][j] = Dead;
            }
        }
    }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{   assert(universe[ROWS][COLUMNS]);
    //                                                
    //                                 
    for (int i = 1; i < ROWS-1; ++i) {
        for (int j = 1; j < COLUMNS-1; ++j) {

            if(universe[i][j] == Dead) {
                cout << DEAD;
            }
            if(universe[i][j] == Live) {
                cout << LIVE;
            }
        }
        cout << "\n";
    }

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS]) {
    assert(now[ROWS][COLUMNS]);
    //                                                
    //                                                                                                    
    for (int i = 1; i < ROWS - 1; ++i) {
        for (int j = 1; j < COLUMNS - 1; ++j) {
            next[i][j] = Dead;
        }
    }

    for (int k = 1; k < ROWS - 1; k++) {
        for (int i = 1; i < COLUMNS - 1; i++) {
            int xalive = 0;

            for (int j = k - 1; j < k + 2; j++) {
                for (int l = i - 1; l < i + 2; l++) {

                    if (now[j][l] == Live) {
                        xalive++;
                    }
                }
            }
            if(now[k][i] == Live){
                xalive--;
            }

            //      
            if ((xalive < 2) && now[k][i] == Live) {
                next[k][i] = Dead;
            }

            //      
            if ((xalive == 2 || xalive == 3) && (now[k][i] == Live)) {
                next[k][i] = Live;
            }

            //      
            if ((xalive > 3) && now[k][i] == Live) {
                next[k][i] = Dead;
            }

            //      
            if (xalive == 3 && now[k][i] == Dead) {
                next[k][i] = Live;
            }

        }
    }
    for (int m = 1; m < ROWS - 1; ++m) {
        for (int j = 1; j < COLUMNS - 1; ++j) {
            now[m][j] = next[m][j];
        }
    }

cout<<"\n\n\n";
show_universe(now);

}

int main ()
{
    ifstream file;
    Cell currentgen[ROWS][COLUMNS];
    Cell nextgen[ROWS][COLUMNS];
    char array[MAX_FILENAME_LENGTH];
    int gens = 1;
    cout << "Enter file name\n";
    if(enter_filename(array)){
        cout << array;
        file.open(array);

        cout << "\nhow many generations?\n";
        cin >> gens;
        read_universe_file(file,currentgen);
        show_universe(currentgen);
        for (int i = 1; i < gens; ++i) {
            next_generation(currentgen,nextgen);
        }
    }
}

