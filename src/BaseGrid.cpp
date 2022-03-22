#include "BaseGrid.h"
#include "UserInput.h"

BaseGrid::BaseGrid() { //Default Constructor
  m_grid = NULL;
  m_height = 0;
  m_width = 0;
}

BaseGrid::BaseGrid(string in) { //Overloaded Constructor, takes inputfile name
  string line;
  string recordGrid;
  int lineCounter = 0;

  ifstream infile(in);
  if(infile.is_open()) {
    while (getline(infile, line)) {
      if(lineCounter == 0) {
        m_height = stoi(line); // gets height from text file
      } else if(lineCounter == 1) {
        m_width = stoi(line); // gets width from text file
      } else {
        recordGrid += line; // records grid into a string from the text file
      }
      lineCounter++;
    }
  }
  infile.close();

  m_grid = new char*[m_height]; // sets dimensions of the grid
  for(int i = 0; i < m_height; ++i) {
    m_grid[i] = new char[m_width];
  }

  int placeCounter = 0;
  for(int row = 0; row < m_height; ++row) {
    for(int col = 0; col < m_width; ++col) {
      m_grid[row][col] = recordGrid[placeCounter++]; // places grid from the string into the 2D array
    }
  }
}

BaseGrid::BaseGrid(int h, int w, float d, bool empty) { //Overloaded Constructor, creates empty grid or random one
  m_height = h;
  m_width = w;
  m_grid = new char*[h];
  for(int i = 0; i < h; ++i) {
    m_grid[i] = new char[w];
  }
  for(int row = 0; row < m_height; ++row) {
    for(int col = 0; col < m_width; ++col) {
      m_grid[row][col] = '-'; // fills grid with empty space
    }
  }
  if (empty) { //creates empty grid
  } else { //creates random one
    srand(time(0)); //sets random seed
    int totalSize = h*w;
    float numX = d*totalSize;
    int totalX = static_cast<int>(numX);
    cout << totalX << endl;
    int randHeight = rand() % h;
    int randRow = rand() % w;
    while (totalX != 0) {
      if(m_grid[randHeight][randRow] == 'X') {
        randHeight = rand() % h;
        randRow = rand() % w;
      } else {
        m_grid[randHeight][randRow] = 'X';
        randHeight = rand() % h;
        randRow = rand() % w;
        totalX--;
      }
    }
  }
}

BaseGrid::~BaseGrid() { //deletes grid
  for(int i = 0; i < m_height; ++i) {
    delete[] m_grid[i];
  }
  delete[] m_grid;
  cout << "Grid deleted" << endl;
}

void BaseGrid::makeGrid(string in) { // Creates grid with input file
  string line;
  string recordGrid;
  int lineCounter = 0;

  ifstream infile(in);
  if(infile.is_open()) {
    while (getline(infile, line)) {
      if(lineCounter == 0) {
        m_height = stoi(line); // gets height from text file
      } else if(lineCounter == 1) {
        m_width = stoi(line); // gets width from text file
        // cout << m_width << endl;
      } else {
        recordGrid += line; // records grid into a string from the text file
      }
      lineCounter++;
    }
  }
  infile.close();

  m_grid = new char*[m_height]; // sets dimensions of the grid
  for(int i = 0; i < m_height; ++i) {
    m_grid[i] = new char[m_width];
  }

  int placeCounter = 0;
  for(int row = 0; row < m_height; ++row) {
    for(int col = 0; col < m_width; ++col) {
      m_grid[row][col] = recordGrid[placeCounter++]; // places grid from the string into the 2D array
    }
  }
}

void BaseGrid::makeGrid(int h, int w, float d, bool empty) { // Creates empty grid or random grid
  m_height = h;
  m_width = w;
  m_grid = new char*[h];
  for(int i = 0; i < h; ++i) {
    m_grid[i] = new char[w];
  }
  for(int row = 0; row < m_height; ++row) {
    for(int col = 0; col < m_width; ++col) {
      m_grid[row][col] = '-'; // fills grid with empty space
    }
  }
  if (empty) {
  } else {
    srand(time(0));
    int totalSize = h*w;
    float numX = d*totalSize;
    int totalX = static_cast<int>(numX);
    cout << totalX << endl;
    int randHeight = rand() % h;
    int randRow = rand() % w;
    while (totalX != 0) {
      if(m_grid[randHeight][randRow] == 'X') {
        randHeight = rand() % h;
        randRow = rand() % w;
      } else {
        m_grid[randHeight][randRow] = 'X';
        randHeight = rand() % h;
        randRow = rand() % w;
        totalX--;
      }
    }
  }
}

