#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                                                
    //              
    assert(MAX_FILENAME_LENGTH > 0);

    //                                                                                                                                 
    //                                                  

    cout << "Please enter file name and end with enter" << endl;

    char letter_of_file = '\0';
    int i = 0;
    cin.get(letter_of_file);
    while (i<MAX_FILENAME_LENGTH && letter_of_file !='\n')
    {
        filename[i] = letter_of_file;
        i++;
        cin.get(letter_of_file);
    }

    if (letter_of_file =='\n') //                                
    {
        filename[i]='\0';
        return true;
    } else //                                         
    {
        //                  
        cin.ignore(1000, '\n');
        return false;
    }
}

void fillEdge(Cell universe [ROWS][COLUMNS])
{
    //              
    assert(ROWS >= 3 && COLUMNS >= 3);
    //                                                               
    for (int i = 0; i < COLUMNS; i++){
        universe[0][i] = Dead;
        universe[ROWS-1][i] = Dead;
    }
    for (int i = 0; i < ROWS; i++){
        universe[i][0] = Dead;
        universe[i][COLUMNS-1] = Dead;
    }
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    //              
    assert(inputfile.is_open() && ROWS >= 3 && COLUMNS >= 3 && ROWS == (NO_OF_ROWS+2) && COLUMNS == (NO_OF_COLUMNS+2));
    //                                                                                     
    //                                                        

    int cRow = 1;
    int cCol = 1;

    char c;
    inputfile.get(c);
    while(inputfile && cRow < (1+NO_OF_ROWS)){
        if (cCol >= 1 + NO_OF_COLUMNS){ //                                                  
            if (c == '\n'){
                //                                                                                                     
                cCol = 1;
                cRow++;
                if (cRow >= 1 + NO_OF_ROWS){ //                                    
                    //                                                                                           
                    inputfile.get(c);
                    if (inputfile){
                        cout << "File was too long, extra char found at end: " << c << endl;
                        return false;
                    }
                }
            } else {
                //                                                                             
                cout << "File error: Row " << cRow << " is too long." << endl;
                return false;
            }
        } else { //                                        
            //                                                          
            if (c == DEAD){
                universe [cRow][cCol] = Dead;
            } else if (c == LIVE){
                universe [cRow][cCol] = Live;
            } else { //                               
                cout << "File error: Found unexpected character " << c << " at Row " << cRow << " and Column " << cCol << endl;
                return false;
            }
            cCol++; //           
        }

        //                                     
        inputfile.get(c); //      
    }

    fillEdge(universe);
    return true; //                     
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(ROWS >= 3 && COLUMNS >= 3);
    //                                                                     
    for (int r = 0; r < ROWS; r++){
        for (int c = 0; c < COLUMNS; c++){
            Cell currentCell = universe[r][c];
            if (currentCell == Live){
                cout << "* ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int nLiveNeighbours(int row, int col, Cell universe [ROWS][COLUMNS]){
    //                                                
    assert(ROWS >= 3 && COLUMNS >= 3 && ROWS == (NO_OF_ROWS+2) && COLUMNS == (NO_OF_COLUMNS+2) && row > 0 && row <= NO_OF_ROWS && col > 0 && col <= NO_OF_COLUMNS);
    //                                                                              
    //                                                                      
    int result = static_cast<int>(universe[row-1][col-1]) + static_cast<int>(universe[row-1][col]) + static_cast<int>(universe[row-1][col+1]) + static_cast<int>(universe[row][col-1]);
    result += static_cast<int>(universe[row][col+1]) + static_cast<int>(universe[row+1][col-1]) + static_cast<int>(universe[row+1][col]) + static_cast<int>(universe[row+1][col+1]);
    return result;
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
    assert(ROWS >= 3 && COLUMNS >= 3 && ROWS == (NO_OF_ROWS+2) && COLUMNS == (NO_OF_COLUMNS+2));
    //                                                   
    for (int r = 1; r <= NO_OF_ROWS; r++){
        for (int c = 1; c < NO_OF_COLUMNS; c++){
            int nb = nLiveNeighbours(r,c,now);
            if (now[r][c] == Live){
                if (nb == 2 || nb == 3){
                    next[r][c] = Live;
                } else {
                    next[r][c] = Dead;
                }
            } else {
                if (nb == 3){
                    next[r][c] = Live;
                } else {
                    next[r][c] = Dead;
                }
            }
        }
    }
}

void empty_character_array (char cArray[], int arrayLength)
{
    //              
    assert (arrayLength > 0);
    //                                                                 
    for (int i= 0; i < arrayLength; i++)
    {
        cArray [i] = '\0';
    }
}

bool openFile(char fName [], ifstream& file)
{
    //              
    assert(true);
    //                                                                                                               
    file.open(fName);
    if (file){ //                   
        return true;
    } else {
        return false;
    }
}
int main ()
{
    ifstream file;
    char Fname[MAX_FILENAME_LENGTH];
    empty_character_array (Fname, MAX_FILENAME_LENGTH);

    bool correctFName = enter_filename(Fname);
    while (!correctFName){
        cout << "\nFile Name is too long" << endl;
        cout << "Please enter a filename of max. " << MAX_FILENAME_LENGTH << " characters." << endl;
        correctFName = enter_filename(Fname);
    }

    if (openFile(Fname, file)){
        cout << "File opened successfully." << endl;
    } else {
        cout << "File could not open successfully, please check the filename." << endl;
        return 1; //     
    }

    Cell Universe [ROWS][COLUMNS];
    if (read_universe_file(file,Universe)){
        cout << "File was correctly formatted." << endl;
    } else {
        cout << "Program terminated because of file format error." << endl;
        return 1; //     
    }
    cout << "====================================" << endl << "Universe starting configuration: " << endl << "====================================" << endl;
    show_universe(Universe);

    Cell nextUniverse [ROWS][COLUMNS];
    next_generation(Universe, nextUniverse);
    cout << "====================================" << endl << "Universe after 1 generation: " << endl << "====================================" << endl;
    show_universe(nextUniverse);

    return 0;
}

