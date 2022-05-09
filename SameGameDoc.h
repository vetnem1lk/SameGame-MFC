
// SameGameDoc.h: интерфейс класса CSameGameDoc 
//


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
	// Геттеры для получения информации о параметрах игрового поля
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board.GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	int GetRows(void) { return m_board.GetRows(); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
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
