/*                                                                    
                                                                      
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

enum Cell {Dead=0, Live};                        //                                                                           

const char DEAD             = '.';               //                                                          
const char LIVE             = '*';               //                                                          
const int NO_OF_ROWS        = 40;                //                                                                      
const int NO_OF_COLUMNS     = 60;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2; //                                                                               

const int MAX_FILENAME_LENGTH = 80;              //                                                                                   

//                                
bool enter_filename(char filename[MAX_FILENAME_LENGTH])
{
//               
    assert(filename);
/*                
                                                                            
                              
 */

    cout << "What is your filename called?" << endl;
    cin.getline(filename, (MAX_FILENAME_LENGTH + 1));

    if (strlen(filename) >= MAX_FILENAME_LENGTH){
        cout << "Filename too long" << endl << "Program aborted" << endl;
        return false;
    } else {
        return true;
    }
}

//                           
bool read_universe_file(ifstream& inputfile, Cell universe[ROWS][COLUMNS])
{
//               
    assert(inputfile);
/*                
                                                                            
                     
 */

    char c;

    if (!inputfile.is_open()) {
        return false;
    }

    while (!inputfile.eof()) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                inputfile.get(c);

                if (c == '.') {
                    universe[i][j] = Dead;
                } else if (c == '*') {
                    universe[i][j] = Live;
                } else if (c == '\n') {
                    break;
                }
            }
        }
    }

    return true;
}

void show_universe(Cell universe [ROWS][COLUMNS])
{
//               
    assert(universe);
/*                
                                         
 */
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (universe[i][j] == Dead)
                cout << ".";
            else
                cout << "*";
        }
        cout << '\n';
    }
    cout << '\n';
}

//                             
void next_generation(Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
//               
    assert(now);
    assert(next);
/*                
                                                                    
                        
 */

    for (int i = 1; i < ROWS - 1; i++) {
        for (int j = 1; j < COLUMNS - 1; j++) {
            int Livecounter = 0;

            if (now[i-1][j-1] == Live)
                Livecounter++;
            if (now[i-1][j] == Live)
                Livecounter++;
            if (now[i-1][j+1] == Live)
                Livecounter++;
            if (now[i][j-1] == Live)
                Livecounter++;
            if (now[i][j+1] == Live)
                Livecounter++;
            if (now[i+1][j-1] == Live)
                Livecounter++;
            if (now[i+1][j] == Live)
                Livecounter++;
            if (now[i+1][j+1] == Live)
                Livecounter++;

            if (now[i][j] == Live && Livecounter < 2)
                next[i][j]= Dead;
            if (now[i][j] == Live && (Livecounter == 2 || Livecounter == 3))
                next[i][j]= Live;
            if (now[i][j] == Live && Livecounter > 3)
                next[i][j]= Dead;
            if (now[i][j] == Dead && Livecounter == 3)
                next[i][j]= Live;
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            now[i][j] = next[i][j];
        }
    }
}

void clear_universe(Cell universe[ROWS][COLUMNS], Cell nextuniverse[ROWS][COLUMNS])
{
//               
    assert(universe);
    assert(nextuniverse);
/*                
                                              
 */
 
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            universe[i][j] = Dead;
            nextuniverse[i][j] = Dead;
        }
    }
}

int main()
{
    ifstream inputfile;
    ofstream outputfile;
    char filename[MAX_FILENAME_LENGTH] = "";
    Cell universe[ROWS][COLUMNS];
    Cell nextuniverse[ROWS][COLUMNS];

    clear_universe(universe, nextuniverse);
    enter_filename(filename);
    inputfile.open(filename);

    if (inputfile.good()) {
        read_universe_file(inputfile, universe);
    } else {
        cout << "File does not exist" << '\n';
        return -1;
    }

    //                                                      
    //                                                                                     

    show_universe(universe);
    next_generation(universe, nextuniverse);
    show_universe(universe);
    //                                         
    //                         
    //                                         
    //                         
    //                                         
    //                         

    return 0;
}

