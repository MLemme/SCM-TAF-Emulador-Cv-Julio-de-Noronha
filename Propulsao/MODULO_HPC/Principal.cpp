//---------------------------------------------------------------------------
//***************************************************************************
//MAURICIO ANDRADE LEMME - ANALISTA DE SISTEMAS J2
//IPqM - INSTITUTO DE PESQUISAS DA MARINHA
//GSD - GRUPO DE SISTEMAS DIGITAIS
//FUNDEP - FUNDA��O DE DESENVOLVIMENTO DA PESQUISA

//EMULADOR DE SINAIS DA PROPULS�O
//NAVIO MODELO.....: V-32 JULIO DE NORONHA (INHAUMA)
//USU�RIO FINAL....: EQUIPE CLP
//VERS�O INICIAL...: V001b
//M�DULO...........: HPC
//DATA DE IN�CIO...: 01.07.2015
//DATA DE PROT�TIPO: 24.09.2015
//DATA DE T�RMINO..: 28.08.2015
//DATA DE ATUALIZ..:  30.06.2023
//DESIGNA��O.......: ESTE M�DULO DO SOFTWARE TEM COMO OBJETIVO EMULAR O FUNCIONAMENTO DO HPC BB
//EM COPARCERIA DESTE M�DULO ESTA O M�DULO DE COMUNICA��O MODBUS DE AUTORIA DO
//FUNCION�RIO F�BIO TEIXEIRA, SUA IMPLEMENTA��O � DESCONHECIDA
//***************************************************************************
#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
//#include "TModBusScanner.cpp" /* DRIVER MODBUS */
#include "ModBusDriverLib\TModBusTCPDriver.cpp"
#include "CtrlPasso.h"
#include "CtrlPress.h"

//----------------- ENDERE�OS DOS EQUIPAMENTOS -----------------
//--------------------------- UDOHPC ---------------------------
String PC_HA_HPCBB_UDOHPC_PASSOBBPOS            = "%MF6172";
String PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL         = "%MW6025.12";
String PC_HL_HPCBB_UDOHPC_FILT21APDIFAL         = "%MW6025.11";
String PC_HL_HPCBB_UDOHPC_ZEROTHRUST            = "%MW6025.10";
String PC_HL_HPCBB_UDOHPC_OLPRESSOK             = "%MW6025.9";
//--------------------------- TQGRAV ---------------------------
String PC_HL_HPCBB_TQGRAV_NIVELBAIXO            = "%MW6025.8";
//--------------------------- HDWSCM ---------------------------
String CP_HL_HPCBB_HDWSCM_EMAUTOSCM             = "%MW510.7";
String CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX         = "%MW510.6";
String CP_HL_HPCBB_HDWSCM_LIGARRPMBX            = "%MW510.5";
//--------------------------- BBP3BB ---------------------------
String CP_HL_HPCBB_BBP3BB_LIBPEMERG             = "%MW510.12";
String CP_HL_HPCBB_BBP3BB_MANUAL                = "%MW510.4";
String CP_HL_HPCBB_BBP3BB_PARAREMERG            = "%MW510.3";
String CP_HL_HPCBB_BBP3BB_AUTOMATICO            = "%MW510.2";
String CP_HL_HPCBB_BBP3BB_DESLIGAR              = "%MW510.1";
String CP_HL_HPCBB_BBP3BB_LIGAR                 = "%MW510.0";
String PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE         = "%MW6027.11";
String PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI         = "%MW6027.10";
String PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES         = "%MW6027.9";
String PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG         = "%MW6027.8";
String PC_HL_HPCBB_BBP3BB_SOBRECARGA            = "%MW6025.7";
String PC_HL_HPCBB_BBP3BB_EMAUT                 = "%MW6025.6";
String PC_HL_HPCBB_BBP3BB_EMREM                 = "%MW6025.5";
String PC_HL_HPCBB_BBP3BB_LIGADO                = "%MW6025.4";
//--------------------------- BBP1BB ---------------------------
String CP_HL_HPCBB_BBP1BB_LIBPEMERG             = "%MW510.11";
String CP_HL_HPCBB_BBP1BB_MANUAL                = "%MW509.15";
String CP_HL_HPCBB_BBP1BB_PARAREMERG            = "%MW509.14";
String CP_HL_HPCBB_BBP1BB_AUTOMATICO            = "%MW509.13";
String CP_HL_HPCBB_BBP1BB_DESLIGAR              = "%MW509.12";
String CP_HL_HPCBB_BBP1BB_LIGAR                 = "%MW509.11";
String PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE         = "%MW6027.7";
String PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI         = "%MW6027.6";
String PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES         = "%MW6027.5";
String PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG         = "%MW6027.4";
String PC_HL_HPCBB_BBP1BB_EMAUTOLOCAL           = "%MW6025.3";
String PC_HL_HPCBB_BBP1BB_EMREM                 = "%MW6025.2";
String PC_HL_HPCBB_BBP1BB_SOBREC                = "%MW6025.1";
String PC_HL_HPCBB_BBP1BB_LIGADO                = "%MW6025.0";
//--------------------------- MODHID ---------------------------
String PC_HA_HPCBB_MODHID_OLTEMP                = "%MF6168";
String PC_HA_HPCBB_MODHID_OLPRESS               = "%MF6166";
String PC_HL_HPCBB_MODHID_OLPBX                 = "%MW6025.15";
String PC_HL_HPCBB_MODHID_FILT2PDIFAL           = "%MW6025.14";
String PC_HL_HPCBB_MODHID_FILT1PDIFAL           = "%MW6025.13";
//--------------------------- CTRPRI ---------------------------
String CP_HA_HPCBB_CTRPRI_DEMANDAPASSO          = "%MW529";
String PC_HL_HPCBB_CTRPRI_MANRPMBXSCM           = "%MW6026.9";
String PC_HL_HPCBB_CTRPRI_FALHA                 = "%MW6026.6";
//--------------------------- CTRBKP ---------------------------
String PC_HL_HPCBB_CTRBKP_EMOPERACAO            = "%MW6026.5";
//--------------------------- MODHID ---------------------------
String PC_HA_HPCBE_MODHID_OLTEMP                = "%MF6164";
String PC_HA_HPCBE_MODHID_OLPRESS               = "%MF6162";
String PC_HL_HPCBE_MODHID_OLPBX                 = "%MW6024.15";
String PC_HL_HPCBE_MODHID_FILT2PDIFAL           = "%MW6024.14";
String PC_HL_HPCBE_MODHID_FILT1PDIFAL           = "%MW6024.13";
//--------------------------- CTRPRI ---------------------------
String CP_HA_HPCBE_CTRPRI_DEMANDAPASSO          = "%MW528";
String PC_HL_HPCBE_CTRPRI_MANRPMBXSCM           = "%MW6026.8";
String PC_HL_HPCBE_CTRPRI_FALHA                 = "%MW6026.7";
//--------------------------- CTRBKP ---------------------------
String PC_HL_HPCBE_CTRBKP_EMOPERACAO            = "%MW6026.4";
//--------------------------- UDOHPC ---------------------------
String PC_HA_HPCBE_UDOHPC_PASSOBEPOS            = "%MF6170";
String PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL         = "%MW6024.12";
String PC_HL_HPCBE_UDOHPC_FILT21APDIFAL         = "%MW6024.11";
String PC_HL_HPCBE_UDOHPC_ZEROTHRUST            = "%MW6024.10";
String PC_HL_HPCBE_UDOHPC_OLPRESSOK             = "%MW6024.9";
//--------------------------- TQGRAV ---------------------------
String PC_HL_HPCBE_TQGRAV_NIVELBAIXO            = "%MW6024.8";
//--------------------------- HDWSCM ---------------------------
String CP_HL_HPCBE_HDWSCM_EMAUTOSCM             = "%MW509.10";
String CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX         = "%MW509.9";
String CP_HL_HPCBE_HDWSCM_LIGARRPMBX            = "%MW509.8";
//--------------------------- BBP3BE ---------------------------
String CP_HL_HPCBE_BBP3BE_LIBPEMERG             = "%MW510.10";
String CP_HL_HPCBE_BBP3BE_MANUAL                = "%MW509.7";
String CP_HL_HPCBE_BBP3BE_PARAREMERG            = "%MW509.6";
String CP_HL_HPCBE_BBP3BE_AUTOMATICO            = "%MW509.5";
String CP_HL_HPCBE_BBP3BE_DESLIGAR              = "%MW509.4";
String CP_HL_HPCBE_BBP3BE_LIGAR                 = "%MW509.3";
String PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE         = "%MW6027.3";
String PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI         = "%MW6027.2";
String PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES         = "%MW6027.1";
String PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG         = "%MW6027.0";
String PC_HL_HPCBE_BBP3BE_SOBRECARGA            = "%MW6024.7";
String PC_HL_HPCBE_BBP3BE_EMAUT                 = "%MW6024.6";
String PC_HL_HPCBE_BBP3BE_EMREM                 = "%MW6024.5";
String PC_HL_HPCBE_BBP3BE_LIGADO                = "%MW6024.4";
//--------------------------- BBP1BE ---------------------------
String CP_HL_HPCBE_BBP1BE_LIBPEMERG             = "%MW510.9";
String PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE         = "%MW6026.15";
String PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI         = "%MW6026.14";
String PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES         = "%MW6026.13";
String PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG         = "%MW6026.12";
String PC_HL_HPCBE_BBP1BE_EMAUTOLOCAL           = "%MW6024.3";
String PC_HL_HPCBE_BBP1BE_EMREM                 = "%MW6024.2";
String PC_HL_HPCBE_BBP1BE_SOBREC                = "%MW6024.1";
String PC_HL_HPCBE_BBP1BE_LIGADO                = "%MW6024.0";
String CP_HL_HPCBE_BBP1BE_MANUAL                = "%MW509.2";
String CP_HL_HPCBE_BBP1BE_PARAREMERG            = "%MW509.1";
String CP_HL_HPCBE_BBP1BE_AUTOMATICO            = "%MW509.0";
String CP_HL_HPCBE_BBP1BE_DESLIGAR              = "%MW508.15";
String CP_HL_HPCBE_BBP1BE_LIGAR                 = "%MW508.14";
//--------------------------- MODSBE ---------------------------
String PC_HA_ERSBE_MODSBE_EIXOBERPM             = "%MF6154";
//--------------------------- MODSBB ---------------------------
String PC_HA_ERSBB_MODSBB_EIXOBBRPM             = "%MF6156";
//------------------- VARIAVEIS DOS INTERNAS -------------------
String IP              = "120.40.0.1";
String CONTADOR_CONEXAO= "%MW33000";
String NomeForm        = "HPC";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;
int    lista           = 0;

bool  ativademanda_HPCBB = true;
float calib_y1_demandapasso_HPCBB = 2000.0;
float calib_x1_demandapasso_HPCBB = -100.0;
float calib_y2_demandapasso_HPCBB = 10000.0;
float calib_x2_demandapasso_HPCBB = 100.0;
bool  ativademanda_HPCBE = true;
float calib_y1_demandapasso_HPCBE = 2000.0;
float calib_x1_demandapasso_HPCBE = -100.0;
float calib_y2_demandapasso_HPCBE = 10000.0;
float calib_x2_demandapasso_HPCBE = 100.0;
float pressao_modhid_hpcbb = 0.0;
float pressao_modhid_hpcbe = 0.0;

bool  nao_atender_cmd_bb = false;
bool  nao_pressurizar_bb = false;

bool  nao_atender_cmd_be = false;
bool  nao_pressurizar_be = false;

bool  emauto_p1_bb = false;
bool  emauto_p1_be = false;

float vlr_press_auto_bb = 10.0;
float vlr_press_auto_be = 10.0;

float vlr_press_alar_bb = 1.0;
float vlr_press_alar_be = 1.0;

float vlr_press_atua_bb = 1.5;
float vlr_press_atua_be = 1.5;

float vlr_press_oper_bb = 12.0;
float vlr_press_oper_be = 12.0;

float rpm_eixo_bb = 0.0;
float rpm_eixo_be = 0.0;

float valor_min_rpm_eixo_bb = 50.0;
float valor_min_rpm_eixo_be = 50.0;

//-------------------- PARAM. PASSO --------------------
//LEMBRAR DE SE ALTERAR AQUI TAMB�M ALTERAR
//NO FORM DE CONTROLE / VALORES ORIGINAIS
float PASSO_BE_DIF_AV_1 = 5;
float PASSO_BE_INC_AV_1 = 4;
float PASSO_BE_DIF_AV_2 = 1;
float PASSO_BE_INC_AV_2 = 2;
float PASSO_BE_DIF_AV_3 = 0.01;
float PASSO_BE_INC_AV_3 = 0.5;

float PASSO_BE_DIF_AR_1 = 5;
float PASSO_BE_INC_AR_1 = 4;
float PASSO_BE_DIF_AR_2 = 1;
float PASSO_BE_INC_AR_2 = 2;
float PASSO_BE_DIF_AR_3 = 0.01;
float PASSO_BE_INC_AR_3 = 0.5;

float PASSO_BB_DIF_AV_1 = 5;
float PASSO_BB_INC_AV_1 = 4;
float PASSO_BB_DIF_AV_2 = 1;
float PASSO_BB_INC_AV_2 = 2;
float PASSO_BB_DIF_AV_3 = 0.01;
float PASSO_BB_INC_AV_3 = 0.5;

float PASSO_BB_DIF_AR_1 = 5;
float PASSO_BB_INC_AR_1 = 4;
float PASSO_BB_DIF_AR_2 = 1;
float PASSO_BB_INC_AR_2 = 2;
float PASSO_BB_DIF_AR_3 = 0.01;
float PASSO_BB_INC_AR_3 = 0.5;

float Erro_BB = 0;
float Erro_BE = 0;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;
//INCIALIZA��O DO DRIVER
//TModBusScanner CLP ( frmPrincipal, QUANTUM, 2, 2 );
TModBusTCPDriver CLP ( frmPrincipal, IP, QUANTUM);

