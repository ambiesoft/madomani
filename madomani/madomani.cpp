// madomani.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
// CMadomaniApp �N���X�̍\�z

CMadomaniApp::CMadomaniApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CMadomaniApp �I�u�W�F�N�g

CMadomaniApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMadomaniApp �N���X�̏�����

BOOL CMadomaniApp::InitInstance()
{
	// �W���I�ȏ���������

#ifdef _AFXDLL
	// Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
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

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
