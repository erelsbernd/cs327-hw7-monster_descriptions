//
//  MonsterFactory.hpp
//  hw7-monster_descriptions
//
//  Created by Erin Elsbernd on 11/1/16.
//  Copyright © 2016 Erin Elsbernd. All rights reserved.
//

#ifndef MonsterFactory_hpp
#define MonsterFactory_hpp

#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <list>
#include "MonsterType.hpp"

using namespace std;

class MonsterFactory {
  
public:
  vector<MonsterType> monsterList;
  
  //MonsterType& createNewMonsterType();
  
  int readInMonsterDescriptionsFile(char* filepath);
  
  string getNextLine(istream& in);
  string getNextWord(istream& in);
  string getString(istream & in, char delim);
  
  
};



#endif /* MonsterFactory_hpp */
