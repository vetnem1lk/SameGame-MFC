
#pragma once

class CSameGameBoard
{
public:
	CSameGameBoard(void);

	// Deep copy constructor
	CSameGameBoard(const CSameGameBoard& board);

	~CSameGameBoard(void);

	// creating and configuring game board settings
	void SetupBoard(void);

	// get the color in a certain area of the game board
	COLORREF GetBoardSpace(int row, int col);

	//  counting the number of remaining blocks
	int GetRemainingCount(void) const { return m_nRemaining; }
	int GetWidth(void) const { return m_nWidth; }
	void SetWidth(int nWidth)
	{
		m_nWidth = (nWidth >= 3) ? nWidth : 3;
	}
	int GetHeight(void) const { return m_nHeight; }
	void SetHeight(int nHeight)
	{
		m_nHeight = (nHeight >= 3) ? nHeight : 3;
	}
	int GetColumns(void) const { return m_nColumns; }
	void SetColumns(int nColumns)
	{
		m_nColumns = (nColumns >= 5) ? nColumns : 5;
	}
	int GetRows(void) const { return m_nRows; }
	void SetRows(int nRows)
	{
		m_nRows = (nRows >= 5) ? nRows : 5;
	}

	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors)
	{
		m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;
	}

	bool IsGameOver(void) const;
	int DeleteBlocks(int row, int col);
	void DeleteBoard(void);

private:
	void CreateBoard(void);

	// enumeration with direction options (where we came from)
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	// Helper recursive function to remove adjoining blocks
	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);

	// compact the board after blocks have been removed
	void CompactBoard(void);

	int** m_arrBoard;

	// list of colors: 0 is the background color, 1-7 are the block colors
	COLORREF m_arrColors[8];

	// Information about the size of the playing field
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;

	// Number of remaining blocks
	int m_nRemaining;
	// Number of colors
	int m_nColors;
};

