
/*
 *  CLASSE THREAD DE SOCKET - TModBusSocketThread
 *
 *  - Implementa uma classe thread para o processamento
 *    da tráfego de rede independentemente do processo pai
 *    do Driver ModBus
 *
 *  Features:
 *
 *  >
 *
 *
 */


#ifndef  __TMODBUSSOCKETTHREAD_CPP
#define  __TMODBUSSOCKETTHREAD_CPP


#ifndef __QUEUE_H
#include <queue.h>
#endif

#ifndef  __DEQUE_H
#include <deque.h>
#endif

#ifndef  __TLISTACIRCULAR_CPP
#include "TListaCircular.cpp"
#endif

#ifndef  __TMODBUSCMD_CPP
#include "TModBusCmd.cpp"
#endif


class TModBusSocketThread : public TThread  // ModBus Driver Thread
{
protected:
   void __fastcall Execute();


public:
   __fastcall TModBusSocketThread ( bool CreateSuspended );

   int  GetTamMsgBurst();
   void SetTamMsgBurst( int t );

   void SetClientSocket( TClientSocket *s );

   void SetStringListDebugLog( TStringList *l );

   void EnableDebugLog();

   int  GetTamCmdsCiclicos();
   int  GetTamCmdsSimples();


   bool CmdSimplesPushFront( TModBusCmd* );
   bool CmdSimplesLivre();


   bool
      rebuildCiclicos,    // Flag que indica ser necessário o rebuild da lista de comandos cíclicos

     *M,        // Área de memória ModBus (Coils)
     *M_init,   // Flags de endereços inicializados (Coils)
     *M_read,   // Flags de necessidade de leitura dos endereços (Coils)
     *MW_init,  // Flags de endereços inicializados (Holding Registers)
     *MW_read;  // Flags de necessidade de leitura dos endereços (Holding Registers)

   short int
     *MW;       // Área de memória ModBus (Holding Registers)

   TModBusCmd
     **inputCmds;


//private:

   void __fastcall RefreshSocket();


   bool TemIDLivre();

   void GuardaIDUsado( unsigned short int id );
   void LiberaIDUsado( unsigned short int id );


   void RecebeSePuder();              //

   TModBusCmd* GetCmdParaEnviar();    //

   bool EnviaSePuder();               //
   void TimedOut();                   //

   void ProcessaRespostasComandos();  //

   void VerificaComandosPerdidosFalhaSock();
   void ReenviaComandosPerdidosFalhaSock();
   
   
   void RebuildComandosCiclicos();    //



   bool ConsomeComandoSimplesInput(); //

   // 'RebuildComandosSimples' e Sub-Funções

   void RebuildComandosSimples();     //

   void OrdenaComandosSimplesASC();   //


   void ReduzFC22();                  // Mask Write Register
   void CombinaComandosFC22( TModBusCmd *cmd1, TModBusCmd *cmd2 );
   bool TransformaFC22emFC16( TModBusCmd *cmd1 );
 
   void ReduzFC06();                  // 
   void TransformaFC06emFC16( TModBusCmd *cmd1 );

   void ReduzFC16();                  // 
   bool CombinaComandosFC16( TModBusCmd *cmd1, TModBusCmd *cmd2 );

   void ReduzFC05();                  // 
   void TransformaFC05emFC15( TModBusCmd *cmd1 );
   
   void ReduzFC15();                  // 
   bool CombinaComandosFC15( TModBusCmd *cmd1, TModBusCmd *cmd2 );

/*
   void OrdenaComandosSimplesDESC();  //

   bool ReduzFC01();    // Read Coil
   bool ReduzFC03();    // Read Holding Registers
   bool ReduzFC05();    // Force Single Coil

   bool ExpandeFC15();  // Force Multiple Coils
   void ExpandeFC16();  // Preset Multiple Registers
*/


   bool
      resendCmdsFalhaSock,
      rebuildingCmdSimples;  // Flag que sinaliza que os comandos simples estão sendo reconstruídos;


   unsigned short int
      timeoutMS,
      transacID_idx,
      tamMsgBurst;

   deque < unsigned short int >
      listaIDsUsados;



   TListaCircular < TModBusCmd* >
      cmdsCiclicos;

   deque < TModBusCmd* >
     *cmdsSimples,
     *cmdsSimplesRebuilding,
      cmdsEnviados;

   deque < byteBuffStruct* >
      buffersRecebidos;



   TStringList
      *debugLog;

   TClientSocket
      *sock;

   TDateTime
      T0, T1;
};


__fastcall TModBusSocketThread::TModBusSocketThread( bool CreateSuspended = true ) : TThread( CreateSuspended )  // CONFERIDO, SEM MEM. LEAKS
{
   timeoutMS     = 1000;
   transacID_idx = 0;
   tamMsgBurst   = 8;

   resendCmdsFalhaSock  = false;
   rebuildCiclicos      = false;
   rebuildingCmdSimples = false;

   sock = NULL;

   cmdsSimples = new deque < TModBusCmd* >;
   cmdsSimplesRebuilding = cmdsSimples;

   debugLog = NULL;
}


