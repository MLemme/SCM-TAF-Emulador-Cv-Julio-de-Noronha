
/*
 *  CLASSE DRIVER MODBUS TCP - TModBusTCPDriver.
 *
 *  - Implementa um driver simples para comunicação ModBus TCP.
 *
 *  Features:
 *
 *  > Quantidade de Conexões Configurável
 *  > Processamento em Threads
 *
 *
 *
 */


#ifndef __TMODBUSDRIVER_CPP
#define __TMODBUSDRIVER_CPP


#define __TMODBUSDRIVER_VERSAO "0.0"


#ifndef __VECTOR_H
#include <vector.h>
#endif


#ifndef __DEQUE_H
#include <deque.h>
#endif


#ifndef __MAP_H
#include <map.h>
#endif

/*
#ifndef __LIST_H
#include <list.h>
#endif
*/

#ifndef ScktCompHPP
#include <ScktComp.hpp>
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

#define  QUANTUM  __IEC0
#define  PREMIUM  __IEC1


class TModBusTCPDriver
{
public:

    TModBusTCPDriver( TComponent* AOwner, AnsiString ip, int SlaveSyntax, int numConexoes, int rate );
   ~TModBusTCPDriver();


   void Open();
   void Close();

   bool CadastraLeituraEnd( AnsiString end );
   void CriaListaCiclica();

   void  WR( AnsiString var, float val );
   float RD( AnsiString var, AnsiString tipo );


   int
      conectado;

//private:

   // Métodos

   void __fastcall TimerEvent( TObject *Sender );

   void __fastcall ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket );
   void __fastcall ClientSocketRead( TObject *Sender, TCustomWinSocket *Socket );
//   void __fastcall ClientSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket );
//   void __fastcall ClientSocketError( TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int &ErrorCode );

//   bool ParseEnd ( AnsiString s_end, AnsiString *areaMem, unsigned short int *end, unsigned short int *bit );


// ----- Variáveis -----

// [#] OBJETO DE CLOCK

   TTimer*
      _clock;


// [>] VARIÁVEIS DAS CONEXÕES DE REDE

   AnsiString
      _ip;

   TComponent*
      _Owner;

   vector< TClientSocket* >
      _vetorSocketsClientes;

   int
      _rate,         // Tempo em [ms] para o clock de envio dos comandos ciclicos
      _numConexoes,
      _SlaveSyntax;

// [<] VARIÁVEIS DAS CONEXÕES DE REDE


// [>] LISTAS INTERNAS DE ALOCAÇÃO DAS TABELAS MODBUS

   unsigned char
     *_M;

   short int
     *_MW;

// [>] LISTAS INTERNAS DE ALOCAÇÃO DAS TABELAS MODBUS


// [>] VARIÁVEIS DE ARMAZENAGEM E CONTROLE DE EXECUÇÃO DOS COMANDOS MODBUS

   deque <TModBusCmd*>
      _cmds_Ciclicos;

   int
      _idx_modBus_ciclico;


   map < unsigned short int, TModBusCmd* >
      _listaCmdMod_fc [ 24 ];


// [<] VARIÁVEIS DE ARMAZENAGEM E CONTROLE DE EXECUÇÃO DOS COMANDOS MODBUS


   TMemo*
      _debugMemo;
};



TModBusTCPDriver::TModBusTCPDriver( TComponent* AOwner, AnsiString ip, int SlaveSyntax = __IEC0, int numConexoes = 4, int rate = 50 )
{
   _debugMemo = NULL;


   _ip = ip;
   _numConexoes = ( numConexoes > 0 ) ? numConexoes : 1;
   _Owner = AOwner;
   _rate  = rate;
   _SlaveSyntax = SlaveSyntax;


   _M    = new unsigned char [ 0x10000 ];  // Aloca a tabela de %M ( Coils )
   _MW   = new short int     [ 0x10000 ];  // Aloca a tabela de %M ( Holding Registers )

   _idx_modBus_ciclico = 0;


   _clock = new TTimer ( _Owner );
   _clock->Enabled  = false;
   _clock->Interval = _rate;

   _clock->OnTimer = TimerEvent;
}


TModBusTCPDriver::~TModBusTCPDriver()
{
   delete[] _M;
   delete[] _MW;

                   // fcMax
   for ( int i = 0; i < 24; i++ )
      while ( _listaCmdMod_fc[i].size() )
      {
         delete _listaCmdMod_fc[i].end()->second;               // Apaga o CmdModbus alocado
         _listaCmdMod_fc[i].erase( _listaCmdMod_fc[i].end() );  // Remove a entrada no mapa
      }


   // _cmds_Ciclicos
   // Não deve-se tentar apagar as entradas dinâmicas em '_cmds_Ciclicos',
   // pois são as mesmas já apagadas acima.
}


void TModBusTCPDriver::Open()
{
   CriaListaCiclica();


   for ( int i = 0; i < _numConexoes; i++ )
   {
      TClientSocket*
         socket = new TClientSocket( _Owner );

      socket->Active     = false;
      socket->Address    = _ip;
      socket->Port       = 502;
      socket->Tag        = 0; //i;
      socket->ClientType = ctNonBlocking;

      socket->OnConnect  = ClientSocketConnect;
      socket->OnRead     = ClientSocketRead;
//      socket->OnError    = ClientSocketError;

      _vetorSocketsClientes.push_back( socket );
   }


   for ( int i = 0; i < _vetorSocketsClientes.size(); i++ )
      _vetorSocketsClientes[i]->Open();

   _clock->Enabled = true;
}


