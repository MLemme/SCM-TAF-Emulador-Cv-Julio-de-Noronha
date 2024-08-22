//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BBAELPN.h"
#include "Principal.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmBBAELPN *frmBBAELPN;
//---------------------------------------------------------------------------
__fastcall TfrmBBAELPN::TfrmBBAELPN(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmBBAELPN::FormShow(TObject *Sender)
{
        tmrPosicao->Enabled = true;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmBBAELPN::FormHide(TObject *Sender)
{
        tmrPosicao->Enabled = false;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmBBAELPN::tmrPosicaoTimer(TObject *Sender)
{
// Grante que a tela não ultrapassa os limites da janela Pai

   if ( this->Top  < 0 ) this->Top  = 0;
   if ( this->Left < 0 ) this->Left = 0;

   if ( this->Top  + this->Height > this->Parent->ClientHeight ) this->Top  = this->Parent->ClientHeight - this->Height;
   if ( this->Left + this->Width  > this->Parent->ClientWidth  ) this->Left = this->Parent->ClientWidth  - this->Width;
}
//---------------------------------------------------------------------------
