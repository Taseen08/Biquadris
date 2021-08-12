#include <iostream>

#include <sstream>

#include <stdlib.h>

#include <time.h>

#include <string>

#include <termios.h>

#include <unistd.h>

#include <stdio.h>

#include <vector>

#include <memory>

#include "grid.h"

#include "manager.h"

#include "ZeroLev.h"

#include "OneLev.h"

#include "specialaction.h"

#include "jblock.h"

#include "iblock.h"

#include "lblock.h"

#include "oblock.h"

#include "sblock.h"

#include "zblock.h"

#include "tblock.h"

#include "Operations.h"

#include "blind.h"

#include "force.h"

#include "heavy.h"

#include "decorator.h"

#include "graphics.h"


Manager::Manager(Grid * theGridOne, Grid * theGridTwo, CommandManager * ComManage) {
  this -> ComManage = ComManage;
  this -> theGridOne = theGridOne;
  this -> theGridTwo = theGridTwo;

}

Manager::~Manager() {
  // delete this->ComManage;
  // delete this->theGridOne;
  // delete this->theGridTwo;
}

int Manager::play(int c, char * v[]) {

  srand(2); // should change to something else
  Operations all_operations;
  int width = 11; //main
  int height = 18; // main
  int level_initial = 0;
  int grid1_count = 1;
  int grid2_count = 1;
  int count = -1;
  int playerOne = 1;
  int playerTwo = 2;
  string L0_player1 = "sequence1.txt";
  string L0_player2 = "sequence2.txt";
  int highestScore = 0;

  // Graphics stuff
  bool graphicSwitch = true;
  int space = 8;
  int border = 5;
  int cellWidth = 22;
  int displayW = space + (border * 2) + (width * 2);
  int displayH = (border * 3) + height;

  // Command line interface functionality
  for (int i = 1; i < c; i++) { // for loop to while might be done

    string cmd = v[i];

    if (cmd == "-text") {
      graphicSwitch = false;
    } else if (c == 2) {
      cerr << "Not Enough Arguments. Expected xxx after " << cmd << endl;
      return 1;
    } else if (cmd == "-seed") {
      string xxx = v[i + 1];
      try {
        srand(stoi(xxx));
      } catch (...) {
        cerr << "ERROR! Unable to convert " << xxx << " into a seed." << endl;
        return 1;
      }
    } else if (cmd == "-scriptfile1") {
      string xxx = v[i + 1];
      ifstream test(xxx);

      // see if the file is readable or exists
      if (!test.good()) {
        cerr << "ERROR! " << xxx << " File not readable or does not exist." << endl;
        return 1;
      } else {
        L0_player1 = xxx; // file works
      }

    } else if (cmd == "-scriptfile2") {
      string xxx = v[i + 1];
      ifstream test(xxx);

      // see if the file is readable or exists
      if (!test.good()) {
        cerr << "ERROR! " << xxx << " File not readable or does not exist." << endl;
        return 1;
      } else {
        L0_player2 = xxx; // file works 
      }
    } else if (cmd == "-startlevel") {
      string xxx = v[i + 1];
      try {
        level_initial = stoi(xxx);
      } catch (...) {
        cerr << "ERROR! Unable to convert " << xxx << " into a seed." << endl;
        return 1;
      }

      //adjust the level n to the valid range 0-4
      if (level_initial < 0) {
        level_initial = 0;
        cout << "Adjusting the level n to be the lowest within range." << endl;
      }
      if (level_initial > 4) {
        level_initial = 4;
        cout << "Adjusting the level n to be the greatest within range." << endl;
      }

    }
    i++;
  }

  // Setup

  theGridOne = new Grid(width, height, level_initial, playerOne);
  shared_ptr < SpecialAction > sa1(theGridOne);
  theGridTwo = new Grid(width, height, level_initial, playerTwo);
  shared_ptr < SpecialAction > sa2(theGridTwo);
  TextDisplay td {
    width,
    height,
    theGridOne,
    theGridTwo
  };
  GraphicsDisplay * gd = nullptr;
  theGridOne -> setObserver( & td);
  theGridTwo -> setObserver( & td);
  int gridOneCurLev = level_initial;
  int gridTwoCurLev = level_initial;
  int gridOneNextLev = level_initial;
  int gridTwoNextLev = level_initial;
  int drops = 0;
  vector < string > comList;

  // documentation

  if (level_initial > 0) {
    theGridOne -> setCurrentLevel(level_initial, true);
    theGridTwo -> setCurrentLevel(level_initial, true);
  } else {
    theGridOne -> setCurrentLevel(level_initial, false, L0_player1);
    theGridTwo -> setCurrentLevel(level_initial, false, L0_player2);
  }

  // Output graphic display if the graphic is switched on
  if (graphicSwitch) {
    gd = new GraphicsDisplay(cellWidth, displayW, displayH,
      width, height, theGridOne, theGridTwo);
    theGridOne -> setObserver(gd);
    theGridTwo -> setObserver(gd);
  }

  // Create the first 4 blocks on the grid
  theGridOne -> setCurrentBlock((theGridOne -> getCurrentLevel()) -> NextBlock(0));
  theGridTwo -> setCurrentBlock((theGridTwo -> getCurrentLevel()) -> NextBlock(0));
  theGridOne -> setNextBlock((theGridOne -> getCurrentLevel()) -> NextBlock(1));
  theGridTwo -> setNextBlock((theGridTwo -> getCurrentLevel()) -> NextBlock(1));
  // Moveblocks
  all_operations.moveBlock( * theGridOne, 0, 0, 0);
  all_operations.moveBlock( * theGridTwo, 0, 0, 0);

  // Play
  while (true) {

    bool restart = false;

    if (drops == 0) {
      cout << td;
      count++;
    }

    Grid * theGrid = nullptr;
    if ((count % 2) == 0) {
      theGrid = theGridOne;
    } else {
      theGrid = theGridTwo;
    }

    while (true) {
      // multiple drops
      if (drops > 0) {
        // keep dropping consecutive blocks until 0 drops left
        while (all_operations.isValid( * theGrid, 0, 1, 0)) {
          all_operations.moveBlock( * theGrid, 0, 1, 0);
        }

        if ((count % 2) == 0) {
          theGrid -> findLyingBlock(gridOneCurLev);
        } else {
          theGrid -> findLyingBlock(gridTwoCurLev);
        }
        all_operations.removeLines( * theGrid);
        drops--;
        break;
      }

      string cmd;
      string in ;
      int mult;

      if (!comList.empty()) {
        in = comList.front();
        comList.erase(comList.begin());
      } else {
        cin >> in ;
      }

      // Use command interpreter
      cmd = ComManage -> commandDetector( in );
      mult = ComManage -> multiplier( in );

      // COMMAND FUNCTIONALITIES

      // invalid command check
      if (cmd == "error!") {
        cout << "Invalid command" << endl;
        continue;
      }

      // if multiplier is 0, do nothing except if the block is heavy
      if (mult == 0) {
        if (!theGrid -> getCurrentBlock() -> isEffectHeavy() &&
          !theGrid -> getCurrentBlock() -> isLevelHeavy()) {
          continue;
        }
      }

      // rename
      if (cmd == "rename") {
        string old;
        string replace;

        //read from comList or standard input
        if (!comList.empty()) {
          old = comList.front();
          comList.erase(comList.begin());
        } else {
          cin >> old;
        }
        if (!comList.empty()) {
          replace = comList.front();
          comList.erase(comList.begin());
        } else {
          cin >> replace;
        }

        // rename using command manager
        ComManage -> renamer(old, replace);

        cout << td;
        continue;
      }

      // left
      if (cmd == "left") {
        // move left mult times
        for (int i = 0; i < mult; i++) {
          if (all_operations.isValid( * theGrid, -1, 0, 0)) {
            all_operations.moveBlock( * theGrid, -1, 0, 0);
          } else {
            break;
          }
        }
      }

      // right
      if (cmd == "right") {
        // move right mult times 
        for (int i = 0; i < mult; i++) {
          if (all_operations.isValid( * theGrid, 1, 0, 0)) {
            all_operations.moveBlock( * theGrid, 1, 0, 0);
          } else {
            break;
          }
        }
      }

      // down
      if (cmd == "down") {
        // move down mult times 
        for (int i = 0; i < mult; i++) {
          if (all_operations.isValid( * theGrid, 0, 1, 0)) {
            all_operations.moveBlock( * theGrid, 0, 1, 0);
          } else {
            break;
          }
        }
      }

      // clockwise rotation
      if (cmd == "clockwise") {
        //rotate clockwise mult times
        for (int i = 0; i < mult; i++) {
          if (all_operations.isValid( * theGrid, 0, 0, 1)) {
            all_operations.moveBlock( * theGrid, 0, 0, 1);
          } else {
            break;
          }
        }
      }

      //counterclockwise rotation
      if (cmd == "counterclockwise") {
        //rotate counterclockwise mult times
        for (int i = 0; i < mult; i++) {
          if (all_operations.isValid( * theGrid, 0, 0, -1)) {
            all_operations.moveBlock( * theGrid, 0, 0, -1);
          } else {
            break;
          }
        }
      }

      //drop
      if (cmd == "drop") {
        // dropping logic
        while (all_operations.isValid( * theGrid, 0, 1, 0)) {
          all_operations.moveBlock( * theGrid, 0, 1, 0);
        }

        // complete lines check
        if (count % 2 == 0) {
          theGrid -> findLyingBlock(gridOneCurLev);
        } else {
          theGrid -> findLyingBlock(gridTwoCurLev);
        }
        all_operations.removeLines( * theGrid);

        // if drops > 0, keep dropping until 0
        if (mult > 1) {
          drops = mult - 1;
        }
        break;

      }

      // level down

      if (cmd == "leveldown") {
        int curr = theGrid -> getLevel();
        // level shouldnt go below 0
        if (curr != 0) {
          for (int i = 0; i < mult; i++) {
            if (curr == 0) {
              break;
            }
            curr--;
          }

          if (curr > 0) {
            theGrid -> setCurrentLevel(curr, true);
          } else {
            if (theGrid -> getPlayer() == 1) {
              theGrid -> setCurrentLevel(curr, false, L0_player1);
            } else {
              theGrid -> setCurrentLevel(curr, false, L0_player2);
            }
          }
          // adjust level
          if (count % 2 == 0) {
            gridOneCurLev = curr;
            gridOneNextLev = curr;
          } else {
            gridTwoCurLev = curr;
            gridTwoNextLev = curr;
          }
        }
        //print textdisplay and continue
        cout << td;
        continue;
      }

      // level up
      if (cmd == "levelup") {
        int curr = theGrid -> getLevel();

        /// level shouldnt exceed 4
        if (curr != 4) {
          for (int i = 0; i < mult; i++) {
            if (curr == 4) {
              break;
            }
            curr++;
          }
          theGrid -> setCurrentLevel(curr, true);

          // adjust level
          if (count % 2 == 0) {
            gridOneCurLev = curr;
            gridOneNextLev = curr;
          } else {
            gridTwoCurLev = curr;
            gridTwoNextLev = curr;
          }
        }

        //print textdisplay and continue
        cout << td;
        continue;
      }

      // random 
      if (cmd == "random") {
        int curr = theGrid -> getLevel();

        if (!(curr == 0)) {
          theGrid -> setCurrentLevel(curr, true);
        }

        //print textdisplay and continue
        cout << td;
        continue;
      }

      // no random sequence
      if (cmd == "norandom") {
        int curr = theGrid -> getLevel();

        // check if level 0
        if (!(curr == 0)) {
          string file;
          // check comList for existing filename in queue
          if (!comList.empty()) {
            file = comList.front();
            comList.erase(comList.begin());
          } else {
            cin >> file;
          }

          ifstream f(file);
          if (!f.good()) {
            cout << "File not readable or does not exist!" << endl;
          } else {
            theGrid -> setCurrentLevel(curr, false, file);
          }
        }

        // print textdisplay and continue
        cout << td;
        continue;
      }

      // sequence
      if (cmd == "sequence") {
        string file;
        string command;
        ifstream f;

        if (!comList.empty()) {
          file = comList.front();
          comList.erase(comList.begin());
        } else {
          cin >> file;
        }

        f.open(file);
        if (!f.good()) {
          cout << "File does not exist." << endl;
          continue;
        }

        while (f >> command) {
          comList.emplace_back(command);
        }
        continue;
      }

      // BLOCK COMMANDS
      if (cmd.length() == 1) {

        bool heavy = false;
        if (theGrid -> getLevel() == 3 || theGrid -> getLevel() == 4) {
          heavy = true;
        }

        Block * old = theGrid -> getCurrentBlock();
        Block * newblock = nullptr;
        if (cmd == "J") {
          newblock = new jblock {
            heavy
          };
        } else if (cmd == "T") {
          newblock = new tblock {
            heavy
          };
        } else if (cmd == "O") {
          newblock = new oblock {
            heavy
          };
        } else if (cmd == "S") {
          newblock = new sblock {
            heavy
          };
        } else if (cmd == "Z") {
          newblock = new zblock {
            heavy
          };
        } else if (cmd == "L") {
          newblock = new lblock {
            heavy
          };
        } else if (cmd == "I") {
          newblock = new iblock {
            heavy
          };
        } else {
          continue;
        }

        newblock -> setX(old -> getX());
        newblock -> setY(old -> getY());
        theGrid -> deactivateBlock();
        theGrid -> setCurrentBlock(newblock);

        if (all_operations.isValid( * theGrid, 0, 0, 0)) {
          all_operations.moveBlock( * theGrid, 0, 0, 0);
          delete old;
        } else {
          theGrid -> setCurrentBlock(old);
          all_operations.moveBlock( * theGrid, 0, 0, 0);
          delete newblock;
        }

        //print textdisplay and continue
        cout << td;
        continue;
      }

      // restart

      if (cmd == "restart") {
        restart = true;

        // reset variables
        theGridOne -> reset();
        theGridTwo -> reset();
        count = -1;
        grid1_count = 1;
        grid2_count = 1;

        theGridOne -> setCurrentBlock((theGridOne -> getCurrentLevel()) -> NextBlock(0));
        theGridTwo -> setCurrentBlock((theGridTwo -> getCurrentLevel()) -> NextBlock(0));
        theGridOne -> setNextBlock((theGridOne -> getCurrentLevel()) -> NextBlock(1));
        theGridTwo -> setNextBlock((theGridTwo -> getCurrentLevel()) -> NextBlock(1));
        all_operations.moveBlock( * theGrid, 0, 0, 0);
        all_operations.moveBlock( * theGrid, 0, 0, 0);
        break;

      }

      // endgame
      if (cmd == "quit") {
        delete gd;
        return 0;
      }

      // Level heavy (level 3 and 4)
      if (theGrid -> getCurrentBlock() -> isLevelHeavy()) {
        if (all_operations.isValid( * theGrid, 0, 1, 0)) {
          all_operations.moveBlock( * theGrid, 0, 1, 0);
        }
        if (!all_operations.isValid( * theGrid, 0, 1, 0)) {
          if (count % 2 == 0) {
            theGrid -> findLyingBlock(gridOneCurLev);
          } else {
            theGrid -> findLyingBlock(gridTwoCurLev);
          }
          all_operations.removeLines( * theGrid);
          break;
        }
      }

      // Effect heavy 
      if (theGrid -> getCurrentBlock() -> isEffectHeavy()) {
        if (cmd == "right" || cmd == "left") {
          for (int i = 0; i < 2; i++) {
            if (all_operations.isValid( * theGrid, 0, 1, 0)) {
              all_operations.moveBlock( * theGrid, 0, 1, 0);
            } else {
              break;
            }
          }
          if (!all_operations.isValid( * theGrid, 0, 1, 0)) {
            if (count % 2 == 0) {
              theGrid -> findLyingBlock(gridOneCurLev);
            } else {
              theGrid -> findLyingBlock(gridTwoCurLev);
            }
            all_operations.removeLines( * theGrid);
            break;
          }
        }
      }

      // print textdisplay after the turn
      cout << td;

    }

    int scoreP1 = theGridOne -> getScore();
    int scoreP2 = theGridTwo -> getScore();
    if (scoreP1 > highestScore || scoreP2 > highestScore) {
      if (scoreP1 >= scoreP2) {
        highestScore = scoreP1;
      } else {
        highestScore = scoreP2;
      }
      theGridOne -> setHighScore(highestScore);
      theGridTwo -> setHighScore(highestScore);
    }

    // check if restart called
    if (restart) {
      continue;
    }

    //Turn off blind effect after the player's turn
    if (theGrid -> isBlind()) {
      theGrid -> setBlind(false);
    }

    //Turn off heavy effect after the player's turn
    if (theGrid -> isHeavy()) {
      theGrid -> setHeavy(false);
    }

    //Turn off force effect after the player's turn
    if (theGrid -> isForce()) {
      theGrid -> setForce(false);
    }

    // (1,1) block check
    if (theGrid -> getLevel() == 4) {
      Block * b = theGrid -> getCurrentLevel() -> NextBlock(0);

      if (b -> whichBlock() == '*') {
        theGrid -> setCurrentBlock(b);

        //drop it
        while (all_operations.isValid( * theGrid, 0, 1, 0)) {
          all_operations.moveBlock( * theGrid, 0, 1, 0);
        }
        theGrid -> findLyingBlock(4);
        all_operations.removeLines( * theGrid);
      } else {
        delete b;
      }
    }

    // special effect called by player on opponent
    if (theGrid -> isEffect()) {
      cout << td;
      cout << "CHOOSE YOUR EFFECT ON YOUR OPPONENT: blind/heavy/force (only 1)" << endl;
      string in ;

      while (true) {
        if (!comList.empty()) {
          in = comList.front();
          comList.erase(comList.begin());
        } else {
          cin >> in ;
        }

        // blind effect 
        if ( in == "force") {
          char b;
          while (true) {
            cout << "Provide the block that you would want to force to your opponent: " << endl;
            if (!comList.empty()) {
              b = comList.front();
              comList.erase(comList.begin());
            } else {
              cin >> b;
            }
            if (b == "J" || b == "I" || b == "T" ||
              b == "S" || b == "O" || b == "Z" || b == "L") {
              break;
            }
            cout << "Not a valid block." << endl;
          }
          if (theGrid -> getPlayer() == 1) {
            theGridTwo -> setForce(true);
            sa2.reset(new Force {
              sa2,
              b
            });
            sa2 -> execute( * theGridTwo);
            if (theGridTwo -> getDead()) {
              cout << "Game over! Player 1 won!" << endl;
              if (graphicSwitch) {
                gd -> displayWinner(1);
              }
              delete gd;
              return 0;
            }
            break;
          } else {
            theGridOne -> setForce(true);
            sa1.reset(new Force {
              sa1,
              b
            });
            sa1 -> execute( * theGridOne);
            if (theGridOne -> getDead()) {
              cout << "Game over! Player 2 won!" << endl;
              if (graphicSwitch) {
                gd -> displayWinner(2);
              }
              delete gd;
              return 0;
            }
            break;
          }
        } else if ( in == "blind") {
          if (theGrid -> getPlayer() == 1) {
            theGridTwo -> setBlind(true);
            sa2.reset(new Blind {
              sa2
            });
            sa2 -> execute( * theGridTwo);
            break;
          } else {
            theGridOne -> setBlind(true);
            sa1.reset(new Blind {
              sa1
            });
            sa1 -> execute( * theGridOne);
            break;
          }
        } else if ( in == "heavy") {
          if (theGrid -> getPlayer() == 1) {
            theGridTwo -> setHeavy(true);
            sa2.reset(new Heavy {
              sa2
            });
            sa2 -> execute( * theGridTwo);
            break;
          } else {
            theGridOne -> setHeavy(true);
            sa1.reset(new Heavy {
              sa1
            });
            sa1 -> execute( * theGridOne);
            break;
          }
        } else {
          cout << in << " is not a valid special effect!" << endl;
        }
      }
      theGrid -> setEffect(false);
    }

    // Next block

    int gridcount;
    if (count % 2 == 0) {
      grid1_count++;
      gridcount = grid1_count;
    } else {
      grid2_count++;
      gridcount = grid2_count;
    }

    theGrid -> setCurrentBlock(theGrid -> getNextBlock());
    theGrid -> setNextBlock((theGrid -> getCurrentLevel()) -> NextBlock(gridcount));

    // Check if someone lost
    if (all_operations.isValid( * theGrid, 0, 0, 0)) {
      all_operations.moveBlock( * theGrid, 0, 0, 0);

      if (count % 2 == 0) { // player 1 was playing
        gridOneCurLev = gridOneNextLev;
        gridOneNextLev = theGrid -> getLevel();
      } else { // player 2 was playing
        gridTwoCurLev = gridTwoNextLev;
        gridTwoNextLev = theGrid -> getLevel();
      }
    } else {
      if (count % 2 == 0) {
        cout << "Game over! Player 2 won!" << endl;
        if (graphicSwitch) {
          gd -> displayWinner(2);
        }
        delete gd;
        return 0;
      } else {
        cout << "Game over! Player 1 won!" << endl;
        if (graphicSwitch) {
          gd -> displayWinner(1);
        }
        delete gd;
        return 0;
      }

    }
  }

}