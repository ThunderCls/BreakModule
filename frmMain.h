//---------------------------------------------------------------------------
#pragma once
#ifndef frmMainH
#define frmMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TMainFrm : public TForm
{
__published:	// IDE-managed Components
	TButton *btnAdd;
	TButton *btnDelete;
	TEdit *edtModule;
	TLabel *Label2;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TCheckBox *chkActive;
	TListView *lstModules;
	TPopupMenu *popmnuModules;
	TMenuItem *Activate1;
	TMenuItem *Delete1;
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
	void __fastcall lstModulesSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall popmnuModulesPopup(TObject *Sender);
	void __fastcall Activate1Click(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    TList *lstBreakInfo; // Global variable that holds all the info for the current module
	__fastcall TMainFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainFrm *MainFrm;
//---------------------------------------------------------------------------
#endif
