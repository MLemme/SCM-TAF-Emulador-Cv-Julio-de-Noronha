//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//***************************************************************************
//MAURICIO ANDRADE LEMME - ANALISTA DE SISTEMAS J2
//IPqM - INSTITUTO DE PESQUISAS DA MARINHA
//GSD - GRUPO DE SISTEMAS DIGITAIS
//FUNDEP - FUNDAÇÃO DE DESENVOLVIMENTO DA PESQUISA

//EMULADOR DE SINAIS DA PROPULSÃO
//NAVIO MODELO.....: V-32 JULIO DE NORONHA (INHAUMA)
//USUÁRIO FINAL....: EQUIPE CLP
//VERSÃO INICIAL...: V001b
//MÓDULO...........: ER
//DATA DE INÍCIO...: 08.06.2016
//DATA DE PROTÓTIPO: 21.06.2016
//DATA DE TÉRMINO..: 15.05.2017
//DATA DE ATUALIZ..: 28.06.2023
//DESIGNAÇÃO.......: ESTE MÓDULO DO SOFTWARE TEM COMO OBJETIVO EMULAR O FUNCIONAMENTO DO ER BB
//EM COPARCERIA DESTE MÓDULO ESTA O MÓDULO DE COMUNICAÇÃO MODBUS DE AUTORIA DO
//FUNCIONÁRIO FÁBIO TEIXEIRA, SUA IMPLEMENTAÇÃO É DESCONHECIDA
//***************************************************************************
#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
#include "Mancais.h"
#include "ModBusDriverLib\TModBusTCPDriver.cpp"
#include "math.h"
#include <cmath>

//----------------- ENDEREÇOS DOS EQUIPAMENTOS -----------------
//--------------------------- BBELPN ---------------------------
String CP_HL_ERHBC_BBELPN_LIBPEMERG             = "%MW510.8";
String CP_HL_ERHBC_BBELPN_AUTOMATICO            = "%MW508.12";
String CP_HL_ERHBC_BBELPN_MANUAL                = "%MW508.11";
String CP_HL_ERHBC_BBELPN_PARAREMERG            = "%MW508.10";
String CP_HL_ERHBC_BBELPN_DESLIGAR              = "%MW508.9";
String CP_HL_ERHBC_BBELPN_LIGAR                 = "%MW508.8";
String PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE         = "%MW6027.13";
String PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI         = "%MW6027.12";
String PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES         = "%MW6026.11";
String PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG         = "%MW6026.10";
String PC_HL_ERHBC_BBELPN_EMREM                 = "%MW6022.4";
String PC_HL_ERHBC_BBELPN_SOBREC                = "%MW6022.3";
String PC_HL_ERHBC_BBELPN_MOTPNLIG              = "%MW6022.2";
String PC_HL_ERHBC_BBELPN_EMAUT                 = "%MW6022.1";
String PC_HL_ERHBC_BBELPN_MOTELLIG              = "%MW6022.0";
//--------------------------- MODHID ---------------------------
String PC_HA_ERHBC_MODHID_TEMPOL                = "%MF6266";
String PC_HA_ERHBC_MODHID_OLPRESS               = "%MF6158";
String PC_HL_ERHBC_MODHID_OLPBX                 = "%MW6022.6";
String PC_HL_ERHBC_MODHID_OLPDIFAL              = "%MW6022.5";
//--------------------------- CATRAC ---------------------------
String PC_HL_ERPBC_CATRAC_DESENGATADO           = "%MW6023.3";
//--------------------------- FREIO ---------------------------
String PC_HL_ERPBC_FREIO_DESENGATADO            = "%MW6023.4";
//--------------------------- MODPRI ---------------------------
String PC_HA_ERPBC_MODPRI_TEMPMANCAL9           = "%MF6284";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL8           = "%MF6282";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL7           = "%MF6280";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL6           = "%MF6278";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL5           = "%MF6276";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL4           = "%MF6274";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL3           = "%MF6272";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL2           = "%MF6270";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL1           = "%MF6268";
String PC_HA_ERPBC_MODPRI_TEMPMANCAL10          = "%MF6286";
//--------------------------- SSSK1 ---------------------------
String CP_HL_ERPBC_SSSK1_TRAVAR                 = "%MW508.0";
String PC_HL_ERPBC_SSSK1_NTRAVACPL              = "%MW6022.14";
String PC_HL_ERPBC_SSSK1_TRAVACPL               = "%MW6022.13";
String PC_HL_ERPBC_SSSK1_DACPL                  = "%MW6022.12";
String PC_HL_ERPBC_SSSK1_ACPL                   = "%MW6022.11";
String PC_HL_ERPBC_SSSK1_NTRAVABER              = "%MW6022.8";
String PC_HL_ERPBC_SSSK1_TRAVABER               = "%MW6022.7";
//--------------------------- SSSK2 ---------------------------
String CP_HL_ERPBC_SSSK2_TRAVAR                 = "%MW508.1";
String PC_HL_ERPBC_SSSK2_NTRAVACPL              = "%MW6023.2";
String PC_HL_ERPBC_SSSK2_TRAVACPL               = "%MW6023.1";
String PC_HL_ERPBC_SSSK2_DACPL                  = "%MW6023.0";
String PC_HL_ERPBC_SSSK2_ACPL                   = "%MW6022.15";
String PC_HL_ERPBC_SSSK2_NTRAVABER              = "%MW6022.10";
String PC_HL_ERPBC_SSSK2_TRAVABER               = "%MW6022.9";
//--------------------------- MLEAR ---------------------------
String PC_HA_ERSBB_MLEAR_TEMP                   = "%MF6152";
//--------------------------- MLEAV ---------------------------
String PC_HA_ERSBB_MLEAV_TEMP                   = "%MF6148";
//--------------------------- MODSBB ---------------------------
String PC_HA_ERSBB_MODSBB_TEMPMANCAL8           = "%MF6364";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL7           = "%MF6362";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL6           = "%MF6360";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL5           = "%MF6358";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL4           = "%MF6356";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL3           = "%MF6354";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL2           = "%MF6352";
String PC_HA_ERSBB_MODSBB_TEMPMANCAL1           = "%MF6350";
String PC_HA_ERSBB_MODSBB_EIXOBBRPM             = "%MF6156";
//--------------------------- SSSK3 ---------------------------
String CP_HL_ERSBB_SSSK3_TRAVAR                 = "%MW508.3";
String PC_HL_ERSBB_SSSK3_DACPL                  = "%MW6023.14";
String PC_HL_ERSBB_SSSK3_ACPL                   = "%MW6023.13";
String PC_HL_ERSBB_SSSK3_OLPBX                  = "%MW6023.12";
String PC_HL_ERSBB_SSSK3_NTRAVACPL              = "%MW6023.11";
String PC_HL_ERSBB_SSSK3_TRAVACPL               = "%MW6023.10";
//--------------------------- MLEAR ---------------------------
String PC_HA_ERSBE_MLEAR_TEMP                   = "%MF6150";
//--------------------------- MLEAV ---------------------------
String PC_HA_ERSBE_MLEAV_TEMP                   = "%MF6146";
//--------------------------- MODSBE ---------------------------
String PC_HA_ERSBE_MODSBE_TEMPMANCAL8           = "%MF6348";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL7           = "%MF6346";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL6           = "%MF6344";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL5           = "%MF6342";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL4           = "%MF6340";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL3           = "%MF6338";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL2           = "%MF6336";
String PC_HA_ERSBE_MODSBE_TEMPMANCAL1           = "%MF6334";
String PC_HA_ERSBE_MODSBE_EIXOBERPM             = "%MF6154";
//--------------------------- SSSK4 ---------------------------
String CP_HL_ERSBE_SSSK4_TRAVAR                 = "%MW508.2";
String PC_HL_ERSBE_SSSK4_DACPL                  = "%MW6023.9";
String PC_HL_ERSBE_SSSK4_ACPL                   = "%MW6023.8";
String PC_HL_ERSBE_SSSK4_OLPBX                  = "%MW6023.7";
String PC_HL_ERSBE_SSSK4_NTRAVACPL              = "%MW6023.6";
String PC_HL_ERSBE_SSSK4_TRAVACPL               = "%MW6023.5";
//---------------------------  AFBB  ---------------------------
String PC_SL_MCPBB_ECS_AFCHEIO                  = "%MW7502.6";
String PC_HL_MCPBB_RTU_AFCHEIO                  = "%MW6298.11";
//---------------------------  AFBE  ---------------------------
String PC_SL_MCPBE_ECS_AFCHEIO                  = "%MW7002.6";
String PC_HL_MCPBE_RTU_AFCHEIO                  = "%MW6230.11";
//---------------------------  MCPBB ---------------------------
String PC_SA_MCPBB_ECS_MCPRPM                   = "%MF7662";
String PC_HA_MCPBB_RTU_MCPRPM                   = "%MF6302";
//---------------------------  MCPBE ---------------------------
String PC_SA_MCPBE_ECS_MCPRPM                   = "%MF7162";
String PC_HA_MCPBE_RTU_MCPRPM                   = "%MF6234";
//---------------------------   TG   ---------------------------
String PC_SA_TBGAS_ATLAS_NTP                    = "%MF8120";
String PC_HA_TBGAS_MCTG_NTP                     = "%MF6200";

//------------------- VARIAVEIS DOS INTERNAS -------------------
//DEFINIÇÃO DE CONEXÃO
String IP              = "120.40.0.1";
String CONTADOR_CONEXAO= "%MW33000";
String NomeForm        = "ER";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;
int    lista           = 0;

//DEFINIÇÃO INTERNA
float   pressao           = 0.0;
bool    AF_BB_CHEIO       = false;
bool    AF_BE_CHEIO       = false;
bool    SSS_MCP_BB_ACPL   = false;
bool    SSS_MCP_BE_ACPL   = false;
bool    SSS_TG_BB_ACPL    = false;
bool    SSS_TG_BE_ACPL    = false;
bool    SSS_MCP_BB_TRAV   = false;
bool    SSS_MCP_BE_TRAV   = false;
bool    SSS_TG_BB_TRAV    = false;
bool    SSS_TG_BE_TRAV    = false;
bool    SSS_TG_BB_TRANS   = false;
bool    SSS_TG_BE_TRANS   = false;
float   rotacao_MCP_BB    = 0.0;
float   rotacao_MCP_BE    = 0.0;
float   rotacao_TG_NTP    = 0.0;
bool    habilita_edicao   = false;
float   escorreg_bb       = 0.0;
float   escorreg_be       = 0.0;
double  referencia_mcpbb  = 0.0;
double  referencia_mcpbe  = 0.0;
double  referencia_tg     = 0.0;
bool    nao_atender_cmd   = false;
bool    nao_pressurizar   = false;
bool    habilita_sss      = true;
bool    ctrl_auto_temp_ol = true;
bool    ROT_MOD_SEC       = false;
bool    ROT_MOD_PRI       = false;
int     temp_ol_er        = 25;

bool    bba_elpn_emauto   = false;
int     rot_eixo_bb_geral = 0;
int     rot_eixo_be_geral = 0;
bool    ctrl_auto_presost = false;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;

//CONFIGURAÇÃO DO DRIVER
TModBusTCPDriver CLP ( frmPrincipal,IP,QUANTUM );

