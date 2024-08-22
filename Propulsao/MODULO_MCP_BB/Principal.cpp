//---------------------------------------------------------------------------
//***************************************************************************
//MAURICIO ANDRADE LEMME - ASSISTENTE DE ENGENHARIA
//IPqM - INSTITUTO DE PESQUISAS DA MARINHA
//GSD - GRUPO DE SISTEMAS DIGITAIS
//FUNDEP - FUNDAÇÃO DE DESENVOLVIMENTO DA PESQUISA

//EMULADOR DE SINAIS DE COMUNICAÇÃO DOS MCPS
//NAVIO MODELO.....: V-32 JULIO DE NORONHA (INHAUMA)
//USUÁRIO FINAL....: EQUIPE CLP
//VERSÃO INICIAL...: V001b
//MÓDULO...........: MCP BB
//DATA DE INÍCIO...: 29.09.2015
//DATA DE PROTÓTIPO: 28.08.2016
//DATA DE TÉRMINO..: 15.08.2017
//DATA DE ATUALIZ..: 29.11.2017
//                   26.01.2018
//		     30.06.2023
//		     05.07.2023
//DESIGNAÇÃO.......: ESTE MÓDULO DO SOFTWARE TEM COMO OBJETIVO A OPERAÇÃO DO MCP BB
//EM COPARCERIA DESTE MÓDULO ESTA O MÓDULO DE COMUNICAÇÃO MODBUS DE AUTORIA DO
//FUNCIONÁRIO FÁBIO TEIXEIRA, SUA IMPLEMENTAÇÃO É DESCONHECIDA
//***************************************************************************
#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
#include "Analogicas.h"
#include "Controles.h"
#include "ControleNovo.h"
#include "BBAELPN.h"
#include "ModBusDriverLib\TModBusTCPDriver.cpp"