//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
        : TForm(Owner)
{
//CADASTROS DOS ENDERE�OS UTILIZADOS
//--------------------------- UDOHPC ---------------------------
/*	CLP.CadastraLeitura(PC_HA_HPCBB_UDOHPC_PASSOBBPOS);
	CLP.CadastraLeitura(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL);
	CLP.CadastraLeitura(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL);
	CLP.CadastraLeitura(PC_HL_HPCBB_UDOHPC_ZEROTHRUST);
	CLP.CadastraLeitura(PC_HL_HPCBB_UDOHPC_OLPRESSOK);
//--------------------------- TQGRAV ---------------------------
	CLP.CadastraLeitura(PC_HL_HPCBB_TQGRAV_NIVELBAIXO);
//--------------------------- HDWSCM ---------------------------
	CLP.CadastraLeitura(CP_HL_HPCBB_HDWSCM_EMAUTOSCM);
	CLP.CadastraLeitura(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX);
	CLP.CadastraLeitura(CP_HL_HPCBB_HDWSCM_LIGARRPMBX);
//--------------------------- BBP3BB ---------------------------
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP3BB_LIBPEMERG);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP3BB_MANUAL);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP3BB_PARAREMERG);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP3BB_AUTOMATICO);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP3BB_DESLIGAR);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP3BB_LIGAR);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES);
	//CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_AUTOHDWSCM);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_EMAUT);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_EMREM);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP3BB_LIGADO);
//--------------------------- BBP1BB ---------------------------
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP1BB_LIBPEMERG);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP1BB_MANUAL);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP1BB_PARAREMERG);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP1BB_AUTOMATICO);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP1BB_DESLIGAR);
	CLP.CadastraLeitura(CP_HL_HPCBB_BBP1BB_LIGAR);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES);
	//CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_AUTOHDWSCM);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_EMREM);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_SOBREC);
	CLP.CadastraLeitura(PC_HL_HPCBB_BBP1BB_LIGADO);
//--------------------------- MODHID ---------------------------
	CLP.CadastraLeitura(PC_HA_HPCBB_MODHID_OLTEMP);
	CLP.CadastraLeitura(PC_HA_HPCBB_MODHID_OLPRESS);
	CLP.CadastraLeitura(PC_HL_HPCBB_MODHID_OLPBX);
	CLP.CadastraLeitura(PC_HL_HPCBB_MODHID_FILT2PDIFAL);
	CLP.CadastraLeitura(PC_HL_HPCBB_MODHID_FILT1PDIFAL);
//--------------------------- CTRPRI ---------------------------
	CLP.CadastraLeitura(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO);
	CLP.CadastraLeitura(PC_HL_HPCBB_CTRPRI_MANRPMBXSCM);
	CLP.CadastraLeitura(PC_HL_HPCBB_CTRPRI_FALHA);
//--------------------------- CTRBKP ---------------------------
	CLP.CadastraLeitura(PC_HL_HPCBB_CTRBKP_EMOPERACAO);
//--------------------------- MODHID ---------------------------
	CLP.CadastraLeitura(PC_HA_HPCBE_MODHID_OLTEMP);
	CLP.CadastraLeitura(PC_HA_HPCBE_MODHID_OLPRESS);
	CLP.CadastraLeitura(PC_HL_HPCBE_MODHID_OLPBX);
	CLP.CadastraLeitura(PC_HL_HPCBE_MODHID_FILT2PDIFAL);
	CLP.CadastraLeitura(PC_HL_HPCBE_MODHID_FILT1PDIFAL);
//--------------------------- CTRPRI ---------------------------
	CLP.CadastraLeitura(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO);
	CLP.CadastraLeitura(PC_HL_HPCBE_CTRPRI_MANRPMBXSCM);
	CLP.CadastraLeitura(PC_HL_HPCBE_CTRPRI_FALHA);
//--------------------------- CTRBKP ---------------------------
	CLP.CadastraLeitura(PC_HL_HPCBE_CTRBKP_EMOPERACAO);
//--------------------------- UDOHPC ---------------------------
	CLP.CadastraLeitura(PC_HA_HPCBE_UDOHPC_PASSOBEPOS);
	CLP.CadastraLeitura(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL);
	CLP.CadastraLeitura(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL);
	CLP.CadastraLeitura(PC_HL_HPCBE_UDOHPC_ZEROTHRUST);
	CLP.CadastraLeitura(PC_HL_HPCBE_UDOHPC_OLPRESSOK);
//--------------------------- TQGRAV ---------------------------
	CLP.CadastraLeitura(PC_HL_HPCBE_TQGRAV_NIVELBAIXO);
//--------------------------- HDWSCM ---------------------------
	CLP.CadastraLeitura(CP_HL_HPCBE_HDWSCM_EMAUTOSCM);
	CLP.CadastraLeitura(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX);
	CLP.CadastraLeitura(CP_HL_HPCBE_HDWSCM_LIGARRPMBX);
//--------------------------- BBP3BE ---------------------------
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP3BE_LIBPEMERG);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP3BE_MANUAL);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP3BE_PARAREMERG);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP3BE_AUTOMATICO);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP3BE_DESLIGAR);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP3BE_LIGAR);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES);
	//CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_AUTOHDWSCM);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_EMAUT);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_EMREM);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP3BE_LIGADO);
//--------------------------- BBP1BE ---------------------------
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP1BE_LIBPEMERG);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES);
	//CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_AUTOHDWSCM);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_EMREM);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_SOBREC);
	CLP.CadastraLeitura(PC_HL_HPCBE_BBP1BE_LIGADO);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP1BE_MANUAL);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP1BE_PARAREMERG);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP1BE_AUTOMATICO);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP1BE_DESLIGAR);
	CLP.CadastraLeitura(CP_HL_HPCBE_BBP1BE_LIGAR);
 */
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{
        AnsiString TimeStamp;
//ABERTURA DA CONEX�O COM CLP
        CLP.Open(IP);
//IN�CIO DA INICIALIZA��O
        frmPrincipal->Caption = NomeForm + " - Carregando";
        frmPrincipal->Top = 0;
        frmPrincipal->Left = 0;
        frmPrincipal->Height = 600;
        frmPrincipal->Width = 800;

        //pnlHPCBB->Top = 8;
        //pnlHPCBB->Left = 8;

        //pnlHPCBE->Top = 8;
        //pnlHPCBE->Left = 8;

        pnlStatus->Visible = true;

        pnlHPCBB_CTRL->Visible = false;
        pnlHPCBB_UDOMODHID->Visible = false;
        pnlHPCBB_P1->Visible = false;
        pnlHPCBB_P3->Visible = false;

        btnHPCBB_CTRL->Visible = false;
        btnHPCBB_UDOMODHID->Visible = false;
        btnHPCBB_P1->Visible = false;
        btnHPCBB_P3->Visible = false;

        pnlHPCBE_CTRL->Visible = false;
        pnlHPCBE_UDOMODHID->Visible = false;
        pnlHPCBE_P1->Visible = false;
        pnlHPCBE_P3->Visible = false;

        btnHPCBE_CTRL->Visible = false;
        btnHPCBE_UDOMODHID->Visible = false;
        btnHPCBE_P1->Visible = false;
        btnHPCBE_P3->Visible = false;

        DateTimeToString( TimeStamp, AnsiString( "hh:nn:ss" ), Now() );

        lblInit1->Caption = "Incializando";
        lblInit2->Caption = "Incializando";
        lblInit3->Caption = "Incializando";
        lblInit4->Caption = "Incializando";
        lblInit5->Caption = "Incializando";
        lblInit6->Caption = "Incializando";
        lblInit7->Caption = "Incializando";
        lblInit8->Caption = "Incializando";
        lblInit9->Caption = "Incializando";
        lblInit10->Caption = "Incializando";
        lblInit11->Caption = "Incializando";
        lblInit12->Caption = "Incializando";
        lblInit13->Caption = "Incializando";
        lblInit14->Caption = "Incializando";
        lblInit15->Caption = "Incializando";
        lblInit16->Caption = "Incializando";

        lblInicioPrograma->Caption = TimeStamp;
        lblInicioPrograma->Visible = true;
        lblEndereco->Caption = CONTADOR_CONEXAO;
        lblEndereco->Visible = true;
        lblWatchdogEx->Visible = true;

        Starting->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::ConexaoWatchTimer(TObject *Sender)
{
//TIMER DE VERIFICA��O DE CONEX�O
        lblProgramaAtual->Visible = true;
        lblTamListaIDs->Visible = true;
        lblQuedas->Visible = true;
        lblWatchdog->Visible = true;

        if ( VALOR_ANTIGO != CLP.RD( CONTADOR_CONEXAO ) ){
                //contador_ok = true;
                contador_scan = 0;
        }
        else{
                //contador_ok = false;
                if ( contador_scan <= 3 ){
                        contador_scan++;
                }
        }

         if ( contador_scan <= 3 ){
                contador_ok = true;
        }
        else{
                contador_ok = false;
        }

        lblTamListaIDs->Caption = "ID Usados: " + String (CLP._thread->listaIDsUsados.size());

        if (CLP.Conectado() == 0 ){ //|| contador_ok == false){
               perdaconexao = true;
               numeroquedas++;
               CLP.Close();
               //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Inativa";
               frmPrincipal->Caption = NomeForm + " - Pronto - Leitura Inativa";
               tmrLeitura->Enabled = false;
               if (tmrReconecta->Enabled == false){
                       tmrReconecta->Enabled = true;
               }
        }
        if (CLP.Conectado() != 0 && perdaconexao == true ){//&& contador_ok == true){
               perdaconexao = false;
               tmrLeitura->Enabled = true;
               //tmrStarting->Enabled = true;
        }

        if (CLP.Conectado() != 0 && perdaconexao == false ){//&& contador_ok == true){
                switch(Varredura){
                        case 0:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                break;
                        case 1:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                break;
                        case 2:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                break;
                        case 3:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                break;
                        case 4:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                break;
                        case 5:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                break;
                        case 6:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                break;
                        case 7:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                break;
                        case 8:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                break;
                        case 9:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                Varredura = -1;
                                break;
               }
               Varredura++;
        }
//        lblLista->Caption = CLP._listaCmdSimples.size();
//        lblLista->Caption = CLP.TamBufWR();
//        lblLista->Caption = CLP._thread->buffersRecebidos.size();
//        lblConexao->Refresh();

        AnsiString TimeStamp;

        DateTimeToString( TimeStamp, AnsiString( "hh:nn:ss" ), Now() );

        lblProgramaAtual->Caption = TimeStamp;

        lblQuedas->Caption = "Fall: " + String (numeroquedas);

        VALOR_ANTIGO = CLP.RD( CONTADOR_CONEXAO );
        lblWatchdog->Caption = VALOR_ANTIGO;

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::StartingTimer(TObject *Sender)
{
//--------------------- INICIA ANAL�GICAS ---------------------
        CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS , 0);
        prbPASSOBBPOS_HPCBB->Max = 100 * 1000;
        prbPASSOBBPOS_HPCBB->Min = -100 * 1000;


        CLP.WR( PC_HA_HPCBB_MODHID_OLTEMP , 0);
        prbOLTEMP_HPCBB->Max = 100 * 1000;
        prbOLTEMP_HPCBB->Min = 0;

        CLP.WR( PC_HA_HPCBB_MODHID_OLPRESS , 0);
        prbOLPRESS_HPCBB->Max = 100 * 1000;
        prbOLPRESS_HPCBB->Min = 0;

        CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS , 0);
        prbPASSOBEPOS_HPCBE->Max = 100 * 1000;
        prbPASSOBEPOS_HPCBE->Min = -100 * 1000;

        CLP.WR( PC_HA_HPCBE_MODHID_OLTEMP , 0);
        prbOLTEMP_HPCBE->Max = 100 * 1000;
        prbOLTEMP_HPCBE->Min = 0;

        CLP.WR( PC_HA_HPCBE_MODHID_OLPRESS , 0);
        prbOLPRESS_HPCBE->Max = 100 * 1000;
        prbOLPRESS_HPCBE->Min = 0;

        CLP.WR( PC_HA_HPCBB_MODHID_OLTEMP , 25);

        CLP.WR( PC_HA_HPCBE_MODHID_OLTEMP , 25);


//-------------------------------------------------------------
//---------------------  INICIA DIGITAIS  ---------------------
        /*CLP.WR( VARIAVEL_DIGITAL, 0 OU 1 );*/
        CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG, 0 );
        CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES, 1 );
        CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI, 0 );
        CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE, 1 );
        CLP.WR( PC_HL_HPCBB_BBP1BB_EMREM        , 1 );
        CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO       , 0 );

        CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG, 1 );
        CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES, 0 );
        CLP.WR( PC_HL_HPCBB_BBP3BB_EMAUT        , 1 );
        CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI, 0 );
        CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE, 1 );
        CLP.WR( PC_HL_HPCBB_BBP3BB_EMREM        , 1 );
        CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO       , 0 );

        CLP.WR( PC_HL_HPCBB_UDOHPC_ZEROTHRUST   , 1 );
        CLP.WR( PC_HL_HPCBB_UDOHPC_OLPRESSOK    , 0 );

        CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG, 0 );
        CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES, 1 );
        CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI, 0 );
        CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE, 1 );
        CLP.WR( PC_HL_HPCBE_BBP1BE_EMREM        , 1 );
        CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO       , 0 );

        CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG, 1 );
        CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES, 0 );
        CLP.WR( PC_HL_HPCBE_BBP3BE_EMAUT        , 1 );
        CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI, 0 );
        CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE, 1 );
        CLP.WR( PC_HL_HPCBE_BBP3BE_EMREM        , 1 );
        CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO       , 0 );

        CLP.WR( PC_HL_HPCBE_UDOHPC_ZEROTHRUST   , 1 );
        CLP.WR( PC_HL_HPCBE_UDOHPC_OLPRESSOK    , 0 );

        CLP.WR( PC_HL_HPCBB_MODHID_OLPBX        , 1 );
        CLP.WR( PC_HL_HPCBE_MODHID_OLPBX        , 0 );

        CLP.WR( PC_HL_HPCBB_CTRPRI_FALHA        , 1 );
        CLP.WR( PC_HL_HPCBE_CTRPRI_FALHA        , 1 );

//-------------------------------------------------------------
//-------------------------------------------------------------
//ACIONA TODOS OS ENDERE�OS DE SIMULA��O
        for (int i = 3010; i < 3114; i++){
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0xFFFF);
        }
//-------------------------------------------------------------

        frmPrincipal->Caption = NomeForm + " - Pronto (CLP" + IP + ")";

        tmrLeitura->Enabled = true;

        lblInit1->Caption  = "BBP1BB";
        lblInit2->Caption  = "BBP3BB";
        lblInit3->Caption  = "UDOHPC";
        lblInit4->Caption  = "CTRPRI";
        lblInit5->Caption  = "CTRBKP";
        lblInit6->Caption  = "MODHID";
        lblInit7->Caption  = "TQGRAV";
        lblInit8->Caption  = "HDWSCM";
        lblInit9->Caption  = "BBP1BE";
        lblInit10->Caption = "BBP3BE";
        lblInit11->Caption = "UDOHPC";
        lblInit12->Caption = "CTRPRI";
        lblInit13->Caption = "CTRBKP";
        lblInit14->Caption = "MODHID";
        lblInit15->Caption = "TQGRAV";
        lblInit16->Caption = "HDWSCM";

        lblBufferR->Visible = true;
        lblBufferW->Visible = true;
        lblBufferEx->Visible = true;
        lblLista->Visible = true;

        if (ConexaoWatch->Enabled == false){
                ConexaoWatch->Enabled = true;
        }

        Lista->Enabled = true;
//FIM DA INICIALIZA��O
        Starting->Enabled = false;

        btnReset->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrLeituraTimer(TObject *Sender)
{
float passo_atual;
float referencia;
//TIMER DE ESCRITA, LEITURA E TRATAMENTO DOS SINAIS
//==============================================================================

        rpm_eixo_bb = CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM);

        rpm_eixo_be = CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM);

