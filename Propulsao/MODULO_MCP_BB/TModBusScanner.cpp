
#ifndef __TMODBUSDRIVER_H
#define __TMODBUSDRIVER_H


#define VERSAO "2.3"


#ifndef __VECTOR_H
#include <vector.h>
#endif

#ifndef __LIST_H
#include <list.h>
#endif

#ifndef __MAP_H
#include <map.h>
#endif

#ifndef __SET_H
#include <set.h>
#endif

#ifndef ScktCompHPP
#include <ScktComp.hpp>
#endif


#include "lib - acesso a arquivos CSV.cpp"


#define Sb(a) |  ( 0x01 << a )
#define Rb(a) & ~( 0x01 << a )

#define PREMIUM  0
#define QUANTUM -1



typedef struct TModBusCmd
{
   ~TModBusCmd()
   { delete[] buffer; }

   int tam;
   unsigned char *buffer;

} TModBusCmd;


typedef struct fcEnd
{
   fcEnd( unsigned short int f = 1, unsigned short int e = 0, short int b = -1, unsigned short int t = 0 )
   {
     fc   = f;
     end  = e;
     bit  = b;
     tipo = t;
   }

   unsigned short int
      fc,
      end,
      tipo;

   short int
      bit;

} fcEnd;


class TModBusScanner
{
public:

   TModBusScanner( TComponent* AOwner, short int clp, int conexoesWR, int conexoesRD );
  ~TModBusScanner();

   void Open();
   void Open( AnsiString ip );

   void __fastcall ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket );
   void __fastcall ClientSocketRead( TObject *Sender, TCustomWinSocket *Socket );
   void __fastcall ClientSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket );
   void __fastcall ClientSocketError( TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int &ErrorCode );

   void Close();


// ---

   void CadastraLeitura( AnsiString end, AnsiString tipo, AnsiString alias );
   void CadastraEscrita( AnsiString end, AnsiString tipo, AnsiString alias );
   void CarregaArquivoVariaveis( AnsiString arq );

// ---

        bool R_M ( unsigned short int end );
   short int R_MW( unsigned short int end );
   short int R_MW( unsigned short int end, unsigned char bit );
         int R_MD( unsigned short int end );
         int R_MD( unsigned short int end, unsigned char bit );
       float R_MF( unsigned short int end );

       float RD  ( AnsiString var );


        void W_M ( unsigned short int end, int val );
        void W_MW( unsigned short int end, short int val );
        void W_MW( unsigned short int end, unsigned char bit, bool val );
        void W_MD( unsigned short int end, int val );
        void W_MD( unsigned short int end, unsigned char bit, bool val );
        void W_MF( unsigned short int end, float val );

       void  WR  ( AnsiString var, float val );

   int
      conectado;

//private:

   void LeituraCiclica_fc01( unsigned short int end );
   void LeituraCiclica_fc03( unsigned short int end );

   void GeraRequests_fc01();
   void GeraRequests_fc03();



// [>] VARI�VEIS DAS CONEX�ES DE REDE

   AnsiString
      _ip;

   TComponent*
      _Owner;

   vector< TClientSocket* >
      _vetorClientes;

   int
      _numConexoesRD,
      _numConexoesWR,
      _numConexoesTotal;

// [<] VARI�VEIS DAS CONEX�ES DE REDE


// [#] LISTAS DOS ENDERE�OS DE LEITURA DE TODAS AS TABELAS USADAS

   set< unsigned short int >
      _listaEndRD_fc01,
      _listaEndRD_fc03;


// [#] MAPA QUE RELACIONA UMA ALIAS QUALQUER A UM ENDERE�O MODBUS

   map< AnsiString, fcEnd* >
      _mapaAliasEndRD,
      _mapaAliasEndWR;


// [>] TABELAS INTERNAS DE ALOCA��O DAS TABELAS MODBUS

   unsigned char
      _fc01[ 0x10000 / 8 ],
      _fc02[ 0x10000 / 8 ];

   unsigned short int
      _fc03[ 0x10000 ],
      _fc04[ 0x10000 ];

// [>] TABELAS INTERNAS DE ALOCA��O DAS TABELAS MODBUS


// [>] VARI�VEIS DE ARMAZENAGEM E CONTROLE DE EXECU��O DOS COMANDOS MODBUS

   vector< TModBusCmd* >
      _vetorCmdCiclicos;

   list< TModBusCmd* >
      _listaCmdSimples;

   int
      _qtdEndOffsetPLC,
      _qtdCmdCiclicos,
      _idxCmdCiclicos;

