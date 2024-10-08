
/*
 *  CLASSE DRIVER MODBUS TCP - TModBusTCPDriver.
 *
 *  - Implementa um driver simples para comunica��o ModBus TCP.
 *
 *  Features:
 *
 *  > Quantidade de Conex�es Configur�vel
 *  > Processamento em Threads
 *
 *
 *
 */


#ifndef __TMODBUSDRIVER_CPP
#define __TMODBUSDRIVER_CPP


#define __TMODBUSDRIVER_VERSAO "1.0"


#ifndef ScktCompHPP
#include <ScktComp.hpp>
#endif



#ifndef __VECTOR_H
#include <vector.h>
#endif

#ifndef __QUEUE_H
#include <queue.h>
#endif

#ifndef __UTIL_CPP
#include "util.cpp"
#endif


#ifndef __TMODBUSCMD_CPP
#include "TModBusCmd.cpp"
#endif

#ifndef __TMODBUSSOCKETTHREAD_CPP
#include "TModBusSocketThread.cpp"
#endif



#define  __IEC0 0
#define  __IEC1 1

#define  QUANTUM  __IEC1
#define  PREMIUM  __IEC0


class TModBusTCPDriver
{
public:

    TModBusTCPDriver( TComponent* AOwner, AnsiString ip, int SlaveSyntax );
   ~TModBusTCPDriver();


   void Open();
   void Open( AnsiString ip );

   void Close();

   bool Conectado();



   int TamBufRD();
   int TamBufWR();

   float RD( AnsiString var );
   float WR( AnsiString var, float val );


//private:

// ----- M�todos -----


   void __fastcall ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket );
   void __fastcall ClientSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket );
   void __fastcall ClientSocketError( TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int &ErrorCode );

   bool ProduzCmdSimplesThread( TModBusCmd *cmd );

   bool ParseEnd( char* s_end, int *areaMem, int *end, int *bit );


// ----- Vari�veis -----


// VARI�VEIS PARA CONEX�O DE REDE

   AnsiString
      _ip;

   int
      _port,
      _slaveSyntax;

   TComponent*
      _owner;

   TClientSocket*
      _socket;


// THREAD DE GERENCIAMENTO DA CONEX�O DE REDE

   TModBusSocketThread
      *_thread;


// VARI�VEIS RELATIVAS � �REA DE MEM�RIA MODBUS INTERNA

   bool
     *_M,       // Regi�o de COILS
     *_M_init,  // Flags de endere�os inicializados
     *_M_read,  // Flags de necessidade de leitura dos endere�os
     *_MW_init, // Flags de endere�os inicializados
     *_MW_read, // Flags de necessidade de leitura dos endere�os
     conectado;

   short int
     *_MW;      // Regi�o de HOLDING REGISTERS


// LISTA DE TROCA DE COMANDOS COM A THREAD

   TModBusCmd
     **_threadInputCmds;  // Vetor de Ponteiros de "TModBusCmd" a serem trocados com a Thread
};



