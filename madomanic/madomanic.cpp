#include "stdafx.h"
#include <tchar.h>

#include "../../MyUtility/GetFileNameFromHwnd.h"
#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"

#include "madomanic.h"

BOOL movewinto(HWND hwnd, MOVEWINDOW_POS postype, MOVEWINDOW_SIZE sizetype)
{
	RECT rcWork;
	if(!GetWorkingArea(hwnd, &rcWork))
		return FALSE;

	RECT rcWin;
	if(!GetWindowRect(hwnd, &rcWin))
		return FALSE;

	POINT targetPos;
	int targetWidth = rcWin.right - rcWin.left;
	int targetHeight = rcWin.bottom - rcWin.top;

	switch(postype)
	{
	case MOVEWINDOW_POS_NONE:
		break;
	case MOVEWINDOW_POS_TOPLEFT:
		targetPos.x = rcWork.left;// screenRect.Location;
		targetPos.y = rcWork.top;
		break;
	case MOVEWINDOW_POS_TOPRIGHT:
		targetPos.x = rcWork.right - (rcWin.right-rcWin.left); // screenRect.Right - curSize.Width;
		targetPos.y = rcWork.bottom; // screenRect.Location.Y;
		break;
	case MOVEWINDOW_POS_BOTTOMLEFT:
		targetPos.x = rcWork.left;// screenRect.Location.X;
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top); // screenRect.Bottom - curSize.Height;
		break;
	case MOVEWINDOW_POS_BOTTOMRIGHT:
		targetPos.x = rcWork.right - (rcWin.right - rcWin.left);// screenRect.Right - curSize.Width;
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top); // screenRect.Bottom - curSize.Height;
		break;

	default:
		// DASSERT(false);
		return FALSE;
		
	}

	switch(sizetype)
	{
	case MOVEWINDOW_SIZE_NONE:
		break;
	
	case MOVEWINDOW_SIZE_MAXWIDTH:
		targetWidth = rcWork.right - rcWork.left;
		break;
	case MOVEWINDOW_SIZE_MAXHEIGHT:
		targetHeight = rcWork.bottom - rcWork.top;
		break;

	default:
		// DASSERT(false);
		return FALSE;
	}

	return SetWindowPos(hwnd, 
		NULL, 
		targetPos.x, 
		targetPos.y, 
		targetWidth,
		targetHeight,
		SWP_NOACTIVATE |
		(postype==MOVEWINDOW_POS_NONE ? SWP_NOMOVE : 0) | 
		(sizetype==MOVEWINDOW_SIZE_NONE ? SWP_NOSIZE : 0) |
		SWP_NOZORDER);
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TOPWINVECTOR& allwins = *( (TOPWINVECTOR*)lParam );
	TCHAR szT[1024];
	if(IsWindowVisible(hwnd) && GetFileNameFromHwnd(hwnd, szT, countof(szT)-1)))
	{
		allwins.push_back(new CTopWinInfo(hwnd, szT));
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
			_T("firefox.exe"))
			)
		{
//			movewinto((*it)->GetHwnd(), MOVEWINDOW_POS_BOTTOMLEFT, MOVEWINDOW_SIZE_NONE);
			movewinto((*it)->GetHwnd(), MOVEWINDOW_POS_BOTTOMLEFT, MOVEWINDOW_SIZE_MAXWIDTH);
			return 0;
		}
	}
	return 0;
}



