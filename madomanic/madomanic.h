
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
enum MOVEWINDOW_POS
{
	MOVEWINDOW_POS_NONE = 0,
	
	MOVEWINDOW_POS_TOPLEFT,
	MOVEWINDOW_POS_TOPCENTER,
	MOVEWINDOW_POS_TOPRIGHT,

	MOVEWINDOW_POS_CENTERRIGHT,
	MOVEWINDOW_POS_BOTTOMRIGHT,
	MOVEWINDOW_POS_BOTTOMCENTER,
	MOVEWINDOW_POS_BOTTOMLEFT,

	MOVEWINDOW_POS_CENTERLEFT,
	
	MOVEWINDOW_POS_CENTER,
};

#define MOVEWINDOW_SIZE DWORD
#define MOVEWINDOW_SIZE_NONE		0

#define MOVEWINDOW_SIZE_MAXWIDTH		(1<<0)
#define MOVEWINDOW_SIZE_MAXHEIGHT		(1<<1)
#define MOVEWINDOW_SIZE_HALFWIDTH		(1<<2)
#define MOVEWINDOW_SIZE_HALFHEIGHT		(1<<3)
#define MOVEWINDOW_SIZE_3RDWIDTH		(1<<4)
#define MOVEWINDOW_SIZE_3RDHEIGHT		(1<<5)
#define MOVEWINDOW_SIZE_CUSTOMWIDTH		(1<<6)
#define MOVEWINDOW_SIZE_CUSTOMHEIGHT	(1<<7)




BOOL maniWindow(HWND hwnd, MOVEWINDOW_POS postype, MOVEWINDOW_SIZE sizetype, int cw, int ch);