TModBusTCPDriver::TModBusTCPDriver( TComponent* AOwner, AnsiString ip = "127.0.0.1", int SlaveSyntax = __IEC0 )  // CONFERIDO, SEM MEM. LEAKS
{
   _ip          = ip;
   _port        = 502;
   _owner       = AOwner;
   _slaveSyntax = SlaveSyntax;


   // Instancia o socket

   _socket = new TClientSocket( _owner );

   _socket->Active     = false;
   _socket->Address    = _ip;
   _socket->Port       = _port;
   _socket->ClientType = ctNonBlocking;

   _socket->OnConnect    = ClientSocketConnect;
   _socket->OnDisconnect = ClientSocketDisconnect;
   _socket->OnError      = ClientSocketError;

   conectado = false;


   // Inicializa os vetores de mem�ria interna

   _M       = new      bool [0x10000];  // Aloca a tabela de valores %M  ( Coils )
   _M_init  = new      bool [0x10000];  // Aloca a tabela de flags de inicializa��o de %M  ( Coils )
   _M_read  = new      bool [0x10000];  // Aloca a tabela de necessidade de leitura de %M  ( Coils )
   _MW_init = new      bool [0x10000];  // Aloca a tabela de flags de inicializa��o de %MW ( Holding Registers )
   _MW_read = new      bool [0x10000];  // Aloca a tabela de necessidade de leitura de %MW ( Holding Registers )
   _MW      = new short int [0x10000];  // Aloca a tabela de valores %MW ( Holding Registers )

   _threadInputCmds = new TModBusCmd* [0x10000];  // Aloca a tabela de Ponteiros de "TModBusCmd" a serem trocados com a Thread

   for ( int i = 0; i < 0x10000; i++ )  // Inicializa as tabelas em false
   {
      _M      [i] = false;
      _M_init [i] = false;
      _M_read [i] = false;
      _MW_init[i] = false;
      _MW_read[i] = false;
      _MW     [i] = 0;

      _threadInputCmds[i] = NULL;
   }


   // Instancia a Thread

   _thread = new TModBusSocketThread( true );  // Cria a thread suspensa
   _thread->SetClientSocket( _socket );        // Passa o socket para a thread

   _thread->M       = _M;                      //                      |
   _thread->M_init  = _M_init;                 //                      |
   _thread->M_read  = _M_read;                 // Passa � thread as �reas de mem�ria necess�rias
   _thread->MW      = _MW;                     //                      |
   _thread->MW_init = _MW_init;                //                      |
   _thread->MW_read = _MW_read;                //                      |

   _thread->inputCmds = _threadInputCmds;      // Compartilha com a Thread a lista de troca de comandos

//   _thread->Resume();                          // Roda a thread
}


TModBusTCPDriver::~TModBusTCPDriver()  // CONFERIDO, SEM MEM. LEAKS
{
   if ( _thread  )  _thread->Suspend();

   if ( _socket  )  delete _socket;
   if ( _thread  )  delete _thread;

   if ( _M       )  delete[] _M;
   if ( _M_init  )  delete[] _M_init;
   if ( _M_read  )  delete[] _M_read;
   if ( _MW      )  delete[] _MW;
   if ( _MW_init )  delete[] _MW_init;
   if ( _MW_read )  delete[] _MW_read;

   if ( _threadInputCmds )  delete[] _threadInputCmds;
}


void TModBusTCPDriver::Open()  // CONFERIDO, SEM MEM. LEAKS
{
   if ( _thread->Suspended )  // Continua a thread se ela estiver Suspensa quando tentar 'Open'
      _thread->Resume();


   if ( ! _socket->Active )
   {
      _thread->rebuildCiclicos = true;
      _socket->Open();
   }
}


void TModBusTCPDriver::Open( AnsiString ip )  // CONFERIDO, SEM MEM. LEAKS
{
   if ( ! _socket->Active )
   {
      _thread->rebuildCiclicos = true;

      _ip = ip;
      _socket->Address = _ip;
      _socket->Open();
   }
}


void TModBusTCPDriver::Close()  // CONFERIDO, SEM MEM. LEAKS
{
   if ( _socket->Active )
      _socket->Close();
}


void __fastcall TModBusTCPDriver::ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket )  // CONFERIDO, SEM MEM. LEAKS
{
   conectado = true;
}


void __fastcall TModBusTCPDriver::ClientSocketDisconnect( TObject *Sender, TCustomWinSocket *Socket )  // CONFERIDO, SEM MEM. LEAKS
{
   conectado = false;
}


