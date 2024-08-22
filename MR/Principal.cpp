//---------------------------------------------------------------------------
//***************************************************************************
//MAURICIO ANDRADE LEMME - ENG ELETRICISTA - BOLSISTA
//IPqM - INSTITUTO DE PESQUISAS DA MARINHA
//GSD - GRUPO DE SISTEMAS DIGITAIS
//FUNDEP - FUNDAÇÃO DE DESENVOLVIMENTO DA PESQUISA

//NAVIO MODELO.....: JULIO DE NORONHA
//USUÁRIO FINAL....: EQUIPE CLP
//VERSÃO INICIAL...: V001b
//DATA DE INÍCIO...: 15.06.2023
//DATA DE PROTÓTIPO: 15.06.2023
//DATA DE TÉRMINO..:
//DATA DE ATUALIZ..:
//DESIGNAÇÃO.......: SOFTWARE PARA PERMIRTIR COMANDAR OS SINAIS DO MR
//SEU USO DEVE SER SUPERVISIONADO E POR
//PESSOAL AUTORIZADO COM O CONHECIMENTO NECESSÁRIO NA OPERAÇÃO
//***************************************************************************

#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
//#include "TModBusScanner.cpp" /* DRIVER MODBUS */
#include "ModBusDriverLib\TModBusTCPDriver.cpp"

String PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWO   = "%MW3108.8";
String PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS   = "%MF6324";

String PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWO   = "%MW3108.9";
String PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS   = "%MF6326";

  String PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO    	= "%MW3033.12";
  String PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS       = "%MW6033.12";
  String PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO  	= "%MW3033.13";
  String PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS     = "%MW6033.13";

//ENTRADA DIGITAL
  String PC_HL_SODPG_BEROD1_LIGADO                = "%MW6100.0";    //Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Ligado
  String PC_HL_SODPG_BEROD1_SOBREC1               = "%MW6100.1";    //Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Sobrecarga 1
//String PC_HL_SPARE_DISP_0003                    = "%MW6100.2";    //SPARE
  String PC_HL_SODPG_BEROD2_LIGADO                = "%MW6100.3";    //Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Ligado
  String PC_HL_SODPG_BEROD2_SOBREC1               = "%MW6100.4";    //Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Sobrecarga 1
//String PC_HL_SPARE_DISP_0006                    = "%MW6100.5";    //SPARE
//String PC_HL_SPARE_DISP_0007                    = "%MW6100.6";    //SPARE
//String PC_HL_SPARE_DISP_0008                    = "%MW6100.7";    //SPARE
  String PC_HL_SODPG_FCOD1_PRESSDIFALTA           = "%MW6100.8";    //Filtro Coalescedor N° 1 - Pressão Diferencial Alta
  String PC_HL_SODPG_FCOD2_PRESSDIFALTA           = "%MW6100.9";    //Filtro Coalescedor N° 2 - Pressão Diferencial Alta
  String PC_HL_SODPG_TSOD08_NIVELBAIXO            = "%MW6100.10";   //Tanque de Serviço de Óleo Diesel N° 8 - Nível Baixo
  String PC_HL_SODPG_TSOD09_NIVELBAIXO            = "%MW6100.11";   //Tanque de Serviço de Óleo Diesel N° 9 - Nível Baixo
  String PC_HL_SODPG_TSOD07_NIVELBAIXO            = "%MW6100.12";   //Tanque de Serviço de Óleo Diesel N° 7 - Nível Baixo
  String PC_HL_AOLTG_PUROL1_LIGADO                = "%MW6100.13";   //Purificador Centrífugo de Óleo Lubrificante N° 1 - Ligado
  String PC_HL_AOLTG_PUROL1_PERDASELO             = "%MW6100.14";   //Purificador Centrífugo de Óleo Lubrificante N° 1 - Perda de Selo
  String PC_HL_AOLTG_PUROL2_LIGADO                = "%MW6100.15";   //Purificador Centrífugo de Óleo Lubrificante N° 2 - Ligado
  String PC_HL_AOLTG_PUROL2_PERDASELO             = "%MW6101.0";    //Purificador Centrífugo de Óleo Lubrificante N° 2 - Perda de Selo
  String PC_HL_TBGAS_ARCOMB_PDIFAL                = "%MW6101.1";    //Ar de Combustão da TG - Pressão Diferencial Alta
  String PC_HL_TBGAS_ARRESF_PDIFAL                = "%MW6101.2";    //Ar para Resfriamento da TG - Pressão Diferencial Alta
  String PC_HL_TBGAS_ARCOMB_QQPORTAABER           = "%MW6101.3";    //Ar de Combustão da TG - Qualquer Porta Aberta
  String PC_HL_TBGAS_ARRESF_QQPORTAABER           = "%MW6101.4";    //Ar para Resfriamento da TG - Qualquer Porta Aberta
//String PC_HL_SPARE_DISP_0022                    = "%MW6101.5";    //SPARE
//String PC_HL_SPARE_DISP_0023                    = "%MW6101.6";    //SPARE
  String PC_HL_ERHBC_BBELPN_EMAUT                 = "%MW6101.7";    //Bomba Eletro-Pneumática - ER - Em Automático
  String PC_HL_ERHBC_BBELPN_MOTELLIG              = "%MW6101.8";    //Bomba Eletro-Pneumática - ER - Ligar Motor Elétrico
  String PC_HL_ERHBC_BBELPN_SOBREC                = "%MW6101.9";    //Bomba Eletro-Pneumática - ER - Sobrecarga
  String PC_HL_ERHBC_BBELPN_MOTPNLIG              = "%MW6101.10";   //Bomba Eletro-Pneumática - ER - Ligar Motor Pneumático
  String PC_HL_ERHBC_BBELPN_EMREM                 = "%MW6101.11";   //Bomba Eletro-Pneumática - ER - Em Remoto
  String PC_HL_ERHBC_MODHID_OLPDIFAL              = "%MW6101.12";   //Módulo Hidráulico da ER - Pressão Diferencial Alta de Óleo Lubrificante
  String PC_HL_AOLTG_TAOL14_NIVELBAIXO            = "%MW6101.13";   //Nível baixo no tanque de serviço nº: 14
  String PC_HL_RASRG_OERHPC_PRESSBAIXA            = "%MW6101.14";   //Óleo da ER do HPC - Pressão Baixa
  String PC_HL_ERHBC_MODHID_OLPBX                 = "%MW6101.15";   //Módulo Hidráulico da ER - Pressão Baixa de OL
  String PC_HL_ERPBC_SSSK1_TRAVABER               = "%MW6102.0";    //Embreagem Síncrona da ER do Módulo Primário de BB - Trava Aberta
  String PC_HL_ERPBC_SSSK1_NTRAVABER              = "%MW6102.1";    //Embreagem Síncrona da ER do Módulo Primário de BB - Não Travado Aberta
  String PC_HL_ERPBC_SSSK2_TRAVABER               = "%MW6102.2";    //Embreagem Síncrona da ER do Módulo Primário de BE - Trava Aberta
  String PC_HL_ERPBC_SSSK2_NTRAVABER              = "%MW6102.3";    //Embreagem Síncrona da ER do Módulo Primário de BE - Não Travado Aberta
  String PC_HL_ERPBC_SSSK1_ACPL                   = "%MW6102.4";    //Embreagem Síncrona da ER do Módulo Primário de BB - Acoplar
  String PC_HL_ERPBC_SSSK1_DACPL                  = "%MW6102.5";    //Embreagem Síncrona da ER do Módulo Primário de BB - Desacoplar
  String PC_HL_ERPBC_SSSK1_TRAVACPL               = "%MW6102.6";    //Embreagem Síncrona da ER do Módulo Primário de BB - Travar Acoplado
  String PC_HL_ERPBC_SSSK1_NTRAVACPL              = "%MW6102.7";    //Embreagem Síncrona da ER do Módulo Primário de BB - Não Travado Acoplada
  String PC_HL_ERPBC_SSSK2_ACPL                   = "%MW6102.8";    //Embreagem Síncrona da ER do Módulo Primário de BE - Acoplar
  String PC_HL_ERPBC_SSSK2_DACPL                  = "%MW6102.9";    //Embreagem Síncrona da ER do Módulo Primário de BE - Desacoplar
  String PC_HL_ERPBC_SSSK2_TRAVACPL               = "%MW6102.10";   //Embreagem Síncrona da ER do Módulo Primário de BE - Travar Acoplado
  String PC_HL_ERPBC_SSSK2_NTRAVACPL              = "%MW6102.11";   //Embreagem Síncrona da ER do Módulo Primário de BE - Não Travado Acoplada
  String PC_HL_ERPBC_CATRAC_DESENGATADO           = "%MW6102.12";   //Giro Lento do Módulo Primário da ER - Desengatado
  String PC_HL_ERPBC_FREIO_DESENGATADO            = "%MW6102.13";   //Freio do Módulo Primário da ER - Desengatado
  String PC_HL_ERSBE_SSSK4_TRAVACPL               = "%MW6102.14";   //Embreagem Síncrona da ER do Módulo Secundário de BE - Travar Acoplado
  String PC_HL_ERSBE_SSSK4_NTRAVACPL              = "%MW6102.15";   //Embreagem Síncrona da ER do Módulo Secundário de BE - Não Travado Acoplada
  String PC_HL_ERSBE_SSSK4_OLPBX                  = "%MW6103.0";    //Embreagem Síncrona da ER do Módulo Secundário de BE - Pressão Baixa de OL
  String PC_HL_ERSBE_SSSK4_ACPL                   = "%MW6103.1";    //Embreagem Síncrona da ER do Módulo Secundário de BE - Acoplar
  String PC_HL_ERSBE_SSSK4_DACPL                  = "%MW6103.2";    //Embreagem Síncrona da ER do Módulo Secundário de BE - Desacoplar
  String PC_HL_ERSBB_SSSK3_TRAVACPL               = "%MW6103.3";    //Embreagem Síncrona da ER do Módulo Secundário de BB - Travar Acoplado
  String PC_HL_ERSBB_SSSK3_NTRAVACPL              = "%MW6103.4";    //Embreagem Síncrona da ER do Módulo Secundário de BB - Não Travado Acoplada
  String PC_HL_ERSBB_SSSK3_OLPBX                  = "%MW6103.5";    //Embreagem Síncrona da ER do Módulo Secundário de BB - Pressão Baixa de OL
  String PC_HL_ERSBB_SSSK3_ACPL                   = "%MW6103.6";    //Embreagem Síncrona da ER do Módulo Secundário de BB - Acoplar
  String PC_HL_ERSBB_SSSK3_DACPL                  = "%MW6103.7";    //Embreagem Síncrona da ER do Módulo Secundário de BB - Desacoplar
  String PC_HL_HPCBE_CTRPRI_FALHA                 = "%MW6103.8";    //Controlador Closed Loop" do HPC de BE - Em Falha"
  String PC_HL_HPCBE_CTRPRI_MANRPMBXSCM           = "%MW6103.9";    //Controlador Closed Loop" do HPC de BE - Manobra Baixa Rotação Acionada Pelo SCM"
  String PC_HL_HPCBE_CTRBKP_EMOPERACAO            = "%MW6103.10";   //Controlador Back-up" do HPC de BE - Em Operação"
  String PC_HL_HPCBE_MODHID_OLPBX                 = "%MW6103.11";   //Módulo Hidráulico do HPC de BE - Pressão Baixa de OL
  String PC_HL_HPCBE_MODHID_FILT1PDIFAL           = "%MW6103.12";   //Módulo Hidráulico do HPC de BE - Pressão Diferencial Alta Filtro 1
  String PC_HL_HPCBE_MODHID_FILT2PDIFAL           = "%MW6103.13";   //Módulo Hidráulico do HPC de BE - Pressão Diferencial Alta Filtro 2
  String PC_HL_HPCBE_UDOHPC_OLPRESSOK             = "%MW6103.14";   //Unidade Distribuidora de Oléo do HPC de BB - Pressão de Óleo Lubrificante - OK
  String PC_HL_HPCBE_UDOHPC_ZEROTHRUST            = "%MW6103.15";   //Unidade Distribuidora de Oléo do HPC de BB - Zero Thrust
  String PC_HL_HPCBE_UDOHPC_FILT21APDIFAL         = "%MW6104.0";    //Unidade Distribuidora de Oléo do HPC de BB - Pressão Diferencial Alta Filtro 21A
  String PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL         = "%MW6104.1";    //Unidade Distribuidora de Oléo do HPC de BB - Pressão Diferencial Alta Filtro 21B
  String PC_HL_HPCBE_BBP1BE_LIGADO                = "%MW6104.2";    //Bomba Elétrica de Acionamento do HPC de BE - Ligado
  String PC_HL_HPCBE_BBP1BE_SOBREC                = "%MW6104.3";    //Bomba Elétrica de Acionamento do HPC de BE - Sobrecarga
  String PC_HL_HPCBE_BBP1BE_EMREM                 = "%MW6104.4";    //Bomba Elétrica de Acionamento do HPC de BE - Em Remoto
//String PC_HL_SPARE_DISP_0070                    = "%MW6104.5";    //SPARE
  String PC_HL_HPCBE_BBP3BE_LIGADO                = "%MW6104.6";    //Bomba Elétrica de Transferência do HPC de BE - Ligado
  String PC_HL_HPCBE_BBP3BE_EMREM                 = "%MW6104.7";    //Bomba Elétrica de Transferência do HPC de BE - Em Remoto
  String PC_HL_HPCBE_BBP3BE_EMAUT                 = "%MW6104.8";    //Bomba Elétrica de Transferência do HPC de BE - Em Automático
  String PC_HL_HPCBE_BBP3BE_SOBREC                = "%MW6104.9";    //SPARE
  String PC_HL_HPCBE_TQGRAV_NIVELBAIXO            = "%MW6104.10";   //Tanque Gravitacional do HPC de BB - Nível Baixo
//String PC_HL_SPARE_DISP_0076                    = "%MW6104.11";   //SPARE
  String PC_HL_HPCBB_CTRPRI_FALHA                 = "%MW6104.12";   //Controlador Closed Loop" do HPC de BE - Em Falha"
  String PC_HL_HPCBB_CTRPRI_MANRPMBXSCM           = "%MW6104.13";   //Controlador Closed Loop" do HPC de BE - Manobra Baixa Rotação Acionada Pelo SCM"
  String PC_HL_HPCBB_CTRBKP_EMOPERACAO            = "%MW6104.14";   //Controlador Back-up" do HPC de BE - Em Operação"
  String PC_HL_HPCBB_MODHID_OLPBX                 = "%MW6104.15";   //Módulo Hidráulico do HPC de BB - Pressão Baixa de OL
  String PC_HL_HPCBB_MODHID_FILT1PDIFAL           = "%MW6105.0";    //Módulo Hidráulico do HPC de BB - Pressão Diferencial Alta Filtro 1
  String PC_HL_HPCBB_MODHID_FILT2PDIFAL           = "%MW6105.1";    //Módulo Hidráulico do HPC de BB - Pressão Diferencial Alta Filtro 2
  String PC_HL_HPCBB_UDOHPC_OLPRESSOK             = "%MW6105.2";    //Unidade Distribuidora de Oléo do HPC de BB - Pressão de Óleo Lubrificante - OK
  String PC_HL_HPCBB_UDOHPC_ZEROTHRUST            = "%MW6105.3";    //Unidade Distribuidora de Oléo do HPC de BB - Zero Thrust
  String PC_HL_HPCBB_UDOHPC_FILT21APDIFAL         = "%MW6105.4";    //Unidade Distribuidora de Oléo do HPC de BB - Pressão Diferencial Alta Filtro 21A
  String PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL         = "%MW6105.5";    //Unidade Distribuidora de Oléo do HPC de BB - Pressão Diferencial Alta Filtro 21B
  String PC_HL_HPCBB_BBP1BB_LIGADO                = "%MW6105.6";    //Bomba Elétrica de Acionamento do HPC de BB - Ligado
  String PC_HL_HPCBB_BBP1BB_SOBREC                = "%MW6105.7";    //Bomba Elétrica de Acionamento do HPC de BB - Sobrecarga
  String PC_HL_HPCBB_BBP1BB_EMREM                 = "%MW6105.8";    //Bomba Elétrica de Acionamento do HPC de BB - Em Remoto
//String PC_HL_SPARE_DISP_0090                    = "%MW6105.9";    //SPARE
  String PC_HL_HPCBB_BBP3BB_LIGADO                = "%MW6105.10";   //Bomba Elétrica de Transferência do HPC de BB - Ligado
  String PC_HL_HPCBB_BBP3BB_EMREM                 = "%MW6105.11";   //Bomba Elétrica de Transferência do HPC de BB - Em Remoto
  String PC_HL_HPCBB_BBP3BB_EMAUT                 = "%MW6105.12";   //Bomba Elétrica de Transferência do HPC de BB - Em Automático
  String PC_HL_HPCBB_BBP3BB_SOBREC                = "%MW6105.13";   //SPARE
  String PC_HL_HPCBB_TQGRAV_NIVELBAIXO            = "%MW6105.14";   //Tanque Gravitacional do HPC de BB - Nível Baixo
