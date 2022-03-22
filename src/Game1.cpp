#include "Game.h"
#include "BaseGrid.h"
#include "UserInput.h"

Game::Game() { //default constructor
  m_generations = 1;
}

Game::~Game() {} //deletes game

int Game::playGame() { // plays game
  UserInput in; // retrieves user's inputs
  BaseGrid *grid1 = new BaseGrid();
  m_fName = "none";
  if (in.getChoice() == 1) { // sets grid to user specified file in.getChoice() == 1
    grid1->makeGrid(in.getFilePath()); // changed
  } else if (in.getChoice() == 2) { // sets grid randomly with user's desired height and width
    grid1->makeGrid(in.getHeight(), in.getWidth(), in.getDensity(), false); // changed
  }
  grid1->printGrid(); // changed
  int h = grid1->getHeight(); // changed
  int w = grid1->getWidth(); // changed
  BaseGrid *grid2 = new BaseGrid(h, w, 0.0, true);
  int mode = in.chooseMode();
  m_next = in.chooseNext();

  if (mode == 1) { //plays game if mode is classic
    while(!grid1->isEmpty()) { // changed
      grid2->gridClear();

      for(int row = 0; row < h; ++row) {
        for(int col = 0; col < w; ++col) {
          if (grid1->numNeighborsClassic(row, col) <= 1) { // changed
            grid2->setGrid(row, col, '-');
          } else if (grid1->numNeighborsClassic(row, col) == 2) { // changed
            grid2->setGrid(row, col, grid1->getGridAt(row, col)); // changed
          } else if (grid1->numNeighborsClassic(row, col) == 3) { // changed
            grid2->setGrid(row, col, 'X');
          } else if (grid1->numNeighborsClassic(row, col) >= 4) { // changed
            grid2->setGrid(row, col, '-');
          }
        }
      }

      if (outputMode(grid1, grid2, in)) {
        break;
      }
    }
  } else if (mode == 2) { //plays game if mode is donut
    while(!grid1->isEmpty()) { // changed
      grid2->gridClear();
      for(int row = 0; row < h; ++row) {
        for(int col = 0; col < w; ++col) {
          if (grid1->numNeighborsDonut(row, col) <= 1) { // changed
            grid2->setGrid(row, col, '-');
          } else if (grid1->numNeighborsDonut(row, col) == 2) { // changed
            grid2->setGrid(row, col, grid1->getGridAt(row, col)); // changed
          } else if (grid1->numNeighborsDonut(row, col) == 3) { // changed
            grid2->setGrid(row, col, 'X');
          } else if (grid1->numNeighborsDonut(row, col) >= 4) { // changed
            grid2->setGrid(row, col, '-');
          }
        }
      }

      if (outputMode(grid1, grid2, in)) {
        break;
      }
    }
  } else if (mode == 3) { //plays game if mode is mirror
    while(!grid1->isEmpty()) { // changed
      grid2->gridClear();

      for(int row = 0; row < h; ++row) {
        for(int col = 0; col < w; ++col) {
          if (grid1->numNeighborsMirror(row, col) <= 1) { // changed
            grid2->setGrid(row, col, '-');
          } else if (grid1->numNeighborsMirror(row, col) == 2) { // changed
            grid2->setGrid(row, col, grid1->getGridAt(row, col)); // changed
          } else if (grid1->numNeighborsMirror(row, col) == 3) { // changed
            grid2->setGrid(row, col, 'X');
          } else if (grid1->numNeighborsMirror(row, col) >= 4) { // changed
            grid2->setGrid(row, col, '-');
          }
        }
      }

      if (outputMode(grid1, grid2, in)) {
        break;
      }
    }
  }

  while (true) {
    cin.ignore();
    cout << "Simulation ended. Press the enter key to exit. " << endl;
    if (cin.get() == '\n')
      break;
  }
  delete grid1;
  delete grid2;
  return m_generations;
}

bool Game::outputMode(BaseGrid* grid1, BaseGrid* grid2, UserInput in) { //determines output mode
  bool isSame = true;
  for(int row = 0; row < grid1->getHeight(); ++row) {
    for(int col = 0; col < grid1->getWidth(); ++col) {
      if (grid1->getGridAt(row, col) != grid2->getGridAt(row, col)) {
        isSame = false;
        break;
      }
    }
    if (!isSame)
      break;
  }

  if (!isSame) {
    if(m_next != 3) {
      m_generations++;
      for(int row = 0; row < grid1->getHeight(); ++row) {
        for(int col = 0; col < grid1->getWidth(); ++col) {
          grid1->setGrid(row, col, grid2->getGridAt(row, col));
        }
      }
      if (m_next == 1) { //for a brief pause
        string n;
        cout << m_generations << endl;
        grid2->printGrid();
        cout << "Simulation paused. Press any key then enter to continue: ";
        cin >> n;
        cout << "Simulation resumed." << endl;
      } else if (m_next == 2) { // for enter to continue
        while (true) {
          cout << m_generations << endl;
          grid2->printGrid();
          cout << "Press enter to continue." << endl;
          if (cin.get() == '\n')
            break;
        }
      }
    } else { //for outputting to file
      ofstream outFile;
      if(m_fName == "none") {
        cout << "Enter an output file or file path: " << endl;
        cin >> m_fName;
        outFile.open(m_fName);
        outFile << "0" << endl;
        outFile << grid1->toString();
        outFile << "generation " << m_generations++ << endl;
        outFile << grid1->toString();
        for(int row = 0; row < grid1->getHeight(); ++row) {
          for(int col = 0; col < grid1->getWidth(); ++col) {
            grid1->setGrid(row, col, grid2->getGridAt(row, col));
          }
        }
        outFile << "generation " << m_generations << endl;
        outFile << grid2->toString();
        outFile.close();
      } else {
        m_generations++;
        for(int row = 0; row < grid1->getHeight(); ++row) {
          for(int col = 0; col < grid1->getWidth(); ++col) {
            grid1->setGrid(row, col, grid2->getGridAt(row, col));
          }
        }
        outFile.open(m_fName, ofstream::app);
        outFile << "generation " << m_generations << endl;
        outFile << grid2->toString();
        outFile.close();
      }
    }
    return false;
  }
  return true;
}