void __fastcall TModBusTCPDriver::ClientSocketError( TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int &ErrorCode )  // CONFERIDO, SEM MEM. LEAKS
{/*
   AnsiString erro;

        if ( ErrorCode == 10048 ) erro = "\"Address already in use\"";
   else if ( ErrorCode == 10049 ) erro = "\"Cannot assign requested address\"";
   else if ( ErrorCode == 10050 ) erro = "\"Network is down\"";
   else if ( ErrorCode == 10051 ) erro = "\"Network is unreachable\"";
   else if ( ErrorCode == 10052 ) erro = "\"Network dropped connection on reset\"";
   else if ( ErrorCode == 10053 ) erro = "\"Software caused connection abort\"";
   else if ( ErrorCode == 10054 ) erro = "\"Connection reset by peer\"";
   else if ( ErrorCode == 10055 ) erro = "\"No buffer space available\"";
   else if ( ErrorCode == 10057 ) erro = "\"Socket is not connected\"";
   else if ( ErrorCode == 10058 ) erro = "\"Cannot send after socket shutdown\"";
   else if ( ErrorCode == 10060 ) erro = "\"Connection timed out\"";
   else if ( ErrorCode == 10061 ) erro = "\"Connection refused\"";
   else if ( ErrorCode == 10064 ) erro = "\"Host is down\"";
   else if ( ErrorCode == 10065 ) erro = "\"No route to host\"";
*/
   ErrorCode = 0;

   conectado = false;

   ( (TClientSocket*) Sender )->Active = false;
//   ( (TClientSocket*) Sender )->Open();
}


bool TModBusTCPDriver::Conectado()  // CONFERIDO, SEM MEM. LEAKS
{
   return conectado;
}


int TModBusTCPDriver::TamBufRD()  // CONFERIDO, SEM MEM. LEAKS
{
   return _thread->GetTamCmdsCiclicos();
}


int TModBusTCPDriver::TamBufWR()  // CONFERIDO, SEM MEM. LEAKS
{
   return _thread->GetTamCmdsSimples();
}


