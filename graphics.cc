#include <iostream>

#include <vector>

#include <string>

#include "subject.h"

#include "observer.h"

#include "window.h"

#include "graphics.h"

#include "grid.h"

#include <map>

#include <string>

using namespace std;

// map of block and corresponding color
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

//initializes the background of the board
void GraphicsDisplay::init() {
  highscore = "HIGH SCORE:" + gapHS + to_string(g1 -> getHighScore());
  // levels
  levelP1 = "LEVEL:" + gapLevel + to_string(g1 -> getLevel());
  levelP2 = "LEVEL:" + gapLevel + to_string(g2 -> getLevel());
  xw.drawString((ww - (cw * 8)) / 2, (cw * 7) - 80, highscore);
  xw.drawString((cw * 5), (cw * 7) - 40, levelP1);
  xw.drawString((cw * 5), (cw * 7) - 20, "SCORE:" + gapLevel + "0");
  xw.drawString(((cw * 5) + gw + (cw * 8)), (cw * 7) - 40, levelP2);
  xw.drawString(((cw * 5) + gw + (cw * 8)), (cw * 7) - 20, "SCORE:" + gapLevel + "0");
  // backgrounds
  xw.fillRectangle((cw * 5), (cw * 7), gw - 0.01, gh - 0.01, 9);
  xw.fillRectangle(((cw * 5) + gw + (cw * 8)), (cw * 7), gw - 0.01, gh - 0.01, 9);
  // next block
  xw.drawString((cw * 5), wh - (cw * 7) + 10, "NEXT BLOCK:");
  xw.drawString(((cw * 5) + gw + (cw * 8)), wh - (cw * 7) + 10, "NEXT BLOCK:");
}

void GraphicsDisplay::notify(Cell & whoNotified) {
  int x = whoNotified.getX();
  int y = whoNotified.getY();
  char state = whoNotified.getState();
  int player = whoNotified.getGrid() -> getPlayer();
  // not occupied logic
  if (!whoNotified.isOccupied()) {
    if (player == 1) xw.fillRectangle((y * cw) + (cw * 5),
      (x * cw) + (cw * 7), (cw - 0.01), (cw - 0.01), 8);
    else xw.fillRectangle((y * cw) + ((cw * 5) + gw + (cw * 8)),
      (x * cw) + (cw * 7), (cw - 0.01), (cw - 0.01), 8);

  } else {
    if (player == 1) xw.fillRectangle((y * cw) + (cw * 5),
      (x * cw) + (cw * 7), (cw - 0.01), (cw - 0.01), dict[state]);
    else xw.fillRectangle((y * cw) + ((cw * 5) + gw + (cw * 8)),
      (x * cw) + (cw * 7), (cw - 0.01), (cw - 0.01), dict[state]);
  }
  if (whoNotified.getGrid() -> isBlind()) {
    doBlind(player);
  }
}

