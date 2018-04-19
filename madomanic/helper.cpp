#include "StdAfx.h"
#include "helper.h"

void errorMeesageAndQuit(LPCTSTR pMessage, int returnvalue)
{
	MessageBox(NULL, pMessage, APP_NAME, MB_ICONERROR);
	exit(returnvalue);
}