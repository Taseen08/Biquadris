#ifndef _MANAGER_H
#define _MANAGER_H
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include "Level.h"
#include "OneLev.h"
#include "grid.h"
#include "block.h"
#include "textdisplay.h"
#include "commandmanager.h"
#include "Level.h"

class Manager{
    Grid *theGridOne;
    Grid *theGridTwo;
    CommandManager *ComManage;
    
    public:
        Manager(Grid *theGridOne, Grid *theGridTwo, CommandManager *ComManage);
        int play(int c, char * v[]);
        ~Manager();
        

};

#endif