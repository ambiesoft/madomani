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

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>

#include <assert.h>
#include <crtdbg.h>

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <map>

#include "../../lsMisc/GetFileNameFromHwnd.h"
#include "../../lsMisc/GetWorkingArea.h"
#include "../../lsMisc/vbregexp.h"
#include "../../lsMisc/getWindowString.h"
#include "../../lsMisc/stdosd/stdosd.h"

using namespace std;

#define countof(a) (sizeof(a)/sizeof(a[0]))




#if _DEBUG
#pragma warning(disable:4291)
#define malloc(size) _malloc_dbg(size, _NORMAL_BLOCK, __FILE__, __LINE__ )
#define calloc(s1,s2) _calloc_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__ )
#define realloc(p,s) _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define free(p)  _free_dbg(p, _NORMAL_BLOCK)
inline void* operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
{
	return _malloc_dbg(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}
inline void operator delete(void *p)
{
	_free_dbg(p, _NORMAL_BLOCK);
}
#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#if defined(_DEBUG) || defined(_RELEASE)
#define DASSERT(s) assert(!!(s))
inline void DTRACE(LPCTSTR s) { OutputDebugString(s); }
#define DTRACE_NUMBER(start) do { static int num = start; DTRACE(num.ToString()); ++num; } while(0);
#define DTRACE_NUMBERTEXT(start,text) do { static int num = start; DTRACE(num.ToString() + ":" + text); ++num; } while(0);
#define DVERIFY DASSERT
#define DVERIFY_IS(a,b)  DASSERT( (a)==(b) )
#define DVERIFY_NOT(a,b) DASSERT( (a)!=(b) )
#define DVERIFY_GL(a) do { DASSERT( (a) ); DWORD gle = GetLastError(); if ( gle!=0 ) { DASSERT(gle || 0); } } while(0)
#define DVERIFY_GL_NUM(a,n) do { DASSERT( (a) ); DWORD gle = GetLastError(); if ( gle!=n ) { DASSERT( gle || 0); } } while(0)
#define DVERIFY_GL_NUM2(a,n1, n2) do { DASSERT( (a) ); DWORD gle = GetLastError(); if ( gle!=n1 && gle!= n2) { DTRACE(gle.ToString()); DASSERT( gle || 0); } } while(0)
#define DASSERT_IS_CLASS(instance, clazz) DASSERT( ((instance)->GetType())==clazz::typeid ) 
#define DASSERT_IS_CLASS_OR_NULL(instance, clazz) DASSERT( instance==nullptr || ((instance)->GetType())==clazz::typeid ) 
#define DASSERT_IS_DERIVED(instance, clazz) DASSERT(isDerived(instance, clazz::typeid))
#else
#define DASSERT(s) ((void)0)
#define DTRACE(s) ((void)0)
#define DTRACE_NUMBER(start) ((void)0)
#define DTRACE_NUMBERTEXT(start,text) ((void)0)
#define DVERIFY(a) (a)
#define DVERIFY_IS(a,b)  (a)
#define DVERIFY_NOT(a,b) (a)
#define DVERIFY_GL(a) (a)
#define DVERIFY_GL_NUM(a,n) (a)
#define DVERIFY_GL_NUM2(a,n1, n2) (a)
#define DASSERT_IS_CLASS(instance, clazz) ((void)0)
#define DASSERT_IS_CLASS_OR_NULL(instance, clazz) ((void)0)
#define DASSERT_IS_DERIVED(instance, clazz) ((void)0)
#endif

#ifdef _UNICODE
#define targv __wargv
#else
#define targv __argv
#endif

#define I18S(t) (t) 
#define APP_NAME _T("madomani")
#define APP_VERSION _T("2.0.1")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
