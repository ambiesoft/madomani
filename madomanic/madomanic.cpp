#include "stdafx.h"


#include "../../MyUtility/GetFileNameFromHwnd.h"
#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"
#include "../../MyUtility/stringEndwith.h"
#include "../../MyUtility/vbregexp.h"
#include "../../MyUtility/getWindowTstring.h"

#include "madomanic.h"




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

void argprocessWidthHeight(const bool iswidth, int& i, const int argc, LPTSTR*& argv, DWORD *pST, LPCTSTR pError)
{
	tstring message;
	if(*pST)
	{
		message = pError;
		message += I18S(_T(" : size already set"));
		errorMeesageAndQuit(message.c_str());
	}
	if( (i+1)== argc )
	{
		message = I18S(_T("No argument for "));
		message += pError; 
		errorMeesageAndQuit(message.c_str());
	}
	++i;
	LPCTSTR arg = argv[i];
	if(lstrcmp(arg, _T("max"))==0)
	{
		if(iswidth)
			*pST = MOVEWINDOW_SIZE_MAXWIDTH;
		else
			*pST = MOVEWINDOW_SIZE_MAXHEIGHT;
	}
	else if(lstrcmp(arg, _T("half"))==0)
	{
		if(iswidth)
			*pST = MOVEWINDOW_SIZE_HALFWIDTH;
		else
			*pST = MOVEWINDOW_SIZE_HALFHEIGHT;
	}
	else
	{
		tstring t= arg;
		t+= _T(" : ");
		t+= I18S(_T("Invalid argument for "));
		t+= pError;
		errorMeesageAndQuit(t.c_str());
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	MOVEWINDOW_POS postype = MOVEWINDOW_POS_NONE;
	DWORD sizetypeWidth = 0;
	DWORD sizetypeHeight = 0;
	LPCTSTR mainarg = NULL;
	LPCTSTR regtitle = NULL;
	// -pos bottomleft -width max AcroRd32.exe
	// -pos bottomright -width half -height max AcroRd32.exe
	// -pos bottomleft firefox.exe -rtitle " - Mozilla Firefox$"
	// -pos topright larmoji.exe
	// -pos bottomright iexplore.exe -rtitle " - Windows Internet Explorer$"
	// -pos topleft mdie.exe -rtitle "^MDIE"
	for(int i=1 ; i < __argc ; ++i)
	{
		LPCTSTR arg = targv[i];
		if(lstrcmp(arg, _T("-pos"))==0)
		{
			if(postype)
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
				postype = MOVEWINDOW_POS_TOPLEFT;
			}
			else if(lstrcmp(arg, _T("bottomleft"))==0)
			{
				postype = MOVEWINDOW_POS_BOTTOMLEFT;
			}
			else if(lstrcmp(arg, _T("topright"))==0)
			{
				postype = MOVEWINDOW_POS_TOPRIGHT;
			}
			else if(lstrcmp(arg, _T("bottomright"))==0)
			{
				postype = MOVEWINDOW_POS_BOTTOMRIGHT;
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
			argprocessWidthHeight(true, i, __argc, targv, &sizetypeWidth, arg);
		}
		else if(lstrcmp(arg, _T("-height"))==0)
		{
			argprocessWidthHeight(false, i, __argc, targv, &sizetypeHeight, arg);
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
		else
		{
			if(mainarg)
			{
				LPTSTR pMessage = (LPTSTR)malloc( (lstrlen(mainarg) + 128)*sizeof(TCHAR));
				wsprintf(pMessage, I18S(_T("Main arg \"%s\" already set.")), mainarg);
				errorMeesageAndQuit(pMessage);
			}
			mainarg = arg;
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