//==============================================================================
//HPCBB_BBP1BB
	if ( CLP.RD(PC_HL_HPCBB_BBP1BB_LIGADO) == 1 ){
		shpLigada_BBP1BB->Brush->Color = clLime;
                shpLigada_BBP1BB_ex->Brush->Color = clLime;
		btnLigada_BBP1BB->Caption = "Ligado";
	}
	else{
		shpLigada_BBP1BB->Brush->Color = clWhite;
                shpLigada_BBP1BB_ex->Brush->Color = clWhite;
		btnLigada_BBP1BB->Caption = "Parado";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP1BB_SOBREC) == 1 ){
		shpSobrec_BBP1BB->Brush->Color = clRed;
		btnSobrec_BBP1BB->Caption = "Em Sobrec.";
	}
	else{
		shpSobrec_BBP1BB->Brush->Color = clWhite;
		btnSobrec_BBP1BB->Caption = "Sem Sobrec.";
	};

        if ( CLP.RD(PC_HL_HPCBB_BBP1BB_EMREM) == 1 ){
		shpRemoto_BBP1BB->Brush->Color = clNavy;
                shpRemoto_BBP1BB_ex->Brush->Color = clNavy;
		btnRemoto_BBP1BB->Caption = "Remoto";
	}
	else{
		shpRemoto_BBP1BB->Brush->Color = clWhite;
                shpRemoto_BBP1BB_ex->Brush->Color = clWhite;
		btnRemoto_BBP1BB->Caption = "Local";
	};

    if ( CLP.RD(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG) == 1 ){
		shpAUTOHDWSCMLIG_BBP1BB->Brush->Color = clBlue;
		btnAUTOHDWSCMLIG_BBP1BB->Caption = "AUTOHDWSCMLIG";
	}
	else{
		shpAUTOHDWSCMLIG_BBP1BB->Brush->Color = clWhite;
		btnAUTOHDWSCMLIG_BBP1BB->Caption = "� AUTOHDWSCMLIG";
	};

    /*if ( CLP.RD(PC_HL_HPCBB_BBP1BB_AUTOHDWSCM) == 1 ){
		shpAUTOHDWSCM_BBP1BB->Brush->Color = clBlue;
		btnAUTOHDWSCM_BBP1BB->Caption = "AUTOHDWSCM";
	}
	else{
		shpAUTOHDWSCM_BBP1BB->Brush->Color = clWhite;
		btnAUTOHDWSCM_BBP1BB->Caption = "� AUTOHDWSCM";
	}*/

    if ( CLP.RD(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES) == 1 ){
		shpAUTOHDWSCMDES_BBP1BB->Brush->Color = clMaroon;
		btnAUTOHDWSCMDES_BBP1BB->Caption = "AUTOHDWSCMDES";
	}
	else{
		shpAUTOHDWSCMDES_BBP1BB->Brush->Color = clWhite;
		btnAUTOHDWSCMDES_BBP1BB->Caption = "� AUTOHDWSCMDES";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI) == 1 ){
		shpPRDEMERGSCMLI_BBP1BB->Brush->Color = clRed;
		btnPRDEMERGSCMLI_BBP1BB->Caption = "PRDEMERGSCMLI";
	}
	else{
		shpPRDEMERGSCMLI_BBP1BB->Brush->Color = clWhite;
		btnPRDEMERGSCMLI_BBP1BB->Caption = "� PRDEMERGSCMLI";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE) == 1 ){
		shpPRDEMERGSCMDE_BBP1BB->Brush->Color = clBlue;
		btnPRDEMERGSCMDE_BBP1BB->Caption = "PRDEMERGSCMDE";
	}
	else{
		shpPRDEMERGSCMDE_BBP1BB->Brush->Color = clWhite;
		btnPRDEMERGSCMDE_BBP1BB->Caption = "� PRDEMERGSCMDE";
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP1BB_LIGAR) == 1 ){
		shpLigarBBP1BB->Brush->Color = clLime;
                tmrParar_BBP1_HPCBB->Enabled = false;
		if (btnLigada_BBP1BB->Caption == "Parado"  && tmrPartir_BBP1_HPCBB->Enabled == false ){
                        if ( nao_atender_cmd_bb == false ) {
        			tmrPartir_BBP1_HPCBB->Enabled = true;
                        }
		}
	}
	else{
		shpLigarBBP1BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR) == 1 ){
		shpDesligarBBP1BB->Brush->Color = clYellow;
                tmrPartir_BBP1_HPCBB->Enabled = false;
		if (btnLigada_BBP1BB->Caption == "Ligado"  && tmrParar_BBP1_HPCBB->Enabled == false ){
                        if ( nao_atender_cmd_bb == false ) {
        			tmrParar_BBP1_HPCBB->Enabled = true;
                        }
		}
	}
	else{
		shpDesligarBBP1BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO) == 1 ){
		shpAUTOMATICOBBP1BB->Brush->Color = clYellow;
		//if (btnEMAUT_BBP1BB->Caption == "Em Manual"){
		if (btnAUTOHDWSCMLIG_BBP1BB->Caption == "� AUTOHDWSCMLIG"){
			//CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCM, 1 );
			CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG, 1 );
			CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES, 0 );
		}
	}
	else{
		shpAUTOMATICOBBP1BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP1BB_MANUAL) == 1 ){
		shpMANUALBBP1BB->Brush->Color = clYellow;
		//if (btnEMAUT_BBP1BB->Caption == "Em Auto"){
		if (btnAUTOHDWSCMLIG_BBP1BB->Caption == "AUTOHDWSCMLIG"){
                        //CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCM, 0 );
                        CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG, 0 );
                        CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES, 1 );
		}
	}
	else{
		shpMANUALBBP1BB->Brush->Color = clWhite;
	}

	if ( CLP.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG) == 1){
		shpEmerg_BBP1BB->Brush->Color = clRed;
		if (btnLigada_BBP1BB->Caption == "Ligado" || btnPRDEMERGSCMLI_BBP1BB->Caption == "� PRDEMERGSCMLI" ){
                        tmrPartir_BBP1_HPCBB->Enabled = false;
                        if (btnLigada_BBP1BB->Caption == "Ligado"  && tmrParar_BBP1_HPCBB->Enabled == false ){
                                if ( nao_atender_cmd_bb == false ) {
        			        tmrParar_BBP1_HPCBB->Enabled = true;
                                }
	        	}
       			CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 0 );
			CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE, 0 );
                        CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI, 1 );

		}
	}
	else{
		shpEmerg_BBP1BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG) == 1 ){
		shpLibEmerg_BBP1BB->Brush->Color = clRed;
		//if (btnLigada_BBP1BB->Caption == "Ligado"){
		//	CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 0 );
		//}
		if (btnPRDEMERGSCMLI_BBP1BB->Caption == "PRDEMERGSCMLI"){
			CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI, 0 );
			CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE, 1 );
		}
	}
	else{
		shpLibEmerg_BBP1BB->Brush->Color = clWhite;
	};

        if ( CLP.RD(PC_HL_HPCBB_BBP1BB_EMAUTOLOCAL) == 1 ){
		shpEmAut_BBP1BB->Brush->Color = clNavy;
		btnEmAut_BBP1BB->Caption = "Em Auto";
	}
	else{
		shpEmAut_BBP1BB->Brush->Color = clWhite;
		btnEmAut_BBP1BB->Caption = "Em Manual";
	};

        if ((btnAUTOHDWSCMLIG_BBP1BB->Caption == "AUTOHDWSCMLIG") || (btnEmAut_BBP1BB->Caption == "Em Auto")){
                emauto_p1_bb = true;
        }
        else{
                emauto_p1_bb = false;
        }

//==============================================================================
//HPCBB_BBP3BB
	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_LIGADO) == 1 ){
		shpLigada_BBP3BB->Brush->Color = clLime;
		btnLigada_BBP3BB->Caption = "Ligado";
	}
	else{
		shpLigada_BBP3BB->Brush->Color = clWhite;
		btnLigada_BBP3BB->Caption = "Parado";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_EMREM) == 1 ){
		shpRemoto_BBP3BB->Brush->Color = clNavy;
		btnRemoto_BBP3BB->Caption = "Remoto";
	}
	else{
		shpRemoto_BBP3BB->Brush->Color = clWhite;
		btnRemoto_BBP3BB->Caption = "Local";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_EMAUT) == 1 ){
		shpEmAut_BBP3BB->Brush->Color = clNavy;
		btnEmAut_BBP3BB->Caption = "Em Auto";
	}
	else{
		shpEmAut_BBP3BB->Brush->Color = clWhite;
		btnEmAut_BBP3BB->Caption = "Em Manual";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG) == 1 ){
		shpAUTOHDWSCMLIG_BBP3BB->Brush->Color = clBlue;
		btnAUTOHDWSCMLIG_BBP3BB->Caption = "AUTOHDWSCMLIG";
	}
	else{
		shpAUTOHDWSCMLIG_BBP3BB->Brush->Color = clWhite;
		btnAUTOHDWSCMLIG_BBP3BB->Caption = "� AUTOHDWSCMLIG";
	};

	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES) == 1 ){
		shpAUTOHDWSCMDES_BBP3BB->Brush->Color = clMaroon;
		btnAUTOHDWSCMDES_BBP3BB->Caption = "AUTOHDWSCMDES";
	}
	else{
		shpAUTOHDWSCMDES_BBP3BB->Brush->Color = clWhite;
		btnAUTOHDWSCMDES_BBP3BB->Caption = "� AUTOHDWSCMDES";
	};
	
	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI) == 1 ){
		shpPRDEMERGSCMLI_BBP3BB->Brush->Color = clRed;
		btnPRDEMERGSCMLI_BBP3BB->Caption = "PRDEMERGSCMLI";
	}
	else{
		shpPRDEMERGSCMLI_BBP3BB->Brush->Color = clWhite;
		btnPRDEMERGSCMLI_BBP3BB->Caption = "� PRDEMERGSCMLI";
	};
	
	if ( CLP.RD(PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE) == 1 ){
		shpPRDEMERGSCMDE_BBP3BB->Brush->Color = clBlue;
		btnPRDEMERGSCMDE_BBP3BB->Caption = "PRDEMERGSCMDE";
	}
	else{
		shpPRDEMERGSCMDE_BBP3BB->Brush->Color = clWhite;
		btnPRDEMERGSCMDE_BBP3BB->Caption = "� PRDEMERGSCMDE";
	};
	
	if ( CLP.RD(CP_HL_HPCBB_BBP3BB_LIGAR) == 1 ){
		shpLigarBBP3BB->Brush->Color = clLime;
		if (btnLigada_BBP3BB->Caption == "Parado"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO, 1 );
		}
	}
	else{
		shpLigarBBP3BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR) == 1 ){
		shpDesligarBBP3BB->Brush->Color = clYellow;
		if (btnLigada_BBP3BB->Caption == "Ligado"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO, 0 );
		}
	}
	else{
		shpDesligarBBP3BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO) == 1 ){
		shpAUTOMATICOBBP3BB->Brush->Color = clYellow;
		if (btnEmAut_BBP3BB->Caption == "Em Manual"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_EMAUT, 1 );
                }
                if (btnAUTOHDWSCMLIG_BBP3BB->Caption == "� AUTOHDWSCMLIG"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG, 1 );
			CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES, 0 );
		}
	}
	else{
		shpAUTOMATICOBBP3BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG) == 1 ){
		shpEmerg_BBP3BB->Brush->Color = clRed;
		if (btnLigada_BBP3BB->Caption == "Ligado" || btnPRDEMERGSCMLI_BBP3BB->Caption == "� PRDEMERGSCMLI"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO, 0 );
			CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE, 0 );
			CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI, 1 );
		}
	}
	else{
		shpEmerg_BBP3BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP3BB_MANUAL) == 1 ){
		shpMANUALBBP3BB->Brush->Color = clYellow;
		if (btnEmAut_BBP3BB->Caption == "Em Auto"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_EMAUT, 0 );
                }
                if (btnAUTOHDWSCMLIG_BBP3BB->Caption == "AUTOHDWSCMLIG"){
			CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG, 0 );
			CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES, 1 );
		}
	}
	else{
		shpMANUALBBP3BB->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG) == 1 ){
		shpLibEmerg_BBP3BB->Brush->Color = clBlue;
		if (btnPRDEMERGSCMLI_BBP3BB->Caption == "PRDEMERGSCMLI"){
			//CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO, 0 );
                        CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE, 1 );
			CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI, 0 );
		}
	}
	else{
		shpLibEmerg_BBP3BB->Brush->Color = clWhite;
	};

        if ( CLP.RD(PC_HL_HPCBB_BBP3BB_SOBRECARGA) == 1 ){
		shpSobrec_BBP3BB->Brush->Color = clRed;
		btnSobrec_BBP3BB->Caption = "Em Sobrec.";
	}
	else{
		shpSobrec_BBP3BB->Brush->Color = clWhite;
		btnSobrec_BBP3BB->Caption = "Sem Sobrec.";
	};
//==============================================================================
//HPCBB_UDOHPC
	if ( CLP.RD(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL) == 1 ){
		shpFILT21BPDIFAL_HPCBB->Brush->Color = clRed;
		btnFILT21BPDIFAL_HPCBB->Caption = "FILT21BPDIFAL";
	}
	else{
		shpFILT21BPDIFAL_HPCBB->Brush->Color = clWhite;
		btnFILT21BPDIFAL_HPCBB->Caption = "� FILT21BPDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL) == 1 ){
		shpFILT21APDIFAL_HPCBB->Brush->Color = clRed;
		btnFILT21APDIFAL_HPCBB->Caption = "FILT21APDIFAL";
	}
	else{
		shpFILT21APDIFAL_HPCBB->Brush->Color = clWhite;
		btnFILT21APDIFAL_HPCBB->Caption = "� FILT21APDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBB_UDOHPC_ZEROTHRUST) == 1 ){
		shpZEROTHRUST_HPCBB->Brush->Color = clLime;
                shpZEROTHRUST_HPCBB_ex->Brush->Color = clLime;
		btnZEROTHRUST_HPCBB->Caption = "ZEROTHRUST";
	}
	else{
		shpZEROTHRUST_HPCBB->Brush->Color = clWhite;
                shpZEROTHRUST_HPCBB_ex->Brush->Color = clWhite;
		btnZEROTHRUST_HPCBB->Caption = "� ZEROTHRUST";
	};

        if ( CLP.RD(PC_HL_HPCBB_UDOHPC_OLPRESSOK) == 1 ){
		shpOLPRESSOK_HPCBB->Brush->Color = clLime;
                shpOLPRESSOK_HPCBB_ex->Brush->Color = clLime;
		btnOLPRESSOK_HPCBB->Caption = "OLPRESSOK";
	}
	else{
		shpOLPRESSOK_HPCBB->Brush->Color = clWhite;
                shpOLPRESSOK_HPCBB_ex->Brush->Color = clWhite;
		btnOLPRESSOK_HPCBB->Caption = "� OLPRESSOK";
	};

        bool TestaDouble = false;
        double Teste;

        lblPASSOBBPOS_HPCBB->Caption = CLP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS);
        lblPASSOBBPOS_HPCBB->Caption = FormatFloat("0.##",lblPASSOBBPOS_HPCBB->Caption.ToDouble());
        lblPASSOBBPOS_HPCBB_ex->Caption = lblPASSOBBPOS_HPCBB->Caption;
        prbPASSOBBPOS_HPCBB->Position = CLP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS) * 1000;

        try{
                Teste = txtZEROTHRUST_HPCBB->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
        }

        if (txtZEROTHRUST_HPCBB->Text.IsEmpty() != true && TestaDouble == false){
                if ( FormatFloat("0.##",CLP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS)) != FormatFloat("0.##",txtZEROTHRUST_HPCBB->Text.ToDouble()) && CLP.RD(PC_HL_HPCBB_UDOHPC_ZEROTHRUST) == 1){
                        if (abs(CLP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS)) > txtZEROTHRUST_HPCBB->Text.ToDouble()){
                                if (CLP.RD( PC_HL_HPCBB_UDOHPC_ZEROTHRUST) != 0 ){
	                	        CLP.WR( PC_HL_HPCBB_UDOHPC_ZEROTHRUST, 0 );
                            }
                        }
        	}
	        else{
                        //if (FormatFloat("0.##",CLP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS)) == FormatFloat("0.##",txtZEROTHRUST_HPCBB->Text.ToDouble()) && CLP.RD(PC_HL_HPCBB_UDOHPC_ZEROTHRUST) == 0){
                                if (abs(CLP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS)) <= txtZEROTHRUST_HPCBB->Text.ToDouble()){
                                        if (CLP.RD( PC_HL_HPCBB_UDOHPC_ZEROTHRUST) != 1 ){
	        	                       CLP.WR( PC_HL_HPCBB_UDOHPC_ZEROTHRUST, 1 );
                                        }
                                }
                        //}
	        };
        };