//String PC_HL_SPARE_DISP_0096                    = "%MW6105.15";   //SPARE
  String PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG         = "%MW6106.0";    //Bomba Eletro-Pneumática - Em Auto Pelo Hardware do SCM - Ligar
  String PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES         = "%MW6106.1";    //Bomba Eletro-Pneumática - Em Auto Pelo Hardware do SCM - Desligar
  String PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG         = "%MW6106.2";    //Bomba Elétrica de Acionamento do HPC de BE - Em Auto Pelo Hardware do SCM - Ligada
  String PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES         = "%MW6106.3";    //Bomba Elétrica de Acionamento do HPC de BE - Em Auto Pelo Hardware do SCM - Desligada
  String PC_HL_HPCBE_BBP1BE_PRDEMGSCMLIG          = "%MW6106.4";    //Bomba Elétrica de Acionamento do HPC de BE - Parada em Emergência - Ligada
  String PC_HL_HPCBE_BBP1BE_PRDEMGSCMDES          = "%MW6106.5";    //Bomba Elétrica de Acionamento do HPC de BE - Parada em Emergência - Desligada
  String PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG         = "%MW6106.6";    //Bomba Elétrica de Transferência do HPC de BE - Está em Auto Pelo Hardware do SCM - Ligado
  String PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES         = "%MW6106.7";    //Bomba Elétrica de Transferência do HPC de BE - Está em Auto Pelo Hardware do SCM - Desligado
  String PC_HL_HPCBE_BBP3BE_PRDEMGSCMLIG          = "%MW6106.8";    //Bomba Elétrica de Acionamento do HPC de BE - Parada em Emergência - Ligada
  String PC_HL_HPCBE_BBP3BE_PRDEMGSCMDES          = "%MW6106.9";    //Bomba Elétrica de Acionamento do HPC de BE - Parada em Emergência - Desligada
  String PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG         = "%MW6106.10";   //Bomba Elétrica de Acionamento do HPC de BB - Está em Auto Pelo Hardware do SCM - Ligado
  String PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES         = "%MW6106.11";   //Bomba Elétrica de Acionamento do HPC de BB - Está em Auto Pelo Hardware do SCM - Desligado
  String PC_HL_HPCBB_BBP1BB_PRDEMGSCMLIG          = "%MW6106.12";   //Bomba Elétrica de Acionamento do HPC de BB - Parada em Emergência - Ligada
  String PC_HL_HPCBB_BBP1BB_PRDEMGSCMDES          = "%MW6106.13";   //Bomba Elétrica de Acionamento do HPC de BB - Parada em Emergência - Desligada
  String PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG         = "%MW6106.14";   //Bomba Elétrica de Transferência do HPC de BB - Está em Auto Pelo Hardware do SCM - Ligado
  String PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES         = "%MW6106.15";   //Bomba Elétrica de Transferência do HPC de BB - Está em Auto Pelo Hardware do SCM - Desligado
  String PC_HL_HPCBB_BBP3BB_PEMERGSCMLIG          = "%MW6107.0";    //Bomba Elétrica de Acionamento do HPC de BB - Parada em Emergência - Ligada
  String PC_HL_HPCBB_BBP3BB_PEMERGSCMDES          = "%MW6107.1";    //Bomba Elétrica de Acionamento do HPC de BB - Parada em Emergência - Desligada
  String PC_HL_ERHBC_BBELPN_PEMERGSCMLIG          = "%MW6107.2";    //Bomba Eletro-Pneumática - Parada em Emergência - Ligado
  String PC_HL_ERHBC_BBELPN_PEMERGSCMDES          = "%MW6107.3";    //Bomba Eletro-Pneumática - Parada em Emergência - Desligado
  String PC_HL_SMR_CPCCM_MCPBBPRDEMERG            = "%MW6107.4";    //CPCCM - MCPBB em prda. emerg.
  String PC_HL_SMR_CPCCM_TGPRDEMERG               = "%MW6107.5";    //TG em prda. emerg.
  String PC_HL_SMR_CPCCM_TGPRDINC                 = "%MW6107.6";    //TG em prda. incend.
  String PC_HL_SMR_CPCCM_MCPBEPRDEMERG            = "%MW6107.7";    //CPCCM - MCPBE em prda. emerg.
  String PC_HL_SMR_CPCCM_SOLICMR                  = "%MW6107.8";    //Solicitação MR
  String PC_HL_SMR_CPCCM_SOLICAUTO                = "%MW6107.9";    //Solicitação AUTO
//String PC_HL_SPARE_DISP_0123                    = "%MW6107.10";   //SPARE
//String PC_HL_SPARE_DISP_0124                    = "%MW6107.11";   //SPARE
//String PC_HL_SPARE_DISP_0125                    = "%MW6107.12";   //SPARE
//String PC_HL_SPARE_DISP_0126                    = "%MW6107.13";   //SPARE
//String PC_HL_SPARE_DISP_0127                    = "%MW6107.14";   //SPARE
//String PC_HL_SPARE_DISP_0128                    = "%MW6107.15";   //SPARE
  String PC_HL_MCPBE_CTRPRI_EMREM                 = "%MW6066.0";    //Controlador Primário do MCPBE - Em Remoto
  String PC_HL_MCPBE_CTRPRI_PARTINDO              = "%MW6066.1";    //Controlador Primário do MCPBE - MCP Partindo
  String PC_HL_MCPBE_CTRPRI_VIRANDO               = "%MW6066.2";    //Controlador Primário do MCPBE - MCP Virando
  String PC_HL_MCPBE_CTRPRI_PARANDO               = "%MW6066.3";    //Controlador Primário do MCPBE - MCP Parando
  String PC_HL_MCPBE_CTRPRI_PARADONORMAL          = "%MW6066.4";    //Controlador Primário do MCPBE - MCP Parado Normal
  String PC_HL_MCPBE_CTRPRI_PRNDOEMEMERG          = "%MW6066.5";    //Controlador Primário do MCPBE - MCP Parando em Emerg.
  String PC_HL_MCPBE_CTRPRI_PRNDOEMAUTO           = "%MW6066.6";    //Controlador Primário do MCPBE - MCP Parando em Auto
  String PC_HL_MCPBE_CTRPRI_BATOVERLIG            = "%MW6066.7";    //Controlador Primário do MCPBE - Battle Override Ligado
  String PC_HL_MCPBE_AFBE_VAZIO                   = "%MW6066.8";    //Acoplamento Fluido MCPBE - Vazio
  String PC_HL_MCPBE_AFBE_ENCHENDO                = "%MW6066.9";    //Acoplamento Fluido MCPBE - Enchendo
  String PC_HL_MCPBE_AFBE_CHEIO                   = "%MW6066.10";   //Acoplamento Fluido MCPBE - Cheio
  String PC_HL_MCPBE_AFBE_ESVAZIANDO              = "%MW6066.11";   //Acoplamento Fluido MCPBE - Esvaziando
  String PC_HL_MCPBE_CTRPRI_ALARMECOMUM           = "%MW6066.12";   //Controlador Primário do MCPBE - Alarme Comum
  String PC_HL_MCPBE_CTRPRI_BUZLIG                = "%MW6066.13";   //Controlador Primário do MCPBE - Buzina Ligada
  String PC_HL_MCPBE_CTRPRI_TQEXPADNVBX           = "%MW6066.14";   //Controlador Primário do MCPBE - Tanque de Expansão com Nível Baixo
  String PC_HL_MCPBE_CTRPRI_RPMMCPIOFL            = "%MW6066.15";   //SPARE
  String PC_HL_MCPBE_CTRPRI_CREMALIOFL            = "%MW6067.0";    //SPARE
  String PC_HL_MCPBE_CTRPRI_CARGAIOFL             = "%MW6067.1";    //SPARE
  String PC_HL_MCPBE_AFBE_OKENCHER                = "%MW6067.2";    //Acoplamento Fluido MCPBE - Interlock para encher atendido
  String PC_HL_MCPBE_AFBE_OKESVAZIAR              = "%MW6067.3";    //Acoplamento Fluido MCPBE - Interlock para esvaziar atendido
  String PC_HL_MCPBE_AFBE_ENCHIMENBLQ             = "%MW6067.4";    //Acoplamento Fluido MCPBE - Enchimento Bloqueado
  String PC_HL_MCPBE_CTRPRI_EMLIMCARGA            = "%MW6067.5";    //Controlador Primário do MCPBE - Em Limitação de Carga
  String PC_HL_MCPBE_CTRPRI_MCPEMSOBREC           = "%MW6067.6";    //Controlador Primário do MCPBE - MCP em Sobrecarga
  String PC_HL_MCPBE_AFBE_ESVAZAUTO               = "%MW6067.7";    //Acoplamento Fluido MCPBE - Esvaziando em Auto
  String PC_HL_MCPBE_CTRPRI_QQALNREC              = "%MW6067.8";    //Controlador Primário do MCPBE - Qualquer Alarme não Reconhecido
//String PC_HL_SPARE_DISP_0154                    = "%MW6067.9";    //SPARE
//String PC_HL_SPARE_DISP_0155                    = "%MW6067.10";   //SPARE
//String PC_HL_SPARE_DISP_0156                    = "%MW6067.11";   //SPARE
//String PC_HL_SPARE_DISP_0157                    = "%MW6067.12";   //SPARE
//String PC_HL_SPARE_DISP_0158                    = "%MW6067.13";   //SPARE
//String PC_HL_SPARE_DISP_0159                    = "%MW6067.14";   //SPARE
//String PC_HL_SPARE_DISP_0160                    = "%MW6067.15";   //SPARE
  String PC_HL_MCPBB_CTRPRI_EMREM                 = "%MW6068.0";    //Controlador Primário do MCPBB - Em Remoto
  String PC_HL_MCPBB_CTRPRI_PARTINDO              = "%MW6068.1";    //Controlador Primário do MCPBB - MCP Partindo
  String PC_HL_MCPBB_CTRPRI_VIRANDO               = "%MW6068.2";    //Controlador Primário do MCPBB - MCP Virando
  String PC_HL_MCPBB_CTRPRI_PARANDO               = "%MW6068.3";    //Controlador Primário do MCPBB - MCP Parando
  String PC_HL_MCPBB_CTRPRI_PARADONORMAL          = "%MW6068.4";    //Controlador Primário do MCPBB - MCP Parado Normal
  String PC_HL_MCPBB_CTRPRI_PRNDOEMEMERG          = "%MW6068.5";    //Controlador Primário do MCPBB - MCP Parando em Emerg.
  String PC_HL_MCPBB_CTRPRI_PRNDOEMAUTO           = "%MW6068.6";    //Controlador Primário do MCPBB - MCP Parando em Auto
  String PC_HL_MCPBB_CTRPRI_BATOVERLIG            = "%MW6068.7";    //Controlador Primário do MCPBB - Battle Override Ligado
  String PC_HL_MCPBB_AFBB_VAZIO                   = "%MW6068.8";    //Acoplamento Fluido MCPBB - Vazio
  String PC_HL_MCPBB_AFBB_ENCHENDO                = "%MW6068.9";    //Acoplamento Fluido MCPBB - Enchendo
  String PC_HL_MCPBB_AFBB_CHEIO                   = "%MW6068.10";   //Acoplamento Fluido MCPBB - Cheio
  String PC_HL_MCPBB_AFBB_ESVAZIANDO              = "%MW6068.11";   //Acoplamento Fluido MCPBB - Esvaziando
  String PC_HL_MCPBB_CTRPRI_ALARMECOMUM           = "%MW6068.12";   //Controlador Primário do MCPBB - Alarme Comum
  String PC_HL_MCPBB_CTRPRI_BUZLIG                = "%MW6068.13";   //Controlador Primário do MCPBB - Buzina Ligada
  String PC_HL_MCPBB_CTRPRI_TQEXPADNVBX           = "%MW6068.14";   //Controlador Primário do MCPBB - Tanque de Expansão com Nível Baixo
  String PC_HL_MCPBB_CTRPRI_RPMMCPIOFL            = "%MW6068.15";   //SPARE
  String PC_HL_MCPBB_CTRPRI_CREMALIOFL            = "%MW6069.0";    //SPARE
  String PC_HL_MCPBB_CTRPRI_CARGAIOFL             = "%MW6069.1";    //SPARE
  String PC_HL_MCPBB_AFBB_OKENCHER                = "%MW6069.2";    //Acoplamento Fluido MCPBB - Interlock para encher atendido
  String PC_HL_MCPBB_AFBB_OKESVAZIAR              = "%MW6069.3";    //Acoplamento Fluido MCPBB - Interlock para esvaziar atendido
  String PC_HL_MCPBB_AFBB_ENCHIMENBLQ             = "%MW6069.4";    //Acoplamento Fluido MCPBB - Enchimento Bloqueado
  String PC_HL_MCPBB_CTRPRI_EMLIMCARGA            = "%MW6069.5";    //Controlador Primário do MCPBB - Em Limitação de Carga
  String PC_HL_MCPBB_CTRPRI_MCPEMSOBREC           = "%MW6069.6";    //Controlador Primário do MCPBB - MCP em Sobrecarga
  String PC_HL_MCPBB_AFBB_ESVAZAUTO               = "%MW6069.7";    //Acoplamento Fluido MCPBB - Esvaziando em Auto
  String PC_HL_MCPBB_CTRPRI_QQALNREC              = "%MW6069.8";    //Controlador Primário do MCPBB - Qualquer Alarme não Reconhecido
//String PC_HL_SPARE_DISP_0186                    = "%MW6069.9";    //SPARE
//String PC_HL_SPARE_DISP_0187                    = "%MW6069.10";   //SPARE
//String PC_HL_SPARE_DISP_0188                    = "%MW6069.11";   //SPARE
//String PC_HL_SPARE_DISP_0189                    = "%MW6069.12";   //SPARE
//String PC_HL_SPARE_DISP_0190                    = "%MW6069.13";   //SPARE
//String PC_HL_SPARE_DISP_0191                    = "%MW6069.14";   //SPARE
//String PC_HL_SPARE_DISP_0192                    = "%MW6069.15";   //SPARE
  String PC_HL_TBGAS_CTRPRI_PLALIMNTP             = "%MW6800.0";    //Controlador Primário da TG - PLA Limitado por NTP
  String PC_HL_TBGAS_CTRPRI_PLALIMTORQUE          = "%MW6800.1";    //Controlador Primário da TG - PLA Limitado por Torque
  String PC_HL_TBGAS_CTRPRI_PLALIMT54             = "%MW6800.2";    //Controlador Primário da TG - PLA Limitado por T5.4
  String PC_HL_TBGAS_CTRPRI_MTALTAVIBGG           = "%MW6800.3";    //Controlador Primário da TG - Muito Alta Vibração GG
  String PC_HL_TBGAS_CTRPRI_MTALTAVIBTP           = "%MW6800.4";    //Controlador Primário da TG - Muito Alta Vibração TP
  String PC_HL_TBGAS_CTRPRI_ALTAVIBGG             = "%MW6800.5";    //Controlador Primário da TG - Alta Vibração GG
  String PC_HL_TBGAS_CTRPRI_ALTAVIBTP             = "%MW6800.6";    //Controlador Primário da TG - Alta Vibração TP
  String PC_HL_TBGAS_CTRPRI_PLALIMPLA             = "%MW6800.7";    //Controlador Primário da TG - PLA Limitado por PLA
  String PC_HL_TBGAS_CTRPRI_ALARMECOMUM           = "%MW6800.8";    //Controlador Primário da TG - Alarme Comum
  String PC_HL_TBGAS_CTRPRI_NPARADA               = "%MW6800.9";    //Controlador Primário da TG - Não Parada
  String PC_HL_TBGAS_CTRPRI_PRNDO                 = "%MW6800.10";   //Controlador Primário da TG - Parando
  String PC_HL_TBGAS_CTRPRI_EMOPERACAO            = "%MW6800.11";   //Controlador Primário da TG - Em Operação
  String PC_HL_TBGAS_CTRPRI_LT7500_STALL          = "%MW6800.12";   //Controlador Primário da TG - Stall no GG
  String PC_HL_TBGAS_CTRPRI_PRNDOEMAUTO           = "%MW6800.13";   //Controlador Primário da TG - Parando em Auto
  String PC_HL_TBGAS_CTRPRI_PRNDOEMEMERG          = "%MW6800.14";   //Controlador Primário da TG - Parando em Emerg.
  String PC_HL_TBGAS_CTRPRI_EMPRDINCENDIO         = "%MW6800.15";   //Controlador Primário da TG - Em parada de incêndio
  String PC_HL_TBGAS_CTRPRI_PRDAUTONEXEC          = "%MW6801.0";    //Controlador Primário da TG - Parada Automática Não Executada
  String PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL           = "%MW6801.1";    //Controlador Primário da TG - Falha Circuito Externo Prd. Emerg.
  String PC_HL_TBGAS_CTRPRI_CIRPRDINCFL           = "%MW6801.2";    //Controlador Primário da TG - Falha Circuito Externo Prd. Incêndio
  String PC_HL_TBGAS_CTRPRI_EMREM                 = "%MW6801.3";    //Controlador Primário da TG - Em Remoto
  String PC_HL_TBGAS_CTRPRI_BATOVER1LIG           = "%MW6801.4";    //Controlador Primário da TG - Battle Override 1 Ligado
  String PC_HL_TBGAS_CTRPRI_BATOVER2LIG           = "%MW6801.5";    //Controlador Primário da TG - Battle Override 2 Ligado
  String PC_HL_TBGAS_CTRPRI_QQALNREC              = "%MW6801.6";    //Controlador Primário da TG - Qualquer Alarme Não Reconhecido
  String PC_HL_TBGAS_CTRPRI_PTNDOEMOP             = "%MW6801.7";    //Controlador Primário da TG - Partindo em Operação
  String PC_HL_TBGAS_CTRPRI_INCENDIO              = "%MW6801.8";    //Controlador Primário da TG - Incêndio
  String PC_HL_TBGAS_CTRPRI_GT7500_STALL          = "%MW6801.9";    //Controlador Primário da TG - PLA Limitado por PLA
