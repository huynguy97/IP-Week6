//                         
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
bool enter_filename (char filename [MAX_FILENAME_LENGTH]){
    //                                                
    assert(true);
    //                
    /*                                                                             
    */

    string input;
    cout << "Please enter the name of the file (including .txt\\n)\n";
    getline(cin,input);

    if(input.length() <= MAX_FILENAME_LENGTH)
    {
        for(int i = 0; i < MAX_FILENAME_LENGTH; i++)
        {
            filename[i] = input[i];
            if(input[i] == '\n')
            {
                filename[i] = '\0';
                break; //                                                                        
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS]){
    //               
    assert(inputfile.is_open());
    //                
    //                                                                                     

    //                  
    for (int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            universe[y][x] = Dead;
        }
    }

    char c;
    int x = 0;
    int y = 0;
    while (inputfile)
    {
        inputfile.get(c);
        if(c == DEAD)
        {
            universe[y+1][x+1] = Dead;
        }
        else if(c == LIVE)
        {
            universe[y+1][x+1] = Live;
        }
        x++;
        if(c == '\n')
        {
            x = 0;
            y++;
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS]){
    //              
    assert(true);
    //               
    //                                                               

    for (int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            if(universe[y][x] == Dead)
            {
                cout << DEAD;
            }
            else
            {
                cout << LIVE;
            }
        }
        cout << '\n';
    }
}

//                             
Cell cell_status (int y, int x, Cell universe[ROWS][COLUMNS]){
    //              
    assert(x != 0 && y != 0 && x != COLUMNS-1 && y != ROWS-1);
    //               
    //                                                        

    int pop = 0;

    if(universe[y-1][x-1] == Live)
        pop++;
    if(universe[y-1][x] == Live)
        pop++;
    if(universe[y-1][x+1] == Live)
        pop++;
    if(universe[y][x-1] == Live)
        pop++;
    if(universe[y][x+1] == Live)
        pop++;
    if(universe[y+1][x-1] == Live)
        pop++;
    if(universe[y+1][x] == Live)
        pop++;
    if(universe[y+1][x+1] == Live)
        pop++;

    if(universe[y][x] == Live)
    {
        if(pop == 2 || pop == 3)
        {
            return Live;
        }
    }
    else
    {
        if(pop == 3)
        {
            return Live;
        }
    }
    return Dead;
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS]){
    //                
    assert(true);
    //                
    //                                                                                                       

    for (int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            next[y][x] = Dead;
        }
    }

    for (int y = 0; y < NO_OF_ROWS; y++)
    {
        for(int x = 0; x < NO_OF_COLUMNS; x++)
        {
            next[y+1][x+1] = cell_status(y+1,x+1,now);
        }
    }

}

int main (){
    char filename [MAX_FILENAME_LENGTH];
    if(enter_filename(filename))
    {
        ifstream inputfile(filename);
        Cell Universe [ROWS][COLUMNS];
        if(inputfile.is_open())
        {
            read_universe_file(inputfile, Universe);
            show_universe(Universe);

            cout << endl;

            Cell New_Universe [ROWS][COLUMNS];

            next_generation(Universe,New_Universe);
            show_universe(New_Universe);

        }
        else
        {
            cout << "File not found \n";
        }
    }
    else
    {
        cout << "This filename was too long \n";
    }
}

