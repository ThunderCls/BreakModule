#pragma once
#include "pluginmain.h"

enum
{
	MENU_SET_MODULES,
	MENU_ABOUT,
};

//functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
bool pluginStop();
void pluginSetup();
