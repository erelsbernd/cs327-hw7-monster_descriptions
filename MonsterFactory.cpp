#include "MonsterFactory.hpp"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>



#define SAVE_DIR                ".rlg327"
#define MONSTER_DESC_SAVE_FILE  "monster_desc.txt"
#define MONSTER_DESC_SEMANTIC   "RLG327"
#define MONSTER_DESC_VERSION    1

using namespace std;

void try_f_read(char* file) {
  char semantic[6];
  FILE *f;
  char *home=NULL, *filename=NULL;
  size_t len;
  struct stat buf;
  
  if (!file) {
    if (!(home = getenv("HOME"))) {
      fprintf(stderr, "\"HOME\" is undefined.  Using working directory.\n");
      home = (char*)calloc(2, sizeof(char));
      home[0] = '.';
      home[1] = '\0';
    }
    
    len = (strlen(home) + strlen(SAVE_DIR) + strlen(MONSTER_DESC_SAVE_FILE) +
           1 /* The NULL terminator */                                 +
           2 /* The slashes */);
    
    filename = (char*) malloc(len * sizeof (*filename));
    sprintf(filename, "%s/%s/%s", home, SAVE_DIR, MONSTER_DESC_SAVE_FILE);
    
    if (!(f = fopen(filename, "r"))) {
      perror(filename);
      free(filename);
      exit(-1);
    }
    
    if (stat(filename, &buf)) {
      perror(filename);
      exit(-1);
    }
    
    free(filename);
  } else {
    if (!(f = fopen(file, "r"))) {
      perror(file);
      exit(-1);
    }
    if (stat(file, &buf)) {
      perror(file);
      exit(-1);
    }
    
  }
  
  fread(semantic, sizeof(semantic), 1, f);
  if (strncmp(semantic, MONSTER_DESC_SEMANTIC, 6)) {
    fprintf(stderr, "Not an RLG327 save file.\n");
    exit(-1);
  }
}
  
int MonsterFactory::readInMonsterDescriptionsFile(char* filepath) {
  //try_f_read(filepath);
  cout << "-- START FILE READ --\n";
  ifstream f(filepath);
  
  int linenum = 0;
  string word;
  
  string line = getNextLine(f);
  //line = getNextLine(f);
  if (line.compare("RLG327 MONSTER DESCRIPTION 1") != 0) {
    cout << "first line did not match description";
    return 1;
  }
  
  
  line = getNextLine(f);
  linenum += 2;
  
  /* go through each line of the file and parse */
  while(line.size() > 0) {
    cout << "R" << linenum << " " << line << "\n";
    if (linenum == 2) {
      if (line.compare("") != 0) {
        cout << "second line wasn't blank\n";
        return 1;
      }
      
    }
    line = getNextLine(f);
    linenum++;
    
  }
  return 0;
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