//String PC_HL_SPARE_DISP_205                     = "%MW6801.10";   //SPARE
//String PC_HL_SPARE_DISP_206                     = "%MW6801.11";   //SPARE
//String PC_HL_SPARE_DISP_207                     = "%MW6801.12";   //SPARE
//String PC_HL_SPARE_DISP_208                     = "%MW6801.13";   //SPARE
//String PC_HL_SPARE_DISP_209                     = "%MW6801.14";   //SPARE
//String PC_HL_SPARE_DISP_210                     = "%MW6801.15";   //SPARE
//String PC_HL_SPARE_DISP_211                     = "%MW6801.0";    //SPARE
//String PC_HL_SPARE_DISP_201                     = "%MW6802.1";    //SPARE
//String PC_HL_SPARE_DISP_202                     = "%MW6802.2";    //SPARE
//String PC_HL_SPARE_DISP_203_2                   = "%MW6802.3";    //SPARE
//String PC_HL_SPARE_DISP_204_2                   = "%MW6802.4";    //SPARE

//ENTRADA ANALÓGICA
  String PC_HA_ERSBE_MODSBE_EIXOBERPM	        = "%MF6308";    //Módulo Secundário de BE - Rotação do Eixo de Boreste
  String PC_HA_ERSBB_MODSBB_EIXOBBRPM	        = "%MF6310";    //Módulo Secundário de BB - Rotação do Eixo de Bombordo
  String PC_HA_ERHBC_MODHID_OLPRESS     	= "%MF6312";    //Módulo Hidráulico da ER - Pressão de Óleo Lubrificante
  String PC_HA_HPCBE_MODHID_OLPRESS	        = "%MF6314";    //Módulo Hidráulico do HPC de BE - Pressão de Óleo Lubrificante
  String PC_HA_HPCBE_MODHID_OLTEMP	        = "%MF6316";    //Módulo Hidráulico do HPC de BE - Temperatura de Óleo
  String PC_HA_HPCBB_MODHID_OLPRESS	        = "%MF6318";    //Módulo Hidráulico do HPC de BB - Pressão de Óleo Lubrificante
  String PC_HA_HPCBB_MODHID_OLTEMP	        = "%MF6320";    //Módulo Hidráulico do HPC de BB - Temperatura de Óleo
//String PC_HA_SPARE_DISP_0008	                = "%MF6322";    //SPARE - Sinal Analógico Reservado ou Não Usado
  String PC_HA_HPCBE_UDOHPC_PASSOBEPOS	        = "%MF6324";    //Unidade Distribuidora de Oléo do HPC de BE - Posição de Passo da Hélice de Boreste
  String PC_HA_HPCBB_UDOHPC_PASSOBBPOS	        = "%MF6326";    //Unidade Distribuidora de Oléo do HPC de BB - Posição de Passo da Hélice de Bombordo
//String PC_HA_SPARE_DISP_0011	                = "%MF6328";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0012	                = "%MF6330";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0013	                = "%MF6332";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0014	                = "%MF6334";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0015	                = "%MF6336";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0016	                = "%MF6338";    //SPARE - Sinal Analógico Reservado ou Não Usado
  String PC_HA_ERHBC_MODHID_OLTEMP	        = "%MF6346";    //Módulo Hidráulico da ER - Temperatura de Óleo Lubrificante
  String PC_HA_ERPBC_K2MPRI_MANCAL1TEMP	        = "%MF6348";    //Módulo Primário - Temperatura do Mancal 1
  String PC_HA_ERPBC_K2MPRI_MANCAL2TEMP	        = "%MF6350";    //Módulo Primário - Temperatura do Mancal 2
  String PC_HA_ERPBC_K2MPRI_MANCAL3TEMP	        = "%MF6352";    //Módulo Primário - Temperatura do Mancal 3
  String PC_HA_ERPBC_K2MPRI_MANCAL4TEMP	        = "%MF6354";    //Módulo Primário - Temperatura do Mancal 4
  String PC_HA_ERPBC_K2MPRI_MANCAL5TEMP	        = "%MF6356";    //Módulo Primário - Temperatura do Mancal 5
  String PC_HA_ERPBC_K2MPRI_MANCAL6TEMP	        = "%MF6358";    //Módulo Primário - Temperatura do Mancal 6
  String PC_HA_ERPBC_K2MPRI_MANCAL7TEMP	        = "%MF6360";    //Módulo Primário - Temperatura do Mancal 7
  String PC_HA_ERPBC_K2MPRI_MANCAL8TEMP	        = "%MF6362";    //Módulo Primário - Temperatura do Mancal 8
  String PC_HA_ERPBC_K2MPRI_MANCAL9TEMP	        = "%MF6364";    //Módulo Primário - Temperatura do Mancal 9
  String PC_HA_ERPBC_K2MPRI_MANCAL10TEMP	= "%MF6366";    //Módulo Primário - Temperatura do Mancal 10
//String PC_HA_SPARE_DISP_0028	                = "%MF6368";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0029	                = "%MF6370";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0030	                = "%MF6372";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0031	                = "%MF6374";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0032	                = "%MF6376";    //SPARE - Sinal Analógico Reservado ou Não Usado
  String PC_HA_ERSBE_K3MSEC_MANCAL1TEMP	        = "%MF6378";    //Módulo Secundário BE - Temperatura do Mancal 1
  String PC_HA_ERSBE_K3MSEC_MANCAL2TEMP	        = "%MF6380";    //Módulo Secundário BE - Temperatura do Mancal 2
  String PC_HA_ERSBE_K3MSEC_MANCAL3TEMP	        = "%MF6382";    //Módulo Secundário BE - Temperatura do Mancal 3
  String PC_HA_ERSBE_K3MSEC_MANCAL4TEMP	        = "%MF6384";    //Módulo Secundário BE - Temperatura do Mancal 4
  String PC_HA_ERSBE_K3MSEC_MANCAL5TEMP	        = "%MF6386";    //Módulo Secundário BE - Temperatura do Mancal 5
  String PC_HA_ERSBE_K3MSEC_MANCAL6TEMP	        = "%MF6388";    //Módulo Secundário BE - Temperatura do Mancal 6
  String PC_HA_ERSBE_K3MSEC_MANCAL7TEMP	        = "%MF6390";    //Módulo Secundário BE - Temperatura do Mancal 7
  String PC_HA_ERSBE_K3MSEC_MANCAL8TEMP	        = "%MF6392";    //Módulo Secundário BE - Temperatura do Mancal 8
  String PC_HA_ERSBB_K4MSEC_MANCAL1TEMP	        = "%MF6394";    //Módulo Secundário BB - Temperatura do Mancal 1
  String PC_HA_ERSBB_K4MSEC_MANCAL2TEMP	        = "%MF6396";    //Módulo Secundário BB - Temperatura do Mancal 2
  String PC_HA_ERSBB_K4MSEC_MANCAL3TEMP	        = "%MF6398";    //Módulo Secundário BB - Temperatura do Mancal 3
  String PC_HA_ERSBB_K4MSEC_MANCAL4TEMP	        = "%MF6400";    //Módulo Secundário BB - Temperatura do Mancal 4
  String PC_HA_ERSBB_K4MSEC_MANCAL5TEMP	        = "%MF6402";    //Módulo Secundário BB - Temperatura do Mancal 5
  String PC_HA_ERSBB_K4MSEC_MANCAL6TEMP	        = "%MF6404";    //Módulo Secundário BB - Temperatura do Mancal 6
  String PC_HA_ERSBB_K4MSEC_MANCAL7TEMP	        = "%MF6406";    //Módulo Secundário BB - Temperatura do Mancal 7
  String PC_HA_ERSBB_K4MSEC_MANCAL8TEMP	        = "%MF6408";    //Módulo Secundário BB - Temperatura do Mancal 8
  String PC_HA_MCPBE_CTRPRI_RPM	                = "%MF6410";    //Controlador Primário do MCPBE - RPM
  String PC_HA_MCPBE_AFBE_OLTEMP	        = "%MF6412";    //Acoplamento Fluido MCPBE - Temperatura de Óleo Lub.
  String PC_HA_MCPBE_AFBE_OLPRESS	        = "%MF6414";    //Acoplamento Fluido MCPBE - Pressão de Óleo Lub.
  String PC_HA_MCPBE_CTRPRI_CREMALPOSIC	        = "%MF6416";    //Controlador Primário do MCPBE - Posição de Cremalheira
  String PC_HA_MCPBE_CTRPRI_CARGA	        = "%MF6418";    //Controlador Primário do MCPBE - Carga
  String PC_HA_MCPBE_CTRPRI_ADTEMP	        = "%MF6420";    //Controlador Primário do MCPBE - Temperatura de Água Doce
  String PC_HA_MCPBE_CTRPRI_OLPRESS	        = "%MF6422";    //Controlador Primário do MCPBE - Pressão de Óleo Lub.
//String PC_HA_SPARE_DISP_056	                = "%MF6424";    //SPARE - Sinal Analógico Reservado ou Não Usado
  String PC_HA_MCPBB_CTRPRI_RPM	                = "%MF6426";    //Controlador Primário do MCPBB - RPM
  String PC_HA_MCPBB_AFBB_OLTEMP	        = "%MF6428";    //Acoplamento Fluido MCPBB - Temperatura de Óleo Lub.
  String PC_HA_MCPBB_AFBB_OLPRESS	        = "%MF6430";    //Acoplamento Fluido MCPBB - Pressão de Óleo Lub.
  String PC_HA_MCPBB_CTRPRI_CREMALPOSIC	        = "%MF6432";    //Controlador Primário do MCPBB - Posição de Cremalheira
  String PC_HA_MCPBB_CTRPRI_CARGA	        = "%MF6434";    //Controlador Primário do MCPBB - Carga
  String PC_HA_MCPBB_CTRPRI_ADTEMP	        = "%MF6436";    //Controlador Primário do MCPBB - Temperatura de Água Doce
  String PC_HA_MCPBB_CTRPRI_OLPRESS	        = "%MF6438";    //Controlador Primário do MCPBB - Pressão de Óleo Lub.
//String PC_HA_SPARE_DISP_0064	                = "%MF6440";    //SPARE - Sinal Analógico Reservado ou Não Usado
  String PC_HA_TBGAS_CTRPRI_PLAPOSIC    	= "%MF6442";    //Controlador Primário da TG - Posição PLA
  String PC_HA_TBGAS_CTRPRI_NGG	                = "%MF6444";    //Controlador Primário da TG - NGG
  String PC_HA_TBGAS_CTRPRI_NTP	                = "%MF6446";    //Controlador Primário da TG - NTP
  String PC_HA_TBGAS_CTRPRI_T54	                = "%MF6448";    //Controlador Primário da TG - T5.4
//String PC_HA_SPARE_DISP_0069	                = "%MF6450";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0070	                = "%MF6452";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0071          	= "%MF6454";    //SPARE - Sinal Analógico Reservado ou Não Usado
//String PC_HA_SPARE_DISP_0072          	= "%MF6456";    //SPARE - Sinal Analógico Reservado ou Não Usado


//TRANSFERENCIA
  String PC_SL_SCM_SCM_EMAUTO  	          = "%MW28000.1";
  String PC_SL_SCM_HPCBE_AUMENTARPASSO    = "%MW28000.3";
  String PC_SL_SCM_HPCBE_DIMINUIRPASSO    = "%MW28000.4";
  String PC_SL_SCM_HPCBB_AUMENTARPASSO    = "%MW28000.5";
  String PC_SL_SCM_HPCBB_DIMINUIRPASSO    = "%MW28000.6";
  String PC_SL_SCM_MCPBE_AUMENTARRPM      = "%MW28000.7";
  String PC_SL_SCM_MCPBE_DIMINUIRRPM      = "%MW28000.8";
  String PC_SL_SCM_MCPBB_AUMENTARRPM      = "%MW28000.9";
  String PC_SL_SCM_MCPBB_DIMINUIRRPM      = "%MW28000.10";
  String PC_SL_SCM_TBGAS_AUMENTARPLA      = "%MW28000.11";
  String PC_SL_SCM_TBGAS_DIMINUIRPLA      = "%MW28000.12";
  String CP_SL_SCM_SMR_EMMR               = "%MW301.0";

  String CP_SL_MANREM_SCM_EMAUTO	  = "%MW820.1";
  String CP_SL_MANREM_HPCBE_AUMENTARPASSO = "%MW820.2";
  String CP_SL_MANREM_HPCBE_DIMINUIRPASSO = "%MW820.3";
  String CP_SL_MANREM_HPCBB_AUMENTARPASSO = "%MW820.4";
  String CP_SL_MANREM_HPCBB_DIMINUIRPASSO = "%MW820.5";
  String CP_SL_MANREM_MCPBE_AUMENTARRPM	  = "%MW820.6";
  String CP_SL_MANREM_MCPBE_DIMINUIRRPM	  = "%MW820.7";
  String CP_SL_MANREM_MCPBB_AUMENTARRPM	  = "%MW820.8";
  String CP_SL_MANREM_MCPBB_DIMINUIRRPM	  = "%MW820.9";
  String CP_SL_MANREM_TBGAS_AUMENTARNTP	  = "%MW820.10";
  String CP_SL_MANREM_TBGAS_DIMINUIRNTP	  = "%MW820.11";
  String PC_SL_MANREM_SMR_EMMR_MWO        = "%MW5500.12";
  String PC_SL_MANREM_SMR_EMMR_MWS        = "%MW8400.12";


  //ELPN - COMANDOS
  String CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO          = "MW3508.8";
  String CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWS          = "%MW6508.8";
  String CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO       = "%MW3508.9";
  String CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWS       = "%MW6508.9";
  String CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO     = "%MW3508.10";
  String CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWS     = "%MW6508.10";
  String CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO      = "%MW3510.8";
  String CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWS      = "%MW6510.8";
  String CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO         = "%MW3508.11";
  String CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWS         = "%MW6508.11";
  String CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO     = "MW3508.12";
  String CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWS     = "%MW6508.12";
  String CP_HL_ERHBC_BBELPN_LIGAR                  = "%MW210.0";
  String CP_HL_ERHBC_BBELPN_DESLIGAR               = "%MW210.1";
  String CP_HL_ERHBC_BBELPN_PARAREMERG             = "%MW210.2";
  String CP_HL_ERHBC_BBELPN_LIBPEMERG              = "%MW212.3";
  String CP_HL_ERHBC_BBELPN_MANUAL                 = "%MW210.3";
  String CP_HL_ERHBC_BBELPN_AUTOMATICO             = "%MW210.4";
  //HPC BE - COMANDOS
  //P1
  String CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO          = "%MW3508.14";
  String CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWS          = "%MW6508.14";
  String CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO       = "%MW3508.15";
  String CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWS       = "%MW6508.15";
  String CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO     = "%MW3509.0";
  String CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWS     = "%MW6509.0";
  String CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO     = "%MW3509.1";
  String CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWS     = "%MW6509.1";
  String CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO         = "%MW3509.2";
  String CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWS         = "%MW6509.2";
  String CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO      = "%MW3510.9";
  String CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWS      = "%MW6510.9";
  String CP_HL_HPCBE_BBP1BE_LIGAR                  = "%MW210.5";
  String CP_HL_HPCBE_BBP1BE_DESLIGAR               = "%MW210.6";
  String CP_HL_HPCBE_BBP1BE_PARAREMERG             = "%MW210.7";
  String CP_HL_HPCBE_BBP1BE_AUTOMATICO             = "%MW210.8";
  String CP_HL_HPCBE_BBP1BE_MANUAL                 = "%MW210.9";
  String CP_HL_HPCBE_BBP1BE_LIBPEMERG              = "%MW212.4";
  //P3
  String CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO          = "%MW3509.3";
  String CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWS          = "%MW6509.3";
  String CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO       = "%MW3509.4";
  String CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWS       = "%MW6509.4";
  String CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO     = "%MW3509.5";
  String CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWS     = "%MW6509.5";
  String CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO     = "%MW3509.6";
  String CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWS     = "%MW6509.6";
  String CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO         = "%MW3509.7";
  String CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWS         = "%MW6509.7";
  String CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO      = "%MW3510.10";
  String CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWS      = "%MW6510.10";
  String CP_HL_HPCBE_BBP3BE_LIGAR                  = "%MW210.10";
  String CP_HL_HPCBE_BBP3BE_DESLIGAR               = "%MW210.11";
  String CP_HL_HPCBE_BBP3BE_PARAREMERG             = "%MW210.12";
  String CP_HL_HPCBE_BBP3BE_AUTOMATICO             = "%MW210.13";
  String CP_HL_HPCBE_BBP3BE_MANUAL                 = "%MW210.14";
  String CP_HL_HPCBE_BBP3BE_LIBPEMERG              = "%MW212.5";
  //MNB BX VELOC
  String CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO    = "%MW3509.8";
  String CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWS    = "%MW6509.8";
  String CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO = "%MW3509.9";
  String CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWS = "%MW6509.9";
  String CP_HL_HPCBE_HDWSCM_LIGARRPMBX            = "%MW210.15";
  String CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX         = "%MW211.0";
  //HPC BB - COMANDOS
  //P1
  String CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO          = "%MW3509.11";
  String CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWS          = "%MW6509.11";
  String CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO       = "%MW3509.12";
  String CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWS       = "%MW6509.12";
  String CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO     = "%MW3509.13";
  String CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWS     = "%MW6509.13";
  String CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO     = "%MW3509.14";
  String CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWS     = "%MW6509.14";
  String CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO         = "%MW3509.15";
  String CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWS         = "%MW6509.15";
  String CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO      = "%MW3510.11";
  String CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWS      = "%MW6510.11";
  String CP_HL_HPCBB_BBP1BB_LIGAR                  = "%MW211.2";
  String CP_HL_HPCBB_BBP1BB_DESLIGAR               = "%MW211.3";
  String CP_HL_HPCBB_BBP1BB_PARAREMERG             = "%MW211.4";
  String CP_HL_HPCBB_BBP1BB_AUTOMATICO             = "%MW211.5";
  String CP_HL_HPCBB_BBP1BB_MANUAL                 = "%MW211.6";
  String CP_HL_HPCBB_BBP1BB_LIBPEMERG              = "%MW212.6";
  //P3
  String CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO          = "%MW3510.0";
  String CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWS          = "%MW6510.0";
  String CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO       = "%MW3510.1";
  String CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWS       = "%MW6510.1";
  String CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO     = "%MW3510.2";
  String CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWS     = "%MW6510.2";
  String CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO     = "%MW3510.3";
  String CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWS     = "%MW6510.3";
  String CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO         = "%MW3510.4";
  String CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWS         = "%MW6510.4";
  String CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO      = "%MW3510.12";
  String CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWS      = "%MW6510.12";
  String CP_HL_HPCBB_BBP3BB_LIGAR                  = "%MW211.7";
  String CP_HL_HPCBB_BBP3BB_DESLIGAR               = "%MW211.8";
  String CP_HL_HPCBB_BBP3BB_PARAREMERG             = "%MW211.9";
  String CP_HL_HPCBB_BBP3BB_AUTOMATICO             = "%MW211.10";
  String CP_HL_HPCBB_BBP3BB_MANUAL                 = "%MW211.11";
  String CP_HL_HPCBB_BBP3BB_LIBPEMERG              = "%MW212.7";
  //MNB BX VELOC
  String CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO     = "%MW3510.5";
  String CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWS     = "%MW6510.5";
  String CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO  = "%MW3510.6";
  String CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWS  = "%MW6510.6";
  String CP_HL_HPCBB_HDWSCM_LIGARRPMBX             = "%MW211.12";
  String CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX          = "%MW211.13";
  //PASSO HPC BE
  String CP_HL_HPCBE_CTRBKP_AUMENTARPASSO          = "%MW211.15";
  String CP_HL_HPCBE_CTRBKP_DIMINUIRPASSO          = "%MW212.0";
  String PC_HA_HPCBE_UDOHPC_PASSOBEPOS_SCM         = "%MF6170";
  String CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO   = "%MW3528.0";
  String CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWS   = "%MF6528";
  //PASSO HPC BB
  String CP_HL_HPCBB_CTRBKP_AUMENTARPASSO          = "%MW212.1";
  String CP_HL_HPCBB_CTRBKP_DIMINUIRPASSO          = "%MW212.2";
  String PC_HA_HPCBB_UDOHPC_PASSOBBPOS_SCM         = "%MF6172";
  String CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO   = "%MW3528.1";
  String CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWS   = "%MF6530";
  //SSS K1
  String CP_HL_ERPBC_SSSK1_TRAVAR                  = "%MW212.11";
  String CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO          = "%MW3508.0";
  String CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWS          = "%MW6508.0";
  //SSS K2
  String CP_HL_ERPBC_SSSK2_TRAVAR                  = "%MW212.12";
  String CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO          = "%MW3508.1";
  String CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWS          = "%MW6508.1";
  //SSS K3
  String CP_HL_ERSBB_SSSK3_DESTRAVAR               = "%MW212.14";
  String CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO          = "%MW3508.3";
  String CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWS          = "%MW6508.3";
  //SSS K4
  String CP_HL_ERSBE_SSSK4_DESTRAVAR               = "%MW212.13";
  String CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO          = "%MW3508.2";
  String CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWS          = "%MW6508.2";
  //MCP BE
  String CP_HL_MCPBE_CTRPRI_PARARNORMAL            = "%MW213.0";
  String CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO        = "%MW3573.5";
  String CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWS        = "%MW6580.1";
  String CP_HL_MCPBE_CTRPRI_AUMENTARRPM            = "%MW213.1";
  String CP_HL_MCPBE_CTRPRI_DIMINUIRRPM            = "%MW213.2";
  String CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO   = "%MW3573.0";
  String CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWS   = "%MF6573";
  String CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWO    = "%MW4083.0";
  String CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWS    = "%MF7427";
  String CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWO    = "%MW4093.0";
  String CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWS    = "%MF7439";
  String PC_SA_MCPBE_ECS_MCPRPM_SCM                = "%MF7162";
  String CP_HL_MCPBE_AFBE_ENCHER                   = "%MW213.3";
  String CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO      = "%MW4068.5";
  String CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWS      = "%MW7412.5";
  String CP_HL_MCPBE_AFBE_ESVAZIAR                 = "%MW213.4";
  String CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO    = "%MW4068.6";
  String CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWS    = "%MW7412.6";
  String CP_HL_MCPBE_CTRPRI_DESLBATOVER            = "%MW213.5";
  String CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO        = "%MW3573.7";
  String CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWS        = "%MW6580.3";
