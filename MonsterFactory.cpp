#define NOMINMAX
#include "MonsterFactory.hpp"

#include <fstream>
#include <iostream>
#include <deque>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include <ncurses.h>


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
  
  /* FILE READ IN */
  /* go through each line of the file and parse */
  while(!f.eof()) {
    //cout << "Read in: " << line << "\n";
    
    /* CHECK for BLANK LINE */
    if (line.compare("") != 0) {
      cout << "BLANK LINE not seen before next monster! Aborting program.\n";
      return 1;
    }
    
    line = getNextLine(f); //get NEXT line to check
    
    /* CHECK for BEGIN MONSTER */
    if (line.compare("BEGIN MONSTER") != 0) {
      cout << "BEGIN MONSTER did not appear first. Discarding monster.\n\n";
      invalid_monster = true;
      break;
    }
    
    line = getNextLine(f); // get NEXT line to check
    
    /* SETUP for NEXT monster */
    
    MonsterType *m = new MonsterType();
    
    invalid_monster = false;
    for (int i = 0; i < NUM_KEYWORDS; i++) //REST KEYWORDS MEMORY
      keywords[i] = false;
    
    tokens = split(line.c_str()); //split into a STRING vector
    
    string keyword = tokens.front(); tokens.pop_front();
    
    /* MONSTER READ IN */
    while (keyword.compare("END") != 0 && invalid_monster != true) {
      
      if (keyword.compare("NAME") == 0) {
        
        /* CHECK if KEYWORD already used */
        if ( keywords[NAME] == true ) {
          cout << "NAME Keyword was already used! Discarding monster.\n\n";
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
        for (uint32_t i=0; i<tokens.size(); i++) { //auto word : tokens) {
          string word = tokens[i];
          m->name += ' ' + word;
        }
        
        //cout << "Name = " << m->name << "\n";
      }
      else if (keyword.compare("SYMB") == 0) {
        
        if ( keywords[SYMB] == true ) {
          cout << "SYMB Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[SYMB] = true;
        }
        
        //line = getNextLine(f);
        if (tokens.size() != 1) {
          cout << "symbol is wrong size!\n";
          invalid_monster = true;
          break;
        }
        m->symbol = tokens.front()[0];
        
        //cout << "Symbol = " << m->symbol << "\n";
      }
      else if (keyword.compare("COLOR") == 0){
        //cout << "Colors";
        
        /* CHECK if KEYWORD already used */
        if ( keywords[COLOR] == true ) {
          cout << "COLOR Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[COLOR] = true;
        }
        
        for (uint32_t i=0; i < tokens.size(); i++) {
          string color = tokens[i];
          if      (color.compare("BLACK")  == 0){ m->color[BLACK]   = true; }
          else if (color.compare("RED")    == 0){ m->color[RED]     = true; }
          else if (color.compare("GREEN")  == 0){ m->color[GREEN]   = true; }
          else if (color.compare("YELLOW") == 0){ m->color[YELLOW]  = true; }
          else if (color.compare("BLUE")   == 0){ m->color[BLUE]    = true; }
          else if (color.compare("MAGENTA")== 0){ m->color[MAGENTA] = true; }
          else if (color.compare("CYAN")   == 0){ m->color[CYAN]    = true; }
          else if (color.compare("WHITE")  == 0){ m->color[WHITE]   = true; }
          else {
            cout << "Invalid Color = " << color <<  " , Discarding monster.\n\n";
            invalid_monster = true;
            break;

          }
          //cout << " ~ " << color << "\n";
        }
      }
      else if (keyword.compare("DESC") == 0) {
        
        /* CHECK if KEYWORD already used */
        if ( keywords[DESC] == true ) {
          cout << "DESC Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[DESC] = true;
        }
        
        line = getNextLine(f);
        //cout << "Description:\n";
        while (line.compare(".") != 0) {
          if (line.size() > 77) {
            cout << "Description line longer than 77. Discarding monster.\n\n";
            invalid_monster = true;
            break;

          }
          //cout << line << "\n";
          m->description += line + "\n";
          line = getNextLine(f);
        }
      }
      else if (keyword.compare("SPEED") == 0) {
        
        /* CHECK if KEYWORD already used */
        if ( keywords[SPEED] == true ) {
          cout << "SPEED Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[SPEED] = true;
        }
        
        if (tokens.size() != 1) {
          cout << "Speed has too many arguments! Discarding monster.\n\n";
          invalid_monster = true;
          break;

        }
        
        //cout << "Speed  ";
        string speed = tokens.front();
        read_in_dice(m->speed, speed);
        
      }
      else if (keyword.compare("DAM") == 0) {
        
        /* CHECK if KEYWORD already used */
        if ( keywords[DAM] == true ) {
          cout << "DAM Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[DAM] = true;
        }
        
        if (tokens.size() != 1) {
          cout << "Damage has too many arguments! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        
        //cout << "Damage ";
        string damage = tokens.front();
        read_in_dice(m->attackdamage, damage);
        
      }
      else if (keyword.compare("HP") == 0) {
        
        /* CHECK if KEYWORD already used */
        if ( keywords[HP] == true ) {
          cout << "HP Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[HP] = true;
        }
        
        if (tokens.size() != 1) {
          cout << "Hitpoints has too many arguments! Discarding monster.\n\n";
          invalid_monster = true;
          break;

        }
        
        //cout << "Health ";
        string hitpoints = tokens.front();
        read_in_dice(m->hitpoints, hitpoints);
        
      }
      else if (keyword.compare("ABIL") == 0){
        
        /* CHECK if KEYWORD already used */
        if ( keywords[ABIL] == true ) {
          cout << "ABIL Keyword was already used! Discarding monster.\n\n";
          invalid_monster = true;
          break;
        }
        else {
          keywords[ABIL] = true;
        }
        
        //cout << "Abilities";
        for (uint32_t i=0; i<tokens.size(); i++) { //auto skill : tokens) {
          string skill = tokens[i];
          if      (skill.compare("SMART")  == 0){ m->skillz[SMART]  = true;}
          else if (skill.compare("TELE")   == 0){ m->skillz[TELE]   = true;}
          else if (skill.compare("TUNNEL") == 0){ m->skillz[TUNNEL] = true;}
          else if (skill.compare("ERRATIC")== 0){ m->skillz[ERRATIC]= true;}
          else if (skill.compare("PASS")   == 0){ m->skillz[PASS]   = true;}
          else {
            cout << "Invalid Ability = " << skill << ". Discarding monster.\n\n";
            invalid_monster = true;
            break;

          }
          //cout << " ~ " << skill;
        }
        //cout << "\n";
      }
      else {
        cout << "Invalid Keyword! = " << keyword << "\n";
        cout << "  Discarding Monster Type.\n" ;
        invalid_monster = true;
        break;
      } // END of keyword read block
      
      /* get next line */
      line = getNextLine(f);
      tokens = split(line.c_str());
      keyword = tokens.front();
      tokens.pop_front(); //remove the front
      
      
    } // END of single MONSTER read in
    //cout << "END SINGLE MONSTER!\n";
    
    /* KEYWORDS CHECK */
    if (!invalid_monster) {
      for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (keywords[i] == false) {
          invalid_monster = true;
          cout << "A Keyword was missing! Discarding Monster Type.\n";
          break;
        }
      }
    }
    
    /* INVALID - throw away data and lines */
    if (invalid_monster) {
     
     //eat lines until next emptyline
      while (line.size() > 0) {
        line = getNextLine(f);
      }
    }
    else {
      this->monsterList.push_back(*m);
      line = getNextLine(f);
    }
    
  
  
  } // END of FILE READ IN, WHILE
  //cout << "END FILE!\n";

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