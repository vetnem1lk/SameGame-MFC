
#pragma once

#include "CSameGameBoard.h"

class CSameGameDoc : public CDocument
{
protected: // создать только из сериализации
	CSameGameDoc() noexcept;
	virtual ~CSameGameDoc();
	DECLARE_DYNCREATE(CSameGameDoc)

	// Атрибуты
public:

	// Операции
public:
	// get the color in a certain area of the game board
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board.GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board.SetupBoard(); }

	int GetWidth(void) { return m_board.GetWidth(); }
	void SetWidth(int nWidth) { m_board.SetWidth(nWidth); }
	int GetHeight(void) { return m_board.GetHeight(); }
	void SetHeight(int nHeight) { m_board.SetHeight(nHeight); }
	int GetColumns(void) { return m_board.GetColumns(); }
	void SetColumns(int nColumns) { m_board.SetColumns(nColumns); }
	int GetRows(void) { return m_board.GetRows(); }
	void SetRows(int nRows) { m_board.SetRows(nRows); }

	void DeleteBoard(void) { m_board.DeleteBoard(); }
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col)
	{
		return m_board.DeleteBlocks(row, col);
	}
	int GetRemainingCount()
	{
		return m_board.GetRemainingCount();
	}
	int GetNumColors() { return m_board.GetNumColors(); }
	void SetNumColors(int nColors);
	// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Реализация
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CSameGameBoard m_board;
	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