//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{
        AnsiString TimeStamp;
//ABERTURA DA CONEXÃO COM CLP
        CLP.Open(IP);
//INÍCIO DA INICIALIZAÇÃO
        frmPrincipal->Caption = NomeForm + " - Carregando";
        frmPrincipal->Top = 0;
        frmPrincipal->Left = 0;
        frmPrincipal->Height = 600;
        frmPrincipal->Width = 800;

        DateTimeToString( TimeStamp, AnsiString( "hh:nn:ss" ), Now() );

        lblInit1->Caption  = "Incializando";
        lblInit2->Caption  = "Incializando";
        lblInit3->Caption  = "Incializando";
        lblInit4->Caption  = "Incializando";
        lblInit5->Caption  = "Incializando";
        lblInit6->Caption  = "Incializando";
        lblInit7->Caption  = "Incializando";
        lblInit8->Caption  = "Incializando";
        lblInit9->Caption  = "Incializando";
        lblInit10->Caption = "Incializando";

        lblInicioPrograma->Caption = TimeStamp;
        lblInicioPrograma->Visible = true;
        lblEndereco->Caption = CONTADOR_CONEXAO;
        lblEndereco->Visible = true;
        lblWatchdogEx->Visible = true;

//CHAMA TIMER DE INICIALIZAÇÃO
        tmrStarting->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrStartingTimer(TObject *Sender)
{
//TIMER DE INICIALIZÃÇÃO
//-------------------------------------------------------------
//--------------------- INICIA ANALÓGICAS ---------------------
//        CLP.WR( VARIAVEL_ANALOGICA , VALOR INCIAL);
//        PROGRESS_BAR>Max = 100 * 1000;
//        PROGRESS_BAR->Min = -100 * 1000;

        CLP.WR( PC_HA_ERHBC_MODHID_TEMPOL , 25);
        prbMODHID_TEMPOL->Max = 100 * 1000;
        prbMODHID_TEMPOL->Min = 0 * 1000;


        CLP.WR( PC_HA_ERHBC_MODHID_OLPRESS , 0.0);
        prbMODHID_OLPRESS->Max = 10 * 1000;
        prbMODHID_OLPRESS->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL10 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL10->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL10->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL9 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL9->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL9->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL8 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL8->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL8->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL7 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL7->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL7->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL6 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL6->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL6->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL5 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL5->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL5->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL4 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL4->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL4->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL3 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL3->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL3->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL2 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL2->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL2->Min = 0 * 1000;

        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL1 , 25);
        frmMancal->prbMODPRI_TEMPMANCAL1->Max = 100 * 1000;
        frmMancal->prbMODPRI_TEMPMANCAL1->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL8 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL8->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL8->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL7 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL7->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL7->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL6 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL6->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL6->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL5 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL5->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL5->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL4 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL4->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL4->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL3 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL3->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL3->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL2 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL2->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL2->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL1 , 25);
        frmMancal->prbMODSBB_TEMPMANCAL1->Max = 100 * 1000;
        frmMancal->prbMODSBB_TEMPMANCAL1->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL8 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL8->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL8->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL7 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL7->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL7->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL6 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL6->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL6->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL5 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL5->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL5->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL4 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL4->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL4->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL3 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL3->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL3->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL2 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL2->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL2->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL1 , 25);
        frmMancal->prbMODSBE_TEMPMANCAL1->Max = 100 * 1000;
        frmMancal->prbMODSBE_TEMPMANCAL1->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MLEAV_TEMP , 25);
        frmMancal->prbBB_MLEAV_TEMP->Max = 100 * 1000;
        frmMancal->prbBB_MLEAV_TEMP->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MLEAR_TEMP , 25);
        frmMancal->prbBB_MLEAR_TEMP->Max = 100 * 1000;
        frmMancal->prbBB_MLEAR_TEMP->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MLEAV_TEMP , 25);
        frmMancal->prbBE_MLEAV_TEMP->Max = 100 * 1000;
        frmMancal->prbBE_MLEAV_TEMP->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBE_MLEAR_TEMP , 25);
        frmMancal->prbBE_MLEAR_TEMP->Max = 100 * 1000;
        frmMancal->prbBE_MLEAR_TEMP->Min = 0 * 1000;

        CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM , 0);
        prbEIXOBBRPM_MODSBB->Max = 300 * 1000;
        prbEIXOBBRPM_MODSBB->Min = -250 * 1000;

        CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM , 0);
        prbEIXOBERPM_MODSBE->Max = 300 * 1000;
        prbEIXOBERPM_MODSBE->Min = -250 * 1000;


//-------------------------------------------------------------
//---------------------  INICIA DIGITAIS  ---------------------
        /*CLP.WR( VARIAVEL_DIGITAL, 0 OU 1 );*/
        CLP.WR( PC_HL_ERHBC_BBELPN_MOTELLIG     , 0 );
        CLP.WR( PC_HL_ERHBC_BBELPN_MOTPNLIG     , 0 );
        CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI, 0 );
	CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE, 1 );
        CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG, 0 );
        CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES, 1 );

        CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVACPL     , 1 );
	CLP.WR( PC_HL_ERPBC_SSSK1_TRAVACPL      , 0 );
	CLP.WR( PC_HL_ERPBC_SSSK1_DACPL         , 1 );
	CLP.WR( PC_HL_ERPBC_SSSK1_ACPL          , 0 );
	CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVABER     , 1 );
	CLP.WR( PC_HL_ERPBC_SSSK1_TRAVABER      , 0 );

        CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVACPL     , 1 );
	CLP.WR( PC_HL_ERPBC_SSSK2_TRAVACPL      , 0 );
	CLP.WR( PC_HL_ERPBC_SSSK2_DACPL         , 1 );
	CLP.WR( PC_HL_ERPBC_SSSK2_ACPL          , 0 );
	CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVABER     , 1 );
	CLP.WR( PC_HL_ERPBC_SSSK2_TRAVABER      , 0 );

        CLP.WR( PC_HL_ERSBB_SSSK3_NTRAVACPL     , 1 );
	CLP.WR( PC_HL_ERSBB_SSSK3_TRAVACPL      , 0 );
	CLP.WR( PC_HL_ERSBB_SSSK3_DACPL         , 1 );
	CLP.WR( PC_HL_ERSBB_SSSK3_ACPL          , 0 );

        CLP.WR( PC_HL_ERSBE_SSSK4_NTRAVACPL     , 1 );
	CLP.WR( PC_HL_ERSBE_SSSK4_TRAVACPL      , 0 );
	CLP.WR( PC_HL_ERSBE_SSSK4_DACPL         , 1 );
	CLP.WR( PC_HL_ERSBE_SSSK4_ACPL          , 0 );

	CLP.WR( PC_HL_ERPBC_CATRAC_DESENGATADO  , 1 );
	CLP.WR( PC_HL_ERPBC_FREIO_DESENGATADO   , 1 );
        CLP.WR( PC_HL_ERHBC_BBELPN_EMREM        , 1 );


//-------------------------------------------------------------
//ACIONA TODOS OS ENDEREÇOS DE SIMULAÇÃO
        for (int i = 3010; i < 3236; i++){
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0xFFFF);
        }

        frmPrincipal->Caption = NomeForm + " - Populando";

        tmrLeitura->Enabled = true;



        lblInit1->Caption   = "BBELPN";
        lblInit2->Caption   = "MODHID";
        lblInit3->Caption   = "CATRAC";
        lblInit4->Caption   = "FREIO";

        frmMancal->lblInit1->Caption = "MODPRI";
        frmMancal->lblInit2->Caption = "MODSBB";
        frmMancal->lblInit3->Caption = "MODSBE";
        frmMancal->lblInit4->Caption = "ERSBB LE";
        frmMancal->lblInit5->Caption = "ERSBE LE";

        lblInit5->Caption   = "MODSBB";
        lblInit6->Caption   = "MODSBE";
        lblInit7->Caption   = "SSSK1";
        lblInit8->Caption   = "SSSK2";
        lblInit9->Caption   = "SSSK3";
        lblInit10->Caption  = "SSSK4";
        //INFORMAÇÕES FIXAS
        lblInit11->Caption  = "BBELPN";
        lblInit12->Caption  = "MODPRI";
        lblInit13->Caption  = "MODSBB";
        lblInit14->Caption  = "MODSBE";
        lblInit15->Caption = "Rotação Eixo BB";
        lblInit16->Caption = "Rotação Eixo BE";
        lblInit17->Caption = "SSSK1 TG BB MPRI";
        lblInit18->Caption = "SSSK2 TG BE MPRI";
        lblInit19->Caption = "SSSK3 MCP BB MSEC";
        lblInit20->Caption = "SSSK4 MCP BE MSEC";

        lblBufferR->Visible  = true;
        lblBufferW->Visible  = true;
        lblBufferEx->Visible = true;
        lblLista->Visible    = true;

        if (ConexaoWatch->Enabled == false){
                ConexaoWatch->Enabled = true;
        }

        Lista->Enabled = true;

        btnReset->Enabled = true;

