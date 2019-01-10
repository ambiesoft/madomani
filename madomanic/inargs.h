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

class CINArgs
{
	MV_POS* postype_;
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
	MV_POS GetPostType() const {
		if (!postype_)
			return MV_POS::MV_POS_NONE;
		return *postype_;
	}
	void SetPostype(MV_POS pos) {
		DASSERT(!postype_);
		postype_ = new MV_POS;
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