//==============================================================================
//HPCBB_UDOHPC

        lblDEMANDAPASSO_HPCBB->Caption = (((calib_x2_demandapasso_HPCBB - calib_x1_demandapasso_HPCBB)*(CLP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO) - calib_y1_demandapasso_HPCBB))/(calib_y2_demandapasso_HPCBB - calib_y1_demandapasso_HPCBB)) + calib_x1_demandapasso_HPCBB;
        lblDEMANDAPASSO_HPCBB_ex->Caption = lblDEMANDAPASSO_HPCBB->Caption;
        if (ativademanda_HPCBB == true) {
                if ( ((float) ((int) (lblDEMANDAPASSO_HPCBB->Caption.ToDouble() * 10))/10) !=  ((float) ((int) (lblPASSOBBPOS_HPCBB->Caption.ToDouble() * 10))/10) ) {
                        //if ( ((float) ((int) (CLP.RD( PC_HA_HPCBB_UDOHPC_PASSOBBPOS) * 10))/10) !=  ((float) ((int) (lblDEMANDAPASSO_HPCBB->Caption.ToDouble() * 10))/10) ) {
                        //if ((int) CLP.RD( PC_HA_HPCBB_UDOHPC_PASSOBBPOS) != (int) lblDEMANDAPASSO_HPCBB->Caption.ToDouble() ){
                        passo_atual = CLP.RD( PC_HA_HPCBB_UDOHPC_PASSOBBPOS);
                        referencia = ((float) ((int) (lblDEMANDAPASSO_HPCBB->Caption.ToDouble() * 10)))/10  ;
                        if (fabs(passo_atual - referencia ) > 0.001) {
                                //CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, lblDEMANDAPASSO_HPCBB->Caption.ToDouble() );
                                if (tmrPassoBB->Enabled == false){
                                        tmrPassoBB->Enabled = true;
                                }
                        }
                        else{
                                tmrPassoBB->Enabled = false;
                        }

                }
        };

        if ( CLP.RD(PC_HL_HPCBB_CTRPRI_MANRPMBXSCM) == 1 ){
		shpMANRPMBXSCM_HPCBB->Brush->Color = clYellow;
		btnMANRPMBXSCM_HPCBB->Caption = "MANRPMBXSCM";
	}
	else{
		shpMANRPMBXSCM_HPCBB->Brush->Color = clWhite;
		btnMANRPMBXSCM_HPCBB->Caption = "� MANRPMBXSCM";
	};

        if ( CLP.RD(PC_HL_HPCBB_CTRPRI_FALHA) == 0 ){
		shpbtnCTRPRIFALHA_HPCBB->Brush->Color = clRed;
		btnCTRPRIFALHA_HPCBB->Caption = "Em Falha";
	}
	else{
		shpbtnCTRPRIFALHA_HPCBB->Brush->Color = clWhite;
		btnCTRPRIFALHA_HPCBB->Caption = "Sem Falha";
	};
//==============================================================================
//HPCBB_CTRBKP

        if ( CLP.RD(PC_HL_HPCBB_CTRBKP_EMOPERACAO) == 1 ){
                shpCTRBKPEMOPERACAO_HPCBB->Brush->Color = clRed;
		btnCTRBKPEMOPERACAO_HPCBB->Caption = "Em Opera��o";
	}
	else{
                shpCTRBKPEMOPERACAO_HPCBB->Brush->Color = clWhite;
		btnCTRBKPEMOPERACAO_HPCBB->Caption = "Desligado";
	};

//==============================================================================
//HPCBB_MODHID

        if ( CLP.RD(PC_HL_HPCBB_MODHID_FILT2PDIFAL) == 1 ){
                shpFILT2PDIFAL_HPCBB->Brush->Color = clRed;
		btnFILT2PDIFAL_HPCBB->Caption = "FILT2PDIFAL";
	}
	else{
                shpFILT2PDIFAL_HPCBB->Brush->Color = clWhite;
		btnFILT2PDIFAL_HPCBB->Caption = "� FILT2PDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBB_MODHID_FILT1PDIFAL) == 1 ){
                shpFILT1PDIFAL_HPCBB->Brush->Color = clRed;
		btnFILT1PDIFAL_HPCBB->Caption = "FILT1PDIFAL";
	}
	else{
                shpFILT1PDIFAL_HPCBB->Brush->Color = clWhite;
		btnFILT1PDIFAL_HPCBB->Caption = "� FILT1PDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBB_MODHID_OLPBX) == 1 ){
                shpOLPBX_HPCBB->Brush->Color = clRed;
                shpOLPBX_HPCBB_ex->Brush->Color = clRed;
		btnOLPBX_HPCBB->Caption = "OLPBX";
	}
	else{
                shpOLPBX_HPCBB->Brush->Color = clWhite;
                shpOLPBX_HPCBB_ex->Brush->Color = clWhite;
		btnOLPBX_HPCBB->Caption = "� OLPBX";
	};

        lblOLTEMP_HPCBB->Caption = CLP.RD(PC_HA_HPCBB_MODHID_OLTEMP);
        lblOLTEMP_HPCBB->Caption = FormatFloat("0.##",lblOLTEMP_HPCBB->Caption.ToDouble());
        prbOLTEMP_HPCBB->Position = CLP.RD(PC_HA_HPCBB_MODHID_OLTEMP) * 1000;

        lblOLPRESS_HPCBB->Caption = CLP.RD(PC_HA_HPCBB_MODHID_OLPRESS);
        lblOLPRESS_HPCBB->Caption = FormatFloat("0.##",lblOLPRESS_HPCBB->Caption.ToDouble());
        prbOLPRESS_HPCBB->Position = CLP.RD(PC_HA_HPCBB_MODHID_OLPRESS) * 1000;

//==============================================================================
//HPCBB_TQGRAV

        if ( CLP.RD(PC_HL_HPCBB_TQGRAV_NIVELBAIXO) == 1 ){
                shpTQGRAVNIVELBAIXO_HPCBB->Brush->Color = clYellow;
		btnTQGRAVNIVELBAIXO_HPCBB->Caption = "N�vel Baixo";
	}
	else{
                shpTQGRAVNIVELBAIXO_HPCBB->Brush->Color = clWhite;
		btnTQGRAVNIVELBAIXO_HPCBB->Caption = "N�vel OK";
	};

//==============================================================================
//HPCBB_HDWSCM

        if ( CLP.RD(CP_HL_HPCBB_HDWSCM_EMAUTOSCM) == 1 ){
		shpEMAUTOSCM_HPCBB->Brush->Color = clBlue;
	}
	else{
		shpEMAUTOSCM_HPCBB->Brush->Color = clWhite;
	}

        if ( CLP.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX) == 1 ){
		shpLIGARRPMBX_HPCBB->Brush->Color = clLime;
                if (btnMANRPMBXSCM_HPCBB->Caption == "� MANRPMBXSCM"){
                        CLP.WR( PC_HL_HPCBB_CTRPRI_MANRPMBXSCM, 1 );
                }
	}
	else{
		shpLIGARRPMBX_HPCBB->Brush->Color = clWhite;
	}

        if ( CLP.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX) == 1 ){
		shpDESLIGARRPMBX_HPCBB->Brush->Color = clLime;
                if (btnMANRPMBXSCM_HPCBB->Caption == "MANRPMBXSCM"){
                        CLP.WR( PC_HL_HPCBB_CTRPRI_MANRPMBXSCM, 0 );
                }
	}
	else{
		shpDESLIGARRPMBX_HPCBB->Brush->Color = clWhite;
	}

//==============================================================================
//HPCBE_BBP1BE
	if ( CLP.RD(PC_HL_HPCBE_BBP1BE_LIGADO) == 1 ){
		shpLigada_BBP1BE->Brush->Color = clLime;
                shpLigada_BBP1BE_ex->Brush->Color = clLime;
		btnLigada_BBP1BE->Caption = "Ligado";
	}
	else{
		shpLigada_BBP1BE->Brush->Color = clWhite;
                shpLigada_BBP1BE_ex->Brush->Color = clWhite;
		btnLigada_BBP1BE->Caption = "Parado";
	};

	if ( CLP.RD(PC_HL_HPCBE_BBP1BE_SOBREC) == 1 ){
		shpSobrec_BBP1BE->Brush->Color = clRed;
		btnSobrec_BBP1BE->Caption = "Em Sobrec.";
	}
	else{
		shpSobrec_BBP1BE->Brush->Color = clWhite;
		btnSobrec_BBP1BE->Caption = "Sem Sobrec.";
	};

        if ( CLP.RD(PC_HL_HPCBE_BBP1BE_EMREM) == 1 ){
		shpRemoto_BBP1BE->Brush->Color = clNavy;
                shpRemoto_BBP1BE_ex->Brush->Color = clNavy;
		btnRemoto_BBP1BE->Caption = "Remoto";
	}
	else{
		shpRemoto_BBP1BE->Brush->Color = clWhite;
                shpRemoto_BBP1BE_ex->Brush->Color = clWhite;
		btnRemoto_BBP1BE->Caption = "Local";
	};

    if ( CLP.RD(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG) == 1 ){
		shpAUTOHDWSCMLIG_BBP1BE->Brush->Color = clBlue;
		btnAUTOHDWSCMLIG_BBP1BE->Caption = "AUTOHDWSCMLIG";
	}
	else{
		shpAUTOHDWSCMLIG_BBP1BE->Brush->Color = clWhite;
		btnAUTOHDWSCMLIG_BBP1BE->Caption = "� AUTOHDWSCMLIG";
	};

    /*if ( CLP.RD(PC_HL_HPCBE_BBP1BE_AUTOHDWSCM) == 1 ){
		shpAUTOHDWSCM_BBP1BE->Brush->Color = clBlue;
		btnAUTOHDWSCM_BBP1BE->Caption = "AUTOHDWSCM";
	}
	else{
		shpAUTOHDWSCM_BBP1BE->Brush->Color = clWhite;
		btnAUTOHDWSCM_BBP1BE->Caption = "� AUTOHDWSCM";
	}*/

    if ( CLP.RD(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES) == 1 ){
		shpAUTOHDWSCMDES_BBP1BE->Brush->Color = clMaroon;
		btnAUTOHDWSCMDES_BBP1BE->Caption = "AUTOHDWSCMDES";
	}
	else{
		shpAUTOHDWSCMDES_BBP1BE->Brush->Color = clWhite;
		btnAUTOHDWSCMDES_BBP1BE->Caption = "� AUTOHDWSCMDES";
	};

	if ( CLP.RD(PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI) == 1 ){
		shpPRDEMERGSCMLI_BBP1BE->Brush->Color = clRed;
		btnPRDEMERGSCMLI_BBP1BE->Caption = "PRDEMERGSCMLI";
	}
	else{
		shpPRDEMERGSCMLI_BBP1BE->Brush->Color = clWhite;
		btnPRDEMERGSCMLI_BBP1BE->Caption = "� PRDEMERGSCMLI";
	};

	if ( CLP.RD(PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE) == 1 ){
		shpPRDEMERGSCMDE_BBP1BE->Brush->Color = clBlue;
		btnPRDEMERGSCMDE_BBP1BE->Caption = "PRDEMERGSCMDE";
	}
	else{
		shpPRDEMERGSCMDE_BBP1BE->Brush->Color = clWhite;
		btnPRDEMERGSCMDE_BBP1BE->Caption = "� PRDEMERGSCMDE";
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP1BE_LIGAR) == 1 ){
		shpLigarBBP1BE->Brush->Color = clLime;
                tmrParar_BBP1_HPCBE->Enabled = false;
		if (btnLigada_BBP1BE->Caption == "Parado"  && tmrPartir_BBP1_HPCBE->Enabled == false ){
                        if ( nao_atender_cmd_be == false ) {
        			tmrPartir_BBP1_HPCBE->Enabled = true;
                        }
		}
	}
	else{
		shpLigarBBP1BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR) == 1 ){
		shpDesligarBBP1BE->Brush->Color = clYellow;
                tmrPartir_BBP1_HPCBE->Enabled = false;
		if (btnLigada_BBP1BE->Caption == "Ligado"  && tmrParar_BBP1_HPCBE->Enabled == false ){
                        if ( nao_atender_cmd_be == false ) {
        			tmrParar_BBP1_HPCBE->Enabled = true;
	        	}
                }
	}
	else{
		shpDesligarBBP1BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO) == 1 ){
		shpAUTOMATICOBBP1BE->Brush->Color = clYellow;
		//if (btnEMAUT_BBP1BE->Caption == "Em Manual"){
		if (btnAUTOHDWSCMLIG_BBP1BE->Caption == "� AUTOHDWSCMLIG"){
			//CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCM, 1 );
			CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG, 1 );
			CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES, 0 );
		}
	}
	else{
		shpAUTOMATICOBBP1BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP1BE_MANUAL) == 1 ){
		shpMANUALBBP1BE->Brush->Color = clYellow;
		//if (btnEMAUT_BBP1BE->Caption == "Em Auto"){
		if (btnAUTOHDWSCMLIG_BBP1BE->Caption == "AUTOHDWSCMLIG"){
                        //CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCM, 0 );
                        CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG, 0 );
                        CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES, 1 );
		}
	}
	else{
		shpMANUALBBP1BE->Brush->Color = clWhite;
	}

	if ( CLP.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG) == 1){
		shpEmerg_BBP1BE->Brush->Color = clRed;
		if (btnLigada_BBP1BE->Caption == "Ligado" || btnPRDEMERGSCMLI_BBP1BE->Caption == "� PRDEMERGSCMLI" ){
                        tmrPartir_BBP1_HPCBE->Enabled = false;
                        if (btnLigada_BBP1BE->Caption == "Ligado"  && tmrParar_BBP1_HPCBE->Enabled == false ){
                               if ( nao_atender_cmd_be == false ) {
        		                tmrParar_BBP1_HPCBE->Enabled = true;
        	               }
                        }
       			CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 0 );
			CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE, 0 );
                        CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI, 1 );

		}
	}
	else{
		shpEmerg_BBP1BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG) == 1 ){
		shpLibEmerg_BBP1BE->Brush->Color = clRed;
		//if (btnLigada_BBP1BE->Caption == "Ligado"){
		//	CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 0 );
		//}
		if (btnPRDEMERGSCMLI_BBP1BE->Caption == "PRDEMERGSCMLI"){
			CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI, 0 );
			CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE, 1 );
		}
	}
	else{
		shpLibEmerg_BBP1BE->Brush->Color = clWhite;
	};

        if ( CLP.RD(PC_HL_HPCBE_BBP1BE_EMAUTOLOCAL) == 1 ){
		shpEmAut_BBP1BE->Brush->Color = clNavy;
		btnEmAut_BBP1BE->Caption = "Em Auto";
	}
	else{
		shpEmAut_BBP1BE->Brush->Color = clWhite;
		btnEmAut_BBP1BE->Caption = "Em Manual";
	};

        if ((btnAUTOHDWSCMLIG_BBP1BE->Caption == "AUTOHDWSCMLIG") || (btnEmAut_BBP1BE->Caption == "Em Auto")){
                emauto_p1_be = true;
        }
        else{
                emauto_p1_be = false;
        }


