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
#include "madomanic.h"
#include "inargs.h"
#include "helper.h"

bool isStringDigit(const wstring& str)
{
	for (TCHAR t : str)
	{
		if (!_istdigit(t))
			return false;
	}
	return true;
}
void CINArgs::argprocessHeight(int& i, const int argc, LPTSTR*& argv, LPCTSTR pError)
{
	argprocessWH(false, i, argc, argv, pError);
}
void CINArgs::argprocessWidth(int& i, const int argc, LPTSTR*& argv, LPCTSTR pError)
{
	argprocessWH(true, i, argc, argv, pError);
}
void CINArgs::argprocessWH(bool bWidth, int& i, const int argc, LPTSTR*& argv, LPCTSTR pError)
{
	wstring message;
	DWORD*& target = bWidth ? sizetypeWidth_ : sizetypeHeight_;
	int& customtarget = bWidth ? sizeWidthCustom_ : sizeHeightCustom_;
	if (target != NULL)
	{
		message = pError;
		message += I18S(_T(" : size already set"));
		errorMeesageAndQuit(message.c_str());
	}
	if( (i+1)== argc )
	{
		message = I18S(_T("No argument for "));
		message += pError; 
		errorMeesageAndQuit(message.c_str());
	}
	target = new DWORD;
	++i;
	LPCTSTR arg = argv[i];
	if(lstrcmp(arg, _T("max"))==0)
	{
		*target = bWidth ? MV_SIZE_MAXWIDTH : MV_SIZE_MAXHEIGHT;
	}
	else if (lstrcmp(arg, _T("half")) == 0)
	{
		*target = bWidth ? MV_SIZE_HALFWIDTH : MV_SIZE_HALFHEIGHT;
	}
	else if (lstrcmp(arg, _T("3rd")) == 0)
	{
		*target = bWidth ? MV_SIZE_THIRD_WIDTH : MV_SIZE_THIRD_HEIGHT;
	}
	else if (lstrcmp(arg, _T("4th")) == 0)
	{
		*target = bWidth ? MV_SIZE_FOURTH_WIDTH : MV_SIZE_FOURTH_HEIGHT;
	}
	else
	{
		if (isStringDigit(arg))
		{
			int custom = _ttoi(arg);
			if (custom < 0)
				errorMeesageAndQuit(I18S(_T("Size can not be minus value.")));

			*target = bWidth ? MV_SIZE_CUSTOMWIDTH : MV_SIZE_CUSTOMHEIGHT;
			customtarget = custom;
		}
		else
		{
			wstring t = arg;
			t += _T(" : ");
			t += I18S(_T("Invalid argument for "));
			t += pError;
			errorMeesageAndQuit(t.c_str());
		}
	}
}
