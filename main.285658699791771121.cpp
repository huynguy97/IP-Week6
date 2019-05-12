#include <iostream>
#include <fstream>
#include <cassert>
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
//                                                                                          

//                                

bool enter_filename(char filename[MAX_FILENAME_LENGTH],int& a)
{
    //               
    assert(true);
    //               
    //                                                                                                               
    a = 0;
    cout << "Please enter filename" << "\n";
    cin.get(filename,MAX_FILENAME_LENGTH);
    while (filename[a] != '\0'){
       a++;}
    if (a>MAX_FILENAME_LENGTH){
        cout<<"The filename is too long";
        return false;}
    else return true;
}

//                           
bool read_universe_file (ifstream& infile, char filename[MAX_FILENAME_LENGTH], Cell universe[ROWS][COLUMNS])
{
    //               
    assert(infile.is_open());
    //               
    //                                                                      
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            universe[i][j]=Dead;
        }
    }
    for(int k=0;k<=NO_OF_ROWS;k++){
        for(int l=0;l<=NO_OF_COLUMNS;l++){
            char u=DEAD;
            infile.get(u);
            if(u==LIVE){
                universe[1+k][1+l]=Live;}
            else if(u==DEAD)
                universe[1+k][1+l]=Dead;
        }
    }
    return true;
}

void show_universe (Cell universe[ROWS][COLUMNS])
{
    //               
    assert(true);
    //               
    //                                                      
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            if(universe[i][j]==Live){
                cout<<LIVE;}
            else if(universe[i][j]==Dead){
                cout<<DEAD;}
        }
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
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            next[i][j]=Dead;
        }
    }
    int no_of_live_cells_around;
    for(int k=1;k<=NO_OF_ROWS;k++){
        for(int l=1;l<=NO_OF_COLUMNS;l++){
            no_of_live_cells_around = now[k-1][1-l]+now[k-1][l]+now[k-1][1+l]+now[k][l-1]+now[k][l+1]+now[k+1][l-1]+now[k+1][l]+now[k+1][l+1];
            if(now[k][l]==Dead){
                if(no_of_live_cells_around==3){
                    next[k][l]==Live;}
                else{
                    next[k][l]==Dead;}
            }
            else if(now[k][l]==Live){
                switch(no_of_live_cells_around){
                    case 2:
                        next[k][l]=Live; break;
                    case 3:
                        next[k][l]=Live; break;
                    default:
                        next[k][l]=Dead; break;}
            }
        }
    }
}

int main ()
{
    char filename[MAX_FILENAME_LENGTH]= {0};
    int a=0;
    Cell universe[ROWS][COLUMNS];
    Cell now[ROWS][COLUMNS];
    Cell next[ROWS][COLUMNS];
    ifstream infile;
    if(enter_filename(filename,a)){
      infile.open(filename);
            if(read_universe_file(infile,filename,universe)){
                show_universe(universe);
                next_generation(universe,next);
                cout<<endl<<"The result is:"<<endl;
                show_universe(next);}
            }
return 0;
}

