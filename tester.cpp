#include <list>
#include <iostream>
#include <string>
#include <sstream> // used to parse a string
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>

using namespace std;


int main()
{

  // variables
  string temp_open;
  string temp_close;

  // define 4 empty arrays to store values
  list<float> open;
  list<float> close;

  string file = "amd.csv";

  int i = 0;

  ifstream myFile;
  myFile.open(file);
  if(myFile.is_open()) // while the file is open
  {
    while(!myFile.eof())
    {
      getline(myFile, temp_open, ',');
      cout << temp_open << " | ";
      //float temp = strtof((temp_open).c_str(), 0); // string to float with help from https://www.cplusplus.com/forum/beginner/148948/
      double temp = atof(temp_open.c_str());
      cout << temp << endl;
      //cout << temp << endl;
      open.push_back(temp);


      getline(myFile,temp_close, '\n');
      //float temp2 = strtof((temp_close).c_str(),0);
      close.push_back(temp);
    }
  }


  auto reader = open.begin();
  //float add1 = *reader;
  cout << *reader << endl;
  reader++;
  cout << *reader << endl;
  reader++;
  cout << *reader << endl;
  reader++;
  cout << *reader << endl;
  reader++;
  cout << *reader << endl;
  reader++;
  //float add2 = *reader;
  //cout << (add1+add2);


  /*
  for (auto i = open_fixed.begin(); i != open_fixed.end(); ++i)
  {
    std::cout << *i << ' ';
  }
  */


}







/*
  ifstream myFile;
  myFile.open("amd.csv");
  while(myFile.good())
  {
    string line;
    getline(myFile, line, ',');// read the text until we get to the comma, then stop, and store into line.
    cout << line << endl;
  }
  */
