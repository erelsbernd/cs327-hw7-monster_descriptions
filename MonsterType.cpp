//
//  MonsterType.cpp
//  hw7-monster_descriptions
//
//  Created by Erin Elsbernd on 11/1/16.
//  Copyright © 2016 Erin Elsbernd. All rights reserved.
//

#include "MonsterType.hpp"

class MonsterType {
  
  public:
  /** A name to describe the monster, for example, a “slime”, an “amazon”,
   a “wyvern”, or “Sauron”. Terminated by a newline */
  char* name;
  
  /** A textual description of the monster. Beginning on the next line
   after the keyword, terminated by a period on a line by itself, and
   limited to a width of 77 characters (the newline must appear at or
   before byte 78).*/
  char* description;
  
  /** A list of space-delineated color name keywords (see color information
   below), used to color the monster in the dungeon (not implemented
   yet, but curses makes this easy), followed by a newline. */
  char* color;
  
  /** A numerical value (dice, as defined above) describing the speed of
   a monster, followed by a newline */
  int base;
  int dice;
  int sides;
  
  /** List of space-delineated abilities keywords. For now, we’ve got
   SMART, for smart monsters, TELE, for telepathic monsters, TUNNEL
   for monsters that can tunnel through rock, ERRATIC for erratic
   monsters, and let’s add and PASS, for non-corporeal monsters, like
   ghosts, that can pass through matter without damaging it, followed
   by a newline. */
  char* abilities;
  
  /** A numerical value describing the amount of damage a monster can
   take, followed by a newline. */
  int hitpoints;
  
  /** A numerical value describing the amount of damage a monster can
   inflict per attack, followed by a newline. */
  int attackdamage;
  
  
};