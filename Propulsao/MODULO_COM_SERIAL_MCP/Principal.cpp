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
//MÓDULO...........: MCP
//DATA DE INÍCIO...: 22.06.2015
//DATA DE PROTÓTIPO:
//DATA DE TÉRMINO..:
//DATA DE ATUALIZ..:
//DESIGNAÇÃO.......: ESTE MÓDULO DO SOFTWARE TEM COMO OBJETIVO EMULAR A COMUNICAÇÃO
//SERIAL DOS MCPS
//EM COPARCERIA DESTE MÓDULO ESTA O MÓDULO DE COMUNICAÇÃO MODBUS DE AUTORIA DO
//FUNCIONÁRIO FÁBIO TEIXEIRA, SUA IMPLEMENTAÇÃO É DESCONHECIDA
//***************************************************************************
#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
//#include "TModBusScanner.cpp" /* DRIVER MODBUS */
#include "ModBusDriverLib\TModBusTCPDriver.cpp"

//----------------- ENDEREÇOS DOS EQUIPAMENTOS -----------------
String MCPBE_ETH1_MAINWD     = "%MW2464";
String MCPBE_ETH1_STDBWD     = "%MW2465";
String MCPBE_ETH2_MAINWD     = "%MW2466";
String MCPBE_ETH2_STDBWD     = "%MW2467";

String MCPBE_ETH1_MAIN_LOPRu = "%MW740";
String MCPBE_ETH1_STDB_LOPRu = "%MW741";
String MCPBE_ETH2_MAIN_LOPRu = "%MW742";
String MCPBE_ETH2_STDB_LOPRu = "%MW743";

String MCPBB_ETH1_MAINWD     = "%MW2468";
String MCPBB_ETH1_STDBWD     = "%MW2469";
String MCPBB_ETH2_MAINWD     = "%MW2470";
String MCPBB_ETH2_STDBWD     = "%MW2471";

String MCPBB_ETH1_MAIN_LOPRu = "%MW744";
String MCPBB_ETH1_STDB_LOPRu = "%MW745";
String MCPBB_ETH2_MAIN_LOPRu = "%MW746";
String MCPBB_ETH2_STDB_LOPRu = "%MW747";

String TG_ETH1_WD            = "%MW2538";
String TG_ETH2_WD            = "%MW2673";
//------------------- VARIAVEIS DOS INTERNAS -------------------

String IP              = "120.40.0.1";
String CONTADOR_CONEXAO= "%MW33000";
String NomeForm        = "COMUNICAÇÃO SERIAL";
bool   perdaconexao    = false;
int    Varredura       = 0;
float  VALOR_ANTIGO    = 0;
bool   contador_ok     = false;
int    contador_scan   = 0;
int    numeroquedas    = 0;
int    lista           = 0;

int contador = 0;
int contadas = 0;

bool ativa_ETH1_BE = true;
bool ativa_MAIN_BE = true;
bool ativaETH1_M_BE = true;
bool ativa_STDB_BE = true;
bool ativaETH1_S_BE = true;
bool ativa_ETH2_BE = true;
bool ativaETH2_M_BE = true;
bool ativaETH2_S_BE = true;

bool ativa_ETH1_BB = true;
bool ativa_MAIN_BB = true;
bool ativaETH1_M_BB = true;
bool ativa_STDB_BB = true;
bool ativaETH1_S_BB = true;
bool ativa_ETH2_BB = true;
bool ativaETH2_M_BB = true;
bool ativaETH2_S_BB = true;