// notify grid
void GraphicsDisplay::notify(Grid & whoNotified) {
  // get corresponding index from dict
  int player = whoNotified.getPlayer();
  vector < int > shape = whoNotified.getNextBlock() -> getShape();
  char state = whoNotified.getNextBlock() -> whichBlock();
  // clear and prepare next
  if (whoNotified.fixedNext) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 1; j++) {
        if (player == 1) {
          xw.fillRectangle((i * cw) + (cw * 5),
            (j * cw) + (wh - (cw * 7) + 30), cw + 1, cw + 1, 8);
        } else {
          xw.fillRectangle((i * cw) + ((cw * 5) + gw + (cw * 8)),
            (j * cw) + (wh - (cw * 7) + 30), cw + 1, cw + 1, 8);
        }
      }
    }
    for (int i = 0; i <= shape.size() - 1; i++) {
      int lim = 3;
      if (shape[i] <= lim) {
        if (player == 1) {
          xw.fillRectangle((shape[i] * cw) + (cw * 5),
            (0 * cw) + (wh - (cw * 7) + 30), cw + 1, cw + 1, 9);
          xw.fillRectangle((shape[i] * cw) + (cw * 5) + 0.005,
            (0 * cw) + (wh - (cw * 7) + 30) + 0.005, (cw - 0.01), (cw - 0.01), dict[state]);
        } else {
          xw.fillRectangle((shape[i] * cw) + ((cw * 5) + gw + (cw * 8)),
            (0 * cw) + (wh - (cw * 7) + 30), cw + 1, cw + 1, 9);
          xw.fillRectangle((shape[i] * cw) + ((cw * 5) + gw + (cw * 8)) + 0.005,
            (0 * cw) + (wh - (cw * 7) + 30) + 0.005, (cw - 0.01), (cw - 0.01), dict[state]);
        }

      } else {
        if (player == 1) {
          xw.fillRectangle((shape[i] % 4) * cw + (cw * 5),
            (1 * cw) + (wh - (cw * 7) + 30), cw + 1, cw + 1, 9);
          xw.fillRectangle((shape[i] % 4) * cw + (cw * 5) + 0.005,
            (1 * cw) + (wh - (cw * 7) + 30) + 0.005, (cw - 0.01), (cw - 0.01), dict[state]);
        } else {
          xw.fillRectangle((shape[i] % 4) * cw + ((cw * 5) + gw + (cw * 8)),
            (1 * cw) + (wh - (cw * 7) + 30), cw + 1, cw + 1, 9);
          xw.fillRectangle((shape[i] % 4) * cw + ((cw * 5) + gw + (cw * 8)) + 0.005,
            (1 * cw) + (wh - (cw * 7) + 30) + 0.005, (cw - 0.01), (cw - 0.01), dict[state]);
        }
      }
    }
  }
  //if the high score has been changed, update it on the display
  if (whoNotified.hiScoreModified) {
    string gapHS;
    string highscore;
    for (int i = 0; i <= 15; i++) {
      gapHS += " ";
    }
    // update high score
    highscore = "HIGH SCORE:" + gapHS + to_string(g1 -> getHighScore());
    xw.fillRectangle((cw * 5) * 4.3, (cw * 7) - 90, 80, 15, 8);
    xw.drawString((ww - (cw * 8)) / 2, (cw * 7) - 80, highscore);
  }
  // update level
  if (whoNotified.levelModified) {
    levelP1 = "LEVEL:" + gapLevel + to_string(g1 -> getLevel());
    levelP2 = "LEVEL:" + gapLevel + to_string(g2 -> getLevel());
    if (player == 1) {
      xw.fillRectangle((cw * 5) * 3, (cw * 7) - 50, 30, 15, 8);
      xw.drawString((cw * 5), (cw * 7) - 40, levelP1);
    } else {
      xw.fillRectangle((cw * 5) * 6.8, (cw * 7) - 50, 30, 15, 8);
      xw.drawString(((cw * 5) + gw + (cw * 8)), (cw * 7) - 40, levelP2);
    }
  }
  // update score
  if (whoNotified.pointsModified) {
    scoreP1 = "SCORE:" + gapLevel + to_string(g1 -> getScore());
    scoreP2 = "SCORE:" + gapLevel + to_string(g2 -> getScore());
    if (player == 1) {
      xw.fillRectangle((cw * 5) * 2.6, (cw * 7) - 30, 80, 15, 8);
      xw.drawString((cw * 5), (cw * 7) - 20, scoreP1);
    } else {
      xw.fillRectangle((cw * 5) * 6.4, (cw * 7) - 30, 80, 15, 8);
      xw.drawString(((cw * 5) + gw + (cw * 8)), (cw * 7) - 20, scoreP2);
    }
  }
  // check blind
  if (whoNotified.blindOff) {
    if (player == 1) undoBlind(g1);
    else undoBlind(g2);
  }

  if (whoNotified.blindOn) {
    doBlind(player);
  }
  // last reset
  whoNotified.setFixedNext(false);
  whoNotified.setPointsModified(false);
  whoNotified.setLevelModified(false);
  whoNotified.setHiScoreModified(false);
  whoNotified.setBlindOn(false);
  whoNotified.setBlindOff(false);
}

// graphics with blind on
void GraphicsDisplay::doBlind(int player) {
  if (player == 1) {
    xw.fillRectangle((2 * cw) + (cw * 5),
      (5 * cw) + (cw * 7), 7 * cw, 10 * cw, 8);
  } else {
    xw.fillRectangle((2 * cw) + ((cw * 5) + gw + (cw * 8)),
      (5 * cw) + (cw * 7), 7 * cw, 10 * cw, 8);
  }
}

// graphics with blind off
void GraphicsDisplay::undoBlind(Grid * b) {
  const vector < vector < Cell >> & cells = b -> getGrid();
  if (b -> getPlayer() == 1) {
    xw.fillRectangle((2 * cw) + (cw * 5),
      (5 * cw) + (cw * 7), 7 * cw, 10 * cw, 9);
  } else {
    xw.fillRectangle((2 * cw) + ((cw * 5) + gw + (cw * 8)),
      (5 * cw) + (cw * 7), 7 * cw, 10 * cw, 9);
  }
  for (int x = 5; x <= 14; x++) {
    for (int y = (1 + 1); y <= 8; y++) {
      if (cells[x][y].isOccupied()) {
        char state = cells[x][y].getState();
        if (b -> getPlayer() == 1) {
          xw.fillRectangle((y * cw) + (cw * 5),
            (x * cw) + (cw * 7), (cw - 0.01), (cw - 0.01), dict[state]);
        } else {
          xw.fillRectangle((y * cw) + ((cw * 5) + gw + (cw * 8)),
            (x * cw) + (cw * 7), (cw - 0.01), (cw - 0.01), dict[state]);
        }
      }
    }
  }
}

// win message
void GraphicsDisplay::winnerWho(int player) {
  if (player == 1) {
    xw.drawString((ww / 2) - 45, (wh / 2), "Player One is the Winner!");
  } else {
    xw.drawString((ww / 2) - 45, (wh / 2), "Player Two is the Winner!");
  }
}

GraphicsDisplay::~GraphicsDisplay() {}