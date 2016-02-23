// Steve Brown
// CS355
// Assignment #2 (Sudoku solver)
// Due 2/9/16

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <array>
#include <bitset>
#include <string>
#include <cstdlib>
#include <iostream>


class SudokuGrid {
private:
  	struct Cell{ // Cell structure 
	std::bitset<10> pencils; // Number of pencils for each cell
	int number; // Number for each cell
    bool fixed; // If cell is fixed during input
	bool solved; // If cell is solved
	};
public:
	std::array<std::array<Cell, 9>, 9> grid; // Creates the grid with 81 cells
	// Constructor
  	SudokuGrid(std::string s) 
	{ 
		int r, c, k = 0;

		for(r = 0; r < 9; r++) // Row
		{
			for(c = 0; c < 9; c++, k++) // Column
			{
				if(s.at(k) == '.') // If read a period, then it's a zero
				{
					grid[r][c].number = 0;
					grid[r][c].fixed = false;
					grid[r][c].solved = false;
					grid[r][c].pencils.reset();
				}
				else // Otherwise it's a number
				{		
					grid[r][c].number = (int) (s.at(k) - '0'); // Subtract the ASCII char to get the proper number
					grid[r][c].fixed = true;
					grid[r][c].solved = true;
					grid[r][c].pencils.reset();
				}
			}
		}
	};

  	int number(int row, int col) const // Read mumber at grid location (row,col). Returns 0 for empty cell
	{ 
		return (grid[row][col].number);
	}
  	void setNumber(int row, int col, int number) // Set number at grid location. Use num = 0 to clear value
	{ 
		grid[row][col].number = number;
	}
  	bool isFixed(int row, int col) const // Number at grid location (row,col) is original "fixed" value
	{ 
		if(grid[row][col].fixed == true) return true;
		else return false;
	}
  	bool isSolved(int row, int col) const // Cell at (row,col) has been marked as solved
	{
		if(grid[row][col].solved == true) return true;
		else return false;
	}
  	void setSolved(int row, int col) // Mark the cell at (row,col) as having been solved
	{
		grid[row][col].solved = true;
	}
  	bool isPencilSet(int row, int col, int n) const // Is value 1 <= n <= 9 penciled into the cell at (row,col)
	{
		if(grid[row][col].pencils[n]) return true;
		else return false;
	}
  	bool anyPencilsSet(int row, int col) const // Are any values at cell (row,col) penciled in?
	{
		if(grid[row][col].pencils.any() == true) return true;
		else return false;
	}
  	void setPencil(int row, int col, int n) // Set pencil n in cell (row,col)
	{ 
		grid[row][col].pencils[n] = 1;
	}
  	void setAllPencils(int row, int col) // Set all nine pencil values in cell (row,col)
	{ 
		grid[row][col].pencils.set();
	}
  	void clearPencil(int row, int col, int n) // Clear pencil n in cell (row,col)
	{
		grid[row][col].pencils[n] = 0;
	}
  	void clearAllPencils(int row, int col) // Clear all pencil values in cell(row,col)
	{
		grid[row][col].pencils.reset();
	}
};

#endif // SUDOKUGRID_H