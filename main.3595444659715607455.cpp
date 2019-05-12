#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;
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
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //                
    assert(true);
    //                                                               
    //              
    char c;
    cout << "Enter file name, that is no longer than 80 symbols"<<endl;
    for (int a=0 ; a<MAX_FILENAME_LENGTH-1; a++)
    {
          c = cin.get();
          cout<<filename[a];
          if (c == '\n')
          {
            filename[a]= '\0';
            return true;
          }
           else
          {
            filename[a]= c;
          }

    }
    if (filename[MAX_FILENAME_LENGTH]<=MAX_FILENAME_LENGTH)
        return true;
    else
        cout<<"Your filename is too long";
        return false;
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //                
    assert(inputfile.is_open());
    //                                                                                 

int a,b;
char g;
inputfile >> g;
while(inputfile)
{
for (a=1; a<=NO_OF_ROWS;a++)
{

    for(b=1; b<=NO_OF_COLUMNS; b++)
    {
      if (g== '*')
      {
        universe[a][b] =Live;
      }
      else
    {
        universe[a][b] = Dead;
    }
     inputfile>>g;
    }
    cout<<endl;
}
return true;
}

if (inputfile.is_open()){
    cout<<"File is open"<<endl;;
    return true;
}
else
{
    cout<<"File is not open"<<endl;;
    return false;
}

}

void show_universe ( Cell universe [ROWS][COLUMNS])
{
    //                
    assert(true);
    //                                                                           

int a,b;
char g;
for (a=1; a<ROWS;a++)
{

    for(b=1; b<COLUMNS; b++)
    {

      if (universe[a][b] == Live)
      {
        g='*';
      cout<<g;
    }
      else
      {
        g='.';
        cout<<g;
    }
    }
    cout<<endl;
}

}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //                                                
}

int main ()
{
   Cell ColumnsAndRows[ROWS][COLUMNS];
    ifstream inputfile;
    char nwefilename[MAX_FILENAME_LENGTH];
 enter_filename(nwefilename);
 //                            
 inputfile.open(nwefilename);
 read_universe_file(inputfile,ColumnsAndRows );
 show_universe(ColumnsAndRows);

}

