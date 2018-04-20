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