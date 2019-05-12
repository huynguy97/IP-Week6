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

char filename [MAX_FILENAME_LENGTH];
Cell universe [ROWS][COLUMNS];

//                                 
//                  
//
//                                                                                                                        
//
//                                                                                                             
//                                                                                                                                                           
//                                                                                                                                                   
//                                                                                                                                                    
//                                                                                                                                                                                          
//                 
//                                                                                                                                                                         
//                                                                                                                                                               
//                                                                                                                                                                                     
//       

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert (MAX_FILENAME_LENGTH > 0);

    //                 
    //                                                                                                                            
    cout << "Please enter a file name. You are allowed to use spaces, but you also have to include the file extension and you should stay under 79 characters.\n" << endl;
    //                                                                                                                
    char input_name;
    cin.get(input_name);
    cout << "you entered: ";

    for (int counter = 0; cin && counter < MAX_FILENAME_LENGTH; counter++)
    {
        cout << input_name;
        if (counter == 80)
        {
            cout << "ERROR: Too many characters entered!" << endl;
            return false;
        }
        if (input_name != '\n')
            filename [counter] = input_name;
        else
        {
            filename [counter] = '\0';
            return true;
        }
        cin.get(input_name);
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert (true);
    //                
    //                                                                                                                                                   

    inputfile.open (filename);
    if (!inputfile.is_open())
    {
        cout << "ERROR: Unable to open file." << endl;
        return false;
    }
    else
        cout << "File has been opened."<< endl;
    char c;
    int counter_row = 1;
    inputfile.get(c);

    for (int counter_column = 1; counter_column < NO_OF_COLUMNS; counter_column++)
    {

        cout << c << endl;
        switch (c)
        {
        case '.':
            universe [counter_row][counter_column] = Dead;
            cout << "found dot!" << endl;
            break;
        case '*':
            universe [counter_row][counter_column] = Live;
            cout << "found star!" << endl;
            break;
        case '\n':
            if (counter_row < NO_OF_ROWS)
            {
                counter_row++;
                counter_column = 1;
            }
        default:
            cout << "What is this?" << endl;

        }
        inputfile.get(c);           //                                                                                                                                                         
    }
    counter_row = 0;

    for (int counter_column = 0; counter_column == 0 || counter_column == COLUMNS -1 || counter_row == 0 || counter_row == ROWS -1; counter_column++)
    {
        if (counter_column < COLUMNS)
            universe [counter_row][counter_column] = static_cast<Cell>(0);
        else
        {
            if (counter_row < ROWS)
            {
                counter_row++;
                counter_column = 0;
            }
        }
    }
    cout << "Done reading." << endl;
    inputfile.clear ();
    inputfile.close ();
    if (filename)
    {
        cout << "File closed successfully." << endl;
        return true;
    }
    cout << "ERROR: Unable to close file." << endl;
    return false;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                 
    //                                                              
    int counter_row = 0;
    for (int counter_column = 0; counter_column < COLUMNS && counter_row < ROWS; counter_column++)
    {
        if (universe[counter_row][counter_column] == Dead)
            cout << DEAD << ' ';
        if (universe[counter_row][counter_column] == Live)
            cout << LIVE << ' ';
        if (counter_column == COLUMNS -1 && counter_row < ROWS)
        {
            cout << endl;
            counter_column = 0;
            counter_row++;

        }
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
    enter_filename(filename);
    ifstream inputfile (filename);
    read_universe_file(inputfile, universe);
    show_universe(universe);

}

