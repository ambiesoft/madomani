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

#include <map>

#include "../../lsMisc/GetFileNameFromHwnd.h"
#include "../../lsMisc/tstring.h"
#include "../../lsMisc/GetWorkingArea.h"
#include "../../lsMisc/stringEndwith.h"
#include "../../lsMisc/vbregexp.h"
#include "../../lsMisc/getWindowTstring.h"
#include "../../lsMisc/stdosd/stdosd.h"

#include "madomanic.h"
#include "inargs.h"
#include "helper.h"


using namespace Ambiesoft;
using namespace Ambiesoft::stdosd;
using namespace std;

wstring splitWithComma2(size_t& i,const wstring& lookee)
{
	wstring ret;
	for (; i < lookee.length(); ++i)
	{
		wchar_t c = lookee[i];
		if (c == L'\\')
		{
			++i;
			c = lookee[i];
		}
		else if (c == L',')
		{
			break;
		}
		ret += c;
	}
	return ret;
}
vector<wstring> splitWithComma(const wstring& lookee)
{
	vector<wstring> rets;
	size_t i = 0;
	for (;;)
	{
		wstring t = splitWithComma2(i, lookee);
		if (t.empty())
			break;
		rets.push_back(t);
		++i;
	}
	return rets;
}

pair<wstring, wstring> splitNameAndValue(const wstring& sIn)
{
	wstring::size_type pos = sIn.find(L'=');
	if (pos == wstring::npos)
		return pair<wstring, wstring>();

	wstring lhs = sIn.substr(0, pos);
	wstring rhs = sIn.substr(pos + 1);

	return pair<wstring, wstring>(lhs, rhs);
}
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	static UINT oi;
	TOPWINVECTOR& allwins = *( (TOPWINVECTOR*)lParam );
	TCHAR szT[1024];
	if(IsWindowVisible(hwnd) && 
		GetFileNameFromHwnd(hwnd, szT, countof(szT)-1)
		)
	{
		allwins.push_back(
			shared_ptr<CTopWinInfo>(
			new CTopWinInfo(hwnd, szT, ++oi, GetWindowThreadProcessId(hwnd, nullptr))));
	}
	return TRUE;
}





int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	// these are old
	// -pos bottomleft -width max -e AcroRd32.exe
	// -pos bottomright -width half -height max AcroRd32.exe
	// -pos bottomleft firefox.exe -rtitle " - Mozilla Firefox$"
	// -pos topright -e larmoji.exe
	// -pos bottomright iexplore.exe -rtitle " - Windows Internet Explorer$"
	// -pos topleft mdie.exe -rtitle "^MDIE"

	// these are new
	// -pos topleft -height max -width half -target="rtitle=,exe=AcroRd32.exe" -target="rtitle=,exe=FOXITREADER.EXE"

	if(__argc <= 1)
	{
		showhelp();
		return 0;
	}

	bool bShowResult = false;
	bool bRestoreWindow = false;
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
		else if(wcsncmp(arg, _T("-target="), 8)==0)
		{
			// Example:
			// -target="rtitle=,exe=AcroRd32.exe"
			wstring lookee = arg + 8;
			

			// split with ','
			vector<wstring> parts = splitWithComma(lookee);
			map<wstring, wstring> nameandvalues;
			for (auto&& s : parts)
			{
				pair<wstring, wstring> nameandvalue = splitNameAndValue(s);
				nameandvalues.insert(nameandvalue);
			}

			wstring rtitle, exe;
			if (nameandvalues.find(L"rtitle") != nameandvalues.end())
				rtitle = nameandvalues[L"rtitle"];
			if (nameandvalues.find(L"exe") != nameandvalues.end())
				exe = nameandvalues[L"exe"];

			if (rtitle.empty() && exe.empty())
			{
				// both empty
				wstring message = I18S(L"'rtitle' or 'exe' must be specified.");
				errorMeesageAndQuit(message.c_str());
			}

			//if (inargs.HasRegTitle())
			//{
			//	LPTSTR pMessage = (LPTSTR)malloc((lstrlen(inargs.GetMainArg().c_str()) + 128)*sizeof(TCHAR));
			//	wsprintf(pMessage, I18S(_T("rtitle \"%s\" already set.")), inargs.GetRegTitle().c_str());
			//	errorMeesageAndQuit(pMessage);
			//}
			//if( (i+1)==__argc )
			//{
			//	errorMeesageAndQuit(I18S(_T("No argument for -rtitle")));
			//}
			//++i;
			//arg = targv[i];
			inargs.AddMainArg(rtitle,exe);
		}
		//else if(lstrcmp(arg, _T("-e"))==0)
		//{
		//	if(inargs.HasMainArg())
		//	{
		//		LPTSTR pMessage = (LPTSTR)malloc( (lstrlen(inargs.GetMainArg().c_str()) + 128)*sizeof(TCHAR));
		//		wsprintf(pMessage, I18S(_T("Main arg \"%s\" already set.")), inargs.GetMainArg().c_str());
		//		errorMeesageAndQuit(pMessage);
		//	}
		//	if ((i + 1) == __argc)
		//	{
		//		errorMeesageAndQuit(I18S(_T("No argument for -e")));
		//	}
		//	++i;
		//	inargs.SetMainArg(targv[i]);
		//}
		else if (lstrcmp(arg, _T("-h")) == 0 || lstrcmp(arg, _T("/?")) == 0)
		{
			showhelp();
			return 0;
		}
		else if (lstrcmp(arg, _T("-r")) == 0)
		{
			bShowResult = true;
		}
		else if (lstrcmp(arg, _T("-g")) == 0)
		{
			bRestoreWindow = true;
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

	wstring processResults;
	for (auto&& win : allwins)
	{
		for (size_t i = 0; i < inargs.length(); ++i)
		{
			// No exe == true 
			// OR
			// exe matches
			if (!inargs.HasMainArg(i) ||
				stringEndwithI(
				win->GetPath().c_str(),
				inargs.GetMainArg(i).c_str())
				)
			{
				// No reg
				// OR
				// title matches reg
				if (!inargs.HasRegTitle(i) ||
					(vbregMatch(getWindowTstring(win->GetHwnd()).c_str(), inargs.GetRegTitle(i).c_str())))
				{
					RECT resultRect = { 0 };
					BOOL success = maniWindow(
						win->GetHwnd(),
						inargs.GetPostType(),
						inargs.GetSizeTypeWidth() | inargs.GetSizeTypeHeight(),
						inargs.GetCustomWidth(), inargs.GetCustomHeight(),
						bRestoreWindow,
						resultRect);

					if (bShowResult)
					{
						processResults += stdFormat(L"%s '%s' (Process=%d, HWND=%#p) has moved to (%d,%d,%d,%d)\r\n",
							(success ? I18S(L"Succeeded") : I18S(L"Failed")),
							win->GetPath().c_str(),
							win->GetProcessID(),
							win->GetHwnd(),
							resultRect.left, resultRect.top, resultRect.right, resultRect.bottom);
					}
				}
			}
		}
	}

	if (bShowResult)
	{
		if (processResults.empty())
		{
			processResults = I18S(L"No windows are processed.");
		}
		
		MessageBox(NULL,
			processResults.c_str(),
			APP_NAME,
			MB_ICONINFORMATION);
	}
	return 0;
}



