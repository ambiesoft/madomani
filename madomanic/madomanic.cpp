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

#include "stdafx.h"


#include "../../lsMisc/GetFileNameFromHwnd.h"
#include "../../lsMisc/tstring.h"
#include "../../lsMisc/GetWorkingArea.h"
#include "../../lsMisc/stringEndwith.h"
#include "../../lsMisc/vbregexp.h"
#include "../../lsMisc/getWindowTstring.h"

#include "madomanic.h"
#include "inargs.h"
#include "helper.h"


using namespace Ambiesoft;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	static UINT oi;
	TOPWINVECTOR& allwins = *( (TOPWINVECTOR*)lParam );
	TCHAR szT[1024];
	if(IsWindowVisible(hwnd) && 
		GetFileNameFromHwnd(hwnd, szT, countof(szT)-1)
		)
	{
		allwins.push_back(new CTopWinInfo(hwnd, szT, ++oi));
	}
	return TRUE;
}




void showhelp()
{
	MessageBox(NULL,
		_T("Usage:\n")
		_T("madomanic [-e <executable>] [-E <executablefull>] [-title <title>] [-rtitle <regextitle>] ")
		_T("[-width <max | half | 3rd | 4th | <AnyPixcels>] ")
		_T("[-height <max | half | 3rd | 4th | <AnyPixcels>] ")
		_T("[-pos <topleft | topcenter | topright | centerright | bottomright | bottomcenter | bottomleft | centerleft | center>] ")
		_T("[-h]"),

		APP_NAME _T(" ") APP_VERSION,
		MB_ICONINFORMATION
		);
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{

	// -pos bottomleft -width max -e AcroRd32.exe
	// -pos bottomright -width half -height max AcroRd32.exe
	// -pos bottomleft firefox.exe -rtitle " - Mozilla Firefox$"
	// -pos topright -e larmoji.exe
	// -pos bottomright iexplore.exe -rtitle " - Windows Internet Explorer$"
	// -pos topleft mdie.exe -rtitle "^MDIE"

	if(__argc <= 1)
	{
		showhelp();
		return 0;
	}

	CINArgs inargs;
	for(int i=1 ; i < __argc ; ++i)
	{
		LPCTSTR arg = targv[i];
		if(lstrcmp(arg, _T("-pos"))==0)
		{
			if(inargs.HasPostype())
			{
				errorMeesageAndQuit(I18S(_T("-pos : pos already set")));
			}
			if( (i+1)==__argc )
			{
				errorMeesageAndQuit(I18S(_T("No argument for -pos")));
			}
			++i;
			arg = targv[i];
			if(lstrcmp(arg, _T("topleft"))==0)
			{
				inargs.SetPostype(MV_POS_TOPLEFT);
			}
			else if(lstrcmp(arg, _T("topcenter"))==0)
			{
				inargs.SetPostype(MV_POS_TOPCENTER);
			}
			else if(lstrcmp(arg, _T("topright"))==0)
			{
				inargs.SetPostype(MV_POS_TOPRIGHT);
			}
			else if(lstrcmp(arg, _T("centerright"))==0)
			{
				inargs.SetPostype(MV_POS_CENTERRIGHT);
			}
			else if(lstrcmp(arg, _T("bottomright"))==0)
			{
				inargs.SetPostype(MV_POS_BOTTOMRIGHT);
			}
			else if(lstrcmp(arg, _T("bottomcenter"))==0)
			{
				inargs.SetPostype(MV_POS_BOTTOMCENTER);
			}
			else if(lstrcmp(arg, _T("bottomleft"))==0)
			{
				inargs.SetPostype(MV_POS_BOTTOMLEFT);
			}
			else if(lstrcmp(arg, _T("centerleft"))==0)
			{
				inargs.SetPostype(MV_POS_CENTERLEFT);
			}
			else if(lstrcmp(arg, _T("center"))==0)
			{
				inargs.SetPostype(MV_POS_CENTER);
			}
			else
			{
				tstring t= arg;
				t+= _T(" : ");
				t+= I18S(_T("Invalid argument for -pos"));
				errorMeesageAndQuit(t.c_str());
			}
		}
		else if(lstrcmp(arg, _T("-width"))==0)
		{
			inargs.argprocessWidth(i, __argc, targv, arg);
		}
		else if(lstrcmp(arg, _T("-height"))==0)
		{
			inargs.argprocessHeight(i, __argc, targv, arg);
		}
		else if(lstrcmp(arg, _T("-rtitle"))==0)
		{
			if (inargs.HasRegTitle())
			{
				LPTSTR pMessage = (LPTSTR)malloc((lstrlen(inargs.GetMainArg().c_str()) + 128)*sizeof(TCHAR));
				wsprintf(pMessage, I18S(_T("rtitle \"%s\" already set.")), inargs.GetRegTitle().c_str());
				errorMeesageAndQuit(pMessage);
			}
			if( (i+1)==__argc )
			{
				errorMeesageAndQuit(I18S(_T("No argument for -rtitle")));
			}
			++i;
			arg = targv[i];
			inargs.SetRegTitle(arg);
		}
		else if(lstrcmp(arg, _T("-e"))==0)
		{
			if(inargs.HasMainArg())
			{
				LPTSTR pMessage = (LPTSTR)malloc( (lstrlen(inargs.GetMainArg().c_str()) + 128)*sizeof(TCHAR));
				wsprintf(pMessage, I18S(_T("Main arg \"%s\" already set.")), inargs.GetMainArg().c_str());
				errorMeesageAndQuit(pMessage);
			}
			if ((i + 1) == __argc)
			{
				errorMeesageAndQuit(I18S(_T("No argument for -e")));
			}
			++i;
			inargs.SetMainArg(targv[i]);
		}
		else if (lstrcmp(arg, _T("-h")) == 0 || lstrcmp(arg, _T("/?")) == 0)
		{
			showhelp();
			return 0;
		}
		else
		{
			tstring message = I18S(_T("Unknown option:"));
			message += arg;
			errorMeesageAndQuit(message.c_str());
		}
	}

	if (!inargs.HasPostype() && ( 0 == (inargs.GetSizeTypeWidth() | inargs.GetSizeTypeHeight())))
	{
		errorMeesageAndQuit(I18S(_T("No position specified.")));
	}
	TOPWINVECTOR allwins;
	EnumWindows(EnumWindowsProc, (LPARAM)&allwins);

	for(TOPWINVECTOR::iterator it=allwins.begin() ; it != allwins.end() ; ++it)
	{
		if(stringEndwithI( 
			(*it)->GetPath(),
			inargs.GetMainArg().c_str())
			)
		{
			if(inargs.HasRegTitle())
			{
				tstring title = getWindowTstring((*it)->GetHwnd());
				if(!vbregMatch(title.c_str(), inargs.GetRegTitle().c_str()))
					continue;
			}
			maniWindow(
				(*it)->GetHwnd(), 
				inargs.GetPostType(), // postype, // MV_POS_BOTTOMLEFT, 
				inargs.GetSizeTypeWidth() | inargs.GetSizeTypeHeight(),
				inargs.GetCustomWidth(), inargs.GetCustomHeight()); // sizetypeWidth | sizetypeHeight);
			return 0;
		}
	}
	return 0;
}



