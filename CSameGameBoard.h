#pragma once
class CSameGameBoard
{
public:
	// Конструктор по умолчанию
	CSameGameBoard(void);

	// Деструктор
	~CSameGameBoard(void);

	// Функция для рандомной расстановки блоков в начале игры
	void SetupBoard(void);

	// Получаем цвет в определенном участке игрового поля
	COLORREF GetBoardSpace(int row, int col);

	// Геттеры для получения информации о параметрах игрового поля
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }

	// Функция для удаления игрового поля и освобождения памяти
	void DeleteBoard(void);
private:
	// Функция для создания игрового поля и выделения памяти под него
	void CreateBoard(void);

	// Указатель на двумерный массив
	int** m_arrBoard;

	// Список цветов: 0 – это цвет фона, 1-3 – это цвета блоков
	COLORREF m_arrColors[4];

	// Информация о размере игрового поля
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
};

