
/*
 *  Classe TModBusTCPDriver.
 *
 *  Implementa um driver simples para comunicação ModBus TCP com
 *  quantidade de conexões configurável e processamento dos sockets
 *  em thread separada.
 *
 *
 *
 */


#ifndef __TMODBUSDRIVER_H
#define __TMODBUSDRIVER_H


#define VERSAO "1.0"


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


#define  GET_BIT_IN_BYTE(a)  &     0x01 << a

#define  SET_BIT_IN_BYTE(a)  |=    0x01 << a
#define  CLR_BIT_IN_BYTE(a)  &= ~( 0x01 << a )

#define  SWAP_ENDIANNESS_16BITS(n)  (     0xFF00 & n << 8 ) | (     0x00FF & n >> 8 )
#define  SWAP_ENDIANNESS_32BITS(n)  ( 0x00FF00FF & n >> 8 ) | ( 0xFF00FF00 & n << 8 )


#define  PREMIUM  0
#define  QUANTUM -1


/*
 *
 * -------------- CLASSE COMANDO MODBUS --------------
 *
 */

class TModBusCmd
{

public:

   TModBusCmd();
   ~TModBusCmd();

   void Clear();

   bool fc01 ( int end,                  int  qtd, unsigned char slaveAddr );  // Read Coil Status
   bool fc02 ( int end,                  int  qtd, unsigned char slaveAddr );  // Read Input Status
   bool fc03 ( int end,                  int  qtd, unsigned char slaveAddr );  // Read Holding Registers
   bool fc04 ( int end,                  int  qtd, unsigned char slaveAddr );  // Read Input Registers
   bool fc05 ( int end,                  bool val, unsigned char slaveAddr );  // Force Single Coil
   bool fc06 ( int end,            short int  val, unsigned char slaveAddr );  // Preset Single Register

   bool fc15 ( int end, int qtd,       bool *vals, unsigned char slaveAddr );  // Force Multiple Coils
   bool fc16 ( int end, int qtd, short int  *vals, unsigned char slaveAddr );  // Preset Multiple Registers ( words 16 bits )
   bool fc16 ( int end,                 float val, unsigned char slaveAddr );  // Preset Multiple Registers ( float 32 bits )

   bool fc22 ( int end, short int and, short int or, unsigned char slaveAddr );  // Mask Write Register


   bool ParseResponseToCmd( unsigned char *buffer, int tam );


   AnsiString PrintBufferCmd();   // Imprime o Buffer de Comando
   AnsiString PrintBufferResp();  // Imprime o Buffer da Resposta
   AnsiString PrintBuffer();      // Imprime ambos os Buffers


   AnsiString
      erro;

   unsigned char
      fc,
      slaveAddr,
     *bufferCmd,
     *bufferResp;

   bool
     *b_vals;

   unsigned short int
      id,
      end,
      qtd,
      tam;

   short int
      val,
     *i_vals;


private:

   bool fcGEN( int end, int qtd, unsigned char slaveAddr );  // Default
};


TModBusCmd::TModBusCmd()
{
   bufferCmd  = NULL;
   bufferResp = NULL;
   b_vals     = NULL;
   i_vals     = NULL;

   Clear();
}


TModBusCmd::~TModBusCmd()
{
   Clear();
}


void TModBusCmd::Clear()
{
   id = 0;
   fc = 0;
   slaveAddr = 1;

   end = 0;
   qtd = 0;
   tam = 0;

   val = 0;

   if ( bufferCmd )
   {
      delete[] bufferCmd;
      bufferCmd = NULL;
   }

   if ( bufferResp )
   {
      delete[] bufferResp;
      bufferResp = NULL;
   }

   if ( b_vals )
   {
      delete[] b_vals;
      b_vals = NULL;
   }

   if ( i_vals )
   {
      delete[] i_vals;
      i_vals = NULL;
   }
}