void __fastcall TModBusSocketThread::Execute()  // CONFERIDO, SEM MEM. LEAKS
{
   while( sock )
      RefreshSocket();


//      Synchronize( RefreshSocket );
}



int TModBusSocketThread::GetTamMsgBurst()  { return tamMsgBurst; }  // CONFERIDO, SEM MEM. LEAKS


void TModBusSocketThread::SetTamMsgBurst( int t )  // CONFERIDO, SEM MEM. LEAKS
{
   if ( ( t > 0 ) && ( t <= 64 ) )
      tamMsgBurst = t;
}


void TModBusSocketThread::SetClientSocket( TClientSocket *s )  { sock = s; }  // CONFERIDO, SEM MEM. LEAKS


void TModBusSocketThread::SetStringListDebugLog( TStringList *l )  { debugLog = l; }  // CONFERIDO, SEM MEM. LEAKS


void TModBusSocketThread::EnableDebugLog()  { debugLog = new TStringList; }  // CONFERIDO, SEM MEM. LEAKS


int TModBusSocketThread::GetTamCmdsCiclicos()  // CONFERIDO, SEM MEM. LEAKS
{
   return cmdsCiclicos.size();
}

int TModBusSocketThread::GetTamCmdsSimples()  // CONFERIDO, SEM MEM. LEAKS
{
   return ( cmdsSimples ) ? cmdsSimples->size() : 0;
}


bool TModBusSocketThread::CmdSimplesPushFront( TModBusCmd* cmd )  // CONFERIDO, SEM MEM. LEAKS
{
   cmdsSimples->push_front( cmd );
}


bool TModBusSocketThread::TemIDLivre()  // CONFERIDO, SEM MEM. LEAKS
{
   int
      somaCmds  = ( cmdsSimples ) ? cmdsCiclicos.size() + cmdsSimples->size() : cmdsCiclicos.size(),
      qtdLimite = ( somaCmds > tamMsgBurst ) ? tamMsgBurst : somaCmds;

   return ( listaIDsUsados.size() < qtdLimite );
}


void TModBusSocketThread::GuardaIDUsado( unsigned short int id )  // CONFERIDO, SEM MEM. LEAKS
{
   listaIDsUsados.push_back( id );
}


void TModBusSocketThread::LiberaIDUsado( unsigned short int id )  // CONFERIDO, SEM MEM. LEAKS
{
   for ( int i = 0, qtd = listaIDsUsados.size(); i < qtd; i++ )
      if ( listaIDsUsados[i] == id )
      {
         listaIDsUsados.erase( listaIDsUsados.begin() + i );
         break;
      }
}


bool TModBusSocketThread::ConsomeComandoSimplesInput()  // CONFERIDO, SEM MEM. LEAKS
{
   bool novoCmd = false;

   for ( int i = 0; cmdsSimples && ( i < 0x10000 ); i++ )
      if ( inputCmds[i] )
      {
         cmdsSimples->push_back( inputCmds[i] );

         inputCmds[i] = NULL;
         novoCmd = true;
      }


   return novoCmd;
}


void __fastcall TModBusSocketThread::RefreshSocket()  // CONFERIDO, SEM MEM. LEAKS
{
   bool novoCmdSimples = ConsomeComandoSimplesInput();

   if ( rebuildCiclicos )
      RebuildComandosCiclicos();


   if ( sock->Active )  // Socket Ativo
   {
      ReenviaComandosPerdidosFalhaSock();
      
      RecebeSePuder();

      if ( ! EnviaSePuder() )  // Se não pôde enviar nada
      {
         // Monitora por quanto tempo e gera um timeout (???)

         /*
         if ( ( cmdsCiclicos.size() > 0 ) ||
              ( cmdsSimples .size() > 0 ) )
         {
            T1 = Now() - T0;

            int t = ( T1.FormatString( "s" ).ToInt() * 1000 ) + T1.FormatString( "z" ).ToInt();

            if ( t > timeoutMS )
               TimedOut();
         }
         */
      }

      else if ( novoCmdSimples )  // Sempre que não puder enviar nada, tenta otimizar a lista de comandos simples
         RebuildComandosSimples();
   }
   
   else
   {
      VerificaComandosPerdidosFalhaSock();
      
      if ( novoCmdSimples )  // Sempre que não estiver conectado tenta otimizar a lista de comandos simples
         RebuildComandosSimples();
   }


   ProcessaRespostasComandos();
}


