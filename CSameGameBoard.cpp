#include "pch.h"
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard(void)
	: m_arrBoard(NULL),
	m_nColumns(15), m_nRows(15),
	m_nHeight(35), m_nWidth(35),
	m_nRemaining(0)
{
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(255, 0, 0);
	m_arrColors[2] = RGB(255, 255, 64);
	m_arrColors[3] = RGB(0, 0, 255);

	SetupBoard();
}

CSameGameBoard::~CSameGameBoard(void)
{
	DeleteBoard();
}

void CSameGameBoard::SetupBoard(void)
{
	// create a board if necessary
	if (m_arrBoard == NULL)
		CreateBoard();

	// set each block to a random color
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = (rand() % 3) + 1;

	// set the number of remaining blocks
	m_nRemaining = m_nRows * m_nColumns;
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col)
{
	// checking array bounds
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return m_arrColors[0];
	return m_arrColors[m_arrBoard[row][col]];
}

void CSameGameBoard::DeleteBoard(void)
{
	if (m_arrBoard != NULL)
	{
		for (int row = 0; row < m_nRows; row++)
		{
			if (m_arrBoard[row] != NULL)
			{
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

void CSameGameBoard::CreateBoard(void)
{
	// if we have a board left from the previous time, then delete it
	if (m_arrBoard != NULL)
		DeleteBoard();

	// create an array to store rows
	m_arrBoard = new int* [m_nRows];

	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];

		// set the color value for each block to be the same as the background color.
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}
}

int CSameGameBoard::DeleteBlocks(int row, int col)
{
	//  checking for validity of row and column indices
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return -1;

	//  if the block already has a background color, then it will no longer be possible to delete it.
	int nColor = m_arrBoard[row][col];
	if (nColor == 0)
		return -1;

	//	check if adjacent blocks with the same color
	int nCount = -1;
	if ((row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) ||
		(row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) ||
		(col - 1 >= 0 && m_arrBoard[row][col - 1] == nColor) ||
		(col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor))
	{
		//  recursively call the function to remove adjoining blocks of the same color...
		m_arrBoard[row][col] = 0;
		nCount = 1;
		//  ...up...
		nCount +=
			DeleteNeighborBlocks(row - 1, col, nColor, Direction::DOWN);
		//  ...down...
		nCount +=
			DeleteNeighborBlocks(row + 1, col, nColor, Direction::UP);
		//  ...left...
		nCount +=
			DeleteNeighborBlocks(row, col - 1, nColor, Direction::RIGHT);
		//  ...right
		nCount +=
			DeleteNeighborBlocks(row, col + 1, nColor, Direction::LEFT);
		//  compress our board
		CompactBoard();
		//  subtract the number of removed blocks from the total
		m_nRemaining -= nCount;
	}
	//  returning the number of deleted blocks
	return nCount;
}

int CSameGameBoard::DeleteNeighborBlocks(int row, int col, int color,
	Direction direction)
{
	//  checking for validity of row and column indices
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return 0;

	//  checking if a block has the same color
	if (m_arrBoard[row][col] != color)
		return 0;
	int nCount = 1;
	m_arrBoard[row][col] = 0;
	//  if we didn't come from the TOP, then we go UP...
	if (direction != Direction::UP)
		nCount +=
		DeleteNeighborBlocks(row - 1, col, color, Direction::DOWN);
	//  if we did NOT come from the bottom, then we go down...
	if (direction != Direction::DOWN)
		nCount +=
		DeleteNeighborBlocks(row + 1, col, color, Direction::UP);
	//  if we did NOT come from the LEFT, then we go to the LEFT ...
	if (direction != Direction::LEFT)
		nCount +=
		DeleteNeighborBlocks(row, col - 1, color, Direction::RIGHT);
	//  if we came NOT RIGHT, then we go RIGHT ...
	if (direction != Direction::RIGHT)
		nCount +=
		DeleteNeighborBlocks(row, col + 1, color, Direction::LEFT);
	//  Returning the total number of deleted blocks
	return nCount;
}

void CSameGameBoard::CompactBoard(void)
{
	//  move everything down
	for (int col = 0; col < m_nColumns; col++)
	{
		int nNextEmptyRow = m_nRows - 1;
		int nNextOccupiedRow = nNextEmptyRow;
		while (nNextOccupiedRow >= 0 && nNextEmptyRow >= 0)
		{
			//  find an empty string
			while (nNextEmptyRow >= 0 &&
				m_arrBoard[nNextEmptyRow][col] != 0)
				nNextEmptyRow--;
			if (nNextEmptyRow >= 0)
			{
				//  find the busy line next to the empty one
				nNextOccupiedRow = nNextEmptyRow - 1;
				while (nNextOccupiedRow >= 0 &&
					m_arrBoard[nNextOccupiedRow][col] == 0)
					nNextOccupiedRow--;
				if (nNextOccupiedRow >= 0)
				{
					// move blocks from a busy line to an empty one
					m_arrBoard[nNextEmptyRow][col] =
						m_arrBoard[nNextOccupiedRow][col];
					m_arrBoard[nNextOccupiedRow][col] = 0;
				}
			}
		}
	}
	//  everything on the right is shifted to the left
	int nNextEmptyCol = 0;
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns)
	{
		//  find an empty column
		while (nNextEmptyCol < m_nColumns &&
			m_arrBoard[m_nRows - 1][nNextEmptyCol] != 0)
			nNextEmptyCol++;
		if (nNextEmptyCol < m_nColumns)
		{
			//  find the occupied column next to the empty one
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < m_nColumns &&
				m_arrBoard[m_nRows - 1][nNextOccupiedCol] == 0)
				nNextOccupiedCol++;
			if (nNextOccupiedCol < m_nColumns)
			{
				//  move the whole column to the left
				for (int row = 0; row < m_nRows; row++)
				{
					m_arrBoard[row][nNextEmptyCol] =
						m_arrBoard[row][nNextOccupiedCol];
					m_arrBoard[row][nNextOccupiedCol] = 0;
				}
			}
		}
	}
}

bool CSameGameBoard::IsGameOver(void) const
{
	//  checking column by column, from left to right
	for (int col = 0; col < m_nColumns; col++)
	{
		//  row by row, bottom to top
		for (int row = m_nRows - 1; row >= 0; row--)
		{
			int nColor = m_arrBoard[row][col];
			//  if we hit a cell with a background color, then this column has already been destroyed
			if (nColor == 0)
				break;
			else
			{
				//  checking top and right
				if (row - 1 >= 0 &&
					m_arrBoard[row - 1][col] == nColor)
					return false;
				else if (col + 1 < m_nColumns &&
					m_arrBoard[row][col + 1] == nColor)
					return false;
			}
		}
	}
	//  if no adjoining blocks are found
	return true;
}