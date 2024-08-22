//---------------------------------------------------------------------------

#ifndef AnalogicasH
#define AnalogicasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAnalogicas : public TForm
{
__published:	// IDE-managed Components
   TLabel *lblAnalog02;
   TLabel *Label4;
   TLabel *Label3;
   TLabel *lblAnalog01;
   TLabel *lblAnalog03;
   TLabel *lblAnalog04;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *lblAnalog08;
   TLabel *lblAnalog07;
   TLabel *lblAnalog06;
   TLabel *lblAnalog05;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *Label14;
   TLabel *Label15;
   TLabel *lblAnalog16;
   TLabel *lblAnalog15;
   TLabel *lblAnalog14;
   TLabel *lblAnalog13;
   TLabel *lblAnalog12;
   TLabel *lblAnalog11;
   TLabel *lblAnalog10;
   TLabel *lblAnalog09;
   TLabel *Label24;
   TLabel *Label25;
   TLabel *Label26;
   TLabel *Label27;
   TLabel *Label28;
   TLabel *Label29;
   TLabel *Label30;
   TLabel *Label31;
   TLabel *lblAnalog18;
   TLabel *Label33;
   TLabel *Label34;
   TLabel *lblAnalog17;
   TLabel *lblAnalog19;
   TLabel *lblAnalog20;
   TLabel *Label38;
   TLabel *Label39;
   TLabel *lblAnalog24;
   TLabel *lblAnalog23;
   TLabel *lblAnalog22;
   TLabel *lblAnalog21;
   TLabel *Label44;
   TLabel *Label45;
   TLabel *Label46;
   TLabel *Label47;
   TLabel *lblAnalog32;
   TLabel *lblAnalog31;
   TLabel *lblAnalog30;
   TLabel *lblAnalog29;
   TLabel *lblAnalog28;
   TLabel *lblAnalog27;
   TLabel *lblAnalog26;
   TLabel *lblAnalog25;
   TLabel *Label56;
   TLabel *Label57;
   TLabel *Label58;
   TLabel *Label59;
   TLabel *Label60;
   TLabel *Label61;
   TLabel *Label62;
   TLabel *Label63;
   TLabel *lblAnalog34;
   TLabel *Label2;
   TLabel *Label5;
   TLabel *lblAnalog33;
   TLabel *lblAnalog35;
   TLabel *lblAnalog36;
   TLabel *Label11;
   TLabel *Label16;
   TLabel *lblAnalog40;
   TLabel *lblAnalog39;
   TLabel *lblAnalog38;
   TLabel *lblAnalog37;
   TLabel *Label21;
   TLabel *Label22;
   TLabel *Label23;
   TLabel *Label32;
   TLabel *lblAnalog46;
   TLabel *lblAnalog45;
   TLabel *lblAnalog44;
   TLabel *lblAnalog43;
   TLabel *lblAnalog42;
   TLabel *lblAnalog41;
   TLabel *Label49;
   TLabel *Label50;
   TLabel *Label51;
   TLabel *Label52;
   TLabel *Label53;
   TLabel *Label54;
   TTimer *tmrPosicao;
   TTimer *Leitura;
   TButton *btnFechar;
        void __fastcall tmrPosicaoTimer(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
   void __fastcall btnFecharClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmAnalogicas(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAnalogicas *frmAnalogicas;
//---------------------------------------------------------------------------
#endif
