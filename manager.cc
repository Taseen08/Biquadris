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
#include "manager.h"
#include "ZeroLev.h"
#include "OneLev.h"


Manager::Manager(Grid *theGrid, CommandManager *ComManage, TextDisplay * theTextDisplay){
    this->ComManage = ComManage;
    this->theGrid = theGrid;
    this->theTextDisplay = theTextDisplay;
}

