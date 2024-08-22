//---------------------------------------------------------------------------

#ifndef ControleNovoH
#define ControleNovoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <chartfx3.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmControlesNovo : public TForm
{
__published:	// IDE-managed Components
        TChartfx *chtBaixaRotacao;
        TChartfx *cht1400;
        TShape *Shape1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label6;
        TLabel *Label8;
        TLabel *Label10;
        TLabel *Label12;
        TLabel *lblCARGA_CALCULADA;
        TLabel *lblPasso;
        TLabel *lblRPMMCP;
        TLabel *Label14;
        TLabel *Label19;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *lblMCRMCP;
        TLabel *Label24;
        TLabel *lblCREMMCP;
        TLabel *Label25;
        TLabel *Label23;
        TLabel *Label26;
        TShape *Shape2;
        TEdit *txtX_LOAD_1;
        TEdit *txtX_LOAD_2;
        TEdit *txtX_LOAD_3;
        TEdit *txtX_LOAD_4;
        TButton *btnParametrizar;
        TButton *Button1;
        TEdit *txtRPM1;
        TEdit *txtRPM2;
        TEdit *txtRPM3;
        TEdit *txtPASSO1;
        TEdit *txtPASSO22;
        TEdit *txtCARGA1_RPM1;
        TEdit *txtCARGA2_RPM1;
        TEdit *txtPASSO23;
        TEdit *txtCARGA3_RPM1;
        TEdit *txtPASSO24;
        TEdit *txtCARGA4_RPM1;
        TEdit *txtCARGA1_RPM2;
        TEdit *txtCARGA2_RPM2;
        TEdit *txtCARGA3_RPM2;
        TEdit *txtCARGA4_RPM2;
        TEdit *txtCARGA1_RPM3;
        TEdit *txtCARGA2_RPM3;
        TEdit *txtCARGA3_RPM3;
        TEdit *txtCARGA4_RPM3;
        TEdit *txtCGMCR1_RPM1;
        TEdit *txtCGMCR2_RPM1;
        TEdit *txtCGMCR3_RPM1;
        TEdit *txtCGMCR4_RPM1;
        TEdit *txtCGMCR1_RPM2;
        TEdit *txtCGMCR2_RPM2;
        TEdit *txtCGMCR3_RPM2;
        TEdit *txtCGMCR4_RPM2;
        TEdit *txtCGMCR1_RPM3;
        TEdit *txtCGMCR2_RPM3;
        TEdit *txtCGMCR3_RPM3;
        TEdit *txtCGMCR4_RPM3;
        TButton *btnFechar;
        TTimer *tmrPosicao;
        TLabel *Label5;
        TLabel *Label7;
        TLabel *Label9;
        TLabel *Label11;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *txtY_LOAD_1;
        TEdit *txtY_LOAD_2;
        TEdit *txtY_LOAD_3;
        TEdit *txtY_LOAD_4;
        TEdit *txtMCR6;
        TEdit *txtMCR7;
        TEdit *txtMCR8;
        TLabel *Label13;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btnParametrizarClick(TObject *Sender);
        void __fastcall btnFecharClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmControlesNovo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmControlesNovo *frmControlesNovo;
//---------------------------------------------------------------------------
#endif