//----------------- ENDEREÇOS DOS EQUIPAMENTOS -----------------
//--------------------------- ECS ---------------------------
String PC_SL_ECS_AFENCHESVPRESSEN         = "%MW7500.14";
String PC_SL_ECS_QQALARMEREC              = "%MW7500.15";
String PC_SL_ECS_MECEMSERV                = "%MW7501.0";
String PC_SL_ECS_STDBYMECEMSERV           = "%MW7501.1";
String PC_SL_ECS_EXBLOPCARTATIVO          = "%MW7501.2";
String PC_SL_ECS_EXBLOCAFENATIVO          = "%MW7501.3";
String PC_SL_ECS_BUZLIGADA                = "%MW7501.4";
String PC_SL_ECS_QQALARME                 = "%MW7501.5";
String PC_SL_ECS_MCPOKOPERAR              = "%MW7501.6";
String PC_SL_ECS_EMLOCAL                  = "%MW7501.7";
String PC_SL_ECS_EMREMOTO                 = "%MW7501.8";
String PC_SL_ECS_PRIMPUMPMCFUNC           = "%MW7501.9";
String PC_SL_ECS_OLPRESSPARTMCPOK         = "%MW7501.10";
String PC_SL_ECS_MCPVIRANDO               = "%MW7501.12";
String PC_SL_ECS_PARTINDO                 = "%MW7501.13";
String PC_SL_ECS_PARANDO                  = "%MW7501.14";
String PC_SL_ECS_PARADO                   = "%MW7501.15";
String PC_SL_ECS_MCPPRDEMERG1NET          = "%MW7502.0";
String PC_SL_ECS_ENFORNPRTVALLIG          = "%MW7502.1";
String PC_SL_ECS_FLAPAABERTO              = "%MW7502.2";
String PC_SL_ECS_FLAPBABERTO              = "%MW7502.3";
String PC_SL_ECS_FLAPAFECHANDO            = "%MW7502.4";
String PC_SL_ECS_FLAPBFECHANDO            = "%MW7502.5";
String PC_SL_ECS_AFCHEIO                  = "%MW7502.6";
String PC_SL_ECS_AFVAZIO                  = "%MW7502.7";
String PC_SL_ECS_OVERRIDELIG              = "%MW7502.8";
String PC_SL_ECS_AFENCHENDO               = "%MW7502.9";
String PC_SL_ECS_AFESVAZIANDO             = "%MW7502.10";
String PC_SL_ECS_SEQPTDABORT              = "%MW7502.11";
String PC_SL_ECS_MCPPRTINTERLOCOK         = "%MW7502.12";
String PC_SL_ECS_AFENCHINTERLOCOK         = "%MW7502.13";
String PC_SL_ECS_MCPPRTDOK                = "%MW7502.14";
String PC_SL_ECS_AFENCHEROK               = "%MW7502.15";
String PC_SL_ECS_AFESVINTERLOCOK          = "%MW7503.0";
String PC_SL_ECS_PREAQUCOCDEC             = "%MW7505.13";
String PC_SL_ECS_OLBBAREMLOC              = "%MW7505.14";
String PC_SL_ECS_OLBBAAUTOMAN             = "%MW7505.15";
String PC_SL_ECS_OLBBASOBREC              = "%MW7506.0";
String PC_SL_ECS_REMCTRLHDW               = "%MW7524.7";
String PC_SL_ECS_REMCTRLAUTO              = "%MW7524.8";
String PC_SL_ECS_MCPEXECMAGELIS           = "%MW7524.14";
String PC_SL_ECS_MCPPRDNDOEMERG           = "%MW7525.14";
String PC_SL_ECS_PREAQAUTOMODO            = "%MW7525.15";
String PC_SL_ECS_PREAQMANUALMODO          = "%MW7526.0";
String PC_SL_ECS_VELCTRLVEL               = "%MW7526.6";
String PC_SL_ECS_VELPRTDALIMITE           = "%MW7526.7";
String PC_SL_ECS_VELMAXLIMITE             = "%MW7526.8";
String PC_SL_ECS_VELCOMBLIMITE            = "%MW7526.9";
String PC_SL_ECS_VELTORQUELIMITE          = "%MW7526.10";
String PC_SL_ECS_VELHABVELREF             = "%MW7526.11";
String PC_SL_ECS_VELDINAJSEMCARGA         = "%MW7526.12";
String PC_SL_ECS_UACPSFPRONTO             = "%MW7527.10";
String PC_SL_ECS_UACPSIPRONTO             = "%MW7527.11";
String PC_SL_ECS_UACREDUNCOK              = "%MW7527.12";
String PC_SL_ECS_MCPRPMALINHADA           = "%MW7529.0";
String PC_SL_ECS_PSWAFENCHENDO            = "%MW7529.1";
String PC_SL_ECS_PSWAFESVAZIANDO          = "%MW7529.2";
String PC_SL_ECS_POLANTFIFLSEN            = "%MW7532.0";
String PC_SL_ECS_POLANTFIBXSEN            = "%MW7532.1";
String PC_SL_ECS_POLANTFIMBXSEN           = "%MW7532.2";
String PC_SL_ECS_POLDEPFIFLSEN            = "%MW7532.3";
String PC_SL_ECS_POLDEPFIBXSEN            = "%MW7532.4";
String PC_SL_ECS_POLDEPFIMBXSEN           = "%MW7532.5";
String PC_SL_ECS_OLRESFPBX                = "%MW7532.6";
String PC_SL_ECS_OLRESFPMBX               = "%MW7532.7";
String PC_SL_ECS_OLRESFPFLSEN             = "%MW7532.8";
String PC_SL_ECS_PENTFIODFLSEN            = "%MW7532.9";
String PC_SL_ECS_PODAPOFIFLSEN            = "%MW7532.12";
String PC_SL_ECS_PODAPOFIBX               = "%MW7532.13";
String PC_SL_ECS_ODAPOFIPBX               = "%MW7532.14";
String PC_SL_ECS_PADBX                    = "%MW7532.15";
String PC_SL_ECS_PADMBX                   = "%MW7533.0";
String PC_SL_ECS_PADFLSEN                 = "%MW7533.1";
String PC_SL_ECS_ASPBX                    = "%MW7533.2";
String PC_SL_ECS_ASPMBX                   = "%MW7533.3";
String PC_SL_ECS_PASFLSEN                 = "%MW7533.4";
String PC_SL_ECS_ARPTDPBX                 = "%MW7533.5";
String PC_SL_ECS_ARPTDPMBX                = "%MW7533.6";
String PC_SL_ECS_ARPTDPBXFLPTD            = "%MW7533.7";
String PC_SL_ECS_PARCARGAMALBA            = "%MW7533.8";
String PC_SL_ECS_PARCARGAALBA             = "%MW7533.9";
String PC_SL_ECS_PARCARGAFLSENBA          = "%MW7533.10";
String PC_SL_ECS_PARCARGAMALBB            = "%MW7533.11";
String PC_SL_ECS_PARCARGAALBB             = "%MW7533.12";
String PC_SL_ECS_PARCARGAFLSENBB          = "%MW7533.13";
String PC_SL_ECS_PNVOLAFFLSEN1            = "%MW7533.14";
String PC_SL_ECS_PNVOLAFFLSEN2            = "%MW7533.15";
String PC_SL_ECS_PLCCRTLFL                = "%MW7534.0";
String PC_SL_ECS_POLAFBX                  = "%MW7534.2";
String PC_SL_ECS_POLAFMBX                 = "%MW7534.3";
String PC_SL_ECS_POLAFFLSEN               = "%MW7534.4";
String PC_SL_ECS_TOLFLSEN1                = "%MW7534.5";
String PC_SL_ECS_TOLFLSEN2                = "%MW7534.6";
String PC_SL_ECS_OLTAL                    = "%MW7534.7";
String PC_SL_ECS_OLTMAL                   = "%MW7534.8";
String PC_SL_ECS_TADFLSEN1                = "%MW7534.9";
String PC_SL_ECS_TADFLSEN2                = "%MW7534.10";
String PC_SL_ECS_TADAL                    = "%MW7534.11";
String PC_SL_ECS_TADMAL                   = "%MW7534.12";
String PC_SL_ECS_DESCA1TAL                = "%MW7534.13";
String PC_SL_ECS_DESCA1TMAL               = "%MW7534.14";
String PC_SL_ECS_TDESCA1FLSEN             = "%MW7534.15";
String PC_SL_ECS_DESCA2TAL                = "%MW7535.0";
String PC_SL_ECS_DESCA2TMAL               = "%MW7535.1";
String PC_SL_ECS_TDESCA2FLSEN             = "%MW7535.2";
String PC_SL_ECS_DESCA3TAL                = "%MW7535.3";
String PC_SL_ECS_DESCA3TMAL               = "%MW7535.4";
String PC_SL_ECS_TDESCA3FLSEN             = "%MW7535.5";
String PC_SL_ECS_DESCA4TAL                = "%MW7535.6";
String PC_SL_ECS_DESCA4TMAL               = "%MW7535.7";
String PC_SL_ECS_TDESCA4FLSEN             = "%MW7535.8";
String PC_SL_ECS_DESCA5TAL                = "%MW7535.9";
String PC_SL_ECS_DESCA5TMAL               = "%MW7535.10";
String PC_SL_ECS_TDESCA5FLSEN             = "%MW7535.11";
String PC_SL_ECS_DESCA6TAL                = "%MW7535.12";
String PC_SL_ECS_DESCA6TMAL               = "%MW7535.13";
String PC_SL_ECS_TDESCA6FLSEN             = "%MW7535.14";
String PC_SL_ECS_DESCA7TAL                = "%MW7535.15";
String PC_SL_ECS_DESCA7TMAL               = "%MW7536.0";
String PC_SL_ECS_TDESCA7FLSEN             = "%MW7536.1";
String PC_SL_ECS_DESCA8TAL                = "%MW7536.2";
String PC_SL_ECS_DESCA8TMAL               = "%MW7536.3";
String PC_SL_ECS_TDESCA8FLSEN             = "%MW7536.4";
String PC_SL_ECS_DESCB1TAL                = "%MW7536.5";
String PC_SL_ECS_DESCB1TMAL               = "%MW7536.6";
String PC_SL_ECS_TDESCB1FLSEN             = "%MW7536.7";
String PC_SL_ECS_DESCB2TAL                = "%MW7536.8";
String PC_SL_ECS_DESCB2MTAL               = "%MW7536.9";
String PC_SL_ECS_TDESCB2FLSEN             = "%MW7536.10";
String PC_SL_ECS_DESCB3AL                 = "%MW7536.11";
String PC_SL_ECS_DESCB3MAL                = "%MW7536.12";
String PC_SL_ECS_TDESCB3FLSEN             = "%MW7536.13";
String PC_SL_ECS_DESCB4TAL                = "%MW7536.14";
String PC_SL_ECS_DESCB4TMAL               = "%MW7536.15";
String PC_SL_ECS_TDESCB4FLSEN             = "%MW7537.0";
String PC_SL_ECS_DESCB5TAL                = "%MW7537.1";
String PC_SL_ECS_DESCB5TMAL               = "%MW7537.2";
String PC_SL_ECS_TDESCB5FLSEN             = "%MW7537.3";
String PC_SL_ECS_DESCB6TAL                = "%MW7537.4";
String PC_SL_ECS_DESCB6TMAL               = "%MW7537.5";
String PC_SL_ECS_TDESCB6FLSEN             = "%MW7537.6";
String PC_SL_ECS_DESCB7TAL                = "%MW7537.7";
String PC_SL_ECS_DESCB7TMAL               = "%MW7537.8";
String PC_SL_ECS_TDESCB7FLSEN             = "%MW7537.9";
String PC_SL_ECS_DESCB8TAL                = "%MW7537.10";
String PC_SL_ECS_DESCB8TMAL               = "%MW7537.11";
String PC_SL_ECS_TDESCB8FLSEN             = "%MW7537.12";
String PC_SL_ECS_DESCT1TAL                = "%MW7537.13";
String PC_SL_ECS_DESCT1TMAL               = "%MW7537.14";
String PC_SL_ECS_DESCT1SENSFL             = "%MW7537.15";
String PC_SL_ECS_DESCT2TAL                = "%MW7538.0";
String PC_SL_ECS_DESCT2TMAL               = "%MW7538.1";
String PC_SL_ECS_DESCT2SENSFL             = "%MW7538.2";
String PC_SL_ECS_DESCANTSLSENFL           = "%MW7538.6";
String PC_SL_ECS_DESCANTSLTAL             = "%MW7538.7";
String PC_SL_ECS_DESCANTSLTMAL            = "%MW7538.8";
String PC_SL_ECS_DESCTMEDALBA             = "%MW7538.9";
String PC_SL_ECS_DESCTMEDMALBA            = "%MW7538.10";
String PC_SL_ECS_DESCTMEDALBB             = "%MW7538.11";
String PC_SL_ECS_DESCTMEDMALBB            = "%MW7538.12";
String PC_SL_ECS_DESCTMEDGAL              = "%MW7538.13";
String PC_SL_ECS_DESCTMEDGMAL             = "%MW7538.14";
String PC_SL_ECS_TOLAFFLSEN1              = "%MW7538.15";
String PC_SL_ECS_TOLAFFLSEN2              = "%MW7539.0";
String PC_SL_ECS_TOLAFAL                  = "%MW7539.1";
String PC_SL_ECS_TOLAFMAL                 = "%MW7539.2";
String PC_SL_ECS_CREMAL1FLSEN             = "%MW7539.3";
String PC_SL_ECS_CREMAL3FLSEN             = "%MW7539.4";
String PC_SL_ECS_RPMMCPFLSENJ1            = "%MW7539.5";
String PC_SL_ECS_RPMMCPFLSENJ3            = "%MW7539.6";
String PC_SL_ECS_TARCARGAFLSENLA          = "%MW7539.7";
String PC_SL_ECS_TARCARGAFLSENLB          = "%MW7539.8";
String PC_SL_ECS_TARCARGAAL               = "%MW7539.9";
String PC_SL_ECS_TARCARGAMAL              = "%MW7539.10";
String PC_SL_ECS_QQALATIVO                = "%MW7539.11";
String PC_SL_ECS_MECPRINCFALHA            = "%MW7539.12";
String PC_SL_ECS_MECSTDBYCFALHA           = "%MW7539.13";
String PC_SL_ECS_QQSENFALHA               = "%MW7539.14";
String PC_SL_ECS_PRDEMERG1REDE            = "%MW7539.15";
String PC_SL_ECS_PRDEMERG2CIRC            = "%MW7540.0";
String PC_SL_ECS_PRDEMERG3CIRC            = "%MW7540.1";
String PC_SL_ECS_PRDEMERG4CIRC            = "%MW7540.2";
String PC_SL_ECS_PRDEMERG2FIOFL           = "%MW7540.3";
String PC_SL_ECS_PRDEMERG3FIOFL           = "%MW7540.4";
String PC_SL_ECS_PRDEMERG4FIOFL           = "%MW7540.5";
String PC_SL_ECS_MCPPRDEMERGPNL           = "%MW7540.6";
String PC_SL_ECS_FLAPSAFECHADOS           = "%MW7540.7";
String PC_SL_ECS_FLAPSBFECHADOS           = "%MW7540.8";
String PC_SL_ECS_PRIMESOBREC              = "%MW7540.9";
String PC_SL_ECS_PRIMEFLINICIAR           = "%MW7540.10";
String PC_SL_ECS_PRIMEFLPARAR             = "%MW7540.11";
String PC_SL_ECS_PRIMEALGERAL             = "%MW7540.12";
String PC_SL_ECS_PRDAUT                   = "%MW7540.13";
String PC_SL_ECS_POLPRDAUTSEN             = "%MW7540.14";
String PC_SL_ECS_POLPRDAUTALDED           = "%MW7540.15";
String PC_SL_ECS_POLPRDAUTRESFAL          = "%MW7541.0";
String PC_SL_ECS_PRDAUTADTEMP             = "%MW7541.1";
String PC_SL_ECS_PRDAUTOLTEMP             = "%MW7541.2";
String PC_SL_ECS_PRDAUTADOLTEMP           = "%MW7541.3";
String PC_SL_ECS_RPMALTAPRDAUTSEN         = "%MW7541.4";
String PC_SL_ECS_RPMALTAPRDAUTDED         = "%MW7541.5";
String PC_SL_ECS_PRDAUTFLAPFECHA          = "%MW7541.6";
String PC_SL_ECS_REDPOT                   = "%MW7541.7";
String PC_SL_ECS_REDPOTPAD                = "%MW7541.8";
String PC_SL_ECS_REDPOTPOL                = "%MW7541.9";
String PC_SL_ECS_REDPOTPRESFOL            = "%MW7541.10";
String PC_SL_ECS_REDPOTPOD                = "%MW7541.11";
String PC_SL_ECS_REDPOTTAD                = "%MW7541.12";
String PC_SL_ECS_REDPOTTARCARGA           = "%MW7541.13";
String PC_SL_ECS_REDPOTTMEDDESC           = "%MW7541.14";
String PC_SL_ECS_REDPOTTEMPOL             = "%MW7541.15";
String PC_SL_ECS_REDPOTTEMPOLAF           = "%MW7542.0";
String PC_SL_ECS_AUTOESVAF                = "%MW7542.1";
String PC_SL_ECS_AUTOESVAFTOL             = "%MW7542.2";
String PC_SL_ECS_FLPTDABORT               = "%MW7542.3";
String PC_SL_ECS_FLPTDMINRPM              = "%MW7542.4";
String PC_SL_ECS_FLPTDIDLE                = "%MW7542.5";
String PC_SL_ECS_FLPTDCANCEL              = "%MW7542.6";
String PC_SL_ECS_PTDNORMALFL              = "%MW7542.7";
String PC_SL_ECS_PRDEMERGFL               = "%MW7542.8";
String PC_SL_ECS_ENCHENDOAFFL             = "%MW7542.9";
String PC_SL_ECS_ESVAZIANDOAFFL           = "%MW7542.10";
String PC_SL_ECS_RPMNAOATING              = "%MW7542.11";
String PC_SL_ECS_RPMNAOATINGCTRFL         = "%MW7542.12";
String PC_SL_ECS_RPMNAOATINGNETFL         = "%MW7542.13";
String PC_SL_ECS_ETH1FALHA                = "%MW7542.14";
String PC_SL_ECS_ETH2FALHA                = "%MW7542.15";
String PC_SL_ECS_LOPLOCCOMFL              = "%MW7543.0";
String PC_SL_ECS_LOPRTUCOMFL              = "%MW7543.1";
String PC_SL_ECS_LOPRTU1COMFL             = "%MW7543.2";
String PC_SL_ECS_LOPRTU2COMFL             = "%MW7543.3";
String PC_SL_ECS_COMGERALFALHA            = "%MW7543.4";
String PC_SL_ECS_CREMALMONITFL            = "%MW7543.5";
String PC_SL_ECS_RPMMONITFL               = "%MW7543.6";
String PC_SL_ECS_OVERRIDEATIVO            = "%MW7543.8";
String PC_SL_ECS_POTENCIAREVERSA          = "%MW7543.9";
String PC_SL_ECS_NVBXTQEXPAD              = "%MW7543.10";
String PC_SL_ECS_A1FORAMEDIABANC          = "%MW7543.11";
String PC_SL_ECS_A2FORAMEDIABANC          = "%MW7543.12";
String PC_SL_ECS_A3FORAMEDIABANC          = "%MW7543.13";
String PC_SL_ECS_A4FORAMEDIABANC          = "%MW7543.14";
String PC_SL_ECS_A5FORAMEDIABANC          = "%MW7543.15";
String PC_SL_ECS_A6FORAMEDIABANC          = "%MW7544.0";
String PC_SL_ECS_A7FORAMEDIABANC          = "%MW7544.1";
String PC_SL_ECS_A8FORAMEDIABANC          = "%MW7544.2";
String PC_SL_ECS_B1FORAMEDIABANC          = "%MW7544.3";
String PC_SL_ECS_B2FORAMEDIABANC          = "%MW7544.4";
String PC_SL_ECS_B3FORAMEDIABANC          = "%MW7544.5";
String PC_SL_ECS_B4FORAMEDIABANC          = "%MW7544.6";
String PC_SL_ECS_B5FORAMEDIABANC          = "%MW7544.7";
String PC_SL_ECS_B6FORAMEDIABANC          = "%MW7544.8";
String PC_SL_ECS_B7FORAMEDIABANC          = "%MW7544.9";
String PC_SL_ECS_DIFTEMPMEDBANC           = "%MW7544.10";
String PC_SL_ECS_NETSTBYFLETH1            = "%MW7544.11";
String PC_SL_ECS_NETSTBYFLETH2            = "%MW7544.12";
String PC_SL_ECS_MCPSOBRECACIMDBR         = "%MW7544.13";
String PC_SL_ECS_QQACAONAOTOMADBO         = "%MW7544.14";
String PC_SL_ECS_TADPRDAUTNEXECBO         = "%MW7544.15";
String PC_SL_ECS_TOLPRDAUTNEXECBO         = "%MW7545.0";
String PC_SL_ECS_AFESVAUTNEXECBO          = "%MW7545.1";
String PC_SL_ECS_PRDAEMERG2FL             = "%MW7545.2";
String PC_SL_ECS_PRDAEMERG3FL             = "%MW7545.3";
String PC_SL_ECS_PRDAEMERG4FL             = "%MW7545.4";
String PC_SL_ECS_POLBXPRDAAUTOAL          = "%MW7545.5";
String PC_SL_ECS_TADALTPRDAAUTOAL         = "%MW7545.6";
String PC_SL_ECS_CTRLPR                   = "%MW7545.7";
String PC_SL_ECS_CTRLSE                   = "%MW7545.8";
String PC_SL_ECS_CTRLPRRPMALTCH           = "%MW7546.7";
String PC_SL_ECS_CTRLPRACAORETFL          = "%MW7546.10";
String PC_SL_ECS_CTRLSEMPU1FL             = "%MW7546.12";
String PC_SL_ECS_CTRLSEMPU2FL             = "%MW7546.13";
String PC_SL_ECS_CTRLSEARCOLFL            = "%MW7546.14";
String PC_SL_ECS_CTRLSERPMREMFL           = "%MW7546.15";
String PC_SL_ECS_CTRLSECREMALFL           = "%MW7547.0";
String PC_SL_ECS_CTRLSETORQLIM            = "%MW7547.2";
String PC_SL_ECS_CTRLSECOLLIM             = "%MW7547.3";
String PC_SL_ECS_CTRLSEMODPORT3           = "%MW7547.5";
String PC_SL_ECS_CTRLCAODEGUARDA1         = "%MW7547.15";
String PC_SL_ECS_CTRLCAODEGUARDA2         = "%MW7548.0";
String PC_SL_ECS_DEMROTHDWFPTD            = "%MW7548.1";
String PC_SL_ECS_ROTHDWSCMFPTD            = "%MW7548.2";
String PC_SL_ECS_ROTHDWMRFPTD             = "%MW7548.3";
String PC_SL_ECS_AFTOLUBHDWFPTD           = "%MW7548.4";
String PC_SL_ECS_AFPOLUBHDWFPTD           = "%MW7548.5";
String PC_SL_ECS_PSCCRHDWSCMFPTD          = "%MW7548.6";
String PC_SL_ECS_PSCCRHDWMRFPTD           = "%MW7548.7";
String PC_SL_ECS_CARGAHDWSCMFPTD          = "%MW7548.8";
String PC_SL_ECS_CARGAHDWMRFPTD           = "%MW7548.9";
String PC_SL_ECS_TADHDWFPTD               = "%MW7548.10";
String PC_SL_ECS_POLHDWFPTD               = "%MW7548.11";
String PC_SL_ECS_OLAFTEMPANFL             = "%MW7548.12";
String PC_SL_ECS_OLMCPTEMPANFL            = "%MW7548.13";
String PC_SL_ECS_ADTEMPANLGFL             = "%MW7548.14";
String PC_SL_ECS_ARCARGTEMPAFLAN          = "%MW7548.15";
String PC_SL_ECS_ARCARGTEMPBFLAN          = "%MW7549.0";
String PC_SL_ECS_VELREMREFANFL            = "%MW7549.1";
String PC_SL_ECS_COMDEMSENJ1FL            = "%MW7549.2";
String PC_SL_ECS_COMDEMSENJ3FL            = "%MW7549.3";
String PC_SL_ECS_COMPTEMPSENFL            = "%MW7549.4";
String PC_SL_ECS_ROTHDWSENFL              = "%MW7549.5";
String PC_SL_ECS_BREAKWIREAFLAP           = "%MW7549.6";
String PC_SL_ECS_BREAKWIREBFLAP           = "%MW7549.7";
String PC_SL_ECS_PRDAEMERGFLETH1          = "%MW7549.9";
String PC_SL_ECS_PRDAEMERGFLPAIN          = "%MW7549.10";
String PC_SL_ECS_FLAPAWRBRKSENFL          = "%MW7549.11";
String PC_SL_ECS_FLAPBWRBRKSENFL          = "%MW7549.12";
String PC_SL_ECS_MCPBLOQ                  = "%MW7549.13";
String PC_SL_ECS_OLAFPRESSNVS1S2          = "%MW7549.14";
String PC_SL_ECS_OLTEMPFILDPS1S2          = "%MW7549.15";
String PC_SL_ECS_OLAFTEMPS1S2             = "%MW7550.0";
String PC_SL_ECS_MCPVELMPUJ1              = "%MW7550.1";
String PC_SL_ECS_ADTEMPS1S2               = "%MW7550.2";
String PC_SL_ECS_CIL8TEMPALTBCB           = "%MW7550.3";
String PC_SL_ECS_UACPSFFALHA              = "%MW7550.4";
String PC_SL_ECS_UACPSIFALHA              = "%MW7550.5";
String PC_SL_ECS_UACREDUNCFL              = "%MW7550.6";
String PC_SL_ECS_UACUPSGRUP               = "%MW7550.7";
String PC_SL_ECS_MCPVELALDIFMPU           = "%MW7550.9";
String PC_SL_ECS_PLCAOFF                  = "%MW7550.10";
String PC_SL_ECS_PLCBOFF                  = "%MW7550.11";
String PC_SL_ECS_ARCARGALTTEMP            = "%MW7550.12";
String PC_SL_ECS_ARCARGMALTTEMP           = "%MW7550.13";
String PC_SL_ECS_PRDAAUTOGOV              = "%MW7550.14";
String PC_SL_ECS_PRDAAUTOSEGSIS           = "%MW7550.15";
String PC_SL_ECS_SWDDPOLFL                = "%MW7551.0";
String PC_SL_ECS_PLCAFONTEFALHA           = "%MW7551.1";
String PC_SL_ECS_PLCABSINCFALHA           = "%MW7551.2";
String PC_SL_ECS_PLCAMODCOMFALHA          = "%MW7551.3";
String PC_SL_ECS_PLCACRTFALHA             = "%MW7551.4";
String PC_SL_ECS_PLCASLT3ETHCRTFL         = "%MW7551.5";
String PC_SL_ECS_PLCASLT4ETHCRTFL         = "%MW7551.6";
String PC_SL_ECS_PLCBFONTEFALHA           = "%MW7551.8";
String PC_SL_ECS_PLCBBSINCFALHA           = "%MW7551.9";
String PC_SL_ECS_PLCBMODCOMFALHA          = "%MW7551.10";
String PC_SL_ECS_PLCBCRTFALHA             = "%MW7551.11";
String PC_SL_ECS_PLCBSLT3ETHCRTFL         = "%MW7551.12";
String PC_SL_ECS_PLCBSLT4ETHCRTFL         = "%MW7551.13";
String PC_SL_ECS_MPU1J3FALHA              = "%MW7551.15";
String PC_SL_ECS_MPU2J3FALHA              = "%MW7552.0";
String PC_SL_ECS_CRGREDTEMPEXBCB          = "%MW7552.1";
String PC_SL_ECS_CRGARTEMPBCB             = "%MW7552.2";
String PC_SL_ECS_RPMMCPADIFCVHDW          = "%MW7552.3";
String PC_SL_ECS_PRDAUTOAMBOSAL           = "%MW7552.4";
String PC_SL_ECS_MCPSOBRECNCALC           = "%MW7552.5";
String PC_SL_ECS_PERDAREFRPM              = "%MW7552.6";
String PC_SL_ECS_CTRLSETEMPCTLRAL         = "%MW7552.7";
String PC_SL_ECS_IOLOPFLRTU1              = "%MW7552.8";
String PC_SL_ECS_IOLOPFLRTU2              = "%MW7552.9";
String PC_SL_ECS_IOLOPFLRTUREM            = "%MW7552.10";
String PC_SL_ECS_DATARECCOMFL             = "%MW7552.11";
String PC_SL_ECS_REDCARGAEXECBO           = "%MW7552.12";
String PC_SL_ECS_AFESVFLVALVNP            = "%MW7552.13";
String PC_SL_ECS_REDCGPADEXECBO           = "%MW7552.14";
String PC_SL_ECS_REDCGPOLEXECBO           = "%MW7552.15";
String PC_SL_ECS_REDCGPOLREXECBO          = "%MW7553.0";
String PC_SL_ECS_REDCGPODEXECBO           = "%MW7553.1";
String PC_SL_ECS_REDCGTADEXECBO           = "%MW7553.2";
String PC_SL_ECS_REDCGTBAEXECBO           = "%MW7553.3";
String PC_SL_ECS_REDCGMTBAEXECBO          = "%MW7553.4";
String PC_SL_ECS_REDCGTOLEXECBO           = "%MW7553.5";
String PC_SL_ECS_REDCGTOLAFEXECBO         = "%MW7553.6";
String PC_SL_ECS_REDCGTBBEXECBO           = "%MW7553.7";
String PC_SL_ECS_REDCGMTBBEXECBO          = "%MW7553.8";
String PC_SL_ECS_CHOVSCMNAMR              = "%MW7553.9";
String PC_SL_ECS_AFENCFLVALVNP            = "%MW7553.10";
String CP_SL_ECS_PARTIRETH1               = "%MW720.0";
String CP_SL_ECS_PARARETH1                = "%MW720.1";
String CP_SL_ECS_DESARMARETH1             = "%MW720.2";
String CP_SL_ECS_BUZDESLIGETH1            = "%MW720.3";
String CP_SL_ECS_RECTODOSALETH1           = "%MW720.4";
String CP_SL_ECS_ENCHERAFETH1             = "%MW720.5";
String CP_SL_ECS_ESVAZIARAFETH1           = "%MW720.6";
String CP_SL_ECS_PARTIRETH2               = "%MW730.0";
String CP_SL_ECS_PARARETH2                = "%MW730.1";
String CP_SL_ECS_DESARMARETH2             = "%MW730.2";
String CP_SL_ECS_BUZDESLIGETH2            = "%MW730.3";
String CP_SL_ECS_RECTODOSALETH2           = "%MW730.4";
String CP_SL_ECS_ENCHERAFETH2             = "%MW730.5";
String CP_SL_ECS_ESVAZIARAFETH2           = "%MW730.6";
String PC_SA_ECS_OLPRESSANTFI             = "%MF7558";
String PC_SA_ECS_OLPRESSDEPFI             = "%MF7560";
String PC_SA_ECS_OLRESFPRESS              = "%MF7562";
String PC_SA_ECS_ODPRESSANTFI             = "%MF7564";
String PC_SA_ECS_ODPRESSDEPFI             = "%MF7566";
String PC_SA_ECS_ADPRESS                  = "%MF7568";
String PC_SA_ECS_ASPRESS                  = "%MF7570";
String PC_SA_ECS_ARPTDPRESS               = "%MF7572";
String PC_SA_ECS_ARCMBTPRESSBA            = "%MF7574";
String PC_SA_ECS_ARCMBTPRESSBB            = "%MF7576";
String PC_SA_ECS_AFOLUBPRESSS1            = "%MF7578";
String PC_SA_ECS_AFOLUBPRESSS2            = "%MF7580";
String PC_SA_ECS_AFOLUBPRESSNVL           = "%MF7582";
String PC_SA_ECS_AFOLUBPRESS              = "%MF7584";
String PC_SA_ECS_OLTEMPS1DEPFI            = "%MF7586";
String PC_SA_ECS_OLTEMPS2DEPFI            = "%MF7588";
String PC_SA_ECS_OLTEMP                   = "%MF7590";
String PC_SA_ECS_ADTEMPS1                 = "%MF7592";
String PC_SA_ECS_ADTEMPS2                 = "%MF7594";
String PC_SA_ECS_ADTEMP                   = "%MF7596";
String PC_SA_ECS_DESCA1TEMP               = "%MF7598";
String PC_SA_ECS_DESCA2TEMP               = "%MF7600";
String PC_SA_ECS_DESCA3TEMP               = "%MF7602";
String PC_SA_ECS_DESCA4TEMP               = "%MF7604";
String PC_SA_ECS_DESCA5TEMP               = "%MF7606";
String PC_SA_ECS_DESCA6TEMP               = "%MF7608";
String PC_SA_ECS_DESCA7TEMP               = "%MF7610";
String PC_SA_ECS_DESCA8TEMP               = "%MF7612";
String PC_SA_ECS_DESCB1TEMP               = "%MF7614";
String PC_SA_ECS_DESCB2TEMP               = "%MF7616";
String PC_SA_ECS_DESCB3TEMP               = "%MF7618";
String PC_SA_ECS_DESCB4TEMP               = "%MF7620";
String PC_SA_ECS_DESCB5TEMP               = "%MF7622";
String PC_SA_ECS_DESCB6TEMP               = "%MF7624";
String PC_SA_ECS_DESCB7TEMP               = "%MF7626";
String PC_SA_ECS_DESCB8TEMP               = "%MF7628";
String PC_SA_ECS_DESCTC1TEMP              = "%MF7630";
String PC_SA_ECS_DESCTC2TEMP              = "%MF7632";
String PC_SA_ECS_DESCANTSLTEMP            = "%MF7636";
String PC_SA_ECS_DESCTEMPMEDBA            = "%MF7638";
String PC_SA_ECS_DESCTEMPMEDBB            = "%MF7640";
String PC_SA_ECS_DESCCILTMEDIA            = "%MF7642";
String PC_SA_ECS_AFOLUBTEMPS1             = "%MF7644";
String PC_SA_ECS_AFOLUBTEMPS2             = "%MF7646";
String PC_SA_ECS_AFOLUBTEMP               = "%MF7648";
String PC_SA_ECS_POSICREMALPRINC          = "%MF7650";
String PC_SA_ECS_POSICREMALSEC            = "%MF7652";
String PC_SA_ECS_FBSETPOINTRPM            = "%MF7654";
String PC_SA_ECS_SPRPMPMOTOR              = "%MF7656";
String PC_SA_ECS_RPMMOTORS1PRINC          = "%MF7658";
String PC_SA_ECS_RPMMOTORS2PRINC          = "%MF7660";
String PC_SA_ECS_MCPRPM                   = "%MF7662";
String PC_SA_ECS_ARCARGATEMPLA            = "%MF7664";
String PC_SA_ECS_ARCARGATEMPLB            = "%MF7666";
String PC_SA_ECS_DBRATUAL                 = "%MF7670";
String PC_SA_ECS_MCRATUAL                 = "%MF7672";
String PC_SA_ECS_CARGA                    = "%MF7674";
String PC_SA_ECS_BBAELOLHORAFUNC          = "%MF7676";
String PC_SA_ECS_BBAELOLMINFUNC           = "%MF7678";
String PC_SA_ECS_BBAELOLLIG               = "%MF7680";
String PC_SA_ECS_HORASFUNC                = "%MF7682";
String PC_SA_ECS_MINUTOSFUNC              = "%MF7684";
String PC_SA_ECS_ECSLIG                   = "%MF7686";
String PC_SA_ECS_MCPVELHDW                = "%MF7692";
String PC_SA_ECS_COMBDEMJ1                = "%MF7694";
String PC_SA_ECS_COMBDEMJ3                = "%MF7696";
String PC_SA_ECS_COMBCREMALPOS            = "%MF7706";
String PC_SA_ECS_COMBDEMANDA              = "%MF7708";
String PC_SA_ECS_GOVVELMPU1PRINC          = "%MF7736";
String PC_SA_ECS_GOVVELMPU2PRINC          = "%MF7738";
String PC_SA_ECS_GOVVELMPU1STDBY          = "%MF7740";
String PC_SA_ECS_GOVVELMPU2STDBY          = "%MF7742";
String PC_SA_ECS_GOVVELREFPRINC           = "%MF7744";
String PC_SA_ECS_GOVVELREFSTDBY           = "%MF7746";
String PC_SA_ECS_GOVVELTINTCPRINC         = "%MF7748";
String PC_SA_ECS_GOVVELTINTCSTDBY         = "%MF7750";
String PC_SA_ECS_OLTEMPHH                 = "%MF7756";
String PC_SA_ECS_ADTEMPHH                 = "%MF7758";
String PC_SA_ECS_EXACILATEMPHH            = "%MF7760";
String PC_SA_ECS_EXACILBTEMPHH            = "%MF7762";
String PC_SA_ECS_EXATC1DPTEMPHH           = "%MF7764";
String PC_SA_ECS_EXATC2DPTEMPHH           = "%MF7766";
String PC_SA_ECS_EXAANSILTEMPHH           = "%MF7770";
String PC_SA_ECS_BCADCMDTEMPHH            = "%MF7772";
String PC_SA_ECS_BCBDCMDTEMPHH            = "%MF7774";
String PC_SA_ECS_EXMDTEMPHH               = "%MF7776";
String PC_SA_ECS_AFOLTEMPHH               = "%MF7778";
String PC_SA_ECS_LACRGARTEMPHH            = "%MF7780";
String PC_SA_ECS_OLTEMPH                  = "%MF7782";
String PC_SA_ECS_ADTEMPH                  = "%MF7784";
String PC_SA_ECS_EXACILATEMPH             = "%MF7786";
String PC_SA_ECS_EXACILBTEMPH             = "%MF7788";
String PC_SA_ECS_EXATC1DPTEMPH            = "%MF7790";
String PC_SA_ECS_EXATC2DPTEMPH            = "%MF7792";
String PC_SA_ECS_EXAANSILTEMPH            = "%MF7796";
String PC_SA_ECS_BCADCMDTEMPH             = "%MF7798";
String PC_SA_ECS_BCBDCMDTEMPH             = "%MF7800";
String PC_SA_ECS_EXMDTEMPH                = "%MF7802";
String PC_SA_ECS_AFOLTEMPH                = "%MF7804";
String PC_SA_ECS_LACRGARTEMPH             = "%MF7806";
String PC_SA_ECS_OLMCPPRESSANFTL          = "%MF7808";
String PC_SA_ECS_OLMCPPRESSDPFTL          = "%MF7810";
String PC_SA_ECS_OLPSTRESFPRESSL          = "%MF7812";
String PC_SA_ECS_ODPRESSDPFTL             = "%MF7816";
String PC_SA_ECS_ADPRESSL                 = "%MF7818";
String PC_SA_ECS_ASPRESSL                 = "%MF7820";
String PC_SA_ECS_PRTDARPRESSL             = "%MF7822";
String PC_SA_ECS_BCACRGARPRESSH           = "%MF7824";
String PC_SA_ECS_BCBCRGARPRESSH           = "%MF7826";
String PC_SA_ECS_AFOLPRESSL               = "%MF7830";
String PC_SA_ECS_OLMCPPRESSANFTLL         = "%MF7832";
String PC_SA_ECS_OLMCPPRESSDPFTLL         = "%MF7834";
String PC_SA_ECS_OLPSTRESFPRESSLL         = "%MF7836";
String PC_SA_ECS_ODPRESSDPFTLL            = "%MF7840";
String PC_SA_ECS_ADPRESSLL                = "%MF7842";
String PC_SA_ECS_ASPRESSLL                = "%MF7844";
String PC_SA_ECS_PRTDARPRESSLL            = "%MF7846";
String PC_SA_ECS_BCACRGARPRESSHH          = "%MF7848";
String PC_SA_ECS_BCBCRGARPRESSHH          = "%MF7850";
String PC_SA_ECS_AFOLPRESSLL              = "%MF7854";
String PC_SA_ECS_BCACILATEMPDIFH          = "%MF7856";
String PC_SA_ECS_BCBCILBTEMPDIFH          = "%MF7858";
String PC_SA_ECS_BCABTEMPDIFH             = "%MF7860";
String PC_SA_ECS_AFOLPRESSDIFH            = "%MF7862";
String PC_SA_ECS_OLTEMPDPFTDIFH           = "%MF7864";
String PC_SA_ECS_AFOLTEMPDIFH             = "%MF7866";
String PC_SA_ECS_MCPVELCJ1MPUDIFH         = "%MF7868";
String PC_SA_ECS_ADTEMPDIFH               = "%MF7870";
String PC_SA_ECS_MCPVELCJ3MPUDIFH         = "%MF7872";
String PC_SA_ECS_LBCRGARTEMPH             = "%MF7874";
String PC_SA_ECS_LBCRGARTEMPHH            = "%MF7876";
String PC_SA_ECS_BCADCMDTEMPRC            = "%MF7880";
String PC_SA_ECS_BCBDCMDTEMPRC            = "%MF7882";
String PC_SA_ECS_LACRGARTEMPRC            = "%MF7884";
String PC_SA_ECS_LBCRGARTEMPRC            = "%MF7886";
String PC_SA_ECS_OLTEMPRC                 = "%MF7888";
String PC_SA_ECS_ADTEMPRC                 = "%MF7890";
String PC_SA_ECS_OLMCPPRESSDPFTRC         = "%MF7892";
String PC_SA_ECS_AFOLTEMPRC               = "%MF7894";
String PC_SA_ECS_ADPRESSRC                = "%MF7896";
String PC_SA_ECS_ODPRESSDPFTRC            = "%MF7898";
String PC_SA_ECS_OLPSTRESFPRESSRC         = "%MF7902";
String PC_SA_ECS_RPMMCPADIFCVHDW          = "%MF7904";
String PC_SA_ECS_VLENCHERAFFL             = "%MF7906";
String PC_SA_ECS_VLESVAZIARAFFL           = "%MF7908";
String CP_SA_ECS_DEMANDARPMETH1           = "%MW725";
String CP_SA_ECS_DEMANDARPMETH2           = "%MW735";
String PC_SL_ECS_INTPRELUBOK              = "%MW7530.10";
String CP_SL_ECS_PARTIRPRIMEETH1          = "%MW720.7";
String CP_SL_ECS_PARARPRIMEETH1           = "%MW720.8";
String CP_SL_ECS_PARTIRPRIMEETH2          = "%MW730.7";
String CP_SL_ECS_PARARPRIMEETH2           = "%MW730.8";
//---------------------------- RTU ---------------------------
String PC_HL_RTU_OVERRIDELIG            = "%MW6298.8";
String PC_HL_RTU_CREMALIOFL             = "%MW6299.2";
String PC_HL_RTU_RPMMCPIOFL             = "%MW6299.1";
String PC_HL_RTU_CREMALMONITFL          = "%MW6299.0";
String PC_HL_RTU_MCPDEMANDAFL           = "%MW6298.15";
String PC_HL_RTU_NVBXTQEXPAD            = "%MW6298.14";
String PC_HL_RTU_BUZLIGADA              = "%MW6298.13";
String PC_HL_RTU_AFESVAZIANDO           = "%MW6298.12";
String PC_HL_RTU_AFCHEIO                = "%MW6298.11";
String CP_HL_RTU_PARAREMERGHDW          = "%MW511.0";
String PC_HL_RTU_AFVAZIO                = "%MW6298.9";
String PC_HL_RTU_AFESVINTRLCKOK         = "%MW6299.5";
String PC_HL_RTU_PRDAUTO                = "%MW6298.7";
String PC_HL_RTU_PRDEMERG               = "%MW6298.6";
String PC_HL_RTU_PRDNORMAL              = "%MW6298.5";
String PC_HL_RTU_PARANDO                = "%MW6298.4";
String PC_HL_RTU_MCPVIRANDO             = "%MW6298.3";
String PC_HL_RTU_PARTINDO               = "%MW6298.2";
String PC_HL_RTU_EMLOCAL                = "%MW6298.1";
String PC_HL_RTU_EMREMOTO               = "%MW6298.0";
String PC_HL_RTU_AFENCHENDO             = "%MW6298.10";
String PC_HL_RTU_AUTOESVAF              = "%MW6299.14";
String CP_HL_RTU_RECALRMHDW             = "%MW593.4";
String CP_HL_RTU_ATVBOHDW               = "%MW593.3";
String CP_HL_RTU_ESVAFHDW               = "%MW593.2";
String CP_HL_RTU_PARARHDW               = "%MW593.1";
String CP_HL_RTU_PARTIRHDW              = "%MW593.0";
String CP_HA_RTU_DEMANDARPMHDW          = "%MW589";
String PC_HA_RTU_CARGAMCP               = "%MF6306";
String PC_HA_RTU_POSICREMAL             = "%MF6304";
String PC_HL_RTU_CARGAIOFL              = "%MW6299.3";
String PC_HL_RTU_QQALATIVO              = "%MW6299.15";
String PC_HL_RTU_AFENCINTRLCKOK         = "%MW6299.4";
String PC_HL_RTU_AFENCHESVPREST         = "%MW6299.13";
String PC_HL_RTU_UACREDUNCFL            = "%MW6299.12";
String PC_HL_RTU_UACUPSGRUPFL           = "%MW6299.11";
String PC_HL_RTU_UACPSIPRONTO           = "%MW6299.10";
String PC_HL_RTU_UACPSFPRONTO           = "%MW6299.9";
String PC_HL_RTU_MCPSOBREC              = "%MW6299.8";
String PC_HL_RTU_REDCARGAATIVA          = "%MW6299.7";
String PC_HL_RTU_BLOQCAFENATIVO         = "%MW6299.6";
String CP_HL_RTU_SILENCALRHDW           = "%MW593.5";
String PC_HA_RTU_MCPRPM                 = "%MF6302";
//------------------------------- ENG. RED. -------------------------------
String PC_HL_ERHBC_MODHID_OLPBX         = "%MW6022.6";
String PC_HL_ERHBC_MODHID_OLPDIFAL      = "%MW6022.5";
String PC_HA_ERHBC_MODHID_OLPRESS       = "%MF6158";