void TModBusSocketThread::RecebeSePuder()  // CONFERIDO, SEM MEM. LEAKS
{
   int tam = 0;

   // Se tem algo a receber pelo socket

   if ( tam = sock->Socket->ReceiveLength() )
   {
      byteBuffStruct
         *sockBuff = new byteBuffStruct( tam );

      sock->Socket->ReceiveBuf( sockBuff->buf, sockBuff->tam );



      if ( ExtraiComandosDoBufferRecurs( sockBuff, & buffersRecebidos ) )  // Se conseguiu extrair algum comando do Buffer recebido no socket
      {
         for ( int i = 0, qtd = buffersRecebidos.size(); i < qtd; i++ )
            LiberaIDUsado( toggleEndianess( readMemAs <unsigned short int> ( & buffersRecebidos[i]->buf[0] ) ) );



         if ( debugLog )  // Rotinas de debug
         {
            if ( buffersRecebidos.size() == 1 )
               debugLog->Add( FormatDateTime( "nn:ss:zzz", Now() ) + "\t" + PrintBuffAsModBusResp( buffersRecebidos[0] ) );

            else if ( buffersRecebidos.size() > 1 )
            {
               AnsiString temp = "--> ";

               for ( int i = 0; i < sockBuff->tam; i++ )
                  temp += IntToHex( (unsigned short int) sockBuff->buf[i], 2 );

               debugLog->Add( FormatDateTime( "nn:ss:zzz", Now() ) + "\t" + temp );


               for ( int i = 0, qtd = buffersRecebidos.size(); i < qtd; i++ )
                  debugLog->Add( "\t\t" + PrintBuffAsModBusResp( buffersRecebidos[i] ) ) ;
            }
         }
      }


      delete sockBuff;
   }
}


TModBusCmd* TModBusSocketThread::GetCmdParaEnviar()  // CONFERIDO, SEM MEM. LEAKS
{
   static bool enviaSimplesDessaVez = true;

   TModBusCmd* cmdToSend = NULL;


   if ( ( enviaSimplesDessaVez ) && cmdsSimples && ( cmdsSimples->size() ) )
   {
      cmdToSend = cmdsSimples->front();
      cmdsSimples->pop_front();
      
      enviaSimplesDessaVez = false;
   }

   else
   {
      if ( cmdsCiclicos.size() )
         cmdToSend = new TModBusCmd ( cmdsCiclicos.get() );
      
      enviaSimplesDessaVez = true;
   }


   return cmdToSend;
}


void TModBusSocketThread::VerificaComandosPerdidosFalhaSock()  // CONFERIDO, SEM MEM. LEAKS
{
   resendCmdsFalhaSock = cmdsEnviados.size() > 0;
}


void TModBusSocketThread::ReenviaComandosPerdidosFalhaSock()  // CONFERIDO, SEM MEM. LEAKS
{
   if ( resendCmdsFalhaSock )
   {
      resendCmdsFalhaSock = false;
      
      for ( int i = 0; i < cmdsEnviados.size(); i++ )
         sock->Socket->SendBuf( cmdsEnviados[i]->cmd->buf, cmdsEnviados[i]->cmd->tam );
   }
}


bool TModBusSocketThread::EnviaSePuder()  // CONFERIDO, SEM MEM. LEAKS
{
   bool enviou = false;

   // Se puder enviar algo pelo socket

   if ( ( ( cmdsCiclicos.size() > 0 ) ||
          ( cmdsSimples->size() > 0 ) )  &&  // Testa se pode enviar pelo socket
        TemIDLivre() )
   {
      //T0 = Now();  // Horário da última vez que conseguiu entrar nesse bloco.


      TModBusCmd* cmdToSend = GetCmdParaEnviar();


      if ( cmdToSend )
      {
         cmdToSend->SetTransactionId( transacID_idx );
         GuardaIDUsado( transacID_idx++ );

         sock->Socket->SendBuf( cmdToSend->cmd->buf, cmdToSend->cmd->tam );

         cmdsEnviados.push_back( cmdToSend );

         enviou = true;

         
         if ( debugLog )
            debugLog->Add( FormatDateTime( "nn:ss:zzz", Now() ) + "\t" + PrintBuffAsModBusCmd( cmdToSend->cmd ) );
      }
   }

   return enviou;
}


void TModBusSocketThread::TimedOut()  // CONFERIDO, SEM MEM. LEAKS
{
   // Função que faz algo se der TimeOut
}