float TModBusTCPDriver::RD( AnsiString var )  // CONFERIDO, SEM MEM. LEAKS
{
   int
      areaMem =  0,
      end     =  0,
      bit     = -1;

   float retorno = 0.0;


   if ( _thread->Suspended )  // Continua a thread se ela estiver Suspensa quando tentar 'RD'
      _thread->Resume();



   if ( ! ParseEnd( var.c_str(), & areaMem, & end, & bit ) )  // Valida o endere�o passado
      writeToMemAddr <int> ( & retorno, -1 );                 // Em caso de erro de parse, retorna um float malcriado (INF? NaN?)

   else  // Se for um endere�o v�lido
   {
      // Ajusta o offset do endere�o de acordo com a 'SlaveSyntax' declarada

      if ( end > 0 )
         end -= _slaveSyntax;


      // A forma de responder ir� variar se estiver conectado ou n�o

      if ( ! _socket->Active )  // N�o estando conectado - "ESSE IF" CONFERIDO, SEM MEM. LEAKS
      {
         // Se n�o estiver conectado no momento, devolve o que estiver escrito na mem�ria interna,
         // mas sinaliza a necessidade de leitura desse endere�o no futuro.

         if ( areaMem == 1 )
         {
            retorno = (int) _M[ end ];

            _M_read[ end ] = true;   // Sinaliza que o endere�o est� sendo lido (Ajuda a otimizar os ranges de leitura)
            _M_init[ end ] = false;  // Marca a �rea de mem�ria como n�o-inicializada
         }

         else  // Passou pelo parser, se n�o � %M � %MW, %MD ou %MF
         {
            _MW_read[ end ] = true;   // Sinaliza que o endere�o est� sendo lido (Ajuda a otimizar os ranges de leitura)
            _MW_init[ end ] = false;  // Marca a �rea de mem�ria como n�o-inicializada


            if ( areaMem == 2 )
            {
               if ( bit < 0 )
                  retorno = readMemAs <short int> ( & _MW[ end ] );
               else
                  retorno = (int) GET_BIT ( readMemAs <short int> ( & _MW[ end ] ), bit );
            }

            else  // Chegou at� aqui, � %MD ou %MF
            {
               _MW_read[ end +1 ] = true;   // %MD e %MF usam 2 words de dados, marca que a segunda deve ser lida tamb�m
               _MW_init[ end +1 ] = false;  //   "    "     "     "     "    "    "     "     "     "    "    "     "


               if ( areaMem == 3 )
               {
                  if ( bit < 0 )
                     retorno = readMemAs <int> ( & _MW[ end ] );
                  else
                     retorno = (int) GET_BIT ( readMemAs <int> ( & _MW[ end ] ), bit );
               }
               else
                  retorno = readMemAs <float> ( & _MW[ end ] );
            }
         }
      }

      else  // Estando conectado
      {
         // Se estiver conectado no momento, s� devolve o que estiver escrito na mem�ria interna
         // se o endere�o j� foi inicializado (j� foi lido uma vez), sen�o dispara um comando de leitura
         // como comando simples e espera at� ele ser lido pela thread.
         // Tamb�m sinaliza a necessidade de leitura desse endere�o.

         TModBusCmd*
            cmdRDSimples;  // Novo cmd ModBus para a leitura desse endere�o v�lido que passou pelo parser


         if ( areaMem == 1 )
         {
            _M_read[ end ] = true;  // Marca que o endere�o deve ser lido

            if ( ! _M_init[ end ] )  // Se a mem�ria ainda n�o foi inicializada.
            {
               cmdRDSimples = new TModBusCmd();  // Aloca o cmd
               cmdRDSimples->fc01( end, 1 );     // Comando de Leitura de Coil

               _thread->rebuildCiclicos = true;
               _thread->CmdSimplesPushFront( cmdRDSimples );  // Insere esse comando na frente da lista de comandos simples da thread. (Garante execu��o mais r�pida poss�vel)

               while ( cmdRDSimples && ( ! _M_init[ end ] ) );   // Espera aqui at� a thread ler o endere�o da rede. S� espera se conseguiu criar o comando.
            }

            retorno = (int) _M[ end ];
         }

         else // Passou pelo parser, se n�o � %M � %MW, %MD ou %MF
         {
            _MW_read[ end ] = true;  // Marca que o endere�o deve ser lido

            if ( areaMem == 2 )
            {
               if ( ! _MW_init[ end ] )  // Se a mem�ria ainda n�o foi inicializada.
               {
                  cmdRDSimples = new TModBusCmd();  // Aloca o cmd
                  cmdRDSimples->fc03( end, 1 );  // Comando de Leitura de Holding Register, 1 word

                  _thread->rebuildCiclicos = true;
                  _thread->CmdSimplesPushFront( cmdRDSimples );  // Insere esse comando na frente da lista de comandos simples da thread. (Garante execu��o mais r�pida poss�vel)

                  while ( cmdRDSimples && ( ! _MW_init[ end ] ) );   // Espera aqui at� a thread ler o endere�o da rede. S� espera se conseguiu criar o comando.
               }

               if ( bit < 0 )
                  retorno = readMemAs <short int> ( & _MW[ end ] );
               else
                  retorno = (int) GET_BIT ( readMemAs <short int> ( & _MW[ end ] ), bit );
            }

            else  // Chegou at� aqui, � %MD ou %MF
            {
               _MW_read[ end +1 ] = true;  // %MD e %MF usam 2 words de dados, marca que a segunda deve ser lida tamb�m

               if ( ! ( _MW_init[ end ] || _MW_init[ end +1 ] ) )  // Se a mem�ria ainda n�o foi inicializada.
               {
                  cmdRDSimples = new TModBusCmd();  // Aloca o cmd
                  cmdRDSimples->fc03( end, 2 );  // Comando de Leitura de Holding Register, 2 words

                  _thread->rebuildCiclicos = true;
                  _thread->CmdSimplesPushFront( cmdRDSimples );  // Insere esse comando na frente da lista de comandos simples da thread. (Garante execu��o mais r�pida poss�vel)

                  while ( cmdRDSimples && ( ! ( _MW_init[ end ] || _MW_init[ end +1 ] ) ) );  // Espera aqui at� a thread ler o endere�o da rede. S� espera se conseguiu criar o comando.
               }

               if ( areaMem == 3 )
               {
                  if ( bit < 0 )
                     retorno = readMemAs <int> ( & _MW[ end ] );
                  else
                     retorno = (int) GET_BIT ( readMemAs <int> ( & _MW[ end ] ), bit );
               }
               else
                  retorno = readMemAs <float> ( & _MW[ end ] );
            }
         }
      }
   }

   return retorno;
}


