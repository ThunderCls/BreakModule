#pragma once

#include <windows.h>
#include "pluginmain.h"

//functions
_di_IXMLNode FindNodeByAttribute(_di_IXMLNodeList nodeList, char *attr_name, char *value, int *index = NULL);
void GetModulesData();
bool cbSetModules(int argc, char* argv[]);
void ShowAboutForm();
void OnBreakpoint(PLUG_CB_BREAKPOINT* bpInfo);
void OnLoadModule(PLUG_CB_LOADDLL *cbInfo);
void OnStopDbg();
void OnInitDbg(PLUG_CB_INITDEBUG* info);