void TModBusSocketThread::ProcessaRespostasComandos()
{
   // Processa a lista de respostas recebidas VS comandos já enviados
   
   if ( debugLog )
   {
      debugLog->Add( "Processa Respostas:" );
      
      for ( int k = 0, qtd = cmdsEnviados.size(); k < qtd; k++ )
         debugLog->Add( cmdsEnviados[k]->PrintModBusCmd() );
      
      for ( int k = 0, qtd = buffersRecebidos.size(); k < qtd; k++ )
         debugLog->Add( PrintBuffAsModBusResp( buffersRecebidos[k] ) );
   }
   

   for ( int i = 0, respondido = 0; i < cmdsEnviados.size(); )
   {
      respondido = 0;

      TModBusCmd* cmd = cmdsEnviados[i];


      for ( int j = 0; ( ! respondido ) && ( j < buffersRecebidos.size() ); j++ )   // Procura pela lista de respostas, aquela deste comando
      {
         if ( cmd->ParseResponse( buffersRecebidos[j] ) )  // Se é uma resposta válida
         {
            // Pareada a resposta ao comando, armazena quaisquer valores recebidos nas áreas de memória correspondentes

            if ( cmd->fc == 0x01 )  // Armazena respostas a 'Read Coil Status'
               for ( int k = 0, qtd = cmd->b_returnVals.size(); k < qtd; k++ )
               {
                  M     [ cmd->end + k ] = cmd->b_returnVals[k];
                  M_init[ cmd->end + k ] = true;
               }

            if ( cmd->fc == 0x03 )  // Armazena respostas a 'Read Holding Registers'
               for ( int k = 0, qtd = cmd->i_returnVals.size(); k < qtd; k++ )
               {
                  MW     [ cmd->end + k ] = cmd->i_returnVals[k];
                  MW_init[ cmd->end + k ] = true;
               }



            if ( debugLog )
            {
               if ( cmd->b_returnVals.size() )
               {
                  AnsiString temp = "bools: ";

                  for ( int k = 0, qtd = cmd->b_returnVals.size(); k < qtd; k++ )
                     temp += AnsiString( IntToHex( (unsigned short int) cmd->b_returnVals[k], 2 ) ) + " ";

                  debugLog->Add( "\t\t--> " + temp );
               }

               else if ( cmd->i_returnVals.size() )
               {
                  AnsiString temp = "words: ";

                  for ( int k = 0, qtd = cmdsEnviados[i]->i_returnVals.size(); k < qtd; k++ )
                     temp += AnsiString( IntToHex( (unsigned short int) cmd->i_returnVals[k], 4 ) ) + " ";

                  debugLog->Add( "\t\t--> " + temp );
               }
            }


            delete *( cmdsEnviados    .begin() + i );
            delete *( buffersRecebidos.begin() + j );

            cmdsEnviados    .erase( cmdsEnviados    .begin() + i );
            buffersRecebidos.erase( buffersRecebidos.begin() + j );

            respondido = 1;
         }
      }

      i = ( ! respondido ) ? i + 1 : 0;  // Se não encontrou a resposta a esse comando, incrementa i e olha o próximo, senão zera
   }
   
   
   // E se tiver mais respostas que comandos???
   
   if ( debugLog )
      for ( int k = 0, qtd = buffersRecebidos.size(); k < qtd; k++ )
         debugLog->Add( PrintBuffAsModBusResp( buffersRecebidos[k] ) );
}


void TModBusSocketThread::RebuildComandosCiclicos()  // CONFERIDO, SEM MEM. LEAKS
{
   rebuildCiclicos = false;

   // Função que (re)constrói os comandos ModBus Cíclicos (Leituras)

   int
      endI     = -1,
      endF     = -1,
      qtdMaxM  = 2000,
      qtdMaxMW = 125;

   TModBusCmd
      *cmd = NULL;



   // Limpa a lista

   cmdsCiclicos.rewind();
   while ( cmdsCiclicos.size() )
   {
      delete cmdsCiclicos.peek();
      cmdsCiclicos.pop();
   }


   // Coils

   for ( int i = 0; i < 0x10000; i++ )
   {
      if ( M_read[i] )
      {
         if (     endI < 0       ) endI = i;
         if ( i - endI < qtdMaxM ) endF = i;
      }

      if ( ( endI > -1 ) &&
           ( ( i - endI >= qtdMaxM ) || ( i == 0xFFFF ) ) )
      {
         cmd = new TModBusCmd();
         cmd->fc01( endI, endF - endI + 1 );
         cmdsCiclicos.push( cmd );

         endI = -1;
      }
   }


   // Holding Registers

   endI = -1;

   for ( int i = 0; i < 0x10000; i++ )
   {
      if ( MW_read[i] )
      {
         if (     endI < 0        ) endI = i;
         if ( i - endI < qtdMaxMW ) endF = i;
      }

      if ( ( endI > -1 ) &&
           ( ( i - endI >= qtdMaxMW ) || ( i == 0xFFFF ) ) )
      {
         cmd = new TModBusCmd();
         cmd->fc03( endI, endF - endI + 1 );
         cmdsCiclicos.push( cmd );

         endI = -1;
      }
   }
}


