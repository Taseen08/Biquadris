#include <iostream>

#include "observer.h"

#include "subject.h"

#include "cell.h"

Cell::Cell(int x, int y, Grid * mainBoard, bool occupied, char state) {
  this -> x = x;
  this -> y = y;
  this -> occupied = occupied;
  this -> state = state;
  this -> mainBoard = mainBoard;
}

void Cell::notifyObservers() {
  // for (auto &o:observers) o->notify(*this);

  for (int i = 0; i < this -> observers.size(); ++i) {
    this -> observers[i] -> notify( * this);
  }
}

int Cell::getX() {
  return this -> x;
}

int Cell::getY() {
  return this -> y;
}

void Cell::setX(int x) {
  this -> x = x;
}

void Cell::setY(int y) {
  this -> y = y;
}

bool Cell::isOccupied() const {
  return this -> occupied;
}

char Cell::getState() const {
  return this -> state;
}

void Cell::setState(char myState) {
  this -> state = myState;
  this -> occupied = true;
  this -> notifyObservers(); // maybe call it after the function 
}

void Cell::unsetState() {
  this -> state = ' ';
  this -> occupied = false;
  this -> notifyObservers();
}
Grid * Cell::getGrid() {
  return this -> mainBoard;
}