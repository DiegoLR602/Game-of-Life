#include "UserInput.h"

UserInput::UserInput() { //takes input and sets memvars
  m_choice = 0;
  m_density = -1;
  while(m_choice != 1 && m_choice != 2) {
    cout << "Enter 1 for a map file and 2 for a random assignment: " << endl;
    cin >> m_choice;
    if (m_choice == 1) {
      cout << "Enter a file or file path: " << endl;
      cin >> m_filePath;
      break;
    } else if (m_choice == 2) {
      cout << "Enter the height of the grid: " << endl;
      cin >> m_height;
      cout << "Enter the width of the grid: " << endl;
      cin >> m_width;
      while (!(m_density > 0 && m_density <= 1)) {
        cout << "Enter the density of the grid, greater than 0 and less than or equal to 1: " << endl;
        cin >> m_density;
      }
      break;
    } else {
      cout << "Please enter a valid input." << endl;
    }
  }
}

UserInput::~UserInput(){}

int UserInput::chooseMode() { // chooses what mode to run in
  m_modeChoice = 0;
  while(m_modeChoice != 1 || m_modeChoice != 2 || m_modeChoice != 3) {
    cout << "Enter 1 for classic, 2 for donut, and 3 for mirror mode: " << endl;
    cin >> m_modeChoice;
    if (m_modeChoice == 1 || m_modeChoice == 2 || m_modeChoice == 3 ) {
      return m_modeChoice;
    }
    cout << "Please enter a valid input." << endl;
  }
  return -1;
}

int UserInput::chooseNext() { // chooses how to go between generations
  m_nextChoice = 0;
  while(m_nextChoice != 1 || m_nextChoice != 2 || m_nextChoice != 3) {
    cout << "Enter 1 for a brief pause between generations, 2 to further the simulation by hitting enter, and 3 to output each generation to a file: " << endl;
    cin >> m_nextChoice;
    if (m_nextChoice == 1 || m_nextChoice == 2 || m_nextChoice == 3 ) {
      return m_nextChoice;
    }
    cout << "Please enter a valid input." << endl;
  }
  return -1;
}

string UserInput::getFilePath() { //accessor
  return m_filePath;
}

int UserInput::getHeight() {//accessor
  return m_height;
}

int UserInput::getWidth() {//accessor
  return m_width;
}

float UserInput::getDensity() {//accessor
  return m_density;
}

int UserInput::getChoice() {//accessor
  return m_choice;
}