void TModBusSocketThread::RebuildComandosSimples()  // CONFERIDO, SEM MEM. LEAKS
{
   cmdsSimples = NULL;  // Invalida o ponteiro para a lista de cmdsSimples enquanto a reconstrói


   if ( debugLog )
   {
      debugLog->Add( "Lista Original:" );
      for ( int i = 0, qtd = cmdsSimplesRebuilding->size(); i < qtd; i++ )
         debugLog->Add( cmdsSimplesRebuilding->at(i)->PrintModBusCmd() );
      debugLog->Add( "" );
   }


   OrdenaComandosSimplesASC();  // Garante uma lista ordenada, antes de processar


   // Comandos de Mask Write Registers

   ReduzFC22();                 // Reduz comandos de Mask Write entre si e possivelmente a um Preset Single Register


   if ( debugLog )
   {
      debugLog->Add( "Depois de 'ReduzFC22':" );
      for ( int i = 0, qtd = cmdsSimplesRebuilding->size(); i < qtd; i++ )
         debugLog->Add( cmdsSimplesRebuilding->at(i)->PrintModBusCmd() );
      debugLog->Add( "" );
   }


   // Comandos de Preset Single Register

   ReduzFC06();


   if ( debugLog )
   {
      debugLog->Add( "Depois de 'ReduzFC06':" );
      for ( int i = 0, qtd = cmdsSimplesRebuilding->size(); i < qtd; i++ )
         debugLog->Add( cmdsSimplesRebuilding->at(i)->PrintModBusCmd() );
      debugLog->Add( "" );
   }


   OrdenaComandosSimplesASC();


   // Comandos de Preset Multiple Registers

   ReduzFC16();


   if ( debugLog )
   {
      debugLog->Add( "Depois de 'ReduzFC16':" );
      for ( int i = 0, qtd = cmdsSimplesRebuilding->size(); i < qtd; i++ )
         debugLog->Add( cmdsSimplesRebuilding->at(i)->PrintModBusCmd() );
      debugLog->Add( "" );
   }

   
   // Comandos de Preset Single Register

   ReduzFC05();


   if ( debugLog )
   {
      debugLog->Add( "Depois de 'ReduzFC05':" );
      for ( int i = 0, qtd = cmdsSimplesRebuilding->size(); i < qtd; i++ )
         debugLog->Add( cmdsSimplesRebuilding->at(i)->PrintModBusCmd() );
      debugLog->Add( "" );
   }
   
   
   // Comandos de Preset Single Register

   ReduzFC15();


   if ( debugLog )
   {
      debugLog->Add( "Depois de 'ReduzFC15':" );
      for ( int i = 0, qtd = cmdsSimplesRebuilding->size(); i < qtd; i++ )
         debugLog->Add( cmdsSimplesRebuilding->at(i)->PrintModBusCmd() );
      debugLog->Add( "" );
   }
   

   cmdsSimples = cmdsSimplesRebuilding;  // Devolve a referência ao ponteiro da lista
}


void TModBusSocketThread::OrdenaComandosSimplesASC()  // CONFERIDO, SEM MEM. LEAKS
{
   // Bubble Sort Otimizado (Estável!)

   int n = cmdsSimplesRebuilding->size();

   do
   {
      int novo = 0;

      for ( int i = 1; i < n; i ++ )
      {
         TModBusCmd
            *cmd1 = cmdsSimplesRebuilding->at(i-1),
            *cmd2 = cmdsSimplesRebuilding->at(i);

         if (   ( cmd1->fc  >  cmd2->fc  ) ||
              ( ( cmd1->fc  == cmd2->fc  ) &&
                ( cmd1->end >  cmd2->end ) ) )
         {
            cmdsSimplesRebuilding->erase ( cmdsSimplesRebuilding->begin() + i );
            cmdsSimplesRebuilding->insert( cmdsSimplesRebuilding->begin() + i - 1, cmd2 );
            novo = i;
         }
      }

      n = novo;
   }
   while (n);
}



void TModBusSocketThread::ReduzFC22()  // CONFERIDO, SEM MEM. LEAKS
{
   bool combinou;

   TModBusCmd
      *cmd1 = NULL,
      *cmd2 = NULL;


   do
   {
      combinou = false;

      for ( int i = 0; i < cmdsSimplesRebuilding->size(); i++ )  // Varre a lista removendo comandos repetidos
      {
         cmd1 = cmdsSimplesRebuilding->at(i);
         cmd2 = NULL;

         if ( i + 1 < cmdsSimplesRebuilding->size() )  // Tenta pegar dois comandos da lista, cuidado com out-of-bounds
            cmd2 = cmdsSimplesRebuilding->at( i + 1 );


         if ( cmd1->fc == 22 )
         {
            if (   cmd2 &&
                 ( cmd2->fc  == cmdsSimplesRebuilding->at(i)->fc ) &&   // Testa se são comandos que
                 ( cmd2->end == cmdsSimplesRebuilding->at(i)->end ) )   // alteram um mesmo endereço
            {
               CombinaComandosFC22( cmd1, cmd2 );  // Se forem, os combina
               combinou = true;

               delete cmd2;                                       // Libera memória do cmd2
               cmdsSimplesRebuilding->erase( cmdsSimplesRebuilding->begin() + i + 1 );  // Remove o cmd2 da lista

               i--;  // Garante que vai reavaliar o comando atual
            }
            else
               TransformaFC22emFC16( cmdsSimplesRebuilding->at(i) );
         }
      }
   }
   while ( combinou );
}


