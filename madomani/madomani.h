// madomani.h : MADOMANI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_MADOMANI_H__A0E2D342_078A_46FC_AA3A_EEBB849BA2BC__INCLUDED_)
#define AFX_MADOMANI_H__A0E2D342_078A_46FC_AA3A_EEBB849BA2BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CMadomaniApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� madomani.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CMadomaniApp : public CWinApp
{
public:
	CMadomaniApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMadomaniApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CMadomaniApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MADOMANI_H__A0E2D342_078A_46FC_AA3A_EEBB849BA2BC__INCLUDED_)
