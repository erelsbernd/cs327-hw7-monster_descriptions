//
//  MonsterType.cpp
//  hw7-monster_descriptions
//
//  Created by Erin Elsbernd on 11/1/16.
//  Copyright © 2016 Erin Elsbernd. All rights reserved.
//

#include <iostream>
#include <ncurses.h>

#include "MonsterType.hpp"


MonsterType::MonsterType() {
  
  for(int i = 0; i < NUM_SKILLZ; i++) {
    skillz[i] = false;
  }
  
  for(int i = 0; i < 8; i++) {
    color[i] = false;
  }
}

void printDice(dice &d) {
  cout << d.base_value << "+" << d.num_dice << "d" << d.num_sides << "\n";
}

void printSkillz(bool s[NUM_SKILLZ]) {
  if (s[ SMART   ]){ cout << "SMART "   ;}
  if (s[ TELE    ]){ cout << "TELE "    ;}
  if (s[ TUNNEL  ]){ cout << "TUNNEL "  ;}
  if (s[ ERRATIC ]){ cout << "ERRATIC " ;}
  if (s[ PASS    ]){ cout << "PASS "    ;}
  cout << "\n";
}

void printColors(bool c[NUM_COLORS]) {
  if (c[ COLOR_BLACK  ]){ cout << "BLACK "  ;}
  if (c[ COLOR_RED    ]){ cout << "RED "    ;}
  if (c[ COLOR_GREEN  ]){ cout << "GREEN "  ;}
  if (c[ COLOR_YELLOW ]){ cout << "YELLOW " ;}
  if (c[ COLOR_BLUE   ]){ cout << "BLUE "   ;}
  if (c[ COLOR_MAGENTA]){ cout << "MAGENTA ";}
  if (c[ COLOR_CYAN   ]){ cout << "CYAN "   ;}
  if (c[ COLOR_WHITE  ]){ cout << "WHITE "  ;}
  cout << "\n";
  
  
#define COLOR_BLACK	  0
#define COLOR_RED	    1
#define COLOR_GREEN	  2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7
}

void MonsterType::printMonsterType() {
  
  //cout << "MonsterType\n";
  cout << name << "\n";
  cout << description;
  cout << symbol << "\n";
  printColors(color);
  printDice(speed);
  printSkillz(skillz);
  printDice(hitpoints);
  printDice(attackdamage);
  
}