bool TModBusTCPDriver::ProduzCmdSimplesThread( TModBusCmd *cmd )  // CONFERIDO, SEM MEM. LEAKS
{
   bool inseriu = false;

   for ( int i = 0; ( ! inseriu ) && ( i < 0x10000 ); i++ )
      if ( _threadInputCmds[i] == NULL )
      {
         _threadInputCmds[i] = cmd;
         inseriu = true;
      }

   return inseriu;
}


float TModBusTCPDriver::WR( AnsiString var, float val )
{
   int
      areaMem =  0,
      end     =  0,
      bit     = -1;

   float retorno = 0.0;


   if ( _thread->Suspended )  // Continua a thread se ela estiver Suspensa quando tentar 'WR'
      _thread->Resume();



   if ( ! ParseEnd( var.c_str(), & areaMem, & end, & bit ) )  // Valida o endere�o passado
      writeToMemAddr <int> ( & retorno, -1 );                 // Em caso de erro de parse, retorna um float malcriado (INF? NaN?)

   else  // Se for um endere�o v�lido
   {
      // Ajusta o offset do endere�o de acordo com a 'SlaveSyntax' declarada

      if ( end > 0 )
         end -= _slaveSyntax;


      // Independentemente de estar conectado ou n�o, gera comandos que eventualmente ser�o consumidos pela thread

      TModBusCmd*
         cmdWRSimples;  // Novo cmd ModBus para a leitura desse endere�o v�lido que passou pelo parser


      if ( areaMem == 1 )
      {
         cmdWRSimples = new TModBusCmd();      // Aloca o cmd
         cmdWRSimples->fc05( end, val != 0 );  // Monta o comando de escrita da Coil

         while ( ! ProduzCmdSimplesThread( cmdWRSimples ) );  // Insere esse comando na �rea de troca com a thread.
         retorno = val;
      }

      else  // Passou pelo parser, se n�o � %M � %MW, %MD ou %MF
      {
         if ( areaMem == 2 )
         {
            unsigned short int
               AND = ~( 1 << bit ),
               OR  = ( val ) ? ~0 : 0; //( 1 << bit );


            cmdWRSimples = new TModBusCmd();  // Aloca o cmd

            if ( bit > -1 )
               cmdWRSimples->fc22( end, AND, OR );  // Monta o comando de Mask Write Register
            else
               cmdWRSimples->fc06( end, (short int) val );  // Monta o comando de escrita do Register


            while ( ! ProduzCmdSimplesThread( cmdWRSimples ) );  // Insere esse comando na �rea de troca com a thread.
            retorno = val;
         }

         else  // Chegou at� aqui, � %MD ou %MF
         {
            cmdWRSimples = new TModBusCmd();  // Aloca o cmd
            
            if ( areaMem == 3 )
            {
               if ( bit > 15 )
               {
                  bit -= 16;
                  end++;
               }

               unsigned short int
                  AND = ~( 1 << bit ),
                  OR  = ( val ) ? ~0 : 0;//( 1 << bit );

               short int temp[2];

               if ( bit > -1 )
                  cmdWRSimples->fc22( end, AND, OR );  // Monta o comando de Mask Write Register
               else
                  cmdWRSimples->fc16( end, 2, (short int*) writeToMemAddr( & temp, toggleEndianess( (int) val ) ) );  // Monta o comando de escrita do Register
            }
            else
               cmdWRSimples->fc16( end, val );  // Monta o comando de escrita de Multiple Registers


            while ( ! ProduzCmdSimplesThread( cmdWRSimples ) );  // Insere esse comando na �rea de troca com a thread.
            retorno = val;
         }
      }
   }

   return retorno;
}