bool ativa_TG     = true;
bool ativaETH1_TG = true;
bool ativaETH2_TG = true;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;
//INCIALIZAÇÃO DO DRIVER
//TModBusScanner CLP ( frmPrincipal, QUANTUM, 3, 1 );
//INCIALIZAÇÃO DO DRIVER
TModBusTCPDriver CLP( frmPrincipal,IP,QUANTUM );
//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
        : TForm(Owner)
{
//CADASTROS DOS ENDEREÇOS UTILIZADOS
/*      CLP.CadastraLeitura(MCPBE_ETH1_MAINWD);
        CLP.CadastraLeitura(MCPBE_ETH1_STDBWD);
        CLP.CadastraLeitura(MCPBE_ETH2_MAINWD);
        CLP.CadastraLeitura(MCPBE_ETH2_STDBWD);

        CLP.CadastraLeitura(MCPBE_ETH1_MAIN_LOPRu);
        CLP.CadastraLeitura(MCPBE_ETH1_STDB_LOPRu);
        CLP.CadastraLeitura(MCPBE_ETH2_MAIN_LOPRu);
        CLP.CadastraLeitura(MCPBE_ETH2_STDB_LOPRu);

        CLP.CadastraLeitura(MCPBB_ETH1_MAINWD);
        CLP.CadastraLeitura(MCPBB_ETH1_STDBWD);
        CLP.CadastraLeitura(MCPBB_ETH2_MAINWD);
        CLP.CadastraLeitura(MCPBB_ETH2_STDBWD);

        CLP.CadastraLeitura(MCPBB_ETH1_MAIN_LOPRu);
        CLP.CadastraLeitura(MCPBB_ETH1_STDB_LOPRu);
        CLP.CadastraLeitura(MCPBB_ETH2_MAIN_LOPRu);
        CLP.CadastraLeitura(MCPBB_ETH2_STDB_LOPRu); */
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
void __fastcall TfrmPrincipal::tmrStartingTimer(TObject *Sender)
{
        tmrLeitura->Enabled = true;

        Animacao->Enabled = true;

        lblBufferR->Visible = true;
        lblBufferW->Visible = true;
        lblBufferEx->Visible = true;
        lblLista->Visible = true;

        if (ConexaoWatch->Enabled == false){
                ConexaoWatch->Enabled = true;
        }

        Lista->Enabled = true;

//FIM DA INICIALIZAÇÃO
        tmrStarting->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmrLeituraTimer(TObject *Sender)
{
        if ( ativa_ETH1_BE == true ){
                if ( ativa_MAIN_BE == true ){
                        if ( ativaETH1_M_BE == true && CLP.TamBufWR() < 10  ){
                                CLP.WR( MCPBE_ETH1_MAINWD, contador );
                                lblWDETH1MAIN->Caption = contador;

                                CLP.WR( MCPBE_ETH1_MAIN_LOPRu, 0);
                        }
                }
                if ( ativa_STDB_BE == true ){
                        if ( ativaETH1_S_BE == true && CLP.TamBufWR() < 10){
                                CLP.WR( MCPBE_ETH1_STDBWD, contador );
                                lblWDETH1STDB->Caption = contador;

                                CLP.WR( MCPBE_ETH1_STDB_LOPRu, 0);
                        }
                }
        }
        if ( ativa_ETH2_BE == true ){
                if ( ativa_MAIN_BE == true ){
                        if ( ativaETH2_M_BE == true && CLP.TamBufWR() < 10){
                                CLP.WR( MCPBE_ETH2_MAINWD, contador );
                                lblWDETH2MAIN->Caption = contador;

                                CLP.WR( MCPBE_ETH2_MAIN_LOPRu, 0);
                        }
                }
                if ( ativa_STDB_BE == true ){
                        if ( ativaETH2_S_BE == true && CLP.TamBufWR() < 10){
                                CLP.WR( MCPBE_ETH1_STDBWD, contador );
                                lblWDETH2STDB->Caption = contador;

                                 CLP.WR( MCPBE_ETH2_STDB_LOPRu, 0);
                        }
                }
        }

        if ( ativa_ETH1_BB == true ){
                if ( ativa_MAIN_BB == true && CLP.TamBufWR() < 10){
                        if ( ativaETH1_M_BB == true ){
                                CLP.WR( MCPBB_ETH1_MAINWD, contador );
                                lblWDETH1MAIN2->Caption = contador;

                                CLP.WR( MCPBB_ETH1_MAIN_LOPRu, 0);
                        }
                }
                if ( ativa_STDB_BB == true && CLP.TamBufWR() < 10){
                        if ( ativaETH1_S_BB == true ){
                                CLP.WR( MCPBB_ETH1_STDBWD, contador );
                                lblWDETH1STDB2->Caption = contador;

                                CLP.WR( MCPBB_ETH1_STDB_LOPRu, 0);
                        }
                }
        }
        if ( ativa_ETH2_BB == true ){
                if ( ativa_MAIN_BB == true ){
                        if ( ativaETH2_M_BB == true && CLP.TamBufWR() < 10){
                                CLP.WR( MCPBB_ETH2_MAINWD, contador );
                                lblWDETH2MAIN2->Caption = contador;

                                CLP.WR( MCPBB_ETH2_MAIN_LOPRu, 0);
                        }
                }
                if ( ativa_STDB_BB == true ){
                        if ( ativaETH2_S_BB == true && CLP.TamBufWR() < 10){
                                CLP.WR( MCPBB_ETH2_STDBWD, contador );
                                lblWDETH2STDB2->Caption = contador;

                                CLP.WR( MCPBB_ETH2_STDB_LOPRu, 0);
                        }
                }
        }

        if ( ativa_TG == true ){
                if ( ativaETH1_TG == true && CLP.TamBufWR() < 10){
                        CLP.WR( TG_ETH1_WD, contadas );
                        lblWDETH1TG->Caption = contadas;
                }
                if ( ativaETH2_TG == true && CLP.TamBufWR() < 10){
                        CLP.WR( TG_ETH2_WD, contadas );
                        lblWDETH2TG->Caption = contadas;
                }
        }

        contadas++;
        contador++;

        if (contador > 32000) {
                contador = 0;
        };

        if (contadas >60) {
                contadas = 0;
        };
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::AnimacaoTimer(TObject *Sender)
{
        if (( CLP.RD(MCPBE_ETH1_MAIN_LOPRu) == 1 )){
                Shape1->Brush->Color = clLime;
        }
        else{
                Shape1->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBE_ETH1_STDB_LOPRu) == 1 )){
                Shape2->Brush->Color = clLime;
        }
        else{
                Shape2->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBE_ETH2_MAIN_LOPRu) == 1 )){
                Shape3->Brush->Color = clLime;
        }
        else{
                Shape3->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBE_ETH2_STDB_LOPRu) == 1 )){
                Shape4->Brush->Color = clLime;
        }
        else{
                Shape4->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBB_ETH1_MAIN_LOPRu) == 1 )){
                Shape5->Brush->Color = clLime;
        }
        else{
                Shape5->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBB_ETH1_STDB_LOPRu) == 1 )){
                Shape6->Brush->Color = clLime;
        }
        else{
                Shape6->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBB_ETH2_MAIN_LOPRu) == 1 )){
                Shape7->Brush->Color = clLime;
        }
        else{
                Shape7->Brush->Color = clWhite;
        };

        if (( CLP.RD(MCPBB_ETH2_STDB_LOPRu) == 1 )){
                Shape8->Brush->Color = clLime;
        }
        else{
                Shape8->Brush->Color = clWhite;
        };
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1MBBClick(TObject *Sender)
{
        if ( btnETH1MBB->Caption == "ETH1 M ON" ) {
                btnETH1MBB->Caption = "ETH1 M OFF";
                ativaETH1_M_BB = false;
        }
        else{
                btnETH1MBB->Caption = "ETH1 M ON";
                ativaETH1_M_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1SBBClick(TObject *Sender)
{
        if ( btnETH1SBB->Caption == "ETH1 S ON" ) {
                btnETH1SBB->Caption = "ETH1 S OFF";
                ativaETH1_S_BB = false;
        }
        else{
                btnETH1SBB->Caption = "ETH1 S ON";
                ativaETH1_S_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2MBBClick(TObject *Sender)
{
         if ( btnETH2MBB->Caption == "ETH2 M ON" ) {
                btnETH2MBB->Caption = "ETH2 M OFF";
                ativaETH2_M_BB = false;
        }
        else{
                btnETH2MBB->Caption = "ETH2 M ON";
                ativaETH2_M_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2SBBClick(TObject *Sender)
{
        if ( btnETH2SBB->Caption == "ETH2 S ON" ) {
                btnETH2SBB->Caption = "ETH2 S OFF";
                ativaETH2_S_BB = false;
        }
        else{
                btnETH2SBB->Caption = "ETH1 S ON";
                ativaETH2_S_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1BBClick(TObject *Sender)
{
        if ( btnETH1BB->Caption == "ETH1 ON" ) {
                btnETH1BB->Caption = "ETH1 OFF";
                ativa_ETH1_BB = false;
        }
        else{
                btnETH1BB->Caption = "ETH1 ON";
                ativa_ETH1_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2BBClick(TObject *Sender)
{
        if ( btnETH2BB->Caption == "ETH2 ON" ) {
                btnETH2BB->Caption = "ETH2 OFF";
                ativa_ETH2_BB = false;
        }
        else{
                btnETH2BB->Caption = "ETH2 ON";
                ativa_ETH2_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMAINBBClick(TObject *Sender)
{
        if ( btnMAINBB->Caption == "MAIN ON" ) {
                btnMAINBB->Caption = "MAIN OFF";
                ativa_MAIN_BB = false;
        }
        else{
                btnMAINBB->Caption = "MAIN ON";
                ativa_MAIN_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSTDBBBClick(TObject *Sender)
{
        if ( btnSTDBBB->Caption == "STDB ON" ) {
                btnSTDBBB->Caption = "STDB OFF";
                ativa_STDB_BB = false;
        }
        else{
                btnSTDBBB->Caption = "STDB ON";
                ativa_STDB_BB = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1MBEClick(TObject *Sender)
{
        if ( btnETH1MBE->Caption == "ETH1 M ON" ) {
                btnETH1MBE->Caption = "ETH1 M OFF";
                ativaETH1_M_BE = false;
        }
        else{
                btnETH1MBE->Caption = "ETH1 M ON";
                ativaETH1_M_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1SBEClick(TObject *Sender)
{
        if ( btnETH1SBE->Caption == "ETH1 S ON" ) {
                btnETH1SBE->Caption = "ETH1 S OFF";
                ativaETH1_S_BE = false;
        }
        else{
                btnETH1SBE->Caption = "ETH1 S ON";
                ativaETH1_S_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2MBEClick(TObject *Sender)
{
         if ( btnETH2MBE->Caption == "ETH2 M ON" ) {
                btnETH2MBE->Caption = "ETH2 M OFF";
                ativaETH2_M_BE = false;
        }
        else{
                btnETH2MBE->Caption = "ETH2 M ON";
                ativaETH2_M_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2SBEClick(TObject *Sender)
{
        if ( btnETH2SBE->Caption == "ETH2 S ON" ) {
                btnETH2SBE->Caption = "ETH2 S OFF";
                ativaETH2_S_BE = false;
        }
        else{
                btnETH2SBE->Caption = "ETH1 S ON";
                ativaETH2_S_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1BEClick(TObject *Sender)
{
        if ( btnETH1BE->Caption == "ETH1 ON" ) {
                btnETH1BE->Caption = "ETH1 OFF";
                ativa_ETH1_BE = false;
        }
        else{
                btnETH1BE->Caption = "ETH1 ON";
                ativa_ETH1_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2BEClick(TObject *Sender)
{
        if ( btnETH2BE->Caption == "ETH2 ON" ) {
                btnETH2BE->Caption = "ETH2 OFF";
                ativa_ETH2_BE = false;
        }
        else{
                btnETH2BE->Caption = "ETH2 ON";
                ativa_ETH2_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnMAINBEClick(TObject *Sender)
{
        if ( btnMAINBE->Caption == "MAIN ON" ) {
                btnMAINBE->Caption = "MAIN OFF";
                ativa_MAIN_BE = false;
        }
        else{
                btnMAINBE->Caption = "MAIN ON";
                ativa_MAIN_BE = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnSTDBBEClick(TObject *Sender)
{
        if ( btnSTDBBE->Caption == "STDB ON" ) {
                btnSTDBBE->Caption = "STDB OFF";
                ativa_STDB_BE = false;
        }
        else{
                btnSTDBBE->Caption = "STDB ON";
                ativa_STDB_BE = true;
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::tmrReconectaTimer(TObject *Sender)
{
        //RECONEXÃO
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
                /*shpAguarde->Top = 440;
                shpAguarde->Left = 0;
                shpAguarde->Width = 657;
                shpAguarde->Height = 49;*/
                shpAguarde->Visible = true;
                /*lblAguarde->Top = 8;
                lblAguarde->Left = 0;
                lblAguarde->Width = 649;
                lblAguarde->Height = 29;*/
                lblAguarde->Visible = true;
        }
        else{
                //if (lista < 10 ){
                //        tmrLeitura->Enabled = true;
                //}
                /*shpAguarde->Top = 5000;
                shpAguarde->Left = 5000;
                shpAguarde->Width = 0;
                shpAguarde->Height = 0;*/
                shpAguarde->Visible = false;
                /*lblAguarde->Top = 5000;
                lblAguarde->Left = 5000;
                lblAguarde->Width = 0;
                lblAguarde->Height = 0;*/
                lblAguarde->Visible = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH1TGClick(TObject *Sender)
{
        if ( btnETH1TG->Caption == "ETH1 ON" ) {
                btnETH1TG->Caption = "ETH1 OFF";
                ativaETH1_TG = false;
        }
        else{
                btnETH1TG->Caption = "ETH1 ON";
                ativaETH1_TG = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnETH2TGClick(TObject *Sender)
{
        if ( btnETH2TG->Caption == "ETH2 ON" ) {
                btnETH2TG->Caption = "ETH2 OFF";
                ativaETH2_TG = false;
        }
        else{
                btnETH2TG->Caption = "ETH2 ON";
                ativaETH2_TG = true;
        }
}
//---------------------------------------------------------------------------

