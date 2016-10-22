#pragma once

#include <windows.h>
#include "pluginmain.h"

/*variables*/
const wchar_t *x32dbg_module = L".\\x32dbg.dll";

/*functions*/
void GetDllFunctions();

/* global functions pointers*/
//---------------------------------------------------------------------------
typedef duint (__cdecl *_DebugSetBreakpoint)(
	duint
);

typedef bool (__cdecl *_DebugDeleteBreakpoint)(
	duint address
);

typedef duint (__cdecl *_ModuleEntryFromName)(
	const char* name
);

extern _DebugSetBreakpoint DebugSetBreakpoint;
extern _DebugDeleteBreakpoint DebugDeleteBreakpoint;
extern _ModuleEntryFromName ModuleEntryFromName;