String PC_HL_ERPBC_SSSK2_NTRAVACPL      = "%MW6023.2";
String PC_HL_ERPBC_SSSK2_TRAVACPL       = "%MW6023.1";
String PC_HL_ERPBC_SSSK2_DACPL          = "%MW6023.0";
String PC_HL_ERPBC_SSSK2_ACPL           = "%MW6022.15";
String PC_HL_ERPBC_SSSK2_NTRAVABER      = "%MW6022.10";
String PC_HL_ERPBC_SSSK2_TRAVABER       = "%MW6022.9";

String PC_HL_ERPBC_SSSK1_NTRAVACPL      = "%MW6022.14";
String PC_HL_ERPBC_SSSK1_TRAVACPL       = "%MW6022.13";
String PC_HL_ERPBC_SSSK1_DACPL          = "%MW6022.12";
String PC_HL_ERPBC_SSSK1_ACPL           = "%MW6022.11";
String PC_HL_ERPBC_SSSK1_NTRAVABER      = "%MW6022.8";
String PC_HL_ERPBC_SSSK1_TRAVABER       = "%MW6022.7";

String PC_HL_ERSBB_SSSK3_DACPL          = "%MW6023.14";
String PC_HL_ERSBB_SSSK3_ACPL           = "%MW6023.13";
String PC_HL_ERSBB_SSSK3_OLPBX          = "%MW6023.12";
String PC_HL_ERSBB_SSSK3_NTRAVACPL      = "%MW6023.11";
String PC_HL_ERSBB_SSSK3_TRAVACPL       = "%MW6023.10";

String PC_HL_ERSBE_SSSK4_DACPL          = "%MW6023.9";
String PC_HL_ERSBE_SSSK4_ACPL           = "%MW6023.8";
String PC_HL_ERSBE_SSSK4_OLPBX          = "%MW6023.7";
String PC_HL_ERSBE_SSSK4_NTRAVACPL      = "%MW6023.6";
String PC_HL_ERSBE_SSSK4_TRAVACPL       = "%MW6023.5";

String CP_HL_ERHBC_BBELPN_AUTOMATICO            = "%MW508.12";
String CP_HL_ERHBC_BBELPN_MANUAL                = "%MW508.11";
String CP_HL_ERHBC_BBELPN_LIGAR                 = "%MW508.8";
String CP_HL_ERHBC_BBELPN_DESLIGAR              = "%MW508.9";
String CP_HL_ERHBC_BBELPN_PARAREMERG            = "%MW508.10";
String CP_HL_ERHBC_BBELPN_LIBPEMERG             = "%MW510.8";

String PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES         = "%MW6026.11";
String PC_HL_ERHBC_BBELPN_PRDEMERGSCMLI         = "%MW6027.12";
String PC_HL_ERHBC_BBELPN_PRDEMERGSCMDE         = "%MW6027.13";
String PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG         = "%MW6026.10";
String PC_HL_ERHBC_BBELPN_EMREM                 = "%MW6022.4";
String PC_HL_ERHBC_BBELPN_MOTELLIG              = "%MW6022.0";
String PC_HL_ERHBC_BBELPN_EMAUT                 = "%MW6022.1";
String PC_HL_ERHBC_BBELPN_MOTPNLIG              = "%MW6022.2";
String PC_HL_ERHBC_BBELPN_SOBREC                = "%MW6022.3";


//-------------------------------    HPC    -------------------------------
String PC_HL_HPCBB_UDOHPC_OLPRESSOK     = "%MW6025.9";
String PC_HL_HPCBB_MODHID_OLPBX         = "%MW6025.15";
String PC_HL_HPCBE_MODHID_OLPBX         = "%MW6024.15";
String PC_HL_HPCBE_UDOHPC_OLPRESSOK     = "%MW6024.9";



//------------------- VARIAVEIS DOS INTERNAS -------------------

String IP              = "120.40.0.1";
String CONTADOR_CONEXAO= "%MW33000";
String NomeForm        = "MCP BB";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;

int   MWO_i           = 4500;
int   MWO_f           = 4567;

int   contador        = 0;

bool  ackpartida      = false;
bool  ackparada       = false;
bool  ackparadaemerg  = false;
int   contadorpartida = 0;
int   contadorparada  = 0;
float rotacao         = 0;
float demanda_et1     = 680;
float demanda_et2     = 680;
float demanda_hdw     = 600;
bool  mcpvirando      = false;
bool  emlocal         = false;
int   lista           = 0;
bool  primefunc       = false;
float olpressantfi    = 0.0;
float olpressdepfi    = 0.0;
float olpressresfr    = 0.0;
int   tempoEncherAF   = 1;
int   tempoEsvaziarAF = 1;

