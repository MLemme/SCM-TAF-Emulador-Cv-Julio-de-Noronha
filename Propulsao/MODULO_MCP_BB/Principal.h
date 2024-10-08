//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//#include "TModBusScanner.cpp" /* DRIVER MODBUS */

//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TPanel *pnlAF;
        TShape *Shape6;
        TLabel *Label30;
        TLabel *Label31;
        TShape *shpEncherETH2;
        TShape *shpEncherETH1;
        TLabel *Label32;
        TLabel *Label33;
        TLabel *Label34;
        TShape *shpEsvaziarETH1;
        TShape *shpEsvaziarETH2;
        TShape *shpVazio;
        TLabel *Label35;
        TShape *shpEnchendo;
        TLabel *Label36;
        TShape *shpEsvaziarHDW;
        TLabel *Label37;
        TShape *shpCheio;
        TLabel *Label38;
        TShape *shpEsvaziando;
        TLabel *Label39;
        TLabel *lblEncher;
        TLabel *lblEsvaziar;
        TShape *shpPS3;
        TLabel *Label40;
        TLabel *lblConta;
        TImage *Image6;
        TButton *btnEncherAF;
        TButton *btnEsvaziarAF;
        TButton *btnControles;
        TPanel *pnlPrime;
        TShape *Shape8;
        TLabel *Label23;
        TLabel *Label24;
        TShape *shpPartirBBAOLETH2;
        TShape *shpPartirBBAOLETH1;
        TLabel *Label25;
        TLabel *Label26;
        TLabel *Label27;
        TShape *shpPararBBAOLETH1;
        TShape *shpPararBBAOLETH2;
        TShape *shpBBAOLEmRemoto;
        TLabel *Label28;
        TShape *shpBBAOLEmOpercao;
        TLabel *Label29;
        TLabel *lblPressOLub;
        TLabel *Label45;
        TImage *Image5;
        TButton *btnBBAOLEmRemoto;
        TButton *btnBBAOLPCtrl;
        TButton *cmdInibirCMD_PRIME;
        TButton *cmdInibirPRESS_PRIME;
        TButton *btnInterlocksOKPartir;
        TPanel *pnlCTRL;
        TLabel *lblCREMex1;
        TLabel *lblCREM1;
        TLabel *lblCREMex2;
        TLabel *lblCREM2;
        TLabel *lblCREMex3;
        TLabel *lblCREM3;
        TLabel *lblCREMex4;
        TLabel *lblCREM4;
        TLabel *lblCARGA2ex;
        TLabel *lblCARGA1ex;
        TLabel *lblMCRex;
        TLabel *lblDBRex;
        TLabel *lblDBR;
        TLabel *lblMCR;
        TLabel *lblCARGA1;
        TLabel *lblCARGA2;
        TLabel *Label44;
        TLabel *lblPasso;
        TLabel *Label46;
        TLabel *lblTolerCaturro;
        TLabel *Label48;
        TLabel *lblCARGA_CALCULADA;
        TButton *btnCREM;
        TButton *btnDBR;
        TButton *btnMCR;
        TButton *btnCARGA;
        TEdit *txtCREM;
        TEdit *txtDBR;
        TEdit *txtMCR;
        TEdit *txtCARGA;
        TButton *btnEscolhePasso;
        TButton *btnHabilitaCaturro;
        TEdit *txtTolerCaturro;
        TButton *btnTolerCaturro;
        TPanel *pnlLocal;
        TShape *Shape5;
        TLabel *lblPainelLocal;
        TLabel *lblDemandaLocal;
        TButton *btnEmRemoto;
        TButton *btnBatOver;
        TButton *btnPrdEmergLocal;
        TButton *btnPartir;
        TButton *btnParar;
        TButton *btnAcelerarLocal;
        TButton *btnDesacelerarLocal;
        TPanel *pnlStatus;
        TImage *Image1;
        TShape *Shape1;
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
        TGroupBox *grbIPQM;
        TImage *imgGSD;
        TLabel *lblIPQM;
        TLabel *lblGSD;
        TLabel *lbl142;
        TImage *imgIPQM;
        TGroupBox *grbNAVIO;
        TImage *imgNAVIO;
        TLabel *lblNAVIO;
        TLabel *Label123;
        TLabel *Label124;
        TLabel *Label125;
        TLabel *Label47;
        TPanel *shpAguarde;
        TLabel *lblAguarde;
        TButton *btnReset;
        TButton *btnOutrosAnalogicos;
        TButton *btnCargaDinamica;
        TPanel *pnlFixo;
        TShape *Shape7;
        TShape *Shape3;
        TShape *Shape2;
        TShape *Shape10;
        TShape *shpPartirETH1;
        TShape *shpPartirETH2;
        TShape *shpPartirHDW;
        TLabel *lblComandos;
        TLabel *Label11;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TShape *shpPararETH1;
        TShape *shpPararETH2;
        TShape *shpPararHDW;
        TLabel *Label9;
        TShape *shpPararEmergETH1;
        TShape *shpPararEmergETH2;
        TShape *shpPararEmergHDW;
        TLabel *Label10;
        TShape *shpSilenciarETH1;
        TShape *shpSilenciarETH2;
        TShape *shpSilenciarHDW;
        TLabel *Label12;
        TShape *shpReconhecerETH1;
        TShape *shpReconhecerETH2;
        TShape *shpReconhecerHDW;
        TLabel *Label13;
        TShape *shpAtivarBOHDW;
        TShape *Shape4;
        TShape *shpParado;
        TShape *shpPartindo;
        TShape *shpVirando;
        TShape *shpParando;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TShape *shpEmRemoto;
        TLabel *Label2;
        TShape *shpEmLocal;
        TLabel *Label4;
        TShape *shpBatOver;
        TLabel *Label41;
        TShape *shpInterlockOK;
        TLabel *Label19;
        TShape *shpInterlockOKLub;
        TLabel *Label43;
        TLabel *lblRotacao;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *lblDemandaETH1;
        TLabel *Label18;
        TLabel *lblDemandaETH2;
        TLabel *Label22;
        TLabel *lblDemandaHDW;
        TShape *shpCtrlRPM;
        TLabel *lblRotacaoCalc;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *lblTempoPartida;
        TLabel *lblTempoParada;
        TButton *btnStatus;
        TButton *btnFechar;
        TButton *btnCtrl;
        TButton *btnAF;
        TButton *btnPrime;
        TButton *btnLocal;
        TTimer *tmrStarting;
        TTimer *ConexaoWatch;
        TTimer *tmrLeitura;
        TTimer *Animacao;
        TTimer *Demanda;
        TTimer *Partida;
        TTimer *Parada;
        TTimer *Acelerar;
        TTimer *Desacelerar;
        TTimer *Lista;
        TTimer *tmrPRIME;
        TTimer *tmrConta;
        TTimer *tmrBO;
        TTimer *tmrPreEncherAF;
        TTimer *tmrPreEsvaziarAF;
        TTimer *tmrReconecta;
        TTimer *tmrCtrlCarga;
        TTimer *tmrEncherAF;
        TTimer *tmrEsvaziarAF;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ConexaoWatchTimer(TObject *Sender);
        void __fastcall tmrStartingTimer(TObject *Sender);
        void __fastcall tmrLeituraTimer(TObject *Sender);
        void __fastcall PartidaTimer(TObject *Sender);
        void __fastcall AcelerarTimer(TObject *Sender);
        void __fastcall btnOutrosAnalogicosClick(TObject *Sender);
        void __fastcall ParadaTimer(TObject *Sender);
        void __fastcall DesacelerarTimer(TObject *Sender);
        void __fastcall btnControlesClick(TObject *Sender);
        void __fastcall DemandaTimer(TObject *Sender);
        void __fastcall btnPartirClick(TObject *Sender);
        void __fastcall btnPararClick(TObject *Sender);
        void __fastcall btnPrdEmergLocalClick(TObject *Sender);
        void __fastcall btnAcelerarLocalClick(TObject *Sender);
        void __fastcall btnDesacelerarLocalClick(TObject *Sender);
        void __fastcall ListaTimer(TObject *Sender);
        void __fastcall btnBBAOLEmRemotoClick(TObject *Sender);
        void __fastcall btnBBAOLPCtrlClick(TObject *Sender);
        void __fastcall tmrPRIMETimer(TObject *Sender);
        void __fastcall tmrEncherAFTimer(TObject *Sender);
        void __fastcall btnEncherAFClick(TObject *Sender);
        void __fastcall tmrEsvaziarAFTimer(TObject *Sender);
        void __fastcall btnEsvaziarAFClick(TObject *Sender);
        void __fastcall tmrContaTimer(TObject *Sender);
        void __fastcall tmrBOTimer(TObject *Sender);
        void __fastcall tmrPreEncherAFTimer(TObject *Sender);
        void __fastcall tmrPreEsvaziarAFTimer(TObject *Sender);
        void __fastcall tmrReconectaTimer(TObject *Sender);
        void __fastcall btnEmRemotoClick(TObject *Sender);
        void __fastcall btnBatOverClick(TObject *Sender);
        void __fastcall btnCREMClick(TObject *Sender);
        void __fastcall btnDBRClick(TObject *Sender);
        void __fastcall btnMCRClick(TObject *Sender);
        void __fastcall btnCARGAClick(TObject *Sender);
        void __fastcall cmdInibirCMD_PRIMEClick(TObject *Sender);
        void __fastcall cmdInibirPRESS_PRIMEClick(TObject *Sender);
        void __fastcall btnInterlocksOKPartirClick(TObject *Sender);
        void __fastcall btnEscolhePassoClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall tmrCtrlCargaTimer(TObject *Sender);
        void __fastcall btnCargaDinamicaClick(TObject *Sender);
        void __fastcall btnHabilitaCaturroClick(TObject *Sender);
        void __fastcall btnTolerCaturroClick(TObject *Sender);
        void __fastcall btnStatusClick(TObject *Sender);
        void __fastcall btnPrimeClick(TObject *Sender);
        void __fastcall btnCtrlClick(TObject *Sender);
        void __fastcall btnFecharClick(TObject *Sender);
        void __fastcall btnAFClick(TObject *Sender);
        void __fastcall btnLocalClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
