#include "pch.h"
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard(void)
	: m_arrBoard(NULL),
	m_nColumns(15), m_nRows(15),
	m_nHeight(35), m_nWidth(35)
{
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(255, 0, 0);
	m_arrColors[2] = RGB(255, 255, 64);
	m_arrColors[3] = RGB(0, 0, 255);
}

CSameGameBoard::~CSameGameBoard(void)
{
	// ������ ������� ���� �����
	DeleteBoard();
}

void CSameGameBoard::SetupBoard(void)
{
	// ��� ������������� ������� �����
	if (m_arrBoard == NULL)
		CreateBoard();

	// ������������� ������� ����� ��������� ����
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = (rand() % 3) + 1;
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col)
{
	// ��������� ������� �������
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
				// ������� ������� ������ ��������� ������
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		// � ����� ������� ������, ���������� ������
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

void CSameGameBoard::CreateBoard(void)
{
	// ���� � ��� �������� ����� � ����������� ����, �� ������� �
	if (m_arrBoard != NULL)
		DeleteBoard();

	// ������� ������ ��� �������� �����
	m_arrBoard = new int* [m_nRows];

	// ������� �������� ������ ������
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];

		// ������������� ��� ������� ����� �������� �����, ������ ����� ����
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}
}