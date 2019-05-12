#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;
//                            

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 30;              //                                                                                   
char naam[MAX_FILENAME_LENGTH];
//                                
//                                                         
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    assert(true);
    //                
    //                                                                                                                 
    int lengtecheck = 0;
    cout << "Please enter the name of the file you want to use (including .txt). The maximum length of the file name is : " << MAX_FILENAME_LENGTH - 1<< endl;
    cin.getline(filename, MAX_FILENAME_LENGTH); //                                             
    if (filename[MAX_FILENAME_LENGTH - 2] == '\0')
    {
        return true;
    }
    return false;
}

//                           
//                                                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                                                
    //                                                                                                                            
    assert(ROWS > 0 && COLUMNS > 0);
    //               
    //                                                                                                                            
    inputfile.open(naam);
    char DATA;
    while (inputfile.is_open())
    {
        for(int r = 0; r < NO_OF_ROWS; r++)
        {
            for(int k = 0; k < NO_OF_COLUMNS; k++)
            {
                inputfile >> DATA;
                if (DATA == DEAD)
                {
                    universe[r+1][k+1] = Dead;
                }
                else if (DATA == LIVE)
                {
                    universe[r+1][k+1] = Live;
                }

            }
        }
        inputfile.close();
    }
    if(!inputfile.is_open())
    {
        return true;
    }
    return false;

}
//                                                     
void show_universe (Cell universe [ROWS][COLUMNS])
{
    assert(ROWS > NO_OF_ROWS && COLUMNS > NO_OF_COLUMNS);
    //                                                               
    //                
    //                                                                                                     
    for(int r = 0; r < ROWS ; r++)
    {
        universe[r][COLUMNS-1] = Dead;
        universe[r][0] = Dead;
    }
    for(int k = 0; k < COLUMNS; k++)
    {
        universe[0][k] = Dead;
        universe[ROWS - 1][k] = Dead;
    }
    for(int r = 0; r < ROWS; r++)
    {

        for(int k = 0; k < COLUMNS; k++)
        {
            if(universe[r][k] == Dead)
            {
                cout << ".";
            }
            else if (universe[r][k] == Live)
            {
                cout << "*";
            }
        }
        cout << endl;
    }
}
//                                               
//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    assert(ROWS > NO_OF_ROWS && COLUMNS > NO_OF_COLUMNS);
    //                                                               
    //               
    //                                                                        
    cout << "The next step : " << endl;
    int teller;
    for(int r = 1; r<= NO_OF_ROWS; r++)
    {
        for(int k = 1; k<=NO_OF_COLUMNS; k++)
        {
            teller = 0;
            for(int i = -1; i <=1 ; i++)
            {
                //                                           
                for(int j = -1; j <= 1; j++)
                {
                    if(now [r + i][k+j] == Live)
                    {
                        if (i != 0 || j!=0)
                        {
                            teller++;
                        }
                    }
                }
            }
            if(now[r][k] == Live)
            {
                if(teller < 2)
                {
                    next[r][k] = Dead;
                }
                if(teller == 2 || teller == 3 )
                {
                    next[r][k] = Live;
                }
                if(teller > 3)
                {
                    next[r][k] = Dead;
                }
            }
            else if(now[r][k] == Dead && teller == 3)
            {
                next[r][k] = Live;
            }
            else
            {
                next[r][k] = now[r][k];
            }
        }
    }
}

int main ()
{
    ifstream myfile;
    Cell universum [ROWS][COLUMNS];
    Cell universum1[ROWS][COLUMNS];
    if (!enter_filename(naam))
    {
        cout << "You entered a filename which is too long" << endl;
        return 0;
    }
    if(!read_universe_file(myfile, universum))
    {
        cout << "Something went wrong closing the file, please rerun the program" << endl;
        return 0;
    }
    read_universe_file(myfile, universum);
    cout << "The first configuration: " << endl;
    show_universe(universum);
    next_generation(universum,universum1);
    show_universe(universum1);
    return 0;
}