void TModBusSocketThread::CombinaComandosFC22( TModBusCmd *cmd1, TModBusCmd *cmd2 )  // CONFERIDO, SEM MEM. LEAKS
{
   unsigned char
      slA = cmd1->slaveAddr;

   unsigned short int
      end1 = cmd1->end,
      and1 = readMemAs <unsigned short int> ( & cmd1->cmd->buf[10] ),
      and2 = readMemAs <unsigned short int> ( & cmd2->cmd->buf[10] ),
      and_,
       or1 = readMemAs <unsigned short int> ( & cmd1->cmd->buf[12] ),
       or2 = readMemAs <unsigned short int> ( & cmd2->cmd->buf[12] ),
       or_ = 0;


   and_ = and1 & and2;
    or_ = ( ( ~and1 ) & or1 ) | ( ( ~and2 ) & or2 );


   // Combina os dois comandos em um só

   writeToMemAddr( & cmd1->cmd->buf[10], and_ );
   writeToMemAddr( & cmd1->cmd->buf[12], or_ );
}


bool TModBusSocketThread::TransformaFC22emFC16( TModBusCmd *cmd1 )  // CONFERIDO, SEM MEM. LEAKS
{
   bool transformou = false;

   unsigned char
      slA = cmd1->slaveAddr;

   short int
      end1 = cmd1->end,
      and1 = readMemAs <short int> ( & cmd1->cmd->buf[10] ),
       or1 = readMemAs <short int> ( & cmd1->cmd->buf[12] ),
      val1 = toggleEndianess(or1);


   // Se todos os bits da word estiverem sendo escritos em Mask Write (_and == 0) esse comando equivale
   // a escrever o Holding Register desse mesmo endereço com o conteúdo de OR. Fazendo isso, essa operação
   // poderá ser otimizada mais tarde, escrevendo em lote com outros endereços.

   if ( ! and1 )
   {
      cmd1->Clear();
      cmd1->fc16( end1, 1, & val1, slA );
      transformou = true;
   }


   return transformou;
}


void TModBusSocketThread::ReduzFC06()  // CONFERIDO, SEM MEM. LEAKS
{
   for ( int i = 0, t = cmdsSimplesRebuilding->size(); i < t; i++ )
      if ( cmdsSimplesRebuilding->at(i)->fc  == 06 )
         TransformaFC06emFC16( cmdsSimplesRebuilding->at(i) );
}


void TModBusSocketThread::TransformaFC06emFC16( TModBusCmd *cmd1 )  // CONFERIDO, SEM MEM. LEAKS
{
   unsigned char
      slA = cmd1->slaveAddr;

   short int
      end = cmd1->end,
      val = readMemAs <short int> ( & cmd1->cmd->buf[10] );


   cmd1->Clear();
   cmd1->fc16( end, 1, & val, slA );
}


void TModBusSocketThread::ReduzFC16()  // CONFERIDO, SEM MEM. LEAKS
{
   bool combinou;

   TModBusCmd
      *cmd1 = NULL,
      *cmd2 = NULL;


   do
   {
      combinou = false;

      for ( int i = 0; i < cmdsSimplesRebuilding->size(); i++ )  // Varre a lista removendo comandos repetidos
      {
         cmd1 = cmdsSimplesRebuilding->at(i);
         cmd2 = NULL;

         if ( i + 1 < cmdsSimplesRebuilding->size() )  // Tenta pegar dois comandos da lista, cuidado com out-of-bounds
            cmd2 = cmdsSimplesRebuilding->at( i + 1 );


         if (   cmd1 &&      cmd2 &&                    // Enquanto conseguir pegar dois comandos consecutivos
              ( cmd1->fc  == 16 ) &&                    //
              ( cmd1->fc  == cmd2->fc ) &&              // e ambos tiverem fc 06
              ( combinou  =  CombinaComandosFC16( cmd1, cmd2 ) ) )   // Se conseguir combinar os comandos
         {
            cmdsSimplesRebuilding->erase( cmdsSimplesRebuilding->begin() + i + 1 );  // Remove o cmd2, sempre combina sobre o ponteiro do cmd1
            i--;                                                                     // Garante que vai reavaliar o comando atual
         }
      }
   }
   while ( combinou );
}


