#define NOMINMAX
#include "MonsterFactory.hpp"

#include <fstream>
#include <iostream>
#include <deque>

#include <ncurses.h>


#define SAVE_DIR                ".rlg327"
#define MONSTER_DESC_SAVE_FILE  "monster_desc.txt"
#define MONSTER_DESC_SEMANTIC   "RLG327"
#define MONSTER_DESC_VERSION    1

using namespace std;

/* splits a string into tokens */
deque<string> split(const char *str, char c = ' ')
{
  deque<string> result;
  
  do
  {
    const char *start = str; //remember pointer start
    
    while(*str != c && *str) //increment pointer until space
      str++;
    
    result.push_back(string(start, str)); //push string from start to space
    
  } while (0 != *str++); //continue if pointer not at terminal character
  
  return result;
}

void read_in_dice(dice &d, string &s) {
  
  uint64_t start = 0;
  uint64_t end   = s.find('+');
  
  string num = s.substr(start,end);
  d.base_value = atoi( num.c_str() );
  //cout << "base = " << m->speed.base_value << "\n";
  
  start = s.find('+') + 1;
  end   = s.find('d');
  
  num = s.substr(start,end);
  d.num_dice = atoi( num.c_str() );
  //cout << "dice = " << m->speed.num_dice << "\n";
  
  start = s.find('d') + 1;
  end   = s.npos;
  
  num = s.substr(start,end);
  d.num_sides = atoi( num.c_str() );
  //cout << "sides = " << m->speed.num_sides << "\n";
  
  cout << "dice = base " << d.base_value << " plus "
                    << d.num_dice   << " dice with "
                    << d.num_sides  << " sides\n";
}

int MonsterFactory::readInMonsterDescriptionsFile(char* filepath) {
  //try_f_read(filepath);
  cout << "-- START FILE READ --\n";
  ifstream f(filepath);
  
  int linenum = 0;
  deque<string> tokens;
  
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
      
      MonsterType *m = new MonsterType();
      
      line = getNextLine(f);
      tokens = split(line.c_str());
      
      string keyword = tokens.front();
      tokens.pop_front(); //remove the front
      
      while (keyword.compare("END") != 0) {
        
        /* NAME keyword */
        if (keyword.compare("NAME") == 0) {
          
          //makes name equal to front token and pops it off
          m->name = tokens.front();
          //pops off front of tokens
          tokens.pop_front();
          for (auto word : tokens) {
            m->name += ' ' + word;
          }
          
          cout << "Name = " << m->name << "\n";
        }
        else if (keyword.compare("SYMB") == 0) {
          //line = getNextLine(f);
          if (tokens.size() != 1) {
            cout << "symbol is wrong size!\n";
            return 1;
          }
          m->symbol = tokens.front()[0];
          
          cout << "Symbol = " << m->symbol << "\n";
        }
        else if (keyword.compare("COLOR") == 0){
          
          cout << "Colors";
          for ( auto color : tokens) {
            if      (color.compare("BLACK") == 0){ m->color = COLOR_BLACK;  }
            else if (color.compare("RED")   == 0){ m->color = COLOR_RED;    }
            else if (color.compare("GREEN") == 0){ m->color = COLOR_GREEN;  }
            else if (color.compare("YELLOW")== 0){ m->color = COLOR_YELLOW; }
            else if (color.compare("BLUE")  == 0){ m->color = COLOR_BLUE;   }
            else if (color.compare("MAGENTA")==0){ m->color = COLOR_MAGENTA;}
            else if (color.compare("CYAN")  == 0){ m->color = COLOR_CYAN;   }
            else if (color.compare("WHITE") == 0){ m->color = COLOR_WHITE;  }
            else {
              cout << "Bad color = " << color << "\n";
              return 1;
            }
            cout << " ~ " << color << "\n";
          }
        }
        else if (keyword.compare("DESC") == 0) {
          line = getNextLine(f);
          cout << "Description:\n";
          while (line.compare(".") != 0) {
            if (line.size() > 77) {
              cout << "line size greater than 77\n";
              return 1;
            }
            cout << line << "\n";
            m->description += line + "\n";
            line = getNextLine(f);
          }
        }
        else if (keyword.compare("SPEED") == 0) {
          
          if (tokens.size() != 1) {
            cout << "speed is wrong size!\n";
            return 1;
          }
          
          cout << "Speed  ";
          string speed = tokens.front();
          read_in_dice(m->speed, speed);
          
        }
        else if (keyword.compare("DAM") == 0) {
          
          if (tokens.size() != 1) {
            cout << "damage is wrong size!\n";
            return 1;
          }
          
          cout << "Damage ";
          string damage = tokens.front();
          read_in_dice(m->attackdamage, damage);
          
        }
        else if (keyword.compare("HP") == 0) {
          
          if (tokens.size() != 1) {
            cout << "hitpoints is wrong size!\n";
            return 1;
          }
          
          cout << "Health ";
          string hitpoints = tokens.front();
          read_in_dice(m->hitpoints, hitpoints);
          
        }
        else if (keyword.compare("ABIL") == 0){
          
        }
        else {
          cout << "bad keyword! = " << keyword << "\n" ;
          return 1;
        }
        
        /* get next line */
        line = getNextLine(f);
        tokens = split(line.c_str());
        keyword = tokens.front();
        tokens.pop_front(); //remove the front
        
      } // while not "END"
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