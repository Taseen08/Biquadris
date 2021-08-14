#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "subject.h"

#include "observer.h"

#include "display.h"

#include <string>

using namespace std;

class GraphicsDisplay: public Observer {
  int cw; // cell width
  int ww;
  int wh;
  int gw; // grid width
  int gh; // grid height
  Grid * g1;
  Grid * g2;
  Xwindow xw;
  int dist1;
  int dist2;
  int mainB;
  int gridGap;

  public:
    GraphicsDisplay(int cw, int ww, int wh, int gw, int gh, Grid * g1, Grid * g2);
  void init();
    void undoBlind(Grid * b);
  void winnerWho(int player);
  ~GraphicsDisplay();
  void notify(Cell & whoNotified) override;
  void notify(Grid & whoNotified) override;
  void doBlind(int player);
};

#endif
