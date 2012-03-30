// madomani.h : MADOMANI アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MADOMANI_H__A0E2D342_078A_46FC_AA3A_EEBB849BA2BC__INCLUDED_)
#define AFX_MADOMANI_H__A0E2D342_078A_46FC_AA3A_EEBB849BA2BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMadomaniApp:
// このクラスの動作の定義に関しては madomani.cpp ファイルを参照してください。
//

class CMadomaniApp : public CWinApp
{
public:
	CMadomaniApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMadomaniApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMadomaniApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MADOMANI_H__A0E2D342_078A_46FC_AA3A_EEBB849BA2BC__INCLUDED_)
