// Steve Brown
// CS355
// Assignment #2 (Sudoku solver)
// Due 2/9/16


#include <string>
#include <iostream>
#include <algorithm>
#include "SudokuGrid.h"


using namespace std;

// Finds the number of pencils in a row
int numPencilsInRow(SudokuGrid& grid, int row, int n) 
{
	int count = 0;

	for(int c = 0; c < 9; c++) // Loops through and keeps track of the pencils in the row
		if(grid.isPencilSet(row, c, n) == true)
			count++;

	return count; // Returns the count of pencils
}

// Finds the number of pencils in a column
int numPencilsInColumn(SudokuGrid& grid, int col, int n) 
{
	int count = 0;

	for(int r = 0; r < 9; r++) // Loops through and keeps track of the pencils in the column
		if(grid.isPencilSet(r, col, n) == true)
			count++;

	return count; // Returns the count of pencils
}	

// Finds the number of pencils in a block
int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n) 
{
	int count = 0;
	int beginC = (col-(col%3)); // Beginning point of column
	int beginR = (row-(row%3)); // Beginning point of row

	for(int r = beginR; r < (beginR+3); r++) // Loops through the block and counts the number of pencils
		for(int c = beginC; c < (beginC+3); c++)
			if(grid.isPencilSet(r,c,n) == true)
				count++;
	
	return count; // Returns the count of pencils
}

// Loops through row, column, and block and checks for conflicting numbers
bool conflictingNumber(SudokuGrid& grid, int row, int col, int n) 
{
	for(int i = 0; i < 9; i++) // Checks the column and row
	{
		if(grid.number(i,col) == n) return true;
		if(grid.number(row,i) == n) return true;
	}

	int beginC = (col-(col%3));
	int beginR = (row-(row%3));
	
	for(int r = beginR; r < (beginR+3); r++) // Checks the block
		for(int c = beginC; c < (beginC+3); c++)
			if((r != row && c != col) && grid.number(r,c) == n)
				return true;

	return false; // Returns false if no conflicting value found
}
	
// Finds a cell with no value
bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col) 
{
	for(row = 0; row < 9; row++) // Loops through the whole grid and looks for a zero
		for(col = 0; col < 9; col++)
			if(grid.number(row,col) == 0)
				return true;

	return false; // Returns false if no empty cells. Solved!
}

// Loops through and checks for cells to pencil in values
void autoPencil(SudokuGrid& grid) 
{
	for(int r = 0; r < 9; r++)
		for(int c = 0; c < 9; c++)
			if(grid.number(r,c) == 0) 
			{
				grid.setAllPencils(r,c);
				for(int n = 1; n <= 9; n++)
					if(conflictingNumber(grid,r,c,n))
						grid.clearPencil(r,c,n);
			}
}

// Uses autoPencil to check for possible values to be deduced before solving
void deduce(SudokuGrid& grid) 
{
	bool changed;
	do 
	{ // repeat until no changes made
		autoPencil(grid);
		changed = false;
		for (int row = 0; row < 9; row++)
			for (int col = 0; col < 9; col++)
				for (int n = 1; n <= 9; n++)
					if (grid.isPencilSet(row, col, n) &&
						(numPencilsInRow(grid, row, n) == 1 ||
						numPencilsInColumn(grid, col, n) == 1 ||
						numPencilsInBlock(grid, row, col, n) == 1)) 
					{
						grid.clearAllPencils(row, col);
						grid.setNumber(row,col,n);
						grid.setSolved(row,col);
						autoPencil(grid);
						changed = true;
						break;
					}
	} while(changed);
}

// Solves the puzzle after deducing it first
bool solveSudoku(SudokuGrid& grid) 
{
	int row=0, col=0; // Initialize?
	if (findUnassignedLocation(grid, row, col) == false)
		return true; // puzzle filled, solution found!
	for (int num = 1; num <= 9; num++)
		if (conflictingNumber(grid, row, col, num) == false) 
		{
			grid.setNumber(row, col, num); // try next number
			if (solveSudoku(grid))
				return true;                 // solved!
			grid.setNumber(row, col, 0);   // not solved, clear number
		}
	return false; // not solved, back track
}

// Main function
int main(int argc, char *argv[])
{
  	string puzzle; // Reads in the initial puzzle from stdin
  	cin >> puzzle;
  	if (puzzle.length() != 9*9 ||
      	!all_of(puzzle.begin(), puzzle.end(),
	    [](char ch) {
			return ch == '.' || ('1' <= ch && ch <= '9');
	     })) {
    	cerr << "bogus puzzle!" << endl;
    	exit(1);
  	}
	
	SudokuGrid grid(puzzle); // Constructs a grid from the puzzle string

	cout << "\n";
	for(int r = 0; r < 9; r++) // Prints out the unsolved puzzle
	{
		for(int c = 0; c < 9; c++)
		{
			if(grid.number(r,c) == 0)
				cout << ". ";
			else cout << grid.number(r,c) << " ";
			if(c%3 == 2 && c != 8) cout << "| ";
		}
		if(r%3 == 2 && r != 8) cout << "\n" << "------+-------+------" << "\n";
		else cout << "\n";
	}	
	cout << "\n";

	deduce(grid); // Deduce the puzzle
	
	for(int r = 0; r < 9; r++) // Prints out the deduced puzzle
	{
		for(int c = 0; c < 9; c++)
		{
			if(grid.number(r,c) == 0)
				cout << ". ";
			else cout << grid.number(r,c) << " ";
			if(c%3 == 2 && c != 8) cout << "| ";
		}
		if(r%3 == 2 && r != 8) cout << "\n" << "------+-------+------" << "\n";
		else cout << "\n";
	}	
	cout << "\n";	

	solveSudoku(grid); // Solve the puzzle
	
	for(int r = 0; r < 9; r++) // Prints out the solved puzzle
	{
		for(int c = 0; c < 9; c++)
		{
			if(grid.number(r,c) == 0)
				cout << ". ";
			else cout << grid.number(r,c) << " ";
			if(c%3 == 2 && c != 8) cout << "| ";
		}
		if(r%3 == 2 && r != 8) cout << "\n" << "------+-------+------" << "\n";
		else cout << "\n";
	}	
	cout << "\n";

  	return 0;
}