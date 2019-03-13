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

#include "StdAfx.h"
#include "helper.h"

void errorMeesageAndQuit(LPCTSTR pMessage, int returnvalue)
{
	MessageBox(NULL, pMessage, APP_NAME, MB_ICONERROR);
	exit(returnvalue);
}

void showhelp()
{

	MessageBox(NULL,
		L"madomanic : Move windows to specified positon\r\n\r\n"
		_T("Usage:\n")
		LR"(madomanic -target="rtitle=<regex>,exe=<executable>" [-target=...]...)" L"\r\n"
		_T("[-width <max | half | 3rd | 4th | <AnyPixcels>] \r\n")
		_T("[-height <max | half | 3rd | 4th | <AnyPixcels>] \r\n")
		_T("[-pos <topleft | topcenter | topright | centerright | bottomright | bottomcenter | bottomleft | centerleft | center>] \r\n")
		_T("[-h] [-g] [-r] \r\n\r\n")

		L"Specify a window by regex and executable, regex is used to filter windows by its tilte and executable by its path.\t\n"
		L"'-g' restores the window if it is iconized or zoomed.\r\n"
		L"'-r' show the result of the operation.\r\n"
		L"\r\n"

		L"Ex:\r\n"
		LR"(-pos topleft -height max -width half -target="rtitle=,exe=AcroRd32.exe" -target="rtitle=,exe=FOXITREADER.EXE")"

		L"",

		APP_NAME _T(" ") APP_VERSION,
		MB_ICONINFORMATION
		);
}