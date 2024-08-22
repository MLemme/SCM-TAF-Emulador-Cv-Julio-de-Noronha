//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
        TTimer *tmrStarting;
        TTimer *ConexaoWatch;
        TTimer *tmrLeitura;
        TLabel *lblWDETH1MAIN;
        TLabel *lblWDETH1STDB;
        TLabel *lblWDETH2MAIN;
        TLabel *lblWDETH2STDB;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TTimer *Animacao;
        TLabel *lblWDETH1MAIN2;
        TLabel *lblWDETH1STDB2;
        TLabel *lblWDETH2MAIN2;
        TLabel *lblWDETH2STDB2;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        TShape *Shape8;
        TShape *Shape9;
        TShape *Shape10;
        TLabel *Label5;
        TLabel *Label6;
        TButton *btnETH1MBB;
        TButton *btnETH1SBB;
        TButton *btnETH2MBB;
        TButton *btnETH2SBB;
        TButton *btnETH1BB;
        TButton *btnETH2BB;
        TButton *btnMAINBB;
        TButton *btnSTDBBB;
        TButton *btnETH1MBE;
        TButton *btnETH1SBE;
        TButton *btnETH2MBE;
        TButton *btnETH2SBE;
        TButton *btnETH1BE;
        TButton *btnETH2BE;
        TButton *btnMAINBE;
        TButton *btnSTDBBE;
        TShape *Shape11;
        TLabel *lblLista;
        TLabel *lblBufferEx;
        TLabel *lblTamListaIDs;
        TLabel *lblInicioPrograma;
        TLabel *lblBufferR;
        TLabel *lblBufferW;
        TLabel *lblProgramaAtual;
        TLabel *lblQuedas;
        TLabel *Label42;
        TLabel *lblWatchdogEx;
        TLabel *lblWatchdog;
        TLabel *lblEndereco;
        TTimer *Lista;
        TTimer *tmrReconecta;
        TPanel *shpAguarde;
        TLabel *lblAguarde;
        TLabel *lblWDETH1TG;
        TLabel *lblWDETH2TG;
        TLabel *Label15;
        TLabel *Label17;
        TShape *Shape16;
        TLabel *Label19;
        TButton *btnETH1TG;
        TButton *btnETH2TG;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ConexaoWatchTimer(TObject *Sender);
        void __fastcall tmrStartingTimer(TObject *Sender);
        void __fastcall tmrLeituraTimer(TObject *Sender);
        void __fastcall AnimacaoTimer(TObject *Sender);
        void __fastcall btnETH1MBBClick(TObject *Sender);
        void __fastcall btnETH1SBBClick(TObject *Sender);
        void __fastcall btnETH2MBBClick(TObject *Sender);
        void __fastcall btnETH2SBBClick(TObject *Sender);
        void __fastcall btnETH1BBClick(TObject *Sender);
        void __fastcall btnETH2BBClick(TObject *Sender);
        void __fastcall btnMAINBBClick(TObject *Sender);
        void __fastcall btnSTDBBBClick(TObject *Sender);
        void __fastcall btnETH1MBEClick(TObject *Sender);
        void __fastcall btnETH1SBEClick(TObject *Sender);
        void __fastcall btnETH2MBEClick(TObject *Sender);
        void __fastcall btnETH2SBEClick(TObject *Sender);
        void __fastcall btnETH1BEClick(TObject *Sender);
        void __fastcall btnETH2BEClick(TObject *Sender);
        void __fastcall btnMAINBEClick(TObject *Sender);
        void __fastcall btnSTDBBEClick(TObject *Sender);
        void __fastcall tmrReconectaTimer(TObject *Sender);
        void __fastcall ListaTimer(TObject *Sender);
        void __fastcall btnETH1TGClick(TObject *Sender);
        void __fastcall btnETH2TGClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
