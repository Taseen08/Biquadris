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


Manager::Manager(Grid *theGridOne, Grid *theGridTwo, CommandManager *ComManage, TextDisplay * theTextDisplay){
    this->ComManage = ComManage;
    this->theGridOne = theGridOne;
    this->theGridTwo = theGridTwo;
    this->td = theTextDisplay;
}


int Manager::play(int c, char * v[]) {

    srand(2);  // should change to something else

    size_t width = 11; //main
    size_t height = 18;  // main
    size_t level_initial = 0;
    size_t grid1_count = 1;
    size_t grid2_count = 1;
    int count = -1;
    size_t playerOne = 1;
    size_t playerTwo = 2;
    string L0_player1 = "sequence1.txt";
	string L0_player2 = "sequence2.txt";


    // Graphics stuff
    bool graphicSwitch = true;

    // Command line interface functionality
    for (int i = 1; i < c; i++) {  // for loop to while might be done

        string cmd = v[i];

        if (cmd == "-text") {
            graphicSwitch = true;
        } else if (c == 2) {
            cerr << "Not Enough Arguments. Expected xxx after " << cmd << endl;
            return 1;
        } else if (cmd == "-seed") {
            string xxx = v[i+1];
            try {
					srand(stoi(xxx));
            } 
            catch(...) {
					cerr << "ERROR! Unable to convert " << xxx << " into a seed." << endl;
					return 1;
            }
        } else if (cmd == "-scriptfile1") {
            string xxx = v[i+1];
            ifstream test(xxx);

            // see if the file is readable or exists
            if (!test.good()) {
                cerr << "ERROR! " << xxx << " File not readable or does not exist." << endl;
                return 1;
            } else {
                L0_player1 = xxx; // file works
            }

        } else if (cmd == "-scriptfile2") {
            string xxx = v[i+1];
            ifstream test(xxx);

            // see if the file is readable or exists
            if (!test.good()) {
                cerr << "ERROR! " << xxx << " File not readable or does not exist." << endl;
                return 1;
            } else {
                L0_player2 = xxx; // file works 
            }
        } else if (cmd == "-startlevel") {
                string xxx = v[i+1];
				try {
                    level_initial = stoi(xxx);
				}
				catch(...) {
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
    // shared_ptr<SpecialAction> sa1( theGridOne );  for decorator
    theGridTwo = new Grid(width, height, level_initial, playerTwo);
    //shared_ptr<SpecialAction> sa2( theGridTwo );
    TextDisplay td1{width,height,theGridOne,theGridTwo};
    // graphicsdisplay
    theGridOne->setObserver(&td1);
    theGridTwo->setObserver(&td1);
    







}