bool TModBusSocketThread::CombinaComandosFC16( TModBusCmd *cmd1, TModBusCmd *cmd2 )  // CONFERIDO, SEM MEM. LEAKS
{
   bool
      combinou = false;

   short int
      end,
      qtd1 = 0,
      qtd2 = 0,
     *valores1,
     *valores2;

   TModBusCmd
     *cmdA = NULL,
     *cmdB = NULL;


   if ( ( cmd1->qtd <= 125 ) && ( cmd2->qtd <= 125 ) )
   {
           if ( cmd2->end == cmd1->end + cmd1->qtd )  // 2 começa onde 1 termina
      {
         cmdA = cmd1;
         cmdB = cmd2;
      }

      else if ( cmd1->end == cmd2->end + cmd2->qtd )  // 1 começa onde 2 termina
      {
         cmdA = cmd2;
         cmdB = cmd1;
      }


      if ( cmdA && cmdB )
      {
         end  = cmdA->end;
         qtd1 = cmdA->qtd + cmdB->qtd;

         if ( qtd1 > 125 )
         {
            qtd2 = qtd1 - 125;
            qtd1 = 125;
         }


         valores1 = new short int [ qtd1 ];

         for ( int i = 0; i < cmdA->qtd; i++ )
            valores1[i] = readMemAs <short int> ( & cmdA->cmd->buf[13 + i*2] );

         for ( int i = cmdA->qtd, j = 0; i < qtd1; i++, j++ )
            valores1[i] = readMemAs <short int> ( & cmdB->cmd->buf[13 + j*2] );


         cmdA->Clear();
         cmdA->fc16( end, qtd1, valores1 );
         
         delete[] valores1;


         if ( qtd2 )
         {
            valores2 = new short int [ qtd2 ];

            for ( int i = 0, j = qtd1 - cmdA->qtd; i < qtd2; i++, j++ )
               valores2[i] = readMemAs <short int> ( & cmdB->cmd->buf[13 + j*2] );


            cmdB->Clear();
            cmdB->fc16( end + qtd1, qtd2, valores2 );
            
            delete[] valores2;
         }
         
         else
         {
            delete cmdB;
            combinou = true;
         }
      }
   }

   return combinou;
}


void TModBusSocketThread::ReduzFC05()  // CONFERIDO, SEM MEM. LEAKS
{
   for ( int i = 0, t = cmdsSimplesRebuilding->size(); i < t; i++ )
      if ( cmdsSimplesRebuilding->at(i)->fc  == 05 )
         TransformaFC05emFC15( cmdsSimplesRebuilding->at(i) );
}


void TModBusSocketThread::TransformaFC05emFC15( TModBusCmd *cmd1 )  // CONFERIDO, SEM MEM. LEAKS
{
   unsigned char
      slA = cmd1->slaveAddr;

   short int
      end = cmd1->end;
      
   bool
      val = readMemAs <short int> ( & cmd1->cmd->buf[10] );


   cmd1->Clear();
   cmd1->fc15( end, 1, & val, slA );
}


void TModBusSocketThread::ReduzFC15()  // CONFERIDO, SEM MEM. LEAKS
{
   bool combinou;

   TModBusCmd
      *cmd1 = NULL,
      *cmd2 = NULL;


   do
   {
      combinou = false;

      for ( int i = 0; i < cmdsSimplesRebuilding->size(); i++ )  // Varre a lista removendo comandos repetidos
      {
         cmd1 = cmdsSimplesRebuilding->at(i);
         cmd2 = NULL;

         if ( i + 1 < cmdsSimplesRebuilding->size() )  // Tenta pegar dois comandos da lista, cuidado com out-of-bounds
            cmd2 = cmdsSimplesRebuilding->at( i + 1 );


         if (   cmd1 &&      cmd2 &&                    // Enquanto conseguir pegar dois comandos consecutivos
              ( cmd1->fc  == 15 ) &&                    //
              ( cmd1->fc  == cmd2->fc ) &&              // e ambos tiverem fc 06
              ( combinou  =  CombinaComandosFC15( cmd1, cmd2 ) ) )   // Se conseguir combinar os comandos
         {
            cmdsSimplesRebuilding->erase( cmdsSimplesRebuilding->begin() + i + 1 );  // Remove o cmd2, sempre combina sobre o ponteiro do cmd1
            i--;                                                                     // Garante que vai reavaliar o comando atual
         }
      }
   }
   while ( combinou );
}


