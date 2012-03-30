
class CTopWinInfo
{
	HWND h_;
	tstring path_;
public:
	CTopWinInfo(HWND h, LPCTSTR path)
	{
		h_=h;
		path_=path;
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

enum MOVEWINDOW_SIZE
{
	MOVEWINDOW_SIZE_NONE,
	MOVEWINDOW_SIZE_MAXWIDTH,
	MOVEWINDOW_SIZE_MAXHEIGHT,
};
