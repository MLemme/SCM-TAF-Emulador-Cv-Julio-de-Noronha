//---------------------------------------------------------------------------

#ifndef PermissivosH
#define PermissivosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPermissivos : public TForm
{
__published:	// IDE-managed Components
        TShape *shpTQDREN_NIVELALTO;
        TLabel *Label22;
        TShape *shpPERMPTDATLASOK;
        TLabel *Label23;
        TShape *shpPERMPTDOLNVOK;
        TLabel *Label24;
        TShape *shpPERMPTDLUBOK;
        TLabel *Label25;
        TShape *shpABVFEC;
        TLabel *Label26;
        TShape *shpPERMPTDODPOK;
        TLabel *Label1;
        TShape *shpPERMPTDODTOK;
        TLabel *Label2;
        TShape *shpPLAEMIDLE;
        TLabel *Label3;
        TShape *shpLIMPLAATUANDO;
        TLabel *Label4;
        TShape *shpPERMPTDIGNOK;
        TLabel *Label5;
        TShape *shpPERMPTDNGGBX;
        TLabel *Label6;
        TShape *shpVVEXTODFECH;
        TLabel *Label7;
        TShape *shpASOVFECH;
        TLabel *Label8;
        TShape *shpARRANQUEOK;
        TLabel *Label9;
        TShape *shpPERMPTDSPNTPBX;
        TLabel *Label10;
        TButton *shpABV;
        TButton *btnVVEXTOD;
        TButton *btnASOVFECH;
        TButton *btnTQDREN_NIVELALTO;
        TButton *btnPERMPTDATLASOK;
        TButton *btnPERMPTDOLNVOK;
        TButton *btnPERMPTDLUBOK;
        TButton *btnPERMPTDIGNOK;
        TButton *btnPERMPTDODPOK;
        TButton *btnPERMPTDODTOK;
        TButton *btnPLAEMIDLE;
        TButton *btnLIMPLAATUANDO;
        TButton *btnPERMPTDNGGBX;
        TButton *btnARRANQUEOK;
        TButton *btnPERMPTDSPNTPBX;
        TShape *Shape2;
        TButton *btnFechar;
        void __fastcall btnTQDREN_NIVELALTOClick(TObject *Sender);
        void __fastcall btnPERMPTDATLASOKClick(TObject *Sender);
        void __fastcall btnPERMPTDOLNVOKClick(TObject *Sender);
        void __fastcall btnPERMPTDLUBOKClick(TObject *Sender);
        void __fastcall shpABVClick(TObject *Sender);
        void __fastcall btnPERMPTDODPOKClick(TObject *Sender);
        void __fastcall btnPERMPTDODTOKClick(TObject *Sender);
        void __fastcall btnPLAEMIDLEClick(TObject *Sender);
        void __fastcall btnLIMPLAATUANDOClick(TObject *Sender);
        void __fastcall btnPERMPTDIGNOKClick(TObject *Sender);
        void __fastcall btnPERMPTDNGGBXClick(TObject *Sender);
        void __fastcall btnVVEXTODClick(TObject *Sender);
        void __fastcall btnASOVFECHClick(TObject *Sender);
        void __fastcall btnARRANQUEOKClick(TObject *Sender);
        void __fastcall btnPERMPTDSPNTPBXClick(TObject *Sender);
        void __fastcall btnFecharClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPermissivos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPermissivos *frmPermissivos;
//---------------------------------------------------------------------------
#endif
