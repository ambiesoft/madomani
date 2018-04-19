#pragma once

class CINArgs
{
	MOVEWINDOW_POS* postype_;
	DWORD* sizetypeWidth_;
	int sizeWidthCustom_;
	DWORD* sizetypeHeight_;
	int sizeHeightCustom_;

	tstring* mainarg_;
	tstring* regtitle_;

	void argprocessWH(bool bWidth, int& i, const int argc, LPTSTR*& argv, LPCTSTR pError);

public:
	CINArgs()
	{
		postype_ = NULL;
		sizetypeWidth_ = NULL;
		sizetypeHeight_ = NULL;
		mainarg_ = NULL;
		regtitle_ = NULL;

		sizeWidthCustom_ = 0;
		sizeHeightCustom_ = 0;
	}
	~CINArgs()
	{
		delete postype_;
		delete sizetypeWidth_;
		delete sizetypeHeight_;
		delete mainarg_;
		delete regtitle_;
	}
	int GetCustomWidth() const {
		return sizeWidthCustom_;
	}
	int GetCustomHeight() const {
		return sizeHeightCustom_;
	}
	DWORD GetSizeTypeWidth() const {
		if (!sizetypeWidth_)
			return 0;
		return *sizetypeWidth_;
	}
	DWORD GetSizeTypeHeight() const {
		if (!sizetypeHeight_)
			return 0;
		return *sizetypeHeight_;
	}
	bool HasPostype() const {
		return postype_ != NULL;
	}
	MOVEWINDOW_POS GetPostType() const {
		if (!postype_)
			return MOVEWINDOW_POS::MOVEWINDOW_POS_NONE;
		return *postype_;
	}
	void SetPostype(MOVEWINDOW_POS pos) {
		DASSERT(!postype_);
		postype_ = new MOVEWINDOW_POS;
		*postype_ = pos;
	}
	
	void argprocessWidth(int& i, const int argc, LPTSTR*& argv, LPCTSTR pError);
	void argprocessHeight(int& i, const int argc, LPTSTR*& argv, LPCTSTR pError);
	
	bool HasRegTitle() const {
		return regtitle_ != NULL;
	}
	tstring GetRegTitle() const {
		if (!regtitle_)
			return tstring();
		return *regtitle_;
	}
	void SetRegTitle(const tstring& t) {
		DASSERT(!regtitle_);
		regtitle_ = new tstring(t);
	}

	bool HasMainArg() const {
		return mainarg_ != NULL;
	}
	tstring GetMainArg() const {
		if (!mainarg_)
			return tstring();
		return *mainarg_;
	}
	void SetMainArg(const tstring& t) {
		DASSERT(!mainarg_);
		mainarg_ = new tstring(t);
	}
};