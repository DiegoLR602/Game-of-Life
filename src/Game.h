#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "BaseGrid.h"
#include "UserInput.h"

using namespace std;

class Game {
public:
  Game();
  virtual ~Game();
  int playGame();

private:
  unsigned int m_generations;
  string m_fName;
  int m_next = 0;
  bool outputMode(BaseGrid *grid1, BaseGrid *grid2, UserInput in);
};

#endif
