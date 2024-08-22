//---------------------------------------------------------------------------
//***************************************************************************
//MAURICIO ANDRADE LEMME - ANALISTA DE SISTEMAS J2
//IPqM - INSTITUTO DE PESQUISAS DA MARINHA
//GSD - GRUPO DE SISTEMAS DIGITAIS
//FUNDEP - FUNDAÇÃO DE DESENVOLVIMENTO DA PESQUISA

//EMULADOR DE SINAIS DA PROPULSÃO
//NAVIO MODELO.....: JULIO DE NORONHA
//USUÁRIO FINAL....: EQUIPE CLP
//VERSÃO INICIAL...: V001b
//MÓDULO...........: AUXILIARES
//DATA DE INÍCIO...: 29.06.2022
//DATA DE PROTÓTIPO: 08.07.2022
//DATA DE TÉRMINO..: 12.03.2024
//DATA DE ATUALIZ..:
//DESIGNAÇÃO.......: ESTE MÓDULO DO SOFTWARE TEM COMO OBJETIVO EMULAR O FUNCIONAMENTO DAS AUXILIARES
//EM COPARCERIA DESTE MÓDULO ESTA O MÓDULO DE COMUNICAÇÃO MODBUS DE AUTORIA DO
//FUNCIONÁRIO FÁBIO TEIXEIRA, SUA IMPLEMENTAÇÃO É DESCONHECIDA
//***************************************************************************
#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
//#include "TModBusScanner.cpp" /* DRIVER MODBUS */
#include "ModBusDriverLib\TModBusTCPDriver.cpp"
//----------------- ENDEREÇOS DOS EQUIPAMENTOS -----------------
//-------------------------- AODPG ----------------------------
String PC_HA_AODPG_TAOD01_NIVEL			= "%MF6114";    //Tanque de Armazenamento de Óleo Diesel N° 1 - Indicador de Nível
String PC_HL_AODPG_TAOD01_NIVELALTO		= "%MW6031.12"; //Tanque de Armazenamento de Óleo Diesel N° 1 - Nível Alto
String PC_HL_AODPG_TAOD01_TRANSBORDA		= "%MW6031.13"; //Tanque de Armazenamento de Óleo Diesel N° 1 - Transbordo
String PC_HA_AODPG_TAOD02_NIVEL	        	= "%MF6116";    //Tanque de Armazenamento de Óleo Diesel N° 2 - Indicador de Nível
String PC_HL_AODPG_TAOD02_NIVELALTO		= "%MW6031.14"; //Tanque de Armazenamento de Óleo Diesel N° 2 - Nível Alto
String PC_HL_AODPG_TAOD02_TRANSBORDA		= "%MW6031.15"; //Tanque de Armazenamento de Óleo Diesel N° 2 - Transbordo
String PC_HA_AODPG_TAOD03_NIVEL 		= "%MF6118";    //Tanque de Armazenamento de Óleo Diesel N° 3 - Indicador de Nível
String PC_HL_AODPG_TAOD03_NIVELALTO		= "%MW6032.0";  //Tanque de Armazenamento de Óleo Diesel N° 3 - Nível Alto
String PC_HL_AODPG_TAOD03_TRANSBORDA		= "%MW6032.1";  //Tanque de Armazenamento de Óleo Diesel N° 3 - Transbordo
String PC_HA_AODPG_TAOD04_NIVEL	        	= "%MF6130";    //Tanque de Armazenamento de Óleo Diesel N° 4 - Indicador de Nível
String PC_HL_AODPG_TAOD04_NIVELALTO		= "%MW6032.7";  //Tanque de Armazenamento de Óleo Diesel N° 4 - Nível Alto
String PC_HL_AODPG_TAOD04_TRANSBORDA		= "%MW6032.8";  //Tanque de Armazenamento de Óleo Diesel N° 4 - Transbordo
String PC_HA_AODPG_TAOD05_NIVEL	        	= "%MF6132";    //Tanque de Armazenamento de Óleo Diesel N° 5 - Indicador de Nível
String PC_HL_AODPG_TAOD05_NIVELALTO		= "%MW6032.9";  //Tanque de Armazenamento de Óleo Diesel N° 5 - Nível Alto
String PC_HL_AODPG_TAOD05_TRANSBORDA		= "%MW6032.10"; //Tanque de Armazenamento de Óleo Diesel N° 5 - Transbordo
String PC_HA_AODPG_TAOD06_NIVEL	        	= "%MF6134";    //Tanque de Armazenamento de Óleo Diesel N° 6 - Indicador de Nível
String PC_HL_AODPG_TAOD06_NIVELALTO		= "%MW6032.11"; //Tanque de Armazenamento de Óleo Diesel N° 6 - Nível Alto
String PC_HL_AODPG_TAOD06_TRANSBORDA		= "%MW6032.12"; //Tanque de Armazenamento de Óleo Diesel N° 6 - Transbordo
String PC_HL_AODPG_VOD005_FECHADO		= "%MW6017.6";  //Válvula de Óleo Diesel N° 005 - Fechado
String PC_HL_AODPG_VOD005_ABERTO		= "%MW6017.7";  //Válvula de Óleo Diesel N° 005 - Aberto
String CP_HL_AODPG_VOD005_FECHAR		= "%MW505.1";   //Válvula de Óleo Diesel N° 005 - Fechar
String CP_HL_AODPG_VOD005_ABRIR	        	= "%MW505.2";   //Válvula de Óleo Diesel N° 005 - Abrir
String PC_HL_AODPG_VOD010_FECHADO		= "%MW6017.8";  //Válvula de Óleo Diesel N° 010 - Fechado
String PC_HL_AODPG_VOD010_ABERTO		= "%MW6017.9";  //Válvula de Óleo Diesel N° 010 - Aberto
String CP_HL_AODPG_VOD010_FECHAR		= "%MW505.3";   //Válvula de Óleo Diesel N° 010 - Fechar
String CP_HL_AODPG_VOD010_ABRIR	        	= "%MW505.4";   //Válvula de Óleo Diesel N° 010 - Abrir
String PC_HL_AODPG_VOD012_FECHADO		= "%MW6018.2";  //Válvula de Óleo Diesel N° 012 - Fechado
String PC_HL_AODPG_VOD012_ABERTO		= "%MW6018.3";  //Válvula de Óleo Diesel N° 012 - Aberto
String CP_HL_AODPG_VOD012_ABRIR	        	= "%MW505.11";  //Válvula de Óleo Diesel N° 012 - Abrir
String PC_HL_AODPG_VOD013_FECHADO		= "%MW6017.14"; //Válvula de Óleo Diesel N° 013 - Fechado
String PC_HL_AODPG_VOD013_ABERTO		= "%MW6017.15"; //Válvula de Óleo Diesel N° 013 - Aberto
String CP_HL_AODPG_VOD013_ABRIR	        	= "%MW505.9";   //Válvula de Óleo Diesel N° 013 - Abrir
String PC_HL_AODPG_VOD014_FECHADO		= "%MW6018.0";  //Válvula de Óleo Diesel N° 014 - Fechado
String PC_HL_AODPG_VOD014_ABERTO		= "%MW6018.1";  //Válvula de Óleo Diesel N° 014 - Aberto
String CP_HL_AODPG_VOD014_ABRIR	        	= "%MW505.10";  //Válvula de Óleo Diesel N° 014 - Abrir
String PC_HL_AODPG_VOD015_FECHADO		= "%MW6018.6";  //Válvula de Óleo Diesel N° 015 - Fechado
String PC_HL_AODPG_VOD015_ABERTO		= "%MW6018.7";  //Válvula de Óleo Diesel N° 015 - Aberto
String CP_HL_AODPG_VOD015_ABRIR	        	= "%MW505.13";  //Válvula de Óleo Diesel N° 015 - Abrir
String PC_HL_AODPG_VOD016_FECHADO		= "%MW6018.4";  //Válvula de Óleo Diesel N° 016 - Fechado
String PC_HL_AODPG_VOD016_ABERTO		= "%MW6018.5"; //Válvula de Óleo Diesel N° 016 - Aberto
String CP_HL_AODPG_VOD016_ABRIR	        	= "%MW505.12";  //Válvula de Óleo Diesel N° 016 - Abrir
String PC_HL_AODPG_VOD017_FECHADO		= "%MW6018.8";  //Válvula de Óleo Diesel N° 017 - Fechado
String PC_HL_AODPG_VOD017_ABERTO		= "%MW6018.9";  //Válvula de Óleo Diesel N° 017 - Aberto
String CP_HL_AODPG_VOD017_ABRIR	        	= "%MW505.14";  //Válvula de Óleo Diesel N° 017 - Abrir
String PC_HL_AODPG_VOD030_FECHADO		= "%MW6017.12"; //Válvula de Óleo Diesel N° 030 - Fechado
String PC_HL_AODPG_VOD030_ABERTO		= "%MW6017.13"; //Válvula de Óleo Diesel N° 030 - Aberto
String CP_HL_AODPG_VOD030_FECHAR		= "%MW505.7";   //Válvula de Óleo Diesel N° 030 - Fechar
String CP_HL_AODPG_VOD030_ABRIR	        	= "%MW505.8";   //Válvula de Óleo Diesel N° 030 - Abrir
String PC_HL_AODPG_VOD031_FECHADO		= "%MW6017.10"; //Válvula de Óleo Diesel N° 031 - Fechado
String PC_HL_AODPG_VOD031_ABERTO		= "%MW6017.11"; //Válvula de Óleo Diesel N° 031 - Aberto
String CP_HL_AODPG_VOD031_FECHAR		= "%MW505.5";   //Válvula de Óleo Diesel N° 031 - Fechar
String CP_HL_AODPG_VOD031_ABRIR	        	= "%MW505.6";   //Válvula de Óleo Diesel N° 031 - Abrir
String PC_HL_AODPG_VOD035_FECHADO		= "%MW6018.10"; //Válvula de Óleo Diesel N° 035 - Fechado
String PC_HL_AODPG_VOD035_ABERTO		= "%MW6018.11"; //Válvula de Óleo Diesel N° 035 - Aberto
String CP_HL_AODPG_VOD035_FECHAR		= "%MW506.0";   //Válvula de Óleo Diesel N° 035 - Fechar
String CP_HL_AODPG_VOD035_ABRIR	        	= "%MW506.1";   //Válvula de Óleo Diesel N° 035 - Abrir
String PC_HL_AODPG_VOD043_FECHADO		= "%MW6018.12"; //Válvula de Óleo Diesel N° 043 - Fechado
String PC_HL_AODPG_VOD043_ABERTO		= "%MW6018.13"; //Válvula de Óleo Diesel N° 043 - Aberto
String CP_HL_AODPG_VOD043_FECHAR		= "%MW506.2";   //Válvula de Óleo Diesel N° 043 - Fechar
String CP_HL_AODPG_VOD043_ABRIR	        	= "%MW506.3";   //Válvula de Óleo Diesel N° 043 - Abrir
String PC_HL_AODPG_VOD059_FECHADO		= "%MW6018.14"; //Válvula de Óleo Diesel N° 059 - Fechado
String PC_HL_AODPG_VOD059_ABERTO		= "%MW6018.15"; //Válvula de Óleo Diesel N° 059 - Aberto
String CP_HL_AODPG_VOD059_ABRIR	        	= "%MW506.4";   //Válvula de Óleo Diesel N° 059 - Abrir
String PC_HL_AODPG_VOD060_FECHADO		= "%MW6019.0";  //Válvula de Óleo Diesel N° 060 - Fechado
String PC_HL_AODPG_VOD060_ABERTO		= "%MW6019.1";  //Válvula de Óleo Diesel N° 060 - Aberto
String CP_HL_AODPG_VOD060_ABRIR	        	= "%MW506.5";   //Válvula de Óleo Diesel N° 060 - Abrir
String PC_HL_AODPG_VOD061_FECHADO		= "%MW6019.2";  //Válvula de Óleo Diesel N° 061 - Fechado
String PC_HL_AODPG_VOD061_ABERTO		= "%MW6019.3";  //Válvula de Óleo Diesel N° 061 - Aberto
String CP_HL_AODPG_VOD061_ABRIR	        	= "%MW506.6";   //Válvula de Óleo Diesel N° 061 - Abrir
String PC_HL_AODPG_VOD062_FECHADO		= "%MW6019.8";  //Válvula de Óleo Diesel N° 062 - Fechado
String PC_HL_AODPG_VOD062_ABERTO		= "%MW6019.9";  //Válvula de Óleo Diesel N° 062 - Aberto
String CP_HL_AODPG_VOD062_ABRIR	        	= "%MW506.9";   //Válvula de Óleo Diesel N° 062 - Abrir
String PC_HL_AODPG_VOD063_FECHADO		= "%MW6019.6";  //Válvula de Óleo Diesel N° 063 - Fechado
String PC_HL_AODPG_VOD063_ABERTO		= "%MW6019.7";  //Válvula de Óleo Diesel N° 063 - Aberto
String CP_HL_AODPG_VOD063_ABRIR	        	= "%MW506.8";   //Válvula de Óleo Diesel N° 063 - Abrir
String PC_HL_AODPG_VOD064_FECHADO		= "%MW6019.4";  //Válvula de Óleo Diesel N° 064 - Fechado
String PC_HL_AODPG_VOD064_ABERTO		= "%MW6019.5";  //Válvula de Óleo Diesel N° 064 - Aberto
String CP_HL_AODPG_VOD064_ABRIR	        	= "%MW506.7";   //Válvula de Óleo Diesel N° 064 - Abrir
String PC_HL_AODPG_VOD066_FECHADO		= "%MW6019.10"; //Válvula de Óleo Diesel N° 066 - Fechado
String PC_HL_AODPG_VOD066_ABERTO		= "%MW6019.11"; //Válvula de Óleo Diesel N° 066 - Aberto
String CP_HL_AODPG_VOD066_FECHAR		= "%MW506.10";  //Válvula de Óleo Diesel N° 066 - Fechar
String CP_HL_AODPG_VOD066_ABRIR	        	= "%MW506.11";  //Válvula de Óleo Diesel N° 066 - Abrir
String PC_HL_AODPG_TTOD12_NIVELALTO		= "%MW6032.2";  //Tanque de Transbordo de Óleo Diesel N° 12 - Nível Alto
String PC_HA_AODPG_TTOD12_NIVEL 		= "%MF6126";    //Tanque de Transbordo de Óleo Diesel N° 12 - Indicador de Nível
String PC_HL_AODPG_TTOD13_NIVELALTO		= "%MW6033.4";  //Tanque de Transbordo de Óleo Diesel N° 12 - Nível Alto
String PC_HA_AODPG_TTOD13_NIVEL 		= "%MF6140";    //Tanque de Transbordo de Óleo Diesel N° 13 - Indicador de Nível
String PC_HL_AODPG_BETOD1_LIGADO		= "%MW6013.8";  //Bomba Elétrica de Transferência de Óleo Diesel N° 1 - Ligado
String PC_HL_AODPG_BETOD1_EMREM	        	= "%MW6013.9";  //Bomba Elétrica de Transferência de Óleo Diesel N° 1 - Em Remoto
String CP_HL_AODPG_BETOD1_LIGAR	                = "%MW502.13";  //Bomba Elétrica de Transferência de Óleo Diesel N° 1 - Ligar
String CP_HL_AODPG_BETOD1_DESLIGAR	        = "%MW502.14";  //Bomba Elétrica de Transferência de Óleo Diesel N° 1 - Desligar
String CP_HL_AODPG_BETOD1_PARAREMERG	        = "%MW502.15";  //Bomba Elétrica de Transferência de Óleo Diesel N° 1 - Parar em Emergência
String PC_HL_AODPG_BETOD2_LIGADO	        = "%MW6013.10"; //Bomba Elétrica de Transferência de Óleo Diesel N° 2 - Ligado
String PC_HL_AODPG_BETOD2_EMREM	                = "%MW6013.11"; //Bomba Elétrica de Transferência de Óleo Diesel N° 2 - Em Remoto
String CP_HL_AODPG_BETOD2_LIGAR	                = "%MW503.0";   //Bomba Elétrica de Transferência de Óleo Diesel N° 2 - Ligar
String CP_HL_AODPG_BETOD2_DESLIGAR	        = "%MW503.1";   //Bomba Elétrica de Transferência de Óleo Diesel N° 2 - Desligar
String CP_HL_AODPG_BETOD2_PARAREMERG	        = "%MW503.2";   //Bomba Elétrica de Transferência de Óleo Diesel N° 2 - Parar em Emergência
String PC_HL_AODPG_PLOD1_FALHAALIM	        = "%MW6032.3";  //Painel Local de Óleo Diesel N° 1 - Falha de Alimentação
String PC_HL_AODPG_PLOD2_FALHAALIM	        = "%MW6032.13"; //Painel Local de Óleo Diesel N° 2 - Falha de Alimentação
//-------------------------- AOLTG  ----------------------------
String PC_HL_AOLTG_AQCOL1_LIGADO		= "%MW6014.0";	//Aquecedor de Óleo Lubrificante N° 1 - Ligado
String PC_HL_AOLTG_AQCOL1_FALHA			= "%MW6014.1";	//Aquecedor de Óleo Lubrificante N° 1 - Em Falha
String PC_HL_AOLTG_AQCOL2_LIGADO		= "%MW6013.14"; //Aquecedor de Óleo Lubrificante N° 2 - Ligado
String PC_HL_AOLTG_AQCOL2_FALHA			= "%MW6013.15"; //Aquecedor de Óleo Lubrificante N° 2 - Em Falha
String PC_HL_AOLTG_BETOL1_LIGADO		= "%MW6014.2";	//Bomba Elétrica de Transferência de Óleo Lubrificante N° 1 - Ligado
String PC_HL_AOLTG_BETOL2_LIGADO		= "%MW6014.3";	//Bomba Elétrica de Transferência de Óleo Lubrificante N° 2 - Ligado
String PC_HL_AOLTG_PUROL1_LIGADO		= "%MW6013.12"; //Purificador Centrífugo de Óleo Lubrificante N° 1 - Ligado
String PC_HL_AOLTG_PUROL1_PERDASELO		= "%MW6013.13"; //Purificador Centrífugo de Óleo Lubrificante N° 1 - Perda de Selo
String PC_HL_AOLTG_PUROL2_LIGADO		= "%MW6014.4";	//Purificador Centrífugo de Óleo Lubrificante N° 2 - Ligado
String PC_HL_AOLTG_PUROL2_PERDASELO		= "%MW6014.5";	//Purificador Centrífugo de Óleo Lubrificante N° 2 - Perda de Selo
String PC_HL_AOLTG_TAOL14_NIVELBAIXO		= "%MW6031.7";	//Tanque de Armazenamento de Óleo Lubrificante N° 14 - Nível Baixo
String PC_HL_AOLTG_TAOL25_NIVELALTO		= "%MW6033.6";	//Tanque de Armazenamento de Óleo Lubrificante N° 25 - Nível Alto
String PC_HL_AOLTG_TBORRA_NIVELALTO		= "%MW6033.7";	//Tanque de Borra - Nível Alto
String PC_HL_AOLTG_TQDREN_NIVELALTO		= "%MW6016.8";	//Tanque de Dreno - Nível Alto
String CP_HL_AOLTG_BETOL1_PARAREMERG		= "%MW503.4";	//Bomba Elétrica de Transferência de Óleo Lubrificante N° 1 - Parar em Emergência
String CP_HL_AOLTG_BETOL2_PARAREMERG		= "%MW503.5";	//Bomba Elétrica de Transferência de Óleo Lubrificante N° 2 - Parar em Emergência
String CP_HL_AOLTG_PUROL1_PARAREMERG		= "%MW503.3";	//Purificador Centrífugo de Óleo Lubrificante N° 1 - Parar em Emergência
String CP_HL_AOLTG_PUROL2_PARAREMERG		= "%MW503.6";	//Purificador Centrífugo de Óleo Lubrificante N° 2 - Parar em Emergência
//-------------------------- CPTAS  ----------------------------
String PC_HL_CPTAS_BEM1_LIGADO			= "%MW6030.2";	//Bomba Elétrica Maceradora N° 1 - Ligado
String PC_HL_CPTAS_BEM1_FALHA			= "%MW6030.3";	//Bomba Elétrica Maceradora N° 1 - Em Falha
String PC_HL_CPTAS_BEM2_LIGADO			= "%MW6030.4";	//Bomba Elétrica Maceradora N° 2 - Ligado
String PC_HL_CPTAS_BEM2_FALHA			= "%MW6030.5";	//Bomba Elétrica Maceradora N° 2 - Em Falha
String PC_HL_CPTAS_BET1_LIGADO			= "%MW6030.7";	//Bomba Elétrica de Transferência N° 1 - Ligado
String PC_HL_CPTAS_BET1_FALHA			= "%MW6030.8";	//Bomba Elétrica de Transferência N° 1 - Em Falha
String PC_HL_CPTAS_BET2_LIGADO			= "%MW6030.9";	//Bomba Elétrica de Transferência N° 2 - Ligado
String PC_HL_CPTAS_BET2_FALHA			= "%MW6030.10"; //Bomba Elétrica de Transferência N° 2 - Em Falha
String PC_HL_CPTAS_PLUTAS_LIGADO		= "%MW6030.0";	//Painel Local da Unidade de Tratamento de Águas Servidas - Ligado
String PC_HL_CPTAS_PLUTAS_FALHA			= "%MW6030.1";  //Painel Local da Unidade de Tratamento de Águas Servidas - Em Falha
String PC_HL_CPTAS_SEPAO_TEORALTO		= "%MW6030.12"; //Separador de Água/Óleo - Alto Teor
String PC_HL_CPTAS_SEPAO_LIGADO			= "%MW6033.14"; //Separador de Água/Óleo - Ligado
String PC_HL_CPTAS_TQSEPR_NIVELALTO		= "%MW6030.11"; //Tanque Séptico À Ré - Nível Alto
String PC_HL_CPTAS_TQSEPV_NIVELALTO		= "%MW6030.6";	//Tanque Séptico À Vante - Nível Alto
//-------------------------- DASOR  ----------------------------
String PC_HL_DASOR_GDEST1_LIGADO		= "%MW6010.8";	//Grupo Destilatório N° 1 - Ligado
String PC_HL_DASOR_GDEST1_SALINALTA		= "%MW6010.9";	//Grupo Destilatório N° 1 - Alta Salinidade
String PC_HL_DASOR_GDEST1_FALHA			= "%MW6010.10"; //Grupo Destilatório N° 1 - Em Falha
String PC_HL_DASOR_GDEST2_LIGADO		= "%MW6010.11"; //Grupo Destilatório N° 2 - Ligado
String PC_HL_DASOR_GDEST2_SALINALTA		= "%MW6010.12"; //Grupo Destilatório N° 2 - Alta Salinidade
String PC_HL_DASOR_GDEST2_FALHA			= "%MW6010.13"; //Grupo Destilatório N° 2 - Em Falha
String CP_HL_DASOR_GDEST1_PARAREMERG		= "%MW501.0";	//Grupo Destilatório N° 1 - Parar em Emergência
String CP_HL_DASOR_GDEST2_PARAREMERG		= "%MW501.1";	//Grupo Destilatório N° 2 - Parar em Emergência
//-------------------------- GERENE ----------------------------
String PC_HA_GERENE_MCA1_ARALIMPRESS		= "%MF6076";	//Motor de Combustão Auxiliar N° 1 - Pressão de Ar de alimetação
String PC_HA_GERENE_MCA1_ODPRESS		= "%MF6078";	//Motor de Combustão Auxiliar N° 1 - Pressão de Óleo Diesel
String PC_HA_GERENE_MCA1_ASPRESS		= "%MF6080";	//Motor de Combustão Auxiliar N° 1 - Pressão de Água Salgada
String PC_HA_GERENE_MCA1_ADPRESS		= "%MF6082";	//Motor de Combustão Auxiliar N° 1 - Pressão de Água Doce
String PC_HA_GERENE_MCA1_OLPRESS		= "%MF6084";	//Motor de Combustão Auxiliar N° 1 - Pressão de Óleo Lubrificante
String PC_HA_GERENE_MCA1_OLTEMP			= "%MF6186";	//Motor de Combustão Auxiliar N° 1 - Temperatura de Óleo Lubrificante
String PC_HA_GERENE_MCA1_ADTEMP			= "%MF6188";	//Motor de Combustão Auxiliar N° 1 - Temperatura de Água Doce
String PC_HA_GERENE_MCA2_ARALIMPRESS		= "%MF6086";	//Motor de Combustão Auxiliar N° 2 - Pressão de Ar de alimetação
String PC_HA_GERENE_MCA2_ODPRESS		= "%MF6088";	//Motor de Combustão Auxiliar N° 2 - Pressão de Óleo Diesel
String PC_HA_GERENE_MCA2_ASPRESS		= "%MF6090";	//Motor de Combustão Auxiliar N° 2 - Pressão de Água Salgada
String PC_HA_GERENE_MCA2_ADPRESS		= "%MF6092";	//Motor de Combustão Auxiliar N° 2 - Pressão de Água Doce
String PC_HA_GERENE_MCA2_OLPRESS		= "%MF6094";	//Motor de Combustão Auxiliar N° 2 - Pressão de Óleo Lubrificante
String PC_HA_GERENE_MCA2_OLTEMP			= "%MF6190";	//Motor de Combustão Auxiliar N° 2 - Temperatura de Óleo Lubrificante
String PC_HA_GERENE_MCA2_ADTEMP			= "%MF6192";	//Motor de Combustão Auxiliar N° 2 - Temperatura de Água Doce
String PC_HA_GERENE_MCA3_ARALIMPRESS		= "%MF6056";	//Motor de Combustão Auxiliar N° 3 - Pressão de Ar de alimetação
String PC_HA_GERENE_MCA3_ODPRESS		= "%MF6058";	//Motor de Combustão Auxiliar N° 3 - Pressão de Óleo Diesel
String PC_HA_GERENE_MCA3_ASPRESS		= "%MF6060";	//Motor de Combustão Auxiliar N° 3 - Pressão de Água Salgada
String PC_HA_GERENE_MCA3_ADPRESS		= "%MF6062";	//Motor de Combustão Auxiliar N° 3 - Pressão de Água Doce
String PC_HA_GERENE_MCA3_OLPRESS		= "%MF6064";	//Motor de Combustão Auxiliar N° 3 - Pressão de Óleo Lubrificante
String PC_HA_GERENE_MCA3_ADTEMP			= "%MF6178";	//Motor de Combustão Auxiliar N° 3 - Temperatura de Água Doce
String PC_HA_GERENE_MCA3_OLTEMP			= "%MF6180";	//Motor de Combustão Auxiliar N° 3 - Temperatura de Óleo Lubrificante
String PC_HA_GERENE_MCA4_ARALIMPRESS		= "%MF6066";	//Motor de Combustão Auxiliar N° 4 - Pressão de Ar de alimetação
String PC_HA_GERENE_MCA4_ODPRESS		= "%MF6068";	//Motor de Combustão Auxiliar N° 4 - Pressão de Óleo Diesel
String PC_HA_GERENE_MCA4_ASPRESS		= "%MF6070";	//Motor de Combustão Auxiliar N° 4 - Pressão de Água Salgada
String PC_HA_GERENE_MCA4_ADPRESS		= "%MF6072";	//Motor de Combustão Auxiliar N° 4 - Pressão de Água Doce
String PC_HA_GERENE_MCA4_OLPRESS		= "%MF6074";	//Motor de Combustão Auxiliar N° 4 - Pressão de Óleo Lubrificante
String PC_HA_GERENE_MCA4_ADTEMP			= "%MF6182";	//Motor de Combustão Auxiliar N° 4 - Temperatura de Água Doce
String PC_HA_GERENE_MCA4_OLTEMP			= "%MF6184";	//Motor de Combustão Auxiliar N° 4 - Temperatura de Óleo Lubrificante
//-------------------------- GOVBC  ----------------------------
String PC_HA_GOVBC_MAQLEM_LEMEPOSIC		= "%MF6174";	//Máquina do Leme - Sistema de Governo - Posição do Leme
//-------------------------- MAQLEM ----------------------------
String PC_HL_MAQLEM_MOTBB_ALIMDISPON	        = "%MW6020.0";	//Alimentação disponível para o Motor BB (ENERGIZADO) - LP2
String PC_HL_MAQLEM_MOTBB_EMREM	                = "%MW6020.1";	//Controle do Motor de BB disponível (REMOTO) - LP3
String PC_HL_MAQLEM_MOTBB_LIGADO        	= "%MW6020.2";	//Motor de BB funcionando (LIGADO) - LP4
String PC_HL_MAQLEM_MOTBB_DESUMLIG	        = "%MW6020.3";	//Desumidificador do Motor de BB energizado (LIGADO) - LP5
String PC_HL_MAQLEM_MOTBB_EMSOBREC	        = "%MW6020.4";	//Sobrecarga do Motor de BB - LP15
String PC_HL_MAQLEM_MOTBB_ALIMLOGICOK	        = "%MW6020.5";	//Alimentação Lógica do Controlador do Moto BB OK
String PC_HL_MAQLEM_MOTBB_FALTADEFASE	        = "%MW6020.6";	//Falta de fase no Motor de BB - LP16
String PC_HL_MAQLEM_MOTBE_ALIMDISPON	        = "%MW6020.7";	//Alimentação disponível para o Motor BE (ENERGIZADO) - LP10
String PC_HL_MAQLEM_MOTBE_EMREM                 = "%MW6020.8";	//Controle do Motor de BE disponível (REMOTO) - LP11
String PC_HL_MAQLEM_MOTBE_LIGADO	        = "%MW6020.9";	//Motor de BE funcionando (LIGADO) - LP12
String PC_HL_MAQLEM_MOTBE_DESUMLIG	        = "%MW6020.10";	//Desumidificador do Motor de BE energizado (LIGADO) - LP13
String PC_HL_MAQLEM_MOTBE_EMSOBREC	        = "%MW6020.11";	//Sobrecarga do Motor de BE - LP21
String PC_HL_MAQLEM_MOTBE_ALIMLOGICOK	        = "%MW6020.12";	//Alimentação Lógica do Controlador do Moto BE OK
String PC_HL_MAQLEM_MOTBE_FALTADEFASE	        = "%MW6020.13";	//Falta de fase no Motor de BE - LP22
String CP_HL_MAQLEM_MOTBB_PARTIR	        = "%MW507.2";	//Comando de Partir do Motor de BB - Substitui chave S2
String CP_HL_MAQLEM_MOTBB_PARAR	                = "%MW507.3";	//Comando de Parar do Motor de BB - Substitui chave S2
String PP_HL_MAQLEM_MOTBB_MEMORIA	        = "%MW507.4";	//Acionamento Interno (Painel CML) - Memória Partida/Parada BB
String CP_HL_MAQLEM_MOTBE_PARTIR	        = "%MW507.5";	//Comando de Partir do Motor de BE - Substitui chave S3
String CP_HL_MAQLEM_MOTBE_PARAR	                = "%MW507.6";	//Comando de Parar do Motor de BE - Substitui chave S3
String PP_HL_MAQLEM_MOTBE_MEMORIA	        = "%MW507.7";	//Acionamento Interno (Painel CML) - Memória Partida/Parada BE
String PC_HL_MAQLEM_CML_UHNASSOC		= "%MW6021.4";	//Unidade hidráulica não associada ao motor em operação - LP20
String PC_HL_MAQLEM_CML_SELCUHDISPON		= "%MW6021.5";	//Seleção da Unidade Hidráulica disponínvel no CCM - LP6
String PC_HL_MAQLEM_CML_CMDDISPCCM		= "%MW6021.6";	//Estação de Comando no CCM - LP9
String PP_HL_MAQLEM_CML_UHIDNASSC		= "%MW6507.12"; //Acionamento Interno (Painel CML) - Unidade hidráulica não associada ao motor em operação
String PP_HL_MAQLEM_CML_CHKSELCUH		= "%MW6507.13"; //Acionamento Interno (Painel CML) - Check de Seleção de Unidade Hidráulica
String PC_HL_MAQLEM_CML_UHBBSEL			= "%MW6065.0";	//Unidade Hidráulica de BB selecionada - LP7
String PC_HL_MAQLEM_CML_UHBESEL			= "%MW6065.1";	//Unidade Hidráulica de BE selecionada - LP8
String PC_HL_MAQLEM_UHIDBB_NVBX			= "%MW6020.14"; //Nível baixo do fluído hidráulico na Unidade Hidráulica de BB - LP17
String PC_HL_MAQLEM_UHIDBB_TEMPAL		= "%MW6020.15"; //Alta Temperatura do fluído hidráulico na Unidade Hidráulica de BB - LP18
String PC_HL_MAQLEM_UHIDBB_PRESSBX		= "%MW6021.0";	//Baixa Pressão no circuito hidráulico na Unidade Hidráulica de BB - L19
String PP_HL_MAQLEM_UHIDBB_NVBX			= "%MW6506.12"; //Acionamento Interno (Painel CML) - Rep. PC_HL_MAQLEM_UHIDBB_NVBX
String PP_HL_MAQLEM_UHIDBB_TEMPAL		= "%MW6506.13"; //Acionamento Interno (Painel CML) - Rep. PC_HL_MAQLEM_UHIDBB_TEMPAL
String PP_HL_MAQLEM_UHIDBB_PRESSBX		= "%MW6506.14"; //Acionamento Interno (Painel CML) - Rep. PC_HL_MAQLEM_UHIDBB_PRESSBX
String PP_HL_MAQLEM_UHIDBB_SELEC		= "%MW6507.8";	//Comando de Seleção da Unidade Hidráulica de BB - Substitui chave S4
String PP_HL_MAQLEM_UHIDBB_TRFAUTO		= "%MW6507.9";	//Acionamento Interno (Painel CML) - Transf. Auto BB
String PC_HL_MAQLEM_UHIDBE_NVBX			= "%MW6021.1";	//Nível baixo do fluído hidráulico na Unidade Hidráulica de BE - LP23
String PC_HL_MAQLEM_UHIDBE_TEMPAL		= "%MW6021.2";	//Alta Temperatura do fluído hidráulico na Unidade Hidráulica de BE - LP24
String PC_HL_MAQLEM_UHIDBE_PRESSBX		= "%MW6021.3";	//Baixa Pressão no circuito hidráulico na Unidade Hidráulica de BE - L25
String PP_HL_MAQLEM_UHIDBE_NVBX			= "%MW6506.15"; //Acionamento Interno (Painel CML) - Rep. PC_HL_MAQLEM_UHIDBE_NVBX
String PP_HL_MAQLEM_UHIDBE_TEMPAL		= "%MW6507.0";	//Acionamento Interno (Painel CML) - Rep. PC_HL_MAQLEM_UHIDBE_TEMPAL
String PP_HL_MAQLEM_UHIDBE_PRESSBX		= "%MW6507.1";	//Acionamento Interno (Painel CML) - Rep. PC_HL_MAQLEM_UHIDBE_PRESSBX
String PP_HL_MAQLEM_UHIDBE_SELEC		= "%MW6507.10"; //Comando de Seleção da Unidade Hidráulica de BE - Substitui chave S4
String PP_HL_MAQLEM_UHIDBE_TRFAUTO		= "%MW6507.11"; //Acionamento Interno (Painel CML) - Transf. Auto BE
String CP_HL_MAQLEM_UHIDBB_SELEC		= "%MW512.0";	//Acionamento Interno (PRA 0100) - Rep. CP_HL_MAQLEM_UHIDBB_SELEC
String CP_HL_MAQLEM_UHIDBE_SELEC		= "%MW512.1";	//Acionamento Interno (PRA 0100) - Rep. CP_HL_MAQLEM_UHIDBE_SELEC
//-------------------------- PROTC  ----------------------------
String PC_HL_PROTC_PRPC_SINAL1			= "%MW6030.13"; //Proteção Catódica - Sinal 1
String PC_HL_PROTC_PRPC_SINAL2			= "%MW6030.14"; //Proteção Catódica - Sinal 2
String PC_HL_PROTC_PRPC_SINAL3			= "%MW6030.15"; //Proteção Catódica - Sinal 3
//-------------------------- RACAP  ----------------------------
String PC_HL_RACAP_CAAP01_LIGADO		= "%MW6010.0";	//Compressor de Ar de Alta Pressão N° 1 - Ligado
String PC_HL_RACAP_CAAP01_EMREM			= "%MW6010.1";	//Compressor de Ar de Alta Pressão N° 1 - Em Remoto
String PC_HL_RACAP_CAAP01_EMAUT			= "%MW6010.2";	//Compressor de Ar de Alta Pressão N° 1 - Em Automático
String PC_HL_RACAP_CAAP01_FALHA			= "%MW6010.3";	//Compressor de Ar de Alta Pressão N° 1 - Em Falha
String PC_HL_RACAP_CAAP02_LIGADO		= "%MW6010.4";	//Compressor de Ar de Alta Pressão N° 2 - Ligado
String PC_HL_RACAP_CAAP02_EMREM			= "%MW6010.5";	//Compressor de Ar de Alta Pressão N° 2 - Em Remoto
String PC_HL_RACAP_CAAP02_EMAUT			= "%MW6010.6";	//Compressor de Ar de Alta Pressão N° 2 - Em Automático
String PC_HL_RACAP_CAAP02_FALHA			= "%MW6010.7";	//Compressor de Ar de Alta Pressão N° 2 - Em Falha
String PC_HA_RACAP_RAPDPM_PRESS			= "%MF6052";	//Rede de Alta Pressão Dentro da Praça de Máquinas - Indicador de Pressão
String PC_HA_RACAP_RAPFPM_PRESS			= "%MF6050";	//Rede de Alta Pressão Fora da Praça de Máquinas - Indicador de Pressão
String PC_HA_RACAP_RAPMCP_PRESS			= "%MF6054";	//Rede de Alta Pressão do Motor de Combustão Principal - Indicador de Pressão
String CP_HL_RACAP_CAAP01_1S4			= "%MW500.0";	//Compressor de Ar de Alta Pressão N° 1 - 1S4
String CP_HL_RACAP_CAAP01_2S4			= "%MW500.1";	//Compressor de Ar de Alta Pressão N° 1 - 2S4
String CP_HL_RACAP_CAAP01_3S4			= "%MW500.2";	//Compressor de Ar de Alta Pressão N° 1 - 3S4
String CP_HL_RACAP_CAAP01_4S4			= "%MW500.3";	//Compressor de Ar de Alta Pressão N° 1 - 4S4
String CP_HL_RACAP_CAAP01_1S5			= "%MW500.4";	//Compressor de Ar de Alta Pressão N° 1 - 1S5
String CP_HL_RACAP_CAAP01_2S5			= "%MW500.5";	//Compressor de Ar de Alta Pressão N° 1 - 2S5
String CP_HL_RACAP_CAAP01_3S5			= "%MW500.6";	//Compressor de Ar de Alta Pressão N° 1 - 3S5
String CP_HL_RACAP_CAAP01_4S5			= "%MW500.7";	//Compressor de Ar de Alta Pressão N° 1 - 4S5
String CP_HL_RACAP_CAAP02_1S4			= "%MW500.8";	//Compressor de Ar de Alta Pressão N° 2 - 1S4
String CP_HL_RACAP_CAAP02_2S4			= "%MW500.9";	//Compressor de Ar de Alta Pressão N° 2 - 2S4
String CP_HL_RACAP_CAAP02_3S4			= "%MW500.10";	//Compressor de Ar de Alta Pressão N° 2 - 3S4
String CP_HL_RACAP_CAAP02_4S4			= "%MW500.11";	//Compressor de Ar de Alta Pressão N° 2 - 4S4
String CP_HL_RACAP_CAAP02_1S5			= "%MW500.12";	//Compressor de Ar de Alta Pressão N° 2 - 1S5
String CP_HL_RACAP_CAAP02_2S5			= "%MW500.13";	//Compressor de Ar de Alta Pressão N° 2 - 2S5
String CP_HL_RACAP_CAAP02_3S5			= "%MW500.14";	//Compressor de Ar de Alta Pressão N° 2 - 3S5
String CP_HL_RACAP_CAAP02_4S5			= "%MW500.15";	//Compressor de Ar de Alta Pressão N° 2 - 4S5
//-------------------------- RACUG  ----------------------------
String PC_HL_RACUG_EF1_LIGADO			= "%MW6028.0";	//Estação de Filtragem N° 1 - Ligado - AV
String PC_HL_RACUG_EF2_LIGADO			= "%MW6028.3";	//Estação de Filtragem N° 2 - Ligado - AR  e UCA 06
String PC_HL_RACUG_EF3_LIGADO			= "%MW6028.2";	//Estação de Filtragem N° 3 - Ligado - Compartimento UCA 05
String PC_HL_RACUG_EF4_LIGADO			= "%MW6028.8";	//Estação de Filtragem N° 4 - Ligado - UCA 01 e 02
String PC_HL_RACUG_UCA13_UMIDALTA		= "%MW6028.7";	//Unidade de Condicionamento de Ar N° 13 - Umidade Alta
String PC_HL_RACUG_UCA14_UMIDALTA		= "%MW6028.1";	//Unidade de Condicionamento de Ar N° 14 - Umidade Alta
//-------------------------- RADUG  ----------------------------
String PC_HL_RADUG_BECAD1_LIGADO		= "%MW6029.0";	//Bomba Elétrica de Circulação de Água Doce N° 1 - Ligado
String PC_HL_RADUG_BECAD2_LIGADO		= "%MW6028.14"; //Bomba Elétrica de Circulação de Água Doce N° 2 - Ligado
String PC_HL_RADUG_BECAQ_LIGADO			= "%MW6028.15"; //Bomba Elétrica de Circulação de Água Quente - Ligado
String PC_HL_RADUG_TAAD26_NIVELALTO		= "%MW6029.1";	//Tanque de Armazenamento de Água Doce N° 26 - Nível Alto
String PC_HL_RADUG_TAAD26_NIVELBAIXO		= "%MW6029.2";	//Tanque de Armazenamento de Água Doce N° 26 - Nível Baixo
String PC_HL_RADUG_TAAD27_NIVELALTO		= "%MW6029.3";	//Tanque de Armazenamento de Água Doce N° 27 - Nível Alto
String PC_HL_RADUG_TAAD27_NIVELBAIXO		= "%MW6029.4";	//Tanque de Armazenamento de Água Doce N° 27 - Nível Baixo
String PC_HL_RADUG_VAP001_FECHADO		= "%MW6010.14"; //Válvula do Sistema de Água Desmineralizada N° 1 - Fechado
String PC_HL_RADUG_VAP001_ABERTO		= "%MW6010.15"; //Válvula do Sistema de Água Desmineralizada N° 1 - Aberto
String PC_HL_RADUG_VAP002_FECHADO		= "%MW6011.0";	//Válvula do Sistema de Água Desmineralizada N° 2 - Fechado
String PC_HL_RADUG_VAP002_ABERTO		= "%MW6011.1";	//Válvula do Sistema de Água Desmineralizada N° 2 - Aberto
String CP_HL_RADUG_VAP001_FECHAR		= "%MW501.2";	//Válvula do Sistema de Água Desmineralizada N° 1 - Fechar
String CP_HL_RADUG_VAP001_ABRIR			= "%MW501.3";	//Válvula do Sistema de Água Desmineralizada N° 1 - Abrir
String CP_HL_RADUG_VAP002_FECHAR		= "%MW501.4";	//Válvula do Sistema de Água Desmineralizada N° 2 - Fechar
String CP_HL_RADUG_VAP002_ABRIR			= "%MW501.5";	//Válvula do Sistema de Água Desmineralizada N° 2 - Abrir
//-------------------------- RARCF  ----------------------------
String PC_HL_RARCF_CFCAR_TEMPALTA		= "%MW6031.4";	//Câmara de Carnes - Temperatura Alta
String PC_HL_RARCF_CFLAT_TEMPALTA		= "%MW6031.2";	//Câmara de Laticínios - Temperatura Alta
String PC_HL_RARCF_CFLAT_TEMPBAIXA		= "%MW6031.3";	//Câmara de Laticínios - Temperatura Baixa
String PC_HL_RARCF_CFVEG_TEMPALTA		= "%MW6031.0";	//Câmara de Vegetais - Temperatura Alta
String PC_HL_RARCF_CFVEG_TEMPBAIXA		= "%MW6031.1";	//Câmara de Vegetais - Temperatura Baixa
//-------------------------- RARUG  ----------------------------
String PC_HL_RARUG_BEAGD1_FALHA			= "%MW6029.11"; //Bomba Elétrica de Água Doce N° 1 - Em Falha
String PC_HL_RARUG_BEAGD1_LIGADO		= "%MW6029.12"; //Bomba Elétrica de Água Doce N° 1 - Ligado
String PC_HL_RARUG_BEAGD2_FALHA			= "%MW6029.13"; //Bomba Elétrica de Água Doce N° 2 - Em Falha
String PC_HL_RARUG_BEAGD2_LIGADO		= "%MW6029.14"; //Bomba Elétrica de Água Doce N° 2 - Ligado
String PC_HL_RARUG_URA1_FALHA			= "%MW6029.9";	//Unidade de Resfriamento de Água N° 1 - Em Falha
String PC_HL_RARUG_URA1_LIGADO			= "%MW6029.10"; //Unidade de Resfriamento de Água N° 1 - Ligado
String PC_HL_RARUG_URA2_FALHA			= "%MW6029.5";	//Unidade de Resfriamento de Água N° 2 - Em Falha
String PC_HL_RARUG_URA2_LIGADO			= "%MW6029.6";	//Unidade de Resfriamento de Água N° 2 - Ligado
String PC_HL_RARUG_URA3_FALHA			= "%MW6029.7";	//Unidade de Resfriamento de Água N° 3 - Em Falha
String PC_HL_RARUG_URA3_LIGADO			= "%MW6029.8";	//Unidade de Resfriamento de Água N° 3 - Ligado
//-------------------------- RASIS  ----------------------------
String PC_HL_RASIS_BECAS1_LIGADO		= "%MW6011.10"; //Bomba Elétrica de Circulação de Água Salgada N° 1 - Ligado
String PC_HL_RASIS_BECAS1_EMREM			= "%MW6011.11"; //Bomba Elétrica de Circulação de Água Salgada N° 1 - Em Remoto
String PC_HL_RASIS_BECAS1_SOBREC1		= "%MW6011.12"; //Bomba Elétrica de Circulação de Água Salgada N° 1 - Sobrecarga
String PC_HL_RASIS_BECAS1_SOBREC2		= "%MW6011.13"; //Bomba Elétrica de Circulação de Água Salgada N° 1 - Sobretemperatura
String PC_HL_RASIS_BECAS1_PRDEMERGLOCAL		= "%MW6011.14"; //Bomba Elétrica de Circulação de Água Salgada N° 1 - Parada Emerg. Local
String PC_HL_RASIS_BECAS2_LIGADO		= "%MW6011.2";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Ligado
String PC_HL_RASIS_BECAS2_EMREM			= "%MW6011.3";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Em Remoto
String PC_HL_RASIS_BECAS2_SOBREC1		= "%MW6011.4";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Sobrecarga
String PC_HL_RASIS_BECAS2_SOBREC2		= "%MW6011.5";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Sobretemperatura
String PC_HL_RASIS_BECAS2_PRDEMERGLOCAL		= "%MW6011.6";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Parada Emerg. Local
String PC_HL_RASIS_BECAS3_LIGADO		= "%MW6012.0";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Ligado
String PC_HL_RASIS_BECAS3_EMREM			= "%MW6012.1";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Em Remoto
String PC_HL_RASIS_BECAS3_SOBREC1		= "%MW6012.2";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Sobrecarga
String PC_HL_RASIS_BECAS3_SOBREC2		= "%MW6012.3";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Sobretemperatura
String PC_HL_RASIS_BECAS3_PRDEMERGLOCAL		= "%MW6012.4";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Parada Emerg. Local
String CP_HL_RASIS_BECAS1_LIGAR			= "%MW501.10";	//Bomba Elétrica de Circulação de Água Salgada N° 1 - Ligar
String CP_HL_RASIS_BECAS1_DESLIGAR		= "%MW501.11";	//Bomba Elétrica de Circulação de Água Salgada N° 1 - Desligar
String CP_HL_RASIS_BECAS1_PARAREMERG		= "%MW501.12";	//Bomba Elétrica de Circulação de Água Salgada N° 1 - Parar em Emergência
String CP_HL_RASIS_BECAS2_LIGAR			= "%MW502.0";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Ligar
String CP_HL_RASIS_BECAS2_DESLIGAR		= "%MW502.1";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Desligar
String CP_HL_RASIS_BECAS2_PARAREMERG		= "%MW502.2";	//Bomba Elétrica de Circulação de Água Salgada N° 2 - Parar em Emergência
String CP_HL_RASIS_BECAS3_LIGAR			= "%MW501.13";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Ligar
String CP_HL_RASIS_BECAS3_DESLIGAR		= "%MW501.14";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Desligar
String CP_HL_RASIS_BECAS3_PARAREMERG		= "%MW501.15";	//Bomba Elétrica de Circulação de Água Salgada N° 3 - Parar em Emergência
String PC_HA_RASIS_RASAPM_PRESS			= "%MF6100";	//Rede de Água Salgada do Anel Principal a Meia - Indicador de Pressão
String PC_HA_RASIS_RASAPR_PRESS			= "%MF6102";	//Rede de Água Salgada do Anel Principal a Ré - Indicador de Pressão
String PC_HA_RASIS_RASAPV_PRESS			= "%MF6098";	//Rede de Água Salgada do Anel Principal a Vante - Indicador de Pressão
//-------------------------- RASRG  ----------------------------
String PC_HL_RASRG_OERHPC_PRESSBAIXA		= "%MW6029.15"; //Selo de Água Salgada da ER e HPC - Pressão Baixa
//-------------------------- SODPG ----------------------------
String PC_HL_SODPG_AQCOD1_LIGADO	        = "%MW6012.8";	//Aquecedor de Óleo Diesel N° 1 - Ligado
String PC_HL_SODPG_AQCOD1_ENERGIZADO	        = "%MW6012.9";	//Aquecedor de Óleo Diesel N° 1 - Energizado
String PC_HL_SODPG_AQCOD1_EMREM	                = "%MW6012.10";	//Aquecedor de Óleo Diesel N° 1 - Em Remoto
String PC_HL_SODPG_AQCOD1_FALHA	                = "%MW6012.11";	//Aquecedor de Óleo Diesel N° 1 - Em Falha
String CP_HL_SODPG_AQCOD1_LIGAR	                = "%MW502.3";	//Aquecedor de Óleo Diesel N° 1 - Ligar
String CP_HL_SODPG_AQCOD1_DESLIGAR	        = "%MW502.4";	//Aquecedor de Óleo Diesel N° 1 - Desligar
String PC_HL_SODPG_AQCOD2_LIGADO	        = "%MW6012.12";	//Aquecedor de Óleo Diesel N° 2 - Ligado
String PC_HL_SODPG_AQCOD2_ENERGIZADO	        = "%MW6012.13";	//Aquecedor de Óleo Diesel N° 2 - Energizado
String PC_HL_SODPG_AQCOD2_EMREM	                = "%MW6012.14";	//Aquecedor de Óleo Diesel N° 2 - Em Remoto
String PC_HL_SODPG_AQCOD2_FALHA	                = "%MW6012.15";	//Aquecedor de Óleo Diesel N° 2 - Em Falha
String CP_HL_SODPG_AQCOD2_LIGAR	                = "%MW502.5";	//Aquecedor de Óleo Diesel N° 2 - Ligar
String CP_HL_SODPG_AQCOD2_DESLIGAR	        = "%MW502.6";	//Aquecedor de Óleo Diesel N° 2 - Desligar
String PC_HL_SODPG_BEROD1_LIGADO	        = "%MW6013.0";	//Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Ligado
String PC_HL_SODPG_BEROD1_EMREM	                = "%MW6013.1";	//Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Em Remoto
String PC_HL_SODPG_BEROD1_SOBREC1	        = "%MW6013.2";	//Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Sobrecarga 1
String CP_HL_SODPG_BEROD1_LIGAR	                = "%MW502.7";	//Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Ligar
String CP_HL_SODPG_BEROD1_DESLIGAR	        = "%MW502.8";	//Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Desligar
String CP_HL_SODPG_BEROD1_PARAREMERG	        = "%MW502.9";	//Bomba Elétrica de Recalque de Óleo Diesel N° 1 - Parar em Emergência
String PC_HL_SODPG_BEROD2_LIGADO	        = "%MW6013.4";	//Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Ligado
String PC_HL_SODPG_BEROD2_EMREM	                = "%MW6013.5";	//Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Em Remoto
String PC_HL_SODPG_BEROD2_SOBREC1	        = "%MW6013.6";	//Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Sobrecarga 1
String CP_HL_SODPG_BEROD2_LIGAR	                = "%MW502.10";	//Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Ligar
String CP_HL_SODPG_BEROD2_DESLIGAR	        = "%MW502.11";	//Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Desligar
String CP_HL_SODPG_BEROD2_PARAREMERG	        = "%MW502.12";	//Bomba Elétrica de Recalque de Óleo Diesel N° 2 - Parar em Emergência
String PC_HL_SODPG_FCOD1_PRESSDIFALTA	        = "%MW6031.5";	//Filtro Coalescedor N° 1 - Pressão Diferencial Alta
String PC_HL_SODPG_FCOD2_PRESSDIFALTA	        = "%MW6031.6";	//Filtro Coalescedor N° 2 - Pressão Diferencial Alta
String PC_HA_SODPG_RSODTG_TEMP	                = "%MF6104";	//Rede de Serviço de Óleo Diesel da Turbina à Gás - Indicador de Temperatura
String PC_HA_SODPG_RSODTG_PRESS	                = "%MF6106";	//Rede de Serviço de Óleo Diesel da Turbina à Gás - Indicador de Pressão
String PC_HL_SODPG_TSOD07_NIVELBAIXO	        = "%MW6032.14";	//Tanque de Serviço de Óleo Diesel N° 7 - Nível Baixo
String PC_HL_SODPG_TSOD07_NIVELALTO	        = "%MW6033.5";	//Tanque de Serviço de Óleo Diesel N° 7 - Nível Alto
String PC_HA_SODPG_TSOD07_NIVEL	                = "%MF6136";	//Tanque de Serviço de Óleo Diesel N° 7 - Indicador de Nível
String PC_HL_SODPG_TSOD08_NIVELBAIXO	        = "%MW6032.4";	//Tanque de Serviço de Óleo Diesel N° 8 - Nível Baixo
String PC_HL_SODPG_TSOD08_NIVELALTO	        = "%MW6033.0";	//Tanque de Serviço de Óleo Diesel N° 8 - Nível Alto
String PC_HA_SODPG_TSOD08_TEMP		        = "%MF6108";	//Tanque de Serviço de Óleo Diesel N° 8 - Indicador de Temperatura
String PC_HA_SODPG_TSOD08_NIVEL		        = "%MF6120";	//Tanque de Serviço de Óleo Diesel N° 8 - Indicador de Nível
String PC_HL_SODPG_TSOD09_NIVELBAIXO	        = "%MW6032.5";	//Tanque de Serviço de Óleo Diesel N° 9 - Nível Baixo
String PC_HL_SODPG_TSOD09_NIVELALTO	        = "%MW6033.1";	//Tanque de Serviço de Óleo Diesel N° 9 - Nível Alto
String PC_HA_SODPG_TSOD09_TEMP	                = "%MF6110";	//Tanque de Serviço de Óleo Diesel N° 9 - Indicador de Temperatura
String PC_HA_SODPG_TSOD09_NIVEL	                = "%MF6122";	//Tanque de Serviço de Óleo Diesel N° 9 - Indicador de Nível
String PC_HL_SODPG_TSOD10_NIVELBAIXO	        = "%MW6032.6";	//Tanque de Serviço de Óleo Diesel N° 10 - Nível Baixo
String PC_HL_SODPG_TSOD10_NIVELALTO	        = "%MW6033.2";	//Tanque de Serviço de Óleo Diesel N° 10 - Nível Alto
String PC_HA_SODPG_TSOD10_NIVEL	                = "%MF6124";	//Tanque de Serviço de Óleo Diesel N° 10 - Indicador de Nível
String PC_HL_SODPG_TSOD11_NIVELBAIXO	        = "%MW6032.15";	//Tanque de Serviço de Óleo Diesel N° 11 - Nível Baixo
String PC_HL_SODPG_TSOD11_NIVELALTO	        = "%MW6033.3";	//Tanque de Serviço de Óleo Diesel N° 11 - Nível Alto
String PC_HA_SODPG_TSOD11_NIVEL	                = "%MF6138";	//Tanque de Serviço de Óleo Diesel N° 11 - Indicador de Nível
String PC_HL_SODPG_VOD098_FECHADO	        = "%MW6016.0";	//Válvula de Óleo Diesel N° 098 - Fechado
String PC_HL_SODPG_VOD098_ABERTO	        = "%MW6016.1";	//Válvula de Óleo Diesel N° 098 - Aberto
String CP_HL_SODPG_VOD098_FECHAR	        = "%MW504.0";	//Válvula de Óleo Diesel N° 098 - Fechar
String CP_HL_SODPG_VOD098_ABRIR	                = "%MW504.1";	//Válvula de Óleo Diesel N° 098 - Abrir
String PC_HL_SODPG_VOD101_FECHADO	        = "%MW6016.4";	//Válvula de Óleo Diesel N° 101 - Fechado
String PC_HL_SODPG_VOD101_ABERTO	        = "%MW6016.5";	//Válvula de Óleo Diesel N° 101 - Aberto
String CP_HL_SODPG_VOD101_FECHAR	        = "%MW504.4";	//Válvula de Óleo Diesel N° 101 - Fechar
String CP_HL_SODPG_VOD101_ABRIR	                = "%MW504.5";	//Válvula de Óleo Diesel N° 101 - Abrir
String PC_HL_SODPG_VOD103_FECHADO	        = "%MW6016.6";	//Válvula de Óleo Diesel N° 103 - Fechado
String PC_HL_SODPG_VOD103_ABERTO	        = "%MW6016.7";	//Válvula de Óleo Diesel N° 103 - Aberto
String CP_HL_SODPG_VOD103_FECHAR	        = "%MW504.6";	//Válvula de Óleo Diesel N° 103 - Fechar
String CP_HL_SODPG_VOD103_ABRIR	                = "%MW504.7";	//Válvula de Óleo Diesel N° 103 - Abrir
String PC_HL_SODPG_VOD106_FECHADO	        = "%MW6016.2";	//Válvula de Óleo Diesel N° 106 - Fechado
String PC_HL_SODPG_VOD106_ABERTO	        = "%MW6016.3";	//Válvula de Óleo Diesel N° 106 - Aberto
String CP_HL_SODPG_VOD106_FECHAR	        = "%MW504.2";	//Válvula de Óleo Diesel N° 106 - Fechar
String CP_HL_SODPG_VOD106_ABRIR	                = "%MW504.3";	//Válvula de Óleo Diesel N° 106 - Abrir
String PC_HL_SODPG_VOD120_FECHADO	        = "%MW6016.11";	//Válvula de Óleo Diesel N° 120 - Fechado
String PC_HL_SODPG_VOD120_ABERTO	        = "%MW6016.12";	//Válvula de Óleo Diesel N° 120 - Aberto
String CP_HL_SODPG_VOD120_ABRIR	                = "%MW504.10";	//Válvula de Óleo Diesel N° 120 - Abrir
String PC_HL_SODPG_VOD122_FECHADO	        = "%MW6016.9";	//Válvula de Óleo Diesel N° 122 - Fechado
String PC_HL_SODPG_VOD122_ABERTO	        = "%MW6016.10";	//Válvula de Óleo Diesel N° 122 - Aberto
String CP_HL_SODPG_VOD122_FECHAR	        = "%MW504.8";	//Válvula de Óleo Diesel N° 122 - Fechar
String CP_HL_SODPG_VOD122_ABRIR	                = "%MW504.9";	//Válvula de Óleo Diesel N° 122 - Abrir
String PC_HL_SODPG_VOD129_FECHADO	        = "%MW6017.0";	//Válvula de Óleo Diesel N° 129 - Fechado
String PC_HL_SODPG_VOD129_ABERTO	        = "%MW6017.1";	//Válvula de Óleo Diesel N° 129 - Aberto
String CP_HL_SODPG_VOD129_ABRIR	                = "%MW504.13";	//Válvula de Óleo Diesel N° 129 - Abrir
String PC_HL_SODPG_VOD133_FECHADO	        = "%MW6016.13";	//Válvula de Óleo Diesel N° 133 - Fechado
String PC_HL_SODPG_VOD133_ABERTO	        = "%MW6016.14";	//Válvula de Óleo Diesel N° 133 - Aberto
String CP_HL_SODPG_VOD133_FECHAR	        = "%MW504.11";	//Válvula de Óleo Diesel N° 133 - Fechar
String CP_HL_SODPG_VOD133_ABRIR	                = "%MW504.12";	//Válvula de Óleo Diesel N° 133 - Abrir
String PC_HL_SODPG_VOD152_FECHADO	        = "%MW6017.4";	//Válvula de Óleo Diesel N° 152 - Fechado
String PC_HL_SODPG_VOD152_ABERTO	        = "%MW6017.5";	//Válvula de Óleo Diesel N° 152 - Aberto
String CP_HL_SODPG_VOD152_ABRIR	                = "%MW505.0";	//Válvula de Óleo Diesel N° 152 - Abrir
String PC_HL_SODPG_VOD155_FECHADO	        = "%MW6017.2";	//Válvula de Óleo Diesel N° 155 - Fechado
String PC_HL_SODPG_VOD155_ABERTO	        = "%MW6017.3";	//Válvula de Óleo Diesel N° 155 - Aberto
String CP_HL_SODPG_VOD155_FECHAR	        = "%MW504.14";	//Válvula de Óleo Diesel N° 155 - Fechar
String CP_HL_SODPG_VOD155_ABRIR	                = "%MW504.15";	//Válvula de Óleo Diesel N° 155 - Abrir
//-------------------------- VEDPM  ----------------------------
String PC_HA_VEDPM_RVENPMA_TEMP			= "%MF6038";	//Rede de Ventilação da Praça de Máquinas de Auxiliares - Indicador de Temperatura
String PC_HA_VEDPM_RVENPMR_TEMP			= "%MF6036";	//Rede de Ventilação da Praça de Máquinas à Ré - Indicador de Temperatura
String PC_HA_VEDPM_RVENPMV_TEMP			= "%MF6034";	//Rede de Ventilação da Praça de Máquinas à Vante - Indicador de Temperatura
//-------------------------- VEFPM  ----------------------------
String PC_HA_VEFPM_ANTCME_TEMP			= "%MF6042";	//Compartimento da Antena do CME - Indicador de Temperatura
String PC_HA_VEFPM_ANTMAGE_TEMP			= "%MF6040";	//Compartimento da Antena do MAGE - Indicador de Temperatura
String PC_HA_VEFPM_CONTALCA_TEMP		= "%MF6048";	//Compartimento da Alça do Canhão - Indicador de Temperatura
String PC_HA_VEFPM_CPTCME_TEMP			= "%MF6044";	//Compartimento do CME - Indicador de Temperatura
String PC_HA_VEFPM_ESTCHAFF_TEMP		= "%MF6046";	//Estação do CHAFF - Indicador de Temperatura
String PC_HL_VEFPM_EXAE01_LIGADO		= "%MW6028.9";	//Exaustor E1 - Ligado - Exaustão dos Banheiros
String PC_HL_VEFPM_EXAE02_LIGADO		= "%MW6028.10"; //Exaustor E2 - Ligado - Banheiros de SO / SG
String PC_HL_VEFPM_EXAE03_LIGADO		= "%MW6028.4";	//Exaustor E3 - Ligado - Enfermaria
String PC_HL_VEFPM_EXAE04_LIGADO		= "%MW6028.13"; //Exaustor E4 - Ligado - Cozinha
String PC_HL_VEFPM_EXAE05_LIGADO		= "%MW6028.12"; //Exaustor E5 - Ligado - Paiol de Tintas e Inflamáveis
String PC_HL_VEFPM_EXAE06_LIGADO		= "%MW6028.5";	//Exaustor E6 - Ligado - Compartimento de JP5
String PC_HL_VEFPM_EXAE07_LIGADO		= "%MW6028.11"; //Exaustor E7 - Ligado - PMA
String PC_HL_VEFPM_VENT_LIGADO			= "%MW6028.6";	//Ventilador - Ligado - Compartimento da Torreta do Canhão

//--------------------- VARIAVEIS INTERNAS ---------------------
String IP              = "120.40.0.1";
String CONTADOR_CONEXAO= "%MW33000";
String NomeForm        = "EQUIP. AUXILIARES - JÚLIO DE NORONHA - V 0.0.1 b";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;
int    lista           = 0;
bool   modooperacao    = true;

bool   operaauto_cnod  = true;

bool   VOD012_RetornoAuto = true;
bool   VOD012_ModoOpera   = false;
bool   VOD013_RetornoAuto = true;
bool   VOD013_ModoOpera   = false;
bool   VOD014_RetornoAuto = true;
bool   VOD014_ModoOpera   = false;
bool   VOD015_RetornoAuto = true;
bool   VOD015_ModoOpera   = false;
bool   VOD016_RetornoAuto = true;
bool   VOD016_ModoOpera   = false;
bool   VOD017_RetornoAuto = true;
bool   VOD017_ModoOpera   = false;

bool   VOD059_RetornoAuto = true;
bool   VOD059_ModoOpera   = false;
bool   VOD060_RetornoAuto = true;
bool   VOD060_ModoOpera   = false;
bool   VOD061_RetornoAuto = true;
bool   VOD061_ModoOpera   = false;
bool   VOD062_RetornoAuto = true;
bool   VOD062_ModoOpera   = false;
bool   VOD063_RetornoAuto = true;
bool   VOD063_ModoOpera   = false;
bool   VOD064_RetornoAuto = true;
bool   VOD064_ModoOpera   = false;

bool   VOD005_ModoOpera   = false;
bool   VOD010_ModoOpera   = false;

bool   VOD030_ModoOpera   = false;
bool   VOD031_ModoOpera   = false;

bool   VOD035_ModoOpera   = false;
bool   VOD043_ModoOpera   = false;
bool   VOD066_ModoOpera   = false;

bool   VOD103_ModoOpera   = false;
bool   VOD106_ModoOpera   = false;
bool   VOD101_ModoOpera   = false;
bool   VOD098_ModoOpera   = false;

bool   VOD120_RetornoAuto = true;
bool   VOD120_ModoOpera   = false;
bool   VOD129_RetornoAuto = true;
bool   VOD129_ModoOpera   = false;
bool   VOD152_RetornoAuto = true;
bool   VOD152_ModoOpera   = false;

bool   VOD122_ModoOpera   = false;
bool   VOD133_ModoOpera   = false;
bool   VOD155_ModoOpera   = false;

bool CAAP01_1S4 = false;
bool CAAP01_2S4 = false;
bool CAAP01_3S4 = false;
bool CAAP01_4S4 = false;
bool CAAP01_1S5 = false;
bool CAAP01_2S5 = false;
bool CAAP01_3S5 = false;
bool CAAP01_4S5 = false;

bool CAAP02_1S4 = false;
bool CAAP02_2S4 = false;
bool CAAP02_3S4 = false;
bool CAAP02_4S4 = false;
bool CAAP02_1S5 = false;
bool CAAP02_2S5 = false;
bool CAAP02_3S5 = false;
bool CAAP02_4S5 = false;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;
//INCIALIZAÇÃO DO DRIVER
//TModBusScanner CLP ( frmPrincipal, QUANTUM, 2, 2 );
TModBusTCPDriver CLP ( frmPrincipal, IP, QUANTUM);
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
        frmPrincipal->Top = 10;
        frmPrincipal->Left = 10;
        frmPrincipal->Width = 1024;
        frmPrincipal->Height = 724;

        pnlStatus->Visible = true;
        pnlStatus->Top  = 0;
        pnlStatus->Left = 0;

        mnuODiesel->Enabled = false;
        mnuRACAP->Enabled = false;
        mnuAOLTG->Enabled = false;
        mnuAgua->Enabled = false;
        mnuCPTAS->Enabled = false;
        mnuMAQLEM->Enabled = false;
        mnuGERENE->Enabled = false;
        mnuPROTC->Enabled = false;
        mnuRARCF->Enabled = false;
        mnuVentilacao->Enabled = false;

        pnlSVCOD_1->Visible = false;
        pnlSVCOD_1->Top  = 0;
        pnlSVCOD_1->Left = 0;
        pnlSVCOD_2->Visible = false;
        pnlSVCOD_2->Top  = 0;
        pnlSVCOD_2->Left = 0;

        pnlAODPG_1->Visible = false;
        pnlAODPG_1->Top  = 0;
        pnlAODPG_1->Left = 0;
        pnlAODPG_2->Visible = false;
        pnlAODPG_2->Top  = 0;
        pnlAODPG_2->Left = 0;

        pnlCPTAS->Visible = false;
        pnlCPTAS->Top  = 0;
        pnlCPTAS->Left = 0;

        pnlAOLTG->Visible = false;
        pnlAOLTG->Top  = 0;
        pnlAOLTG->Left = 0;

        pnlDASOR->Visible = false;
        pnlDASOR->Top  = 0;
        pnlDASOR->Left = 0;

        pnlGERENE->Visible = false;
        pnlGERENE->Top  = 0;
        pnlGERENE->Left = 0;

        pnlPROTC->Visible = false;
        pnlPROTC->Top  = 0;
        pnlPROTC->Left = 0;

        pnlRACAP->Visible = false;
        pnlRACAP->Top  = 0;
        pnlRACAP->Left = 0;

        pnlRACUG->Visible = false;
        pnlRACUG->Top  = 0;
        pnlRACUG->Left = 0;

        pnlRADUG->Visible = false;
        pnlRADUG->Top  = 0;
        pnlRADUG->Left = 0;

        pnlRARCF->Visible = false;
        pnlRARCF->Top  = 0;
        pnlRARCF->Left = 0;

        pnlRARUG->Visible = false;
        pnlRARUG->Top  = 0;
        pnlRARUG->Left = 0;

        pnlRASIS->Visible = false;
        pnlRASIS->Top  = 0;
        pnlRASIS->Left = 0;

        pnlRASRG->Visible = false;
        pnlRASRG->Top  = 0;
        pnlRASRG->Left = 0;

        pnlVEDPM->Visible = false;
        pnlVEDPM->Top  = 0;
        pnlVEDPM->Left = 0;

        pnlVEFPM->Visible = false;
        pnlVEFPM->Top  = 0;
        pnlVEFPM->Left = 0;

        pnlMaqLem->Visible = false;
        pnlMaqLem->Top  = 0;
        pnlMaqLem->Left = 0;

        DateTimeToString( TimeStamp, AnsiString( "DD/MM/YY hh:nn:ss" ), Now() );

        lblInicioPrograma->Caption = TimeStamp;
        lblInicioPrograma->Visible = true;
        lblEndereco->Caption = CONTADOR_CONEXAO;
        lblEndereco->Visible = true;
        lblWatchdogEx->Visible = true;

        tmrStarting->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrStartingTimer(TObject *Sender)
{
//--------------------- INICIA ANALÓGICAS ---------------------
        if (CLP.RD(PC_HA_AODPG_TAOD01_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TAOD01_NIVEL     , 1.2);
               CLP.WR(PC_HL_AODPG_TAOD01_NIVELALTO , 1);
               CLP.WR(PC_HL_AODPG_TAOD01_TRANSBORDA, 0);
        }
        txtTAOD01_NIVEL->Text = CLP.RD(PC_HA_AODPG_TAOD01_NIVEL);
        txtTAOD01_NIVEL->Text = FormatFloat("0.###",txtTAOD01_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TAOD02_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TAOD02_NIVEL     , 1.2);
               CLP.WR(PC_HL_AODPG_TAOD02_NIVELALTO , 1);
               CLP.WR(PC_HL_AODPG_TAOD02_TRANSBORDA, 0);
        }
        txtTAOD02_NIVEL->Text = CLP.RD(PC_HA_AODPG_TAOD02_NIVEL);
        txtTAOD02_NIVEL->Text = FormatFloat("0.###",txtTAOD02_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TAOD03_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TAOD03_NIVEL     , 0.63);
               CLP.WR(PC_HL_AODPG_TAOD03_NIVELALTO , 1);
               CLP.WR(PC_HL_AODPG_TAOD03_TRANSBORDA, 0);
        }
        txtTAOD03_NIVEL->Text = CLP.RD(PC_HA_AODPG_TAOD03_NIVEL);
        txtTAOD03_NIVEL->Text = FormatFloat("0.###",txtTAOD03_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TAOD04_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TAOD04_NIVEL     , 1.9);
               CLP.WR(PC_HL_AODPG_TAOD04_NIVELALTO , 1);
               CLP.WR(PC_HL_AODPG_TAOD04_TRANSBORDA, 0);
        }
        txtTAOD04_NIVEL->Text = CLP.RD(PC_HA_AODPG_TAOD04_NIVEL);
        txtTAOD04_NIVEL->Text = FormatFloat("0.###",txtTAOD04_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TAOD05_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TAOD05_NIVEL     , 1.7);
               CLP.WR(PC_HL_AODPG_TAOD05_NIVELALTO , 1);
               CLP.WR(PC_HL_AODPG_TAOD05_TRANSBORDA, 0);
        }
        txtTAOD05_NIVEL->Text = CLP.RD(PC_HA_AODPG_TAOD05_NIVEL);
        txtTAOD05_NIVEL->Text = FormatFloat("0.###",txtTAOD05_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TAOD06_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TAOD06_NIVEL     , 1.7);
               CLP.WR(PC_HL_AODPG_TAOD06_NIVELALTO , 1);
               CLP.WR(PC_HL_AODPG_TAOD06_TRANSBORDA, 0);
        }
        txtTAOD06_NIVEL->Text = CLP.RD(PC_HA_AODPG_TAOD06_NIVEL);
        txtTAOD06_NIVEL->Text = FormatFloat("0.###",txtTAOD06_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TTOD12_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TTOD12_NIVEL     , 0.6);
               CLP.WR(PC_HL_AODPG_TTOD12_NIVELALTO , 1);
        }
        txtTTOD12_NIVEL->Text = CLP.RD(PC_HA_AODPG_TTOD12_NIVEL);
        txtTTOD12_NIVEL->Text = FormatFloat("0.###",txtTTOD12_NIVEL->Text.ToDouble());
        if (CLP.RD(PC_HA_AODPG_TTOD13_NIVEL) == 0){
               CLP.WR(PC_HA_AODPG_TTOD13_NIVEL     , 0.6);
               CLP.WR(PC_HL_AODPG_TTOD13_NIVELALTO , 1);
        }
        txtTTOD13_NIVEL->Text = CLP.RD(PC_HA_AODPG_TTOD13_NIVEL);
        txtTTOD13_NIVEL->Text = FormatFloat("0.###",txtTTOD13_NIVEL->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD08_NIVEL) == 0){
               CLP.WR(PC_HA_SODPG_TSOD08_NIVEL      , 2.0);
               CLP.WR(PC_HL_SODPG_TSOD08_NIVELALTO  , 1);
               CLP.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO , 0);
        }
        txtTSOD08_NIVEL->Text = CLP.RD(PC_HA_SODPG_TSOD08_NIVEL);
        txtTSOD08_NIVEL->Text = FormatFloat("0.###",txtTSOD08_NIVEL->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD08_TEMP) == 0){
               CLP.WR(PC_HA_SODPG_TSOD08_TEMP      , 25.0);
        }
        txtTSOD08_TEMP->Text = CLP.RD(PC_HA_SODPG_TSOD08_TEMP);
        txtTSOD08_TEMP->Text = FormatFloat("0.###",txtTSOD08_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD09_NIVEL) == 0){
               CLP.WR(PC_HA_SODPG_TSOD09_NIVEL      , 2.0);
               CLP.WR(PC_HL_SODPG_TSOD09_NIVELALTO  , 1);
               CLP.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO , 0);
        }
        txtTSOD09_NIVEL->Text = CLP.RD(PC_HA_SODPG_TSOD09_NIVEL);
        txtTSOD09_NIVEL->Text = FormatFloat("0.###",txtTSOD09_NIVEL->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD09_TEMP) == 0){
               CLP.WR(PC_HA_SODPG_TSOD09_TEMP      , 25.0);
        }
        txtTSOD09_TEMP->Text = CLP.RD(PC_HA_SODPG_TSOD09_TEMP);
        txtTSOD09_TEMP->Text = FormatFloat("0.###",txtTSOD09_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD07_NIVEL) == 0){
               CLP.WR(PC_HA_SODPG_TSOD07_NIVEL      , 1.2);
               CLP.WR(PC_HL_SODPG_TSOD07_NIVELALTO  , 1);
               CLP.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO , 0);
        }
        txtTSOD07_NIVEL->Text = CLP.RD(PC_HA_SODPG_TSOD07_NIVEL);
        txtTSOD07_NIVEL->Text = FormatFloat("0.###",txtTSOD07_NIVEL->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD10_NIVEL) == 0){
               CLP.WR(PC_HA_SODPG_TSOD10_NIVEL      , 0.9);
               CLP.WR(PC_HL_SODPG_TSOD10_NIVELALTO  , 1);
               CLP.WR(PC_HL_SODPG_TSOD10_NIVELBAIXO , 0);
        }
        txtTSOD10_NIVEL->Text = CLP.RD(PC_HA_SODPG_TSOD10_NIVEL);
        txtTSOD10_NIVEL->Text = FormatFloat("0.###",txtTSOD10_NIVEL->Text.ToDouble());

        if (CLP.RD(PC_HA_SODPG_TSOD11_NIVEL) == 0){
               CLP.WR(PC_HA_SODPG_TSOD11_NIVEL      , 0.9);
               CLP.WR(PC_HL_SODPG_TSOD11_NIVELALTO  , 1);
               CLP.WR(PC_HL_SODPG_TSOD11_NIVELBAIXO , 0);
        }
        txtTSOD11_NIVEL->Text = CLP.RD(PC_HA_SODPG_TSOD11_NIVEL);
        txtTSOD11_NIVEL->Text = FormatFloat("0.###",txtTSOD11_NIVEL->Text.ToDouble());

        if (CLP.RD(PC_HA_RACAP_RAPDPM_PRESS) == 0){
               CLP.WR(PC_HA_RACAP_RAPDPM_PRESS      , 275);
        }
        txtRACAP_RAPDPM_PRESS->Text = CLP.RD(PC_HA_RACAP_RAPDPM_PRESS);
        txtRACAP_RAPDPM_PRESS->Text = FormatFloat("0.###",txtRACAP_RAPDPM_PRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_RACAP_RAPFPM_PRESS) == 0){
               CLP.WR(PC_HA_RACAP_RAPFPM_PRESS      , 250);
        }
        txtRACAP_RAPFPM_PRESS->Text = CLP.RD(PC_HA_RACAP_RAPFPM_PRESS);
        txtRACAP_RAPFPM_PRESS->Text = FormatFloat("0.###",txtRACAP_RAPFPM_PRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_RACAP_RAPMCP_PRESS) == 0){
               CLP.WR(PC_HA_RACAP_RAPMCP_PRESS      , 50);
        }
        txtRACAP_RAPMCP_PRESS->Text = CLP.RD(PC_HA_RACAP_RAPMCP_PRESS);
        txtRACAP_RAPMCP_PRESS->Text = FormatFloat("0.###",txtRACAP_RAPMCP_PRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_RASIS_RASAPV_PRESS) == 0){
               CLP.WR(PC_HA_RASIS_RASAPV_PRESS      , 6);
        }
        txtRASIS_RASAPV_PRESS->Text = CLP.RD(PC_HA_RASIS_RASAPV_PRESS);
        txtRASIS_RASAPV_PRESS->Text = FormatFloat("0.###",txtRASIS_RASAPV_PRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_RASIS_RASAPM_PRESS) == 0){
               CLP.WR(PC_HA_RASIS_RASAPM_PRESS      , 6);
        }
        txtRASIS_RASAPM_PRESS->Text = CLP.RD(PC_HA_RASIS_RASAPM_PRESS);
        txtRASIS_RASAPM_PRESS->Text = FormatFloat("0.###",txtRASIS_RASAPM_PRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_RASIS_RASAPR_PRESS) == 0){
               CLP.WR(PC_HA_RASIS_RASAPR_PRESS      , 6);
        }
        txtRASIS_RASAPR_PRESS->Text = CLP.RD(PC_HA_RASIS_RASAPR_PRESS);
        txtRASIS_RASAPR_PRESS->Text = FormatFloat("0.###",txtRASIS_RASAPR_PRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_ARALIMPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_ARALIMPRESS      , 3);
        }
        txtGERENE_MCA1_ARALIMPRESS->Text = CLP.RD(PC_HA_GERENE_MCA1_ARALIMPRESS);
        txtGERENE_MCA1_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ARALIMPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_ODPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_ODPRESS      , 3.5);
        }
        txtGERENE_MCA1_ODPRESS->Text = CLP.RD(PC_HA_GERENE_MCA1_ODPRESS);
        txtGERENE_MCA1_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ODPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_ASPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_ASPRESS      , 5.6);
        }
        txtGERENE_MCA1_ASPRESS->Text = CLP.RD(PC_HA_GERENE_MCA1_ASPRESS);
        txtGERENE_MCA1_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ASPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_ADPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_ADPRESS      , 4.2);
        }
        txtGERENE_MCA1_ADPRESS->Text = CLP.RD(PC_HA_GERENE_MCA1_ADPRESS);
        txtGERENE_MCA1_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ADPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_OLPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_OLPRESS      , 5);
        }
        txtGERENE_MCA1_OLPRESS->Text = CLP.RD(PC_HA_GERENE_MCA1_OLPRESS);
        txtGERENE_MCA1_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_OLPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_OLTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_OLTEMP      , 80);
        }
        txtGERENE_MCA1_OLTEMP->Text = CLP.RD(PC_HA_GERENE_MCA1_OLTEMP);
        txtGERENE_MCA1_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA1_OLTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA1_ADTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA1_ADTEMP      , 60);
        }
        txtGERENE_MCA1_ADTEMP->Text = CLP.RD(PC_HA_GERENE_MCA1_ADTEMP);
        txtGERENE_MCA1_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA1_ADTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_ARALIMPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_ARALIMPRESS      , 3);
        }
        txtGERENE_MCA2_ARALIMPRESS->Text = CLP.RD(PC_HA_GERENE_MCA2_ARALIMPRESS);
        txtGERENE_MCA2_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ARALIMPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_ODPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_ODPRESS      , 3.5);
        }
        txtGERENE_MCA2_ODPRESS->Text = CLP.RD(PC_HA_GERENE_MCA2_ODPRESS);
        txtGERENE_MCA2_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ODPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_ASPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_ASPRESS      , 5.6);
        }
        txtGERENE_MCA2_ASPRESS->Text = CLP.RD(PC_HA_GERENE_MCA2_ASPRESS);
        txtGERENE_MCA2_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ASPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_ADPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_ADPRESS      , 4.2);
        }
        txtGERENE_MCA2_ADPRESS->Text = CLP.RD(PC_HA_GERENE_MCA2_ADPRESS);
        txtGERENE_MCA2_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ADPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_OLPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_OLPRESS      , 5);
        }
        txtGERENE_MCA2_OLPRESS->Text = CLP.RD(PC_HA_GERENE_MCA2_OLPRESS);
        txtGERENE_MCA2_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_OLPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_OLTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_OLTEMP      , 80);
        }
        txtGERENE_MCA2_OLTEMP->Text = CLP.RD(PC_HA_GERENE_MCA2_OLTEMP);
        txtGERENE_MCA2_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA2_OLTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA2_ADTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA2_ADTEMP      , 60);
        }
        txtGERENE_MCA2_ADTEMP->Text = CLP.RD(PC_HA_GERENE_MCA2_ADTEMP);
        txtGERENE_MCA2_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA2_ADTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_ARALIMPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_ARALIMPRESS      , 1.6);
        }
        txtGERENE_MCA3_ARALIMPRESS->Text = CLP.RD(PC_HA_GERENE_MCA3_ARALIMPRESS);
        txtGERENE_MCA3_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ARALIMPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_ODPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_ODPRESS      , 2.0);
        }
        txtGERENE_MCA3_ODPRESS->Text = CLP.RD(PC_HA_GERENE_MCA3_ODPRESS);
        txtGERENE_MCA3_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ODPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_ASPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_ASPRESS      , 2.2);
        }
        txtGERENE_MCA3_ASPRESS->Text = CLP.RD(PC_HA_GERENE_MCA3_ASPRESS);
        txtGERENE_MCA3_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ASPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_ADPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_ADPRESS      , 3.2);
        }
        txtGERENE_MCA3_ADPRESS->Text = CLP.RD(PC_HA_GERENE_MCA3_ADPRESS);
        txtGERENE_MCA3_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ADPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_OLPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_OLPRESS      , 5);
        }
        txtGERENE_MCA3_OLPRESS->Text = CLP.RD(PC_HA_GERENE_MCA3_OLPRESS);
        txtGERENE_MCA3_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_OLPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_OLTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_OLTEMP      , 80);
        }
        txtGERENE_MCA3_OLTEMP->Text = CLP.RD(PC_HA_GERENE_MCA3_OLTEMP);
        txtGERENE_MCA3_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA3_OLTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA3_ADTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA3_ADTEMP      , 60);
        }
        txtGERENE_MCA3_ADTEMP->Text = CLP.RD(PC_HA_GERENE_MCA3_ADTEMP);
        txtGERENE_MCA3_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA3_ADTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_ARALIMPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_ARALIMPRESS      , 1.6);
        }
        txtGERENE_MCA4_ARALIMPRESS->Text = CLP.RD(PC_HA_GERENE_MCA4_ARALIMPRESS);
        txtGERENE_MCA4_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ARALIMPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_ODPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_ODPRESS      , 2.0);
        }
        txtGERENE_MCA4_ODPRESS->Text = CLP.RD(PC_HA_GERENE_MCA4_ODPRESS);
        txtGERENE_MCA4_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ODPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_ASPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_ASPRESS      , 2.2);
        }
        txtGERENE_MCA4_ASPRESS->Text = CLP.RD(PC_HA_GERENE_MCA4_ASPRESS);
        txtGERENE_MCA4_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ASPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_ADPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_ADPRESS      , 3.2);
        }
        txtGERENE_MCA4_ADPRESS->Text = CLP.RD(PC_HA_GERENE_MCA4_ADPRESS);
        txtGERENE_MCA4_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ADPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_OLPRESS) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_OLPRESS      , 5);
        }
        txtGERENE_MCA4_OLPRESS->Text = CLP.RD(PC_HA_GERENE_MCA4_OLPRESS);
        txtGERENE_MCA4_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_OLPRESS->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_OLTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_OLTEMP      , 80);
        }
        txtGERENE_MCA4_OLTEMP->Text = CLP.RD(PC_HA_GERENE_MCA4_OLTEMP);
        txtGERENE_MCA4_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA4_OLTEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_GERENE_MCA4_ADTEMP) == 0){
               CLP.WR(PC_HA_GERENE_MCA4_ADTEMP      , 60);
        }
        txtGERENE_MCA4_ADTEMP->Text = CLP.RD(PC_HA_GERENE_MCA4_ADTEMP);
        txtGERENE_MCA4_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA4_ADTEMP->Text.ToDouble());



        if (CLP.RD(PC_HA_VEDPM_RVENPMV_TEMP) == 0){
               CLP.WR(PC_HA_VEDPM_RVENPMV_TEMP      , 35);
        }
        txtVEDPM_RVENPMV_TEMP->Text = CLP.RD(PC_HA_VEDPM_RVENPMV_TEMP);
        txtVEDPM_RVENPMV_TEMP->Text = FormatFloat("0.###",txtVEDPM_RVENPMV_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEDPM_RVENPMR_TEMP) == 0){
               CLP.WR(PC_HA_VEDPM_RVENPMR_TEMP      , 36);
        }
        txtVEDPM_RVENPMR_TEMP->Text = CLP.RD(PC_HA_VEDPM_RVENPMR_TEMP);
        txtVEDPM_RVENPMR_TEMP->Text = FormatFloat("0.###",txtVEDPM_RVENPMR_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEDPM_RVENPMA_TEMP) == 0){
               CLP.WR(PC_HA_VEDPM_RVENPMA_TEMP      , 33);
        }
        txtVEDPM_RVENPMA_TEMP->Text = CLP.RD(PC_HA_VEDPM_RVENPMA_TEMP);
        txtVEDPM_RVENPMA_TEMP->Text = FormatFloat("0.###",txtVEDPM_RVENPMA_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEFPM_ANTMAGE_TEMP) == 0){
               CLP.WR(PC_HA_VEFPM_ANTMAGE_TEMP      , 33);
        }
        txtVEFPM_ANTMAGE_TEMP->Text = CLP.RD(PC_HA_VEFPM_ANTMAGE_TEMP);
        txtVEFPM_ANTMAGE_TEMP->Text = FormatFloat("0.###",txtVEFPM_ANTMAGE_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEFPM_ANTCME_TEMP) == 0){
               CLP.WR(PC_HA_VEFPM_ANTCME_TEMP      , 33);
        }
        txtVEFPM_ANTCME_TEMP->Text = CLP.RD(PC_HA_VEFPM_ANTCME_TEMP);
        txtVEFPM_ANTCME_TEMP->Text = FormatFloat("0.###",txtVEFPM_ANTCME_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEFPM_CPTCME_TEMP) == 0){
               CLP.WR(PC_HA_VEFPM_CPTCME_TEMP      , 33);
        }
        txtVEFPM_CPTCME_TEMP->Text = CLP.RD(PC_HA_VEFPM_CPTCME_TEMP);
        txtVEFPM_CPTCME_TEMP->Text = FormatFloat("0.###",txtVEFPM_CPTCME_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEFPM_ESTCHAFF_TEMP) == 0){
               CLP.WR(PC_HA_VEFPM_ESTCHAFF_TEMP      , 33);
        }
        txtVEFPM_ESTCHAFF_TEMP->Text = CLP.RD(PC_HA_VEFPM_ESTCHAFF_TEMP);
        txtVEFPM_ESTCHAFF_TEMP->Text = FormatFloat("0.###",txtVEFPM_ESTCHAFF_TEMP->Text.ToDouble());

        if (CLP.RD(PC_HA_VEFPM_CONTALCA_TEMP) == 0){
               CLP.WR(PC_HA_VEFPM_CONTALCA_TEMP      , 33);
        }
        txtVEFPM_CONTALCA_TEMP->Text = CLP.RD(PC_HA_VEFPM_CONTALCA_TEMP);
        txtVEFPM_CONTALCA_TEMP->Text = FormatFloat("0.###",txtVEFPM_CONTALCA_TEMP->Text.ToDouble());
//-------------------------------------------------------------
//---------------------  INICIA DIGITAIS  ---------------------
        /*CLP.WR( VARIAVEL_DIGITAL, 0 OU 1 );*/
        if ( (CLP.RD(PC_HL_AODPG_VOD012_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD012_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD012_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD013_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD013_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD013_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD014_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD014_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD014_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD015_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD015_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD015_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD016_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD016_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD016_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD017_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD017_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD017_ABERTO,  0);
        }
        
        if ( (CLP.RD(PC_HL_AODPG_VOD059_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD059_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD059_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD060_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD060_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD060_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD061_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD061_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD061_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD062_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD062_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD062_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD063_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD063_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD063_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD064_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD064_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD064_ABERTO,  0);
        }

        if ( (CLP.RD(PC_HL_AODPG_VOD005_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD005_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD005_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD010_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD010_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD010_ABERTO,  0);
        }

        if ( (CLP.RD(PC_HL_AODPG_VOD030_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD030_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD030_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD031_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD031_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD031_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD035_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD035_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD035_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD043_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD043_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD043_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_AODPG_VOD066_ABERTO) == 0) && (CLP.RD(PC_HL_AODPG_VOD066_FECHADO) == 0) ){
                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 1);
                CLP.WR(PC_HL_AODPG_VOD066_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD098_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD098_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD098_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD101_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD101_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD101_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD103_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD103_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD103_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD106_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD106_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD106_ABERTO,  0);
        }

        CLP.WR( PC_HL_AODPG_BETOD1_EMREM, 1 );
        CLP.WR( PC_HL_AODPG_BETOD2_EMREM, 1 );

        CLP.WR( PC_HL_SODPG_BEROD1_EMREM, 1 );
        CLP.WR( PC_HL_SODPG_BEROD2_EMREM, 1 );

        CLP.WR( PC_HL_SODPG_AQCOD1_EMREM, 1 );
        CLP.WR( PC_HL_SODPG_AQCOD1_ENERGIZADO, 1 );
        CLP.WR( PC_HL_SODPG_AQCOD2_EMREM, 1 );
        CLP.WR( PC_HL_SODPG_AQCOD2_ENERGIZADO, 1 );

        if ( (CLP.RD(PC_HL_SODPG_VOD120_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD120_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD120_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD122_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD122_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD122_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD129_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD129_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD129_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD133_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD133_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD133_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD152_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD152_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD152_ABERTO,  0);
        }
        if ( (CLP.RD(PC_HL_SODPG_VOD155_ABERTO) == 0) && (CLP.RD(PC_HL_SODPG_VOD155_FECHADO) == 0) ){
                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 1);
                CLP.WR(PC_HL_SODPG_VOD155_ABERTO,  0);
        }

        CLP.WR( PC_HL_RACAP_CAAP01_EMREM, 1 );
        CLP.WR( PC_HL_RACAP_CAAP02_EMREM, 1 );

        CLP.WR( PC_HL_AOLTG_TAOL25_NIVELALTO, 1);
        CLP.WR( PC_HL_AOLTG_TBORRA_NIVELALTO, 1);
        CLP.WR( PC_HL_AOLTG_TQDREN_NIVELALTO, 1);

        if ( (CLP.RD(PC_HL_RADUG_VAP001_ABERTO) == 0) && (CLP.RD(PC_HL_RADUG_VAP001_FECHADO) == 0) ){
                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 1);
                CLP.WR(PC_HL_RADUG_VAP001_ABERTO,  0);
        }

        if ( (CLP.RD(PC_HL_RADUG_VAP002_ABERTO) == 0) && (CLP.RD(PC_HL_RADUG_VAP002_FECHADO) == 0) ){
                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 1);
                CLP.WR(PC_HL_RADUG_VAP002_ABERTO,  0);
        }

        CLP.WR( PC_HL_RADUG_TAAD26_NIVELALTO,  1);
        CLP.WR( PC_HL_RADUG_TAAD26_NIVELBAIXO, 0);

        CLP.WR( PC_HL_RADUG_TAAD27_NIVELALTO,  1);
        CLP.WR( PC_HL_RADUG_TAAD27_NIVELBAIXO, 0);

        CLP.WR( PC_HL_RASIS_BECAS1_PRDEMERGLOCAL, 0);
        CLP.WR( PC_HL_RASIS_BECAS1_EMREM        , 1);

        CLP.WR( PC_HL_RASIS_BECAS2_PRDEMERGLOCAL, 0);
        CLP.WR( PC_HL_RASIS_BECAS2_EMREM        , 1);

        CLP.WR( PC_HL_RASIS_BECAS3_PRDEMERGLOCAL, 0);
        CLP.WR( PC_HL_RASIS_BECAS3_EMREM        , 1);

        CLP.WR( PC_HL_RARCF_CFLAT_TEMPBAIXA     , 1);
        CLP.WR( PC_HL_RARCF_CFVEG_TEMPBAIXA     , 1);

        CLP.WR( PC_HL_MAQLEM_MOTBB_ALIMDISPON   , 1);
        CLP.WR( PC_HL_MAQLEM_MOTBB_EMREM        , 1);
        CLP.WR( PC_HL_MAQLEM_MOTBB_LIGADO       , 1);
        CLP.WR( PC_HL_MAQLEM_MOTBB_ALIMLOGICOK  , 1);

        CLP.WR( PC_HL_MAQLEM_MOTBE_ALIMDISPON   , 1);
        CLP.WR( PC_HL_MAQLEM_MOTBE_EMREM        , 1);
        CLP.WR( PC_HL_MAQLEM_MOTBE_DESUMLIG     , 1);
        CLP.WR( PC_HL_MAQLEM_MOTBE_ALIMLOGICOK  , 1);

        CLP.WR( PC_HL_MAQLEM_UHIDBB_NVBX        , 1);
        CLP.WR( PC_HL_MAQLEM_UHIDBB_TEMPAL      , 1);
        CLP.WR( PC_HL_MAQLEM_UHIDBB_PRESSBX     , 1);

        CLP.WR( PC_HL_MAQLEM_UHIDBE_NVBX        , 1);
        CLP.WR( PC_HL_MAQLEM_UHIDBE_TEMPAL      , 1);
        CLP.WR( PC_HL_MAQLEM_UHIDBE_PRESSBX     , 1);

        CLP.WR( PC_HL_MAQLEM_CML_CMDDISPCCM     , 1);
        CLP.WR( PC_HL_MAQLEM_CML_SELCUHDISPON   , 1);
//-------------------------------------------------------------
//-------------------------------------------------------------
//ACIONA TODOS OS ENDEREÇOS DE SIMULAÇÃO
        for (int i = 3010; i < 3036; i++){ //ARM IO 1
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0xFFFF);
        }
        for (int i = 3066; i < 3070; i++){ //ARM IO 2
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0xFFFF);
        }
//-------------------------------------------------------------

        frmPrincipal->Caption = NomeForm + " - Pronto (CLP" + IP + ")";

        tmrLeitura->Enabled = true;

        lblBufferR->Visible = true;
        lblBufferW->Visible = true;
        lblBufferEx->Visible = true;
        lblLista->Visible = true;

        if (tmrConexaoWatch->Enabled == false){
                tmrConexaoWatch->Enabled = true;
        }

        tmrLista->Enabled = true;

        btnReset->Enabled = true;
        btnReset->Visible = false;

        mnuODiesel->Enabled = true;
        mnuRACAP->Enabled = true;
        mnuAOLTG->Enabled = true;
        mnuAgua->Enabled = true;
        mnuCPTAS->Enabled = true;
        mnuMAQLEM->Enabled = true;
        mnuGERENE->Enabled = true;
        mnuPROTC->Enabled = true;
        mnuRARCF->Enabled = true;
        mnuVentilacao->Enabled = true;

//FIM DA INICIALIZAÇÃO
        tmrStarting->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrReconectaTimer(TObject *Sender)
{
//RECONEXÃO
        CLP.Open(IP);
        tmrReconecta->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrListaTimer(TObject *Sender)
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
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrConexaoWatchTimer(TObject *Sender)
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

        DateTimeToString( TimeStamp, AnsiString( "DD/MM/YY hh:nn:ss" ), Now() );

        lblProgramaAtual->Caption = TimeStamp;

        lblQuedas->Caption = "Fall: " + String (numeroquedas);

        VALOR_ANTIGO = CLP.RD( CONTADOR_CONEXAO );
        lblWatchdog->Caption = VALOR_ANTIGO;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrLeituraTimer(TObject *Sender)
{
//==============================================================================
//TIMER DE ESCRITA, LEITURA E TRATAMENTO DOS SINAIS - INICIO
//==============================================================================
//==============================================================================
//AOLTG_AQCOL1
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_AQCOL1_LIGADO) == 1 ){
		shpAOLTG_AQCOL1_LIGADO->Brush->Color = clLime;
		btnAOLTG_AQCOL1_LIGADO->Caption = "Ligado";
	}
	else{
		shpAOLTG_AQCOL1_LIGADO->Brush->Color = clWhite;
		btnAOLTG_AQCOL1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_AQCOL1_FALHA) == 1 ){
		shpAOLTG_AQCOL1_FALHA->Brush->Color = clRed;
		btnAOLTG_AQCOL1_FALHA->Caption = "Falha";
	}
	else{
		shpAOLTG_AQCOL1_FALHA->Brush->Color = clWhite;
		btnAOLTG_AQCOL1_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_AQCOL2
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_AQCOL2_LIGADO) == 1 ){
		shpAOLTG_AQCOL2_LIGADO->Brush->Color = clLime;
		btnAOLTG_AQCOL2_LIGADO->Caption = "Ligado";
	}
	else{
		shpAOLTG_AQCOL2_LIGADO->Brush->Color = clWhite;
		btnAOLTG_AQCOL2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_AQCOL2_FALHA) == 1 ){
		shpAOLTG_AQCOL2_FALHA->Brush->Color = clRed;
		btnAOLTG_AQCOL2_FALHA->Caption = "Falha";
	}
	else{
		shpAOLTG_AQCOL2_FALHA->Brush->Color = clWhite;
		btnAOLTG_AQCOL2_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_BETOL1
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_BETOL1_LIGADO) == 1 ){
		shpAOLTG_BETOL1_LIGADO->Brush->Color = clLime;
		btnAOLTG_BETOL1_LIGADO->Caption = "Ligado";
	}
	else{
		shpAOLTG_BETOL1_LIGADO->Brush->Color = clWhite;
		btnAOLTG_BETOL1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_AOLTG_BETOL1_PARAREMERG) == 1 ){
                shpAOLTG_BETOL1_PARAREMERG->Brush->Color = clRed;
                btnAOLTG_BETOL1_LIGADO->Enabled = false;
		if (btnAOLTG_BETOL1_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_AOLTG_BETOL1_LIGADO, 0);
		}
	}
	else{
                btnAOLTG_BETOL1_LIGADO->Enabled = true;
		shpAOLTG_BETOL1_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_BETOL2
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_BETOL2_LIGADO) == 1 ){
		shpAOLTG_BETOL2_LIGADO->Brush->Color = clLime;
		btnAOLTG_BETOL2_LIGADO->Caption = "Ligado";
	}
	else{
		shpAOLTG_BETOL2_LIGADO->Brush->Color = clWhite;
		btnAOLTG_BETOL2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_AOLTG_BETOL2_PARAREMERG) == 1 ){
                shpAOLTG_BETOL2_PARAREMERG->Brush->Color = clRed;
                btnAOLTG_BETOL2_LIGADO->Enabled = false;
		if (btnAOLTG_BETOL2_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_AOLTG_BETOL2_LIGADO, 0);
		}
	}
	else{
                btnAOLTG_BETOL2_LIGADO->Enabled = true;
		shpAOLTG_BETOL2_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_PUROL1
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_PUROL1_LIGADO) == 1 ){
		shpAOLTG_PUROL1_LIGADO->Brush->Color = clLime;
		btnAOLTG_PUROL1_LIGADO->Caption = "Ligado";
	}
	else{
		shpAOLTG_PUROL1_LIGADO->Brush->Color = clWhite;
		btnAOLTG_PUROL1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_PUROL1_PERDASELO) == 1 ){
		shpAOLTG_PUROL1_PERDASELO->Brush->Color = clYellow;
		btnAOLTG_PUROL1_PERDASELO->Caption = "Perda de Selo";
	}
	else{
		shpAOLTG_PUROL1_PERDASELO->Brush->Color = clWhite;
		btnAOLTG_PUROL1_PERDASELO->Caption = "Selo Normal";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_AOLTG_PUROL1_PARAREMERG) == 1 ){
                shpAOLTG_PUROL1_PARAREMERG->Brush->Color = clRed;
                btnAOLTG_PUROL1_LIGADO->Enabled = false;
		if (btnAOLTG_PUROL1_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_AOLTG_PUROL1_LIGADO, 0);
		}
	}
	else{
                btnAOLTG_PUROL1_LIGADO->Enabled = true;
		shpAOLTG_PUROL1_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_PUROL2
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_PUROL2_LIGADO) == 1 ){
		shpAOLTG_PUROL2_LIGADO->Brush->Color = clLime;
		btnAOLTG_PUROL2_LIGADO->Caption = "Ligado";
	}
	else{
		shpAOLTG_PUROL2_LIGADO->Brush->Color = clWhite;
		btnAOLTG_PUROL2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_PUROL2_PERDASELO) == 1 ){
		shpAOLTG_PUROL2_PERDASELO->Brush->Color = clYellow;
		btnAOLTG_PUROL2_PERDASELO->Caption = "Perda de Selo";
	}
	else{
		shpAOLTG_PUROL2_PERDASELO->Brush->Color = clWhite;
		btnAOLTG_PUROL2_PERDASELO->Caption = "Selo Normal";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_AOLTG_PUROL2_PARAREMERG) == 1 ){
                shpAOLTG_PUROL2_PARAREMERG->Brush->Color = clRed;
                btnAOLTG_PUROL2_LIGADO->Enabled = false;
		if (btnAOLTG_PUROL2_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_AOLTG_PUROL2_LIGADO, 0);
		}
	}
	else{
                btnAOLTG_PUROL2_LIGADO->Enabled = true;
		shpAOLTG_PUROL2_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_TAOL14
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_TAOL14_NIVELBAIXO) == 1 ){
		shpAOLTG_TAOL14_NIVELBAIXO->Brush->Color = clRed;
		btnAOLTG_TAOL14_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpAOLTG_TAOL14_NIVELBAIXO->Brush->Color = clWhite;
		btnAOLTG_TAOL14_NIVELBAIXO->Caption = "Não Nível Baixo";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_TAOL25
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_TAOL25_NIVELALTO) == 0 ){
		shpAOLTG_TAOL25_NIVELALTO->Brush->Color = clRed;
		btnAOLTG_TAOL25_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpAOLTG_TAOL25_NIVELALTO->Brush->Color = clWhite;
		btnAOLTG_TAOL25_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_TBORRA
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_TBORRA_NIVELALTO) == 0 ){
		shpAOLTG_TBORRA_NIVELALTO->Brush->Color = clRed;
		btnAOLTG_TBORRA_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpAOLTG_TBORRA_NIVELALTO->Brush->Color = clWhite;
		btnAOLTG_TBORRA_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//AOLTG_TQDREN
        //***********************************************************
        if ( CLP.RD(PC_HL_AOLTG_TQDREN_NIVELALTO) == 0 ){
		shpAOLTG_TQDREN_NIVELALTO->Brush->Color = clRed;
		btnAOLTG_TQDREN_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpAOLTG_TQDREN_NIVELALTO->Brush->Color = clWhite;
		btnAOLTG_TQDREN_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_BEM1
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BEM1_LIGADO) == 1 ){
		shpCPTAS_BEM1_LIGADO->Brush->Color = clLime;
		btnCPTAS_BEM1_LIGADO->Caption = "Ligado";
	}
	else{
		shpCPTAS_BEM1_LIGADO->Brush->Color = clWhite;
		btnCPTAS_BEM1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BEM1_FALHA) == 1 ){
		shpCPTAS_BEM1_FALHA->Brush->Color = clRed;
		btnCPTAS_BEM1_FALHA->Caption = "Falha";
	}
	else{
		shpCPTAS_BEM1_FALHA->Brush->Color = clWhite;
		btnCPTAS_BEM1_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_BEM2
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BEM2_LIGADO) == 1 ){
		shpCPTAS_BEM2_LIGADO->Brush->Color = clLime;
		btnCPTAS_BEM2_LIGADO->Caption = "Ligado";
	}
	else{
		shpCPTAS_BEM2_LIGADO->Brush->Color = clWhite;
		btnCPTAS_BEM2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BEM2_FALHA) == 1 ){
		shpCPTAS_BEM2_FALHA->Brush->Color = clRed;
		btnCPTAS_BEM2_FALHA->Caption = "Falha";
	}
	else{
		shpCPTAS_BEM2_FALHA->Brush->Color = clWhite;
		btnCPTAS_BEM2_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_BET1
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BET1_LIGADO) == 1 ){
		shpCPTAS_BET1_LIGADO->Brush->Color = clLime;
		btnCPTAS_BET1_LIGADO->Caption = "Ligado";
	}
	else{
		shpCPTAS_BET1_LIGADO->Brush->Color = clWhite;
		btnCPTAS_BET1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BET1_FALHA) == 1 ){
		shpCPTAS_BET1_FALHA->Brush->Color = clRed;
		btnCPTAS_BET1_FALHA->Caption = "Falha";
	}
	else{
		shpCPTAS_BET1_FALHA->Brush->Color = clWhite;
		btnCPTAS_BET1_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_BET2
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BET2_LIGADO) == 1 ){
		shpCPTAS_BET2_LIGADO->Brush->Color = clLime;
		btnCPTAS_BET2_LIGADO->Caption = "Ligado";
	}
	else{
		shpCPTAS_BET2_LIGADO->Brush->Color = clWhite;
		btnCPTAS_BET2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_BET2_FALHA) == 1 ){
		shpCPTAS_BET2_FALHA->Brush->Color = clRed;
		btnCPTAS_BET2_FALHA->Caption = "Falha";
	}
	else{
		shpCPTAS_BET2_FALHA->Brush->Color = clWhite;
		btnCPTAS_BET2_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_PLUTAS
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_PLUTAS_LIGADO) == 1 ){
		shpCPTAS_PLUTAS_LIGADO->Brush->Color = clLime;
		btnCPTAS_PLUTAS_LIGADO->Caption = "Ligado";
	}
	else{
		shpCPTAS_PLUTAS_LIGADO->Brush->Color = clWhite;
		btnCPTAS_PLUTAS_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_PLUTAS_FALHA) == 1 ){
		shpCPTAS_PLUTAS_FALHA->Brush->Color = clRed;
		btnCPTAS_PLUTAS_FALHA->Caption = "Falha";
	}
	else{
		shpCPTAS_PLUTAS_FALHA->Brush->Color = clWhite;
		btnCPTAS_PLUTAS_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_SEPAO
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_SEPAO_LIGADO) == 1 ){
		shpCPTAS_SEPAO_LIGADO->Brush->Color = clLime;
		btnCPTAS_SEPAO_LIGADO->Caption = "Ligado";
	}
	else{
		shpCPTAS_SEPAO_LIGADO->Brush->Color = clWhite;
		btnCPTAS_SEPAO_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_SEPAO_TEORALTO) == 1 ){
		shpCPTAS_SEPAO_TEORALTO->Brush->Color = clYellow;
		btnCPTAS_SEPAO_TEORALTO->Caption = "Teor Alto";
	}
	else{
		shpCPTAS_SEPAO_TEORALTO->Brush->Color = clWhite;
		btnCPTAS_SEPAO_TEORALTO->Caption = "Teor Normal";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_TQSEPR
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_TQSEPR_NIVELALTO) == 1 ){
		shpCPTAS_TQSEPR_NIVELALTO->Brush->Color = clRed;
		btnCPTAS_TQSEPR_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpCPTAS_TQSEPR_NIVELALTO->Brush->Color = clWhite;
		btnCPTAS_TQSEPR_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//CPTAS_TQSEPV
        //***********************************************************
        if ( CLP.RD(PC_HL_CPTAS_TQSEPV_NIVELALTO) == 1 ){
		shpCPTAS_TQSEPV_NIVELALTO->Brush->Color = clRed;
		btnCPTAS_TQSEPV_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpCPTAS_TQSEPV_NIVELALTO->Brush->Color = clWhite;
		btnCPTAS_TQSEPV_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//DASOR_GDEST1
        //***********************************************************
        if ( CLP.RD(PC_HL_DASOR_GDEST1_LIGADO) == 1 ){
		shpDASOR_GDEST1_LIGADO->Brush->Color = clLime;
		btnDASOR_GDEST1_LIGADO->Caption = "Ligado";
	}
	else{
		shpDASOR_GDEST1_LIGADO->Brush->Color = clWhite;
		btnDASOR_GDEST1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_DASOR_GDEST1_FALHA) == 1 ){
		shpDASOR_GDEST1_FALHA->Brush->Color = clRed;
		btnDASOR_GDEST1_FALHA->Caption = "Falha";
	}
	else{
		shpDASOR_GDEST1_FALHA->Brush->Color = clWhite;
		btnDASOR_GDEST1_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_DASOR_GDEST1_SALINALTA) == 1 ){
		shpDASOR_GDEST1_SALINALTA->Brush->Color = clYellow;
		btnDASOR_GDEST1_SALINALTA->Caption = "Salinidade Alta";
	}
	else{
		shpDASOR_GDEST1_SALINALTA->Brush->Color = clWhite;
		btnDASOR_GDEST1_SALINALTA->Caption = "Salinidade Normal";
	};
        //***********************************************************
	if ( CLP.RD(CP_HL_DASOR_GDEST1_PARAREMERG) == 1 ){
                shpDASOR_GDEST1_PARAREMERG->Brush->Color = clRed;
                btnDASOR_GDEST1_LIGADO->Enabled = false;
		if (btnDASOR_GDEST1_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_DASOR_GDEST1_LIGADO, 0);
		}
	}
	else{
                btnDASOR_GDEST1_LIGADO->Enabled = true;
		shpDASOR_GDEST1_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//DASOR_GDEST2
        //***********************************************************
        if ( CLP.RD(PC_HL_DASOR_GDEST2_LIGADO) == 1 ){
		shpDASOR_GDEST2_LIGADO->Brush->Color = clLime;
		btnDASOR_GDEST2_LIGADO->Caption = "Ligado";
	}
	else{
		shpDASOR_GDEST2_LIGADO->Brush->Color = clWhite;
		btnDASOR_GDEST2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_DASOR_GDEST2_FALHA) == 1 ){
		shpDASOR_GDEST2_FALHA->Brush->Color = clRed;
		btnDASOR_GDEST2_FALHA->Caption = "Falha";
	}
	else{
		shpDASOR_GDEST2_FALHA->Brush->Color = clWhite;
		btnDASOR_GDEST2_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_DASOR_GDEST2_SALINALTA) == 1 ){
		shpDASOR_GDEST2_SALINALTA->Brush->Color = clYellow;
		btnDASOR_GDEST2_SALINALTA->Caption = "Salinidade Alta";
	}
	else{
		shpDASOR_GDEST2_SALINALTA->Brush->Color = clWhite;
		btnDASOR_GDEST2_SALINALTA->Caption = "Salinidade Normal";
	};
        //***********************************************************
	if ( CLP.RD(CP_HL_DASOR_GDEST2_PARAREMERG) == 1 ){
                shpDASOR_GDEST2_PARAREMERG->Brush->Color = clRed;
                btnDASOR_GDEST2_LIGADO->Enabled = false;
		if (btnDASOR_GDEST2_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_DASOR_GDEST2_LIGADO, 0);
		}
	}
	else{
                btnDASOR_GDEST2_LIGADO->Enabled = true;
		shpDASOR_GDEST2_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//GERENE_MCA1
        //***********************************************************
	lblGERENE_MCA1_ARALIMPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA1_ARALIMPRESS);
	lblGERENE_MCA1_ARALIMPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA1_ARALIMPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA1_ARALIMPRESS->Position = (((lblGERENE_MCA1_ARALIMPRESS->Caption*100)-(0*100))*(100-0))/((4-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA1_ODPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA1_ODPRESS);
	lblGERENE_MCA1_ODPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA1_ODPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA1_ODPRESS->Position = (((lblGERENE_MCA1_ODPRESS->Caption*100)-(0*100))*(100-0))/((7-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA1_ASPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA1_ASPRESS);
	lblGERENE_MCA1_ASPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA1_ASPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA1_ASPRESS->Position = (((lblGERENE_MCA1_ASPRESS->Caption*100)-(0*100))*(100-0))/((7-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA1_ADPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA1_ADPRESS);
	lblGERENE_MCA1_ADPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA1_ADPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA1_ADPRESS->Position = (((lblGERENE_MCA1_ADPRESS->Caption*100)-(0*100))*(100-0))/((7-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA1_OLPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA1_OLPRESS);
	lblGERENE_MCA1_OLPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA1_OLPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA1_OLPRESS->Position = (((lblGERENE_MCA1_OLPRESS->Caption*100)-(0*100))*(100-0))/((10-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA1_OLTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA1_OLTEMP);
	lblGERENE_MCA1_OLTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA1_OLTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA1_OLTEMP->Position = (((lblGERENE_MCA1_OLTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
	lblGERENE_MCA1_ADTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA1_ADTEMP);
	lblGERENE_MCA1_ADTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA1_ADTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA1_ADTEMP->Position = (((lblGERENE_MCA1_ADTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//GERENE_MCA2
        //***********************************************************
	lblGERENE_MCA2_ARALIMPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA2_ARALIMPRESS);
	lblGERENE_MCA2_ARALIMPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA2_ARALIMPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA2_ARALIMPRESS->Position = (((lblGERENE_MCA2_ARALIMPRESS->Caption*100)-(0*100))*(100-0))/((4-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA2_ODPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA2_ODPRESS);
	lblGERENE_MCA2_ODPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA2_ODPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA2_ODPRESS->Position = (((lblGERENE_MCA2_ODPRESS->Caption*100)-(0*100))*(100-0))/((7-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA2_ASPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA2_ASPRESS);
	lblGERENE_MCA2_ASPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA2_ASPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA2_ASPRESS->Position = (((lblGERENE_MCA2_ASPRESS->Caption*100)-(0*100))*(100-0))/((7-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA2_ADPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA2_ADPRESS);
	lblGERENE_MCA2_ADPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA2_ADPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA2_ADPRESS->Position = (((lblGERENE_MCA2_ADPRESS->Caption*100)-(0*100))*(100-0))/((7-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA2_OLPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA2_OLPRESS);
	lblGERENE_MCA2_OLPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA2_OLPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA2_OLPRESS->Position = (((lblGERENE_MCA2_OLPRESS->Caption*100)-(0*100))*(100-0))/((10-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA2_OLTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA2_OLTEMP);
	lblGERENE_MCA2_OLTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA2_OLTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA2_OLTEMP->Position = (((lblGERENE_MCA2_OLTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
	lblGERENE_MCA2_ADTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA2_ADTEMP);
	lblGERENE_MCA2_ADTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA2_ADTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA2_ADTEMP->Position = (((lblGERENE_MCA2_ADTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//GERENE_MCA3
        //***********************************************************
	lblGERENE_MCA3_ARALIMPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA3_ARALIMPRESS);
	lblGERENE_MCA3_ARALIMPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA3_ARALIMPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA3_ARALIMPRESS->Position = (((lblGERENE_MCA3_ARALIMPRESS->Caption*100)-(0*100))*(100-0))/((2.8-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA3_ODPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA3_ODPRESS);
	lblGERENE_MCA3_ODPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA3_ODPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA3_ODPRESS->Position = (((lblGERENE_MCA3_ODPRESS->Caption*100)-(0*100))*(100-0))/((4-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA3_ASPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA3_ASPRESS);
	lblGERENE_MCA3_ASPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA3_ASPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA3_ASPRESS->Position = (((lblGERENE_MCA3_ASPRESS->Caption*100)-(0*100))*(100-0))/((2.8-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA3_ADPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA3_ADPRESS);
	lblGERENE_MCA3_ADPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA3_ADPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA3_ADPRESS->Position = (((lblGERENE_MCA3_ADPRESS->Caption*100)-(0*100))*(100-0))/((4-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA3_OLPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA3_OLPRESS);
	lblGERENE_MCA3_OLPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA3_OLPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA3_OLPRESS->Position = (((lblGERENE_MCA3_OLPRESS->Caption*100)-(0*100))*(100-0))/((10-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA3_OLTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA3_OLTEMP);
	lblGERENE_MCA3_OLTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA3_OLTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA3_OLTEMP->Position = (((lblGERENE_MCA3_OLTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
	lblGERENE_MCA3_ADTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA3_ADTEMP);
	lblGERENE_MCA3_ADTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA3_ADTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA3_ADTEMP->Position = (((lblGERENE_MCA3_ADTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//GERENE_MCA4
        //***********************************************************
	lblGERENE_MCA4_ARALIMPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA4_ARALIMPRESS);
	lblGERENE_MCA4_ARALIMPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA4_ARALIMPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA4_ARALIMPRESS->Position = (((lblGERENE_MCA4_ARALIMPRESS->Caption*100)-(0*100))*(100-0))/((2.8-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA4_ODPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA4_ODPRESS);
	lblGERENE_MCA4_ODPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA4_ODPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA4_ODPRESS->Position = (((lblGERENE_MCA4_ODPRESS->Caption*100)-(0*100))*(100-0))/((4-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA4_ASPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA4_ASPRESS);
	lblGERENE_MCA4_ASPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA4_ASPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA4_ASPRESS->Position = (((lblGERENE_MCA4_ASPRESS->Caption*100)-(0*100))*(100-0))/((2.8-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA4_ADPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA4_ADPRESS);
	lblGERENE_MCA4_ADPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA4_ADPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA4_ADPRESS->Position = (((lblGERENE_MCA4_ADPRESS->Caption*100)-(0*100))*(100-0))/((4-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA4_OLPRESS->Caption = CLP.RD(PC_HA_GERENE_MCA4_OLPRESS);
	lblGERENE_MCA4_OLPRESS->Caption = FormatFloat("0.###",lblGERENE_MCA4_OLPRESS->Caption.ToDouble()) ;
	pgrGERENE_MCA4_OLPRESS->Position = (((lblGERENE_MCA4_OLPRESS->Caption*100)-(0*100))*(100-0))/((10-0)*100); //bar
	//***********************************************************
	lblGERENE_MCA4_OLTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA4_OLTEMP);
	lblGERENE_MCA4_OLTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA4_OLTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA4_OLTEMP->Position = (((lblGERENE_MCA4_OLTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
	lblGERENE_MCA4_ADTEMP->Caption = CLP.RD(PC_HA_GERENE_MCA4_ADTEMP);
	lblGERENE_MCA4_ADTEMP->Caption = FormatFloat("0.###",lblGERENE_MCA4_ADTEMP->Caption.ToDouble()) ;
	pgrGERENE_MCA4_ADTEMP->Position = (((lblGERENE_MCA4_ADTEMP->Caption*100)-(0*100))*(100-0))/((120-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//PROTC_PRPC
        //***********************************************************
        if ( CLP.RD(PC_HL_PROTC_PRPC_SINAL1) == 1 ){
		shpPROTC_PRPC_SINAL1->Brush->Color = clLime;
		btnPROTC_PRPC_SINAL1->Caption = "Ativo";
	}
	else{
		shpPROTC_PRPC_SINAL1->Brush->Color = clWhite;
		btnPROTC_PRPC_SINAL1->Caption = "Inativo";
	};
        //***********************************************************
        //***********************************************************
        if ( CLP.RD(PC_HL_PROTC_PRPC_SINAL2) == 1 ){
		shpPROTC_PRPC_SINAL2->Brush->Color = clLime;
		btnPROTC_PRPC_SINAL2->Caption = "Ativo";
	}
	else{
		shpPROTC_PRPC_SINAL2->Brush->Color = clWhite;
		btnPROTC_PRPC_SINAL2->Caption = "Inativo";
	};
        //***********************************************************
        //***********************************************************
        if ( CLP.RD(PC_HL_PROTC_PRPC_SINAL3) == 1 ){
		shpPROTC_PRPC_SINAL3->Brush->Color = clLime;
		btnPROTC_PRPC_SINAL3->Caption = "Ativo";
	}
	else{
		shpPROTC_PRPC_SINAL3->Brush->Color = clWhite;
		btnPROTC_PRPC_SINAL3->Caption = "Inativo";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RACAP_CAAP01
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP01_LIGADO) == 1 ){
		shpRACAP_CAAP01_LIGADO->Brush->Color = clLime;
		btnRACAP_CAAP01_LIGADO->Caption = "Ligado";
	}
	else{
		shpRACAP_CAAP01_LIGADO->Brush->Color = clWhite;
		btnRACAP_CAAP01_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP01_EMREM) == 1 ){
		shpRACAP_CAAP01_EMREM->Brush->Color = clNavy;
		btnRACAP_CAAP01_EMREM->Caption = "Em Remoto";
                btnRACAP_CAAP01_PARTIR->Enabled = false;
                btnRACAP_CAAP01_PARAR->Enabled = false;
	}
	else{
		shpRACAP_CAAP01_EMREM->Brush->Color = clWhite;
		btnRACAP_CAAP01_EMREM->Caption = "Em Local";
                if ( !( CAAP01_1S5 == false && CAAP01_2S5 == true  && CAAP01_3S5 == false && CAAP01_4S5 == true  ) && shpRACAP_CAAP01_PARAREMERGLOC->Brush->Color == clWhite ){
                        btnRACAP_CAAP01_PARTIR->Enabled = true;
                        btnRACAP_CAAP01_PARAR->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP01_EMAUT) == 1 ){
		shpRACAP_CAAP01_EMAUT->Brush->Color = clYellow;
		btnRACAP_CAAP01_EMAUT->Caption = "Em Automático";
	}
	else{
		shpRACAP_CAAP01_EMAUT->Brush->Color = clWhite;
		btnRACAP_CAAP01_EMAUT->Caption = "Em Manual";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP01_FALHA) == 1 ){
		shpRACAP_CAAP01_FALHA->Brush->Color = clRed;
		btnRACAP_CAAP01_FALHA->Caption = "Em Falha";
	}
	else{
		shpRACAP_CAAP01_FALHA->Brush->Color = clWhite;
		btnRACAP_CAAP01_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_1S4) == 1 ){
		CAAP01_1S4 = true;
                shpRACAP_CAAP01_1S4->Brush->Color = clLime;
	}
	else{
                CAAP01_1S4 = false;
                shpRACAP_CAAP01_1S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_2S4) == 1 ){
		CAAP01_2S4 = true;
                shpRACAP_CAAP01_2S4->Brush->Color = clLime;
	}
	else{
                CAAP01_2S4 = false;
                shpRACAP_CAAP01_2S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_3S4) == 1 ){
		CAAP01_3S4 = true;
                shpRACAP_CAAP01_3S4->Brush->Color = clLime;
	}
	else{
                CAAP01_3S4 = false;
                shpRACAP_CAAP01_3S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_4S4) == 1 ){
		CAAP01_4S4 = true;
                shpRACAP_CAAP01_4S4->Brush->Color = clLime;
	}
	else{
                CAAP01_4S4 = false;
                shpRACAP_CAAP01_4S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_1S5) == 1 ){
		CAAP01_1S5 = true;
                shpRACAP_CAAP01_1S5->Brush->Color = clLime;
	}
	else{
                CAAP01_1S5 = false;
                shpRACAP_CAAP01_1S5->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_2S5) == 1 ){
		CAAP01_2S5 = true;
                shpRACAP_CAAP01_2S5->Brush->Color = clLime;
	}
	else{
                CAAP01_2S5 = false;
                shpRACAP_CAAP01_2S5->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_3S5) == 1 ){
		CAAP01_3S5 = true;
                shpRACAP_CAAP01_3S5->Brush->Color = clLime;
	}
	else{
                CAAP01_3S5 = false;
                shpRACAP_CAAP01_3S5->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP01_4S5) == 1 ){
		CAAP01_4S5 = true;
                shpRACAP_CAAP01_4S5->Brush->Color = clLime;
	}
	else{
                CAAP01_4S5 = false;
                shpRACAP_CAAP01_4S5->Brush->Color = clWhite;
	};
        //***********************************************************
        //Execução dos comandos do CAAP01
        //PARTIR
        if ( CAAP01_1S5 == false && CAAP01_2S5 == false && CAAP01_3S5 == true  && CAAP01_4S5 == false ){
                if (btnRACAP_CAAP01_LIGADO->Caption == "Parado"){
                        if (CLP.RD(PC_HL_RACAP_CAAP01_LIGADO) == 0){
                                CLP.WR(PC_HL_RACAP_CAAP01_LIGADO, 1);
                                if (tmrCAAP01_PARAR->Enabled == true){
                                        tmrCAAP01_PARAR->Enabled = false;
                                }
                        }
                }
        }
        //PARAR
        if ( CAAP01_1S5 == true  && CAAP01_2S5 == false && CAAP01_3S5 == false && CAAP01_4S5 == false ){
                if (btnRACAP_CAAP01_LIGADO->Caption == "Ligado" && tmrCAAP01_PARAR->Enabled == false){
                        tmrCAAP01_PARAR->Enabled = true;
                }
        }
        //PARAR EM EMERGÊNCIA
        if ( CAAP01_1S5 == false && CAAP01_2S5 == true  && CAAP01_3S5 == false && CAAP01_4S5 == true  ){
                btnRACAP_CAAP01_PARTIR->Enabled = false;
                btnRACAP_CAAP01_PARAR->Enabled = false;
                btnRACAP_CAAP01_LIGADO->Enabled = false;
                if (btnRACAP_CAAP01_LIGADO->Caption == "Ligado"){
                        tmrCAAP01_PARAR->Enabled = false;
                        if (CLP.RD(PC_HL_RACAP_CAAP01_LIGADO) == 1){
                                CLP.WR(PC_HL_RACAP_CAAP01_LIGADO, 0);
                        }
                }
        }else{
                btnRACAP_CAAP01_LIGADO->Enabled = true;
        }
        //MANUAL
        if ( CAAP01_1S4 == false && CAAP01_2S4 == true  && CAAP01_3S4 == false && CAAP01_4S4 == true  ){
                if (btnRACAP_CAAP01_EMAUT->Caption == "Em Automático"){
                        if (CLP.RD(PC_HL_RACAP_CAAP01_EMAUT) == 1){
                                CLP.WR(PC_HL_RACAP_CAAP01_EMAUT, 0);
                        }
                }
        }
        //AUTOMÁTICO
        if ( CAAP01_1S4 == true  && CAAP01_2S4 == false && CAAP01_3S4 == true  && CAAP01_4S4 == false ){
                if (btnRACAP_CAAP01_EMAUT->Caption == "Em Manual"){
                        if (CLP.RD(PC_HL_RACAP_CAAP01_EMAUT) == 0){
                                CLP.WR(PC_HL_RACAP_CAAP01_EMAUT, 1);
                        }
                }
        }
//==============================================================================
//==============================================================================
//RACAP_CAAP02
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP02_LIGADO) == 1 ){
		shpRACAP_CAAP02_LIGADO->Brush->Color = clLime;
		btnRACAP_CAAP02_LIGADO->Caption = "Ligado";
	}
	else{
		shpRACAP_CAAP02_LIGADO->Brush->Color = clWhite;
		btnRACAP_CAAP02_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP02_EMREM) == 1 ){
		shpRACAP_CAAP02_EMREM->Brush->Color = clNavy;
		btnRACAP_CAAP02_EMREM->Caption = "Em Remoto";
                btnRACAP_CAAP02_PARTIR->Enabled = false;
                btnRACAP_CAAP02_PARAR->Enabled = false;
	}
	else{
		shpRACAP_CAAP02_EMREM->Brush->Color = clWhite;
		btnRACAP_CAAP02_EMREM->Caption = "Em Local";
                if ( !( CAAP02_1S5 == false && CAAP02_2S5 == true  && CAAP02_3S5 == false && CAAP02_4S5 == true  ) && shpRACAP_CAAP02_PARAREMERGLOC->Brush->Color == clWhite ){
                        btnRACAP_CAAP02_PARTIR->Enabled = true;
                        btnRACAP_CAAP02_PARAR->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP02_EMAUT) == 1 ){
		shpRACAP_CAAP02_EMAUT->Brush->Color = clYellow;
		btnRACAP_CAAP02_EMAUT->Caption = "Em Automático";
	}
	else{
		shpRACAP_CAAP02_EMAUT->Brush->Color = clWhite;
		btnRACAP_CAAP02_EMAUT->Caption = "Em Manual";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RACAP_CAAP02_FALHA) == 1 ){
		shpRACAP_CAAP02_FALHA->Brush->Color = clRed;
		btnRACAP_CAAP02_FALHA->Caption = "Em Falha";
	}
	else{
		shpRACAP_CAAP02_FALHA->Brush->Color = clWhite;
		btnRACAP_CAAP02_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_1S4) == 1 ){
		CAAP02_1S4 = true;
                shpRACAP_CAAP02_1S4->Brush->Color = clLime;
	}
	else{
                CAAP02_1S4 = false;
                shpRACAP_CAAP02_1S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_2S4) == 1 ){
		CAAP02_2S4 = true;
                shpRACAP_CAAP02_2S4->Brush->Color = clLime;
	}
	else{
                CAAP02_2S4 = false;
                shpRACAP_CAAP02_2S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_3S4) == 1 ){
		CAAP02_3S4 = true;
                shpRACAP_CAAP02_3S4->Brush->Color = clLime;
	}
	else{
                CAAP02_3S4 = false;
                shpRACAP_CAAP02_3S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_4S4) == 1 ){
		CAAP02_4S4 = true;
                shpRACAP_CAAP02_4S4->Brush->Color = clLime;
	}
	else{
                CAAP02_4S4 = false;
                shpRACAP_CAAP02_4S4->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_1S5) == 1 ){
		CAAP02_1S5 = true;
                shpRACAP_CAAP02_1S5->Brush->Color = clLime;
	}
	else{
                CAAP02_1S5 = false;
                shpRACAP_CAAP02_1S5->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_2S5) == 1 ){
		CAAP02_2S5 = true;
                shpRACAP_CAAP02_2S5->Brush->Color = clLime;
	}
	else{
                CAAP02_2S5 = false;
                shpRACAP_CAAP02_2S5->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_3S5) == 1 ){
		CAAP02_3S5 = true;
                shpRACAP_CAAP02_3S5->Brush->Color = clLime;
	}
	else{
                CAAP02_3S5 = false;
                shpRACAP_CAAP02_3S5->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RACAP_CAAP02_4S5) == 1 ){
		CAAP02_4S5 = true;
                shpRACAP_CAAP02_4S5->Brush->Color = clLime;
	}
	else{
                CAAP02_4S5 = false;
                shpRACAP_CAAP02_4S5->Brush->Color = clWhite;
	};
        //***********************************************************
        //Execução dos comandos do CAAP02
        //PARTIR
        if ( CAAP02_1S5 == false && CAAP02_2S5 == false && CAAP02_3S5 == true  && CAAP02_4S5 == false ){
                if (btnRACAP_CAAP02_LIGADO->Caption == "Parado"){
                        if (CLP.RD(PC_HL_RACAP_CAAP02_LIGADO) == 0){
                                CLP.WR(PC_HL_RACAP_CAAP02_LIGADO, 1);
                                if (tmrCAAP02_PARAR->Enabled == true){
                                        tmrCAAP02_PARAR->Enabled = false;
                                }
                        }
                }
        }
        //PARAR
        if ( CAAP02_1S5 == true  && CAAP02_2S5 == false && CAAP02_3S5 == false && CAAP02_4S5 == false ){
                if (btnRACAP_CAAP02_LIGADO->Caption == "Ligado" && tmrCAAP02_PARAR->Enabled == false){
                        tmrCAAP02_PARAR->Enabled = true;
                }
        }
        //PARAR EM EMERGÊNCIA
        if ( CAAP02_1S5 == false && CAAP02_2S5 == true  && CAAP02_3S5 == false && CAAP02_4S5 == true  ){
                btnRACAP_CAAP02_PARTIR->Enabled = false;
                btnRACAP_CAAP02_PARAR->Enabled = false;
                btnRACAP_CAAP02_LIGADO->Enabled = false;
                if (btnRACAP_CAAP02_LIGADO->Caption == "Ligado"){
                        tmrCAAP02_PARAR->Enabled = false;
                        if (CLP.RD(PC_HL_RACAP_CAAP02_LIGADO) == 1){
                                CLP.WR(PC_HL_RACAP_CAAP02_LIGADO, 0);
                        }
                }
        }else{
                btnRACAP_CAAP02_LIGADO->Enabled = true;
        }
        //MANUAL
        if ( CAAP02_1S4 == false && CAAP02_2S4 == true  && CAAP02_3S4 == false && CAAP02_4S4 == true  ){
                if (btnRACAP_CAAP02_EMAUT->Caption == "Em Automático"){
                        if (CLP.RD(PC_HL_RACAP_CAAP02_EMAUT) == 1){
                                CLP.WR(PC_HL_RACAP_CAAP02_EMAUT, 0);
                        }
                }
        }
        //AUTOMÁTICO
        if ( CAAP02_1S4 == true  && CAAP02_2S4 == false && CAAP02_3S4 == true  && CAAP02_4S4 == false ){
                if (btnRACAP_CAAP02_EMAUT->Caption == "Em Manual"){
                        if (CLP.RD(PC_HL_RACAP_CAAP02_EMAUT) == 0){
                                CLP.WR(PC_HL_RACAP_CAAP02_EMAUT, 1);
                        }
                }
        }
//==============================================================================
//==============================================================================
//RACAP_RAPDPM
        //***********************************************************
	lblRACAP_RAPDPM_PRESS->Caption = CLP.RD(PC_HA_RACAP_RAPDPM_PRESS);
	lblRACAP_RAPDPM_PRESS->Caption = FormatFloat("0.###",lblRACAP_RAPDPM_PRESS->Caption.ToDouble()) ;
	pgrRACAP_RAPDPM_PRESS->Position = (((lblRACAP_RAPDPM_PRESS->Caption*100)-(0*100))*(100-0))/((413.7-0)*100); //bar
	//***********************************************************
//==============================================================================
//==============================================================================
//RACAP_RAPFPM
        //***********************************************************
	lblRACAP_RAPFPM_PRESS->Caption = CLP.RD(PC_HA_RACAP_RAPFPM_PRESS);
	lblRACAP_RAPFPM_PRESS->Caption = FormatFloat("0.###",lblRACAP_RAPFPM_PRESS->Caption.ToDouble()) ;
	pgrRACAP_RAPFPM_PRESS->Position = (((lblRACAP_RAPFPM_PRESS->Caption*100)-(0*100))*(100-0))/((413.7-0)*100); //bar
	//***********************************************************
//==============================================================================
//==============================================================================
//RACAP_RAPMCP
        //***********************************************************
	lblRACAP_RAPMCP_PRESS->Caption = CLP.RD(PC_HA_RACAP_RAPMCP_PRESS);
	lblRACAP_RAPMCP_PRESS->Caption = FormatFloat("0.###",lblRACAP_RAPMCP_PRESS->Caption.ToDouble()) ;
	pgrRACAP_RAPMCP_PRESS->Position = (((lblRACAP_RAPMCP_PRESS->Caption*100)-(0*100))*(100-0))/((70.0-0)*100); //bar
	//***********************************************************
//==============================================================================
//==============================================================================
//RACUG_EF1
        //***********************************************************
        if ( CLP.RD(PC_HL_RACUG_EF1_LIGADO) == 1 ){
		shpRACUG_EF1_LIGADO->Brush->Color = clLime;
		btnRACUG_EF1_LIGADO->Caption = "Ligada";
	}
	else{
		shpRACUG_EF1_LIGADO->Brush->Color = clWhite;
		btnRACUG_EF1_LIGADO->Caption = "Parada";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RACUG_EF2
        //***********************************************************
        if ( CLP.RD(PC_HL_RACUG_EF2_LIGADO) == 1 ){
		shpRACUG_EF2_LIGADO->Brush->Color = clLime;
		btnRACUG_EF2_LIGADO->Caption = "Ligada";
	}
	else{
		shpRACUG_EF2_LIGADO->Brush->Color = clWhite;
		btnRACUG_EF2_LIGADO->Caption = "Parada";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RACUG_EF3
        //***********************************************************
        if ( CLP.RD(PC_HL_RACUG_EF3_LIGADO) == 1 ){
		shpRACUG_EF3_LIGADO->Brush->Color = clLime;
		btnRACUG_EF3_LIGADO->Caption = "Ligada";
	}
	else{
		shpRACUG_EF3_LIGADO->Brush->Color = clWhite;
		btnRACUG_EF3_LIGADO->Caption = "Parada";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RACUG_EF4
        //***********************************************************
        if ( CLP.RD(PC_HL_RACUG_EF4_LIGADO) == 1 ){
		shpRACUG_EF4_LIGADO->Brush->Color = clLime;
		btnRACUG_EF4_LIGADO->Caption = "Ligada";
	}
	else{
		shpRACUG_EF4_LIGADO->Brush->Color = clWhite;
		btnRACUG_EF4_LIGADO->Caption = "Parada";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RACUG_UCA13
        //***********************************************************
        if ( CLP.RD(PC_HL_RACUG_UCA13_UMIDALTA) == 1 ){
		shpRACUG_UCA13_UMIDALTA->Brush->Color = clYellow;
		btnRACUG_UCA13_UMIDALTA->Caption = "Umidade Alta";
	}
	else{
		shpRACUG_UCA13_UMIDALTA->Brush->Color = clWhite;
		btnRACUG_UCA13_UMIDALTA->Caption = "Umidade Normal";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RACUG_UCA14
        //***********************************************************
        if ( CLP.RD(PC_HL_RACUG_UCA14_UMIDALTA) == 1 ){
		shpRACUG_UCA14_UMIDALTA->Brush->Color = clYellow;
		btnRACUG_UCA14_UMIDALTA->Caption = "Umidade Alta";
	}
	else{
		shpRACUG_UCA14_UMIDALTA->Brush->Color = clWhite;
		btnRACUG_UCA14_UMIDALTA->Caption = "Umidade Normal";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_BECAD1
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_BECAD1_LIGADO) == 1 ){
		shpRADUG_BECAD1_LIGADO->Brush->Color = clLime;
		btnRADUG_BECAD1_LIGADO->Caption = "Ligado";
	}
	else{
		shpRADUG_BECAD1_LIGADO->Brush->Color = clWhite;
		btnRADUG_BECAD1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_BECAD2
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_BECAD2_LIGADO) == 1 ){
		shpRADUG_BECAD2_LIGADO->Brush->Color = clLime;
		btnRADUG_BECAD2_LIGADO->Caption = "Ligado";
	}
	else{
		shpRADUG_BECAD2_LIGADO->Brush->Color = clWhite;
		btnRADUG_BECAD2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_BECAQ
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_BECAQ_LIGADO) == 1 ){
		shpRADUG_BECAQ_LIGADO->Brush->Color = clLime;
		btnRADUG_BECAQ_LIGADO->Caption = "Ligado";
	}
	else{
		shpRADUG_BECAQ_LIGADO->Brush->Color = clWhite;
		btnRADUG_BECAQ_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_TAAD26
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_TAAD26_NIVELBAIXO) == 1 ){
		shpRADUG_TAAD26_NIVELBAIXO->Brush->Color = clRed;
		btnRADUG_TAAD26_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpRADUG_TAAD26_NIVELBAIXO->Brush->Color = clWhite;
		btnRADUG_TAAD26_NIVELBAIXO->Caption = "Não Nível Baixo";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_TAAD26_NIVELALTO) == 0 ){
		shpRADUG_TAAD26_NIVELALTO->Brush->Color = clRed;
		btnRADUG_TAAD26_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpRADUG_TAAD26_NIVELALTO->Brush->Color = clWhite;
		btnRADUG_TAAD26_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_TAAD27
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_TAAD27_NIVELBAIXO) == 1 ){
		shpRADUG_TAAD27_NIVELBAIXO->Brush->Color = clRed;
		btnRADUG_TAAD27_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpRADUG_TAAD27_NIVELBAIXO->Brush->Color = clWhite;
		btnRADUG_TAAD27_NIVELBAIXO->Caption = "Não Nível Baixo";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_TAAD27_NIVELALTO) == 0 ){
		shpRADUG_TAAD27_NIVELALTO->Brush->Color = clRed;
		btnRADUG_TAAD27_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpRADUG_TAAD27_NIVELALTO->Brush->Color = clWhite;
		btnRADUG_TAAD27_NIVELALTO->Caption = "Não Nível Alto";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_VAP001
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_VAP001_FECHADO) == 1 ){
		shpRADUG_VAP001_FECHADO->Brush->Color = clLime;
		btnRADUG_VAP001_FECHADO->Caption = "Fechada";
	}
	else{
		shpRADUG_VAP001_FECHADO->Brush->Color = clWhite;
		btnRADUG_VAP001_FECHADO->Caption = "Não Fechada";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_VAP001_ABERTO) == 1 ){
		shpRADUG_VAP001_ABERTO->Brush->Color = clRed;
		btnRADUG_VAP001_ABERTO->Caption = "Aberta";
	}
	else{
		shpRADUG_VAP001_ABERTO->Brush->Color = clWhite;
		btnRADUG_VAP001_ABERTO->Caption = "Não Aberta";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RADUG_VAP001_FECHAR) == 1 ){
		shpRADUG_VAP001_FECHAR->Brush->Color = clLime;
                if (btnRADUG_VAP001_FECHADO->Caption == "Não Fechada"){
                        if (CLP.RD(PC_HL_RADUG_VAP001_FECHADO) == 0){
                                CLP.WR(PC_HL_RADUG_VAP001_ABERTO,  0);
                                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 1);
                        }
                }
	}
	else{
		shpRADUG_VAP001_FECHAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RADUG_VAP001_ABRIR) == 1 ){
		shpRADUG_VAP001_ABRIR->Brush->Color = clYellow;
                if (btnRADUG_VAP001_ABERTO->Caption == "Não Aberta"){
                        if (CLP.RD(PC_HL_RADUG_VAP001_ABERTO) == 0){
                                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 0);
                                CLP.WR(PC_HL_RADUG_VAP001_ABERTO,  1);
                        }
                }
	}
	else{
		shpRADUG_VAP001_ABRIR->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RADUG_VAP002
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_VAP002_FECHADO) == 1 ){
		shpRADUG_VAP002_FECHADO->Brush->Color = clLime;
		btnRADUG_VAP002_FECHADO->Caption = "Fechada";
	}
	else{
		shpRADUG_VAP002_FECHADO->Brush->Color = clWhite;
		btnRADUG_VAP002_FECHADO->Caption = "Não Fechada";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RADUG_VAP002_ABERTO) == 1 ){
		shpRADUG_VAP002_ABERTO->Brush->Color = clRed;
		btnRADUG_VAP002_ABERTO->Caption = "Aberta";
	}
	else{
		shpRADUG_VAP002_ABERTO->Brush->Color = clWhite;
		btnRADUG_VAP002_ABERTO->Caption = "Não Aberta";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RADUG_VAP002_FECHAR) == 1 ){
		shpRADUG_VAP002_FECHAR->Brush->Color = clLime;
                if (btnRADUG_VAP002_FECHADO->Caption == "Não Fechada"){
                        if (CLP.RD(PC_HL_RADUG_VAP002_FECHADO) == 0){
                                CLP.WR(PC_HL_RADUG_VAP002_ABERTO,  0);
                                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 1);
                        }
                }
	}
	else{
		shpRADUG_VAP002_FECHAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RADUG_VAP002_ABRIR) == 1 ){
		shpRADUG_VAP002_ABRIR->Brush->Color = clYellow;
                if (btnRADUG_VAP002_ABERTO->Caption == "Não Aberta"){
                        if (CLP.RD(PC_HL_RADUG_VAP002_ABERTO) == 0){
                                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 0);
                                CLP.WR(PC_HL_RADUG_VAP002_ABERTO,  1);
                        }
                }
	}
	else{
		shpRADUG_VAP002_ABRIR->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARCF_CFCAR
        //***********************************************************
        if ( CLP.RD(PC_HL_RARCF_CFCAR_TEMPALTA) == 1 ){
		shpRARCF_CFCAR_TEMPALTA->Brush->Color = clRed;
		btnRARCF_CFCAR_TEMPALTA->Caption = "Temp. Alta";
	}
	else{
		shpRARCF_CFCAR_TEMPALTA->Brush->Color = clWhite;
		btnRARCF_CFCAR_TEMPALTA->Caption = "Não Temp. Alta";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARCF_CFLAT
        //***********************************************************
        if ( CLP.RD(PC_HL_RARCF_CFLAT_TEMPALTA) == 1 ){
		shpRARCF_CFLAT_TEMPALTA->Brush->Color = clRed;
		btnRARCF_CFLAT_TEMPALTA->Caption = "Temp. Alta";
	}
	else{
		shpRARCF_CFLAT_TEMPALTA->Brush->Color = clWhite;
		btnRARCF_CFLAT_TEMPALTA->Caption = "Não Temp. Alta";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARCF_CFLAT_TEMPBAIXA) == 0 ){
		shpRARCF_CFLAT_TEMPBAIXA->Brush->Color = clYellow;
		btnRARCF_CFLAT_TEMPBAIXA->Caption = "Temp. Baixa";
	}
	else{
		shpRARCF_CFLAT_TEMPBAIXA->Brush->Color = clWhite;
		btnRARCF_CFLAT_TEMPBAIXA->Caption = "Não Temp. Baixa";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARCF_CFVEG
        //***********************************************************
        if ( CLP.RD(PC_HL_RARCF_CFVEG_TEMPALTA) == 1 ){
		shpRARCF_CFVEG_TEMPALTA->Brush->Color = clRed;
		btnRARCF_CFVEG_TEMPALTA->Caption = "Temp. Alta";
	}
	else{
		shpRARCF_CFVEG_TEMPALTA->Brush->Color = clWhite;
		btnRARCF_CFVEG_TEMPALTA->Caption = "Não Temp. Alta";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARCF_CFVEG_TEMPBAIXA) == 0 ){
		shpRARCF_CFVEG_TEMPBAIXA->Brush->Color = clYellow;
		btnRARCF_CFVEG_TEMPBAIXA->Caption = "Temp. Baixa";
	}
	else{
		shpRARCF_CFVEG_TEMPBAIXA->Brush->Color = clWhite;
		btnRARCF_CFVEG_TEMPBAIXA->Caption = "Não Temp. Baixa";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARUG_BEAGD1
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_BEAGD1_LIGADO) == 1 ){
		shpRARUG_BEAGD1_LIGADO->Brush->Color = clLime;
		btnRARUG_BEAGD1_LIGADO->Caption = "Ligado";
	}
	else{
		shpRARUG_BEAGD1_LIGADO->Brush->Color = clWhite;
		btnRARUG_BEAGD1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_BEAGD1_FALHA) == 1 ){
		shpRARUG_BEAGD1_FALHA->Brush->Color = clRed;
		btnRARUG_BEAGD1_FALHA->Caption = "Em Falha";
	}
	else{
		shpRARUG_BEAGD1_FALHA->Brush->Color = clWhite;
		btnRARUG_BEAGD1_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARUG_BEAGD2
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_BEAGD2_LIGADO) == 1 ){
		shpRARUG_BEAGD2_LIGADO->Brush->Color = clLime;
		btnRARUG_BEAGD2_LIGADO->Caption = "Ligado";
	}
	else{
		shpRARUG_BEAGD2_LIGADO->Brush->Color = clWhite;
		btnRARUG_BEAGD2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_BEAGD2_FALHA) == 1 ){
		shpRARUG_BEAGD2_FALHA->Brush->Color = clRed;
		btnRARUG_BEAGD2_FALHA->Caption = "Em Falha";
	}
	else{
		shpRARUG_BEAGD2_FALHA->Brush->Color = clWhite;
		btnRARUG_BEAGD2_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARUG_URA1
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_URA1_LIGADO) == 1 ){
		shpRARUG_URA1_LIGADO->Brush->Color = clLime;
		btnRARUG_URA1_LIGADO->Caption = "Ligado";
	}
	else{
		shpRARUG_URA1_LIGADO->Brush->Color = clWhite;
		btnRARUG_URA1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_URA1_FALHA) == 1 ){
		shpRARUG_URA1_FALHA->Brush->Color = clRed;
		btnRARUG_URA1_FALHA->Caption = "Em Falha";
	}
	else{
		shpRARUG_URA1_FALHA->Brush->Color = clWhite;
		btnRARUG_URA1_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARUG_URA2
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_URA2_LIGADO) == 1 ){
		shpRARUG_URA2_LIGADO->Brush->Color = clLime;
		btnRARUG_URA2_LIGADO->Caption = "Ligado";
	}
	else{
		shpRARUG_URA2_LIGADO->Brush->Color = clWhite;
		btnRARUG_URA2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_URA2_FALHA) == 1 ){
		shpRARUG_URA2_FALHA->Brush->Color = clRed;
		btnRARUG_URA2_FALHA->Caption = "Em Falha";
	}
	else{
		shpRARUG_URA2_FALHA->Brush->Color = clWhite;
		btnRARUG_URA2_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RARUG_URA3
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_URA3_LIGADO) == 1 ){
		shpRARUG_URA3_LIGADO->Brush->Color = clLime;
		btnRARUG_URA3_LIGADO->Caption = "Ligado";
	}
	else{
		shpRARUG_URA3_LIGADO->Brush->Color = clWhite;
		btnRARUG_URA3_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RARUG_URA3_FALHA) == 1 ){
		shpRARUG_URA3_FALHA->Brush->Color = clRed;
		btnRARUG_URA3_FALHA->Caption = "Em Falha";
	}
	else{
		shpRARUG_URA3_FALHA->Brush->Color = clWhite;
		btnRARUG_URA3_FALHA->Caption = "Sem Falha";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RASIS_BECAS1
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS1_LIGADO) == 1 ){
		shpRASIS_BECAS1_LIGADO->Brush->Color = clLime;
		btnRASIS_BECAS1_LIGADO->Caption = "Ligado";
	}
	else{
		shpRASIS_BECAS1_LIGADO->Brush->Color = clWhite;
		btnRASIS_BECAS1_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS1_EMREM) == 1 ){
		shpRASIS_BECAS1_EMREM->Brush->Color = clNavy;
		btnRASIS_BECAS1_EMREM->Caption = "Em Remoto";
                btnRASIS_BECAS1_LIGAR->Enabled = false;
                btnRASIS_BECAS1_DESLIGAR->Enabled = false;
	}
	else{
		shpRASIS_BECAS1_EMREM->Brush->Color = clWhite;
		btnRASIS_BECAS1_EMREM->Caption = "Em Local";
                if ( shpRASIS_BECAS1_PARAREMERG->Brush->Color == clWhite && shpRASIS_BECAS1_PRDEMERGLOCAL->Brush->Color == clWhite ){
                        btnRASIS_BECAS1_LIGAR->Enabled = true;
                        btnRASIS_BECAS1_DESLIGAR->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS1_SOBREC1) == 1 ){
		shpRASIS_BECAS1_SOBREC1->Brush->Color = clRed;
		btnRASIS_BECAS1_SOBREC1->Caption = "Em Sobrecarga";
	}
	else{
		shpRASIS_BECAS1_SOBREC1->Brush->Color = clWhite;
		btnRASIS_BECAS1_SOBREC1->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS1_SOBREC2) == 1 ){
		shpRASIS_BECAS1_SOBREC2->Brush->Color = clRed;
		btnRASIS_BECAS1_SOBREC2->Caption = "Em Sobretemperatura";
	}
	else{
		shpRASIS_BECAS1_SOBREC2->Brush->Color = clWhite;
		btnRASIS_BECAS1_SOBREC2->Caption = "Sem Sobretemperatura";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RASIS_BECAS1_LIGAR) == 1 ){
		shpRASIS_BECAS1_LIGAR->Brush->Color = clLime;
                 if (btnRASIS_BECAS1_LIGADO->Caption == "Parado"){
                        if (CLP.RD(PC_HL_RASIS_BECAS1_LIGADO) == 0){
                                CLP.WR(PC_HL_RASIS_BECAS1_LIGADO, 1);
                        }
                }
	}
	else{
                shpRASIS_BECAS1_LIGAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RASIS_BECAS1_DESLIGAR) == 1 || CLP.RD(CP_HL_RASIS_BECAS1_PARAREMERG) == 1){
		if ( CLP.RD(CP_HL_RASIS_BECAS1_PARAREMERG) == 1 ){
		        shpRASIS_BECAS1_PARAREMERG->Brush->Color = clRed;
                        btnRASIS_BECAS1_LIGAR->Enabled = false;
                        btnRASIS_BECAS1_DESLIGAR->Enabled = false;
                        btnRASIS_BECAS1_LIGADO->Enabled = false;
	        }
                if ( CLP.RD(CP_HL_RASIS_BECAS1_DESLIGAR) == 1 ){
		        shpRASIS_BECAS1_DESLIGAR->Brush->Color = clYellow;
	        }
                if (btnRASIS_BECAS1_LIGADO->Caption == "Ligado"){
                        if (CLP.RD(PC_HL_RASIS_BECAS1_LIGADO) == 1){
                                CLP.WR(PC_HL_RASIS_BECAS1_LIGADO, 0);
                        }
                }
	}
	else{
                shpRASIS_BECAS1_PARAREMERG->Brush->Color = clWhite;
                shpRASIS_BECAS1_DESLIGAR->Brush->Color = clWhite;
                if (shpRASIS_BECAS1_PRDEMERGLOCAL->Brush->Color == clWhite){
                        if (btnRASIS_BECAS1_EMREM->Caption == "Em Local"){
                                btnRASIS_BECAS1_LIGAR->Enabled = true;
                                btnRASIS_BECAS1_DESLIGAR->Enabled = true;
                        }
                        btnRASIS_BECAS1_LIGADO->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS1_PRDEMERGLOCAL) == 1 ){
		shpRASIS_BECAS1_PRDEMERGLOCAL->Brush->Color = clRed;
                btnRASIS_BECAS1_LIGAR->Enabled = false;
                btnRASIS_BECAS1_DESLIGAR->Enabled = false;
                btnRASIS_BECAS1_LIGADO->Enabled = false;
	}
	else{
		shpRASIS_BECAS1_PRDEMERGLOCAL->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RASIS_BECAS2
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS2_LIGADO) == 1 ){
		shpRASIS_BECAS2_LIGADO->Brush->Color = clLime;
		btnRASIS_BECAS2_LIGADO->Caption = "Ligado";
	}
	else{
		shpRASIS_BECAS2_LIGADO->Brush->Color = clWhite;
		btnRASIS_BECAS2_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS2_EMREM) == 1 ){
		shpRASIS_BECAS2_EMREM->Brush->Color = clNavy;
		btnRASIS_BECAS2_EMREM->Caption = "Em Remoto";
                btnRASIS_BECAS2_LIGAR->Enabled = false;
                btnRASIS_BECAS2_DESLIGAR->Enabled = false;
	}
	else{
		shpRASIS_BECAS2_EMREM->Brush->Color = clWhite;
		btnRASIS_BECAS2_EMREM->Caption = "Em Local";
                if ( shpRASIS_BECAS2_PARAREMERG->Brush->Color == clWhite && shpRASIS_BECAS2_PRDEMERGLOCAL->Brush->Color == clWhite ){
                        btnRASIS_BECAS2_LIGAR->Enabled = true;
                        btnRASIS_BECAS2_DESLIGAR->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS2_SOBREC1) == 1 ){
		shpRASIS_BECAS2_SOBREC1->Brush->Color = clRed;
		btnRASIS_BECAS2_SOBREC1->Caption = "Em Sobrecarga";
	}
	else{
		shpRASIS_BECAS2_SOBREC1->Brush->Color = clWhite;
		btnRASIS_BECAS2_SOBREC1->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS2_SOBREC2) == 1 ){
		shpRASIS_BECAS2_SOBREC2->Brush->Color = clRed;
		btnRASIS_BECAS2_SOBREC2->Caption = "Em Sobretemperatura";
	}
	else{
		shpRASIS_BECAS2_SOBREC2->Brush->Color = clWhite;
		btnRASIS_BECAS2_SOBREC2->Caption = "Sem Sobretemperatura";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RASIS_BECAS2_LIGAR) == 1 ){
		shpRASIS_BECAS2_LIGAR->Brush->Color = clLime;
                 if (btnRASIS_BECAS2_LIGADO->Caption == "Parado"){
                        if (CLP.RD(PC_HL_RASIS_BECAS2_LIGADO) == 0){
                                CLP.WR(PC_HL_RASIS_BECAS2_LIGADO, 1);
                        }
                }
	}
	else{
                shpRASIS_BECAS2_LIGAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RASIS_BECAS2_DESLIGAR) == 1 || CLP.RD(CP_HL_RASIS_BECAS2_PARAREMERG) == 1){
		if ( CLP.RD(CP_HL_RASIS_BECAS2_PARAREMERG) == 1 ){
		        shpRASIS_BECAS2_PARAREMERG->Brush->Color = clRed;
                        btnRASIS_BECAS2_LIGAR->Enabled = false;
                        btnRASIS_BECAS2_DESLIGAR->Enabled = false;
                        btnRASIS_BECAS2_LIGADO->Enabled = false;
	        }
                if ( CLP.RD(CP_HL_RASIS_BECAS2_DESLIGAR) == 1 ){
		        shpRASIS_BECAS2_DESLIGAR->Brush->Color = clYellow;
	        }
                if (btnRASIS_BECAS2_LIGADO->Caption == "Ligado"){
                        if (CLP.RD(PC_HL_RASIS_BECAS2_LIGADO) == 1){
                                CLP.WR(PC_HL_RASIS_BECAS2_LIGADO, 0);
                        }
                }
	}
	else{
                shpRASIS_BECAS2_PARAREMERG->Brush->Color = clWhite;
                shpRASIS_BECAS2_DESLIGAR->Brush->Color = clWhite;
                if (shpRASIS_BECAS2_PRDEMERGLOCAL->Brush->Color == clWhite){
                        if (btnRASIS_BECAS2_EMREM->Caption == "Em Local"){
                                btnRASIS_BECAS2_LIGAR->Enabled = true;
                                btnRASIS_BECAS2_DESLIGAR->Enabled = true;
                        }
                        btnRASIS_BECAS2_LIGADO->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS2_PRDEMERGLOCAL) == 1 ){
		shpRASIS_BECAS2_PRDEMERGLOCAL->Brush->Color = clRed;
                btnRASIS_BECAS2_LIGAR->Enabled = false;
                btnRASIS_BECAS2_DESLIGAR->Enabled = false;
                btnRASIS_BECAS2_LIGADO->Enabled = false;
	}
	else{
		shpRASIS_BECAS2_PRDEMERGLOCAL->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RASIS_BECAS3
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS3_LIGADO) == 1 ){
		shpRASIS_BECAS3_LIGADO->Brush->Color = clLime;
		btnRASIS_BECAS3_LIGADO->Caption = "Ligado";
	}
	else{
		shpRASIS_BECAS3_LIGADO->Brush->Color = clWhite;
		btnRASIS_BECAS3_LIGADO->Caption = "Parado";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS3_EMREM) == 1 ){
		shpRASIS_BECAS3_EMREM->Brush->Color = clNavy;
		btnRASIS_BECAS3_EMREM->Caption = "Em Remoto";
                btnRASIS_BECAS3_LIGAR->Enabled = false;
                btnRASIS_BECAS3_DESLIGAR->Enabled = false;
	}
	else{
		shpRASIS_BECAS3_EMREM->Brush->Color = clWhite;
		btnRASIS_BECAS3_EMREM->Caption = "Em Local";
                if ( shpRASIS_BECAS3_PARAREMERG->Brush->Color == clWhite && shpRASIS_BECAS3_PRDEMERGLOCAL->Brush->Color == clWhite ){
                        btnRASIS_BECAS3_LIGAR->Enabled = true;
                        btnRASIS_BECAS3_DESLIGAR->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS3_SOBREC1) == 1 ){
		shpRASIS_BECAS3_SOBREC1->Brush->Color = clRed;
		btnRASIS_BECAS3_SOBREC1->Caption = "Em Sobrecarga";
	}
	else{
		shpRASIS_BECAS3_SOBREC1->Brush->Color = clWhite;
		btnRASIS_BECAS3_SOBREC1->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS3_SOBREC2) == 1 ){
		shpRASIS_BECAS3_SOBREC2->Brush->Color = clRed;
		btnRASIS_BECAS3_SOBREC2->Caption = "Em Sobretemperatura";
	}
	else{
		shpRASIS_BECAS3_SOBREC2->Brush->Color = clWhite;
		btnRASIS_BECAS3_SOBREC2->Caption = "Sem Sobretemperatura";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RASIS_BECAS3_LIGAR) == 1 ){
		shpRASIS_BECAS3_LIGAR->Brush->Color = clLime;
                 if (btnRASIS_BECAS3_LIGADO->Caption == "Parado"){
                        if (CLP.RD(PC_HL_RASIS_BECAS3_LIGADO) == 0){
                                CLP.WR(PC_HL_RASIS_BECAS3_LIGADO, 1);
                        }
                }
	}
	else{
                shpRASIS_BECAS3_LIGAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_RASIS_BECAS3_DESLIGAR) == 1 || CLP.RD(CP_HL_RASIS_BECAS3_PARAREMERG) == 1){
		if ( CLP.RD(CP_HL_RASIS_BECAS3_PARAREMERG) == 1 ){
		        shpRASIS_BECAS3_PARAREMERG->Brush->Color = clRed;
                        btnRASIS_BECAS3_LIGAR->Enabled = false;
                        btnRASIS_BECAS3_DESLIGAR->Enabled = false;
                        btnRASIS_BECAS3_LIGADO->Enabled = false;
	        }
                if ( CLP.RD(CP_HL_RASIS_BECAS3_DESLIGAR) == 1 ){
		        shpRASIS_BECAS3_DESLIGAR->Brush->Color = clYellow;
	        }
                if (btnRASIS_BECAS3_LIGADO->Caption == "Ligado"){
                        if (CLP.RD(PC_HL_RASIS_BECAS3_LIGADO) == 1){
                                CLP.WR(PC_HL_RASIS_BECAS3_LIGADO, 0);
                        }
                }
	}
	else{
                shpRASIS_BECAS3_PARAREMERG->Brush->Color = clWhite;
                shpRASIS_BECAS3_DESLIGAR->Brush->Color = clWhite;
                if (shpRASIS_BECAS3_PRDEMERGLOCAL->Brush->Color == clWhite){
                        if (btnRASIS_BECAS3_EMREM->Caption == "Em Local"){
                                btnRASIS_BECAS3_LIGAR->Enabled = true;
                                btnRASIS_BECAS3_DESLIGAR->Enabled = true;
                        }
                        btnRASIS_BECAS3_LIGADO->Enabled = true;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_RASIS_BECAS3_PRDEMERGLOCAL) == 1 ){
		shpRASIS_BECAS3_PRDEMERGLOCAL->Brush->Color = clRed;
                btnRASIS_BECAS3_LIGAR->Enabled = false;
                btnRASIS_BECAS3_DESLIGAR->Enabled = false;
                btnRASIS_BECAS3_LIGADO->Enabled = false;
	}
	else{
		shpRASIS_BECAS3_PRDEMERGLOCAL->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//RASIS_RASAPM
        //***********************************************************
	lblRASIS_RASAPM_PRESS->Caption = CLP.RD(PC_HA_RASIS_RASAPM_PRESS);
	lblRASIS_RASAPM_PRESS->Caption = FormatFloat("0.###",lblRASIS_RASAPM_PRESS->Caption.ToDouble()) ;
	pgrRASIS_RASAPM_PRESS->Position = (((lblRASIS_RASAPM_PRESS->Caption*100)-(0*100))*(100-0))/((8.4-0)*100); //bar
	//***********************************************************
//==============================================================================
//==============================================================================
//RASIS_RASAPR
        //***********************************************************
	lblRASIS_RASAPR_PRESS->Caption = CLP.RD(PC_HA_RASIS_RASAPR_PRESS);
	lblRASIS_RASAPR_PRESS->Caption = FormatFloat("0.###",lblRASIS_RASAPR_PRESS->Caption.ToDouble()) ;
	pgrRASIS_RASAPR_PRESS->Position = (((lblRASIS_RASAPR_PRESS->Caption*100)-(0*100))*(100-0))/((16.0-0)*100); //bar
	//***********************************************************
//==============================================================================
//==============================================================================
//RASIS_RASAPV
        //***********************************************************
	lblRASIS_RASAPV_PRESS->Caption = CLP.RD(PC_HA_RASIS_RASAPV_PRESS);
	lblRASIS_RASAPV_PRESS->Caption = FormatFloat("0.###",lblRASIS_RASAPV_PRESS->Caption.ToDouble()) ;
	pgrRASIS_RASAPV_PRESS->Position = (((lblRASIS_RASAPV_PRESS->Caption*100)-(0*100))*(100-0))/((8.4-0)*100); //bar
	//***********************************************************
//==============================================================================
//==============================================================================
//RASIS_BECAS3
        //***********************************************************
        if ( CLP.RD(PC_HL_RASRG_OERHPC_PRESSBAIXA) == 1 ){
		shpRASRG_OERHPC_PRESSBAIXA->Brush->Color = clRed;
		btnRASRG_OERHPC_PRESSBAIXA->Caption = "Pressão Baixa";
	}
	else{
		shpRASRG_OERHPC_PRESSBAIXA->Brush->Color = clWhite;
		btnRASRG_OERHPC_PRESSBAIXA->Caption = "Pressão Normal";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEDPM_RVENPMA
        //***********************************************************
	lblVEDPM_RVENPMA_TEMP->Caption = CLP.RD(PC_HA_VEDPM_RVENPMA_TEMP);
	lblVEDPM_RVENPMA_TEMP->Caption = FormatFloat("0.###",lblVEDPM_RVENPMA_TEMP->Caption.ToDouble()) ;
	pgrVEDPM_RVENPMA_TEMP->Position = (((lblVEDPM_RVENPMA_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEDPM_RVENPMR
        //***********************************************************
	lblVEDPM_RVENPMR_TEMP->Caption = CLP.RD(PC_HA_VEDPM_RVENPMR_TEMP);
	lblVEDPM_RVENPMR_TEMP->Caption = FormatFloat("0.###",lblVEDPM_RVENPMR_TEMP->Caption.ToDouble()) ;
	pgrVEDPM_RVENPMR_TEMP->Position = (((lblVEDPM_RVENPMR_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEDPM_RVENPMV
        //***********************************************************
	lblVEDPM_RVENPMV_TEMP->Caption = CLP.RD(PC_HA_VEDPM_RVENPMV_TEMP);
	lblVEDPM_RVENPMV_TEMP->Caption = FormatFloat("0.###",lblVEDPM_RVENPMV_TEMP->Caption.ToDouble()) ;
	pgrVEDPM_RVENPMV_TEMP->Position = (((lblVEDPM_RVENPMV_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_ANTCME
        //***********************************************************
	lblVEFPM_ANTCME_TEMP->Caption = CLP.RD(PC_HA_VEFPM_ANTCME_TEMP);
	lblVEFPM_ANTCME_TEMP->Caption = FormatFloat("0.###",lblVEFPM_ANTCME_TEMP->Caption.ToDouble()) ;
	pgrVEFPM_ANTCME_TEMP->Position = (((lblVEFPM_ANTCME_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_ANTMAGE
        //***********************************************************
	lblVEFPM_ANTMAGE_TEMP->Caption = CLP.RD(PC_HA_VEFPM_ANTMAGE_TEMP);
	lblVEFPM_ANTMAGE_TEMP->Caption = FormatFloat("0.###",lblVEFPM_ANTMAGE_TEMP->Caption.ToDouble()) ;
	pgrVEFPM_ANTMAGE_TEMP->Position = (((lblVEFPM_ANTMAGE_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_CONTALCA
        //***********************************************************
	lblVEFPM_CONTALCA_TEMP->Caption = CLP.RD(PC_HA_VEFPM_CONTALCA_TEMP);
	lblVEFPM_CONTALCA_TEMP->Caption = FormatFloat("0.###",lblVEFPM_CONTALCA_TEMP->Caption.ToDouble()) ;
	pgrVEFPM_CONTALCA_TEMP->Position = (((lblVEFPM_CONTALCA_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_CPTCME
        //***********************************************************
	lblVEFPM_CPTCME_TEMP->Caption = CLP.RD(PC_HA_VEFPM_CPTCME_TEMP);
	lblVEFPM_CPTCME_TEMP->Caption = FormatFloat("0.###",lblVEFPM_CPTCME_TEMP->Caption.ToDouble()) ;
	pgrVEFPM_CPTCME_TEMP->Position = (((lblVEFPM_CPTCME_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_ESTCHAFF
        //***********************************************************
	lblVEFPM_ESTCHAFF_TEMP->Caption = CLP.RD(PC_HA_VEFPM_ESTCHAFF_TEMP);
	lblVEFPM_ESTCHAFF_TEMP->Caption = FormatFloat("0.###",lblVEFPM_ESTCHAFF_TEMP->Caption.ToDouble()) ;
	pgrVEFPM_ESTCHAFF_TEMP->Position = (((lblVEFPM_ESTCHAFF_TEMP->Caption*100)-(0*100))*(100-0))/((100.0-0)*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE01
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE01_LIGADO) == 1 ){
		shpVEFPM_EXAE01_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE01_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE01_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE01_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE02
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE02_LIGADO) == 1 ){
		shpVEFPM_EXAE02_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE02_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE02_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE02_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE03
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE03_LIGADO) == 1 ){
		shpVEFPM_EXAE03_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE03_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE03_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE03_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE04
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE04_LIGADO) == 1 ){
		shpVEFPM_EXAE04_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE04_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE04_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE04_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE05
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE05_LIGADO) == 1 ){
		shpVEFPM_EXAE05_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE05_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE05_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE05_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE06
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE06_LIGADO) == 1 ){
		shpVEFPM_EXAE06_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE06_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE06_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE06_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_EXAE07
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_EXAE07_LIGADO) == 1 ){
		shpVEFPM_EXAE07_LIGADO->Brush->Color = clLime;
		btnVEFPM_EXAE07_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_EXAE07_LIGADO->Brush->Color = clWhite;
		btnVEFPM_EXAE07_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//VEFPM_VENT
        //***********************************************************
        if ( CLP.RD(PC_HL_VEFPM_VENT_LIGADO) == 1 ){
		shpVEFPM_VENT_LIGADO->Brush->Color = clLime;
		btnVEFPM_VENT_LIGADO->Caption = "Ligado";
	}
	else{
		shpVEFPM_VENT_LIGADO->Brush->Color = clWhite;
		btnVEFPM_VENT_LIGADO->Caption = "Parado";
	};
        //***********************************************************
//==============================================================================
//==============================================================================
//GOVBC_MAQLEM
        //***********************************************************
	lblGOVBC_MAQLEM_LEMEPOSIC->Caption = CLP.RD(PC_HA_GOVBC_MAQLEM_LEMEPOSIC);
	lblGOVBC_MAQLEM_LEMEPOSIC->Caption = FormatFloat("0.###",lblGOVBC_MAQLEM_LEMEPOSIC->Caption.ToDouble()) ;
	pgrGOVBC_MAQLEM_LEMEPOSIC->Position = (((lblGOVBC_MAQLEM_LEMEPOSIC->Caption*100)-(-45*100))*(100-0))/((45-(-45))*100); //°C
	//***********************************************************
//==============================================================================
//==============================================================================
//MAQLEM_CML e UHIDBB e UHIDBE
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_CML_UHBBSEL) == 1 ){
		shpMAQLEM_CML_UHBBSEL->Brush->Color = clLime;
		btnMAQLEM_CML_UHBBSEL->Caption = "U. Hid. de BB sel.";
	}
	else{
		shpMAQLEM_CML_UHBBSEL->Brush->Color = clWhite;
		btnMAQLEM_CML_UHBBSEL->Caption = "U. Hid. de BB n sel.";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_CML_UHBESEL) == 1 ){
		shpMAQLEM_CML_UHBESEL->Brush->Color = clLime;
		btnMAQLEM_CML_UHBESEL->Caption = "U. Hid. de BE sel.";
	}
	else{
		shpMAQLEM_CML_UHBESEL->Brush->Color = clWhite;
		btnMAQLEM_CML_UHBESEL->Caption = "U. Hid. de Be n sel.";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_CML_UHNASSOC) == 1 ){
		shpMAQLEM_CML_UHNASSOC->Brush->Color = clLime;
		btnMAQLEM_CML_UHNASSOC->Caption = "U. hid. assoc.";

                if ( CLP.RD(PP_HL_MAQLEM_CML_UHIDNASSC) == 0 ){
                        shpMAQLEM_CML_UHIDNASSC->Brush->Color = clLime;
                        CLP.WR(PP_HL_MAQLEM_CML_UHIDNASSC, 1);
                }
	}
	else{
		shpMAQLEM_CML_UHNASSOC->Brush->Color = clWhite;
		btnMAQLEM_CML_UHNASSOC->Caption = "U. hid. n assoc.";

                if ( CLP.RD(PP_HL_MAQLEM_CML_UHIDNASSC) == 1 ){
                        shpMAQLEM_CML_UHIDNASSC->Brush->Color = clWhite;
                        CLP.WR(PP_HL_MAQLEM_CML_UHIDNASSC, 0);
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_CML_SELCUHDISPON) == 1 ){
		shpMAQLEM_CML_SELCUHDISPON->Brush->Color = clLime;
		btnMAQLEM_CML_SELCUHDISPON->Caption = "Sel. da U. Hid. disp.";
	}
	else{
		shpMAQLEM_CML_SELCUHDISPON->Brush->Color = clWhite;
		btnMAQLEM_CML_SELCUHDISPON->Caption = "Sel. da U. Hid. n disp.";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_CML_CMDDISPCCM) == 1 ){
		shpMAQLEM_CML_CMDDISPCCM->Brush->Color = clLime;
		btnMAQLEM_CML_CMDDISPCCM->Caption = "Est. de Cmd. no CCM";
	}
	else{
		shpMAQLEM_CML_CMDDISPCCM->Brush->Color = clWhite;
		btnMAQLEM_CML_CMDDISPCCM->Caption = "Est. de Cmd. n no CCM";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_MAQLEM_UHIDBB_SELEC) == 1 && CLP.RD(CP_HL_MAQLEM_UHIDBE_SELEC) == 0){
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_SELEC) == 1 ){
                        shpMAQLEM_UHIDBB_SELEC->Brush->Color = clWhite;
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_SELEC, 0);
                }
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_SELEC) == 1 ){
                        shpMAQLEM_UHIDBE_SELEC->Brush->Color = clWhite;
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_SELEC, 0);
                }
                if ( CLP.RD(PP_HL_MAQLEM_CML_CHKSELCUH) == 1 ){
                        shpMAQLEM_CML_CHKSELCUH->Brush->Color = clWhite;
                        CLP.WR(PP_HL_MAQLEM_CML_CHKSELCUH, 0);
                }
                if ( CLP.RD(PC_HL_MAQLEM_CML_UHBBSEL) == 0 ){
                        CLP.WR(PC_HL_MAQLEM_CML_UHBBSEL, 1);
                }
                if ( CLP.RD(PC_HL_MAQLEM_CML_UHBESEL) == 1 ){
                        CLP.WR(PC_HL_MAQLEM_CML_UHBESEL, 0);
                }
        }else{
                if ( CLP.RD(CP_HL_MAQLEM_UHIDBB_SELEC) == 0 && CLP.RD(CP_HL_MAQLEM_UHIDBE_SELEC) == 1){
                        if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_SELEC) == 0 ){
                                shpMAQLEM_UHIDBB_SELEC->Brush->Color = clLime;
                                CLP.WR(PP_HL_MAQLEM_UHIDBB_SELEC, 1);
                        }
                        if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_SELEC) == 0 ){
                                shpMAQLEM_UHIDBE_SELEC->Brush->Color = clLime;
                                CLP.WR(PP_HL_MAQLEM_UHIDBE_SELEC, 1);
                        }
                        if ( CLP.RD(PP_HL_MAQLEM_CML_CHKSELCUH) == 0 ){
                                shpMAQLEM_CML_CHKSELCUH->Brush->Color = clLime;
                                CLP.WR(PP_HL_MAQLEM_CML_CHKSELCUH, 1);
                        }
                        if ( CLP.RD(PC_HL_MAQLEM_CML_UHBESEL) == 0 ){
                                CLP.WR(PC_HL_MAQLEM_CML_UHBESEL, 1);
                        }
                        if ( CLP.RD(PC_HL_MAQLEM_CML_UHBBSEL) == 1 ){
                                CLP.WR(PC_HL_MAQLEM_CML_UHBBSEL, 0);
                        }
                }else{
                        if ( CLP.RD(CP_HL_MAQLEM_UHIDBB_SELEC) == 0 && CLP.RD(CP_HL_MAQLEM_UHIDBE_SELEC) == 0){
                                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_SELEC) == 1 ){
                                        shpMAQLEM_UHIDBB_SELEC->Brush->Color = clWhite;
                                        CLP.WR(PP_HL_MAQLEM_UHIDBB_SELEC, 0);
                                }
                                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_SELEC) == 1 ){
                                        shpMAQLEM_UHIDBE_SELEC->Brush->Color = clWhite;
                                        CLP.WR(PP_HL_MAQLEM_UHIDBE_SELEC, 0);
                                }
                                if ( CLP.RD(PP_HL_MAQLEM_CML_CHKSELCUH) == 1 ){
                                        shpMAQLEM_CML_CHKSELCUH->Brush->Color = clWhite;
                                        CLP.WR(PP_HL_MAQLEM_CML_CHKSELCUH, 0);
                                }
                                if ( CLP.RD(PC_HL_MAQLEM_CML_UHBBSEL) == 0 ){
                                        CLP.WR(PC_HL_MAQLEM_CML_UHBBSEL, 1);
                                }
                                if ( CLP.RD(PC_HL_MAQLEM_CML_UHBESEL) == 1 ){
                                        CLP.WR(PC_HL_MAQLEM_CML_UHBESEL, 0);
                                }
                        }
                }
        }
        if (CLP.RD(PP_HL_MAQLEM_UHIDBB_SELEC) == 1){
                shpPP_HL_MAQLEM_UHIDBB_SELEC->Brush->Color = clLime;
        }else{
                shpPP_HL_MAQLEM_UHIDBB_SELEC->Brush->Color = clWhite;
        }
        if (CLP.RD(PP_HL_MAQLEM_UHIDBE_SELEC) == 1){
                shpPP_HL_MAQLEM_UHIDBE_SELEC->Brush->Color = clLime;
        }else{
                shpPP_HL_MAQLEM_UHIDBE_SELEC->Brush->Color = clWhite;
        }
//==============================================================================
//MAQLEM_UHIDBB
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_UHIDBB_NVBX) == 0 ){
                shpMAQLEM_UHIDBB_NVBX->Brush->Color = clRed;
                shpPP_HL_MAQLEM_UHIDBB_NVBX->Brush->Color = clRed;
                btnMAQLEM_UHIDBB_NVBX->Caption = "Nível Baixo";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_NVBX) == 0 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_NVBX, 1);
                }
        }else{
                shpMAQLEM_UHIDBB_NVBX->Brush->Color = clWhite;
                shpPP_HL_MAQLEM_UHIDBB_NVBX->Brush->Color = clWhite;
                btnMAQLEM_UHIDBB_NVBX->Caption = "Nível Normal";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_NVBX) == 1 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_NVBX, 0);
                }
        }
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_UHIDBB_PRESSBX) == 0 ){
                shpMAQLEM_UHIDBB_PRESSBX->Brush->Color = clRed;
                shpPP_HL_MAQLEM_UHIDBB_PRESSBX->Brush->Color = clRed;
                btnMAQLEM_UHIDBB_PRESSBX->Caption = "Pressão Baixa";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_PRESSBX) == 0 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_PRESSBX, 1);
                }
        }else{
                shpMAQLEM_UHIDBB_PRESSBX->Brush->Color = clWhite;
                shpPP_HL_MAQLEM_UHIDBB_PRESSBX->Brush->Color = clWhite;
                btnMAQLEM_UHIDBB_PRESSBX->Caption = "Pressão Normal";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_PRESSBX) == 1 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_PRESSBX, 0);
                }
        }
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_UHIDBB_TEMPAL) == 0 ){
                shpMAQLEM_UHIDBB_TEMPAL->Brush->Color = clRed;
                shpPP_HL_MAQLEM_UHIDBB_TEMPAL->Brush->Color = clRed;
                btnMAQLEM_UHIDBB_TEMPAL->Caption = "Temperatura Alta";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_TEMPAL) == 0 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_TEMPAL, 1);
                }
        }else{
                shpMAQLEM_UHIDBB_TEMPAL->Brush->Color = clWhite;
                shpPP_HL_MAQLEM_UHIDBB_TEMPAL->Brush->Color = clWhite;
                btnMAQLEM_UHIDBB_TEMPAL->Caption = "Temperatura Normal";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_TEMPAL) == 1 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_TEMPAL, 0);
                }
        }
        //***********************************************************
        if(shpMAQLEM_UHIDBB_NVBX->Brush->Color == clRed ||  shpMAQLEM_UHIDBB_PRESSBX->Brush->Color == clRed || shpMAQLEM_UHIDBB_TEMPAL->Brush->Color == clRed){
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_TRFAUTO) == 0){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_TRFAUTO, 1);
                }
        }else{
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_TRFAUTO) == 1){
                        CLP.WR(PP_HL_MAQLEM_UHIDBB_TRFAUTO, 0);
                }
        }
        if ( CLP.RD(PP_HL_MAQLEM_UHIDBB_TRFAUTO) == 1){
                shpPP_HL_MAQLEM_UHIDBB_TRFAUTO->Brush->Color = clYellow;
        }else{
                shpPP_HL_MAQLEM_UHIDBB_TRFAUTO->Brush->Color = clWhite;
        }
        //***********************************************************
//==============================================================================
//MAQLEM_UHIDBE
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_UHIDBE_NVBX) == 0 ){
                shpMAQLEM_UHIDBE_NVBX->Brush->Color = clRed;
                shpPP_HL_MAQLEM_UHIDBE_NVBX->Brush->Color = clRed;
                btnMAQLEM_UHIDBE_NVBX->Caption = "Nível Baixo";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_NVBX) == 0 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_NVBX, 1);
                }
        }else{
                shpMAQLEM_UHIDBE_NVBX->Brush->Color = clWhite;
                shpPP_HL_MAQLEM_UHIDBE_NVBX->Brush->Color = clWhite;
                btnMAQLEM_UHIDBE_NVBX->Caption = "Nível Normal";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_NVBX) == 1 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_NVBX, 0);
                }
        }
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_UHIDBE_PRESSBX) == 0 ){
                shpMAQLEM_UHIDBE_PRESSBX->Brush->Color = clRed;
                shpPP_HL_MAQLEM_UHIDBE_PRESSBX->Brush->Color = clRed;
                btnMAQLEM_UHIDBE_PRESSBX->Caption = "Pressão Baixa";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_PRESSBX) == 0 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_PRESSBX, 1);
                }
        }else{
                shpMAQLEM_UHIDBE_PRESSBX->Brush->Color = clWhite;
                shpPP_HL_MAQLEM_UHIDBE_PRESSBX->Brush->Color = clWhite;
                btnMAQLEM_UHIDBE_PRESSBX->Caption = "Pressão Normal";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_PRESSBX) == 1 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_PRESSBX, 0);
                }
        }
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_UHIDBE_TEMPAL) == 0 ){
                shpMAQLEM_UHIDBE_TEMPAL->Brush->Color = clRed;
                shpPP_HL_MAQLEM_UHIDBE_TEMPAL->Brush->Color = clRed;
                btnMAQLEM_UHIDBE_TEMPAL->Caption = "Temperatura Alta";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_TEMPAL) == 0 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_TEMPAL, 1);
                }
        }else{
                shpMAQLEM_UHIDBE_TEMPAL->Brush->Color = clWhite;
                shpPP_HL_MAQLEM_UHIDBE_TEMPAL->Brush->Color = clWhite;
                btnMAQLEM_UHIDBE_TEMPAL->Caption = "Temperatura Normal";
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_TEMPAL) == 1 ){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_TEMPAL, 0);
                }
        }
        //***********************************************************
        if(shpMAQLEM_UHIDBE_NVBX->Brush->Color == clRed ||  shpMAQLEM_UHIDBE_PRESSBX->Brush->Color == clRed || shpMAQLEM_UHIDBE_TEMPAL->Brush->Color == clRed){
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_TRFAUTO) == 0){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_TRFAUTO, 1);
                }
        }else{
                if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_TRFAUTO) == 1){
                        CLP.WR(PP_HL_MAQLEM_UHIDBE_TRFAUTO, 0);
                }
        }
        if ( CLP.RD(PP_HL_MAQLEM_UHIDBE_TRFAUTO) == 1){
                shpPP_HL_MAQLEM_UHIDBE_TRFAUTO->Brush->Color = clYellow;
        }else{
                shpPP_HL_MAQLEM_UHIDBE_TRFAUTO->Brush->Color = clWhite;
        }
        //***********************************************************
//==============================================================================
//MAQLEM_MOTBB
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBB_LIGADO) == 1 ){
		shpMAQLEM_MOTBB_LIGADO->Brush->Color = clLime;
		btnMAQLEM_MOTBB_LIGADO->Caption = "Ligado";
                if (btnMAQLEM_MOTBB_EMREM->Caption == "Em Local" && btnMAQLEM_MOTBB_PARAREMERGLOC->Caption == "Parar em Emergência"){
                        btnPartirMAQLEM_MOTBB->Enabled = false;
                        btnPararMAQLEM_MOTBB->Enabled = true;
                }
	}
	else{
		shpMAQLEM_MOTBB_LIGADO->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_LIGADO->Caption = "Parado";
                if (btnMAQLEM_MOTBB_EMREM->Caption == "Em Local" && btnMAQLEM_MOTBB_PARAREMERGLOC->Caption == "Parar em Emergência"){
                        btnPartirMAQLEM_MOTBB->Enabled = true;
                        btnPararMAQLEM_MOTBB->Enabled = false;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBB_EMREM) == 1 ){
		shpMAQLEM_MOTBB_EMREM->Brush->Color = clNavy;
		btnMAQLEM_MOTBB_EMREM->Caption = "Em Remoto";
                btnPartirMAQLEM_MOTBB->Enabled = false;
                btnPararMAQLEM_MOTBB->Enabled = false;
	}
	else{
		shpMAQLEM_MOTBB_EMREM->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_EMREM->Caption = "Em Local";
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_MAQLEM_MOTBB_ALIMDISPON) == 1 ){
		shpMAQLEM_MOTBB_ALIMDISPON->Brush->Color = clLime;
		btnMAQLEM_MOTBB_ALIMDISPON->Caption = "Alim. Dispon.";
	}
	else{
		shpMAQLEM_MOTBB_ALIMDISPON->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_ALIMDISPON->Caption = "Alim. Não Dispon.";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBB_ALIMLOGICOK) == 1 ){
		shpMAQLEM_MOTBB_ALIMLOGICOK->Brush->Color = clLime;
		btnMAQLEM_MOTBB_ALIMLOGICOK->Caption = "Alim. Lógica OK";
	}
	else{
		shpMAQLEM_MOTBB_ALIMLOGICOK->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_ALIMLOGICOK->Caption = "Sem Alim. Lógica";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBB_FALTADEFASE) == 1 ){
		shpMAQLEM_MOTBB_FALTADEFASE->Brush->Color = clYellow;
		btnMAQLEM_MOTBB_FALTADEFASE->Caption = "Falta de Fase";
	}
	else{
		shpMAQLEM_MOTBB_FALTADEFASE->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_FALTADEFASE->Caption = "Sem Falta de Fase";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBB_EMSOBREC) == 1 ){
		shpMAQLEM_MOTBB_EMSOBREC->Brush->Color = clRed;
		btnMAQLEM_MOTBB_EMSOBREC->Caption = "Em Sobrecarga";
	}
	else{
		shpMAQLEM_MOTBB_EMSOBREC->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_EMSOBREC->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBB_DESUMLIG) == 1 ){
		shpMAQLEM_MOTBB_DESUMLIG->Brush->Color = clRed;
		btnMAQLEM_MOTBB_DESUMLIG->Caption = "Desum. Lig.";
	}
	else{
		shpMAQLEM_MOTBB_DESUMLIG->Brush->Color = clWhite;
		btnMAQLEM_MOTBB_DESUMLIG->Caption = "Desum. Des.";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_MAQLEM_MOTBB_PARTIR) == 1 ){
		shpMAQLEM_MOTBB_PARTIR->Brush->Color = clLime;
                tmrPararMAQLEM_MOTBB->Enabled = false;
		if (btnMAQLEM_MOTBB_LIGADO->Caption == "Parado"  && tmrPartirMAQLEM_MOTBB->Enabled == false && btnMAQLEM_MOTBB_PARAREMERGLOC->Caption == "Parar em Emergência"){
                        //if ( nao_atender_cmd_bba == false ) {
        			tmrPartirMAQLEM_MOTBB->Enabled = true;
                        //}
	        }
        }
	else{
		shpMAQLEM_MOTBB_PARTIR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_MAQLEM_MOTBB_PARAR) == 1 ){
                shpMAQLEM_MOTBB_PARAR->Brush->Color = clYellow;
                btnPartirMAQLEM_MOTBB->Enabled = false;
                btnPararMAQLEM_MOTBB->Enabled = false;
                tmrPartirMAQLEM_MOTBB->Enabled = false;
		if (btnMAQLEM_MOTBB_LIGADO->Caption == "Ligado"  && tmrPararMAQLEM_MOTBB->Enabled == false){
                        //if ( nao_atender_cmd_bba == false ) {
        			tmrPararMAQLEM_MOTBB->Enabled = true;
                        //}
	        }
        }
	else{
		shpMAQLEM_MOTBB_PARAR->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//MAQLEM_MOTBE
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBE_LIGADO) == 1 ){
		shpMAQLEM_MOTBE_LIGADO->Brush->Color = clLime;
		btnMAQLEM_MOTBE_LIGADO->Caption = "Ligado";
                if (btnMAQLEM_MOTBE_EMREM->Caption == "Em Local" && btnMAQLEM_MOTBE_PARAREMERGLOC->Caption == "Parar em Emergência"){
                        btnPartirMAQLEM_MOTBE->Enabled = false;
                        btnPararMAQLEM_MOTBE->Enabled = true;
                }
	}
	else{
		shpMAQLEM_MOTBE_LIGADO->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_LIGADO->Caption = "Parado";
                if (btnMAQLEM_MOTBE_EMREM->Caption == "Em Local" && btnMAQLEM_MOTBE_PARAREMERGLOC->Caption == "Parar em Emergência"){
                        btnPartirMAQLEM_MOTBE->Enabled = true;
                        btnPararMAQLEM_MOTBE->Enabled = false;
                }
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBE_EMREM) == 1 ){
		shpMAQLEM_MOTBE_EMREM->Brush->Color = clNavy;
		btnMAQLEM_MOTBE_EMREM->Caption = "Em Remoto";
                btnPartirMAQLEM_MOTBE->Enabled = false;
                btnPararMAQLEM_MOTBE->Enabled = false;
	}
	else{
		shpMAQLEM_MOTBE_EMREM->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_EMREM->Caption = "Em Local";
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_MAQLEM_MOTBE_ALIMDISPON) == 1 ){
		shpMAQLEM_MOTBE_ALIMDISPON->Brush->Color = clLime;
		btnMAQLEM_MOTBE_ALIMDISPON->Caption = "Alim. Dispon.";
	}
	else{
		shpMAQLEM_MOTBE_ALIMDISPON->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_ALIMDISPON->Caption = "Alim. Não Dispon.";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBE_ALIMLOGICOK) == 1 ){
		shpMAQLEM_MOTBE_ALIMLOGICOK->Brush->Color = clLime;
		btnMAQLEM_MOTBE_ALIMLOGICOK->Caption = "Alim. Lógica OK";
	}
	else{
		shpMAQLEM_MOTBE_ALIMLOGICOK->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_ALIMLOGICOK->Caption = "Sem Alim. Lógica";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBE_FALTADEFASE) == 1 ){
		shpMAQLEM_MOTBE_FALTADEFASE->Brush->Color = clYellow;
		btnMAQLEM_MOTBE_FALTADEFASE->Caption = "Falta de Fase";
	}
	else{
		shpMAQLEM_MOTBE_FALTADEFASE->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_FALTADEFASE->Caption = "Sem Falta de Fase";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBE_EMSOBREC) == 1 ){
		shpMAQLEM_MOTBE_EMSOBREC->Brush->Color = clRed;
		btnMAQLEM_MOTBE_EMSOBREC->Caption = "Em Sobrecarga";
	}
	else{
		shpMAQLEM_MOTBE_EMSOBREC->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_EMSOBREC->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_MAQLEM_MOTBE_DESUMLIG) == 1 ){
		shpMAQLEM_MOTBE_DESUMLIG->Brush->Color = clRed;
		btnMAQLEM_MOTBE_DESUMLIG->Caption = "Desum. Lig.";
	}
	else{
		shpMAQLEM_MOTBE_DESUMLIG->Brush->Color = clWhite;
		btnMAQLEM_MOTBE_DESUMLIG->Caption = "Desum. Des.";
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_MAQLEM_MOTBE_PARTIR) == 1 ){
		shpMAQLEM_MOTBE_PARTIR->Brush->Color = clLime;
                tmrPararMAQLEM_MOTBE->Enabled = false;
		if (btnMAQLEM_MOTBE_LIGADO->Caption == "Parado"  && tmrPartirMAQLEM_MOTBE->Enabled == false && btnMAQLEM_MOTBE_PARAREMERGLOC->Caption == "Parar em Emergência"){
                        //if ( nao_atender_cmd_bba == false ) {
        			tmrPartirMAQLEM_MOTBE->Enabled = true;
                        //}
	        }
        }
	else{
		shpMAQLEM_MOTBE_PARTIR->Brush->Color = clWhite;
	};
        //***********************************************************
        if ( CLP.RD(CP_HL_MAQLEM_MOTBE_PARAR) == 1 ){
                shpMAQLEM_MOTBE_PARAR->Brush->Color = clYellow;
                btnPartirMAQLEM_MOTBE->Enabled = false;
                btnPararMAQLEM_MOTBE->Enabled = false;
                tmrPartirMAQLEM_MOTBE->Enabled = false;
		if (btnMAQLEM_MOTBE_LIGADO->Caption == "Ligado"  && tmrPararMAQLEM_MOTBE->Enabled == false){
                        //if ( nao_atender_cmd_bba == false ) {
        			tmrPararMAQLEM_MOTBE->Enabled = true;
                        //}
	        }
        }
	else{
		shpMAQLEM_MOTBE_PARAR->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//========= Tanques =========
float a;
float b;
float x;
float x1;
float y1;
float x2;
float y2;
//y1 = a x1 + b
//y2 = a x2 + b

tmrOperaAutoCNOD->Enabled = operaauto_cnod;

//========= Tanques =========
//==============================================================================
//AODPG_TAOD01
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TAOD01_NIVELALTO) == 0 ){ //possui inversão
		shpTAOD01_NIVELALTO->Brush->Color = clRed;
		btnTAOD01_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTAOD01_NIVELALTO->Brush->Color = clWhite;
		btnTAOD01_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_TAOD01_TRANSBORDA) == 1 ){
		shpTAOD01_TRANSBORDA->Brush->Color = clRed;
		btnTAOD01_TRANSBORDA->Caption = "Transbordo";
	}
	else{
		shpTAOD01_TRANSBORDA->Brush->Color = clWhite;
		btnTAOD01_TRANSBORDA->Caption = "Sem Transbordo";
	};
        //***********************************************************
        lblTAOD01_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TAOD01_NIVEL);
        lblTAOD01_NIVEL->Caption = FormatFloat("0.###",lblTAOD01_NIVEL->Caption.ToDouble()) ;
        pgrTAOD01_NIVEL->Position = (((lblTAOD01_NIVEL->Caption*100)-(0*100))*(100-0))/((1.942-0)*100); //metros

        //32.161 litros  1.942 m
        x = lblTAOD01_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.100){
		y1 = 0.0;
		y2 = 333.0;
		x1 = 0.000;
		x2 = 0.100;
	}else{
		if (x > 0.100 && x <= 0.200){
			y1 = 333.0;
			y2 = 944.0;
			x1 = 0.100;
			x2 = 0.200;
		}else{
			if (x > 0.200 && x <= 0.400){
				y1 = 944.0;
				y2 = 2789.0;
				x1 = 0.200;
				x2 = 0.400;
			}else{
				if (x > 0.400 && x <= 0.600){
					y1 = 2789.0;
					y2 = 5610.0;
					x1 = 0.400;
					x2 = 0.600;
				}else{
					if (x > 0.600 && x <= 0.700){
						y1 = 5610.0;
						y2 = 7229.0;
						x1 = 0.600;
						x2 = 0.700;
					}else{
						if (x > 0.700 && x <= 0.800){
							y1 = 7229.0;
							y2 = 8999.0;
							x1 = 0.700;
							x2 = 0.800;
						}else{
							if (x > 0.800 && x <= 1.000){
								y1 = 8999.0;
								y2 = 12962.0;
								x1 = 0.800;
								x2 = 1.000;
							}else{
								if (x > 1.000 && x <= 1.200){
									y1 = 12962.0;
									y2 = 17436.0;
									x1 = 1.000;
									x2 = 1.200;
								}else{
									if (x > 1.200 && x <= 1.400){
										y1 = 17436.0;
										y2 = 22367.0;
										x1 = 1.200;
										x2 = 1.400;
									}else{
										if (x > 1.400 && x <= 1.600){
											y1 = 22367.0;
											y2 = 27705.0;
											x1 = 1.400;
											x2 = 1.600;
										}else{
											if (x > 1.600 && x <= 1.679){
												y1 = 27705.0;
												y2 = 29680.0;
												x1 = 1.600;
												x2 = 1.679;
											}else{
												if (x > 1.679 && x <= 1.761){
													y1 = 29680.0;
													y2 = 31035.0;
													x1 = 1.679;
													x2 = 1.761;
												}else{
													if (x > 1.761 && x <= 1.851){
														y1 = 31035.0;
														y2 = 31904.0;
														x1 = 1.761;
														x2 = 1.851;
													}else{
														if (x > 1.851 && x <= 1.942){
															y1 = 31904.0;
															y2 = 32161.0;
															x1 = 1.851;
															x2 = 1.942;
														}
													}
												}
											}
										}
									}
								}
							}
						}	
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTAOD01_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 31904.0;
                y2 = 32161.0;
                x1 = 1.851;
		x2 = 1.942;
                lblTAOD01_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTAOD01_NIVEL_litros->Caption = FormatFloat("0.##",lblTAOD01_NIVEL_litros->Caption.ToDouble());
        lblTAOD01_NIVEL_litros->Caption = lblTAOD01_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_TAOD02
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TAOD02_NIVELALTO) == 0 ){ //possui inversão
		shpTAOD02_NIVELALTO->Brush->Color = clRed;
		btnTAOD02_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTAOD02_NIVELALTO->Brush->Color = clWhite;
		btnTAOD02_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_TAOD02_TRANSBORDA) == 1 ){
		shpTAOD02_TRANSBORDA->Brush->Color = clRed;
		btnTAOD02_TRANSBORDA->Caption = "Transbordo";
	}
	else{
		shpTAOD02_TRANSBORDA->Brush->Color = clWhite;
		btnTAOD02_TRANSBORDA->Caption = "Sem Transbordo";
	};
        //***********************************************************
        lblTAOD02_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TAOD02_NIVEL);
        lblTAOD02_NIVEL->Caption = FormatFloat("0.###",lblTAOD02_NIVEL->Caption.ToDouble()) ;
        pgrTAOD02_NIVEL->Position = (((lblTAOD02_NIVEL->Caption*100)-(0*100))*(100-0))/((1.942-0)*100); //metros

        //32.161 litros  1.942 m
        x = lblTAOD02_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.100){
		y1 = 0.0;
		y2 = 333.0;
		x1 = 0.000;
		x2 = 0.100;
	}else{
		if (x > 0.100 && x <= 0.200){
			y1 = 333.0;
			y2 = 944.0;
			x1 = 0.100;
			x2 = 0.200;
		}else{
			if (x > 0.200 && x <= 0.400){
				y1 = 944.0;
				y2 = 2789.0;
				x1 = 0.200;
				x2 = 0.400;
			}else{
				if (x > 0.400 && x <= 0.600){
					y1 = 2789.0;
					y2 = 5610.0;
					x1 = 0.400;
					x2 = 0.600;
				}else{
					if (x > 0.600 && x <= 0.700){
						y1 = 5610.0;
						y2 = 7229.0;
						x1 = 0.600;
						x2 = 0.700;
					}else{
						if (x > 0.700 && x <= 0.800){
							y1 = 7229.0;
							y2 = 8999.0;
							x1 = 0.700;
							x2 = 0.800;
						}else{
							if (x > 0.800 && x <= 1.000){
								y1 = 8999.0;
								y2 = 12962.0;
								x1 = 0.800;
								x2 = 1.000;
							}else{
								if (x > 1.000 && x <= 1.200){
									y1 = 12962.0;
									y2 = 17436.0;
									x1 = 1.000;
									x2 = 1.200;
								}else{
									if (x > 1.200 && x <= 1.400){
										y1 = 17436.0;
										y2 = 22367.0;
										x1 = 1.200;
										x2 = 1.400;
									}else{
										if (x > 1.400 && x <= 1.600){
											y1 = 22367.0;
											y2 = 27705.0;
											x1 = 1.400;
											x2 = 1.600;
										}else{
											if (x > 1.600 && x <= 1.679){
												y1 = 27705.0;
												y2 = 29680.0;
												x1 = 1.600;
												x2 = 1.679;
											}else{
												if (x > 1.679 && x <= 1.761){
													y1 = 29680.0;
													y2 = 31035.0;
													x1 = 1.679;
													x2 = 1.761;
												}else{
													if (x > 1.761 && x <= 1.851){
														y1 = 31035.0;
														y2 = 31904.0;
														x1 = 1.761;
														x2 = 1.851;
													}else{
														if (x > 1.851 && x <= 1.942){
															y1 = 31904.0;
															y2 = 32161.0;
															x1 = 1.851;
															x2 = 1.942;
														}
													}
												}
											}
										}
									}
								}
							}
						}	
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTAOD02_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 31904.0;
                y2 = 32161.0;
                x1 = 1.851;
		x2 = 1.942;
                lblTAOD02_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTAOD02_NIVEL_litros->Caption = FormatFloat("0.##",lblTAOD02_NIVEL_litros->Caption.ToDouble());
        lblTAOD02_NIVEL_litros->Caption = lblTAOD02_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_TAOD03
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TAOD03_NIVELALTO) == 0 ){ //possui inversão
		shpTAOD03_NIVELALTO->Brush->Color = clRed;
		btnTAOD03_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTAOD03_NIVELALTO->Brush->Color = clWhite;
		btnTAOD03_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_TAOD03_TRANSBORDA) == 1 ){
		shpTAOD03_TRANSBORDA->Brush->Color = clRed;
		btnTAOD03_TRANSBORDA->Caption = "Transbordo";
	}
	else{
		shpTAOD03_TRANSBORDA->Brush->Color = clWhite;
		btnTAOD03_TRANSBORDA->Caption = "Sem Transbordo";
	};
        //***********************************************************
        lblTAOD03_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TAOD03_NIVEL);
        lblTAOD03_NIVEL->Caption = FormatFloat("0.###",lblTAOD03_NIVEL->Caption.ToDouble()) ;
        pgrTAOD03_NIVEL->Position = (((lblTAOD03_NIVEL->Caption*100)-(0*100))*(100-0))/((1.014-0)*100); //metros

        //38.325 litros  1.014 m
        x = lblTAOD03_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.100){
		y1 = 0.0;
		y2 = 972.0;
		x1 = 0.000;
		x2 = 0.100;
	}else{
		if (x > 0.100 && x <= 0.200){
			y1 = 972.0;
			y2 = 2935.0;
			x1 = 0.100;
			x2 = 0.200;
		}else{
			if (x > 0.200 && x <= 0.300){
				y1 = 2935.0;
				y2 = 5830.0;
				x1 = 0.200;
				x2 = 0.300;
			}else{
				if (x > 0.300 && x <= 0.400){
					y1 = 5830.0;
					y2 = 9542.0;
					x1 = 0.300;
					x2 = 0.400;
				}else{
					if (x > 0.400 && x <= 0.497){
						y1 = 9542.0;
						y2 = 13774.0;
						x1 = 0.400;
						x2 = 0.497;
					}else{
						if (x > 0.497 && x <= 0.500){
							y1 = 13774.0;
							y2 = 13934.0;
							x1 = 0.497;
							x2 = 0.500;
						}else{
							if (x > 0.500 && x <= 0.506){
								y1 = 13934.0;
								y2 = 14204.0;
								x1 = 0.500;
								x2 = 0.506;
							}else{
								if (x > 0.506 && x <= 0.517){
									y1 = 14204.0;
									y2 = 14747.0;
									x1 = 0.506;
									x2 = 0.517;
								}else{
									if (x > 0.517 && x <= 0.530){
										y1 = 14747.0;
										y2 = 15343.0;
										x1 = 0.517;
										x2 = 0.530;
									}else{
										if (x > 0.530 && x <= 1.000){
											y1 = 15343.0;
											y2 = 38325.0;
											x1 = 0.530;
											x2 = 1.000;
										}
									}
								}
							}
						}	
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTAOD03_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 15343.0;
                y2 = 38325.0;
                x1 = 0.530;
                x2 = 1.000;
                lblTAOD03_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTAOD03_NIVEL_litros->Caption = FormatFloat("0.##",lblTAOD03_NIVEL_litros->Caption.ToDouble());
        lblTAOD03_NIVEL_litros->Caption = lblTAOD03_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_TAOD04
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TAOD04_NIVELALTO) == 0 ){ //possui inversão
		shpTAOD04_NIVELALTO->Brush->Color = clRed;
		btnTAOD04_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTAOD04_NIVELALTO->Brush->Color = clWhite;
		btnTAOD04_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_TAOD04_TRANSBORDA) == 1 ){
		shpTAOD04_TRANSBORDA->Brush->Color = clRed;
		btnTAOD04_TRANSBORDA->Caption = "Transbordo";
	}
	else{
		shpTAOD04_TRANSBORDA->Brush->Color = clWhite;
		btnTAOD04_TRANSBORDA->Caption = "Sem Transbordo";
	};
        //***********************************************************
        lblTAOD04_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TAOD04_NIVEL);
        lblTAOD04_NIVEL->Caption = FormatFloat("0.###",lblTAOD04_NIVEL->Caption.ToDouble()) ;
        pgrTAOD04_NIVEL->Position = (((lblTAOD04_NIVEL->Caption*100)-(0*100))*(100-0))/((2.810-0)*100); //metros

        //37.156 litros  2.810 m
        x = lblTAOD04_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.365){
		y1 = 0.0;
		y2 = 207.0;
		x1 = 0.000;
		x2 = 0.365;
	}else{
		if (x > 0.365 && x <= 0.665){
			y1 = 207.0;
			y2 = 856.0;
			x1 = 0.365;
			x2 = 0.665;
		}else{
			if (x > 0.665 && x <= 0.865){
				y1 = 856.0;
				y2 = 1735.0;
				x1 = 0.665;
				x2 = 0.865;
			}else{
				if (x > 0.865 && x <= 0.965){
					y1 = 1735.0;
					y2 = 2367.0;
					x1 = 0.865;
					x2 = 0.965;
				}else{
					if (x > 0.965 && x <= 1.065){
						y1 = 2367.0;
						y2 = 3170.0;
						x1 = 0.965;
						x2 = 1.065;
					}else{
						if (x > 1.065 && x <= 1.210){
							y1 = 3170.0;
							y2 = 4706.0;
							x1 = 1.065;
							x2 = 1.210;
						}else{
							if (x > 1.210 && x <= 1.365){
								y1 = 4706.0;
								y2 = 6925.0;
								x1 = 1.210;
								x2 = 1.365;
							}else{
								if (x > 1.365 && x <= 1.465){
									y1 = 6925.0;
									y2 = 8637.0;
									x1 = 1.365;
									x2 = 1.465;
								}else{
									if (x > 1.465 && x <= 1.565){
										y1 = 8637.0;
										y2 = 10538.0;
										x1 = 1.465;
										x2 = 1.565;
									}else{
										if (x > 1.565 && x <= 1.665){
											y1 = 10538.0;
											y2 = 12603.0;
											x1 = 1.565;
											x2 = 1.665;
										}else{
											if (x > 1.665 && x <= 1.865){
												y1 = 12603.0;
												y2 = 17149.0;
												x1 = 1.665;
												x2 = 1.865;
											}else{
												if (x > 1.865 && x <= 2.065){
													y1 = 17149.0;
													y2 = 22022.0;
													x1 = 1.865;
													x2 = 2.065;
												}else{
													if (x > 2.065 && x <= 2.665){
														y1 = 22022.0;
														y2 = 37156.0;
														x1 = 2.065;
														x2 = 2.665;
													}
												}
											}
										}
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
      	lblTAOD04_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 22022.0;
                y2 = 37156.0;
                x1 = 2.065;
                x2 = 2.665;
                lblTAOD04_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTAOD04_NIVEL_litros->Caption = FormatFloat("0.##",lblTAOD04_NIVEL_litros->Caption.ToDouble());
        lblTAOD04_NIVEL_litros->Caption = lblTAOD04_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_TAOD05
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TAOD05_NIVELALTO) == 0 ){ //possui inversão
		shpTAOD05_NIVELALTO->Brush->Color = clRed;
		btnTAOD05_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTAOD05_NIVELALTO->Brush->Color = clWhite;
		btnTAOD05_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_TAOD05_TRANSBORDA) == 1 ){
		shpTAOD05_TRANSBORDA->Brush->Color = clRed;
		btnTAOD05_TRANSBORDA->Caption = "Transbordo";
	}
	else{
		shpTAOD05_TRANSBORDA->Brush->Color = clWhite;
		btnTAOD05_TRANSBORDA->Caption = "Sem Transbordo";
	};
        //***********************************************************
        lblTAOD05_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TAOD05_NIVEL);
        lblTAOD05_NIVEL->Caption = FormatFloat("0.###",lblTAOD05_NIVEL->Caption.ToDouble()) ;
        pgrTAOD05_NIVEL->Position = (((lblTAOD05_NIVEL->Caption*100)-(0*100))*(100-0))/((2.555-0)*100); //metros

        //41.039 litros  2.555 m
        x = lblTAOD05_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.055){
		y1 = 0.0;
		y2 = 100.0;
		x1 = 0.000;
		x2 = 0.055;
	}else{
		if (x > 0.055 && x <= 0.155){
			y1 = 100.0;
			y2 = 170.0;
			x1 = 0.055;
			x2 = 0.155;
		}else{
			if (x > 0.155 && x <= 0.355){
				y1 = 170.0;
				y2 = 209.0;
				x1 = 0.155;
				x2 = 0.355;
			}else{
				if (x > 0.355 && x <= 0.455){
					y1 = 209.0;
					y2 = 456.0;
					x1 = 0.355;
					x2 = 0.455;
				}else{
					if (x > 0.455 && x <= 0.555){
						y1 = 456.0;
						y2 = 857.0;
						x1 = 0.455;
						x2 = 0.555;
					}else{
						if (x > 0.555 && x <= 0.655){
							y1 = 857.0;
							y2 = 1461.0;
							x1 = 0.555;
							x2 = 0.655;
						}else{
							if (x > 0.655 && x <= 0.755){
								y1 = 1461.0;
								y2 = 2299.0;
								x1 = 0.655;
								x2 = 0.755;
							}else{
								if (x > 0.755 && x <= 0.889){
									y1 = 2299.0;
									y2 = 3838.0;
									x1 = 0.755;
									x2 = 0.889;
								}else{
									if (x > 0.889 && x <= 0.955){
										y1 = 3838.0;
										y2 = 4771.0;
										x1 = 0.889;
										x2 = 0.955;
									}else{
										if (x > 0.955 && x <= 1.055){
											y1 = 4771.0;
											y2 = 6424.0;
											x1 = 0.955;
											x2 = 1.055;
										}else{
											if (x > 1.055 && x <= 1.155){
												y1 = 6424.0;
												y2 = 8306.0;
												x1 = 1.055;
												x2 = 1.155;
											}else{
												if (x > 1.155 && x <= 1.355){
													y1 = 8306.0;
													y2 = 12475.0;
													x1 = 1.155;
													x2 = 1.355;
												}else{
													if (x > 1.355 && x <= 1.655){
														y1 = 12475.0;
														y2 = 19227.0;
														x1 = 1.355;
														x2 = 1.655;
													}else{
													        if (x > 1.655 && x <= 2.055){
														        y1 = 19227.0;
        														y2 = 28729.0;
	        													x1 = 1.655;
		        												x2 = 2.055;
			        										}else{
                                                                                                                        if (x > 2.055 && x <= 2.555){
                                                                                                                                y1 = 28729.0;
        													        	y2 = 41039.0;
	        												        	x1 = 2.055;
		        											        	x2 = 2.555;
                                                                                                                        }
                                                                                                                }
                                                                                                        }
                                                                                                }
											}
										}
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
      	lblTAOD05_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 28729.0;
                y2 = 41039.0;
                x1 = 2.055;
                x2 = 2.555;
                lblTAOD05_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTAOD05_NIVEL_litros->Caption = FormatFloat("0.##",lblTAOD05_NIVEL_litros->Caption.ToDouble());
        lblTAOD05_NIVEL_litros->Caption = lblTAOD05_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_TAOD06
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TAOD06_NIVELALTO) == 0 ){ //possui inversão
		shpTAOD06_NIVELALTO->Brush->Color = clRed;
		btnTAOD06_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTAOD06_NIVELALTO->Brush->Color = clWhite;
		btnTAOD06_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_TAOD06_TRANSBORDA) == 1 ){
		shpTAOD06_TRANSBORDA->Brush->Color = clRed;
		btnTAOD06_TRANSBORDA->Caption = "Transbordo";
	}
	else{
		shpTAOD06_TRANSBORDA->Brush->Color = clWhite;
		btnTAOD06_TRANSBORDA->Caption = "Sem Transbordo";
	};
        //***********************************************************
        lblTAOD06_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TAOD06_NIVEL);
        lblTAOD06_NIVEL->Caption = FormatFloat("0.###",lblTAOD06_NIVEL->Caption.ToDouble()) ;
        pgrTAOD06_NIVEL->Position = (((lblTAOD06_NIVEL->Caption*100)-(0*100))*(100-0))/((2.555-0)*100); //metros

        //41.039 litros  2.555 m
        x = lblTAOD06_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.055){
		y1 = 0.0;
		y2 = 100.0;
		x1 = 0.000;
		x2 = 0.055;
	}else{
		if (x > 0.055 && x <= 0.155){
			y1 = 100.0;
			y2 = 170.0;
			x1 = 0.055;
			x2 = 0.155;
		}else{
			if (x > 0.155 && x <= 0.355){
				y1 = 170.0;
				y2 = 209.0;
				x1 = 0.155;
				x2 = 0.355;
			}else{
				if (x > 0.355 && x <= 0.455){
					y1 = 209.0;
					y2 = 456.0;
					x1 = 0.355;
					x2 = 0.455;
				}else{
					if (x > 0.455 && x <= 0.555){
						y1 = 456.0;
						y2 = 857.0;
						x1 = 0.455;
						x2 = 0.555;
					}else{
						if (x > 0.555 && x <= 0.655){
							y1 = 857.0;
							y2 = 1461.0;
							x1 = 0.555;
							x2 = 0.655;
						}else{
							if (x > 0.655 && x <= 0.755){
								y1 = 1461.0;
								y2 = 2299.0;
								x1 = 0.655;
								x2 = 0.755;
							}else{
								if (x > 0.755 && x <= 0.889){
									y1 = 2299.0;
									y2 = 3838.0;
									x1 = 0.755;
									x2 = 0.889;
								}else{
									if (x > 0.889 && x <= 0.955){
										y1 = 3838.0;
										y2 = 4771.0;
										x1 = 0.889;
										x2 = 0.955;
									}else{
										if (x > 0.955 && x <= 1.055){
											y1 = 4771.0;
											y2 = 6424.0;
											x1 = 0.955;
											x2 = 1.055;
										}else{
											if (x > 1.055 && x <= 1.155){
												y1 = 6424.0;
												y2 = 8306.0;
												x1 = 1.055;
												x2 = 1.155;
											}else{
												if (x > 1.155 && x <= 1.355){
													y1 = 8306.0;
													y2 = 12475.0;
													x1 = 1.155;
													x2 = 1.355;
												}else{
													if (x > 1.355 && x <= 1.655){
														y1 = 12475.0;
														y2 = 19227.0;
														x1 = 1.355;
														x2 = 1.655;
													}else{
													        if (x > 1.655 && x <= 2.055){
														        y1 = 19227.0;
        														y2 = 28729.0;
	        													x1 = 1.655;
		        												x2 = 2.055;
			        										}else{
                                                                                                                        if (x > 2.055 && x <= 2.555){
                                                                                                                                y1 = 28729.0;
        													        	y2 = 41039.0;
	        												        	x1 = 2.055;
		        											        	x2 = 2.555;
                                                                                                                        }
                                                                                                                }
                                                                                                        }
                                                                                                }
											}
										}
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
      	lblTAOD06_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 28729.0;
                y2 = 41039.0;
                x1 = 2.055;
                x2 = 2.555;
                lblTAOD06_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTAOD06_NIVEL_litros->Caption = FormatFloat("0.##",lblTAOD06_NIVEL_litros->Caption.ToDouble());
        lblTAOD06_NIVEL_litros->Caption = lblTAOD06_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_VOD012
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD012_FECHADO) == 1) {
                btnVOD012_FECHADO->Caption = "Fechada";
                shpVOD012_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD012_FECHADO->Caption = "Não Fechada";
                shpVOD012_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD012_ABERTO) == 1) {
                btnVOD012_ABERTO->Caption = "Aberta";
                shpVOD012_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD012_ABERTO->Caption = "Não Aberta";
                shpVOD012_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD012_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD012_ABRIR) == 1) {
                        shpVOD012_ABRIR->Brush->Color = clRed;
                        if (btnVOD012_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 0);
                        }
                        if (btnVOD012_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD012_ABERTO, 1);
                        }
                }else{
                        shpVOD012_ABRIR->Brush->Color = clWhite;
                        if ( VOD012_RetornoAuto == true) {
                                if (btnVOD012_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD012_ABERTO, 0);
                                }
                                if (btnVOD012_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD012_ABERTO->Enabled  = VOD012_ModoOpera;
        btnVOD012_FECHADO->Enabled = VOD012_ModoOpera;
        btnVOD012_ABRIR->Enabled   = VOD012_ModoOpera;
        btnVOD012_FECHAR->Enabled  = VOD012_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD013
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD013_FECHADO) == 1) {
                btnVOD013_FECHADO->Caption = "Fechada";
                shpVOD013_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD013_FECHADO->Caption = "Não Fechada";
                shpVOD013_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD013_ABERTO) == 1) {
                btnVOD013_ABERTO->Caption = "Aberta";
                shpVOD013_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD013_ABERTO->Caption = "Não Aberta";
                shpVOD013_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD013_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD013_ABRIR) == 1) {
                        shpVOD013_ABRIR->Brush->Color = clRed;
                        if (btnVOD013_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 0);
                        }
                        if (btnVOD013_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD013_ABERTO, 1);
                        }
                }else{
                        shpVOD013_ABRIR->Brush->Color = clWhite;
                        if ( VOD013_RetornoAuto == true) {
                                if (btnVOD013_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD013_ABERTO, 0);
                                }
                                if (btnVOD013_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD013_ABERTO->Enabled  = VOD013_ModoOpera;
        btnVOD013_FECHADO->Enabled = VOD013_ModoOpera;
        btnVOD013_ABRIR->Enabled   = VOD013_ModoOpera;
        btnVOD013_FECHAR->Enabled  = VOD013_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD014
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD014_FECHADO) == 1) {
                btnVOD014_FECHADO->Caption = "Fechada";
                shpVOD014_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD014_FECHADO->Caption = "Não Fechada";
                shpVOD014_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD014_ABERTO) == 1) {
                btnVOD014_ABERTO->Caption = "Aberta";
                shpVOD014_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD014_ABERTO->Caption = "Não Aberta";
                shpVOD014_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD014_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD014_ABRIR) == 1) {
                        shpVOD014_ABRIR->Brush->Color = clRed;
                        if (btnVOD014_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 0);
                        }
                        if (btnVOD014_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD014_ABERTO, 1);
                        }
                }else{
                        shpVOD014_ABRIR->Brush->Color = clWhite;
                        if ( VOD014_RetornoAuto == true) {
                                if (btnVOD014_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD014_ABERTO, 0);
                                }
                                if (btnVOD014_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD014_ABERTO->Enabled  = VOD014_ModoOpera;
        btnVOD014_FECHADO->Enabled = VOD014_ModoOpera;
        btnVOD014_ABRIR->Enabled   = VOD014_ModoOpera;
        btnVOD014_FECHAR->Enabled  = VOD014_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD015
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD015_FECHADO) == 1) {
                btnVOD015_FECHADO->Caption = "Fechada";
                shpVOD015_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD015_FECHADO->Caption = "Não Fechada";
                shpVOD015_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD015_ABERTO) == 1) {
                btnVOD015_ABERTO->Caption = "Aberta";
                shpVOD015_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD015_ABERTO->Caption = "Não Aberta";
                shpVOD015_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD015_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD015_ABRIR) == 1) {
                        shpVOD015_ABRIR->Brush->Color = clRed;
                        if (btnVOD015_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 0);
                        }
                        if (btnVOD015_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD015_ABERTO, 1);
                        }
                }else{
                        shpVOD015_ABRIR->Brush->Color = clWhite;
                        if ( VOD015_RetornoAuto == true) {
                                if (btnVOD015_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD015_ABERTO, 0);
                                }
                                if (btnVOD015_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD015_ABERTO->Enabled  = VOD015_ModoOpera;
        btnVOD015_FECHADO->Enabled = VOD015_ModoOpera;
        btnVOD015_ABRIR->Enabled   = VOD015_ModoOpera;
        btnVOD015_FECHAR->Enabled  = VOD015_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD016
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD016_FECHADO) == 1) {
                btnVOD016_FECHADO->Caption = "Fechada";
                shpVOD016_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD016_FECHADO->Caption = "Não Fechada";
                shpVOD016_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD016_ABERTO) == 1) {
                btnVOD016_ABERTO->Caption = "Aberta";
                shpVOD016_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD016_ABERTO->Caption = "Não Aberta";
                shpVOD016_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD016_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD016_ABRIR) == 1) {
                        shpVOD016_ABRIR->Brush->Color = clRed;
                        if (btnVOD016_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 0);
                        }
                        if (btnVOD016_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD016_ABERTO, 1);
                        }
                }else{
                        shpVOD016_ABRIR->Brush->Color = clWhite;
                        if ( VOD016_RetornoAuto == true) {
                                if (btnVOD016_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD016_ABERTO, 0);
                                }
                                if (btnVOD016_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD016_ABERTO->Enabled  = VOD016_ModoOpera;
        btnVOD016_FECHADO->Enabled = VOD016_ModoOpera;
        btnVOD016_ABRIR->Enabled   = VOD016_ModoOpera;
        btnVOD016_FECHAR->Enabled  = VOD016_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD017
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD017_FECHADO) == 1) {
                btnVOD017_FECHADO->Caption = "Fechada";
                shpVOD017_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD017_FECHADO->Caption = "Não Fechada";
                shpVOD017_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD017_ABERTO) == 1) {
                btnVOD017_ABERTO->Caption = "Aberta";
                shpVOD017_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD017_ABERTO->Caption = "Não Aberta";
                shpVOD017_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD017_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD017_ABRIR) == 1) {
                        shpVOD017_ABRIR->Brush->Color = clRed;
                        if (btnVOD017_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 0);
                        }
                        if (btnVOD017_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD017_ABERTO, 1);
                        }
                }else{
                        shpVOD017_ABRIR->Brush->Color = clWhite;
                        if ( VOD017_RetornoAuto == true) {
                                if (btnVOD017_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD017_ABERTO, 0);
                                }
                                if (btnVOD017_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD017_ABERTO->Enabled  = VOD017_ModoOpera;
        btnVOD017_FECHADO->Enabled = VOD017_ModoOpera;
        btnVOD017_ABRIR->Enabled   = VOD017_ModoOpera;
        btnVOD017_FECHAR->Enabled  = VOD017_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD059
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD059_FECHADO) == 1) {
                btnVOD059_FECHADO->Caption = "Fechada";
                shpVOD059_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD059_FECHADO->Caption = "Não Fechada";
                shpVOD059_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD059_ABERTO) == 1) {
                btnVOD059_ABERTO->Caption = "Aberta";
                shpVOD059_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD059_ABERTO->Caption = "Não Aberta";
                shpVOD059_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD059_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD059_ABRIR) == 1) {
                        shpVOD059_ABRIR->Brush->Color = clRed;
                        if (btnVOD059_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 0);
                        }
                        if (btnVOD059_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD059_ABERTO, 1);
                        }
                }else{
                        shpVOD059_ABRIR->Brush->Color = clWhite;
                        if ( VOD059_RetornoAuto == true) {
                                if (btnVOD059_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD059_ABERTO, 0);
                                }
                                if (btnVOD059_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD059_ABERTO->Enabled  = VOD059_ModoOpera;
        btnVOD059_FECHADO->Enabled = VOD059_ModoOpera;
        btnVOD059_ABRIR->Enabled   = VOD059_ModoOpera;
        btnVOD059_FECHAR->Enabled  = VOD059_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD060
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD060_FECHADO) == 1) {
                btnVOD060_FECHADO->Caption = "Fechada";
                shpVOD060_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD060_FECHADO->Caption = "Não Fechada";
                shpVOD060_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD060_ABERTO) == 1) {
                btnVOD060_ABERTO->Caption = "Aberta";
                shpVOD060_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD060_ABERTO->Caption = "Não Aberta";
                shpVOD060_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD060_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD060_ABRIR) == 1) {
                        shpVOD060_ABRIR->Brush->Color = clRed;
                        if (btnVOD060_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 0);
                        }
                        if (btnVOD060_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD060_ABERTO, 1);
                        }
                }else{
                        shpVOD060_ABRIR->Brush->Color = clWhite;
                        if ( VOD060_RetornoAuto == true) {
                                if (btnVOD060_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD060_ABERTO, 0);
                                }
                                if (btnVOD060_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD060_ABERTO->Enabled  = VOD060_ModoOpera;
        btnVOD060_FECHADO->Enabled = VOD060_ModoOpera;
        btnVOD060_ABRIR->Enabled   = VOD060_ModoOpera;
        btnVOD060_FECHAR->Enabled  = VOD060_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD061
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD061_FECHADO) == 1) {
                btnVOD061_FECHADO->Caption = "Fechada";
                shpVOD061_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD061_FECHADO->Caption = "Não Fechada";
                shpVOD061_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD061_ABERTO) == 1) {
                btnVOD061_ABERTO->Caption = "Aberta";
                shpVOD061_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD061_ABERTO->Caption = "Não Aberta";
                shpVOD061_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD061_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD061_ABRIR) == 1) {
                        shpVOD061_ABRIR->Brush->Color = clRed;
                        if (btnVOD061_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 0);
                        }
                        if (btnVOD061_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD061_ABERTO, 1);
                        }
                }else{
                        shpVOD061_ABRIR->Brush->Color = clWhite;
                        if ( VOD061_RetornoAuto == true) {
                                if (btnVOD061_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD061_ABERTO, 0);
                                }
                                if (btnVOD061_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD061_ABERTO->Enabled  = VOD061_ModoOpera;
        btnVOD061_FECHADO->Enabled = VOD061_ModoOpera;
        btnVOD061_ABRIR->Enabled   = VOD061_ModoOpera;
        btnVOD061_FECHAR->Enabled  = VOD061_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD062
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD062_FECHADO) == 1) {
                btnVOD062_FECHADO->Caption = "Fechada";
                shpVOD062_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD062_FECHADO->Caption = "Não Fechada";
                shpVOD062_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD062_ABERTO) == 1) {
                btnVOD062_ABERTO->Caption = "Aberta";
                shpVOD062_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD062_ABERTO->Caption = "Não Aberta";
                shpVOD062_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD062_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD062_ABRIR) == 1) {
                        shpVOD062_ABRIR->Brush->Color = clRed;
                        if (btnVOD062_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 0);
                        }
                        if (btnVOD062_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD062_ABERTO, 1);
                        }
                }else{
                        shpVOD062_ABRIR->Brush->Color = clWhite;
                        if ( VOD062_RetornoAuto == true) {
                                if (btnVOD062_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD062_ABERTO, 0);
                                }
                                if (btnVOD062_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD062_ABERTO->Enabled  = VOD062_ModoOpera;
        btnVOD062_FECHADO->Enabled = VOD062_ModoOpera;
        btnVOD062_ABRIR->Enabled   = VOD062_ModoOpera;
        btnVOD062_FECHAR->Enabled  = VOD062_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD063
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD063_FECHADO) == 1) {
                btnVOD063_FECHADO->Caption = "Fechada";
                shpVOD063_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD063_FECHADO->Caption = "Não Fechada";
                shpVOD063_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD063_ABERTO) == 1) {
                btnVOD063_ABERTO->Caption = "Aberta";
                shpVOD063_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD063_ABERTO->Caption = "Não Aberta";
                shpVOD063_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD063_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD063_ABRIR) == 1) {
                        shpVOD063_ABRIR->Brush->Color = clRed;
                        if (btnVOD063_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 0);
                        }
                        if (btnVOD063_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD063_ABERTO, 1);
                        }
                }else{
                        shpVOD063_ABRIR->Brush->Color = clWhite;
                        if ( VOD063_RetornoAuto == true) {
                                if (btnVOD063_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD063_ABERTO, 0);
                                }
                                if (btnVOD063_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD063_ABERTO->Enabled  = VOD063_ModoOpera;
        btnVOD063_FECHADO->Enabled = VOD063_ModoOpera;
        btnVOD063_ABRIR->Enabled   = VOD063_ModoOpera;
        btnVOD063_FECHAR->Enabled  = VOD063_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD064
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD064_FECHADO) == 1) {
                btnVOD064_FECHADO->Caption = "Fechada";
                shpVOD064_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD064_FECHADO->Caption = "Não Fechada";
                shpVOD064_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD064_ABERTO) == 1) {
                btnVOD064_ABERTO->Caption = "Aberta";
                shpVOD064_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD064_ABERTO->Caption = "Não Aberta";
                shpVOD064_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD064_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD064_ABRIR) == 1) {
                        shpVOD064_ABRIR->Brush->Color = clRed;
                        if (btnVOD064_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 0);
                        }
                        if (btnVOD064_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD064_ABERTO, 1);
                        }
                }else{
                        shpVOD064_ABRIR->Brush->Color = clWhite;
                        if ( VOD064_RetornoAuto == true) {
                                if (btnVOD064_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_AODPG_VOD064_ABERTO, 0);
                                }
                                if (btnVOD064_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD064_ABERTO->Enabled  = VOD064_ModoOpera;
        btnVOD064_FECHADO->Enabled = VOD064_ModoOpera;
        btnVOD064_ABRIR->Enabled   = VOD064_ModoOpera;
        btnVOD064_FECHAR->Enabled  = VOD064_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD005
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD005_FECHADO) == 1) {
                btnVOD005_FECHADO->Caption = "Fechada";
                shpVOD005_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD005_FECHADO->Caption = "Não Fechada";
                shpVOD005_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD005_ABERTO) == 1) {
                btnVOD005_ABERTO->Caption = "Aberta";
                shpVOD005_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD005_ABERTO->Caption = "Não Aberta";
                shpVOD005_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD005_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD005_ABRIR) == 1) {
                        shpVOD005_ABRIR->Brush->Color = clRed;
                        if (btnVOD005_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 0);
                        }
                        if (btnVOD005_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD005_ABERTO, 1);
                        }
                }else{
                        shpVOD005_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD005_FECHAR) == 1) {
                        shpVOD005_FECHAR->Brush->Color = clLime;
                        if (btnVOD005_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD005_ABERTO, 0);
                        }
                        if (btnVOD005_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 1);
                        }
                }else{
                        shpVOD005_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD005_ABERTO->Enabled  = VOD005_ModoOpera;
        btnVOD005_FECHADO->Enabled = VOD005_ModoOpera;
        btnVOD005_ABRIR->Enabled   = VOD005_ModoOpera;
        btnVOD005_FECHAR->Enabled  = VOD005_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD010
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD010_FECHADO) == 1) {
                btnVOD010_FECHADO->Caption = "Fechada";
                shpVOD010_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD010_FECHADO->Caption = "Não Fechada";
                shpVOD010_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD010_ABERTO) == 1) {
                btnVOD010_ABERTO->Caption = "Aberta";
                shpVOD010_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD010_ABERTO->Caption = "Não Aberta";
                shpVOD010_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD010_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD010_ABRIR) == 1) {
                        shpVOD010_ABRIR->Brush->Color = clRed;
                        if (btnVOD010_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 0);
                        }
                        if (btnVOD010_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD010_ABERTO, 1);
                        }
                }else{
                        shpVOD010_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD010_FECHAR) == 1) {
                        shpVOD010_FECHAR->Brush->Color = clLime;
                        if (btnVOD010_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD010_ABERTO, 0);
                        }
                        if (btnVOD010_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 1);
                        }
                }else{
                        shpVOD010_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD010_ABERTO->Enabled  = VOD010_ModoOpera;
        btnVOD010_FECHADO->Enabled = VOD010_ModoOpera;
        btnVOD010_ABRIR->Enabled   = VOD010_ModoOpera;
        btnVOD010_FECHAR->Enabled  = VOD010_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD030
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD030_FECHADO) == 1) {
                btnVOD030_FECHADO->Caption = "Fechada";
                shpVOD030_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD030_FECHADO->Caption = "Não Fechada";
                shpVOD030_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD030_ABERTO) == 1) {
                btnVOD030_ABERTO->Caption = "Aberta";
                shpVOD030_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD030_ABERTO->Caption = "Não Aberta";
                shpVOD030_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD030_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD030_ABRIR) == 1) {
                        shpVOD030_ABRIR->Brush->Color = clRed;
                        if (btnVOD030_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 0);
                        }
                        if (btnVOD030_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD030_ABERTO, 1);
                        }
                }else{
                        shpVOD030_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD030_FECHAR) == 1) {
                        shpVOD030_FECHAR->Brush->Color = clLime;
                        if (btnVOD030_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD030_ABERTO, 0);
                        }
                        if (btnVOD030_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 1);
                        }
                }else{
                        shpVOD030_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD030_ABERTO->Enabled  = VOD030_ModoOpera;
        btnVOD030_FECHADO->Enabled = VOD030_ModoOpera;
        btnVOD030_ABRIR->Enabled   = VOD030_ModoOpera;
        btnVOD030_FECHAR->Enabled  = VOD030_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD031
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD031_FECHADO) == 1) {
                btnVOD031_FECHADO->Caption = "Fechada";
                shpVOD031_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD031_FECHADO->Caption = "Não Fechada";
                shpVOD031_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD031_ABERTO) == 1) {
                btnVOD031_ABERTO->Caption = "Aberta";
                shpVOD031_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD031_ABERTO->Caption = "Não Aberta";
                shpVOD031_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD031_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD031_ABRIR) == 1) {
                        shpVOD031_ABRIR->Brush->Color = clRed;
                        if (btnVOD031_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 0);
                        }
                        if (btnVOD031_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD031_ABERTO, 1);
                        }
                }else{
                        shpVOD031_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD031_FECHAR) == 1) {
                        shpVOD031_FECHAR->Brush->Color = clLime;
                        if (btnVOD031_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD031_ABERTO, 0);
                        }
                        if (btnVOD031_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 1);
                        }
                }else{
                        shpVOD031_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD031_ABERTO->Enabled  = VOD031_ModoOpera;
        btnVOD031_FECHADO->Enabled = VOD031_ModoOpera;
        btnVOD031_ABRIR->Enabled   = VOD031_ModoOpera;
        btnVOD031_FECHAR->Enabled  = VOD031_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD035
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD035_FECHADO) == 1) {
                btnVOD035_FECHADO->Caption = "Fechada";
                shpVOD035_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD035_FECHADO->Caption = "Não Fechada";
                shpVOD035_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD035_ABERTO) == 1) {
                btnVOD035_ABERTO->Caption = "Aberta";
                shpVOD035_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD035_ABERTO->Caption = "Não Aberta";
                shpVOD035_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD035_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD035_ABRIR) == 1) {
                        shpVOD035_ABRIR->Brush->Color = clRed;
                        if (btnVOD035_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 0);
                        }
                        if (btnVOD035_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD035_ABERTO, 1);
                        }
                }else{
                        shpVOD035_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD035_FECHAR) == 1) {
                        shpVOD035_FECHAR->Brush->Color = clLime;
                        if (btnVOD035_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD035_ABERTO, 0);
                        }
                        if (btnVOD035_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 1);
                        }
                }else{
                        shpVOD035_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD035_ABERTO->Enabled  = VOD035_ModoOpera;
        btnVOD035_FECHADO->Enabled = VOD035_ModoOpera;
        btnVOD035_ABRIR->Enabled   = VOD035_ModoOpera;
        btnVOD035_FECHAR->Enabled  = VOD035_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD043
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD043_FECHADO) == 1) {
                btnVOD043_FECHADO->Caption = "Fechada";
                shpVOD043_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD043_FECHADO->Caption = "Não Fechada";
                shpVOD043_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD043_ABERTO) == 1) {
                btnVOD043_ABERTO->Caption = "Aberta";
                shpVOD043_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD043_ABERTO->Caption = "Não Aberta";
                shpVOD043_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD043_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD043_ABRIR) == 1) {
                        shpVOD043_ABRIR->Brush->Color = clRed;
                        if (btnVOD043_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 0);
                        }
                        if (btnVOD043_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD043_ABERTO, 1);
                        }
                }else{
                        shpVOD043_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD043_FECHAR) == 1) {
                        shpVOD043_FECHAR->Brush->Color = clLime;
                        if (btnVOD043_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD043_ABERTO, 0);
                        }
                        if (btnVOD043_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 1);
                        }
                }else{
                        shpVOD043_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD043_ABERTO->Enabled  = VOD043_ModoOpera;
        btnVOD043_FECHADO->Enabled = VOD043_ModoOpera;
        btnVOD043_ABRIR->Enabled   = VOD043_ModoOpera;
        btnVOD043_FECHAR->Enabled  = VOD043_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_VOD066
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD066_FECHADO) == 1) {
                btnVOD066_FECHADO->Caption = "Fechada";
                shpVOD066_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD066_FECHADO->Caption = "Não Fechada";
                shpVOD066_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_AODPG_VOD066_ABERTO) == 1) {
                btnVOD066_ABERTO->Caption = "Aberta";
                shpVOD066_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD066_ABERTO->Caption = "Não Aberta";
                shpVOD066_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD066_ModoOpera == false){
                if (CLP.RD(CP_HL_AODPG_VOD066_ABRIR) == 1) {
                        shpVOD066_ABRIR->Brush->Color = clRed;
                        if (btnVOD066_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 0);
                        }
                        if (btnVOD066_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD066_ABERTO, 1);
                        }
                }else{
                        shpVOD066_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_AODPG_VOD066_FECHAR) == 1) {
                        shpVOD066_FECHAR->Brush->Color = clLime;
                        if (btnVOD066_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_AODPG_VOD066_ABERTO, 0);
                        }
                        if (btnVOD066_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 1);
                        }
                }else{
                        shpVOD066_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD066_ABERTO->Enabled  = VOD066_ModoOpera;
        btnVOD066_FECHADO->Enabled = VOD066_ModoOpera;
        btnVOD066_ABRIR->Enabled   = VOD066_ModoOpera;
        btnVOD066_FECHAR->Enabled  = VOD066_ModoOpera;
        //***********************************************************
//==============================================================================
//AODPG_TTOD12
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TTOD12_NIVELALTO) == 0 ){ //possui inversão
		shpTTOD12_NIVELALTO->Brush->Color = clRed;
		btnTTOD12_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTTOD12_NIVELALTO->Brush->Color = clWhite;
		btnTTOD12_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        lblTTOD12_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TTOD12_NIVEL);
        lblTTOD12_NIVEL->Caption = FormatFloat("0.###",lblTTOD12_NIVEL->Caption.ToDouble()) ;
        pgrTTOD12_NIVEL->Position = (((lblTTOD12_NIVEL->Caption*100)-(0*100))*(100-0))/((1.00-0)*100); //metros

        //5.842 litros  1.000  m
        x = lblTTOD12_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.100){
		y1 = 0.0;
		y2 = 226.0;
		x1 = 0.000;
		x2 = 0.100;
	}else{
		if (x > 0.100 && x <= 0.200){
			y1 = 226.0;
			y2 = 662.0;
			x1 = 0.100;
			x2 = 0.200;
		}else{
			if (x > 0.200 && x <= 0.246){
				y1 = 662.0;
				y2 = 929.0;
				x1 = 0.200;
				x2 = 0.246;
			}else{
				if (x > 0.246 && x <= 0.265){
					y1 = 929.0;
					y2 = 1049.0;
					x1 = 0.246;
					x2 = 0.265;
				}else{
					if (x > 0.265 && x <= 0.286){
						y1 = 1049.0;
						y2 = 1185.0;
						x1 = 0.265;
						x2 = 0.286;
					}else{
						if (x > 0.286 && x <= 0.300){
							y1 = 1185.0;
							y2 = 1279.0;
							x1 = 0.286;
							x2 = 0.300;
						}else{
							if (x > 0.300 && x <= 0.400){
								y1 = 1279.0;
								y2 = 1931.0;
								x1 = 0.300;
								x2 = 0.400;
							}else{
								if (x > 0.400 && x <= 0.500){
									y1 = 1931.0;
									y2 = 2593.0;
									x1 = 0.400;
									x2 = 0.500;
								}else{
									if (x > 0.500 && x <= 0.600){
										y1 = 2593.0;
										y2 = 3235.0;
										x1 = 0.500;
										x2 = 0.600;
									}else{
										if (x > 0.600 && x <= 0.700){
											y1 = 3235.0;
											y2 = 3887.0;
											x1 = 0.600;
											x2 = 0.700;
										}else{
											if (x > 0.700 && x <= 0.800){
												y1 = 3887.0;
												y2 = 4538.0;
												x1 = 0.700;
												x2 = 0.800;
											}else{
												if (x > 0.800 && x <= 0.900){
													y1 = 4538.0;
													y2 = 5190.0;
													x1 = 0.800;
													x2 = 0.900;
												}else{
													if (x > 0.900 && x <= 1.000){
														y1 = 5190.0;
														y2 = 5842.0;
														x1 = 0.900;
														x2 = 1.000;
                                                                                                        }
                                                                                                }
											}
										}
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
      	lblTTOD12_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 5190.0;
                y2 = 5842.0;
                x1 = 0.900;
                x2 = 1.000;
                lblTTOD12_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTTOD12_NIVEL_litros->Caption = FormatFloat("0.##",lblTTOD12_NIVEL_litros->Caption.ToDouble());
        lblTTOD12_NIVEL_litros->Caption = lblTTOD12_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_TTOD13
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_TTOD13_NIVELALTO) == 0 ){ //possui inversão
		shpTTOD13_NIVELALTO->Brush->Color = clRed;
		btnTTOD13_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTTOD13_NIVELALTO->Brush->Color = clWhite;
		btnTTOD13_NIVELALTO->Caption = "Nível OK";
	};
        //***********************************************************
        lblTTOD13_NIVEL->Caption = CLP.RD(PC_HA_AODPG_TTOD13_NIVEL);
        lblTTOD13_NIVEL->Caption = FormatFloat("0.###",lblTTOD13_NIVEL->Caption.ToDouble()) ;
        pgrTTOD13_NIVEL->Position = (((lblTTOD13_NIVEL->Caption*100)-(0*100))*(100-0))/((1.066-0)*100); //metros

        //7.117 litros  1.066  m
        x = lblTTOD13_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.100){
		y1 = 0.0;
		y2 = 231.0;
		x1 = 0.000;
		x2 = 0.100;
	}else{
		if (x > 0.100 && x <= 0.200){
			y1 = 231.0;
			y2 = 635.0;
			x1 = 0.100;
			x2 = 0.200;
		}else{
			if (x > 0.200 && x <= 0.300){
				y1 = 635.0;
				y2 = 1229.0;
				x1 = 0.200;
				x2 = 0.300;
			}else{
				if (x > 0.300 && x <= 0.339){
					y1 = 1229.0;
					y2 = 1512.0;
					x1 = 0.300;
					x2 = 0.339;
				}else{
					if (x > 0.339 && x <= 0.400){
						y1 = 1512.0;
						y2 = 2002.0;
						x1 = 0.339;
						x2 = 0.400;
					}else{
						if (x > 0.400 && x <= 0.464){
							y1 = 2002.0;
							y2 = 2049.0;
							x1 = 0.400;
							x2 = 0.464;
						}else{
							if (x > 0.464 && x <= 0.500){
								y1 = 2049.0;
								y2 = 2543.0;
								x1 = 0.464;
								x2 = 0.500;
							}else{
								if (x > 0.500 && x <= 0.600){
									y1 = 2543.0;
									y2 = 3703.0;
									x1 = 0.500;
									x2 = 0.600;
								}else{
									if (x > 0.600 && x <= 1.000){
										y1 = 3703.0;
										y2 = 7117.0;
										x1 = 0.600;
										x2 = 1.000;
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
      	lblTTOD13_NIVEL_litros->Caption = (a * x) + b;
        if (x > x2){
                y1 = 3703.0;
                y2 = 7117.0;
                x1 = 0.600;
                x2 = 1.000;
                lblTTOD13_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
        }
	lblTTOD13_NIVEL_litros->Caption = FormatFloat("0.##",lblTTOD13_NIVEL_litros->Caption.ToDouble());
        lblTTOD13_NIVEL_litros->Caption = lblTTOD13_NIVEL_litros->Caption + " litros";
        //***********************************************************
//==============================================================================
//AODPG_BETOD1
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_BETOD1_LIGADO) == 1 ){
		shpBETOD1_LIGADO->Brush->Color = clLime;
		btnBETOD1_LIGADO->Caption = "Ligado";
                if (btnBETOD1_EMREM->Caption == "Em Local" && btnBETOD1_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBETOD1_LIGAR->Enabled = false;
                        btnBETOD1_DESLIGAR->Enabled = true;
                }
	}
	else{
		shpBETOD1_LIGADO->Brush->Color = clWhite;
		btnBETOD1_LIGADO->Caption = "Parado";
                if (btnBETOD1_EMREM->Caption == "Em Local" && btnBETOD1_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBETOD1_LIGAR->Enabled = true;
                        btnBETOD1_DESLIGAR->Enabled = false;
                }
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_BETOD1_EMREM) == 1 ){
		shpBETOD1_EMREM->Brush->Color = clNavy;
		btnBETOD1_EMREM->Caption = "Em Remoto";
		btnBETOD1_LIGAR->Enabled = false;
		btnBETOD1_DESLIGAR->Enabled = false;
	}
	else{
		shpBETOD1_EMREM->Brush->Color = clWhite;
		btnBETOD1_EMREM->Caption = "Em Local";
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_AODPG_BETOD1_LIGAR) == 1 ){
		shpBETOD1_LIGAR->Brush->Color = clLime;
                tmrBETOD1_DESLIGAR->Enabled = false;
		if (btnBETOD1_LIGADO->Caption == "Parado"  && tmrBETOD1_LIGAR->Enabled == false && btnBETOD1_PARAREMERG->Caption == "Parar em Emergência"){
        	        tmrBETOD1_LIGAR->Enabled = true;
	        }
        }
	else{
		shpBETOD1_LIGAR->Brush->Color = clWhite;
	};
	//***********************************************************
	if (( CLP.RD(CP_HL_AODPG_BETOD1_DESLIGAR) == 1 ) || ( CLP.RD(CP_HL_AODPG_BETOD1_PARAREMERG) == 1 )){
		if ( CLP.RD(CP_HL_AODPG_BETOD1_DESLIGAR) == 1 ){
		        shpBETOD1_DESLIGAR->Brush->Color = clYellow;
		}
		if ( CLP.RD(CP_HL_AODPG_BETOD1_PARAREMERG) == 1 ){
			shpBETOD1_PARAREMERG->Brush->Color = clRed;
			btnBETOD1_LIGAR->Enabled = false;
			btnBETOD1_DESLIGAR->Enabled = false;
		}
		tmrBETOD1_LIGAR->Enabled = false;
		if (btnBETOD1_LIGADO->Caption == "Ligado"  && tmrBETOD1_DESLIGAR->Enabled == false){
			tmrBETOD1_DESLIGAR->Enabled = true;
		}
	}
	else{
		shpBETOD1_DESLIGAR->Brush->Color = clWhite;
		shpBETOD1_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//AODPG_BETOD2
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_BETOD2_LIGADO) == 1 ){
		shpBETOD2_LIGADO->Brush->Color = clLime;
		btnBETOD2_LIGADO->Caption = "Ligado";
                if (btnBETOD2_EMREM->Caption == "Em Local" && btnBETOD2_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBETOD2_LIGAR->Enabled = false;
                        btnBETOD2_DESLIGAR->Enabled = true;
                }
	}
	else{
		shpBETOD2_LIGADO->Brush->Color = clWhite;
		btnBETOD2_LIGADO->Caption = "Parado";
                if (btnBETOD2_EMREM->Caption == "Em Local" && btnBETOD2_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBETOD2_LIGAR->Enabled = true;
                        btnBETOD2_DESLIGAR->Enabled = false;
                }
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_AODPG_BETOD2_EMREM) == 1 ){
		shpBETOD2_EMREM->Brush->Color = clNavy;
		btnBETOD2_EMREM->Caption = "Em Remoto";
		btnBETOD2_LIGAR->Enabled = false;
		btnBETOD2_DESLIGAR->Enabled = false;
	}
	else{
		shpBETOD2_EMREM->Brush->Color = clWhite;
		btnBETOD2_EMREM->Caption = "Em Local";
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_AODPG_BETOD2_LIGAR) == 1 ){
		shpBETOD2_LIGAR->Brush->Color = clLime;
                tmrBETOD2_DESLIGAR->Enabled = false;
		if (btnBETOD2_LIGADO->Caption == "Parado"  && tmrBETOD2_LIGAR->Enabled == false && btnBETOD2_PARAREMERG->Caption == "Parar em Emergência"){
        	        tmrBETOD2_LIGAR->Enabled = true;
	        }
        }
	else{
		shpBETOD2_LIGAR->Brush->Color = clWhite;
	};
	//***********************************************************
	if (( CLP.RD(CP_HL_AODPG_BETOD2_DESLIGAR) == 1 ) || ( CLP.RD(CP_HL_AODPG_BETOD2_PARAREMERG) == 1 )){
		if ( CLP.RD(CP_HL_AODPG_BETOD2_DESLIGAR) == 1 ){
		        shpBETOD2_DESLIGAR->Brush->Color = clYellow;
		}
		if ( CLP.RD(CP_HL_AODPG_BETOD2_PARAREMERG) == 1 ){
			shpBETOD2_PARAREMERG->Brush->Color = clRed;
			btnBETOD2_LIGAR->Enabled = false;
			btnBETOD2_DESLIGAR->Enabled = false;
		}
		tmrBETOD2_LIGAR->Enabled = false;
		if (btnBETOD2_LIGADO->Caption == "Ligado"  && tmrBETOD2_DESLIGAR->Enabled == false){
			tmrBETOD2_DESLIGAR->Enabled = true;
		}
	}
	else{
		shpBETOD2_DESLIGAR->Brush->Color = clWhite;
		shpBETOD2_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//AODPG_PLOD1
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_PLOD1_FALHAALIM) == 1 ){
		shpPLOD1_FALHAALIM->Brush->Color = clRed;
		btnPLOD1_FALHAALIM->Caption = "Falha Alim.";
	}
	else{
		shpPLOD1_FALHAALIM->Brush->Color = clWhite;
		btnPLOD1_FALHAALIM->Caption = "Alim. OK";
	};
        //***********************************************************
//==============================================================================
//AODPG_PLOD2
        //***********************************************************
        if ( CLP.RD(PC_HL_AODPG_PLOD2_FALHAALIM) == 1 ){
		shpPLOD2_FALHAALIM->Brush->Color = clRed;
		btnPLOD2_FALHAALIM->Caption = "Falha Alim.";
	}
	else{
		shpPLOD2_FALHAALIM->Brush->Color = clWhite;
		btnPLOD2_FALHAALIM->Caption = "Alim. OK";
	};
        //***********************************************************
//==============================================================================
//SODPG_VOD103
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD103_FECHADO) == 1) {
                btnVOD103_FECHADO->Caption = "Fechada";
                shpVOD103_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD103_FECHADO->Caption = "Não Fechada";
                shpVOD103_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD103_ABERTO) == 1) {
                btnVOD103_ABERTO->Caption = "Aberta";
                shpVOD103_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD103_ABERTO->Caption = "Não Aberta";
                shpVOD103_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD103_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD103_ABRIR) == 1) {
                        shpVOD103_ABRIR->Brush->Color = clRed;
                        if (btnVOD103_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 0);
                        }
                        if (btnVOD103_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD103_ABERTO, 1);
                        }
                }else{
                        shpVOD103_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD103_FECHAR) == 1) {
                        shpVOD103_FECHAR->Brush->Color = clLime;
                        if (btnVOD103_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD103_ABERTO, 0);
                        }
                        if (btnVOD103_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 1);
                        }
                }else{
                        shpVOD103_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD103_ABERTO->Enabled  = VOD103_ModoOpera;
        btnVOD103_FECHADO->Enabled = VOD103_ModoOpera;
        btnVOD103_ABRIR->Enabled   = VOD103_ModoOpera;
        btnVOD103_FECHAR->Enabled  = VOD103_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD106
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD106_FECHADO) == 1) {
                btnVOD106_FECHADO->Caption = "Fechada";
                shpVOD106_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD106_FECHADO->Caption = "Não Fechada";
                shpVOD106_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD106_ABERTO) == 1) {
                btnVOD106_ABERTO->Caption = "Aberta";
                shpVOD106_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD106_ABERTO->Caption = "Não Aberta";
                shpVOD106_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD106_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD106_ABRIR) == 1) {
                        shpVOD106_ABRIR->Brush->Color = clRed;
                        if (btnVOD106_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 0);
                        }
                        if (btnVOD106_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD106_ABERTO, 1);
                        }
                }else{
                        shpVOD106_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD106_FECHAR) == 1) {
                        shpVOD106_FECHAR->Brush->Color = clLime;
                        if (btnVOD106_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD106_ABERTO, 0);
                        }
                        if (btnVOD106_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 1);
                        }
                }else{
                        shpVOD106_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD106_ABERTO->Enabled  = VOD106_ModoOpera;
        btnVOD106_FECHADO->Enabled = VOD106_ModoOpera;
        btnVOD106_ABRIR->Enabled   = VOD106_ModoOpera;
        btnVOD106_FECHAR->Enabled  = VOD106_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD101
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD101_FECHADO) == 1) {
                btnVOD101_FECHADO->Caption = "Fechada";
                shpVOD101_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD101_FECHADO->Caption = "Não Fechada";
                shpVOD101_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD101_ABERTO) == 1) {
                btnVOD101_ABERTO->Caption = "Aberta";
                shpVOD101_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD101_ABERTO->Caption = "Não Aberta";
                shpVOD101_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD101_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD101_ABRIR) == 1) {
                        shpVOD101_ABRIR->Brush->Color = clRed;
                        if (btnVOD101_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 0);
                        }
                        if (btnVOD101_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD101_ABERTO, 1);
                        }
                }else{
                        shpVOD101_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD101_FECHAR) == 1) {
                        shpVOD101_FECHAR->Brush->Color = clLime;
                        if (btnVOD101_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD101_ABERTO, 0);
                        }
                        if (btnVOD101_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 1);
                        }
                }else{
                        shpVOD101_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD101_ABERTO->Enabled  = VOD101_ModoOpera;
        btnVOD101_FECHADO->Enabled = VOD101_ModoOpera;
        btnVOD101_ABRIR->Enabled   = VOD101_ModoOpera;
        btnVOD101_FECHAR->Enabled  = VOD101_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD098
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD098_FECHADO) == 1) {
                btnVOD098_FECHADO->Caption = "Fechada";
                shpVOD098_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD098_FECHADO->Caption = "Não Fechada";
                shpVOD098_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD098_ABERTO) == 1) {
                btnVOD098_ABERTO->Caption = "Aberta";
                shpVOD098_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD098_ABERTO->Caption = "Não Aberta";
                shpVOD098_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD098_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD098_ABRIR) == 1) {
                        shpVOD098_ABRIR->Brush->Color = clRed;
                        if (btnVOD098_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 0);
                        }
                        if (btnVOD098_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD098_ABERTO, 1);
                        }
                }else{
                        shpVOD098_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD098_FECHAR) == 1) {
                        shpVOD098_FECHAR->Brush->Color = clLime;
                        if (btnVOD098_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD098_ABERTO, 0);
                        }
                        if (btnVOD098_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 1);
                        }
                }else{
                        shpVOD098_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD098_ABERTO->Enabled  = VOD098_ModoOpera;
        btnVOD098_FECHADO->Enabled = VOD098_ModoOpera;
        btnVOD098_ABRIR->Enabled   = VOD098_ModoOpera;
        btnVOD098_FECHAR->Enabled  = VOD098_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_BEROD1
        //***********************************************************
        if ( CLP.RD(PC_HL_SODPG_BEROD1_SOBREC1) == 1 ){
		shpBEROD1_SOBREC1->Brush->Color = clRed;
		btnBEROD1_SOBREC1->Caption = "Sobrecarga";
	}
	else{
		shpBEROD1_SOBREC1->Brush->Color = clWhite;
		btnBEROD1_SOBREC1->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_SODPG_BEROD1_LIGADO) == 1 ){
		shpBEROD1_LIGADO->Brush->Color = clLime;
		btnBEROD1_LIGADO->Caption = "Ligado";
                if (btnBEROD1_EMREM->Caption == "Em Local" && btnBEROD1_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBEROD1_LIGAR->Enabled = false;
                        btnBEROD1_DESLIGAR->Enabled = true;
                }
	}
	else{
		shpBEROD1_LIGADO->Brush->Color = clWhite;
		btnBEROD1_LIGADO->Caption = "Parado";
                if (btnBEROD1_EMREM->Caption == "Em Local" && btnBEROD1_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBEROD1_LIGAR->Enabled = true;
                        btnBEROD1_DESLIGAR->Enabled = false;
                }
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_BEROD1_EMREM) == 1 ){
		shpBEROD1_EMREM->Brush->Color = clNavy;
		btnBEROD1_EMREM->Caption = "Em Remoto";
		btnBEROD1_LIGAR->Enabled = false;
		btnBEROD1_DESLIGAR->Enabled = false;
	}
	else{
		shpBEROD1_EMREM->Brush->Color = clWhite;
		btnBEROD1_EMREM->Caption = "Em Local";
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_SODPG_BEROD1_LIGAR) == 1 ){
		shpBEROD1_LIGAR->Brush->Color = clLime;
                tmrBEROD1_DESLIGAR->Enabled = false;
		if (btnBEROD1_LIGADO->Caption == "Parado"  && tmrBEROD1_LIGAR->Enabled == false && btnBEROD1_PARAREMERG->Caption == "Parar em Emergência"){
        	        tmrBEROD1_LIGAR->Enabled = true;
	        }
        }
	else{
		shpBEROD1_LIGAR->Brush->Color = clWhite;
	};
	//***********************************************************
	if (( CLP.RD(CP_HL_SODPG_BEROD1_DESLIGAR) == 1 ) || ( CLP.RD(CP_HL_SODPG_BEROD1_PARAREMERG) == 1 )){
		if ( CLP.RD(CP_HL_SODPG_BEROD1_DESLIGAR) == 1 ){
		        shpBEROD1_DESLIGAR->Brush->Color = clYellow;
		}
		if ( CLP.RD(CP_HL_SODPG_BEROD1_PARAREMERG) == 1 ){
			shpBEROD1_PARAREMERG->Brush->Color = clRed;
			btnBEROD1_LIGAR->Enabled = false;
			btnBEROD1_DESLIGAR->Enabled = false;
		}
		tmrBEROD1_LIGAR->Enabled = false;
		if (btnBEROD1_LIGADO->Caption == "Ligado"  && tmrBEROD1_DESLIGAR->Enabled == false){
			tmrBEROD1_DESLIGAR->Enabled = true;
		}
	}
	else{
		shpBEROD1_DESLIGAR->Brush->Color = clWhite;
		shpBEROD1_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//SODPG_BEROD2
        //***********************************************************
        if ( CLP.RD(PC_HL_SODPG_BEROD2_SOBREC1) == 1 ){
		shpBEROD2_SOBREC1->Brush->Color = clRed;
		btnBEROD2_SOBREC1->Caption = "Sobrecarga";
	}
	else{
		shpBEROD2_SOBREC1->Brush->Color = clWhite;
		btnBEROD2_SOBREC1->Caption = "Sem Sobrecarga";
	};
        //***********************************************************
        if ( CLP.RD(PC_HL_SODPG_BEROD2_LIGADO) == 1 ){
		shpBEROD2_LIGADO->Brush->Color = clLime;
		btnBEROD2_LIGADO->Caption = "Ligado";
                if (btnBEROD2_EMREM->Caption == "Em Local" && btnBEROD2_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBEROD2_LIGAR->Enabled = false;
                        btnBEROD2_DESLIGAR->Enabled = true;
                }
	}
	else{
		shpBEROD2_LIGADO->Brush->Color = clWhite;
		btnBEROD2_LIGADO->Caption = "Parado";
                if (btnBEROD2_EMREM->Caption == "Em Local" && btnBEROD2_PARAREMERG->Caption == "Parar em Emergência"){
                        btnBEROD2_LIGAR->Enabled = true;
                        btnBEROD2_DESLIGAR->Enabled = false;
                }
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_BEROD2_EMREM) == 1 ){
		shpBEROD2_EMREM->Brush->Color = clNavy;
		btnBEROD2_EMREM->Caption = "Em Remoto";
		btnBEROD2_LIGAR->Enabled = false;
		btnBEROD2_DESLIGAR->Enabled = false;
	}
	else{
		shpBEROD2_EMREM->Brush->Color = clWhite;
		btnBEROD2_EMREM->Caption = "Em Local";
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_SODPG_BEROD2_LIGAR) == 1 ){
		shpBEROD2_LIGAR->Brush->Color = clLime;
                tmrBEROD2_DESLIGAR->Enabled = false;
		if (btnBEROD2_LIGADO->Caption == "Parado"  && tmrBEROD2_LIGAR->Enabled == false && btnBEROD2_PARAREMERG->Caption == "Parar em Emergência"){
        	        tmrBEROD2_LIGAR->Enabled = true;
	        }
        }
	else{
		shpBEROD2_LIGAR->Brush->Color = clWhite;
	};
	//***********************************************************
	if (( CLP.RD(CP_HL_SODPG_BEROD2_DESLIGAR) == 1 ) || ( CLP.RD(CP_HL_SODPG_BEROD2_PARAREMERG) == 1 )){
		if ( CLP.RD(CP_HL_SODPG_BEROD2_DESLIGAR) == 1 ){
		        shpBEROD2_DESLIGAR->Brush->Color = clYellow;
		}
		if ( CLP.RD(CP_HL_SODPG_BEROD2_PARAREMERG) == 1 ){
			shpBEROD2_PARAREMERG->Brush->Color = clRed;
			btnBEROD2_LIGAR->Enabled = false;
			btnBEROD2_DESLIGAR->Enabled = false;
		}
		tmrBEROD2_LIGAR->Enabled = false;
		if (btnBEROD2_LIGADO->Caption == "Ligado"  && tmrBEROD2_DESLIGAR->Enabled == false){
			tmrBEROD2_DESLIGAR->Enabled = true;
		}
	}
	else{
		shpBEROD2_DESLIGAR->Brush->Color = clWhite;
		shpBEROD2_PARAREMERG->Brush->Color = clWhite;
	};
        //***********************************************************
//==============================================================================
//SODPG_AQCOD1
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD1_FALHA) == 1 ){
		shpAQCOD1_FALHA->Brush->Color = clRed;
		btnAQCOD1_FALHA->Caption = "Temp. Alta";
	}
	else{
		shpAQCOD1_FALHA->Brush->Color = clWhite;
		btnAQCOD1_FALHA->Caption = "Sem Temp. Alta";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD1_ENERGIZADO) == 1 ){
		shpAQCOD1_ENERGIZADO->Brush->Color = clLime;
		btnAQCOD1_ENERGIZADO->Caption = "Energizado";
	}
	else{
		shpAQCOD1_ENERGIZADO->Brush->Color = clWhite;
		btnAQCOD1_ENERGIZADO->Caption = "Desenergizado";
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD1_LIGADO) == 1 ){
		shpAQCOD1_LIGADO->Brush->Color = clLime;
		btnAQCOD1_LIGADO->Caption = "Ligado";
                if (btnAQCOD1_EMREM->Caption == "Em Local"){
                        btnAQCOD1_LIGAR->Enabled = false;
                        btnAQCOD1_DESLIGAR->Enabled = true;
                }
	}
	else{
		shpAQCOD1_LIGADO->Brush->Color = clWhite;
		btnAQCOD1_LIGADO->Caption = "Parado";
                if (btnAQCOD1_EMREM->Caption == "Em Local"){
                        btnAQCOD1_LIGAR->Enabled = true;
                        btnAQCOD1_DESLIGAR->Enabled = false;
                }
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD1_EMREM) == 1 ){
		shpAQCOD1_EMREM->Brush->Color = clNavy;
		btnAQCOD1_EMREM->Caption = "Em Remoto";
		btnAQCOD1_LIGAR->Enabled = false;
		btnAQCOD1_DESLIGAR->Enabled = false;
	}
	else{
		shpAQCOD1_EMREM->Brush->Color = clWhite;
		btnAQCOD1_EMREM->Caption = "Em Local";
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_SODPG_AQCOD1_LIGAR) == 1 ){
		shpAQCOD1_LIGAR->Brush->Color = clLime;
                if (btnAQCOD1_LIGADO->Caption == "Parado" && btnAQCOD1_ENERGIZADO->Caption == "Energizado"){
        	        CLP.WR(PC_HL_SODPG_AQCOD1_LIGADO, 1);
	        }
        }
	else{
		shpAQCOD1_LIGAR->Brush->Color = clWhite;
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_SODPG_AQCOD1_DESLIGAR) == 1 ) {
                shpAQCOD1_DESLIGAR->Brush->Color = clYellow;
		if (btnAQCOD1_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_SODPG_AQCOD1_LIGADO, 0);
		}
	}
	else{
		shpAQCOD1_DESLIGAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if (btnAQCOD1_ENERGIZADO->Caption == "Desenergizado"){
                if (btnAQCOD1_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_SODPG_AQCOD1_LIGADO, 0);
		}
                if (btnAQCOD1_EMREM->Caption == "Em Remoto"){
			CLP.WR(PC_HL_SODPG_AQCOD1_EMREM, 0);
		}
                if (btnAQCOD1_FALHA->Caption == "Temp. Alta"){
			CLP.WR(PC_HL_SODPG_AQCOD1_FALHA, 0);
		}
                btnAQCOD1_LIGAR->Enabled = false;
                btnAQCOD1_DESLIGAR->Enabled = false;
        }
        //***********************************************************
//==============================================================================
//SODPG_AQCOD2
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD2_FALHA) == 1 ){
		shpAQCOD2_FALHA->Brush->Color = clRed;
		btnAQCOD2_FALHA->Caption = "Temp. Alta";
	}
	else{
		shpAQCOD2_FALHA->Brush->Color = clWhite;
		btnAQCOD2_FALHA->Caption = "Sem Temp. Alta";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD2_ENERGIZADO) == 1 ){
		shpAQCOD2_ENERGIZADO->Brush->Color = clLime;
		btnAQCOD2_ENERGIZADO->Caption = "Energizado";
	}
	else{
		shpAQCOD2_ENERGIZADO->Brush->Color = clWhite;
		btnAQCOD2_ENERGIZADO->Caption = "Desenergizado";
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD2_LIGADO) == 1 ){
		shpAQCOD2_LIGADO->Brush->Color = clLime;
		btnAQCOD2_LIGADO->Caption = "Ligado";
                if (btnAQCOD2_EMREM->Caption == "Em Local"){
                        btnAQCOD2_LIGAR->Enabled = false;
                        btnAQCOD2_DESLIGAR->Enabled = true;
                }
	}
	else{
		shpAQCOD2_LIGADO->Brush->Color = clWhite;
		btnAQCOD2_LIGADO->Caption = "Parado";
                if (btnAQCOD2_EMREM->Caption == "Em Local"){
                        btnAQCOD2_LIGAR->Enabled = true;
                        btnAQCOD2_DESLIGAR->Enabled = false;
                }
	};
        //***********************************************************
	if ( CLP.RD(PC_HL_SODPG_AQCOD2_EMREM) == 1 ){
		shpAQCOD2_EMREM->Brush->Color = clNavy;
		btnAQCOD2_EMREM->Caption = "Em Remoto";
		btnAQCOD2_LIGAR->Enabled = false;
		btnAQCOD2_DESLIGAR->Enabled = false;
	}
	else{
		shpAQCOD2_EMREM->Brush->Color = clWhite;
		btnAQCOD2_EMREM->Caption = "Em Local";
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_SODPG_AQCOD2_LIGAR) == 1 ){
		shpAQCOD2_LIGAR->Brush->Color = clLime;
                if (btnAQCOD2_LIGADO->Caption == "Parado" && btnAQCOD1_ENERGIZADO->Caption == "Energizado"){
                        CLP.WR(PC_HL_SODPG_AQCOD2_LIGADO, 1);
                }
        }
	else{
		shpAQCOD2_LIGAR->Brush->Color = clWhite;
	};
	//***********************************************************
	if ( CLP.RD(CP_HL_SODPG_AQCOD2_DESLIGAR) == 1 ) {
                shpAQCOD2_DESLIGAR->Brush->Color = clYellow;
		if (btnAQCOD2_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_SODPG_AQCOD2_LIGADO, 0);
		}
	}
	else{
		shpAQCOD2_DESLIGAR->Brush->Color = clWhite;
	};
        //***********************************************************
        if (btnAQCOD2_ENERGIZADO->Caption == "Desenergizado"){
                if (btnAQCOD2_LIGADO->Caption == "Ligado"){
			CLP.WR(PC_HL_SODPG_AQCOD2_LIGADO, 0);
		}
                if (btnAQCOD2_EMREM->Caption == "Em Remoto"){
			CLP.WR(PC_HL_SODPG_AQCOD2_EMREM, 0);
		}
                if (btnAQCOD2_FALHA->Caption == "Temp. Alta"){
			CLP.WR(PC_HL_SODPG_AQCOD2_FALHA, 0);
		}
                btnAQCOD2_LIGAR->Enabled = false;
                btnAQCOD2_DESLIGAR->Enabled = false;
        }
        //***********************************************************
//==============================================================================
//SODPG_FCOD1
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_FCOD1_PRESSDIFALTA) == 1) {
                btnFCOD1_PRESSDIFALTA->Caption = "Pressão Alta";
                shpFCOD1_PRESSDIFALTA->Brush->Color = clRed;
        }else{
                btnFCOD1_PRESSDIFALTA->Caption = "Pressão OK";
                shpFCOD1_PRESSDIFALTA->Brush->Color = clWhite;
        }

        //***********************************************************
//==============================================================================
//SODPG_FCOD2
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_FCOD2_PRESSDIFALTA) == 1) {
                btnFCOD2_PRESSDIFALTA->Caption = "Pressão Alta";
                shpFCOD2_PRESSDIFALTA->Brush->Color = clRed;
        }else{
                btnFCOD2_PRESSDIFALTA->Caption = "Pressão OK";
                shpFCOD2_PRESSDIFALTA->Brush->Color = clWhite;
        }
        //***********************************************************
//==============================================================================
//SODPG_TSOD08
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD08_NIVELALTO) == 0 ){ //possui inversão
		shpTSOD08_NIVELALTO->Brush->Color = clYellow;
		btnTSOD08_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTSOD08_NIVELALTO->Brush->Color = clWhite;
		btnTSOD08_NIVELALTO->Caption = "Nível OK";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD08_NIVELBAIXO) == 1 ){
		shpTSOD08_NIVELBAIXO->Brush->Color = clRed;
		btnTSOD08_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpTSOD08_NIVELBAIXO->Brush->Color = clWhite;
		btnTSOD08_NIVELBAIXO->Caption = "Nível OK";
	};
	//***********************************************************
	lblTSOD08_NIVEL->Caption = CLP.RD(PC_HA_SODPG_TSOD08_NIVEL);
	lblTSOD08_NIVEL->Caption = FormatFloat("0.###",lblTSOD08_NIVEL->Caption.ToDouble()) ;
	pgrTSOD08_NIVEL->Position = (((lblTSOD08_NIVEL->Caption*100)-(0*100))*(100-0))/((2.504-0)*100); //metros

	//8.633 litros  2,504  m
	x = lblTSOD08_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.050){
		y1 = 32.0;
		y2 = 93.0;
		x1 = 0.000;
		x2 = 0.050;
	}else{
		if (x > 0.050 && x <= 0.100){
			y1 = 93.0;
			y2 = 180.0;
			x1 = 0.050;
			x2 = 0.100;
		}else{
			if (x > 0.100 && x <= 0.150){
				y1 = 180.0;
				y2 = 295.0;
				x1 = 0.100;
				x2 = 0.150;
			}else{
				if (x > 0.150 && x <= 0.200){
					y1 = 295.0;
					y2 = 436.0;
					x1 = 0.150;
					x2 = 0.200;
				}else{
					if (x > 0.200 && x <= 0.250){
						y1 = 436.0;
						y2 = 604.0;
						x1 = 0.200;
						x2 = 0.250;
					}else{
						if (x > 0.250 && x <= 0.350){
							y1 = 604.0;
							y2 = 971.0;
							x1 = 0.250;
							x2 = 0.350;
						}else{
							if (x > 0.350 && x <= 1.050){
								y1 = 971.0;
								y2 = 3536.0;
								x1 = 0.350;
								x2 = 1.050;
							}else{
								if (x > 1.050 && x <= 1.750){
									y1 = 3536.0;
									y2 = 6102.0;
									x1 = 1.050;
									x2 = 1.750;
								}else{
									if (x > 1.750 && x <= 2.460){
										y1 = 6102.0;
										y2 = 8633.0;
										x1 = 1.750;
										x2 = 2.460;
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTSOD08_NIVEL_litros->Caption = (a * x) + b;
	if (x > x2){
	        y1 = 6102.0;
	        y2 = 8633.0;
	        x1 = 1.750;
                x2 = 2.460;
	        lblTSOD08_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
	}
	lblTSOD08_NIVEL_litros->Caption = FormatFloat("0.##",lblTSOD08_NIVEL_litros->Caption.ToDouble());
	lblTSOD08_NIVEL_litros->Caption = lblTSOD08_NIVEL_litros->Caption + " litros";
	//***********************************************************
	lblTSOD08_TEMP->Caption = CLP.RD(PC_HA_SODPG_TSOD08_TEMP);
	lblTSOD08_TEMP->Caption = FormatFloat("0.###",lblTSOD08_TEMP->Caption.ToDouble()) ;
	pgrTSOD08_TEMP->Position = (((lblTSOD08_TEMP->Caption*100)-(0*100))*(100-0))/((45-0)*100); //°C
	//***********************************************************
//==============================================================================
//SODPG_TSOD09
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD09_NIVELALTO) == 0 ){ //possui inversão
		shpTSOD09_NIVELALTO->Brush->Color = clYellow;
		btnTSOD09_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTSOD09_NIVELALTO->Brush->Color = clWhite;
		btnTSOD09_NIVELALTO->Caption = "Nível OK";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD09_NIVELBAIXO) == 1 ){
		shpTSOD09_NIVELBAIXO->Brush->Color = clRed;
		btnTSOD09_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpTSOD09_NIVELBAIXO->Brush->Color = clWhite;
		btnTSOD09_NIVELBAIXO->Caption = "Nível OK";
	};
	//***********************************************************
	lblTSOD09_NIVEL->Caption = CLP.RD(PC_HA_SODPG_TSOD09_NIVEL);
	lblTSOD09_NIVEL->Caption = FormatFloat("0.###",lblTSOD09_NIVEL->Caption.ToDouble()) ;
	pgrTSOD09_NIVEL->Position = (((lblTSOD09_NIVEL->Caption*100)-(0*100))*(100-0))/((2.624-0)*100); //metros

	//8.633 litros  2,624  m
	x = lblTSOD09_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.042){
		y1 = 0.0;
		y2 = 29.0;
		x1 = 0.000;
		x2 = 0.042;
	}else{
		if (x > 0.042 && x <= 0.142){
			y1 = 29.0;
			y2 = 174.0;
			x1 = 0.042;
			x2 = 0.142;
		}else{
			if (x > 0.142 && x <= 0.242){
				y1 = 174.0;
				y2 = 427.0;
				x1 = 0.142;
				x2 = 0.242;
			}else{
				if (x > 0.242 && x <= 0.350){
					y1 = 427.0;
					y2 = 806.0;
					x1 = 0.242;
					x2 = 0.350;
				}else{
					if (x > 0.350 && x <= 1.042){
						y1 = 806.0;
						y2 = 3342.0;
						x1 = 0.350;
						x2 = 1.042;
					}else{
						if (x > 1.042 && x <= 1.142){
							y1 = 3342.0;
							y2 = 3079.0;
							x1 = 1.042;
							x2 = 1.142;
						}else{
							if (x > 1.142 && x <= 1.242){
								y1 = 3079.0;
								y2 = 4075.0;
								x1 = 1.142;
								x2 = 1.242;
							}else{
								if (x > 1.242 && x <= 2.467){
									y1 = 4075.0;
									y2 = 8565.0;
									x1 = 1.242;
									x2 = 2.467;
								}else{
									if (x > 2.467 && x <= 2.487){
										y1 = 8565.0;
										y2 = 8619.0;
										x1 = 2.467;
										x2 = 2.487;
									}else{
										if (x > 2.487 && x <= 2.504){
											y1 = 8619.0;
											y2 = 8633.0;
											x1 = 2.487;
											x2 = 2.504;
										}
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTSOD09_NIVEL_litros->Caption = (a * x) + b;
	if (x > x2){
	        y1 = 8619.0;
	        y2 = 8633.0;
	        x1 = 2.487;
	        x2 = 2.504;
	        lblTSOD09_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
	}
	lblTSOD09_NIVEL_litros->Caption = FormatFloat("0.##",lblTSOD09_NIVEL_litros->Caption.ToDouble());
	lblTSOD09_NIVEL_litros->Caption = lblTSOD09_NIVEL_litros->Caption + " litros";
	//***********************************************************
	lblTSOD09_TEMP->Caption = CLP.RD(PC_HA_SODPG_TSOD09_TEMP);
	lblTSOD09_TEMP->Caption = FormatFloat("0.###",lblTSOD09_TEMP->Caption.ToDouble()) ;
	pgrTSOD09_TEMP->Position = (((lblTSOD09_TEMP->Caption*100)-(0*100))*(100-0))/((45-0)*100); //°C
	//***********************************************************
//==============================================================================
//SODPG_VOD120
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD120_FECHADO) == 1) {
                btnVOD120_FECHADO->Caption = "Fechada";
                shpVOD120_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD120_FECHADO->Caption = "Não Fechada";
                shpVOD120_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD120_ABERTO) == 1) {
                btnVOD120_ABERTO->Caption = "Aberta";
                shpVOD120_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD120_ABERTO->Caption = "Não Aberta";
                shpVOD120_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD120_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD120_ABRIR) == 1) {
                        shpVOD120_ABRIR->Brush->Color = clRed;
                        if (btnVOD120_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 0);
                        }
                        if (btnVOD120_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD120_ABERTO, 1);
                        }
                }else{
                        shpVOD120_ABRIR->Brush->Color = clWhite;
                        if ( VOD120_RetornoAuto == true) {
                                if (btnVOD120_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_SODPG_VOD120_ABERTO, 0);
                                }
                                if (btnVOD120_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD120_ABERTO->Enabled  = VOD120_ModoOpera;
        btnVOD120_FECHADO->Enabled = VOD120_ModoOpera;
        btnVOD120_ABRIR->Enabled   = VOD120_ModoOpera;
        btnVOD120_FECHAR->Enabled  = VOD120_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD129
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD129_FECHADO) == 1) {
                btnVOD129_FECHADO->Caption = "Fechada";
                shpVOD129_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD129_FECHADO->Caption = "Não Fechada";
                shpVOD129_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD129_ABERTO) == 1) {
                btnVOD129_ABERTO->Caption = "Aberta";
                shpVOD129_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD129_ABERTO->Caption = "Não Aberta";
                shpVOD129_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD129_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD129_ABRIR) == 1) {
                        shpVOD129_ABRIR->Brush->Color = clRed;
                        if (btnVOD129_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 0);
                        }
                        if (btnVOD129_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD129_ABERTO, 1);
                        }
                }else{
                        shpVOD129_ABRIR->Brush->Color = clWhite;
                        if ( VOD129_RetornoAuto == true) {
                                if (btnVOD129_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_SODPG_VOD129_ABERTO, 0);
                                }
                                if (btnVOD129_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD129_ABERTO->Enabled  = VOD129_ModoOpera;
        btnVOD129_FECHADO->Enabled = VOD129_ModoOpera;
        btnVOD129_ABRIR->Enabled   = VOD129_ModoOpera;
        btnVOD129_FECHAR->Enabled  = VOD129_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD152
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD152_FECHADO) == 1) {
                btnVOD152_FECHADO->Caption = "Fechada";
                shpVOD152_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD152_FECHADO->Caption = "Não Fechada";
                shpVOD152_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD152_ABERTO) == 1) {
                btnVOD152_ABERTO->Caption = "Aberta";
                shpVOD152_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD152_ABERTO->Caption = "Não Aberta";
                shpVOD152_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD152_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD152_ABRIR) == 1) {
                        shpVOD152_ABRIR->Brush->Color = clRed;
                        if (btnVOD152_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 0);
                        }
                        if (btnVOD152_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD152_ABERTO, 1);
                        }
                }else{
                        shpVOD152_ABRIR->Brush->Color = clWhite;
                        if ( VOD152_RetornoAuto == true) {
                                if (btnVOD152_ABERTO->Caption == "Aberta"){
                                        CLP.WR(PC_HL_SODPG_VOD152_ABERTO, 0);
                                }
                                if (btnVOD152_FECHADO->Caption == "Não Fechada"){
                                        CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 1);
                                }
                        }
                }
        }
        //***********************************************************
        btnVOD152_ABERTO->Enabled  = VOD152_ModoOpera;
        btnVOD152_FECHADO->Enabled = VOD152_ModoOpera;
        btnVOD152_ABRIR->Enabled   = VOD152_ModoOpera;
        btnVOD152_FECHAR->Enabled  = VOD152_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD122
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD122_FECHADO) == 1) {
                btnVOD122_FECHADO->Caption = "Fechada";
                shpVOD122_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD122_FECHADO->Caption = "Não Fechada";
                shpVOD122_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD122_ABERTO) == 1) {
                btnVOD122_ABERTO->Caption = "Aberta";
                shpVOD122_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD122_ABERTO->Caption = "Não Aberta";
                shpVOD122_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD122_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD122_ABRIR) == 1) {
                        shpVOD122_ABRIR->Brush->Color = clRed;
                        if (btnVOD122_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 0);
                        }
                        if (btnVOD122_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD122_ABERTO, 1);
                        }
                }else{
                        shpVOD122_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD122_FECHAR) == 1) {
                        shpVOD122_FECHAR->Brush->Color = clLime;
                        if (btnVOD122_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD122_ABERTO, 0);
                        }
                        if (btnVOD122_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 1);
                        }
                }else{
                        shpVOD122_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD122_ABERTO->Enabled  = VOD122_ModoOpera;
        btnVOD122_FECHADO->Enabled = VOD122_ModoOpera;
        btnVOD122_ABRIR->Enabled   = VOD122_ModoOpera;
        btnVOD122_FECHAR->Enabled  = VOD122_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD133
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD133_FECHADO) == 1) {
                btnVOD133_FECHADO->Caption = "Fechada";
                shpVOD133_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD133_FECHADO->Caption = "Não Fechada";
                shpVOD133_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD133_ABERTO) == 1) {
                btnVOD133_ABERTO->Caption = "Aberta";
                shpVOD133_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD133_ABERTO->Caption = "Não Aberta";
                shpVOD133_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD133_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD133_ABRIR) == 1) {
                        shpVOD133_ABRIR->Brush->Color = clRed;
                        if (btnVOD133_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 0);
                        }
                        if (btnVOD133_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD133_ABERTO, 1);
                        }
                }else{
                        shpVOD133_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD133_FECHAR) == 1) {
                        shpVOD133_FECHAR->Brush->Color = clLime;
                        if (btnVOD133_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD133_ABERTO, 0);
                        }
                        if (btnVOD133_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 1);
                        }
                }else{
                        shpVOD133_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD133_ABERTO->Enabled  = VOD133_ModoOpera;
        btnVOD133_FECHADO->Enabled = VOD133_ModoOpera;
        btnVOD133_ABRIR->Enabled   = VOD133_ModoOpera;
        btnVOD133_FECHAR->Enabled  = VOD133_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_VOD155
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD155_FECHADO) == 1) {
                btnVOD155_FECHADO->Caption = "Fechada";
                shpVOD155_FECHADO->Brush->Color = clLime;
        }else{
                btnVOD155_FECHADO->Caption = "Não Fechada";
                shpVOD155_FECHADO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (CLP.RD(PC_HL_SODPG_VOD155_ABERTO) == 1) {
                btnVOD155_ABERTO->Caption = "Aberta";
                shpVOD155_ABERTO->Brush->Color = clYellow;
        }else{
                btnVOD155_ABERTO->Caption = "Não Aberta";
                shpVOD155_ABERTO->Brush->Color = clWhite;
        }
        //***********************************************************
        if (VOD155_ModoOpera == false){
                if (CLP.RD(CP_HL_SODPG_VOD155_ABRIR) == 1) {
                        shpVOD155_ABRIR->Brush->Color = clRed;
                        if (btnVOD155_FECHADO->Caption == "Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 0);
                        }
                        if (btnVOD155_ABERTO->Caption == "Não Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD155_ABERTO, 1);
                        }
                }else{
                        shpVOD155_ABRIR->Brush->Color = clWhite;
                }
                if (CLP.RD(CP_HL_SODPG_VOD155_FECHAR) == 1) {
                        shpVOD155_FECHAR->Brush->Color = clLime;
                        if (btnVOD155_ABERTO->Caption == "Aberta"){
                                CLP.WR(PC_HL_SODPG_VOD155_ABERTO, 0);
                        }
                        if (btnVOD155_FECHADO->Caption == "Não Fechada"){
                                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 1);
                        }
                }else{
                        shpVOD155_FECHAR->Brush->Color = clWhite;
                }
        }
        //***********************************************************
        btnVOD155_ABERTO->Enabled  = VOD155_ModoOpera;
        btnVOD155_FECHADO->Enabled = VOD155_ModoOpera;
        btnVOD155_ABRIR->Enabled   = VOD155_ModoOpera;
        btnVOD155_FECHAR->Enabled  = VOD155_ModoOpera;
        //***********************************************************
//==============================================================================
//SODPG_TSOD10
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD10_NIVELALTO) == 0 ){ //possui inversão
		shpTSOD10_NIVELALTO->Brush->Color = clYellow;
		btnTSOD10_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTSOD10_NIVELALTO->Brush->Color = clWhite;
		btnTSOD10_NIVELALTO->Caption = "Nível OK";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD10_NIVELBAIXO) == 1 ){
		shpTSOD10_NIVELBAIXO->Brush->Color = clRed;
		btnTSOD10_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpTSOD10_NIVELBAIXO->Brush->Color = clWhite;
		btnTSOD10_NIVELBAIXO->Caption = "Nível OK";
	};
	//***********************************************************
	lblTSOD10_NIVEL->Caption = CLP.RD(PC_HA_SODPG_TSOD10_NIVEL);
	lblTSOD10_NIVEL->Caption = FormatFloat("0.###",lblTSOD10_NIVEL->Caption.ToDouble()) ;
	pgrTSOD10_NIVEL->Position = (((lblTSOD10_NIVEL->Caption*100)-(0*100))*(100-0))/((1.934-0)*100); //metros

	//1.711 litros  1,934  m
	x = lblTSOD10_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.081){
		y1 = 0.0;
		y2 = 104.0;
		x1 = 0.000;
		x2 = 0.081;
	}else{
		if (x > 0.081 && x <= 0.181){
			y1 = 104.0;
			y2 = 232.0;
			x1 = 0.081;
			x2 = 0.181;
		}else{
			if (x > 0.181 && x <= 0.281){
				y1 = 232.0;
				y2 = 360.0;
				x1 = 0.181;
				x2 = 0.281;
			}else{
				if (x > 0.281 && x <= 0.381){
					y1 = 360.0;
					y2 = 489.0;
					x1 = 0.281;
					x2 = 0.381;
				}else{
					if (x > 0.381 && x <= 0.481){
						y1 = 489.0;
						y2 = 617.0;
						x1 = 0.381;
						x2 = 0.481;
					}else{
						if (x > 0.481 && x <= 0.581){
							y1 = 617.0;
							y2 = 745.0;
							x1 = 0.481;
							x2 = 0.581;
						}else{
							if (x > 0.581 && x <= 0.681){
								y1 = 745.0;
								y2 = 874.0;
								x1 = 0.581;
								x2 = 0.681;
							}else{
								if (x > 0.681 && x <= 0.781){
									y1 = 874.0;
									y2 = 1002.0;
									x1 = 0.681;
									x2 = 0.781;
								}else{
									if (x > 0.781 && x <= 0.881){
										y1 = 1002.0;
										y2 = 1130.0;
										x1 = 0.781;
										x2 = 0.881;
									}else{
										if (x > 0.881 && x <= 0.981){
											y1 = 1130.0;
											y2 = 1258.0;
											x1 = 0.881;
											x2 = 0.981;
										}else{
											if (x > 0.981 && x <= 1.081){
												y1 = 1258.0;
												y2 = 1387.0;
												x1 = 0.981;
												x2 = 1.081;
											}else{
												if (x > 1.081 && x <= 1.181){
													y1 = 1387.0;
													y2 = 1515.0;
													x1 = 1.081;
													x2 = 1.181;
												}else{
													if (x > 1.181 && x <= 1.281){
														y1 = 1515.0;
														y2 = 1643.0;
														x1 = 1.181;
														x2 = 1.281;
													}else{
														if (x > 1.281 && x <= 1.334){
															y1 = 1643.0;
															y2 = 1711.0;
															x1 = 1.281;
															x2 = 1.334;
														}
													}
												}
											}
										}
									}
								}
							}
						}
                                        }
                                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTSOD10_NIVEL_litros->Caption = (a * x) + b;
	if (x > x2){
	        y1 = 1643.0;
	        y2 = 1711.0;
	        x1 = 1.281;
	        x2 = 1.334;
	        lblTSOD10_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
	}
	lblTSOD10_NIVEL_litros->Caption = FormatFloat("0.##",lblTSOD10_NIVEL_litros->Caption.ToDouble());
	lblTSOD10_NIVEL_litros->Caption = lblTSOD10_NIVEL_litros->Caption + " litros";
	//***********************************************************
//==============================================================================
//SODPG_TSOD11
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD11_NIVELALTO) == 0 ){ //possui inversão
		shpTSOD11_NIVELALTO->Brush->Color = clYellow;
		btnTSOD11_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTSOD11_NIVELALTO->Brush->Color = clWhite;
		btnTSOD11_NIVELALTO->Caption = "Nível OK";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD11_NIVELBAIXO) == 1 ){
		shpTSOD11_NIVELBAIXO->Brush->Color = clRed;
		btnTSOD11_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpTSOD11_NIVELBAIXO->Brush->Color = clWhite;
		btnTSOD11_NIVELBAIXO->Caption = "Nível OK";
	};
	//***********************************************************
	lblTSOD11_NIVEL->Caption = CLP.RD(PC_HA_SODPG_TSOD11_NIVEL);
	lblTSOD11_NIVEL->Caption = FormatFloat("0.###",lblTSOD11_NIVEL->Caption.ToDouble()) ;
	pgrTSOD11_NIVEL->Position = (((lblTSOD11_NIVEL->Caption*100)-(0*100))*(100-0))/((1.370-0)*100); //metros

	//1.702 litros  1,370  m
	x = lblTSOD11_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 0.081){
		y1 = 0.0;
		y2 = 102.0;
		x1 = 0.000;
		x2 = 0.081;
	}else{
		if (x > 0.081 && x <= 0.181){
			y1 = 102.0;
			y2 = 228.0;
			x1 = 0.081;
			x2 = 0.181;
		}else{
			if (x > 0.181 && x <= 0.281){
				y1 = 228.0;
				y2 = 354.0;
				x1 = 0.181;
				x2 = 0.281;
			}else{
				if (x > 0.281 && x <= 0.381){
					y1 = 354.0;
					y2 = 480.0;
					x1 = 0.281;
					x2 = 0.381;
				}else{
					if (x > 0.381 && x <= 0.481){
						y1 = 480.0;
						y2 = 607.0;
						x1 = 0.381;
						x2 = 0.481;
					}else{
						if (x > 0.481 && x <= 0.581){
							y1 = 607.0;
							y2 = 733.0;
							x1 = 0.481;
							x2 = 0.581;
						}else{
							if (x > 0.581 && x <= 0.681){
								y1 = 733.0;
								y2 = 859.0;
								x1 = 0.581;
								x2 = 0.681;
							}else{
								if (x > 0.681 && x <= 0.781){
									y1 = 859.0;
									y2 = 935.0;
									x1 = 0.681;
									x2 = 0.781;
								}else{
									if (x > 0.781 && x <= 0.881){
										y1 = 935.0;
										y2 = 1111.0;
										x1 = 0.781;
										x2 = 0.881;
									}else{
										if (x > 0.881 && x <= 0.981){
											y1 = 1111.0;
											y2 = 1237.0;
											x1 = 0.881;
											x2 = 0.981;
										}else{
											if (x > 0.981 && x <= 1.081){
												y1 = 1237.0;
												y2 = 1363.0;
												x1 = 0.981;
												x2 = 1.081;
											}else{
												if (x > 1.081 && x <= 1.181){
													y1 = 1363.0;
													y2 = 1489.0;
													x1 = 1.081;
													x2 = 1.181;
												}else{
													if (x > 1.181 && x <= 1.281){
														y1 = 1489.0;
														y2 = 1615.0;
														x1 = 1.181;
														x2 = 1.281;
													}else{
														if (x > 1.281 && x <= 1.350){
															y1 = 1615.0;
															y2 = 1702.0;
															x1 = 1.281;
															x2 = 1.350;
														}
													}
												}
											}
										}
									}
								}
							}
						}
                    }
                }
			}
		}
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTSOD11_NIVEL_litros->Caption = (a * x) + b;
	if (x > x2){
	        y1 = 1615.0;
	        y2 = 1702.0;
	        x1 = 1.281;
	        x2 = 1.350;
	        lblTSOD11_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
	}
	lblTSOD11_NIVEL_litros->Caption = FormatFloat("0.##",lblTSOD11_NIVEL_litros->Caption.ToDouble());
	lblTSOD11_NIVEL_litros->Caption = lblTSOD11_NIVEL_litros->Caption + " litros";
	//***********************************************************
//==============================================================================
//SODPG_TSOD07
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD07_NIVELALTO) == 0 ){ //possui inversão
		shpTSOD07_NIVELALTO->Brush->Color = clYellow;
		btnTSOD07_NIVELALTO->Caption = "Nível Alto";
	}
	else{
		shpTSOD07_NIVELALTO->Brush->Color = clWhite;
		btnTSOD07_NIVELALTO->Caption = "Nível OK";
	};
	//***********************************************************
	if ( CLP.RD(PC_HL_SODPG_TSOD07_NIVELBAIXO) == 1 ){
		shpTSOD07_NIVELBAIXO->Brush->Color = clRed;
		btnTSOD07_NIVELBAIXO->Caption = "Nível Baixo";
	}
	else{
		shpTSOD07_NIVELBAIXO->Brush->Color = clWhite;
		btnTSOD07_NIVELBAIXO->Caption = "Nível OK";
	};
	//***********************************************************
	lblTSOD07_NIVEL->Caption = CLP.RD(PC_HA_SODPG_TSOD07_NIVEL);
	lblTSOD07_NIVEL->Caption = FormatFloat("0.###",lblTSOD07_NIVEL->Caption.ToDouble()) ;
	pgrTSOD07_NIVEL->Position = (((lblTSOD07_NIVEL->Caption*100)-(0*100))*(100-0))/((1.794-0)*100); //metros

	//5.714 litros  1,794  m
	x = lblTSOD07_NIVEL->Caption.ToDouble();
	if ( x >= 0.000 && x <= 1.794){
                y1 = 0.0;
                y2 = 5714;
                x1 = 0.000;
		x2 = 1.794;
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	lblTSOD07_NIVEL_litros->Caption = (a * x) + b;
	if (x > x2){
                y1 = 0.0;
                y2 = 5714;
                x1 = 0.000;
                x2 = 1.794;
	        lblTSOD07_NIVEL_litros->Caption = (((y2-y1)*(x-x1))/(x2-x1)) + y1;
	}
	lblTSOD07_NIVEL_litros->Caption = FormatFloat("0.##",lblTSOD07_NIVEL_litros->Caption.ToDouble());
	lblTSOD07_NIVEL_litros->Caption = lblTSOD07_NIVEL_litros->Caption + " litros";
	//***********************************************************
//==============================================================================
//==============================================================================
//TIMER DE ESCRITA, LEITURA E TRATAMENTO DOS SINAIS - FIM
//==============================================================================
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuStatusClick(TObject *Sender)
{
        pnlStatus->Visible  = true; //<<<<<<<
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuARMAZ_1Click(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlAODPG_1->Visible = true; //<<<<<<<
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuARMAZ_2Click(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = true; //<<<<<<<
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuSERVIOClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlSVCOD_1->Visible = true; //<<<<<<<
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuSERVIOTGClick(TObject *Sender)
{
        pnlStatus->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = true; //<<<<<<<
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRACAPClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = true; //<<<<<<<
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuAOLTGClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = true; //<<<<<<<
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuDASORClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = true; //<<<<<<<
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRACUGClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = true; //<<<<<<<
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRADUGClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = true; //<<<<<<<
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRARUGClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = true; //<<<<<<<
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRASISClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = true; //<<<<<<<
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRASRGClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = true; //<<<<<<<
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuCPTASClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = true; //<<<<<<<
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuMAQLEMClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = true; //<<<<<<<
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuGERENEClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = true; //<<<<<<<
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuPROTCClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = true; //<<<<<<<
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuRARCFClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = true; //<<<<<<<
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuVEDPMClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = true; //<<<<<<<
        pnlVEFPM->Visible   = false; 
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mnuVEFPMClick(TObject *Sender)
{
        pnlStatus->Visible  = false;
        pnlSVCOD_1->Visible = false;
        pnlSVCOD_2->Visible = false;
        pnlAODPG_1->Visible = false;
        pnlAODPG_2->Visible = false;
        pnlMaqLem->Visible  = false;
        pnlAOLTG->Visible   = false;
        pnlCPTAS->Visible   = false;
        pnlDASOR->Visible   = false;
        pnlGERENE->Visible  = false;
        pnlPROTC->Visible   = false;
        pnlRACAP->Visible   = false;
        pnlRACUG->Visible   = false;
        pnlRADUG->Visible   = false;
        pnlRARCF->Visible   = false;
        pnlRARUG->Visible   = false;
        pnlRASIS->Visible   = false;
        pnlRASRG->Visible   = false;
        pnlVEDPM->Visible   = false;
        pnlVEFPM->Visible   = true; //<<<<<<<
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormClose(TObject *Sender,
      TCloseAction &Action)
{
/*        for (int i = 3010; i < 3035; i++){ //ARM IO 1
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0);
        }
        for (int i = 3066; i < 3069; i++){ //ARM IO 2
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0);
        }*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormDestroy(TObject *Sender)
{
/*        for (int i = 3010; i < 3035; i++){ //ARM IO 1
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0);
        }
        for (int i = 3066; i < 3069; i++){ //ARM IO 2
                String tempMW = "%MW" ;
                tempMW += i;
                CLP.WR(tempMW, 0);
        }*/
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              ÓLEO DIESEL
//==============================================================================
//==============================================================================
void __fastcall TfrmPrincipal::btnModoOperacaoClick(TObject *Sender)
{
        if ( modooperacao == true ){
                lblModoOperacao->Caption = "Simulação OFF";
                lblModoOperacao->Font->Color = clRed;
                modooperacao = false;
                for (int i = 3010; i < 3036; i++){ //ARM IO 1
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP.WR(tempMW, 0);
                }
                for (int i = 3066; i < 3070; i++){ //ARM IO 2
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP.WR(tempMW, 0);
                }
        }
        else{
                lblModoOperacao->Caption = "Simulação ON";
                lblModoOperacao->Font->Color = clGreen;
                modooperacao = true;
                for (int i = 3010; i < 3036; i++){ //ARM IO 1
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP.WR(tempMW, 0XFFFF);
                }
                for (int i = 3066; i < 3070; i++){ //ARM IO 2
                        String tempMW = "%MW" ;
                        tempMW += i;
                        CLP.WR(tempMW, 0XFFFF);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnOperaAuto_CNODClick(TObject *Sender)
{
        if (operaauto_cnod == true) {
                operaauto_cnod = false;
                btnOperaAuto_CNOD->Caption = "Chaves de Nível em Manual";
                btnTAOD01_NIVELALTO->Enabled = true;
                btnTAOD01_TRANSBORDA->Enabled = true;
                btnTAOD02_NIVELALTO->Enabled = true;
                btnTAOD02_TRANSBORDA->Enabled = true;
                btnTAOD03_NIVELALTO->Enabled = true;
                btnTAOD03_TRANSBORDA->Enabled = true;
                btnTAOD04_NIVELALTO->Enabled = true;
                btnTAOD04_TRANSBORDA->Enabled = true;
                btnTAOD05_NIVELALTO->Enabled = true;
                btnTAOD05_TRANSBORDA->Enabled = true;
                btnTAOD06_NIVELALTO->Enabled = true;
                btnTAOD06_TRANSBORDA->Enabled = true;
                btnTTOD12_NIVELALTO->Enabled = true;
                btnTTOD13_NIVELALTO->Enabled = true;
                btnTSOD07_NIVELALTO->Enabled = true;
                btnTSOD07_NIVELBAIXO->Enabled = true;
                btnTSOD08_NIVELALTO->Enabled = true;
                btnTSOD08_NIVELBAIXO->Enabled = true;
                btnTSOD09_NIVELALTO->Enabled = true;
                btnTSOD09_NIVELBAIXO->Enabled = true;
                btnTSOD10_NIVELALTO->Enabled = true;
                btnTSOD10_NIVELBAIXO->Enabled = true;
                btnTSOD11_NIVELALTO->Enabled = true;
                btnTSOD11_NIVELBAIXO->Enabled = true;
        }
        else{
                operaauto_cnod = true;
                btnOperaAuto_CNOD->Caption = "Chaves de Nível em Automático";
                btnTAOD01_NIVELALTO->Enabled = false;
                btnTAOD01_TRANSBORDA->Enabled = false;
                btnTAOD02_NIVELALTO->Enabled = false;
                btnTAOD02_TRANSBORDA->Enabled = false;
                btnTAOD03_NIVELALTO->Enabled = false;
                btnTAOD03_TRANSBORDA->Enabled = false;
                btnTAOD04_NIVELALTO->Enabled = false;
                btnTAOD04_TRANSBORDA->Enabled = false;
                btnTAOD05_NIVELALTO->Enabled = false;
                btnTAOD05_TRANSBORDA->Enabled = false;
                btnTAOD06_NIVELALTO->Enabled = false;
                btnTAOD06_TRANSBORDA->Enabled = false;
                btnTTOD12_NIVELALTO->Enabled = false;
                btnTTOD13_NIVELALTO->Enabled = false;
                btnTSOD07_NIVELALTO->Enabled = false;
                btnTSOD07_NIVELBAIXO->Enabled = false;
                btnTSOD08_NIVELALTO->Enabled = false;
                btnTSOD08_NIVELBAIXO->Enabled = false;
                btnTSOD09_NIVELALTO->Enabled = false;
                btnTSOD09_NIVELBAIXO->Enabled = false;
                btnTSOD10_NIVELALTO->Enabled = false;
                btnTSOD10_NIVELBAIXO->Enabled = false;
                btnTSOD11_NIVELALTO->Enabled = false;
                btnTSOD11_NIVELBAIXO->Enabled = false;
        }

        btnOperaAuto_CNOD_ex1->Caption = btnOperaAuto_CNOD->Caption;
        btnOperaAuto_CNOD_ex2->Caption = btnOperaAuto_CNOD->Caption;
        btnOperaAuto_CNOD_ex3->Caption = btnOperaAuto_CNOD->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrOperaAutoCNODTimer(TObject *Sender)
{
        if ( (CLP.RD(PC_HA_AODPG_TAOD01_NIVEL) >= 1.7) && (CLP.RD(PC_HL_AODPG_TAOD01_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TAOD01_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD01_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TAOD01_NIVEL) < 1.7)){
                        CLP.WR(PC_HL_AODPG_TAOD01_NIVELALTO, 1);
                }
        }
        if ( (CLP.RD(PC_HA_AODPG_TAOD01_NIVEL) >= 1.85) && (CLP.RD(PC_HL_AODPG_TAOD01_TRANSBORDA) == 0)){
                CLP.WR(PC_HL_AODPG_TAOD01_TRANSBORDA, 1);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD01_TRANSBORDA) == 1) && (CLP.RD(PC_HA_AODPG_TAOD01_NIVEL) < 1.85)){
                        CLP.WR(PC_HL_AODPG_TAOD01_TRANSBORDA, 0);
                }
        }

          if ((CLP.RD(PC_HA_AODPG_TAOD02_NIVEL) >= 1.7) && (CLP.RD(PC_HL_AODPG_TAOD02_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TAOD02_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD02_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TAOD02_NIVEL) < 1.7)){
                        CLP.WR(PC_HL_AODPG_TAOD02_NIVELALTO, 1);
                }
        }
        if ( (CLP.RD(PC_HA_AODPG_TAOD02_NIVEL) >= 1.85) && (CLP.RD(PC_HL_AODPG_TAOD02_TRANSBORDA) == 0)){
                CLP.WR(PC_HL_AODPG_TAOD02_TRANSBORDA, 1);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD02_TRANSBORDA) == 1) && (CLP.RD(PC_HA_AODPG_TAOD02_NIVEL) < 1.85)){
                        CLP.WR(PC_HL_AODPG_TAOD02_TRANSBORDA, 0);
                }
        }

        if ((CLP.RD(PC_HA_AODPG_TAOD03_NIVEL) >= 0.85) && (CLP.RD(PC_HL_AODPG_TAOD03_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TAOD03_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD03_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TAOD03_NIVEL) < 0.85)){
                        CLP.WR(PC_HL_AODPG_TAOD03_NIVELALTO, 1);
                }
        }
        if ( (CLP.RD(PC_HA_AODPG_TAOD03_NIVEL) >= 0.95) && (CLP.RD(PC_HL_AODPG_TAOD03_TRANSBORDA) == 0)){
                CLP.WR(PC_HL_AODPG_TAOD03_TRANSBORDA, 1);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD03_TRANSBORDA) == 1) && (CLP.RD(PC_HA_AODPG_TAOD03_NIVEL) < 0.95)){
                        CLP.WR(PC_HL_AODPG_TAOD03_TRANSBORDA, 0);
                }
        }

        if ((CLP.RD(PC_HA_AODPG_TAOD04_NIVEL) >= 2.1) && (CLP.RD(PC_HL_AODPG_TAOD04_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TAOD04_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD04_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TAOD04_NIVEL) < 2.1)){
                        CLP.WR(PC_HL_AODPG_TAOD04_NIVELALTO, 1);
                }
        }
        if ( (CLP.RD(PC_HA_AODPG_TAOD04_NIVEL) >= 2.5) && (CLP.RD(PC_HL_AODPG_TAOD04_TRANSBORDA) == 0)){
                CLP.WR(PC_HL_AODPG_TAOD04_TRANSBORDA, 1);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD04_TRANSBORDA) == 1) && (CLP.RD(PC_HA_AODPG_TAOD04_NIVEL) < 2.5)){
                        CLP.WR(PC_HL_AODPG_TAOD04_TRANSBORDA, 0);
                }
        }

        if ((CLP.RD(PC_HA_AODPG_TAOD05_NIVEL) >= 2.1) && (CLP.RD(PC_HL_AODPG_TAOD05_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TAOD05_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD05_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TAOD05_NIVEL) < 2.1)){
                        CLP.WR(PC_HL_AODPG_TAOD05_NIVELALTO, 1);
                }
        }
        if ( (CLP.RD(PC_HA_AODPG_TAOD05_NIVEL) >= 2.4) && (CLP.RD(PC_HL_AODPG_TAOD05_TRANSBORDA) == 0)){
                CLP.WR(PC_HL_AODPG_TAOD05_TRANSBORDA, 1);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD05_TRANSBORDA) == 1) && (CLP.RD(PC_HA_AODPG_TAOD05_NIVEL) < 2.4)){
                        CLP.WR(PC_HL_AODPG_TAOD05_TRANSBORDA, 0);
                }
        }

        if ((CLP.RD(PC_HA_AODPG_TAOD06_NIVEL) >= 2.1) && (CLP.RD(PC_HL_AODPG_TAOD06_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TAOD06_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD06_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TAOD06_NIVEL) < 2.1)){
                        CLP.WR(PC_HL_AODPG_TAOD06_NIVELALTO, 1);
                }
        }
        if ( (CLP.RD(PC_HA_AODPG_TAOD06_NIVEL) >= 2.4) && (CLP.RD(PC_HL_AODPG_TAOD06_TRANSBORDA) == 0)){
                CLP.WR(PC_HL_AODPG_TAOD06_TRANSBORDA, 1);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TAOD06_TRANSBORDA) == 1) && (CLP.RD(PC_HA_AODPG_TAOD06_NIVEL) < 2.4)){
                        CLP.WR(PC_HL_AODPG_TAOD06_TRANSBORDA, 0);
                }
        }

        if ((CLP.RD(PC_HA_AODPG_TTOD12_NIVEL) >= 0.9) && (CLP.RD(PC_HL_AODPG_TTOD12_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TTOD12_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TTOD12_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TTOD12_NIVEL) < 0.9)){
                        CLP.WR(PC_HL_AODPG_TTOD12_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_AODPG_TTOD13_NIVEL) >= 0.9) && (CLP.RD(PC_HL_AODPG_TTOD13_NIVELALTO) == 1)){
                CLP.WR(PC_HL_AODPG_TTOD13_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_AODPG_TTOD13_NIVELALTO) == 0) && (CLP.RD(PC_HA_AODPG_TTOD13_NIVEL) < 0.9)){
                        CLP.WR(PC_HL_AODPG_TTOD13_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD08_NIVEL) >= 2.2) && (CLP.RD(PC_HL_SODPG_TSOD08_NIVELALTO) == 1)){
                CLP.WR(PC_HL_SODPG_TSOD08_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD08_NIVELALTO) == 0) && (CLP.RD(PC_HA_SODPG_TSOD08_NIVEL) < 2.2)){
                        CLP.WR(PC_HL_SODPG_TSOD08_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD08_NIVEL) <= 1.1) && (CLP.RD(PC_HL_SODPG_TSOD08_NIVELBAIXO) == 0)){
                CLP.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, 1);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD08_NIVELBAIXO) == 1) && (CLP.RD(PC_HA_SODPG_TSOD08_NIVEL) > 1.1)){
                        CLP.WR(PC_HL_SODPG_TSOD08_NIVELBAIXO, 0);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD09_NIVEL) >= 2.2) && (CLP.RD(PC_HL_SODPG_TSOD09_NIVELALTO) == 1)){
                CLP.WR(PC_HL_SODPG_TSOD09_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD09_NIVELALTO) == 0) && (CLP.RD(PC_HA_SODPG_TSOD09_NIVEL) < 2.2)){
                        CLP.WR(PC_HL_SODPG_TSOD09_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD09_NIVEL) <= 1.1) && (CLP.RD(PC_HL_SODPG_TSOD09_NIVELBAIXO) == 0)){
                CLP.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, 1);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD09_NIVELBAIXO) == 1) && (CLP.RD(PC_HA_SODPG_TSOD09_NIVEL) > 1.1)){
                        CLP.WR(PC_HL_SODPG_TSOD09_NIVELBAIXO, 0);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD07_NIVEL) >= 1.5) && (CLP.RD(PC_HL_SODPG_TSOD07_NIVELALTO) == 1)){
                CLP.WR(PC_HL_SODPG_TSOD07_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD07_NIVELALTO) == 0) && (CLP.RD(PC_HA_SODPG_TSOD07_NIVEL) < 1.5)){
                        CLP.WR(PC_HL_SODPG_TSOD07_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD07_NIVEL) <= 0.5) && (CLP.RD(PC_HL_SODPG_TSOD07_NIVELBAIXO) == 0)){
                CLP.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, 1);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD07_NIVELBAIXO) == 1) && (CLP.RD(PC_HA_SODPG_TSOD07_NIVEL) > 0.5)){
                        CLP.WR(PC_HL_SODPG_TSOD07_NIVELBAIXO, 0);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD10_NIVEL) >= 1.2) && (CLP.RD(PC_HL_SODPG_TSOD10_NIVELALTO) == 1)){
                CLP.WR(PC_HL_SODPG_TSOD10_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD10_NIVELALTO) == 0) && (CLP.RD(PC_HA_SODPG_TSOD10_NIVEL) < 1.2)){
                        CLP.WR(PC_HL_SODPG_TSOD10_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD10_NIVEL) <= 0.5) && (CLP.RD(PC_HL_SODPG_TSOD10_NIVELBAIXO) == 0)){
                CLP.WR(PC_HL_SODPG_TSOD10_NIVELBAIXO, 1);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD10_NIVELBAIXO) == 1) && (CLP.RD(PC_HA_SODPG_TSOD10_NIVEL) > 0.5)){
                        CLP.WR(PC_HL_SODPG_TSOD10_NIVELBAIXO, 0);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD11_NIVEL) >= 1.2) && (CLP.RD(PC_HL_SODPG_TSOD11_NIVELALTO) == 1)){
                CLP.WR(PC_HL_SODPG_TSOD11_NIVELALTO, 0);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD11_NIVELALTO) == 0) && (CLP.RD(PC_HA_SODPG_TSOD11_NIVEL) < 1.2)){
                        CLP.WR(PC_HL_SODPG_TSOD11_NIVELALTO, 1);
                }
        }

        if ((CLP.RD(PC_HA_SODPG_TSOD11_NIVEL) <= 0.5) && (CLP.RD(PC_HL_SODPG_TSOD11_NIVELBAIXO) == 0)){
                CLP.WR(PC_HL_SODPG_TSOD11_NIVELBAIXO, 1);
        }else{
                if ((CLP.RD(PC_HL_SODPG_TSOD11_NIVELBAIXO) == 1) && (CLP.RD(PC_HA_SODPG_TSOD11_NIVEL) > 0.5)){
                        CLP.WR(PC_HL_SODPG_TSOD11_NIVELBAIXO, 0);
                }
        }

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD01_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTAOD01_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTAOD01_NIVEL->Text = FormatFloat("0.###",txtTAOD01_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTAOD01_NIVEL->Text.ToDouble()) > 1.942){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TAOD01_NIVEL, (txtTAOD01_NIVEL->Text.ToDouble()) );
                }
        }

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD01_NIVELALTOClick(TObject *Sender)
{
        if (btnTAOD01_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TAOD01_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD01_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD01_TRANSBORDAClick(TObject *Sender)
{
        if (btnTAOD01_TRANSBORDA->Caption == "Sem Transbordo"){
		CLP.WR( PC_HL_AODPG_TAOD01_TRANSBORDA, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD01_TRANSBORDA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD02_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTAOD02_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTAOD02_NIVEL->Text = FormatFloat("0.###",txtTAOD02_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTAOD02_NIVEL->Text.ToDouble()) > 1.942){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TAOD02_NIVEL, (txtTAOD02_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD02_NIVELALTOClick(TObject *Sender)
{
        if (btnTAOD02_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TAOD02_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD02_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD02_TRANSBORDAClick(TObject *Sender)
{
        if (btnTAOD02_TRANSBORDA->Caption == "Sem Transbordo"){
		CLP.WR( PC_HL_AODPG_TAOD02_TRANSBORDA, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD02_TRANSBORDA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD03_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTAOD03_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTAOD03_NIVEL->Text = FormatFloat("0.###",txtTAOD03_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTAOD03_NIVEL->Text.ToDouble()) > 1.014){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TAOD03_NIVEL, (txtTAOD03_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD03_NIVELALTOClick(TObject *Sender)
{
        if (btnTAOD03_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TAOD03_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD03_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD03_TRANSBORDAClick(TObject *Sender)
{
        if (btnTAOD03_TRANSBORDA->Caption == "Sem Transbordo"){
		CLP.WR( PC_HL_AODPG_TAOD03_TRANSBORDA, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD03_TRANSBORDA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD04_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTAOD04_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTAOD04_NIVEL->Text = FormatFloat("0.###",txtTAOD04_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTAOD04_NIVEL->Text.ToDouble()) > 2.810){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TAOD04_NIVEL, (txtTAOD04_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD04_NIVELALTOClick(TObject *Sender)
{
        if (btnTAOD04_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TAOD04_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD04_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD04_TRANSBORDAClick(TObject *Sender)
{
        if (btnTAOD04_TRANSBORDA->Caption == "Sem Transbordo"){
		CLP.WR( PC_HL_AODPG_TAOD04_TRANSBORDA, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD04_TRANSBORDA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD05_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTAOD05_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTAOD05_NIVEL->Text = FormatFloat("0.###",txtTAOD05_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTAOD05_NIVEL->Text.ToDouble()) > 2.57){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TAOD05_NIVEL, (txtTAOD05_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD05_NIVELALTOClick(TObject *Sender)
{
        if (btnTAOD05_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TAOD05_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD05_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD05_TRANSBORDAClick(TObject *Sender)
{
        if (btnTAOD05_TRANSBORDA->Caption == "Sem Transbordo"){
		CLP.WR( PC_HL_AODPG_TAOD05_TRANSBORDA, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD05_TRANSBORDA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD06_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTAOD06_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTAOD06_NIVEL->Text = FormatFloat("0.###",txtTAOD06_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTAOD06_NIVEL->Text.ToDouble()) > 2.57){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TAOD06_NIVEL, (txtTAOD06_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD06_NIVELALTOClick(TObject *Sender)
{
        if (btnTAOD06_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TAOD06_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD06_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTAOD06_TRANSBORDAClick(TObject *Sender)
{
        if (btnTAOD06_TRANSBORDA->Caption == "Sem Transbordo"){
		CLP.WR( PC_HL_AODPG_TAOD06_TRANSBORDA, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TAOD06_TRANSBORDA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD012_ABRIRClick(TObject *Sender)
{
        if (btnVOD012_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 0);
        }
        if (btnVOD012_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD012_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD012_FECHARClick(TObject *Sender)
{
        if (btnVOD012_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD012_ABERTO, 0);
        }
        if (btnVOD012_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD012_RTAUTOClick(TObject *Sender)
{
        if (VOD012_RetornoAuto == true) {
                VOD012_RetornoAuto = false;
                btnVOD012_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD012_RetornoAuto = true;
                btnVOD012_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD012_MODOClick(TObject *Sender)
{
        if (VOD012_ModoOpera == true) {
                VOD012_ModoOpera = false;
                btnVOD012_MODO->Caption = "Remoto";
        }else{
                VOD012_ModoOpera = true;
                btnVOD012_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD012_ABERTOClick(TObject *Sender)
{
        if (btnVOD012_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD012_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD012_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD012_FECHADOClick(TObject *Sender)
{
        if (btnVOD012_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD012_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD013_ABRIRClick(TObject *Sender)
{
        if (btnVOD013_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 0);
        }
        if (btnVOD013_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD013_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD013_FECHARClick(TObject *Sender)
{
        if (btnVOD013_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD013_ABERTO, 0);
        }
        if (btnVOD013_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD013_RTAUTOClick(TObject *Sender)
{
        if (VOD013_RetornoAuto == true) {
                VOD013_RetornoAuto = false;
                btnVOD013_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD013_RetornoAuto = true;
                btnVOD013_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD013_MODOClick(TObject *Sender)
{
        if (VOD013_ModoOpera == true) {
                VOD013_ModoOpera = false;
                btnVOD013_MODO->Caption = "Remoto";
        }else{
                VOD013_ModoOpera = true;
                btnVOD013_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD013_ABERTOClick(TObject *Sender)
{
        if (btnVOD013_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD013_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD013_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD013_FECHADOClick(TObject *Sender)
{
        if (btnVOD013_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD013_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD014_ABRIRClick(TObject *Sender)
{
        if (btnVOD014_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 0);
        }
        if (btnVOD014_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD014_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD014_FECHARClick(TObject *Sender)
{
        if (btnVOD014_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD014_ABERTO, 0);
        }
        if (btnVOD014_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD014_RTAUTOClick(TObject *Sender)
{
        if (VOD014_RetornoAuto == true) {
                VOD014_RetornoAuto = false;
                btnVOD014_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD014_RetornoAuto = true;
                btnVOD014_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD014_MODOClick(TObject *Sender)
{
        if (VOD014_ModoOpera == true) {
                VOD014_ModoOpera = false;
                btnVOD014_MODO->Caption = "Remoto";
        }else{
                VOD014_ModoOpera = true;
                btnVOD014_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD014_ABERTOClick(TObject *Sender)
{
        if (btnVOD014_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD014_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD014_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD014_FECHADOClick(TObject *Sender)
{
        if (btnVOD014_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD014_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD015_ABRIRClick(TObject *Sender)
{
        if (btnVOD015_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 0);
        }
        if (btnVOD015_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD015_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD015_FECHARClick(TObject *Sender)
{
        if (btnVOD015_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD015_ABERTO, 0);
        }
        if (btnVOD015_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD015_RTAUTOClick(TObject *Sender)
{
        if (VOD015_RetornoAuto == true) {
                VOD015_RetornoAuto = false;
                btnVOD015_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD015_RetornoAuto = true;
                btnVOD015_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD015_MODOClick(TObject *Sender)
{
        if (VOD015_ModoOpera == true) {
                VOD015_ModoOpera = false;
                btnVOD015_MODO->Caption = "Remoto";
        }else{
                VOD015_ModoOpera = true;
                btnVOD015_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD015_ABERTOClick(TObject *Sender)
{
        if (btnVOD015_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD015_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD015_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD015_FECHADOClick(TObject *Sender)
{
        if (btnVOD015_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD015_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD016_ABRIRClick(TObject *Sender)
{
        if (btnVOD016_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 0);
        }
        if (btnVOD016_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD016_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD016_FECHARClick(TObject *Sender)
{
        if (btnVOD016_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD016_ABERTO, 0);
        }
        if (btnVOD016_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD016_RTAUTOClick(TObject *Sender)
{
        if (VOD016_RetornoAuto == true) {
                VOD016_RetornoAuto = false;
                btnVOD016_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD016_RetornoAuto = true;
                btnVOD016_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD016_MODOClick(TObject *Sender)
{
        if (VOD016_ModoOpera == true) {
                VOD016_ModoOpera = false;
                btnVOD016_MODO->Caption = "Remoto";
        }else{
                VOD016_ModoOpera = true;
                btnVOD016_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD016_ABERTOClick(TObject *Sender)
{
        if (btnVOD016_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD016_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD016_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD016_FECHADOClick(TObject *Sender)
{
        if (btnVOD016_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD016_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD017_ABRIRClick(TObject *Sender)
{
        if (btnVOD017_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 0);
        }
        if (btnVOD017_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD017_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD017_FECHARClick(TObject *Sender)
{
        if (btnVOD017_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD017_ABERTO, 0);
        }
        if (btnVOD017_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD017_RTAUTOClick(TObject *Sender)
{
        if (VOD017_RetornoAuto == true) {
                VOD017_RetornoAuto = false;
                btnVOD017_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD017_RetornoAuto = true;
                btnVOD017_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD017_MODOClick(TObject *Sender)
{
        if (VOD017_ModoOpera == true) {
                VOD017_ModoOpera = false;
                btnVOD017_MODO->Caption = "Remoto";
        }else{
                VOD017_ModoOpera = true;
                btnVOD017_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD017_ABERTOClick(TObject *Sender)
{
        if (btnVOD017_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD017_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD017_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD017_FECHADOClick(TObject *Sender)
{
        if (btnVOD017_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD017_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD059_ABRIRClick(TObject *Sender)
{
        if (btnVOD059_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 0);
        }
        if (btnVOD059_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD059_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD059_FECHARClick(TObject *Sender)
{
        if (btnVOD059_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD059_ABERTO, 0);
        }
        if (btnVOD059_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD059_RTAUTOClick(TObject *Sender)
{
        if (VOD059_RetornoAuto == true) {
                VOD059_RetornoAuto = false;
                btnVOD059_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD059_RetornoAuto = true;
                btnVOD059_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD059_MODOClick(TObject *Sender)
{
        if (VOD059_ModoOpera == true) {
                VOD059_ModoOpera = false;
                btnVOD059_MODO->Caption = "Remoto";
        }else{
                VOD059_ModoOpera = true;
                btnVOD059_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD059_ABERTOClick(TObject *Sender)
{
        if (btnVOD059_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD059_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD059_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD059_FECHADOClick(TObject *Sender)
{
        if (btnVOD059_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD059_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD060_ABRIRClick(TObject *Sender)
{
        if (btnVOD060_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 0);
        }
        if (btnVOD060_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD060_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD060_FECHARClick(TObject *Sender)
{
        if (btnVOD060_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD060_ABERTO, 0);
        }
        if (btnVOD060_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD060_RTAUTOClick(TObject *Sender)
{
        if (VOD060_RetornoAuto == true) {
                VOD060_RetornoAuto = false;
                btnVOD060_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD060_RetornoAuto = true;
                btnVOD060_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD060_MODOClick(TObject *Sender)
{
        if (VOD060_ModoOpera == true) {
                VOD060_ModoOpera = false;
                btnVOD060_MODO->Caption = "Remoto";
        }else{
                VOD060_ModoOpera = true;
                btnVOD060_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD060_ABERTOClick(TObject *Sender)
{
        if (btnVOD060_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD060_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD060_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD060_FECHADOClick(TObject *Sender)
{
        if (btnVOD060_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD060_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD061_ABRIRClick(TObject *Sender)
{
        if (btnVOD061_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 0);
        }
        if (btnVOD061_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD061_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD061_FECHARClick(TObject *Sender)
{
        if (btnVOD061_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD061_ABERTO, 0);
        }
        if (btnVOD061_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD061_RTAUTOClick(TObject *Sender)
{
        if (VOD061_RetornoAuto == true) {
                VOD061_RetornoAuto = false;
                btnVOD061_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD061_RetornoAuto = true;
                btnVOD061_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD061_MODOClick(TObject *Sender)
{
        if (VOD061_ModoOpera == true) {
                VOD061_ModoOpera = false;
                btnVOD061_MODO->Caption = "Remoto";
        }else{
                VOD061_ModoOpera = true;
                btnVOD061_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD061_ABERTOClick(TObject *Sender)
{
        if (btnVOD061_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD061_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD061_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD061_FECHADOClick(TObject *Sender)
{
        if (btnVOD061_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD061_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD062_ABRIRClick(TObject *Sender)
{
        if (btnVOD062_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 0);
        }
        if (btnVOD062_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD062_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD062_FECHARClick(TObject *Sender)
{
        if (btnVOD062_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD062_ABERTO, 0);
        }
        if (btnVOD062_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD062_RTAUTOClick(TObject *Sender)
{
        if (VOD062_RetornoAuto == true) {
                VOD062_RetornoAuto = false;
                btnVOD062_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD062_RetornoAuto = true;
                btnVOD062_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD062_MODOClick(TObject *Sender)
{
        if (VOD062_ModoOpera == true) {
                VOD062_ModoOpera = false;
                btnVOD062_MODO->Caption = "Remoto";
        }else{
                VOD062_ModoOpera = true;
                btnVOD062_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD062_ABERTOClick(TObject *Sender)
{
        if (btnVOD062_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD062_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD062_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD062_FECHADOClick(TObject *Sender)
{
        if (btnVOD062_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD062_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD063_ABRIRClick(TObject *Sender)
{
        if (btnVOD063_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 0);
        }
        if (btnVOD063_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD063_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD063_FECHARClick(TObject *Sender)
{
        if (btnVOD063_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD063_ABERTO, 0);
        }
        if (btnVOD063_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD063_RTAUTOClick(TObject *Sender)
{
        if (VOD063_RetornoAuto == true) {
                VOD063_RetornoAuto = false;
                btnVOD063_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD063_RetornoAuto = true;
                btnVOD063_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD063_MODOClick(TObject *Sender)
{
        if (VOD063_ModoOpera == true) {
                VOD063_ModoOpera = false;
                btnVOD063_MODO->Caption = "Remoto";
        }else{
                VOD063_ModoOpera = true;
                btnVOD063_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD063_ABERTOClick(TObject *Sender)
{
        if (btnVOD063_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD063_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD063_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD063_FECHADOClick(TObject *Sender)
{
        if (btnVOD063_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD063_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD064_ABRIRClick(TObject *Sender)
{
        if (btnVOD064_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 0);
        }
        if (btnVOD064_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD064_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD064_FECHARClick(TObject *Sender)
{
        if (btnVOD064_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD064_ABERTO, 0);
        }
        if (btnVOD064_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD064_RTAUTOClick(TObject *Sender)
{
        if (VOD064_RetornoAuto == true) {
                VOD064_RetornoAuto = false;
                btnVOD064_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD064_RetornoAuto = true;
                btnVOD064_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD064_MODOClick(TObject *Sender)
{
        if (VOD064_ModoOpera == true) {
                VOD064_ModoOpera = false;
                btnVOD064_MODO->Caption = "Remoto";
        }else{
                VOD064_ModoOpera = true;
                btnVOD064_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD064_ABERTOClick(TObject *Sender)
{
        if (btnVOD064_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD064_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD064_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD064_FECHADOClick(TObject *Sender)
{
        if (btnVOD064_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD064_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD005_ABRIRClick(TObject *Sender)
{
        if (btnVOD005_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 0);
        }
        if (btnVOD005_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD005_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD005_FECHARClick(TObject *Sender)
{
        if (btnVOD005_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD005_ABERTO, 0);
        }
        if (btnVOD005_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD005_MODOClick(TObject *Sender)
{
        if (VOD005_ModoOpera == true) {
                VOD005_ModoOpera = false;
                btnVOD005_MODO->Caption = "Remoto";
        }else{
                VOD005_ModoOpera = true;
                btnVOD005_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD005_ABERTOClick(TObject *Sender)
{
        if (btnVOD005_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD005_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD005_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD005_FECHADOClick(TObject *Sender)
{
        if (btnVOD005_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD005_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD010_ABRIRClick(TObject *Sender)
{
        if (btnVOD010_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 0);
        }
        if (btnVOD010_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD010_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD010_FECHARClick(TObject *Sender)
{
        if (btnVOD010_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD010_ABERTO, 0);
        }
        if (btnVOD010_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD010_MODOClick(TObject *Sender)
{
        if (VOD010_ModoOpera == true) {
                VOD010_ModoOpera = false;
                btnVOD010_MODO->Caption = "Remoto";
        }else{
                VOD010_ModoOpera = true;
                btnVOD010_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD010_ABERTOClick(TObject *Sender)
{
        if (btnVOD010_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD010_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD010_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD010_FECHADOClick(TObject *Sender)
{
        if (btnVOD010_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD010_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD030_ABRIRClick(TObject *Sender)
{
        if (btnVOD030_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 0);
        }
        if (btnVOD030_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD030_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD030_FECHARClick(TObject *Sender)
{
        if (btnVOD030_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD030_ABERTO, 0);
        }
        if (btnVOD030_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD030_MODOClick(TObject *Sender)
{
        if (VOD030_ModoOpera == true) {
                VOD030_ModoOpera = false;
                btnVOD030_MODO->Caption = "Remoto";
        }else{
                VOD030_ModoOpera = true;
                btnVOD030_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD030_ABERTOClick(TObject *Sender)
{
        if (btnVOD030_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD030_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD030_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD030_FECHADOClick(TObject *Sender)
{
        if (btnVOD030_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD030_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD031_ABRIRClick(TObject *Sender)
{
        if (btnVOD031_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 0);
        }
        if (btnVOD031_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD031_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD031_FECHARClick(TObject *Sender)
{
        if (btnVOD031_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD031_ABERTO, 0);
        }
        if (btnVOD031_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD031_MODOClick(TObject *Sender)
{
        if (VOD031_ModoOpera == true) {
                VOD031_ModoOpera = false;
                btnVOD031_MODO->Caption = "Remoto";
        }else{
                VOD031_ModoOpera = true;
                btnVOD031_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD031_ABERTOClick(TObject *Sender)
{
        if (btnVOD031_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD031_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD031_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD031_FECHADOClick(TObject *Sender)
{
        if (btnVOD031_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD031_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD035_ABRIRClick(TObject *Sender)
{
        if (btnVOD035_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 0);
        }
        if (btnVOD035_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD035_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD035_FECHARClick(TObject *Sender)
{
        if (btnVOD035_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD035_ABERTO, 0);
        }
        if (btnVOD035_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD035_MODOClick(TObject *Sender)
{
        if (VOD035_ModoOpera == true) {
                VOD035_ModoOpera = false;
                btnVOD035_MODO->Caption = "Remoto";
        }else{
                VOD035_ModoOpera = true;
                btnVOD035_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD035_ABERTOClick(TObject *Sender)
{
        if (btnVOD035_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD035_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD035_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD035_FECHADOClick(TObject *Sender)
{
        if (btnVOD035_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD035_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD043_ABRIRClick(TObject *Sender)
{
        if (btnVOD043_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 0);
        }
        if (btnVOD043_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD043_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD043_FECHARClick(TObject *Sender)
{
        if (btnVOD043_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD043_ABERTO, 0);
        }
        if (btnVOD043_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD043_MODOClick(TObject *Sender)
{
        if (VOD043_ModoOpera == true) {
                VOD043_ModoOpera = false;
                btnVOD043_MODO->Caption = "Remoto";
        }else{
                VOD043_ModoOpera = true;
                btnVOD043_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD043_ABERTOClick(TObject *Sender)
{
        if (btnVOD043_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD043_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD043_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD043_FECHADOClick(TObject *Sender)
{
        if (btnVOD043_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD043_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD066_ABRIRClick(TObject *Sender)
{
        if (btnVOD066_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 0);
        }
        if (btnVOD066_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD066_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD066_FECHARClick(TObject *Sender)
{
        if (btnVOD066_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_AODPG_VOD066_ABERTO, 0);
        }
        if (btnVOD066_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD066_MODOClick(TObject *Sender)
{
        if (VOD066_ModoOpera == true) {
                VOD066_ModoOpera = false;
                btnVOD066_MODO->Caption = "Remoto";
        }else{
                VOD066_ModoOpera = true;
                btnVOD066_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD066_ABERTOClick(TObject *Sender)
{
        if (btnVOD066_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_AODPG_VOD066_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD066_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD066_FECHADOClick(TObject *Sender)
{
        if (btnVOD066_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_AODPG_VOD066_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTTOD12_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTTOD12_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTTOD12_NIVEL->Text = FormatFloat("0.###",txtTTOD12_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTTOD12_NIVEL->Text.ToDouble()) > 1.00){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TTOD12_NIVEL, (txtTTOD12_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTTOD12_NIVELALTOClick(TObject *Sender)
{
        if (btnTTOD12_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TTOD12_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TTOD12_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTTOD13_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTTOD13_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTTOD13_NIVEL->Text = FormatFloat("0.###",txtTTOD13_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTTOD13_NIVEL->Text.ToDouble()) > 1.066){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_AODPG_TTOD13_NIVEL, (txtTTOD13_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTTOD13_NIVELALTOClick(TObject *Sender)
{
        if (btnTTOD13_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_AODPG_TTOD13_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_AODPG_TTOD13_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD1_LIGADOClick(TObject *Sender)
{
        if (btnBETOD1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AODPG_BETOD1_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_BETOD1_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD1_EMREMClick(TObject *Sender)
{
        if (btnBETOD1_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_AODPG_BETOD1_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_BETOD1_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD1_LIGARClick(TObject *Sender)
{
        if (btnBETOD1_LIGADO->Caption == "Parado"){
                tmrBETOD1_DESLIGAR->Enabled = false;
                tmrBETOD1_LIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD1_DESLIGARClick(TObject *Sender)
{
        if (btnBETOD1_LIGADO->Caption == "Ligado"){
                tmrBETOD1_LIGAR->Enabled = false;
                tmrBETOD1_DESLIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBETOD1_LIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_AODPG_BETOD1_LIGADO, 1 );
        tmrBETOD1_LIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBETOD1_DESLIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_AODPG_BETOD1_LIGADO, 0 );
        tmrBETOD1_DESLIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD1_PARAREMERGClick(TObject *Sender)
{
        if (btnBETOD1_PARAREMERG->Caption == "Parar em Emergência"){
                tmrBETOD1_LIGAR->Enabled = false;
                if (btnBETOD1_LIGADO->Caption == "Ligado"  && tmrBETOD1_DESLIGAR->Enabled == false){
                        tmrBETOD1_DESLIGAR->Enabled = true;
                }
                btnBETOD1_PARAREMERG->Caption = "Rearmar";
                shpBETOD1_PARAREMERG_LOC->Brush->Color = clRed;
                btnBETOD1_LIGAR->Enabled = false;
                btnBETOD1_LIGADO->Enabled = false;
        }else{
                btnBETOD1_PARAREMERG->Caption = "Parar em Emergência";
                shpBETOD1_PARAREMERG_LOC->Brush->Color = clWhite;
                btnBETOD1_LIGAR->Enabled = true;
                btnBETOD1_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD2_LIGADOClick(TObject *Sender)
{
        if (btnBETOD2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AODPG_BETOD2_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_BETOD2_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD2_EMREMClick(TObject *Sender)
{
        if (btnBETOD2_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_AODPG_BETOD2_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_BETOD2_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD2_LIGARClick(TObject *Sender)
{
        if (btnBETOD2_LIGADO->Caption == "Parado"){
                tmrBETOD2_DESLIGAR->Enabled = false;
                tmrBETOD2_LIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD2_DESLIGARClick(TObject *Sender)
{
        if (btnBETOD2_LIGADO->Caption == "Ligado"){
                tmrBETOD2_LIGAR->Enabled = false;
                tmrBETOD2_DESLIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBETOD2_LIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_AODPG_BETOD2_LIGADO, 1 );
        tmrBETOD2_LIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBETOD2_DESLIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_AODPG_BETOD2_LIGADO, 0 );
        tmrBETOD2_DESLIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBETOD2_PARAREMERGClick(TObject *Sender)
{
        if (btnBETOD2_PARAREMERG->Caption == "Parar em Emergência"){
                tmrBETOD2_LIGAR->Enabled = false;
                if (btnBETOD2_LIGADO->Caption == "Ligado"  && tmrBETOD2_DESLIGAR->Enabled == false){
                        tmrBETOD2_DESLIGAR->Enabled = true;
                }
                btnBETOD2_PARAREMERG->Caption = "Rearmar";
                shpBETOD2_PARAREMERG_LOC->Brush->Color = clRed;
                btnBETOD2_LIGAR->Enabled = false;
                btnBETOD2_LIGADO->Enabled = false;
        }else{
                btnBETOD2_PARAREMERG->Caption = "Parar em Emergência";
                shpBETOD2_PARAREMERG_LOC->Brush->Color = clWhite;
                btnBETOD2_LIGAR->Enabled = true;
                btnBETOD2_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPLOD1_FALHAALIMClick(TObject *Sender)
{
        if (btnPLOD1_FALHAALIM->Caption == "Alim. OK"){
		CLP.WR( PC_HL_AODPG_PLOD1_FALHAALIM, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_PLOD1_FALHAALIM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPLOD2_FALHAALIMClick(TObject *Sender)
{
         if (btnPLOD2_FALHAALIM->Caption == "Alim. OK"){
		CLP.WR( PC_HL_AODPG_PLOD2_FALHAALIM, 1 );
	}
	else{
		CLP.WR( PC_HL_AODPG_PLOD2_FALHAALIM, 0 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnVOD103_ABRIRClick(TObject *Sender)
{
        if (btnVOD103_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 0);
        }
        if (btnVOD103_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD103_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD103_FECHARClick(TObject *Sender)
{
        if (btnVOD103_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD103_ABERTO, 0);
        }
        if (btnVOD103_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD103_MODOClick(TObject *Sender)
{
        if (VOD103_ModoOpera == true) {
                VOD103_ModoOpera = false;
                btnVOD103_MODO->Caption = "Remoto";
        }else{
                VOD103_ModoOpera = true;
                btnVOD103_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD103_ABERTOClick(TObject *Sender)
{
        if (btnVOD103_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD103_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD103_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD103_FECHADOClick(TObject *Sender)
{
        if (btnVOD103_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD103_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD106_ABRIRClick(TObject *Sender)
{
        if (btnVOD106_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 0);
        }
        if (btnVOD106_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD106_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD106_FECHARClick(TObject *Sender)
{
        if (btnVOD106_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD106_ABERTO, 0);
        }
        if (btnVOD106_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD106_MODOClick(TObject *Sender)
{
        if (VOD106_ModoOpera == true) {
                VOD106_ModoOpera = false;
                btnVOD106_MODO->Caption = "Remoto";
        }else{
                VOD106_ModoOpera = true;
                btnVOD106_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD106_ABERTOClick(TObject *Sender)
{
        if (btnVOD106_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD106_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD106_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD106_FECHADOClick(TObject *Sender)
{
        if (btnVOD106_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD106_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD101_ABRIRClick(TObject *Sender)
{
        if (btnVOD101_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 0);
        }
        if (btnVOD101_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD101_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD101_FECHARClick(TObject *Sender)
{
        if (btnVOD101_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD101_ABERTO, 0);
        }
        if (btnVOD101_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD101_MODOClick(TObject *Sender)
{
        if (VOD101_ModoOpera == true) {
                VOD101_ModoOpera = false;
                btnVOD101_MODO->Caption = "Remoto";
        }else{
                VOD101_ModoOpera = true;
                btnVOD101_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD101_ABERTOClick(TObject *Sender)
{
        if (btnVOD101_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD101_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD101_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD101_FECHADOClick(TObject *Sender)
{
        if (btnVOD101_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD101_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD098_ABRIRClick(TObject *Sender)
{
        if (btnVOD098_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 0);
        }
        if (btnVOD098_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD098_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD098_FECHARClick(TObject *Sender)
{
        if (btnVOD098_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD098_ABERTO, 0);
        }
        if (btnVOD098_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD098_MODOClick(TObject *Sender)
{
        if (VOD098_ModoOpera == true) {
                VOD098_ModoOpera = false;
                btnVOD098_MODO->Caption = "Remoto";
        }else{
                VOD098_ModoOpera = true;
                btnVOD098_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD098_ABERTOClick(TObject *Sender)
{
        if (btnVOD098_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD098_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD098_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD098_FECHADOClick(TObject *Sender)
{
        if (btnVOD098_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD098_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD1_LIGADOClick(TObject *Sender)
{
        if (btnBEROD1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_SODPG_BEROD1_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_BEROD1_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD1_EMREMClick(TObject *Sender)
{
        if (btnBEROD1_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_SODPG_BEROD1_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_BEROD1_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD1_SOBREC1Click(TObject *Sender)
{
	if (btnBEROD1_SOBREC1->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_SODPG_BEROD1_SOBREC1, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_BEROD1_SOBREC1, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD1_LIGARClick(TObject *Sender)
{
        if (btnBEROD1_LIGADO->Caption == "Parado"){
                tmrBEROD1_DESLIGAR->Enabled = false;
                tmrBEROD1_LIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD1_DESLIGARClick(TObject *Sender)
{
        if (btnBEROD1_LIGADO->Caption == "Ligado"){
                tmrBEROD1_LIGAR->Enabled = false;
                tmrBEROD1_DESLIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBEROD1_LIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_SODPG_BEROD1_LIGADO, 1 );
        tmrBEROD1_LIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBEROD1_DESLIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_SODPG_BEROD1_LIGADO, 0 );
        tmrBEROD1_DESLIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD1_PARAREMERGClick(TObject *Sender)
{
        if (btnBEROD1_PARAREMERG->Caption == "Parar em Emergência"){
                tmrBEROD1_LIGAR->Enabled = false;
                if (btnBEROD1_LIGADO->Caption == "Ligado"  && tmrBEROD1_DESLIGAR->Enabled == false){
                        tmrBEROD1_DESLIGAR->Enabled = true;
                }
                btnBEROD1_PARAREMERG->Caption = "Rearmar";
                shpBEROD1_PARAREMERG_LOC->Brush->Color = clRed;
                btnBEROD1_LIGAR->Enabled = false;
                btnBEROD1_LIGADO->Enabled = false;
        }else{
                btnBEROD1_PARAREMERG->Caption = "Parar em Emergência";
                shpBEROD1_PARAREMERG_LOC->Brush->Color = clWhite;
                btnBEROD1_LIGAR->Enabled = true;
                btnBEROD1_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD2_LIGADOClick(TObject *Sender)
{
        if (btnBEROD2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_SODPG_BEROD2_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_BEROD2_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD2_EMREMClick(TObject *Sender)
{
        if (btnBEROD2_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_SODPG_BEROD2_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_BEROD2_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD2_SOBREC1Click(TObject *Sender)
{
	if (btnBEROD2_SOBREC1->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_SODPG_BEROD2_SOBREC1, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_BEROD2_SOBREC1, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD2_LIGARClick(TObject *Sender)
{
        if (btnBEROD2_LIGADO->Caption == "Parado"){
                tmrBEROD2_DESLIGAR->Enabled = false;
                tmrBEROD2_LIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD2_DESLIGARClick(TObject *Sender)
{
        if (btnBEROD2_LIGADO->Caption == "Ligado"){
                tmrBEROD2_LIGAR->Enabled = false;
                tmrBEROD2_DESLIGAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBEROD2_LIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_SODPG_BEROD2_LIGADO, 1 );
        tmrBEROD2_LIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrBEROD2_DESLIGARTimer(TObject *Sender)
{
        CLP.WR( PC_HL_SODPG_BEROD2_LIGADO, 0 );
        tmrBEROD2_DESLIGAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnBEROD2_PARAREMERGClick(TObject *Sender)
{
        if (btnBEROD2_PARAREMERG->Caption == "Parar em Emergência"){
                tmrBEROD2_LIGAR->Enabled = false;
                if (btnBEROD2_LIGADO->Caption == "Ligado"  && tmrBEROD2_DESLIGAR->Enabled == false){
                        tmrBEROD2_DESLIGAR->Enabled = true;
                }
                btnBEROD2_PARAREMERG->Caption = "Rearmar";
                shpBEROD2_PARAREMERG_LOC->Brush->Color = clRed;
                btnBEROD2_LIGAR->Enabled = false;
                btnBEROD2_LIGADO->Enabled = false;
        }else{
                btnBEROD2_PARAREMERG->Caption = "Parar em Emergência";
                shpBEROD2_PARAREMERG_LOC->Brush->Color = clWhite;
                btnBEROD2_LIGAR->Enabled = true;
                btnBEROD2_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnFCOD1_PRESSDIFALTAClick(TObject *Sender)
{
        if (btnFCOD1_PRESSDIFALTA->Caption == "Pressão OK"){
		CLP.WR( PC_HL_SODPG_FCOD1_PRESSDIFALTA, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_FCOD1_PRESSDIFALTA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnFCOD2_PRESSDIFALTAClick(TObject *Sender)
{
        if (btnFCOD2_PRESSDIFALTA->Caption == "Pressão OK"){
		CLP.WR( PC_HL_SODPG_FCOD2_PRESSDIFALTA, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_FCOD2_PRESSDIFALTA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD08_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD08_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD08_NIVEL->Text = FormatFloat("0.###",txtTSOD08_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTSOD08_NIVEL->Text.ToDouble()) > 2.504){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_SODPG_TSOD08_NIVEL, (txtTSOD08_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD08_NIVELALTOClick(TObject *Sender)
{
        if (btnTSOD08_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD08_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD08_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD08_NIVELBAIXOClick(TObject *Sender)
{
        if (btnTSOD08_NIVELBAIXO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD08_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD08_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD08_TEMPClick(TObject *Sender)
{
	float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD08_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD08_TEMP->Text = FormatFloat("0.###",txtTSOD08_TEMP->Text.ToDouble());
                CLP.WR( PC_HA_SODPG_TSOD08_TEMP, (txtTSOD08_TEMP->Text.ToDouble()) );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD09_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD09_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD09_NIVEL->Text = FormatFloat("0.###",txtTSOD09_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTSOD09_NIVEL->Text.ToDouble()) > 2.624){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_SODPG_TSOD09_NIVEL, (txtTSOD09_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD09_NIVELALTOClick(TObject *Sender)
{
        if (btnTSOD09_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD09_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD09_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD09_NIVELBAIXOClick(TObject *Sender)
{
        if (btnTSOD09_NIVELBAIXO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD09_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD09_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD09_TEMPClick(TObject *Sender)
{
	float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD09_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD09_TEMP->Text = FormatFloat("0.###",txtTSOD09_TEMP->Text.ToDouble());
                CLP.WR( PC_HA_SODPG_TSOD09_TEMP, (txtTSOD09_TEMP->Text.ToDouble()) );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD1_LIGADOClick(TObject *Sender)
{
        if (btnAQCOD1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_SODPG_AQCOD1_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD1_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD1_EMREMClick(TObject *Sender)
{
        if (btnAQCOD1_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_SODPG_AQCOD1_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD1_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD1_FALHAClick(TObject *Sender)
{
	if (btnAQCOD1_FALHA->Caption == "Sem Temp. Alta"){
		CLP.WR( PC_HL_SODPG_AQCOD1_FALHA, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD1_FALHA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD1_ENERGIZADOClick(TObject *Sender)
{
	if (btnAQCOD1_ENERGIZADO->Caption == "Desenergizado"){
		CLP.WR( PC_HL_SODPG_AQCOD1_ENERGIZADO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD1_ENERGIZADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD1_LIGARClick(TObject *Sender)
{
        if (btnAQCOD1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_SODPG_AQCOD1_LIGADO, 1 );
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD1_DESLIGARClick(TObject *Sender)
{
        if (btnAQCOD1_LIGADO->Caption == "Ligado"){
		CLP.WR( PC_HL_SODPG_AQCOD1_LIGADO, 0 );
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD2_LIGADOClick(TObject *Sender)
{
        if (btnAQCOD2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_SODPG_AQCOD2_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD2_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD2_EMREMClick(TObject *Sender)
{
        if (btnAQCOD2_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_SODPG_AQCOD2_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD2_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD2_FALHAClick(TObject *Sender)
{
	if (btnAQCOD2_FALHA->Caption == "Sem Temp. Alta"){
		CLP.WR( PC_HL_SODPG_AQCOD2_FALHA, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD2_FALHA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD2_ENERGIZADOClick(TObject *Sender)
{
	if (btnAQCOD2_ENERGIZADO->Caption == "Desenergizado"){
		CLP.WR( PC_HL_SODPG_AQCOD2_ENERGIZADO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_AQCOD2_ENERGIZADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD2_LIGARClick(TObject *Sender)
{
        if (btnAQCOD2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_SODPG_AQCOD2_LIGADO, 1 );
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAQCOD2_DESLIGARClick(TObject *Sender)
{
        if (btnAQCOD2_LIGADO->Caption == "Ligado"){
		CLP.WR( PC_HL_SODPG_AQCOD2_LIGADO, 0 );
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD120_ABRIRClick(TObject *Sender)
{
        if (btnVOD120_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 0);
        }
        if (btnVOD120_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD120_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD120_FECHARClick(TObject *Sender)
{
        if (btnVOD120_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD120_ABERTO, 0);
        }
        if (btnVOD120_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD120_RTAUTOClick(TObject *Sender)
{
        if (VOD120_RetornoAuto == true) {
                VOD120_RetornoAuto = false;
                btnVOD120_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD120_RetornoAuto = true;
                btnVOD120_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD120_MODOClick(TObject *Sender)
{
        if (VOD120_ModoOpera == true) {
                VOD120_ModoOpera = false;
                btnVOD120_MODO->Caption = "Remoto";
        }else{
                VOD120_ModoOpera = true;
                btnVOD120_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD120_ABERTOClick(TObject *Sender)
{
        if (btnVOD120_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD120_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD120_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD120_FECHADOClick(TObject *Sender)
{
        if (btnVOD120_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD120_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD129_ABRIRClick(TObject *Sender)
{
        if (btnVOD129_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 0);
        }
        if (btnVOD129_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD129_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD129_FECHARClick(TObject *Sender)
{
        if (btnVOD129_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD129_ABERTO, 0);
        }
        if (btnVOD129_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD129_RTAUTOClick(TObject *Sender)
{
        if (VOD129_RetornoAuto == true) {
                VOD129_RetornoAuto = false;
                btnVOD129_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD129_RetornoAuto = true;
                btnVOD129_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD129_MODOClick(TObject *Sender)
{
        if (VOD129_ModoOpera == true) {
                VOD129_ModoOpera = false;
                btnVOD129_MODO->Caption = "Remoto";
        }else{
                VOD129_ModoOpera = true;
                btnVOD129_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD129_ABERTOClick(TObject *Sender)
{
        if (btnVOD129_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD129_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD129_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD129_FECHADOClick(TObject *Sender)
{
        if (btnVOD129_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD129_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD152_ABRIRClick(TObject *Sender)
{
        if (btnVOD152_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 0);
        }
        if (btnVOD152_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD152_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD152_FECHARClick(TObject *Sender)
{
        if (btnVOD152_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD152_ABERTO, 0);
        }
        if (btnVOD152_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD152_RTAUTOClick(TObject *Sender)
{
        if (VOD152_RetornoAuto == true) {
                VOD152_RetornoAuto = false;
                btnVOD152_RTAUTO->Caption = "Ret. Des.";
        }else{
                VOD152_RetornoAuto = true;
                btnVOD152_RTAUTO->Caption = "Ret. Lig.";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD152_MODOClick(TObject *Sender)
{
        if (VOD152_ModoOpera == true) {
                VOD152_ModoOpera = false;
                btnVOD152_MODO->Caption = "Remoto";
        }else{
                VOD152_ModoOpera = true;
                btnVOD152_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD152_ABERTOClick(TObject *Sender)
{
        if (btnVOD152_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD152_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD152_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD152_FECHADOClick(TObject *Sender)
{
        if (btnVOD152_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD152_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD122_ABRIRClick(TObject *Sender)
{
        if (btnVOD122_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 0);
        }
        if (btnVOD122_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD122_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD122_FECHARClick(TObject *Sender)
{
        if (btnVOD122_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD122_ABERTO, 0);
        }
        if (btnVOD122_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD122_MODOClick(TObject *Sender)
{
        if (VOD122_ModoOpera == true) {
                VOD122_ModoOpera = false;
                btnVOD122_MODO->Caption = "Remoto";
        }else{
                VOD122_ModoOpera = true;
                btnVOD122_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD122_ABERTOClick(TObject *Sender)
{
        if (btnVOD122_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD122_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD122_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD122_FECHADOClick(TObject *Sender)
{
        if (btnVOD122_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD122_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD133_ABRIRClick(TObject *Sender)
{
        if (btnVOD133_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 0);
        }
        if (btnVOD133_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD133_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD133_FECHARClick(TObject *Sender)
{
        if (btnVOD133_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD133_ABERTO, 0);
        }
        if (btnVOD133_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD133_MODOClick(TObject *Sender)
{
        if (VOD133_ModoOpera == true) {
                VOD133_ModoOpera = false;
                btnVOD133_MODO->Caption = "Remoto";
        }else{
                VOD133_ModoOpera = true;
                btnVOD133_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD133_ABERTOClick(TObject *Sender)
{
        if (btnVOD133_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD133_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD133_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD133_FECHADOClick(TObject *Sender)
{
        if (btnVOD133_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD133_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD155_ABRIRClick(TObject *Sender)
{
        if (btnVOD155_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 0);
        }
        if (btnVOD155_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD155_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD155_FECHARClick(TObject *Sender)
{
        if (btnVOD155_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_SODPG_VOD155_ABERTO, 0);
        }
        if (btnVOD155_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD155_MODOClick(TObject *Sender)
{
        if (VOD155_ModoOpera == true) {
                VOD155_ModoOpera = false;
                btnVOD155_MODO->Caption = "Remoto";
        }else{
                VOD155_ModoOpera = true;
                btnVOD155_MODO->Caption = "Local";
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD155_ABERTOClick(TObject *Sender)
{
        if (btnVOD155_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_SODPG_VOD155_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD155_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVOD155_FECHADOClick(TObject *Sender)
{
        if (btnVOD155_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_SODPG_VOD155_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD07_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD07_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD07_NIVEL->Text = FormatFloat("0.###",txtTSOD07_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTSOD07_NIVEL->Text.ToDouble()) > 1.794){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_SODPG_TSOD07_NIVEL, (txtTSOD07_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD07_NIVELALTOClick(TObject *Sender)
{
        if (btnTSOD07_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD07_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD07_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD07_NIVELBAIXOClick(TObject *Sender)
{
        if (btnTSOD07_NIVELBAIXO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD07_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD07_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD10_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD10_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD10_NIVEL->Text = FormatFloat("0.###",txtTSOD10_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTSOD10_NIVEL->Text.ToDouble()) > 1.934){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_SODPG_TSOD10_NIVEL, (txtTSOD10_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD10_NIVELALTOClick(TObject *Sender)
{
        if (btnTSOD10_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD10_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD10_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD10_NIVELBAIXOClick(TObject *Sender)
{
        if (btnTSOD10_NIVELBAIXO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD10_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD10_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD11_NIVELClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtTSOD11_NIVEL->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtTSOD11_NIVEL->Text = FormatFloat("0.###",txtTSOD11_NIVEL->Text.ToDouble());
                if (FormatFloat("0.###",txtTSOD11_NIVEL->Text.ToDouble()) > 1.370){
                        Application->MessageBox("Valor Inválido - Acima do Limite", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_SODPG_TSOD11_NIVEL, (txtTSOD11_NIVEL->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD11_NIVELALTOClick(TObject *Sender)
{
        if (btnTSOD11_NIVELALTO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD11_NIVELALTO, 0 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD11_NIVELALTO, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTSOD11_NIVELBAIXOClick(TObject *Sender)
{
        if (btnTSOD11_NIVELBAIXO->Caption == "Nível OK"){
		CLP.WR( PC_HL_SODPG_TSOD11_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_SODPG_TSOD11_NIVELBAIXO, 0 );
	};
}
//==============================================================================
//==============================================================================
//                              ÓLEO DIESEL
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              AR COMPRIMIDO
//==============================================================================
//==============================================================================
void __fastcall TfrmPrincipal::tmrCAAP01_PARARTimer(TObject *Sender)
{
        CLP.WR(PC_HL_RACAP_CAAP01_LIGADO, 0);
        tmrCAAP01_PARAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_LIGADOClick(TObject *Sender)
{
        if (btnRACAP_CAAP01_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RACAP_CAAP01_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP01_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_EMAUTClick(TObject *Sender)
{
        if (btnRACAP_CAAP01_EMAUT->Caption == "Em Manual"){
		CLP.WR( PC_HL_RACAP_CAAP01_EMAUT, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP01_EMAUT, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_FALHAClick(TObject *Sender)
{
        if (btnRACAP_CAAP01_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RACAP_CAAP01_FALHA, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP01_FALHA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_EMREMClick(TObject *Sender)
{
        if (btnRACAP_CAAP01_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_RACAP_CAAP01_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP01_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_PARTIRClick(TObject *Sender)
{
        tmrCAAP01_PARAR->Enabled = false;
        if (btnRACAP_CAAP01_LIGADO->Caption == "Parado"){
                CLP.WR( PC_HL_RACAP_CAAP01_LIGADO, 1 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_PARARClick(TObject *Sender)
{
        if (btnRACAP_CAAP01_LIGADO->Caption == "Ligado"){
                tmrCAAP01_PARAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP01_PARAREMERGLOCClick(
      TObject *Sender)
{
        if (btnRACAP_CAAP01_PARAREMERGLOC->Caption == "Parar em Emergência"){
                tmrCAAP01_PARAR->Enabled = false;
                if (btnRACAP_CAAP01_LIGADO->Caption == "Ligado"){
                        CLP.WR( PC_HL_RACAP_CAAP01_LIGADO, 0 );
                }

                btnRACAP_CAAP01_PARAREMERGLOC->Caption = "Rearmar";
                shpRACAP_CAAP01_PARAREMERGLOC->Brush->Color = clRed;
                btnRACAP_CAAP01_PARTIR->Enabled = false;
                btnRACAP_CAAP01_PARAR->Enabled = false;
                btnRACAP_CAAP01_LIGADO->Enabled = false;
        }
        else{
                btnRACAP_CAAP01_PARAREMERGLOC->Caption = "Parar em Emergência";
                shpRACAP_CAAP01_PARAREMERGLOC->Brush->Color = clWhite;
                btnRACAP_CAAP01_PARTIR->Enabled = true;
                btnRACAP_CAAP01_PARAR->Enabled = true;
                btnRACAP_CAAP01_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrCAAP02_PARARTimer(TObject *Sender)
{
        CLP.WR(PC_HL_RACAP_CAAP02_LIGADO, 0);
        tmrCAAP02_PARAR->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_LIGADOClick(TObject *Sender)
{
        if (btnRACAP_CAAP02_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RACAP_CAAP02_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP02_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_EMAUTClick(TObject *Sender)
{
        if (btnRACAP_CAAP02_EMAUT->Caption == "Em Manual"){
		CLP.WR( PC_HL_RACAP_CAAP02_EMAUT, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP02_EMAUT, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_FALHAClick(TObject *Sender)
{
        if (btnRACAP_CAAP02_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RACAP_CAAP02_FALHA, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP02_FALHA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_EMREMClick(TObject *Sender)
{
        if (btnRACAP_CAAP02_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_RACAP_CAAP02_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_RACAP_CAAP02_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_PARTIRClick(TObject *Sender)
{
        tmrCAAP02_PARAR->Enabled = false;
        if (btnRACAP_CAAP02_LIGADO->Caption == "Parado"){
                CLP.WR( PC_HL_RACAP_CAAP02_LIGADO, 1 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_PARARClick(TObject *Sender)
{
        if (btnRACAP_CAAP02_LIGADO->Caption == "Ligado"){
                tmrCAAP02_PARAR->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_CAAP02_PARAREMERGLOCClick(
      TObject *Sender)
{
        if (btnRACAP_CAAP02_PARAREMERGLOC->Caption == "Parar em Emergência"){
                tmrCAAP02_PARAR->Enabled = false;
                if (btnRACAP_CAAP02_LIGADO->Caption == "Ligado"){
                        CLP.WR( PC_HL_RACAP_CAAP02_LIGADO, 0 );
                }

                btnRACAP_CAAP02_PARAREMERGLOC->Caption = "Rearmar";
                shpRACAP_CAAP02_PARAREMERGLOC->Brush->Color = clRed;
                btnRACAP_CAAP02_PARTIR->Enabled = false;
                btnRACAP_CAAP02_PARAR->Enabled = false;
                btnRACAP_CAAP02_LIGADO->Enabled = false;
        }
        else{
                btnRACAP_CAAP02_PARAREMERGLOC->Caption = "Parar em Emergência";
                shpRACAP_CAAP02_PARAREMERGLOC->Brush->Color = clWhite;
                btnRACAP_CAAP02_PARTIR->Enabled = true;
                btnRACAP_CAAP02_PARAR->Enabled = true;
                btnRACAP_CAAP02_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_RAPDPM_PRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtRACAP_RAPDPM_PRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtRACAP_RAPDPM_PRESS->Text = FormatFloat("0.###",txtRACAP_RAPDPM_PRESS->Text.ToDouble());
                if (FormatFloat("0.###",txtRACAP_RAPDPM_PRESS->Text.ToDouble()) > 413.7){
                        Application->MessageBox("Valor Inválido - Acima do Limite (413.7 bar)", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_RACAP_RAPDPM_PRESS, (txtRACAP_RAPDPM_PRESS->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_RAPFPM_PRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtRACAP_RAPFPM_PRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtRACAP_RAPFPM_PRESS->Text = FormatFloat("0.###",txtRACAP_RAPFPM_PRESS->Text.ToDouble());
                if (FormatFloat("0.###",txtRACAP_RAPFPM_PRESS->Text.ToDouble()) > 413.7){
                        Application->MessageBox("Valor Inválido - Acima do Limite (413.7 bar)", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_RACAP_RAPFPM_PRESS, (txtRACAP_RAPFPM_PRESS->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACAP_RAPMCP_PRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtRACAP_RAPMCP_PRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtRACAP_RAPMCP_PRESS->Text = FormatFloat("0.###",txtRACAP_RAPMCP_PRESS->Text.ToDouble());
                if (FormatFloat("0.###",txtRACAP_RAPMCP_PRESS->Text.ToDouble()) > 70.0){
                        Application->MessageBox("Valor Inválido - Acima do Limite (70.0 bar)", NULL, MB_OKCANCEL);
                }else{
                        CLP.WR( PC_HA_RACAP_RAPMCP_PRESS, (txtRACAP_RAPMCP_PRESS->Text.ToDouble()) );
                }
        }
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              AR COMPRIMIDO
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              Ó. LUBRIFICANTE
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_AQCOL1_LIGADOClick(TObject *Sender)
{
        if (btnAOLTG_AQCOL1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AOLTG_AQCOL1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_AQCOL1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_AQCOL1_FALHAClick(TObject *Sender)
{
        if (btnAOLTG_AQCOL1_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_AOLTG_AQCOL1_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_AQCOL1_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_AQCOL2_LIGADOClick(TObject *Sender)
{
        if (btnAOLTG_AQCOL2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AOLTG_AQCOL2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_AQCOL2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_AQCOL2_FALHAClick(TObject *Sender)
{
        if (btnAOLTG_AQCOL2_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_AOLTG_AQCOL2_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_AQCOL2_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_BETOL1_LIGADOClick(TObject *Sender)
{
        if (btnAOLTG_BETOL1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AOLTG_BETOL1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_BETOL1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_BETOL2_LIGADOClick(TObject *Sender)
{
        if (btnAOLTG_BETOL2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AOLTG_BETOL2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_BETOL2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_PUROL1_LIGADOClick(TObject *Sender)
{
        if (btnAOLTG_PUROL1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AOLTG_PUROL1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_PUROL1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_PUROL1_PERDASELOClick(
      TObject *Sender)
{
        if (btnAOLTG_PUROL1_PERDASELO->Caption == "Selo Normal"){
		CLP.WR( PC_HL_AOLTG_PUROL1_PERDASELO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_PUROL1_PERDASELO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_PUROL2_LIGADOClick(TObject *Sender)
{
        if (btnAOLTG_PUROL2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_AOLTG_PUROL2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_PUROL2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_PUROL2_PERDASELOClick(
      TObject *Sender)
{
        if (btnAOLTG_PUROL2_PERDASELO->Caption == "Selo Normal"){
		CLP.WR( PC_HL_AOLTG_PUROL2_PERDASELO , 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_PUROL2_PERDASELO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_TAOL14_NIVELBAIXOClick(
      TObject *Sender)
{
        if (btnAOLTG_TAOL14_NIVELBAIXO->Caption == "Não Nível Baixo"){
		CLP.WR( PC_HL_AOLTG_TAOL14_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_AOLTG_TAOL14_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_TAOL25_NIVELALTOClick(
      TObject *Sender)
{
        if (btnAOLTG_TAOL25_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_AOLTG_TAOL25_NIVELALTO, 0);
	}
	else{
		CLP.WR( PC_HL_AOLTG_TAOL25_NIVELALTO, 1);
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_TBORRA_NIVELALTOClick(
      TObject *Sender)
{
        if (btnAOLTG_TBORRA_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_AOLTG_TBORRA_NIVELALTO, 0);
	}
	else{
		CLP.WR( PC_HL_AOLTG_TBORRA_NIVELALTO, 1);
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAOLTG_TQDREN_NIVELALTOClick(
      TObject *Sender)
{
        if (btnAOLTG_TQDREN_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_AOLTG_TQDREN_NIVELALTO, 0);
	}
	else{
		CLP.WR( PC_HL_AOLTG_TQDREN_NIVELALTO, 1);
	};
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              Ó. LUBRIFICANTE
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                                    ÁGUA
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnDASOR_GDEST1_LIGADOClick(TObject *Sender)
{
        if (btnDASOR_GDEST1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_DASOR_GDEST1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_DASOR_GDEST1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnDASOR_GDEST1_FALHAClick(TObject *Sender)
{
        if (btnDASOR_GDEST1_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_DASOR_GDEST1_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_DASOR_GDEST1_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnDASOR_GDEST1_SALINALTAClick(
      TObject *Sender)
{
        if (btnDASOR_GDEST1_SALINALTA->Caption == "Salinidade Normal"){
		CLP.WR( PC_HL_DASOR_GDEST1_SALINALTA , 1 );
	}
	else{
		CLP.WR( PC_HL_DASOR_GDEST1_SALINALTA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnDASOR_GDEST2_LIGADOClick(TObject *Sender)
{
        if (btnDASOR_GDEST2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_DASOR_GDEST2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_DASOR_GDEST2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnDASOR_GDEST2_FALHAClick(TObject *Sender)
{
        if (btnDASOR_GDEST2_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_DASOR_GDEST2_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_DASOR_GDEST2_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnDASOR_GDEST2_SALINALTAClick(
      TObject *Sender)
{
        if (btnDASOR_GDEST2_SALINALTA->Caption == "Salinidade Normal"){
		CLP.WR( PC_HL_DASOR_GDEST2_SALINALTA , 1 );
	}
	else{
		CLP.WR( PC_HL_DASOR_GDEST2_SALINALTA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACUG_EF1_LIGADOClick(TObject *Sender)
{
        if (btnRACUG_EF1_LIGADO->Caption == "Parada"){
		CLP.WR( PC_HL_RACUG_EF1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RACUG_EF1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACUG_EF2_LIGADOClick(TObject *Sender)
{
         if (btnRACUG_EF2_LIGADO->Caption == "Parada"){
		CLP.WR( PC_HL_RACUG_EF2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RACUG_EF2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACUG_EF3_LIGADOClick(TObject *Sender)
{
         if (btnRACUG_EF3_LIGADO->Caption == "Parada"){
		CLP.WR( PC_HL_RACUG_EF3_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RACUG_EF3_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACUG_EF4_LIGADOClick(TObject *Sender)
{
         if (btnRACUG_EF4_LIGADO->Caption == "Parada"){
		CLP.WR( PC_HL_RACUG_EF4_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RACUG_EF4_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACUG_UCA13_UMIDALTAClick(
      TObject *Sender)
{
        if (btnRACUG_UCA13_UMIDALTA->Caption == "Umidade Normal"){
		CLP.WR( PC_HL_RACUG_UCA13_UMIDALTA , 1 );
	}
	else{
		CLP.WR( PC_HL_RACUG_UCA13_UMIDALTA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRACUG_UCA14_UMIDALTAClick(
      TObject *Sender)
{
        if (btnRACUG_UCA14_UMIDALTA->Caption == "Umidade Normal"){
		CLP.WR( PC_HL_RACUG_UCA14_UMIDALTA , 1 );
	}
	else{
		CLP.WR( PC_HL_RACUG_UCA14_UMIDALTA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_BECAD1_LIGADOClick(TObject *Sender)
{
        if (btnRADUG_BECAD1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RADUG_BECAD1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RADUG_BECAD1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_BECAD2_LIGADOClick(TObject *Sender)
{
        if (btnRADUG_BECAD2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RADUG_BECAD2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RADUG_BECAD2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_BECAQ_LIGADOClick(TObject *Sender)
{
        if (btnRADUG_BECAQ_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RADUG_BECAQ_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RADUG_BECAQ_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP001_ABERTOClick(TObject *Sender)
{
        if (btnRADUG_VAP001_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_RADUG_VAP001_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_RADUG_VAP001_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP001_FECHADOClick(
      TObject *Sender)
{
        if (btnRADUG_VAP001_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP001_ABRIRClick(TObject *Sender)
{
        if (btnRADUG_VAP001_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 0);
        }
        if (btnRADUG_VAP001_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_RADUG_VAP001_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP001_FECHARClick(TObject *Sender)
{
        if (btnRADUG_VAP001_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_RADUG_VAP001_ABERTO, 0);
        }
        if (btnRADUG_VAP001_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_RADUG_VAP001_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP002_ABERTOClick(TObject *Sender)
{
        if (btnRADUG_VAP002_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_RADUG_VAP002_ABERTO, 1);
        }else{
                CLP.WR(PC_HL_RADUG_VAP002_ABERTO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP002_FECHADOClick(
      TObject *Sender)
{
        if (btnRADUG_VAP002_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 1);
        }else{
                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP002_ABRIRClick(TObject *Sender)
{
        if (btnRADUG_VAP002_FECHADO->Caption == "Fechada"){
                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 0);
        }
        if (btnRADUG_VAP002_ABERTO->Caption == "Não Aberta"){
                CLP.WR(PC_HL_RADUG_VAP002_ABERTO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_VAP002_FECHARClick(TObject *Sender)
{
        if (btnRADUG_VAP002_ABERTO->Caption == "Aberta"){
                CLP.WR(PC_HL_RADUG_VAP002_ABERTO, 0);
        }
        if (btnRADUG_VAP002_FECHADO->Caption == "Não Fechada"){
                CLP.WR(PC_HL_RADUG_VAP002_FECHADO, 1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_TAAD26_NIVELALTOClick(
      TObject *Sender)
{
        if (btnRADUG_TAAD26_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_RADUG_TAAD26_NIVELALTO, 0);
	}
	else{
		CLP.WR( PC_HL_RADUG_TAAD26_NIVELALTO, 1);
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_TAAD26_NIVELBAIXOClick(
      TObject *Sender)
{
        if (btnRADUG_TAAD26_NIVELBAIXO->Caption == "Não Nível Baixo"){
		CLP.WR( PC_HL_RADUG_TAAD26_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_RADUG_TAAD26_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_TAAD27_NIVELALTOClick(
      TObject *Sender)
{
        if (btnRADUG_TAAD27_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_RADUG_TAAD27_NIVELALTO, 0);
	}
	else{
		CLP.WR( PC_HL_RADUG_TAAD27_NIVELALTO, 1);
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRADUG_TAAD27_NIVELBAIXOClick(
      TObject *Sender)
{
        if (btnRADUG_TAAD27_NIVELBAIXO->Caption == "Não Nível Baixo"){
		CLP.WR( PC_HL_RADUG_TAAD27_NIVELBAIXO, 1 );
	}
	else{
		CLP.WR( PC_HL_RADUG_TAAD27_NIVELBAIXO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_URA1_LIGADOClick(TObject *Sender)
{
        if (btnRARUG_URA1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RARUG_URA1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_URA1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_URA1_FALHAClick(TObject *Sender)
{
        if (btnRARUG_URA1_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RARUG_URA1_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_URA1_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_URA2_LIGADOClick(TObject *Sender)
{
        if (btnRARUG_URA2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RARUG_URA2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_URA2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_URA2_FALHAClick(TObject *Sender)
{
        if (btnRARUG_URA2_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RARUG_URA2_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_URA2_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_URA3_LIGADOClick(TObject *Sender)
{
        if (btnRARUG_URA3_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RARUG_URA3_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_URA3_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_URA3_FALHAClick(TObject *Sender)
{
        if (btnRARUG_URA3_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RARUG_URA3_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_URA3_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_BEAGD1_LIGADOClick(TObject *Sender)
{
        if (btnRARUG_BEAGD1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RARUG_BEAGD1_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_BEAGD1_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_BEAGD1_FALHAClick(TObject *Sender)
{
        if (btnRARUG_BEAGD1_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RARUG_BEAGD1_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_BEAGD1_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_BEAGD2_LIGADOClick(TObject *Sender)
{
        if (btnRARUG_BEAGD2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RARUG_BEAGD2_LIGADO , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_BEAGD2_LIGADO , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARUG_BEAGD2_FALHAClick(TObject *Sender)
{
        if (btnRARUG_BEAGD2_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_RARUG_BEAGD2_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_RARUG_BEAGD2_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_LIGADOClick(TObject *Sender)
{
        if (btnRASIS_BECAS1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RASIS_BECAS1_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS1_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_SOBREC1Click(
      TObject *Sender)
{
        if (btnRASIS_BECAS1_SOBREC1->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_RASIS_BECAS1_SOBREC1, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS1_SOBREC1, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_SOBREC2Click(
      TObject *Sender)
{
        if (btnRASIS_BECAS1_SOBREC2->Caption == "Sem Sobretemperatura"){
		CLP.WR( PC_HL_RASIS_BECAS1_SOBREC2, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS1_SOBREC2, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_EMREMClick(TObject *Sender)
{
        if (btnRASIS_BECAS1_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_RASIS_BECAS1_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS1_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_LIGARClick(TObject *Sender)
{
        if (btnRASIS_BECAS1_LIGADO->Caption == "Parado"){
                CLP.WR( PC_HL_RASIS_BECAS1_LIGADO, 1 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_DESLIGARClick(
      TObject *Sender)
{
        if (btnRASIS_BECAS1_LIGADO->Caption == "Ligado"){
                CLP.WR( PC_HL_RASIS_BECAS1_LIGADO, 0 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS1_PRDEMERGLOCALClick(
      TObject *Sender)
{
        if (btnRASIS_BECAS1_PRDEMERGLOCAL->Caption == "Parar em Emergência"){
                if (btnRASIS_BECAS1_LIGADO->Caption == "Ligado"){
                        CLP.WR( PC_HL_RASIS_BECAS1_LIGADO, 0 );
                }
                CLP.WR( PC_HL_RASIS_BECAS1_PRDEMERGLOCAL, 1 );
                btnRASIS_BECAS1_PRDEMERGLOCAL->Caption = "Rearmar";
                shpRASIS_BECAS1_PRDEMERGLOCAL->Brush->Color = clRed;
                btnRASIS_BECAS1_LIGAR->Enabled = false;
                btnRASIS_BECAS1_DESLIGAR->Enabled = false;
                btnRASIS_BECAS1_LIGADO->Enabled = false;
        }
        else{
                CLP.WR( PC_HL_RASIS_BECAS1_PRDEMERGLOCAL, 0 );
                btnRASIS_BECAS1_PRDEMERGLOCAL->Caption = "Parar em Emergência";
                shpRASIS_BECAS1_PRDEMERGLOCAL->Brush->Color = clWhite;
                btnRASIS_BECAS1_LIGAR->Enabled = true;
                btnRASIS_BECAS1_DESLIGAR->Enabled = true;
                btnRASIS_BECAS1_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_LIGADOClick(TObject *Sender)
{
        if (btnRASIS_BECAS2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RASIS_BECAS2_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS2_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_SOBREC1Click(
      TObject *Sender)
{
        if (btnRASIS_BECAS2_SOBREC1->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_RASIS_BECAS2_SOBREC1, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS2_SOBREC1, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_SOBREC2Click(
      TObject *Sender)
{
        if (btnRASIS_BECAS2_SOBREC2->Caption == "Sem Sobretemperatura"){
		CLP.WR( PC_HL_RASIS_BECAS2_SOBREC2, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS2_SOBREC2, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_EMREMClick(TObject *Sender)
{
        if (btnRASIS_BECAS2_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_RASIS_BECAS2_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS2_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_LIGARClick(TObject *Sender)
{
        if (btnRASIS_BECAS2_LIGADO->Caption == "Parado"){
                CLP.WR( PC_HL_RASIS_BECAS2_LIGADO, 1 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_DESLIGARClick(
      TObject *Sender)
{
        if (btnRASIS_BECAS2_LIGADO->Caption == "Ligado"){
                CLP.WR( PC_HL_RASIS_BECAS2_LIGADO, 0 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS2_PRDEMERGLOCALClick(
      TObject *Sender)
{
        if (btnRASIS_BECAS2_PRDEMERGLOCAL->Caption == "Parar em Emergência"){
                if (btnRASIS_BECAS2_LIGADO->Caption == "Ligado"){
                        CLP.WR( PC_HL_RASIS_BECAS2_LIGADO, 0 );
                }
                CLP.WR( PC_HL_RASIS_BECAS2_PRDEMERGLOCAL, 1 );
                btnRASIS_BECAS2_PRDEMERGLOCAL->Caption = "Rearmar";
                shpRASIS_BECAS2_PRDEMERGLOCAL->Brush->Color = clRed;
                btnRASIS_BECAS2_LIGAR->Enabled = false;
                btnRASIS_BECAS2_DESLIGAR->Enabled = false;
                btnRASIS_BECAS2_LIGADO->Enabled = false;
        }
        else{
                CLP.WR( PC_HL_RASIS_BECAS2_PRDEMERGLOCAL, 0 );
                btnRASIS_BECAS2_PRDEMERGLOCAL->Caption = "Parar em Emergência";
                shpRASIS_BECAS2_PRDEMERGLOCAL->Brush->Color = clWhite;
                btnRASIS_BECAS2_LIGAR->Enabled = true;
                btnRASIS_BECAS2_DESLIGAR->Enabled = true;
                btnRASIS_BECAS2_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_LIGADOClick(TObject *Sender)
{
        if (btnRASIS_BECAS3_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_RASIS_BECAS3_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS3_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_SOBREC1Click(
      TObject *Sender)
{
        if (btnRASIS_BECAS3_SOBREC1->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_RASIS_BECAS3_SOBREC1, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS3_SOBREC1, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_SOBREC2Click(
      TObject *Sender)
{
        if (btnRASIS_BECAS3_SOBREC2->Caption == "Sem Sobretemperatura"){
		CLP.WR( PC_HL_RASIS_BECAS3_SOBREC2, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS3_SOBREC2, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_EMREMClick(TObject *Sender)
{
        if (btnRASIS_BECAS3_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_RASIS_BECAS3_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_RASIS_BECAS3_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_LIGARClick(TObject *Sender)
{
        if (btnRASIS_BECAS3_LIGADO->Caption == "Parado"){
                CLP.WR( PC_HL_RASIS_BECAS3_LIGADO, 1 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_DESLIGARClick(
      TObject *Sender)
{
        if (btnRASIS_BECAS3_LIGADO->Caption == "Ligado"){
                CLP.WR( PC_HL_RASIS_BECAS3_LIGADO, 0 );
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_BECAS3_PRDEMERGLOCALClick(
      TObject *Sender)
{
        if (btnRASIS_BECAS3_PRDEMERGLOCAL->Caption == "Parar em Emergência"){
                if (btnRASIS_BECAS3_LIGADO->Caption == "Ligado"){
                        CLP.WR( PC_HL_RASIS_BECAS3_LIGADO, 0 );
                }
                CLP.WR( PC_HL_RASIS_BECAS3_PRDEMERGLOCAL, 1 );
                btnRASIS_BECAS3_PRDEMERGLOCAL->Caption = "Rearmar";
                shpRASIS_BECAS3_PRDEMERGLOCAL->Brush->Color = clRed;
                btnRASIS_BECAS3_LIGAR->Enabled = false;
                btnRASIS_BECAS3_DESLIGAR->Enabled = false;
                btnRASIS_BECAS3_LIGADO->Enabled = false;
        }
        else{
                CLP.WR( PC_HL_RASIS_BECAS3_PRDEMERGLOCAL, 0 );
                btnRASIS_BECAS3_PRDEMERGLOCAL->Caption = "Parar em Emergência";
                shpRASIS_BECAS3_PRDEMERGLOCAL->Brush->Color = clWhite;
                btnRASIS_BECAS3_LIGAR->Enabled = true;
                btnRASIS_BECAS3_DESLIGAR->Enabled = true;
                btnRASIS_BECAS3_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_RASAPV_PRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtRASIS_RASAPV_PRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtRASIS_RASAPV_PRESS->Text = FormatFloat("0.###",txtRASIS_RASAPV_PRESS->Text.ToDouble());
                if (txtRASIS_RASAPV_PRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_RASIS_RASAPV_PRESS, (txtRASIS_RASAPV_PRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_RASAPM_PRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtRASIS_RASAPM_PRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtRASIS_RASAPM_PRESS->Text = FormatFloat("0.###",txtRASIS_RASAPM_PRESS->Text.ToDouble());
                if (txtRASIS_RASAPM_PRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_RASIS_RASAPM_PRESS, (txtRASIS_RASAPM_PRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASIS_RASAPR_PRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtRASIS_RASAPR_PRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtRASIS_RASAPR_PRESS->Text = FormatFloat("0.###",txtRASIS_RASAPR_PRESS->Text.ToDouble());
                if (txtRASIS_RASAPR_PRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_RASIS_RASAPR_PRESS, (txtRASIS_RASAPR_PRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRASRG_OERHPC_PRESSBAIXAClick(
      TObject *Sender)
{
        if (btnRASRG_OERHPC_PRESSBAIXA->Caption == "Pressão Normal"){
		CLP.WR( PC_HL_RASRG_OERHPC_PRESSBAIXA, 1 );
	}
	else{
		CLP.WR( PC_HL_RASRG_OERHPC_PRESSBAIXA, 0 );
	};
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                                    ÁGUA
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                            CONTROLE DE POLUIÇÃO
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BEM1_LIGADOClick(TObject *Sender)
{
        if (btnCPTAS_BEM1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_CPTAS_BEM1_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BEM1_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BEM1_FALHAClick(TObject *Sender)
{
        if (btnCPTAS_BEM1_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_CPTAS_BEM1_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BEM1_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BEM2_LIGADOClick(TObject *Sender)
{
        if (btnCPTAS_BEM2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_CPTAS_BEM2_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BEM2_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BEM2_FALHAClick(TObject *Sender)
{
        if (btnCPTAS_BEM2_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_CPTAS_BEM2_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BEM2_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BET1_LIGADOClick(TObject *Sender)
{
        if (btnCPTAS_BET1_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_CPTAS_BET1_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BET1_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BET1_FALHAClick(TObject *Sender)
{
        if (btnCPTAS_BET1_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_CPTAS_BET1_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BET1_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BET2_LIGADOClick(TObject *Sender)
{
        if (btnCPTAS_BET2_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_CPTAS_BET2_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BET2_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_BET2_FALHAClick(TObject *Sender)
{
        if (btnCPTAS_BET2_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_CPTAS_BET2_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_BET2_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_PLUTAS_LIGADOClick(TObject *Sender)
{
        if (btnCPTAS_PLUTAS_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_CPTAS_PLUTAS_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_PLUTAS_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_PLUTAS_FALHAClick(TObject *Sender)
{
        if (btnCPTAS_PLUTAS_FALHA->Caption == "Sem Falha"){
		CLP.WR( PC_HL_CPTAS_PLUTAS_FALHA , 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_PLUTAS_FALHA , 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_SEPAO_LIGADOClick(TObject *Sender)
{
        if (btnCPTAS_SEPAO_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_CPTAS_SEPAO_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_SEPAO_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_SEPAO_TEORALTOClick(
      TObject *Sender)
{
        if (btnCPTAS_SEPAO_TEORALTO->Caption == "Teor Normal"){
		CLP.WR( PC_HL_CPTAS_SEPAO_TEORALTO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_SEPAO_TEORALTO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_TQSEPR_NIVELALTOClick(
      TObject *Sender)
{
        if (btnCPTAS_TQSEPR_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_CPTAS_TQSEPR_NIVELALTO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_TQSEPR_NIVELALTO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCPTAS_TQSEPV_NIVELALTOClick(
      TObject *Sender)
{
         if (btnCPTAS_TQSEPV_NIVELALTO->Caption == "Não Nível Alto"){
		CLP.WR( PC_HL_CPTAS_TQSEPV_NIVELALTO, 1 );
	}
	else{
		CLP.WR( PC_HL_CPTAS_TQSEPV_NIVELALTO, 0 );
	};
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                            CONTROLE DE POLUIÇÃO
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                                     MCAS
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_ARALIMPRESSClick(
      TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_ARALIMPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ARALIMPRESS->Text.ToDouble());
                if (txtGERENE_MCA1_ARALIMPRESS->Text.ToDouble() <= 4){
                        CLP.WR( PC_HA_GERENE_MCA1_ARALIMPRESS, (txtGERENE_MCA1_ARALIMPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (4.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_OLPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_OLPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_OLPRESS->Text.ToDouble());
                if (txtGERENE_MCA1_OLPRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_GERENE_MCA1_OLPRESS, (txtGERENE_MCA1_OLPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_ODPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_ODPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ODPRESS->Text.ToDouble());
                if (txtGERENE_MCA1_ODPRESS->Text.ToDouble() <= 7){
                        CLP.WR( PC_HA_GERENE_MCA1_ODPRESS, (txtGERENE_MCA1_ODPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (7.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_ASPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_ASPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ASPRESS->Text.ToDouble());
                if (txtGERENE_MCA1_ASPRESS->Text.ToDouble() <= 7){
                        CLP.WR( PC_HA_GERENE_MCA1_ASPRESS, (txtGERENE_MCA1_ASPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (7.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_ADPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_ADPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA1_ADPRESS->Text.ToDouble());
                if (txtGERENE_MCA1_ADPRESS->Text.ToDouble() <= 7){
                        CLP.WR( PC_HA_GERENE_MCA1_ADPRESS, (txtGERENE_MCA1_ADPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (7.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_OLTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_OLTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA1_OLTEMP->Text.ToDouble());
                if (txtGERENE_MCA1_OLTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA1_OLTEMP, (txtGERENE_MCA1_OLTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA1_ADTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA1_ADTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA1_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA1_ADTEMP->Text.ToDouble());
                if (txtGERENE_MCA1_ADTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA1_ADTEMP, (txtGERENE_MCA1_ADTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_ARALIMPRESSClick(
      TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_ARALIMPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ARALIMPRESS->Text.ToDouble());
                if (txtGERENE_MCA2_ARALIMPRESS->Text.ToDouble() <= 4){
                        CLP.WR( PC_HA_GERENE_MCA2_ARALIMPRESS, (txtGERENE_MCA2_ARALIMPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (4.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_OLPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_OLPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_OLPRESS->Text.ToDouble());
                if (txtGERENE_MCA2_OLPRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_GERENE_MCA2_OLPRESS, (txtGERENE_MCA2_OLPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_ODPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_ODPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ODPRESS->Text.ToDouble());
                if (txtGERENE_MCA2_ODPRESS->Text.ToDouble() <= 7){
                        CLP.WR( PC_HA_GERENE_MCA2_ODPRESS, (txtGERENE_MCA2_ODPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (7.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_ASPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_ASPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ASPRESS->Text.ToDouble());
                if (txtGERENE_MCA2_ASPRESS->Text.ToDouble() <= 7){
                        CLP.WR( PC_HA_GERENE_MCA2_ASPRESS, (txtGERENE_MCA2_ASPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (7.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_ADPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_ADPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA2_ADPRESS->Text.ToDouble());
                if (txtGERENE_MCA2_ADPRESS->Text.ToDouble() <= 7){
                        CLP.WR( PC_HA_GERENE_MCA2_ADPRESS, (txtGERENE_MCA2_ADPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (7.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_OLTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_OLTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA2_OLTEMP->Text.ToDouble());
                if (txtGERENE_MCA2_OLTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA2_OLTEMP, (txtGERENE_MCA2_OLTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA2_ADTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA2_ADTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA2_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA2_ADTEMP->Text.ToDouble());
                if (txtGERENE_MCA2_ADTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA2_ADTEMP, (txtGERENE_MCA2_ADTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_ARALIMPRESSClick(
      TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_ARALIMPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ARALIMPRESS->Text.ToDouble());
                if (txtGERENE_MCA3_ARALIMPRESS->Text.ToDouble() <= 3){
                        CLP.WR( PC_HA_GERENE_MCA3_ARALIMPRESS, (txtGERENE_MCA3_ARALIMPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (2.8 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_OLPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_OLPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_OLPRESS->Text.ToDouble());
                if (txtGERENE_MCA3_OLPRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_GERENE_MCA3_OLPRESS, (txtGERENE_MCA3_OLPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_ODPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_ODPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ODPRESS->Text.ToDouble());
                if (txtGERENE_MCA3_ODPRESS->Text.ToDouble() <= 4){
                        CLP.WR( PC_HA_GERENE_MCA3_ODPRESS, (txtGERENE_MCA3_ODPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (4.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_ASPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_ASPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ASPRESS->Text.ToDouble());
                if (txtGERENE_MCA3_ASPRESS->Text.ToDouble() <= 3){
                        CLP.WR( PC_HA_GERENE_MCA3_ASPRESS, (txtGERENE_MCA3_ASPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (2.8 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_ADPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_ADPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA3_ADPRESS->Text.ToDouble());
                if (txtGERENE_MCA3_ADPRESS->Text.ToDouble() <= 4){
                        CLP.WR( PC_HA_GERENE_MCA3_ADPRESS, (txtGERENE_MCA3_ADPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (4.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_OLTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_OLTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA3_OLTEMP->Text.ToDouble());
                if (txtGERENE_MCA3_OLTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA3_OLTEMP, (txtGERENE_MCA3_OLTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA3_ADTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA3_ADTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA3_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA3_ADTEMP->Text.ToDouble());
                if (txtGERENE_MCA3_ADTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA3_ADTEMP, (txtGERENE_MCA3_ADTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_ARALIMPRESSClick(
      TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_ARALIMPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_ARALIMPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ARALIMPRESS->Text.ToDouble());
                if (txtGERENE_MCA4_ARALIMPRESS->Text.ToDouble() <= 3){
                        CLP.WR( PC_HA_GERENE_MCA4_ARALIMPRESS, (txtGERENE_MCA4_ARALIMPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (2.8 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_OLPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_OLPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_OLPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_OLPRESS->Text.ToDouble());
                if (txtGERENE_MCA4_OLPRESS->Text.ToDouble() <= 10){
                        CLP.WR( PC_HA_GERENE_MCA4_OLPRESS, (txtGERENE_MCA4_OLPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (10.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_ODPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_ODPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_ODPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ODPRESS->Text.ToDouble());
                if (txtGERENE_MCA4_ODPRESS->Text.ToDouble() <= 4){
                        CLP.WR( PC_HA_GERENE_MCA4_ODPRESS, (txtGERENE_MCA4_ODPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (4.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_ASPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_ASPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_ASPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ASPRESS->Text.ToDouble());
                if (txtGERENE_MCA4_ASPRESS->Text.ToDouble() <= 3){
                        CLP.WR( PC_HA_GERENE_MCA4_ASPRESS, (txtGERENE_MCA4_ASPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (2.8 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_ADPRESSClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_ADPRESS->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_ADPRESS->Text = FormatFloat("0.###",txtGERENE_MCA4_ADPRESS->Text.ToDouble());
                if (txtGERENE_MCA4_ADPRESS->Text.ToDouble() <= 4){
                        CLP.WR( PC_HA_GERENE_MCA4_ADPRESS, (txtGERENE_MCA4_ADPRESS->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (4.0 bar)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_OLTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_OLTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_OLTEMP->Text = FormatFloat("0.###",txtGERENE_MCA4_OLTEMP->Text.ToDouble());
                if (txtGERENE_MCA4_OLTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA4_OLTEMP, (txtGERENE_MCA4_OLTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGERENE_MCA4_ADTEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGERENE_MCA4_ADTEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGERENE_MCA4_ADTEMP->Text = FormatFloat("0.###",txtGERENE_MCA4_ADTEMP->Text.ToDouble());
                if (txtGERENE_MCA4_ADTEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GERENE_MCA4_ADTEMP, (txtGERENE_MCA4_ADTEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                                     MCAS
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              PROTEÇÃO CATÓDICA
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPROTC_PRPC_SINAL1Click(TObject *Sender)
{
        if (btnPROTC_PRPC_SINAL1->Caption == "Inativo"){
		CLP.WR( PC_HL_PROTC_PRPC_SINAL1, 1 );
	}
	else{
		CLP.WR( PC_HL_PROTC_PRPC_SINAL1, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPROTC_PRPC_SINAL2Click(TObject *Sender)
{
        if (btnPROTC_PRPC_SINAL2->Caption == "Inativo"){
		CLP.WR( PC_HL_PROTC_PRPC_SINAL2, 1 );
	}
	else{
		CLP.WR( PC_HL_PROTC_PRPC_SINAL2, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPROTC_PRPC_SINAL3Click(TObject *Sender)
{
        if (btnPROTC_PRPC_SINAL3->Caption == "Inativo"){
		CLP.WR( PC_HL_PROTC_PRPC_SINAL3, 1 );
	}
	else{
		CLP.WR( PC_HL_PROTC_PRPC_SINAL3, 0 );
	};
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              PROTEÇÃO CATÓDICA
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                                  FRIGORÍFICA
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARCF_CFCAR_TEMPALTAClick(
      TObject *Sender)
{
        if (btnRARCF_CFCAR_TEMPALTA->Caption == "Não Temp. Alta"){
		CLP.WR( PC_HL_RARCF_CFCAR_TEMPALTA, 1 );
	}
	else{
		CLP.WR( PC_HL_RARCF_CFCAR_TEMPALTA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARCF_CFLAT_TEMPALTAClick(
      TObject *Sender)
{
        if (btnRARCF_CFLAT_TEMPALTA->Caption == "Não Temp. Alta"){
		CLP.WR( PC_HL_RARCF_CFLAT_TEMPALTA, 1 );
	}
	else{
		CLP.WR( PC_HL_RARCF_CFLAT_TEMPALTA, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRARCF_CFLAT_TEMPBAIXAClick(
      TObject *Sender)
{
        if (btnRARCF_CFLAT_TEMPBAIXA->Caption == "Não Temp. Baixa"){
		CLP.WR( PC_HL_RARCF_CFLAT_TEMPBAIXA, 0 );
	}
	else{
		CLP.WR( PC_HL_RARCF_CFLAT_TEMPBAIXA, 1 );
	};
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnRARCF_CFVEG_TEMPALTAClick(
      TObject *Sender)
{
        if (btnRARCF_CFVEG_TEMPALTA->Caption == "Não Temp. Alta"){
		CLP.WR( PC_HL_RARCF_CFVEG_TEMPALTA, 1 );
	}
	else{
		CLP.WR( PC_HL_RARCF_CFVEG_TEMPALTA, 0 );
	};        
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnRARCF_CFVEG_TEMPBAIXAClick(
      TObject *Sender)
{
        if (btnRARCF_CFVEG_TEMPBAIXA->Caption == "Não Temp. Baixa"){
		CLP.WR( PC_HL_RARCF_CFVEG_TEMPBAIXA, 0 );
	}
	else{
		CLP.WR( PC_HL_RARCF_CFVEG_TEMPBAIXA, 1 );
	};
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                                  FRIGORÍFICA
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              MAQUINA DO LEME
//==============================================================================
//==============================================================================
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_LIGADOClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBB_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_MAQLEM_MOTBB_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_EMREMClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBB_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_MAQLEM_MOTBB_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_ALIMDISPONClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBB_ALIMDISPON->Caption == "Alim. Não Dispon."){
		CLP.WR( PC_HL_MAQLEM_MOTBB_ALIMDISPON, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_ALIMDISPON, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_ALIMLOGICOKClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBB_ALIMLOGICOK->Caption == "Sem Alim. Lógica"){
		CLP.WR( PC_HL_MAQLEM_MOTBB_ALIMLOGICOK, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_ALIMLOGICOK, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_FALTADEFASEClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBB_FALTADEFASE->Caption == "Sem Falta de Fase"){
		CLP.WR( PC_HL_MAQLEM_MOTBB_FALTADEFASE, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_FALTADEFASE, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_EMSOBRECClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBB_EMSOBREC->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_MAQLEM_MOTBB_EMSOBREC, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_EMSOBREC, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_DESUMLIGClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBB_DESUMLIG->Caption == "Desum. Des."){
		CLP.WR( PC_HL_MAQLEM_MOTBB_DESUMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBB_DESUMLIG, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPartirMAQLEM_MOTBBClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBB_LIGADO->Caption == "Parado"){
                tmrPararMAQLEM_MOTBB->Enabled = false;
                tmrPartirMAQLEM_MOTBB->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPararMAQLEM_MOTBBClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBB_LIGADO->Caption == "Ligado"){
                tmrPartirMAQLEM_MOTBB->Enabled = false;
                tmrPararMAQLEM_MOTBB->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrPartirMAQLEM_MOTBBTimer(TObject *Sender)
{
        CLP.WR( PC_HL_MAQLEM_MOTBB_LIGADO, 1 );
        tmrPartirMAQLEM_MOTBB->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrPararMAQLEM_MOTBBTimer(TObject *Sender)
{
        CLP.WR( PC_HL_MAQLEM_MOTBB_LIGADO, 0 );
        tmrPararMAQLEM_MOTBB->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBB_PARAREMERGLOCClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBB_PARAREMERGLOC->Caption == "Parar em Emergência"){
                tmrPartirMAQLEM_MOTBB->Enabled = false;
                if (btnMAQLEM_MOTBB_LIGADO->Caption == "Ligado"  && tmrPararMAQLEM_MOTBB->Enabled == false){
                        //if ( nao_atender_cmd_bba == false ) {
                                tmrPararMAQLEM_MOTBB->Enabled = true;
                        //}
                }
                btnMAQLEM_MOTBB_PARAREMERGLOC->Caption = "Rearmar";
                shpMAQLEM_MOTBB_PARAREMERGLOC->Brush->Color = clRed;
                btnPartirMAQLEM_MOTBB->Enabled = false;
                btnMAQLEM_MOTBB_LIGADO->Enabled = false;
        }else{
                btnMAQLEM_MOTBB_PARAREMERGLOC->Caption = "Parar em Emergência";
                shpMAQLEM_MOTBB_PARAREMERGLOC->Brush->Color = clWhite;
                btnPartirMAQLEM_MOTBB->Enabled = true;
                btnMAQLEM_MOTBB_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_LIGADOClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBE_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_MAQLEM_MOTBE_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_EMREMClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBE_EMREM->Caption == "Em Local"){
		CLP.WR( PC_HL_MAQLEM_MOTBE_EMREM, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_EMREM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_ALIMDISPONClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBE_ALIMDISPON->Caption == "Alim. Não Dispon."){
		CLP.WR( PC_HL_MAQLEM_MOTBE_ALIMDISPON, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_ALIMDISPON, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_ALIMLOGICOKClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBE_ALIMLOGICOK->Caption == "Sem Alim. Lógica"){
		CLP.WR( PC_HL_MAQLEM_MOTBE_ALIMLOGICOK, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_ALIMLOGICOK, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_FALTADEFASEClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBE_FALTADEFASE->Caption == "Sem Falta de Fase"){
		CLP.WR( PC_HL_MAQLEM_MOTBE_FALTADEFASE, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_FALTADEFASE, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_EMSOBRECClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBE_EMSOBREC->Caption == "Sem Sobrecarga"){
		CLP.WR( PC_HL_MAQLEM_MOTBE_EMSOBREC, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_EMSOBREC, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_DESUMLIGClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBE_DESUMLIG->Caption == "Desum. Des."){
		CLP.WR( PC_HL_MAQLEM_MOTBE_DESUMLIG, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_MOTBE_DESUMLIG, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPartirMAQLEM_MOTBEClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBE_LIGADO->Caption == "Parado"){
                tmrPararMAQLEM_MOTBE->Enabled = false;
                tmrPartirMAQLEM_MOTBE->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnPararMAQLEM_MOTBEClick(TObject *Sender)
{
        if (btnMAQLEM_MOTBE_LIGADO->Caption == "Ligado"){
                tmrPartirMAQLEM_MOTBE->Enabled = false;
                tmrPararMAQLEM_MOTBE->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrPartirMAQLEM_MOTBETimer(TObject *Sender)
{
        CLP.WR( PC_HL_MAQLEM_MOTBE_LIGADO, 1 );
        tmrPartirMAQLEM_MOTBE->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrPararMAQLEM_MOTBETimer(TObject *Sender)
{
        CLP.WR( PC_HL_MAQLEM_MOTBE_LIGADO, 0 );
        tmrPararMAQLEM_MOTBE->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_MOTBE_PARAREMERGLOCClick(
      TObject *Sender)
{
        if (btnMAQLEM_MOTBE_PARAREMERGLOC->Caption == "Parar em Emergência"){
                tmrPartirMAQLEM_MOTBE->Enabled = false;
                if (btnMAQLEM_MOTBE_LIGADO->Caption == "Ligado"  && tmrPararMAQLEM_MOTBE->Enabled == false){
                        //if ( nao_atender_cmd_bba == false ) {
                                tmrPararMAQLEM_MOTBE->Enabled = true;
                        //}
                }
                btnMAQLEM_MOTBE_PARAREMERGLOC->Caption = "Rearmar";
                shpMAQLEM_MOTBE_PARAREMERGLOC->Brush->Color = clRed;
                btnPartirMAQLEM_MOTBE->Enabled = false;
                btnMAQLEM_MOTBE_LIGADO->Enabled = false;
        }else{
                btnMAQLEM_MOTBE_PARAREMERGLOC->Caption = "Parar em Emergência";
                shpMAQLEM_MOTBE_PARAREMERGLOC->Brush->Color = clWhite;
                btnPartirMAQLEM_MOTBE->Enabled = true;
                btnMAQLEM_MOTBE_LIGADO->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_CML_UHNASSOCClick(TObject *Sender)
{
        if (btnMAQLEM_CML_UHNASSOC->Caption == "U. hid. assoc."){
		CLP.WR( PC_HL_MAQLEM_CML_UHNASSOC, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_CML_UHNASSOC, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_CML_SELCUHDISPONClick(
      TObject *Sender)
{
        if (btnMAQLEM_CML_SELCUHDISPON->Caption == "Sel. da U. Hid. n disp."){
		CLP.WR( PC_HL_MAQLEM_CML_SELCUHDISPON, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_CML_SELCUHDISPON, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_CML_CMDDISPCCMClick(
      TObject *Sender)
{
        if (btnMAQLEM_CML_CMDDISPCCM->Caption == "Est. de Cmd. n no CCM"){
		CLP.WR( PC_HL_MAQLEM_CML_CMDDISPCCM, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_CML_CMDDISPCCM, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_CML_UHBBSELClick(TObject *Sender)
{
        if (btnMAQLEM_CML_UHBBSEL->Caption == "U. Hid. de BB n sel."){
		CLP.WR( PC_HL_MAQLEM_CML_UHBBSEL, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_CML_UHBBSEL, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_CML_UHBESELClick(TObject *Sender)
{
        if (btnMAQLEM_CML_UHBESEL->Caption == "U. Hid. de BE n sel."){
		CLP.WR( PC_HL_MAQLEM_CML_UHBESEL, 1 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_CML_UHBESEL, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_UHIDBB_NVBXClick(TObject *Sender)
{
        if (btnMAQLEM_UHIDBB_NVBX->Caption == "Nível Normal"){
		CLP.WR( PC_HL_MAQLEM_UHIDBB_NVBX, 0 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_UHIDBB_NVBX, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_UHIDBB_TEMPALClick(
      TObject *Sender)
{
        if (btnMAQLEM_UHIDBB_TEMPAL->Caption == "Temperatura Normal"){
		CLP.WR( PC_HL_MAQLEM_UHIDBB_TEMPAL, 0 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_UHIDBB_TEMPAL, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_UHIDBB_PRESSBXClick(
      TObject *Sender)
{
        if (btnMAQLEM_UHIDBB_PRESSBX->Caption == "Pressão Normal"){
		CLP.WR( PC_HL_MAQLEM_UHIDBB_PRESSBX, 0 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_UHIDBB_PRESSBX, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_UHIDBE_NVBXClick(TObject *Sender)
{
        if (btnMAQLEM_UHIDBE_NVBX->Caption == "Nível Normal"){
		CLP.WR( PC_HL_MAQLEM_UHIDBE_NVBX, 0 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_UHIDBE_NVBX, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_UHIDBE_TEMPALClick(
      TObject *Sender)
{
       if (btnMAQLEM_UHIDBE_TEMPAL->Caption == "Temperatura Normal"){
		CLP.WR( PC_HL_MAQLEM_UHIDBE_TEMPAL, 0 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_UHIDBE_TEMPAL, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMAQLEM_UHIDBE_PRESSBXClick(
      TObject *Sender)
{
        if (btnMAQLEM_UHIDBE_PRESSBX->Caption == "Pressão Normal"){
		CLP.WR( PC_HL_MAQLEM_UHIDBE_PRESSBX, 0 );
	}
	else{
		CLP.WR( PC_HL_MAQLEM_UHIDBE_PRESSBX, 1 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnGOVBC_MAQLEM_LEMEPOSICClick(
      TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtGOVBC_MAQLEM_LEMEPOSIC->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtGOVBC_MAQLEM_LEMEPOSIC->Text = FormatFloat("0.###",txtGOVBC_MAQLEM_LEMEPOSIC->Text.ToDouble());
                CLP.WR( PC_HA_GOVBC_MAQLEM_LEMEPOSIC, (txtGOVBC_MAQLEM_LEMEPOSIC->Text.ToDouble()) );
                /*if (txtGOVBC_MAQLEM_LEMEPOSIC->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_GOVBC_MAQLEM_LEMEPOSIC, (txtGOVBC_MAQLEM_LEMEPOSIC->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                } */
        }
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                              MAQUINA DO LEME
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                             VENTILAÇÃO E EXTRAÇÃO
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEDPM_RVENPMA_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEDPM_RVENPMA_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEDPM_RVENPMA_TEMP->Text = FormatFloat("0.###",txtVEDPM_RVENPMA_TEMP->Text.ToDouble());
                if (txtVEDPM_RVENPMA_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEDPM_RVENPMA_TEMP, (txtVEDPM_RVENPMA_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEDPM_RVENPMV_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEDPM_RVENPMV_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEDPM_RVENPMV_TEMP->Text = FormatFloat("0.###",txtVEDPM_RVENPMV_TEMP->Text.ToDouble());
                if (txtVEDPM_RVENPMV_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEDPM_RVENPMV_TEMP, (txtVEDPM_RVENPMV_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEDPM_RVENPMR_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEDPM_RVENPMR_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEDPM_RVENPMR_TEMP->Text = FormatFloat("0.###",txtVEDPM_RVENPMR_TEMP->Text.ToDouble());
                if (txtVEDPM_RVENPMR_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEDPM_RVENPMR_TEMP, (txtVEDPM_RVENPMR_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_ANTCME_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEFPM_ANTCME_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEFPM_ANTCME_TEMP->Text = FormatFloat("0.###",txtVEFPM_ANTCME_TEMP->Text.ToDouble());
                if (txtVEFPM_ANTCME_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEFPM_ANTCME_TEMP, (txtVEFPM_ANTCME_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_ANTMAGE_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEFPM_ANTMAGE_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEFPM_ANTMAGE_TEMP->Text = FormatFloat("0.###",txtVEFPM_ANTMAGE_TEMP->Text.ToDouble());
                if (txtVEFPM_ANTMAGE_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEFPM_ANTMAGE_TEMP, (txtVEFPM_ANTMAGE_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_CONTALCA_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEFPM_CONTALCA_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEFPM_CONTALCA_TEMP->Text = FormatFloat("0.###",txtVEFPM_CONTALCA_TEMP->Text.ToDouble());
                if (txtVEFPM_CONTALCA_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEFPM_CONTALCA_TEMP, (txtVEFPM_CONTALCA_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_CPTCME_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEFPM_CPTCME_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEFPM_CPTCME_TEMP->Text = FormatFloat("0.###",txtVEFPM_CPTCME_TEMP->Text.ToDouble());
                if (txtVEFPM_CPTCME_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEFPM_CPTCME_TEMP, (txtVEFPM_CPTCME_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_ESTCHAFF_TEMPClick(TObject *Sender)
{
        float Teste;
        bool  TestaDouble = false;
        try{
                Teste = txtVEFPM_ESTCHAFF_TEMP->Text.ToDouble();
        }
        catch(...)
        {
                TestaDouble = true;
                Application->MessageBox("Valor Inválido - Não é do tipo correto", NULL, MB_OKCANCEL);
        }
        if (TestaDouble == false){
                txtVEFPM_ESTCHAFF_TEMP->Text = FormatFloat("0.###",txtVEFPM_ESTCHAFF_TEMP->Text.ToDouble());
                if (txtVEFPM_ESTCHAFF_TEMP->Text.ToDouble() <= 100){
                        CLP.WR( PC_HA_VEFPM_ESTCHAFF_TEMP, (txtVEFPM_ESTCHAFF_TEMP->Text.ToDouble()) );
                }else{
                        Application->MessageBox("Valor Inválido - Acima do Limite (100.0 ºC)", NULL, MB_OKCANCEL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE01_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE01_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE01_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE01_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE02_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE02_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE02_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE02_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE03_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE03_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE03_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE03_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE04_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE04_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE04_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE04_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE05_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE05_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE05_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE05_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE06_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE06_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE06_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE06_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_EXAE07_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_EXAE07_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_EXAE07_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_EXAE07_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVEFPM_VENT_LIGADOClick(TObject *Sender)
{
        if (btnVEFPM_VENT_LIGADO->Caption == "Parado"){
		CLP.WR( PC_HL_VEFPM_VENT_LIGADO, 1 );
	}
	else{
		CLP.WR( PC_HL_VEFPM_VENT_LIGADO, 0 );
	};
}
//---------------------------------------------------------------------------
//==============================================================================
//==============================================================================
//                             VENTILAÇÃO E EXTRAÇÃO
//==============================================================================
//==============================================================================
//---------------------------------------------------------------------------


