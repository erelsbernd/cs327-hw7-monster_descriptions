#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#include "dungeon.h"
#include "pc.h"
#include "npc.h"
#include "move.h"
#include "io.h"
#include "MonsterFactory.hpp"

const char *victory =
  "\n                                       o\n"
  "                                      $\"\"$o\n"
  "                                     $\"  $$\n"
  "                                      $$$$\n"
  "                                      o \"$o\n"
  "                                     o\"  \"$\n"
  "                oo\"$$$\"  oo$\"$ooo   o$    \"$    ooo\"$oo  $$$\"o\n"
  "   o o o o    oo\"  o\"      \"o    $$o$\"     o o$\"\"  o$      \"$  "
  "\"oo   o o o o\n"
  "   \"$o   \"\"$$$\"   $$         $      \"   o   \"\"    o\"         $"
  "   \"o$$\"    o$$\n"
  "     \"\"o       o  $          $\"       $$$$$       o          $  ooo"
  "     o\"\"\n"
  "        \"o   $$$$o $o       o$        $$$$$\"       $o        \" $$$$"
  "   o\"\n"
  "         \"\"o $$$$o  oo o  o$\"         $$$$$\"        \"o o o o\"  "
  "\"$$$  $\n"
  "           \"\" \"$\"     \"\"\"\"\"            \"\"$\"            \""
  "\"\"      \"\"\" \"\n"
  "            \"oooooooooooooooooooooooooooooooooooooooooooooooooooooo$\n"
  "             \"$$$$\"$$$$\" $$$$$$$\"$$$$$$ \" \"$$$$$\"$$$$$$\"  $$$\""
  "\"$$$$\n"
  "              $$$oo$$$$   $$$$$$o$$$$$$o\" $$$$$$$$$$$$$$ o$$$$o$$$\"\n"
  "              $\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""
  "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"$\n"
  "              $\"                                                 \"$\n"
  "              $\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\""
  "$\"$\"$\"$\"$\"$\"$\"$\n"
  "                                   You win!\n\n";

const char *tombstone =
  "\n\n\n\n                /\"\"\"\"\"/\"\"\"\"\"\"\".\n"
  "               /     /         \\             __\n"
  "              /     /           \\            ||\n"
  "             /____ /   Rest in   \\           ||\n"
  "            |     |    Pieces     |          ||\n"
  "            |     |               |          ||\n"
  "            |     |   A. Luser    |          ||\n"
  "            |     |               |          ||\n"
  "            |     |     * *   * * |         _||_\n"
  "            |     |     *\\/* *\\/* |        | TT |\n"
  "            |     |     *_\\_  /   ...\"\"\"\"\"\"| |"
  "| |.\"\"....\"\"\"\"\"\"\"\".\"\"\n"
  "            |     |         \\/..\"\"\"\"\"...\"\"\""
  "\\ || /.\"\"\".......\"\"\"\"...\n"
  "            |     |....\"\"\"\"\"\"\"........\"\"\"\"\""
  "\"^^^^\".......\"\"\"\"\"\"\"\"..\"\n"
  "            |......\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"......"
  "..\"\"\"\"\"....\"\"\"\"\"..\"\"...\"\"\".\n\n"
  "            You're dead.  Better luck in the next life.\n\n\n";

void usage(char *name)
{
  fprintf(stderr,
          "Usage: %s [-r|--rand <seed>] [-l|--load [<file>]]\n"
          "       [-i|--image <pgm>] [-s|--save] [-p|--pc <y> <x>]\n"
          "       [-n|--nummon <monster count>\n",
          name);

  exit(-1);
}

#define MONSTER_DESC_SAVE_DIR   ".rlg327"
#define MONSTER_DESC_SAVE_FILE  "monster_desc.txt"

/* for testing */
int main(int argc, char *argv[])
{
  //char filename[] = "monster_desc.txt";
  ///Users/erelsbernd/Documents/IowaState/IowaStateFall2016/cs327/hw7-monster_descriptions
  
  
  //char *save_file = NULL;
  /*char filename[] = "/Users/erelsbernd/Documents/IowaState/IowaStateFall2016/cs327/hw7-monster_descriptions/monster_desc.txt";
  */
  //cout << "file=" << filename << "\n";
  
  FILE *f;
  char *home;
  size_t len;
  char *filename;
  
  if (!(home = getenv("HOME"))) {
    fprintf(stderr, "\"HOME\" is undefined.  Using working directory.\n");
    home = (char*)calloc(2, sizeof(char));
    home[0] = '.';
    home[1] = '\0';
  }
  
  len = (strlen(home) + strlen(SAVE_DIR) + strlen(DUNGEON_SAVE_FILE) +
         1 /* The NULL terminator */                                 +
         2 /* The slashes */);
  
  filename = (char*) malloc(len * sizeof (*filename));
  sprintf(filename, "%s/%s/%s", home, MONSTER_DESC_SAVE_DIR,
          MONSTER_DESC_SAVE_FILE);
  //cout << "file=" << filename << "\n";
  
  MonsterFactory factory;
  int factoryReturn = factory.readInMonsterDescriptionsFile(filename);
  if (factoryReturn == 1) {
    std::cout << "Shit didn't work yo\n";
    return 1;
  }
  
  int i = 0;
  for (i = 0; i < factory.monsterList.size(); i++)
  {
    factory.monsterList[i].printMonsterType();
    cout << "\n";
  }
 
  
  return 0;
}