float rotacaoinicial  = 680;
float rotacaovirando  = 300;

bool  ack_batover     = false;
bool  BOligar         = false;
bool  BOdesligar      = false;
bool  batover         = false;

bool  ackesvaziar     = false;
bool  ackencher       = false;

bool  afvazio         = false;
bool  afcheio         = false;

bool  esvaziar        = false;
float demanda         = 0;
bool  tempos_curtos   = false;

bool  inibir_cmd_prime = false;
bool  inibir_pre_prime = false;

bool  ativa_piscar     = false;
bool  piscar           = false;

//DADOS DE PASSO PARA CONTROLE DE CARGA

String PASSO_OPTO   = "%MW3069.5";
String PASSO_REAL   = "%MW119";
String PASSO_SIML   = "%MF6172";
float  PASSO___X1   = 2588;
float  PASSO___Y1   = -100;
float  PASSO___X2   = 6357;
float  PASSO___Y2   = 0;
float  PASSO___X3   = 9531;
float  PASSO___Y3   = 100;
float  PASSO_SIST   = 0;
float  PASSO_CARG   = 0;
float  PASSO_ANTIGO = 0;

float  CREMALHEIRA  = 35;
float  MCR          = 50;
float  DBR          = MCR + 10;
float  CARGA        = CREMALHEIRA - MCR;

float  CARGA_PAS_1  = 0;
float  CARGA_PAS_2  = 85;
float  CARGA_PAS_3  = 90;
float  CARGA_PAS_4  = 100;

float  CARGA_RPM_1  = 705;
float  CARGA1_RPM1  = -20;
float  CARGA2_RPM1  = -15;
float  CARGA3_RPM1  = -10;
float  CARGA4_RPM1  = -5;
float  CGMCR1_RPM1  = 50;
float  CGMCR2_RPM1  = 50;
float  CGMCR3_RPM1  = 65;
float  CGMCR4_RPM1  = 75;

float  CARGA_RPM_2  = 950;
float  CARGA1_RPM2  = -15;
float  CARGA2_RPM2  = -13;
float  CARGA3_RPM2  = -7;
float  CARGA4_RPM2  = -2;
float  CGMCR1_RPM2  = 50;
float  CGMCR2_RPM2  = 65;
float  CGMCR3_RPM2  = 80;
float  CGMCR4_RPM2  = 85;

float  CARGA_RPM_3  = 1200;
float  CARGA1_RPM3  = -15;
float  CARGA2_RPM3  = -10;
float  CARGA3_RPM3  = -5;
float  CARGA4_RPM3  = 0;
float  CGMCR1_RPM3  = 50;
float  CGMCR2_RPM3  = 70;
float  CGMCR3_RPM3  = 85;
float  CGMCR4_RPM3  = 90;

bool   USAR_PASSO_REAL = false;

float  X_LOAD_1 = -15;
float  Y_LOAD_1 = 0;
float  X_LOAD_2 = -5;
float  Y_LOAD_2 = 85;
float  X_LOAD_3 = 0;
float  Y_LOAD_3 = 90;
float  X_LOAD_4 = 5;
float  Y_LOAD_4 = 100;

bool   Habilitar_Caturro = false;
float  TOLER_CATURRO = 0.2;
bool   VARIA_CARGA = true;

bool   controle_escrita_rpm = false;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;
//INCIALIZAÇÃO DO DRIVER
TModBusTCPDriver CLP( frmPrincipal,IP,QUANTUM );

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

        pnlStatus->Visible = true;
        pnlCTRL->Visible = false;
        pnlPrime->Visible = false;
        pnlAF->Visible = false;
        pnlLocal->Visible = false;

        DateTimeToString( TimeStamp, AnsiString( "hh:nn:ss" ), Now() );

        lblInicioPrograma->Caption = TimeStamp;
        lblInicioPrograma->Visible = true;
        lblEndereco->Caption = CONTADOR_CONEXAO;
        lblEndereco->Visible = true;
        lblWatchdogEx->Visible = true;

        tmrStarting->Enabled = true;
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
               tmrCtrlCarga->Enabled = false;
               if (tmrReconecta->Enabled == false){
                       tmrReconecta->Enabled = true;
               }
        }
        if (CLP.Conectado() != 0 && perdaconexao == true ){//&& contador_ok == true){
               perdaconexao = false;
               tmrLeitura->Enabled = true;
               tmrCtrlCarga->Enabled = true;
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
void __fastcall TfrmPrincipal::tmrStartingTimer(TObject *Sender)
{
//--------------------- INICIA ANALÓGICAS ---------------------
        /* CLP.WR( VARIAVEL ANALOGICA , 0);                      */
        /* prbVARIAVEL ANALOGICA->Max =  100 * 1000; //SE HOUVER */
        /* prbVARIAVEL ANALOGICA->Min = -100 * 1000; //SE HOUVER */

        lblDemandaLocal->Caption = rotacaoinicial;
        lblTolerCaturro->Caption = FormatFloat( "##0.##", TOLER_CATURRO );
        txtTolerCaturro->Text    = FormatFloat( "##0.##", TOLER_CATURRO );

        CLP.WR( PC_SA_ECS_MCPRPM           ,0   );
        CLP.WR( PC_HA_RTU_MCPRPM           ,0   );
        CLP.WR( PC_SA_ECS_RPMMOTORS1PRINC  ,0   );
        CLP.WR( PC_SA_ECS_RPMMOTORS2PRINC  ,0   );
        CLP.WR( PC_SA_ECS_OLTEMPHH         ,90  );
        CLP.WR( PC_SA_ECS_OLTEMPH          ,70  );
        CLP.WR( PC_SA_ECS_ADTEMPHH         ,90  );
        CLP.WR( PC_SA_ECS_ADTEMPH          ,80  );
        CLP.WR( PC_SA_ECS_EXACILATEMPHH    ,300 );
        CLP.WR( PC_SA_ECS_EXACILATEMPH     ,150 );
        CLP.WR( PC_SA_ECS_EXACILBTEMPHH    ,300 );
        CLP.WR( PC_SA_ECS_EXACILBTEMPH     ,150 );
        CLP.WR( PC_SA_ECS_EXATC1DPTEMPHH   ,300 );
        CLP.WR( PC_SA_ECS_EXATC1DPTEMPH    ,150 );
        CLP.WR( PC_SA_ECS_EXATC2DPTEMPHH   ,300 );
        CLP.WR( PC_SA_ECS_EXATC2DPTEMPH    ,150 );
        CLP.WR( PC_SA_ECS_EXAANSILTEMPHH   ,300 );
        CLP.WR( PC_SA_ECS_EXAANSILTEMPH    ,150 );
        CLP.WR( PC_SA_ECS_BCADCMDTEMPHH    ,300 );
        CLP.WR( PC_SA_ECS_BCADCMDTEMPH     ,150 );
        CLP.WR( PC_SA_ECS_BCBDCMDTEMPHH    ,300 );
        CLP.WR( PC_SA_ECS_BCBDCMDTEMPH     ,150 );
        CLP.WR( PC_SA_ECS_EXMDTEMPHH       ,300 );
        CLP.WR( PC_SA_ECS_EXMDTEMPH        ,150 );
        CLP.WR( PC_SA_ECS_AFOLTEMPHH       ,90  );
        CLP.WR( PC_SA_ECS_AFOLTEMPH        ,70  );
        CLP.WR( PC_SA_ECS_LACRGARTEMPHH    ,50  );
        CLP.WR( PC_SA_ECS_LACRGARTEMPH     ,40  );
        CLP.WR( PC_SA_ECS_LBCRGARTEMPHH    ,50  );
        CLP.WR( PC_SA_ECS_LBCRGARTEMPH     ,40  );
        CLP.WR( PC_SA_ECS_OLMCPPRESSANFTL  ,2   );
        CLP.WR( PC_SA_ECS_OLMCPPRESSANFTLL ,1   );
        CLP.WR( PC_SA_ECS_OLMCPPRESSDPFTL  ,2   );
        CLP.WR( PC_SA_ECS_OLMCPPRESSDPFTLL ,1   );
        CLP.WR( PC_SA_ECS_OLPSTRESFPRESSL  ,3   );
        CLP.WR( PC_SA_ECS_OLPSTRESFPRESSLL ,2   );
        CLP.WR( PC_SA_ECS_ODPRESSDPFTL     ,0.5 );
        CLP.WR( PC_SA_ECS_ODPRESSDPFTLL    ,0.3 );
        CLP.WR( PC_SA_ECS_ADPRESSL         ,2   );
        CLP.WR( PC_SA_ECS_ADPRESSLL        ,1   );
        CLP.WR( PC_SA_ECS_ASPRESSL         ,0.5 );
        CLP.WR( PC_SA_ECS_ASPRESSLL        ,0.3 );
        CLP.WR( PC_SA_ECS_PRTDARPRESSL     ,20  );
        CLP.WR( PC_SA_ECS_PRTDARPRESSLL    ,10  );
        CLP.WR( PC_SA_ECS_BCACRGARPRESSHH  ,1.5 );
        CLP.WR( PC_SA_ECS_BCACRGARPRESSH   ,1.0 );
        CLP.WR( PC_SA_ECS_BCBCRGARPRESSHH  ,1.5 );
        CLP.WR( PC_SA_ECS_BCBCRGARPRESSH   ,1.0 );
        CLP.WR( PC_SA_ECS_AFOLPRESSL       ,2   );
        CLP.WR( PC_SA_ECS_AFOLPRESSLL      ,1   );
        CLP.WR( PC_SA_ECS_POSICREMALPRINC  ,CREMALHEIRA );
        CLP.WR( PC_SA_ECS_POSICREMALSEC    ,CREMALHEIRA );
        CLP.WR( PC_SA_ECS_COMBCREMALPOS    ,CREMALHEIRA );
        CLP.WR( PC_HA_RTU_POSICREMAL       ,CREMALHEIRA );
        CLP.WR( PC_SA_ECS_DBRATUAL         ,DBR );
        CLP.WR( PC_SA_ECS_MCRATUAL         ,MCR );
        CLP.WR( PC_SA_ECS_CARGA            ,CARGA );
        CLP.WR( PC_HA_RTU_CARGAMCP         ,CARGA );
        CLP.WR( PC_SA_ECS_OLTEMPS1DEPFI    ,70  );
        CLP.WR( PC_SA_ECS_OLTEMPS2DEPFI    ,70  );
        CLP.WR( PC_SA_ECS_OLTEMP           ,70  );
        CLP.WR( PC_SA_ECS_OLPRESSANTFI     , 0  );
      	CLP.WR( PC_SA_ECS_OLPRESSDEPFI     , 0  );
        CLP.WR( PC_SA_ECS_OLRESFPRESS      , 0  );
        CLP.WR( PC_SA_ECS_AFOLUBTEMPS1     ,60  );
        CLP.WR( PC_SA_ECS_AFOLUBTEMPS2     ,60  );
        CLP.WR( PC_SA_ECS_AFOLUBTEMP       ,60  );
        CLP.WR( PC_SA_ECS_AFOLUBPRESSS1    ,1.5 );
        CLP.WR( PC_SA_ECS_AFOLUBPRESSS2    ,1.5 );
        CLP.WR( PC_SA_ECS_AFOLUBPRESSNVL   ,1.5 );
        CLP.WR( PC_SA_ECS_AFOLUBPRESS      ,2.3 );
//-------------------------------------------------------------
//---------------------  INICIA DIGITAIS  ---------------------
        /*CLP.WR( VARIAVEL_DIGITAL, 0 OU 1 );*/

        CLP.WR( PC_SL_ECS_PARADO           ,1   );
        CLP.WR( PC_SL_ECS_PARANDO          ,0   );
        CLP.WR( PC_SL_ECS_PARTINDO         ,0   );
        CLP.WR( PC_SL_ECS_PARANDO          ,0   );
        CLP.WR( PC_SL_ECS_MCPVIRANDO       ,0   );
        CLP.WR( PC_SL_ECS_EMLOCAL          ,0   );
        CLP.WR( PC_SL_ECS_EMREMOTO         ,1   );
        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC   ,0   );
        CLP.WR( PC_SL_ECS_OLBBAREMLOC      ,0   );
        CLP.WR( PC_SL_ECS_INTPRELUBOK      ,1   );
        CLP.WR( PC_HL_RTU_PRDNORMAL        ,0   );
        CLP.WR( PC_HL_RTU_PARANDO          ,0   );
        CLP.WR( PC_HL_RTU_PARTINDO         ,0   );
        CLP.WR( PC_HL_RTU_PARANDO          ,0   );
        CLP.WR( PC_HL_RTU_MCPVIRANDO       ,0   );
        CLP.WR( PC_HL_RTU_EMLOCAL          ,0   );
        CLP.WR( PC_HL_RTU_EMREMOTO         ,1   );
        CLP.WR( PC_SL_ECS_AFENCHESVPRESSEN ,0   );
        CLP.WR( PC_HL_RTU_AFENCHESVPREST   ,0   );
        CLP.WR( PC_SL_ECS_AFVAZIO          ,1   );
        CLP.WR( PC_HL_RTU_AFVAZIO          ,1   );
        CLP.WR( PC_SL_ECS_AFENCHENDO       ,0   );
        CLP.WR( PC_HL_RTU_AFENCHENDO       ,0   );
        CLP.WR( PC_SL_ECS_AFCHEIO          ,0   );
        CLP.WR( PC_HL_RTU_AFCHEIO          ,0   );
        CLP.WR( PC_SL_ECS_AFESVAZIANDO     ,0   );
        CLP.WR( PC_HL_RTU_AFESVAZIANDO     ,0   );
        CLP.WR( PC_SL_ECS_MECEMSERV        ,1   );
        CLP.WR( PC_SL_ECS_AFENCHINTERLOCOK ,1   );
        CLP.WR( PC_HL_RTU_AFENCINTRLCKOK   ,1   );
        CLP.WR( PC_SL_ECS_AFESVINTERLOCOK  ,1   );
        CLP.WR( PC_HL_RTU_AFESVINTRLCKOK   ,1   );
        CLP.WR( PC_SL_ECS_MCPOKOPERAR      ,1   );
        CLP.WR( PC_SL_ECS_FLAPAABERTO      ,1   );
        CLP.WR( PC_SL_ECS_FLAPBABERTO      ,1   );
        CLP.WR( PC_SL_ECS_FLAPAFECHANDO    ,0   );
        CLP.WR( PC_SL_ECS_FLAPBFECHANDO    ,0   );
        CLP.WR( PC_SL_ECS_FLAPSAFECHADOS   ,0   );
        CLP.WR( PC_SL_ECS_FLAPSBFECHADOS   ,0   );

        CLP.WR(PASSO_OPTO, 1);

        afvazio = true;
        afcheio = false;

//-------------------------------------------------------------
//-------------------------------------------------------------
//ACIONA TODOS OS ENDEREÇOS DE SIMULAÇÃO
        for (int i = MWO_i; i < MWO_f + 1; i++){
                String tempMW = "%MW" ;
                tempMW += i;
                //int teste =  CLP.RD( tempMW );
                //if ( teste != -1){
                        CLP.WR(tempMW, 0xFFFF);
                //}
        }
        for (int i = 3230; i < 3236; i++){
                String tempMW = "%MW" ;
                tempMW += i;
                //int teste =  CLP.RD(  tempMW );
                //if ( teste != -1){
                        CLP.WR(tempMW, 0xFFFF);
                //}
        }

        frmPrincipal->Caption = NomeForm + " - Pronto (CLP" + IP + ")";
        tmrLeitura->Enabled = true;
        //frmAnalogicas->Leitura->Enabled = true;
        //Animacao->Enabled = true;
        Demanda->Enabled = true;
        lblBufferR->Visible = true;
        lblBufferW->Visible = true;
        lblBufferEx->Visible = true;
        lblLista->Visible = true;
        btnOutrosAnalogicos->Enabled = true;
        btnControles->Enabled = true;
        btnPrdEmergLocal->Enabled = true;
        btnPartir->Enabled = true;
        btnParar->Enabled = true;
        btnAcelerarLocal->Enabled = true;
        btnDesacelerarLocal->Enabled = true;
        btnEmRemoto->Enabled = true;
        btnBatOver->Enabled = true;
        btnBBAOLPCtrl->Enabled = true;
        btnBBAOLEmRemoto->Enabled = true;
        btnEncherAF->Enabled = true;
        btnEsvaziarAF->Enabled = true;
        btnCREM->Enabled = true;
        btnDBR->Enabled = true;
        btnMCR->Enabled = true;
        btnCARGA->Enabled = true;
        btnHabilitaCaturro->Enabled = true;
        btnTolerCaturro->Enabled = true;
        btnEscolhePasso->Enabled = true;
        if (ConexaoWatch->Enabled == false){
                ConexaoWatch->Enabled = true;
        }
        Lista->Enabled = true;
        tmrCtrlCarga->Enabled = true;
//FIM DA INICIALIZAÇÃO
        tmrStarting->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrLeituraTimer(TObject *Sender)
{
/* INTERLOCKS OK PARAR PARTIR */
        if ( CLP.RD(PC_SL_ECS_MCPPRTINTERLOCOK) == 1 ){
                //btnInterlocksOKPartir->Caption = "OK Partir";
                shpInterlockOK->Brush->Color = clLime;
        }else{
                //btnInterlocksOKPartir->Caption = "N OK Partir";
                shpInterlockOK->Brush->Color = clWhite;
        }

        if ( CLP.RD(PC_SL_ECS_INTPRELUBOK) == 1 ){
                //btnInterlocksOKPartir->Caption = "OK Partir";
                shpInterlockOKLub->Brush->Color = clLime;
        }else{
                //btnInterlocksOKPartir->Caption = "N OK Partir";
                shpInterlockOKLub->Brush->Color = clWhite;
        }

/* COMANDO DE PARTIR */
        if ( CLP.RD(CP_SL_ECS_PARTIRETH1) == 1 ){
                shpPartirETH1->Brush->Color = clLime;
        }
        else{
                shpPartirETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARTIRETH2) == 1 ){
                shpPartirETH2->Brush->Color = clLime;
        }
        else{
                shpPartirETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_HL_RTU_PARTIRHDW) == 1 ){
                shpPartirHDW->Brush->Color = clLime;
        }
        else{
                shpPartirHDW->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARTIRETH1) == 1    || CLP.RD(CP_SL_ECS_PARTIRETH2) == 1      || CLP.RD(CP_HL_RTU_PARTIRHDW) == 1 ){
                if (ackpartida == false){
                        ackpartida = true;
                        Parada->Enabled = false;
                        Partida->Enabled = true;
                }
        }
