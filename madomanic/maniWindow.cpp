#include "stdafx.h"

#include "../../MyUtility/tstring.h"
#include "../../MyUtility/GetWorkingArea.h"

#include "madomanic.h"

BOOL maniWindow(HWND hwnd, MOVEWINDOW_POS postype, MOVEWINDOW_SIZE sizetype)
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





	if(sizetype & MOVEWINDOW_SIZE_MAXWIDTH)
	{
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_HALFWIDTH));
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_3RDWIDTH));
		targetWidth = rcWork.right - rcWork.left;
	}
	if(sizetype & MOVEWINDOW_SIZE_HALFWIDTH)
	{
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_MAXWIDTH));
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_3RDWIDTH));
		targetWidth = (rcWork.right - rcWork.left)/2;
	}
	if(sizetype & MOVEWINDOW_SIZE_3RDWIDTH)
	{
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_MAXWIDTH));
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_HALFWIDTH));
		targetWidth = (rcWork.right - rcWork.left)/3;
	}


	if(sizetype & MOVEWINDOW_SIZE_MAXHEIGHT)
	{
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_HALFHEIGHT));
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_3RDHEIGHT));
		targetHeight = rcWork.bottom - rcWork.top;
	}
	if(sizetype & MOVEWINDOW_SIZE_HALFHEIGHT)
	{
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_MAXHEIGHT));
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_3RDHEIGHT));
		targetHeight = (rcWork.bottom - rcWork.top)/2;
	}
	if(sizetype & MOVEWINDOW_SIZE_3RDHEIGHT)
	{
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_MAXHEIGHT));
		DASSERT(!(sizetype & MOVEWINDOW_SIZE_HALFHEIGHT));
		targetHeight = (rcWork.bottom - rcWork.top)/3;
	}

	rcWin.right = rcWin.left + targetWidth;
	rcWin.bottom = rcWin.top + targetHeight;





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
		targetPos.y = rcWork.top; // screenRect.Location.Y;
		break;
	case MOVEWINDOW_POS_BOTTOMLEFT:
		targetPos.x = rcWork.left;// screenRect.Location.X;
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top); // screenRect.Bottom - curSize.Height;
		break;
	case MOVEWINDOW_POS_BOTTOMRIGHT:
		targetPos.x = rcWork.right - (rcWin.right - rcWin.left);// screenRect.Right - curSize.Width;
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top); // screenRect.Bottom - curSize.Height;
		break;
	case MOVEWINDOW_POS_CENTER:

	default:
		DASSERT(false);
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