//FIM DA INICIALIZAÇÃO
        tmrStarting->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::ConexaoWatchTimer(TObject *Sender)
{
//TIMER DE VERIFICAÇÃO DE CONEXÃO
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
void __fastcall TfrmPrincipal::tmrReconectaTimer(TObject *Sender)
{
//RECONEXÃO
        CLP.Open(IP);
        tmrReconecta->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrLeituraTimer(TObject *Sender)
{
//TIMER DE ESCRITA, LEITURA E TRATAMENTO DOS SINAIS
//==============================================================================
//==============================================================================
//ERHBC_BBELPN
	if ( CLP.RD(PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES) == 1 ){
		shpAUTOHDWSCMDES_BBELPN->Brush->Color = clNavy;
		btnAUTOHDWSCMDES_BBELPN->Caption = "AUTOHDWSCMDES";
	}
	else{
		shpAUTOHDWSCMDES_BBELPN->Brush->Color = clWhite;
		btnAUTOHDWSCMDES_BBELPN->Caption = "Ñ AUTOHDWSCMDES";
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG) == 1 ){
		shpAUTOHDWSCMLIG_BBELPN->Brush->Color = clNavy;
		btnAUTOHDWSCMLIG_BBELPN->Caption = "AUTOHDWSCMLIG";
	}
	else{
		shpAUTOHDWSCMLIG_BBELPN->Brush->Color = clWhite;
		btnAUTOHDWSCMLIG_BBELPN->Caption = "Ñ AUTOHDWSCMLIG";
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI) == 1 ){
		shpPRDEMERGSCMLI_BBELPN->Brush->Color = clNavy;
		btnPRDEMERGSCMLI_BBELPN->Caption = "PRDEMERGSCMLI";
	}
	else{
		shpPRDEMERGSCMLI_BBELPN->Brush->Color = clWhite;
		btnPRDEMERGSCMLI_BBELPN->Caption = "Ñ PRDEMERGSCMLI";
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE) == 1 ){
		shpPRDEMERGSCMDE_BBELPN->Brush->Color = clNavy;
		btnPRDEMERGSCMDE_BBELPN->Caption = "PRDEMERGSCMDE";
	}
	else{
		shpPRDEMERGSCMDE_BBELPN->Brush->Color = clWhite;
		btnPRDEMERGSCMDE_BBELPN->Caption = "Ñ PRDEMERGSCMDE";
	}

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_EMAUT) == 1 ){
		shpEmAut_BBELPN->Brush->Color = clNavy;
		btnEmAut_BBELPN->Caption = "Em Auto";
                bba_elpn_emauto = true;
	}
	else{
		shpEmAut_BBELPN->Brush->Color = clWhite;
		btnEmAut_BBELPN->Caption = "Em Manual";
                bba_elpn_emauto = false;
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_EMREM) == 1 ){
		shpRemoto_BBELPN->Brush->Color = clNavy;
		btnRemoto_BBELPN->Caption = "Remoto";
	}
	else{
		shpRemoto_BBELPN->Brush->Color = clWhite;
		btnRemoto_BBELPN->Caption = "Local";
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_MOTELLIG) == 1 ){
		shpMOTELLIG_BBELPN->Brush->Color = clLime;
		btnMOTELLIG_BBELPN->Caption = "Mot. El. Ligado";
	}
	else{
		shpMOTELLIG_BBELPN->Brush->Color = clWhite;
		btnMOTELLIG_BBELPN->Caption = "Mot. El. Parado";
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_MOTPNLIG) == 1 ){
		shpMOTPNLIG_BBELPN->Brush->Color = clLime;
		btnMOTPNLIG_BBELPN->Caption = "Mot. Pn. Ligado";
	}
	else{
		shpMOTPNLIG_BBELPN->Brush->Color = clWhite;
		btnMOTPNLIG_BBELPN->Caption = "Mot. Pn. Parado";
	};

        if ( CLP.RD(PC_HL_ERHBC_BBELPN_SOBREC) == 1 ){
		shpSobrec_BBELPN->Brush->Color = clRed;
		btnSobrec_BBELPN->Caption = "Em Sobrec.";
	}
	else{
		shpSobrec_BBELPN->Brush->Color = clWhite;
		btnSobrec_BBELPN->Caption = "Sem Sobrec.";
	};

        if ( CLP.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG) == 1 ){
		shpLibEmerg_BBELPN->Brush->Color = clYellow;
		if (btnPRDEMERGSCMLI_BBELPN->Caption == "PRDEMERGSCMLI"){
			CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI, 0 );
			CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE, 1 );
		}
        }
        else{
		shpLibEmerg_BBELPN->Brush->Color = clWhite;
	};

        if ( CLP.RD(CP_HL_ERHBC_BBELPN_PARAREMERG) == 1 ){
		shpEmerg_BBELPN->Brush->Color = clRed;
		if ((btnMOTELLIG_BBELPN->Caption == "Mot. El. Ligado" || btnMOTPNLIG_BBELPN->Caption == "Mot. Pn. Ligado") || btnPRDEMERGSCMLI_BBELPN->Caption == "Ñ PRDEMERGSCMLI" ){
                        tmrPartir_ERHBC_BBELPN->Enabled = false;
                        CLP.WR( PC_HL_ERHBC_BBELPN_MOTELLIG, 0 );
                        CLP.WR( PC_HL_ERHBC_BBELPN_MOTPNLIG, 0 );
			CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE, 0 );
                        CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI, 1 );
		}
	}
	else{
		shpEmerg_BBELPN->Brush->Color = clWhite;
	};

        if ( CLP.RD(CP_HL_ERHBC_BBELPN_DESLIGAR) == 1 ){
		shpDesligarBBELPN->Brush->Color = clYellow;
		if ((btnMOTELLIG_BBELPN->Caption == "Mot. El. Ligado" || btnMOTPNLIG_BBELPN->Caption == "Mot. Pn. Ligado") && tmrParar_ERHBC_BBELPN->Enabled == false){
                        if ( nao_atender_cmd == false ) {
        			tmrPartir_ERHBC_BBELPN->Enabled = false;
                                tmrParar_ERHBC_BBELPN->Enabled = true;
                                if ( nao_pressurizar == false ){
                                        tmrPressurizar->Enabled = false;
                                        tmrDespressurizar->Enabled = true;
                                }
                        }
		}
	}
	else{
		shpDesligarBBELPN->Brush->Color = clWhite;
                //tmrParar_ERHBC_BBELPN->Enabled = false;
	};

        if ( CLP.RD(CP_HL_ERHBC_BBELPN_LIGAR) == 1 ){
		shpLigarBBELPN->Brush->Color = clLime;
		if ((btnMOTELLIG_BBELPN->Caption == "Mot. El. Parado" || btnMOTPNLIG_BBELPN->Caption == "Mot. Pn. Parado") && tmrPartir_ERHBC_BBELPN->Enabled == false){
                        if ( nao_atender_cmd == false ) {
                                tmrParar_ERHBC_BBELPN->Enabled = false;
                                tmrPartir_ERHBC_BBELPN->Enabled = true;
                                if ( nao_pressurizar == false ){
                                        tmrDespressurizar->Enabled = false;
                                        tmrPressurizar->Enabled = true;
                                }
                        }
		}
	}
	else{
		shpLigarBBELPN->Brush->Color = clWhite;
                //tmrPartir_ERHBC_BBELPN->Enabled = false;
	};

        if ( CLP.RD(CP_HL_ERHBC_BBELPN_MANUAL) == 1 ){
		shpMANUALBBELPN->Brush->Color = clYellow;
		if (btnEmAut_BBELPN->Caption == "Em Auto"){
			CLP.WR( PC_HL_ERHBC_BBELPN_EMAUT, 0 );
                }
                if (btnAUTOHDWSCMLIG_BBELPN->Caption == "AUTOHDWSCMLIG"){
                        CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG, 0 );
                        CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES, 1 );
		}
	}
	else{
		shpMANUALBBELPN->Brush->Color = clWhite;
	};

        if ( CLP.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO) == 1 ){
		shpAUTOMATICOBBELPN->Brush->Color = clYellow;
		if (btnEmAut_BBELPN->Caption == "Em Manual"){
                        CLP.WR( PC_HL_ERHBC_BBELPN_EMAUT, 1 );
                }
                if(btnAUTOHDWSCMLIG_BBELPN->Caption == "Ñ AUTOHDWSCMLIG"){
                        CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES, 0 );
                        CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG, 1 );
		}
	}
	else{
		shpAUTOMATICOBBELPN->Brush->Color = clWhite;
	};


//==============================================================================
//ERHBC_MODHID

        if ( CLP.RD(PC_HL_ERHBC_MODHID_OLPBX) == 0 ){
		shpMODHID_OLPBX->Brush->Color = clRed;
		btnMODHID_OLPBX->Caption = "Baixa Press.";
	}
	else{
		shpMODHID_OLPBX->Brush->Color = clWhite;
		btnMODHID_OLPBX->Caption = "Press. OK";
	};

        if ( CLP.RD(PC_HL_ERHBC_MODHID_OLPDIFAL) == 1 ){
		shpMODHID_OLPDIFAL->Brush->Color = clRed;
		btnMODHID_OLPDIFAL->Caption = "Alta Press. Dif.";
	}
	else{
		shpMODHID_OLPDIFAL->Brush->Color = clWhite;
		btnMODHID_OLPDIFAL->Caption = "Press. Dif. OK";
	};

        lblMODHID_TEMPOL->Caption = CLP.RD(PC_HA_ERHBC_MODHID_TEMPOL);
        lblMODHID_TEMPOL->Caption = FormatFloat("0.##",lblMODHID_TEMPOL->Caption.ToDouble());
        prbMODHID_TEMPOL->Position = CLP.RD(PC_HA_ERHBC_MODHID_TEMPOL) * 1000;

        lblMODHID_OLPRESS->Caption = CLP.RD(PC_HA_ERHBC_MODHID_OLPRESS);
        lblMODHID_OLPRESS->Caption = FormatFloat("0.##",lblMODHID_OLPRESS->Caption.ToDouble());
        prbMODHID_OLPRESS->Position = CLP.RD(PC_HA_ERHBC_MODHID_OLPRESS) * 1000;

//==============================================================================
//ERPBC_CATRAC

        if ( CLP.RD(PC_HL_ERPBC_CATRAC_DESENGATADO) == 1 ){
		shpERPBC_CATRAC->Brush->Color = clYellow;
		btnERPBC_CATRAC->Caption = "Desengatado";
	}
	else{
		shpERPBC_CATRAC->Brush->Color = clWhite;
		btnERPBC_CATRAC->Caption = "Engatado";
	};

//==============================================================================
//ERPBC_FREIO

        if ( CLP.RD(PC_HL_ERPBC_FREIO_DESENGATADO) == 1 ){
		shpERPBC_FREIO->Brush->Color = clYellow;
		btnERPBC_FREIO->Caption = "Desengatado";
	}
	else{
		shpERPBC_FREIO->Brush->Color = clWhite;
		btnERPBC_FREIO->Caption = "Engatado";
	};


//==============================================================================
//ERPBC_MODPRI

        frmMancal->lblMODPRI_TEMPMANCAL10->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL10);
        frmMancal->lblMODPRI_TEMPMANCAL10->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL10->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL10->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL10) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL9->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL9);
        frmMancal->lblMODPRI_TEMPMANCAL9->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL9->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL9->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL9) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL8->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL8);
        frmMancal->lblMODPRI_TEMPMANCAL8->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL8->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL8->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL8) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL7->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL7);
        frmMancal->lblMODPRI_TEMPMANCAL7->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL7->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL7->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL7) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL6->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL6);
        frmMancal->lblMODPRI_TEMPMANCAL6->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL6->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL6->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL6) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL5->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL5);
        frmMancal->lblMODPRI_TEMPMANCAL5->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL5->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL5->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL5) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL4->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL4);
        frmMancal->lblMODPRI_TEMPMANCAL4->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL4->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL4->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL4) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL3->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL3);
        frmMancal->lblMODPRI_TEMPMANCAL3->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL3->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL3->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL3) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL2->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL2);
        frmMancal->lblMODPRI_TEMPMANCAL2->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL2->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL2->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL2) * 1000;

        frmMancal->lblMODPRI_TEMPMANCAL1->Caption = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL1);
        frmMancal->lblMODPRI_TEMPMANCAL1->Caption = FormatFloat("0.##",frmMancal->lblMODPRI_TEMPMANCAL1->Caption.ToDouble());
        frmMancal->prbMODPRI_TEMPMANCAL1->Position = CLP.RD(PC_HA_ERPBC_MODPRI_TEMPMANCAL1) * 1000;