bool TModBusSocketThread::CombinaComandosFC15( TModBusCmd *cmd1, TModBusCmd *cmd2 )  // CONFERIDO, SEM MEM. LEAKS
{
   bool
      combinou = false,
     *valores1,
     *valores2;

   short int
      end,
      qtd1 = 0,
      qtd2 = 0;

   TModBusCmd
     *cmdA = NULL,
     *cmdB = NULL;


   if ( ( cmd1->qtd <= 2000 ) && ( cmd2->qtd <= 2000 ) )
   {
           if ( cmd2->end == cmd1->end + cmd1->qtd )  // 2 começa onde 1 termina
      {
         cmdA = cmd1;
         cmdB = cmd2;
      }

      else if ( cmd1->end == cmd2->end + cmd2->qtd )  // 1 começa onde 2 termina
      {
         cmdA = cmd2;
         cmdB = cmd1;
      }


      if ( cmdA && cmdB )  // Se cair em uma das situações acima
      {
         end  = cmdA->end;
         qtd1 = cmdA->qtd + cmdB->qtd;

         if ( qtd1 > 2000 )
         {
            qtd2 = qtd1 - 2000;
            qtd1 = 2000;
         }


         valores1 = new bool [ qtd1 ];

         for ( int i = 0; i < cmdA->qtd; i++ )
            valores1[i] = GET_BIT( cmdA->cmd->buf[ 13 + i / 8 ], i % 8 );

         for ( int i = cmdA->qtd, j = 0; i < qtd1; i++, j++ )
            valores1[i] = GET_BIT( cmdA->cmd->buf[ 13 + j / 8 ], j % 8 );


         cmdA->Clear();
         cmdA->fc15( end, qtd1, valores1 );
         
         delete[] valores1;


         if ( qtd2 )
         {
            valores2 = new bool [ qtd2 ];

            for ( int i = 0, j = qtd1 - cmdA->qtd; i < qtd2; i++, j++ )
               valores2[i] = GET_BIT( cmdB->cmd->buf[ 13 + j / 8 ], j % 8 );


            cmdB->Clear();
            cmdB->fc15( end + qtd1, qtd2, valores2 );
            
            delete[] valores2;
         }
         
         else
         {
            delete cmdB;
            combinou = true;
         }
      }
   }

   return combinou;
}


/*
void TModBusSocketThread::OrdenaComandosSimplesDESC()
{
   // Bubble Sort Otimizado (Estável!)

   int n = cmdsSimplesRebuilding->size();

   do
   {
      int novo = 0;

      for ( int i = 1; i < n; i ++ )
      {
         TModBusCmd
            *cmd1 = cmdsSimplesRebuilding[i-1],
            *cmd2 = cmdsSimplesRebuilding->at(i);

         if (   ( cmd1->fc  <  cmd2->fc  ) ||
              ( ( cmd1->fc  == cmd2->fc  ) &&
                ( cmd1->end <  cmd2->end ) ) )
         {
            cmdsSimplesRebuilding->erase ( cmdsSimplesRebuilding->begin() + i );
            cmdsSimplesRebuilding->insert( cmdsSimplesRebuilding->begin() + i - 1, cmd2 );
            novo = i;
         }
      }

      n = novo;
   }
   while (n);
}


bool TModBusSocketThread::ReduzFC01() {}
bool TModBusSocketThread::ReduzFC03() {}
bool TModBusSocketThread::ReduzFC05() {}


bool TModBusSocketThread::ExpandeFC15()  // Force Multiple Coils
{
   TModBusCmd
      *cmd1  = NULL,
      *novo  = NULL;


   for ( int i = 0; i < cmdsSimplesRebuilding->size(); i++ )
   {
      cmd1 = cmdsSimplesRebuilding->at(i);


      if (   cmd1 &&
           ( cmd1->fc == 15 ) )
      {
         unsigned char
            slA = cmd1->slaveAddr;

         short int
            end = cmd1->end,
            qtd = cmd1->qtd;


         for ( int j = 0; j < qtd; j++ )
         {
            novo = new TModBusCmd();
            novo->fc05( end + j, GET_BIT( cmd1->cmd->buf[ 13 + j / 8 ], j % 8 ), slA );

            if ( i + 1 + j >= cmdsSimplesRebuilding->size() )  // Lida com inserção no fim da lista
               cmdsSimplesRebuilding->push_back( novo );
            else
               cmdsSimplesRebuilding->insert( cmdsSimplesRebuilding->begin() + i + 1 + j, novo );
         }

         delete cmd1;
         cmdsSimplesRebuilding->erase( cmdsSimplesRebuilding->begin() + i );
         i--;
      }
   }
}


void TModBusSocketThread::ExpandeFC16()  // Preset Multiple Registers
{
   TModBusCmd
      *cmd1 = NULL,
      *novo = NULL;



   for ( int i = 0; i < cmdsSimplesRebuilding->size(); i++ )
   {
      cmd1 = cmdsSimplesRebuilding->at(i);

      if (   cmd1 &&
           ( cmd1->fc == 16 ) )
      {
         unsigned char
            slA = cmd1->slaveAddr;

         short int
            end = cmd1->end,
            qtd = cmd1->qtd;


         for ( int j = 0; j < qtd; j++ )
         {
            novo = new TModBusCmd();
            novo->fc06( end + j, toggleEndianess( readMemAs <short int> ( & cmd1->cmd->buf[13 + j*2] ) ), slA );

            if ( i + 1 + j >= cmdsSimplesRebuilding->size() )
               cmdsSimplesRebuilding->push_back( novo );
            else
               cmdsSimplesRebuilding->insert( cmdsSimplesRebuilding->begin() + i + 1 + j, novo );
         }

         delete cmd1;
         cmdsSimplesRebuilding->erase( cmdsSimplesRebuilding->begin() + i );
         i--;
      }
   }
}
*/

#endif
