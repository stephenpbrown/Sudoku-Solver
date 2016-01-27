#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <array>
#include <bitset>
#include <string>

class SudokuGrid {
private:
  // private class instance vars go here
public:
  // implement the following

  SudokuGrid(std::string s) { } // constructor

  int number(int row, int col) const {  }
  void setNumber(int row, int col, int number) { }
  bool isFixed(int row, int col) const { }
  bool isSolved(int row, int col) const { }
  void setSolved(int row, int col) { }

  bool isPencilSet(int row, int col, int n) const { }
  bool anyPencilsSet(int row, int col) const { }
  void setPencil(int row, int col, int n) { }
  void setAllPencils(int row, int col) { }
  void clearPencil(int row, int col, int n) { }
  void clearAllPencils(int row, int col) { }
};

#endif // SUDOKUGRID_H
