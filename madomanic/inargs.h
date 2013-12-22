#pragma once

class CINArgs
{
	MOVEWINDOW_POS* postype_;
	DWORD* sizetypeWidth_;
	DWORD* sizetypeHeight_;
	tstring* mainarg_;
	tstring* regtitle_;
public:
	CINArgs()
	{
		postype_ = NULL;
		sizetypeWidth_ = NULL;
		sizetypeHeight_ = NULL;
		mainarg_ = NULL;
		regtitle_ = NULL;
	}
	~CINArgs()
	{
		delete postype_;
		delete sizetypeWidth_;
		delete sizetypeHeight_;
		delete mainarg_;
		delete regtitle_;
	}

	bool HasPostype() const {
		return postype_ != NULL;
	}
	void SetPostype(MOVEWINDOW_POS pos) {
		DASSERT(!postype_);
		postype_ = new MOVEWINDOW_POS;
		*postype_ = pos;
	}
	void argprocessWidth(int& i, const int argc, LPTSTR*& argv, LPCTSTR pError);
inargs.
};