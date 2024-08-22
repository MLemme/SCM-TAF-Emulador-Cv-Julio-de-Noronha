//---------------------------------------------------------------------------

#ifndef BBAELPNH
#define BBAELPNH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmBBAELPN : public TForm
{
__published:	// IDE-managed Components
        TTimer *tmrPosicao;
        TShape *shpPartirBBAOLETH1;
        TLabel *Label25;
        TShape *shpPararBBAOLETH1;
        TLabel *Label27;
        TLabel *Label1;
        TLabel *Label2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall tmrPosicaoTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmBBAELPN(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBBAELPN *frmBBAELPN;
//---------------------------------------------------------------------------
#endif
