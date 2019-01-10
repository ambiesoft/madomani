//Copyright (C) 2017 Ambiesoft All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//1. Redistributions of source code must retain the above copyright
//notice, this list of conditions and the following disclaimer.
//2. Redistributions in binary form must reproduce the above copyright
//notice, this list of conditions and the following disclaimer in the
//documentation and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//SUCH DAMAGE.

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