BaseGrid::BaseGrid(const BaseGrid &g1) { //Copy constructor
  m_height = g1.m_height;
  m_width = g1.m_width;

  if (g1.m_grid) {
    m_grid = new char*[m_height];
    for(int i = 0; i < m_height; ++i)
      m_grid[i] = new char[m_width];
    for(int row = 0; row < m_height; ++row) {
      for(int col = 0; col < m_width; ++col) {
        m_grid[row][col] = g1.m_grid[row][col];
      }
    }
  }
}

int BaseGrid::numNeighborsClassic(int h, int w) { //Determines numbers of neighbors for classic mode
  int countNeighbors = 0;
  if (h == 0 && w == 0) { // checks top left corner
    if (m_grid[0][1] == 'X')
      countNeighbors++;
    if (m_grid[1][0] == 'X')
      countNeighbors++;
    if (m_grid[1][1] == 'X')
      countNeighbors++;
  } else if (h == 0 && w == m_width-1) { // checks top right corner
    if (m_grid[0][w-1] == 'X')
      countNeighbors++;
    if (m_grid[1][w] == 'X')
      countNeighbors++;
    if (m_grid[1][w-1] == 'X')
      countNeighbors++;
  } else if (h == m_height-1 && w == 0) { // checks bottom left corner
    if (m_grid[h-1][0] == 'X')
      countNeighbors++;
    if (m_grid[h][1] == 'X')
      countNeighbors++;
    if (m_grid[h-1][1] == 'X')
      countNeighbors++;
  } else if (h == m_height-1 && w == m_width-1) { // checks bottom right corner
    if (m_grid[h][w-1] == 'X')
      countNeighbors++;
    if (m_grid[h-1][w] == 'X')
      countNeighbors++;
    if (m_grid[h-1][w-1] == 'X')
      countNeighbors++;
    } else if (h == 0) { //checks top edge
      if (m_grid[h][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h][w+1] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w+1] == 'X')
        countNeighbors++;
    } else if (h == m_height-1) { //check bottom edge
      if (m_grid[h][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h][w+1] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w+1] == 'X')
        countNeighbors++;
    } else if (w == 0) { //checks left edge
      if (m_grid[h-1][w] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w+1] == 'X')
        countNeighbors++;
      if (m_grid[h][w+1] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w+1] == 'X')
        countNeighbors++;
    } else if (w == m_width-1) { //checks right edge
      if (m_grid[h-1][w] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w-1] == 'X')
        countNeighbors++;
    } else { // checks middle
      if (m_grid[h-1][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w] == 'X')
        countNeighbors++;
      if (m_grid[h-1][w+1] == 'X')
        countNeighbors++;
      if (m_grid[h][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h][w+1] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w-1] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w] == 'X')
        countNeighbors++;
      if (m_grid[h+1][w+1] == 'X')
        countNeighbors++;
    }
    return countNeighbors;
}

int BaseGrid::numNeighborsDonut(int h, int w) { //Determines numbers of neighbors for donut mode
  int countNeighbors = numNeighborsClassic(h, w);
  if (h == 0 && w == 0) { // checks top left corner
    if (m_grid[0][m_width-1] == 'X')
      countNeighbors++;
    if (m_grid[1][m_width-1] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][0] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][1] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][m_width-1] == 'X')
      countNeighbors++;
  } else if (h == 0 && w == m_width-1) { // checks top right corner
    if (m_grid[0][0] == 'X')
      countNeighbors++;
    if (m_grid[1][0] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][w] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][w-1] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][0] == 'X')
      countNeighbors++;
  } else if (h == m_height-1 && w == 0) { // checks bottom left corner
    if (m_grid[h][m_width-1] == 'X')
      countNeighbors++;
    if (m_grid[h-1][m_width-1] == 'X')
      countNeighbors++;
    if (m_grid[0][0] == 'X')
      countNeighbors++;
    if (m_grid[0][1] == 'X')
      countNeighbors++;
    if (m_grid[0][m_width-1] == 'X')
      countNeighbors++;
  } else if (h == m_height-1 && w == m_width-1) { // checks bottom right corner
    if (m_grid[0][0] == 'X')
      countNeighbors++;
    if (m_grid[0][w] == 'X')
      countNeighbors++;
    if (m_grid[0][w-1] == 'X')
      countNeighbors++;
    if (m_grid[h][0] == 'X')
      countNeighbors++;
    if (m_grid[h-1][0] == 'X')
      countNeighbors++;
  } else if (h == 0) { //checks top edge
    if (m_grid[m_height-1][w] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][w+1] == 'X')
      countNeighbors++;
    if (m_grid[m_height-1][w-1] == 'X')
      countNeighbors++;
  } else if (h == m_height-1) { //check bottom edge
    if (m_grid[0][w-1] == 'X')
      countNeighbors++;
    if (m_grid[0][w] == 'X')
      countNeighbors++;
    if (m_grid[0][w+1] == 'X')
      countNeighbors++;
  } else if (w == 0) { //checks left edge
    if (m_grid[h-1][m_width - 1] == 'X')
      countNeighbors++;
    if (m_grid[h][m_width - 1] == 'X')
      countNeighbors++;
    if (m_grid[h+1][m_width - 1] == 'X')
      countNeighbors++;
  } else if (w == m_width-1) { //checks right edge
    if (m_grid[h-1][0] == 'X')
      countNeighbors++;
    if (m_grid[h][0] == 'X')
      countNeighbors++;
    if (m_grid[h+1][0] == 'X')
      countNeighbors++;
  }

  return countNeighbors;
}

