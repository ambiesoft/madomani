// madomaniDlg.h : ヘッダー ファイル
//

#if !defined(AFX_MADOMANIDLG_H__7349D6C5_7C64_4D0F_9414_B0ECC5D622E8__INCLUDED_)
#define AFX_MADOMANIDLG_H__7349D6C5_7C64_4D0F_9414_B0ECC5D622E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMadomaniDlg ダイアログ

class CMadomaniDlg : public CDialog
{
// 構築
public:
	CMadomaniDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMadomaniDlg)
	enum { IDD = IDD_MADOMANI_DIALOG };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMadomaniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMadomaniDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MADOMANIDLG_H__7349D6C5_7C64_4D0F_9414_B0ECC5D622E8__INCLUDED_)