//String CP_HL_MCPBE_CTRPRI_EMMR                   = "%MW213.6";
  String CP_HL_MCPBE_CTRPRI_RECONALARM             = "%MW213.7";
  String CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO    = "%MW4068.4";
  String CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWS    = "%MW7412.4";
  String CP_HL_MCPBE_CTRPRI_SILENCIARBUZ           = "%MW213.8";
  String CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO     = "%MW4068.3";
  String CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWS     = "%MW7412.3";
  //MCP BB
  String CP_HL_MCPBB_CTRPRI_PARARNORMAL            = "%MW214.0";
  String CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO        = "%MW3589.5";
  String CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWS        = "%MW6596.1";
  String CP_HL_MCPBB_CTRPRI_AUMENTARRPM            = "%MW214.1";
  String CP_HL_MCPBB_CTRPRI_DIMINUIRRPM            = "%MW214.2";
  String CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO   = "%MW3589.0";
  String CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWS   = "%MF6589";
  String CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWO    = "%MW4583.0";
  String CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWS    = "%MF7927";
  String CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWO    = "%MW4593.0";
  String CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWS    = "%MF7939";
  String PC_SA_MCPBB_ECS_MCPRPM_SCM                = "%MF7662";
  String CP_HL_MCPBB_AFBB_ENCHER                   = "%MW214.3";
  String CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO      = "%MW4568.5";
  String CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWS      = "%MW7912.5";
  String CP_HL_MCPBB_AFBB_ESVAZIAR                 = "%MW214.4";
  String CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO    = "%MW4568.6";
  String CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWS    = "%MW7912.6";
  String CP_HL_MCPBB_CTRPRI_DESLBATOVER            = "%MW214.5";
  String CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO        = "%MW3589.7";
  String CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWS        = "%MW6596.3";
//String CP_HL_MCPBB_CTRPRI_EMMR                   = "%MW214.6";
  String CP_HL_MCPBB_CTRPRI_RECONALARM             = "%MW214.7";
  String CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO    = "%MW4568.4";
  String CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWS    = "%MW7912.4";
  String CP_HL_MCPBB_CTRPRI_SILENCIARBUZ           = "%MW214.8";
  String CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO     = "%MW4568.3";
  String CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWS     = "%MW7912.3";
  //TG
  String CP_HL_TBGAS_CTRPRI_AUMENTARPLA            = "%MW215.0";
  String CP_HL_TBGAS_CTRPRI_DIMINUIRPLA            = "%MW215.1";
  String CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO         = "%MW5408.1";
  String CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWS         = "%MF8304";
  String PC_HA_TBGAS_MCTG_PLA         		   = "%MF6204";
  String CP_HL_TBGAS_CTRPRI_DESLBATOVER1           = "%MW215.2";
  String CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO      = "%MW5400.11";
  String CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWS      = "%MW8300.11";
  String CP_HL_TBGAS_CTRPRI_DESLBATOVER2           = "%MW215.3";
  String CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO      = "%MW5400.12";
  String CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWS      = "%MW8300.12";
  String CP_HL_TBGAS_CTRPRI_RECONALARM             = "%MW215.4";
  String CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO          = "%MW5400.13";
  String CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWS          = "%MW8300.13";
  String CP_HL_TBGAS_CTRPRI_SILENCIARBUZ           = "%MW215.5";
  String CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO         = "%MW5400.15";
  String CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWS         = "%MW8300.15";
//String CP_HL_TBGAS_CTRPRI_EMMR                   = "%MW215.6";
  String CP_HL_TBGAS_CTRPRI_LIMITARTORQUE          = "%MW215.7";
  String CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO      = "%MW3556.0";
  String CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWS      = "%MW6556.0";
  String CP_HL_TBGAS_CTRPRI_PARAREMERG             = "%MW212.15";
  String CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO       = "%MW5400.3";
  String CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWS       = "%MW8300.3";


  bool em_mr = false;

/* ============================================================================================================================================================================*/

//CONFIGURAÇÃO MODBUS
String IP_SUP          = "120.40.0.1";
String IP_PLT          = "10.7.40.1";
String IP_MR           = "192.168.0.1";
String CONTADOR_CONEXAO= "%MW33000";
String NomeForm        = "JÚLIO DE NORONHA - MR";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;
int    lista           = 0;
bool   modooperacao    = true;

bool   perdaconexao_SCM    = false;
int    Varredura_SCM       = 0;
float  VALOR_ANTIGO_SCM    = 0;
bool   contador_ok_SCM     = false;
int    contador_scan_SCM   = 0;
int    numeroquedas_SCM    = 0;
int    lista_SCM           = 0;


//CONFIGURAÇÃO GERAL
bool monitor_ativo = false;
bool conectado = true;

bool fechando = true;


