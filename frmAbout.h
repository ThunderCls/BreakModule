//---------------------------------------------------------------------------

#ifndef frmAboutH
#define frmAboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TAboutFrm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TImage *imgIcon;
	TRichEdit *RichEdit1;
	TLabel *Label3;
	void __fastcall Label3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAboutFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutFrm *AboutFrm;
//---------------------------------------------------------------------------
#endif
