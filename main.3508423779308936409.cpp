#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>

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

void clrscr()
{
    //                
    //                
    system("@cls||clear");
}

void translater(Cell universe[ROWS][COLUMNS],char field1[][62],int a)
{
    //               
    assert(a==0 || a==1);
    //                
    //                                                                                               
    int i,j;
    for (i=0;i<ROWS;i++)
    {
        for (j=0;j<COLUMNS;j++)
        {
            if (a==0)
            {
                if (field1[i][j]=='.')
                {
                    universe[i][j]=Dead;
                }
                else if (field1[i][j]=='*')
                {
                    universe[i][j]=Live;
                }
            }
            if (a==1)
            {
                if (universe[i][j]==Dead)
                    field1[i][j]='.';
                else if (universe[i][j]==Live)
                {
                    field1[i][j]='*';
                }
            }
        }
    }
}

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //               
    assert(true);
    //                
    //                                                                                                                                  
    int a;
    cout << "Please enter a filename with at most " << MAX_FILENAME_LENGTH-1 << " characters:" << endl;
    cin.getline(filename,MAX_FILENAME_LENGTH);
    a=strlen(filename);
    a++;
    if (a>=MAX_FILENAME_LENGTH)
    {
        return false;
    }
    return true;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());
    //                
    //                                                                 
    int i,j;
    char c;
    char  field1 [ROWS][COLUMNS];
    //                                              
    for (i=0; i<ROWS; i++)
	{
		for (int j=0; j<COLUMNS; j++)
		{
            universe[i][j]=Dead;
            field1[i][j]='.';
		}
	}
    //                                                   
    for (i=1; i<(NO_OF_ROWS+1); i++)
	{
		for (int j=1; j<(NO_OF_COLUMNS+1); j++)
		{
            inputfile >>field1[i][j];
		}
	}
	translater(universe,field1,0);
}

int count_living_cells(int i, int j, Cell universe[ROWS][COLUMNS])
{
    //               
    assert(i>0 && j>0);
    //                
    //                                                                                                                                                                    
    int counter=0, a,b;
    for (a=-1; a<=1; a++)
    {
        for (b=-1; b<=1; b++)
        {
            if (universe[i+a][j+b]==Live)
            {
                counter ++;
            }
        }
    }
    return counter;
}

void copying_universe(Cell universe1[ROWS][COLUMNS],Cell universe2[ROWS][COLUMNS])
{
    //               
        assert(true);
    //                
    //                                                
    int i,j;
    for (i=0; i<ROWS; i++)
    {
        for (j=0; j<COLUMNS; j++)
        {
            universe1[i][j]=universe2[i][j];
        }
    }
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                
    //                                                      
    char field1[ROWS][COLUMNS];
    int i,j;
    //                           
    translater(universe,field1,1);
    for (i=0; i<ROWS;i++)
    {
        for (j=0; j<COLUMNS; j++)
        {
            printf("%c ", field1[i][j]);
            if(j==61)
            {
                printf("\n");
            }
        }
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                
    //                                                                                                               
    int i,j,living_cells;
    for (i=1; i<=NO_OF_ROWS; i++)
    {
        for (j=1; j<=NO_OF_COLUMNS; j++)
        {
            living_cells=count_living_cells(i,j,now);
            if (now[i][j]==Dead && living_cells==3 )
            {
                next[i][j]=Live;
            }
            else if (now[i][j]==Live)
            {
                living_cells--;
                if (living_cells<2 ||living_cells>3)
                {
                    next[i][j]=Dead;
                }
            }
        }
    }
}

int main ()
{
    char filename [MAX_FILENAME_LENGTH];
    char c;
    int i,j,living_cells;
    Cell universe1 [ROWS][COLUMNS];
    Cell universe2 [ROWS][COLUMNS];
    ifstream inputfile;
    if (enter_filename(filename))
    {
        inputfile.open(filename);
    }
    else
    {
        cout << "Your filename was not correct!" << endl;
        return 0;
    }
    read_universe_file(inputfile,universe1);
    show_universe(universe1);
    copying_universe(universe2,universe1);
	char answer='y';
	while (answer=='y' || answer=='Y')
    {
        cout << "Do you want to see the next generation?(y/n)" << endl;
        cin >> answer;
        clrscr();
	    //                                         
	    next_generation(universe1,universe2);
        show_universe(universe2);
        copying_universe(universe1,universe2);
    }
    inputfile.close();
}

