//---------------------------------------------------------------------------

#ifndef CtrlPassoH
#define CtrlPassoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCtrlPasso : public TForm
{
__published:	// IDE-managed Components
        TEdit *txtPASSO_BB_INC_AV_1;
        TEdit *txtPASSO_BB_INC_AV_3;
        TEdit *txtPASSO_BB_INC_AV_2;
        TEdit *txtTempoBB;
        TLabel *lblInit3;
        TShape *Shape2;
        TLabel *lblInit11;
        TShape *Shape41;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *txtPASSO_BB_DIF_AV_3;
        TEdit *txtPASSO_BB_DIF_AV_2;
        TEdit *txtPASSO_BB_DIF_AV_1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TButton *btnAjustar_BB;
        TButton *btnValoresOriginais_BB;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TEdit *txtPASSO_BB_INC_AR_3;
        TEdit *txtPASSO_BB_INC_AR_2;
        TEdit *txtPASSO_BB_INC_AR_1;
        TLabel *Label20;
        TLabel *Label21;
        TEdit *txtPASSO_BB_DIF_AR_1;
        TEdit *txtPASSO_BB_DIF_AR_2;
        TEdit *txtPASSO_BB_DIF_AR_3;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TEdit *txtPASSO_BE_INC_AV_1;
        TEdit *txtPASSO_BE_INC_AV_3;
        TEdit *txtPASSO_BE_INC_AV_2;
        TEdit *txtTempoBE;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *txtPASSO_BE_DIF_AV_3;
        TEdit *txtPASSO_BE_DIF_AV_2;
        TEdit *txtPASSO_BE_DIF_AV_1;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TButton *btnAjustar_BE;
        TButton *btnValoresOriginais_BE;
        TLabel *Label25;
        TLabel *Label26;
        TLabel *Label27;
        TEdit *txtPASSO_BE_INC_AR_3;
        TEdit *txtPASSO_BE_INC_AR_2;
        TEdit *txtPASSO_BE_INC_AR_1;
        TLabel *Label28;
        TLabel *Label29;
        TEdit *txtPASSO_BE_DIF_AR_1;
        TEdit *txtPASSO_BE_DIF_AR_2;
        TEdit *txtPASSO_BE_DIF_AR_3;
        TLabel *Label30;
        TLabel *Label31;
        TLabel *Label32;
        TButton *btnFechar;
        void __fastcall btnAjustar_BBClick(TObject *Sender);
        void __fastcall btnValoresOriginais_BBClick(TObject *Sender);
        void __fastcall btnAjustar_BEClick(TObject *Sender);
        void __fastcall btnValoresOriginais_BEClick(TObject *Sender);
        void __fastcall btnFecharClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCtrlPasso(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCtrlPasso *frmCtrlPasso;
//---------------------------------------------------------------------------
#endif
