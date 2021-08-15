#include <iostream>

#include <vector>

#include <string>

#include "display.h"

#include "graphics.h"

#include "subject.h"

#include "observer.h"

#include "grid.h"

#include <string>

#include <map>

using namespace std;

// // map of block and corresponding color
map < char, int > dict = {
  {
    'I',
    0
  },
  {
    'J',
    1
  },
  {
    'L',
    2
  },
  {
    'O',
    3
  },
  {
    'S',
    4
  },
  {
    'Z',
    5
  },
  {
    'T',
    6
  },
  {
    '*',
    7
  }
};

string levelP1;
string levelP2;
string scoreP1;
string scoreP2;
string highscore;

int ss = 8;
string gapHS((ss * 2), ' ');
string gapLevel((ss * 4) + 1, ' ');

// constructor of GraphicsDisplay
GraphicsDisplay::GraphicsDisplay(int cw, int ww, int wh, int gw, int gh, Grid * g1, Grid * g2):
  cw {
    cw
  }, ww {
    cw * ww
  }, wh {
    cw * wh
  }, gw {
    cw * gw
  }, gh {
    cw * gh
  },
  xw {
    (cw * ww), (cw * wh)
  }, g1 {
    g1
  }, g2 {
    g2
  } {
    init();
  }

// //initializes grid cover
void GraphicsDisplay::init() {
  dist1 = cw * 5;
  mainB = cw * 7;
  gridGap = cw * 8;
  dist2 = dist1 + gw + gridGap;
  string hiVal = to_string(g1 -> getHighScore());
  string levVal1 = to_string(g1 -> getLevel());
  string levVal2 = to_string(g2 -> getLevel());
  highscore = "HIGH SCORE:" + gapHS + hiVal;
  levelP1 = "LEVEL:" + gapLevel + levVal1;
  levelP2 = "LEVEL:" + gapLevel + levVal2;
  int multiplier = 2;
  // high score and level
  string scoreStr = "SCORE:" + gapLevel + "0";
  xw.drawString((ww - gridGap) / multiplier, mainB - (multiplier * 40), highscore);
  xw.drawString(dist1, mainB - (multiplier * 20), levelP1);
  xw.drawString(dist1, mainB - (multiplier * 10), scoreStr);
  xw.drawString(dist2, mainB - (multiplier * 20), levelP2);
  xw.drawString(dist2, mainB - (multiplier * 10), scoreStr);
  double adjuster = 0.01;
  // backgrounds
  xw.fillRectangle(dist1, mainB, gw - adjuster, gh - adjuster, 9);
  xw.fillRectangle(dist2, mainB, gw - adjuster, gh - adjuster, 9);
  // next block
  xw.drawString(dist1, wh - mainB + (multiplier * 5), "NEXT BLOCK:");
  xw.drawString(dist2, wh - mainB + (multiplier * 5), "NEXT BLOCK:");
}

// notify cell
void GraphicsDisplay::notify(Cell & whoNotified) {
  int x = whoNotified.getX();
  int y = whoNotified.getY();
  int fist1 = y * cw;
  int fist2 = x * cw;
  char piece = whoNotified.getState();
  int player = whoNotified.getGrid() -> getPlayer();
  bool cellOccupied = whoNotified.isOccupied();
  // not occupied logic
  if (!cellOccupied) {
    if (player == 1) {
      xw.fillRectangle(fist1 + dist1, fist2 + mainB, (cw - 0.01), (cw - 0.01), 9);
    } else {
      xw.fillRectangle(fist1 + dist2, fist2 + mainB, (cw - 0.01), (cw - 0.01), 9);
    }
  } else {
    if (player == 1) {
      xw.fillRectangle(fist1 + dist1, fist2 + mainB, (cw - 0.01), (cw - 0.01), dict[piece]);
    } else {
      xw.fillRectangle(fist1 + dist2, fist2 + mainB, (cw - 0.01), (cw - 0.01), dict[piece]);
    }
  }
  //if this tile's board is blind, redraw the blind rectangle
  if (whoNotified.getGrid() -> isBlind()) {
    doBlind(player);
  }
}

// win message
void GraphicsDisplay::winnerWho(int player) {
  int multi = 2;
  if (player == 1) {
    xw.drawString((ww / multi) - (40 + 5), (wh / multi), "Player One is the winner!");
  } else {
    xw.drawString((ww / multi) - (40 + 5), (wh / multi), "Player Two is the winner!");
  }
}

// destructor
GraphicsDisplay::~GraphicsDisplay() {}

