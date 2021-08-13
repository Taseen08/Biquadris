#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <X11/Xlib.h>

#include <string>

#include <iostream>

class Xwindow {
  Display * d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

  public:
    Xwindow(int width = 700, int height = 600); // xwindow constructor for displaying window
  ~Xwindow(); // xwindow destructor
  Xwindow(const Xwindow & ) = delete;
  Xwindow & operator = (const Xwindow & ) = delete;

  enum {
    White = 0, Black, Red, Green, Blue
  }; // Available colours.

  // Draws rectangle
  void fillRectangle(int x, int y, int width, int height, int colour = Black);

  // Draws string
  void drawString(int x, int y, std::string msg);

};

#endif