// [<] VARI�VEIS DE ARMAZENAGEM E CONTROLE DE EXECU��O DOS COMANDOS MODBUS
};


TModBusScanner::TModBusScanner( TComponent* AOwner, short int clp = 0, int conexoesWR = 1, int conexoesRD = 1 )
{
   conectado = 0;  // Indicador de conex�o

   _numConexoesRD    = conexoesRD;               // Conex�es Exclusivamente de Leitura
   _numConexoesWR    = conexoesWR;               // Conex�es primariamente de Escrita, sen�o, Leitura
   _numConexoesTotal = conexoesRD + conexoesWR;  // Total de Conex�es
   _Owner = AOwner;                              // "Dono" dos Clientes Socket

   _ip = "";

   _qtdEndOffsetPLC = clp;  // Endere�os de Offset desse PLC. Padr�o 0.
   _qtdCmdCiclicos  = 0;    // Tamanho do vetor de comandos c�clicos
   _idxCmdCiclicos  = 0;    // �ndice de itera��o pelo vetor
}


TModBusScanner::~TModBusScanner()
{
   Close();
}


void TModBusScanner::Open()
{
   if ( _ip.Length() )
      Open( _ip );
}


void TModBusScanner::Open( AnsiString ip )
{
   if ( _listaEndRD_fc01.size() ) GeraRequests_fc01();  // Gera os requests ModBus para todas as tabelas
   if ( _listaEndRD_fc03.size() ) GeraRequests_fc03();  // com endere�os cadastrados


   _ip = ip;

   for ( int i = 0; i < _numConexoesTotal; i++ )  // S�o criados RD + WR clientes socket.
   {
      TClientSocket*
         socket = new TClientSocket( _Owner );

      socket->Active       = false;
      socket->Address      = _ip;
      socket->Port         = 502;
      socket->Tag          = ( i >= _numConexoesRD );  // Tag == 1, conex�es de Escrita
      socket->ClientType   = ctNonBlocking;

      socket->OnConnect    = ClientSocketConnect;      //
      socket->OnRead       = ClientSocketRead;         // Atribui os eventos a esse objeto
      socket->OnDisconnect = ClientSocketDisconnect;   //
      socket->OnError      = ClientSocketError;        //

      _vetorClientes.push_back( socket );              // Armazena esse ClientSocket no vetor
   }


   for ( int j = 0; j < _numConexoesTotal; j++ )       // Abre todas as conex�es
      _vetorClientes[j]->Open();
}


void __fastcall TModBusScanner::ClientSocketConnect( TObject *Sender, TCustomWinSocket *Socket )
{
   bool nenhumaOff = 1;                                                 //
   for ( int i = 0; ( nenhumaOff ) && ( i < _numConexoesTotal ); i++ )  //
      if ( ! _vetorClientes[i]->Active )                                // Determina��o de status de conex�o
         nenhumaOff = 0;                                                //
                                                                        //
   conectado = ( nenhumaOff ) ? 2 : 1;                                  //



   if ( _listaCmdSimples.size() && ((TClientSocket*) Sender)->Tag )  // Se houverem comandos simples pendentes e a conex�o for de escrita
   {
      ((TClientSocket*) Sender)->Tag = 1;  // Sinaliza que esse Socket � de escrita mas n�o est� dispon�vel para receber comandos de
                                              // escrita direta

      Socket->SendBuf( _listaCmdSimples.front()->buffer,
                       _listaCmdSimples.front()->tam );   // Executa o primeiro comando da lista

      _listaCmdSimples.pop_front();                       // e o retira
   }
   else if ( _qtdCmdCiclicos )  // Se houverem comandos c�clicos
   {
      Socket->SendBuf( _vetorCmdCiclicos[ _idxCmdCiclicos ]->buffer,
                       _vetorCmdCiclicos[ _idxCmdCiclicos ]->tam );   // Executa o comando apontado pelo �ndice

      if ( ++_idxCmdCiclicos >= _qtdCmdCiclicos )  // Incrementa o �ndice e, se necess�rio,
         _idxCmdCiclicos = 0;                      // o reseta.
   }
   else if ( ((TClientSocket*) Sender)->Tag ) // Salvaguarda para o caso de n�o haver nenhum comando a ser executado.
      ((TClientSocket*) Sender)->Tag = -1;    // Sinaliza o comando como dispon�vel para escrita direta.
}


