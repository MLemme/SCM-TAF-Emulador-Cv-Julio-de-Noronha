//---------------------------------------------------------------------------

#ifndef CtrlPressH
#define CtrlPressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCtrlParamAuto : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblRPMEIXOBB;
        TLabel *Label1;
        TLabel *Label2;
        TShape *Shape20;
        TLabel *Label5;
        TLabel *lblRotMin_BB;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *lblPressMin_BB;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *lblPressAlm_BB;
        TLabel *lblPressLib_BB;
        TLabel *lblPressOpe_BB;
        TTimer *tmrAtualiza;
        TEdit *txtRotMin_BB;
        TEdit *txtPressMin_BB;
        TEdit *txtPressAlm_BB;
        TEdit *txtPressLib_BB;
        TEdit *txtPressOpe_BB;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label26;
        TLabel *Label27;
        TLabel *lblRPMEIXOBE;
        TLabel *Label29;
        TLabel *Label30;
        TShape *Shape1;
        TLabel *Label31;
        TLabel *lblRotMin_BE;
        TLabel *Label33;
        TLabel *Label34;
        TLabel *lblPressMin_BE;
        TLabel *Label36;
        TLabel *Label37;
        TLabel *Label38;
        TLabel *Label39;
        TLabel *Label40;
        TLabel *Label41;
        TLabel *Label42;
        TLabel *lblPressAlm_BE;
        TLabel *lblPressLib_BE;
        TLabel *lblPressOpe_BE;
        TEdit *txtRotMin_BE;
        TEdit *txtPressMin_BE;
        TEdit *txtPressAlm_BE;
        TEdit *txtPressLib_BE;
        TEdit *txtPressOpe_BE;
        TLabel *Label46;
        TLabel *Label47;
        TLabel *Label48;
        TLabel *Label49;
        TLabel *Label50;
        TLabel *Label51;
        TLabel *Label52;
        TLabel *Label53;
        TLabel *Label54;
        TLabel *Label55;
        TLabel *Label56;
        TLabel *Label57;
        TLabel *Label58;
        TLabel *Label59;
        TLabel *Label60;
        TButton *btnAlterar;
        TButton *btnFECHAR;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall tmrAtualizaTimer(TObject *Sender);
        void __fastcall btnAlterarClick(TObject *Sender);
        void __fastcall btnFECHARClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCtrlParamAuto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCtrlParamAuto *frmCtrlParamAuto;
//---------------------------------------------------------------------------
#endif
