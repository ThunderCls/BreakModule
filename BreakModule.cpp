#include "BreakModule.h"
#include <windows.h>
#include <vcl.h>
#include <XMLDoc.hpp>
#include "frmMain.h"
#include "frmAbout.h"
#include "pluginmain.h"
#include "dll_link.h"
/*=============================================================================================*/
TList *lstBreakInfo;
//---------------------------------------------------------------------------
/* global functions pointers */
/* sample */
//---------------------------------------------------------------------------
_DebugSetBreakpoint DebugSetBreakpoint;
_DebugDeleteBreakpoint DebugDeleteBreakpoint;
_ModuleEntryFromName ModuleEntryFromName;
/*=============================================================================================*/

void GetModulesData()
{
	stBreakInfo *breakInfo;
	_di_IXMLDocument XML;
	_di_IXMLNode node;
	_di_IXMLNodeList nodeList;

	if(lstBreakInfo != NULL)
	{
		lstBreakInfo->Clear(); // clear the previous values

		// retrieve the config file
		XML = interface_cast<Xmlintf::IXMLDocument>(new TXMLDocument(NULL));
		XML->LoadFromFile(configFileName);

		node = XML->DocumentElement;
		nodeList = node->ChildNodes; // getting the list of executables
		// Find the current application info node
		node = FindNodeByAttribute(nodeList, "path", dExeName);
		if(node != NULL)
		{
			nodeList = node->ChildNodes; // getting the list of modules
			for (int i = 0; i < nodeList->Count; i++)
			{
				node = nodeList->Get(i);
				try
				{
					AnsiString name = node->Attributes["name"];
					AnsiString active = node->Attributes["active"];

					breakInfo = new stBreakInfo;
					ZeroMemory(breakInfo, sizeof(stBreakInfo));

					strcpy(breakInfo->module, name.c_str());
					strcpy(breakInfo->active, active.c_str());
					lstBreakInfo->Add(breakInfo);
				}catch(Exception *ex){
					ShowMessage(ex->Message);
				}
			}
		}
		else
		{
			// add new exe to the config file
			_di_IXMLNode exeNode;

			exeNode = XML->DocumentElement->AddChild("executable");
			exeNode->SetAttribute("path", dExeName);
			XML->SaveToFile(configFileName);
		}
	}
}
/*=============================================================================================*/

_di_IXMLNode FindNodeByAttribute(_di_IXMLNodeList nodeList, char *attr_name, char *value, int *index)
{
	for (int i = 0; i < nodeList->Count; i++)
	{
		if(nodeList->Get(i)->Attributes[attr_name] == String(value))
		{
			if(index != NULL) // in case index is required
				*index = i;

			return nodeList->Get(i);
		}
	}

	return NULL;
}
/*=============================================================================================*/

bool cbSetModules(int argc, char* argv[])
{
	// Create Form
	if(!MainFrm)
		MainFrm = new TMainFrm(NULL);

	MainFrm->lstBreakInfo = lstBreakInfo; // pass the list pointer to the class instance
	MainFrm->ShowModal();

	delete MainFrm;
	MainFrm = NULL;
    return true;
}
/*=============================================================================================*/

void ShowAboutForm()
{
	if(!AboutFrm)
		AboutFrm = new TAboutFrm(NULL);

	AboutFrm->ShowModal();
	delete AboutFrm;
	AboutFrm = NULL;
}
/*=============================================================================================*/

void OnBreakpoint(PLUG_CB_BREAKPOINT* bpInfo)
{
	stBreakInfo *breakInfo;

	for(int i = 0; i < lstBreakInfo->Count; i++)
	{
		breakInfo = (stBreakInfo*)lstBreakInfo->Items[i];
		if((strncmp(breakInfo->module, bpInfo->breakpoint->mod, MAX_MODULE_SIZE) == 0) &&
		   (bpInfo->breakpoint->addr == ModuleEntryFromName(bpInfo->breakpoint->mod)))
		{
			DebugDeleteBreakpoint(bpInfo->breakpoint->addr);
			break;
		}
	}
}
/*=============================================================================================*/

void OnLoadModule(PLUG_CB_LOADDLL *cbInfo)
{
	stBreakInfo *breakInfo;

	for(int i = 0; i < lstBreakInfo->Count; i++)
	{
		breakInfo = (stBreakInfo*)lstBreakInfo->Items[i];
		if(strncmp(breakInfo->module, cbInfo->modname, MAX_MODULE_SIZE) == 0 &&
		   strcmp(breakInfo->active, "true") == 0) // if the bp in the module is active
		{
			DebugSetBreakpoint(ModuleEntryFromName(cbInfo->modname));
			break;
		}
	}
}
/*=============================================================================================*/

void OnInitDbg(PLUG_CB_INITDEBUG* info)
{
	_di_IXMLDocument XML;
	_di_IXMLNode rootNode, exeNode;

	// get dinamic dll functions
	GetDllFunctions();
	// copy debugged exe name to global variable
	strncpy(dExeName, info->szFileName, strlen(info->szFileName));

	if(!FileExists(configFileName))
	{
		// create a blank xml config file
		XML = interface_cast<Xmlintf::IXMLDocument>(new TXMLDocument(NULL));
		XML->Active = true; // need to activate on new document
		XML->Version = "1.0";
		XML->Encoding = "UTF-8";
		XML->StandAlone = "no";
		XML->NodeIndentStr = "  ";
		XML->Options = XML->Options + (TXMLDocOptions() << doNodeAutoIndent);

		rootNode = XML->AddChild("data");
		exeNode = rootNode->AddChild("executable");
		exeNode->SetAttribute("path", dExeName);

		XML->SaveToFile(configFileName);
	}

	// create the global list of modules to break in
	if(lstBreakInfo == NULL)
		lstBreakInfo = new TList();

	GetModulesData(); // populate modules list
}
/*=============================================================================================*/

void OnStopDbg()
{
	// delete the global list of modules to break in
	if(lstBreakInfo != NULL)
	{
		lstBreakInfo->Clear();
		delete lstBreakInfo;
		lstBreakInfo = NULL;
	}
}
/*=============================================================================================*/