int BaseGrid::numNeighborsMirror(int h, int w) { //Determines numbers of neighbors for mirror mode
  int countNeighbors = numNeighborsClassic(h, w);

  if (h == 0 && w == 0) { // checks top left corner
    if (m_grid[0][0] == 'X')
      countNeighbors += 3;
    if (m_grid[0][1] == 'X')
      countNeighbors++;
    if (m_grid[1][0] == 'X')
      countNeighbors++;
  } else if (h == 0 && w == m_width-1) { // checks top right corner
    if (m_grid[0][w] == 'X')
      countNeighbors += 3;
    if (m_grid[0][w-1] == 'X')
      countNeighbors++;
    if (m_grid[1][w] == 'X')
      countNeighbors++;
  } else if (h == m_height-1 && w == 0) { // checks bottom left corner
    if (m_grid[h][0] == 'X')
      countNeighbors += 3;
    if (m_grid[h-1][0] == 'X')
      countNeighbors++;
    if (m_grid[h][1] == 'X')
      countNeighbors++;
  } else if (h == m_height-1 && w == m_width-1) { // checks bottom right corner
    if (m_grid[h][w] == 'X')
      countNeighbors += 3;
    if (m_grid[h-1][w] == 'X')
      countNeighbors++;
    if (m_grid[h][w-1] == 'X')
      countNeighbors++;
  } else if (h == 0) { //checks top edge
    if (m_grid[h][w] == 'X')
      countNeighbors++;
    if (m_grid[h][w-1] == 'X')
      countNeighbors++;
    if (m_grid[h][w+1] == 'X')
      countNeighbors++;
  } else if (h == m_height-1) { //check bottom edge
    if (m_grid[h][w] == 'X')
      countNeighbors++;
    if (m_grid[h][w+1] == 'X')
      countNeighbors++;
    if (m_grid[h][w-1] == 'X')
      countNeighbors++;
  } else if (w == 0) { //checks left edge
    if (m_grid[h][w] == 'X')
      countNeighbors++;
    if (m_grid[h-1][w] == 'X')
      countNeighbors++;
    if (m_grid[h+1][w] == 'X')
      countNeighbors++;
  } else if (w == m_width-1) { //checks right edge
    if (m_grid[h][w] == 'X')
      countNeighbors++;
    if (m_grid[h-1][w] == 'X')
      countNeighbors++;
    if (m_grid[h+1][w] == 'X')
      countNeighbors++;
  }

  return countNeighbors;
}

void BaseGrid::printGrid() { //prints grid
  for(int i = 0; i < m_height; ++i) {
    for(int j = 0; j < m_width; ++j) {
      cout << m_grid[i][j] << ' ';
    }
    cout << endl;
  }
}

string BaseGrid::toString() { //converts grid to string
  string str;
  for(int i = 0; i < m_height; ++i) {
    for(int j = 0; j < m_width; ++j) {
      str += m_grid[i][j];
    }
    str += "\n";
  }
  return str;
}

bool BaseGrid::isEmpty() { //determines if grid is empty
  for(int i = 0; i < m_height; ++i) {
    for(int j = 0; j < m_width; ++j) {
      if (m_grid[i][j] == 'X')
        return false;
    }
  }
  return true;
}

void BaseGrid::setGrid(int h, int w, char c) { //sets grid to x or -
  m_grid[h][w] = c;
}

char BaseGrid::getGridAt(int h, int w) { //accessor
  return m_grid[h][w];
}

int BaseGrid::getHeight() { //accessor
  return m_height;
}

int BaseGrid::getWidth() { //accessor
  return m_width;
}

void BaseGrid::gridClear() { //clears grid
  for(int row = 0; row < m_height; ++row) {
    for(int col = 0; col < m_width; ++col) {
      m_grid[row][col] = '-'; // fills grid with empty space
    }
  }
}
