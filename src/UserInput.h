#ifndef USERINPUT_H
#define USERINPUT_H
#include <iostream>
#include <string>

using namespace std;

class UserInput {
public:
  UserInput();
  virtual ~UserInput();
  int chooseMode();
  string getFilePath();
  int getHeight();
  int getWidth();
  float getDensity();
  int getChoice();
  int chooseNext();
private:
  string m_filePath;
  int m_height;
  int m_width;
  float m_density;
  int m_choice;
  int m_modeChoice;
  int m_nextChoice;
};

#endif