void __fastcall TModBusScanner::ClientSocketRead( TObject *Sender, TCustomWinSocket *Socket )
{
   int tam = Socket->ReceiveLength();

   unsigned char buffer[264];  // 264 bytes de mensagem no m�ximo = 10 bytes de cabe�alho + 254 bytes ( 127 * 2 words ) de dados

   Socket->ReceiveBuf( buffer, tam );  // Recebe o buffer

                             // Pega o "Transaction Identifier" que � o endere�o inicial do comando e o salva invertido (vem Big Endian)
   unsigned short int end = ( ( (unsigned short int) buffer[0] ) << 8 ) |
                                (unsigned short int) buffer[1];


// Armazena o que leu, nos buffers, se o buffer n�o estiver marcado como descarte

        if ( buffer[7] == 0x01 )  // fc01
      for ( unsigned char i = 0; i < buffer[8]; i++, end += 8 )
         _fc01[ end / 8 ] = buffer[i + 9];

   else if ( buffer[7] == 0x03 )  // fc03
      for ( unsigned char i = 0; i < buffer[8]; i += 2 )
         _fc03[ end++ ] = ( ( (unsigned short int) buffer[i +  9] ) << 8 ) |
                              (unsigned short int) buffer[i + 10];


   if ( _listaCmdSimples.size() && ((TClientSocket*) Sender)->Tag )  // Se houverem comandos simples pendentes e a conex�o for de escrita
   {
      ((TClientSocket*) Sender)->Tag = 1;  // Sinaliza que esse Socket � de escrita mas n�o est� dispon�vel para receber comandos de
                                           // escrita direta

      Socket->SendBuf( _listaCmdSimples.front()->buffer,
                       _listaCmdSimples.front()->tam );   // Executa o primeiro comando da lista

      _listaCmdSimples.pop_front();                       // e o retira                       
   }
   else if ( _qtdCmdCiclicos )  // Se houverem comandos c�clicos
   {
      Socket->SendBuf( _vetorCmdCiclicos[ _idxCmdCiclicos ]->buffer,
                       _vetorCmdCiclicos[ _idxCmdCiclicos ]->tam );   // Executa o comando apontado pelo �ndice

      if ( ++_idxCmdCiclicos == _qtdCmdCiclicos )  // Incrementa o �ndice e, se necess�rio,
         _idxCmdCiclicos = 0;                      // o reseta.
   }
   else if ( ((TClientSocket*) Sender)->Tag )  // Salvaguarda para o caso de n�o haver nenhum comando a ser executado.
      ((TClientSocket*) Sender)->Tag = -1;     // Sinaliza o comando como dispon�vel para escrita direta.
}


void __fastcall TModBusScanner::ClientSocketDisconnect( TObject *Sender, TCustomWinSocket *Socket )
{
   bool nenhumaOn = 1;                                                 //
   for ( int i = 0; ( nenhumaOn ) && ( i < _numConexoesTotal ); i++ )  //
      if ( _vetorClientes[i]->Active )                                 // Determina��o de status de conex�o
         nenhumaOn = 0;                                                //
                                                                       //
   conectado = ( nenhumaOn ) ? 0 : 1;                                  //
}


void __fastcall TModBusScanner::ClientSocketError( TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int &ErrorCode )
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

   ( (TClientSocket*) Sender )->Active = false;
   ( (TClientSocket*) Sender )->Open();
}


void TModBusScanner::Close()
{
   for ( int i = 0; i < _numConexoesTotal; i++ )
      _vetorClientes[i]->Close();

   for ( int j = 0; j < _numConexoesTotal; j++ )
   {
      while ( _vetorClientes[j]->Active );  // Espera para ter certeza que a conex�o est� fechada
      delete  _vetorClientes[j];            // Apaga o socket
   }

   _vetorClientes.clear();


   for ( int k = 0; k < _vetorCmdCiclicos.size(); k++ )
      delete _vetorCmdCiclicos[k];

   _vetorCmdCiclicos.clear();


   while ( _listaCmdSimples.size() )
   {
      delete _listaCmdSimples.front();
      _listaCmdSimples.pop_front();
   }


   while ( _mapaAliasEndRD.size() )
   {
      delete _mapaAliasEndRD.begin()->second;
      _mapaAliasEndRD.erase( _mapaAliasEndRD.begin() );
   }


   while ( _mapaAliasEndWR.size() )
   {
      delete _mapaAliasEndWR.begin()->second;
      _mapaAliasEndWR.erase( _mapaAliasEndWR.begin() );
   }
}


void TModBusScanner::LeituraCiclica_fc01( unsigned short int end )
{
   _listaEndRD_fc01.insert( 8 * ( end / 8 ) + 0 );
   _listaEndRD_fc01.insert( 8 * ( end / 8 ) + 7 );
}


