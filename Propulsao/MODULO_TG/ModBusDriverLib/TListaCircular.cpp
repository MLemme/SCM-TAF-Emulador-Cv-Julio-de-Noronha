
/*
 *  CLASSE LISTA CIRCULAR GEN�RICA - TListaCircular
 *
 *  - Implementa uma classe para gerir uma lista circular
 *
 *  Features:
 *
 *  >
 *
 *
 */


#ifndef __TLISTACIRCULAR_CPP
#define __TLISTACIRCULAR_CPP

 
#ifndef __DEQUE_H
#include <deque.h>
#endif


template < class tipo_el >
class TListaCircular
{
public:

   TListaCircular();
  ~TListaCircular();


   void     push( tipo_el el );
   void     pop();
   
   tipo_el  get();
   tipo_el  peek();
   void     rewind();

   void     clear();
   int      size();


private:

   int idx;

   deque < tipo_el >
      lista;
};



template < class tipo_el >
TListaCircular < tipo_el >::TListaCircular()
{
   idx = 0;
}


template < class tipo_el >
TListaCircular < tipo_el >::~TListaCircular()
{
   lista.clear();
}


template < class tipo_el >
void TListaCircular < tipo_el >::push( tipo_el el )
{
   lista.push_back( el );
}


template < class tipo_el >
void TListaCircular < tipo_el >::pop()
{
   lista.erase( lista.begin() + idx );
   
   if ( idx >= lista.size() )
      idx = 0;
}


template < class tipo_el >
tipo_el TListaCircular < tipo_el >::get()
{
   tipo_el retorno = lista[idx++];

   if ( idx >= lista.size() )
      idx = 0;

   return retorno;
}


template < class tipo_el >
tipo_el TListaCircular < tipo_el >::peek()
{
   tipo_el retorno = lista[idx];

   return retorno;
}


template < class tipo_el >
void TListaCircular < tipo_el >::rewind()
{
   idx = 0;
}


template < class tipo_el >
void TListaCircular < tipo_el >::clear()
{
   lista.clear();
   idx = 0;
}


template < class tipo_el >
int TListaCircular < tipo_el >::size()
{
   return lista.size();
}

#endif
