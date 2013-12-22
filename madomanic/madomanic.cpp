#include "stdafx.h"


#include "../../MyUtility/GetFileNameFromHwnd.h"
#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"
#include "../../MyUtility/stringEndwith.h"
#include "../../MyUtility/vbregexp.h"
#include "../../MyUtility/getWindowTstring.h"

#include "madomanic.h"
#include "inargs.h"





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

void errorMeesageAndQuit(LPCTSTR pMessage, int returnvalue = -1)
{
	MessageBox(NULL, pMessage, APP_NAME, MB_ICONERROR);
	exit(returnvalue);
}


void showhelp()
{
	MessageBox(NULL,
		_T("Usage:\n")
		_T("madomanic [-e executable|-E executablefull|-title <title>|-rtitle regextitle] ")
		_T("[-width <w>|-height <h>] ")
		_T("-pos <topleft|topcenter|topright|centerright|bottomright|bottomcenter|bottomleft|centerleft|center>"),
		_T("madomanic"),
		MB_ICONINFORMATION
		);
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{

	// -pos bottomleft -size maxwidth AcroRd32.exe // err
	// -pos bottomleft -width max AcroRd32.exe
	// -pos bottomright -width half -height max AcroRd32.exe
	// -pos bottomleft firefox.exe -rtitle " - Mozilla Firefox$"
	// -pos topright larmoji.exe
	// -pos bottomright iexplore.exe -rtitle " - Windows Internet Explorer$"
	// -pos topleft mdie.exe -rtitle "^MDIE"

	if(__argc==2 && lstrcmp(__targv[1],_T("-h"))==0)
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
				inargs.SetPostype(MOVEWINDOW_POS_TOPLEFT);
			}
			else if(lstrcmp(arg, _T("topcenter"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_TOPCENTER);
			}
			else if(lstrcmp(arg, _T("topright"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_TOPRIGHT);
			}
			else if(lstrcmp(arg, _T("centerright"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_CENTERRIGHT);
			}
			else if(lstrcmp(arg, _T("bottomright"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_BOTTOMRIGHT);
			}
			else if(lstrcmp(arg, _T("bottomcenter"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_BOTTOMCENTER);
			}
			else if(lstrcmp(arg, _T("bottomleft"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_BOTTOMLEFT);
			}
			else if(lstrcmp(arg, _T("centerleft"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_CENTERLEFT);
			}
			else if(lstrcmp(arg, _T("center"))==0)
			{
				inargs.SetPostype(MOVEWINDOW_POS_CENTER);
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
			if( (i+1)==__argc )
			{
				errorMeesageAndQuit(I18S(_T("No argument for -rtitle")));
			}
			++i;
			arg = targv[i];
			regtitle = arg;
		}
		else if(lstrcmp(arg, _T("-e"))==0)
		{
			if(mainarg)
			{
				LPTSTR pMessage = (LPTSTR)malloc( (lstrlen(mainarg) + 128)*sizeof(TCHAR));
				wsprintf(pMessage, I18S(_T("Main arg \"%s\" already set.")), mainarg);
				errorMeesageAndQuit(pMessage);
			}
			++i;
			mainarg = targv[i];
		}
	}
	TOPWINVECTOR allwins;
	EnumWindows(EnumWindowsProc, (LPARAM)&allwins);

	for(TOPWINVECTOR::iterator it=allwins.begin() ; it != allwins.end() ; ++it)
	{
		if(stringEndwithI( 
			(*it)->GetPath(),
			mainarg)
			)
		{
			if(regtitle)
			{
				tstring title = getWindowTstring((*it)->GetHwnd());
				if(!vbregMatch(title.c_str(), regtitle))
					continue;
			}
			maniWindow(
				(*it)->GetHwnd(), 
				postype, // MOVEWINDOW_POS_BOTTOMLEFT, 
				sizetypeWidth | sizetypeHeight);
			return 0;
		}
	}
	return 0;
}



