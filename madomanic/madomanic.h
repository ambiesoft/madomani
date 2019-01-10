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

#pragma once

#define MV_SIZE DWORD
#define MV_SIZE_NONE		0

#define MV_SIZE_MAXWIDTH		(1<<0)
#define MV_SIZE_MAXHEIGHT		(1<<1)
#define MV_SIZE_HALFWIDTH		(1<<2)
#define MV_SIZE_HALFHEIGHT		(1<<3)
#define MV_SIZE_THIRD_WIDTH		(1<<4)
#define MV_SIZE_THIRD_HEIGHT	(1<<5)
#define MV_SIZE_FOURTH_WIDTH	(1<<6)
#define MV_SIZE_FOURTH_HEIGHT	(1<<7)
#define MV_SIZE_CUSTOMWIDTH		(1<<8)
#define MV_SIZE_CUSTOMHEIGHT	(1<<9)




//#define MW_SIZE_4THWIDTH 111
//#define MV_SIZE_FORTH_WIDTH		(1<<6)




class CTopWinInfo
{
	HWND h_;
	tstring path_;
	UINT order_;
public:
	CTopWinInfo(HWND h, LPCTSTR path, UINT o)
	{
		h_=h;
		path_=path;
		order_=o;
	}
	LPCTSTR GetPath() const {
		return path_.c_str();
	}
	HWND GetHwnd() const {
		return h_;
	}
};

typedef vector<CTopWinInfo*> TOPWINVECTOR;
enum MV_POS
{
	MV_POS_NONE = 0,
	
	MV_POS_TOPLEFT,
	MV_POS_TOPCENTER,
	MV_POS_TOPRIGHT,

	MV_POS_CENTERRIGHT,
	MV_POS_BOTTOMRIGHT,
	MV_POS_BOTTOMCENTER,
	MV_POS_BOTTOMLEFT,

	MV_POS_CENTERLEFT,
	
	MV_POS_CENTER,
};



BOOL maniWindow(HWND hwnd, MV_POS postype, MV_SIZE sizetype, int cw, int ch);