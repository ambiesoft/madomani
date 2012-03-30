
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
	tstring GetPath() const {
		return path_;
	}
	HWND GetHwnd() const {
		return h_;
	}
};

typedef vector<CTopWinInfo*> TOPWINVECTOR;
enum MOVEWINDOW_POS
{
	MOVEWINDOW_POS_NONE,
	MOVEWINDOW_POS_TOPLEFT,
	MOVEWINDOW_POS_TOPRIGHT,
	MOVEWINDOW_POS_BOTTOMLEFT,
	MOVEWINDOW_POS_BOTTOMRIGHT,
};

#define MOVEWINDOW_SIZE DWORD
#define MOVEWINDOW_SIZE_NONE		0
#define MOVEWINDOW_SIZE_MAXWIDTH	(1<<0)
#define MOVEWINDOW_SIZE_HALFWIDTH	(1<<1)
#define MOVEWINDOW_SIZE_3RDWIDTH	(1<<2)
#define MOVEWINDOW_SIZE_MAXHEIGHT	(1<<3)
#define MOVEWINDOW_SIZE_HALFHEIGHT	(1<<4)
#define MOVEWINDOW_SIZE_3RDHEIGHT	(1<<5)


BOOL maniWindow(HWND hwnd, MOVEWINDOW_POS postype, MOVEWINDOW_SIZE sizetype);