void TModBusScanner::LeituraCiclica_fc03( unsigned short int end )
{
   _listaEndRD_fc03.insert( end );
}


void TModBusScanner::GeraRequests_fc01()
{
   unsigned short int
      end = 0,
      qtd = 1;


   while ( _listaEndRD_fc01.size() )
   {
      // Determina o endere�o de in�cio de leitura e a quantidade de bits lidos

      end = *_listaEndRD_fc01.begin();
             _listaEndRD_fc01.erase( _listaEndRD_fc01.begin() );

      while (  _listaEndRD_fc01.size() )
         if ( *_listaEndRD_fc01.begin() - end + 1 <= 2000 )  // 2000 bits == 250 Bytes (125 Words) * 8 bits
         {
            qtd = *_listaEndRD_fc01.begin() - end + 1;
                   _listaEndRD_fc01.erase( _listaEndRD_fc01.begin() );
         }
         else
            break;


   /*  Cria a requisi��o de leitura ModBus
    *
    *  Frame:
    *
    *  2 BYTES - Identificador de Transa��o
    *  2 BYTES - Identificador de Protocolo
    *  2 BYTES - Quantidades de Bytes de Mensagem, a seguir ( fc01 -> 6 BYTES )
    *  1 BYTES - Slave Address (Sempre 1)
    *  1 BYTES - Function Code
    *  2 BYTES - Endere�o
    *  2 BYTES - Quantidade de Dados (Bits em %M) a serem lidos
    */

      TModBusCmd *cmd = new TModBusCmd;

      cmd->tam    = 12;
      cmd->buffer = new unsigned char [ cmd->tam ];

//                                                               1                       0
      *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );  // Endere�o como identificador
//                                                        5 4 3 2                                    // de transa��o
      *( (unsigned       int*) & cmd->buffer[2]  ) =   0x06000000;
//                                                        7 6
      *( (unsigned short int*) & cmd->buffer[6]  ) =   0x0101;                                       // Slave Address + Function Code 01
//                                                               9                       8
      *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                              11                      10
      *( (unsigned short int*) & cmd->buffer[10] ) = ( 0xFF00 & qtd << 8 ) | ( 0x00FF & qtd >> 8 );


      _vetorCmdCiclicos.push_back( cmd );
      _qtdCmdCiclicos = _vetorCmdCiclicos.size();
   }
}


void TModBusScanner::GeraRequests_fc03()
{
   unsigned short int
      end = 0,
      qtd = 1;


   while ( _listaEndRD_fc03.size() )
   {
      // Determina o endere�o de in�cio de leitura e a quantidade de bits lidos

      end = *_listaEndRD_fc03.begin();
             _listaEndRD_fc03.erase( _listaEndRD_fc03.begin() );

      while (  _listaEndRD_fc03.size() )
         if ( *_listaEndRD_fc03.begin() - end + 1 <= 125 )  // 250 Bytes == 125 Words
         {
            qtd = *_listaEndRD_fc03.begin() - end + 1;
                   _listaEndRD_fc03.erase( _listaEndRD_fc03.begin() );
         }
         else
            break;


   /*  Cria a requisi��o de leitura ModBus
    *
    *  Frame:
    *
    *  2 BYTES - Identificador de Transa��o
    *  2 BYTES - Identificador de Protocolo
    *  2 BYTES - Quantidades de Bytes de Mensagem, a seguir ( fc03 -> 6 BYTES )
    *  1 BYTES - Slave Address (Sempre 1)
    *  1 BYTES - Function Code
    *  2 BYTES - Endere�o
    *  2 BYTES - Quantidade de Dados (Bits em %M) a serem lidos
    */

      TModBusCmd *cmd = new TModBusCmd;

      cmd->tam    = 12;
      cmd->buffer = new unsigned char [ cmd->tam ];

//                                                               1                       0
      *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );  // Endere�o como identificador
//                                                        5 4 3 2                                    // de transa��o
      *( (unsigned       int*) & cmd->buffer[2]  ) =   0x06000000;
//                                                        7 6
      *( (unsigned short int*) & cmd->buffer[6]  ) =   0x0301;                                       // Slave Address + Function Code 03
//                                                               9                       8
      *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                              11                      10
      *( (unsigned short int*) & cmd->buffer[10] ) = ( 0xFF00 & qtd << 8 ) | ( 0x00FF & qtd >> 8 );


      _vetorCmdCiclicos.push_back( cmd );
      _qtdCmdCiclicos = _vetorCmdCiclicos.size();
   }
}