void TModBusTCPDriver::Close()
{
   _clock->Enabled = false;

   for ( int i = 0; i < _vetorSocketsClientes.size(); i++ )
      _vetorSocketsClientes[i]->Close();

   while ( _vetorSocketsClientes.size() )
      if ( ! _vetorSocketsClientes.back()->Active )
      {
         delete _vetorSocketsClientes.back();
         _vetorSocketsClientes.pop_back();
      }
}


void __fastcall TModBusTCPDriver::TimerEvent( TObject *Sender )
{
   static int qtd = ( _cmds_Ciclicos.size() < _vetorSocketsClientes.size() ) ? _cmds_Ciclicos.size() : _vetorSocketsClientes.size();

   for ( int i = 0; i < qtd; i++ )
   {
      _vetorSocketsClientes[i]->Socket->SendBuf( _cmds_Ciclicos[ _idx_modBus_ciclico ]->bufferCmd,
                                                 _cmds_Ciclicos[ _idx_modBus_ciclico ]->tam );

      if ( _debugMemo )
         _debugMemo->Lines->Add( _cmds_Ciclicos[ _idx_modBus_ciclico ]->PrintBufferCmd() );

      if ( ++_idx_modBus_ciclico >= _cmds_Ciclicos.size() )
         _idx_modBus_ciclico = 0;
   }
}


void __fastcall TModBusTCPDriver::ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket )
{
//
}


void __fastcall TModBusTCPDriver::ClientSocketRead( TObject *Sender, TCustomWinSocket *Socket )
{
   int tam, fc, end;

   unsigned char *buf = new unsigned char [ tam = Socket->ReceiveLength() ];

   Socket->ReceiveBuf( buf, tam );


   fc  = (int) ParseResponseGetfc( buf,tam );
   end = (int) ParseResponseGetEnd( buf,tam );

   if ( ( fc > 0 ) && ( end > 0 ) )
   {
      _listaCmdMod_fc[ fc ][ end ]->ParseResponseToCmd( buf,tam );

      if ( _debugMemo )
         _debugMemo->Lines->Add( _listaCmdMod_fc[ fc ][ end ]->PrintBufferResp() );
   }
}



bool ParseEnd ( AnsiString s_end, AnsiString *areaMem, unsigned short int *end, unsigned short int *bit )
{
   bool retorno = false;


   *bit = -1;

   if ( s_end.Pos( "." ) )  // Procura por bits
   {
      *bit  = s_end.SubString(    s_end.Pos( "." ) + 1, s_end.Length() ).ToInt();  // Armazena o bit
      s_end = s_end.SubString( 1, s_end.Pos( "." ) - 1 );                          // Tira o bit do endereço
   }


   if ( s_end.Pos( "%M" ) == 1 )  // Se for uma região de memória contemplada (%M_xxxx ou %Mxxxx)
   {
      *areaMem = "%M";
      s_end    = s_end.SubString( 3, s_end.Length() );  // Tira o %M


      if ( isdigit( s_end[1] ) )  // Se o primeiro caracter, tirando o %M, é um dígito, é um endereço %M. Doh!
      {
         *end    = (unsigned short int) s_end.ToInt();
         retorno = true;
      }
      else  // Senão, é um %M_
      {
         if ( ( s_end[1] == 'W' ) ||  // Se é um endereço %MW,
              ( s_end[1] == 'D' ) ||  // Se é um endereço %MD ou
              ( s_end[1] == 'F' ) )   // Se é um endereço %MF
         {
            *areaMem += s_end[1];
            *end      = (unsigned short int) s_end.SubString( 2, s_end.Length() ).ToInt();
            retorno   = true;  // É válido
         }
      }
   }

   return retorno;
}


bool TModBusTCPDriver::CadastraLeituraEnd( AnsiString s_end )
{
   bool cadastroOK = false;

   AnsiString
      areaMem;

   unsigned short int
      end, bit;

   TModBusCmd*
      cmd;


   if ( ParseEnd( s_end, & areaMem, & end, & bit ) )  // Se foi passado um endereço válido
   {
           if   ( areaMem == "%M" )
      {
         cmd = new TModBusCmd();
         cmd->fc01( end - _SlaveSyntax, 1 );

         _listaCmdMod_fc[ cmd->fc ][ cmd->end ] = cmd;
      }
      else if   ( areaMem == "%MW" )
      {
         cmd = new TModBusCmd();
         cmd->fc03( end - _SlaveSyntax, 1 );

         _listaCmdMod_fc[ cmd->fc ][ cmd->end ] = cmd;
      }
      else if ( ( areaMem == "%MD" ) || ( areaMem == "%MF" ) )
      {
         cmd = new TModBusCmd();
         cmd->fc03( end - _SlaveSyntax, 2 );

         _listaCmdMod_fc[ cmd->fc ][ cmd->end ] = cmd;
      }
   }


   return cadastroOK;
}


void TModBusTCPDriver::CriaListaCiclica()
{
/*
   for ( int i = 0; i < 5; i++ )
      for ( int j = 0; _listaCmdMod_fc[i].begin() + j < _listaCmdMod_fc[i].end(); j++ )
         _cmds_Ciclicos.push_back( (_listaCmdMod_fc[i].begin() + j)->second )
*/
}

#endif