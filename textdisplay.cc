#include <iostream>

#include <string>

#include <vector>

#include <iomanip>

#include "cell.h"

#include "grid.h"

#include "textdisplay.h"

#include "observer.h"

#include "subject.h"

using namespace std;

void TextDisplay::makeReadyNext() {
  int val = 8;
  char x = ' ';
  for (int i = 0; i < val; i++) {
    stateOne.emplace_back(x);
    stateTwo.emplace_back(x);
  }
}

//TextDisplay Constructor
TextDisplay::TextDisplay(int w, int h, Grid * gridOne, Grid * gridTwo):
  w {
    w
  }, h {
    h
  }, gridOne {
    gridOne
  }, gridTwo {
    gridTwo
  } {
    //initialize the board displays
    for (int i = 0; i < h; i++) {
      vector < char > line;
      displayOne.emplace_back(line);
      displayTwo.emplace_back(line);
      for (int j = 0; j < w; j++) {
        displayOne[i].emplace_back(' ');
        displayTwo[i].emplace_back(' ');
      }
    }
    makeReadyNext();
  }

//notify the TextDisplay if a tile has changed
void TextDisplay::notify(Cell & who) {
  char state = who.getState();
  Grid * grid = who.getGrid();
  if (grid == gridOne) displayOne[who.getX()][who.getY()] = state;
  else if (grid == gridTwo) displayTwo[who.getX()][who.getY()] = state;
}

// blinds
void TextDisplay::blind(int player, ostream & out) const {
  string spaceBetweenBoards;
  for (size_t i = 0; i < 8; i++) {
    spaceBetweenBoards += " ";
  }
  vector < vector < char >> cd;
  if (player == 1) {
    cd = displayOne;
  }
  else if (player == 2) {
    cd = displayTwo;
  }
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      if ((y >= 2 && y <= 8) && (x >= 5 && x <= 14)) {
        cd[x][y] = '?';
      }
    }
  }
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      if (!(player == 1)) {
        out << displayOne[x][y];
      } else {
        out << cd[x][y];
      }
    }
    out << spaceBetweenBoards;
    for (int y = 0; y < w; y++) {
      if (!(player == 2)) {
        out << displayTwo[x][y];
      } else {
        out << cd[x][y];
      }
    }
    out << endl;
  }
}


//notify the TextDisplay if a nextBlock has been set
void TextDisplay::notify(Grid & who) {
  if (who.fixedNext) {
    int p = who.getPlayer();
    modifyNext(who.getNextBlock(), p);
  }
}

//takes in two block pointers and prints them in the preview section
void TextDisplay::modifyNext(Block * nextBlock, int player) {
  //if the block is a * block, ignore it
  if (nextBlock -> whichBlock() == '*') return;
  //clear the preview before we do anything
  int total = 8;
  for (int i = 0; i < total; i++) {
    if (player == 1) {
      stateOne[i] = ' ';
    } else {
      stateTwo[i] = ' ';
    }
  }
  for (int i = 0; i < (total / 2); i++) {
    int idx = nextBlock -> getShape()[i];
    if (player == 1) {
      stateOne[idx] = nextBlock -> whichBlock();
    } else {
      stateTwo[idx] = nextBlock -> whichBlock();
    }
  }
}

//prints the two previews for the nextblock
void TextDisplay::showDisplay(ostream & out) const {
  string beforeGap;
  string afterGap;
  for (int i = 0; i < (w + 4); i++) {
    beforeGap += " ";
  }
  for (int i = 0; i < (w + 3); i++) {
    afterGap += " ";
  }
  out << "Next:" << afterGap << "Next:" << endl; // below loops can be combined
  for (int i = 0; i < 4; i++) {
    out << stateOne[i];
  }
  out << beforeGap;
  for (int i = 0; i < 4; i++) {
    out << stateTwo[i];
  }
  out << endl;
  for (int i = 4; i < 8; i++) {
    out << stateOne[i];
  }
  out << beforeGap;
  for (int i = 4; i < 8; i++) {
    out << stateTwo[i];
  }
  out << endl;
}

void implementGap(ostream & out, int val) {
  string s = "";
  for (int i = 0; i < val - 1; i++) {
    s += " ";
  }
  s += " ";
  out << s;
}

//overloaded ostream operator for TextDisplay
ostream & operator << (ostream & out,
  const TextDisplay & td) {
  int s = (((td.w * 2) + 8) - (8 * 2)) / 2;
  string gapGrids = "";
  string gapHiscore = "";
  string dashedLine = "";
  for (int i = 0; i < 8; i++) {
    gapGrids.append(" "); // can use +=?
  }
  for (int i = 0; i < s; i++) {
    gapHiscore.append(" "); // can use +=?
  }
  //initialization of the divider and the space between the two boards
  for (int i = 0; i < td.w; i++) {
    dashedLine += "-";
  }
  //Print out the High Score at the top
  out << endl;
  out << gapHiscore << "High Score:";
  implementGap(out, 5);
  out << td.gridOne -> getHighScore() << gapHiscore << endl;
  //Printing the header information
  out << "Level:";
  implementGap(out, 5);
  out << td.gridOne -> getLevel() << gapGrids;
  out << "Level:";
  implementGap(out, 5);
  out << td.gridTwo -> getLevel() << endl;
  out << "Score:";
  implementGap(out, 5);
  out << td.gridOne -> getScore() << gapGrids;
  out << "Score:";
  implementGap(out, 5);
  out << td.gridTwo -> getScore() << endl;
  out << dashedLine << gapGrids << dashedLine << endl;
  //Printing the two boards and their contents
  if (td.gridOne -> isBlind()) {
    td.blind(1, out);
  } else if (td.gridTwo -> isBlind()) {
    td.blind(2, out);
  } else {
    for (int x = 0; x < td.h; x++) {
      for (int y = 0; y < td.w; y++) {
        out << td.displayOne[x][y];
      }
      out << gapGrids;
      for (int y = 0; y < td.w; y++) {
        out << td.displayTwo[x][y];
      }
      out << endl;
    }
  }
  out << dashedLine << gapGrids << dashedLine << endl;
  //Printing the preview section
  td.showDisplay(out);
  out << endl;
  return out;
}

TextDisplay::~TextDisplay() {}