void TModBusScanner::CadastraLeitura( AnsiString end, AnsiString tipo = "", AnsiString alias = "" )
{
   short int _bit = -1;
   AnsiString temp = end;

   if ( temp.Pos( "." ) )  // Procura por bits
   {
      _bit = temp.SubString(    temp.Pos( "." ) + 1, temp.Length() ).ToInt();  // Armazena o bit
      temp = temp.SubString( 1, temp.Pos( "." ) - 1 );                         // Tira o bits do endere�o
   }

   if ( temp.Pos( "%M" ) == 1 )  // Se for uma regi�o de mem�ria contemplada
   {
      temp = temp.SubString( 3, temp.Length() );  // Tira o %MW

      if ( isdigit( temp[1] ) )  // Se o primeiro caracter, tirando o %M, � um d�gito, � um endere�o %M. Doh!
      {
         unsigned short int _end = (unsigned short int) temp.ToInt();

         LeituraCiclica_fc01( _end + _qtdEndOffsetPLC );


         if ( alias.Length() )
            _mapaAliasEndRD[ alias ] = new fcEnd( 0x01, _end + _qtdEndOffsetPLC );

         _mapaAliasEndRD[ end ] = new fcEnd( 0x01, _end + _qtdEndOffsetPLC );
      }
      else  // � um %MW, %MD ou %MF.
      {
         if ( temp[1] == 'W' )  // Sendo %MW, atentar aos poss�veis tipos
         {
            unsigned short int
               _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt(),
               _tipo = 0;  // 0 == INT


            if ( ( tipo == "REAL" ) || ( tipo == "DOUBLE" ) )  // Tipos REAL e DOUBLE devem ler duas words
            {
               LeituraCiclica_fc03( _end     + _qtdEndOffsetPLC );
               LeituraCiclica_fc03( _end + 1 + _qtdEndOffsetPLC );
            }
            else  // Se n�o for nem real nem double, cadastra s� uma word
               LeituraCiclica_fc03( _end + _qtdEndOffsetPLC );


                 if ( tipo == "DOUBLE" ) _tipo = 1;  // Sendo desses dois tipos,
            else if ( tipo == "REAL" )   _tipo = 2;  // sinaliza


            if ( alias.Length() )
               _mapaAliasEndRD[ alias ] = new fcEnd( 0x03, _end + _qtdEndOffsetPLC, _bit, _tipo );

            _mapaAliasEndRD[ end ] = new fcEnd( 0x03, _end + _qtdEndOffsetPLC, _bit, _tipo );
         }
         else if ( ( temp[1] == 'D' ) || ( temp[1] == 'F' ) )
         {
            unsigned short int
               _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt(),
               _tipo = 1;  // 1 == DOUBLE

            LeituraCiclica_fc03( _end     + _qtdEndOffsetPLC );
            LeituraCiclica_fc03( _end + 1 + _qtdEndOffsetPLC );


            if ( temp[1] == 'F' ) _tipo = 2;  // 2 == REAL

            if ( alias.Length() )
               _mapaAliasEndRD[ alias ] = new fcEnd( 0x03, _end + _qtdEndOffsetPLC, _bit, _tipo );

            _mapaAliasEndRD[ end ] = new fcEnd( 0x03, _end + _qtdEndOffsetPLC, _bit, _tipo );
         }
      }
   }
}


void TModBusScanner::CadastraEscrita( AnsiString end, AnsiString tipo = "", AnsiString alias = "" )
{
   short int _bit = -1;
   AnsiString temp = end;

   if ( temp.Pos( "." ) )  // Procura por bits
   {
      _bit = temp.SubString(    temp.Pos( "." ) + 1, temp.Length() ).ToInt();  // Armazena o bit
      temp = temp.SubString( 1, temp.Pos( "." ) - 1 );                         // Tira o bits do endere�o
   }

   if ( temp.Pos( "%M" ) == 1 )  // Se for uma regi�o de mem�ria contemplada
   {
      temp = temp.SubString( 3, temp.Length() );  // Tira o %MW

      if ( isdigit( temp[1] ) )  // Se o primeiro caracter, tirando o %M, � um d�gito, � um endere�o %M. Doh!
      {
         unsigned short int _end = (unsigned short int) temp.ToInt();

         if ( alias.Length() )
            _mapaAliasEndWR[ alias ] = new fcEnd( 0x0F, _end + _qtdEndOffsetPLC );

         _mapaAliasEndWR[ end ] = new fcEnd( 0x0F, _end + _qtdEndOffsetPLC );
      }
      else  // � um %MW, %MD ou %MF.
      {
         if ( temp[1] == 'W' )  // Sendo %MW, atentar aos poss�veis tipos
         {
            unsigned short int
               _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt(),
               _tipo = 0;  // 0 == INT


                 if ( tipo == "DOUBLE" ) _tipo = 1;  // Sendo desses dois tipos,
            else if ( tipo == "REAL"   ) _tipo = 2;  // sinaliza

            if ( alias.Length() )
               _mapaAliasEndWR[ alias ] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, _tipo );

            _mapaAliasEndWR[ end ] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, _tipo );
         }
         else if ( ( temp[1] == 'D' ) || ( temp[1] == 'F' ) )
         {
            unsigned short int
               _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt(),
               _tipo = 1;  // 1 == DOUBLE


            if ( temp[1] == 'F' ) _tipo = 2;  // 2 == REAL

            if ( alias.Length() )
               _mapaAliasEndWR[ alias ] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, _tipo );

            _mapaAliasEndWR[ end ] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, _tipo );
         }
      }
   }
}


