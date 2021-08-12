#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <vector>

#include <string>

#include <iostream>

#include <sstream>

#include <algorithm>  // not sure what this does

using namespace std;

class CommandManager {
  private:
    bool isPrefix(string original, string prefix);
  vector < string > commands = {
    "quit",
    "left",
    "right",
    "down",
    "clockwise",
    "counterclockwise",
    "drop",
    "levelup",
    "leveldown",
    "norandom",
    "random",
    "sequence",
    "I",
    "J",
    "L",
    "O",
    "S",
    "Z",
    "T",
    "restart",
    "blind",
    "force",
    "heavy",
    "rename",
    "keystrokeson"
  };
  vector < string > renamed = {
    "quit",
    "left",
    "right",
    "down",
    "clockwise",
    "counterclockwise",
    "drop",
    "levelup",
    "leveldown",
    "norandom",
    "random",
    "sequence",
    "I",
    "J",
    "L",
    "O",
    "S",
    "Z",
    "T",
    "restart",
    "blind",
    "force",
    "heavy",
    "rename",
    "keystrokeson"
  };

  public:
    int multiplier(string in );
  string commandDetector(string in );
  void renamer(string oldcommand, string newcommand);

};

#endif