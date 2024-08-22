//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
        TTimer *Starting;
        TTimer *tmrParar_BBP1_HPCBB;
        TTimer *tmrPartir_BBP1_HPCBE;
        TTimer *tmrParar_BBP1_HPCBE;
        TTimer *tmrPassoBB;
        TTimer *tmrPassoBE;
        TPanel *pnlHPCBB_P1;
        TShape *Shape10;
        TLabel *lblInit1;
        TShape *shpLigada_BBP1BB;
        TLabel *Label28;
        TShape *shpSobrec_BBP1BB;
        TLabel *Label1;
        TShape *shpRemoto_BBP1BB;
        TLabel *Label2;
        TShape *shpAUTOHDWSCMLIG_BBP1BB;
        TLabel *Label3;
        TShape *shpAUTOHDWSCMDES_BBP1BB;
        TLabel *Label5;
        TShape *shpPRDEMERGSCMLI_BBP1BB;
        TLabel *Label6;
        TShape *shpPRDEMERGSCMDE_BBP1BB;
        TLabel *Label7;
        TShape *shpLigarBBP1BB;
        TShape *shpDesligarBBP1BB;
        TShape *shpAUTOMATICOBBP1BB;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TShape *shpMANUALBBP1BB;
        TLabel *Label11;
        TShape *shpEmerg_BBP1BB;
        TLabel *Label12;
        TLabel *Label13;
        TShape *shpLibEmerg_BBP1BB;
        TShape *shpEmAut_BBP1BB;
        TLabel *Label44;
        TButton *btnLigada_BBP1BB;
        TButton *btnSobrec_BBP1BB;
        TButton *btnRemoto_BBP1BB;
        TButton *btnAUTOHDWSCMLIG_BBP1BB;
        TButton *btnAUTOHDWSCMDES_BBP1BB;
        TButton *btnPRDEMERGSCMLI_BBP1BB;
        TButton *btnPRDEMERGSCMDE_BBP1BB;
        TButton *btnPartir_BBP1BB;
        TButton *btnParar_BBP1BB;
        TButton *btnEmAut_BBP1BB;
        TTimer *tmrPressurizarHPCBB;
        TTimer *tmrDespressurizarHPCBB;
        TPanel *pnlHPCBE_P1;
        TShape *Shape9;
        TLabel *lblInit9;
        TShape *shpLigada_BBP1BE;
        TLabel *Label45;
        TShape *shpSobrec_BBP1BE;
        TLabel *Label47;
        TShape *shpRemoto_BBP1BE;
        TLabel *Label48;
        TShape *shpAUTOHDWSCMLIG_BBP1BE;
        TLabel *Label49;
        TShape *shpAUTOHDWSCMDES_BBP1BE;
        TLabel *Label51;
        TShape *shpPRDEMERGSCMLI_BBP1BE;
        TLabel *Label52;
        TShape *shpPRDEMERGSCMDE_BBP1BE;
        TLabel *Label53;
        TShape *shpLigarBBP1BE;
        TShape *shpDesligarBBP1BE;
        TShape *shpAUTOMATICOBBP1BE;
        TLabel *Label54;
        TLabel *Label55;
        TLabel *Label56;
        TShape *shpMANUALBBP1BE;
        TLabel *Label57;
        TShape *shpEmerg_BBP1BE;
        TLabel *Label58;
        TLabel *Label59;
        TShape *shpLibEmerg_BBP1BE;
        TShape *shpEmAut_BBP1BE;
        TLabel *Label60;
        TButton *btnLigada_BBP1BE;
        TButton *btnSobrec_BBP1BE;
        TButton *btnRemoto_BBP1BE;
        TButton *btnAUTOHDWSCMLIG_BBP1BE;
        TButton *btnAUTOHDWSCMDES_BBP1BE;
        TButton *btnPRDEMERGSCMLI_BBP1BE;
        TButton *btnPRDEMERGSCMDE_BBP1BE;
        TButton *btnPartir_BBP1BE;
        TButton *btnParar_BBP1BE;
        TButton *btnEmAut_BBP1BE;
        TTimer *tmrLeitura;
        TTimer *ConexaoWatch;
        TTimer *tmrPartir_BBP1_HPCBB;
        TTimer *tmrPressurizarHPCBE;
        TTimer *tmrDespressurizarHPCBE;
        TTimer *tmrReconecta;
        TTimer *Lista;
        TMainMenu *mnuPrincipal;
        TMenuItem *AjusteParamPasso1;
        TMenuItem *mnuHPCBB;
        TMenuItem *mnuHPCBE;
        TTimer *tmrErro;
        TTimer *tmrHPCBB_Auto;
        TMenuItem *mnuParamAuto;
        TTimer *tmrHPCBE_Auto;
        TPanel *pnlHPCBB_UDOMODHID;
        TLabel *lblInit3;
        TButton *btnFILT21BPDIFAL_HPCBB;
        TButton *btnFILT21APDIFAL_HPCBB;
        TButton *btnOLPRESSOK_HPCBB;
        TButton *btnZEROTHRUST_HPCBB;
        TLabel *PASSOBBPOS;
        TProgressBar *prbPASSOBBPOS_HPCBB;
        TEdit *txtPASSOBBPOS_HPCBB;
        TButton *btnPASSOBBPOS_HPCBB;
        TEdit *txtErro_BB;
        TLabel *lblErro_BB;
        TButton *btnErro_BB;
        TEdit *txtZEROTHRUST_HPCBB;
        TShape *Shape2;
        TShape *shpFILT21BPDIFAL_HPCBB;
        TLabel *Label19;
        TShape *shpFILT21APDIFAL_HPCBB;
        TLabel *Label30;
        TShape *shpOLPRESSOK_HPCBB;
        TLabel *Label31;
        TShape *shpZEROTHRUST_HPCBB;
        TLabel *Label14;
        TLabel *lblPASSOBBPOS_HPCBB;
        TPanel *pnlHPCBB_CTRL;
        TLabel *lblInit4;
        TButton *btnMANRPMBXSCM_HPCBB;
        TButton *btnCTRPRIFALHA_HPCBB;
        TLabel *Label38;
        TLabel *lblDEMANDAPASSO_HPCBB;
        TButton *btnDEMANDAPASSO_HPCBB;
        TShape *shpATIVARDEMANDA_HPCBB;
        TShape *Shape3;
        TShape *shpbtnCTRPRIFALHA_HPCBB;
        TLabel *Label35;
        TShape *shpMANRPMBXSCM_HPCBB;
        TLabel *Label34;
        TLabel *lblInit5;
        TShape *Shape4;
        TButton *btnCTRBKPEMOPERACAO_HPCBB;
        TShape *shpCTRBKPEMOPERACAO_HPCBB;
        TLabel *Label33;
        TLabel *lblInit7;
        TButton *btnTQGRAVNIVELBAIXO_HPCBB;
        TShape *shpTQGRAVNIVELBAIXO_HPCBB;
        TLabel *Label36;
        TShape *Shape6;
        TShape *Shape5;
        TLabel *lblInit6;
        TButton *btnFILT2PDIFAL_HPCBB;
        TButton *btnFILT1PDIFAL_HPCBB;
        TButton *btnOLPBX_HPCBB;
        TLabel *OLTEMP;
        TProgressBar *prbOLTEMP_HPCBB;
        TEdit *txtOLTEMP_HPCBB;
        TButton *btnOLTEMP_HPCBB;
        TEdit *txtOLPRESS_HPCBB;
        TButton *btnOLPRESS_HPCBB;
        TProgressBar *prbOLPRESS_HPCBB;
        TLabel *lblOLPRESS_HPCBB;
        TLabel *OLPRESS;
        TLabel *lblOLTEMP_HPCBB;
        TLabel *Label40;
        TShape *shpOLPBX_HPCBB;
        TShape *shpFILT1PDIFAL_HPCBB;
        TLabel *Label39;
        TShape *shpFILT2PDIFAL_HPCBB;
        TLabel *Label37;
        TPanel *pnlHPCBB_P3;
        TLabel *lblInit2;
        TButton *btnLigada_BBP3BB;
        TButton *btnEmAut_BBP3BB;
        TButton *btnRemoto_BBP3BB;
        TShape *shpLigarBBP3BB;
        TShape *Shape1;
        TLabel *Label23;
        TShape *shpDesligarBBP3BB;
        TLabel *Label24;
        TShape *shpAUTOMATICOBBP3BB;
        TLabel *Label25;
        TShape *shpMANUALBBP3BB;
        TLabel *Label26;
        TShape *shpEmerg_BBP3BB;
        TLabel *Label27;
        TShape *shpLibEmerg_BBP3BB;
        TLabel *Label29;
        TShape *shpRemoto_BBP3BB;
        TLabel *Label17;
        TShape *shpEmAut_BBP3BB;
        TLabel *Label16;
        TShape *shpLigada_BBP3BB;
        TLabel *Label15;
        TButton *btnAUTOHDWSCMLIG_BBP3BB;
        TButton *btnAUTOHDWSCMDES_BBP3BB;
        TButton *btnPRDEMERGSCMLI_BBP3BB;
        TButton *btnPRDEMERGSCMDE_BBP3BB;
        TButton *btnSobrec_BBP3BB;
        TShape *shpSobrec_BBP3BB;
        TLabel *Label70;
        TLabel *Label22;
        TShape *shpPRDEMERGSCMDE_BBP3BB;
        TShape *shpPRDEMERGSCMLI_BBP3BB;
        TLabel *Label21;
        TLabel *Label20;
        TShape *shpAUTOHDWSCMDES_BBP3BB;
        TShape *shpAUTOHDWSCMLIG_BBP3BB;
        TLabel *Label18;
        TShape *Shape7;
        TLabel *lblInit8;
        TShape *shpEMAUTOSCM_HPCBB;
        TLabel *Label41;
        TShape *shpLIGARRPMBX_HPCBB;
        TLabel *Label42;
        TShape *shpDESLIGARRPMBX_HPCBB;
        TLabel *Label43;
        TButton *cmdInbirCMDBB;
        TButton *cmdInbirPRESSBB;
        TPanel *pnlHPCBE_CTRL;
        TLabel *lblInit12;
        TButton *btnMANRPMBXSCM_HPCBE;
        TButton *btnCTRPRIFALHA_HPCBE;
        TLabel *Label84;
        TLabel *lblDEMANDAPASSO_HPCBE;
        TShape *shpATIVARDEMANDA_HPCBE;
        TButton *btnDEMANDAPASSO_HPCBE;
        TShape *shpbtnCTRPRIFALHA_HPCBE;
        TLabel *Label83;
        TShape *shpMANRPMBXSCM_HPCBE;
        TLabel *Label82;
        TShape *Shape46;
        TShape *Shape50;
        TLabel *lblInit13;
        TButton *btnCTRBKPEMOPERACAO_HPCBE;
        TLabel *Label86;
        TShape *shpCTRBKPEMOPERACAO_HPCBE;
        TShape *Shape56;
        TLabel *lblInit15;
        TButton *btnTQGRAVNIVELBAIXO_HPCBE;
        TShape *shpTQGRAVNIVELBAIXO_HPCBE;
        TLabel *Label96;
        TShape *Shape58;
        TLabel *lblInit16;
        TShape *shpEMAUTOSCM_HPCBE;
        TLabel *Label4;
        TShape *shpLIGARRPMBX_HPCBE;
        TLabel *Label32;
        TShape *shpDESLIGARRPMBX_HPCBE;
        TLabel *Label50;
        TButton *cmdInbirCMDBE;
        TButton *cmdInbirPRESSBE;
        TPanel *pnlHPCBE_UDOMODHID;
        TShape *Shape41;
        TLabel *lblInit11;
        TButton *btnFILT21BPDIFAL_HPCBE;
        TButton *btnFILT21APDIFAL_HPCBE;
        TButton *btnOLPRESSOK_HPCBE;
        TButton *btnZEROTHRUST_HPCBE;
        TLabel *PASSOBEPOS;
        TProgressBar *prbPASSOBEPOS_HPCBE;
        TEdit *txtPASSOBEPOS_HPCBE;
        TButton *btnPASSOBEPOS_HPCBE;
        TLabel *lblPASSOBEPOS_HPCBE;
        TLabel *lblErro_BE;
        TEdit *txtErro_BE;
        TButton *btnErro_BE;
        TEdit *txtZEROTHRUST_HPCBE;
        TLabel *Label74;
        TShape *shpZEROTHRUST_HPCBE;
        TShape *shpOLPRESSOK_HPCBE;
        TLabel *Label73;
        TShape *shpFILT21APDIFAL_HPCBE;
        TLabel *Label72;
        TShape *shpFILT21BPDIFAL_HPCBE;
        TLabel *Label71;
        TShape *Shape52;
        TLabel *lblInit14;
        TButton *btnFILT2PDIFAL_HPCBE;
        TButton *btnFILT1PDIFAL_HPCBE;
        TButton *btnOLPBX_HPCBE;
        TLabel *Label92;
        TProgressBar *prbOLTEMP_HPCBE;
        TEdit *txtOLTEMP_HPCBE;
        TButton *btnOLTEMP_HPCBE;
        TLabel *lblOLTEMP_HPCBE;
        TLabel *Label93;
        TProgressBar *prbOLPRESS_HPCBE;
        TEdit *txtOLPRESS_HPCBE;
        TButton *btnOLPRESS_HPCBE;
        TLabel *lblOLPRESS_HPCBE;
        TLabel *Label91;
        TShape *shpOLPBX_HPCBE;
        TShape *shpFILT1PDIFAL_HPCBE;
        TLabel *Label90;
        TLabel *Label89;
        TShape *shpFILT2PDIFAL_HPCBE;
        TPanel *pnlHPCBE_P3;
        TLabel *lblInit10;
        TButton *btnLigada_BBP3BE;
        TButton *btnEmAut_BBP3BE;
        TButton *btnRemoto_BBP3BE;
        TShape *shpLigarBBP3BE;
        TLabel *Label64;
        TShape *shpDesligarBBP3BE;
        TLabel *Label65;
        TShape *shpAUTOMATICOBBP3BE;
        TLabel *Label66;
        TShape *shpMANUALBBP3BE;
        TLabel *Label67;
        TShape *shpEmerg_BBP3BE;
        TLabel *Label68;
        TShape *shpLibEmerg_BBP3BE;
        TLabel *Label69;
        TShape *shpRemoto_BBP3BE;
        TLabel *Label63;
        TLabel *Label62;
        TShape *shpEmAut_BBP3BE;
        TShape *shpLigada_BBP3BE;
        TLabel *Label61;
        TButton *btnAUTOHDWSCMLIG_BBP3BE;
        TButton *btnAUTOHDWSCMDES_BBP3BE;
        TButton *btnPRDEMERGSCMLI_BBP3BE;
        TButton *btnPRDEMERGSCMDE_BBP3BE;
        TButton *btnSobrec_BBP3BE;
        TShape *shpSobrec_BBP3BE;
        TLabel *Label75;
        TLabel *Label79;
        TShape *shpPRDEMERGSCMDE_BBP3BE;
        TShape *shpPRDEMERGSCMLI_BBP3BE;
        TLabel *Label78;
        TShape *shpAUTOHDWSCMLIG_BBP3BE;
        TShape *shpAUTOHDWSCMDES_BBP3BE;
        TShape *Shape27;
        TLabel *Label77;
        TLabel *Label76;
        TPanel *pnlStatus;
        TImage *Image1;
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
        TShape *Shape8;
        TLabel *lblLista;
        TLabel *lblBufferEx;
        TLabel *lblTamListaIDs;
        TLabel *lblInicioPrograma;
        TLabel *lblBufferR;
        TLabel *lblBufferW;
        TLabel *lblProgramaAtual;
        TLabel *lblQuedas;
        TLabel *Label46;
        TLabel *lblWatchdogEx;
        TLabel *lblWatchdog;
        TLabel *lblEndereco;
        TPanel *shpAguarde;
        TLabel *lblAguarde;
        TButton *btnReset;
        TTimer *Timer1;
        TTimer *Timer2;
        TShape *Shape11;
        TLabel *Label111;
        TShape *shpLigada_BBP1BB_ex;
        TLabel *Label80;
        TShape *shpRemoto_BBP1BB_ex;
        TLabel *Label81;
        TShape *shpZEROTHRUST_HPCBB_ex;
        TLabel *Label85;
        TShape *shpOLPRESSOK_HPCBB_ex;
        TLabel *Label87;
        TShape *shpOLPBX_HPCBB_ex;
        TLabel *Label88;
        TLabel *Label99;
        TLabel *Label98;
        TLabel *lblPASSOBBPOS_HPCBB_ex;
        TLabel *lblDEMANDAPASSO_HPCBB_ex;
        TLabel *Label94;
        TLabel *Label97;
        TLabel *Label112;
        TShape *shpLigada_BBP1BE_ex;
        TLabel *Label100;
        TShape *shpRemoto_BBP1BE_ex;
        TLabel *Label101;
        TShape *shpZEROTHRUST_HPCBE_ex;
        TLabel *Label102;
        TShape *shpOLPRESSOK_HPCBE_ex;
        TLabel *Label103;
        TShape *shpOLPBX_HPCBE_ex;
        TLabel *Label104;
        TLabel *Label110;
        TLabel *Label109;
        TLabel *lblPASSOBEPOS_HPCBE_ex;
        TShape *Shape21;
        TLabel *lblDEMANDAPASSO_HPCBE_ex;
        TLabel *Label108;
        TLabel *Label107;
        TButton *btnStatus;
        TButton *btnHPC;
        TButton *btnFechar;
        TButton *btnHPCBB_CTRL;
        TButton *btnHPCBE_CTRL;
        TButton *btnHPCBB_UDOMODHID;
        TButton *btnHPCBE_UDOMODHID;
        TButton *btnHPCBB_P1;
        TButton *btnHPCBB_P3;
        TButton *btnHPCBE_P1;
        TButton *btnHPCBE_P3;
        TButton *btnParamPasso;
        TButton *btnAutoP1;
        TImage *Image2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ConexaoWatchTimer(TObject *Sender);
        void __fastcall StartingTimer(TObject *Sender);
        void __fastcall tmrLeituraTimer(TObject *Sender);
        void __fastcall btnLigada_BBP1BBClick(TObject *Sender);
        void __fastcall btnSobrec_BBP1BBClick(TObject *Sender);
        void __fastcall btnRemoto_BBP1BBClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMLIG_BBP1BBClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMDES_BBP1BBClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMLI_BBP1BBClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMDE_BBP1BBClick(TObject *Sender);
        void __fastcall btnFILT21BPDIFAL_HPCBBClick(TObject *Sender);
        void __fastcall btnFILT21APDIFAL_HPCBBClick(TObject *Sender);
        void __fastcall btnOLPRESSOK_HPCBBClick(TObject *Sender);
        void __fastcall btnZEROTHRUST_HPCBBClick(TObject *Sender);
        void __fastcall btnPASSOBBPOS_HPCBBClick(TObject *Sender);
        void __fastcall btnDEMANDAPASSO_HPCBBClick(TObject *Sender);
        void __fastcall btnLigada_BBP3BBClick(TObject *Sender);
        void __fastcall btnRemoto_BBP3BBClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMLIG_BBP3BBClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMDES_BBP3BBClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMLI_BBP3BBClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMDE_BBP3BBClick(TObject *Sender);
        void __fastcall btnEmAut_BBP3BBClick(TObject *Sender);
        void __fastcall btnMANRPMBXSCM_HPCBBClick(TObject *Sender);
        void __fastcall btnCTRPRIFALHA_HPCBBClick(TObject *Sender);
        void __fastcall tmrPartir_BBP1_HPCBBTimer(TObject *Sender);
        void __fastcall tmrParar_BBP1_HPCBBTimer(TObject *Sender);
        void __fastcall btnCTRBKPEMOPERACAO_HPCBBClick(TObject *Sender);
        void __fastcall btnFILT2PDIFAL_HPCBBClick(TObject *Sender);
        void __fastcall btnFILT1PDIFAL_HPCBBClick(TObject *Sender);
        void __fastcall btnOLPBX_HPCBBClick(TObject *Sender);
        void __fastcall btnOLTEMP_HPCBBClick(TObject *Sender);
        void __fastcall btnOLPRESS_HPCBBClick(TObject *Sender);
        void __fastcall btnTQGRAVNIVELBAIXO_HPCBBClick(TObject *Sender);
        void __fastcall btnLigada_BBP1BEClick(TObject *Sender);
        void __fastcall btnSobrec_BBP1BEClick(TObject *Sender);
        void __fastcall btnRemoto_BBP1BEClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMLIG_BBP1BEClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMDES_BBP1BEClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMLI_BBP1BEClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMDE_BBP1BEClick(TObject *Sender);
        void __fastcall btnFILT21BPDIFAL_HPCBEClick(TObject *Sender);
        void __fastcall btnFILT21APDIFAL_HPCBEClick(TObject *Sender);
        void __fastcall btnOLPRESSOK_HPCBEClick(TObject *Sender);
        void __fastcall btnZEROTHRUST_HPCBEClick(TObject *Sender);
        void __fastcall btnPASSOBEPOS_HPCBEClick(TObject *Sender);
        void __fastcall btnDEMANDAPASSO_HPCBEClick(TObject *Sender);
        void __fastcall btnLigada_BBP3BEClick(TObject *Sender);
        void __fastcall btnRemoto_BBP3BEClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMLIG_BBP3BEClick(TObject *Sender);
        void __fastcall btnAUTOHDWSCMDES_BBP3BEClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMLI_BBP3BEClick(TObject *Sender);
        void __fastcall btnPRDEMERGSCMDE_BBP3BEClick(TObject *Sender);
        void __fastcall btnEmAut_BBP3BEClick(TObject *Sender);
        void __fastcall btnMANRPMBXSCM_HPCBEClick(TObject *Sender);
        void __fastcall btnCTRPRIFALHA_HPCBEClick(TObject *Sender);
        void __fastcall tmrPartir_BBP1_HPCBETimer(TObject *Sender);
        void __fastcall tmrParar_BBP1_HPCBETimer(TObject *Sender);
        void __fastcall btnCTRBKPEMOPERACAO_HPCBEClick(TObject *Sender);
        void __fastcall btnFILT2PDIFAL_HPCBEClick(TObject *Sender);
        void __fastcall btnFILT1PDIFAL_HPCBEClick(TObject *Sender);
        void __fastcall btnOLPBX_HPCBEClick(TObject *Sender);
        void __fastcall btnOLTEMP_HPCBEClick(TObject *Sender);
        void __fastcall btnOLPRESS_HPCBEClick(TObject *Sender);
        void __fastcall btnTQGRAVNIVELBAIXO_HPCBEClick(TObject *Sender);
        void __fastcall tmrPressurizarHPCBBTimer(TObject *Sender);
        void __fastcall tmrDespressurizarHPCBBTimer(TObject *Sender);
        void __fastcall tmrDespressurizarHPCBETimer(TObject *Sender);
        void __fastcall tmrPressurizarHPCBETimer(TObject *Sender);
        void __fastcall btnPartir_BBP1BBClick(TObject *Sender);
        void __fastcall btnParar_BBP1BBClick(TObject *Sender);
        void __fastcall btnPartir_BBP1BEClick(TObject *Sender);
        void __fastcall btnParar_BBP1BEClick(TObject *Sender);
        void __fastcall tmrReconectaTimer(TObject *Sender);
        void __fastcall ListaTimer(TObject *Sender);
        void __fastcall btnResetClick(TObject *Sender);
        void __fastcall tmrPassoBBTimer(TObject *Sender);
        void __fastcall tmrPassoBETimer(TObject *Sender);
        void __fastcall btnEmAut_BBP1BBClick(TObject *Sender);
        void __fastcall btnEmAut_BBP1BEClick(TObject *Sender);
        void __fastcall btnSobrec_BBP3BEClick(TObject *Sender);
        void __fastcall btnSobrec_BBP3BBClick(TObject *Sender);
        void __fastcall cmdInbirCMDBBClick(TObject *Sender);
        void __fastcall cmdInbirPRESSBBClick(TObject *Sender);
        void __fastcall cmdInbirCMDBEClick(TObject *Sender);
        void __fastcall cmdInbirPRESSBEClick(TObject *Sender);
        void __fastcall AjusteParamPasso1Click(TObject *Sender);
        void __fastcall mnuHPCBBClick(TObject *Sender);
        void __fastcall mnuHPCBEClick(TObject *Sender);
        void __fastcall btnErro_BBClick(TObject *Sender);
        void __fastcall btnErro_BEClick(TObject *Sender);
        void __fastcall tmrErroTimer(TObject *Sender);
        void __fastcall tmrHPCBB_AutoTimer(TObject *Sender);
        void __fastcall tmrHPCBE_AutoTimer(TObject *Sender);
        void __fastcall mnuParamAutoClick(TObject *Sender);
        void __fastcall btnStatusClick(TObject *Sender);
        void __fastcall btnHPCClick(TObject *Sender);
        void __fastcall btnHPCBB_CTRLClick(TObject *Sender);
        void __fastcall btnHPCBE_CTRLClick(TObject *Sender);
        void __fastcall btnHPCBB_UDOMODHIDClick(TObject *Sender);
        void __fastcall btnHPCBB_P1Click(TObject *Sender);
        void __fastcall btnHPCBB_P3Click(TObject *Sender);
        void __fastcall btnHPCBE_UDOMODHIDClick(TObject *Sender);
        void __fastcall btnHPCBE_P1Click(TObject *Sender);
        void __fastcall btnHPCBE_P3Click(TObject *Sender);
        void __fastcall btnFecharClick(TObject *Sender);
        void __fastcall btnParamPassoClick(TObject *Sender);
        void __fastcall btnAutoP1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