void TModBusScanner::CarregaArquivoVariaveis( AnsiString arq )
{
   TStringList
     *arquivo = new TStringList;

   arquivo->LoadFromFile( arq );

   for ( int i = 0; i < arquivo->Count; i++ )
      if ( getCampoCSV( arquivo->Strings[i], 1, '\t' ).Length() )
      {
         CadastraLeitura( getCampoCSV( arquivo->Strings[i], 1, '\t' ),
                          getCampoCSV( arquivo->Strings[i], 2, '\t' ),
                          getCampoCSV( arquivo->Strings[i], 0, '\t' ) );

         CadastraEscrita( getCampoCSV( arquivo->Strings[i], 1, '\t' ),
                          getCampoCSV( arquivo->Strings[i], 2, '\t' ),
                          getCampoCSV( arquivo->Strings[i], 0, '\t' ) );
      }
}


bool TModBusScanner::R_M ( unsigned short int end )
{
   return ( 1 & ( _fc01[end / 8] >> (end % 8) ) );
}


short int TModBusScanner::R_MW( unsigned short int end )
{
   return _fc03[end];
}


short int TModBusScanner::R_MW( unsigned short int end, unsigned char bit )
{
   return ( bit > 15 ) ? -1 : ( 1 & ( _fc03[end] >> bit ) );
}


int TModBusScanner::R_MD( unsigned short int end )
{
   return *( (int*) & _fc03[end] );
}


int TModBusScanner::R_MD( unsigned short int end, unsigned char bit )
{
   return ( bit > 31 ) ? -1 : ( 1 & ( *( (unsigned int*) & _fc03[end] ) >> bit ) );
}


float TModBusScanner::R_MF( unsigned short int end )
{
   return *( (float*) & _fc03[end] );
}


float TModBusScanner::RD( AnsiString var )
{
   int
      _1 = 0xFFFFFFFF;

   AnsiString
      bit,
      end;

   float
      retorno = *( (float*) & _1 );


   if ( _mapaAliasEndRD.find(var) != _mapaAliasEndRD.end() )
   {
           if ( _mapaAliasEndRD[var]->fc == 0x01 )
         retorno = R_M( _mapaAliasEndRD[var]->end );

      else if ( _mapaAliasEndRD[var]->fc == 0x03 )
      {
              if ( _mapaAliasEndRD[var]->tipo == 0 )  // INT
         {
            if ( _mapaAliasEndRD[var]->bit < 0 )
               retorno = R_MW( _mapaAliasEndRD[var]->end );
            else
               retorno = R_MW( _mapaAliasEndRD[var]->end, _mapaAliasEndRD[var]->bit );
         }
         else if ( _mapaAliasEndRD[var]->tipo == 1 )  // DOUBLE
         {
            if ( _mapaAliasEndRD[var]->bit < 0 )
               retorno = R_MD( _mapaAliasEndRD[var]->end );
            else
               retorno = R_MD( _mapaAliasEndRD[var]->end, _mapaAliasEndRD[var]->bit );
         }
         else if ( _mapaAliasEndRD[var]->tipo == 2 )  // REAL
            retorno = R_MF( _mapaAliasEndRD[var]->end );
      }
   }

   return retorno;
}