//--------------------------------------------
/* COMAMNDO DE PARAR */
        if ( CLP.RD(CP_SL_ECS_PARARETH1) == 1 ){
                shpPararETH1->Brush->Color = clYellow;
        }
        else{
                shpPararETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARARETH2) == 1 ){
                shpPararETH2->Brush->Color = clYellow;
        }
        else{
                shpPararETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_HL_RTU_PARARHDW) == 1 ){
                shpPararHDW->Brush->Color = clYellow;
        }
        else{
                shpPararHDW->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARARETH1) == 1     || CLP.RD(CP_SL_ECS_PARARETH2) == 1       || CLP.RD(CP_HL_RTU_PARARHDW) == 1 ){
                if (ackparada == false){
                        ackparada = true;
                        Partida->Enabled = false;
                        Parada->Enabled = true;
                }
        }
//--------------------------------------------
/* COMANDO DE PARAR EM EMERGÊNCIA */
        if ( CLP.RD(CP_SL_ECS_DESARMARETH1) == 1 ){
                shpPararEmergETH1->Brush->Color = clRed;
                if ( CLP.RD( PC_SL_ECS_MCPPRDEMERG1NET ) != 1 ){
                        CLP.WR( PC_SL_ECS_MCPPRDEMERG1NET, 1 );
                }
                if ( CLP.RD( PC_SL_ECS_PRDEMERG1REDE ) != 1 ){
                        CLP.WR( PC_SL_ECS_PRDEMERG1REDE  , 1 );
                }
        }
        else{
                shpPararEmergETH1->Brush->Color = clWhite;
                if (shpPararEmergETH1->Brush->Color == clWhite){
                        if ( CLP.RD( PC_SL_ECS_MCPPRDEMERG1NET ) != 0 ){
                                CLP.WR( PC_SL_ECS_MCPPRDEMERG1NET, 0 );
                        }
                        if ( CLP.RD( PC_SL_ECS_PRDEMERG1REDE ) != 0 ){
                                CLP.WR( PC_SL_ECS_PRDEMERG1REDE  , 0 );
                        }
                }
        }
        if ( CLP.RD(CP_SL_ECS_DESARMARETH2) == 1 ){
                shpPararEmergETH2->Brush->Color = clRed;
        }
        else{
                shpPararEmergETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_HL_RTU_PARAREMERGHDW) == 1 ){
                shpPararEmergHDW->Brush->Color = clRed;
        }
        else{
                shpPararEmergHDW->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_DESARMARETH1) == 1  || CLP.RD(CP_SL_ECS_DESARMARETH2) == 1    || CLP.RD(CP_HL_RTU_PARAREMERGHDW) == 1 ){
                if (ackparadaemerg == false && emlocal == false){
                        ackparadaemerg = true;
                        Partida->Enabled = false;
                        if (shpParado->Brush->Color == clWhite){
                                Parada->Enabled = true;
                        }
                        CLP.WR( PC_HL_RTU_PRDEMERG       , 1 );
                }
        }
        else{
                ackparadaemerg = false;
                if (CLP.RD( PC_SL_ECS_MCPPRDEMERGPNL ) == 0 && emlocal == false){
                        if ( CLP.RD( PC_HL_RTU_PRDEMERG ) != 0 ){
                                CLP.WR( PC_HL_RTU_PRDEMERG       , 0 );
                        }
                }
        }
//--------------------------------------------
/* COMANDO DE SILENCIAR BUZINA */
        if ( CLP.RD(CP_SL_ECS_BUZDESLIGETH1) == 1 ){
                shpSilenciarETH1->Brush->Color = clBlue;
        }
        else{
                shpSilenciarETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_BUZDESLIGETH2) == 1 ){
                shpSilenciarETH2->Brush->Color = clBlue;
        }
        else{
                shpSilenciarETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_HL_RTU_SILENCALRHDW) == 1 ){
                shpSilenciarHDW->Brush->Color = clBlue;
        }
        else{
                shpSilenciarHDW->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_BUZDESLIGETH1) == 1  || CLP.RD(CP_SL_ECS_BUZDESLIGETH2) == 1  || CLP.RD(CP_HL_RTU_SILENCALRHDW) == 1 ){
        }
//--------------------------------------------
/* COMANDO DE RECONHECER TODOS ALARMES */
        if ( CLP.RD(CP_SL_ECS_RECTODOSALETH1) == 1 ){
                shpReconhecerETH1->Brush->Color = clBlue;
        }
        else{
                shpReconhecerETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_RECTODOSALETH2) == 1 ){
                shpReconhecerETH2->Brush->Color = clBlue;
        }
        else{
                shpReconhecerETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_HL_RTU_RECALRMHDW) == 1 ){
                shpReconhecerHDW->Brush->Color = clBlue;
        }
        else{
                shpReconhecerHDW->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_RECTODOSALETH1) == 1 || CLP.RD(CP_SL_ECS_RECTODOSALETH2) == 1 || CLP.RD(CP_HL_RTU_RECALRMHDW) == 1 ){
        }
//--------------------------------------------
/* ESTADOS OPERAÇÃO AF */
        if ( CLP.RD(PC_SL_ECS_AFENCHESVPRESSEN) == 1 ){
                shpPS3->Brush->Color = clLime;
        }
        else{
                shpPS3->Brush->Color = clWhite;
        }
        if ( CLP.RD(PC_SL_ECS_AFVAZIO) == 1 ){
                shpVazio->Brush->Color = clLime;
                afvazio = true;
        }
        else{
                shpVazio->Brush->Color = clWhite;
                afvazio = false;
        }
        if ( CLP.RD(PC_SL_ECS_AFENCHENDO) == 1 ){
                shpEnchendo->Brush->Color = clLime;
        }
        else{
                shpEnchendo->Brush->Color = clWhite;
        }
        if ( CLP.RD(PC_SL_ECS_AFCHEIO) == 1 ){
                shpCheio->Brush->Color = clLime;
                afcheio = true;
        }
        else{
                shpCheio->Brush->Color = clWhite;
                afcheio = false;
        }
        if ( CLP.RD(PC_SL_ECS_AFESVAZIANDO) == 1 ){
                shpEsvaziando->Brush->Color = clLime;
        }
        else{
                shpEsvaziando->Brush->Color = clWhite;
        }
//--------------------------------------------
/* COMANDO DE ENCHER AF */
        if ( CLP.RD(CP_SL_ECS_ENCHERAFETH1) == 1 ){
                shpEncherETH1->Brush->Color = clLime;
        }
        else{
                shpEncherETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_ENCHERAFETH2) == 1 ){
                shpEncherETH2->Brush->Color = clLime;
        }
        else{
                shpEncherETH2->Brush->Color = clWhite;
        }
        if ( tempos_curtos == false ){
                if ( rotacao >= 1000 ){
                        tempoEncherAF = 35 * 1000;
                }else{
                        if ( rotacao >= 900 ){
                                tempoEncherAF = (((1000 - rotacao)/20)+35)*1000;
                        }else{
                                if ( rotacao >= 750 ){
                                        tempoEncherAF = (((900 - rotacao)/15)+40)*1000;
                                }else{
                                        if ( rotacao >= 600 ){
                                                tempoEncherAF = (((750 - rotacao)/10)+50)*1000;
                                        }else{
                                                tempoEncherAF = 70 * 1000;
                                        };
                                };
                        };
                };
        }else{
                tempoEncherAF = 10000;
        }
        if ( tempos_curtos == false ){
                if ( rotacao >= 850 ){
                        tempoEsvaziarAF = 35 * 1000;
                }else{
                        if ( rotacao >= 675 ){
                                tempoEsvaziarAF =  57 * 1000;
                        }else{
                                tempoEsvaziarAF = (35+((22.5/175)*(850 - rotacao)))*1000;
                        };
                };
        }else{
                tempoEsvaziarAF = 10000;
        }
        if (( CLP.RD(CP_SL_ECS_ENCHERAFETH1) == 1   || CLP.RD(CP_SL_ECS_ENCHERAFETH2) == 1 ) && ackencher == false){
                if ( tmrPreEncherAF->Enabled == false  && afcheio == false) {
                        ackencher = true;
                        tmrEsvaziarAF->Enabled = false;
                        if ( ackesvaziar == true ){
                                ackesvaziar = false;
                        }
                        tmrPreEncherAF->Enabled = true;
                }
        }
//--------------------------------------------
/* COMANDO DE ESVAZIAR AF*/
        if ( CLP.RD(CP_SL_ECS_ESVAZIARAFETH1) == 1 ){
                shpEsvaziarETH1->Brush->Color = clLime;
        }
        else{
                shpEsvaziarETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_ESVAZIARAFETH2) == 1 ){
                shpEsvaziarETH2->Brush->Color = clLime;
        }
        else{
                shpEsvaziarETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_HL_RTU_ESVAFHDW) == 1 ){
                shpEsvaziarHDW->Brush->Color = clLime;
        }
        else{
                shpEsvaziarHDW->Brush->Color = clWhite;
        }
        if (CLP.RD(CP_SL_ECS_ESVAZIARAFETH1) == 1 || CLP.RD(CP_SL_ECS_ESVAZIARAFETH2) == 1 || CLP.RD(CP_HL_RTU_ESVAFHDW) == 1 ){
                esvaziar = true;
        }
        else{
                esvaziar = false;
        }
        if (  esvaziar == true && ackesvaziar == false){

                if ( tmrPreEsvaziarAF->Enabled == false && afvazio == false && afcheio == true) {
                        ackesvaziar = true;
                        tmrEncherAF->Enabled = false;
                        if ( ackencher == true ){
                                ackencher = false;
                        }
                        tmrPreEsvaziarAF->Enabled = true;
                }
        }
//--------------------------------------------
/* COMANDO DE ATIVAR BO*/
        if ( CLP.RD(CP_HL_RTU_ATVBOHDW) == 1 && ack_batover == false){
                if ( batover == false && ack_batover == false && BOligar == false){
                        ack_batover = true;
                        shpAtivarBOHDW->Brush->Color = clRed;
                        BOdesligar = false;
                        BOligar = true;
                        tmrBO->Enabled = true;
                }else{
                        if (  batover == true && ack_batover == false && BOdesligar == false){
                                ack_batover = true;
                                shpAtivarBOHDW->Brush->Color = clYellow;
                                BOligar = false;
                                BOdesligar = true;
                                tmrBO->Enabled = true;
                        }
                }
        }
        else{
                shpAtivarBOHDW->Brush->Color = clWhite;
                ack_batover = false;
        };
        if (CLP.RD(PC_SL_ECS_OVERRIDELIG) == 1 || CLP.RD(PC_HL_RTU_OVERRIDELIG) == 1){
                shpBatOver->Brush->Color = clRed;
                btnBatOver->Caption = "B. O. Lig.";
                batover = true;
        }
        else{
                shpBatOver->Brush->Color = clWhite;
                btnBatOver->Caption = "B. O. Des.";
                batover = false;
        }
//--------------------------------------------
/* COMANDO DE PARTIR PRIME*/
        if ( CLP.RD(CP_SL_ECS_PARTIRPRIMEETH1) == 1 ){
                shpPartirBBAOLETH1->Brush->Color = clLime;
                /*if ( shpBBAOLEmOpercao->Brush->Color == clWhite ){
                        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC , 1 );
                        //CLP.WR( PC_SL_ECS_OLPRESSPARTMCPOK, 1 );
                        //shpBBAOLEmOpercao->Brush->Color = clLime
                }*/
        }
        else{
                shpPartirBBAOLETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARTIRPRIMEETH2) == 1 ){
                shpPartirBBAOLETH2->Brush->Color = clLime;
                /*if ( shpBBAOLEmOpercao->Brush->Color == clWhite ){
                        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC , 1 );
                        //CLP.WR( PC_SL_ECS_OLPRESSPARTMCPOK, 1 );
                        //shpBBAOLEmOpercao->Brush->Color = clLime
                }*/
        }
        else{
                shpPartirBBAOLETH2->Brush->Color = clWhite;
        }
        if  ( CLP.RD(CP_SL_ECS_PARTIRPRIMEETH2) == 1 || CLP.RD(CP_SL_ECS_PARTIRPRIMEETH1) == 1 ) {
                if ( shpBBAOLEmOpercao->Brush->Color == clWhite && inibir_cmd_prime == false){
                        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC , 1 );
                        //CLP.WR( PC_SL_ECS_OLPRESSPARTMCPOK, 1 );
                        //shpBBAOLEmOpercao->Brush->Color = clLime
                        primefunc = true;
                        if (inibir_pre_prime == false){
                                tmrPRIME->Enabled = true;
                        }
                }
        }
//--------------------------------------------
/* COMANDO DE PARAR PRIME*/
        if ( CLP.RD(CP_SL_ECS_PARARPRIMEETH1) == 1 ){
                shpPararBBAOLETH1->Brush->Color = clYellow;
                /*if ( shpBBAOLEmOpercao->Brush->Color == clLime ){
                        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC , 0 );
                        //shpBBAOLEmOpercao->Brush->Color = clWhite
                }*/
        }
        else{
                shpPararBBAOLETH1->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARARPRIMEETH2) == 1 ){
                shpPararBBAOLETH2->Brush->Color = clYellow;
                /*if ( shpBBAOLEmOpercao->Brush->Color == clLime ){
                        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC , 0 );
                        //shpBBAOLEmOpercao->Brush->Color = clWhite
                }*/
        }
        else{
                shpPararBBAOLETH2->Brush->Color = clWhite;
        }
        if ( CLP.RD(CP_SL_ECS_PARARPRIMEETH1) == 1 ||  CLP.RD(CP_SL_ECS_PARARPRIMEETH2) == 1 ){
                if ( shpBBAOLEmOpercao->Brush->Color == clLime ){
                        CLP.WR( PC_SL_ECS_PRIMPUMPMCFUNC , 0 );
                        primefunc = false;
                        tmrPRIME->Enabled = true;
                        //shpBBAOLEmOpercao->Brush->Color = clWhite
                }
        }
        if ( CLP.RD(PC_SL_ECS_OLBBAREMLOC) == 0 ){
                shpBBAOLEmRemoto->Brush->Color = clBlue;
                btnBBAOLEmRemoto->Caption = "Em Remoto";
        }
        else{
                shpBBAOLEmRemoto->Brush->Color = clWhite;
                btnBBAOLEmRemoto->Caption = "Em Local";
        }
        if ( CLP.RD(PC_SL_ECS_PRIMPUMPMCFUNC) == 1 ){
                shpBBAOLEmOpercao->Brush->Color = clLime;
                btnBBAOLPCtrl->Caption = "Parar";
        }
        else{
                shpBBAOLEmOpercao->Brush->Color = clWhite;
                btnBBAOLPCtrl->Caption = "Partir";
        }
