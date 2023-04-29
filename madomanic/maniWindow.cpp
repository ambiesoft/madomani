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

#include "../../lsMisc/GetWorkingArea.h"

#include "madomanic.h"

BOOL maniWindow(HWND hwnd, MV_POS postype, MV_SIZE sizetype, int cw, int ch, bool bRestoreWindow, RECT& resultRect)
{
	RECT rcWork;
	if(!GetWorkingArea(hwnd, &rcWork))
		return FALSE;

	RECT rcWin;
	if(!GetWindowRect(hwnd, &rcWin))
		return FALSE;

	POINT targetPos;
	targetPos.x = rcWin.left;
	targetPos.y = rcWin.top;

	int targetWidth = rcWin.right - rcWin.left;
	int targetHeight = rcWin.bottom - rcWin.top;





	if(sizetype & MV_SIZE_MAXWIDTH)
	{
		DASSERT(!(sizetype & MV_SIZE_HALFWIDTH));
		DASSERT(!(sizetype & MV_SIZE_THIRD_WIDTH));
		DASSERT(!(sizetype & MV_SIZE_FOURTH_WIDTH ));
		targetWidth = rcWork.right - rcWork.left;
	}
	if(sizetype & MV_SIZE_HALFWIDTH)
	{
		DASSERT(!(sizetype & MV_SIZE_MAXWIDTH));
		DASSERT(!(sizetype & MV_SIZE_THIRD_WIDTH));
		DASSERT(!(sizetype & MV_SIZE_FOURTH_WIDTH));
		targetWidth = (rcWork.right - rcWork.left)/2;
	}
	if (sizetype & MV_SIZE_THIRD_WIDTH)
	{
		DASSERT(!(sizetype & MV_SIZE_MAXWIDTH));
		DASSERT(!(sizetype & MV_SIZE_HALFWIDTH));
		DASSERT(!(sizetype & MV_SIZE_FOURTH_WIDTH));
		targetWidth = (rcWork.right - rcWork.left) / 3;
	}
	if (sizetype & MV_SIZE_FOURTH_WIDTH)
	{
		DASSERT(!(sizetype & MV_SIZE_MAXWIDTH));
		DASSERT(!(sizetype & MV_SIZE_HALFWIDTH));
		DASSERT(!(sizetype & MV_SIZE_THIRD_WIDTH));
		targetWidth = (rcWork.right - rcWork.left) / 4;
	}


	if(sizetype & MV_SIZE_MAXHEIGHT)
	{
		DASSERT(!(sizetype & MV_SIZE_HALFHEIGHT));
		DASSERT(!(sizetype & MV_SIZE_THIRD_HEIGHT));
		DASSERT(!(sizetype & MV_SIZE_FOURTH_HEIGHT ));
		targetHeight = rcWork.bottom - rcWork.top;
	}
	if(sizetype & MV_SIZE_HALFHEIGHT)
	{
		DASSERT(!(sizetype & MV_SIZE_MAXHEIGHT));
		DASSERT(!(sizetype & MV_SIZE_THIRD_HEIGHT));
		DASSERT(!(sizetype & MV_SIZE_FOURTH_HEIGHT));
		targetHeight = (rcWork.bottom - rcWork.top)/2;
	}
	if (sizetype & MV_SIZE_THIRD_HEIGHT)
	{
		DASSERT(!(sizetype & MV_SIZE_MAXHEIGHT));
		DASSERT(!(sizetype & MV_SIZE_HALFHEIGHT));
		DASSERT(!(sizetype & MV_SIZE_FOURTH_HEIGHT));
		targetHeight = (rcWork.bottom - rcWork.top) / 3;
	}
	if (sizetype & MV_SIZE_FOURTH_HEIGHT)
	{
		DASSERT(!(sizetype & MV_SIZE_MAXHEIGHT));
		DASSERT(!(sizetype & MV_SIZE_HALFHEIGHT));
		DASSERT(!(sizetype & MV_SIZE_THIRD_HEIGHT));
		targetHeight = (rcWork.bottom - rcWork.top) / 4;
	}

	
	
	if (sizetype & (MV_SIZE_CUSTOMWIDTH))
	{
		targetHeight = cw;
	}
	if (sizetype & MV_SIZE_CUSTOMHEIGHT)
	{
		targetHeight = ch;
	}

	rcWin.right = rcWin.left + targetWidth;
	rcWin.bottom = rcWin.top + targetHeight;





	switch(postype)
	{
	case MV_POS_NONE:
		break;
	case MV_POS_TOPLEFT:
		targetPos.x = rcWork.left;
		targetPos.y = rcWork.top;
		break;
	case MV_POS_TOPCENTER:
		targetPos.x = (rcWork.right - (rcWin.right-rcWin.left))/2;
		targetPos.y = rcWork.top;
		break;
	case MV_POS_TOPRIGHT:
		targetPos.x = rcWork.right - (rcWin.right-rcWin.left);
		targetPos.y = rcWork.top;
		break;
	case MV_POS_CENTERRIGHT:
		targetPos.x = rcWork.right - (rcWin.right - rcWin.left);
		targetPos.y = (rcWork.bottom - (rcWin.bottom - rcWin.top))/2;
		break;
	case MV_POS_BOTTOMRIGHT:
		targetPos.x = rcWork.right - (rcWin.right - rcWin.left);
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top);
		break;
	case MV_POS_BOTTOMCENTER:
		targetPos.x =  (rcWork.right - (rcWin.right-rcWin.left))/2;
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top);
		break;



	
	case MV_POS_BOTTOMLEFT:
		targetPos.x = rcWork.left;// screenRect.Location.X;
		targetPos.y = rcWork.bottom - (rcWin.bottom - rcWin.top); // screenRect.Bottom - curSize.Height;
		break;
	case MV_POS_CENTERLEFT:
		targetPos.x = rcWork.left;// screenRect.Location.X;
		targetPos.y = (rcWork.bottom - (rcWin.bottom - rcWin.top))/2; // screenRect.Bottom - curSize.Height;
		break;

	case MV_POS_CENTER:

	default:
		DASSERT(false);
		return FALSE;
		
	}

	// return value
	resultRect.top = targetPos.y;
	resultRect.left = targetPos.x;
	resultRect.bottom = resultRect.top + targetHeight;
	resultRect.right = resultRect.left + targetWidth;

	if (bRestoreWindow)
	{
		if (IsIconic(hwnd) || IsZoomed(hwnd))
			ShowWindow(hwnd, SW_RESTORE);
	}
	else
	{
		if (IsIconic(hwnd) || IsZoomed(hwnd))
			return false;
	}
	return SetWindowPos(hwnd, 
		NULL, 
		targetPos.x, 
		targetPos.y, 
		targetWidth,
		targetHeight,
		SWP_NOACTIVATE |
		(postype==MV_POS_NONE ? SWP_NOMOVE : 0) | 
		(sizetype==MV_SIZE_NONE ? SWP_NOSIZE : 0) |
		SWP_NOZORDER);
}


