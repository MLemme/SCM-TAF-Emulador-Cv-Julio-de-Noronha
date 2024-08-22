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
//MÓDULO...........: MCP BE
//DATA DE INÍCIO...: 29.09.2015
//DATA DE PROTÓTIPO: 28.08.2016
//DATA DE TÉRMINO..: 15.08.2017
//DATA DE ATUALIZ..: 29.11.2017
//                   26.01.2018
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
String PC_SL_ECS_AFENCHESVPRESSEN         = "%MW7000.14";
String PC_SL_ECS_QQALARMEREC              = "%MW7000.15";
String PC_SL_ECS_MECEMSERV                = "%MW7001.0";
String PC_SL_ECS_STDBYMECEMSERV           = "%MW7001.1";
String PC_SL_ECS_EXBLOPCARTATIVO          = "%MW7001.2";
String PC_SL_ECS_EXBLOCAFENATIVO          = "%MW7001.3";
String PC_SL_ECS_BUZLIGADA                = "%MW7001.4";
String PC_SL_ECS_QQALARME                 = "%MW7001.5";
String PC_SL_ECS_MCPOKOPERAR              = "%MW7001.6";
String PC_SL_ECS_EMLOCAL                  = "%MW7001.7";
String PC_SL_ECS_EMREMOTO                 = "%MW7001.8";
String PC_SL_ECS_PRIMPUMPMCFUNC           = "%MW7001.9";
String PC_SL_ECS_OLPRESSPARTMCPOK         = "%MW7001.10";
String PC_SL_ECS_MCPVIRANDO               = "%MW7001.12";
String PC_SL_ECS_PARTINDO                 = "%MW7001.13";
String PC_SL_ECS_PARANDO                  = "%MW7001.14";
String PC_SL_ECS_PARADO                   = "%MW7001.15";
String PC_SL_ECS_MCPPRDEMERG1NET          = "%MW7002.0";
String PC_SL_ECS_ENFORNPRTVALLIG          = "%MW7002.1";
String PC_SL_ECS_FLAPAABERTO              = "%MW7002.2";
String PC_SL_ECS_FLAPBABERTO              = "%MW7002.3";
String PC_SL_ECS_FLAPAFECHANDO            = "%MW7002.4";
String PC_SL_ECS_FLAPBFECHANDO            = "%MW7002.5";
String PC_SL_ECS_AFCHEIO                  = "%MW7002.6";
String PC_SL_ECS_AFVAZIO                  = "%MW7002.7";
String PC_SL_ECS_OVERRIDELIG              = "%MW7002.8";
String PC_SL_ECS_AFENCHENDO               = "%MW7002.9";
String PC_SL_ECS_AFESVAZIANDO             = "%MW7002.10";
String PC_SL_ECS_SEQPTDABORT              = "%MW7002.11";
String PC_SL_ECS_MCPPRTINTERLOCOK         = "%MW7002.12";
String PC_SL_ECS_AFENCHINTERLOCOK         = "%MW7002.13";
String PC_SL_ECS_MCPPRTDOK                = "%MW7002.14";
String PC_SL_ECS_AFENCHEROK               = "%MW7002.15";
String PC_SL_ECS_AFESVINTERLOCOK          = "%MW7003.0";
String PC_SL_ECS_PREAQUCOCDEC             = "%MW7005.13";
String PC_SL_ECS_OLBBAREMLOC              = "%MW7005.14";
String PC_SL_ECS_OLBBAAUTOMAN             = "%MW7005.15";
String PC_SL_ECS_OLBBASOBREC              = "%MW7006.0";
String PC_SL_ECS_REMCTRLHDW               = "%MW7024.7";
String PC_SL_ECS_REMCTRLAUTO              = "%MW7024.8";
String PC_SL_ECS_MCPEXECMAGELIS           = "%MW7024.14";
String PC_SL_ECS_MCPPRDNDOEMERG           = "%MW7025.14";
String PC_SL_ECS_PREAQAUTOMODO            = "%MW7025.15";
String PC_SL_ECS_PREAQMANUALMODO          = "%MW7026.0";
String PC_SL_ECS_VELCTRLVEL               = "%MW7026.6";
String PC_SL_ECS_VELPRTDALIMITE           = "%MW7026.7";
String PC_SL_ECS_VELMAXLIMITE             = "%MW7026.8";
String PC_SL_ECS_VELCOMBLIMITE            = "%MW7026.9";
String PC_SL_ECS_VELTORQUELIMITE          = "%MW7026.10";
String PC_SL_ECS_VELHABVELREF             = "%MW7026.11";
String PC_SL_ECS_VELDINAJSEMCARGA         = "%MW7026.12";
String PC_SL_ECS_UACPSFPRONTO             = "%MW7027.10";
String PC_SL_ECS_UACPSIPRONTO             = "%MW7027.11";
String PC_SL_ECS_UACREDUNCOK              = "%MW7027.12";
String PC_SL_ECS_MCPRPMALINHADA           = "%MW7029.0";
String PC_SL_ECS_PSWAFENCHENDO            = "%MW7029.1";
String PC_SL_ECS_PSWAFESVAZIANDO          = "%MW7029.2";
String PC_SL_ECS_POLANTFIFLSEN            = "%MW7032.0";
String PC_SL_ECS_POLANTFIBXSEN            = "%MW7032.1";
String PC_SL_ECS_POLANTFIMBXSEN           = "%MW7032.2";
String PC_SL_ECS_POLDEPFIFLSEN            = "%MW7032.3";
String PC_SL_ECS_POLDEPFIBXSEN            = "%MW7032.4";
String PC_SL_ECS_POLDEPFIMBXSEN           = "%MW7032.5";
String PC_SL_ECS_OLRESFPBX                = "%MW7032.6";
String PC_SL_ECS_OLRESFPMBX               = "%MW7032.7";
String PC_SL_ECS_OLRESFPFLSEN             = "%MW7032.8";
String PC_SL_ECS_PENTFIODFLSEN            = "%MW7032.9";
String PC_SL_ECS_PODAPOFIFLSEN            = "%MW7032.12";
String PC_SL_ECS_PODAPOFIBX               = "%MW7032.13";
String PC_SL_ECS_ODAPOFIPBX               = "%MW7032.14";
String PC_SL_ECS_PADBX                    = "%MW7032.15";
String PC_SL_ECS_PADMBX                   = "%MW7033.0";
String PC_SL_ECS_PADFLSEN                 = "%MW7033.1";
String PC_SL_ECS_ASPBX                    = "%MW7033.2";
String PC_SL_ECS_ASPMBX                   = "%MW7033.3";
String PC_SL_ECS_PASFLSEN                 = "%MW7033.4";
String PC_SL_ECS_ARPTDPBX                 = "%MW7033.5";
String PC_SL_ECS_ARPTDPMBX                = "%MW7033.6";
String PC_SL_ECS_ARPTDPBXFLPTD            = "%MW7033.7";
String PC_SL_ECS_PARCARGAMALBA            = "%MW7033.8";
String PC_SL_ECS_PARCARGAALBA             = "%MW7033.9";
String PC_SL_ECS_PARCARGAFLSENBA          = "%MW7033.10";
String PC_SL_ECS_PARCARGAMALBB            = "%MW7033.11";
String PC_SL_ECS_PARCARGAALBB             = "%MW7033.12";
String PC_SL_ECS_PARCARGAFLSENBB          = "%MW7033.13";
String PC_SL_ECS_PNVOLAFFLSEN1            = "%MW7033.14";
String PC_SL_ECS_PNVOLAFFLSEN2            = "%MW7033.15";
String PC_SL_ECS_PLCCRTLFL                = "%MW7034.0";
String PC_SL_ECS_POLAFBX                  = "%MW7034.2";
String PC_SL_ECS_POLAFMBX                 = "%MW7034.3";
String PC_SL_ECS_POLAFFLSEN               = "%MW7034.4";
String PC_SL_ECS_TOLFLSEN1                = "%MW7034.5";
String PC_SL_ECS_TOLFLSEN2                = "%MW7034.6";
String PC_SL_ECS_OLTAL                    = "%MW7034.7";
String PC_SL_ECS_OLTMAL                   = "%MW7034.8";
String PC_SL_ECS_TADFLSEN1                = "%MW7034.9";
String PC_SL_ECS_TADFLSEN2                = "%MW7034.10";
String PC_SL_ECS_TADAL                    = "%MW7034.11";
String PC_SL_ECS_TADMAL                   = "%MW7034.12";
String PC_SL_ECS_DESCA1TAL                = "%MW7034.13";
String PC_SL_ECS_DESCA1TMAL               = "%MW7034.14";
String PC_SL_ECS_TDESCA1FLSEN             = "%MW7034.15";
String PC_SL_ECS_DESCA2TAL                = "%MW7035.0";
String PC_SL_ECS_DESCA2TMAL               = "%MW7035.1";
String PC_SL_ECS_TDESCA2FLSEN             = "%MW7035.2";
String PC_SL_ECS_DESCA3TAL                = "%MW7035.3";
String PC_SL_ECS_DESCA3TMAL               = "%MW7035.4";
String PC_SL_ECS_TDESCA3FLSEN             = "%MW7035.5";
String PC_SL_ECS_DESCA4TAL                = "%MW7035.6";
String PC_SL_ECS_DESCA4TMAL               = "%MW7035.7";
String PC_SL_ECS_TDESCA4FLSEN             = "%MW7035.8";
String PC_SL_ECS_DESCA5TAL                = "%MW7035.9";
String PC_SL_ECS_DESCA5TMAL               = "%MW7035.10";
String PC_SL_ECS_TDESCA5FLSEN             = "%MW7035.11";
String PC_SL_ECS_DESCA6TAL                = "%MW7035.12";
String PC_SL_ECS_DESCA6TMAL               = "%MW7035.13";
String PC_SL_ECS_TDESCA6FLSEN             = "%MW7035.14";
String PC_SL_ECS_DESCA7TAL                = "%MW7035.15";
String PC_SL_ECS_DESCA7TMAL               = "%MW7036.0";
String PC_SL_ECS_TDESCA7FLSEN             = "%MW7036.1";
String PC_SL_ECS_DESCA8TAL                = "%MW7036.2";
String PC_SL_ECS_DESCA8TMAL               = "%MW7036.3";
String PC_SL_ECS_TDESCA8FLSEN             = "%MW7036.4";
String PC_SL_ECS_DESCB1TAL                = "%MW7036.5";
String PC_SL_ECS_DESCB1TMAL               = "%MW7036.6";
String PC_SL_ECS_TDESCB1FLSEN             = "%MW7036.7";
String PC_SL_ECS_DESCB2TAL                = "%MW7036.8";
String PC_SL_ECS_DESCB2MTAL               = "%MW7036.9";
String PC_SL_ECS_TDESCB2FLSEN             = "%MW7036.10";
String PC_SL_ECS_DESCB3AL                 = "%MW7036.11";
String PC_SL_ECS_DESCB3MAL                = "%MW7036.12";
String PC_SL_ECS_TDESCB3FLSEN             = "%MW7036.13";
String PC_SL_ECS_DESCB4TAL                = "%MW7036.14";
String PC_SL_ECS_DESCB4TMAL               = "%MW7036.15";
String PC_SL_ECS_TDESCB4FLSEN             = "%MW7037.0";
String PC_SL_ECS_DESCB5TAL                = "%MW7037.1";
String PC_SL_ECS_DESCB5TMAL               = "%MW7037.2";
String PC_SL_ECS_TDESCB5FLSEN             = "%MW7037.3";
String PC_SL_ECS_DESCB6TAL                = "%MW7037.4";
String PC_SL_ECS_DESCB6TMAL               = "%MW7037.5";
String PC_SL_ECS_TDESCB6FLSEN             = "%MW7037.6";
String PC_SL_ECS_DESCB7TAL                = "%MW7037.7";
String PC_SL_ECS_DESCB7TMAL               = "%MW7037.8";
String PC_SL_ECS_TDESCB7FLSEN             = "%MW7037.9";
String PC_SL_ECS_DESCB8TAL                = "%MW7037.10";
String PC_SL_ECS_DESCB8TMAL               = "%MW7037.11";
String PC_SL_ECS_TDESCB8FLSEN             = "%MW7037.12";
String PC_SL_ECS_DESCT1TAL                = "%MW7037.13";
String PC_SL_ECS_DESCT1TMAL               = "%MW7037.14";
String PC_SL_ECS_DESCT1SENSFL             = "%MW7037.15";
String PC_SL_ECS_DESCT2TAL                = "%MW7038.0";
String PC_SL_ECS_DESCT2TMAL               = "%MW7038.1";
String PC_SL_ECS_DESCT2SENSFL             = "%MW7038.2";
String PC_SL_ECS_DESCANTSLSENFL           = "%MW7038.6";
String PC_SL_ECS_DESCANTSLTAL             = "%MW7038.7";
String PC_SL_ECS_DESCANTSLTMAL            = "%MW7038.8";
String PC_SL_ECS_DESCTMEDALBA             = "%MW7038.9";
String PC_SL_ECS_DESCTMEDMALBA            = "%MW7038.10";
String PC_SL_ECS_DESCTMEDALBB             = "%MW7038.11";
String PC_SL_ECS_DESCTMEDMALBB            = "%MW7038.12";
String PC_SL_ECS_DESCTMEDGAL              = "%MW7038.13";
String PC_SL_ECS_DESCTMEDGMAL             = "%MW7038.14";
String PC_SL_ECS_TOLAFFLSEN1              = "%MW7038.15";
String PC_SL_ECS_TOLAFFLSEN2              = "%MW7039.0";
String PC_SL_ECS_TOLAFAL                  = "%MW7039.1";
String PC_SL_ECS_TOLAFMAL                 = "%MW7039.2";
String PC_SL_ECS_CREMAL1FLSEN             = "%MW7039.3";
String PC_SL_ECS_CREMAL3FLSEN             = "%MW7039.4";
String PC_SL_ECS_RPMMCPFLSENJ1            = "%MW7039.5";
String PC_SL_ECS_RPMMCPFLSENJ3            = "%MW7039.6";
String PC_SL_ECS_TARCARGAFLSENLA          = "%MW7039.7";
String PC_SL_ECS_TARCARGAFLSENLB          = "%MW7039.8";
String PC_SL_ECS_TARCARGAAL               = "%MW7039.9";
String PC_SL_ECS_TARCARGAMAL              = "%MW7039.10";
String PC_SL_ECS_QQALATIVO                = "%MW7039.11";
String PC_SL_ECS_MECPRINCFALHA            = "%MW7039.12";
String PC_SL_ECS_MECSTDBYCFALHA           = "%MW7039.13";
String PC_SL_ECS_QQSENFALHA               = "%MW7039.14";
String PC_SL_ECS_PRDEMERG1REDE            = "%MW7039.15";
String PC_SL_ECS_PRDEMERG2CIRC            = "%MW7040.0";
String PC_SL_ECS_PRDEMERG3CIRC            = "%MW7040.1";
String PC_SL_ECS_PRDEMERG4CIRC            = "%MW7040.2";
String PC_SL_ECS_PRDEMERG2FIOFL           = "%MW7040.3";
String PC_SL_ECS_PRDEMERG3FIOFL           = "%MW7040.4";
String PC_SL_ECS_PRDEMERG4FIOFL           = "%MW7040.5";
String PC_SL_ECS_MCPPRDEMERGPNL           = "%MW7040.6";
String PC_SL_ECS_FLAPSAFECHADOS           = "%MW7040.7";
String PC_SL_ECS_FLAPSBFECHADOS           = "%MW7040.8";
String PC_SL_ECS_PRIMESOBREC              = "%MW7040.9";
String PC_SL_ECS_PRIMEFLINICIAR           = "%MW7040.10";
String PC_SL_ECS_PRIMEFLPARAR             = "%MW7040.11";
String PC_SL_ECS_PRIMEALGERAL             = "%MW7040.12";
String PC_SL_ECS_PRDAUT                   = "%MW7040.13";
String PC_SL_ECS_POLPRDAUTSEN             = "%MW7040.14";
String PC_SL_ECS_POLPRDAUTALDED           = "%MW7040.15";
String PC_SL_ECS_POLPRDAUTRESFAL          = "%MW7041.0";
String PC_SL_ECS_PRDAUTADTEMP             = "%MW7041.1";
String PC_SL_ECS_PRDAUTOLTEMP             = "%MW7041.2";
String PC_SL_ECS_PRDAUTADOLTEMP           = "%MW7041.3";
String PC_SL_ECS_RPMALTAPRDAUTSEN         = "%MW7041.4";
String PC_SL_ECS_RPMALTAPRDAUTDED         = "%MW7041.5";
String PC_SL_ECS_PRDAUTFLAPFECHA          = "%MW7041.6";
String PC_SL_ECS_REDPOT                   = "%MW7041.7";
String PC_SL_ECS_REDPOTPAD                = "%MW7041.8";
String PC_SL_ECS_REDPOTPOL                = "%MW7041.9";
String PC_SL_ECS_REDPOTPRESFOL            = "%MW7041.10";
String PC_SL_ECS_REDPOTPOD                = "%MW7041.11";
String PC_SL_ECS_REDPOTTAD                = "%MW7041.12";
String PC_SL_ECS_REDPOTTARCARGA           = "%MW7041.13";
String PC_SL_ECS_REDPOTTMEDDESC           = "%MW7041.14";
String PC_SL_ECS_REDPOTTEMPOL             = "%MW7041.15";
String PC_SL_ECS_REDPOTTEMPOLAF           = "%MW7042.0";
String PC_SL_ECS_AUTOESVAF                = "%MW7042.1";
String PC_SL_ECS_AUTOESVAFTOL             = "%MW7042.2";
String PC_SL_ECS_FLPTDABORT               = "%MW7042.3";
String PC_SL_ECS_FLPTDMINRPM              = "%MW7042.4";
String PC_SL_ECS_FLPTDIDLE                = "%MW7042.5";
String PC_SL_ECS_FLPTDCANCEL              = "%MW7042.6";
String PC_SL_ECS_PTDNORMALFL              = "%MW7042.7";
String PC_SL_ECS_PRDEMERGFL               = "%MW7042.8";
String PC_SL_ECS_ENCHENDOAFFL             = "%MW7042.9";
String PC_SL_ECS_ESVAZIANDOAFFL           = "%MW7042.10";
String PC_SL_ECS_RPMNAOATING              = "%MW7042.11";
String PC_SL_ECS_RPMNAOATINGCTRFL         = "%MW7042.12";
String PC_SL_ECS_RPMNAOATINGNETFL         = "%MW7042.13";
String PC_SL_ECS_ETH1FALHA                = "%MW7042.14";
String PC_SL_ECS_ETH2FALHA                = "%MW7042.15";
String PC_SL_ECS_LOPLOCCOMFL              = "%MW7043.0";
String PC_SL_ECS_LOPRTUCOMFL              = "%MW7043.1";
String PC_SL_ECS_LOPRTU1COMFL             = "%MW7043.2";
String PC_SL_ECS_LOPRTU2COMFL             = "%MW7043.3";
String PC_SL_ECS_COMGERALFALHA            = "%MW7043.4";
String PC_SL_ECS_CREMALMONITFL            = "%MW7043.5";
String PC_SL_ECS_RPMMONITFL               = "%MW7043.6";
String PC_SL_ECS_OVERRIDEATIVO            = "%MW7043.8";
String PC_SL_ECS_POTENCIAREVERSA          = "%MW7043.9";
String PC_SL_ECS_NVBXTQEXPAD              = "%MW7043.10";
String PC_SL_ECS_A1FORAMEDIABANC          = "%MW7043.11";
String PC_SL_ECS_A2FORAMEDIABANC          = "%MW7043.12";
String PC_SL_ECS_A3FORAMEDIABANC          = "%MW7043.13";
String PC_SL_ECS_A4FORAMEDIABANC          = "%MW7043.14";
String PC_SL_ECS_A5FORAMEDIABANC          = "%MW7043.15";
String PC_SL_ECS_A6FORAMEDIABANC          = "%MW7044.0";
String PC_SL_ECS_A7FORAMEDIABANC          = "%MW7044.1";
String PC_SL_ECS_A8FORAMEDIABANC          = "%MW7044.2";
String PC_SL_ECS_B1FORAMEDIABANC          = "%MW7044.3";
String PC_SL_ECS_B2FORAMEDIABANC          = "%MW7044.4";
String PC_SL_ECS_B3FORAMEDIABANC          = "%MW7044.5";
String PC_SL_ECS_B4FORAMEDIABANC          = "%MW7044.6";
String PC_SL_ECS_B5FORAMEDIABANC          = "%MW7044.7";
String PC_SL_ECS_B6FORAMEDIABANC          = "%MW7044.8";
String PC_SL_ECS_B7FORAMEDIABANC          = "%MW7044.9";
String PC_SL_ECS_DIFTEMPMEDBANC           = "%MW7044.10";
String PC_SL_ECS_NETSTBYFLETH1            = "%MW7044.11";
String PC_SL_ECS_NETSTBYFLETH2            = "%MW7044.12";
String PC_SL_ECS_MCPSOBRECACIMDBR         = "%MW7044.13";
String PC_SL_ECS_QQACAONAOTOMADBO         = "%MW7044.14";
String PC_SL_ECS_TADPRDAUTNEXECBO         = "%MW7044.15";
String PC_SL_ECS_TOLPRDAUTNEXECBO         = "%MW7045.0";
String PC_SL_ECS_AFESVAUTNEXECBO          = "%MW7045.1";
String PC_SL_ECS_PRDAEMERG2FL             = "%MW7045.2";
String PC_SL_ECS_PRDAEMERG3FL             = "%MW7045.3";
String PC_SL_ECS_PRDAEMERG4FL             = "%MW7045.4";
String PC_SL_ECS_POLBXPRDAAUTOAL          = "%MW7045.5";
String PC_SL_ECS_TADALTPRDAAUTOAL         = "%MW7045.6";
String PC_SL_ECS_CTRLPR                   = "%MW7045.7";
String PC_SL_ECS_CTRLSE                   = "%MW7045.8";
String PC_SL_ECS_CTRLPRRPMALTCH           = "%MW7046.7";
String PC_SL_ECS_CTRLPRACAORETFL          = "%MW7046.10";
String PC_SL_ECS_CTRLSEMPU1FL             = "%MW7046.12";
String PC_SL_ECS_CTRLSEMPU2FL             = "%MW7046.13";
String PC_SL_ECS_CTRLSEARCOLFL            = "%MW7046.14";
String PC_SL_ECS_CTRLSERPMREMFL           = "%MW7046.15";
String PC_SL_ECS_CTRLSECREMALFL           = "%MW7047.0";
String PC_SL_ECS_CTRLSETORQLIM            = "%MW7047.2";
String PC_SL_ECS_CTRLSECOLLIM             = "%MW7047.3";
String PC_SL_ECS_CTRLSEMODPORT3           = "%MW7047.5";
String PC_SL_ECS_CTRLCAODEGUARDA1         = "%MW7047.15";
String PC_SL_ECS_CTRLCAODEGUARDA2         = "%MW7048.0";
String PC_SL_ECS_DEMROTHDWFPTD            = "%MW7048.1";
String PC_SL_ECS_ROTHDWSCMFPTD            = "%MW7048.2";
String PC_SL_ECS_ROTHDWMRFPTD             = "%MW7048.3";
String PC_SL_ECS_AFTOLUBHDWFPTD           = "%MW7048.4";
String PC_SL_ECS_AFPOLUBHDWFPTD           = "%MW7048.5";
String PC_SL_ECS_PSCCRHDWSCMFPTD          = "%MW7048.6";
String PC_SL_ECS_PSCCRHDWMRFPTD           = "%MW7048.7";
String PC_SL_ECS_CARGAHDWSCMFPTD          = "%MW7048.8";
String PC_SL_ECS_CARGAHDWMRFPTD           = "%MW7048.9";
String PC_SL_ECS_TADHDWFPTD               = "%MW7048.10";
String PC_SL_ECS_POLHDWFPTD               = "%MW7048.11";
String PC_SL_ECS_OLAFTEMPANFL             = "%MW7048.12";
String PC_SL_ECS_OLMCPTEMPANFL            = "%MW7048.13";
String PC_SL_ECS_ADTEMPANLGFL             = "%MW7048.14";
String PC_SL_ECS_ARCARGTEMPAFLAN          = "%MW7048.15";
String PC_SL_ECS_ARCARGTEMPBFLAN          = "%MW7049.0";
String PC_SL_ECS_VELREMREFANFL            = "%MW7049.1";
String PC_SL_ECS_COMDEMSENJ1FL            = "%MW7049.2";
String PC_SL_ECS_COMDEMSENJ3FL            = "%MW7049.3";
String PC_SL_ECS_COMPTEMPSENFL            = "%MW7049.4";
String PC_SL_ECS_ROTHDWSENFL              = "%MW7049.5";
String PC_SL_ECS_BREAKWIREAFLAP           = "%MW7049.6";
String PC_SL_ECS_BREAKWIREBFLAP           = "%MW7049.7";
String PC_SL_ECS_PRDAEMERGFLETH1          = "%MW7049.9";
String PC_SL_ECS_PRDAEMERGFLPAIN          = "%MW7049.10";
String PC_SL_ECS_FLAPAWRBRKSENFL          = "%MW7049.11";
String PC_SL_ECS_FLAPBWRBRKSENFL          = "%MW7049.12";
String PC_SL_ECS_MCPBLOQ                  = "%MW7049.13";
String PC_SL_ECS_OLAFPRESSNVS1S2          = "%MW7049.14";
String PC_SL_ECS_OLTEMPFILDPS1S2          = "%MW7049.15";
String PC_SL_ECS_OLAFTEMPS1S2             = "%MW7050.0";
String PC_SL_ECS_MCPVELMPUJ1              = "%MW7050.1";
String PC_SL_ECS_ADTEMPS1S2               = "%MW7050.2";
String PC_SL_ECS_CIL8TEMPALTBCB           = "%MW7050.3";
String PC_SL_ECS_UACPSFFALHA              = "%MW7050.4";
String PC_SL_ECS_UACPSIFALHA              = "%MW7050.5";
String PC_SL_ECS_UACREDUNCFL              = "%MW7050.6";
String PC_SL_ECS_UACUPSGRUP               = "%MW7050.7";
String PC_SL_ECS_MCPVELALDIFMPU           = "%MW7050.9";
String PC_SL_ECS_PLCAOFF                  = "%MW7050.10";
String PC_SL_ECS_PLCBOFF                  = "%MW7050.11";
String PC_SL_ECS_ARCARGALTTEMP            = "%MW7050.12";
String PC_SL_ECS_ARCARGMALTTEMP           = "%MW7050.13";
String PC_SL_ECS_PRDAAUTOGOV              = "%MW7050.14";
String PC_SL_ECS_PRDAAUTOSEGSIS           = "%MW7050.15";
String PC_SL_ECS_SWDDPOLFL                = "%MW7051.0";
String PC_SL_ECS_PLCAFONTEFALHA           = "%MW7051.1";
String PC_SL_ECS_PLCABSINCFALHA           = "%MW7051.2";
String PC_SL_ECS_PLCAMODCOMFALHA          = "%MW7051.3";
String PC_SL_ECS_PLCACRTFALHA             = "%MW7051.4";
String PC_SL_ECS_PLCASLT3ETHCRTFL         = "%MW7051.5";
String PC_SL_ECS_PLCASLT4ETHCRTFL         = "%MW7051.6";
String PC_SL_ECS_PLCBFONTEFALHA           = "%MW7051.8";
String PC_SL_ECS_PLCBBSINCFALHA           = "%MW7051.9";
String PC_SL_ECS_PLCBMODCOMFALHA          = "%MW7051.10";
String PC_SL_ECS_PLCBCRTFALHA             = "%MW7051.11";
String PC_SL_ECS_PLCBSLT3ETHCRTFL         = "%MW7051.12";
String PC_SL_ECS_PLCBSLT4ETHCRTFL         = "%MW7051.13";
String PC_SL_ECS_MPU1J3FALHA              = "%MW7051.15";
String PC_SL_ECS_MPU2J3FALHA              = "%MW7052.0";
String PC_SL_ECS_CRGREDTEMPEXBCB          = "%MW7052.1";
String PC_SL_ECS_CRGARTEMPBCB             = "%MW7052.2";
String PC_SL_ECS_RPMMCPADIFCVHDW          = "%MW7052.3";
String PC_SL_ECS_PRDAUTOAMBOSAL           = "%MW7052.4";
String PC_SL_ECS_MCPSOBRECNCALC           = "%MW7052.5";
String PC_SL_ECS_PERDAREFRPM              = "%MW7052.6";
String PC_SL_ECS_CTRLSETEMPCTLRAL         = "%MW7052.7";
String PC_SL_ECS_IOLOPFLRTU1              = "%MW7052.8";
String PC_SL_ECS_IOLOPFLRTU2              = "%MW7052.9";
String PC_SL_ECS_IOLOPFLRTUREM            = "%MW7052.10";
String PC_SL_ECS_DATARECCOMFL             = "%MW7052.11";
String PC_SL_ECS_REDCARGAEXECBO           = "%MW7052.12";
String PC_SL_ECS_AFESVFLVALVNP            = "%MW7052.13";
String PC_SL_ECS_REDCGPADEXECBO           = "%MW7052.14";
String PC_SL_ECS_REDCGPOLEXECBO           = "%MW7052.15";
String PC_SL_ECS_REDCGPOLREXECBO          = "%MW7053.0";
String PC_SL_ECS_REDCGPODEXECBO           = "%MW7053.1";
String PC_SL_ECS_REDCGTADEXECBO           = "%MW7053.2";
String PC_SL_ECS_REDCGTBAEXECBO           = "%MW7053.3";
String PC_SL_ECS_REDCGMTBAEXECBO          = "%MW7053.4";
String PC_SL_ECS_REDCGTOLEXECBO           = "%MW7053.5";
String PC_SL_ECS_REDCGTOLAFEXECBO         = "%MW7053.6";
String PC_SL_ECS_REDCGTBBEXECBO           = "%MW7053.7";
String PC_SL_ECS_REDCGMTBBEXECBO          = "%MW7053.8";
String PC_SL_ECS_CHOVSCMNAMR              = "%MW7053.9";
String PC_SL_ECS_AFENCFLVALVNP            = "%MW7053.10";
String CP_SL_ECS_PARTIRETH1               = "%MW700.0";
String CP_SL_ECS_PARARETH1                = "%MW700.1";
String CP_SL_ECS_DESARMARETH1             = "%MW700.2";
String CP_SL_ECS_BUZDESLIGETH1            = "%MW700.3";
String CP_SL_ECS_RECTODOSALETH1           = "%MW700.4";
String CP_SL_ECS_ENCHERAFETH1             = "%MW700.5";
String CP_SL_ECS_ESVAZIARAFETH1           = "%MW700.6";
String CP_SL_ECS_PARTIRETH2               = "%MW710.0";
String CP_SL_ECS_PARARETH2                = "%MW710.1";
String CP_SL_ECS_DESARMARETH2             = "%MW710.2";
String CP_SL_ECS_BUZDESLIGETH2            = "%MW710.3";
String CP_SL_ECS_RECTODOSALETH2           = "%MW710.4";
String CP_SL_ECS_ENCHERAFETH2             = "%MW710.5";
String CP_SL_ECS_ESVAZIARAFETH2           = "%MW710.6";
String PC_SA_ECS_OLPRESSANTFI             = "%MF7058";
String PC_SA_ECS_OLPRESSDEPFI             = "%MF7060";
String PC_SA_ECS_OLRESFPRESS              = "%MF7062";
String PC_SA_ECS_ODPRESSANTFI             = "%MF7064";
String PC_SA_ECS_ODPRESSDEPFI             = "%MF7066";
String PC_SA_ECS_ADPRESS                  = "%MF7068";
String PC_SA_ECS_ASPRESS                  = "%MF7070";
String PC_SA_ECS_ARPTDPRESS               = "%MF7072";
String PC_SA_ECS_ARCMBTPRESSBA            = "%MF7074";
String PC_SA_ECS_ARCMBTPRESSBB            = "%MF7076";
String PC_SA_ECS_AFOLUBPRESSS1            = "%MF7078";
String PC_SA_ECS_AFOLUBPRESSS2            = "%MF7080";
String PC_SA_ECS_AFOLUBPRESSNVL           = "%MF7082";
String PC_SA_ECS_AFOLUBPRESS              = "%MF7084";
String PC_SA_ECS_OLTEMPS1DEPFI            = "%MF7086";
String PC_SA_ECS_OLTEMPS2DEPFI            = "%MF7088";
String PC_SA_ECS_OLTEMP                   = "%MF7090";
String PC_SA_ECS_ADTEMPS1                 = "%MF7092";
String PC_SA_ECS_ADTEMPS2                 = "%MF7094";
String PC_SA_ECS_ADTEMP                   = "%MF7096";
String PC_SA_ECS_DESCA1TEMP               = "%MF7098";
String PC_SA_ECS_DESCA2TEMP               = "%MF7100";
String PC_SA_ECS_DESCA3TEMP               = "%MF7102";
String PC_SA_ECS_DESCA4TEMP               = "%MF7104";
String PC_SA_ECS_DESCA5TEMP               = "%MF7106";
String PC_SA_ECS_DESCA6TEMP               = "%MF7108";
String PC_SA_ECS_DESCA7TEMP               = "%MF7110";
String PC_SA_ECS_DESCA8TEMP               = "%MF7112";
String PC_SA_ECS_DESCB1TEMP               = "%MF7114";
String PC_SA_ECS_DESCB2TEMP               = "%MF7116";
String PC_SA_ECS_DESCB3TEMP               = "%MF7118";
String PC_SA_ECS_DESCB4TEMP               = "%MF7120";
String PC_SA_ECS_DESCB5TEMP               = "%MF7122";
String PC_SA_ECS_DESCB6TEMP               = "%MF7124";
String PC_SA_ECS_DESCB7TEMP               = "%MF7126";
String PC_SA_ECS_DESCB8TEMP               = "%MF7128";
String PC_SA_ECS_DESCTC1TEMP              = "%MF7130";
String PC_SA_ECS_DESCTC2TEMP              = "%MF7132";
String PC_SA_ECS_DESCANTSLTEMP            = "%MF7136";
String PC_SA_ECS_DESCTEMPMEDBA            = "%MF7138";
String PC_SA_ECS_DESCTEMPMEDBB            = "%MF7140";
String PC_SA_ECS_DESCCILTMEDIA            = "%MF7142";
String PC_SA_ECS_AFOLUBTEMPS1             = "%MF7144";
String PC_SA_ECS_AFOLUBTEMPS2             = "%MF7146";
String PC_SA_ECS_AFOLUBTEMP               = "%MF7148";
String PC_SA_ECS_POSICREMALPRINC          = "%MF7150";
String PC_SA_ECS_POSICREMALSEC            = "%MF7152";
String PC_SA_ECS_FBSETPOINTRPM            = "%MF7154";
String PC_SA_ECS_SPRPMPMOTOR              = "%MF7156";
String PC_SA_ECS_RPMMOTORS1PRINC          = "%MF7158";
String PC_SA_ECS_RPMMOTORS2PRINC          = "%MF7160";
String PC_SA_ECS_MCPRPM                   = "%MF7162";
String PC_SA_ECS_ARCARGATEMPLA            = "%MF7164";
String PC_SA_ECS_ARCARGATEMPLB            = "%MF7166";
String PC_SA_ECS_DBRATUAL                 = "%MF7170";
String PC_SA_ECS_MCRATUAL                 = "%MF7172";
String PC_SA_ECS_CARGA                    = "%MF7174";
String PC_SA_ECS_BBAELOLHORAFUNC          = "%MF7176";
String PC_SA_ECS_BBAELOLMINFUNC           = "%MF7178";
String PC_SA_ECS_BBAELOLLIG               = "%MF7180";
String PC_SA_ECS_HORASFUNC                = "%MF7182";
String PC_SA_ECS_MINUTOSFUNC              = "%MF7184";
String PC_SA_ECS_ECSLIG                   = "%MF7186";
String PC_SA_ECS_MCPVELHDW                = "%MF7192";
String PC_SA_ECS_COMBDEMJ1                = "%MF7194";
String PC_SA_ECS_COMBDEMJ3                = "%MF7196";
String PC_SA_ECS_COMBCREMALPOS            = "%MF7206";
String PC_SA_ECS_COMBDEMANDA              = "%MF7208";
String PC_SA_ECS_GOVVELMPU1PRINC          = "%MF7236";
String PC_SA_ECS_GOVVELMPU2PRINC          = "%MF7238";
String PC_SA_ECS_GOVVELMPU1STDBY          = "%MF7240";
String PC_SA_ECS_GOVVELMPU2STDBY          = "%MF7242";
String PC_SA_ECS_GOVVELREFPRINC           = "%MF7244";
String PC_SA_ECS_GOVVELREFSTDBY           = "%MF7246";
String PC_SA_ECS_GOVVELTINTCPRINC         = "%MF7248";
String PC_SA_ECS_GOVVELTINTCSTDBY         = "%MF7250";
String PC_SA_ECS_OLTEMPHH                 = "%MF7256";
String PC_SA_ECS_ADTEMPHH                 = "%MF7258";
String PC_SA_ECS_EXACILATEMPHH            = "%MF7260";
String PC_SA_ECS_EXACILBTEMPHH            = "%MF7262";
String PC_SA_ECS_EXATC1DPTEMPHH           = "%MF7264";
String PC_SA_ECS_EXATC2DPTEMPHH           = "%MF7266";
String PC_SA_ECS_EXAANSILTEMPHH           = "%MF7270";
String PC_SA_ECS_BCADCMDTEMPHH            = "%MF7272";
String PC_SA_ECS_BCBDCMDTEMPHH            = "%MF7274";
String PC_SA_ECS_EXMDTEMPHH               = "%MF7276";
String PC_SA_ECS_AFOLTEMPHH               = "%MF7278";
String PC_SA_ECS_LACRGARTEMPHH            = "%MF7280";
String PC_SA_ECS_OLTEMPH                  = "%MF7282";
String PC_SA_ECS_ADTEMPH                  = "%MF7284";
String PC_SA_ECS_EXACILATEMPH             = "%MF7286";
String PC_SA_ECS_EXACILBTEMPH             = "%MF7288";
String PC_SA_ECS_EXATC1DPTEMPH            = "%MF7290";
String PC_SA_ECS_EXATC2DPTEMPH            = "%MF7292";
String PC_SA_ECS_EXAANSILTEMPH            = "%MF7296";
String PC_SA_ECS_BCADCMDTEMPH             = "%MF7298";
String PC_SA_ECS_BCBDCMDTEMPH             = "%MF7300";
String PC_SA_ECS_EXMDTEMPH                = "%MF7302";
String PC_SA_ECS_AFOLTEMPH                = "%MF7304";
String PC_SA_ECS_LACRGARTEMPH             = "%MF7306";
String PC_SA_ECS_OLMCPPRESSANFTL          = "%MF7308";
String PC_SA_ECS_OLMCPPRESSDPFTL          = "%MF7310";
String PC_SA_ECS_OLPSTRESFPRESSL          = "%MF7312";
String PC_SA_ECS_ODPRESSDPFTL             = "%MF7316";
String PC_SA_ECS_ADPRESSL                 = "%MF7318";
String PC_SA_ECS_ASPRESSL                 = "%MF7320";
String PC_SA_ECS_PRTDARPRESSL             = "%MF7322";
String PC_SA_ECS_BCACRGARPRESSH           = "%MF7324";
String PC_SA_ECS_BCBCRGARPRESSH           = "%MF7326";
String PC_SA_ECS_AFOLPRESSL               = "%MF7330";
String PC_SA_ECS_OLMCPPRESSANFTLL         = "%MF7332";
String PC_SA_ECS_OLMCPPRESSDPFTLL         = "%MF7334";
String PC_SA_ECS_OLPSTRESFPRESSLL         = "%MF7336";
String PC_SA_ECS_ODPRESSDPFTLL            = "%MF7340";
String PC_SA_ECS_ADPRESSLL                = "%MF7342";
String PC_SA_ECS_ASPRESSLL                = "%MF7344";
String PC_SA_ECS_PRTDARPRESSLL            = "%MF7346";
String PC_SA_ECS_BCACRGARPRESSHH          = "%MF7348";
String PC_SA_ECS_BCBCRGARPRESSHH          = "%MF7350";
String PC_SA_ECS_AFOLPRESSLL              = "%MF7354";
String PC_SA_ECS_BCACILATEMPDIFH          = "%MF7356";
String PC_SA_ECS_BCBCILBTEMPDIFH          = "%MF7358";
String PC_SA_ECS_BCABTEMPDIFH             = "%MF7360";
String PC_SA_ECS_AFOLPRESSDIFH            = "%MF7362";
String PC_SA_ECS_OLTEMPDPFTDIFH           = "%MF7364";
String PC_SA_ECS_AFOLTEMPDIFH             = "%MF7366";
String PC_SA_ECS_MCPVELCJ1MPUDIFH         = "%MF7368";
String PC_SA_ECS_ADTEMPDIFH               = "%MF7370";
String PC_SA_ECS_MCPVELCJ3MPUDIFH         = "%MF7372";
String PC_SA_ECS_LBCRGARTEMPH             = "%MF7374";
String PC_SA_ECS_LBCRGARTEMPHH            = "%MF7376";
String PC_SA_ECS_BCADCMDTEMPRC            = "%MF7380";
String PC_SA_ECS_BCBDCMDTEMPRC            = "%MF7382";
String PC_SA_ECS_LACRGARTEMPRC            = "%MF7384";
String PC_SA_ECS_LBCRGARTEMPRC            = "%MF7386";
String PC_SA_ECS_OLTEMPRC                 = "%MF7388";
String PC_SA_ECS_ADTEMPRC                 = "%MF7390";
String PC_SA_ECS_OLMCPPRESSDPFTRC         = "%MF7392";
String PC_SA_ECS_AFOLTEMPRC               = "%MF7394";
String PC_SA_ECS_ADPRESSRC                = "%MF7396";
String PC_SA_ECS_ODPRESSDPFTRC            = "%MF7398";
String PC_SA_ECS_OLPSTRESFPRESSRC         = "%MF7402";
String PC_SA_ECS_RPMMCPADIFCVHDW          = "%MF7404";
String PC_SA_ECS_VLENCHERAFFL             = "%MF7406";
String PC_SA_ECS_VLESVAZIARAFFL           = "%MF7408";
String CP_SA_ECS_DEMANDARPMETH1           = "%MW705";
String CP_SA_ECS_DEMANDARPMETH2           = "%MW715";
String PC_SL_ECS_INTPRELUBOK              = "%MW7030.10";
String CP_SL_ECS_PARTIRPRIMEETH1          = "%MW700.7";
String CP_SL_ECS_PARARPRIMEETH1           = "%MW700.8";
String CP_SL_ECS_PARTIRPRIMEETH2          = "%MW710.7";
String CP_SL_ECS_PARARPRIMEETH2           = "%MW710.8";
//---------------------------- RTU ---------------------------
String PC_HL_RTU_OVERRIDELIG            = "%MW6230.8";
String PC_HL_RTU_CREMALIOFL             = "%MW6231.2";
String PC_HL_RTU_RPMMCPIOFL             = "%MW6231.1";
String PC_HL_RTU_CREMALMONITFL          = "%MW6231.0";
String PC_HL_RTU_MCPDEMANDAFL           = "%MW6230.15";
String PC_HL_RTU_NVBXTQEXPAD            = "%MW6230.14";
String PC_HL_RTU_BUZLIGADA              = "%MW6230.13";
String PC_HL_RTU_AFESVAZIANDO           = "%MW6230.12";
String PC_HL_RTU_AFCHEIO                = "%MW6230.11";
String CP_HL_RTU_PARAREMERGHDW          = "%MW510.14";
String PC_HL_RTU_AFVAZIO                = "%MW6230.9";
String PC_HL_RTU_AFESVINTRLCKOK         = "%MW6231.5";
String PC_HL_RTU_PRDAUTO                = "%MW6230.7";
String PC_HL_RTU_PRDEMERG               = "%MW6230.6";
String PC_HL_RTU_PRDNORMAL              = "%MW6230.5";
String PC_HL_RTU_PARANDO                = "%MW6230.4";
String PC_HL_RTU_MCPVIRANDO             = "%MW6230.3";
String PC_HL_RTU_PARTINDO               = "%MW6230.2";
String PC_HL_RTU_EMLOCAL                = "%MW6230.1";
String PC_HL_RTU_EMREMOTO               = "%MW6230.0";
String PC_HL_RTU_AFENCHENDO             = "%MW6230.10";
String PC_HL_RTU_AUTOESVAF              = "%MW6231.14";
String CP_HL_RTU_RECALRMHDW             = "%MW577.4";
String CP_HL_RTU_ATVBOHDW               = "%MW577.3";
String CP_HL_RTU_ESVAFHDW               = "%MW577.2";
String CP_HL_RTU_PARARHDW               = "%MW577.1";
String CP_HL_RTU_PARTIRHDW              = "%MW577.0";
String CP_HA_RTU_DEMANDARPMHDW          = "%MW573";
String PC_HA_RTU_CARGAMCP               = "%MF6238";
String PC_HA_RTU_POSICREMAL             = "%MF6236";
String PC_HL_RTU_CARGAIOFL              = "%MW6231.3";
String PC_HL_RTU_QQALATIVO              = "%MW6231.15";
String PC_HL_RTU_AFENCINTRLCKOK         = "%MW6231.4";
String PC_HL_RTU_AFENCHESVPREST         = "%MW6231.13";
String PC_HL_RTU_UACREDUNCFL            = "%MW6231.12";
String PC_HL_RTU_UACUPSGRUPFL           = "%MW6231.11";
String PC_HL_RTU_UACPSIPRONTO           = "%MW6231.10";
String PC_HL_RTU_UACPSFPRONTO           = "%MW6231.9";
String PC_HL_RTU_MCPSOBREC              = "%MW6231.8";
String PC_HL_RTU_REDCARGAATIVA          = "%MW6231.7";
String PC_HL_RTU_BLOQCAFENATIVO         = "%MW6231.6";
String CP_HL_RTU_SILENCALRHDW           = "%MW577.5";
String PC_HA_RTU_MCPRPM                 = "%MF6234";
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
String NomeForm        = "MCP BE";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;

int   MWO_i           = 4000;
int   MWO_f           = 4067;

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

String PASSO_OPTO   = "%MW3069.4";
String PASSO_REAL   = "%MW118";
String PASSO_SIML   = "%MF6170";
float  PASSO___X1   = 2642;
float  PASSO___Y1   = -100;
float  PASSO___X2   = 6666;
float  PASSO___Y2   = 0;
float  PASSO___X3   = 9738;
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


