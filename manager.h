#ifndef _MANAGER_H
#define _MANAGER_H
// #include <iostream>
// #include <sstream>
// #include <stdlib.h>
// #include <time.h>
// #include <string>
// #include <vector>
// #include <memory>
#include "grid.h"
#include "block.h"
#include "textdisplay.h"
#include "commandmanager.h"
#include "Level.h"

class Manager{
    Grid *theGrid;
    CommandManager *ComManage;
    TextDisplay * theTextDisplay;
    public:
        Manager(Grid *theGrid, CommandManager *ComManage, TextDisplay * theTextDisplay);
        void play(int argc, char * argv[]);

};

#endif