//--------------------------------------------
/* ESTADOS DE OPERAÇÃO */
        if ( CLP.RD(PC_SL_ECS_PARADO) == 1 ){
                shpParado->Brush->Color = clLime;
        }
        else{
                shpParado->Brush->Color = clWhite;
        }
        if ( CLP.RD(PC_SL_ECS_PARTINDO) == 1 ){
                shpPartindo->Brush->Color = clYellow;
        }
        else{
                shpPartindo->Brush->Color = clWhite;
        }
        if ( CLP.RD(PC_SL_ECS_MCPVIRANDO) == 1 ){
                shpVirando->Brush->Color = clLime;
                mcpvirando = true;
        }
        else{
                shpVirando->Brush->Color = clWhite;
                mcpvirando = false;
        }
        if ( CLP.RD(PC_SL_ECS_PARANDO) == 1 ){
                shpParando->Brush->Color = clRed;
        }
        else{
                shpParando->Brush->Color = clWhite;
        }
        //ROTAÇÃO
        lblRotacao->Caption =  CLP.RD( PC_SA_ECS_MCPRPM );
        frmControles->lblRPMMCP->Caption = lblRotacao->Caption;
        frmControlesNovo->lblRPMMCP->Caption = lblRotacao->Caption;
        //TEMPOS
        lblTempoPartida->Caption = contadorpartida;
        lblTempoParada->Caption = contadorparada;
        if ( CLP.RD(PC_SL_ECS_EMREMOTO) == 1 ){
                shpEmRemoto->Brush->Color = clBlue;
                btnEmRemoto->Caption = "Em Remoto";
        }
        else{
                shpEmRemoto->Brush->Color = clWhite;
                btnEmRemoto->Caption = "Em Local";
        }
        if ( CLP.RD(PC_SL_ECS_EMLOCAL) == 1 ){
                shpEmLocal->Brush->Color = clRed;
                /*btnPrdEmergLocal->Enabled = true;
                btnPartir->Enabled = true;
                btnParar->Enabled = true;
                btnAcelerarLocal->Enabled = true;
                btnDesacelerarLocal->Enabled = true;*/
        }
        else{
                shpEmLocal->Brush->Color = clWhite;
                /*btnPrdEmergLocal->Enabled = false;
                btnPartir->Enabled = false;
                btnParar->Enabled = false;
                btnAcelerarLocal->Enabled = false;
                btnDesacelerarLocal->Enabled = false;*/
        }
        //ANALOGICAS - LIMITES
        frmAnalogicas->lblAnalog01->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLTEMPHH));
        frmAnalogicas->lblAnalog02->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLTEMPH));
        frmAnalogicas->lblAnalog03->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ADTEMPHH));
        frmAnalogicas->lblAnalog04->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ADTEMPH));
        frmAnalogicas->lblAnalog05->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXACILATEMPHH));
        frmAnalogicas->lblAnalog06->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXACILATEMPH));
        frmAnalogicas->lblAnalog07->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXACILBTEMPHH));
        frmAnalogicas->lblAnalog08->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXACILBTEMPH));
        frmAnalogicas->lblAnalog09->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXATC1DPTEMPHH));
        frmAnalogicas->lblAnalog10->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXATC1DPTEMPH));
        frmAnalogicas->lblAnalog11->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXATC2DPTEMPHH));
        frmAnalogicas->lblAnalog12->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXATC2DPTEMPH));
        frmAnalogicas->lblAnalog13->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXAANSILTEMPHH));
        frmAnalogicas->lblAnalog14->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXAANSILTEMPH));
        frmAnalogicas->lblAnalog15->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCADCMDTEMPHH));
        frmAnalogicas->lblAnalog16->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCADCMDTEMPH));
        frmAnalogicas->lblAnalog17->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCBDCMDTEMPHH));
        frmAnalogicas->lblAnalog18->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCBDCMDTEMPH));
        frmAnalogicas->lblAnalog19->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXMDTEMPHH));
        frmAnalogicas->lblAnalog20->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_EXMDTEMPH));
        frmAnalogicas->lblAnalog21->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_AFOLTEMPHH));
        frmAnalogicas->lblAnalog22->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_AFOLTEMPH));
        frmAnalogicas->lblAnalog23->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_LACRGARTEMPHH));
        frmAnalogicas->lblAnalog24->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_LACRGARTEMPH));
        frmAnalogicas->lblAnalog25->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_LBCRGARTEMPHH));
        frmAnalogicas->lblAnalog26->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_LBCRGARTEMPH));
        frmAnalogicas->lblAnalog27->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLMCPPRESSANFTL));
        frmAnalogicas->lblAnalog28->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLMCPPRESSANFTLL));
        frmAnalogicas->lblAnalog29->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLMCPPRESSDPFTL));
        frmAnalogicas->lblAnalog30->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLMCPPRESSDPFTLL));
        frmAnalogicas->lblAnalog31->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLPSTRESFPRESSL));
        frmAnalogicas->lblAnalog32->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLPSTRESFPRESSLL));
        frmAnalogicas->lblAnalog33->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ODPRESSDPFTL));
        frmAnalogicas->lblAnalog34->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ODPRESSDPFTLL));
        frmAnalogicas->lblAnalog35->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ADPRESSL));
        frmAnalogicas->lblAnalog36->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ADPRESSLL));
        frmAnalogicas->lblAnalog37->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ASPRESSL));
        frmAnalogicas->lblAnalog38->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_ASPRESSLL));
        frmAnalogicas->lblAnalog39->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_PRTDARPRESSL));
        frmAnalogicas->lblAnalog40->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_PRTDARPRESSLL));
        frmAnalogicas->lblAnalog41->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCACRGARPRESSHH));
        frmAnalogicas->lblAnalog42->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCACRGARPRESSH));
        frmAnalogicas->lblAnalog43->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCBCRGARPRESSHH));
        frmAnalogicas->lblAnalog44->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_BCBCRGARPRESSH));
        frmAnalogicas->lblAnalog45->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_AFOLPRESSL));
        frmAnalogicas->lblAnalog46->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_AFOLPRESSLL));

        //LEITURA DEMANDA
        demanda_et1 = CLP.RD(CP_SA_ECS_DEMANDARPMETH1);
        demanda_et2 = CLP.RD(CP_SA_ECS_DEMANDARPMETH2);
        demanda_hdw = CLP.RD(CP_HA_RTU_DEMANDARPMHDW );
        demanda_hdw = ((((demanda_hdw - 2000) * (1490 - 600))/(10000 - 2000))+600);
        lblDemandaETH1->Caption = FormatFloat( "##0", demanda_et1);
        lblDemandaETH2->Caption = FormatFloat( "##0", demanda_et2);
        lblDemandaHDW->Caption  = FormatFloat( "##0", demanda_hdw);

        lblPressOLub->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLPRESSANTFI));

        //RESPOSTA ROTAÇÃO
        lblRotacaoCalc->Caption = rotacao;
        if (CLP.TamBufWR() <= 19){
        if (CLP.RD(PC_SA_ECS_MCPRPM) != (int) rotacao || CLP.RD(PC_HA_RTU_MCPRPM) != (int) rotacao){
                CLP.WR( PC_SA_ECS_MCPRPM, (int) rotacao );
                CLP.WR( PC_HA_RTU_MCPRPM, (int) rotacao );
                CLP.WR( PC_SA_ECS_RPMMOTORS1PRINC, (int) rotacao );
                CLP.WR( PC_SA_ECS_RPMMOTORS2PRINC, (int) rotacao );
                // escrita da rotação
                if (controle_escrita_rpm == true){
                        controle_escrita_rpm = false;
                }else{
                        controle_escrita_rpm = true;
                };
        }}

        if (controle_escrita_rpm == true){
                shpCtrlRPM->Brush->Color = clLime;
        }else{
                shpCtrlRPM->Brush->Color = clWhite;
        }

        //if (CLP.RD(PC_SA_ECS_OLPRESSANTFI) != olpressdepfi){
        if ( FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLPRESSANTFI)) != FormatFloat( "##0.##", olpressdepfi)){
                if (CLP.TamBufWR() <= 20){
                        CLP.WR(PC_SA_ECS_OLPRESSANTFI, olpressantfi);
                	CLP.WR(PC_SA_ECS_OLPRESSDEPFI, olpressdepfi);
                        CLP.WR(PC_SA_ECS_OLRESFPRESS,  olpressresfr);
                        if (lblPressOLub->Color == clWhite){
                                lblPressOLub->Color = clYellow;
                        }else{
                                lblPressOLub->Color = clWhite;
                        }
                }
        }

        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_CARGA)) != FormatFloat( "##0.#", CARGA)){
                if (CLP.TamBufWR() <= 9){
                        CLP.WR(PC_SA_ECS_CARGA     , CARGA);
                        CLP.WR(PC_HA_RTU_CARGAMCP  , CARGA);
                }
        }
        //if ( CLP.RD(PC_SA_ECS_POSICREMALPRINC) != CREMALHEIRA){
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_POSICREMALPRINC)) != FormatFloat( "##0.#", CREMALHEIRA)){
                if (CLP.TamBufWR() <= 9){
                        CLP.WR(PC_SA_ECS_POSICREMALPRINC, CREMALHEIRA);
                        CLP.WR(PC_SA_ECS_POSICREMALSEC  , CREMALHEIRA);
                        CLP.WR(PC_SA_ECS_COMBCREMALPOS  , CREMALHEIRA);
                        CLP.WR(PC_HA_RTU_POSICREMAL     , CREMALHEIRA);
                }
        }
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_MCRATUAL)) != FormatFloat( "##0.#", MCR)){
                if (CLP.TamBufWR() <= 9){
                        CLP.WR(PC_SA_ECS_MCRATUAL, MCR);
                }
        }
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_DBRATUAL)) != FormatFloat( "##0.#", DBR)){
                if (CLP.TamBufWR() <= 9){
                        CLP.WR(PC_SA_ECS_DBRATUAL, DBR );
                }
        }
        lblCREM1->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_POSICREMALPRINC));
        lblCREM2->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_POSICREMALSEC));
        lblCREM3->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_COMBCREMALPOS));
        lblCREM4->Caption = FormatFloat( "##0.##", CLP.RD(PC_HA_RTU_POSICREMAL));
        frmControles->lblCREMMCP->Caption = lblCREM1->Caption;
        frmControlesNovo->lblCREMMCP->Caption = lblCREM1->Caption;
        lblDBR->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_DBRATUAL));
        lblMCR->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_MCRATUAL));
        frmControles->lblMCRMCP->Caption = lblMCR->Caption;
        frmControlesNovo->lblMCRMCP->Caption = lblMCR->Caption;
        lblCARGA1->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_CARGA));
        lblCARGA2->Caption = FormatFloat( "##0.##", CLP.RD(PC_HA_RTU_CARGAMCP));
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::PartidaTimer(TObject *Sender)
{
        if (contadorpartida == 0){
                CLP.WR(PC_SL_ECS_PARADO     ,0);
                CLP.WR(PC_HL_RTU_PRDNORMAL  ,1);
                CLP.WR(PC_HL_RTU_PRDEMERG   ,0);
                CLP.WR(PC_SL_ECS_PARANDO    ,0);
                CLP.WR(PC_HL_RTU_PARANDO    ,0);
                CLP.WR(PC_SL_ECS_PARTINDO   ,1);
                CLP.WR(PC_HL_RTU_PARTINDO   ,1);
                rotacao = 0;
                Acelerar->Enabled = true;
        }
        if ( rotacao >= rotacaovirando && rotacao < rotacaoinicial){
                CLP.WR(PC_SL_ECS_PARTINDO   ,0);
                CLP.WR(PC_HL_RTU_PARTINDO   ,0);
                CLP.WR(PC_SL_ECS_MCPVIRANDO ,1);
                CLP.WR(PC_HL_RTU_MCPVIRANDO ,1);
        }
        if ( rotacao >= rotacaoinicial ){
                rotacao = rotacaoinicial;
                //CLP.WR( PC_SA_ECS_MCPRPM, rotacao );
                //CLP.WR( PC_HA_RTU_MCPRPM, rotacao);
                Acelerar->Enabled = false;
                Partida->Enabled = false;
        }

        contadorpartida++;

        if( Partida->Enabled == false ){
                 contadorpartida = 0;
                 ackparada = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::AcelerarTimer(TObject *Sender)
{
        rotacao = rotacao + 100;
        //CLP.WR( PC_SA_ECS_MCPRPM, rotacao );
        //CLP.WR( PC_HA_RTU_MCPRPM, rotacao);
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::btnOutrosAnalogicosClick(TObject *Sender)
{
        frmAnalogicas->Parent = frmPrincipal;
        frmAnalogicas->Top = frmPrincipal->Top + 20;
        frmAnalogicas->Left = frmPrincipal->Left + 200;
        frmAnalogicas->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::ParadaTimer(TObject *Sender)
{
        if (contadorparada == 0){
                CLP.WR(PC_SL_ECS_MCPVIRANDO ,0);
                CLP.WR(PC_HL_RTU_MCPVIRANDO ,0);
                CLP.WR(PC_SL_ECS_PARTINDO   ,0);
                CLP.WR(PC_HL_RTU_PARTINDO   ,0);
                CLP.WR(PC_SL_ECS_PARANDO    ,1);
                CLP.WR(PC_HL_RTU_PARANDO    ,1);

                if ( ackparadaemerg == true ){
                       CLP.WR(PC_SL_ECS_MCPPRDNDOEMERG, 1);
                }

                Desacelerar->Enabled = true;
                Demanda->Enabled = false;
        }
        if ( rotacao <= 0 ){
                CLP.WR(PC_SL_ECS_PARANDO    ,0);
                CLP.WR(PC_HL_RTU_PARANDO    ,0);
                CLP.WR(PC_SL_ECS_PARADO     ,1);
                CLP.WR(PC_HL_RTU_PRDNORMAL  ,0);
                rotacao = 0;
                //CLP.WR( PC_SA_ECS_MCPRPM, rotacao );
                //CLP.WR( PC_HA_RTU_MCPRPM, rotacao);
                Desacelerar->Enabled = false;
                Parada->Enabled = false;

                if ( ackparadaemerg == true ){
                       CLP.WR(PC_SL_ECS_MCPPRDNDOEMERG, 0);
                       CLP.WR(PC_HL_RTU_PRDEMERG      , 1);
                }
        }

        contadorparada++;

        if( Parada->Enabled == false ){
                 contadorparada = 0;
                 ackpartida = false;
                 Demanda->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::DesacelerarTimer(TObject *Sender)
{
        rotacao = rotacao - 100;
        //CLP.WR( PC_SA_ECS_MCPRPM, rotacao );
        //CLP.WR( PC_HA_RTU_MCPRPM, rotacao);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnControlesClick(TObject *Sender)
{
/*
        frmControles->Parent = frmPrincipal;
        frmControles->Top = btnControles->Top + 10;
        frmControles->Left = btnControles->Left + 10;
        frmControles->Show();
*/
        if ( tempos_curtos == true ){
                tempos_curtos = false;
                lblConta->Font->Color = clBlack;
        }else{
                tempos_curtos = true;
                lblConta->Font->Color = clRed;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPartirClick(TObject *Sender)
{
        ackpartida = true;
        Parada->Enabled = false;
        Partida->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPararClick(TObject *Sender)
{
        ackparada = true;
        Partida->Enabled = false;
        Parada->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPrdEmergLocalClick(TObject *Sender)
{
        ackparadaemerg = true;
        Partida->Enabled = false;
        Parada->Enabled = true;
        if ( btnPrdEmergLocal->Caption == "Prd. Emerg." ) {
                btnPrdEmergLocal->Caption = "Rearmar";
                CLP.WR( PC_SL_ECS_MCPPRDEMERGPNL, 1);
                CLP.WR( PC_HL_RTU_PRDEMERG      , 1);
        }
        else{
                btnPrdEmergLocal->Caption = "Prd. Emerg.";
                CLP.WR( PC_SL_ECS_MCPPRDEMERGPNL, 0);
                CLP.WR( PC_HL_RTU_PRDEMERG      , 0);
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAcelerarLocalClick(TObject *Sender)
{
        int demanda = lblDemandaLocal->Caption.ToInt();
        demanda = demanda + 10;
        if (demanda > 1470){
                lblDemandaLocal->Font->Color = clRed;
        }
        else{
                lblDemandaLocal->Font->Color = clBlack;
        }
        if (demanda > 1490){
                demanda = 1490;
        }
        lblDemandaLocal->Caption = demanda;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnDesacelerarLocalClick(TObject *Sender)
{
        int demanda = lblDemandaLocal->Caption.ToInt();
        demanda = demanda - 20;
        if (demanda > 1470){
                lblDemandaLocal->Font->Color = clRed;
        }
        else{
                lblDemandaLocal->Font->Color = clBlack;
        }
        if (demanda < 0){
                demanda = 0;
        }
        lblDemandaLocal->Caption = demanda;

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
                shpAguarde->Top = 461;
                shpAguarde->Left = 3;
                //shpAguarde->Width = 657;
                //shpAguarde->Height = 49;
                shpAguarde->Visible = true;
                lblAguarde->Top = 0;
                lblAguarde->Left = 0;
                //lblAguarde->Width = 649;
                //lblAguarde->Height = 29;
                lblAguarde->Visible = true;
        }
        else{
                //if (lista < 10 ){
                //        tmrLeitura->Enabled = true;
                //}
                shpAguarde->Top = 5000;
                shpAguarde->Left = 5000;
                //shpAguarde->Width = 0;
                //shpAguarde->Height = 0;
                shpAguarde->Visible = false;
                lblAguarde->Top = 5000;
                lblAguarde->Left = 5000;
                //lblAguarde->Width = 0;
                //lblAguarde->Height = 0;
                lblAguarde->Visible = false;
        }

        /*shpAguarde->Top = 5000;
        shpAguarde->Left = 5000;
        shpAguarde->Width = 0;
        shpAguarde->Height = 0;
        shpAguarde->Visible = false;
        lblAguarde->Top = 5000;
        lblAguarde->Left = 5000;
        lblAguarde->Width = 0;
        lblAguarde->Height = 0;
        lblAguarde->Visible = false;*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnBBAOLEmRemotoClick(TObject *Sender)
{
        if ( btnBBAOLEmRemoto->Caption == "Em Local" ){
                CLP.WR(PC_SL_ECS_OLBBAREMLOC,  0);
        }
        else{
                CLP.WR(PC_SL_ECS_OLBBAREMLOC,  1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnBBAOLPCtrlClick(TObject *Sender)
{
        if ( btnBBAOLPCtrl->Caption == "Partir" ){
                CLP.WR(PC_SL_ECS_PRIMPUMPMCFUNC,  1);
                btnBBAOLPCtrl->Caption = "Parar";
                tmrPRIME->Enabled = true;
                primefunc = true;
        }
        else{
                CLP.WR(PC_SL_ECS_PRIMPUMPMCFUNC,  0);
                btnBBAOLPCtrl->Caption = "Partir";
                tmrPRIME->Enabled = true;
                primefunc = false;
        }
}
//---------------------------------------------------------------------------

/*void __fastcall TfrmPrincipal::btnELPNClick(TObject *Sender)
{
        frmBBAELPN->Parent = frmPrincipal;
        frmBBAELPN->Top = btnELPN->Top + 10;
        frmBBAELPN->Left = btnELPN->Left + 10;
        frmBBAELPN->Show();
}
//---------------------------------------------------------------------------*/

void __fastcall TfrmPrincipal::tmrEncherAFTimer(TObject *Sender)
{
        CLP.WR( PC_SL_ECS_AFENCHENDO       , 0);
        CLP.WR( PC_HL_RTU_AFENCHENDO       , 0);
        CLP.WR( PC_SL_ECS_AFCHEIO          , 1);
        CLP.WR( PC_HL_RTU_AFCHEIO          , 1);
        afcheio = true;
        tmrConta->Enabled = false;
        tmrEncherAF->Enabled = false;
        ackencher = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEncherAFClick(TObject *Sender)
{
        if ( tmrEncherAF->Enabled == false ) {
                tmrEsvaziarAF->Enabled = false;
                CLP.WR( PC_SL_ECS_AFESVAZIANDO     , 0);
                CLP.WR( PC_HL_RTU_AFESVAZIANDO     , 0);
                CLP.WR( PC_SL_ECS_AFCHEIO          , 0);
                CLP.WR( PC_HL_RTU_AFCHEIO          , 0);
                CLP.WR( PC_SL_ECS_AFVAZIO          , 0);
                CLP.WR( PC_HL_RTU_AFVAZIO          , 0);
                CLP.WR( PC_SL_ECS_AFENCHESVPRESSEN , 1);
                CLP.WR( PC_HL_RTU_AFENCHESVPREST   , 1);
                CLP.WR( PC_SL_ECS_AFENCHENDO       , 1);
                CLP.WR( PC_HL_RTU_AFENCHENDO       , 1);
                tmrEncherAF->Interval = tempoEncherAF;
                float tempo = (tmrEncherAF->Interval / 1000);
                lblEncher->Caption = FormatFloat( "##0.##", tempo) + "seg" ;
                lblConta->Caption = 0;
                tmrConta->Enabled = true;
                tmrEncherAF->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrEsvaziarAFTimer(TObject *Sender)
{
        CLP.WR( PC_SL_ECS_AFESVAZIANDO     , 0);
        CLP.WR( PC_HL_RTU_AFESVAZIANDO     , 0);
        CLP.WR( PC_SL_ECS_AFVAZIO          , 1);
        CLP.WR( PC_HL_RTU_AFVAZIO          , 1);
        afvazio = true;
        tmrConta->Enabled = false;
        tmrEsvaziarAF->Enabled = false;
        ackesvaziar = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEsvaziarAFClick(TObject *Sender)
{
        if ( tmrEsvaziarAF->Enabled == false ) {
                tmrEncherAF->Enabled = false;
                CLP.WR( PC_SL_ECS_AFENCHENDO       , 0);
                CLP.WR( PC_HL_RTU_AFENCHENDO       , 0);
                CLP.WR( PC_SL_ECS_AFVAZIO          , 0);
                CLP.WR( PC_HL_RTU_AFVAZIO          , 0);
                CLP.WR( PC_SL_ECS_AFCHEIO          , 0);
                CLP.WR( PC_HL_RTU_AFCHEIO          , 0);
                CLP.WR( PC_SL_ECS_AFENCHESVPRESSEN , 0);
                CLP.WR( PC_HL_RTU_AFENCHESVPREST   , 0);
                CLP.WR( PC_SL_ECS_AFESVAZIANDO     , 1);
                CLP.WR( PC_HL_RTU_AFESVAZIANDO     , 1);
                tmrEsvaziarAF->Interval = tempoEsvaziarAF;
                float tempo = (tmrEsvaziarAF->Interval / 1000);
                lblEsvaziar->Caption = FormatFloat( "##0.##", tempo) + "seg" ;
                lblConta->Caption = 0;
                tmrConta->Enabled = true;
                tmrEsvaziarAF->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrContaTimer(TObject *Sender)
{
        lblConta->Caption = lblConta->Caption.ToInt() + 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrBOTimer(TObject *Sender)
{
        if ( BOligar == true ){
                CLP.WR(PC_SL_ECS_OVERRIDEATIVO ,1);
                CLP.WR(PC_SL_ECS_OVERRIDELIG   ,1);
                CLP.WR(PC_HL_RTU_OVERRIDELIG   ,1);
                tmrBO->Enabled = false;
        }
        else{
                if ( BOdesligar == true ){
                        CLP.WR(PC_SL_ECS_OVERRIDEATIVO ,0);
                        CLP.WR(PC_SL_ECS_OVERRIDELIG   ,0);
                        CLP.WR(PC_HL_RTU_OVERRIDELIG   ,0);
                        tmrBO->Enabled = false;
                }

        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPreEncherAFTimer(TObject *Sender)
{
        CLP.WR( PC_SL_ECS_AFESVAZIANDO     , 0);
        CLP.WR( PC_HL_RTU_AFESVAZIANDO     , 0);
        CLP.WR( PC_SL_ECS_AFCHEIO          , 0);
        CLP.WR( PC_HL_RTU_AFCHEIO          , 0);
        CLP.WR( PC_SL_ECS_AFVAZIO          , 0);
        CLP.WR( PC_HL_RTU_AFVAZIO          , 0);
        CLP.WR( PC_SL_ECS_AFENCHESVPRESSEN , 1);
        CLP.WR( PC_HL_RTU_AFENCHESVPREST   , 1);
        CLP.WR( PC_SL_ECS_AFENCHENDO       , 1);
        CLP.WR( PC_HL_RTU_AFENCHENDO       , 1);
        tmrEncherAF->Interval = tempoEncherAF;
        float tempo = (tmrEncherAF->Interval / 1000);
        lblEncher->Caption = FormatFloat( "##0.##", tempo) + "seg" ;
        lblConta->Caption = 0;
        tmrConta->Enabled = true;
        tmrEncherAF->Enabled = true;
        tmrPreEncherAF->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrPreEsvaziarAFTimer(TObject *Sender)
{
        CLP.WR( PC_SL_ECS_AFENCHENDO       , 0);
        CLP.WR( PC_HL_RTU_AFENCHENDO       , 0);
        CLP.WR( PC_SL_ECS_AFVAZIO          , 0);
        CLP.WR( PC_HL_RTU_AFVAZIO          , 0);
        CLP.WR( PC_SL_ECS_AFCHEIO          , 0);
        CLP.WR( PC_HL_RTU_AFCHEIO          , 0);
        CLP.WR( PC_SL_ECS_AFENCHESVPRESSEN , 0);
        CLP.WR( PC_HL_RTU_AFENCHESVPREST   , 0);
        CLP.WR( PC_SL_ECS_AFESVAZIANDO     , 1);
        CLP.WR( PC_HL_RTU_AFESVAZIANDO     , 1);
        tmrEsvaziarAF->Interval = tempoEsvaziarAF;
        float tempo = (tmrEsvaziarAF->Interval / 1000);
        lblEsvaziar->Caption = FormatFloat( "##0.##", tempo) + "seg" ;
        lblConta->Caption = 0;
        tmrConta->Enabled = true;
        tmrEsvaziarAF->Enabled = true;
        tmrPreEsvaziarAF->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrReconectaTimer(TObject *Sender)
{
        //RECONEXÃO
        CLP.Open(IP);
        tmrReconecta->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEmRemotoClick(TObject *Sender)
{
        if ( btnEmRemoto->Caption == "Em Local" ){
                CLP.WR(PC_SL_ECS_EMLOCAL,  0);
                CLP.WR(PC_HL_RTU_EMLOCAL,  0);
                CLP.WR(PC_SL_ECS_EMREMOTO, 1);
                CLP.WR(PC_HL_RTU_EMREMOTO, 1);
                //btnEmRemoto->Caption = "Em Remoto";
                btnPartir->Enabled = false;
                btnParar->Enabled = false;
                emlocal = false;
        }
        else{
                CLP.WR(PC_SL_ECS_EMREMOTO, 0);
                CLP.WR(PC_HL_RTU_EMREMOTO, 0);
                CLP.WR(PC_SL_ECS_EMLOCAL,  1);
                CLP.WR(PC_HL_RTU_EMLOCAL,  1);
                //btnEmRemoto->Caption = "Em Local";
                btnPartir->Enabled = true;
                btnParar->Enabled = true;
                emlocal = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnBatOverClick(TObject *Sender)
{
        if ( btnBatOver->Caption == "B. O. Des." ){
                CLP.WR(PC_SL_ECS_OVERRIDEATIVO, 1);
                CLP.WR(PC_SL_ECS_OVERRIDELIG  , 1);
                CLP.WR(PC_HL_RTU_OVERRIDELIG  , 1);
                //btnBatOver->Caption = "B. O. Lig.";
        }
        else{
                CLP.WR(PC_SL_ECS_OVERRIDEATIVO, 0);
                CLP.WR(PC_SL_ECS_OVERRIDELIG  , 0);
                CLP.WR(PC_HL_RTU_OVERRIDELIG  , 0);
                //btnBatOver->Caption = "B. O. Des.";
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::btnCREMClick(TObject *Sender)
{
        bool TestaDouble = false;
        double Teste;

        try{
                Teste = txtCREM->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
        }

        if ( TestaDouble == false ){
                CLP.WR(PC_SA_ECS_POSICREMALPRINC, txtCREM->Text.ToDouble());
                CLP.WR(PC_SA_ECS_POSICREMALSEC  , txtCREM->Text.ToDouble());
                CLP.WR(PC_SA_ECS_COMBCREMALPOS  , txtCREM->Text.ToDouble());
                CLP.WR(PC_HA_RTU_POSICREMAL     , txtCREM->Text.ToDouble());
                CREMALHEIRA = txtCREM->Text.ToDouble();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnDBRClick(TObject *Sender)
{
        bool TestaDouble = false;
        double Teste;

        try{
                Teste = txtDBR->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
        }

        if ( TestaDouble == false ){
                CLP.WR(PC_SA_ECS_DBRATUAL, txtDBR->Text.ToDouble());
                DBR = txtDBR->Text.ToDouble();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMCRClick(TObject *Sender)
{
        bool TestaDouble = false;
        double Teste;

        try{
                Teste = txtMCR->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
        }

        if ( TestaDouble == false ){
                CLP.WR(PC_SA_ECS_MCRATUAL, txtMCR->Text.ToDouble());
                MCR = txtMCR->Text.ToDouble();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCARGAClick(TObject *Sender)
{
        bool TestaDouble = false;
        double Teste;

        try{
                Teste = txtCARGA->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
        }

        if ( TestaDouble == false ){
                CLP.WR(PC_SA_ECS_CARGA, txtCARGA->Text.ToDouble());
                CLP.WR(PC_HA_RTU_CARGAMCP  , txtCARGA->Text.ToDouble());
                CARGA = txtCARGA->Text.ToDouble();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInibirCMD_PRIMEClick(TObject *Sender)
{
        if ( inibir_cmd_prime == false ) {
                cmdInibirCMD_PRIME->Caption = "Inibir Comando Lig";
                inibir_cmd_prime = true;
        }else{
                cmdInibirCMD_PRIME->Caption = "Inibir Comando Des";
                inibir_cmd_prime = false;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cmdInibirPRESS_PRIMEClick(TObject *Sender)
{
        if ( inibir_pre_prime == false )  {
                cmdInibirPRESS_PRIME->Caption = "Inibir Pressão Lig";
                inibir_pre_prime = true;
        }else{
                cmdInibirPRESS_PRIME->Caption = "Inibir Pressão Des";
                inibir_pre_prime = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnInterlocksOKPartirClick(TObject *Sender)
{
        if ( ativa_piscar == false ){
                btnInterlocksOKPartir->Caption = "Piscar Ativo";
                ativa_piscar = true;
                piscar = false;
        }else{
                btnInterlocksOKPartir->Caption = "Piscar Inativo";
                ativa_piscar = false;
                piscar = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEscolhePassoClick(TObject *Sender)
{
        if (btnEscolhePasso->Caption == "PASSO SIMUL."){
                USAR_PASSO_REAL = true;
                btnEscolhePasso->Caption = "PASSO REAL";
                CLP.WR(PASSO_OPTO, 0);
        }else{
                USAR_PASSO_REAL = false;
                btnEscolhePasso->Caption = "PASSO SIMUL.";
                CLP.WR(PASSO_OPTO, 1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        CLP.Close();
        while (CLP.conectado != 0){};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrPRIMETimer(TObject *Sender)
{
  //PRESSURIZAÇÃO DO ÓLEO PELA PRIME
  olpressantfi = CLP.RD(PC_SA_ECS_OLPRESSANTFI);
  olpressdepfi = CLP.RD(PC_SA_ECS_OLPRESSDEPFI);
  olpressresfr = CLP.RD(PC_SA_ECS_OLRESFPRESS);
  //if (CLP.TamBufWR() < 5){
        if ( olpressantfi < 3.4 && (primefunc == true || mcpvirando == true)){
                olpressantfi = olpressantfi + 0.4;
        }
        if ( olpressantfi > 0 && primefunc == false && mcpvirando == false){
                olpressantfi = olpressantfi - 0.10;
                if (olpressantfi <= 0 ){
                        olpressantfi = 0;
                        tmrPRIME->Enabled = false;
                }
        }
        if ( olpressantfi < 0.32 ) {
                if (CLP.RD(PC_SL_ECS_OLPRESSPARTMCPOK) != 0){
                        CLP.WR(PC_SL_ECS_OLPRESSPARTMCPOK, 0);
                }
                if (CLP.RD(PC_SL_ECS_INTPRELUBOK) != 1){
                        CLP.WR(PC_SL_ECS_INTPRELUBOK     , 1);
                }
                if (CLP.RD(PC_SL_ECS_MCPPRTINTERLOCOK) != 0){
                        CLP.WR(PC_SL_ECS_MCPPRTINTERLOCOK, 0);
                }
        }
        else{
                if (CLP.RD(PC_SL_ECS_INTPRELUBOK) != 0){
                        CLP.WR(PC_SL_ECS_INTPRELUBOK     , 0);
                }
                if (  olpressantfi >= 0.8 ){
                        if ( ativa_piscar == false ){
                                if (CLP.RD(PC_SL_ECS_MCPPRTINTERLOCOK) != 1){
                                        CLP.WR(PC_SL_ECS_MCPPRTINTERLOCOK, 1);
                                }
                        }
                        else{
                                if ( ativa_piscar == true ){
                                        if ( piscar == true ){
                                                CLP.WR(PC_SL_ECS_MCPPRTINTERLOCOK, 1);
                                                piscar = false;
                                        }else{
                                                CLP.WR(PC_SL_ECS_MCPPRTINTERLOCOK, 0);
                                                piscar = true;
                                        }
                                }
                        }
                        if (CLP.RD(PC_SL_ECS_OLPRESSPARTMCPOK) != 1){
                                CLP.WR(PC_SL_ECS_OLPRESSPARTMCPOK, 1);
                        }
                }
        };

        olpressdepfi = olpressantfi;
        olpressresfr = olpressantfi;


        /*//if (CLP.RD(PC_SA_ECS_OLPRESSANTFI) != olpressdepfi){
        if ( FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_OLPRESSANTFI)) != FormatFloat( "##0.##", olpressdepfi)){
                CLP.WR(PC_SA_ECS_OLPRESSANTFI, olpressantfi);
        	CLP.WR(PC_SA_ECS_OLPRESSDEPFI, olpressdepfi);
                CLP.WR(PC_SA_ECS_OLRESFPRESS,  olpressresfr);
        } */
  //}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrCtrlCargaTimer(TObject *Sender)
{
  //LEITURA PASSO E CONTROLE DE CARGA
        if (USAR_PASSO_REAL == true){
                PASSO_SIST = CLP.RD(PASSO_REAL);
                if ((PASSO_SIST >= PASSO___X1 && PASSO_SIST <= PASSO___X2) || (PASSO_SIST <  PASSO___X1)){
                        PASSO_CARG = (((PASSO_SIST - PASSO___X1)*(PASSO___Y2 - PASSO___Y1))/(PASSO___X2 - PASSO___X1)) +  PASSO___Y1;
                }else{
                        if((PASSO_SIST >= PASSO___X2 && PASSO_SIST <= PASSO___X3) || (PASSO_SIST >  PASSO___X3)){
                                PASSO_CARG = (((PASSO_SIST - PASSO___X2)*(PASSO___Y3 - PASSO___Y2))/(PASSO___X3 - PASSO___X2)) +  PASSO___Y2;
                        }
                }
        }else{
                PASSO_CARG = CLP.RD(PASSO_SIML);
        }

        lblPasso->Caption = FormatFloat( "##0.##", PASSO_CARG);
        frmControles->lblPasso->Caption = FormatFloat( "##0.##", PASSO_CARG);
        frmControlesNovo->lblPasso->Caption = FormatFloat( "##0.##", PASSO_CARG);

        //CALCULO CARGA DINAMICA

        if ( afcheio == true && rotacao > 0){
                if ( rotacao < 1400 ){
                        if ( rotacao >= CARGA_RPM_1 && rotacao <  CARGA_RPM_2){
                                if ( fabs(PASSO_CARG) <= CARGA_PAS_1){
                                         MCR  = CGMCR1_RPM1;
                                        CARGA = CARGA1_RPM1;
                                }else{
                                  if (fabs(PASSO_CARG) >= CARGA_PAS_1 && fabs(PASSO_CARG) < CARGA_PAS_2){
                                          CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_1 )*( CARGA2_RPM1 - CARGA1_RPM1))/(CARGA_PAS_2 - CARGA_PAS_1)) + (CARGA1_RPM1);
                                          MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_1 )*( CGMCR2_RPM1 - CGMCR1_RPM1))/(CARGA_PAS_2 - CARGA_PAS_1)) + (CGMCR1_RPM1);
                                  }else{
                                    if (fabs(PASSO_CARG) >= CARGA_PAS_2 && fabs(PASSO_CARG) < CARGA_PAS_3){
                                            CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_2 )*( CARGA3_RPM1 - CARGA2_RPM1))/(CARGA_PAS_3 - CARGA_PAS_2)) + (CARGA2_RPM1);
                                            MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_2 )*( CGMCR3_RPM1 - CGMCR2_RPM1))/(CARGA_PAS_3 - CARGA_PAS_2)) + (CGMCR2_RPM1);
                                    }else{
                                      if (fabs(PASSO_CARG) >= CARGA_PAS_3 && fabs(PASSO_CARG) < CARGA_PAS_4){
                                              CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_3 )*( CARGA4_RPM1 - CARGA3_RPM1))/(CARGA_PAS_4 - CARGA_PAS_3)) + (CARGA3_RPM1);
                                              MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_3 )*( CGMCR4_RPM1 - CGMCR3_RPM1))/(CARGA_PAS_4 - CARGA_PAS_3)) + (CGMCR3_RPM1);
                                    }
                                  }
                                }}
                                if (MCR > CGMCR4_RPM1) {
                                        MCR = CGMCR4_RPM1;
                                }
                                if (MCR < CGMCR1_RPM1){
                                        MCR = CGMCR1_RPM1;
                                }
                                if(CARGA < CARGA1_RPM1){
                                        CARGA = CARGA1_RPM1;
                                }
                        }
                        if ( rotacao >= CARGA_RPM_2 && rotacao <  CARGA_RPM_3 ){
                                if ( fabs(PASSO_CARG) <= CARGA_PAS_1){
                                         MCR  = CGMCR1_RPM2;
                                        CARGA = CARGA1_RPM2;
                                }else{
                                  if (fabs(PASSO_CARG) >= CARGA_PAS_1 && fabs(PASSO_CARG) < CARGA_PAS_2){
                                          CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_1 )*( CARGA2_RPM2 - CARGA1_RPM2))/(CARGA_PAS_2 - CARGA_PAS_1)) + (CARGA1_RPM2);
                                          MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_1 )*( CGMCR2_RPM2 - CGMCR1_RPM2))/(CARGA_PAS_2 - CARGA_PAS_1)) + (CGMCR1_RPM2);
                                  }else{
                                    if (fabs(PASSO_CARG) >= CARGA_PAS_2 && fabs(PASSO_CARG) < CARGA_PAS_3){
                                            CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_2 )*( CARGA3_RPM2 - CARGA2_RPM2))/(CARGA_PAS_3 - CARGA_PAS_2)) + (CARGA2_RPM2);
                                            MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_2 )*( CGMCR3_RPM2 - CGMCR2_RPM2))/(CARGA_PAS_3 - CARGA_PAS_2)) + (CGMCR2_RPM2);
                                    }else{
                                      if (fabs(PASSO_CARG) >= CARGA_PAS_3 && fabs(PASSO_CARG) < CARGA_PAS_4){
                                              CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_3 )*( CARGA4_RPM2 - CARGA3_RPM2))/(CARGA_PAS_4 - CARGA_PAS_3)) + (CARGA3_RPM2);
                                              MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_3 )*( CGMCR4_RPM2 - CGMCR3_RPM2))/(CARGA_PAS_4 - CARGA_PAS_3)) + (CGMCR3_RPM2);
                                    }
                                  }
                                }}
                                if (MCR > CGMCR4_RPM2) {
                                        MCR = CGMCR4_RPM2;
                                }
                                if (MCR < CGMCR1_RPM2){
                                        MCR = CGMCR1_RPM2;
                                }
                                if(CARGA < CARGA1_RPM2){
                                        CARGA = CARGA1_RPM2;
                                }
                        }
                        if ( rotacao >= CARGA_RPM_3 ){
                                if ( fabs(PASSO_CARG) <= CARGA_PAS_1){
                                         MCR  = CGMCR1_RPM3;
                                        CARGA = CARGA1_RPM3;
                                }else{
                                  if (fabs(PASSO_CARG) >= CARGA_PAS_1 && fabs(PASSO_CARG) < CARGA_PAS_2){
                                          CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_1 )*( CARGA2_RPM3 - CARGA1_RPM3))/(CARGA_PAS_2 - CARGA_PAS_1)) + (CARGA1_RPM3);
                                          MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_1 )*( CGMCR2_RPM3 - CGMCR1_RPM3))/(CARGA_PAS_2 - CARGA_PAS_1)) + (CGMCR1_RPM3);
                                  }else{
                                    if (fabs(PASSO_CARG) >= CARGA_PAS_2 && fabs(PASSO_CARG) < CARGA_PAS_3){
                                            CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_2 )*( CARGA3_RPM3 - CARGA2_RPM3))/(CARGA_PAS_3 - CARGA_PAS_2)) + (CARGA2_RPM3);
                                            MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_2 )*( CGMCR3_RPM3 - CGMCR2_RPM3))/(CARGA_PAS_3 - CARGA_PAS_2)) + (CGMCR2_RPM3);
                                    }else{
                                      if (fabs(PASSO_CARG) >= CARGA_PAS_3 && fabs(PASSO_CARG) < CARGA_PAS_4){
                                              CARGA = ((( fabs(PASSO_CARG) - CARGA_PAS_3 )*( CARGA4_RPM3 - CARGA3_RPM3))/(CARGA_PAS_4 - CARGA_PAS_3)) + (CARGA3_RPM3);
                                              MCR   = ((( fabs(PASSO_CARG) - CARGA_PAS_3 )*( CGMCR4_RPM3 - CGMCR3_RPM3))/(CARGA_PAS_4 - CARGA_PAS_3)) + (CGMCR3_RPM3);
                                    }
                                  }
                                }}
                                if (MCR > CGMCR4_RPM3) {
                                        MCR = CGMCR4_RPM3;
                                }
                                if (MCR < CGMCR1_RPM3){
                                        MCR = CGMCR1_RPM3;
                                }
                                if(CARGA < CARGA1_RPM3){
                                        CARGA = CARGA1_RPM3;
                                }
                        }
                }
                if ( rotacao >= 1400 ) {
                        if ((int) PASSO_CARG >= 0){
                                if (PASSO_CARG <= Y_LOAD_2 && PASSO_CARG >= Y_LOAD_1){
                                        CARGA = ((( PASSO_CARG - Y_LOAD_1 )*( X_LOAD_2 - (X_LOAD_1)))/(Y_LOAD_2 - Y_LOAD_1)) + (X_LOAD_1);
                                        MCR = ((( fabs(PASSO_CARG) - Y_LOAD_1 )*( CGMCR2_RPM3 - CGMCR1_RPM3))/(Y_LOAD_2 - Y_LOAD_1)) + (CGMCR1_RPM3);
                                        if (MCR < CGMCR1_RPM3){
                                                MCR = CGMCR1_RPM3;
                                        }
                                }else{
                                        if ( PASSO_CARG > Y_LOAD_2 &&  PASSO_CARG <= Y_LOAD_3){
                                                CARGA = ((( PASSO_CARG - Y_LOAD_2 )*( X_LOAD_3 - (X_LOAD_2)))/(Y_LOAD_3 - Y_LOAD_2)) + (X_LOAD_2);
                                                MCR = ((( fabs(PASSO_CARG) - Y_LOAD_2 )*( CGMCR3_RPM3 - CGMCR2_RPM3))/(Y_LOAD_3 - Y_LOAD_2)) + (CGMCR2_RPM3);
                                                if (MCR < CGMCR2_RPM3){
                                                        MCR = CGMCR2_RPM3;
                                                }
                                        }else{
                                                if ( PASSO_CARG > Y_LOAD_3){
                                                        CARGA = ((( PASSO_CARG - Y_LOAD_3 )*( X_LOAD_4 - (X_LOAD_3)))/(Y_LOAD_4 - Y_LOAD_3)) + (X_LOAD_3);
                                                        MCR = CGMCR4_RPM3;
                                                }
                                        }
                                }
                       }else{
                                if ((int) PASSO_CARG <= 0){
                                       if ( PASSO_CARG >= ((-1)* Y_LOAD_2) &&  PASSO_CARG <= Y_LOAD_1){
                                                CARGA = ((( PASSO_CARG - Y_LOAD_1 )*( X_LOAD_2 - (X_LOAD_1)))/((-1*Y_LOAD_2) - Y_LOAD_1)) + (X_LOAD_1);
                                                MCR = ((( fabs(PASSO_CARG) - Y_LOAD_1 )*( CGMCR2_RPM3 - CGMCR1_RPM3))/(Y_LOAD_2 - Y_LOAD_1)) + (CGMCR1_RPM3);
                                                if (MCR < CGMCR1_RPM3){
                                                        MCR = CGMCR1_RPM3;
                                                }
                                        }else{
                                                if ( PASSO_CARG < ((-1)* Y_LOAD_2) &&  PASSO_CARG >= ((-1)* Y_LOAD_3)){
                                                       CARGA = ((( PASSO_CARG - ((-1)*Y_LOAD_2))*(X_LOAD_3 - X_LOAD_2))/(((-1)*Y_LOAD_3)-((-1)*Y_LOAD_2))) + X_LOAD_2;
                                                       MCR = ((( fabs(PASSO_CARG) - Y_LOAD_2 )*( CGMCR3_RPM3 - CGMCR2_RPM3))/(Y_LOAD_3 - Y_LOAD_2)) + (CGMCR2_RPM3);
                                                        if (MCR < CGMCR2_RPM3){
                                                                MCR = CGMCR2_RPM3;
                                                        }
                                                }else{
                                                        if ( PASSO_CARG < ((-1)* Y_LOAD_3)){
                                                                CARGA = ((( PASSO_CARG - (((-1)* Y_LOAD_3)) )*( X_LOAD_4 - (X_LOAD_3)))/((((-1)* Y_LOAD_4)) - ((((-1)* Y_LOAD_3))))) + (X_LOAD_3);
                                                                MCR = CGMCR4_RPM3;
                                                        }
                                                }
                                        }
                               }
                       }
                       if (MCR > 100) {
                               MCR = 100;
                       }

                }/*else{
                        CARGA = (X_LOAD_1);
                }*/
                lblCARGA_CALCULADA->Caption = FormatFloat( "##0.#", CARGA);
                frmControles->lblCARGA_CALCULADA->Caption = FormatFloat( "##0.#", CARGA);
                frmControlesNovo->lblCARGA_CALCULADA->Caption = FormatFloat( "##0.#", CARGA);
                if ( FormatFloat( "##0.#",PASSO_CARG) == FormatFloat( "##0.#",PASSO_ANTIGO)){
                        if ( Habilitar_Caturro == true ){
                                if ( VARIA_CARGA == true ){
                                        CARGA = CARGA + TOLER_CATURRO;
                                        VARIA_CARGA = false;
                                }else{
                                        //CARGA = CARGA - TOLER_CATURRO;
                                        VARIA_CARGA = true;
                                }
                        }else{
                                VARIA_CARGA = true;
                        }
                }
                //if ( CLP.RD(PC_SA_ECS_CARGA) != CARGA){
                /*if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_CARGA)) != FormatFloat( "##0.#", CARGA)){
                        if (CLP.TamBufWR() <= 9){
                                CLP.WR(PC_SA_ECS_CARGA     , CARGA);
                                CLP.WR(PC_HA_RTU_CARGAMCP  , CARGA);
                        }
                }*/
                CREMALHEIRA = MCR + CARGA;
                /*
                //if ( CLP.RD(PC_SA_ECS_POSICREMALPRINC) != CREMALHEIRA){
                if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_POSICREMALPRINC)) != FormatFloat( "##0.#", CREMALHEIRA)){
                        if (CLP.TamBufWR() <= 9){
                                CLP.WR(PC_SA_ECS_POSICREMALPRINC, CREMALHEIRA);
                                CLP.WR(PC_SA_ECS_POSICREMALSEC  , CREMALHEIRA);
                                CLP.WR(PC_SA_ECS_COMBCREMALPOS  , CREMALHEIRA);
                                CLP.WR(PC_HA_RTU_POSICREMAL     , CREMALHEIRA);
                        }
                }
                if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_MCRATUAL)) != FormatFloat( "##0.#", MCR)){
                        if (CLP.TamBufWR() <= 9){
                                CLP.WR(PC_SA_ECS_MCRATUAL, MCR);
                        }
                }*/
                if (MCR + 10 > 100){
                        DBR = 100;
                }else{
                        DBR = MCR + 10;
                }
                /*
                if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_DBRATUAL)) != FormatFloat( "##0.#", DBR)){
                        if (CLP.TamBufWR() <= 9){
                                CLP.WR(PC_SA_ECS_DBRATUAL, DBR );
                        }
                }   */
        }
        PASSO_ANTIGO = PASSO_CARG;
        /*//CARGAS
        lblCREM1->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_POSICREMALPRINC));
        lblCREM2->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_POSICREMALSEC));
        lblCREM3->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_COMBCREMALPOS));
        lblCREM4->Caption = FormatFloat( "##0.##", CLP.RD(PC_HA_RTU_POSICREMAL));
        frmControles->lblCREMMCP->Caption = lblCREM1->Caption;
        lblDBR->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_DBRATUAL));
        lblMCR->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_MCRATUAL));
        frmControles->lblMCRMCP->Caption = lblMCR->Caption;
        lblCARGA1->Caption = FormatFloat( "##0.##", CLP.RD(PC_SA_ECS_CARGA));
        lblCARGA2->Caption = FormatFloat( "##0.##", CLP.RD(PC_HA_RTU_CARGAMCP));*/

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::DemandaTimer(TObject *Sender)
{

   //RESPOSTA DA DEMANDA DE ROTAÇÃO (APENAS CÁLCULO)
   //demanda_et1 = CLP.RD(CP_SA_ECS_DEMANDARPMETH1);
   //demanda_et2 = CLP.RD(CP_SA_ECS_DEMANDARPMETH2);
   //demanda_hdw = CLP.RD(CP_HA_RTU_DEMANDARPMHDW );
   //if (CLP.TamBufWR() < 10){
        if ( emlocal == false ){
                if ( (demanda_et1 >= rotacaoinicial || demanda_et2 >= rotacaoinicial || demanda_hdw >= rotacaoinicial) ){
                        if ( demanda_et1 < demanda_et2 ){
                                demanda = demanda_et2;
                        }
                        else{
                                demanda = demanda_et1;
                        }
                        if ( demanda < demanda_hdw ){
                                demanda = demanda_hdw;
                        }
                }
        }
        else{
                demanda = lblDemandaLocal->Caption.ToDouble();
        }
        if ((mcpvirando == true && demanda >= rotacaoinicial) || rotacao >= rotacaoinicial) {
                if ( (int) rotacao < (int) demanda ){
                        if ( (int) rotacao  > (int) demanda * 0.9 ) {
                                if ( (int) demanda - (int) rotacao < 5 ){
                                        rotacao = rotacao + 1;
                                }else{
					rotacao = rotacao + 5;
				}
                        }
                        else{
                                rotacao = rotacao + 25;
                        }
                }
                if ( (int) rotacao > (int) demanda ){
                        if ( (int) rotacao < (int) demanda * 0.9 ) {
				if ( (int) rotacao - (int) demanda < 5 ){
					rotacao = rotacao - 1;
				}else{
					rotacao = rotacao - 5;
				}
                        }
                        else{
                                rotacao = rotacao - 100;
                        }
                }

                //CLP.WR( PC_SA_ECS_MCPRPM, rotacao );
                //CLP.WR( PC_HA_RTU_MCPRPM, rotacao);

        }else{
                if (mcpvirando == false && Acelerar->Enabled == false && Desacelerar->Enabled == false){
                        rotacao = 0;
                }
        }
   //}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCargaDinamicaClick(TObject *Sender)
{
        //frmControles->Parent = frmPrincipal;
        //frmControles->Top = frmPrincipal->Top + 10;
        //frmControles->Left = frmPrincipal->Left + 10;
        //frmControles->ShowModal();

        frmControlesNovo->Top = frmPrincipal->Top + 0;
        frmControlesNovo->Left = frmPrincipal->Left + 0;
        frmControlesNovo->ShowModal();


}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnHabilitaCaturroClick(TObject *Sender)
{
        if ( Habilitar_Caturro == false ){
                btnHabilitaCaturro->Caption = "Caturro Lig.";
                Habilitar_Caturro = true;
        }else{
                btnHabilitaCaturro->Caption = "Caturro Des.";
                Habilitar_Caturro = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnTolerCaturroClick(TObject *Sender)
{
        TOLER_CATURRO = txtTolerCaturro->Text.ToDouble();
        lblTolerCaturro->Caption = FormatFloat( "##0.##", TOLER_CATURRO );
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::btnStatusClick(TObject *Sender)
{
   pnlStatus->Visible = true;
   pnlCTRL->Visible = false;
   pnlPrime->Visible = false;
   pnlAF->Visible = false;
   pnlLocal->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnPrimeClick(TObject *Sender)
{
   pnlStatus->Visible = false;
   pnlCTRL->Visible = false;
   pnlPrime->Visible = true;
   pnlAF->Visible = false;
   pnlLocal->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAFClick(TObject *Sender)
{
   pnlStatus->Visible = false;
   pnlCTRL->Visible = false;
   pnlPrime->Visible = false;
   pnlAF->Visible = true;
   pnlLocal->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnCtrlClick(TObject *Sender)
{
   pnlStatus->Visible = false;
   pnlCTRL->Visible = true;
   pnlPrime->Visible = false;
   pnlAF->Visible = false;
   pnlLocal->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnLocalClick(TObject *Sender)
{
   pnlStatus->Visible = false;
   pnlCTRL->Visible = false;
   pnlPrime->Visible = false;
   pnlAF->Visible = false;
   pnlLocal->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFecharClick(TObject *Sender)
{
   frmPrincipal->Close();   
}
//---------------------------------------------------------------------------


