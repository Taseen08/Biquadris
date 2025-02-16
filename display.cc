#include <X11/Xlib.h>

#include <X11/Xutil.h>

#include <iostream>

#include <cstdlib>

#include <string>

#include <unistd.h>

#include "display.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }

  s = DefaultScreen(d);
  w = XCreateSimpleWindow(
    d, RootWindow(d, s), 10, 10, width, height,
    1, BlackPixel(d, s), WhitePixel(d, s)
  );

  XSelectInput(d, w, ExposureMask | KeyPressMask);

  Pixmap pix = XCreatePixmap(
    d, w, width, height,
    DefaultDepth(d, DefaultScreen(d))
  );

  gc = XCreateGC(d, pix, 0, 0);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10] = {
    "magenta",
    "blue",
    "cyan",
    "yellow",
    "purple",
    "red",
    "green",
    "brown",
    "white",
    "grey"
  };

  cmap = DefaultColormap(d, DefaultScreen(d));

  for (unsigned int i = 0; i < 10; ++i) {
    XParseColor(d, cmap, color_vals[i], & xcolour);
    XAllocColor(d, cmap, & xcolour);
    colours[i] = xcolour.pixel;
  }

  XSetForeground(d, gc, colours[Black]);
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, & hints);
  XMapRaised(d, w);
  XFlush(d);
  sleep((2 - 0.75));
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  XFlush(d);
} 

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XFlush(d);
}

 
Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}



