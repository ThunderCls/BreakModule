//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
#include "BreakModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainFrm *MainFrm;
/* global variables */
char dExeName[MAX_PATH];
//---------------------------------------------------------------------------
__fastcall TMainFrm::TMainFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::btnAddClick(TObject *Sender)
{
	TListItem *ListItem;
	stBreakInfo *breakInfo;

	ListItem = lstModules->FindCaption(0, edtModule->Text, false, true, true);
	if(ListItem == NULL)
	{
		ListItem = lstModules->Items->Add();
		ListItem->Caption = edtModule->Text;
		ListItem->SubItems->Add((chkActive->Checked ? "true" : "false"));

		// Add a new value to TList var
		breakInfo = new stBreakInfo;
		ZeroMemory(breakInfo, sizeof(stBreakInfo));
		strncpy(breakInfo->module, AnsiString(edtModule->Text).c_str(), edtModule->Text.Length());
		strncpy(breakInfo->active, (chkActive->Checked ? "true" : "false"), 10);
		lstBreakInfo->Add(breakInfo);
	}
	else
	{
		ListItem->Caption = edtModule->Text;
		ListItem->SubItems->Strings[0] = (chkActive->Checked ? "true" : "false");

		// Edit the TList var
		breakInfo = (stBreakInfo*)lstBreakInfo->Items[ListItem->Index];
		strncpy(breakInfo->module, AnsiString(edtModule->Text).c_str(), edtModule->Text.Length());
		strncpy(breakInfo->active, (chkActive->Checked ? "true" : "false"), 10);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::btnDeleteClick(TObject *Sender)
{
	Delete1Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::lstModulesSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
	edtModule->Text = Item->Caption;
	chkActive->Checked = (Item->SubItems->Strings[0] == "true");
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	stBreakInfo *breakInfo;
	_di_IXMLDocument XML;
	_di_IXMLNode indexNode, modNode;
	_di_IXMLNodeList nodeList;

	// retrieve the config file
	XML = interface_cast<Xmlintf::IXMLDocument>(new TXMLDocument(NULL));
	XML->LoadFromFile(configFileName);

	nodeList = XML->DocumentElement->ChildNodes;
	// Find the current application info node
	indexNode = FindNodeByAttribute(nodeList, "path", dExeName);
	if(indexNode != NULL)
	{
		for (int i = 0; i < lstBreakInfo->Count; i++)
		{
			breakInfo = (stBreakInfo*)lstBreakInfo->Items[i];
			modNode = FindNodeByAttribute(indexNode->ChildNodes, "name", breakInfo->module);

			if(modNode != NULL)
				modNode->Attributes["active"] = breakInfo->active;
			else
			{
				// the node has to be created
				modNode = indexNode->AddChild("module", i);
				modNode->SetAttribute("name", breakInfo->module);
				modNode->SetAttribute("active", breakInfo->active);
			}
		}

		XML->SaveToFile(configFileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormShow(TObject *Sender)
{
	stBreakInfo *breakInfo;
	TListItem *Item;

	if(lstBreakInfo != NULL)
	{
		for (int i = 0; i < lstBreakInfo->Count; i++)
		{
			breakInfo = (stBreakInfo*)lstBreakInfo->Items[i];

			Item = lstModules->Items->Add();
			Item->Caption = breakInfo->module;
			Item->SubItems->Add(breakInfo->active);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::popmnuModulesPopup(TObject *Sender)
{
	TListItem *ListItem;

	if(lstModules->Selected != NULL)
	{
		Activate1->Enabled = true;
		Delete1->Enabled = true;

		ListItem = lstModules->Selected;
		if(ListItem->SubItems->Strings[0] == "true")
			Activate1->Caption = "Deactivate";
		else
			Activate1->Caption = "Activate";
	}
	else
	{
		Activate1->Enabled = false;
		Delete1->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::Activate1Click(TObject *Sender)
{
	TListItem *ListItem;
	stBreakInfo *breakInfo;

	ListItem = lstModules->Selected;
	if(ListItem->SubItems->Strings[0] == "false")
	{
		ListItem->SubItems->Strings[0] = "true";
		// Edit the TList var
		breakInfo = (stBreakInfo*)lstBreakInfo->Items[ListItem->Index];
		strncpy(breakInfo->active, "true", 10);
	}
	else if(ListItem->SubItems->Strings[0] == "true")
	{
		ListItem->SubItems->Strings[0] = "false";
		// Edit the TList var
		breakInfo = (stBreakInfo*)lstBreakInfo->Items[ListItem->Index];
		strncpy(breakInfo->active, "false", 10);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::Delete1Click(TObject *Sender)
{
	stBreakInfo *breakInfo;
	_di_IXMLDocument XML;
	_di_IXMLNode indexNode, modNode;
	_di_IXMLNodeList nodeList;
	int index = -1;

	if(MessageBox(MainFrm->Handle, L"Are you sure you want to delete the selected entry?",
		L"Confirm", MB_ICONWARNING + MB_YESNO) == ID_YES)
	{
		// retrieve the config file
		XML = interface_cast<Xmlintf::IXMLDocument>(new TXMLDocument(NULL));
		XML->LoadFromFile(configFileName);


		nodeList = XML->DocumentElement->ChildNodes;
		// Find the current application info node
		indexNode = FindNodeByAttribute(nodeList, "path", dExeName);
		if(indexNode != NULL)
		{
			breakInfo = (stBreakInfo*)lstBreakInfo->Items[lstModules->Selected->Index];
			modNode = FindNodeByAttribute(indexNode->ChildNodes, "name", breakInfo->module, &index);
			if(modNode != NULL && index != -1) // module node is found
			{
				indexNode->ChildNodes->Delete(index); // delete module node by index
				XML->SaveToFile(configFileName);
			}
		}

		lstBreakInfo->Delete(lstModules->Selected->Index);
		lstModules->DeleteSelected();
	}
}
//---------------------------------------------------------------------------