//==============================================================================
//HPCBE_BBP3BE
	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_LIGADO) == 1 ){
		shpLigada_BBP3BE->Brush->Color = clLime;
		btnLigada_BBP3BE->Caption = "Ligado";
	}
	else{
		shpLigada_BBP3BE->Brush->Color = clWhite;
		btnLigada_BBP3BE->Caption = "Parado";
	};

	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_EMREM) == 1 ){
		shpRemoto_BBP3BE->Brush->Color = clNavy;
		btnRemoto_BBP3BE->Caption = "Remoto";
	}
	else{
		shpRemoto_BBP3BE->Brush->Color = clWhite;
		btnRemoto_BBP3BE->Caption = "Local";
	};
	
	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_EMAUT) == 1 ){
		shpEmAut_BBP3BE->Brush->Color = clNavy;
		btnEmAut_BBP3BE->Caption = "Em Auto";
	}
	else{
		shpEmAut_BBP3BE->Brush->Color = clWhite;
		btnEmAut_BBP3BE->Caption = "Em Manual";
	};
	
	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG) == 1 ){
		shpAUTOHDWSCMLIG_BBP3BE->Brush->Color = clBlue;
		btnAUTOHDWSCMLIG_BBP3BE->Caption = "AUTOHDWSCMLIG";
	}
	else{
		shpAUTOHDWSCMLIG_BBP3BE->Brush->Color = clWhite;
		btnAUTOHDWSCMLIG_BBP3BE->Caption = "� AUTOHDWSCMLIG";
	};

	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES) == 1 ){
		shpAUTOHDWSCMDES_BBP3BE->Brush->Color = clMaroon;
		btnAUTOHDWSCMDES_BBP3BE->Caption = "AUTOHDWSCMDES";
	}
	else{
		shpAUTOHDWSCMDES_BBP3BE->Brush->Color = clWhite;
		btnAUTOHDWSCMDES_BBP3BE->Caption = "� AUTOHDWSCMDES";
	};
	
	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI) == 1 ){
		shpPRDEMERGSCMLI_BBP3BE->Brush->Color = clRed;
		btnPRDEMERGSCMLI_BBP3BE->Caption = "PRDEMERGSCMLI";
	}
	else{
		shpPRDEMERGSCMLI_BBP3BE->Brush->Color = clWhite;
		btnPRDEMERGSCMLI_BBP3BE->Caption = "� PRDEMERGSCMLI";
	};
	
	if ( CLP.RD(PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE) == 1 ){
		shpPRDEMERGSCMDE_BBP3BE->Brush->Color = clBlue;
		btnPRDEMERGSCMDE_BBP3BE->Caption = "PRDEMERGSCMDE";
	}
	else{
		shpPRDEMERGSCMDE_BBP3BE->Brush->Color = clWhite;
		btnPRDEMERGSCMDE_BBP3BE->Caption = "� PRDEMERGSCMDE";
	};
	
	if ( CLP.RD(CP_HL_HPCBE_BBP3BE_LIGAR) == 1 ){
		shpLigarBBP3BE->Brush->Color = clLime;
		if (btnLigada_BBP3BE->Caption == "Parado"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO, 1 );
		}
	}
	else{
		shpLigarBBP3BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR) == 1 ){
		shpDesligarBBP3BE->Brush->Color = clYellow;
		if (btnLigada_BBP3BE->Caption == "Ligado"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO, 0 );
		}
	}
	else{
		shpDesligarBBP3BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO) == 1 ){
		shpAUTOMATICOBBP3BE->Brush->Color = clYellow;
		if (btnEmAut_BBP3BE->Caption == "Em Manual"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_EMAUT, 1 );
                }
                if  (btnAUTOHDWSCMLIG_BBP3BE->Caption == "� AUTOHDWSCMLIG"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG, 1 );
			CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES, 0 );
		}
	}
	else{
		shpAUTOMATICOBBP3BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG) == 1 ){
		shpEmerg_BBP3BE->Brush->Color = clRed;
		if (btnLigada_BBP3BE->Caption == "Ligado" || btnPRDEMERGSCMLI_BBP3BE->Caption == "� PRDEMERGSCMLI"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO, 0 );
			CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE, 0 );
			CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI, 1 );
		}
	}
	else{
		shpEmerg_BBP3BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP3BE_MANUAL) == 1 ){
		shpMANUALBBP3BE->Brush->Color = clYellow;
		if (btnEmAut_BBP3BE->Caption == "Em Auto"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_EMAUT, 0 );
                }
                 if  (btnAUTOHDWSCMLIG_BBP3BE->Caption == "AUTOHDWSCMLIG"){
			CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG, 0 );
			CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES, 1 );
		}
	}
	else{
		shpMANUALBBP3BE->Brush->Color = clWhite;
	};

	if ( CLP.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG) == 1 ){
		shpLibEmerg_BBP3BE->Brush->Color = clBlue;
		if (btnPRDEMERGSCMLI_BBP3BE->Caption == "PRDEMERGSCMLI"){
			//CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO, 0 );
                        CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE, 1 );
			CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI, 0 );
		}
	}
	else{
		shpLibEmerg_BBP3BE->Brush->Color = clWhite;
	};

        if ( CLP.RD(PC_HL_HPCBE_BBP3BE_SOBRECARGA) == 1 ){
		shpSobrec_BBP3BE->Brush->Color = clRed;
		btnSobrec_BBP3BE->Caption = "Em Sobrec.";
	}
	else{
		shpSobrec_BBP3BE->Brush->Color = clWhite;
		btnSobrec_BBP3BE->Caption = "Sem Sobrec.";
	};
//==============================================================================
//HPCBE_UDOHPC
	if ( CLP.RD(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL) == 1 ){
		shpFILT21BPDIFAL_HPCBE->Brush->Color = clRed;
		btnFILT21BPDIFAL_HPCBE->Caption = "FILT21BPDIFAL";
	}
	else{
		shpFILT21BPDIFAL_HPCBE->Brush->Color = clWhite;
		btnFILT21BPDIFAL_HPCBE->Caption = "� FILT21BPDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL) == 1 ){
		shpFILT21APDIFAL_HPCBE->Brush->Color = clRed;
		btnFILT21APDIFAL_HPCBE->Caption = "FILT21APDIFAL";
	}
	else{
		shpFILT21APDIFAL_HPCBE->Brush->Color = clWhite;
		btnFILT21APDIFAL_HPCBE->Caption = "� FILT21APDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBE_UDOHPC_ZEROTHRUST) == 1 ){
		shpZEROTHRUST_HPCBE->Brush->Color = clLime;
                shpZEROTHRUST_HPCBE_ex->Brush->Color = clLime;
		btnZEROTHRUST_HPCBE->Caption = "ZEROTHRUST";
	}
	else{
		shpZEROTHRUST_HPCBE->Brush->Color = clWhite;
                shpZEROTHRUST_HPCBE_ex->Brush->Color = clWhite;
		btnZEROTHRUST_HPCBE->Caption = "� ZEROTHRUST";
	};

        if ( CLP.RD(PC_HL_HPCBE_UDOHPC_OLPRESSOK) == 1 ){
		shpOLPRESSOK_HPCBE->Brush->Color = clLime;
                shpOLPRESSOK_HPCBE_ex->Brush->Color = clLime;
		btnOLPRESSOK_HPCBE->Caption = "OLPRESSOK";
	}
	else{
		shpOLPRESSOK_HPCBE->Brush->Color = clWhite;
                shpOLPRESSOK_HPCBE_ex->Brush->Color = clWhite;
		btnOLPRESSOK_HPCBE->Caption = "� OLPRESSOK";
	};

        lblPASSOBEPOS_HPCBE->Caption = CLP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS);
        lblPASSOBEPOS_HPCBE->Caption = FormatFloat("0.##",lblPASSOBEPOS_HPCBE->Caption.ToDouble());
        lblPASSOBEPOS_HPCBE_ex->Caption = lblPASSOBEPOS_HPCBE->Caption;
        prbPASSOBEPOS_HPCBE->Position = CLP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS) * 1000;

        TestaDouble = false;

        try{
                Teste = txtZEROTHRUST_HPCBE->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
        }

        if (txtZEROTHRUST_HPCBE->Text.IsEmpty() != true && TestaDouble == false){
                if ( FormatFloat("0.##",CLP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS)) != FormatFloat("0.##",txtZEROTHRUST_HPCBE->Text.ToDouble()) && CLP.RD(PC_HL_HPCBE_UDOHPC_ZEROTHRUST) == 1){
                        if (abs(CLP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS)) > txtZEROTHRUST_HPCBE->Text.ToDouble()){
	                	if (CLP.RD( PC_HL_HPCBE_UDOHPC_ZEROTHRUST) != 0 ){
	                	        CLP.WR( PC_HL_HPCBE_UDOHPC_ZEROTHRUST, 0 );
                             }
                        }
        	}
	        else{
                        //if (FormatFloat("0.##",CLP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS)) == FormatFloat("0.##",txtZEROTHRUST_HPCBE->Text.ToDouble()) && CLP.RD(PC_HL_HPCBE_UDOHPC_ZEROTHRUST) == 0){
                                if (abs(CLP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS)) <= txtZEROTHRUST_HPCBE->Text.ToDouble()){
                                        if (CLP.RD( PC_HL_HPCBE_UDOHPC_ZEROTHRUST) != 1 ){
	        	                        CLP.WR( PC_HL_HPCBE_UDOHPC_ZEROTHRUST, 1 );
                                        }
                                }
                        //}
	        };
        }


//==============================================================================
//HPCBE_UDOHPC

        lblDEMANDAPASSO_HPCBE->Caption = (((calib_x2_demandapasso_HPCBE - calib_x1_demandapasso_HPCBE)*(CLP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO) - calib_y1_demandapasso_HPCBE))/(calib_y2_demandapasso_HPCBE - calib_y1_demandapasso_HPCBE)) + calib_x1_demandapasso_HPCBE;
        lblDEMANDAPASSO_HPCBE_ex->Caption = lblDEMANDAPASSO_HPCBE->Caption;
        if (ativademanda_HPCBE == true) {
                if ( ((float) ((int) (lblDEMANDAPASSO_HPCBE->Caption.ToDouble() * 10))/10) !=  ((float) ((int) (lblPASSOBEPOS_HPCBE->Caption.ToDouble() * 10))/10) ) {
                        //if ( ((float) ((int) (CLP.RD( PC_HA_HPCBE_UDOHPC_PASSOBEPOS) * 10))/10) !=  ((float) ((int) (lblDEMANDAPASSO_HPCBE->Caption.ToDouble() * 10))/10) ) {
                        //if ((int) CLP.RD( PC_HA_HPCBB_UDOHPC_PASSOBBPOS) != (int) lblDEMANDAPASSO_HPCBB->Caption.ToDouble() ){
                        passo_atual = CLP.RD( PC_HA_HPCBE_UDOHPC_PASSOBEPOS);
                        referencia = ((float) ((int) (lblDEMANDAPASSO_HPCBE->Caption.ToDouble() * 10)))/10  ;
                        if (fabs(passo_atual - referencia ) > 0.001) {
                                //CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, lblDEMANDAPASSO_HPCBB->Caption.ToDouble() );
                                if (tmrPassoBE->Enabled == false){
                                        tmrPassoBE->Enabled = true;
                                }
                        }
                        else{
                                tmrPassoBE->Enabled = false;
                        }

                }
        };

        if ( CLP.RD(PC_HL_HPCBE_CTRPRI_MANRPMBXSCM) == 1 ){
		shpMANRPMBXSCM_HPCBE->Brush->Color = clYellow;
		btnMANRPMBXSCM_HPCBE->Caption = "MANRPMBXSCM";
	}
	else{
		shpMANRPMBXSCM_HPCBE->Brush->Color = clWhite;
		btnMANRPMBXSCM_HPCBE->Caption = "� MANRPMBXSCM";
	};

        if ( CLP.RD(PC_HL_HPCBE_CTRPRI_FALHA) == 0 ){
		shpbtnCTRPRIFALHA_HPCBE->Brush->Color = clRed;
		btnCTRPRIFALHA_HPCBE->Caption = "Em Falha";
	}
	else{
		shpbtnCTRPRIFALHA_HPCBE->Brush->Color = clWhite;
		btnCTRPRIFALHA_HPCBE->Caption = "Sem Falha";
	};
//==============================================================================
//HPCBE_CTRBKP

        if ( CLP.RD(PC_HL_HPCBE_CTRBKP_EMOPERACAO) == 1 ){
                shpCTRBKPEMOPERACAO_HPCBE->Brush->Color = clRed;
		btnCTRBKPEMOPERACAO_HPCBE->Caption = "Em Opera��o";
	}
	else{
                shpCTRBKPEMOPERACAO_HPCBE->Brush->Color = clWhite;
		btnCTRBKPEMOPERACAO_HPCBE->Caption = "Desligado";
	};

//==============================================================================
//HPCBE_MODHID

        if ( CLP.RD(PC_HL_HPCBE_MODHID_FILT2PDIFAL) == 1 ){
                shpFILT2PDIFAL_HPCBE->Brush->Color = clRed;
		btnFILT2PDIFAL_HPCBE->Caption = "FILT2PDIFAL";
	}
	else{
                shpFILT2PDIFAL_HPCBE->Brush->Color = clWhite;
		btnFILT2PDIFAL_HPCBE->Caption = "� FILT2PDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBE_MODHID_FILT1PDIFAL) == 1 ){
                shpFILT1PDIFAL_HPCBE->Brush->Color = clRed;
		btnFILT1PDIFAL_HPCBE->Caption = "FILT1PDIFAL";
	}
	else{
                shpFILT1PDIFAL_HPCBE->Brush->Color = clWhite;
		btnFILT1PDIFAL_HPCBE->Caption = "� FILT1PDIFAL";
	};

        if ( CLP.RD(PC_HL_HPCBE_MODHID_OLPBX) == 1 ){
                shpOLPBX_HPCBE->Brush->Color = clRed;
                shpOLPBX_HPCBE_ex->Brush->Color = clRed;
		btnOLPBX_HPCBE->Caption = "OLPBX";
	}
	else{
                shpOLPBX_HPCBE->Brush->Color = clWhite;
                shpOLPBX_HPCBE_ex->Brush->Color = clWhite;
		btnOLPBX_HPCBE->Caption = "� OLPBX";
	};

        lblOLTEMP_HPCBE->Caption = CLP.RD(PC_HA_HPCBE_MODHID_OLTEMP);
        lblOLTEMP_HPCBE->Caption = FormatFloat("0.##",lblOLTEMP_HPCBE->Caption.ToDouble());
        prbOLTEMP_HPCBE->Position = CLP.RD(PC_HA_HPCBE_MODHID_OLTEMP) * 1000;

        lblOLPRESS_HPCBE->Caption = CLP.RD(PC_HA_HPCBE_MODHID_OLPRESS);
        lblOLPRESS_HPCBE->Caption = FormatFloat("0.##",lblOLPRESS_HPCBE->Caption.ToDouble());
        prbOLPRESS_HPCBE->Position = CLP.RD(PC_HA_HPCBE_MODHID_OLPRESS) * 1000;