//==============================================================================
//ERSBB_MODSBB

        frmMancal->lblMODSBB_TEMPMANCAL8->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL8);
        frmMancal->lblMODSBB_TEMPMANCAL8->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL8->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL8->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL8) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL7->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL7);
        frmMancal->lblMODSBB_TEMPMANCAL7->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL7->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL7->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL7) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL6->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL6);
        frmMancal->lblMODSBB_TEMPMANCAL6->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL6->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL6->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL6) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL5->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL5);
        frmMancal->lblMODSBB_TEMPMANCAL5->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL5->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL5->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL5) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL4->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL4);
        frmMancal->lblMODSBB_TEMPMANCAL4->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL4->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL4->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL4) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL3->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL3);
        frmMancal->lblMODSBB_TEMPMANCAL3->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL3->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL3->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL3) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL2->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL2);
        frmMancal->lblMODSBB_TEMPMANCAL2->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL2->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL2->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL2) * 1000;

        frmMancal->lblMODSBB_TEMPMANCAL1->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL1);
        frmMancal->lblMODSBB_TEMPMANCAL1->Caption = FormatFloat("0.##",frmMancal->lblMODSBB_TEMPMANCAL1->Caption.ToDouble());
        frmMancal->prbMODSBB_TEMPMANCAL1->Position = CLP.RD(PC_HA_ERSBB_MODSBB_TEMPMANCAL1) * 1000;

        lblEIXOBBRPM_MODSBB->Caption = CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM);
        lblEIXOBBRPM_MODSBB->Caption = FormatFloat("0.##",lblEIXOBBRPM_MODSBB->Caption.ToDouble());
        prbEIXOBBRPM_MODSBB->Position = CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) * 1000;

        rot_eixo_bb_geral = lblEIXOBBRPM_MODSBB->Caption.ToInt();

//==============================================================================
//ERSBE_MODSBE

        frmMancal->lblMODSBE_TEMPMANCAL8->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL8);
        frmMancal->lblMODSBE_TEMPMANCAL8->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL8->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL8->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL8) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL7->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL7);
        frmMancal->lblMODSBE_TEMPMANCAL7->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL7->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL7->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL7) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL6->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL6);
        frmMancal->lblMODSBE_TEMPMANCAL6->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL6->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL6->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL6) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL5->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL5);
        frmMancal->lblMODSBE_TEMPMANCAL5->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL5->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL5->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL5) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL4->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL4);
        frmMancal->lblMODSBE_TEMPMANCAL4->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL4->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL4->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL4) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL3->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL3);
        frmMancal->lblMODSBE_TEMPMANCAL3->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL3->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL3->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL3) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL2->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL2);
        frmMancal->lblMODSBE_TEMPMANCAL2->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL2->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL2->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL2) * 1000;

        frmMancal->lblMODSBE_TEMPMANCAL1->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL1);
        frmMancal->lblMODSBE_TEMPMANCAL1->Caption = FormatFloat("0.##",frmMancal->lblMODSBE_TEMPMANCAL1->Caption.ToDouble());
        frmMancal->prbMODSBE_TEMPMANCAL1->Position = CLP.RD(PC_HA_ERSBE_MODSBE_TEMPMANCAL1) * 1000;

        lblEIXOBERPM_MODSBE->Caption = CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM);
        lblEIXOBERPM_MODSBE->Caption = FormatFloat("0.##",lblEIXOBERPM_MODSBE->Caption.ToDouble());
        prbEIXOBERPM_MODSBE->Position = CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) * 1000;

        rot_eixo_be_geral = lblEIXOBERPM_MODSBE->Caption.ToInt();

//==============================================================================
//ERPBC_SSSK1

        if ( CLP.RD(PC_HL_ERPBC_SSSK1_ACPL) == 1 ){
                shpSSSK1_ACPL->Brush->Color = clLime;
		btnSSSK1_ACPL->Caption = "Acoplada";
                SSS_TG_BB_ACPL = true;
	}
        else{
                shpSSSK1_ACPL->Brush->Color = clWhite;
		btnSSSK1_ACPL->Caption = "Não Acoplada";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK1_DACPL) == 1 ){
	        shpSSSK1_DACPL->Brush->Color = clYellow;
		btnSSSK1_DACPL->Caption = "Desacoplada";
                SSS_TG_BB_ACPL = false;
	}
        else{
                shpSSSK1_DACPL->Brush->Color = clWhite;
		btnSSSK1_DACPL->Caption = "Não Desacoplada";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK1_TRAVABER) == 1 ){
	        shpSSSK1_TRAVABER->Brush->Color = clLime;
		btnSSSK1_TRAVABER->Caption = "Travada Aberta";
                SSS_TG_BB_TRANS = false;
                btnSSSK1_FERRAMENTA->Caption = "FECHAR";
	}
        else{
                shpSSSK1_TRAVABER->Brush->Color = clWhite;
		btnSSSK1_TRAVABER->Caption = "Travada Aberta Ñ OK";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK1_NTRAVABER) == 1 ){
	        shpSSSK1_NTRAVABER->Brush->Color = clYellow;
		btnSSSK1_NTRAVABER->Caption = "Não Travada Aberta";
                SSS_TG_BB_TRANS = true;
                btnSSSK1_FERRAMENTA->Caption = "ABRIR";
	}
        else{
                shpSSSK1_NTRAVABER->Brush->Color = clWhite;
		btnSSSK1_NTRAVABER->Caption = "Não Trav. Aberta Ñ OK";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK1_TRAVACPL) == 1 ){
	        shpSSSK1_TRAVACPL->Brush->Color = clLime;
		btnSSSK1_TRAVACPL->Caption = "Travada";
                btnSSSK1_TRAVAR->Caption = "DESTRAVAR";
                SSS_TG_BB_TRAV   = true;

	}
        else{
                shpSSSK1_TRAVACPL->Brush->Color = clWhite;
		btnSSSK1_TRAVACPL->Caption = "Não Travada";
                SSS_TG_BB_TRAV   = false;

        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK1_NTRAVACPL) == 1 ){
	        shpSSSK1_NTRAVACPL->Brush->Color = clRed;
		btnSSSK1_NTRAVACPL->Caption = "Destravada";
                btnSSSK1_TRAVAR->Caption = "TRAVAR";
	}
        else{
                shpSSSK1_NTRAVACPL->Brush->Color = clWhite;
		btnSSSK1_NTRAVACPL->Caption = "Não Destravada";
        }

        if ( CLP.RD(CP_HL_ERPBC_SSSK1_TRAVAR) == 1){
                shpSSSK1_TRAVAR->Brush->Color = clLime;
                if ( btnSSSK1_TRAVACPL->Caption == "Não Travada" || btnSSSK1_NTRAVACPL->Caption == "Destravada"){
                        CLP.WR(PC_HL_ERPBC_SSSK1_NTRAVACPL, 0);
                        CLP.WR(PC_HL_ERPBC_SSSK1_TRAVACPL , 1);
                        SSS_TG_BB_TRAV   = true;
                }
        }
        else{
                shpSSSK1_TRAVAR->Brush->Color = clWhite;
                if ( btnSSSK1_TRAVACPL->Caption == "Travada" || btnSSSK1_NTRAVACPL->Caption == "Não Destravada"){
                        if (SSS_TG_BB_TRAV   == true){
                                CLP.WR(PC_HL_ERPBC_SSSK1_TRAVACPL , 0);
                                CLP.WR(PC_HL_ERPBC_SSSK1_NTRAVACPL, 1);
                                SSS_TG_BB_TRAV   = false;
                        }
                }
        }

//==============================================================================
//ERPBC_SSSK2

        if ( CLP.RD(PC_HL_ERPBC_SSSK2_ACPL) == 1 ){
                shpSSSK2_ACPL->Brush->Color = clLime;
		btnSSSK2_ACPL->Caption = "Acoplada";
                SSS_TG_BE_ACPL = true;
	}
        else{
                shpSSSK2_ACPL->Brush->Color = clWhite;
		btnSSSK2_ACPL->Caption = "Não Acoplada";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK2_DACPL) == 1 ){
	        shpSSSK2_DACPL->Brush->Color = clYellow;
		btnSSSK2_DACPL->Caption = "Desacoplada";
                SSS_TG_BE_ACPL = false;
	}
        else{
                shpSSSK2_DACPL->Brush->Color = clWhite;
		btnSSSK2_DACPL->Caption = "Não Desacoplada";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK2_TRAVABER) == 1 ){
	        shpSSSK2_TRAVABER->Brush->Color = clLime;
		btnSSSK2_TRAVABER->Caption = "Travada Aberta";
                SSS_TG_BE_TRANS = false;
                btnSSSK2_FERRAMENTA->Caption = "FECHAR";
	}
        else{
                shpSSSK2_TRAVABER->Brush->Color = clWhite;
		btnSSSK2_TRAVABER->Caption = "Travada Aberta Ñ OK";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK2_NTRAVABER) == 1 ){
	        shpSSSK2_NTRAVABER->Brush->Color = clYellow;
		btnSSSK2_NTRAVABER->Caption = "Não Travada Aberta";
                SSS_TG_BE_TRANS = true;
                btnSSSK2_FERRAMENTA->Caption = "ABRIR";
	}
        else{
                shpSSSK2_NTRAVABER->Brush->Color = clWhite;
		btnSSSK2_NTRAVABER->Caption = "Não Trav. Aberta Ñ OK";
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK2_TRAVACPL) == 1 ){
	        shpSSSK2_TRAVACPL->Brush->Color = clLime;
		btnSSSK2_TRAVACPL->Caption = "Travada";
                btnSSSK2_TRAVAR->Caption = "DESTRAVAR";
                SSS_TG_BE_TRAV   = true;
	}
        else{
                shpSSSK2_TRAVACPL->Brush->Color = clWhite;
		btnSSSK2_TRAVACPL->Caption = "Não Travada";
                SSS_TG_BE_TRAV   = false;
        }

        if ( CLP.RD(PC_HL_ERPBC_SSSK2_NTRAVACPL) == 1 ){
	        shpSSSK2_NTRAVACPL->Brush->Color = clRed;
		btnSSSK2_NTRAVACPL->Caption = "Destravada";
                btnSSSK2_TRAVAR->Caption = "TRAVAR";
	}
        else{
                shpSSSK2_NTRAVACPL->Brush->Color = clWhite;
		btnSSSK2_NTRAVACPL->Caption = "Não Destravada";
        }

        if ( CLP.RD(CP_HL_ERPBC_SSSK2_TRAVAR) == 1){
                shpSSSK2_TRAVAR->Brush->Color = clLime;
                if ( btnSSSK2_TRAVACPL->Caption == "Não Travada" || btnSSSK2_NTRAVACPL->Caption == "Destravada"){
                        CLP.WR(PC_HL_ERPBC_SSSK2_NTRAVACPL, 0);
                        CLP.WR(PC_HL_ERPBC_SSSK2_TRAVACPL , 1);
                        SSS_TG_BE_TRAV   = true;
                }
        }
        else{
                shpSSSK2_TRAVAR->Brush->Color = clWhite;
                if ( btnSSSK2_TRAVACPL->Caption == "Travada" || btnSSSK2_NTRAVACPL->Caption == "Não Destravada"){
                        if (SSS_TG_BE_TRAV   == true){
                                CLP.WR(PC_HL_ERPBC_SSSK2_TRAVACPL , 0);
                                CLP.WR(PC_HL_ERPBC_SSSK2_NTRAVACPL, 1);
                                SSS_TG_BE_TRAV   = false;
                        }
                }
        }