bool TModBusCmd::fcGEN( int _end, int _qtd_val, unsigned char _slaveAddr = 0 )  // Estrutura genérica para vários comandos ModBus
{
   end = _end;
   id  = _end;

   if ( _slaveAddr )
     slaveAddr = _slaveAddr;

   tam = 12;

   if ( bufferCmd = new unsigned char [ tam ] )
   {
      memset( bufferCmd, 0, sizeof(unsigned char) * tam );

      *( (unsigned short int*) & bufferCmd[0]  ) = SWAP_ENDIANNESS_16BITS( id );        // Transaction ID (end)
      *( (unsigned short int*) & bufferCmd[2]  ) = 0;                              // Protocol ID (0x0000)
      *( (unsigned short int*) & bufferCmd[4]  ) = SWAP_ENDIANNESS_16BITS( tam - 6 );   // Length (0x0006)
                                 bufferCmd[6]    = slaveAddr;                      // Slave Address
                                 bufferCmd[7]    = fc;                             // Function Code
      *( (unsigned short int*) & bufferCmd[8]  ) = SWAP_ENDIANNESS_16BITS( end );       // Endereço
      *( (unsigned short int*) & bufferCmd[10] ) = SWAP_ENDIANNESS_16BITS( _qtd_val );  // Qtd ou Valor (fc05)
   }
   else
      Clear();


   return ( bufferCmd != NULL );
}


bool TModBusCmd::fc01 ( int _end, int  _qtd, unsigned char _slaveAddr = 1 )  // Read Coil Status
{
   Clear();

   fc  = 0x01;
   qtd = _qtd;

   return fcGEN( _end, _qtd, _slaveAddr );
}


bool TModBusCmd::fc02 ( int _end, int  _qtd, unsigned char _slaveAddr = 1 )  // Read Input Status
{
   Clear();

   fc  = 0x02;
   qtd = _qtd;

   return fcGEN( _end, _qtd, _slaveAddr );
}


bool TModBusCmd::fc03 ( int _end, int  _qtd, unsigned char _slaveAddr = 1 )  // Read Holding Registers
{
   Clear();

   fc  = 0x03;
   qtd = _qtd;

   return fcGEN( _end, _qtd, _slaveAddr );
}


bool TModBusCmd::fc04 ( int _end, int  _qtd, unsigned char _slaveAddr = 1 )  // Read Input Registers
{
   Clear();

   fc  = 0x04;
   qtd = _qtd;

   return fcGEN( _end, _qtd, _slaveAddr );
}


bool TModBusCmd::fc05 ( int _end, bool _val, unsigned char _slaveAddr = 1 )  // Force Single Coil
{
   Clear();

   fc  = 0x05;
   qtd = 1;
   val = (int) _val;

   return fcGEN( _end, (_val ? 0xFF00 : 0), _slaveAddr );
}


bool TModBusCmd::fc06 ( int _end, short int _val, unsigned char _slaveAddr = 1 )  // Preset Single Register
{
   Clear();

   fc  = 0x06;
   qtd = 1;
   val = _val;

   return fcGEN( _end, _val, _slaveAddr );
}


bool TModBusCmd::fc15 ( int _end, int _qtd, bool *_vals, unsigned char _slaveAddr = 1 )  // Force Multiple Coils
{
   Clear();

   fc  = 0x0F;
   qtd = _qtd;
   end = _end;
   id  = _end;

   if ( _slaveAddr )
     slaveAddr = _slaveAddr;


   tam = 12 + 1 + ( 1 + qtd / 8 );

   if ( bufferCmd = new unsigned char [ tam ] )
   {
      memset( bufferCmd, 0, sizeof(unsigned char) * tam );

      *( (unsigned short int*) & bufferCmd[0]  ) = SWAP_ENDIANNESS_16BITS( id );       // Transaction ID (end)
      *( (unsigned short int*) & bufferCmd[2]  ) = 0;                                  // Protocol ID (0x0000)
      *( (unsigned short int*) & bufferCmd[4]  ) = SWAP_ENDIANNESS_16BITS( tam - 6 );  // Length ()
                                 bufferCmd[6]    = slaveAddr;                          // Slave Address
                                 bufferCmd[7]    = fc;                                 // Function Code
      *( (unsigned short int*) & bufferCmd[8]  ) = SWAP_ENDIANNESS_16BITS( end );      // Endereço
      *( (unsigned short int*) & bufferCmd[10] ) = SWAP_ENDIANNESS_16BITS( qtd );      // Qtd
                                 bufferCmd[12]   = ( 1 + qtd / 8 );                    // Bytes de Dados

      for ( int i = 0; i < qtd; i++ )
         if ( _vals[i] )
            bufferCmd[ 13 + i / 8 ] SET_BIT_IN_BYTE(i%8);
         else
            bufferCmd[ 13 + i / 8 ] CLR_BIT_IN_BYTE(i%8);


      b_vals = _vals;
   }
   else
      Clear();


   return ( bufferCmd != NULL );
}