//==============================================================================
//HPCBE_TQGRAV

        if ( CLP.RD(PC_HL_HPCBE_TQGRAV_NIVELBAIXO) == 1 ){
                shpTQGRAVNIVELBAIXO_HPCBE->Brush->Color = clYellow;
		btnTQGRAVNIVELBAIXO_HPCBE->Caption = "N�vel Baixo";
	}
	else{
                shpTQGRAVNIVELBAIXO_HPCBE->Brush->Color = clWhite;
		btnTQGRAVNIVELBAIXO_HPCBE->Caption = "N�vel OK";
	};

//==============================================================================
//HPCBE_HDWSCM

        if ( CLP.RD(CP_HL_HPCBE_HDWSCM_EMAUTOSCM) == 1 ){
		shpEMAUTOSCM_HPCBE->Brush->Color = clBlue;
	}
	else{
		shpEMAUTOSCM_HPCBE->Brush->Color = clWhite;
	}

        if ( CLP.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX) == 1 ){
		shpLIGARRPMBX_HPCBE->Brush->Color = clLime;
                if (btnMANRPMBXSCM_HPCBE->Caption == "� MANRPMBXSCM"){
                        CLP.WR( PC_HL_HPCBE_CTRPRI_MANRPMBXSCM, 1 );
                }
	}
	else{
		shpLIGARRPMBX_HPCBE->Brush->Color = clWhite;
	}

        if ( CLP.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX) == 1 ){
		shpDESLIGARRPMBX_HPCBE->Brush->Color = clLime;
                if (btnMANRPMBXSCM_HPCBE->Caption == "MANRPMBXSCM"){
                        CLP.WR( PC_HL_HPCBE_CTRPRI_MANRPMBXSCM, 0 );
                }
	}
	else{
		shpDESLIGARRPMBX_HPCBE->Brush->Color = clWhite;
	}


        if (pressao_modhid_hpcbb >= vlr_press_alar_bb){
                if (CLP.RD(PC_HL_HPCBB_UDOHPC_OLPRESSOK) != 1){
                        CLP.WR(PC_HL_HPCBB_UDOHPC_OLPRESSOK, 1);
                }
                if (CLP.RD(PC_HL_HPCBB_MODHID_OLPBX) != 0){
                        CLP.WR(PC_HL_HPCBB_MODHID_OLPBX, 0);
                }
        }
        else{
                if (CLP.RD(PC_HL_HPCBB_UDOHPC_OLPRESSOK) != 0){
                        CLP.WR(PC_HL_HPCBB_UDOHPC_OLPRESSOK, 0);
                }
                if (CLP.RD(PC_HL_HPCBB_MODHID_OLPBX) != 1){
                        CLP.WR(PC_HL_HPCBB_MODHID_OLPBX, 1);
                }
        }

        if (pressao_modhid_hpcbe >= vlr_press_alar_be){
                if (CLP.RD(PC_HL_HPCBE_UDOHPC_OLPRESSOK) != 1){
                        CLP.WR(PC_HL_HPCBE_UDOHPC_OLPRESSOK, 1);
                }
                if (CLP.RD(PC_HL_HPCBE_MODHID_OLPBX) != 0){
                        CLP.WR(PC_HL_HPCBE_MODHID_OLPBX, 0);
                }
        }
        else{
                if (CLP.RD(PC_HL_HPCBE_UDOHPC_OLPRESSOK) != 0){
                        CLP.WR(PC_HL_HPCBE_UDOHPC_OLPRESSOK, 0);
                }
                if (CLP.RD(PC_HL_HPCBE_MODHID_OLPBX) != 1){
                        CLP.WR(PC_HL_HPCBE_MODHID_OLPBX, 1);
                }
        }
}
//---------------------------------------------------------------------------
//***************************************************************************
//COMANDOS LOCAIS E TROCA DE VALORES PELO OPERADOR DE SOFTWARE
//***************************************************************************
void __fastcall TfrmPrincipal::btnLigada_BBP1BBClick(TObject *Sender)
{
	if (btnLigada_BBP1BB->Caption == "Parado"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnSobrec_BBP1BBClick(TObject *Sender)
{
	if (btnSobrec_BBP1BB->Caption == "Sem Sobrec."){
		CLP.WR( PC_HL_HPCBB_BBP1BB_SOBREC, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_SOBREC, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRemoto_BBP1BBClick(TObject *Sender)
{
	if (btnRemoto_BBP1BB->Caption == "Local"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAUTOHDWSCMLIG_BBP1BBClick(TObject *Sender)
{
	if (btnAUTOHDWSCMLIG_BBP1BB->Caption == "� AUTOHDWSCMLIG"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG, 0 );
	};
}
//---------------------------------------------------------------------------
/*void __fastcall TfrmPrincipal::btnAUTOHDWSCM_BBP1BBClick(TObject *Sender)
{
	if (btnAUTOHDWSCM_BBP1BB->Caption == "� AUTOHDWSCM"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCM, 0 );
	};
}*/
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAUTOHDWSCMDES_BBP1BBClick(TObject *Sender)
{
	if (btnAUTOHDWSCMDES_BBP1BB->Caption == "� AUTOHDWSCMDES"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPRDEMERGSCMLI_BBP1BBClick(TObject *Sender)
{
	if (btnPRDEMERGSCMLI_BBP1BB->Caption == "� PRDEMERGSCMLI"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMLI, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPRDEMERGSCMDE_BBP1BBClick(TObject *Sender)
{
	if (btnPRDEMERGSCMDE_BBP1BB->Caption == "� PRDEMERGSCMDE"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_PRDEMERGSCMDE, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnFILT21BPDIFAL_HPCBBClick(TObject *Sender)
{
	if (btnFILT21BPDIFAL_HPCBB->Caption == "� FILT21BPDIFAL"){
		CLP.WR( PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFILT21APDIFAL_HPCBBClick(TObject *Sender)
{
        if (btnFILT21APDIFAL_HPCBB->Caption == "� FILT21APDIFAL"){
		CLP.WR( PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLPRESSOK_HPCBBClick(TObject *Sender)
{
        if (btnOLPRESSOK_HPCBB->Caption == "� OLPRESSOK"){
		CLP.WR( PC_HL_HPCBB_UDOHPC_OLPRESSOK, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_UDOHPC_OLPRESSOK, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnZEROTHRUST_HPCBBClick(TObject *Sender)
{
        if (btnZEROTHRUST_HPCBB->Caption == "� ZEROTHRUST"){
		CLP.WR( PC_HL_HPCBB_UDOHPC_ZEROTHRUST, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_UDOHPC_ZEROTHRUST, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPASSOBBPOS_HPCBBClick(TObject *Sender)
{
	CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, txtPASSOBBPOS_HPCBB->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnDEMANDAPASSO_HPCBBClick(TObject *Sender)
{
        if (ativademanda_HPCBB == true) {
                ativademanda_HPCBB = false;
                shpATIVARDEMANDA_HPCBB->Brush->Color = clWhite;
        }
        else{
                ativademanda_HPCBB = true;
                shpATIVARDEMANDA_HPCBB->Brush->Color = clLime;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnLigada_BBP3BBClick(TObject *Sender)
{
        if (btnLigada_BBP3BB->Caption == "Parado"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnRemoto_BBP3BBClick(TObject *Sender)
{
        if (btnRemoto_BBP3BB->Caption == "Local"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAUTOHDWSCMLIG_BBP3BBClick(
      TObject *Sender)
{
        if (btnAUTOHDWSCMLIG_BBP3BB->Caption == "� AUTOHDWSCMLIG"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAUTOHDWSCMDES_BBP3BBClick(
      TObject *Sender)
{
        if (btnAUTOHDWSCMDES_BBP3BB->Caption == "� AUTOHDWSCMDES"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPRDEMERGSCMLI_BBP3BBClick(
      TObject *Sender)
{
        if (btnPRDEMERGSCMLI_BBP3BB->Caption == "� PRDEMERGSCMLI"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMLI, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPRDEMERGSCMDE_BBP3BBClick(
      TObject *Sender)
{
        if (btnPRDEMERGSCMDE_BBP3BB->Caption == "� PRDEMERGSCMDE"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_PRDEMERGSCMDE, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEmAut_BBP3BBClick(TObject *Sender)
{
        if (btnEmAut_BBP3BB->Caption == "Em Manual"){
		CLP.WR( PC_HL_HPCBB_BBP3BB_EMAUT, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_EMAUT, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMANRPMBXSCM_HPCBBClick(TObject *Sender)
{
        if (btnMANRPMBXSCM_HPCBB->Caption == "� MANRPMBXSCM"){
		CLP.WR( PC_HL_HPCBB_CTRPRI_MANRPMBXSCM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_CTRPRI_MANRPMBXSCM, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCTRPRIFALHA_HPCBBClick(TObject *Sender)
{
        if (btnCTRPRIFALHA_HPCBB->Caption == "Sem Falha"){
		CLP.WR( PC_HL_HPCBB_CTRPRI_FALHA, 0 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_CTRPRI_FALHA, 1 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPartir_BBP1_HPCBBTimer(TObject *Sender)
{
        CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 1 );
        if ( nao_pressurizar_bb == false ){
                tmrDespressurizarHPCBB->Enabled = false;
                tmrPressurizarHPCBB->Enabled = true;
        }
        tmrPartir_BBP1_HPCBB->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrParar_BBP1_HPCBBTimer(TObject *Sender)
{
        CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 0 );
        if ( nao_pressurizar_bb == false ){
                tmrPressurizarHPCBB->Enabled = false;
                tmrDespressurizarHPCBB->Enabled = true;
        }
        tmrParar_BBP1_HPCBB->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCTRBKPEMOPERACAO_HPCBBClick(TObject *Sender)
{
        if (btnCTRBKPEMOPERACAO_HPCBB->Caption == "Desligado"){
		CLP.WR( PC_HL_HPCBB_CTRBKP_EMOPERACAO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_CTRBKP_EMOPERACAO, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFILT2PDIFAL_HPCBBClick(TObject *Sender)
{
        if (btnFILT2PDIFAL_HPCBB->Caption == "� FILT2PDIFAL"){
		CLP.WR( PC_HL_HPCBB_MODHID_FILT2PDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_MODHID_FILT2PDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFILT1PDIFAL_HPCBBClick(TObject *Sender)
{
        if (btnFILT1PDIFAL_HPCBB->Caption == "� FILT1PDIFAL"){
		CLP.WR( PC_HL_HPCBB_MODHID_FILT1PDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_MODHID_FILT1PDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLPBX_HPCBBClick(TObject *Sender)
{
        if (btnOLPBX_HPCBB->Caption == "� OLPBX"){
		CLP.WR( PC_HL_HPCBB_MODHID_OLPBX, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_MODHID_OLPBX, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLTEMP_HPCBBClick(TObject *Sender)
{
	CLP.WR( PC_HA_HPCBB_MODHID_OLTEMP, txtOLTEMP_HPCBB->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLPRESS_HPCBBClick(TObject *Sender)
{
        CLP.WR( PC_HA_HPCBB_MODHID_OLPRESS, txtOLPRESS_HPCBB->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnTQGRAVNIVELBAIXO_HPCBBClick(
      TObject *Sender)
{
        if (btnTQGRAVNIVELBAIXO_HPCBB->Caption == "N�vel OK"){
		CLP.WR( PC_HL_HPCBB_TQGRAV_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_TQGRAV_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnLigada_BBP1BEClick(TObject *Sender)
{
	if (btnLigada_BBP1BE->Caption == "Parado"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnSobrec_BBP1BEClick(TObject *Sender)
{
	if (btnSobrec_BBP1BE->Caption == "Sem Sobrec."){
		CLP.WR( PC_HL_HPCBE_BBP1BE_SOBREC, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_SOBREC, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRemoto_BBP1BEClick(TObject *Sender)
{
	if (btnRemoto_BBP1BE->Caption == "Local"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAUTOHDWSCMLIG_BBP1BEClick(TObject *Sender)
{
	if (btnAUTOHDWSCMLIG_BBP1BE->Caption == "� AUTOHDWSCMLIG"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG, 0 );
	};
}
//---------------------------------------------------------------------------
/*void __fastcall TfrmPrincipal::btnAUTOHDWSCM_BBP1BEClick(TObject *Sender)
{
	if (btnAUTOHDWSCM_BBP1BE->Caption == "� AUTOHDWSCM"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCM, 0 );
	};
}*/
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAUTOHDWSCMDES_BBP1BEClick(TObject *Sender)
{
	if (btnAUTOHDWSCMDES_BBP1BE->Caption == "� AUTOHDWSCMDES"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPRDEMERGSCMLI_BBP1BEClick(TObject *Sender)
{
	if (btnPRDEMERGSCMLI_BBP1BE->Caption == "� PRDEMERGSCMLI"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMLI, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPRDEMERGSCMDE_BBP1BEClick(TObject *Sender)
{
	if (btnPRDEMERGSCMDE_BBP1BE->Caption == "� PRDEMERGSCMDE"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_PRDEMERGSCMDE, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnFILT21BPDIFAL_HPCBEClick(TObject *Sender)
{
	if (btnFILT21BPDIFAL_HPCBE->Caption == "� FILT21BPDIFAL"){
		CLP.WR( PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFILT21APDIFAL_HPCBEClick(TObject *Sender)
{
        if (btnFILT21APDIFAL_HPCBE->Caption == "� FILT21APDIFAL"){
		CLP.WR( PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLPRESSOK_HPCBEClick(TObject *Sender)
{
        if (btnOLPRESSOK_HPCBE->Caption == "� OLPRESSOK"){
		CLP.WR( PC_HL_HPCBE_UDOHPC_OLPRESSOK, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_UDOHPC_OLPRESSOK, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnZEROTHRUST_HPCBEClick(TObject *Sender)
{
        if (btnZEROTHRUST_HPCBE->Caption == "� ZEROTHRUST"){
		CLP.WR( PC_HL_HPCBE_UDOHPC_ZEROTHRUST, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_UDOHPC_ZEROTHRUST, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPASSOBEPOS_HPCBEClick(TObject *Sender)
{
	CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, txtPASSOBEPOS_HPCBE->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnDEMANDAPASSO_HPCBEClick(TObject *Sender)
{
        if (ativademanda_HPCBE == true) {
                ativademanda_HPCBE = false;
                shpATIVARDEMANDA_HPCBE->Brush->Color = clWhite;
        }
        else{
                ativademanda_HPCBE = true;
                shpATIVARDEMANDA_HPCBE->Brush->Color = clLime;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnLigada_BBP3BEClick(TObject *Sender)
{
        if (btnLigada_BBP3BE->Caption == "Parado"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnRemoto_BBP3BEClick(TObject *Sender)
{
        if (btnRemoto_BBP3BE->Caption == "Local"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAUTOHDWSCMLIG_BBP3BEClick(
      TObject *Sender)
{
        if (btnAUTOHDWSCMLIG_BBP3BE->Caption == "� AUTOHDWSCMLIG"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAUTOHDWSCMDES_BBP3BEClick(
      TObject *Sender)
{
        if (btnAUTOHDWSCMDES_BBP3BE->Caption == "� AUTOHDWSCMDES"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPRDEMERGSCMLI_BBP3BEClick(
      TObject *Sender)
{
        if (btnPRDEMERGSCMLI_BBP3BE->Caption == "� PRDEMERGSCMLI"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMLI, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPRDEMERGSCMDE_BBP3BEClick(
      TObject *Sender)
{
        if (btnPRDEMERGSCMDE_BBP3BE->Caption == "� PRDEMERGSCMDE"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_PRDEMERGSCMDE, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEmAut_BBP3BEClick(TObject *Sender)
{
        if (btnEmAut_BBP3BE->Caption == "Em Manual"){
		CLP.WR( PC_HL_HPCBE_BBP3BE_EMAUT, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_EMAUT, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMANRPMBXSCM_HPCBEClick(TObject *Sender)
{
        if (btnMANRPMBXSCM_HPCBE->Caption == "� MANRPMBXSCM"){
		CLP.WR( PC_HL_HPCBE_CTRPRI_MANRPMBXSCM, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_CTRPRI_MANRPMBXSCM, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCTRPRIFALHA_HPCBEClick(TObject *Sender)
{
        if (btnCTRPRIFALHA_HPCBE->Caption == "Sem Falha"){
		CLP.WR( PC_HL_HPCBE_CTRPRI_FALHA, 0 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_CTRPRI_FALHA, 1 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPartir_BBP1_HPCBETimer(TObject *Sender)
{
        CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 1 );
        if ( nao_pressurizar_be == false ){
                tmrDespressurizarHPCBE->Enabled = false;
                tmrPressurizarHPCBE->Enabled = true;
        }
        tmrPartir_BBP1_HPCBE->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrParar_BBP1_HPCBETimer(TObject *Sender)
{
        CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 0 );
        if ( nao_pressurizar_be == false ){
                tmrPressurizarHPCBE->Enabled = false;
                tmrDespressurizarHPCBE->Enabled = true;
        }
        tmrParar_BBP1_HPCBE->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCTRBKPEMOPERACAO_HPCBEClick(TObject *Sender)
{
        if (btnCTRBKPEMOPERACAO_HPCBE->Caption == "Desligado"){
		CLP.WR( PC_HL_HPCBE_CTRBKP_EMOPERACAO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_CTRBKP_EMOPERACAO, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFILT2PDIFAL_HPCBEClick(TObject *Sender)
{
        if (btnFILT2PDIFAL_HPCBE->Caption == "� FILT2PDIFAL"){
		CLP.WR( PC_HL_HPCBE_MODHID_FILT2PDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_MODHID_FILT2PDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFILT1PDIFAL_HPCBEClick(TObject *Sender)
{
        if (btnFILT1PDIFAL_HPCBE->Caption == "� FILT1PDIFAL"){
		CLP.WR( PC_HL_HPCBE_MODHID_FILT1PDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_MODHID_FILT1PDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLPBX_HPCBEClick(TObject *Sender)
{
        if (btnOLPBX_HPCBE->Caption == "� OLPBX"){
		CLP.WR( PC_HL_HPCBE_MODHID_OLPBX, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_MODHID_OLPBX, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLTEMP_HPCBEClick(TObject *Sender)
{
	CLP.WR( PC_HA_HPCBE_MODHID_OLTEMP, txtOLTEMP_HPCBE->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnOLPRESS_HPCBEClick(TObject *Sender)
{
        CLP.WR( PC_HA_HPCBE_MODHID_OLPRESS, txtOLPRESS_HPCBE->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnTQGRAVNIVELBAIXO_HPCBEClick(TObject *Sender)
{
        if (btnTQGRAVNIVELBAIXO_HPCBE->Caption == "N�vel OK"){
		CLP.WR( PC_HL_HPCBE_TQGRAV_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_TQGRAV_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::tmrPressurizarHPCBBTimer(TObject *Sender)
{
        pressao_modhid_hpcbb = CLP.RD(PC_HA_HPCBB_MODHID_OLPRESS);
        if (btnLigada_BBP1BB->Caption == "Ligado"){
                if (pressao_modhid_hpcbb < vlr_press_oper_bb){
                        pressao_modhid_hpcbb = pressao_modhid_hpcbb + 1.5;
                        CLP.WR(PC_HA_HPCBB_MODHID_OLPRESS,pressao_modhid_hpcbb);
                };
        };
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrDespressurizarHPCBBTimer(TObject *Sender)
{
        pressao_modhid_hpcbb = CLP.RD(PC_HA_HPCBB_MODHID_OLPRESS);
        if (btnLigada_BBP1BB->Caption == "Parado"){
                if (pressao_modhid_hpcbb >= vlr_press_oper_bb || pressao_modhid_hpcbb > 0.0 ){
                        pressao_modhid_hpcbb = pressao_modhid_hpcbb - 1.75;
                        if (pressao_modhid_hpcbb < 0.0){
                                pressao_modhid_hpcbb = 0.0;
                        }
                        CLP.WR(PC_HA_HPCBB_MODHID_OLPRESS,pressao_modhid_hpcbb);
                };
        };
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrDespressurizarHPCBETimer(TObject *Sender)
{
        pressao_modhid_hpcbe = CLP.RD(PC_HA_HPCBE_MODHID_OLPRESS);
        if (btnLigada_BBP1BE->Caption == "Parado"){
                if (pressao_modhid_hpcbe >= vlr_press_oper_be || pressao_modhid_hpcbe > 0.0){
                        pressao_modhid_hpcbe = pressao_modhid_hpcbe - 1.75;
                        if (pressao_modhid_hpcbe < 0.0){
                                pressao_modhid_hpcbe = 0.0;
                        }
                        CLP.WR(PC_HA_HPCBE_MODHID_OLPRESS,pressao_modhid_hpcbe);
                };
        };

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPressurizarHPCBETimer(TObject *Sender)
{
        pressao_modhid_hpcbe = CLP.RD(PC_HA_HPCBE_MODHID_OLPRESS);
        if (btnLigada_BBP1BE->Caption == "Ligado"){
                if (pressao_modhid_hpcbe < vlr_press_oper_be){
                        pressao_modhid_hpcbe = pressao_modhid_hpcbe + 1.5;
                        CLP.WR(PC_HA_HPCBE_MODHID_OLPRESS,pressao_modhid_hpcbe);
                };
        };

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPartir_BBP1BBClick(TObject *Sender)
{
        tmrParar_BBP1_HPCBB->Enabled = false;
        tmrPartir_BBP1_HPCBB->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnParar_BBP1BBClick(TObject *Sender)
{
        tmrPartir_BBP1_HPCBB->Enabled = false;
        tmrParar_BBP1_HPCBB->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPartir_BBP1BEClick(TObject *Sender)
{
        tmrParar_BBP1_HPCBE->Enabled = false;
        tmrPartir_BBP1_HPCBE->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnParar_BBP1BEClick(TObject *Sender)
{
        tmrPartir_BBP1_HPCBE->Enabled = false;
        tmrParar_BBP1_HPCBE->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrReconectaTimer(TObject *Sender)
{
         //RECONEX�O
        CLP.Open(IP);
        tmrReconecta->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ListaTimer(TObject *Sender)
{
        lista = CLP.TamBufWR();
        lblLista->Caption = CLP._thread->buffersRecebidos.size();
        lblBufferR->Caption = "RD: " + String (CLP.TamBufRD());
        lblBufferW->Caption = "WR: " + String (CLP.TamBufWR());

        if (lista > 100) {
                //tmrLeitura->Enabled = false;
                //shpAguarde->Top = 440;
                //shpAguarde->Left = 0;
                //shpAguarde->Width = 657;
                //shpAguarde->Height = 49;
                shpAguarde->Visible = true;
                //lblAguarde->Top = 8;
                //lblAguarde->Left = 0;
                //lblAguarde->Width = 649;
                //lblAguarde->Height = 29;
                lblAguarde->Visible = true;
                btnReset->Visible = false;
        }
        else{
                //if (lista < 10 ){
                //        tmrLeitura->Enabled = true;
                //}
                //shpAguarde->Top = 5000;
                //shpAguarde->Left = 5000;
                //shpAguarde->Width = 0;
                //shpAguarde->Height = 0;
                shpAguarde->Visible = false;
                //lblAguarde->Top = 5000;
                //lblAguarde->Left = 5000;
                //lblAguarde->Width = 0;
                //lblAguarde->Height = 0;
                lblAguarde->Visible = false;
                btnReset->Visible = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnResetClick(TObject *Sender)
{
        if ( Starting->Enabled == false){
                btnReset->Enabled = false;
                Starting->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPassoBBTimer(TObject *Sender)
{
        float passo_atual;
        float referencia;
        passo_atual = CLP.RD( PC_HA_HPCBB_UDOHPC_PASSOBBPOS);
        referencia = ((float) ((int) (lblDEMANDAPASSO_HPCBB->Caption.ToDouble() * 10)))/10  ;
        /*if (btnLigada_BBP1BB->Caption == "Ligado"){*/
        if (lblOLPRESS_HPCBB->Caption.ToDouble() >= vlr_press_atua_bb && CLP.TamBufWR() < 10){
        if (ativademanda_HPCBB == true && fabs(passo_atual - (referencia + Erro_BB) ) > 0.001) {
                if ( passo_atual > referencia + Erro_BB){
                        if ( passo_atual - (referencia + Erro_BB) > PASSO_BB_DIF_AV_1){
                                CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, passo_atual - PASSO_BB_INC_AV_1 );
                        }else{
                                if ( passo_atual - (referencia + Erro_BB) > PASSO_BB_DIF_AV_2) {
                                        CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, passo_atual - PASSO_BB_INC_AV_2 );
                                }else{
                                        if ( passo_atual - (referencia + Erro_BB) > PASSO_BB_DIF_AV_3) {
                                                CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, passo_atual - PASSO_BB_INC_AV_3 );
                                        }
                                }
                        }
                }else{
                        if ( passo_atual < referencia + Erro_BB){
                                if ( (referencia + Erro_BB) - passo_atual  > PASSO_BB_DIF_AR_1) {
                                        CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, passo_atual + PASSO_BB_INC_AR_1 );
                                }else{
                                        if ( (referencia + Erro_BB) - passo_atual  > PASSO_BB_DIF_AR_2) {
                                                CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, passo_atual + PASSO_BB_INC_AR_2 );
                                        }else{
                                                if ( (referencia + Erro_BB) - passo_atual > PASSO_BB_DIF_AR_3) {
                                                        CLP.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, passo_atual - PASSO_BB_INC_AR_3 );
                                                }
                                        }
                                }
                        }
                }
        };
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPassoBETimer(TObject *Sender)
{
        float passo_atual;
        float referencia;
        passo_atual = CLP.RD( PC_HA_HPCBE_UDOHPC_PASSOBEPOS);
        referencia = ((float) ((int) (lblDEMANDAPASSO_HPCBE->Caption.ToDouble() * 10)))/10  ;
        /*if (btnLigada_BBP1BE->Caption == "Ligado"){*/
        if (lblOLPRESS_HPCBE->Caption.ToDouble() >= vlr_press_atua_be && CLP.TamBufWR() < 10){
        if (ativademanda_HPCBE == true && fabs(passo_atual - (referencia + Erro_BE) ) > 0.001) {
                if ( passo_atual > referencia + Erro_BE){
                        if ( passo_atual - (referencia + Erro_BE) > PASSO_BE_DIF_AV_1){
                                CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, passo_atual - PASSO_BE_INC_AV_1 );
                        }else{
                                if ( passo_atual - (referencia + Erro_BE) > PASSO_BE_DIF_AV_2) {
                                        CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, passo_atual - PASSO_BE_INC_AV_2 );
                                }else{
                                        if ( passo_atual - (referencia + Erro_BE) > PASSO_BE_DIF_AV_3) {
                                                CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, passo_atual - PASSO_BE_INC_AV_3 );
                                        }
                                }
                        }
                }else{
                        if ( passo_atual < referencia + Erro_BE){
                                if ( (referencia + Erro_BE) - passo_atual  > PASSO_BE_DIF_AR_1) {
                                        CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, passo_atual + PASSO_BE_INC_AR_1 );
                                }else{
                                        if ( (referencia + Erro_BE) - passo_atual  > PASSO_BE_DIF_AR_2) {
                                                CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, passo_atual + PASSO_BE_INC_AR_2 );
                                        }else{
                                                if ( (referencia + Erro_BE) - passo_atual > PASSO_BE_DIF_AR_3) {
                                                        CLP.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, passo_atual - PASSO_BE_INC_AR_3 );
                                                }
                                        }
                                }
                        }
                }
        };
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEmAut_BBP1BBClick(TObject *Sender)
{
        if(btnEmAut_BBP1BB->Caption == "Em Manual"){
		CLP.WR( PC_HL_HPCBB_BBP1BB_EMAUTOLOCAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP1BB_EMAUTOLOCAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEmAut_BBP1BEClick(TObject *Sender)
{
        if(btnEmAut_BBP1BE->Caption == "Em Manual"){
		CLP.WR( PC_HL_HPCBE_BBP1BE_EMAUTOLOCAL, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP1BE_EMAUTOLOCAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSobrec_BBP3BEClick(TObject *Sender)
{
        if (btnSobrec_BBP3BE->Caption == "Sem Sobrec."){
		CLP.WR( PC_HL_HPCBE_BBP3BE_SOBRECARGA, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBE_BBP3BE_SOBRECARGA, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSobrec_BBP3BBClick(TObject *Sender)
{
        if (btnSobrec_BBP3BB->Caption == "Sem Sobrec."){
		CLP.WR( PC_HL_HPCBB_BBP3BB_SOBRECARGA, 1 );
	}
	else{
		CLP.WR( PC_HL_HPCBB_BBP3BB_SOBRECARGA, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInbirCMDBBClick(TObject *Sender)
{
        if ( nao_atender_cmd_bb == false ){
                cmdInbirCMDBB->Caption = "Inibir Cmd. BB Lig.";
                nao_atender_cmd_bb = true;
        }
        else{
                cmdInbirCMDBB->Caption = "Inibir Cmd. BB Des.";
                nao_atender_cmd_bb = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInbirPRESSBBClick(TObject *Sender)
{
        if ( nao_pressurizar_bb == false ){
                cmdInbirPRESSBB->Caption = "Inibir Pres. BB Lig.";
                nao_pressurizar_bb = true;
        }
        else{
                cmdInbirPRESSBB->Caption = "Inibir Pres. BB Des.";
                nao_pressurizar_bb = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInbirCMDBEClick(TObject *Sender)
{
        if ( nao_atender_cmd_be == false ){
                cmdInbirCMDBE->Caption = "Inibir Cmd. BE Lig.";
                nao_atender_cmd_be = true;
        }
        else{
                cmdInbirCMDBE->Caption = "Inibir Cmd. BE Des.";
                nao_atender_cmd_be = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInbirPRESSBEClick(TObject *Sender)
{
        if ( nao_pressurizar_be == false ){
                cmdInbirPRESSBE->Caption = "Inibir Pres. BE Lig.";
                nao_pressurizar_be = true;
        }
        else{
                cmdInbirPRESSBE->Caption = "Inibir Pres. BE Des.";
                nao_pressurizar_be = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::AjusteParamPasso1Click(TObject *Sender)
{
        frmCtrlPasso->Top = frmPrincipal->Top + 10;
        frmCtrlPasso->Left = frmPrincipal->Left + 10;

        frmCtrlPasso->txtPASSO_BE_DIF_AV_1->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AV_1);
        frmCtrlPasso->txtPASSO_BE_INC_AV_1->Text = FormatFloat( "##0.##", PASSO_BE_INC_AV_1);
        frmCtrlPasso->txtPASSO_BE_DIF_AV_2->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AV_2);
        frmCtrlPasso->txtPASSO_BE_INC_AV_2->Text = FormatFloat( "##0.##", PASSO_BE_INC_AV_2);
        frmCtrlPasso->txtPASSO_BE_DIF_AV_3->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AV_3);
        frmCtrlPasso->txtPASSO_BE_INC_AV_3->Text = FormatFloat( "##0.##", PASSO_BE_INC_AV_3);
        frmCtrlPasso->txtPASSO_BE_DIF_AR_1->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AR_1);
        frmCtrlPasso->txtPASSO_BE_INC_AR_1->Text = FormatFloat( "##0.##", PASSO_BE_INC_AR_1);
        frmCtrlPasso->txtPASSO_BE_DIF_AR_2->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AR_2);
        frmCtrlPasso->txtPASSO_BE_INC_AR_2->Text = FormatFloat( "##0.##", PASSO_BE_INC_AR_2);
        frmCtrlPasso->txtPASSO_BE_DIF_AR_3->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AR_3);
        frmCtrlPasso->txtPASSO_BE_INC_AR_3->Text = FormatFloat( "##0.##", PASSO_BE_INC_AR_3);

        frmCtrlPasso->txtTempoBE->Text = tmrPassoBE->Interval;

        frmCtrlPasso->txtPASSO_BB_DIF_AV_1->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AV_1);
        frmCtrlPasso->txtPASSO_BB_INC_AV_1->Text = FormatFloat( "##0.##", PASSO_BB_INC_AV_1);
        frmCtrlPasso->txtPASSO_BB_DIF_AV_2->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AV_2);
        frmCtrlPasso->txtPASSO_BB_INC_AV_2->Text = FormatFloat( "##0.##", PASSO_BB_INC_AV_2);
        frmCtrlPasso->txtPASSO_BB_DIF_AV_3->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AV_3);
        frmCtrlPasso->txtPASSO_BB_INC_AV_3->Text = FormatFloat( "##0.##", PASSO_BB_INC_AV_3);
        frmCtrlPasso->txtPASSO_BB_DIF_AR_1->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AR_1);
        frmCtrlPasso->txtPASSO_BB_INC_AR_1->Text = FormatFloat( "##0.##", PASSO_BB_INC_AR_1);
        frmCtrlPasso->txtPASSO_BB_DIF_AR_2->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AR_2);
        frmCtrlPasso->txtPASSO_BB_INC_AR_2->Text = FormatFloat( "##0.##", PASSO_BB_INC_AR_2);
        frmCtrlPasso->txtPASSO_BB_DIF_AR_3->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AR_3);
        frmCtrlPasso->txtPASSO_BB_INC_AR_3->Text = FormatFloat( "##0.##", PASSO_BB_INC_AR_3);

        frmCtrlPasso->txtTempoBB->Text = tmrPassoBB->Interval;

        frmCtrlPasso->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuHPCBBClick(TObject *Sender)
{
        //pnlHPCBE->Visible = false;
        //pnlHPCBB->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuHPCBEClick(TObject *Sender)
{
        //pnlHPCBB->Visible = false;
        //pnlHPCBE->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnErro_BBClick(TObject *Sender)
{
        Erro_BB = txtErro_BB->Text.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnErro_BEClick(TObject *Sender)
{
        Erro_BE = txtErro_BE->Text.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrErroTimer(TObject *Sender)
{
        lblErro_BB->Caption = "Erro - " + FormatFloat( "#0.#", Erro_BB);
        lblErro_BE->Caption = "Erro - " + FormatFloat( "#0.#", Erro_BE);
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::tmrHPCBB_AutoTimer(TObject *Sender)
{
        frmCtrlParamAuto->lblRPMEIXOBB->Caption = rpm_eixo_bb;
        if (emauto_p1_bb == true && CLP.TamBufWR() < 5){
                pressao_modhid_hpcbb = CLP.RD(PC_HA_HPCBB_MODHID_OLPRESS);
                if (btnLigada_BBP1BB->Caption == "Ligado"){
                        if (pressao_modhid_hpcbb >= vlr_press_auto_bb){
                                CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 0 );
                        };
                }
                else{
                        if (pressao_modhid_hpcbb < vlr_press_auto_bb){
                                CLP.WR( PC_HL_HPCBB_BBP1BB_LIGADO, 1 );
                                tmrPartir_BBP1_HPCBB->Enabled = true;
                        };
                };
        };
        if ( rpm_eixo_bb < valor_min_rpm_eixo_bb && btnLigada_BBP1BB->Caption != "Ligado"){
                if (pressao_modhid_hpcbb > 0.0){
                        pressao_modhid_hpcbb = pressao_modhid_hpcbb - 0.1;
                        if ( pressao_modhid_hpcbb < 0.0){
                                pressao_modhid_hpcbb = 0.0;
                        }
                        CLP.WR(PC_HA_HPCBB_MODHID_OLPRESS,pressao_modhid_hpcbb);
                }
        };
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrHPCBE_AutoTimer(TObject *Sender)
{
        frmCtrlParamAuto->lblRPMEIXOBE->Caption = rpm_eixo_be;
        if (emauto_p1_be == true && CLP.TamBufWR() < 5){
                pressao_modhid_hpcbe = CLP.RD(PC_HA_HPCBE_MODHID_OLPRESS);
                if (btnLigada_BBP1BE->Caption == "Ligado"){
                        if (pressao_modhid_hpcbe >= vlr_press_auto_be){
                                CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 0 );
                        };
                }
                else{
                        if (pressao_modhid_hpcbe < vlr_press_auto_be){
                                CLP.WR( PC_HL_HPCBE_BBP1BE_LIGADO, 1 );
                                tmrPartir_BBP1_HPCBE->Enabled = true;
                        };
                };
        };
        if ( rpm_eixo_be < valor_min_rpm_eixo_be && btnLigada_BBP1BE->Caption != "Ligado"){
                if (pressao_modhid_hpcbe > 0.0){
                        pressao_modhid_hpcbe = pressao_modhid_hpcbe - 0.1;
                        if ( pressao_modhid_hpcbe < 0.0){
                                pressao_modhid_hpcbe = 0.0;
                        }
                        CLP.WR(PC_HA_HPCBE_MODHID_OLPRESS,pressao_modhid_hpcbe);
                }
        };
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuParamAutoClick(TObject *Sender)
{
        frmCtrlParamAuto->Top = frmPrincipal->Top + 10;
        frmCtrlParamAuto->Left = frmPrincipal->Left + 10;
        frmCtrlParamAuto->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnStatusClick(TObject *Sender)
{
        pnlStatus->Visible = true;

        pnlHPCBB_CTRL->Visible = false;
        pnlHPCBB_UDOMODHID->Visible = false;
        pnlHPCBB_P1->Visible = false;
        pnlHPCBB_P3->Visible = false;

        btnHPCBB_CTRL->Visible = false;
        btnHPCBB_UDOMODHID->Visible = false;
        btnHPCBB_P1->Visible = false;
        btnHPCBB_P3->Visible = false;

        pnlHPCBE_CTRL->Visible = false;
        pnlHPCBE_UDOMODHID->Visible = false;
        pnlHPCBE_P1->Visible = false;
        pnlHPCBE_P3->Visible = false;

        btnHPCBE_CTRL->Visible = false;
        btnHPCBE_UDOMODHID->Visible = false;
        btnHPCBE_P1->Visible = false;
        btnHPCBE_P3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnHPCClick(TObject *Sender)
{
        pnlStatus->Visible = false;

        pnlHPCBB_CTRL->Visible = false;
        pnlHPCBB_UDOMODHID->Visible = true;
        pnlHPCBB_P1->Visible = false;
        pnlHPCBB_P3->Visible = false;

        btnHPCBB_CTRL->Visible = true;
        btnHPCBB_UDOMODHID->Visible = true;
        btnHPCBB_P1->Visible = true;
        btnHPCBB_P3->Visible = true;

        pnlHPCBE_CTRL->Visible = false;
        pnlHPCBE_UDOMODHID->Visible = true;
        pnlHPCBE_P1->Visible = false;
        pnlHPCBE_P3->Visible = false;

        btnHPCBE_CTRL->Visible = true;
        btnHPCBE_UDOMODHID->Visible = true;
        btnHPCBE_P1->Visible = true;
        btnHPCBE_P3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBB_CTRLClick(TObject *Sender)
{
        pnlHPCBB_CTRL->Visible = true;
        pnlHPCBB_UDOMODHID->Visible = false;
        pnlHPCBB_P1->Visible = false;
        pnlHPCBB_P3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBB_UDOMODHIDClick(TObject *Sender)
{
        pnlHPCBB_CTRL->Visible = false;
        pnlHPCBB_UDOMODHID->Visible = true;
        pnlHPCBB_P1->Visible = false;
        pnlHPCBB_P3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBB_P1Click(TObject *Sender)
{
        pnlHPCBB_CTRL->Visible = false;
        pnlHPCBB_UDOMODHID->Visible = false;
        pnlHPCBB_P1->Visible = true;
        pnlHPCBB_P3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBB_P3Click(TObject *Sender)
{
        pnlHPCBB_CTRL->Visible = false;
        pnlHPCBB_UDOMODHID->Visible = false;
        pnlHPCBB_P1->Visible = false;
        pnlHPCBB_P3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBE_UDOMODHIDClick(TObject *Sender)
{
        pnlHPCBE_CTRL->Visible = false;
        pnlHPCBE_UDOMODHID->Visible = true;
        pnlHPCBE_P1->Visible = false;
        pnlHPCBE_P3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBE_P1Click(TObject *Sender)
{
        pnlHPCBE_CTRL->Visible = false;
        pnlHPCBE_UDOMODHID->Visible = false;
        pnlHPCBE_P1->Visible = true;
        pnlHPCBE_P3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBE_P3Click(TObject *Sender)
{
        pnlHPCBE_CTRL->Visible = false;
        pnlHPCBE_UDOMODHID->Visible = false;
        pnlHPCBE_P1->Visible = false;
        pnlHPCBE_P3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHPCBE_CTRLClick(TObject *Sender)
{
        pnlHPCBE_CTRL->Visible = true;
        pnlHPCBE_UDOMODHID->Visible = false;
        pnlHPCBE_P1->Visible = false;
        pnlHPCBE_P3->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnFecharClick(TObject *Sender)
{
        frmPrincipal->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnParamPassoClick(TObject *Sender)
{
        frmCtrlPasso->Top = frmPrincipal->Top + 20;
        frmCtrlPasso->Left = frmPrincipal->Left + 50;

        frmCtrlPasso->txtPASSO_BE_DIF_AV_1->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AV_1);
        frmCtrlPasso->txtPASSO_BE_INC_AV_1->Text = FormatFloat( "##0.##", PASSO_BE_INC_AV_1);
        frmCtrlPasso->txtPASSO_BE_DIF_AV_2->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AV_2);
        frmCtrlPasso->txtPASSO_BE_INC_AV_2->Text = FormatFloat( "##0.##", PASSO_BE_INC_AV_2);
        frmCtrlPasso->txtPASSO_BE_DIF_AV_3->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AV_3);
        frmCtrlPasso->txtPASSO_BE_INC_AV_3->Text = FormatFloat( "##0.##", PASSO_BE_INC_AV_3);
        frmCtrlPasso->txtPASSO_BE_DIF_AR_1->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AR_1);
        frmCtrlPasso->txtPASSO_BE_INC_AR_1->Text = FormatFloat( "##0.##", PASSO_BE_INC_AR_1);
        frmCtrlPasso->txtPASSO_BE_DIF_AR_2->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AR_2);
        frmCtrlPasso->txtPASSO_BE_INC_AR_2->Text = FormatFloat( "##0.##", PASSO_BE_INC_AR_2);
        frmCtrlPasso->txtPASSO_BE_DIF_AR_3->Text = FormatFloat( "##0.##", PASSO_BE_DIF_AR_3);
        frmCtrlPasso->txtPASSO_BE_INC_AR_3->Text = FormatFloat( "##0.##", PASSO_BE_INC_AR_3);

        frmCtrlPasso->txtTempoBE->Text = tmrPassoBE->Interval;

        frmCtrlPasso->txtPASSO_BB_DIF_AV_1->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AV_1);
        frmCtrlPasso->txtPASSO_BB_INC_AV_1->Text = FormatFloat( "##0.##", PASSO_BB_INC_AV_1);
        frmCtrlPasso->txtPASSO_BB_DIF_AV_2->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AV_2);
        frmCtrlPasso->txtPASSO_BB_INC_AV_2->Text = FormatFloat( "##0.##", PASSO_BB_INC_AV_2);
        frmCtrlPasso->txtPASSO_BB_DIF_AV_3->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AV_3);
        frmCtrlPasso->txtPASSO_BB_INC_AV_3->Text = FormatFloat( "##0.##", PASSO_BB_INC_AV_3);
        frmCtrlPasso->txtPASSO_BB_DIF_AR_1->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AR_1);
        frmCtrlPasso->txtPASSO_BB_INC_AR_1->Text = FormatFloat( "##0.##", PASSO_BB_INC_AR_1);
        frmCtrlPasso->txtPASSO_BB_DIF_AR_2->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AR_2);
        frmCtrlPasso->txtPASSO_BB_INC_AR_2->Text = FormatFloat( "##0.##", PASSO_BB_INC_AR_2);
        frmCtrlPasso->txtPASSO_BB_DIF_AR_3->Text = FormatFloat( "##0.##", PASSO_BB_DIF_AR_3);
        frmCtrlPasso->txtPASSO_BB_INC_AR_3->Text = FormatFloat( "##0.##", PASSO_BB_INC_AR_3);

        frmCtrlPasso->txtTempoBB->Text = tmrPassoBB->Interval;

        frmCtrlPasso->ShowModal();                
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAutoP1Click(TObject *Sender)
{
        frmCtrlParamAuto->Top = frmPrincipal->Top + 20;
        frmCtrlParamAuto->Left = frmPrincipal->Left + 50;
        frmCtrlParamAuto->ShowModal();
}
//---------------------------------------------------------------------------

