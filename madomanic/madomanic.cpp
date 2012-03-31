#include "stdafx.h"


#include "../../MyUtility/GetFileNameFromHwnd.h"
#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"
#include "../../MyUtility/stringEndwith.h"
#include "../../MyUtility/vbregexp.h"

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

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	MOVEWINDOW_POS postype = MOVEWINDOW_POS_NONE;
	MOVEWINDOW_SIZE sizetype = 0;
	LPCTSTR mainarg = NULL;
	LPCTSTR regtitle = NULL;
	// -pos bottomleft -size maxwidth AcroRd32.exe
	// -pos bottomleft firefox.exe -rtitle " - Mozilla Firefox$"
	// -pos topright larmoji.exe
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
			if(lstrcmp(arg, _T("bottomleft"))==0)
			{
				postype = MOVEWINDOW_POS_BOTTOMLEFT;
			}
			else if(lstrcmp(arg, _T("topright"))==0)
			{
				postype = MOVEWINDOW_POS_TOPRIGHT;
			}
			else
			{
				tstring t= arg;
				t+= _T(" : ");
				t+= I18S(_T("Invalid argument for -pos"));
				errorMeesageAndQuit(t.c_str());
			}
		}
		else if(lstrcmp(arg, _T("-size"))==0)
		{
			if(sizetype)
			{
				errorMeesageAndQuit(I18S(_T("-size : size already set")));
			}
			if( (i+1)==__argc )
			{
				errorMeesageAndQuit(I18S(_T("No argument for -size")));
			}
			++i;
			arg = targv[i];
			if(lstrcmp(arg, _T("maxwidth"))==0)
			{
				sizetype = MOVEWINDOW_SIZE_MAXWIDTH;
							// MOVEWINDOW_SIZE_HALFHEIGHT;
			}
			else
			{
				tstring t= arg;
				t+= _T(" : ");
				t+= I18S(_T("Invalid argument for -size"));
				errorMeesageAndQuit(t.c_str());
			}
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
				TCHAR t[1024];
				t[0]=0;
				GetWindowText((*it)->GetHwnd(), t, countof(t));
				if(!vbregMatch(t, regtitle))
					continue;
			}
			maniWindow(
				(*it)->GetHwnd(), 
				postype, // MOVEWINDOW_POS_BOTTOMLEFT, 
				sizetype);
			return 0;
		}
	}
	return 0;
}