//TESTE HPC
bool subindo_hpcbe  = true;
bool descendo_hpcbe = false;
bool subindo_hpcbb  = true;
bool descendo_hpcbb = false;
//TESTA ALARME
bool teste_alarme   = false;
int  alarmecontador = 0;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;
//INCIALIZAÇÃO DO DRIVER
//TModBusScanner CLP ( frmPrincipal, QUANTUM, 2, 2 );
TModBusTCPDriver  CLP_MR ( frmPrincipal,  IP_MR, PREMIUM);
TModBusTCPDriver CLP_SUP ( frmPrincipal, IP_SUP, QUANTUM);
//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnConectarClick(TObject *Sender)
{
if (btnConectar->Caption == "Conectar") {
                btnConectar->Caption = "Desconectar";
                btnHabilitar->Enabled = true;
                //btnSimul->Enabled = true;
                //btnMonitMODBUS->Enabled = false;
                grbDiagnostico->Visible = true;
                AnsiString TimeStamp;

                //IP = IP_MR;
                CLP_MR.Open(IP_MR);
                CLP_SUP.Open(IP_SUP);

                lblIP_MR->Caption = "MR: " + IP_MR;
                lblIP_SCM->Caption = "SCM: " + IP_SUP;

                DateTimeToString( TimeStamp, AnsiString( "DD/MM/YY hh:nn:ss" ), Now() );

                lblInicioPrograma->Caption = TimeStamp;
                lblInicioPrograma->Visible = true;
                lblEndereco->Caption = CONTADOR_CONEXAO;
                lblEndereco->Visible = true;
                lblWatchdogEx->Visible = true;

                lblEndereco_SCM->Caption = CONTADOR_CONEXAO;
                lblEndereco_SCM->Visible = true;
                lblWatchdogEx_SCM->Visible = true;

                tmrStarting->Enabled = true;
                conectado = true;
        }
        else{
                btnConectar->Caption = "Conectar";
                //if (monitor_ativo == true){
                //        btnMonitor->Click();
                //}
                tmrLeitura->Enabled = false;

                //
                //DESANIMAR OBJETOS AQUI
                lblHPCBB_UDOHPC_PASSOBBPOS->Caption = "--";
                lblHPCBE_UDOHPC_PASSOBEPOS->Caption = "--";
                //

                btnHabilitar->Enabled = false;
                //btnSimul->Enabled = false;
                grbDiagnostico->Visible = false;
                //btnMonitMODBUS->Enabled = true;
                CLP_MR.Close();
                CLP_SUP.Close();

                //tmrLeitura->Enabled = false;
                tmrReconecta->Enabled = false;
                tmrConexaoWatch->Enabled = false;
                tmrLista->Enabled = false;
                lblModbusStatus->Caption = "Desativado - Leitura Inativa";
                conectado = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{
        frmPrincipal->Height = 445;
        frmPrincipal->Width =  800;
        frmPrincipal->Top = 0;
        frmPrincipal->Left = 0;

        lblIP_MR->Caption = "MR: " + IP_MR;
        lblIP_SCM->Caption = "SCM: " + IP_SUP;

        frmPrincipal->Caption = NomeForm;

        //Application->MessageBox("O Uso deste programa deve ser efetuado apenas por pessoal autorizado,\no uso incorreto do mesmo pode causar mal funcionamento em equipamentos\nassim como risco de danos materiais e humanos \n\nEquipe do IPqM - SCM - Automação (142)\nAo fechar verificar se todos os endereços foram zerados", "Disclaimer", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrStartingTimer(TObject *Sender)
{
//-------------------------------------------------------------
//ACIONA TODOS OS ENDEREÇOS DE SIMULAÇÃO
      /*  for (int i = 3100; i <= 3107; i++){ //ARM IO 1   Digitais
                String tempMW = "%MW" ;
                tempMW += i;
                CLP_MR.WR(tempMW, 0xFFFF);
        }
        for (int i = 3066; i <= 3069; i++){ //PMR   Digitais
                String tempMW = "%MW" ;
                tempMW += i;
                CLP_MR.WR(tempMW, 0xFFFF);
        }
        for (int i = 3800; i <= 3802; i++){ //PMV   Digitais
                String tempMW = "%MW" ;
                tempMW += i;
                CLP_MR.WR(tempMW, 0xFFFF);
        }*/
//-------------------------------------------------------------

        //frmPrincipal->Caption = NomeForm + " - Pronto (CLP_MR" + IP + ")";

        lblModbusStatus->Caption = "Pronto (CLP MR " + IP_MR + ") e (CLP SCM " + IP_SUP + ")";
        tmrLeitura->Enabled = true;

        lblBufferR->Visible = true;
        lblBufferW->Visible = true;
        lblBufferEx->Visible = true;
        lblLista->Visible = true;

        lblBufferR_SCM->Visible = true;
        lblBufferW_SCM->Visible = true;
        lblBufferEx_SCM->Visible = true;
        lblLista_SCM->Visible = true;

        if (tmrConexaoWatch->Enabled == false){
                tmrConexaoWatch->Enabled = true;
        }

        tmrLista->Enabled = true;

        btnReset->Enabled = true;
        btnReset->Visible = false;


//FIM DA INICIALIZAÇÃO
        tmrStarting->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrReconectaTimer(TObject *Sender)
{
//RECONEXÃO
        CLP_MR.Open(IP_MR);
        CLP_SUP.Open(IP_SUP);
        tmrReconecta->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrListaTimer(TObject *Sender)
{
        lista = CLP_MR.TamBufWR();
        lblLista->Caption = CLP_MR._thread->buffersRecebidos.size();
        lblBufferR->Caption = "RD: " + String (CLP_MR.TamBufRD());
        lblBufferW->Caption = "WR: " + String (CLP_MR.TamBufWR());

        lista_SCM = CLP_SUP.TamBufWR();
        lblLista_SCM->Caption = CLP_SUP._thread->buffersRecebidos.size();
        lblBufferR_SCM->Caption = "RD: " + String (CLP_SUP.TamBufRD());
        lblBufferW_SCM->Caption = "WR: " + String (CLP_SUP.TamBufWR());

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
                //btnReset->Visible = false; // DESATIVADO PROVISORIAMENTE
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
                //btnReset->Visible = true; // DESATIVADO PROVISORIAMENTE
        }

        if (lista_SCM > 100) {
                //tmrLeitura->Enabled = false;
                //shpAguarde->Top = 440;
                //shpAguarde->Left = 0;
                //shpAguarde->Width = 657;
                //shpAguarde->Height = 49;
                shpAguarde_SCM->Visible = true;
                //lblAguarde->Top = 8;
                //lblAguarde->Left = 0;
                //lblAguarde->Width = 649;
                //lblAguarde->Height = 29;
                lblAguarde_SCM->Visible = true;
                //btnReset->Visible = false; // DESATIVADO PROVISORIAMENTE
        }
        else{
                //if (lista < 10 ){
                //        tmrLeitura->Enabled = true;
                //}
                //shpAguarde->Top = 5000;
                //shpAguarde->Left = 5000;
                //shpAguarde->Width = 0;
                //shpAguarde->Height = 0;
                shpAguarde_SCM->Visible = false;
                //lblAguarde->Top = 5000;
                //lblAguarde->Left = 5000;
                //lblAguarde->Width = 0;
                //lblAguarde->Height = 0;
                lblAguarde_SCM->Visible = false;
                //btnReset->Visible = true; // DESATIVADO PROVISORIAMENTE
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrConexaoWatchTimer(TObject *Sender)
{
//TIMER DE VERIFICAÇÃO DE CONEXÃO
        lblProgramaAtual->Visible = true;
        //MR
        lblTamListaIDs->Visible = true;
        lblQuedas->Visible = true;
        lblWatchdog->Visible = true;
        //SCM
        lblTamListaIDs_SCM->Visible = true;
        lblQuedas_SCM->Visible = true;
        lblWatchdog_SCM->Visible = true;

        if ( VALOR_ANTIGO != CLP_MR.RD( CONTADOR_CONEXAO ) ){
                //contador_ok = true;
                contador_scan = 0;
        }
        else{
                //contador_ok = false;
                if ( contador_scan <= 3 ){
                        contador_scan++;
                }
        }

        if ( VALOR_ANTIGO_SCM != CLP_SUP.RD( CONTADOR_CONEXAO ) ){
                //contador_ok = true;
                contador_scan_SCM = 0;
        }
        else{
                //contador_ok = false;
                if ( contador_scan_SCM <= 3 ){
                        contador_scan_SCM++;
                }
        }

        if ( contador_scan <= 3 ){
                contador_ok = true;
        }
        else{
                contador_ok = false;
        }

        if ( contador_scan_SCM <= 3 ){
                contador_ok_SCM = true;
        }
        else{
                contador_ok_SCM = false;
        }

        lblTamListaIDs->Caption = "ID Usados: " + String (CLP_MR._thread->listaIDsUsados.size());

        lblTamListaIDs_SCM->Caption = "ID Usados: " + String (CLP_SUP._thread->listaIDsUsados.size());

        if (CLP_MR.Conectado() == 0 ){ //|| contador_ok == false){
               perdaconexao = true;
               numeroquedas++;
               CLP_MR.Close();
               CLP_SUP.Close();
               //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Inativa";
               //frmPrincipal->Caption = NomeForm + " - Pronto - Leitura Inativa";
               lblModbusStatus->Caption = "Pronto - Leitura Inativa";

               tmrLeitura->Enabled = false;
               if (tmrReconecta->Enabled == false){
                       tmrReconecta->Enabled = true;
               }
        }

        if (CLP_SUP.Conectado() == 0 ){ //|| contador_ok == false){
               perdaconexao_SCM = true;
               numeroquedas_SCM++;
               CLP_SUP.Close();
               CLP_MR.Close();
               //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Inativa";
               //frmPrincipal->Caption = NomeForm + " - Pronto - Leitura Inativa";
               lblModbusStatus->Caption = "Pronto - Leitura Inativa";

               tmrLeitura->Enabled = false;
               if (tmrReconecta->Enabled == false){
                       tmrReconecta->Enabled = true;
               }
        }

        if ( (CLP_MR.Conectado() != 0 && perdaconexao == true) && (CLP_SUP.Conectado() != 0 && perdaconexao_SCM == true) ){//&& contador_ok == true){
               perdaconexao = false;
               perdaconexao_SCM = false;
               tmrLeitura->Enabled = true;
               //tmrStarting->Enabled = true;
        }

        if ((CLP_MR.Conectado() != 0 && perdaconexao == false) && (CLP_SUP.Conectado() != 0 && perdaconexao_SCM == false) ){//&& contador_ok == true){
                switch(Varredura){
                        case 0:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                //frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa \\";
                                lblModbusStatus->Caption = "Pronto (" + IP_MR + ") e (" + IP_SUP + ") - Leitura Ativa \\";
                                break;
                        case 1:
                                //lblConexao->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                //frmPrincipal->Caption = NomeForm + " - Pronto (" + IP + ") - Leitura Ativa /";
                                lblModbusStatus->Caption = "Pronto (" + IP_MR + ") e (" + IP_SUP + ") - Leitura Ativa /";
                                Varredura = -1;
                                break;
               }
               Varredura++;
        }
//        lblLista->Caption = CLP_MR._listaCmdSimples.size();
//        lblLista->Caption = CLP_MR.TamBufWR();
//        lblLista->Caption = CLP_MR._thread->buffersRecebidos.size();
//        lblConexao->Refresh();

        AnsiString TimeStamp;

        DateTimeToString( TimeStamp, AnsiString( "DD/MM/YY hh:nn:ss" ), Now() );

        lblProgramaAtual->Caption = TimeStamp;

        lblQuedas->Caption = "Fall: " + String (numeroquedas);

        lblQuedas_SCM->Caption = "Fall: " + String (numeroquedas_SCM);

        VALOR_ANTIGO = CLP_MR.RD( CONTADOR_CONEXAO );
        VALOR_ANTIGO_SCM = CLP_SUP.RD( CONTADOR_CONEXAO );
        lblWatchdog->Caption = VALOR_ANTIGO;
        lblWatchdog_SCM->Caption = VALOR_ANTIGO_SCM;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrLeituraTimer(TObject *Sender)
{
 // INSERIR FEED BACKS AQUI
        if (CLP_MR.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWO) == 1) {
                shpHPCBE_UDOHPC_PASSOBEPOS->Brush->Color = clLime;
        }else{
                shpHPCBE_UDOHPC_PASSOBEPOS->Brush->Color = clWhite;
        }
        lblHPCBE_UDOHPC_PASSOBEPOS->Caption = CLP_MR.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS);
        lblHPCBE_UDOHPC_PASSOBEPOS->Caption = FormatFloat("0.##",lblHPCBE_UDOHPC_PASSOBEPOS->Caption.ToDouble()) + " %";

        if (CLP_MR.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWO) == 1) {
                shpHPCBB_UDOHPC_PASSOBBPOS->Brush->Color = clLime;
        }else{
                shpHPCBB_UDOHPC_PASSOBBPOS->Brush->Color = clWhite;
        }
        lblHPCBB_UDOHPC_PASSOBBPOS->Caption = CLP_MR.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS);
        lblHPCBB_UDOHPC_PASSOBBPOS->Caption = FormatFloat("0.##",lblHPCBB_UDOHPC_PASSOBBPOS->Caption.ToDouble()) + " %";

         if (em_mr == true) {
                shpemmr->Brush->Color = clLime;
         }else{
                shpemmr->Brush->Color = clWhite;
         }

         if (tmrComandosMR->Enabled == true ) {
                shpComandos->Brush->Color = clLime;
         }else{
                shpComandos->Brush->Color = clWhite;
         }

         if (tmrEqualSCM->Enabled == true ) {
                shpDados->Brush->Color = clLime;
         }else{
                shpDados->Brush->Color = clWhite;
         }

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHabilitarClick(TObject *Sender)
{
 if (btnHabilitar->Caption == "Habilitar") {
                btnHabilitar->Caption = "Desabilitar";

                CLP_MR.WR(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWO, 1);
                CLP_MR.WR(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWO, 1);


                btnConectar->Enabled = false;

                btnTesteHPC->Enabled = true;

                for (int i = 3100; i <= 3112; i++){ //ARM IO 1   Digitais  E TODAS ANALÓGICAS 3107-3112
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0xFFFF);
                }
                for (int i = 3066; i <= 3069; i++){ //PMR   Digitais
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0xFFFF);
                }
                for (int i = 3800; i <= 3802; i++){ //PMV   Digitais
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0xFFFF);
                }

                CLP_MR.WR("%MW25000", 0xFFFF); //TRANSFERENCIA SCM MR
                CLP_MR.WR("%MW25000.2", 0);

                btnTesteAlarmes->Enabled = true;

                btnEqualSCM->Enabled = true;

                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO  , 1);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO, 1);
                CLP_SUP.WR(PC_SL_MANREM_SMR_EMMR_MWO         , 1);

                if ((CLP_MR.RD(PC_HL_SMR_CPCCM_SOLICMR) == 1) || (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS) == 1)){
                        imgSolicAuto->Visible = false;
                        imgSolicMR->Visible = true;
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS, 0);
                         CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICAUTO         , 0);
                        em_mr = true;
                }
                else{
                        if ((CLP_MR.RD(PC_HL_SMR_CPCCM_SOLICAUTO) == 1) || (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS) == 1)){
                                imgSolicAuto->Visible = true;
                                imgSolicMR->Visible = false;
                                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS, 0);
                                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICMR         , 0);
                                em_mr = false;
                        }else{
                                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS, 1);
                                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS  , 0);
                                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICAUTO         , 1);
                                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICMR           , 0);
                                imgSolicAuto->Visible = true;
                                imgSolicMR->Visible = false;
                                em_mr = false;
                        }
                }


                shpHabilitaSelecao->Visible = false;

                tmrTransferencia->Enabled = true;

        }else{
                btnHabilitar->Caption = "Habilitar";

                CLP_MR.WR(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWO, 0);
                CLP_MR.WR(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWO, 0);

                for (int i = 3100; i <= 3112; i++){ //ARM IO 1   Digitais  E TODAS ANALÓGICAS 3107-3112
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0x0000);
                }
                for (int i = 3066; i <= 3069; i++){ //PMR   Digitais
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0x0000);
                }
                for (int i = 3800; i <= 3802; i++){ //PMV   Digitais
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0x0000);
                }

                CLP_MR.WR("%MW25000", 0x0000); //TRANSFERENCIA SCM MR

                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE P1
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE P3
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO, 0);
                }

                //HPC BB P1
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BB P3
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BB MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO, 0);
                }

                if (CLP_SUP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO, 0);
                }

                if (CLP_SUP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO, 0);
                }

                //MCP BE
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO, 0);
                }

                //MCP BB
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO, 0);
                }

                //TG
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO, 0);
                }

                //SSS K1
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO, 0);
                }
                //SSS K2
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO, 0);
                }
                //SSS K3
                if (CLP_SUP.RD(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO, 0);
                }
                //SSS K4
                if (CLP_SUP.RD(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO, 0);
                }

                btnTesteHPC->Enabled = false;
                btnTesteAlarmes->Enabled = false;

                btnEqualSCM->Enabled = false;

                tmrHabilitar->Enabled = true;
                btnConectar->Enabled = true;

                shpHabilitaSelecao->Visible = true;

                tmrTransferencia->Enabled = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormDestroy(TObject *Sender)
{
        /*if (CLP_MR.Conectado() == 0){
                CLP_MR.Open(IP);
        }

        CLP_MR.WR(CP_HL_ERSBE_SSSK4_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERSBB_SSSK3_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK2_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK1_TRAVAR_MWO, 0);

        CLP_MR.WR(CP_HL_ERSBE_SSSK4_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERSBB_SSSK3_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK2_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK1_TRAVAR_MWS, 0);

        while (fechando == true){
                if (CLP_MR.RD(CP_HL_ERSBE_SSSK4_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERSBB_SSSK3_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR_MWO) == 0){
                        fechando = false;
                }

                if (CLP_MR.RD(CP_HL_ERSBE_SSSK4_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERSBB_SSSK3_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR_MWS) == 0){
                        fechando = false;
                }

        }
        CLP_MR.Close(); */
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormHide(TObject *Sender)
{
        /*if (CLP_MR.Conectado() == 0){
                CLP_MR.Open(IP);
        }

        CLP_MR.WR(CP_HL_ERSBE_SSSK4_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERSBB_SSSK3_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK2_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK1_TRAVAR_MWO, 0);

        CLP_MR.WR(CP_HL_ERSBE_SSSK4_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERSBB_SSSK3_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK2_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK1_TRAVAR_MWS, 0);

        while (fechando == true){
                if (CLP_MR.RD(CP_HL_ERSBE_SSSK4_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERSBB_SSSK3_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR_MWO) == 0){
                        fechando = false;
                }

                if (CLP_MR.RD(CP_HL_ERSBE_SSSK4_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERSBB_SSSK3_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR_MWS) == 0){
                        fechando = false;
                }

        }
        CLP_MR.Close();*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        /*if (CLP_MR.Conectado() == 0){
                CLP_MR.Open(IP);
        }

        CLP_MR.WR(CP_HL_ERSBE_SSSK4_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERSBB_SSSK3_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK2_TRAVAR_MWO, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK1_TRAVAR_MWO, 0);

        CLP_MR.WR(CP_HL_ERSBE_SSSK4_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERSBB_SSSK3_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK2_TRAVAR_MWS, 0);
        CLP_MR.WR(CP_HL_ERPBC_SSSK1_TRAVAR_MWS, 0);

        while (fechando == true){
                if (CLP_MR.RD(CP_HL_ERSBE_SSSK4_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERSBB_SSSK3_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR_MWO) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR_MWO) == 0){
                        fechando = false;
                }

                if (CLP_MR.RD(CP_HL_ERSBE_SSSK4_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERSBB_SSSK3_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR_MWS) == 0){
                        fechando = false;
                }
                if (CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR_MWS) == 0){
                        fechando = false;
                }

        }
        CLP_MR.Close();*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTesteHPCClick(TObject *Sender)
{
        if (btnTesteHPC->Caption == "Iniciar Teste HPC"){
                btnTesteHPC->Caption = "Parar Teste HPC";
                tmrTesteHPC->Interval = txtTesteHPC->Text.ToInt();
                tmrTesteHPC->Enabled  = true;
                if ( CLP_MR.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS) >= 100 ){
                        descendo_hpcbe = true;
                         subindo_hpcbe = false;
                }else{
                        subindo_hpcbe = true;
                        descendo_hpcbe = false;
                }

                if ( CLP_MR.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS) >= 100 ){
                        descendo_hpcbb = true;
                         subindo_hpcbb = false;
                }else{
                         subindo_hpcbb = true;
                        descendo_hpcbb = false;
                }
        }
        else{
                btnTesteHPC->Caption = "Iniciar Teste HPC";
                tmrTesteHPC->Enabled  = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrTesteHPCTimer(TObject *Sender)
{
        float valor_hpcbb = 0;
        float valor_hpcbe = 0;
        float Step        = txtTesteHPC_st->Text.ToDouble();

        valor_hpcbe = CLP_MR.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS);
        valor_hpcbb = CLP_MR.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS);

        if (valor_hpcbe <= 100 && subindo_hpcbe == true){
                valor_hpcbe = valor_hpcbe + Step;
                if ( valor_hpcbe >= 100){
                        descendo_hpcbe = true;
                         subindo_hpcbe = false;
                }
        }else{
                if ( (valor_hpcbe >= -100) && descendo_hpcbe == true){
                        valor_hpcbe = valor_hpcbe - Step;
                }
                if (valor_hpcbe <= -100 ){
                        subindo_hpcbe = true;
                        descendo_hpcbe = false;
                }
        }

        CLP_MR.WR(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS, valor_hpcbe);

        if (valor_hpcbb <= 100 && subindo_hpcbb == true){
                valor_hpcbb = valor_hpcbb + Step;
                if ( valor_hpcbb >= 100){
                        descendo_hpcbb = true;
                         subindo_hpcbb = false;
                }
        }else{
                if ( (valor_hpcbb >= -100) && descendo_hpcbb == true){
                        valor_hpcbb = valor_hpcbb - Step;
                }
                if (valor_hpcbb <= -100 ){
                        subindo_hpcbb = true;
                        descendo_hpcbb = false;
                }
        }

        CLP_MR.WR(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS, valor_hpcbb);

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrTesteAlarmesTimer(TObject *Sender)
{
	if (teste_alarme == true){
			teste_alarme = false;
			shpTesteAlarmes->Brush->Color = clRed;
			shpTesteAlarmes2->Brush->Color = clWhite;
			CLP_MR.WR(PC_HL_SODPG_BEROD1_SOBREC1, 1);
			CLP_MR.WR(PC_HL_SODPG_BEROD2_SOBREC1, 1);
			CLP_MR.WR(PC_HL_SODPG_FCOD1_PRESSDIFALTA, 1);
			CLP_MR.WR(PC_HL_SODPG_FCOD2_PRESSDIFALTA, 1);
			CLP_MR.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, 1);
			CLP_MR.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, 1);
			CLP_MR.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, 1);
			CLP_MR.WR(PC_HL_AOLTG_PUROL1_PERDASELO, 1);
			CLP_MR.WR(PC_HL_AOLTG_PUROL2_PERDASELO, 1);
			CLP_MR.WR(PC_HL_TBGAS_ARCOMB_PDIFAL, 1);
			CLP_MR.WR(PC_HL_TBGAS_ARRESF_PDIFAL, 1);
			CLP_MR.WR(PC_HL_TBGAS_ARCOMB_QQPORTAABER, 1);
			CLP_MR.WR(PC_HL_TBGAS_ARRESF_QQPORTAABER, 1);
			CLP_MR.WR(PC_HL_ERHBC_BBELPN_SOBREC, 1);
			CLP_MR.WR(PC_HL_ERHBC_BBELPN_MOTPNLIG, 1);
			CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPDIFAL, 1);
			CLP_MR.WR(PC_HL_AOLTG_TAOL14_NIVELBAIXO, 1);
			CLP_MR.WR(PC_HL_RASRG_OERHPC_PRESSBAIXA, 1);
			CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPBX, 1);
			CLP_MR.WR(PC_HL_ERPBC_CATRAC_DESENGATADO, 1);
			CLP_MR.WR(PC_HL_ERPBC_FREIO_DESENGATADO, 1);
			CLP_MR.WR(PC_HL_ERSBE_SSSK4_OLPBX, 1);
			CLP_MR.WR(PC_HL_ERSBB_SSSK3_OLPBX, 1);
			CLP_MR.WR(PC_HL_HPCBE_CTRPRI_FALHA, 1);
			CLP_MR.WR(PC_HL_HPCBE_MODHID_OLPBX, 1);
			CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT1PDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT2PDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBE_BBP1BE_SOBREC, 1);
			CLP_MR.WR(PC_HL_HPCBE_BBP3BE_SOBREC, 1);
			CLP_MR.WR(PC_HL_HPCBE_TQGRAV_NIVELBAIXO, 1);
			CLP_MR.WR(PC_HL_HPCBB_CTRPRI_FALHA, 1);
			CLP_MR.WR(PC_HL_HPCBB_MODHID_OLPBX, 1);
			CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT1PDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT2PDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, 1);
			CLP_MR.WR(PC_HL_HPCBB_BBP1BB_SOBREC, 1);
			CLP_MR.WR(PC_HL_HPCBB_BBP3BB_SOBREC, 1);
			CLP_MR.WR(PC_HL_HPCBB_TQGRAV_NIVELBAIXO, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_TQEXPADNVBX, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_RPMMCPIOFL, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CREMALIOFL, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CARGAIOFL, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_EMLIMCARGA, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_MCPEMSOBREC, 1);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_QQALNREC, 1);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_TQEXPADNVBX, 1);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_RPMMCPIOFL, 1);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CREMALIOFL, 1);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CARGAIOFL, 1);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_EMLIMCARGA, 1);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_MCPEMSOBREC, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMNTP, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMTORQUE, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMT54, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBGG, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBTP, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBGG, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBTP, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMPLA, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALARMECOMUM, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_LT7500_STALL, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDINCFL, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_QQALNREC, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_INCENDIO, 1);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_GT7500_STALL, 1);
	}else{
			teste_alarme = true;
			shpTesteAlarmes->Brush->Color = clWhite;
			shpTesteAlarmes2->Brush->Color = clLime;
			CLP_MR.WR(PC_HL_SODPG_BEROD1_SOBREC1, 0);
			CLP_MR.WR(PC_HL_SODPG_BEROD2_SOBREC1, 0);
			CLP_MR.WR(PC_HL_SODPG_FCOD1_PRESSDIFALTA, 0);
			CLP_MR.WR(PC_HL_SODPG_FCOD2_PRESSDIFALTA, 0);
			CLP_MR.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, 0);
			CLP_MR.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, 0);
			CLP_MR.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, 0);
			CLP_MR.WR(PC_HL_AOLTG_PUROL1_PERDASELO, 0);
			CLP_MR.WR(PC_HL_AOLTG_PUROL2_PERDASELO, 0);
			CLP_MR.WR(PC_HL_TBGAS_ARCOMB_PDIFAL, 0);
			CLP_MR.WR(PC_HL_TBGAS_ARRESF_PDIFAL, 0);
			CLP_MR.WR(PC_HL_TBGAS_ARCOMB_QQPORTAABER, 0);
			CLP_MR.WR(PC_HL_TBGAS_ARRESF_QQPORTAABER, 0);
			CLP_MR.WR(PC_HL_ERHBC_BBELPN_SOBREC, 0);
			CLP_MR.WR(PC_HL_ERHBC_BBELPN_MOTPNLIG, 0);
			CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPDIFAL, 0);
			CLP_MR.WR(PC_HL_AOLTG_TAOL14_NIVELBAIXO, 0);
			CLP_MR.WR(PC_HL_RASRG_OERHPC_PRESSBAIXA, 0);
			CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPBX, 0);
			CLP_MR.WR(PC_HL_ERPBC_CATRAC_DESENGATADO, 0);
			CLP_MR.WR(PC_HL_ERPBC_FREIO_DESENGATADO, 0);
			CLP_MR.WR(PC_HL_ERSBE_SSSK4_OLPBX, 0);
			CLP_MR.WR(PC_HL_ERSBB_SSSK3_OLPBX, 0);
			CLP_MR.WR(PC_HL_HPCBE_CTRPRI_FALHA, 0);
			CLP_MR.WR(PC_HL_HPCBE_MODHID_OLPBX, 0);
			CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT1PDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT2PDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBE_BBP1BE_SOBREC, 0);
			CLP_MR.WR(PC_HL_HPCBE_BBP3BE_SOBREC, 0);
			CLP_MR.WR(PC_HL_HPCBE_TQGRAV_NIVELBAIXO, 0);
			CLP_MR.WR(PC_HL_HPCBB_CTRPRI_FALHA, 0);
			CLP_MR.WR(PC_HL_HPCBB_MODHID_OLPBX, 0);
			CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT1PDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT2PDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, 0);
			CLP_MR.WR(PC_HL_HPCBB_BBP1BB_SOBREC, 0);
			CLP_MR.WR(PC_HL_HPCBB_BBP3BB_SOBREC, 0);
			CLP_MR.WR(PC_HL_HPCBB_TQGRAV_NIVELBAIXO, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_TQEXPADNVBX, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_RPMMCPIOFL, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CREMALIOFL, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CARGAIOFL, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_EMLIMCARGA, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_MCPEMSOBREC, 0);
			CLP_MR.WR(PC_HL_MCPBE_CTRPRI_QQALNREC, 0);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_TQEXPADNVBX, 0);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_RPMMCPIOFL, 0);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CREMALIOFL, 0);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CARGAIOFL, 0);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_EMLIMCARGA, 0);
			CLP_MR.WR(PC_HL_MCPBB_CTRPRI_MCPEMSOBREC, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMNTP, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMTORQUE, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMT54, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBGG, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBTP, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBGG, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBTP, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMPLA, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALARMECOMUM, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_LT7500_STALL, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDINCFL, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_QQALNREC, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_INCENDIO, 0);
			CLP_MR.WR(PC_HL_TBGAS_CTRPRI_GT7500_STALL, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnTesteAlarmesClick(TObject *Sender)
{
        if (btnTesteAlarmes->Caption == "Iniciar Teste Alarme"){
                btnTesteAlarmes->Caption = "Parar Teste Alarme";
                tmrTesteAlarmes->Interval = txtTesteAlarmes->Text.ToInt();
                tmrTesteAlarmes->Enabled  = true;
                alarmecontador = 0;
                lblTesteAlarmes2->Caption = alarmecontador;
                tmrTesteAlarmes2->Enabled = true;
                if (teste_alarme == true){
					teste_alarme = false;
					shpTesteAlarmes->Brush->Color = clRed;
					shpTesteAlarmes2->Brush->Color = clWhite;
					CLP_MR.WR(PC_HL_SODPG_BEROD1_SOBREC1, 1);
					CLP_MR.WR(PC_HL_SODPG_BEROD2_SOBREC1, 1);
					CLP_MR.WR(PC_HL_SODPG_FCOD1_PRESSDIFALTA, 1);
					CLP_MR.WR(PC_HL_SODPG_FCOD2_PRESSDIFALTA, 1);
					CLP_MR.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, 1);
					CLP_MR.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, 1);
					CLP_MR.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, 1);
					CLP_MR.WR(PC_HL_AOLTG_PUROL1_PERDASELO, 1);
					CLP_MR.WR(PC_HL_AOLTG_PUROL2_PERDASELO, 1);
					CLP_MR.WR(PC_HL_TBGAS_ARCOMB_PDIFAL, 1);
					CLP_MR.WR(PC_HL_TBGAS_ARRESF_PDIFAL, 1);
					CLP_MR.WR(PC_HL_TBGAS_ARCOMB_QQPORTAABER, 1);
					CLP_MR.WR(PC_HL_TBGAS_ARRESF_QQPORTAABER, 1);
					CLP_MR.WR(PC_HL_ERHBC_BBELPN_SOBREC, 1);
					CLP_MR.WR(PC_HL_ERHBC_BBELPN_MOTPNLIG, 1);
					CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPDIFAL, 1);
					CLP_MR.WR(PC_HL_AOLTG_TAOL14_NIVELBAIXO, 1);
					CLP_MR.WR(PC_HL_RASRG_OERHPC_PRESSBAIXA, 1);
					CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPBX, 1);
					CLP_MR.WR(PC_HL_ERPBC_CATRAC_DESENGATADO, 1);
					CLP_MR.WR(PC_HL_ERPBC_FREIO_DESENGATADO, 1);
					CLP_MR.WR(PC_HL_ERSBE_SSSK4_OLPBX, 1);
					CLP_MR.WR(PC_HL_ERSBB_SSSK3_OLPBX, 1);
					CLP_MR.WR(PC_HL_HPCBE_CTRPRI_FALHA, 1);
					CLP_MR.WR(PC_HL_HPCBE_MODHID_OLPBX, 1);
					CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT1PDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT2PDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBE_BBP1BE_SOBREC, 1);
					CLP_MR.WR(PC_HL_HPCBE_BBP3BE_SOBREC, 1);
					CLP_MR.WR(PC_HL_HPCBE_TQGRAV_NIVELBAIXO, 1);
					CLP_MR.WR(PC_HL_HPCBB_CTRPRI_FALHA, 1);
					CLP_MR.WR(PC_HL_HPCBB_MODHID_OLPBX, 1);
					CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT1PDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT2PDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, 1);
					CLP_MR.WR(PC_HL_HPCBB_BBP1BB_SOBREC, 1);
					CLP_MR.WR(PC_HL_HPCBB_BBP3BB_SOBREC, 1);
					CLP_MR.WR(PC_HL_HPCBB_TQGRAV_NIVELBAIXO, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_TQEXPADNVBX, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_RPMMCPIOFL, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CREMALIOFL, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CARGAIOFL, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_EMLIMCARGA, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_MCPEMSOBREC, 1);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_QQALNREC, 1);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_TQEXPADNVBX, 1);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_RPMMCPIOFL, 1);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CREMALIOFL, 1);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CARGAIOFL, 1);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_EMLIMCARGA, 1);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_MCPEMSOBREC, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMNTP, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMTORQUE, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMT54, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBGG, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBTP, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBGG, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBTP, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMPLA, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALARMECOMUM, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_LT7500_STALL, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDINCFL, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_QQALNREC, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_INCENDIO, 1);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_GT7500_STALL, 1);
			}else{
					teste_alarme = true;
					shpTesteAlarmes->Brush->Color = clWhite;
					shpTesteAlarmes2->Brush->Color = clLime;
					CLP_MR.WR(PC_HL_SODPG_BEROD1_SOBREC1, 0);
					CLP_MR.WR(PC_HL_SODPG_BEROD2_SOBREC1, 0);
					CLP_MR.WR(PC_HL_SODPG_FCOD1_PRESSDIFALTA, 0);
					CLP_MR.WR(PC_HL_SODPG_FCOD2_PRESSDIFALTA, 0);
					CLP_MR.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, 0);
					CLP_MR.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, 0);
					CLP_MR.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, 0);
					CLP_MR.WR(PC_HL_AOLTG_PUROL1_PERDASELO, 0);
					CLP_MR.WR(PC_HL_AOLTG_PUROL2_PERDASELO, 0);
					CLP_MR.WR(PC_HL_TBGAS_ARCOMB_PDIFAL, 0);
					CLP_MR.WR(PC_HL_TBGAS_ARRESF_PDIFAL, 0);
					CLP_MR.WR(PC_HL_TBGAS_ARCOMB_QQPORTAABER, 0);
					CLP_MR.WR(PC_HL_TBGAS_ARRESF_QQPORTAABER, 0);
					CLP_MR.WR(PC_HL_ERHBC_BBELPN_SOBREC, 0);
					CLP_MR.WR(PC_HL_ERHBC_BBELPN_MOTPNLIG, 0);
					CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPDIFAL, 0);
					CLP_MR.WR(PC_HL_AOLTG_TAOL14_NIVELBAIXO, 0);
					CLP_MR.WR(PC_HL_RASRG_OERHPC_PRESSBAIXA, 0);
					CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPBX, 0);
					CLP_MR.WR(PC_HL_ERPBC_CATRAC_DESENGATADO, 0);
					CLP_MR.WR(PC_HL_ERPBC_FREIO_DESENGATADO, 0);
					CLP_MR.WR(PC_HL_ERSBE_SSSK4_OLPBX, 0);
					CLP_MR.WR(PC_HL_ERSBB_SSSK3_OLPBX, 0);
					CLP_MR.WR(PC_HL_HPCBE_CTRPRI_FALHA, 0);
					CLP_MR.WR(PC_HL_HPCBE_MODHID_OLPBX, 0);
					CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT1PDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT2PDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBE_BBP1BE_SOBREC, 0);
					CLP_MR.WR(PC_HL_HPCBE_BBP3BE_SOBREC, 0);
					CLP_MR.WR(PC_HL_HPCBE_TQGRAV_NIVELBAIXO, 0);
					CLP_MR.WR(PC_HL_HPCBB_CTRPRI_FALHA, 0);
					CLP_MR.WR(PC_HL_HPCBB_MODHID_OLPBX, 0);
					CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT1PDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT2PDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, 0);
					CLP_MR.WR(PC_HL_HPCBB_BBP1BB_SOBREC, 0);
					CLP_MR.WR(PC_HL_HPCBB_BBP3BB_SOBREC, 0);
					CLP_MR.WR(PC_HL_HPCBB_TQGRAV_NIVELBAIXO, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_TQEXPADNVBX, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_RPMMCPIOFL, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CREMALIOFL, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CARGAIOFL, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_EMLIMCARGA, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_MCPEMSOBREC, 0);
					CLP_MR.WR(PC_HL_MCPBE_CTRPRI_QQALNREC, 0);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_TQEXPADNVBX, 0);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_RPMMCPIOFL, 0);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CREMALIOFL, 0);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CARGAIOFL, 0);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_EMLIMCARGA, 0);
					CLP_MR.WR(PC_HL_MCPBB_CTRPRI_MCPEMSOBREC, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMNTP, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMTORQUE, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMT54, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBGG, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBTP, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBGG, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBTP, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMPLA, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALARMECOMUM, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_LT7500_STALL, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDINCFL, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_QQALNREC, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_INCENDIO, 0);
					CLP_MR.WR(PC_HL_TBGAS_CTRPRI_GT7500_STALL, 0);
			}
        }
        else{
                btnTesteAlarmes->Caption = "Iniciar Teste Alarme";
                tmrTesteAlarmes->Enabled  = false;
                tmrTesteAlarmes->Enabled  = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrTesteAlarmes2Timer(TObject *Sender)
{
        alarmecontador++;
        if (alarmecontador > (tmrTesteAlarmes->Interval / 1000) ){
                alarmecontador = 1;
        }
        lblTesteAlarmes2->Caption = alarmecontador;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrEqualSCMTimer(TObject *Sender)
{
        double tmp__MR    = 0;
        double tmp_SCM    = 0;
        String frmt_MR    = "";
        String frmtSCM    = "";
        int    DI_tmp__MR = 0;
        int    DI_tmp_SCM = 0;


        tmp__MR =  CLP_MR.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS);
        tmp_SCM = CLP_SUP.RD("%MF6172");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS);
        tmp_SCM = CLP_SUP.RD("%MF6170");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWS, frmtSCM.ToDouble());
        }

        

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_MODSBE_EIXOBERPM);
        tmp_SCM = CLP_SUP.RD("%MF6154");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_MODSBE_EIXOBERPM, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_MODSBB_EIXOBBRPM);
        tmp_SCM = CLP_SUP.RD("%MF6156");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_MODSBB_EIXOBBRPM, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERHBC_MODHID_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF6158");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERHBC_MODHID_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBE_MODHID_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF6162");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBE_MODHID_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBE_MODHID_OLTEMP);
        tmp_SCM = CLP_SUP.RD("%MF6164");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBE_MODHID_OLTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBB_MODHID_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF6166");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBB_MODHID_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBB_MODHID_OLTEMP);
        tmp_SCM = CLP_SUP.RD("%MF6168");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBB_MODHID_OLTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS);
        tmp_SCM = CLP_SUP.RD("%MF6170");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBE_UDOHPC_PASSOBEPOS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS);
        tmp_SCM = CLP_SUP.RD("%MF6172");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_HPCBB_UDOHPC_PASSOBBPOS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERHBC_MODHID_OLTEMP);
        tmp_SCM = CLP_SUP.RD("%MF6266");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERHBC_MODHID_OLTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL1TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6268");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL1TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL2TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6270");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL2TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL3TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6272");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL3TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL4TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6274");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL4TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL5TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6276");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL5TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL6TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6278");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL6TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL7TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6280");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL7TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL8TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6282");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL8TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL9TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6284");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL9TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERPBC_K2MPRI_MANCAL10TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6286");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERPBC_K2MPRI_MANCAL10TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL1TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6334");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL1TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL2TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6336");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL2TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL3TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6338");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL3TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL4TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6340");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL4TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL5TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6342");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL5TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL6TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6344");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL6TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL7TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6346");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL7TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBE_K3MSEC_MANCAL8TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6348");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBE_K3MSEC_MANCAL8TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL1TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6350");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL1TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL2TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6352");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL2TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL3TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6354");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL3TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL4TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6356");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL4TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL5TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6358");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL5TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL6TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6360");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL6TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL7TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6362");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL7TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_ERSBB_K4MSEC_MANCAL8TEMP);
        tmp_SCM = CLP_SUP.RD("%MF6364");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_ERSBB_K4MSEC_MANCAL8TEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_CTRPRI_RPM);
        tmp_SCM = CLP_SUP.RD("%MF7162");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_CTRPRI_RPM, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_AFBE_OLTEMP);
        tmp_SCM = CLP_SUP.RD("%MF7148");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_AFBE_OLTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_AFBE_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF7084");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_AFBE_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_CTRPRI_CREMALPOSIC);
        tmp_SCM = CLP_SUP.RD("%MF7206");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_CTRPRI_CREMALPOSIC, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_CTRPRI_CARGA);
        tmp_SCM = CLP_SUP.RD("%MF7174");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_CTRPRI_CARGA, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_CTRPRI_ADTEMP);
        tmp_SCM = CLP_SUP.RD("%MF7096");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_CTRPRI_ADTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBE_CTRPRI_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF7062");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBE_CTRPRI_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_CTRPRI_RPM);
        tmp_SCM = CLP_SUP.RD("%MF7662");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_CTRPRI_RPM, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_AFBB_OLTEMP);
        tmp_SCM = CLP_SUP.RD("%MF7648");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_AFBB_OLTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_AFBB_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF7584");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_AFBB_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_CTRPRI_CREMALPOSIC);
        tmp_SCM = CLP_SUP.RD("%MF7706");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_CTRPRI_CREMALPOSIC, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_CTRPRI_CARGA);
        tmp_SCM = CLP_SUP.RD("%MF7674");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_CTRPRI_CARGA, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_CTRPRI_ADTEMP);
        tmp_SCM = CLP_SUP.RD("%MF7596");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_CTRPRI_ADTEMP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_MCPBB_CTRPRI_OLPRESS);
        tmp_SCM = CLP_SUP.RD("%MF7562");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_MCPBB_CTRPRI_OLPRESS, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_TBGAS_CTRPRI_PLAPOSIC);
        tmp_SCM = CLP_SUP.RD("%MF8204");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_TBGAS_CTRPRI_PLAPOSIC, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_TBGAS_CTRPRI_NGG);
        tmp_SCM = CLP_SUP.RD("%MF8116");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_TBGAS_CTRPRI_NGG, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_TBGAS_CTRPRI_NTP);
        tmp_SCM = CLP_SUP.RD("%MF8120");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_TBGAS_CTRPRI_NTP, frmtSCM.ToDouble());
        }

        tmp__MR =  CLP_MR.RD(PC_HA_TBGAS_CTRPRI_T54);
        tmp_SCM = CLP_SUP.RD("%MF8132");
        frmt_MR = FormatFloat("0.##",tmp__MR);
        frmtSCM = FormatFloat("0.##",tmp_SCM);
        if (frmt_MR != frmtSCM) {
                CLP_MR.WR( PC_HA_TBGAS_CTRPRI_T54, frmtSCM.ToDouble());
        }


        
        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_BEROD1_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6013.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_BEROD1_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_BEROD1_SOBREC1);
        DI_tmp_SCM = CLP_SUP.RD("%MW6013.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_BEROD1_SOBREC1, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_BEROD2_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6013.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_BEROD2_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_BEROD2_SOBREC1);
        DI_tmp_SCM = CLP_SUP.RD("%MW6013.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_BEROD2_SOBREC1, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_FCOD1_PRESSDIFALTA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_FCOD1_PRESSDIFALTA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_FCOD2_PRESSDIFALTA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_FCOD2_PRESSDIFALTA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_TSOD08_NIVELBAIXO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6032.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_TSOD09_NIVELBAIXO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6032.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SODPG_TSOD07_NIVELBAIXO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6032.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_AOLTG_PUROL1_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6013.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_AOLTG_PUROL1_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_AOLTG_PUROL1_PERDASELO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6013.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_AOLTG_PUROL1_PERDASELO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_AOLTG_PUROL2_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6014.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_AOLTG_PUROL2_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_AOLTG_PUROL2_PERDASELO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6014.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_AOLTG_PUROL2_PERDASELO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_ARCOMB_PDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_ARCOMB_PDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_ARRESF_PDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_ARRESF_PDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_ARCOMB_QQPORTAABER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_ARCOMB_QQPORTAABER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_ARRESF_QQPORTAABER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_ARRESF_QQPORTAABER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_EMAUT);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_EMAUT, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_MOTELLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_MOTELLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_SOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_SOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_MOTPNLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_MOTPNLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_MODHID_OLPDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_AOLTG_TAOL14_NIVELBAIXO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6031.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_AOLTG_TAOL14_NIVELBAIXO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_RASRG_OERHPC_PRESSBAIXA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6029.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_RASRG_OERHPC_PRESSBAIXA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_MODHID_OLPBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_MODHID_OLPBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK1_TRAVABER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK1_TRAVABER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK1_NTRAVABER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK1_NTRAVABER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK2_TRAVABER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK2_TRAVABER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK2_NTRAVABER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK2_NTRAVABER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK1_ACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK1_ACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK1_DACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK1_DACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK1_TRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK1_TRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK1_NTRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK1_NTRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK2_ACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6022.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK2_ACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK2_DACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK2_DACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK2_TRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK2_TRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_SSSK2_NTRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_SSSK2_NTRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_CATRAC_DESENGATADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_CATRAC_DESENGATADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERPBC_FREIO_DESENGATADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERPBC_FREIO_DESENGATADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBE_SSSK4_TRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBE_SSSK4_TRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBE_SSSK4_NTRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBE_SSSK4_NTRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBE_SSSK4_OLPBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBE_SSSK4_OLPBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBE_SSSK4_ACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBE_SSSK4_ACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBE_SSSK4_DACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBE_SSSK4_DACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBB_SSSK3_TRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBB_SSSK3_TRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBB_SSSK3_NTRAVACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBB_SSSK3_NTRAVACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBB_SSSK3_OLPBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBB_SSSK3_OLPBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBB_SSSK3_ACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBB_SSSK3_ACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERSBB_SSSK3_DACPL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6023.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERSBB_SSSK3_DACPL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_CTRPRI_FALHA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_CTRPRI_FALHA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_CTRPRI_MANRPMBXSCM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_CTRPRI_MANRPMBXSCM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_CTRBKP_EMOPERACAO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_CTRBKP_EMOPERACAO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_MODHID_OLPBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_MODHID_OLPBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_MODHID_FILT1PDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT1PDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_MODHID_FILT2PDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_MODHID_FILT2PDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_UDOHPC_OLPRESSOK);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_UDOHPC_OLPRESSOK, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_UDOHPC_ZEROTHRUST);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_UDOHPC_ZEROTHRUST, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21APDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_UDOHPC_FILT21BPDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_SOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_SOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_EMAUT);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_EMAUT, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_SOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_SOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_TQGRAV_NIVELBAIXO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6024.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_TQGRAV_NIVELBAIXO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_CTRPRI_FALHA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_CTRPRI_FALHA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_CTRPRI_MANRPMBXSCM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_CTRPRI_MANRPMBXSCM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_CTRBKP_EMOPERACAO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_CTRBKP_EMOPERACAO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_MODHID_OLPBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_MODHID_OLPBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_MODHID_FILT1PDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT1PDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_MODHID_FILT2PDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_MODHID_FILT2PDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_UDOHPC_OLPRESSOK);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_UDOHPC_OLPRESSOK, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_UDOHPC_ZEROTHRUST);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_UDOHPC_ZEROTHRUST, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21APDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_UDOHPC_FILT21BPDIFAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_SOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_SOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_LIGADO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_LIGADO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_EMAUT);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_EMAUT, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_SOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_SOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_TQGRAV_NIVELBAIXO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6025.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_TQGRAV_NIVELBAIXO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_AUTOHDWSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_AUTOHDWSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_AUTOHDWSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_PRDEMGSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_PRDEMGSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP1BE_PRDEMGSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6026.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP1BE_PRDEMGSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_AUTOHDWSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_PRDEMGSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_PRDEMGSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBE_BBP3BE_PRDEMGSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBE_BBP3BE_PRDEMGSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_AUTOHDWSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_PRDEMGSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_PRDEMGSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP1BB_PRDEMGSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP1BB_PRDEMGSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_AUTOHDWSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_PEMERGSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_PEMERGSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_HPCBB_BBP3BB_PEMERGSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_HPCBB_BBP3BB_PEMERGSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_PEMERGSCMLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_PEMERGSCMLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_ERHBC_BBELPN_PEMERGSCMDES);
        DI_tmp_SCM = CLP_SUP.RD("%MW6027.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_ERHBC_BBELPN_PEMERGSCMDES, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SMR_CPCCM_MCPBBPRDEMERG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6033.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SMR_CPCCM_MCPBBPRDEMERG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SMR_CPCCM_TGPRDEMERG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6033.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SMR_CPCCM_TGPRDEMERG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SMR_CPCCM_TGPRDINC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6033.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SMR_CPCCM_TGPRDINC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_SMR_CPCCM_MCPBEPRDEMERG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6033.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_SMR_CPCCM_MCPBEPRDEMERG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_PARTINDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_PARTINDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_VIRANDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_VIRANDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_PARANDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_PARANDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_PARADONORMAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_PARADONORMAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_PRNDOEMEMERG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_PRNDOEMEMERG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_PRNDOEMAUTO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_PRNDOEMAUTO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_BATOVERLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_BATOVERLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_VAZIO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_VAZIO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_ENCHENDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_ENCHENDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_CHEIO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_CHEIO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_ESVAZIANDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_ESVAZIANDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_ALARMECOMUM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_ALARMECOMUM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_BUZLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_BUZLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_TQEXPADNVBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6230.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_TQEXPADNVBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_RPMMCPIOFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_RPMMCPIOFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_CREMALIOFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CREMALIOFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_CARGAIOFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_CARGAIOFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_OKENCHER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_OKENCHER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_OKESVAZIAR);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_OKESVAZIAR, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_ENCHIMENBLQ);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_ENCHIMENBLQ, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_EMLIMCARGA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_EMLIMCARGA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_MCPEMSOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_MCPEMSOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_AFBE_ESVAZAUTO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_AFBE_ESVAZAUTO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBE_CTRPRI_QQALNREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6231.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBE_CTRPRI_QQALNREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_PARTINDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_PARTINDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_VIRANDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_VIRANDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_PARANDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_PARANDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_PARADONORMAL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_PARADONORMAL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_PRNDOEMEMERG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_PRNDOEMEMERG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_PRNDOEMAUTO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_PRNDOEMAUTO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_BATOVERLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_BATOVERLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_VAZIO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_VAZIO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_ENCHENDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_ENCHENDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_CHEIO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_CHEIO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_ESVAZIANDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_ESVAZIANDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_ALARMECOMUM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_ALARMECOMUM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_BUZLIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_BUZLIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_TQEXPADNVBX);
        DI_tmp_SCM = CLP_SUP.RD("%MW6298.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_TQEXPADNVBX, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_RPMMCPIOFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_RPMMCPIOFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_CREMALIOFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CREMALIOFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_CARGAIOFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_CARGAIOFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_OKENCHER);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_OKENCHER, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_OKESVAZIAR);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_OKESVAZIAR, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_ENCHIMENBLQ);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_ENCHIMENBLQ, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_EMLIMCARGA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_EMLIMCARGA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_MCPEMSOBREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_MCPEMSOBREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_AFBB_ESVAZAUTO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_AFBB_ESVAZAUTO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_MCPBB_CTRPRI_QQALNREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6299.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_MCPBB_CTRPRI_QQALNREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PLALIMNTP);
        DI_tmp_SCM = CLP_SUP.RD("%MW8001.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMNTP, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PLALIMTORQUE);
        DI_tmp_SCM = CLP_SUP.RD("%MW8001.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMTORQUE, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PLALIMT54);
        DI_tmp_SCM = CLP_SUP.RD("%MW8002.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMT54, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_MTALTAVIBGG);
        DI_tmp_SCM = CLP_SUP.RD("%MW8005.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBGG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_MTALTAVIBTP);
        DI_tmp_SCM = CLP_SUP.RD("%MW8006.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_MTALTAVIBTP, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_ALTAVIBGG);
        DI_tmp_SCM = CLP_SUP.RD("%MW8005.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBGG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_ALTAVIBTP);
        DI_tmp_SCM = CLP_SUP.RD("%MW8005.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALTAVIBTP, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PLALIMPLA);
        DI_tmp_SCM = CLP_SUP.RD("%MW8001.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PLALIMPLA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_ALARMECOMUM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_ALARMECOMUM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_NPARADA);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.2");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_NPARADA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PRNDO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.3");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PRNDO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_EMOPERACAO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.4");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_EMOPERACAO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_LT7500_STALL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.8");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_LT7500_STALL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PRNDOEMAUTO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PRNDOEMAUTO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PRNDOEMEMERG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.14");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PRNDOEMEMERG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_EMPRDINCENDIO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.15");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_EMPRDINCENDIO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PRDAUTONEXEC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.13");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PRDAUTONEXEC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.5");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDEMGFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_CIRPRDINCFL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.6");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_CIRPRDINCFL, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_EMREM);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.7");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_EMREM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_BATOVER1LIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.9");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_BATOVER1LIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_BATOVER2LIG);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.10");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_BATOVER2LIG, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_QQALNREC);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.11");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_QQALNREC, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_PTNDOEMOP);
        DI_tmp_SCM = CLP_SUP.RD("%MW6195.12");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_PTNDOEMOP, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_INCENDIO);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.1");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_INCENDIO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_HL_TBGAS_CTRPRI_GT7500_STALL);
        DI_tmp_SCM = CLP_SUP.RD("%MW6194.0");

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_HL_TBGAS_CTRPRI_GT7500_STALL, DI_tmp_SCM);
        }






}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEqualSCMClick(TObject *Sender)
{
        if (btnEqualSCM->Caption == "Iniciar Coleta"){
                btnEqualSCM->Caption = "Parar Coleta";
                tmrEqualSCM->Enabled  = true;
                tmrComandosMR->Enabled = true;
        }
        else{
                btnEqualSCM->Caption = "Iniciar Coleta";
                tmrEqualSCM->Enabled  = false;
                tmrComandosMR->Enabled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuSelecaoClick(TObject *Sender)
{
        pnlTestaAlarme->Visible = false;
        pnlTesteHPC->Visible = false;
        pnlSelecao->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuTestaHPCClick(TObject *Sender)
{
        pnlTestaAlarme->Visible = false;
        pnlSelecao->Visible = false;
        pnlTesteHPC->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mnuTestaAlarmesClick(TObject *Sender)
{
        pnlTesteHPC->Visible = false;
        pnlSelecao->Visible = false;
        pnlTestaAlarme->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::imgSolicAutoClick(TObject *Sender)
{
        if (btnEqualSCM->Enabled == true){
                if (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO) == 0) {
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO, 1);
                }
                if (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO) == 0) {
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO, 1);
                }

                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICAUTO          , 0);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS , 0);
                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICMR            , 1);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS   , 1);

                imgSolicMR->Visible = true;
                imgSolicAuto->Visible = false;
                em_mr = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::imgSolicMRClick(TObject *Sender)
{
        if (btnEqualSCM->Enabled == true){
                if (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO) == 0) {
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO, 1);
                }
                if (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO) == 0) {
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO, 1);
                }
                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICMR            , 0);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS   , 0);
                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICAUTO          , 1);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS , 1);

                imgSolicAuto->Visible = true;
                imgSolicMR->Visible = false;
                em_mr = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrTransferenciaTimer(TObject *Sender)
{
        int    DI_tmp__MR = 0;
        int    DI_tmp_SCM = 0;

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_SCM_EMAUTO);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_SCM_EMAUTO);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_SCM_EMAUTO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_HPCBE_AUMENTARPASSO);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_HPCBE_AUMENTARPASSO);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_HPCBE_AUMENTARPASSO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_HPCBE_DIMINUIRPASSO);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_HPCBE_DIMINUIRPASSO);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_HPCBE_DIMINUIRPASSO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_HPCBB_AUMENTARPASSO);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_HPCBB_AUMENTARPASSO);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_HPCBB_AUMENTARPASSO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_HPCBB_DIMINUIRPASSO);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_HPCBB_DIMINUIRPASSO);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_HPCBB_DIMINUIRPASSO, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_MCPBE_AUMENTARRPM);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_MCPBE_AUMENTARRPM);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_MCPBE_AUMENTARRPM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_MCPBE_DIMINUIRRPM);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_MCPBE_DIMINUIRRPM);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_MCPBE_DIMINUIRRPM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_MCPBB_AUMENTARRPM);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_MCPBB_AUMENTARRPM);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_MCPBB_AUMENTARRPM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_MCPBB_DIMINUIRRPM);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_MCPBB_DIMINUIRRPM);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_MCPBB_DIMINUIRRPM, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_TBGAS_AUMENTARPLA);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_TBGAS_AUMENTARNTP);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_TBGAS_AUMENTARPLA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(PC_SL_SCM_TBGAS_DIMINUIRPLA);
        DI_tmp_SCM = CLP_SUP.RD(CP_SL_MANREM_TBGAS_DIMINUIRNTP);

        if ( DI_tmp__MR != DI_tmp_SCM){
                CLP_MR.WR(PC_SL_SCM_TBGAS_DIMINUIRPLA, DI_tmp_SCM);
        }

        DI_tmp__MR = CLP_MR.RD(CP_SL_SCM_SMR_EMMR);
        DI_tmp_SCM = CLP_SUP.RD(PC_SL_MANREM_SMR_EMMR_MWS);

        if ( DI_tmp_SCM != DI_tmp__MR){
                CLP_SUP.WR(PC_SL_MANREM_SMR_EMMR_MWS, DI_tmp__MR);
        }

        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrComandosMRTimer(TObject *Sender)
{

        int    DI_tmp__MR = 0;
        int    DI_tmp_SCM = 0;

        if (em_mr == true){
                //Primeiro colocar em option comandos do SCM
                //Segundo observar atuadores do MR e comandar no SCM pela simulação
                //Terceiro ler a demanda dos MCP , TG e Passo, e incrementar pelo comando do MR

                //ELPN

                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERHBC_BBELPN_LIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERHBC_BBELPN_DESLIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERHBC_BBELPN_PARAREMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERHBC_BBELPN_MANUAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWS, DI_tmp__MR);
                }

                //HPC BE P1
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP1BE_LIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP1BE_MANUAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWS, DI_tmp__MR);
                }
                //HPC BE P3
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP3BE_LIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP3BE_MANUAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWS, DI_tmp__MR);
                }
                //HPC BE MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWS, DI_tmp__MR);
                }

                //HPC BB P1
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP1BB_LIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP1BB_MANUAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWS, DI_tmp__MR);
                }
                //HPC BB P3
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP3BB_LIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP3BB_MANUAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWS, DI_tmp__MR);
                }
                //HPC BB MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWS, DI_tmp__MR);
                }

                double tmp_DPS    = 0;
                double tmp_PPS    = 0;
                String frmtDPS    = "";
                String frmtPPS    = "";

                if (CLP_SUP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO) == 0){
                       tmp_DPS = CLP_SUP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWS);
                       tmp_PPS = CLP_SUP.RD(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_SCM);
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       frmtPPS = FormatFloat("0.##",tmp_PPS);
                       if (frmtDPS != frmtPPS) {
                               CLP_SUP.WR( CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWS, frmtPPS.ToDouble());
                       }
                       CLP_SUP.WR(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO, 1);
                }

                tmp_DPS = CLP_SUP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWS);

                if (CLP_MR.RD(CP_HL_HPCBE_CTRBKP_AUMENTARPASSO)) {
                       tmp_DPS = tmp_DPS + 5;
                       if (tmp_DPS > 110) {
                                tmp_DPS = 110;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWS, frmtDPS.ToDouble());
                }
                if (CLP_MR.RD(CP_HL_HPCBE_CTRBKP_DIMINUIRPASSO)) {
                       tmp_DPS = tmp_DPS - 5;
                       if (tmp_DPS < -110) {
                                tmp_DPS = -110;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWS, frmtDPS.ToDouble());
                }

                if (CLP_SUP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO) == 0){
                       tmp_DPS = CLP_SUP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWS);
                       tmp_PPS = CLP_SUP.RD(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_SCM);
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       frmtPPS = FormatFloat("0.##",tmp_PPS);
                       if (frmtDPS != frmtPPS) {
                               CLP_SUP.WR( CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWS, frmtPPS.ToDouble());
                       }
                       CLP_SUP.WR(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO, 1);
                }

                tmp_DPS = CLP_SUP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWS);

                if (CLP_MR.RD(CP_HL_HPCBB_CTRBKP_AUMENTARPASSO)) {
                       tmp_DPS = tmp_DPS + 5;
                       if (tmp_DPS > 110) {
                                tmp_DPS = 110;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWS, frmtDPS.ToDouble());
                }
                if (CLP_MR.RD(CP_HL_HPCBB_CTRBKP_DIMINUIRPASSO)) {
                       tmp_DPS = tmp_DPS - 5;
                       if (tmp_DPS < -110) {
                                tmp_DPS = -110;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWS, frmtDPS.ToDouble());
                }


                //MCP BE
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBE_CTRPRI_PARARNORMAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBE_AFBE_ENCHER);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBE_AFBE_ESVAZIAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBE_CTRPRI_DESLBATOVER);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBE_CTRPRI_RECONALARM);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBE_CTRPRI_SILENCIARBUZ);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWS, DI_tmp__MR);
                }

                tmp_DPS    = 0;
                tmp_PPS    = 0;
                frmtDPS    = "";
                frmtPPS    = "";

               if (CLP_SUP.RD(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO) == 0){
                       tmp_DPS = CLP_SUP.RD(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWS);
                       tmp_PPS = CLP_SUP.RD(PC_SA_MCPBE_ECS_MCPRPM_SCM);
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       frmtPPS = FormatFloat("0.##",tmp_PPS);
                       if (frmtDPS != frmtPPS) {
                               CLP_SUP.WR( CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWS, frmtPPS.ToDouble());
                               CLP_SUP.WR( CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWS, frmtPPS.ToDouble());
                               CLP_SUP.WR( CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWS, frmtPPS.ToDouble());
                       }
                       CLP_SUP.WR(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO, 1);
                       CLP_SUP.WR(CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWO, 1);
                       CLP_SUP.WR(CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWO, 1);
                }

                tmp_DPS = CLP_SUP.RD(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWS);

                if (CLP_MR.RD(CP_HL_MCPBB_CTRPRI_AUMENTARRPM)) {
                       tmp_DPS = tmp_DPS + 5;
                       if (tmp_DPS > 1490) {
                                tmp_DPS = 1490;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWS, frmtDPS.ToDouble());
                }
                if (CLP_MR.RD(CP_HL_MCPBB_CTRPRI_DIMINUIRRPM)) {
                       tmp_DPS = tmp_DPS - 5;
                       if (tmp_DPS < 600) {
                                tmp_DPS = 600;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWS, frmtDPS.ToDouble());
                }

                //MCP BB
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBB_CTRPRI_PARARNORMAL);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBB_AFBB_ENCHER);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBB_AFBB_ESVAZIAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBB_CTRPRI_DESLBATOVER);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBB_CTRPRI_RECONALARM);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_MCPBB_CTRPRI_SILENCIARBUZ);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWS, DI_tmp__MR);
                }

                tmp_DPS    = 0;
                tmp_PPS    = 0;
                frmtDPS    = "";
                frmtPPS    = "";

                if (CLP_SUP.RD(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO) == 0){
                       tmp_DPS = CLP_SUP.RD(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWS);
                       tmp_PPS = CLP_SUP.RD(PC_SA_MCPBB_ECS_MCPRPM_SCM);
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       frmtPPS = FormatFloat("0.##",tmp_PPS);
                       if (frmtDPS != frmtPPS) {
                               CLP_SUP.WR( CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWS, frmtPPS.ToDouble());
                               CLP_SUP.WR( CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWS, frmtPPS.ToDouble());
                               CLP_SUP.WR( CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWS, frmtPPS.ToDouble());
                       }
                       CLP_SUP.WR(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO, 1);
                       CLP_SUP.WR(CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWO, 1);
                       CLP_SUP.WR(CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWO, 1);
                }

                tmp_DPS = CLP_SUP.RD(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWS);

                if (CLP_MR.RD(CP_HL_MCPBB_CTRPRI_AUMENTARRPM)) {
                       tmp_DPS = tmp_DPS + 5;
                       if (tmp_DPS > 1490) {
                                tmp_DPS = 1490;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWS, frmtDPS.ToDouble());
                }
                if (CLP_MR.RD(CP_HL_MCPBB_CTRPRI_DIMINUIRRPM)) {
                       tmp_DPS = tmp_DPS - 5;
                       if (tmp_DPS < 600) {
                                tmp_DPS = 600;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWS, frmtDPS.ToDouble());
                       CLP_SUP.WR( CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWS, frmtDPS.ToDouble());
                }

                //TG
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO, 1);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_TBGAS_CTRPRI_DESLBATOVER1);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_TBGAS_CTRPRI_DESLBATOVER2);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_TBGAS_CTRPRI_RECONALARM);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_TBGAS_CTRPRI_SILENCIARBUZ);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_TBGAS_CTRPRI_LIMITARTORQUE);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWS, DI_tmp__MR);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_TBGAS_CTRPRI_PARAREMERG);
                DI_tmp_SCM = CLP_SUP.RD(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWS, DI_tmp__MR);
                }

                tmp_DPS    = 0;
                tmp_PPS    = 0;
                frmtDPS    = "";
                frmtPPS    = "";

                if (CLP_SUP.RD(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO) == 0){
                       tmp_DPS = CLP_SUP.RD(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWS);
                       tmp_PPS = CLP_SUP.RD(PC_HA_TBGAS_MCTG_PLA);
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       frmtPPS = FormatFloat("0.##",tmp_PPS);
                       if (frmtDPS != frmtPPS) {
                               CLP_SUP.WR( CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWS, frmtPPS.ToDouble());
                       }
                       CLP_SUP.WR(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO, 1);
                }

                tmp_DPS = CLP_SUP.RD(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWS);

                if (CLP_MR.RD(CP_HL_TBGAS_CTRPRI_AUMENTARPLA)) {
                       tmp_DPS = tmp_DPS + 1;
                       if (tmp_DPS > 110) {
                                tmp_DPS = 110;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWS, frmtDPS.ToDouble());
                }
                if (CLP_MR.RD(CP_HL_TBGAS_CTRPRI_DIMINUIRPLA)) {
                       tmp_DPS = tmp_DPS - 1;
                       if (tmp_DPS < -25) {
                                tmp_DPS = -25;
                       }
                       frmtDPS = FormatFloat("0.##",tmp_DPS);
                       CLP_SUP.WR( CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWS, frmtDPS.ToDouble());
                }

                //SSS K1
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERPBC_SSSK1_TRAVAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWS, DI_tmp__MR);
                }
                //SSS K2
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERPBC_SSSK2_TRAVAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWS, DI_tmp__MR);
                }
                //SSS K3
                if (CLP_SUP.RD(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERSBB_SSSK3_DESTRAVAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWS, DI_tmp__MR);
                }
                //SSS K4
                if (CLP_SUP.RD(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO) == 0){
                    CLP_SUP.WR(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO, 1);
                }

                DI_tmp__MR = CLP_MR.RD(CP_HL_ERSBE_SSSK4_DESTRAVAR);
                DI_tmp_SCM = CLP_SUP.RD(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWS);

                if ( DI_tmp_SCM != DI_tmp__MR){
                        CLP_SUP.WR(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWS, DI_tmp__MR);
                }

        }else{
                //ELPN

                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE P1
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE P3
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO, 0);
                }

                //HPC BB P1
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BB P3
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BB MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO, 0);
                }

                if (CLP_SUP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO, 0);
                }

                if (CLP_SUP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO, 0);
                }

                //MCP BE
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_MCPBE_ECS_DEMANDARPMETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_MCPBE_ECS_DEMANDARPMETH2_SCM_MWO, 0);
                }

                //MCP BB
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_MCPBB_ECS_DEMANDARPMETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_MCPBB_ECS_DEMANDARPMETH2_SCM_MWO, 0);
                }

                //TG
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO, 0);
                }

                //SSS K1
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO, 0);
                }
                //SSS K2
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO, 0);
                }
                //SSS K3
                if (CLP_SUP.RD(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO, 0);
                }
                //SSS K4
                if (CLP_SUP.RD(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO, 0);
                }
        }
}
//---------------------------------------------------------------------------





void __fastcall TfrmPrincipal::btnFecharClick(TObject *Sender)
{
        if (btnHabilitar->Caption == "Desabilitar"){
                CLP_MR.WR(PC_HA_HPCBE_UDOHPC_PASSOBEPOS_MWO, 0);
                CLP_MR.WR(PC_HA_HPCBB_UDOHPC_PASSOBBPOS_MWO, 0);

                for (int i = 3100; i <= 3112; i++){ //ARM IO 1   Digitais  E TODAS ANALÓGICAS 3107-3112
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0x0000);
                }
                for (int i = 3066; i <= 3069; i++){ //PMR   Digitais
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0x0000);
                }
                for (int i = 3800; i <= 3802; i++){ //PMV   Digitais
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP_MR.WR(tempMW, 0x0000);
                }

                CLP_MR.WR("%MW25000", 0x0000); //TRANSFERENCIA SCM MR

                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERHBC_BBELPN_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE P1
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP1BE_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE P3
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_BBP3BE_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BE MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_LIGARRPMBX_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBE_HDWSCM_DESLIGARRPMBX_SCM_MWO, 0);
                }

                //HPC BB P1
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP1BB_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BB P3
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_DESLIGAR_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_MANUAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_AUTOMATICO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_BBP3BB_LIBPEMERG_SCM_MWO, 0);
                }

                //HPC BB MANOBRA BX VELOC
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_LIGARRPMBX_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_HPCBB_HDWSCM_DESLIGARRPMBX_SCM_MWO, 0);
                }

                if (CLP_SUP.RD(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_HPCBE_CTRPRI_DEMANDAPASSO_SCM_MWO, 0);
                }

                if (CLP_SUP.RD(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_HPCBB_CTRPRI_DEMANDAPASSO_SCM_MWO, 0);
                }

                //MCP BE
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_PARARHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ENCHERAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_ESVAZIARAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBE_RTUBE_ATVBOHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_RECTODOSALETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBE_ECS_BUZDESLIGETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_MCPBE_RTUBE_DEMANDARPMHDW_SCM_MWO, 0);
                }

                //MCP BB
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_PARARHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ENCHERAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_ESVAZIARAFETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_MCPBB_RTUBB_ATVBOHDW_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_RECTODOSALETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_MCPBB_ECS_BUZDESLIGETH1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HA_MCPBB_RTUBB_DEMANDARPMHDW_SCM_MWO, 0);
                }

                //TG
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGBTOV1_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_DESLIGOSOV2_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_RECTDAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_SILENCAL_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_TBGAS_MCTG_OPERAR1EIXO_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SL_TBGAS_ETH1_PARAREMERG_SCM_MWO, 0);
                }
                if (CLP_SUP.RD(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_SA_TBGAS_ETH1_SPSCMPLA_SCM_MWO, 0);
                }

                //SSS K1
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK1_TRAVAR_SCM_MWO, 0);
                }
                //SSS K2
                if (CLP_SUP.RD(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERPBC_SSSK2_TRAVAR_SCM_MWO, 0);
                }
                //SSS K3
                if (CLP_SUP.RD(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERSBB_SSSK3_TRAVAR_SCM_MWO, 0);
                }
                //SSS K4
                if (CLP_SUP.RD(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO) == 1){
                    CLP_SUP.WR(CP_HL_ERSBE_SSSK4_TRAVAR_SCM_MWO, 0);
                }

                btnTesteHPC->Enabled = false;
                btnTesteAlarmes->Enabled = false;

                btnEqualSCM->Enabled = false;

                tmrHabilitar->Enabled = true;
                btnConectar->Enabled = true;

                shpHabilitaSelecao->Visible = true;

                tmrTransferencia->Enabled = false;
        }
        if (em_mr == true){
                if (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO) == 0) {
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWO, 1);
                }
                if (CLP_SUP.RD(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO) == 0) {
                        CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWO, 1);
                }
                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICMR            , 0);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMMR_MWS   , 0);
                 CLP_MR.WR(PC_HL_SMR_CPCCM_SOLICAUTO          , 1);
                CLP_SUP.WR(PC_HL_SCMPA_CPCCM_SOLICSCMAUTO_MWS , 1);

                CLP_SUP.WR(PC_SL_MANREM_SMR_EMMR_MWO          , 0);
                CLP_SUP.WR(PC_SL_MANREM_SMR_EMMR_MWS          , 0);

                imgSolicAuto->Visible = true;
                imgSolicMR->Visible = false;
                em_mr = false;

                int    DI_tmp__MR = 0;
                int    DI_tmp_SCM = 0;

                //rotina de transferência

        }

        btnFechar->Caption = "Fechando";
        tmrFechar->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrFecharTimer(TObject *Sender)
{
        if (btnConectar->Caption == "Desconectar") {
                btnConectar->Caption = "Conectar";
                //if (monitor_ativo == true){
                //        btnMonitor->Click();
                //}
                tmrLeitura->Enabled = false;

                //
                //DESANIMAR OBJETOS AQUI
                lblHPCBB_UDOHPC_PASSOBBPOS->Caption = "--";
                lblHPCBE_UDOHPC_PASSOBEPOS->Caption = "--";
                //

                btnHabilitar->Enabled = false;
                //btnSimul->Enabled = false;
                grbDiagnostico->Visible = false;
                //btnMonitMODBUS->Enabled = true;
                CLP_MR.Close();
                CLP_SUP.Close();

                //tmrLeitura->Enabled = false;
                tmrReconecta->Enabled = false;
                tmrConexaoWatch->Enabled = false;
                tmrLista->Enabled = false;
                lblModbusStatus->Caption = "Desativado - Leitura Inativa";
                conectado = false;
        }
        tmrFechar->Enabled = false;
        tmrFecha->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmrFechaTimer(TObject *Sender)
{
        tmrFecha->Enabled = false;
        frmPrincipal->Close();
}
//---------------------------------------------------------------------------

