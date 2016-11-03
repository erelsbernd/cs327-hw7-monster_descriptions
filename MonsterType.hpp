#ifndef MonsterType_hpp
#define MonsterType_hpp


#include <stdio.h>
#include <string>
#include "npc.h"

using namespace std;

#define NAME  0
#define DESC  1
#define SYMB  2
#define COLOR 3
#define SPEED 4
#define ABIL  5
#define HP    6
#define DAM   7
#define NUM_KEYWORDS 8

#define SMART   0 //smart monsters (remember where player is)
#define TELE    1 //telepathic monsters (always know where player is)
#define TUNNEL  2 //can tunnel through rock (doesn't have to follow hallways)
#define ERRATIC 3 //erratic monsters (random move 50% of time)
#define PASS    4 //non-corporeal monsters, like ghosts, that can
                  //pass through matter without damaging it,
#define NUM_SKILLZ 5


#define BLACK	  0
#define RED	    1
#define GREEN	  2
#define YELLOW   3
#define BLUE     4
#define MAGENTA  5
#define CYAN     6
#define WHITE    7
#define NUM_COLORS 8

/* //colors, from <ncurses.h>
 #define COLOR_BLACK	  0
 #define COLOR_RED	    1
 #define COLOR_GREEN	  2
 #define COLOR_YELLOW   3
 #define COLOR_BLUE     4
 #define COLOR_MAGENTA  5
 #define COLOR_CYAN     6
 #define COLOR_WHITE    7
 */

struct dice {
  uint32_t base_value;
  uint32_t num_dice;
  uint32_t num_sides;
};

class MonsterType {
  
public:
  MonsterType();
  
  void printMonsterType();
  /** A name to describe the monster, for example, a “slime”, an “amazon”,
   a “wyvern”, or “Sauron”. Terminated by a newline */
  string name;
  
  /* a char to represent the monster */
  char symbol;
  
  /** A textual description of the monster. Beginning on the next line
   after the keyword, terminated by a period on a line by itself, and
   limited to a width of 77 characters (the newline must appear at or
   before byte 78).*/
  string description;
  
  /** A list of space-delineated color name keywords (see color information
   below), used to color the monster in the dungeon (not implemented
   yet, but curses makes this easy), followed by a newline. */
  bool color[NUM_COLORS];

/* //colors
#define COLOR_BLACK	  0
#define COLOR_RED	    1
#define COLOR_GREEN	  2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7
 */
  
  /** A numerical value (dice, as defined above) describing the speed of
   a monster, followed by a newline */
  dice speed;
  
  /** List of space-delineated abilities keywords. For now, we’ve got:
   0 SMART:   smart monsters (remember where player is)
   1 TELE:    telepathic monsters (always know where player is)
   2 TUNNEL:  can tunnel through rock (doesn't have to follow hallways)
   3 ERRATIC: erratic monsters (random move 50% of time)
   4 PASS:    non-corporeal monsters, like ghosts, that can pass through 
              matter without damaging it,
   followed by a newline. */
  
  /** A numerical value describing the amount of damage a monster can
   take, followed by a newline. */
  dice hitpoints;
  
  /** A numerical value describing the amount of damage a monster can
   inflict per attack, followed by a newline. */
  dice attackdamage;
  
  bool skillz[NUM_SKILLZ];
  uint32_t skill_bitz; //use for bit-masking???
  
};

#endif /* MonsterType_hpp */