void TModBusScanner::W_M ( unsigned short int end, int val )
{
   unsigned char _val;

   if ( val ) _val = _fc01[ end / 8 ] |  ( 0x01 << ( end % 8 ) );
   else       _val = _fc01[ end / 8 ] & ~( 0x01 << ( end % 8 ) );


   TModBusCmd *cmd = new TModBusCmd;

   cmd->tam    = 12;
   cmd->buffer = new unsigned char [ cmd->tam ];
//                                                            1                       0
   *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                     5 4 3 2
   *( (unsigned       int*) & cmd->buffer[2]  ) =   0x06000000;
//                                                     7 6
   *( (unsigned short int*) & cmd->buffer[6]  ) =   0x0501;
//                                                            9                       8
   *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                              11       11
//                                                                10       10
   *( (unsigned short int*) & cmd->buffer[10] ) = ( ! _val ) ? 0x0000 : 0x00FF;


   _listaCmdSimples.push_back( cmd );
}


void TModBusScanner::W_MW( unsigned short int end, short int val )
{
   TModBusCmd *cmd = new TModBusCmd;

   cmd->tam    = 12;
   cmd->buffer = new unsigned char [ cmd->tam ];
//                                                            1                       0
   *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                     5 4 3 2
   *( (unsigned       int*) & cmd->buffer[2]  ) =   0x06000000;
//                                                     7 6
   *( (unsigned short int*) & cmd->buffer[6]  ) =   0x0601;
//                                                            9                       8
   *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                           11                      10
   *( (unsigned short int*) & cmd->buffer[10] ) = ( 0xFF00 & val << 8 ) | ( 0x00FF & val >> 8 );


   _listaCmdSimples.push_back( cmd );
}


void TModBusScanner::W_MW( unsigned short int end, unsigned char bit, bool val )
{
   if ( bit < 16 )
   {
      unsigned short int
         AND = ~( 0x0001 << bit ),
         OR  =  ( val ) ? -1 : 0;

      TModBusCmd *cmd = new TModBusCmd;

      cmd->tam    = 14;
      cmd->buffer = new unsigned char [ cmd->tam ];
   //                                                            1                       0
      *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
   //                                                     5 4 3 2
      *( (unsigned       int*) & cmd->buffer[2]  ) =   0x08000000;
   //                                                     7 6
      *( (unsigned short int*) & cmd->buffer[6]  ) =   0x1601;
   //                                                            9                       8
      *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );

      *( (unsigned short int*) & cmd->buffer[10] ) = ( 0xFF00 & AND << 8 ) | ( 0x00FF & AND >> 8 );

      *( (unsigned short int*) & cmd->buffer[12] ) = ( 0xFF00 &  OR << 8 ) | ( 0x00FF &  OR >> 8 );

      _listaCmdSimples.push_back( cmd );
   }
}


void TModBusScanner::W_MD( unsigned short int end, int val )
{
   TModBusCmd *cmd = new TModBusCmd;

   cmd->tam    = 17;
   cmd->buffer = new unsigned char [ cmd->tam ];
//                                                            1                       0
   *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                     5 4 3 2
   *( (unsigned       int*) & cmd->buffer[2]  ) =   0x0B000000;
//                                                     7 6
   *( (unsigned short int*) & cmd->buffer[6]  ) =   0x1001;
//                                                            9                       8
   *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                    13  11
//                                                      12  10
   *( (unsigned       int*) & cmd->buffer[10] ) =   0x00040200;

   *( (unsigned       int*) & cmd->buffer[13] ) = ( 0x00FF00FF & val >> 8 ) | // 13 e 15
                                                  ( 0xFF00FF00 & val << 8 );  // 14 e 16

   _listaCmdSimples.push_back( cmd );
}


void TModBusScanner::W_MD( unsigned short int end, unsigned char bit, bool val )
{
   if ( bit < 32 )
   {
      if ( bit > 15 )
      {
         bit -= 16;
         end++;
      }

      unsigned short int
         AND = ~( 0x0001 << bit ),
         OR  =  ( val ) ? -1 : 0;

      TModBusCmd *cmd = new TModBusCmd;

      cmd->tam    = 14;
      cmd->buffer = new unsigned char [ cmd->tam ];
   //                                                            1                       0
      *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
   //                                                     5 4 3 2
      *( (unsigned       int*) & cmd->buffer[2]  ) =   0x08000000;
   //                                                     7 6
      *( (unsigned short int*) & cmd->buffer[6]  ) =   0x1601;
   //                                                            9                       8
      *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );

      *( (unsigned short int*) & cmd->buffer[10] ) = ( 0xFF00 & AND << 8 ) | ( 0x00FF & AND >> 8 );

      *( (unsigned short int*) & cmd->buffer[12] ) = ( 0xFF00 &  OR << 8 ) | ( 0x00FF &  OR >> 8 );

      _listaCmdSimples.push_back( cmd );
   }
}