bool TModBusCmd::fc16 ( int _end, int _qtd, short int *_vals, unsigned char _slaveAddr = 1 )  // Preset Multiple Registers ( words 16 bits )
{
   Clear();

   fc  = 0x10;
   qtd = _qtd;
   end = _end;
   id  = _end;

   if ( _slaveAddr )
     slaveAddr = _slaveAddr;


   tam = 12 + 1 + ( qtd * 2 );

   if ( bufferCmd = new unsigned char [ tam ] )
   {
      memset( bufferCmd, 0, sizeof(unsigned char) * tam );

      *( (unsigned short int*) & bufferCmd[0]  ) = SWAP_ENDIANNESS_16BITS( id );       // Transaction ID (end)
      *( (unsigned short int*) & bufferCmd[2]  ) = 0;                                  // Protocol ID (0x0000)
      *( (unsigned short int*) & bufferCmd[4]  ) = SWAP_ENDIANNESS_16BITS( tam - 6 );  // Length ()
                                 bufferCmd[6]    = slaveAddr;                          // Slave Address
                                 bufferCmd[7]    = fc;                                 // Function Code
      *( (unsigned short int*) & bufferCmd[8]  ) = SWAP_ENDIANNESS_16BITS( end );      // Endereço
      *( (unsigned short int*) & bufferCmd[10] ) = SWAP_ENDIANNESS_16BITS( qtd );      // Qtd
                                 bufferCmd[12]   = qtd * 2;                            // Bytes de Dados

      for ( int i = 0; i < qtd; i++ )
         *( (unsigned short int*) & bufferCmd[ 13 + i*2 ] ) = _vals[i];


      i_vals = _vals;
   }
   else
      Clear();


   return ( bufferCmd != NULL );
}


bool TModBusCmd::fc16 ( int end, float val, unsigned char slaveAddr = 1 )  // Preset Multiple Registers ( float 32 bits )
{
   static unsigned int temp = SWAP_ENDIANNESS_32BITS( *( (unsigned int*) & val ) );

   return fc16( end, 2, (short int*) & temp, slaveAddr );
}


bool TModBusCmd::fc22 ( int _end, short int _and, short int _or, unsigned char _slaveAddr = 1 )  // Mask Write Register
{
  /*
   *  Função usada para SET ou RESET de bits individuais de um holding register
   *
   *  Result = (ATUAL && and) || (or && ! and)
   *
   *  > Se  or == 0, Result = ATUAL && and
   *  > Se and == 0, Result = ATUAL ||  or
   *
   */

   Clear();

   fc  = 0x16;
   qtd = 2;
   val = (0xFFFF && _and) || (_or && ! _and);

   end = _end;
   id  = _end;

   if ( _slaveAddr )
     slaveAddr = _slaveAddr;

   tam = 14;

   if ( bufferCmd = new unsigned char [ tam ] )
   {
      memset( bufferCmd, 0, sizeof(unsigned char) * tam );

      *( (unsigned short int*) & bufferCmd[0]  ) = SWAP_ENDIANNESS_16BITS( id );        // Transaction ID (end)
      *( (unsigned short int*) & bufferCmd[2]  ) = 0;                                   // Protocol ID (0x0000)
      *( (unsigned short int*) & bufferCmd[4]  ) = SWAP_ENDIANNESS_16BITS( tam - 6 );   // Length (0x0006)
                                 bufferCmd[6]    = slaveAddr;                           // Slave Address
                                 bufferCmd[7]    = fc;                                  // Function Code
      *( (unsigned short int*) & bufferCmd[8]  ) = SWAP_ENDIANNESS_16BITS( end );       // Endereço
      *( (unsigned short int*) & bufferCmd[10] ) = SWAP_ENDIANNESS_16BITS( _and );      // Máscara AND
      *( (unsigned short int*) & bufferCmd[12] ) = SWAP_ENDIANNESS_16BITS( _or );       // Máscara OR
   }
   else
      Clear();


   return ( bufferCmd != NULL );
}


