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
  
  /*cout << "dice = base " << d.base_value << " plus "
                    << d.num_dice   << " dice with "
                    << d.num_sides  << " sides\n";*/
}

int MonsterFactory::readInMonsterDescriptionsFile(char* filepath) {
  //try_f_read(filepath);
  //cout << "-- START FILE READ --\n";
  ifstream f(filepath);
  
  /*
   #define NAME  0
   #define DESC  1
   #define SYMB  2
   #define COLOR 3
   #define SPEED 4
   #define ABIL  5
   #define HP    6
   #define DAM   7
   #define NUM_KEYWORDS 8
   */
  bool keywords[NUM_KEYWORDS];
  bool invalid_monster = false; //flag for bad input
  deque<string> tokens;
  
  string line = getNextLine(f);
  if (line.compare("RLG327 MONSTER DESCRIPTION 1") != 0) {
    cout << "first line did not match description";
    return 1;
  }
  
  line = getNextLine(f);
  
  /* go through each line of the file and parse */
  while(!f.eof()) {
    //cout << "Read in: " << line << "\n";
    
    /* checking for blank line */
    if (line.compare("") != 0) {
      cout << "next line wasn't blank!\n";
      return 1;
    }
    
    line = getNextLine(f);
    
    /* checking for BEGIN MONSTER */
    if (line.compare("BEGIN MONSTER") != 0) {
      cout << "third line wasn't correct\n";
      return 1;
    }
    
    /* reset keywords seen */
    for (int i = 0; i < NUM_KEYWORDS; i++)
      keywords[i] = false;
    
    MonsterType *m = new MonsterType();
    
    line = getNextLine(f);
    tokens = split(line.c_str());
    
    string keyword = tokens.front();
    tokens.pop_front(); //remove the front
    
    /* single MONSTER READ IN */
    while (keyword.compare("END") != 0) {
      
      if (keyword.compare("NAME") == 0) {
        
        /* CHECK if KEYWORD already used */
        if ( keywords[NAME] == true ) {
          invalid_monster = true;
          break;
        }
        else {
          keywords[NAME] = true;
        }
        
        //makes name equal to front token and pops it off
        m->name = tokens.front();
        //pops off front of tokens
        tokens.pop_front();
        for (auto word : tokens) {
          m->name += ' ' + word;
        }
        
        //cout << "Name = " << m->name << "\n";
      }
      else if (keyword.compare("SYMB") == 0) {
        
        if ( keywords[SYMB] == true ) {
          invalid_monster = true;
          break;
        }
        else {
          keywords[SYMB] = true;
        }
        
        //line = getNextLine(f);
        if (tokens.size() != 1) {
          cout << "symbol is wrong size!\n";
          return 1;
        }
        m->symbol = tokens.front()[0];
        
        //cout << "Symbol = " << m->symbol << "\n";
      }
      else if (keyword.compare("COLOR") == 0){
        //cout << "Colors";
        for ( auto color : tokens) {
          if      (color.compare("BLACK")  == 0){ m->color[BLACK]   = true; }
          else if (color.compare("RED")    == 0){ m->color[RED]     = true; }
          else if (color.compare("GREEN")  == 0){ m->color[GREEN]   = true; }
          else if (color.compare("YELLOW") == 0){ m->color[YELLOW]  = true; }
          else if (color.compare("BLUE")   == 0){ m->color[BLUE]    = true; }
          else if (color.compare("MAGENTA")== 0){ m->color[MAGENTA] = true; }
          else if (color.compare("CYAN")   == 0){ m->color[CYAN]    = true; }
          else if (color.compare("WHITE")  == 0){ m->color[WHITE]   = true; }
          else {
            cout << "Invalid color = " << color << "\n";
            return 1;
          }
          //cout << " ~ " << color << "\n";
        }
      }
      else if (keyword.compare("DESC") == 0) {
        line = getNextLine(f);
        //cout << "Description:\n";
        while (line.compare(".") != 0) {
          if (line.size() > 77) {
            cout << "line size greater than 77\n";
            return 1;
          }
          //cout << line << "\n";
          m->description += line + "\n";
          line = getNextLine(f);
        }
      }
      else if (keyword.compare("SPEED") == 0) {
        
        if (tokens.size() != 1) {
          cout << "speed is wrong size!\n";
          return 1;
        }
        
        //cout << "Speed  ";
        string speed = tokens.front();
        read_in_dice(m->speed, speed);
        
      }
      else if (keyword.compare("DAM") == 0) {
        
        if (tokens.size() != 1) {
          cout << "damage is wrong size!\n";
          return 1;
        }
        
        //cout << "Damage ";
        string damage = tokens.front();
        read_in_dice(m->attackdamage, damage);
        
      }
      else if (keyword.compare("HP") == 0) {
        
        if (tokens.size() != 1) {
          cout << "hitpoints is wrong size!\n";
          return 1;
        }
        
        //cout << "Health ";
        string hitpoints = tokens.front();
        read_in_dice(m->hitpoints, hitpoints);
        
      }
      else if (keyword.compare("ABIL") == 0){
        
        //cout << "Abilities";
        for ( auto skill : tokens) {
          if      (skill.compare("SMART")  == 0){ m->skillz[SMART]  = true;}
          else if (skill.compare("TELE")   == 0){ m->skillz[TELE]   = true;}
          else if (skill.compare("TUNNEL") == 0){ m->skillz[TUNNEL] = true;}
          else if (skill.compare("ERRATIC")== 0){ m->skillz[ERRATIC]= true;}
          else if (skill.compare("PASS")   == 0){ m->skillz[PASS]   = true;}
          else {
            cout << "Bad ability name = " << skill << "\n";
            return 1;
          }
          //cout << " ~ " << skill;
        }
        //cout << "\n";
      }
      else {
        cout << "bad keyword! = " << keyword << "\n" ;
        return 1;
      } // END of keyword read block
      
      /* get next line */
      line = getNextLine(f);
      tokens = split(line.c_str());
      keyword = tokens.front();
      tokens.pop_front(); //remove the front
      
      
    } // END of single MONSTER read in
    
    /* KEYWORDS CHECK */
    for (int i = 0; i < NUM_KEYWORDS; i++) {
      if (keywords[i] == false) invalid_monster = true;
    }
    
    /* INVALID - throw away data and lines */
    if (invalid_monster) {
      while (line.size() > 0) //eat lines until next emptyline
        line = getNextLine(f);
      break;
    }
    
    this->monsterList.push_back(*m);
    line = getNextLine(f);
  
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