void TModBusScanner::W_MF( unsigned short int end, float val )
{
   TModBusCmd *cmd = new TModBusCmd;

   cmd->tam    = 17;
   cmd->buffer = new unsigned char [ cmd->tam ];
//                                                            1                       0
   *( (unsigned short int*) & cmd->buffer[0]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                     5 4 3 2
   *( (unsigned       int*) & cmd->buffer[2]  ) =   0x0B000000;
//                                                     7 6
   *( (unsigned short int*) & cmd->buffer[6]  ) =   0x1001;
//                                                            9                       8
   *( (unsigned short int*) & cmd->buffer[8]  ) = ( 0xFF00 & end << 8 ) | ( 0x00FF & end >> 8 );
//                                                    13  11
//                                                      12  10
   *( (unsigned       int*) & cmd->buffer[10] ) =   0x00040200;

   *( (unsigned       int*) & cmd->buffer[13] ) = ( 0x00FF00FF & *((int*) & val) >> 8 ) | // 13 e 15
                                                  ( 0xFF00FF00 & *((int*) & val) << 8 );  // 14 e 16

   _listaCmdSimples.push_back( cmd );
}


void TModBusScanner::WR ( AnsiString var, float val )
{
   if ( _mapaAliasEndWR.find(var) != _mapaAliasEndWR.end() )
   {
           if ( _mapaAliasEndWR[var]->fc == 0x0F )   // EBOOL
         W_M( _mapaAliasEndWR[var]->end, val );

      else if ( _mapaAliasEndWR[var]->fc == 0x10 )
      {
              if ( _mapaAliasEndWR[var]->tipo == 0 )  // INT
         {
            if ( _mapaAliasEndWR[var]->bit < 0 )
               W_MW( _mapaAliasEndWR[var]->end, val );
            else
               W_MW( _mapaAliasEndWR[var]->end, _mapaAliasEndWR[var]->bit, val );
         }
         else if ( _mapaAliasEndWR[var]->tipo == 1 )  // DOUBLE
         {
            if ( _mapaAliasEndWR[var]->bit < 0 )
               W_MD( _mapaAliasEndWR[var]->end, val );
            else
               W_MD( _mapaAliasEndWR[var]->end, _mapaAliasEndWR[var]->bit, val );
         }
         else if ( _mapaAliasEndWR[var]->tipo == 2 )  // REAL
            W_MF( _mapaAliasEndWR[var]->end, val );
      }
   }
   else  // Se n�o estiver no mapa de alias, assume que � um endere�o novo e tenta cadastrar e escrever*/
   {
      short int _bit = -1;
      AnsiString temp = var;

      if ( temp.Pos( "." ) )  // Procura bits
      {
         _bit = temp.SubString(    temp.Pos( "." ) + 1, temp.Length() ).ToInt();  // Armazena o bit
         temp = temp.SubString( 1, temp.Pos( "." ) - 1 );                         // Tira o bits do endere�o
      }


      if ( temp.Pos( "%M" ) == 1 )  // Se for uma regi�o de mem�ria contemplada
      {
         temp = temp.SubString( 3, temp.Length() );  // Tira o %M

         if ( isdigit( temp[1] ) )  // Se o primeiro caracter, tirando o %M, � um d�gito, � um endere�o %M. Doh!
         {
            unsigned short int _end = (unsigned short int) temp.ToInt();

            _mapaAliasEndWR[var] = new fcEnd( 0x0F, _end + _qtdEndOffsetPLC );

            W_M( _end + _qtdEndOffsetPLC, val );
         }
         else  // � um %MW, %MD ou %MF.
         {
            if ( temp[1] == 'W' )  // Sendo %MW, atentar aos poss�veis tipos
            {
               unsigned short int _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt();

               _mapaAliasEndWR[var] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, 0 );

               if ( _bit < 0 )
                  W_MW( _end + _qtdEndOffsetPLC, val );
               else
                  W_MW( _end + _qtdEndOffsetPLC, _bit, val );
            }
            else if ( temp[1] == 'D' )
            {
               unsigned short int _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt();

               _mapaAliasEndWR[var] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, 1 );

               if ( _bit < 0 )
                  W_MD( _end + _qtdEndOffsetPLC, val );
               else
                  W_MD( _end + _qtdEndOffsetPLC, _bit, val );
            }
            else if ( temp[1] == 'F' )
            {
               unsigned short int _end  = (unsigned short int) temp.SubString( 2, temp.Length() ).ToInt();

               _mapaAliasEndWR[var] = new fcEnd( 0x10, _end + _qtdEndOffsetPLC, _bit, 2 );

               W_MF( _end + _qtdEndOffsetPLC, val );
            }
         }
      }
   }
}

#endif