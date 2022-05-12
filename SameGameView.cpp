
// SameGameView.cpp: реализация класса CSameGameView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "COptionDialog.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL_3COLORS, &CSameGameView::OnLevel3colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS, &CSameGameView::OnUpdateLevel3colors)
	ON_COMMAND(ID_LEVEL_4COLORS, &CSameGameView::OnLevel4colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS, &CSameGameView::OnUpdateLevel4colors)
	ON_COMMAND(ID_LEVEL_5COLORS, &CSameGameView::OnLevel5colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS, &CSameGameView::OnUpdateLevel5colors)
	ON_COMMAND(ID_LEVEL_6COLORS, &CSameGameView::OnLevel6colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLORS, &CSameGameView::OnUpdateLevel6colors)
	ON_COMMAND(ID_LEVEL_7COLORS, &CSameGameView::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS, &CSameGameView::OnUpdateLevel7colors)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CSameGameView::OnSetupBlocksize)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CSameGameView::OnSetupBlockcount)
	ON_COMMAND(ID_GAME_UNDO, &CSameGameView::OnGameUndo)
	ON_UPDATE_COMMAND_UI(ID_GAME_UNDO, &CSameGameView::OnUpdateGameUndo)
	ON_COMMAND(ID_GAME_REDO, &CSameGameView::OnGameRedo)
	ON_UPDATE_COMMAND_UI(ID_GAME_REDO, &CSameGameView::OnUpdateGameRedo)
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* pDC)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// saving the current state of the device context
	int nDCSave = pDC->SaveDC();

	// getting the dimensions of the client area
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);

	// draw the background
	pDC->FillSolidRect(&rcClient, clr);

	// create a paint brush
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	// draw blocks
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{

			clr = pDoc->GetBoardSpace(row, col);

			// calculate the size and position of the game space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			// fill the block with the appropriate color
			pDC->FillSolidRect(&rcBlock, clr);

			// draw a contour
			pDC->Rectangle(&rcBlock);

		}

	}
	// restoring the device context
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG

void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  create a pointer to Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// get the row and column index of the element that was clicked
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Removing blocks from Document
	int count = pDoc->DeleteBlocks(row, col);
	//  checking if blocks have been removed
	if (count > 0)
	{
		//  redrawing the View
		Invalidate();
		UpdateWindow();
		//  checking if the game is over
		if (pDoc->IsGameOver())
		{
			//  get the number of remaining blocks
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("Нет доступных ходов\nКоличество оставшихся блоков: %d"),
				remaining);
			//  displaying the result of the game to the user
			MessageBox(message, _T("Игра Закончена"), MB_OK | MB_ICONINFORMATION);
		}
	}
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonDown(nFlags, point);
}

void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	ResizeWindow();

}

void CSameGameView::ResizeWindow()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// getting the dimensions of the client area
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// Resizing the window based on the size of our board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;

	GetParentFrame()->MoveWindow(&rcWindow);
}

void CSameGameView::setColorCount(int numColors)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Set the number of colors
	pDoc->SetNumColors(numColors);

	// Redrawing the View
	Invalidate();
	UpdateWindow();
}

void CSameGameView::checkLevelColors(CCmdUI* pCmdUI, int numColors)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Checking the set difficulty level
	pCmdUI->SetCheck(pDoc->GetNumColors() == numColors);
}


// Обработчики сообщений CSameGameView

void CSameGameView::OnLevel3colors()
{
	setColorCount(3);
}


void CSameGameView::OnUpdateLevel3colors(CCmdUI* pCmdUI)
{
	checkLevelColors(pCmdUI, 3);
}


void CSameGameView::OnLevel4colors()
{
	setColorCount(4);
}


void CSameGameView::OnUpdateLevel4colors(CCmdUI* pCmdUI)
{
	checkLevelColors(pCmdUI, 4);
}


void CSameGameView::OnLevel5colors()
{
	setColorCount(5);
}


void CSameGameView::OnUpdateLevel5colors(CCmdUI* pCmdUI)
{
	checkLevelColors(pCmdUI, 5);
}


void CSameGameView::OnLevel6colors()
{
	setColorCount(6);
}


void CSameGameView::OnUpdateLevel6colors(CCmdUI* pCmdUI)
{
	checkLevelColors(pCmdUI, 6);
}


void CSameGameView::OnLevel7colors()
{
	setColorCount(7);
}


void CSameGameView::OnUpdateLevel7colors(CCmdUI* pCmdUI)
{
	checkLevelColors(pCmdUI, 7);
}


void CSameGameView::OnSetupBlocksize()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	COptionDialog dlg(false, this);
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	// Display the resulting window
	if (dlg.DoModal() == IDOK)
	{
		pDoc->DeleteBoard();
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		pDoc->SetupBoard();
		ResizeWindow();
	}
}

void CSameGameView::OnSetupBlockcount()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	COptionDialog dlg(true, this);
	//  Setting row and column options
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	//  Display the resulting window
	if (dlg.DoModal() == IDOK)
	{
		pDoc->DeleteBoard();
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		pDoc->SetupBoard();
		ResizeWindow();
	}
}

void CSameGameView::OnGameUndo()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UndoLast();
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateGameUndo(CCmdUI* pCmdUI)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanUndo());
}


void CSameGameView::OnGameRedo()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->RedoLast();
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateGameRedo(CCmdUI* pCmdUI)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanRedo());
}
