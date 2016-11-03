//
//  MonsterType.hpp
//  hw7-monster_descriptions
//
//  Created by Erin Elsbernd on 11/1/16.
//  Copyright © 2016 Erin Elsbernd. All rights reserved.
//

#ifndef MonsterType_hpp
#define MonsterType_hpp

#include <stdio.h>
#include <string>

using namespace std;

class MonsterType {
  
public:
  MonsterType() {}
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
  int color;
  /* COLOR_BLACK */
  /* COLOR_RED */
  /* COLOR_GREEN */
  /* COLOR_YELLOW */
  /* COLOR_BLUE */
  /* COLOR_MAGENTA */
  /* COLOR_CYAN */
  /* COLOR_WHITE */
  
  /** A numerical value (dice, as defined above) describing the speed of
   a monster, followed by a newline */
  uint32_t base_value;
  uint32_t num_dice;
  uint32_t num_sides;
  
  /** List of space-delineated abilities keywords. For now, we’ve got:
   SMART:   smart monsters (remember where player is)
   TELE:    telepathic monsters (always know where player is)
   TUNNEL:  can tunnel through rock (doesn't have to follow hallways)
   ERRATIC: erratic monsters (random move 50% of time)
   PASS:    non-corporeal monsters, like ghosts, that can
             pass through matter without damaging it,
   followed by a newline. */
  bool abilities[8]; //easier use for single ability checking
  uint32_t ability_bits; //use for bit-masking
  
  /** A numerical value describing the amount of damage a monster can
   take, followed by a newline. */
  uint32_t hitpoints;
  
  /** A numerical value describing the amount of damage a monster can
   inflict per attack, followed by a newline. */
  int32_t attackdamage;
  
  
};

#endif /* MonsterType_hpp */
