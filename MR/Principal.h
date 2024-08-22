//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *grbDiagnostico;
        TLabel *lblEndereco;
        TLabel *lblWatchdogEx;
        TLabel *lblWatchdog;
        TLabel *lblLista;
        TLabel *lblBufferEx;
        TLabel *lblQuedas;
        TLabel *lblBufferW;
        TLabel *lblBufferR;
        TLabel *lblTamListaIDs;
        TLabel *lblProgramaAtual;
        TLabel *lblInicioPrograma;
        TLabel *lblDiagnostico;
        TPanel *shpAguarde;
        TLabel *lblAguarde;
        TButton *btnReset;
        TTimer *tmrLeitura;
        TTimer *tmrConexaoWatch;
        TTimer *tmrLista;
        TTimer *tmrReconecta;
        TTimer *tmrStarting;
        TTimer *tmrHabilitar;
        TButton *btnConectar;
        TLabel *lblModbusStatus;
        TButton *btnHabilitar;
        TTimer *tmrTesteHPC;
        TTimer *tmrTesteAlarmes;
        TTimer *tmrTesteAlarmes2;
        TTimer *tmrEqualSCM;
        TPanel *pnlTesteHPC;
        TShape *shpHPCBB_UDOHPC_PASSOBBPOS;
        TLabel *lblHPCBB;
        TLabel *lblHPCBB_UDOHPC_PASSOBBPOS;
        TShape *shpHPCBE_UDOHPC_PASSOBEPOS;
        TLabel *lblHPCBE_UDOHPC_PASSOBEPOS;
        TLabel *lblHPCBE;
        TEdit *txtTesteHPC;
        TEdit *txtTesteHPC_st;
        TLabel *lblTesteHPC_st;
        TLabel *lblTesteHPC;
        TButton *btnTesteHPC;
        TPanel *pnlTestaAlarme;
        TButton *btnTesteAlarmes;
        TEdit *txtTesteAlarmes;
        TShape *shpTesteAlarmes;
        TShape *shpTesteAlarmes2;
        TLabel *lblTesteAlarmes;
        TLabel *lblTesteAlarmes2;
        TMainMenu *mnuMenu;
        TMenuItem *mnuSelecao;
        TMenuItem *mnuTestes;
        TMenuItem *mnuTestaHPC;
        TMenuItem *mnuTestaAlarmes;
        TPanel *pnlSelecao;
        TButton *btnEqualSCM;
        TImage *imgSolicAuto;
        TImage *imgSolicMR;
        TLabel *lblSolicAuto;
        TLabel *Label1;
        TShape *shpHabilitaSelecao;
        TTimer *tmrTransferencia;
        TTimer *tmrComandosMR;
        TLabel *lblTamListaIDs_SCM;
        TLabel *lblBufferR_SCM;
        TLabel *lblBufferW_SCM;
        TLabel *lblQuedas_SCM;
        TLabel *lblBufferEx_SCM;
        TLabel *lblLista_SCM;
        TLabel *lblWatchdogEx_SCM;
        TLabel *lblEndereco_SCM;
        TLabel *lblWatchdog_SCM;
        TLabel *lblIP;
        TRadioButton *chkIP_SUP;
        TRadioButton *chkIP_PLT;
        TPanel *shpAguarde_SCM;
        TLabel *lblAguarde_SCM;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *lblIP_MR;
        TLabel *lblIP_SCM;
        TShape *Shape1;
        TShape *shpemmr;
        TShape *shpComandos;
        TShape *shpDados;
        TGroupBox *grbNAVIO;
        TImage *imgNAVIO;
        TLabel *lblNAVIO;
        TLabel *Label123;
        TLabel *Label124;
        TLabel *Label125;
        TLabel *Label47;
        TGroupBox *grbIPQM;
        TImage *imgGSD;
        TLabel *lblIPQM;
        TLabel *lblGSD;
        TLabel *lbl142;
        TImage *imgIPQM;
        TButton *btnFechar;
        TTimer *tmrFechar;
        TTimer *tmrFecha;
        void __fastcall btnConectarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall tmrStartingTimer(TObject *Sender);
        void __fastcall tmrReconectaTimer(TObject *Sender);
        void __fastcall tmrListaTimer(TObject *Sender);
        void __fastcall tmrConexaoWatchTimer(TObject *Sender);
        void __fastcall tmrLeituraTimer(TObject *Sender);
        void __fastcall btnHabilitarClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnTesteHPCClick(TObject *Sender);
        void __fastcall tmrTesteHPCTimer(TObject *Sender);
        void __fastcall tmrTesteAlarmesTimer(TObject *Sender);
        void __fastcall btnTesteAlarmesClick(TObject *Sender);
        void __fastcall tmrTesteAlarmes2Timer(TObject *Sender);
        void __fastcall tmrEqualSCMTimer(TObject *Sender);
        void __fastcall btnEqualSCMClick(TObject *Sender);
        void __fastcall mnuSelecaoClick(TObject *Sender);
        void __fastcall mnuTestaHPCClick(TObject *Sender);
        void __fastcall mnuTestaAlarmesClick(TObject *Sender);
        void __fastcall imgSolicAutoClick(TObject *Sender);
        void __fastcall imgSolicMRClick(TObject *Sender);
        void __fastcall tmrTransferenciaTimer(TObject *Sender);
        void __fastcall tmrComandosMRTimer(TObject *Sender);
        void __fastcall btnFecharClick(TObject *Sender);
        void __fastcall tmrFecharTimer(TObject *Sender);
        void __fastcall tmrFechaTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
