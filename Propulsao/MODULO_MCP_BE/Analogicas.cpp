//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Analogicas.h"
#include "Principal.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAnalogicas *frmAnalogicas;
//---------------------------------------------------------------------------
__fastcall TfrmAnalogicas::TfrmAnalogicas(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAnalogicas::tmrPosicaoTimer(TObject *Sender)
{
// Grante que a tela não ultrapassa os limites da janela Pai

   if ( this->Top  < 0 ) this->Top  = 0;
   if ( this->Left < 0 ) this->Left = 0;

   if ( this->Top  + this->Height > this->Parent->ClientHeight ) this->Top  = this->Parent->ClientHeight - this->Height;
   if ( this->Left + this->Width  > this->Parent->ClientWidth  ) this->Left = this->Parent->ClientWidth  - this->Width;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAnalogicas::FormShow(TObject *Sender)
{
        tmrPosicao->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAnalogicas::FormHide(TObject *Sender)
{
        tmrPosicao->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAnalogicas::btnFecharClick(TObject *Sender)
{
   frmAnalogicas->Hide();   
}
//---------------------------------------------------------------------------

