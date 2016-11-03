#define NOMINMAX
#include "MonsterFactory.hpp"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#include <ncurses.h>


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
    
    
    free(filename);
  } else {
    if (!(f = fopen(file, "r"))) {
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

vector<string> split(const char *str, char c = ' ')
{
  vector<string> result;
  
  do
  {
    const char *begin = str;
    
    while(*str != c && *str)
      str++;
    
    result.push_back(string(begin, str));
  } while (0 != *str++);
  
  return result;
}

int MonsterFactory::readInMonsterDescriptionsFile(char* filepath) {
  //try_f_read(filepath);
  cout << "-- START FILE READ --\n";
  ifstream f(filepath);
  
  int linenum = 0;
  string word;
  
  string line = getNextLine(f);
  if (line.compare("RLG327 MONSTER DESCRIPTION 1") != 0) {
    cout << "first line did not match description";
    return 1;
  }
  
  line = getNextLine(f); linenum += 1;
  
  /* go through each line of the file and parse */
  while(!f.eof()) {
    cout << "R" << linenum << " " << line << "\n";
    
    /* checking for blank line */
    if (line.compare("") != 0) {
      cout << "next line wasn't blank!\n";
      return 1;
    } else {
      
      line = getNextLine(f); linenum += 1;
    
      /* checking for BEGIN MONSTER */
      if (line.compare("BEGIN MONSTER") != 0) {
        cout << "third line wasn't correct\n";
        return 1;
      }
      else {
        MonsterType *m = new MonsterType();
        
        word = getNextWord(f);
        
        while (word.compare("END") != 0) {
          
          /* NAME keyword */
          if (word.compare("NAME") == 0) {
            line = getNextLine(f);
            m->name = line;
            
            cout << "name = " << m->name << "\n";
          }
          /* SYMB keyword */
          else if (word.compare("SYMB") == 0) {
            line = getNextLine(f);
            if (line.size() != 1) {
              cout << "symbol is wrong size!\n";
              return 1;
            }
            m->symbol = line[0];
            
            cout << "symbol = " << m->symbol << "\n";
          } else if (word.compare("COLOR") == 0){
            
            line = getNextLine(f);
            
            cout << "all colors = " << line << "\n";
            
            vector<string> colors = split(line.c_str(), ' ');
            
            for ( auto color : colors) {
              if (color.compare("BLACK") == 0) {
                m->color = COLOR_BLACK;
              }
              else if (color.compare("RED") == 0) {
                m->color = COLOR_RED;
              }
              else if (color.compare("GREEN") == 0) {
                m->color = COLOR_GREEN;
              }
              else if (color.compare("YELLOW") == 0) {
                m->color = COLOR_YELLOW;
              }
              else if (color.compare("BLUE") == 0) {
                m->color = COLOR_BLUE;
              }
              else if (color.compare("MAGENTA") == 0) {
                m->color = COLOR_MAGENTA;
              }
              else if (color.compare("CYAN") == 0) {
                m->color = COLOR_CYAN;
              }
              else if (color.compare("WHITE") == 0) {
                m->color = COLOR_WHITE;
              }
              else {
                cout << "Bad color = " << color << "\n";
                return 1;
              }
              //cout << "color += " << color << "\n";
            }
          
          }else {
            cout << "bad keyword!\n";
            return 1;
          }
          
          word = getNextWord(f);
        } // "END" while
      } // "BEGIN MONSTER" else
    } //blank line check
    
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