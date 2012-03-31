#include "stdafx.h"


#include "../../MyUtility/GetFileNameFromHwnd.h"
#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"
#include "../../MyUtility/stringEndwith.h"

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


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	TOPWINVECTOR allwins;
	EnumWindows(EnumWindowsProc, (LPARAM)&allwins);

	for(TOPWINVECTOR::iterator it=allwins.begin() ; it != allwins.end() ; ++it)
	{
		if(stringEndwithI( 
			(*it)->GetPath(),
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



