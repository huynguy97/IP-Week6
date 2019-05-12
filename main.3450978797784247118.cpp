#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                
    assert(true);
    //                                                                         
    //                                                                                 
    cout<<"Please enter the universe config filename: ";
    int i=0;
    char c=' ';
    cin.get(c);
    bool illegal_char=false;
    illegal_char=illegal_char||c=='"';
    illegal_char=illegal_char||c=='\'';
    if(illegal_char){
        i--;
    }else{
        filename[i]=c;
    }
    while(cin&&c!='\n'){
        i+=1;
        if(i>=MAX_FILENAME_LENGTH){
            //                                                                        
            return false;
        }
        cin.get(c);
        //                                                 
        illegal_char=false;
        illegal_char=illegal_char||c=='"';
        illegal_char=illegal_char||c=='\'';
        if(illegal_char){
            i--;
        }else{
            filename[i]=c;
        }
    }
    filename[i]='\0';
    return (bool)cin;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());
    //                                                                                 
    //                                                         

    char c=' ';
    //                            
    for(int x=0;x<COLUMNS;x++){universe[0][x]=Dead;}
    for(int y=1;y<ROWS-1;y++){
        //                                        
        universe[y][0]=Dead;
        for(int x=1;x<COLUMNS-1;x++){
            c=' ';
            inputfile.get(c);
            if(c==LIVE){universe[y][x]=Live;
            }else if(c==DEAD){universe[y][x]=Dead;}
            //                                        
            else{return false;}
        }
        //                                                                
        inputfile.get(c);
        if(c!='\n'){
            return false;
        }

        //                                       
        universe[y][COLUMNS-1]=Dead;
    }
    //                           
    for(int x=0;x<COLUMNS;x++){universe[ROWS-1][x]=Dead;}
    return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                                                    
    for(int y=0;y<ROWS;y++){
        for(int x=0;x<COLUMNS;x++){
            cout<<(universe[y][x]==Live?LIVE:DEAD);
            //                     
        }
        cout<<endl;
    }
}

//                                               
Cell advance_step(Cell orig [ROWS][COLUMNS], int x, int y){
    //               
    assert(0<x&&x<COLUMNS-1);
    assert(0<y&&y<ROWS-1);
    //                                                                 
    //                                        
    int nearby_lives=0;
    nearby_lives+=(orig[y-1][x-1]==Live);
    nearby_lives+=(orig[y-1][x]==Live);
    nearby_lives+=(orig[y-1][x+1]==Live);
    nearby_lives+=(orig[y][x-1]==Live);
    nearby_lives+=(orig[y][x+1]==Live);
    nearby_lives+=(orig[y+1][x-1]==Live);
    nearby_lives+=(orig[y+1][x]==Live);
    nearby_lives+=(orig[y+1][x+1]==Live);
    //                                                         
    if(orig[y][x]==Live){
        if(nearby_lives<2||nearby_lives>3){
            return Dead;
        }else{
            return Live;
        }
    }else{
        if(nearby_lives==3){
            return Live;
        }else{
            return Dead;
        }
    }
}

void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true);
    //                                                                        
    for(int x=0;x<COLUMNS;x++){next[0][x]=Dead;}
    for(int y=1;y<ROWS-1;y++){
        //                                        
        next[y][0]=Dead;
        for(int x=1;x<COLUMNS-1;x++){
            next[y][x]=advance_step(now,x,y);
        }
        //                                       
        next[y][COLUMNS-1]=Dead;
    }
    //                           
    for(int x=0;x<COLUMNS;x++){next[ROWS-1][x]=Dead;}
}

int main ()
{
    char fname[MAX_FILENAME_LENGTH];
    if(!enter_filename(fname)){
        cout<<"Filename to long/Problem with the console! Exiting now...";
        return 1;
    }
    ifstream infile(fname);
    cout<<"Opening file "<<fname<<".\n";
    Cell universe[ROWS][COLUMNS];
    if(read_universe_file(infile,universe)){
        Cell next_universe[ROWS][COLUMNS];
        next_generation(universe,next_universe);
        show_universe(next_universe);
        return 0;
    }else{
        cout<<"Invalid universe config file! Exiting now...";
        return 1;
    }
}