//==============================================================================
//ERSBB_SSSK3

        if ( CLP.RD(PC_HL_ERSBB_SSSK3_ACPL) == 1 ){
                shpSSSK3_ACPL->Brush->Color = clLime;
		btnSSSK3_ACPL->Caption = "Acoplada";
                SSS_MCP_BB_ACPL = true;
	}
        else{
                shpSSSK3_ACPL->Brush->Color = clWhite;
		btnSSSK3_ACPL->Caption = "Não Acoplada";
        }

        if ( CLP.RD(PC_HL_ERSBB_SSSK3_DACPL) == 1 ){
	        shpSSSK3_DACPL->Brush->Color = clYellow;
		btnSSSK3_DACPL->Caption = "Desacoplada";
                SSS_MCP_BB_ACPL = false;
	}
        else{
                shpSSSK3_DACPL->Brush->Color = clWhite;
		btnSSSK3_DACPL->Caption = "Não Desacoplada";
        }
        
        if ( CLP.RD(PC_HL_ERSBB_SSSK3_TRAVACPL) == 1 ){
	        shpSSSK3_TRAVACPL->Brush->Color = clLime;
		btnSSSK3_TRAVACPL->Caption = "Travada";
                btnSSSK3_TRAVAR->Caption = "DESTRAVAR";
                SSS_MCP_BB_TRAV  = true;
	}
        else{
                shpSSSK3_TRAVACPL->Brush->Color = clWhite;
		btnSSSK3_TRAVACPL->Caption = "Não Travada";
                SSS_MCP_BB_TRAV  = false;
        }

        if ( CLP.RD(PC_HL_ERSBB_SSSK3_NTRAVACPL) == 1 ){
	        shpSSSK3_NTRAVACPL->Brush->Color = clRed;
		btnSSSK3_NTRAVACPL->Caption = "Destravada";
                btnSSSK3_TRAVAR->Caption = "TRAVAR";
	}
        else{
                shpSSSK3_NTRAVACPL->Brush->Color = clWhite;
		btnSSSK3_NTRAVACPL->Caption = "Não Destravada";
        }

        if ( CLP.RD(CP_HL_ERSBB_SSSK3_TRAVAR) == 1){
                shpSSSK3_TRAVAR->Brush->Color = clLime;
                if ( btnSSSK3_TRAVACPL->Caption == "Travada" || btnSSSK3_NTRAVACPL->Caption == "Não Destravada"){
                        CLP.WR(PC_HL_ERSBB_SSSK3_TRAVACPL , 0);
                        CLP.WR(PC_HL_ERSBB_SSSK3_NTRAVACPL, 1);
                        SSS_MCP_BB_TRAV  = false;
                }
        }
        else{
                shpSSSK3_TRAVAR->Brush->Color = clWhite;
        }
		
        if ( CLP.RD(PC_HL_ERSBB_SSSK3_OLPBX) == 0 ){
		shpSSSK3_OLPBX->Brush->Color = clRed;
		btnSSSK3_OLPBX->Caption = "Baixa Press.";
	}
	else{
		shpSSSK3_OLPBX->Brush->Color = clWhite;
		btnSSSK3_OLPBX->Caption = "Press. OK";
	};

//==============================================================================
//ERSBE_SSSK4

        if ( CLP.RD(PC_HL_ERSBE_SSSK4_ACPL) == 1 ){
                shpSSSK4_ACPL->Brush->Color = clLime;
		btnSSSK4_ACPL->Caption = "Acoplada";
                SSS_MCP_BE_ACPL = true;
	}
        else{
                shpSSSK4_ACPL->Brush->Color = clWhite;
		btnSSSK4_ACPL->Caption = "Não Acoplada";
        }

        if ( CLP.RD(PC_HL_ERSBE_SSSK4_DACPL) == 1 ){
	        shpSSSK4_DACPL->Brush->Color = clYellow;
		btnSSSK4_DACPL->Caption = "Desacoplada";
                SSS_MCP_BE_ACPL = false;
	}
        else{
                shpSSSK4_DACPL->Brush->Color = clWhite;
		btnSSSK4_DACPL->Caption = "Não Desacoplada";
        }
        
        if ( CLP.RD(PC_HL_ERSBE_SSSK4_TRAVACPL) == 1 ){
	        shpSSSK4_TRAVACPL->Brush->Color = clLime;
		btnSSSK4_TRAVACPL->Caption = "Travada";
                btnSSSK4_TRAVAR->Caption = "DESTRAVAR";
                SSS_MCP_BE_TRAV  = true;
	}
        else{
                shpSSSK4_TRAVACPL->Brush->Color = clWhite;
		btnSSSK4_TRAVACPL->Caption = "Não Travada";
                SSS_MCP_BE_TRAV  = false;
        }

        if ( CLP.RD(PC_HL_ERSBE_SSSK4_NTRAVACPL) == 1 ){
	        shpSSSK4_NTRAVACPL->Brush->Color = clRed;
		btnSSSK4_NTRAVACPL->Caption = "Destravada";
                btnSSSK4_TRAVAR->Caption = "TRAVAR";
	}
        else{
                shpSSSK4_NTRAVACPL->Brush->Color = clWhite;
		btnSSSK4_NTRAVACPL->Caption = "Não Destravada";
        }

        if ( CLP.RD(CP_HL_ERSBE_SSSK4_TRAVAR) == 1){
                shpSSSK4_TRAVAR->Brush->Color = clLime;
                if ( btnSSSK4_TRAVACPL->Caption == "Travada" || btnSSSK4_NTRAVACPL->Caption == "Não Destravada"){
                        CLP.WR(PC_HL_ERSBE_SSSK4_TRAVACPL , 0);
                        CLP.WR(PC_HL_ERSBE_SSSK4_NTRAVACPL, 1);
                        SSS_MCP_BE_TRAV  = false;

                }
        }
        else{
                shpSSSK4_TRAVAR->Brush->Color = clWhite;
        }
		
        if ( CLP.RD(PC_HL_ERSBE_SSSK4_OLPBX) == 0 ){
		shpSSSK4_OLPBX->Brush->Color = clRed;
		btnSSSK4_OLPBX->Caption = "Baixa Press.";
	}
	else{
		shpSSSK4_OLPBX->Brush->Color = clWhite;
		btnSSSK4_OLPBX->Caption = "Press. OK";
	};

//==============================================================================
//ERSBE_MLEAV

        frmMancal->lblBE_MLEAV_TEMP->Caption = CLP.RD(PC_HA_ERSBE_MLEAV_TEMP);
        frmMancal->lblBE_MLEAV_TEMP->Caption = FormatFloat("0.##",frmMancal->lblBE_MLEAV_TEMP->Caption.ToDouble());
        frmMancal->prbBE_MLEAV_TEMP->Position = CLP.RD(PC_HA_ERSBE_MLEAV_TEMP) * 1000;

//==============================================================================
//ERSBE_MLEAR

        frmMancal->lblBE_MLEAR_TEMP->Caption = CLP.RD(PC_HA_ERSBE_MLEAR_TEMP);
        frmMancal->lblBE_MLEAR_TEMP->Caption = FormatFloat("0.##",frmMancal->lblBE_MLEAR_TEMP->Caption.ToDouble());
        frmMancal->prbBE_MLEAR_TEMP->Position = CLP.RD(PC_HA_ERSBE_MLEAR_TEMP) * 1000;

//==============================================================================
//ERSBB_MLEAV

        frmMancal->lblBB_MLEAV_TEMP->Caption = CLP.RD(PC_HA_ERSBB_MLEAV_TEMP);
        frmMancal->lblBB_MLEAV_TEMP->Caption = FormatFloat("0.##",frmMancal->lblBB_MLEAV_TEMP->Caption.ToDouble());
        frmMancal->prbBB_MLEAV_TEMP->Position = CLP.RD(PC_HA_ERSBB_MLEAV_TEMP) * 1000;

//==============================================================================
//ERSBB_MLEAR

        frmMancal->lblBB_MLEAR_TEMP->Caption = CLP.RD(PC_HA_ERSBB_MLEAR_TEMP);
        frmMancal->lblBB_MLEAR_TEMP->Caption = FormatFloat("0.##",frmMancal->lblBB_MLEAR_TEMP->Caption.ToDouble());
        frmMancal->prbBB_MLEAR_TEMP->Position = CLP.RD(PC_HA_ERSBB_MLEAR_TEMP) * 1000;

        if ( ctrl_auto_presost == false ){
                if ( pressao >= 1.0 ){
                        if (CLP.RD(PC_HL_ERSBB_SSSK3_OLPBX) !=  1){
                                CLP.WR(PC_HL_ERSBB_SSSK3_OLPBX  , 1);
                        }
                        if (CLP.RD(PC_HL_ERSBE_SSSK4_OLPBX) !=  1){
                                CLP.WR(PC_HL_ERSBE_SSSK4_OLPBX  , 1);
                        }
                        if (CLP.RD(PC_HL_ERHBC_MODHID_OLPBX) !=  1){
                                CLP.WR(PC_HL_ERHBC_MODHID_OLPBX , 1);
                        }
                }
                else{
                        if (CLP.RD(PC_HL_ERSBB_SSSK3_OLPBX) !=  0){
                                CLP.WR(PC_HL_ERSBB_SSSK3_OLPBX  , 0);
                        }
                        if (CLP.RD(PC_HL_ERSBE_SSSK4_OLPBX) !=  0){
                                CLP.WR(PC_HL_ERSBE_SSSK4_OLPBX  , 0);
                        }
                        if (CLP.RD(PC_HL_ERHBC_MODHID_OLPBX) !=  0){
                                CLP.WR(PC_HL_ERHBC_MODHID_OLPBX , 0);
                        }
                };
        };
        btnSSSK3_OLPBX->Enabled = ctrl_auto_presost;
        btnSSSK4_OLPBX->Enabled = ctrl_auto_presost;
        btnMODHID_OLPBX->Enabled = ctrl_auto_presost;

