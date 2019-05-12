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
//                                                                             
//                                                                             
//                                                                             
//                                                                             

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //              
    assert(true);
    //                                                                    

    //               
    char c;

    cout << "please enter the file name of the .txt file" << endl;
    for (int i = 0; i < MAX_FILENAME_LENGTH; i++)
    {
        cin.get(c);
        filename[i]=c;
        if (filename[i] == 10)
        {
            filename[i] = '\0';
            return true;
            //                                                                                                                                 
        }
    }
    return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //             
    assert(inputfile.is_open());
    //                                                                

    //               
    char character;

    for(int i=1; i<ROWS; i++)
    {
        for(int j=1; j<COLUMNS; j++)
        {

            inputfile.get(character);
            if (character=='*')
            {
                universe[i][j]=Live;
            }
            else if(character=='.')
            {
                universe[i][j]=Dead;
            }
        }
    }

}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //             
    assert(true);
    //                                                                                                                             

    //               

    for(int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLUMNS; j++)
        {
            if(i==0 || i==ROWS-1)
            {
                while (j < COLUMNS)
                {
                    universe[i][j] = Dead;
                    j++;
                }
            }
            if (j==0 || j==COLUMNS-1)
            {
                universe[i][j]=Dead;
            }
        }
    }

    for(int i=0; i<ROWS; i++)
    {

        for(int j=0; j<COLUMNS; j++)
        {

            if (universe[i][j]==0)
            {
                cout<<".";
            }
            else
            {
                cout<<"*";
            }
        }
        cout<<".";
        cout<<endl;
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //              
    assert(true);
    //                                                                                                                          

    //               
    for(int i=1; i<ROWS-1; i++)
    {
        for(int j=1; j<COLUMNS-1; j++)
        {
            int no_of_live_nabours=0;

                for(int k=-1; k<=1; k=k+2)
                {
                    if(now[i+k][j+k]==Live)
                    {
                        no_of_live_nabours++;
                    }
                }
                for(int k=-1; k<=1;k=k+2)
                {
                    if(now[i+k][j]==Live)
                    {
                        no_of_live_nabours++;
                    }
                }
                for(int k=-1; k<=1; k=k+2)
                {
                    if(now[i][j+k]==Live)
                    {
                        no_of_live_nabours++;
                    }
                }
                for(int k=-1; k<=1; k=k+2)
                {
                    if(now[i+k][j-k]==Live)
                    {
                        no_of_live_nabours++;
                    }
                }

            if (now [i][j]==Live)
            {
                if(no_of_live_nabours<2)
                {
                    next[i][j]=Dead;
                }
                else if(no_of_live_nabours==2||no_of_live_nabours==3)
                {
                    next[i][j]=Live;
                }
                else if(no_of_live_nabours>3)
                {
                    next[i][j]=Dead;
                }
            }
            else
            {
                if (no_of_live_nabours==3)
                {
                    next[i][j]=Live;
                }
                else
                {
                    next[i][j]=Dead;
                }
            }
        }
    }
}

int main ()
{
    char names [MAX_FILENAME_LENGTH];
    Cell universe [ROWS][COLUMNS];
    Cell next [ROWS][COLUMNS];

    if(enter_filename(names))
    {
        ifstream input_file;
        input_file.open(names);
        read_universe_file(input_file, universe);
        show_universe(universe);
        cout<<endl;
        cout<< "The next generation is:"<<endl;
        next_generation(universe, next);
        show_universe(next);
    }
    else
    {
        cout<<"the file couldn't be read"<<endl;
    }
}

