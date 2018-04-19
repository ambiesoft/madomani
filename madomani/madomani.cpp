// madomani.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "madomani.h"
#include "madomaniDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMadomaniApp

BEGIN_MESSAGE_MAP(CMadomaniApp, CWinApp)
	//{{AFX_MSG_MAP(CMadomaniApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMadomaniApp クラスの構築

CMadomaniApp::CMadomaniApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CMadomaniApp オブジェクト

CMadomaniApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMadomaniApp クラスの初期化

BOOL CMadomaniApp::InitInstance()
{
	// 標準的な初期化処理

#ifdef _AFXDLL
	// Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	CMadomaniDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
