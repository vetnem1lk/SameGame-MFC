
// SameGameView.h: интерфейс класса CSameGameView
//

#pragma once


class CSameGameView : public CView
{
protected: // создать только из сериализации
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

	// Атрибуты
public:
	CSameGameDoc* GetDocument() const;

	// Операции
public:

	// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Реализация
public:
	void ResizeWindow();
	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // версия отладки в SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
{
	return reinterpret_cast<CSameGameDoc*>(m_pDocument);
}
#endif

