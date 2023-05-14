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



#include "madomanic.h"
#include "inargs.h"
#include "helper.h"

#pragma comment(lib, "Shlwapi.lib")

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


bool isOption(LPCWSTR arg, LPCWSTR pOption, int* pN)
{
	if (!stdStartWith(arg, pOption))
		return false;

	LPCWSTR pNum = arg + stdStringLength(pOption);
	if (!*pNum || stdIsSpace(*pNum))
	{
		*pN = 0;
		return true;
	}

	if (!stdIsAsciiDigit(*pNum))
	{
		errorMeesageAndQuit(stdFormat(L"Illegal option '%s'", arg).c_str());
	}
	*pN = _wtoi(pNum);
	return true;
}


vector<CINArgs> getInargsAsVector(map<int, CINArgs>& inargses)
{
	vector<CINArgs> ret;
	for (int i = 0; ; ++i)
	{
		if (inargses.size() == 0)
			return ret;

		if (inargses.count(i))
		{
			ret.push_back(inargses[i]);
			inargses.erase(i);
		}
	}
	return ret;
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
	// -pos topleft -height max -width half -target "rtitle=,exe=AcroRd32.exe" -target="rtitle=,exe=FOXITREADER.EXE"
	// -pos topright -height half -width 3rd -target "class=Chrome_WidgetWin_1"
	// -pos1 topright -height1 half -width1 3rd -target1 "class=Chrome_WidgetWin_1"
	// -pos1 topright -height1 half -width1 3rd -target1 "class=Chrome_WidgetWin_1" -pos2 bottomright -height2 half -width2 3rd -target2 "class=Chrome_WidgetWin_1"

	if(__argc <= 1)
	{
		showhelp();
		return 0;
	}

	bool bShowResult = false;
	bool bRestoreWindow = false;
	int maxMove = -1;
	int n;
	map<int, CINArgs> inargses;
	for(int i=1 ; i < __argc ; ++i)
	{
		LPCTSTR arg = targv[i];
		if(isOption(arg, L"-pos", &n))
		{
			if(inargses[n].HasPostype())
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
				inargses[n].SetPostype(MV_POS_TOPLEFT);
			}
			else if(lstrcmp(arg, _T("topcenter"))==0)
			{
				inargses[n].SetPostype(MV_POS_TOPCENTER);
			}
			else if(lstrcmp(arg, _T("topright"))==0)
			{
				inargses[n].SetPostype(MV_POS_TOPRIGHT);
			}
			else if(lstrcmp(arg, _T("centerright"))==0)
			{
				inargses[n].SetPostype(MV_POS_CENTERRIGHT);
			}
			else if(lstrcmp(arg, _T("bottomright"))==0)
			{
				inargses[n].SetPostype(MV_POS_BOTTOMRIGHT);
			}
			else if(lstrcmp(arg, _T("bottomcenter"))==0)
			{
				inargses[n].SetPostype(MV_POS_BOTTOMCENTER);
			}
			else if(lstrcmp(arg, _T("bottomleft"))==0)
			{
				inargses[n].SetPostype(MV_POS_BOTTOMLEFT);
			}
			else if(lstrcmp(arg, _T("centerleft"))==0)
			{
				inargses[n].SetPostype(MV_POS_CENTERLEFT);
			}
			else if(lstrcmp(arg, _T("center"))==0)
			{
				inargses[n].SetPostype(MV_POS_CENTER);
			}
			else
			{
				wstring t= arg;
				t+= _T(" : ");
				t+= I18S(_T("Invalid argument for -pos"));
				errorMeesageAndQuit(t.c_str());
			}
		}
		else if(isOption(arg, _T("-width"), &n))
		{
			inargses[n].argprocessWidth(i, __argc, targv, arg);
		}
		else if(isOption(arg, _T("-height"),&n))
		{
			inargses[n].argprocessHeight(i, __argc, targv, arg);
		}
		else if(isOption(arg, _T("-target"), &n))
		{
			// Example:
			// -target "rtitle=,class=Chrome_WidgetWin_1,exe=AcroRd32.exe"
			if ((i + 1) == __argc)
			{
				errorMeesageAndQuit(I18S(_T("No argument for -pos")));
			}
			++i;
			arg = targv[i];
			wstring lookee = arg;

			// split with ','
			vector<wstring> parts = splitWithComma(lookee);
			map<wstring, wstring> nameandvalues;
			for (auto&& s : parts)
			{
				pair<wstring, wstring> nameandvalue = splitNameAndValue(s);
				nameandvalues.insert(nameandvalue);
			}

			wstring rtitle, exe, winclass;
			if (nameandvalues.find(L"rtitle") != nameandvalues.end())
				rtitle = nameandvalues[L"rtitle"];
			if (nameandvalues.find(L"exe") != nameandvalues.end())
				exe = nameandvalues[L"exe"];
			if (nameandvalues.find(L"class") != nameandvalues.end())
				winclass = nameandvalues[L"class"];

			if (rtitle.empty() && exe.empty() && winclass.empty())
			{
				// both empty
				wstring message = I18S(L"'rtitle', 'exe' or 'class' must be specified.");
				errorMeesageAndQuit(message.c_str());
			}

			inargses[n].AddMainArg(rtitle, exe, winclass);
		}
		else if (isOption(arg, _T("-max"), &n))
		{ 
			if ((i + 1) == __argc)
			{
				errorMeesageAndQuit(I18S(_T("No argument for -pos")));
			}
			++i;
			arg = targv[i];
			wstring lookee = arg;
			if (!stdIsAsciiDigitString(lookee))
				errorMeesageAndQuit(I18S(L"Arugment for -max are not digits."));
			maxMove = _ttoi(lookee.c_str());
		}
		else if (
			lstrcmp(arg, _T("-h")) == 0 ||
			lstrcmp(arg, _T("/?")) == 0 ||
			lstrcmp(arg, _T("--help")) == 0 ||
			lstrcmp(arg, _T("-v")) == 0 ||
			lstrcmp(arg, _T("--version")) == 0 )
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
			wstring message = I18S(_T("Unknown option:"));
			message += arg;
			errorMeesageAndQuit(message.c_str());
		}
	}

	for (auto&& inA : inargses)
	{
		if (!inargses[inA.first].HasPostype() && 
			(0 == (inargses[inA.first].GetSizeTypeWidth() | inargses[inA.first].GetSizeTypeHeight())))
		{
			errorMeesageAndQuit(I18S(_T("No position specified.")));
		}
	}

	TOPWINVECTOR allwins;
	EnumWindows(EnumWindowsProc, (LPARAM)&allwins);

	vector<CINArgs> vInArgs = getInargsAsVector(inargses);
	set<vector<CINArgs>::iterator> processedVInargs;

	wstring processResults;
	int moveCount = 0;
	bool breaking = false;
	const bool oneByone = vInArgs.size() > 1;
	for (auto&& win : allwins)
	{
		bool oneByoneNow = false;
		if (breaking)
			break;
		for (vector<CINArgs>::iterator vIt = vInArgs.begin() ; vIt != vInArgs.end(); ++vIt)
		{
			if (breaking || oneByoneNow)
				break;

			for (size_t i = 0; i < vIt->length(); ++i)
			{
				if (processedVInargs.find(vIt) != processedVInargs.end())
					continue;
				// No exe == true 
				// OR
				// exe matches
				if (!vIt->HasExe(i) ||
					stdEndWith(
						stdStringUpper(win->GetPath()),
						stdStringUpper(vIt->GetExe(i)))
					)
				{
					// No reg
					// OR
					// title matches reg
					if (!vIt->HasRegTitle(i) ||
						(vbregMatch(getWindowTitle(win->GetHwnd()).c_str(), vIt->GetRegTitle(i).c_str())))
					{
						if (!vIt->HasClass(i) ||
							getWindowClassName(win->GetHwnd()) == vIt->GetClass(i))
						{
							RECT resultRect = { 0 };
							BOOL success = maniWindow(
								win->GetHwnd(),
								vIt->GetPostType(),
								vIt->GetSizeTypeWidth() | vIt->GetSizeTypeHeight(),
								vIt->GetCustomWidth(), vIt->GetCustomHeight(),
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

							moveCount++;
							if (maxMove >= 0 && moveCount >= maxMove)
							{
								breaking = true;
								break;
							}
							if (oneByone)
							{
								oneByoneNow = true;
								processedVInargs.insert(vIt);
								break;
							}
						}
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