bool TModBusTCPDriver::ParseEnd( char *end_in, int *areaMem = NULL, int *end = NULL, int *bit = NULL )  // CONFERIDO, SEM MEM. LEAKS
{
   bool
      fail     = false,
      temPonto = false;

   int
      _areaMem = 0,
      _end     = 0,
      _bit     = 0;

   char
     *pt_end = NULL,
     *pt_bit = NULL;



   if ( *end_in == '%' )
      end_in++;


   if ( *end_in == 'M' )
      end_in++;
   else
      fail = true;


   if ( ! fail )
   {
      char* pt_end = end_in;

      if ( isdigit(*end_in) )  // Se o pr�ximo caracter for um n�mero, � um endere�o %M
      {
         _areaMem = 1;
         _end = atoi( pt_end );

         while ( ( *end_in != '\0' ) && isdigit(*end_in) )  // Enquanto estiver lendo um d�gito, incrementa
            end_in++;

         fail = ( *end_in != '\0' );  // Quando n�o for um d�gito se n�o for o terminador de string, falha
      }
      else
      {
              if ( *end_in == 'W' )  // Se o pr�ximo caracter for W, � um endere�o %MW
            _areaMem = 2;

         else if ( *end_in == 'D' )  // Se o pr�ximo caracter for W, � um endere�o %MD
            _areaMem = 3;

         else if ( *end_in == 'F' )  // Se o pr�ximo caracter for W, � um endere�o %MF
            _areaMem = 4;

         else
            fail = true;


         if ( ! fail )  // O endere�o est� declarado como '%MW', '%MD' ou '%MF'
         {
            pt_end = ++end_in;  // Armazena o ponteiro para o in�cio do endere�o


            // Verifica se o resto da string � composto s� de n�meros

            while ( ( *end_in != '\0' ) && isdigit(*end_in) )  // Enquanto estiver lendo um d�gito, incrementa
               end_in++;


            if ( *end_in == '.' )  // Quando n�o for um d�gito testa se � um ponto
            {
               temPonto = true;

               *end_in  = '\0';  // Substitui o ponto por um terminador de string para poder ler com o atoi.
               pt_bit   = ++end_in;


               while ( ( *end_in != '\0' ) && isdigit(*end_in) )  // Enquanto estiver lendo um d�gito, incrementa
                  end_in++;

               fail = ( *end_in != '\0' );  // Quando n�o for um d�gito se n�o for o terminador de string, falha
            }

            else if ( *end_in != '\0' )  // Se n�o for o terminador de string, falha
               fail = true;


            if ( ! fail )
            {
               if ( pt_end )
                  _end = atoi( pt_end );

               if ( pt_bit )
               {
                  _bit = atoi( pt_bit-- );
                  *pt_bit = '.';
               }
               else
                  bit = NULL;
            }
         }
      }


      // �ltima valida��o dos valores

      if ( (   _end < 0      ) ||  // Endere�o Inv�lido
           (   _end > 0xFFFF ) ||  //    "        "
           (   _bit < 0      ) ||  // Bit Inv�lido
           ( ( _bit > 15 ) && ( _areaMem == 2 ) ) ||  // Bit Inv�lido para endere�o '%MW'
           ( ( _bit > 31 ) && ( _areaMem == 3 ) ) )   // Bit Inv�lido para endere�o '%MD'
         fail = true;


      // Se o Parse foi v�lido, devolve os valores �s vari�veis passadas

      if ( ! fail )
      {
         if ( areaMem ) *areaMem = _areaMem;
         if ( end     ) *end     = _end;
         if ( bit     ) *bit     = _bit;
      }
   }


   return ! fail;
}


#endif
