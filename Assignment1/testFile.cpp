#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
  ifstream f;
  f.open("test1.txt");

  if (!f.is_open())
    return 1;

  string line;
  int i, length;
  char charsFinal[9];

  while (!f.eof()) {
    getline(f, line);
    char charsTemp[line.size() + 1];
    cout << line << endl;
    strncpy(charsTemp, line.c_str(), sizeof(charsTemp));
    //length = sizeof(charsTemp) / sizeof(*charsTemp);
    cout << length << endl;
    for (int k = 0; k < 18; ++k)
    {
      cout << "put in final array: "<< charsTemp[k] << endl;
      charsFinal[k] = charsTemp[k++];
      cout << k << endl;

      //cout << "k = " << charsFinal[k] << endl;
      if (k == 18)
      {
          cout << "breaking" << endl;
      }
    }
    break;
  }


}