bool TModBusCmd::ParseResponseToCmd( unsigned char *_buf, int _tam )  // Analiza um buffer de resposta a um comando para determinar se é uma resposta válida
{
   bool respostaValida = false;

   if ( _buf && ( _tam > 7 ) )  // Garante que pode ler os 7 primeiros Bytes do Header ModBus TCP
   {
      unsigned char _fc = _buf[7];

      if ( (   id == SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[0] ) )     ) &&  // Se a resposta possuir o mesmo id e,
           ( _tam == SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[4] ) ) + 6 ) &&  // Se o buffer veio íntegro
           (   fc == ( 0x7F & _fc ) ) )                                                       // Se o Function Code, com erro ou não, se refere ao fc deste
      {
         if ( ( _fc & 0x80 ) > 0 )  // Se a tentativa de execução do comando gerou um erro
         {
            switch ( _buf[8] )
            {
               case 0x01: erro = "ILLEGAL FUNCTION"; break;

               /* The function code received in the query is not an allowable action for the server (or slave). This
                * may be because the function code is only applicable to newer devices, and was not implemented in
                * the unit selected. It could also indicate that the server (or slave) is in the wrong state to process
                * a request of this type, for example because it is unconfigured and is being asked to return register values.
                */

               case 0x02: erro = "ILLEGAL DATA ADDRESS"; break;

               /* The data address received in the query is not an allowable address for the server (or slave). More
                * specifically, the combination of reference number and transfer length is invalid. For a controller with
                * 100 registers, the PDU addresses the first register as 0, and the last one as 99. If a request is
                * submitted with a starting register address of 96 and a quantity of registers of 4, then this request
                * will successfully operate (address-wise at least) on registers 96, 97, 98, 99. If a request is
                * submitted with a starting register address of 96 and a quantity of registers of 5, then this request
                * will fail with Exception Code 0x02 “Illegal Data Address” since it attempts to operate on registers
                * 96, 97, 98, 99 and 100, and there is no register with address 100.
                */

               case 0x03: erro = "ILLEGAL DATA VALUE"; break;

               /* A value contained in the query data field is not an allowable value for server (or slave). This
                * indicates a fault in the structure of the remainder of a complex request, such as that the implied
                * length is incorrect. It specifically does NOT mean that a data item submitted for storage in a register
                * has a value outside the expectation of the application program, since the MODBUS protocol is unaware
                * of the significance of any particular value of any particular register.
                */

               case 0x04: erro = "SLAVE DEVICE FAILURE"; break;

               // An unrecoverable error occurred while the server (or slave) was attempting to perform the requested action.

               case 0x05: erro = "ACKNOWLEDGE"; break;

               /* Specialized use in conjunction with programming commands. The server (or slave) has accepted the request
                * and is processing it, but a long duration of time will be required to do so. This response is returned
                * to prevent a timeout error from occurring in the client (or master). The client (or master) can next
                * issue a Poll Program Complete message to determine if processing is completed.
                */

               case 0x06: erro = "SLAVE DEVICE BUSY"; break;

               /* Specialized use in conjunction with programming commands. The server (or slave) is engaged in processing a
                * long–duration program command. The client (or master) should retransmit the message later when the server
                * (or slave) is free.
                */
            }
         }
         else  // Se não gerou um erro, prossegue tentando parsear a resposta
         {
            slaveAddr = _buf[6];


                 if ( ( fc == 0x01 ) || ( fc == 0x02 ) )  // Respostas a comandos de 'Read Coil Status' ou 'Read Input Status'
            {
               int bytes = _buf[8];  // Número de Bytes de Dados que virão

               if ( bytes == ( 1 + qtd / 8 ) )
               {
                  respostaValida = true;

                  b_vals = new bool [ bytes * 8 ];
                  memset( b_vals, 0, sizeof(bool) * bytes * 8 );

                  for ( int i = 0; i < bytes * 8; i++ )
                     b_vals[i] = _buf[ 9 + i/8 ] GET_BIT_IN_BYTE(i%8);
               }
            }

            else if ( ( fc == 0x03 ) || ( fc == 0x04 ) )  // Respostas a comandos de 'Read Holding Registers' ou 'Read Input Registers'
            {
               int words = _buf[8] / 2;  // Número de Words que virão

               if ( words == qtd )
               {
                  respostaValida = true;

                  i_vals = new short int [ words ];
                  memset( i_vals, 0, sizeof(short int) * words / 2 );

                  for ( int i = 0; i < words; i++ )
                     i_vals[i] = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[ 9 + i*2 ] ) );
               }
            }

            else if ( ( fc == 0x05 ) || ( fc == 0x06 ) )  // Respostas a comandos de 'Force Single Coil' ou 'Preset Single Register'
            {
               // Como as Respostas a Esses Comandos são Ecos:

               short int
                  _end = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[8]  ) ),
                  _val = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[10] ) );

               if ( ( fc == 0x05 ) && ( _val ) )
                  _val = 1;


               if ( ( end == _end ) &&  // Se o Eco do Endereço Escrito for igual ao endereço armazenado e,
                    ( val == _val ) )   // Se o Eco do Valor Escrito for igual ao valor armazenado
                  respostaValida = true;
            }

            else if ( ( fc == 0x0F ) || ( fc == 0x10 ) )  // Respostas a comandos de 'Force Multiple Coils' ou 'Preset Multiple Registers'
            {
               // Como as Respostas a Esses Comandos são Ecos:

               if ( ( end == SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[8]  ) ) ) &&  // Se o Eco do Endereço Escrito for igual ao endereço armazenado e,
                    ( qtd == SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[10] ) ) ) )   // Se o Eco da Quantidade Escrita for igual ao valor armazenado
                  respostaValida = true;
            }

            else if ( fc == 0x16 ) // Respostas a comandos de 'Force Multiple Coils' ou 'Preset Multiple Registers'
            {
               short int
                  _end = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[8]  ) ),
                  _and = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[10] ) ),
                  _or  = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[12] ) );

               if ( ( end == _end ) &&
                    ( val == (0xFFFF && _and) || (_or && ! _and) ) )
                  respostaValida = true;
            }


            if ( respostaValida )
            {
               bufferResp = new unsigned char [ _tam ];
               memcpy( bufferResp, _buf, _tam );
            }
         }
      }

   }


   return respostaValida;
}


