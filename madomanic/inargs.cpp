#include "stdafx.h"
#include "madomanic.h"
#include "inargs.h"
#include "helper.h"

bool isStringDigit(const tstring& str)
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
	tstring message;
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
			tstring t = arg;
			t += _T(" : ");
			t += I18S(_T("Invalid argument for "));
			t += pError;
			errorMeesageAndQuit(t.c_str());
		}
	}
}
