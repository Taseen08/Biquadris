#include "commandmanager.h"

using namespace std;

bool CommandManager::isPrefix(string original, string prefix) {
  if (original.find(prefix) == 0) {
    return true;
  } else {
    return false;
  }
}

int CommandManager::multiplier(string in ) {
  stringstream ss;
  ss << in ;
  int mult;
  if (ss >> mult) {
    return mult;
  } else {
    return 1;
  }
}

//if input command ambiguous or wrong, returns error, else returns appropriate command
string CommandManager::commandDetector(string in ) {
  int mult;
  stringstream ss;
  ss << in ;
  string command;
  string out;
  if (ss >> mult) {
    if (!(ss >> command)) {
      out = "error!";
    }
    if (mult < 0) {
      out = "error!";
    }

  } else {
    command = in ;
    if (command.find("rename") != string::npos) {
      return command;
    }
  }

  int count = 0;
  int len = commands.size();
  for (int i = 0; i < len; ++i) {
    string presentcommand = renamed[i]; 
    if (isPrefix(presentcommand, command)) {
      count += 1;
      out = commands[i];
    }
  }
  if (count > 1) {
    return "error!";
  }
  return out;
}

void CommandManager::renamer(string oldcommand, string newcommand) {
  int len = renamed.size();

  for (int i = 0; i < len; ++i) {
    string current = renamed[i];
    if (isPrefix(current, newcommand)) { // if true that command already exists 
      cout << "Error occurred! Command is vague or already exists" << endl; // WHAT is vague command????
      return;
    }
  }
  // modify old command
  for (int i = 0; i < len; ++i) {
    if (renamed[i] == oldcommand) {
      renamed[i] = newcommand;
    }
  }

}