#include "stdafx.h"


#include "../../MyUtility/GetFileNameFromHwnd.h"
#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"

#include "madomanic.h"


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	static UINT oi;
	TOPWINVECTOR& allwins = *( (TOPWINVECTOR*)lParam );
	TCHAR szT[1024];
	if(IsWindowVisible(hwnd) && GetFileNameFromHwnd(hwnd, szT, countof(szT)-1)))
	{
		allwins.push_back(new CTopWinInfo(hwnd, szT, ++oi));
	}
	return TRUE;
}

BOOL stringendwith(LPCTSTR pString, LPCTSTR pEnd)
{
	if(!pString)
		return FALSE;

	if(!pEnd || pEnd[0]==0)
		return TRUE;

	size_t psize = lstrlen(pString);
	size_t endlen = lstrlen(pEnd);
	if(psize < endlen)
		return FALSE;

	LPCTSTR pS = pString;
	LPCTSTR pSS = pS + psize - endlen;
	while(*pEnd)
	{
		if(*pSS != *pEnd)
			return FALSE;

		++pSS;
		++pEnd;
	}
	return TRUE;
}

BOOL stringendwithi(LPCTSTR pString, LPCTSTR pEnd)
{
	if(!pString)
		return FALSE;

	if(!pEnd || pEnd[0]==0)
		return TRUE;

	LPTSTR pdup = _tcsdup(pString);
	_tcslwr(pdup);

	LPTSTR endup = _tcsdup(pEnd);
	_tcslwr(endup);

	BOOL ret = stringendwith(pdup, endup);
	free(pdup);
	free(endup);
	return ret;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	TOPWINVECTOR allwins;
	EnumWindows(EnumWindowsProc, (LPARAM)&allwins);

	for(TOPWINVECTOR::iterator it=allwins.begin() ; it != allwins.end() ; ++it)
	{
		if(stringendwithi( 
			(*it)->GetPath().c_str(),
			_T("AcroRd32.exe"))
			)
		{
//			maniWindow((*it)->GetHwnd(), MOVEWINDOW_POS_BOTTOMLEFT, MOVEWINDOW_SIZE_NONE);
			maniWindow(
				(*it)->GetHwnd(), 
				MOVEWINDOW_POS_BOTTOMLEFT, 
				MOVEWINDOW_SIZE_MAXWIDTH |
				MOVEWINDOW_SIZE_HALFHEIGHT);
			return 0;
		}
	}
	return 0;
}



