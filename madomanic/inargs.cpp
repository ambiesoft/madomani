#include "stdafx.h"
#include "madomanic.h"
#include "inargs.h"


void CINArgs::argprocessWidth(int& i, const int argc, LPTSTR*& argv, LPCTSTR pError)
{
	tstring message;
	if(sizetypeWidth_ != NULL)
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
	sizetypeWidth_ = new DWORD;
	++i;
	LPCTSTR arg = argv[i];
	if(lstrcmp(arg, _T("max"))==0)
	{
		*sizetypeWidth_ = MOVEWINDOW_SIZE_MAXWIDTH;
	}
	else if(lstrcmp(arg, _T("half"))==0)
	{
		*sizetypeWidth_ = MOVEWINDOW_SIZE_HALFWIDTH;
	}
	else
	{
		tstring t= arg;
		t+= _T(" : ");
		t+= I18S(_T("Invalid argument for "));
		t+= pError;
		errorMeesageAndQuit(t.c_str());
	}
}