//=========================================================================================
//================================ CONTROLE DAS SSS E======================================
//================================ ROTAÇÃO DOS EIXOS ======================================
        //DEFINIÇÃO DOS AFS
        //BB
        if (CLP.RD(PC_SL_MCPBB_ECS_AFCHEIO) == 1 || CLP.RD(PC_HL_MCPBB_RTU_AFCHEIO) == 1){
                AF_BB_CHEIO = true;
                shpAFBB_CHEIO->Brush->Color = clLime;
        }else{
                if (CLP.RD(PC_SL_MCPBB_ECS_AFCHEIO) == 0 && CLP.RD(PC_HL_MCPBB_RTU_AFCHEIO) == 0){
                        AF_BB_CHEIO = false;
                        shpAFBB_CHEIO->Brush->Color = clWhite;
                }
        }
        //BE
        if (CLP.RD(PC_SL_MCPBE_ECS_AFCHEIO) == 1 || CLP.RD(PC_HL_MCPBE_RTU_AFCHEIO) == 1){
                AF_BE_CHEIO = true;
                shpAFBE_CHEIO->Brush->Color = clLime;
        }else{
                if (CLP.RD(PC_SL_MCPBE_ECS_AFCHEIO) == 0 && CLP.RD(PC_HL_MCPBE_RTU_AFCHEIO) == 0){
                        AF_BE_CHEIO = false;
                        shpAFBE_CHEIO->Brush->Color = clWhite;
                }
        }
        //DEFINIÇÃO DAS ROTAÇÕES
        //*****************************MCP BB*****************************
        if (CLP.RD(PC_SA_MCPBB_ECS_MCPRPM) >= CLP.RD(PC_HA_MCPBB_RTU_MCPRPM)){
                rotacao_MCP_BB = CLP.RD(PC_SA_MCPBB_ECS_MCPRPM);
        }else{
                rotacao_MCP_BB = CLP.RD(PC_HA_MCPBB_RTU_MCPRPM);
        }
        lblMCPBB_RPM->Caption =  FormatFloat("0.##",rotacao_MCP_BB);
        referencia_mcpbb = (((rotacao_MCP_BB * (1.633/13.383)))) * (1 - (escorreg_bb/100) );
        if ( (referencia_mcpbb - ((float) (int) referencia_mcpbb)) > 0.5) {
                referencia_mcpbb = ceil(referencia_mcpbb - 0.5);
        }else{
                referencia_mcpbb = floor(referencia_mcpbb + 0.5);
        }
        //*****************************MCP BE*****************************
        if (CLP.RD(PC_SA_MCPBE_ECS_MCPRPM) >= CLP.RD(PC_HA_MCPBE_RTU_MCPRPM)){
                rotacao_MCP_BE = CLP.RD(PC_SA_MCPBE_ECS_MCPRPM);
        }else{
                rotacao_MCP_BE = CLP.RD(PC_HA_MCPBE_RTU_MCPRPM);
        }
        lblMCPBE_RPM->Caption =  FormatFloat("0.##",rotacao_MCP_BE);
        referencia_mcpbe = (((rotacao_MCP_BE * (1.633/13.383)))) * (1 - (escorreg_be/100) );
        //referencia_mcpbe = (float) (int) ceil(referencia_mcpbe);
        if ( (referencia_mcpbe - ((float) (int) referencia_mcpbe)) > 0.5) {
                referencia_mcpbe = ceil(referencia_mcpbe - 0.5);
        }else{
                referencia_mcpbe = floor(referencia_mcpbe + 0.5);
        }
        //*****************************  TG  *****************************
        if (CLP.RD(PC_HA_TBGAS_MCTG_NTP) >= CLP.RD(PC_SA_TBGAS_ATLAS_NTP)){
                rotacao_TG_NTP = CLP.RD(PC_HA_TBGAS_MCTG_NTP);
        }else{
                rotacao_TG_NTP = CLP.RD(PC_SA_TBGAS_ATLAS_NTP);
        }
        lblTGNTP_RPM->Caption =  FormatFloat("0.##",rotacao_TG_NTP);
        referencia_tg = (rotacao_TG_NTP /13.383);
        if ( (referencia_tg - ((float) (int) referencia_tg)) > 0.5) {
                referencia_tg = ceil(referencia_tg - 0.5);
        }else{
                referencia_tg = floor(referencia_tg + 0.5);
        }
        lblrefMCPBB->Caption =  FormatFloat("0.##",referencia_mcpbb);
        lblrefMCPBE->Caption =  FormatFloat("0.##",referencia_mcpbe);
        lblrefTG->Caption =  FormatFloat("0.##",referencia_tg);
        //DEFINIÇÃO DAS SSS
        //*****************************  TG  *****************************
        if ( habilita_sss == true ){
        //K1
                if ( rotacao_TG_NTP > 0 && SSS_TG_BB_TRANS == true && (referencia_tg > referencia_mcpbb || SSS_MCP_BB_ACPL == false)){
                        if ( SSS_TG_BB_ACPL == false ) {
                                CLP.WR( PC_HL_ERPBC_SSSK1_DACPL, 0 );
                                CLP.WR( PC_HL_ERPBC_SSSK1_ACPL , 1 );
                                SSS_TG_BB_ACPL = true;
                       }
                }else{
                        if  (SSS_TG_BB_ACPL == true && SSS_TG_BB_TRAV == false){
                                CLP.WR( PC_HL_ERPBC_SSSK1_ACPL , 0 );
                                CLP.WR( PC_HL_ERPBC_SSSK1_DACPL, 1 );
                                SSS_TG_BB_ACPL = false;
                        }
                }
        //K2
                if ( rotacao_TG_NTP > 0 && SSS_TG_BE_TRANS == true && (referencia_tg > referencia_mcpbe || SSS_MCP_BE_ACPL == false)){
                        if ( SSS_TG_BE_ACPL == false ) {
                                CLP.WR( PC_HL_ERPBC_SSSK2_DACPL, 0 );
                                CLP.WR( PC_HL_ERPBC_SSSK2_ACPL , 1 );
                                SSS_TG_BE_ACPL = true;
                        }
                }else{
                        if  (SSS_TG_BE_ACPL == true && SSS_TG_BE_TRAV == false){
                                CLP.WR( PC_HL_ERPBC_SSSK2_ACPL , 0 );
                                CLP.WR( PC_HL_ERPBC_SSSK2_DACPL, 1 );
                                SSS_TG_BE_ACPL = false;
                        }
                }
        //***************************** MCPS *****************************
        //K3
                if ( rotacao_MCP_BB > 0 &&  AF_BB_CHEIO == true && (referencia_tg < referencia_mcpbb || SSS_TG_BB_ACPL == false || SSS_TG_BB_TRANS == false)){
                        if  (SSS_MCP_BB_ACPL == false){
                                CLP.WR( PC_HL_ERSBB_SSSK3_DACPL, 0 );
                                CLP.WR( PC_HL_ERSBB_SSSK3_ACPL , 1 );
                                CLP.WR(PC_HL_ERSBB_SSSK3_NTRAVACPL, 0);
                                CLP.WR(PC_HL_ERSBB_SSSK3_TRAVACPL , 1);
                                SSS_MCP_BB_ACPL = true;
                                SSS_MCP_BB_TRAV = true;
                        }
                }else{
                        if  (SSS_MCP_BB_ACPL == true && SSS_MCP_BB_TRAV == false){
                                CLP.WR( PC_HL_ERSBB_SSSK3_ACPL , 0 );
                                CLP.WR( PC_HL_ERSBB_SSSK3_DACPL, 1 );
                                SSS_MCP_BB_ACPL = false;
                        }
                }
        //K4
                if ( rotacao_MCP_BE > 0 &&  AF_BE_CHEIO == true && (referencia_tg < referencia_mcpbe || SSS_TG_BE_ACPL == false || SSS_TG_BE_TRANS == false)){
                        if  (SSS_MCP_BE_ACPL == false){
                                CLP.WR( PC_HL_ERSBE_SSSK4_DACPL, 0 );
                                CLP.WR( PC_HL_ERSBE_SSSK4_ACPL , 1 );
                                CLP.WR(PC_HL_ERSBE_SSSK4_NTRAVACPL, 0);
                                CLP.WR(PC_HL_ERSBE_SSSK4_TRAVACPL , 1);
                                SSS_MCP_BE_ACPL = true;
                                SSS_MCP_BE_TRAV = true;
                        }
                }else{
                        if  (SSS_MCP_BE_ACPL == true  && SSS_MCP_BE_TRAV == false){
                                CLP.WR( PC_HL_ERSBE_SSSK4_ACPL , 0 );
                                CLP.WR( PC_HL_ERSBE_SSSK4_DACPL, 1 );
                                SSS_MCP_BE_ACPL = false;
                        }
                }
        }
        //DEFINIÇÃO DAS ROTAÇÕES
        //EIXO BB
        if ( SSS_TG_BB_ACPL == true && habilita_edicao == false  && SSS_TG_BB_TRANS == true){
                if (CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) != referencia_tg && referencia_tg > referencia_mcpbb ){
                        CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, referencia_tg);
                }else{
                        if(CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) != referencia_mcpbb && AF_BB_CHEIO == true && SSS_MCP_BB_ACPL == true){
                                CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, referencia_mcpbb);
                        }else{
                                if (CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) != referencia_tg && AF_BB_CHEIO == false && SSS_MCP_BB_ACPL == false){
                                        CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, referencia_tg);
                                }
                        }
                }
        }
        else{
                if (SSS_MCP_BB_ACPL == true && habilita_edicao == false ){
                        //if (CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) != (int) ((((rotacao_MCP_BB * (1.633/13.383)))) * (1 - (escorreg_bb/100) ))){
                        if (CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) != referencia_mcpbb ){
                                //CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, (int) ((((rotacao_MCP_BB * (1.633/13.383)))) * (1 - (escorreg_bb/100) )));
                                CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, referencia_mcpbb );
                        }
                }
                else{
                        if (habilita_edicao == false){
                                if (CLP.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM) != 0.0){
                                        CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, 0.0);
                                }
                        }
                }
        }
        //EIXO BE
        if ( SSS_TG_BE_ACPL == true && habilita_edicao == false && SSS_TG_BE_TRANS == true){
                if (CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) != referencia_tg  && referencia_tg > referencia_mcpbe ){
                        CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, referencia_tg);
                }else{
                        if(CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) != referencia_mcpbe && AF_BE_CHEIO == true && SSS_MCP_BE_ACPL == true){
                                CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, referencia_mcpbe);
                        }else{
                                if (CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) != referencia_tg  && AF_BE_CHEIO == false && SSS_MCP_BE_ACPL == false){
                                        CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, referencia_tg);
                                }
                        }
                }
        }
        else{
                if (SSS_MCP_BE_ACPL == true && habilita_edicao == false){
                        //if (CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) != (int) ((((rotacao_MCP_BE * (1.633/13.383)))) * (1 - (escorreg_be/100) ))){
                        if (CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) != referencia_mcpbe ){
                                //CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, (int) ((((rotacao_MCP_BE * (1.633/13.383)))) * (1 - (escorreg_be/100) )));
                                CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, referencia_mcpbe );
                        }
                }
                else{
                        if (habilita_edicao == false && habilita_edicao == false){
                                if (CLP.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM) != 0.0){
                                        CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, 0.0);
                                }
                        }
                }
        }
        //CALCULO TEMPERATURA ÓLEO
        if (referencia_tg > 0 &&  SSS_TG_BE_TRANS == true){
                ROT_MOD_PRI = true;
                if (SSS_TG_BB_ACPL == true){
                        ROT_MOD_SEC = true;
                }
        }else{
                if ((referencia_mcpbe > 0 || referencia_mcpbb > 0) && (SSS_MCP_BE_ACPL == true || SSS_MCP_BB_ACPL == true)){
                        ROT_MOD_SEC = true;
                        if ( CLP.RD(PC_HL_ERPBC_SSSK1_ACPL) == 1 || CLP.RD(PC_HL_ERPBC_SSSK2_ACPL) == 1){
                                ROT_MOD_PRI = true;
                        }else{
                                ROT_MOD_PRI = false;
                        }
                }else{
                        ROT_MOD_SEC = false;
                        ROT_MOD_PRI = false;
                }
        }

        if (ctrl_auto_temp_ol == true){
                if (ROT_MOD_SEC == true &&  ROT_MOD_PRI == true){
                        if (temp_ol_er < 57){
                                temp_ol_er = temp_ol_er + 1;
                        }else{
                                if (temp_ol_er > 57){
                                        temp_ol_er = temp_ol_er - 1;
                                }
                        }
                        //temp_ol_er = 57;
                }else {
                        if (ROT_MOD_PRI == true){
                                if (temp_ol_er < 46){
                                        temp_ol_er = temp_ol_er + 1;
                                }else{
                                        if (temp_ol_er > 46){
                                                temp_ol_er = temp_ol_er - 1;
                                        }
                                }
                                //temp_ol_er = 46;
                        }else{
                                if(ROT_MOD_SEC == true){
                                        if (temp_ol_er < 40){
                                                temp_ol_er = temp_ol_er + 1;
                                        }else{
                                                if (temp_ol_er > 40){
                                                        temp_ol_er = temp_ol_er - 1;
                                                }
                                        }
                                        //temp_ol_er = 40;
                                }else{
                                        if (temp_ol_er < 25){
                                                temp_ol_er = temp_ol_er + 1;
                                        }else{
                                                if (temp_ol_er > 25){
                                                        temp_ol_er = temp_ol_er - 1;
                                                }
                                        }
                                        //temp_ol_er = 25;
                                }
                        }
                }
                if (CLP.RD(PC_HA_ERHBC_MODHID_TEMPOL) != temp_ol_er && CLP.TamBufWR() < 5 ){
                        CLP.WR( PC_HA_ERHBC_MODHID_TEMPOL, temp_ol_er );
                }
        }


        //EXIBIÇÃO DO ESCORREGAMENTO
        lblEscorregBB->Caption = FormatFloat("0.##",escorreg_bb);
        lblEscorregBE->Caption = FormatFloat("0.##",escorreg_be);

        btnSSSK1_ACPL->Enabled  = !habilita_sss;
        btnSSSK1_DACPL->Enabled = !habilita_sss;
        btnSSSK2_ACPL->Enabled  = !habilita_sss;
        btnSSSK2_DACPL->Enabled = !habilita_sss;
        btnSSSK3_ACPL->Enabled  = !habilita_sss;
        btnSSSK3_DACPL->Enabled = !habilita_sss;
        btnSSSK4_ACPL->Enabled  = !habilita_sss;
        btnSSSK4_DACPL->Enabled = !habilita_sss;


        //INFORMAÇÕES FIXAS
        shpMOTELLIG_BBELPN2->Brush->Color = shpMOTELLIG_BBELPN->Brush->Color;
        shpRemoto_BBELPN2->Brush->Color = shpRemoto_BBELPN->Brush->Color;
        shpMODHID_OLPBX2->Brush->Color = shpMODHID_OLPBX->Brush->Color;
        shpSSSK3_OLPBX2->Brush->Color = shpSSSK3_OLPBX->Brush->Color;
        shpSSSK4_OLPBX2->Brush->Color = shpSSSK4_OLPBX->Brush->Color;
        lblEIXOBBRPM_MODSBB2->Caption = lblEIXOBBRPM_MODSBB->Caption;
        lblEIXOBERPM_MODSBE2->Caption = lblEIXOBERPM_MODSBE->Caption;
        shpSSSK1_ACPL2->Brush->Color = shpSSSK1_ACPL->Brush->Color;
        shpSSSK1_DACPL2->Brush->Color = shpSSSK1_DACPL->Brush->Color;
        shpSSSK1_TRAVABER2->Brush->Color = shpSSSK1_TRAVABER->Brush->Color;
        shpSSSK1_NTRAVABER2->Brush->Color = shpSSSK1_NTRAVABER->Brush->Color;
        shpSSSK1_TRAVACPL2->Brush->Color = shpSSSK1_TRAVACPL->Brush->Color;
        shpSSSK1_NTRAVACPL2->Brush->Color = shpSSSK1_NTRAVACPL->Brush->Color;
        shpSSSK2_ACPL2->Brush->Color = shpSSSK2_ACPL->Brush->Color;
        shpSSSK2_DACPL2->Brush->Color = shpSSSK2_DACPL->Brush->Color;
        shpSSSK2_TRAVABER2->Brush->Color = shpSSSK2_TRAVABER->Brush->Color;
        shpSSSK2_NTRAVABER2->Brush->Color = shpSSSK2_NTRAVABER->Brush->Color;
        shpSSSK2_TRAVACPL2->Brush->Color = shpSSSK2_TRAVACPL->Brush->Color;
        shpSSSK2_NTRAVACPL2->Brush->Color = shpSSSK2_NTRAVACPL->Brush->Color;
        shpSSSK3_ACPL2->Brush->Color = shpSSSK3_ACPL->Brush->Color;
        shpSSSK3_DACPL2->Brush->Color = shpSSSK3_DACPL->Brush->Color;
        shpSSSK3_TRAVACPL2->Brush->Color = shpSSSK3_TRAVACPL->Brush->Color;
        shpSSSK3_NTRAVACPL2->Brush->Color = shpSSSK3_NTRAVACPL->Brush->Color;
        shpSSSK4_ACPL2->Brush->Color = shpSSSK4_ACPL->Brush->Color;
        shpSSSK4_DACPL2->Brush->Color = shpSSSK4_DACPL->Brush->Color;
        shpSSSK4_TRAVACPL2->Brush->Color = shpSSSK4_TRAVACPL->Brush->Color;
        shpSSSK4_NTRAVACPL2->Brush->Color = shpSSSK4_NTRAVACPL->Brush->Color;


}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAUTOHDWSCMDES_BBELPNClick(TObject *Sender)
{
	if (btnAUTOHDWSCMDES_BBELPN->Caption == "Ñ AUTOHDWSCMDES"){
		CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEmAut_BBELPNClick(TObject *Sender)
{
	if (btnEmAut_BBELPN->Caption == "Em Manual"){
		CLP.WR( PC_HL_ERHBC_BBELPN_EMAUT, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_EMAUT, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnRemoto_BBELPNClick(TObject *Sender)
{
        if (btnRemoto_BBELPN->Caption == "Local"){
		CLP.WR( PC_HL_ERHBC_BBELPN_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAUTOHDWSCMLIG_BBELPNClick(
      TObject *Sender)
{
	if (btnAUTOHDWSCMLIG_BBELPN->Caption == "Ñ AUTOHDWSCMLIG"){
		CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPRDEMERGSCMLI_BBELPNClick(
      TObject *Sender)
{
	if (btnPRDEMERGSCMLI_BBELPN->Caption == "Ñ PRDEMERGSCMLI"){
		CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPRDEMERGSCMDE_BBELPNClick(
      TObject *Sender)
{
	if (btnPRDEMERGSCMDE_BBELPN->Caption == "Ñ PRDEMERGSCMDE"){
		CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSobrec_BBELPNClick(TObject *Sender)
{
	if (btnSobrec_BBELPN->Caption == "Sem Sobrec."){
		CLP.WR( PC_HL_ERHBC_BBELPN_SOBREC, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_SOBREC, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMOTELLIG_BBELPNClick(TObject *Sender)
{
        if (btnMOTELLIG_BBELPN->Caption == "Mot. El. Parado"){
		CLP.WR( PC_HL_ERHBC_BBELPN_MOTELLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_MOTELLIG, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMOTPNLIG_BBELPNClick(TObject *Sender)
{
        if (btnMOTPNLIG_BBELPN->Caption == "Mot. Pn. Parado"){
		CLP.WR( PC_HL_ERHBC_BBELPN_MOTPNLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_BBELPN_MOTPNLIG, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPartir_ERHBC_BBELPNTimer(TObject *Sender)
{
        CLP.WR( PC_HL_ERHBC_BBELPN_MOTELLIG, 1 );
        CLP.WR( PC_HL_ERHBC_BBELPN_MOTPNLIG, 0 );
        tmrPartir_ERHBC_BBELPN->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrParar_ERHBC_BBELPNTimer(TObject *Sender)
{
        CLP.WR( PC_HL_ERHBC_BBELPN_MOTELLIG, 0 );
        CLP.WR( PC_HL_ERHBC_BBELPN_MOTPNLIG, 0 );
        tmrParar_ERHBC_BBELPN->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMODHID_OLPBXClick(TObject *Sender)
{
        if (btnMODHID_OLPBX->Caption == "Press. OK"){
		CLP.WR( PC_HL_ERHBC_MODHID_OLPBX, 0 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_MODHID_OLPBX, 1 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMODHID_OLPDIFALClick(TObject *Sender)
{
        if (btnMODHID_OLPDIFAL->Caption == "Press. Dif. OK"){
		CLP.WR( PC_HL_ERHBC_MODHID_OLPDIFAL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERHBC_MODHID_OLPDIFAL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMODHID_TEMPOLClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERHBC_MODHID_TEMPOL, txtMODHID_TEMPOL->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMODHID_OLPRESSClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERHBC_MODHID_OLPRESS, txtMODHID_OLPRESS->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnERPBC_CATRACClick(TObject *Sender)
{
        if (btnERPBC_CATRAC->Caption == "Engatado"){
		CLP.WR( PC_HL_ERPBC_CATRAC_DESENGATADO, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_CATRAC_DESENGATADO, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnERPBC_FREIOClick(TObject *Sender)
{
        if (btnERPBC_FREIO->Caption == "Engatado"){
		CLP.WR( PC_HL_ERPBC_FREIO_DESENGATADO, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_FREIO_DESENGATADO, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuMancaisClick(TObject *Sender)
{
        frmMancal->Top = frmPrincipal->Top + 5;
        frmMancal->Left = frmPrincipal->Left + 5;
        frmMancal->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEIXOBBRPM_MODSBBClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, txtEIXOBBRPM_MODSBB->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEIXOBERPM_MODSBEClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, txtEIXOBERPM_MODSBE->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_ACPLClick(TObject *Sender)
{
        if (btnSSSK1_ACPL->Caption == "Não Acoplada"){
		CLP.WR( PC_HL_ERPBC_SSSK1_ACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK1_ACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_DACPLClick(TObject *Sender)
{
        if (btnSSSK1_DACPL->Caption == "Não Desacoplada"){
		CLP.WR( PC_HL_ERPBC_SSSK1_DACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK1_DACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_TRAVABERClick(TObject *Sender)
{
        if (btnSSSK1_TRAVABER->Caption == "Travada Aberta Ñ OK"){
		CLP.WR( PC_HL_ERPBC_SSSK1_TRAVABER, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK1_TRAVABER, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_NTRAVABERClick(TObject *Sender)
{
        if (btnSSSK1_NTRAVABER->Caption == "Não Trav. Aberta Ñ OK"){
		CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVABER, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVABER, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_TRAVACPLClick(TObject *Sender)
{
        if (btnSSSK1_TRAVACPL->Caption == "Não Travada"){
		CLP.WR( PC_HL_ERPBC_SSSK1_TRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK1_TRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_NTRAVACPLClick(TObject *Sender)
{
        if (btnSSSK1_NTRAVACPL->Caption == "Não Destravada"){
		CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_ACPLClick(TObject *Sender)
{
        if (btnSSSK2_ACPL->Caption == "Não Acoplada"){
		CLP.WR( PC_HL_ERPBC_SSSK2_ACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK2_ACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_DACPLClick(TObject *Sender)
{
        if (btnSSSK2_DACPL->Caption == "Não Desacoplada"){
		CLP.WR( PC_HL_ERPBC_SSSK2_DACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK2_DACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_TRAVABERClick(TObject *Sender)
{
        if (btnSSSK2_TRAVABER->Caption == "Travada Aberta Ñ OK"){
		CLP.WR( PC_HL_ERPBC_SSSK2_TRAVABER, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK2_TRAVABER, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_NTRAVABERClick(TObject *Sender)
{
        if (btnSSSK2_NTRAVABER->Caption == "Não Trav. Aberta Ñ OK"){
		CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVABER, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVABER, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_TRAVACPLClick(TObject *Sender)
{
        if (btnSSSK2_TRAVACPL->Caption == "Não Travada"){
		CLP.WR( PC_HL_ERPBC_SSSK2_TRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK2_TRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_NTRAVACPLClick(TObject *Sender)
{
        if (btnSSSK2_NTRAVACPL->Caption == "Não Destravada"){
		CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK3_ACPLClick(TObject *Sender)
{
        if (btnSSSK3_ACPL->Caption == "Não Acoplada"){
		CLP.WR( PC_HL_ERSBB_SSSK3_ACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBB_SSSK3_ACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK3_DACPLClick(TObject *Sender)
{
        if (btnSSSK3_DACPL->Caption == "Não Desacoplada"){
		CLP.WR( PC_HL_ERSBB_SSSK3_DACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBB_SSSK3_DACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK3_TRAVACPLClick(TObject *Sender)
{
        if (btnSSSK3_TRAVACPL->Caption == "Não Travada"){
		CLP.WR( PC_HL_ERSBB_SSSK3_TRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBB_SSSK3_TRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK3_NTRAVACPLClick(TObject *Sender)
{
        if (btnSSSK3_NTRAVACPL->Caption == "Não Destravada"){
		CLP.WR( PC_HL_ERSBB_SSSK3_NTRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBB_SSSK3_NTRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK3_OLPBXClick(TObject *Sender)
{
        if (btnSSSK3_OLPBX->Caption == "Press. OK"){
		CLP.WR( PC_HL_ERSBB_SSSK3_OLPBX, 0 );
	}
	else{
		CLP.WR( PC_HL_ERSBB_SSSK3_OLPBX, 1 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK4_ACPLClick(TObject *Sender)
{
        if (btnSSSK4_ACPL->Caption == "Não Acoplada"){
		CLP.WR( PC_HL_ERSBE_SSSK4_ACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBE_SSSK4_ACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK4_DACPLClick(TObject *Sender)
{
        if (btnSSSK4_DACPL->Caption == "Não Desacoplada"){
		CLP.WR( PC_HL_ERSBE_SSSK4_DACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBE_SSSK4_DACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK4_TRAVACPLClick(TObject *Sender)
{
        if (btnSSSK4_TRAVACPL->Caption == "Não Travada"){
		CLP.WR( PC_HL_ERSBE_SSSK4_TRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBE_SSSK4_TRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK4_NTRAVACPLClick(TObject *Sender)
{
        if (btnSSSK4_NTRAVACPL->Caption == "Não Destravada"){
		CLP.WR( PC_HL_ERSBE_SSSK4_NTRAVACPL, 1 );
	}
	else{
		CLP.WR( PC_HL_ERSBE_SSSK4_NTRAVACPL, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK4_OLPBXClick(TObject *Sender)
{
        if (btnSSSK4_OLPBX->Caption == "Press. OK"){
		CLP.WR( PC_HL_ERSBE_SSSK4_OLPBX, 0 );
	}
	else{
		CLP.WR( PC_HL_ERSBE_SSSK4_OLPBX, 1 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPressurizarTimer(TObject *Sender)
{
        pressao = CLP.RD(PC_HA_ERHBC_MODHID_OLPRESS);
        if ( btnMOTELLIG_BBELPN->Caption == "Mot. El. Ligado" || btnMOTPNLIG_BBELPN->Caption == "Mot. Pn. Ligado" ){
                if ( pressao < 3.0 ) {
                        pressao = pressao + 0.5;
                        CLP.WR( PC_HA_ERHBC_MODHID_OLPRESS, pressao );
                }
        };


}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrDespressurizarTimer(TObject *Sender)
{
        pressao = CLP.RD(PC_HA_ERHBC_MODHID_OLPRESS);
        if ( btnMOTELLIG_BBELPN->Caption == "Mot. El. Parado" && btnMOTPNLIG_BBELPN->Caption == "Mot. Pn. Parado" ){
                if ( pressao > 0.0 ) {
                        pressao = pressao - 0.5;
                        if (pressao < 0.0){
                                pressao = 0.0;
                        };
                        CLP.WR(PC_HA_ERHBC_MODHID_OLPRESS, pressao );
                };
        }


}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPartirClick(TObject *Sender)
{
        tmrParar_ERHBC_BBELPN->Enabled = false;
        tmrDespressurizar->Enabled = false;
        tmrPartir_ERHBC_BBELPN->Enabled = true;
        tmrPressurizar->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPararClick(TObject *Sender)
{
        tmrPartir_ERHBC_BBELPN->Enabled = false;
        tmrPressurizar->Enabled = false;
        tmrParar_ERHBC_BBELPN->Enabled = true;
        tmrDespressurizar->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnHabilita_EdicaoClick(TObject *Sender)
{
        if (btnHabilita_Edicao->Caption == "Desabilitado"){
                habilita_edicao = true;
                btnHabilita_Edicao->Caption = "Habilitado";
        }else{
                habilita_edicao = false;
                btnHabilita_Edicao->Caption = "Desabilitado";
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEscorregClick(TObject *Sender)
{
        escorreg_bb = txtEscorregBB->Text.ToDouble();
        escorreg_be = txtEscorregBE->Text.ToDouble();
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
        if ( tmrStarting->Enabled == false){
                btnReset->Enabled = false;
                tmrStarting->Enabled = true;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInibirCmdClick(TObject *Sender)
{
        if ( nao_atender_cmd == false ){
                cmdInibirCmd->Caption = "Inibir Cmd Lig.";
                nao_atender_cmd = true;
        }
        else{
                cmdInibirCmd->Caption = "Inibir Cmd Deslig.";
                nao_atender_cmd = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInibirPressClick(TObject *Sender)
{
        if ( nao_pressurizar == false ){
                cmdInibirPress->Caption = "Inibir Press. Lig.";
                nao_pressurizar = true;
        }
        else{
                cmdInibirPress->Caption = "Inibir Press. Deslig.";
                nao_pressurizar = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_TRAVARClick(TObject *Sender)
{
        if (btnSSSK1_TRAVAR->Caption == "TRAVAR"){
                CLP.WR(PC_HL_ERPBC_SSSK1_NTRAVACPL, 0);
                CLP.WR(PC_HL_ERPBC_SSSK1_TRAVACPL , 1);
        }else{
                CLP.WR(PC_HL_ERPBC_SSSK1_TRAVACPL , 0);
                CLP.WR(PC_HL_ERPBC_SSSK1_NTRAVACPL, 1);
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_TRAVARClick(TObject *Sender)
{
        if (btnSSSK2_TRAVAR->Caption == "TRAVAR"){
                CLP.WR(PC_HL_ERPBC_SSSK2_NTRAVACPL, 0);
                CLP.WR(PC_HL_ERPBC_SSSK2_TRAVACPL , 1);
        }else{
                CLP.WR(PC_HL_ERPBC_SSSK2_TRAVACPL , 0);
                CLP.WR(PC_HL_ERPBC_SSSK2_NTRAVACPL, 1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK3_TRAVARClick(TObject *Sender)
{
        if (btnSSSK3_TRAVAR->Caption == "TRAVAR"){
                CLP.WR(PC_HL_ERSBB_SSSK3_NTRAVACPL, 0);
                CLP.WR(PC_HL_ERSBB_SSSK3_TRAVACPL , 1);
        }else{
                CLP.WR(PC_HL_ERSBB_SSSK3_TRAVACPL , 0);
                CLP.WR(PC_HL_ERSBB_SSSK3_NTRAVACPL, 1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK4_TRAVARClick(TObject *Sender)
{
        if (btnSSSK4_TRAVAR->Caption == "TRAVAR"){
                CLP.WR(PC_HL_ERSBE_SSSK4_NTRAVACPL, 0);
                CLP.WR(PC_HL_ERSBE_SSSK4_TRAVACPL , 1);
        }else{
                CLP.WR(PC_HL_ERSBE_SSSK4_TRAVACPL , 0);
                CLP.WR(PC_HL_ERSBE_SSSK4_NTRAVACPL, 1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK1_FERRAMENTAClick(TObject *Sender)
{
        if (btnSSSK1_FERRAMENTA->Caption == "FECHAR"){
	        CLP.WR( PC_HL_ERPBC_SSSK1_TRAVABER      , 0 );
                CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVABER     , 1 );
        }else{
                CLP.WR( PC_HL_ERPBC_SSSK1_NTRAVABER     , 0 );
                CLP.WR( PC_HL_ERPBC_SSSK1_TRAVABER      , 1 );
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSK2_FERRAMENTAClick(TObject *Sender)
{
        if (btnSSSK2_FERRAMENTA->Caption == "FECHAR"){
	        CLP.WR( PC_HL_ERPBC_SSSK2_TRAVABER      , 0 );
                CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVABER     , 1 );
        }else{
                CLP.WR( PC_HL_ERPBC_SSSK2_NTRAVABER     , 0 );
                CLP.WR( PC_HL_ERPBC_SSSK2_TRAVABER      , 1 );
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnHabilita_SSSClick(TObject *Sender)
{
        if(btnHabilita_SSS->Caption == "Desabilitado"){
                habilita_sss = false;
                btnHabilita_SSS->Caption = "Habilitado";
        }else{
                habilita_sss = true;
                btnHabilita_SSS->Caption = "Desabilitado";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCtrlAutoTempClick(TObject *Sender)
{
        if (ctrl_auto_temp_ol == true){
                ctrl_auto_temp_ol = false;
                btnMODHID_TEMPOL->Enabled = true;
                btnCtrlAutoTemp->Font->Color = clRed;
                btnCtrlAutoTemp->Hint = "Controle Automático da Temperatura do Óleo Lub. Inativa";
        }else{
                ctrl_auto_temp_ol = true;
                btnMODHID_TEMPOL->Enabled = false;
                btnCtrlAutoTemp->Font->Color = clLime;
                btnCtrlAutoTemp->Hint = "Controle Automático da Temperatura do Óleo Lub. Ativa";
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnHabilita_PressClick(TObject *Sender)
{
        if(btnHabilita_Press->Caption == "Desabilitado"){
                ctrl_auto_presost = true;
                btnHabilita_Press->Caption = "Habilitado";
        }else{
                ctrl_auto_presost = false;
                btnHabilita_Press->Caption = "Desabilitado";
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuStatusClick(TObject *Sender)
{
        pnlStatus->Visible = true;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuBBELPNClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = true;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuERClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuSSSMCPClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = true;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuSSSTGClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = true;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnStatusClick(TObject *Sender)
{
        pnlStatus->Visible = true;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnBBELPNClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = true;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnERClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSMCPClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = false;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = true;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSSSTGClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlSSSTG->Visible = true;
        pnlBBELPN->Visible = false;
        pnlSSSMCP->Visible = false;
        pnlER->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMancaisClick(TObject *Sender)
{
        frmMancal->Top = frmPrincipal->Top + 20;
        frmMancal->Left = frmPrincipal->Left + 70;
        frmMancal->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFecharClick(TObject *Sender)
{
        frmPrincipal->Close();        
}
//---------------------------------------------------------------------------