unsigned char ParseResponseGetfc( unsigned char *_buf, int _tam )  // Analiza um buffer de resposta a um comando para determinar o function code utilizado
{
   unsigned char _fc = -1;

   if ( ( _buf && ( _tam > 7 ) ) &&   // Garante que pode ler os 7 primeiros Bytes do Header ModBus TCP
        ( _tam == SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[4] ) ) + 6 ) )  // Se o buffer veio íntegro
      _fc = _buf[7];

   return _fc;
}


unsigned int ParseResponseGetEnd( unsigned char *_buf, int _tam )  // Analiza um buffer de resposta a um comando para determinar o function code utilizado
{
   unsigned int _end = -1;

   if ( ( _buf && ( _tam > 7 ) ) &&   // Garante que pode ler os 7 primeiros Bytes do Header ModBus TCP
        ( _tam == SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[4] ) ) + 6 ) )  // Se o buffer veio íntegro
      _end = SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[0] ) );  // Se a resposta possuir o mesmo id e,

   return _end;
}


AnsiString TModBusCmd::PrintBufferCmd()
{
   AnsiString retorno;

   if ( bufferCmd )
   {
      retorno  = "<--";

      retorno += " " + IntToHex( bufferCmd[0] , 2 ) + IntToHex( bufferCmd[1] , 2 );
      retorno += " " + IntToHex( bufferCmd[2] , 2 ) + IntToHex( bufferCmd[3] , 2 );
      retorno += " " + IntToHex( bufferCmd[4] , 2 ) + IntToHex( bufferCmd[5] , 2 );
      retorno += " " + IntToHex( bufferCmd[6] , 2 );
      retorno += " " + IntToHex( bufferCmd[7] , 2 );
      retorno += " " + IntToHex( bufferCmd[8] , 2 ) + IntToHex( bufferCmd[9] , 2 );
      retorno += " " + IntToHex( bufferCmd[10], 2 ) + IntToHex( bufferCmd[11], 2 );


      if ( fc == 0x0F )
      {
         retorno += " " + IntToHex( bufferCmd[12], 2 );

         for ( unsigned char i = 0; i < bufferCmd[12]; i++ )
            retorno += " " + IntToHex( bufferCmd[13 + i], 2 );
      }


      if ( fc == 0x10 )
      {
         retorno += " " + IntToHex( bufferCmd[12], 2 );

         for ( unsigned char i = 0; i < bufferCmd[12]; i += 2 )
            retorno += " " + IntToHex( bufferCmd[13 + i], 2 ) + IntToHex( bufferCmd[14 + i], 2 );
      }
   }

   return retorno;
}


