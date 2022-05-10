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

	// Создание и настройка параметров игровой доски
	SetupBoard();
}

CSameGameBoard::~CSameGameBoard(void)
{
	// Просто удаляем нашу доску
	DeleteBoard();
}

void CSameGameBoard::SetupBoard(void)
{
	// При необходимости создаем доску
	if (m_arrBoard == NULL)
		CreateBoard();

	// Устанавливаем каждому блоку случайный цвет
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = (rand() % 3) + 1;

	// Устанавливаем количество оставшихся блоков
	m_nRemaining = m_nRows * m_nColumns;
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col)
{
	// Проверяем границы массива
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
				// Сначала удаляем каждую отдельную строку
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		// В конце удаляем массив, содержащий строки
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

void CSameGameBoard::CreateBoard(void)
{
	// Если у нас осталась доска с предыдущего раза, то удаляем её
	if (m_arrBoard != NULL)
		DeleteBoard();

	// Создаем массив для хранения строк
	m_arrBoard = new int* [m_nRows];

	// Создаем отдельно каждую строку
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];

		// Устанавливаем для каждого блока значение цвета, равное цвету фона
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}
}

int CSameGameBoard::DeleteBlocks(int row, int col)
{
	//  Проверяем на валидность индексы ячейки и столбца
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return -1;
	//  Если блок уже имеет цвет фона, то удалить его уже не получится
	int nColor = m_arrBoard[row][col];
	if (nColor == 0)
		return -1;
	//	Сначала проверяем, если ли примыкающие блоки с тем же цветом

	int nCount = -1;
	if ((row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) ||
		(row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) ||
		(col - 1 >= 0 && m_arrBoard[row][col - 1] == nColor) ||
		(col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor))
	{
		//  Затем рекурсивно вызываем функцию, для удаления примыкающих блоков одного цвета...

		m_arrBoard[row][col] = 0;
		nCount = 1;
		//  ...сверху...
		nCount +=
			DeleteNeighborBlocks(row - 1, col, nColor, DIRECTION_DOWN);
		//  ...снизу...
		nCount +=
			DeleteNeighborBlocks(row + 1, col, nColor, DIRECTION_UP);
		//  ...слева...
		nCount +=
			DeleteNeighborBlocks(row, col - 1, nColor, DIRECTION_RIGHT);
		//  ...справа
		nCount +=
			DeleteNeighborBlocks(row, col + 1, nColor, DIRECTION_LEFT);
		//  В конце сжимаем нашу доску
		CompactBoard();
		//  Вычитаем число удаленных блоков из общего количества
		m_nRemaining -= nCount;
	}
	//  Возвращаем количество удаленных блоков
	return nCount;
}

int CSameGameBoard::DeleteNeighborBlocks(int row, int col, int color,
	Direction direction)
{
	//  Проверяем на валидность индексы ячейки и столбца
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return 0;
	//  Проверка на то, что блок имеет тот же цвет
	if (m_arrBoard[row][col] != color)
		return 0;
	int nCount = 1;
	m_arrBoard[row][col] = 0;
	//  Если мы пришли НЕ СВЕРХУ, то идем НАВЕРХ...
	if (direction != DIRECTION_UP)
		nCount +=
		DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
	//  Если мы пришли НЕ СНИЗУ, то спускаемся ВНИЗ...
	if (direction != DIRECTION_DOWN)
		nCount +=
		DeleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
	//  Если мы пришли НЕ СЛЕВА, то идем ВЛЕВО...
	if (direction != DIRECTION_LEFT)
		nCount +=
		DeleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
	//  Если мы пришли НЕ СПРАВА, то идем ВПРАВО...
	if (direction != DIRECTION_RIGHT)
		nCount +=
		DeleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);
	//  Возвращаем общее количество удаленных блоков
	return nCount;
}

void CSameGameBoard::CompactBoard(void)
{
	//  Сначала мы всё сдвигаем вниз
	for (int col = 0; col < m_nColumns; col++)
	{
		int nNextEmptyRow = m_nRows - 1;
		int nNextOccupiedRow = nNextEmptyRow;
		while (nNextOccupiedRow >= 0 && nNextEmptyRow >= 0)
		{
			//  Сначала мы находим пустую строку
			while (nNextEmptyRow >= 0 &&
				m_arrBoard[nNextEmptyRow][col] != 0)
				nNextEmptyRow--;
			if (nNextEmptyRow >= 0)
			{
				//  Затем находим занятую строку, расположенную следом за пустой
				nNextOccupiedRow = nNextEmptyRow - 1;
				while (nNextOccupiedRow >= 0 &&
					m_arrBoard[nNextOccupiedRow][col] == 0)
					nNextOccupiedRow--;
				if (nNextOccupiedRow >= 0)
				{
					// Теперь перемещаем блоки с занятой строки на пустую 
					m_arrBoard[nNextEmptyRow][col] =
						m_arrBoard[nNextOccupiedRow][col];
					m_arrBoard[nNextOccupiedRow][col] = 0;
				}
			}
		}
	}
	//  Затем всё, что справа, смещаем влево
	int nNextEmptyCol = 0;
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns)
	{
		//  Сначала мы находим пустой столбец
		while (nNextEmptyCol < m_nColumns &&
			m_arrBoard[m_nRows - 1][nNextEmptyCol] != 0)
			nNextEmptyCol++;
		if (nNextEmptyCol < m_nColumns)
		{
			//  Затем находим занятый столбец, расположенный следом за пустым
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < m_nColumns &&
				m_arrBoard[m_nRows - 1][nNextOccupiedCol] == 0)
				nNextOccupiedCol++;
			if (nNextOccupiedCol < m_nColumns)
			{
				//  Двигаем весь слобец влево
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
	//  Проверяем столбец за столбцом, слева-направо
	for (int col = 0; col < m_nColumns; col++)
	{
		//  Строку за строкой, снизу-вверх
		for (int row = m_nRows - 1; row >= 0; row--)
		{
			int nColor = m_arrBoard[row][col];
			//  Если мы попали на ячейку с цветом фона, значит этот столбец уже уничтожен
			if (nColor == 0)
				break;
			else
			{
				//  Проверяем сверху и справа
				if (row - 1 >= 0 &&
					m_arrBoard[row - 1][col] == nColor)
					return false;
				else if (col + 1 < m_nColumns &&
					m_arrBoard[row][col + 1] == nColor)
					return false;
			}
		}
	}
	//  Если примыкающих блоков не обнаружено
	return true;
}