// notify grid
void GraphicsDisplay::notify(Grid & whoNotified) {
  // get corresponding index from dict
  int multiplier = 2;
  int who = wh + (mainB * -1);
  int player = whoNotified.getPlayer();
  int req = who + (2 * 15);
  vector < int > shape = whoNotified.getNextBlock() -> getShape();
  char piece = whoNotified.getNextBlock() -> whichBlock();
  int inc = cw + 1;
  // clear and prepare next
  if (whoNotified.fixedNext) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 1; j++) {
        if (player == 1) {
          xw.fillRectangle((cw * i) + dist1, (cw * j) + req, inc, inc, 8);
        } else {
          xw.fillRectangle((cw * i) + dist2, (cw * j) + req, inc, inc, 8);
        }
      }
    }
    int shSize = shape.size();
    for (int i = 0; i <= shSize - 1; i++) {
      int sss = shape[i];
      if (sss <= 3) {
        if (player == 1) {
          xw.fillRectangle((sss * cw) + dist1, req, inc, inc, 9);
          xw.fillRectangle((sss * cw) + dist1 + 0.005, req + 0.005, (cw - 0.01), (cw - 0.01), dict[piece]);
        } else {
          xw.fillRectangle((sss * cw) + dist2, req, inc, inc, 9);
          xw.fillRectangle((sss * cw) + dist2 + 0.005, req + 0.005, (cw - 0.01), (cw - 0.01), dict[piece]);
        }

      } else {
        if (player == 1) {
          xw.fillRectangle((sss % 4) * cw + dist1, cw + req, inc, inc, 9);
          xw.fillRectangle((sss % 4) * cw + dist1 + 0.005, cw + req + 0.005, (cw - 0.01), (cw - 0.01), dict[piece]);
        } else {
          xw.fillRectangle((sss % 4) * cw + dist2, cw + req, inc, inc, 9);
          xw.fillRectangle((sss % 4) * cw + dist2 + 0.005, cw + req + 0.005, (cw - 0.01), (cw - 0.01), dict[piece]);
        }
      }
    }
  }
  if (whoNotified.hiScoreModified) {
    string highscore;
    string strHS = to_string(g1 -> getHighScore());
    string gapHS;
    for (int i = 0; i <= ((multiplier * 8) - 1); i++) {
      gapHS += " ";
    }
    // update high score
    highscore = "HIGH SCORE:" + gapHS + strHS;
    xw.fillRectangle(dist1 * (multiplier + 2.3), mainB - (multiplier * 45), (multiplier * 40), (multiplier * 7) + 1, (multiplier * 4));
    xw.drawString((ww - gridGap) / 2, mainB - (multiplier * 40), highscore);
  }
  string lP1 = to_string(g1 -> getLevel());
  string lP2 = to_string(g2 -> getLevel());
  // update level
  if (whoNotified.levelModified) {
    levelP1 = "LEVEL:" + gapLevel + lP1;
    levelP2 = "LEVEL:" + gapLevel + lP2;
    if (player == 1) {
      xw.fillRectangle(3 * dist1, mainB + (50 * -1), (2 * 15), (multiplier * 7) + 1, (multiplier * 4));
      xw.drawString(dist1, mainB - (multiplier * 20), levelP1);
    } else {
      xw.fillRectangle(dist1 * 6.8, mainB + (50 * -1), (2 * 15), (multiplier * 7) + 1, 8);
      xw.drawString(dist2, mainB - (multiplier * 20), levelP2);
    }
  }
  string sss1 = to_string(g1 -> getScore());
  string sss2 = to_string(g2 -> getScore());
  // update score
  if (whoNotified.pointsModified) {
    scoreP1 = "SCORE:" + gapLevel + sss1;
    scoreP2 = "SCORE:" + gapLevel + sss2;
    if (player == 1) {
      xw.fillRectangle(dist1 * 2.6, mainB - (multiplier * 15), (multiplier * 40), 15, 8);
      xw.drawString(dist1, mainB - (multiplier * 10), scoreP1);
    } else {
      xw.fillRectangle(dist1 * 6.4, mainB - 30, (multiplier * 40), 15, 8);
      xw.drawString(dist2, mainB - 20, scoreP2);
    }
  }
  // check blind
  if (whoNotified.blindOn) {
    doBlind(player);
  }
  if (whoNotified.blindOff) {
    if (player == 1) {
      undoBlind(g1);
    } else {
      undoBlind(g2);
    }
  }
  whoNotified.setFixedNext(false);
  whoNotified.setPointsModified(false);
  whoNotified.setLevelModified(false);
  whoNotified.setHiScoreModified(false);
  whoNotified.setBlindOn(false);
  whoNotified.setBlindOff(false);
}

// graphics with blind off
void GraphicsDisplay::undoBlind(Grid * b) {
  int xx = cw * 5;
  const vector < vector < Cell >> & cells = b -> getGrid();
  if (b -> getPlayer() == 2) {
    xw.fillRectangle((cw * 2) + dist2, xx + mainB, (7 * cw), (10 * cw), 9);
  } else {
    xw.fillRectangle((cw * 2) + dist1, xx + mainB, (7 * cw), (10 * cw), 9);
  }
  for (int x = 5; x <= (2 * 7); x++) {
    for (int y = 2; y <= (2 * 4); y++) {
      if (cells[x][y].isOccupied()) {
        char piece = cells[x][y].getState();
        if (b -> getPlayer() == 2) {
          xw.fillRectangle((y * cw) + dist2,(x * cw) + mainB, (cw - 0.01), (cw - 0.01), dict[piece]);
        } else {
          xw.fillRectangle((y * cw) + dist1, (x * cw) + mainB, (cw - 0.01), (cw - 0.01), dict[piece]);
        }
      }
    }
  }
}

// graphics with blind on
void GraphicsDisplay::doBlind(int player) {
  int xx = cw * 5;
  if (player == 1) {
    xw.fillRectangle((2 * cw) + dist1, xx + mainB, cw * 7, 10 * cw, 8);
  } else {
    xw.fillRectangle((2 * cw) + dist2, xx + mainB, cw * 7, 10 * cw, 8);
  }
}