AnsiString TModBusCmd::PrintBufferResp()
{
   AnsiString retorno;

   if( bufferResp )
   {
      retorno += "-->";

      retorno += " " + IntToHex( bufferResp[0], 2 ) + IntToHex( bufferResp[1], 2 );  // Transaction ID (end)
      retorno += " " + IntToHex( bufferResp[2], 2 ) + IntToHex( bufferResp[3], 2 );  // Protocol ID (0x0000)
      retorno += " " + IntToHex( bufferResp[4], 2 ) + IntToHex( bufferResp[5], 2 );  // Length ()
      retorno += " " + IntToHex( bufferResp[6], 2 );                                 // Slave Address
      retorno += " " + IntToHex( bufferResp[7], 2 );                                 // Function Code


           if ( ( fc == 0x01 ) || ( fc == 0x02 ) )  // Respostas a comandos de 'Read Coil Status' ou 'Read Input Status'
      {
         retorno += " " + IntToHex( bufferResp[8], 2 );  // Bytes a Seguir

         for ( int i = 0, bytes = bufferResp[8]; i < bytes; i++ )
            retorno += " " + IntToHex( bufferResp[9 + i], 2 );  // Bytes de Dados
      }

      else if ( ( fc == 0x03 ) || ( fc == 0x04 ) )  // Respostas a comandos de 'Read Holding Registers' ou 'Read Input Registers'
      {
         retorno += " " + IntToHex( bufferResp[8], 2 );  // Bytes a Seguir

         for ( int i = 0, words = bufferResp[8] / 2; i < words; i++ )
            retorno += " " + IntToHex( bufferResp[9 + i*2], 2 ) + IntToHex( bufferResp[10 + i*2], 2 );  // Words de Dados
      }

      else if ( ( fc == 0x05 ) || ( fc == 0x06 ) ||  // Respostas a comandos de 'Force Single Coil' ou 'Preset Single Register'
                ( fc == 0x0F ) || ( fc == 0x10 ) )   // Respostas a comandos de 'Force Multiple Coils' ou 'Preset Multiple Registers'
      {
         retorno += " " + IntToHex( bufferCmd[8] , 2 ) + IntToHex( bufferCmd[9] , 2 );  // Endereço
         retorno += " " + IntToHex( bufferCmd[10], 2 ) + IntToHex( bufferCmd[11], 2 );  // Dado ou Qtd
      }
   }

   return retorno;
}


AnsiString TModBusCmd::PrintBuffer()
{
   return PrintBufferCmd() + "\n" + PrintBufferResp();
}


unsigned short int GetModBusBufferId ( unsigned char *_buf )
{
   return ( _buf != NULL ) ? SWAP_ENDIANNESS_16BITS( *( (unsigned short int*) & _buf[0] ) ) : 0;
}




/*
 *
 * -------------- CLASSE THREAD --------------
 *
 */

class TModBusTCPThread : public TThread  // ModBus Driver Thread
{
protected:
   void __fastcall Execute();

public:
   __fastcall TModBusTCPThread ( bool CreateSuspended );

   void __fastcall RefreshSockets();

   void InsereClientSocket( TClientSocket* S );


   #define NUM_PACOTES 128
   #define RATE_DE_ENVIO_MS 1

   bool
      respOK[NUM_PACOTES],
      doSend;

   TStringList* debugLog;

   vector< bool >
      _aguardandoResposta;

   vector< TClientSocket* >
      _vetorSocketsClientes;
};


