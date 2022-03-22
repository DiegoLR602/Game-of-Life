#ifndef BASEGRID_H
#define BASEGRID_H
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <exception>
#include <cstdlib>
#include <time.h>

using namespace std;

class BaseGrid {
private:
  char **m_grid;
  int m_height;
  int m_width;
public:
  BaseGrid();
  BaseGrid(string in);
  BaseGrid(int h, int w, float d, bool empty); //finish
  void makeGrid(string in);
  void makeGrid(int h, int w, float d, bool empty);
  BaseGrid(const BaseGrid &g1);
  virtual ~BaseGrid();
  int numNeighborsClassic(int h, int w);
  int numNeighborsDonut(int h, int w);
  int numNeighborsMirror(int h, int w);
  bool isEmpty();
  void setGrid(int h, int w, char c);
  char getGridAt(int h, int w);
  int getHeight();
  int getWidth();
  void printGrid();
  string toString();
  void gridClear();
};

#endif
