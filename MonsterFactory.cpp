#include "MonsterFactory.hpp"

#include <fstream>
#include <iostream>

using namespace std;
  
void MonsterFactory::readInMonsterDescriptionsFile(string filePath) {
  
  ifstream f(filePath);
  string temp = getNextLine(f);
  while(temp.size() > 0) {
    cout << temp;
    temp = getNextLine(f);
  }
}

string MonsterFactory::getNextLine(istream& in) {
  return getString(in, '\n');
}

string MonsterFactory::getNextWord(istream& in) {
  return getString(in, ' ');
}

string MonsterFactory::getString(istream & in, char delim) {
  const int size  = 1024;
  char pBuffer[size];
  in.getline(pBuffer, size, delim);
  return string(pBuffer);
}