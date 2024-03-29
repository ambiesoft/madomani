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

	// Input files
	std::vector<tuple<wstring, wstring, wstring> > mainargs_;

	void argprocessWH(bool bWidth, int& i, const int argc, LPTSTR*& argv, LPCTSTR pError);

public:
	CINArgs()
	{
		postype_ = NULL;
		sizetypeWidth_ = NULL;
		sizetypeHeight_ = NULL;

		sizeWidthCustom_ = 0;
		sizeHeightCustom_ = 0;
	}
	CINArgs(const CINArgs& that) {
		if (that.postype_) 
		{
			this->postype_ = new MV_POS;
			*this->postype_ = *that.postype_;
		}
		else {
			this->postype_ = NULL;
		}

		if (that.sizetypeWidth_)
		{
			this->sizetypeWidth_ = new DWORD;
			*this->sizetypeWidth_ = *that.sizetypeWidth_;
		}
		else
		{
			this->sizetypeWidth_ = NULL;
		}

		if (that.sizetypeHeight_)
		{
			this->sizetypeHeight_ = new DWORD;
			*this->sizetypeHeight_ = *that.sizetypeHeight_;
		}
		else
		{
			this->sizetypeHeight_ = NULL;
		}

		this->sizeWidthCustom_ = that.sizeWidthCustom_;
		this->sizeHeightCustom_ = that.sizeHeightCustom_;

		this->mainargs_ = that.mainargs_;
	}
	~CINArgs()
	{
		delete postype_;
		delete sizetypeWidth_;
		delete sizetypeHeight_;
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

	bool HasRegTitle(size_t i) const {
		return !std::get<0>(mainargs_[i]).empty();
	}
	const wstring& GetRegTitle(size_t i) const {
		return std::get<0>(mainargs_[i]);
	}

	bool HasExe(size_t i) const {
		return !std::get<1>(mainargs_[i]).empty();
	}
	const wstring& GetExe(size_t i) const {
		return std::get<1>(mainargs_[i]);
	}

	bool HasClass(size_t i) const {
		return !std::get<2>(mainargs_[i]).empty();
	}
	const wstring& GetClass(size_t i) const {
		return std::get<2>(mainargs_[i]);
	}

	size_t length() const {
		return mainargs_.size();
	}
	void AddMainArg(const wstring& rtitle, const wstring& exe, const wstring& winclass) {
		mainargs_.push_back(tuple<wstring, wstring, wstring>(rtitle, exe, winclass));
	}
};