__fastcall TModBusTCPThread::TModBusTCPThread( bool CreateSuspended = false ) : TThread( CreateSuspended )
{
   debugLog = NULL;
   doSend = true;

   for ( int i = 0; i < NUM_PACOTES; i++ )
      respOK[i] = false;
}


void __fastcall TModBusTCPThread::Execute()
{
   while(1)
      Synchronize( RefreshSockets );
}


void TModBusTCPThread::InsereClientSocket( TClientSocket* S )
{
   _vetorSocketsClientes.push_back( S );
   _aguardandoResposta.push_back( false );
}


void __fastcall TModBusTCPThread::RefreshSockets()
{
   static unsigned short int count = 0;

   if ( count >= NUM_PACOTES )
      doSend = false;

   static TTimeStamp T;

   for ( int i = 0, qtd = _vetorSocketsClientes.size(); i < qtd; i++  )
   {
      static TClientSocket* sock = _vetorSocketsClientes[i];

//      if ( ! sock->Active )
//         _aguardandoResposta[i] = false;

//      else

      if (  sock->Active )
      {
/*
         if ( ! _aguardandoResposta[i] )
         {
            unsigned char buff[] = { 0,0, 0,0, 0,6, 1,3, 0x80, 0xE8, 0,2 };
            
            sock->Socket->SendBuf( buff, 12 );
            _aguardandoResposta[i] = true;


            if ( debugLog )
            {
               static AnsiString temp;

               temp = "";
               for ( int i = 0; i < 12; i++ )
                  temp += IntToHex( (unsigned char) buff[i], 2 );

               debugLog->Lines->Add( FormatDateTime( "nn:ss:zzz", Now() ) + "\t <-- " + temp );
            }
         }
*/

         if ( sock->Socket->ReceiveLength() )
         {
            static int tam;

            static unsigned char *buf = new unsigned char [ tam = sock->Socket->ReceiveLength() ];

            sock->Socket->ReceiveBuf( buf, tam );


            unsigned short int id = SWAP_ENDIANNESS_16BITS(  *( (unsigned short int*) & buf[0] )  );

            if ( id < NUM_PACOTES )
               respOK[ id ] = true;


            _aguardandoResposta[i] = false;


            if ( debugLog )
            {
               static AnsiString temp;

               temp = "";
               for ( int i = 0; i < tam; i++ )
                  temp += IntToHex( (unsigned char) buf[i], 2 );

               debugLog->Add( FormatDateTime( "nn:ss:zzz", Now() ) + "\t --> " + temp );
            }
         }

         if ( doSend )  // Desliga envio do socket
         {
            T = DateTimeToTimeStamp( Now() );
            T.Time += RATE_DE_ENVIO_MS;
            while ( DateTimeToTimeStamp( Now() ).Time < T.Time );


            {
               unsigned char buff[] = { 0,0, 0,0, 0,6, 1,3, 0x80, 0xE8, 0,2 };

               *( (unsigned short int*) & buff[0] ) = SWAP_ENDIANNESS_16BITS( count );
               count++;


               sock->Socket->SendBuf( buff, 12 );
               _aguardandoResposta[i] = true;


               if ( debugLog )
               {
                  static AnsiString temp;

                  temp = "";
                  for ( int i = 0; i < 12; i++ )
                     temp += IntToHex( (unsigned char) buff[i], 2 );

                  debugLog->Add( FormatDateTime( "nn:ss:zzz", Now() ) + "\t <-- " + temp );
               }               
            }
         }
         else
         {
            bool todosOK = true;
            int perdidos = 0;

            for ( int i = 0; i < NUM_PACOTES; i++ )
               if ( ! respOK[i] )
               {
                  todosOK = false;
                  perdidos++;
               }

            if ( todosOK )
               debugLog->Add( "NENHUM PACOTE PACOTE PERDIDO." );
            else
               debugLog->Add( "PERDIDOS: " + AnsiString( perdidos ) + "/" + AnsiString( NUM_PACOTES ) + " - " + FormatFloat( "0.###", ( (float) perdidos / (float) NUM_PACOTES ) * 100.0 ) + "%" );
         }
      }
   }
}




/*
 *
 * -------------- CLASSE DRIVER MODBUS --------------
 *
 */

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