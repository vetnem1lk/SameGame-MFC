
// SameGame.h: основной файл заголовка для приложения SameGame
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSameGameApp:
// Сведения о реализации этого класса: SameGame.cpp
//

class CSameGameApp : public CWinApp
{
public:
	CSameGameApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSameGameApp theApp;
