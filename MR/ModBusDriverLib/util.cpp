
/*
 *  AGREGADO DE MACROS, TIPOS E FUN��ES �TEIS
 *
 *  >
 *
 *
 */


#ifndef __UTIL_CPP
#define __UTIL_CPP


#ifndef __DEQUE_H
#include <deque.h>
#endif


#define  GET_BIT(a,b)  ( ( a &  (0x01 << b) ) != 0 )
#define  SET_BIT(a,b)    ( a |  (0x01 << b) )
#define  CLR_BIT(a,b)    ( a & ~(0x01 << b) )


// Fun��es de acesso a mem�ria com tipo arbitr�rio

template <typename Type>
void* writeToMemAddr( void* addr, Type val )
{
   return & ( *( (Type*) addr ) = val );
}


template <typename Type>
Type readMemAs( void* addr )
{
   return *( (Type*) addr );
}


template <typename Type>
Type readMemAs( void* addr, Type val )
{
   return *( (Type*) addr );
}


// Fun��es de altera��o de 'Endianess', para adequa��o de tr�fego de rede

short int toggleEndianess( short int i )
{
   return ( 0xFF00 & (i << 8) ) | ( 0x00FF & (i >> 8) );
}


int toggleEndianess( int i )
{
   return ( 0x00FF00FF & (i >> 8) ) | ( 0xFF00FF00 & (i << 8) );
}


// Estrutura que encapsula um Buffer de Bytes

typedef struct byteBuffStruct
{
   byteBuffStruct()
   { tam = 0; buf = NULL; }

   byteBuffStruct( unsigned int _tam )
   { tam = _tam; buf = new unsigned char [tam]; memset( buf, 0, tam ); }

   byteBuffStruct( unsigned char *_buf, unsigned int _tam )
   { tam = _tam; buf = new unsigned char [tam]; memcpy( buf, _buf, _tam ); }

   byteBuffStruct( byteBuffStruct* outro )
   { tam = outro->tam; buf = new unsigned char [tam]; memcpy( buf, outro->buf, tam ); }


   ~byteBuffStruct()
   { if ( buf ) delete[] buf; }

   unsigned char *buf;
   unsigned int tam;

} byteBuffStruct;

#endif
