// madomaniDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_MADOMANIDLG_H__7349D6C5_7C64_4D0F_9414_B0ECC5D622E8__INCLUDED_)
#define AFX_MADOMANIDLG_H__7349D6C5_7C64_4D0F_9414_B0ECC5D622E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMadomaniDlg �_�C�A���O

class CMadomaniDlg : public CDialog
{
// �\�z
public:
	CMadomaniDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CMadomaniDlg)
	enum { IDD = IDD_MADOMANI_DIALOG };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMadomaniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CMadomaniDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MADOMANIDLG_H__7349D6C5_7C64_4D0F_9414_B0ECC5D622E8__INCLUDED_)
